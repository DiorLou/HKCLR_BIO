#pragma once
#include <string>
#include <vector>
#include <map>
#include "../GlobalDataService/DataService/Protocol.h"
using std::string;

namespace InoRobBusinessProxy
{
#pragma region 日期时间

struct GSYSTEMTIME_V1
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};

bool GSYSTEMTIME_ToProxy(const GSYSTEMTIME &systemTime, GSYSTEMTIME_V1 &systemTimeV1);
bool GSYSTEMTIME_FromProxy(const GSYSTEMTIME_V1 &systemTimeV1, GSYSTEMTIME &systemTime);

#pragma endregion

}  // namespace InoRobBusinessProxy
