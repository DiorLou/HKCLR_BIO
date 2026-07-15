#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerForceCtrlCalibItem
{
public:
    // 结构体转换到cJSON
    static json ToJson(ForceCtrlCalibItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ForceCtrlCalibItem *data);
};

}  // namespace InoRobUtil
