file(GLOB_RECURSE SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

fun_add_cobot_tp_plugin(SimulationForm
  DEPENDS Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql
  VERSION
    "1.0.0"
  COMPAT_VERSION
    "1.0.0"
  DEFINES
    SIMULATIONFORM_LIBRARY
  DEPENDS
    PluginEngine
    Authority
    Instance
    Metatype
    Communication
    Simulator
    CustomComponent
  PLUGIN_DEPENDS
    Core
  SOURCES
    simulationform_global.h
    simulationform.h
    simulationform.cpp
    simulationformplugin.h
    simulationformplugin.cpp

)
target_include_directories (SimulationForm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
