#pragma once

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(VIRTUALKEYBOARD_LIBRARY)
#define VIRTUALKEYBOARD_EXPORT Q_DECL_EXPORT
#else
#define VIRTUALKEYBOARD_EXPORT Q_DECL_IMPORT
#endif


