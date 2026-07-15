fun_add_cobot_tp_library(Dialog SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui
  DEPENDS
    Authority
    Metatype
    Instance
    GeneralTools
    Tcp
    CustomComponent
    DataBase
    Communication
    CobotLog
    VirtualKeyboard
  DEFINES
    DIALOG_LIBRARY
  SOURCES
    dialog_global.h
    dialogcontainerform.h
    modelessdialogcontainerform.h
    dialogform/controllerform.h
    dialogform/changeauthorityform.h
    dialogform/currentauthorityform.h
    dialogform/customauthorityform.h
    dialogform/connectcontrollerform.h
    dialogform/lockscreenform.h
    dialogform/progressbarform.h
    dialogform/processbarformwithcomm.h
    generalcustomwidget.h
    dialogcontainerform.cpp
    modelessdialogcontainerform.cpp
    # modelessdialogcontainerform.ui
    dialogform/changeauthorityform.cpp
    dialogform/currentauthorityform.cpp
    dialogform/customauthorityform.cpp
    dialogform/connectcontrollerform.cpp
    dialogform/lockscreenform.cpp
    dialogform/progressbarform.cpp
    dialogform/processbarformwithcomm.cpp
    dialogform/controllerform.cpp
    generalcustomwidget.cpp
    dialogform/changeauthorityform.ui
    dialogform/currentauthorityform.ui
    dialogform/connectcontrollerform.ui
    dialogform/customauthorityform.ui
    dialogform/lockscreenform.ui
    dialogform/progressbarform.ui
    dialogform/processbarformwithcomm.ui

    dialogform/controllerform.ui

    dialogform/controllerauthorityform.cpp
    dialogform/controllerauthorityform.h
    dialogform/controllerauthorityform.ui
)

target_include_directories (Dialog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogform
    ${PROJECT_SOURCE_DIR}/src/libs/virtualkeyboard)

if(MINGW)
    # MinGW g++ can ICE on some Qt templates under -O1; reduce optimization here.
    target_compile_options(Dialog PRIVATE -O0 -fno-tree-vectorize)
endif()
