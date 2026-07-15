#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "RobotParamRange/RobotParamRange_V1.h"
#include "GeneralMatch/GeneralMatch_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
// 机型参数
class INOROBBUSINESSPROXY_CLASS RobotParam_V1
{
#pragma region 构造与析构

private:
	IRobotParam *_robotParam = nullptr;
    //子模型
    GeneralMatch_V1 *_generalMatch_V1;
    RobotParamRange_V1 *_robotParamRange_V1;

public:
    RobotParam_V1(IRobotParam *robotParam);
    ~RobotParam_V1();

#pragma endregion

#pragma region 子模型

public:

    //获取通配对象
    GeneralMatch_V1 *getGeneralMatch() const;

    //设置通配对象
    bool SetGeneralMatch(GeneralMatch_V1 *generalMatch_V1);

    //获取机型参数范围对象
    RobotParamRange_V1 *getRobotParamRange() const;

    //设置机型参数范围对象
    bool SetRobotParamRange(RobotParamRange_V1 *robotParamRange_V1);

#pragma endregion

};
}  // namespace InoRobBusinessProxy
