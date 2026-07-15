#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerMechUnitsCalibDataItem
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(MechUnitsCalibDataItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, MechUnitsCalibDataItem *data);
};
}  // namespace InoRobUtil
