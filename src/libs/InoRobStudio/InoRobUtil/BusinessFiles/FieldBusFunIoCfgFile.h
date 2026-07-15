#pragma once
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS FieldBusFunIoCfgFile
{
public:
    FieldBusFunIoCfgFile();
    virtual ~FieldBusFunIoCfgFile();

    // 从文件中获取数据
    int FromFile(std::string fileName, std::string &dataStr, FileInfo *fileInfo);
    // 数据保存到文件
    int ToFile(const std::string &fileName, const std::string &dataStr, const std::string &robotName, const std::string &systemVersion);
    // 文件类型
    const char *GetFileType();
};

}  // namespace InoRobUtil
