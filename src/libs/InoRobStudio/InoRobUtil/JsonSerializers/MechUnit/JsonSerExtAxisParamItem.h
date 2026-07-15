#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerExtAxisParamItem
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(ExtAxisParamItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, ExtAxisParamItem *data);
};

}  // namespace InoRobUtil
