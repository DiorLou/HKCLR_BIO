#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

//

#pragma endregion

class INOROBBUSINESSPROXY_CLASS SafeIOAction_V1
{
#pragma region 数据转换

    //

#pragma endregion

#pragma region 构造与析构

private:
    ISafeIOAction *_safeIOAction = nullptr;

public:
    SafeIOAction_V1(ISafeIOAction *safeIOAction);
    ~SafeIOAction_V1();

#pragma endregion

#pragma endregion

#pragma region 业务逻辑

    //

#pragma endregion
};
}  // namespace InoRobBusinessProxy
