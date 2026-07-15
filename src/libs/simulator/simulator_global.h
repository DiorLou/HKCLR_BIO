#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(SIMULATOR_LIBRARY)
#define SIMULATOR_EXPORT Q_DECL_EXPORT
#else
#define SIMULATOR_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
