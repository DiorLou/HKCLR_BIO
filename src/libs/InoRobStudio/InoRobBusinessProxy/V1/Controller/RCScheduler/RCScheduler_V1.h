#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS RCScheduler_V1
{
#pragma region 构造与析构

private:
    IRCScheduler *_rcScheduler = nullptr;

public:
    RCScheduler_V1(IRCScheduler *rcScheduler);
    ~RCScheduler_V1();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
