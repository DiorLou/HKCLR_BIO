#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerIndAxisParamItem
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(IndAxisParamItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, IndAxisParamItem *data);
};

}  // namespace InoRobUtil
