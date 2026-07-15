#pragma once

#include <qglobal.h>

#if defined(JNIINTERFACE_LIBRARY)
#define JNIINTERFACE_EXPORT Q_DECL_EXPORT
#else
#define JNIINTERFACE_EXPORT Q_DECL_IMPORT
#endif
