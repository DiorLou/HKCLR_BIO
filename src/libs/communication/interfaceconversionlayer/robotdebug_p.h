#pragma once

#include "metatype.h"
#include "communication_global.h"
#include "taskneedtime.h"


namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}

class Communication;
class ServiceInterface;
class RobotIOInfo;
class AbstractCmd;
class RobotDebug;

namespace Internal
{
class RobotDebugTR : public QObject
{
    Q_OBJECT
private:
    RobotDebugTR();
};

class COMMUNICATION_EXPORT RobotDebugPrivate
{
public:
    RobotDebugPrivate(RobotDebug *robotDebug);
    ~RobotDebugPrivate();

    InoRobBusiness::IController *controller();

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
    RobotDebug *q;
    bool m_isFilesForFtpToLoaclReady = false;
    bool m_FilesForFtpToLocalHasStart = false;
    bool m_isNeedTeachpantLog = false;
    QString m_exportLocalPath = "";

    bool m_isExportFilesFinished = false;
    bool m_noMoreSignalExportReportToControllerUSB = true;
    QString m_errorStrForUsb = "";
protected:
    bool readErrExportStaPercent(int &process, InoTaskState &state);

};
}
