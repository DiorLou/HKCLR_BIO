#pragma once

#include "qglobal.h"

#if defined(DATABASE_LIBRARY)
    #define DATABASE_EXPORT Q_DECL_EXPORT
#else
    #define DATABASE_EXPORT Q_DECL_IMPORT
#endif
