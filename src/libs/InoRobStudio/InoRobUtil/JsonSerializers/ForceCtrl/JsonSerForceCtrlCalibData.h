#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerForceCtrlCalibData
{
public:
    // 结构体转换到cJSON
    static json ToJson(ForceCtrlCalibData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlCalibData *data);
};

}  // namespace InoRobUtil
