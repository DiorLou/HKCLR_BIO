#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS ScriptExtension_V1
{
#pragma region 构造与析构

private:
    IScriptExtension *_scriptExtension = nullptr;

public:
    ScriptExtension_V1(IScriptExtension *scriptExtension);
    ~ScriptExtension_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 开始
    bool Start();
    // 暂停
    bool Pause();
    // 暂停
    bool Step();
    // 终止
    bool Abort();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
