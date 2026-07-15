#pragma once

#include <QObject>
#include "communication_global.h"

#include "debuggerdefines.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT DebuggerInterface
{
public:
    DebuggerInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // 0 - 松开停止    1 - 松开不停止
    int writeStartReleaseMode(uint8_t mode);
    int readStartReleaseMode(uint8_t &mode);

    int trajectoryRecoveryFlag(TrajRecvFlag &flag);
    int trajectoryRecoveryExcute(TrajRecvExecMode mode);
};
