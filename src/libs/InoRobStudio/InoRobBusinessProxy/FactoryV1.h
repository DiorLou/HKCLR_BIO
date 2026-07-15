#pragma once
#include <mutex>
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "V1/Workstation/Workstation_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS FactoryV1
{
private:
    static mutex _buildLock;

public:
    FactoryV1();
    ~FactoryV1();

public:
    // 构造工作站实例
    Workstation_V1 *WorkstationBuild();
};

}  // namespace InoRobBusinessProxy