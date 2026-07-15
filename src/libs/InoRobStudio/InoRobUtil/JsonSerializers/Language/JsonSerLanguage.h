#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
// #include "GlobalDataTypes.h"
#include "../Controller/Language/ILanguage.h"
using namespace InoRobBusiness;

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerLanguage
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(Language *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *cjson, Language *data);

    // 对象转换至JSON字符串
    static bool ToStr(Language *data, string &result);
    // JSON字符串转换至对象
    static bool FromStr(string &jsonStr, Language &result);
};
}  // namespace InoRobUtil
