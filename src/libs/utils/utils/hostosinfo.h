#pragma once

#include "utils_global.h"

#include <QString>

#ifdef Q_OS_WIN
    #define INO_HOST_EXE_SUFFIX QTC_WIN_EXE_SUFFIX
#else
    #define INO_HOST_EXE_SUFFIX ""
#endif  // Q_OS_WIN

namespace Utils
{

// Add more as needed.
enum OsType { OsTypeWindows,
              OsTypeLinux,
              OsTypeMac,
              OsTypeOtherUnix,
              OsTypeOther };

class UTILS_EXPORT HostOsInfo
{
public:
    static inline OsType hostOs();

    static bool isWindowsHost();
    static bool isLinuxHost();
    static bool isMacHost();
};

OsType HostOsInfo::hostOs()
{
#if defined(Q_OS_WIN)
    return OsTypeWindows;
#elif defined(Q_OS_LINUX)
    return OsTypeLinux;
#elif defined(Q_OS_MAC)
    return OsTypeMac;
#elif defined(Q_OS_UNIX)
    return OsTypeOtherUnix;
#else
    return OsTypeOther;
#endif
}

}  // namespace Utils
