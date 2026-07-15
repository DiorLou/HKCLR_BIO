#pragma once
#include "DataSrvGlobal.h"
#include "InoRobUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS WobjCalibFile
{
public:
    WobjCalibFile();
    virtual ~WobjCalibFile();

    // 从文件中获取数据
    int FromFile(std::string fileName, WobjCalibData *data, FileInfo *fileInfo);
    // 数据保存到文件
    int ToFile(const std::string &fileName, WobjCalibData *data, const std::string &robotName, const std::string &systemVersion);
    // 文件类型
    const char *GetFileType();
};

}  // namespace InoRobUtil
