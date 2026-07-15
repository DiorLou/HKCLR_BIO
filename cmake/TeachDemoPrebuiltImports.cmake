cmake_minimum_required(VERSION 3.16)

# Imported targets for the trimmed "teach demo" build.
#
# This module is meant to be included from `src/libs/CMakeLists.txt` *before*
# we build the remaining source-code targets (Communication/TeachController).
#
# It creates `SHARED IMPORTED` targets for dependency DLLs so the Core /
# SimulationForm / TeachContainer plugins can still compile and link.

set(_TEACH_DEMO_ARCH "windows-mingw-x64")

# Prefer `prebuilt_demo/<arch>/...` if present; otherwise fall back to:
# 1) already-built outputs in `${PROJECT_BINARY_DIR}/bin`
# 2) existing `prebuilt/<arch>/...`
set(_TEACH_DEMO_PREBUILT_DEMO_ROOT "${PROJECT_SOURCE_DIR}/prebuilt_demo/${_TEACH_DEMO_ARCH}")
set(_TEACH_DEMO_PREBUILT_ROOT "${PROJECT_SOURCE_DIR}/prebuilt/${_TEACH_DEMO_ARCH}")
set(_TEACH_DEMO_BUILD_BIN_ROOT "${PROJECT_BINARY_DIR}/bin")
set(_TEACH_DEMO_BUILD_LIB_ROOT "${PROJECT_BINARY_DIR}/bin/libs")
set(_TEACH_DEMO_INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/prebuilt/include")

if(EXISTS "${_TEACH_DEMO_PREBUILT_DEMO_ROOT}/bin")
  set(_TEACH_DEMO_PREBUILT_ROOT "${_TEACH_DEMO_PREBUILT_DEMO_ROOT}")
  set(_TEACH_DEMO_INCLUDE_ROOT "${_TEACH_DEMO_PREBUILT_DEMO_ROOT}/include")
elseif(NOT EXISTS "${_TEACH_DEMO_PREBUILT_ROOT}")
  # If prebuilt folders are missing, we will still try build outputs.
  set(_TEACH_DEMO_PREBUILT_ROOT "${PROJECT_BINARY_DIR}")
endif()

function(_teach_demo_import_shared target_name)
  if(TARGET "${target_name}")
    return()
  endif()

  # Convention in this project:
  #   DLL:  <root>/bin/lib${Target}.dll
  #   Implib: <root>/lib/lib${Target}.dll.a (MinGW)
  #
  # For already-built outputs, we expect:
  #   DLL:   ${PROJECT_BINARY_DIR}/bin/lib${Target}.dll
  #   Implib:${PROJECT_BINARY_DIR}/bin/libs/lib${Target}.dll.a
  set(_dll_candidates
    "${_TEACH_DEMO_PREBUILT_ROOT}/bin/lib${target_name}.dll"
    "${_TEACH_DEMO_BUILD_BIN_ROOT}/lib${target_name}.dll"
  )
  set(_implib_candidates
    "${_TEACH_DEMO_PREBUILT_ROOT}/lib/lib${target_name}.dll.a"
    "${_TEACH_DEMO_BUILD_LIB_ROOT}/lib${target_name}.dll.a"
  )

  set(_dll_path "")
  foreach(_cand IN LISTS _dll_candidates)
    if(EXISTS "${_cand}")
      set(_dll_path "${_cand}")
      break()
    endif()
  endforeach()
  set(_implib "")
  foreach(_cand IN LISTS _implib_candidates)
    if(EXISTS "${_cand}")
      set(_implib "${_cand}")
      break()
    endif()
  endforeach()

  if(NOT _dll_path)
    message(FATAL_ERROR "Missing imported DLL for target '${target_name}'. Searched: ${_dll_candidates}")
  endif()
  if(NOT _implib)
    message(FATAL_ERROR "Missing imported implib for target '${target_name}'. Searched: ${_implib_candidates}")
  endif()

  add_library("${target_name}" SHARED IMPORTED)
  set_target_properties("${target_name}" PROPERTIES
    IMPORTED_LOCATION "${_dll_path}"
    IMPORTED_IMPLIB   "${_implib}"
  )

  # Headers are shared across many DLLs when the prebuilt package contains an
  # include directory.  The trimmed package may contain only bin/ and lib/;
  # publishing a missing path makes CMake reject every imported target during
  # the generate step.
  if(IS_DIRECTORY "${_TEACH_DEMO_INCLUDE_ROOT}")
    target_include_directories("${target_name}" INTERFACE
      "${_TEACH_DEMO_INCLUDE_ROOT}"
    )
  endif()

  # Most libs in the original build export include dirs pointing at their
  # own source folders. Since the on-disk `prebuilt/include` may be
  # incomplete in this trimmed repo, we supplement key include dirs here.
  if(target_name STREQUAL "Instance")
    target_include_directories("${target_name}" INTERFACE
      "${PROJECT_SOURCE_DIR}/src/libs/utils/instance"
    )
  endif()

  if(target_name STREQUAL "Authority")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/authority")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/authority"
      )
    endif()
  endif()

  if(target_name STREQUAL "Utils")
    target_include_directories("${target_name}" INTERFACE
      "${PROJECT_SOURCE_DIR}/src/libs/utils/utils"
    )
  endif()

  if(target_name STREQUAL "CobotLog")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/cobotlog")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/cobotlog"
      )
    endif()
  endif()

  # utils/* 里的库（目标名与目录名大小写不完全一致时，这里显式补齐）
  if(target_name STREQUAL "DataBase")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/database")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/database"
      )
    endif()
  endif()

  if(target_name STREQUAL "Common")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/common")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/common"
      )
    endif()
  endif()

  if(target_name STREQUAL "GeneralTools")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/generaltools")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/generaltools"
      )
    endif()
  endif()

  if(target_name STREQUAL "CustomComponent")
    set(_cc_root "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent")
    if(EXISTS "${_cc_root}")
      target_include_directories("${target_name}" INTERFACE "${_cc_root}")
    endif()
    # Headers use flat includes: "toolbox.h", "resolutionutils.h".
    if(EXISTS "${_cc_root}/toolbox")
      target_include_directories("${target_name}" INTERFACE "${_cc_root}/toolbox")
    endif()
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/generaltools")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/generaltools"
      )
    endif()
    if(EXISTS "${_cc_root}/comboBox")
      target_include_directories("${target_name}" INTERFACE "${_cc_root}/comboBox")
    endif()
    if(EXISTS "${_cc_root}/cc_lineedit")
      target_include_directories("${target_name}" INTERFACE "${_cc_root}/cc_lineedit")
    endif()
  endif()

  # Flat includes: "communicationengine.h", "backlashcompensationinterface.h", etc.
  # Also needs InoRobBusiness / Include shims for GlobalDataTypes.h and Controller/* headers.
  if(target_name STREQUAL "Communication")
    set(_comm_root "${PROJECT_SOURCE_DIR}/src/libs/communication")
    if(EXISTS "${_comm_root}")
      target_include_directories("${target_name}" INTERFACE "${_comm_root}")
    endif()
    if(EXISTS "${_comm_root}/threadengine")
      target_include_directories("${target_name}" INTERFACE "${_comm_root}/threadengine")
    endif()
    if(EXISTS "${_comm_root}/interfaceconversionlayer")
      target_include_directories("${target_name}" INTERFACE "${_comm_root}/interfaceconversionlayer")
    endif()
    set(_irs "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio")
    foreach(_sub IN ITEMS
        ""
        "/Include"
        "/InoRobUtil/Include"
        "/InoRobBusiness"
        "/InoRobBusiness/Include"
        "/InoRobUdf"
        "/third_party/include"
      )
      if(EXISTS "${_irs}${_sub}")
        target_include_directories("${target_name}" INTERFACE "${_irs}${_sub}")
      endif()
    endforeach()
  endif()

  # PluginEngine public headers (e.g. iplugin.h) live only under the source tree;
  # they are not always copied into `prebuilt/include`.
  if(target_name STREQUAL "PluginEngine")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/pluginengine")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/pluginengine"
      )
    endif()
  endif()

  if(target_name STREQUAL "VirtualKeyboard")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/virtualkeyboard")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/virtualkeyboard"
      )
    endif()
  endif()

  if(target_name STREQUAL "Tcp")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/tcp")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/tcp"
      )
    endif()
    if(TARGET Qt${QT_VERSION_MAJOR}::Network)
      target_link_libraries("${target_name}" INTERFACE Qt${QT_VERSION_MAJOR}::Network)
    endif()
  endif()

  if(target_name STREQUAL "MultiThreadTools")
    if(EXISTS "${PROJECT_SOURCE_DIR}/src/libs/utils/multithreadtools")
      target_include_directories("${target_name}" INTERFACE
        "${PROJECT_SOURCE_DIR}/src/libs/utils/multithreadtools"
      )
    endif()
  endif()

  # Some headers are included with absolute filenames (e.g. "labeldata.h")
  # rather than via sub-paths. In the original build this comes from
  # Metatype's target include directories, so we replicate the relevant
  # metatype subdirectories here.
  if(target_name STREQUAL "Metatype")
    set(_metatype_root "${PROJECT_SOURCE_DIR}/src/libs/utils/metatype")
    set(_metatype_includes "${_metatype_root}")
    foreach(_subdir IN ITEMS
      calibrate
      condition
      other
      peripheral
      project
      motion
      ioinfo
      authority
      safety
    )
      if(EXISTS "${_metatype_root}/${_subdir}")
        list(APPEND _metatype_includes "${_metatype_root}/${_subdir}")
      endif()
    endforeach()

    target_include_directories("${target_name}" INTERFACE ${_metatype_includes})
  endif()
endfunction()

# Mimic the variable that the original `InoRobStudio` CMake provides.
# `Communication` uses it as `PUBLIC_INCLUDES`.
#
# IMPORTANT:
# The on-disk `prebuilt/include` folder may be incomplete in your working
# tree. To keep this trimmed build config working, we point the include list
# at the headers in `src/libs/InoRobStudio/` (headers only; we still link
# the dependency DLLs as IMPORTED targets).
set(_TEACH_DEMO_INOROBSTUDIO_ROOT "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio")
set(InoRobStudio_Public_Include_List
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/Include"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/InoRobUtil"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/InoRobUtil/Include"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/InoRobBusiness"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/InoRobBusiness/Include"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/InoRobUdf"
  "${_TEACH_DEMO_INOROBSTUDIO_ROOT}/third_party/include"
  CACHE INTERNAL "InoRobStudio_Public_Include_List for trimmed demo" FORCE
)

# Libraries required by:
#   - Core plugin (PUBLIC_DEPENDS list in `src/plugins/coreplugin/CMakeLists.txt`)
#   - SimulationForm plugin / TeachContainer plugin (dependency plugin lists)
#   - Communication library (DEPENDS list in `src/libs/communication/CMakeLists.txt`)
#
# NOTE: We intentionally DO NOT import `Communication` / `TeachController`,
# because those are still built from source in the trimmed `src/libs`.
set(_TEACH_DEMO_IMPORTED_LIBS
  Authority
  Utils
  Instance
  Metatype
  GeneralTools
  MultiThreadTools
  CustomComponent
  DataBase
  Common
  Tcp
  PluginEngine
  Dialog
  VirtualKeyboard
  CobotLog
  FlowWidget
  Simulator
  OSUpdate
  Linker
  DataService

  # Communication is very large and can fail to build with MinGW (ICE / too-big
  # object sections during MOC). For the trimmed demo we import its prebuilt DLL.
  Communication

  InoRobUdf
  InoRobUtil
  InoRobLog
  InoRobBusiness
)

# Allow selected libs to be built from source in the trimmed build.
# If these vars are set by the including CMakeLists, we skip creating IMPORTED
# targets so `add_subdirectory()` can define them normally.
if(TEACH_DEMO_BUILD_GENERALTOOLS_FROM_SOURCE)
  list(REMOVE_ITEM _TEACH_DEMO_IMPORTED_LIBS GeneralTools)
endif()
if(TEACH_DEMO_BUILD_DIALOG_FROM_SOURCE)
  list(REMOVE_ITEM _TEACH_DEMO_IMPORTED_LIBS Dialog)
endif()
if(TEACH_DEMO_BUILD_COMMUNICATION_FROM_SOURCE)
  list(REMOVE_ITEM _TEACH_DEMO_IMPORTED_LIBS Communication)
endif()

foreach(_lib IN LISTS _TEACH_DEMO_IMPORTED_LIBS)
  _teach_demo_import_shared("${_lib}")
endforeach()

# Core / SimulationForm / TeachContainer link the IMPORTED targets above, but with
# CMake 3.27 + Ninja + MinGW the INTERFACE_INCLUDE_DIRECTORIES from those IMPORTED
# libraries often do not appear on the *plugin* compile line (they do for normal
# SHARED libs such as TeachController). Aggregate the same include layout here and
# attach it from `src/plugins/CMakeLists.txt` via `target_link_libraries(... PRIVATE ...)`.
if(NOT TARGET TeachDemoPluginCompileIface)
  add_library(TeachDemoPluginCompileIface INTERFACE)
  set(_tdp_iface)
  if(IS_DIRECTORY "${_TEACH_DEMO_INCLUDE_ROOT}")
    list(APPEND _tdp_iface "${_TEACH_DEMO_INCLUDE_ROOT}")
  endif()
  # Keep InoRobStudio paths minimal (full list is long and breaks Qt AUTOMOC on Windows cmd.exe).
  foreach(_root IN ITEMS
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/Include"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/InoRobUtil/Include"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/InoRobBusiness"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/InoRobBusiness/Include"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/InoRobUdf"
      "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/third_party/include"
    )
    if(EXISTS "${_root}")
      list(APPEND _tdp_iface "${_root}")
    endif()
  endforeach()
  foreach(_root IN ITEMS
      "${PROJECT_SOURCE_DIR}/src/libs"
      "${PROJECT_SOURCE_DIR}/src/libs/pluginengine"
      "${PROJECT_SOURCE_DIR}/src/libs/authority"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/instance"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/utils"
      "${PROJECT_SOURCE_DIR}/src/libs/cobotlog"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/database"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/common"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/generaltools"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent/cc_define"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent/cc_lineedit"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent/toolbox"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/customcomponent/comboBox"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/tcp"
      "${PROJECT_SOURCE_DIR}/src/libs/utils/multithreadtools"
      "${PROJECT_SOURCE_DIR}/src/libs/dialog"
      "${PROJECT_SOURCE_DIR}/src/libs/virtualkeyboard"
      "${PROJECT_SOURCE_DIR}/src/libs/simulator"
      "${PROJECT_SOURCE_DIR}/src/libs/flowwidget"
      "${PROJECT_SOURCE_DIR}/src/libs/communication"
      "${PROJECT_SOURCE_DIR}/src/libs/communication/threadengine"
      "${PROJECT_SOURCE_DIR}/src/libs/communication/interfaceconversionlayer"
    )
    if(EXISTS "${_root}")
      list(APPEND _tdp_iface "${_root}")
    endif()
  endforeach()
  set(_tdp_metatype "${PROJECT_SOURCE_DIR}/src/libs/utils/metatype")
  list(APPEND _tdp_iface "${_tdp_metatype}")
  foreach(_subdir IN ITEMS calibrate condition other peripheral project motion ioinfo authority safety)
    if(EXISTS "${_tdp_metatype}/${_subdir}")
      list(APPEND _tdp_iface "${_tdp_metatype}/${_subdir}")
    endif()
  endforeach()
  target_include_directories(TeachDemoPluginCompileIface INTERFACE ${_tdp_iface})

  # Some generators/toolchains (notably MinGW) may still emit link items as
  # `-lFoo` instead of an absolute path to `libFoo.dll.a`. Ensure the directories
  # that contain import libs are on the link search path for trimmed plugins.
  set(_tdp_link_dirs "")
  foreach(_dir IN ITEMS
      "${_TEACH_DEMO_PREBUILT_ROOT}/lib"
      "${_TEACH_DEMO_BUILD_LIB_ROOT}"
    )
    if(EXISTS "${_dir}")
      list(APPEND _tdp_link_dirs "${_dir}")
    endif()
  endforeach()
  if(_tdp_link_dirs)
    target_link_directories(TeachDemoPluginCompileIface INTERFACE ${_tdp_link_dirs})
  endif()

  # Plugins include `metapath.h` (and other shared headers) that depend on
  # path macros computed in `cmake/Fun.cmake`. In the trimmed build we rely on
  # this interface target to propagate compile-time settings to plugins.
  if(DEFINED RELATIVE_SHARE_PATH)
    target_compile_definitions(TeachDemoPluginCompileIface INTERFACE
      RELATIVE_SHARE_PATH="${RELATIVE_SHARE_PATH}"
    )
  endif()
  if(DEFINED RELATIVE_PLUGIN_PATH)
    target_compile_definitions(TeachDemoPluginCompileIface INTERFACE
      RELATIVE_PLUGIN_PATH="${RELATIVE_PLUGIN_PATH}"
    )
  endif()
  if(DEFINED RELATIVE_SDK_SHARE_PATH)
    target_compile_definitions(TeachDemoPluginCompileIface INTERFACE
      RELATIVE_SDK_SHARE_PATH="${RELATIVE_SDK_SHARE_PATH}"
    )
  endif()
  if(DEFINED RELATIVE_DEP_LIB_PATH)
    target_compile_definitions(TeachDemoPluginCompileIface INTERFACE
      RELATIVE_DEP_LIB_PATH="${RELATIVE_DEP_LIB_PATH}"
    )
  endif()
endif()

