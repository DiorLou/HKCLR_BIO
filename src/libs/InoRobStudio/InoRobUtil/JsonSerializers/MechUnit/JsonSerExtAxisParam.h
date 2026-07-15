#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerExtAxisParam
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ExtAxisParam *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ExtAxisParam *data);
};
}  // namespace InoRobUtil
