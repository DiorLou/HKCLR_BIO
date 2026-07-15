#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerRelativeTransformat
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(RelativeTransformat *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, RelativeTransformat *data);
};

}  // namespace InoRobUtil
