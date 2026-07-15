#pragma once
#include "IInoRobUtil.h"
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS MechUnitsCalibFile
{
public:
    MechUnitsCalibFile();
    virtual ~MechUnitsCalibFile();

    // 从文件中获取数据
    int FromFile(std::string fileName, MechUnitsCalibData *data, FileInfo *fileInfo);
    // 数据保存到文件
    int ToFile(const std::string &fileName, MechUnitsCalibData *data, const std::string &robotName, const std::string &systemVersion);
    // 文件类型
    const char *GetFileType();
};
}  // namespace InoRobUtil