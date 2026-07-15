#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "IndexConfig/ProjectIndexConfig_V1.h"
#include "IndexConfig/RPFileIndexConfig_V1.h"
#include "IRLink/IRLink_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Peripheral_V1
{
#pragma region 构造与析构

private:
    IPeripheral *_peripheral = nullptr;

public:
    Peripheral_V1(IPeripheral *peripheral);
    ~Peripheral_V1();

#pragma endregion

#pragma region 子模型

private:
    ProjectIndexConfig_V1 *_projectIndexConfig_V1 = nullptr;
    RPFileIndexConfig_V1 *_rpFileIndexConfig_V1 = nullptr;
    IRLink_V1 *_irLink_V1 = nullptr;

public:
    ProjectIndexConfig_V1 *GetProjectIndexConfig();
    bool SetProjectIndexConfig(ProjectIndexConfig_V1 *projectIndexConfig_V1);

    RPFileIndexConfig_V1 *GetRPFileIndexConfig();
    bool SetRPFileIndexConfig(RPFileIndexConfig_V1 *rpFileIndexConfig_V1);

    IRLink_V1 *GetIRLink();
    bool SetIRLink(IRLink_V1 *irLinkV1);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
