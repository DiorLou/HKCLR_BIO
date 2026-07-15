#pragma once

#include "communication_global.h"

#include "trajrecoverydefines.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT TrajRecoveryInterface
{
public:
    TrajRecoveryInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int WriteTrajRecoveryParam(CobotTrajRecoveryParam &param);
    int ReadTrajRecoveryParam(CobotTrajRecoveryParam &param);
};
