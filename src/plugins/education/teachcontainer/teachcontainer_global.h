#pragma once

#include <qglobal.h>

#if defined(TEACHCONTAINER_LIBRARY)
#define TEACHCONTAINER_EXPORT Q_DECL_EXPORT
#else
#define TEACHCONTAINER_EXPORT Q_DECL_IMPORT
#endif
