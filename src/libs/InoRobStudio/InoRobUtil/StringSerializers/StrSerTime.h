#pragma once
#include <string>
#include "IInoRobUtil.h"

namespace InoRobUtil
{
// 时间序列化与反序列化的工具类
// 时间格式如 2022-05-25 16:54:21.127
// 作者: x3064
// 创建日期: 2022-05-25

class INOROBUTIL_CLASS StrSerTime
{
public:
    // 将当前时间序列化为字符串
    static void ToStr(std::string &timeStr);
    // 获取当前时间的字符串
    static void getCurrentTimeString(std::string &year, std::string &month, std::string &day, std::string &hours,
        std::string &minutes, std::string &seconds);
};
}  // namespace InoRobUtil
