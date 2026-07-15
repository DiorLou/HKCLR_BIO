#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonFCSensorParaArr
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(FCSensorParaArr *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, FCSensorParaArr *data);
};
}  // namespace InoRobUtil
