#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(TEACHCONTROLLER_LIBRARY)
#define TEACHCONTROLLER_EXPORT Q_DECL_EXPORT
#else
#define TEACHCONTROLLER_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
