$ErrorActionPreference = "Stop"

# Generates `prebuilt_demo/windows-mingw-x64/` from the existing `prebuilt/` folder.
# The goal is to provide a trimmed-demo import directory containing:
#   - include/ (public headers)
#   - bin/     (DLLs)
#   - lib/     (import libs: *.dll.a for MinGW)

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = Resolve-Path (Join-Path $scriptDir "..")

$arch = "windows-mingw-x64"
$srcPrebuiltRoot = Join-Path $repoRoot "prebuilt"
$srcIncludeRoot = Join-Path $srcPrebuiltRoot "include"
$srcArchRoot = Join-Path $srcPrebuiltRoot $arch

$dstDemoRoot = Join-Path $repoRoot "prebuilt_demo"
$dstArchRoot = Join-Path $dstDemoRoot $arch
$dstIncludeRoot = Join-Path $dstArchRoot "include"
$dstBinRoot = Join-Path $dstArchRoot "bin"
$dstLibRoot = Join-Path $dstArchRoot "lib"

function Copy-DirIfExists([string] $from, [string] $to) {
  if (-not (Test-Path $from)) {
    throw "Missing required source directory: $from"
  }
  if (Test-Path $to) {
    Remove-Item -Recurse -Force $to
  }
  New-Item -ItemType Directory -Force -Path $to | Out-Null
  Copy-Item -Recurse -Force (Join-Path $from "*") $to
}

Write-Host "== Generate prebuilt_demo =="
Write-Host "repoRoot: $repoRoot"
Write-Host "arch: $arch"

Copy-DirIfExists $srcIncludeRoot $dstIncludeRoot
Copy-DirIfExists (Join-Path $srcArchRoot "bin") $dstBinRoot
Copy-DirIfExists (Join-Path $srcArchRoot "lib") $dstLibRoot

Write-Host "Done. Output:"
Write-Host "  $dstArchRoot"

$ErrorActionPreference = "Stop"

# Generates `prebuilt_demo/windows-mingw-x64/`.
# - Starts from the existing `prebuilt/` folder (headers + dependency DLLs)
# - Optionally rebuilds selected DLLs from the current source tree and
#   overwrites them into `prebuilt_demo/` so the trimmed demo uses the patched binaries.
#
# The goal is to provide a trimmed-demo import directory containing:
#   - include/ (public headers)
#   - bin/     (DLLs)
#   - lib/     (import libs: *.dll.a for MinGW)

param(
  [string] $BuildDir = "",
  [switch] $RebuildPatchedLibs = $true
)

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = Resolve-Path (Join-Path $scriptDir "..")

$arch = "windows-mingw-x64"
$srcPrebuiltRoot = Join-Path $repoRoot "prebuilt"
$srcIncludeRoot = Join-Path $srcPrebuiltRoot "include"
$srcArchRoot = Join-Path $srcPrebuiltRoot $arch

$dstDemoRoot = Join-Path $repoRoot "prebuilt_demo"
$dstArchRoot = Join-Path $dstDemoRoot $arch
$dstIncludeRoot = Join-Path $dstArchRoot "include"
$dstBinRoot = Join-Path $dstArchRoot "bin"
$dstLibRoot = Join-Path $dstArchRoot "lib"

function Copy-DirIfExists([string] $from, [string] $to) {
  if (-not (Test-Path $from)) {
    throw "Missing required source directory: $from"
  }
  if (Test-Path $to) {
    Remove-Item -Recurse -Force $to
  }
  New-Item -ItemType Directory -Force -Path $to | Out-Null
  Copy-Item -Recurse -Force (Join-Path $from "*") $to
}

function Copy-FileIfExists([string] $from, [string] $toDir) {
  if (-not (Test-Path $from)) {
    throw "Missing required file: $from"
  }
  New-Item -ItemType Directory -Force -Path $toDir | Out-Null
  Copy-Item -Force $from $toDir
}

Write-Host "== Generate prebuilt_demo =="
Write-Host "repoRoot: $repoRoot"
Write-Host "arch: $arch"

Copy-DirIfExists $srcIncludeRoot $dstIncludeRoot
Copy-DirIfExists (Join-Path $srcArchRoot "bin") $dstBinRoot
Copy-DirIfExists (Join-Path $srcArchRoot "lib") $dstLibRoot

if ($RebuildPatchedLibs) {
  if ([string]::IsNullOrWhiteSpace($BuildDir)) {
    $BuildDir = Join-Path $repoRoot "build/patch-prebuilt"
  }
  $BuildDir = Join-Path $BuildDir "."  # normalize
  New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null
  $BuildDir = Resolve-Path $BuildDir
  Write-Host "Config + rebuild patched libs in: $BuildDir"

  # Configure a dedicated build tree that enables only the libs we patch.
  & cmake -S "$repoRoot" -B "$BuildDir" -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DTEACH_DEMO_PATCH_PREBUILT_LIBS=ON | Write-Host
  & cmake --build "$BuildDir" --target GeneralTools Dialog | Write-Host

  $builtBin = Join-Path $BuildDir "bin"
  $builtLib = Join-Path $BuildDir "bin/libs"

  $patched = @(
    "GeneralTools",
    "Dialog"
  )

  foreach ($name in $patched) {
    $dll = Join-Path $builtBin ("lib{0}.dll" -f $name)
    $implib = Join-Path $builtLib ("lib{0}.dll.a" -f $name)
    Write-Host "Overwrite prebuilt_demo with: $name"
    Copy-FileIfExists $dll $dstBinRoot
    Copy-FileIfExists $implib $dstLibRoot
  }
}

Write-Host "Done. Output:"
Write-Host "  $dstArchRoot"

