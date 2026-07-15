#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonForceCtrlConfigParaArr
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ForceCtrlConfigParaArr *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlConfigParaArr *data);
};
}  // namespace InoRobUtil
