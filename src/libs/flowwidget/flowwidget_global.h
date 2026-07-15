#pragma once
#include <qglobal.h>

#if defined(FLOWWIDGET_LIBRARY)
    #define FLOWWIDGET_EXPORT Q_DECL_EXPORT
#else
    #define FLOWWIDGET_EXPORT Q_DECL_IMPORT
#endif
