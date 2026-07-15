#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(MULTITHREADTOOLS_LIBRARY)
#  define MULTITHREADTOOLS_EXPORT Q_DECL_EXPORT
#else
#  define MULTITHREADTOOLS_EXPORT Q_DECL_IMPORT
#endif

// Q_DECLARE_LOGGING_CATEGORY(pluginLog)
