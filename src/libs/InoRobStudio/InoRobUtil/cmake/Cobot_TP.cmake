if(Platform_Cobot_TP_MinGW_Win)
    set(InoRobUtil_Depend
        ${BOOST_DIR}/libs/windows/win64/mingw/libboost_atomic-mgw11-mt-x64-1_78.a
        ${BOOST_DIR}/libs/windows/win64/mingw/libboost_filesystem-mgw11-mt-x64-1_78.a
        ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libiconv.dll.a
        ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libzipHelper.dll
        ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libuchardet.dll.a
        ws2_32 )
    file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libzipHelper.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libuchardet.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
elseif(    Platform_Cobot_TP_Android_Arm_V7a
        OR Platform_Cobot_TP_Android_Arm_64_V8a
        OR Platform_Cobot_TP_Android_X86
        OR Platform_Cobot_TP_Android_X86_64)
    set(InoRobUtil_Depend
        ${BOOST_DIR}/libs/android/${COBOT_TP_ANDROID_ABI}/libboost_atomic.a
        ${BOOST_DIR}/libs/android/${COBOT_TP_ANDROID_ABI}/libboost_filesystem.a
        ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libiconv.so
        ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libzipHelper.so
        ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libuchardet.so)
    file(COPY ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libzipHelper.so DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libuchardet.so DESTINATION ${COBOT_TP_LIBRARY_PATH})
elseif(Platform_Cobot_TP_Msvc_Win)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(InoRobUtil_Depend
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_thread-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_locale-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_system-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_filesystem-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_atomic-vc142-mt-x64-1_78.lib

          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/libiconv2.dll
          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/debug/zipHelper.lib
          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/libuchardet.dll.a
          ws2_32 )

          #release
    else()
        message("This is InoRobUtil release")
        set(InoRobUtil_Depend
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_thread-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_locale-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_system-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_filesystem-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_atomic-vc142-mt-x32-1_78.lib
          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/libiconv.lib
          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/zipHelper.lib
          ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/uchardet.lib
          ws2_32 )
    endif()
    file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/zipHelper.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/uchardet.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()

fun_add_cobot_tp_library(InoRobUtil SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core
  PUBLIC_DEFINES
    COBOT
    INOROBOT
    ENABLE_FILE_MD5_CHECK
  INCLUDES
    ${InoRobStudio_Public_Include_List}
  DEPENDS
    InoRobLog
    ${InoRobUtil_Depend}
  DEFINES
    INOROBUTIL_EXPORTS
  SOURCES
      ${InoRoUtil_Public_Src}
      ${InoRoUtil_Public_Cobot_TP_Src}
)

target_include_directories (InoRobUtil PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${InoRobStudio_Path}/InoRobBusiness/Include
)
