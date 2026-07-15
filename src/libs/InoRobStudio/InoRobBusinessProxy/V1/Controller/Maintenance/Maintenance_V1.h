#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Maintenance_V1
{
#pragma region 构造与析构

private:
    IMaintenance *_maintenance = nullptr;

public:
    Maintenance_V1(IMaintenance *maintenance);
    ~Maintenance_V1();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
