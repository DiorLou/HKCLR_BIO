file(GLOB_RECURSE SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

fun_add_cobot_tp_plugin(Core
  DEPENDS Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network
  VERSION
    "1.0.0"
  COMPAT_VERSION
    "1.0.0"
  DEFINES
    CORE_LIBRARY
  DEPENDS
    Authority
    Utils
    Instance
    Metatype
    GeneralTools
    MultiThreadTools
    CustomComponent
    DataBase
    Common
    Tcp
    Communication
    Simulator
    PluginEngine
    Dialog
    VirtualKeyboard
    CobotLog
    FlowWidget
  SOURCES
    containerForm/containformdefine.h
    containerForm/containerradiobutton.h containerForm/containerradiobutton.cpp
    containerForm/firstcontainerform.h  containerForm/firstcontainerform.cpp
    containerForm/secondcontainerform.h containerForm/secondcontainerform.cpp

    logform/mainwidgetlogform.h logform/mainwidgetlogform.cpp logform/mainwidgetlogform.ui


    editgroupmanger/editgroupmanger.h editgroupmanger/editgroupmanger.cpp
    #pointeditform/pointeditform.cpp pointeditform/pointeditform.h
    #pointeditform/pointeditform.h pointeditform/pointeditform.cpp
    #留着这个UI是为了方便复制粘贴
    editgroupmanger/pointeditform.ui

    core_global.h
    coreplugin.h
    mainwidget.h
    coreplugin.cpp
    mainwidget.cpp
    mainwidget.ui
    movelabel.cpp movelabel.h
    passwordconfirmform.h passwordconfirmform.cpp passwordconfirmform.ui
    # logform/logmodel.h logform/logmodel.cpp
    #pointeditform/pointeditmanager.h
    # ${SOURCE}
    # ${orpePath}
    # ${sharePath}
)


target_include_directories (Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/containerForm
    ${CMAKE_CURRENT_SOURCE_DIR}/editgroupmanger)
