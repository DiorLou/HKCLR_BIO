#pragma once
#include <string>
#include "IInoRobUtil.h"

namespace InoRobUtil
{
typedef struct tagFileInfo
{
    std::string FileType;  // 文件类型

    unsigned short MajVersion;  // 文件格式主版本
    unsigned short MinVersion;  // 文件格式次版本

    std::string SystemVersion;  // 系统软件主版本

    std::string RobotName;  // 机型名
    std::string Time;       // 修改时间

    bool CheckFlag;          // 有的文件不需要校验，这时为flase，默认为需要校验
    unsigned int CheckCode;  // 32位文件校验码
    bool CheckResult;

    tagFileInfo()
    {
        MajVersion = 0;
        MinVersion = 0;

        CheckFlag = true;
        CheckCode = 0;
        CheckResult = false;
    }

    tagFileInfo &operator=(const tagFileInfo &other)
    {
        this->FileType = other.FileType;
        this->MajVersion = other.MajVersion;
        this->MinVersion = other.MinVersion;
        this->SystemVersion = other.SystemVersion;
        this->RobotName = other.RobotName;
        this->Time = other.Time;

        this->CheckFlag = other.CheckFlag;
        this->CheckCode = other.CheckCode;
        this->CheckResult = other.CheckResult;

        return (*this);
    }

    void CopyFrom(tagFileInfo &other)
    {
        this->FileType = other.FileType;
        this->MajVersion = other.MajVersion;
        this->MinVersion = other.MinVersion;
        this->SystemVersion = other.SystemVersion;
        this->RobotName = other.RobotName;
        this->Time = other.Time;
        this->CheckCode = other.CheckCode;
        this->CheckResult = other.CheckResult;
    }

} FileInfo;

class INOROBUTIL_CLASS StrSerFileInfo
{
public:
    static FileInfo FromStr(std::string str);
    static std::string ToStr(FileInfo *info);

private:
    static std::string GetValue(std::string *pContent, const char *key);
};

}  // namespace InoRobUtil
