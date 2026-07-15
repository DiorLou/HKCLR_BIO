#pragma once
#include "IInoRobUtil.h"
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"
#include "../InoRobBusiness/Controller/FunctionSafe/ISafeParaSettingMgr.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS FunctionSafeConfigFile
{
public:

    int ToFile(const vector<SafeParaMapEle> &safeParaMap, const string &fileName, const string &robotName, const string &systemVersion);

    int FromFile(vector<SafeParaMapEle> &safeParaMap, const string &fileName, const string &robotName, const string &systemVersion);

    int JsonSerEntrance(vector<SafeParaMapEle> &safeParaMap, cJSON *obj, const FileInfo &info);

};

}  // namespace InoRobUtil
