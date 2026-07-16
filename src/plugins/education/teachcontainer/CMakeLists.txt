file(GLOB_RECURSE SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

fun_add_cobot_tp_plugin(TeachContainer
  DEPENDS Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql
  VERSION
    "1.0.0"
  COMPAT_VERSION
    "1.0.0"
  DEFINES
    TEACHCONTAINER_LIBRARY
  DEPENDS
    PluginEngine
    Authority
    Utils
    Metatype
    Instance
    Communication
    CobotLog
    GeneralTools
    TeachController
    Simulator
    CustomComponent
  PLUGIN_DEPENDS
    Core
    SimulationForm
  SOURCES
    ${SOURCE}
)

target_include_directories (TeachContainer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (TeachContainer PUBLIC
  ${PROJECT_SOURCE_DIR}/src/plugins/simulation/simulationform
)

# Keep MinGW diagnostics visible in Qt Creator's Application Output pane.
if(MINGW)
  target_compile_options(TeachContainer PRIVATE -fdiagnostics-color=never)
endif()
