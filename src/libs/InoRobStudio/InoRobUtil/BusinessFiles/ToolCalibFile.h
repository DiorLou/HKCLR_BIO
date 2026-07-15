#pragma once
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS ToolCalibFile
{
public:
    ToolCalibFile();
    virtual ~ToolCalibFile();

    // 从文件中获取数据
    static int FromFile(std::string fileName, ToolCalibData *data, FileInfo *fileInfo);
    // 数据保存到文件
    static int ToFile(const std::string &fileName, ToolCalibData *data, const std::string &robotName, const std::string &systemVersion);
    // 文件类型
    const char *GetFileType();
};

}  // namespace InoRobUtil
