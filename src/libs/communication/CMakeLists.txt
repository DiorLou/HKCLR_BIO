if(Platform_Cobot_TP_MinGW_Win)
    set(Communication_Depend ws2_32)
endif()

if(WIN32)
    if(Platform_Cobot_TP_Msvc_Win)
        set(simulator_Depend
            ${PROJECT_SOURCE_DIR}/third_party/osg/msvc/lib/OpenThreads.lib
            ${PROJECT_SOURCE_DIR}/third_party/osg/msvc/lib/osg.lib
            ${PROJECT_SOURCE_DIR}/third_party/osg/msvc/lib/osgDB.lib
            ws2_32)
        set(Simulator_Include
            ${PROJECT_SOURCE_DIR}/third_party/osg/msvc/include)
    else()
        set(simulator_Depend
            ${PROJECT_SOURCE_DIR}/third_party/osg/mingw/bin/libOpenThreads.dll
            ${PROJECT_SOURCE_DIR}/third_party/osg/mingw/bin/libosg.dll
            ${PROJECT_SOURCE_DIR}/third_party/osg/mingw/bin/libosgDB.dll
            ws2_32)
        set(Simulator_Include
            ${PROJECT_SOURCE_DIR}/third_party/osg/mingw/include)
    endif()
elseif(ANDROID)
    set(simulator_Depend
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/libOpenThreads.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/libosg.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/libosgDB.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_3dc.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_3ds.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_bmp.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_deprecated_osg.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_osg.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_ply.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_serializers_osg.so
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/lib/osgPlugins-3.6.5/libosgdb_stl.so)
    set(Simulator_Include
        ${PROJECT_SOURCE_DIR}/third_party/osg/${COBOT_TP_ANDROID_ABI}/include)
endif()


fun_add_cobot_tp_library(Communication SHARED
  PUBLIC_DEPENDS
     Qt${QT_VERSION_MAJOR}::Core
     Qt${QT_VERSION_MAJOR}::Widgets
     Qt${QT_VERSION_MAJOR}::Sql
  DEFINES
    COMMUNICATION_LIBRARY
    COBOT
    RELATIVE_PLUGIN_PATH="${RELATIVE_PLUGIN_PATH}"
    RELATIVE_SHARE_PATH="${RELATIVE_SHARE_PATH}"
    ENABLE_LOG_CCCONTAINER_SINGLE_INSTANCE
  PUBLIC_INCLUDES
    ${InoRobStudio_Public_Include_List}
  INCLUDES
    ${Simulator_Include}
    ${PROJECT_SOURCE_DIR}/src/libs/utils
    ${PROJECT_SOURCE_DIR}/src/libs/utils/common
    ${PROJECT_SOURCE_DIR}/src/libs/utils/database
  DEPENDS
    InoRobUdf
    InoRobUtil
    InoRobLog
    InoRobBusiness
    CobotLog
    Common
    Instance
    Metatype
    DataBase
    GeneralTools
    PluginEngine
    CustomComponent
    Utils
    ${Communication_Depend}
    ${simulator_Depend}
  SOURCES
    communicationtr.h
    templateutils.h
    communication.h
    communication_p.h
    communication_global.h
    #interfaceconversionlayer/calibrationinterface.h
    interfaceconversionlayer/connectioninterface.h
    interfaceconversionlayer/controllersystemconfig.h interfaceconversionlayer/controllersystemconfig_p.h
    interfaceconversionlayer/datacollectioninterface.h
    interfaceconversionlayer/datacollectioninterface_p.h
    interfaceconversionlayer/ethernetipinterface.h
    interfaceconversionlayer/ethernetcatinterface.h
    interfaceconversionlayer/globalvarinterface.h
    interfaceconversionlayer/definewarninginterface.h
    interfaceconversionlayer/iointerface.h
    interfaceconversionlayer/jointpointinterface.h
    interfaceconversionlayer/labelinterface.h
    interfaceconversionlayer/metatypeconversion.h
    interfaceconversionlayer/fieldbusinterface.h
    interfaceconversionlayer/modbusinterface.h
    interfaceconversionlayer/monitorinterface.h
    interfaceconversionlayer/peripheralconfiginterface.h
    interfaceconversionlayer/positioninterface.h
    interfaceconversionlayer/projectinterface.h
    interfaceconversionlayer/resourceinterface.h
    interfaceconversionlayer/robotarminterface.h
    interfaceconversionlayer/robotcontrolinterface.h
    interfaceconversionlayer/robotpointinterface.h  interfaceconversionlayer/robotpointinterface_p.h
    interfaceconversionlayer/taskinterface.h
    interfaceconversionlayer/toolcalibrateinterface.h
    interfaceconversionlayer/userinterface.h
    interfaceconversionlayer/wobjcalibrateinterface.h
    interfaceconversionlayer/safetyinterface.h
    interfaceconversionlayer/warninfointerface.h
    interfaceconversionlayer/motioninterface.h
    interfaceconversionlayer/crashdetectinterface.h
    interfaceconversionlayer/interferenceareainterface.h
    interfaceconversionlayer/debuginterface.h
    interfaceconversionlayer/generalmatchinterface.h
    interfaceconversionlayer/trajrecoveryinterface.h
    interfaceconversionlayer/loadidentifyinterface.h
    threadengine/communicationengine.h
    threadengine/communicationthread.h
    communication.cpp
    interfaceconversionlayer/robotdebug.cpp interfaceconversionlayer/robotdebug.h interfaceconversionlayer/robotdebug_p.h
    #interfaceconversionlayer/calibrationinterface.cpp
    interfaceconversionlayer/connectioninterface.cpp
    interfaceconversionlayer/controllersystemconfig.cpp
    interfaceconversionlayer/datacollectioninterface.cpp
    interfaceconversionlayer/ethernetipinterface.cpp
    interfaceconversionlayer/ethernetcatinterface.cpp
    interfaceconversionlayer/globalvarinterface.cpp
    interfaceconversionlayer/definewarninginterface.cpp
    interfaceconversionlayer/iointerface.cpp
    interfaceconversionlayer/jointpointinterface.cpp
    interfaceconversionlayer/labelinterface.cpp
    interfaceconversionlayer/metatypeconversion.cpp
    interfaceconversionlayer/fieldbusinterface.cpp
    interfaceconversionlayer/modbusinterface.cpp
    interfaceconversionlayer/monitorinterface.cpp
    interfaceconversionlayer/peripheralconfiginterface.cpp
    interfaceconversionlayer/positioninterface.cpp
    interfaceconversionlayer/projectinterface.cpp
    interfaceconversionlayer/resourceinterface.cpp
    interfaceconversionlayer/robotarminterface.cpp
    interfaceconversionlayer/robotcontrolinterface.cpp
    interfaceconversionlayer/robotpointinterface.cpp
    interfaceconversionlayer/taskinterface.cpp
    interfaceconversionlayer/toolcalibrateinterface.cpp
    interfaceconversionlayer/userinterface.cpp
    interfaceconversionlayer/wobjcalibrateinterface.cpp
    interfaceconversionlayer/safetyinterface.cpp
    interfaceconversionlayer/warninfointerface.cpp
    interfaceconversionlayer/motioninterface.cpp
    interfaceconversionlayer/crashdetectinterface.cpp
    interfaceconversionlayer/interferenceareainterface.cpp
    interfaceconversionlayer/debuginterface.cpp
    interfaceconversionlayer/generalmatchinterface.cpp
    interfaceconversionlayer/trajrecoveryinterface.cpp
    interfaceconversionlayer/loadidentifyinterface.cpp
    interfaceconversionlayer/robotparameters.cpp interfaceconversionlayer/robotparameters.h
    interfaceconversionlayer/controlauthority.cpp interfaceconversionlayer/controlauthority.h
    interfaceconversionlayer/forcecontrolinterface.cpp interfaceconversionlayer/forcecontrolinterface.h
    interfaceconversionlayer/frictioncompensationinterface.cpp interfaceconversionlayer/frictioncompensationinterface.h
    interfaceconversionlayer/backlashcompensationinterface.cpp interfaceconversionlayer/backlashcompensationinterface.h

    threadengine/communicationengine.cpp
    threadengine/communicationthread.cpp
    threadengine/keyboardthread.cpp
    threadengine/projectthread.cpp
    threadengine/xmlprocessthread.cpp
    threadengine/logictreethread.cpp
    threadengine/modelthread.cpp
    modulesutils.h
)

if(MINGW)
  # Communication is large; reduce MinGW memory pressure.
  target_compile_options(Communication PRIVATE -O0 -fno-tree-vectorize -Wa,-mbig-obj)
endif()

target_include_directories (Communication PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaceconversionlayer
    ${CMAKE_CURRENT_SOURCE_DIR}/threadengine
    ${CMAKE_CURRENT_SOURCE_DIR}/sdk-fake/RobotSDK/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/sdk-fake/sdkcommon/MetaType
    ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_link_libraries(Communication PRIVATE
        $<$<CONFIG:Debug>:vcruntimed>
        $<$<NOT:$<CONFIG:Debug>>:vcruntime>)
endif()
