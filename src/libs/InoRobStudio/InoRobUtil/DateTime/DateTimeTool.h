#pragma once

#include "DataTypeDef.h"
#include "dllspec.h"

namespace InoRobUtil
{
/*
    日期时间工具
*/
class INOROBUTIL_CLASS DateTimeTool
{
public:
    // 计算之前的一个时间与当前时间相差的毫秒
    static int64u TimeSpentMsSinceEpoch();
    static int64u SystemTimeSpanMilliSeconds(int64u beforeTime);
    // 获取当前时间戳(微秒us)
    static long long GetTimeStamp();
    // 计算从某时间戳开始到现在的耗时(毫秒ms)
    static int64u TimeSpentMs(long long startTime);

    static std::string getStrSysTime();
};
}  // namespace InoRobUtil
