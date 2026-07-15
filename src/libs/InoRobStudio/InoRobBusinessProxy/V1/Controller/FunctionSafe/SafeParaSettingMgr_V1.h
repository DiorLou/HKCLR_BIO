#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS SafeParaSettingMgr_V1
{
#pragma region 构造与析构

private:
    ISafeParaSettingMgr *_safeParaSettingMgr = nullptr;

public:
    SafeParaSettingMgr_V1(ISafeParaSettingMgr *safeParaSettingMgr);
    ~SafeParaSettingMgr_V1();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
