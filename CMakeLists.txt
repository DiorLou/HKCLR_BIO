cmake_minimum_required(VERSION 3.14)

# 工程名
project(InoCobotTP LANGUAGES CXX)
set(ProjectPath ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#设置平台属性
message("CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_PROCESSOR : ${CMAKE_SYSTEM_PROCESSOR}")
message("PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR}")
message("BINARY_DIR is ${BINARY_DIR}")
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DPLATFORM_COBOT_TP_WINDOWS)
    if(MINGW)
        set(Platform_Cobot_TP_MinGW_Win ON)
        add_definitions(-DPLATFORM_COBOT_TP_MINGW_WIN)
        set(CMAKE_CXX_FLAGS "-mwindows")
    else()
        message(FATAL_ERROR "ERROR: unknown Windows platform config")
    endif()
else()
    message(FATAL_ERROR "ERROR: unknown CMAKE_SYSTEM_NAME")
endif()

if(MINGW OR CMAKE_SYSTEM_NAME MATCHES "Android")
    set(ALL_QT_COMPONENTS Core Gui Widgets OpenGLWidgets Network Sql Svg)
    find_package(QT NAMES Qt6 COMPONENTS  ${ALL_QT_COMPONENTS} REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${ALL_QT_COMPONENTS})
    find_package(Qt6 OPTIONAL_COMPONENTS Tools LinguistTools QUIET)
endif()

## Add paths to check for cmake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FeatureSummary)
include(Fun)

if(MINGW)
    # 开启编译器优化 O1
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("Debug model, compiler optimization level is O1")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")
        set(COBOT_BULID_TYPE "debug")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        message("Release model, compiler optimization level is O1")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O1")
        set(COBOT_BULID_TYPE "release")
    endif()
endif()


#工程根目录
set(ProjectPath ${CMAKE_CURRENT_SOURCE_DIR})
#资源路径
if(MINGW)
    set(orpePath
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_database.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_disclaimer.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_components.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_programming.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_settings.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_simulator.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_titlebar.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_xmlmodel.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_education.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_mainwidget.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_root_icons.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Bold.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-ExtraLight.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Heavy.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Light.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Medium.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Normal.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_font_SourceHanSansCN-Regular.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe_menu.qrc
    )
else()
    set(orpePath ${CMAKE_CURRENT_SOURCE_DIR}/rc/orpe.qrc)
endif()
set(sharePath ${CMAKE_CURRENT_SOURCE_DIR}/rc/share.qrc)
#模型层路径
set(InoRobStudio_Public_Include_List)
set(COBOT_TP_PLUGIN_LIST "" CACHE INTERNAL "COBOT_TP_PLUGIN_LIST" FORCE)
add_subdirectory(src)
add_subdirectory(share)
