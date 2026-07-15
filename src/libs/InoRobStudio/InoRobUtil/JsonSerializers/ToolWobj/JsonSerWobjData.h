#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerWobjData
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(WobjData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, WobjData *data);
};
}  // namespace InoRobUtil
