#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(GENERALTOOLS_LIBRARY)
#  define GENERALTOOLS_EXPORT Q_DECL_EXPORT
#else
#  define GENERALTOOLS_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
