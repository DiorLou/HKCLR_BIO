#pragma once

#include "communication_global.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT WarnInfoInterface
{
public:
    WarnInfoInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void setWarnMonitorEnable(bool isEnable);
};
