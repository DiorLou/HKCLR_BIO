#pragma once

#include <qglobal.h>

#if defined(SIMULATIONFORM_LIBRARY)
#define SIMULATIONFORM_EXPORT Q_DECL_EXPORT
#else
#define SIMULATIONFORM_EXPORT Q_DECL_IMPORT
#endif
