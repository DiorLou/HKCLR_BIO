#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(PLUGINENGINE_LIBRARY)
#define PLUGINENGINE_EXPORT Q_DECL_EXPORT
#else
#define PLUGINENGINE_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
