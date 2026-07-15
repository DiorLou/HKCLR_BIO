
fun_add_cobot_tp_library(InoRobLog SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core
  DEFINES
    INOROBLOG_EXPORTS
  PUBLIC_DEFINES
    COBOT_CUSTOM_LOG
  PUBLIC_INCLUDES
    ${InoRobStudio_Public_Include_List}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalTip
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/PrintInfo
  SOURCES
    ${InoRobLog_Public_Src}
)

# cmake_minimum_required(VERSION 3.5)

# set(targetName InoRobLog)

# # 设置Qt预处理
# set(CMAKE_AUTOMOC ON)


# add_library(${targetName} SHARED ${InoRobLog_Public_Src})
# target_link_libraries(${targetName} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
# target_compile_definitions(${targetName} PRIVATE INOROBLOG_EXPORTS)


target_include_directories (InoRobLog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/GlobalTip
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/PrintInfo
    ${InoRobStudio_Public_Include_List})

