#pragma once

#include <qglobal.h>

#if defined(OSUPDATE_LIBRARY)
#define OSUPDATE_EXPORT Q_DECL_EXPORT
#else
#define OSUPDATE_EXPORT Q_DECL_IMPORT
#endif
