#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerZeroPointRepairCalibData
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ZeroPointRepairCalibData *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ZeroPointRepairCalibData *data);
};

}  // namespace InoRobUtil
