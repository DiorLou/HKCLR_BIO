#pragma once

#include <qglobal.h>

#if defined(METATYPE_LIBRARY)
#define METATYPE_EXPORT Q_DECL_EXPORT
#else
#define METATYPE_EXPORT Q_DECL_IMPORT
#endif
