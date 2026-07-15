#pragma once

#include <qglobal.h>

#if defined(INSTANCE_LIBRARY)
#define INSTANCE_EXPORT Q_DECL_EXPORT
#else
#define INSTANCE_EXPORT Q_DECL_IMPORT
#endif
