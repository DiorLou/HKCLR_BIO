#pragma once
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS BusinessFileCommon
{
public:
    // 从文件中获取数据
    static int FromFile(std::string fileName, std::string &dataStr, FileInfo *fileInfo);
    // 数据保存到文件
    static int ToFile(const std::string &fileName, const std::string &dataStr, const FileInfo *fileInfo);
};

}  // namespace InoRobUtil
