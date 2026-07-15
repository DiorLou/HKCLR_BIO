fun_add_cobot_tp_library(TeachController SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui
  DEPENDS
    CobotLog
    Communication
    Metatype
    Instance
    CustomComponent
    GeneralTools
  DEFINES
    TEACHCONTROLLER_LIBRARY
  SOURCES
    coorddisplayform.h
    coordselectform.h
    stepmodeform.h
    teachcontrolform.h
    teachcontroller_global.h
    coorddisplayform.cpp
    coordselectform.cpp
    stepmodeform.cpp
    teachcontrolform.cpp
    coorddisplayform.ui
    coordselectform.ui
    stepmodeform.ui
    teachcontrolform.ui
)

target_include_directories (TeachController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
