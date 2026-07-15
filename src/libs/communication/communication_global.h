#pragma once

#include <QLoggingCategory>
#include <qglobal.h>
#if defined(COMMUNICATION_LIBRARY)
#  define COMMUNICATION_EXPORT Q_DECL_EXPORT
#else
#  define COMMUNICATION_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
