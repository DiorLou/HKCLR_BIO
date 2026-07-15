#pragma once

#include <qglobal.h>

#if defined(COBOTLOG_LIBRARY)
#define COBOTLOG_EXPORT Q_DECL_EXPORT
#else
#define COBOTLOG_EXPORT Q_DECL_IMPORT
#endif
