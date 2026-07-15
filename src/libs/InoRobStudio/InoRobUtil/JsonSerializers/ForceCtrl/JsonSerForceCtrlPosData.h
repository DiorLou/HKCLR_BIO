#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerForceCtrlPosData
{
public:
    // 结构体转换到cJSON
    static json ToJson(ForceCtrlPosData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlPosData *data);
};

}  // namespace InoRobUtil
