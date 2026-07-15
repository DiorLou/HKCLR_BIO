#pragma once

#include "communication_global.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;
class ServiceInterface;
class RobotIOInfo;
class AbstractCmd;

class COMMUNICATION_EXPORT ControlAuthority
{
public:
    ControlAuthority()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;
    void setCurrentAuthority(AbstractCmd *absCmd);
    void getCurrentAuthority(AbstractCmd *absCmd);
    // void readRmtDefaultSpeed(AbstractCmd *absCmd);
};
