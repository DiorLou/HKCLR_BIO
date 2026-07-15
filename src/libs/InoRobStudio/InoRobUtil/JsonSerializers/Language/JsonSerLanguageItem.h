#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
// #include "GlobalDataTypes.h"
#include "../Controller/Language/ILanguage.h"

using namespace InoRobBusiness;
namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerLanguageItem
{
public:
    // 结构体转换到cJSON
    static cJSON *ToJson(LanguageItem *data);
    // cJSON转换到结构体
    static bool FromJson(cJSON *cjson, LanguageItem *data);
};
}  // namespace InoRobUtil
