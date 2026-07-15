#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "GlobalDataTypes.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerPose
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(Pose *pose);
    // cJSON转换到结构体
    static bool FromJson(cJSON *obj, Pose *pose);
};

}  // namespace InoRobUtil
