cd %1
gradlew.bat assemble && adb install -r %2/android-build-debug.apk
