#pragma once

#include <qglobal.h>

#if defined(TCP_LIBRARY)
#define TCP_EXPORT Q_DECL_EXPORT
#else
#define TCP_EXPORT Q_DECL_IMPORT
#endif
