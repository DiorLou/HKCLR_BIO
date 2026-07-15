#Depend
set(Target_Depends_List)
list(APPEND Target_Depends_List
    Authority
    CobotLog
    Utils
    GeneralTools
    CustomComponent
    DataBase
    Tcp
    Simulator
    Instance
    Metatype
    MultiThreadTools
    Common
    Communication
    PluginEngine
    Dialog
    VirtualKeyboard
    InoRobLog
    JniInterface
    FlowWidget
    ${BreakPad_Depend}
    ${APP_ALL_QT_COMPONENTS} Qt6::CorePrivate
)

#TargetEnabled
target_compile_definitions(Core PRIVATE TPBox_Windows_x64=1)

#funcEnabled
#Authority_Admin_Enabled
option(Authority_Admin_Enabled "Authority_Admin_Enabled" OFF)
set(Authority_Admin_Enabled ON)
if(${Authority_Admin_Enabled})
    #plugins
    target_compile_definitions(Core PRIVATE PluginLibCore_AdminAuthority_Enabled=1)
    target_compile_definitions(AuthorityManageForm PRIVATE PluginLibAuthorityManageForm_AdminAuthority_Enabled=1)
    #libs
    target_compile_definitions(Authority PRIVATE CommonLibAuthority_AdminAuthority_Enabled=1)
endif()

#libEnabled
set(LIB_ENABLED_LIST)
foreach(Lib ${__COBOT_LIBRARIES})
   set(Lib_Enabled "CommonLib_${Lib}_Enabled")
   option(${Lib_Enabled} ${Lib_Enabled} OFF)
   list(APPEND LIB_ENABLED_LIST ${Lib_Enabled})
endforeach()

foreach(Lib ${LIB_ENABLED_LIST})
   set(${Lib} ON)
endforeach()

set(LIB_ENABLED_LIST_ON)
foreach(LIB ${LIB_ENABLED_LIST})
    if(${LIB})
        list(APPEND LIB_ENABLED_LIST_ON ${LIB})
    endif()
endforeach()

string(REPLACE ";" "," LIB_ENABLED_LIST_ON_STR "${LIB_ENABLED_LIST_ON}")

#公有库其他dll
file(GLOB ALL_LIB_FILES "${SOURCE_FILE_BIN}/*.dll")
foreach(LIB ${ALL_LIB_FILES})
   get_filename_component(LIB_FILE_NAME ${LIB} NAME_WE)
   list(APPEND BIN_LIB_DLL_LIST ${LIB_FILE_NAME})
endforeach()

foreach(LIB ${__COBOT_LIBRARIES})
    set(LIB_DLL_NAME "lib${LIB}")
   list(APPEND LIB_DLL_LIST ${LIB_DLL_NAME})
endforeach()

set(BIN_LIB_DLL_DIFFERENCE)
foreach(Lib ${BIN_LIB_DLL_LIST})
    list(FIND LIB_DLL_LIST ${Lib} index)
    if(index EQUAL -1)
        list(APPEND BIN_LIB_DLL_DIFFERENCE ${Lib})
    endif()
endforeach()
string(REPLACE ";" "," BIN_LIB_DLL_DIFFERENCE_STR "${BIN_LIB_DLL_DIFFERENCE}")

#pluginEnabled
set(PLUGIN_ENABLED_LIST)
foreach(Plugin ${__COBOT_PLUGINS})
   set(Plugin_Enabled "PluginLib_${Plugin}_Enabled")
   option(${Plugin_Enabled} ${Plugin_Enabled} OFF)
   list(APPEND PLUGIN_ENABLED_LIST ${Plugin_Enabled})
endforeach()

set(PluginLib_Core_Enabled ON)
set(PluginLib_SettingsContainer_Enabled ON)
set(PluginLib_SystemConfigContainerForm_Enabled ON)
set(PluginLib_AuthorityManageForm_Enabled ON)

set(PLUGIN_ENABLED_LIST_ON)
foreach(PLUGIN ${PLUGIN_ENABLED_LIST})
    if(${PLUGIN})
        list(APPEND PLUGIN_ENABLED_LIST_ON ${PLUGIN})
    endif()
endforeach()

string(REPLACE ";" "," PLUGIN_ENABLED_LIST_ON_STR "${PLUGIN_ENABLED_LIST_ON}")

target_compile_definitions(PluginEngine PRIVATE "-DPluginsListEnabled=\"${PLUGIN_ENABLED_LIST_ON_STR}\"")
