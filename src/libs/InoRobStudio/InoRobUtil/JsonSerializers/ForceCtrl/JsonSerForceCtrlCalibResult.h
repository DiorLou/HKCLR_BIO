#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerForceCtrlCalibResult
{
public:
    // 结构体转换到cJSON
    static json ToJson(ForceCtrlCalibResult *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlCalibResult *data);
};

}  // namespace InoRobUtil
