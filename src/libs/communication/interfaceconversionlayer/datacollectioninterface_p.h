#pragma once

#include <QObject>
#include "datacollectioninterface.h"
#include "InoRobBusiness/Controller/Connection/IConnection.h"
#include "InoRobLog/PrintInfo/PrintInfo.h"
#include "task.h"
#include "metapath.h"
#include "InoRobBusiness/Controller/Monitor/IMonitor.h"
#include "InoRobBusiness/Controller/Task/ITask.h"
#include "InoRobBusiness/Controller/Control/IControl.h"

namespace Internal
{
class DataCollectionInterfacePrivate : public QObject
{
    Q_OBJECT

public:
    DataCollectionInterfacePrivate(
        DataCollectionInterface *dataCollectionInterface);
    virtual ~DataCollectionInterfacePrivate();
    InoRobBusiness::IController *controller();
    void listenStateChanged();
    void initdatas();

    bool isConnected() const;
    bool isMechLocked() const;

    ControllerState GetControllerStatus() const;

    int GetCurToolId() const
    {
        return m_toolId;
    }
    int GetCurWObjId() const
    {
        return m_wobjId;
    }
    int GetCurLoadId() const
    {
        return m_loadId;
    }
    MetaType::CobotControllerRunStatus getCurRunStatus() const
    {
        return m_runstatus;
    }
    bool GetEnable() const
    {
        return m_isEnable;
    }
    bool GetEmergency() const
    {
        return m_isEmergency;
    }
    InoCoRobotBodyPowerState GetBodyPowerState() const
    {
        return m_bodyPowerState;
    }
    RobotCoordDisplayFormat GetCurPosFormat() const
    {
        return m_posFormat;
    }
    void SetCurPosFormat(RobotCoordDisplayFormat format)
    {
        m_posFormat = format;
    }
    RobotCoordType GetCurCoodType() const
    {
        return m_coordType;
    }
    RoadPoint GetRealTimePt() const
    {
        return m_curDisPt;
    }
    void SetRealTimePt(const RoadPoint &pt)
    {
        m_curDisPt = pt;
    }
    RoadPoint GetRealTimeFlange2BasePt() const
    {
        return m_curPtFlange2Base;
    }
    void SetRealTimeFlage2BasePt(const RoadPoint &pt)
    {
        m_curPtFlange2Base = pt;
    }
    quint16 GetCurSpeed() const
    {
        return m_speed;
    }
    void SetCurSpeed(quint16 speed)
    {
        m_speed = speed;
    }
    MetaType::RobotDeviceMode GetCurDeviceMode() const
    {
        return m_deviceMode;
    }

    void SetCurDeviceMode(MetaType::RobotDeviceMode mode)
    {
        m_deviceMode = mode;
    }

    QStringList getCurToolNames() const
    {
        QStringList sList;
        for (auto &name : m_vToolNames) {
#ifdef INOCOBOTTP_MSVC_QT5
            sList.push_back(name);
#else
            sList.emplace_back(name);
#endif
        }
        return sList;
    }

    QStringList getCurWobjNames() const
    {
        QStringList sList;
        for (auto &name : m_vWobjNames) {
#ifdef INOCOBOTTP_MSVC_QT5
            sList.push_back(name);
#else
            sList.emplace_back(name);
#endif
        }
        return sList;
    }

    QStringList getLoadNames() const
    {
        return m_vLoadNames;
    }

    bool getSafetyMcuStatus() const
    {
        return m_safetyMcuStatus;
    }

    void setSafetyMcuStatus(bool bStatus)
    {
        m_safetyMcuStatus = bStatus;
    }

    InoMoveStepGrade getMoveStepGrade() const
    {
        return m_stepGrade;
    }

    void GetCurToolParams(int toolId, ToolParams &params);
    void GetCurWobjParams(int wobjId, WobjParams &params);
    void SetCurToolParams(int toolId, const ToolParams &params);
    void SetCurWobjParams(int wobjId, const WobjParams &params);

    InoCtrlAuthority getCurCtrlAuthority() const
    {
        return m_ctrlAuthority;
    }

    void setCurCtrlAuthority(const InoCtrlAuthority &ctrlAuthority)
    {
        if (m_ctrlAuthority != ctrlAuthority) {
            m_ctrlAuthority = ctrlAuthority;
        }
    }

    int getToolWobjMatchStatus() const
    {
        return m_toolWobjMatchStatus;
    }

    void setProgramFinished()
    {
        m_statusArr.status[0] = TaskStatus_Finished;
    }

    InoTaskStatusArr getTaskStatusArr() const
    {
        return m_statusArr;
    }

    void setMultiTaskNameList(const QVector<InoTaskInfo> &taskList)
    {
        m_taskNames.clear();

        for (const InoTaskInfo &info : taskList) {
            m_taskNames.append(info.sTaskName);
        }
    }

    QStringList getMultiTaskNameList() const
    {
        return m_taskNames;
    }

    void addScript(const QString &name)
    {
        if (!m_scriptNames.contains(name)) {
            m_scriptNames.append(name);
        }
    }

    void removeScript(const QString &name)
    {
        if (m_scriptNames.contains(name)) {
            m_scriptNames.removeAll(name);
        }
    }

    void clearScriptNameList()
    {
        m_scriptNames.clear();
    }

    QStringList getScriptNameList() const
    {
        return m_scriptNames;
    }

    uint8_t getCurStartReleaseStrategy() const
    {
        return m_startReleaseStrategy;
    }

    void setCurStartReleaseStrategy(uint8_t strategy)
    {
        m_startReleaseStrategy = strategy;
    }

    bool getCurSpeedReducingTrigger() const
    {
        return m_bSpeedReducingTriggered;
    }

    bool getSafetyMonitorStatus() const
    {
        return m_bSafetyMonitorStatus;
    }

    void setPostureAlphaBeta(double alpha, double beta)
    {
        m_postureAlpha = alpha;
        m_postureBeta = beta;
    }

    void getPostureAlphaBeta(double &alpha, double &beta)
    {
        alpha = m_postureAlpha;
        beta = m_postureBeta;
    }

    QString getCurProjectName() const
    {
        return m_sCurProjectName;
    }

    void setCurProjectName(const QString &name)
    {
        m_sCurProjectName = name;
    }

    QStringList programFiles() const
    {
        return m_programFiles;
    }

    void addProgramFile(const QString &fileName)
    {
        if (!m_programFiles.contains(fileName)) {
            m_programFiles.append(fileName);
        }
    }

    void removeProgramFile(const QString &fileName)
    {
        if (m_programFiles.contains(fileName)) {
            m_programFiles.removeAll(fileName);
        }
    }

    void setCurDragTeachStatus(bool bStatus) { m_bDragTeachStatus = bStatus; }
    bool getCurDragTeachStatus() const { return m_bDragTeachStatus; }

    void clearProgramFiles()
    {
        m_programFiles.clear();
    }

    QStringList getTPConfigureFileNames() const
    {
        return {DB_SYSTEM_INFO, DB_CONFIG_INFO, AUTHORITY_FILE};
    }

    QString getWifiName();
    QString getDeviceModel();

    void realTimeEndSpeedCallback(double speed, void *p);
    void pingInterface(AbstractCmd *absCmd);
    int getToolIndex(const QString &sTool);
    int getWobjIndex(const QString &sWobj);
    void installApk(const QString &sApk);
    WifiStrength getWifiStrength();
    bool isProgramNotRunning();
    bool isProgramRunning();
    bool isProgramPause();
    QString getBodyRobotName() const;
    QString getControllerRobotName() const;
    void setBodyRobotName(const QString &name);
    void setControllerRobotName(const QString &name);

private slots:
    void slot_connectionStatusChanged(
        InoRobBusiness::ControllerConnectionStatus status);
    void slot_mechLockStateChanged(bool Changed);
    void slot_enableStateChanged(bool Changed);
    void slot_emergecyStateChanged(bool Changed);
    void slot_currentPositionChanged(bool Changed);
    void slot_controllerStateChanged(int status);
    void slot_connectSuccess();
    void slot_warningoccur(QString time, QString errorCode, QString content);
    void slot_printModelLayerMsg(InoRobLog::PrintInfo::InfoType type, std::string info);

    void slot_initTeachPadInfo_result(
        QObject *object, bool isSuccess, const QString &errMsg);

    void slot_electricChanged();
    void slot_avgLoadRateChanged();
    void slot_overLoadChanged();
    void slot_overHeatChanged();

    void slot_posFormatChanged(InoRobUtil::PosFormat);
    void slot_coordType(InoRobUtil::CoordType);
    void slot_toolidChanged(quint16);
    void slot_wobjidChanged(quint16);
    void slot_loadidChanged(quint16);
    void slot_safetyMcuStatusChanged(bool status);
    void slot_moveStepGradeChanged(InoRobBusiness::MoveStepGrade grd);
    void slot_moduleCommStateChanged(bool);
    void slot_robotBodyPowerStateChanged(InoRobBusiness::CoRobotBodyPowerState);
    void slot_gripperStateChanged(bool);
    void slot_gripperThreePositionStateChanged(bool);
    void slot_speedChanged(quint16);
    void slot_taskRunStatusChanged(InoRobBusiness::TaskStatusArr statuses);
    void slot_safeResetStatusUpdate(int status);
    void slot_safeIOStatusUpdate(S_SAFEIO io);
    void slot_controlAuthorityChanged(InoRobBusiness::CtrlAuthority authority);
    void slot_controllerWiFiFrequencyBandChanged(bool);
    void slot_speedReducingTriggerdChanged(bool);
    void slot_safetyMonitorStatusChanged(bool);
    void slot_runmodeChanged(InoRobBusiness::RunMode rMode);
    void slot_loadIdentifyStatusChanged(int status);

    void slot_logic_tree_item(std::string);
    void slot_logic_tree_robotMoveItem(std::string);

    void slot_tragteach_status(std::string content);
    void slot_tragteach_autorecordpos(std::string content);
    void slot_timer_value(std::string);
    void slot_tool_io_description(std::string);
    void slot_pallet_change(std::string);
    void slot_nng_keepalive(std::string);
    void slot_toolWobjMatchStatusChanged(InoRobBusiness::ToolWobjMatchStatus status);

    void slot_run_status_changed(InoRobBusiness::ControllerRunStatus status);

    void slot_modbus_connectstatus_changed();
    void slot_ethernetip_connectstatus_changed();
    void slot_ethercat_connectstatus_changed();

    void slot_collisionRecommendedValueChange(qint16 value);

    void slot_collisionStatusChange(bool isChanged);

    void slot_CompleteFricIdentify(int isFinish);

private:
    DataCollectionInterface *q;

    bool m_isConnected;
    bool m_isMechLocked = false;
    ControllerState m_controllerstate = ControllerState_STANDBY;

    int m_toolId = 0;
    int m_wobjId = 0;
    int m_loadId = 0;
    int m_toolWobjMatchStatus = 0;
    bool m_bSafetyMonitorStatus = true;
    QVector<QString> m_vToolNames;
    QVector<QString> m_vWobjNames;
    QStringList m_vLoadNames;
    RobotCoordDisplayFormat m_posFormat = RobotCoordDisplayFormat_Base;
    RobotCoordType m_coordType = RobotCoordType_Base;
    bool m_isEnable = false;
    bool m_isEmergency = false;
    quint16 m_speed = 0;
    MetaType::RobotDeviceMode m_deviceMode = MetaType::RobotDeviceMode_Unknow;
    MetaType::CobotControllerRunStatus m_runstatus = MetaType::COBOT_CONTROLLER_RUN_STATUS_STOP;
    InoCtrlAuthority m_ctrlAuthority = InoCtrlAuthority_TeachPad;

    RoadPoint m_curPtFlange2Base;
    RoadPoint m_curDisPt;

    QHash<int, ToolParams> m_toolParams;
    QHash<int, WobjParams> m_wobjParams;

    bool m_safetyMcuStatus = false;
    InoMoveStepGrade m_stepGrade = InoMoveStepGrade_None;
    InoTaskStatusArr m_statusArr;
    QStringList      m_taskNames;
    QStringList      m_scriptNames;
    uint8_t m_startReleaseStrategy = 0;
    bool m_bSpeedReducingTriggered = false;

    double m_postureAlpha = 0.0f;
    double m_postureBeta = 0.0f;

    QString m_sCurProjectName = "";

    bool m_bDragTeachStatus = false;

    InoCoRobotBodyPowerState m_bodyPowerState = InoCoRobotBodyPowerState::ROBOT_BODY_DISCONNECTED_STATE;
    QStringList m_programFiles;

    QString m_sBodyRobotName;
    QString m_sControllerRobotName;
};

}  // namespace Internal
