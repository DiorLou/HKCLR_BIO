#pragma once
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS ForceCtrlConfigFile
{
public:
    ForceCtrlConfigFile();
    virtual ~ForceCtrlConfigFile();

    // 从文件中获取数据
    int FromFile(std::string fileName, ForceCtrlConfigParaArr *data, FileInfo *fileInfo);
    // 数据保存到文件
    int ToFile(const std::string &fileName, ForceCtrlConfigParaArr *data, const std::string &robotName, const std::string &systemVersion);
    // 文件类型
    const char *GetFileType();
};

}  // namespace InoRobUtil
