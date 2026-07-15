#pragma once

#include "metatype.h"
#include "communication_global.h"
#include "taskneedtime.h"

namespace InoRobBusiness
{
class IController;
}

class Communication;
class ServiceInterface;
class RobotIOInfo;
class AbstractCmd;

namespace Internal
{
class RobotDebugPrivate;
}

class COMMUNICATION_EXPORT RobotDebug
{
public:
    RobotDebug();
    ~RobotDebug();

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void ping(AbstractCmd *absCmd);
    void readComState(AbstractCmd *absCmd);
    void writeComState(AbstractCmd *absCmd);

    void startDiagnose(AbstractCmd *absCmd);
    void stopDiagnose(AbstractCmd *absCmd);
    void readDiagnosePercent(AbstractCmd *absCmd);

    void startExportReportToControllerUSB(AbstractCmd *absCmd);
    void readErrExportStaPercentToControllerUSB(AbstractCmd *absCmd);

    void startExportReportToLocal(AbstractCmd *absCmd);
    void readErrExportStaPercentToLocal(AbstractCmd *absCmd);

    void tranferFileProcess(const int total, const int current, void *data);
private:
    Internal::RobotDebugPrivate *d;
    friend class Internal::RobotDebugPrivate;

};
