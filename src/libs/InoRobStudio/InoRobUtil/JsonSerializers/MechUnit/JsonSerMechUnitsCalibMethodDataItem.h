#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerMechUnitsCalibMethodDataItem
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(MechUnitsCalibMethodDataItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, MechUnitsCalibMethodDataItem *data);
};
}  // namespace InoRobUtil
