#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS MechUnit_V1
{

#pragma region 构造与析构

private:
    IMechUnit *_mechUnit = nullptr;

public:
    MechUnit_V1(IMechUnit *mechUnit);
    ~MechUnit_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    bool MechUnitActive(std::string name);  //  --  已测

#pragma endregion

};
}  // namespace InoRobBusinessProxy
