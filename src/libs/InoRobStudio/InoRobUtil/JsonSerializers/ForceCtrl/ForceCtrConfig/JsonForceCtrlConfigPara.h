#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonForceCtrlConfigPara
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ForceCtrlConfigPara *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlConfigPara *data);
};
}  // namespace InoRobUtil
