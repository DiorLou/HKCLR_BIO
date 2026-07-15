#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonForceCtrlLimitPara
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ForceCtrlLimitPara *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlLimitPara *data);
};
}  // namespace InoRobUtil
