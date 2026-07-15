#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerMechUnitsCalibData
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(MechUnitsCalibData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, MechUnitsCalibData *data);
};

}  // namespace InoRobUtil
