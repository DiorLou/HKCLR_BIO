#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerRobPos
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(RobPos *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, RobPos *data);
};
}  // namespace InoRobUtil
