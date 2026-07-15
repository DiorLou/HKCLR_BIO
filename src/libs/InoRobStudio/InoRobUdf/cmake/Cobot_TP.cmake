
if(Platform_Cobot_TP_MinGW_Win)
    set(InoRobUdf_Depend
        ${BOOST_DIR}/libs/windows/win64/mingw/libboost_filesystem-mgw11-mt-x64-1_78.a
        ws2_32 )
elseif(    Platform_Cobot_TP_Android_Arm_V7a
        OR Platform_Cobot_TP_Android_Arm_64_V8a
        OR Platform_Cobot_TP_Android_X86
        OR Platform_Cobot_TP_Android_X86_64)
    set(InoRobUdf_Depend
        ${BOOST_DIR}/libs/android/${COBOT_TP_ANDROID_ABI}/libboost_filesystem.a )
elseif(Platform_Cobot_TP_Msvc_Win)
      if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(InoRobUdf_Depend
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_thread-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_locale-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_system-vc142-mt-gd-x64-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_filesystem-vc142-mt-gd-x64-1_78.lib
            ws2_32 )
      else()
        set(InoRobUdf_Depend
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_thread-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_locale-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_system-vc142-mt-x32-1_78.lib
          ${BOOST_DIR}/libs/windows/win64/msvc/libboost_filesystem-vc142-mt-x32-1_78.lib
          ws2_32 )
      endif()
endif()


fun_add_cobot_tp_library(InoRobUdf SHARED
  DEFINES
    INOROBUDF_EXPORTS
  DEPENDS
    ${InoRobUdf_Depend}
    Qt${QT_VERSION_MAJOR}::Core
  INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/ftp
    ${BOOST_DIR}/include
  PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
  SOURCES
    ${InoRobUdf_Public_Src}
    ${Ftp_Src}
)

