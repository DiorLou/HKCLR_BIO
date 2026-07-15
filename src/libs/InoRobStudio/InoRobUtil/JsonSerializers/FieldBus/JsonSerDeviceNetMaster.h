#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class JsonSerDeviceNetMaster
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(DeviceNetMaster *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, DeviceNetMaster *data);
};
}  // namespace InoRobUtil
