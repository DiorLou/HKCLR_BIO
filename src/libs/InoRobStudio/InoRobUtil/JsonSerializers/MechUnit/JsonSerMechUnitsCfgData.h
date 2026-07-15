#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerMechUnitsCfgData
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(MechUnitsCfgData *data);
    // 结构体转换到cJSON, 含有独立轴数据结构
    static cJSON *ToJson2(MechUnitsCfgData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, MechUnitsCfgData *data);
    // cJSON转换到结构体, 含有独立轴数据结构
    static bool FromJson2(cJSON *obj, MechUnitsCfgData *data);
};

}  // namespace InoRobUtil
