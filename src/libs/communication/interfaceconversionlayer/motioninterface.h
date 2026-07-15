#pragma once

#include <QObject>
#include "communication_global.h"
#include "motionparam.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT MotionInterface
{
public:
    MotionInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    bool SetMoveStepGrade(InoMoveStepGrade grade);

    bool GetMoveStepSizePara(InoMoveStepSizePara &para);
    bool SetMoveStepSizePara(InoMoveStepSizePara para);

    bool JointMoveToZeroStart();
    bool JointMoveToZeroStop();
};
