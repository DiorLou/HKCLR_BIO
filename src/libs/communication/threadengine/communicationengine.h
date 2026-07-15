#pragma once

#include <QObject>
#include "Controller/BacklashCompensation/IBacklashCompensation.h"
#include "Controller/FrictionCompensation/IFrictionCompensation.h"
#include "GlobalDataTypes.h"
#include "communication_global.h"
#include "commandinfo.h"
#include "iomapping.h"
#include "labeldata.h"
#include "wobjparams.h"
#include "metatype.h"
#include "pointdata.h"
#include "projectdata.h"
#include "task.h"
#include "timer.h"
#include "peripheral/ethernertipparams.h"
#include "peripheral/ethernertcatparams.h"
#include "peripheral/modbusparams.h"
#include "safety/safetydefines.h"
#include "safety/crashdetectparams.h"
#include "taskneedtime.h"
#include "projectdata.h"
#include "rs485type.h"
#include "iostruct.h"
#include "trajrecoverydefines.h"
#include "fieldbusaddressassign.h"
#include "calibrate/loadidentifydefines.h"
#include "generalmatchdefines.h"
#include "communicationtr.h"
#include "debuggerdefines.h"
#include "roboteventinfo.h"

class CommunicationThread;
class QMutex;
class CoordParam;
class SimpleItem;
namespace osg{
class Node;
}
namespace Utils
{
class TreeItem;
}
#define MWARNING(x) CommunicationEngine::instance()->signal_needMainWidgetWarning(x)

class COMMUNICATION_EXPORT CommunicationEngine : public QObject
{
    Q_OBJECT

public:
    static CommunicationEngine *instance();

    explicit CommunicationEngine(int threadCountForLocalTask, int threadCountForCommunication = 3, bool bFIFOKeep = true);
    ~CommunicationEngine();
    QList<CommunicationThread *> getCommunicationThreadPool() const;
    QList<CommunicationThread *> getLoacalTaskThreadPool() const;

    Q_INVOKABLE void stopThreadTool();

    void taskFinish(CommunicationThread *thread, AbstractCmd *object);

    Q_INVOKABLE void enqueueCmd(
        QObject *object, const AbstractCmd::CmdType &robotCommandType);
    Q_INVOKABLE void enqueueCmd(
        QObject *object, const int cmdType);
    Q_INVOKABLE void enqueueCmd(QObject *object, const AbstractCmd::CmdType &type,
                                const QVariant &);

    bool logictreeAsynTaskIsInProcess();
    void operateLogicTreeAsynTaskCount(bool isAdd, const QString &reason);
    void enqueueCmd_robotMoveTeachStart(
        QObject *object,
        const TeachMode &teachMode,
        const bool &direction,
        const CoordParam &coordParam);
    void enqueueCmd_robotMoveTeachStop(
        QObject *object,
        const TeachMode &teachMode,
        const bool &direction,
        const CoordParam &coordParam);
    void enqueueCmd_robotMoveJointTeach(
        QObject *object, const RoadPoint &roadPoint);
    void enqueueCmd_robotMoveLine(QObject *object,
                                  const RoadPoint &destPt);
    void enqueueCmd_robotMoveJoint(QObject *object,
                                   const InoRobPos &iRobPos);
    void enqueueCmd_robotMoveRotateTeach(
        QObject *object, const CoordParam &coordParam,
        const TeachMode &teachMode,
        const double &rotateAngle);
    void enqueueCmd_ping(QObject *object, const QString &ip);
    void enqueueCmd_setControllerWifiPassword(QObject *object, const QString &sPassword);
    void enqueueCmd_setControllerWifiFrequencyBand(QObject *object, bool is24GHz);
    void enqueueCmd_enableGripperThreePosition(QObject *object, bool enable);
    void enqueueCmd_enableSingleControllerRunMode(QObject *object, bool enable);

    // Inovance interface
    void enqueueCmd_connectController(
        QObject *object, const QString &ip, const int &port);
    void enqueueCmd_enableMechLock(QObject *object, const bool &enable);
    void enqueueCmd_enableRobot(QObject *object, const bool &enable);
    void enqueueCmd_setEmergecy(QObject *object, const bool &status);

    // 负载
    void enqueueCmd_LoadSave(QObject *object, quint16 loadId, const LoadParams &params, bool bSaveNeed = false);
    void enqueueCmd_LoadClear(QObject *object, quint16 loadId);
    void enqueueCmd_LoadRefresh(QObject *object, quint16 loadId);

    // 功能安全
    void enqueueCmd_WriteSafetyParams(
        QObject *object, int key, int offset, int num);
    void enqueueCmd_ReadSafetyParams(
        QObject *object, int key, int offset, int num);
    void enqueueCmd_GetSafeParaCommon(
        QObject *object, int key, int offset, int length, unsigned char *buf,
        bool forceFlag = false);
    void enqueueCmd_SetSafeParaCommon(
        QObject *object, int key, int offset, int length, unsigned char *buf,
        bool forceFlag = false);
    void enqueueCmd_CheckAStatus(
        QObject *object, int key, int offset, int num, int status);
    void enqueueCmd_ReadSafetyParamsFromMcuDirect(
        QObject *object, int key, int offset, int num, int length, unsigned char *buf,
        bool forceFlag);
    void enqueueCmd_WriteSafetyParamsToMcuDirect(
        QObject *object, int key, int offset, int num, int length, unsigned char *buf,
        bool forceFlag);

    // 工具
    void enqueueCmd_handleToolCalibrate(
        QObject *object, const AbstractCmd::CmdType &type, const QVariant &value);
    void enqueueCmd_ToolSave(
        QObject *object, quint16 toolId, const ToolParams &params, bool bSaveNeed = false);
    void enqueueCmd_ToolCalibrate(
        QObject *object, const QString &sCalibrateName, CalibratePoints &pts);
    void enqueueCmd_ToolCalibratePoints(
        QObject *object, quint16 toolId, CalibratePoints &pts);
    void enqueueCmd_ToolMoveToPoint(
        QObject *object, Robot_ToolCalibrateType calibrateType,
        const Pos &pos, const Ori &ori, Robot_MoveType moveType);

    // 工件
    void enqueueCmd_handleWObjCalibrate(
        QObject *object, const AbstractCmd::CmdType &type, const QVariant &value);
    void enqueueCmd_WObjSave(QObject *object, quint16 wobjId, const WobjParams &params);
    void enqueueCmd_WObjCalibrate(QObject *object, int wobjId,
                                  Robot_WObjType type,
                                  const CalibratePoints &midUFramePos,
                                  const CalibratePoints &midOFramePos,
                                  const Pos &oldUFramePos,
                                  const Ori &oldUFrameOri);
    void enqueueCmd_WObjCalibratePoints(QObject *object,
                                        quint16 wobjNo,
                                        const CalibratePoints &uFramePoint,
                                        const CalibratePoints &oFramePoint);
    void enqueueCmd_WObjMoveToPoint(QObject *object, const Pos &pos,
                                    const Ori &ori,
                                    int ArmParm[4],
                                    Robot_MoveType type,
                                    Robot_WObjType method);

    /**
     * @brief enqueueCmd_axisMove
     * @param object
     * @param axisId 对于关节运动axisId为轴号，0-5对应关节轴1-6;对于直线运动axisId为移动或旋转方向，0-5对应为X、Y、Z、RX、RY、RZ
     * @param isPositive true:正方向 false:负方向
     * @param isPressd true:启动 false:停止
     */
    void enqueueCmd_axisMove(
        QObject *object,
        int axisId, const bool &isPositive, const bool &isPressd);
    void enqueueCmd_putFilesToController(
        QObject *object, const QString &sProjectName,
        const QStringList &srcFileList, const QStringList &destFileList,
        bool isProject = true);
    void enqueueCmd_removeFilesFromController(
        QObject *object, const QString &projectName,
        const QStringList &fileNameList);
    void enqueueCmd_handleProject(QObject *object,
                                  const AbstractCmd::CmdType &type, const QVariant &value);

    void enqueueCmd_userLogin(
        QObject *object, const InoUserMode mode, const QString &sPasswd);
    void enqueueCmd_setCtlAuthority(QObject *object,
                                    InoCtrlAuthority authority);

    void enqueueCmd_CheckOtherFieldBusIsActive(
        QObject *object, QObject *target, int switchtype);

    // 轴参数设置
    void enqueueCmd_saveTorqueLimit(QObject *object, const AbstractCmd::CmdType &type,
                                    bool bSwitch, int values[ROBOT_AXIS_NUM]);
    void enqueueCmd_saveAvrLoadLimit(QObject *object, const AbstractCmd::CmdType &type,
                                     bool bSwitch, int values[ROBOT_AXIS_NUM]);
    void enqueueCmd_saveOverHeatAndLoadLimit(QObject *object, const AbstractCmd::CmdType &type,
                                             bool bOverHeat, bool bOverLoad);

    void enqueueCmd_writeEthernetIpConfig(
        QObject *object, const CobotEthernetIpPara &params);
    void enqueueCmd_writeEthernetCatConfig(
        QObject *object, const InoEthcatPara &params,
        quint16 ARMSetLinkEnhanSwitch, quint16 EtherCATXMLReset);

    void enqueueCmd_writeModbusConfig(
        QObject *object, const CobotModbusParaConfig &config);

    void enqueueCmd_setGlobalVarData(
        QObject *object,
        const AbstractCmd::CmdType type,
        const int row,
        const QVector<QVariant> &data);
    void enqueueCmd_getGlobalVarData(
        QObject *object,
        const AbstractCmd::CmdType type,
        const int currentRow = -1);

    void enqueueCmd_getParam(QObject *object, const AbstractCmd::CmdType type,
                             int targetNode);

    void enqueueCmd_KineInverseSolution(
        QObject *object, short toolId, short wobjId, short loadId,
        double pts[6], int armArgs[]);

    void enqueueCmd_handleReleaseBrake(QObject *object, const AbstractCmd::CmdType type,
                                       int axisNo = -1);
    void enqueueCmd_handleSystemBackupAndLoad(
        QObject *object, const AbstractCmd::CmdType type, const QString &filePath);

    template <typename... Args>
    bool enqueueCmd_getData(
        QObject *object,
        const AbstractCmd::CmdType type,
        const Args... args)
    {
        if (!m_isQuit) {
            CmdDatas<Args...> *cmd = new CmdDatas<Args...>(args...);
            cmd->m_object = object;
            cmd->m_cmdType = type;
            return appendCmdInfo(cmd);
        }
        return false;
    }

    template <typename... Args>
    bool enqueueCmd_setData(
        QObject *object,
        const AbstractCmd::CmdType type,
        const Args... args)
    {
        if (!m_isQuit) {
            CmdDatas<Args...> *cmd = new CmdDatas<Args...>(args...);
            cmd->m_object = object;
            cmd->m_cmdType = type;
            return appendCmdInfo(cmd);
        }
        return false;
    }

signals:
    void signal_contimotion();
    void signal_needMainWidgetWarning(const QString &msg, bool isPrint = true);
    void signal_needMainWidgetInfo(const QString &msg, bool isPrint = true);
    void signal_needMainWidgetError(const QString &msg, bool isPrint = true);
    // 读取机器人名称结果信号
    void singnal_readRobotName_result(QObject *obj, bool isSuccess, const QString &robotName);


    void signal_modbus_connectstatus_changed();
    void signal_ethernetip_connectstatus_changed();
    void signal_ethercat_connectstatus_changed();

    void signal_robotMoveTeachStartInterface_result(
        bool isSuccess);

    void signal_rowCountMaxWidth(QObject *object, int width, int treeViewWidth);
    void signal_robotShutdownInterface_result(QObject *object);

    void signal_pingInterface_result(QObject *object, QString ret);

    // Inovance interface
    void signal_connectControllerInterface_result(
        QObject *object, bool isSuccess);

    void singal_connectVirtualController_result( QObject *object, bool isSuccess, const QString &msg);
    void signal_disconnectControllerInterface_result(
        QObject *object, bool isSuccess);
    void signal_controllerConnectionStatusChanged(
        ControllerConnectionState state);
    void signal_enableMechLockInterface_result(
        QObject *object, bool isSuccess);
    void signal_mechLockStateChanged(bool enable);
    void signal_clearAlarmInterface_result(
        QObject *object, bool isSuccess);
    void signal_enableRobotInterface_result(
        QObject *object, bool isSuccess);
    void signal_setEmergecyInterface_result(
        QObject *object, bool isSuccess);
    void signal_enableStateChanged(bool enable);
    void signal_emergecyStateChanged(bool status);
    void signal_controllerStateChanged(ControllerState state);
    void signal_connectSuccess();
    void signal_moduleCommStateChanged();
    void signal_robotBodyPowerStateChanged(InoCoRobotBodyPowerState state);
    void signal_gripperStateChanged(bool enable);
    void signal_gripperThreePositionStateChanged(bool enable);
    void signal_deviceModeChanged(MetaType::RobotDeviceMode mode);
    void signal_controlAuthorityChanged(InoCtrlAuthority type);
    void signal_axisMoveInterface_result(
        QObject *object, bool isSuccess);
    void signal_handleProgram_result(
        QObject *object, const AbstractCmd::CmdType type, bool isSuccess);
    void signal_setControllerWifiPassword_result(
        QObject *object, bool isSuccess, InoWifiPasswordModifyResult result);
    void signal_setControllerWifiFrequencyBand_result(
        QObject *object, bool isSuccess, bool is24GHz);
    void signal_gripperThreePositionEnabled_result(
        QObject *object, bool isSuccess);
    void signal_handleSingleControllerRunMode_result(
        QObject *object, const AbstractCmd::CmdType type,
        bool isSuccess, bool isEnable);
    void signal_getBusSwitchEnableStatus_result(
        QObject *object, bool isSuccess, bool bEthernetip, bool bEthercat);
    void signal_handleReleaseBrake(
        QObject *object, const AbstractCmd::CmdType type,
        QVariant value, bool isSuccess, const QString &errMsg);
    void signal_handleSystemBackupAndLoad(
        QObject *object, const AbstractCmd::CmdType type,
        QVariant value, bool isSuccess, const QString &errMsg);
    void signal_checkFileIsExist(QObject *object, const AbstractCmd::CmdType type,
                                 QString fileName, QVariant value);
    void signal_wifiFrequencyBandChanged(bool enable);
    void signal_speedReducingTriggerdChanged(bool enable);
    void signal_loadidentify_status_changed(int status);
    void signal_getControllerWifiInfoResult(
        QObject *object, bool isSuccess, const InoCobotWifiInfo &wifiInfo);

    void signal_collisionRecommendedValueChange(qint16 value);

    void signal_collisionStatusChange(bool isChanged);
    void signal_CompleteFricIdentify(int isFinish);

    void signalElectricChanged();
    void signalAvgLoadRateChanged();
    void signalOverLoadChanged();
    void signalOverHeatChanged();

    void signal_generalmatch_getopenstatus(QObject *object, bool status);
    void signal_generalmatch_setopenstatus(QObject *object, bool bSuccess);
    void signal_generalmatch_allowtracing(QObject *object, bool allow);
    void signal_generalmatch_getRecord(QObject *object, bool bSuccess);
    void signal_generalmatch_getinfo(QObject *object, bool bSuccess, const CobotGeneralMatchInfo &info);
    void signal_generalmatch_getparamsyncstatus(QObject *object, bool bSuccess, bool btimeout);
    void signal_generalmatch_startparamsync(QObject *object, bool bSuccess);

    // 负载辨识
    void signal_loadidentify_startIdentify(QObject *object, bool bSuccess);
    void signal_loadidentify_stopIdentify(QObject *object, bool bSuccess);
    void signal_loadidentify_readIdentifyData(
        QObject *object, bool bSuccess, const CobotLoadIdentifyData &retValue);
    void signal_loadidentify_readIdentifyStatus(
        QObject *object, bool bSuccess, const CobotIdentifyStatus &retValue);
    void signal_loadidentify_readIdentifyResult(
        QObject *object, bool bSuccess, const CobotLoadIdentifyResult &retValue);
    void signal_loadidentify_getIdentifyType(
        QObject *object, CobotIdentifyType type);
    void signal_loadidentify_readIdentifyTrajectoryFromRc(
        QObject *object, bool bSuccess, const QVector<QVector<float>> &trajPoint);
    void signal_loadidentify_readIdentifyRecommenPoint(
        QObject *object, bool bSuccess, const QVector<QVector<float>> &identifyPoint);

    void signal_posformat_changed(RobotCoordDisplayFormat foramt);
    void signal_coordtype_changed(RobotCoordType type);
    void signal_speed_changed(quint16 speed);

    void signal_ToolChanged(int id);
    void signal_WobjChanged(int id);
    void signal_LoadChanged(int id);
    void signal_intallposture_changed(double alpha, double beta);
    void signal_safetyMcuStatusChanged(int status);
    void signal_stepgrade_changed(InoMoveStepGrade grade);

    void signal_toolParamChanged(int id);
    void signal_wobjParamChanged(int id);

    void signal_taskRunStatusChanged(InoTaskStatusArr statuses);
    void signal_safety_reset_update_status(int status);

    void signal_logic_tree_item(const std::string &uuid);
    void signal_logic_tree_robotMove_item(const QString &uuid);

    void signal_tragteach_status(bool bDragging);
    void signal_tragteach_autorecordpos(InoPosType type, const RoadPoint &pt);
    void signal_safeio_changed(const CobotSafeIO &io);
    void signal_update_timer_info(InoTimerInfo info);
    void signal_sendPalletInfo(const std::string &info);

    void signal_writeModbusConfig_result(bool bSuccess);
    void signal_readModbusConnStatus_result(
        bool bSuccess, const CobotModbusConnectSts &status);
    void signal_writeEthernetIpConfig_result(bool bSuccess);
    void signal_readEthernetIpConnStatus_result(
        bool bSuccess, const CobotEthernetIpSts &status);
    void signal_writeEthernetCatConfig_result(QObject *object, bool bSuccess);
    void signal_readEthernetCatConnStatus_result(
        QObject *object, bool bSuccess, const InoEthcatSts &status, const INO_ETHCAT_PROP &prop);

    // 工程管理
    void signal_handleProject_result(
        QObject *object, const AbstractCmd::CmdType type,
        const QVariant &value, bool isSuccess, const QString &errMsg);
    void signal_updateToolIOItemDescription(const QString &content);

    void signal_safety_monitor_status_changed(bool bSwitch);

    void signal_pPorintFileChanged(const QStringList &fileList, const PointFileChangeType type);
    // 工况监控
    void signal_readActCurrent_result(int retcode,
                                      const std::vector<double> retArr);
    void signal_readHisMaxCurrent_result(int retcode,
                                         const std::vector<double> retArr);
    void signal_resetHisMaxCurrent_result(int retcode);
    void signal_readActLoadrate_result(int retcode,
                                       const std::vector<double> retArr);
    void signal_readActualOverLoad_result(int retcode,
                                          const std::vector<double> retArr);
    void signal_readMaxOverLoad_result(int retcode,
                                       const std::vector<double> retArr);
    void signal_resetMaxOverLoad_result(int retcode);
    void signal_readOverHeat_result(int retcode,
                                    const std::vector<double> retArr);

    // 轴参数设置
    void signal_readTorqueLimit_result(int retcode, bool bswitch,
                                       const QVector<int> values);
    void signal_readAvrLoadLimit_result(int retcode, bool bswitch,
                                        const QVector<int> values);
    void signal_readOverHeatLimit_result(int retcode, bool bswitch);
    void signal_readOverLoadLimit_result(int retcode, bool bswitch);
    void signal_saveTorqueLimit_result(int retcode);
    void signal_saveAvrLoadLimit_result(int retcode);
    void signal_saveOverHeatAndLoadLimit_result(int retcode);

    // 功能安全
    void signal_safetygetsafeparacomm(QObject *object, bool bSuccess);
    void signal_safetysetsafeparacomm(QObject *object, bool bSuccess);
    void signal_safetyreadparams(QObject *object, bool bSuccess);
    void signal_safetywriteparams(QObject *object, bool bSuccess);
    void signal_safety_writeparamstomcudirect(QObject *object, bool bSuccess, int key);
    void signal_safety_readparamsfrommcudirect(QObject *object, bool bSuccess, int key);
    void signal_safetycheckattr(QObject *object, bool bSuccess);
    void signal_querysafeIOrealtime(QObject *object, bool bSuccess, bool switchFlag);
    void signal_check_passwd(QObject *object, AbstractCmd::CmdType type, bool bSuccess);
    void signal_safety_comm_result(QObject *object, bool bSuccess);
    void signal_safety_read_params(QObject *object, bool bSuccess,
                                   unsigned char *buf, int len);
    void signal_safety_hardver_result(QObject *object, bool bSuccess, const QString &system,
                                      const QString &moni, const QString &commu);
    void signal_safety_multiread_result(QObject *object, bool bSuccess);
    void signal_safety_setInterZoneStatus_result(QObject *object, bool bSuccess);
    void signal_safety_writespeedreducing_result(QObject *object, bool bSuccess);
    void signal_safety_exportconfig_result(QObject *object, bool bSuccess);
    void signal_safety_importconfig_result(QObject *object, bool bSuccess);
    void signal_safety_setmonitorenable_result(QObject *object, bool bSuccess);
    void signal_safety_getmonitorenable_result(QObject *object, bool bSuccess, bool bEnable);
    void signal_safety_readspeedreducing_result(QObject *object, bool bSuccess, const SpeedReducingConf &config);
    void signal_safety_multiwrite_result(QObject *object, bool bSuccess);
    void signal_safety_syncio_result(QObject *object, bool bSuccess);
    void signal_safety_syncAxisSpeed_result(QObject *object, bool bSuccess);
    void signal_safety_syncPositionDismatch_result(QObject *object, bool bSuccess);
    void signal_safety_syncSafetyStatic_result(QObject *object, bool bSuccess);
    void signal_safety_syncAxisPosition_result(QObject *object, bool bSuccess);
    void signal_safety_syncAxisTorque_result(QObject *object, bool bSuccess);
    void signal_safety_syncAxisPower_result(QObject *object, bool bSuccess);
    void signal_safety_syncCartesianSpeed_result(QObject *object, bool bSuccess);
    void signal_safety_syncCartesianDirection_result(QObject *object, bool bSuccess);
    void signal_safety_syncCartesianPosition_result(QObject *object, bool bSuccess);
    void signal_safety_syncZone_result(QObject *object, bool bSuccess);
    void signal_safety_syncObject_result(QObject *object, bool bSuccess);
    void signal_safety_interarea_takepoint_result(QObject *object, bool bSuccess, const RoadPoint &pt);
    void signal_safety_endobject_takepoint_result(QObject *object, bool bSuccess, const RoadPoint &pt);

    // 负载
    void signal_loadRefresh_result(QObject *object, bool bSuccess, const LoadParams &params);
    void signal_loadClear_result(bool bSuccess);
    void signal_loadGetNames_result(const QStringList &sNames);
    void signal_loadSave_result(QObject *object, bool bSuccess);

    // 初始化示教器信息（用户模型、控制权限)
    void signal_initTeachPadInfo_result(
        QObject *object, bool isSuccess, const QString &errMsg);

    // 工具
    void signal_tool_GetCurToolName_result(const QString &sName);
    void signal_tool_GetItems_result(const QVector<QString> &items);
    void signal_tool_Save_result(QObject *object, bool bSuccess);
    void signal_tool_Refresh_result(QObject *object, bool bSuccess, const ToolParams &params);
    void signal_tool_clear_result(bool isSuccess);
    void signal_tool_IdNameSearch_result(const QString &sName);
    void signal_tool_HoldTypeCalibMethodSearch_result(const QVector<QString> &sName);
    void signal_tool_RefreshCalibratePoints_result(bool bSuccess, const CalibratePoints &pts);
    void signal_tool_CalibMethodNameSearch_result(const QString &sName);
    void signal_tool_CalibMethodByName_result(int type);
    void signal_tool_Calibrate_result(bool bSuccess, const Pos &pos, const Ori &ori);
    void signal_tool_SaveCalibratePoints_result(QObject *object, bool isSuccess);
    void signal_tool_ToolExcuteMoveTypeNameSearch_result(
        QObject *object, const QStringList &sName);
    void signal_tool_MoveToPoint_result(bool isSuccess);
    void signal_tool_ToolPointsNameQuery_result(const QVector<QString> &sName);
    void signal_tool_calibrate_tipsearch_result(QObject *obj, const QString &sTips);

    // 调试
    void signal_debugger_read_start_release_result(QObject *obj, bool bSuccess, uint8_t mode);
    void signal_debugger_write_start_release_result(QObject *obj, bool bSuccess);

    // 工件
    void signal_wobj_GetNames_result(const QStringList &items);
    void signal_wobj_Save_result(bool bSuccess);
    void signal_wobj_Refresh_result(QObject *object, bool bSuccess, const WobjParams &params);
    void signal_wobj_clear_result(bool isSuccess);
    void signal_wobj_WobjIdNameSearch_result(const QString &sName);
    void signal_wobj_HoldTypeUFrameCalibMethodSearch_result(const QVector<QString> &sName);
    void signal_wobj_HoldTypeOFrameCalibMethodSearch_result(const QVector<QString> &sName);
    void signal_wobj_RefreshWObjCalibratePoints_result(bool bSuccess,
                                                       const CalibratePoints &uFramePoints, const CalibratePoints &oFramePoints);
    void signal_wobj_CalibUFrameMethodNameSearch_result(const QString &sName);
    void signal_wobj_CalibOFrameMethodNameSearch_result(const QString &sName);
    void signal_wobj_WObjCalibrate_result(bool bSuccess,
                                          const Pos &uFramePos, const Ori &uFrameOri,
                                          const Pos &oFramePos, const Ori &oFrameOri);
    void signal_wobj_SaveWObjCalibratePoints_result(QObject *object, bool isSuccess);
    void signal_wobj_WObjMoveToPoint_result(bool isSuccess);
    void signal_wobj_WObjUFramePointsNameQuery_result(const QVector<QString> &sName);
    void signal_wobj_WObjOFramePointsNameQuery_result(const QVector<QString> &sName);

    // 轨迹恢复
    void signal_debugger_getTrajRecvFlag(QObject *object, bool isSuccess, TrajRecvFlag flag);
    void signal_debugger_setTrajRecvExecMode(QObject *object, bool isSuccess);
    void signal_debugger_trajmsg();

    void signal_trajrecovery_writeparams(QObject *object, bool isSuccess);
    void signal_trajrecovery_readparams(QObject *object, bool isSuccess, CobotTrajRecoveryParam params);

    // 控制面板
    void signal_jointmovezerostart_result(QObject *object, bool isSuccess);
    void signal_jointmovezeroend_result(QObject *object, bool isSuccess);
    void signal_settool_result(QObject *object, bool isSuccess, int toolId);
    void signal_setwobj_result(QObject *object, bool isSuccess, int wobjId);
    void signal_setload_result(QObject *object, bool isSuccess, int loadId);
    void signal_setspeed_result(bool isSuccess, int speed);
    void signal_setdevicemode_result(bool isSuccess, MetaType::RobotDeviceMode mode);
    void signal_setstepgrade_result(QObject *object, bool isSuccess);
    void signal_setstepparams_result(QObject *object, bool isSuccess);
    void signal_getstepparams_result(QObject *object, bool isSuccess,
                                     const InoMoveStepSizePara &params);
    void signal_getPtFileList_result(QObject *object, const QStringList &fileList);
    void signal_control_getPtList_result(
        QObject *object, const QVector<InoRPointInfo> vecRPointInfos, const QVector<InoJPointInfo> vecJPointInfos);
    void signal_control_setcurrent_result(QObject *object, bool isSuccess);

    void signal_downloadfile_result(QObject *object, bool bSuccess);

    // 安装姿态
    void signal_installationposture_write_result(QObject *object, bool isSuccess);
    void signal_installationposture_read_result(QObject *object, bool isSuccess, double compParam[16]);

    // 碰撞检测
    void signal_readColDetectRecommadDegree_result(
        QObject *object, bool bSuccess, std::vector<double> degreeManual, std::vector<double> degreeAuto);
    void signal_resetColDetectRecommadDegree_result(QObject *object, bool bSuccess);
    void signal_writeColDetectPara_result(QObject *object, bool bSuccess);

    void signal_readColProtectionParams_result(
        QObject *object, bool bSuccess, CollisionProtectiontParams params);
    void signal_readColProtectionRecommendLevel_result(
        QObject *object, bool bSuccess, qint16 level);
    void signal_resetColProtectionRecommendLevel_result(
        QObject *object, bool bSuccess, qint16 level);
    void signal_writeColProtectionParams_result(QObject *object, bool bSuccess);

    // 逆解结果
    void signal_KineInverseSolution_result(
        QObject *object, bool bRet, int iRetCode, const QVector<double> &joints);

    // 系统升级
    void signal_execUpgradeResult(QObject *object, bool bSuccess);
    void signal_startUpdate();
    void signal_readSystemUpgradeResult(
        QObject *object, bool bSuccess, const CobotSystemUpdateInfo &info);

    // 启动释放策略
    void signal_readEmgTrigMethod_result(
        QObject *object, bool bSuccess, quint8 method);
    void signal_saveEmgTrigMethod_result(QObject *object, bool bSuccess);

    void signal_readEmgStopMode_result(
        QObject *object, bool bSuccess, quint8 nMode, quint8 nSecondMode);
    void signal_saveEmgStopMode_result(QObject *object, bool bSuccess);

    // 外设
    void signal_checkOtherFieldBusIsActive_result(
        QObject *object, QObject *target, bool bRet);

    // 用户模式
    void signal_userLogin_result(
        QObject *object, bool isSuccess, const QString &errMsg);
    // 控制权限
    void signal_setCtrlAuthority_result(
        QObject *object, bool isSuccess, const QString &errMsg);

    void signal_globalVar_B_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_R_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_D_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_PR_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_String_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_P_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_JP_GetDatas_result(
        const int col, const QVector<int> index, const QVector<QVariant> datas);
    void signal_globalVar_B_GetOnlyValues_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QVariant> datas);
    void signal_globalVar_R_GetOnlyValues_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QVariant> datas);
    void signal_globalVar_D_GetOnlyValues_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QVariant> datas);
    void signal_globalVar_String_GetOnlyValues_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QVariant> datas);
    void signal_globalVar_P_GetOnlyValues_result(
        const QList<int> index,
        const QList<QList<QVariant>> datas);
    void signal_globalVar_JP_GetOnlyValues_result(
        const QList<int> index,
        const QList<QList<QVariant>> datas);
    void signal_input_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<quint8> datas);
    void signal_input_getCommIndex_result(
        QObject *obj,
        QList<unsigned short> index);
    void signal_output_getCommIndex_result(
        QObject *obj,
        QList<unsigned short> index);
    void signal_input_getCommValues_result(
        QObject *obj,
        QList<int> index,
        QList<quint8> values);
    void signal_output_getCommValues_result(
        QObject *obj,
        QList<int> index,
        QList<quint8> values);

    void signal_input_getLabelAndRemark_result(
        QObject *obj,
        int type,
        const QList<InoLabelItem> datas);

    void signal_input_saveDatas_result(
        const bool isSucess);

    void signal_output_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<quint8> datas);

    void signal_output_getLabelAndRemark_result(
        QObject *obj,
        int type,
        const QList<InoLabelItem> datas);

    void signal_Output_setDatas_result(
        const bool isSuccess);

    void signal_AD_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<Ino_AD_DA_Data> datas);

    void signal_Cobot_ADDA_getDatas_result(
        QObject *obj,
        bool sizeChanged,
        const QList<int> index,
        const QList<Ino_Cobot_ADDA_Data> datas);

    void signal_DA_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<Ino_AD_DA_Data> datas);
    void signal_DA_setDatas_result(
        const bool isSuccess);

    void signal_SystemIn_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<bool> datas);
    void signal_SystemIn_getRemarks_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QString> datas);
    void signal_SystemOut_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<bool> datas);
    void signal_SystemOut_getRemarks_result(
        const QVariant customData,
        const QList<int> index,
        const QList<QString> datas);

    void signal_IOMapping_getDatas_result(
        const QVariant customData,
        const QList<int> index,
        const QList<Ino_FieldbusIOMapData> datas);

    void signal_IOMapping_cmd_result(AbstractCmd::CmdType type,
                                     bool isSuccess);

    void signal_updateKeyBoardTableModelData(
        const QObject *obj,
        QList<QString *> data);

    void signal_virtualKeyBoard_getAllLabels_result(
        const QObject *obj,
        const QList<AllLabelType> type,
        const QList<QStringList> data);

    void signal_virtualKeyBoard_LabelChanged(
        const AllLabelType type,
        const QString oldLabel,
        const QString newLabel);

    void signal_virtualKeyBoard_LabelOrDescriChanged(
        const AllLabelType type,
        const InoLabelAndDescriItem olditem,
        const InoLabelAndDescriItem newitem);

    void signal_getEthcfg_result(QObject *obj,
                                 InoControllerEthCfg data,
                                 ushort eth0State, ushort eth1State);

    void signal_getNetStatus_result(QObject *obj,
                                    const QList<int> index,
                                    const QList<InoCommonNetStatus> data,
                                    unsigned char serverIsOn,
                                    ushort visionModel, ushort serverPort);

    void signal_getNetStatus_UIModel(QObject *obj,
                                     const uint visionModel,
                                     const uint serverPort);

    void signal_getCurPoint(QObject *obj,
                            int getCurrentPointJType,
                            bool isSucess,
                            InoJPos pos);

    void signal_getAbsoluteZero_result(QObject *obj,
                                       QList<double> data,
                                       QList<int> min,
                                       QList<int> max);

    void signal_getAbsoluteZeroCurrent_result(QObject *obj,
                                              int index,
                                              QList<double> data);

    void signal_resetAbsoluteZero_result(QObject *obj,const int axisNo,const int result);
    void signal_getResetAbsoluteZero_result(QObject *obj,const int axisNo,const int result);

    void signal_getWorkOriginZeroResult(QObject *obj,
                                        int index,
                                        InoJPos data,
                                        QList<double> min,
                                        QList<double> max,
                                        int mode,
                                        int outIndex,
                                        InoJPos triggerData);

    void signal_getVersionInfoResult(QObject *obj,
                                     bool isSucess,
                                     QStringList ans);

    void signal_controllerTimeIsNeedSysnFromLocal(bool isNeedSyn, QDateTime time);

    void signal_getToolParam_result(QObject *obj, bool isSuccess,
                                    int targetNode, const ToolParams &data);
    void signal_getWobjParam_result(QObject *obj, bool isSuccess,
                                    int targetNode, const WobjParams &data);
    void signal_getLoadParam_result(QObject *obj, bool isSuccess,
                                    int targetNode, const LoadParams &data);

    void signal_getRobotParameters_result(QObject *obj,
                                          QString robotModel,
                                          QList<double> structValue,
                                          QList<double> structRangeMin,
                                          QList<double> structRangeMax,

                                          QList<double> radioValueMin,
                                          QList<double> radioRangeMin,
                                          QList<double> radioRangeMax,

                                          QList<double> compensationValue,
                                          QList<double> compensationRangeMin,
                                          QList<double> compensationRangeMax,

                                          QList<double> couplingValue,
                                          QList<double> couplingRangeMin,
                                          QList<double> couplingRangeMax);
    void signal_getRobotParameters_isSuccess(QObject *obj, bool isSuccess);

    void signal_getRobotParametersForSimulation(QObject *obj,
                                                QList<double> data);

    void signal_getTeachParameters_result(QObject *obj, QList<double> posVelValue,
                                          QList<double> posVelRangeMin,
                                          QList<double> posVelRangeMax,

                                          QList<double> jointVelValue,
                                          QList<double> jointVelRangeMin,
                                          QList<double> jointVelRangeMax,

                                          QList<double> posAccValue,
                                          QList<double> posAccRangeMin,
                                          QList<double> posAccRangeMax,

                                          QList<double> jointAccValue,
                                          QList<double> jointAccRangeMin,
                                          QList<double> jointAccRangeMax);
    void signal_getMotionParameters_result(QObject *obj, QList<double> posVelValue,
                                           QList<double> posVelRangeMin,
                                           QList<double> posVelRangeMax,

                                           QList<double> jointVelValue,
                                           QList<double> jointVelRangeMin,
                                           QList<double> jointVelRangeMax,

                                           QList<double> posAccValue,
                                           QList<double> posAccRangeMin,
                                           QList<double> posAccRangeMax,

                                           QList<double> jointAccValue,
                                           QList<double> jointAccRangeMin,
                                           QList<double> jointAccRangeMax,

                                           QList<double> posDeceValue,
                                           QList<double> posDeceRangeMin,
                                           QList<double> posDeceRangeMax,

                                           QList<double> jointDeceValue,
                                           QList<double> jointDeceRangeMin,
                                           QList<double> jointDeceRangeMax,

                                           QList<double> transCharaValue,
                                           QList<double> transCharaRangeMin,
                                           QList<double> transCharaRangeMax);

    void singnal_getPing_result(QObject *obj, QString result);

    void singnal_getComState_result(QObject *obj, bool state);

    void singnal_dragteach_recordpointfeedback_result(QObject *obj, bool bSuccess);
    void signal_getfirstbootstatus_result(QObject *obj, bool bSuccess, bool status);

    void singnal_processBarFormWithComm_currentState(QObject *obj,
                                                     bool isSucess,
                                                     int percent,
                                                     InoTaskState state,
                                                     QString errorStr);

    void singnal_processBarFormWithComm_stopResult(QObject *obj,
                                                   bool isStopSucess,
                                                   QString tips);

    void singnal_systemDiagnoseTaskHasStartSucess(QObject *obj,
                                                  AbstractCmd::CmdType type);

    void singnal_getControlAuthorityRes(QObject *obj,
                                        InoCtrlAuthority type,
                                        int speed);

    void singnal_setControlAuthorityRes(QObject *obj,
                                        bool isSuccess);

    void signal_getHistoryAlarmRes(QObject *obj, const QStringList &alarm);

    void signal_getToolIOConfigResulte(QObject *obj,
                                       QStringList parents,
                                       QList<QList<ToolIOConfigContent>> childs);

    void signal_getDigitalInputControlAuthority(QObject *obj,
                                                int standardSize,
                                                int fieldbusSIze);

    void signal_getDigitalOutputControlAuthority(QObject *obj,
                                                 int standardSize,
                                                 int fieldbusSIze,
                                                 QList<quint8> standardAuthority,
                                                 QList<quint8> fieldBusAuthority,
                                                 QList<quint8> memoryAuthority);

    void signal_tryRs485DebuggingResult(QObject *obj, QString ans);

    void signal_getRS485Result(QObject *obj,
                               bool read485ConfigIsSuccess,
                               ToolIO_RS485_Config controller,
                               ToolIO_RS485_Config tool,
                               bool readReuseModelIsSuccess,
                               ToolIO_RS485OrAD_ReuseMode ans,
                               bool readRc485StateIsSuccess,
                               bool rc485SwitchState);

    void signal_get_ABZ_Data(QObject *obj, const int value);

    void signal_get_fieldBusAddressAssignResult(QObject *obj,
                                                const int fieldType,
                                                const INO_FIELDBUS_MEM_ASSIGN_CONFIG config,
                                                const bool isNewModbus,
                                                const bool isHasEthercat);
    void signal_get_projectNoConfig(QObject *obj,
                                    const QList<int> index,
                                    const QStringList name,
                                    const QStringList availableProjectNames);

    void signal_get_PointNoConfig(QObject *obj,
                                  const QList<int> index,
                                  const QStringList name,
                                  const QStringList availableProjectNames);

    void signal_getDeviceConnectionResult(QObject *obj,
                                          const QStringList &labelState);

    void signal_getModbusConnectionResult(QObject *obj,
                                          const bool rtuState,
                                          const bool tcpState,
                                          const bool isInEtherNet,
                                          const bool isInEtherCat,
                                          const QStringList &labelStates,
                                          const QList<QStringList> &tables);

    void signal_getMCConnectionResult(QObject *obj,
                                      const bool isActive,
                                      const QString &state,
                                      const QList<QStringList> &tables);

    void signal_getProfinetConnectionResult(QObject *obj,
                                            const bool isActive,
                                            const bool isConnected,
                                            const QStringList &labelStates);

    void signal_getEtherCatConnectionResult(QObject *obj,
                                            const bool isActive,
                                            const bool isConnected,
                                            const QStringList &labelState);

    void signal_getEtherNetIpConnectionResult(QObject *obj,
                                              const bool isActive,
                                              const QString &state,
                                              const QString &slavePort,
                                              const bool connectStatus,
                                              const QString masterConfig);

    void signal_loadRPFileChanged(std::string fileName);
    void signal_exportTeachPadConfuguresResult(QObject *obj, bool isSuccess,
                                               const QString &errMsg);




    void signal_logicTreeItemStandBy(QObject *, const int size);
    void signal_WriteLogicTreeThreadAns(QObject *, const bool isSuccess);

    void signal_ReadLogicTreeNodesCacheAns(QObject *, const bool isSuccess, const int size);
    void signal_CreateLogicTreeNodesThreadAns(QObject *, const bool isSuccess);
    void signal_CreateLogicTreeStrucheThreadAns(QObject *, const bool isSuccess);
    void signal_LogicTreeModelSortAns(QObject *, const bool isSuccess);

    void signal_LogicTreeItemCheckAns(QObject *, const QList<QPair<int, Utils::TreeItem *>> errorList);

    void signal_requireUpdateLineNumbers();

    void signal_ProcessBarFormBaseOnTimerEvent(const RobotEventInfo info);

    void siganl_loadLanguageAns(const int type, const bool isSuccess);

    void siganl_modelLayerHasLoadLanguage(bool isSuccess);

    void signal_getCurPosBaseOnToolAndWobj(RoadPoint rp,const QString &type);

    void signal_calPalletBackgroundColorOver();

    void signal_setLogicTreeItemBreakPointsAns(bool isSucces, QVariant data, int targetType, bool isNeedSetTypeToItem);

    void signal_setBreakPointsEnabledIsSuccess(bool isSuccess, bool isEnable);
    void signal_logicTreeAsynTaskCountChanged(int afterCount);

    void signal_createPalletizingBoxes(const QString &uuid,QMap<int,void*>map);
    void signal_getServoParamsCurValue(int ret, const QByteArray &info);
    void signal_changedServoParamFile(int ret);
    void signal_startRobotServoParams(int ret);
    void signal_stopRobotServoParams(int ret);
    void signal_readServoParamsStatus(int ret, const QByteArray &info);
    void signal_downloadServoFileStatus(int ret);

    //七轴
    void signal_setSevenDragTeaching(QObject *obj, int ret);
    void signal_setSevenTakePoint(QObject *obj, int ret);
    void signal_getSevenRobotParameters_result(QObject *obj,
                                          QString robotModel,
                                          QList<double> structValue,
                                          QList<double> structRangeMin,
                                          QList<double> structRangeMax,

                                          QList<double> radioValueMin,
                                          QList<double> radioRangeMin,
                                          QList<double> radioRangeMax,

                                          QList<double> compensationValue,
                                          QList<double> compensationRangeMin,
                                          QList<double> compensationRangeMax);

    void signal_getSevenRobotParameters_isSuccess(QObject *obj, bool isSuccess);
    void signal_setSevenMotion_status(int status);

    // 指定行
    void signal_setLogicTreeStartLine_result(bool isSuccess, const QString &uuid);
    void signal_getLogicTreeStartLine_result(QString uuid);

    void signal_loadRobotModel_result(const QList<osg::Node *>& linkSTL,
                                      const QList<osg::Node *>& link3DS,
                                      const QList<osg::Node *>& coordinate);
    void signal_loadRobotModelSegment_result(QObject *obj,
                                             osg::Node *linkSTL,
                                             osg::Node *link3DS,
                                             osg::Node *linkCoordinate,
                                             const int &axisNo);

    // 力控传感器
    void singal_getFCSensorDataArr_result(QObject *obj, bool isSuccess, const FCSensorParaArr &dataArr);
    void singal_saveFCSensorItem_result(QObject *obj, bool isSuccess, const QString &msg);

    // 力控设置
    void singal_getFCCalibData_result(QObject *obj, bool isSuccess, int paraIndex, const ForceCtrlCalibData &dataArr);
    void singal_saveFCCalibItems_result(QObject *obj, bool isSuccess, const QString &msg);


    void singal_isCanCalibrate_result(QObject *obj, bool isSuccess, int curSensorType, int curSensorSwitch);
    void singal_getFCForceValue_result(QObject *obj, bool isSuccess, int index, const QList<float>& forceArray, const QString &msg);
    void singal_getFCCalibrateCalc_result(QObject *obj, bool isSuccess, const ForceCtrlCalibItem& data);
    void singal_applyCaliResult_result(QObject *obj, bool isSuccess, const QString &msg);


    // 力控坐标系
    void singal_getFCCoordinateData_result(QObject *obj, bool isSuccess, const FCCoordinatePara &coordinateData);
    void singal_saveFCCoordinateDataItem_result(QObject *obj, bool isSuccess, const QString &msg);

    // 力控配置
    void singal_getFCConfigPara_result(QObject *obj, bool isSuccess, int paraIndex, const ForceCtrlConfigPara &configDataItem);
    void singal_saveFCConfigPara_result(QObject *obj, bool isSuccess, const QString &msg);

    // 力控控制
    void singal_getFCControlPara_result(QObject *obj, bool isSuccess, int paraIndex, const ForceCtrlMovePara &param);
    void singal_saveFCControlPara_result(QObject *obj, bool isSuccess, const QString &msg);

    // 力控限制
    void singal_getFCLimitData_result(QObject *obj, bool isSuccess, int paraIndex, const ForceCtrlLimitPara &param);
    void singal_saveFCLimitData_result(QObject *obj, bool isSuccess, const QString &msg);

    // 主站导入配置文件
    void signal_sendMasterConfigZipFile_result(QObject *obj, bool isSuccess, const QString &msg);

    // 力控监控
    void singal_readForceCtrlLogFormat_result(QObject *obj, bool isSuccess, const ForceCtrlLogFormat &format);
    void singal_writeForceCtrlLogFormat_result(QObject *obj, bool isSuccess, const QString &msg);
    void singal_readForceCtrlMonitorSwitch_result(QObject *obj, bool isSuccess, int8u state, int8u coord);
    void singal_writeForceCtrlMonitorSwitch_result(QObject *obj, bool isSuccess, const QString &msg);
    void singal_readForceCtrlMonitorData_result(QObject *obj, bool isSuccess, int dataNum, int overDataNum, const std::vector<ForceCtrlData> &dataArr, const std::vector<int> &stepIdArr);
    void singal_writeClearSensorForce_result(QObject *obj, bool isSuccess, const QString &msg);
    void singal_readForceCtrlCoordinateSetting_result(QObject *obj, bool isSuccess, int16s coordIndex, int16s paraIndex);
    void singal_writeForceCtrlCoordinateSetting_result(QObject *obj, bool isSuccess, const QString &msg);

    //工具参数
    void signal_getToolData_result(QObject *obj, bool isSuccess,const ToolData & tooldata);
    // 力控日志文件列表
    void singal_getForceCtrlLogList_result(QObject *obj, bool isSuccess, const std::vector<std::string> &fileList);
    void singal_copyLogFilesFromControlToLocal_result(QObject *obj, bool isSuccess, const QString &msg);

    // 摩擦补偿
    void singal_getCoulombFrictionParams_result(QObject *obj, bool isSuccess, const InoRobBusiness::FricIdentifyResult &coulombArray);

    void signal_getRecommendedTrajectoryEndPoints_result(QObject *obj, bool isSuccess, const QStringList &params);

    void signal_startFricIdentification_result(QObject *obj, bool isSuccess, const QString &msg);

    void signal_getRecognitionResult_result(QObject *obj, bool isSuccess, const InoRobBusiness::FricCompParam& result, const QString &msg);

    void signal_setRecognitionResult_result(QObject *obj, bool isSuccess, const QString &msg);

    // 间隙补偿
    // 获取间隙参数结果信号
    void signal_getBacklashParams_result(QObject *obj, bool isOk, const InoRobBusiness::BacklashIdentifyResult &array);
    // 开始间隙辨识结果信号
    void signal_startBacklashIdentification_result(QObject *obj, bool isOk, const QString &msg);
    // 结束间隙辨识结果信号
    void signal_endBacklashIdentification_result(QObject *obj, bool isOk, const QString &msg);
    // 获取间隙辨识结果信号
    void signal_getBacklashRecognitionResult_result(QObject *obj, bool isOk, float f32Backlash, const QString &msg);
    // 设置间隙辨识结果信号
    void signal_setBacklashRecognitionResult_result(QObject *obj, bool isOk, const QString &msg);
    // 获取推荐轨迹端点结果信号
    void signal_getBacklashTrajectoryEndPoints_result(QObject *obj, bool isOk, const QStringList &params);

public:
    void printLogicTreeTaskFun();

private:
    struct AsyncTaskType {
    public:
        QObject *obj = nullptr;
        int type = 0;
        AsyncTaskType(QObject *obj, int type)
        {
            this->type = type;
            this->obj = obj;
        }
    };
    QMap<CommunicationThread *, qint32> m_mapThreadToTaskCount;
    QMap<QObject *, CommunicationThread *> m_mapMapObjectToCommunicationThread;
    QMap<QObject *, qint32> m_mapObjectToCommunicationTaskCount;

    QMap<QObject *, CommunicationThread *> m_mapMapObjectToLocalTaskThread;
    QMap<QObject *, qint32> m_mapObjectToLocalTaskCount;
    //    QHash<int, int> m_hashLogicTreeTaskTypeToCount;
    unsigned int m_logicTreeTaskTypeCount = 0;
    QStringList m_logicTreeTaskFun;
    QSet<int> m_setLogictreeTaskType;
    // QSet<int> m_localTaskType;
    QMutex *m_mutex;
    bool m_bFIFOKeep;
    bool m_isQuit;

    //    QTimer *m_realTimeRoadPointTimer;

    bool appendCmdInfo(AbstractCmd *cmd);

    CommunicationThread *getIdleThread(AbstractCmd *cmd);
    void processTaskFinish(CommunicationThread *thread, AbstractCmd *object);
    QList<CommunicationThread *> m_listThreadsForCommunicationTask;
    QList<CommunicationThread *> m_listThreadsForLocalTask;
};
