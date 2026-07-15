#pragma once

#include "qglobal.h"

#if defined(CUSTOMCOMPONENT_LIBRARY)
    #define CUSTOMCOMPONENT_EXPORT Q_DECL_EXPORT
#else
    #define CUSTOMCOMPONENT_EXPORT Q_DECL_IMPORT
#endif
