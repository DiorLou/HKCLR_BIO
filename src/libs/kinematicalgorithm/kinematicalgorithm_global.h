#pragma once
#include <qglobal.h>

#if defined(KINEMATICALGORITHM_LIBRARY)
    #define KINEMATICALGORITHM_EXPORT Q_DECL_EXPORT
#else
    #define KINEMATICALGORITHM_EXPORT Q_DECL_IMPORT
#endif
