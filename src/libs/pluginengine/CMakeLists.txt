fun_add_cobot_tp_library(PluginEngine SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui
  DEPENDS
    Utils
    Metatype
    Instance
    CobotLog
    CustomComponent
  DEFINES
    PLUGINENGINE_LIBRARY
    RELATIVE_SHARE_PATH="${RELATIVE_SHARE_PATH}"
  SOURCES
      plugindialog.h
      pluginerrorview.h
      plugindetailsview.h
      invoker.h
      iplugin.h
      iplugin_p.h
      pluginengine_global.h
      pluginmanager.h
      pluginmanager_p.h
      pluginspec.h
      pluginspec_p.h
      pluginview.h
      optionsparser.h
      plugincollection.h
      pluginerroroverview.h
      plugindialog.cpp
      pluginerrorview.cpp
      plugindetailsview.cpp
      invoker.cpp
      iplugin.cpp
      pluginmanager.cpp
      pluginspec.cpp
      pluginview.cpp
      optionsparser.cpp
      plugincollection.cpp
      pluginerroroverview.cpp
        pluginerrorview.ui
        plugindetailsview.ui
        pluginerroroverview.ui
        pluginview.qrc
   SKIP_AUTOMOC   pluginspec.cpp pluginmanager.cpp
)

target_include_directories (PluginEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# if(ANDROID)
#     extend_cobot_tp_target(PluginEngine DEPENDS )
# endif()
