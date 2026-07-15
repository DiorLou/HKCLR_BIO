#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(AUTHORITY_LIBRARY)
#define AUTHORITY_EXPORT Q_DECL_EXPORT
#else
#define AUTHORITY_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(pluginLog)
