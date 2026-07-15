fun_add_cobot_tp_library(Utils SHARED
  PUBLIC_DEPENDS
     Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets
  DEFINES
    UTILS_LIBRARY
    RELATIVE_SHARE_PATH="${RELATIVE_SHARE_PATH}"
  SOURCES
    algorithm.h
    utils_global.h
    inocassert.cpp inocassert.h
    categorysortfiltermodel.cpp categorysortfiltermodel.h
    treemodel.cpp treemodel.h
    completinglineedit.cpp completinglineedit.h
    execmenu.cpp execmenu.h
    fancylineedit.cpp fancylineedit.h
    historycompleter.cpp historycompleter.h
    hostosinfo.cpp hostosinfo.h
    utils.qrc
    itemviews.cpp itemviews.h
)

target_include_directories (Utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
