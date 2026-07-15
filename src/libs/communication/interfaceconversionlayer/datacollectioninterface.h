#pragma once

#include <QObject>
#include "communication_global.h"
#include "roadpoint.h"
#include "coordparam.h"
#include "toolparams.h"
#include "wobjparams.h"
#include "motionparam.h"
#include "task.h"
#include "ctrlauthority.h"

enum WifiStrength {
    WifiStrength_0,
    WifiStrength_1,
    WifiStrength_2,
    WifiStrength_3,
    WifiStrength_4
};

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
namespace Internal
{
class DataCollectionInterfacePrivate;
}

class COMMUNICATION_EXPORT DataCollectionInterface : public QObject
{
    Q_OBJECT

public:
    DataCollectionInterface();
    ~DataCollectionInterface();

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void realTimeEndSpeedCallback(double speed, void *p);

    void pingInterface(AbstractCmd *cmd);

    int getToolIndex(const QString &sTool);
    int getWobjIndex(const QString &sWobj);

    void installApk(const QString &sApk);

    void listenStateChanged();
    void initdatas();
    // inovance interface
    bool isConnected();
    bool isMechLocked() const;
    int GetCurToolId() const;
    int GetCurWObjId() const;
    int GetCurLoadId() const;
    MetaType::CobotControllerRunStatus getCurRunStatus() const;
    bool getSafetyMcuStatus() const;
    void setSafetyMcuStatus(bool bStatus);
    QStringList getCurToolNames() const;
    QStringList getCurWobjNames() const;
    QStringList getLoadNames() const;
    bool IsEnable() const;
    bool IsEmergency() const;
    quint16 GetCurSpeed() const;
    void SetCurSpeed(quint16 speed);
    InoCoRobotBodyPowerState GetBodyPowerState() const;
    RobotCoordDisplayFormat GetCurPosFormat() const;
    void SetCurPosFormat(RobotCoordDisplayFormat format);
    RobotCoordType GetCurCoodType() const;
    MetaType::RobotDeviceMode GetCurDeviceMode() const;
    void SetCurDeviceMode(MetaType::RobotDeviceMode mode);

    RoadPoint GetRealTimePt() const;
    RoadPoint GetRealTimeFlange2BasePt() const;

    ControllerState GetControllerStatus() const;

    void SetRealTimePt(const RoadPoint &pt);
    void SetRealTimeFlage2BasePt(const RoadPoint &pt);

    void setPostureAlphaBeta(double alpha, double beta);
    void getPostureAlphaBeta(double &alpha, double &beta);

    QString getWifiName();
    QString getDeviceModel();
    WifiStrength getWifiStrength();

    bool getSafetyMonitorStatus() const;

    InoTaskStatusArr getTaskStatusArr() const;

    void setMultiTaskNameList(const QVector<InoTaskInfo> &taskList);
    QStringList getMultiTaskNameList() const;

    void addScript(const QString &name);
    void removeScript(const QString &name);
    void clearScriptNameList();
    QStringList getScriptNameList() const;

    QStringList programFiles() const;
    void addProgramFile(const QString &fileName);
    void removeProgramFile(const QString &fileName);
    void clearProgramFiles();

    void setProgramFinished();
    bool isProgramNotRunning();
    bool isProgramRunning();
    bool isProgramPause();

    InoMoveStepGrade getMoveStepGrade() const;

    void GetCurToolParams(int toolId, ToolParams &params);
    void GetCurWobjParams(int wobjId, WobjParams &params);
    void SetCurToolParams(int toolId, const ToolParams &params);
    void SetCurWobjParams(int wobjId, const WobjParams &params);

    InoCtrlAuthority GetCurCtrlAuthority() const;
    void setCurCtrlAuthority(const InoCtrlAuthority &ctrlAuthority);

    int getToolWobjMatchStatus() const;

    uint8_t getCurStartReleaseStrategy() const;
    void setCurStartReleaseStrategy(uint8_t strategy);

    bool getCurSpeedReducingTrigger() const;

    QString getBodyRobotName() const;
    QString getControllerRobotName() const;
    void setBodyRobotName(const QString &name);
    void setControllerRobotName(const QString &name);

    QString getCurProjectName() const;
    void setCurProjectName(const QString &name);

    QStringList getTPConfigureFileNames() const;

    void setCurDragTeachStatus(bool bStatus);
    bool getCurDragTeachStatus() const;

protected:
    bool event(QEvent *event);

signals:
    void signal_sendRealTimeRoadPoint(RoadPoint roadPoint);
    void signal_sendRealTimeEndSpeed(double endSpeed);
    void signal_inputValueChanged();
    void signal_outputValueChanged();
    void signal_runmodeChanged(MetaType::RobotDeviceMode mode);
private:
    Internal::DataCollectionInterfacePrivate *d;
    friend class Internal::DataCollectionInterfacePrivate;

};
