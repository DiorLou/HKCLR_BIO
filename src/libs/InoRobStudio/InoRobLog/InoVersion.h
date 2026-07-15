/****************************************************************
 * File Descrip : version公共定义
 * Author       : jinsheng
 ****************************************************************/
#pragma once

#include <string>
#include "dllspec.h"
#include "FilePathDefine.h"
#include "DataTypeDef.h"

constexpr UINT64 VERSION_UNKNOWN = 0;
constexpr UINT64 VERSION_V4R24C1 = 4024001;
constexpr UINT64 VERSION_V4R24C2 = 4024002;
constexpr UINT64 VERSION_V4R24C3 = 4024003;
constexpr UINT64 VERSION_V4R24C4 = 4024004;
constexpr UINT64 VERSION_V4R24C5 = 4024005;
constexpr UINT64 VERSION_V4R24C6 = 4024006;

class INOROBLOG_CLASS InoVersion
{
public:
    InoVersion();
    InoVersion(UINT64 version)
    {
        _version = version;
    }
    InoVersion(const std::string &strVersion)
    {
        setVersion(strVersion);
    }
    ~InoVersion();

    operator UINT64() const
    {
        return _version;
    }
    InoVersion &operator=(const std::string &strVersion)
    {
        setVersion(strVersion);
        return *this;
    }
    bool operator<(const std::string &rhs)
    {
        return *this < InoVersion(rhs);
    }
    bool operator<=(const std::string &rhs)
    {
        return *this <= InoVersion(rhs);
    }
    bool operator>(const std::string &rhs)
    {
        return *this > InoVersion(rhs);
    }
    bool operator>=(const std::string &rhs)
    {
        return *this >= InoVersion(rhs);
    }
    bool operator==(const std::string &rhs)
    {
        return *this == InoVersion(rhs);
    }
    bool operator!=(const std::string &rhs)
    {
        return *this != InoVersion(rhs);
    }

    UINT64 getVersion() const
    {
        return _version;
    }

    std::string getStrVersion() const
    {
        return _strVersion;
    }

    void setVersion(const UINT64 version)
    {
        _version = version;
    }

    void setVersion(const std::string &strVersion);

    bool isVerB()
    {
        return _isVerB;
    }
    bool isVerT()
    {
        return _isVerT;
    }

    UINT64 transVersionFromStr(std::string strVersion);

private:
    UINT64 _version = VERSION_UNKNOWN;
    std::string _strVersion;

    bool _isVerSPC = false;
    bool _isVerL = false;
    bool _isVerF = false;
    bool _isVerB = false;
    bool _isVerT = false;
};
