#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerMechUnit
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(MechUnit *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, MechUnit *data);
};

}  // namespace InoRobUtil
