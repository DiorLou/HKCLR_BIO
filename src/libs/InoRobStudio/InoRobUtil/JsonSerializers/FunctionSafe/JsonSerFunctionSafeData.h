#pragma once
#include "IInoRobUtil.h"
#include "DataSrvGlobal.h"
#include "../InoRobBusiness/Controller/FunctionSafe/ISafeParaSettingMgr.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerFunctionSafeData
{
public:
    static bool ToJson_Base(cJSON *root, const vector<SafeParaMapEle> &safeParaMap);
    static bool FromJson_Base(cJSON *obj, vector<SafeParaMapEle> &safeParaMap);

    static bool ToJson_Ext1(cJSON *obj, const vector<SafeParaMapEle> &safeParaMap);
    static bool FromJson_Ext1(cJSON *obj, vector<SafeParaMapEle> &safeParaMap);

    static bool ToJson_Ext2(cJSON *obj, const vector<SafeParaMapEle> &safeParaMap);
    static bool FromJson_Ext2(cJSON *obj, vector<SafeParaMapEle> &safeParaMap);

    static cJSON *ToJson_S_STOPCONF(unsigned char *data, unsigned short length);
    static bool FromJson_S_STOPCONF(cJSON *obj, unsigned char *data, unsigned short length);

    static cJSON *ToJson_S_SPEEDMODEL(unsigned char *data, unsigned short length);
    static bool FromJson_S_SPEEDMODEL(cJSON *obj, unsigned char *data, unsigned short length);

    static cJSON *ToJson_S_IO(S_IO *data, unsigned short length);
    static bool FromJson_S_IO(cJSON *obj, S_IO *data, unsigned short length);

    static cJSON *ToJson_S_APOS(S_APOS *data, unsigned short length);
    static bool FromJson_S_APOS(cJSON *obj, S_APOS *data, unsigned short length);

    static cJSON *ToJson_S_AVEL(S_AVEL *data, unsigned short length);
    static bool FromJson_S_AVEL(cJSON *obj, S_AVEL *data, unsigned short length);

    static cJSON *ToJson_S_CVEL(S_CVEL *data, unsigned short length);
    static bool FromJson_S_CVEL(cJSON *obj, S_CVEL *data, unsigned short length);

    static cJSON *ToJson_S_SAFETOOLMODE(unsigned char *data, unsigned short length);
    static bool FromJson_S_SAFETOOLMODE(cJSON *obj, unsigned char *data, unsigned short length);
};
}
