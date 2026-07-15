
if(WIN32)
    set(DataService_Depend ws2_32)
endif()

fun_add_cobot_tp_library(DataService SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core
  DEFINES
    DATASRV_EXPORT
  INCLUDES
    ${InoRobStudio_Public_Include_List}
  INCLUDES
    ${InoRobStudio_Path}/InoRobBusiness/include
  DEPENDS
    ${DataService_Depend}
    Linker
    InoRobLog
    InoRobUtil
  SOURCES
    ${InoDataService_Public_Src}
)



target_include_directories (DataService PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CommVersionMgr
    ${CMAKE_CURRENT_SOURCE_DIR}/DataSrvBase
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)
