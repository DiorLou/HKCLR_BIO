#pragma once
#include <string>
#include "IInoRobUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS Crc32
{
public:
    Crc32();
    ~Crc32();

    // 通过字节数组获取校验值
    unsigned int FromData(const unsigned char *buffer, unsigned int size, unsigned int crc = 0xFFFFFFFF);

    // 从文件的某个位置开始计算校验值
    unsigned int FromFile(const char *fileName, long offset, unsigned int crc = 0xFFFFFFFF);

    // 从字符串计算得到
    unsigned int FromString(const std::string data, unsigned int crc = 0xFFFFFFFF);

private:
    unsigned int *_table;
};

}  // namespace InoRobUtil
