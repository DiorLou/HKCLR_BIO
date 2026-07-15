#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerIndAxisParam
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(IndAxisParam *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, IndAxisParam *data);
};
}  // namespace InoRobUtil
