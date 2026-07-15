message("InoRobBusiness Cobot")
if(WIN32)
    if(Platform_Cobot_TP_Msvc_Win)
        set(InoRobBusiness_Depend
            ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/nng.lib
            ${BOOST_DIR}/libs/windows/win64/msvc/libboost_filesystem-vc142-mt-gd-x64-1_78.lib
            ${BOOST_DIR}/libs/windows/win64/msvc/libboost_atomic-vc142-mt-x64-1_78.lib
            ws2_32)
        file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_msvc/nng.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    else()
        set(InoRobBusiness_Depend
            ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/KineDll_21.dll
            ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/KineDll.dll
            ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/TransforNewdll.dll
            ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libnng.dll
            ${BOOST_DIR}/libs/windows/win64/mingw/libboost_atomic-mgw11-mt-x64-1_78.a
            ${BOOST_DIR}/libs/windows/win64/mingw/libboost_filesystem-mgw11-mt-x64-1_78.a
            ws2_32)
        file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/KineDll_21.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
        file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/KineDll.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
        file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x86_msvc/TransforNewdll.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
        file(COPY ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/libnng.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    endif()
endif()

if(COBOT_ANDROID)
    set(InoRobBusiness_Depend
        ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libiconv.so
        ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libnng.so
        ${InoRobStudio_Path}/third_party/boost/libs/android/${COBOT_TP_ANDROID_ABI}/libboost_atomic.a
        ${InoRobStudio_Path}/third_party/boost/libs/android/${COBOT_TP_ANDROID_ABI}/libboost_filesystem.a)
    file(COPY ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libnng.so DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${InoRobStudio_Path}/third_party/lib/android/${COBOT_TP_ANDROID_ABI}/libiconv.so DESTINATION ${COBOT_TP_LIBRARY_PATH})
endif()

fun_add_cobot_tp_library(InoRobBusiness SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core
  PUBLIC_DEFINES
    COBOT
  DEFINES
    INOROBBUSINESS_EXPORTS GLOBALSDATA_EXPORTS
  INCLUDES
    ${InoRobStudio_Public_Include_List}
  DEPENDS
      ${InoRobBusiness_Depend}
      InoRobUdf
      InoRobLog
      InoRobUtil
      Linker
      DataService
  EXPLICIT_MOC
      Controller/Plugin/IInoRobPluginMasterService.h
  SOURCES
      ${InoRobotBussiness_Public_Src}
)

if(WIN32)
    if(Platform_Cobot_TP_Msvc_Win)
        target_include_directories (InoRobBusiness PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
    else()
      message("APPEND InoRobotBussiness_Public_Src")
      target_sources(InoRobBusiness PRIVATE
          Controller/ScriptExtension/ScriptExtensionService.h
          Controller/ScriptExtension/ScriptExtensionService.cpp
          Controller/ScriptExtension/ScriptExtension.pb.h
          Controller/ScriptExtension/ScriptExtension.pb.cc
          Controller/ScriptExtension/ScriptExtension.grpc.pb.h
          Controller/ScriptExtension/ScriptExtension.grpc.pb.cc
      )
        target_include_directories (InoRobBusiness PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${InoRobStudio_Path}/third_party/include/grpc_inc_mingw
        )
        target_link_directories(InoRobBusiness PRIVATE ${InoRobStudio_Path}/third_party/lib/windows/x64_mingw/grpc)
        target_link_libraries(InoRobBusiness PRIVATE ${grpc_libs})
    endif()
endif()
