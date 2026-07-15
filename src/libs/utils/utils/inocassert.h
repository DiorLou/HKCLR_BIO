#pragma once

#include "utils_global.h"

namespace Utils
{
UTILS_EXPORT void writeAssertLocation(const char *msg);
}

#define INO_ASSERT_STRINGIFY_HELPER(x) #x
#define INO_ASSERT_STRINGIFY(x) INO_ASSERT_STRINGIFY_HELPER(x)
#define INO_ASSERT_STRING(cond) ::Utils::writeAssertLocation( \
    "\"" cond "\" in file " __FILE__ ", line " INO_ASSERT_STRINGIFY(__LINE__))

// The 'do {...} while (0)' idiom is not used for the main block here to be
// able to use 'break' and 'continue' as 'actions'.

#define INO_ASSERT(cond, action)  \
    if (cond) {                   \
    } else {                      \
        INO_ASSERT_STRING(#cond); \
        action;                   \
    }                             \
    do {                          \
    } while (0)
#define INO_CHECK(cond)           \
    if (cond) {                   \
    } else {                      \
        INO_ASSERT_STRING(#cond); \
    }                             \
    do {                          \
    } while (0)
