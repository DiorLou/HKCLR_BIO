# Teach demo trimmed libs:
# Default: import most libs as prebuilt (IMPORTED), but allow selecting a few
# to be built from source when we need patches or debug symbols.

option(TEACH_DEMO_BUILD_DIALOG_FROM_SOURCE "Build Dialog from source in trimmed demo" ON)
option(TEACH_DEMO_BUILD_COMMUNICATION_FROM_SOURCE "Build Communication from source in trimmed demo (MinGW may fail due to toolchain limits)" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/TeachDemoPrebuiltImports.cmake)

if(TEACH_DEMO_BUILD_DIALOG_FROM_SOURCE)
  add_subdirectory(dialog)
endif()

if(TEACH_DEMO_BUILD_COMMUNICATION_FROM_SOURCE)
  add_subdirectory(communication)
else()
  # Keep Communication as IMPORTED for linking, but still show sources in IDE.
  file(GLOB_RECURSE _teach_demo_comm_sources
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/communication/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/communication/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/communication/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/communication/*.ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/communication/*.qrc"
  )
  add_custom_target(Communication_Sources SOURCES ${_teach_demo_comm_sources})
endif()

add_subdirectory(teachcontroller)


