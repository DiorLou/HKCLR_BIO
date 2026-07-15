#include "datacollectioninterface.h"
#include "datacollectioninterface_p.h"
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QJsonArray>
#ifdef Q_OS_ANDROID
    #include <QJniObject>
    #include <QJniEnvironment>
#endif
#include "messagebox.h"
#include "metatypeconversion.h"
#include "instance.h"
#include "communication.h"
#include "communicationengine.h"
#include "InoRobBusiness/Controller/Monitor/IMonitor.h"
#include "InoRobLog/PrintInfo/PrintInfo.h"
#include "InoRobBusiness/Controller/IController.h"
#include "cobotlog.h"
#include "modulesutils.h"
#ifdef INOCOBOTTP_MSVC_QT5
    #include <QDateTime>
    #endif
static Communication *s_callbackRegistrant = 0;

namespace Internal
{
DataCollectionInterfacePrivate::DataCollectionInterfacePrivate(
    DataCollectionInterface *dataCollectionInterface) :
    q(dataCollectionInterface),
    m_isConnected(false)
{
}

InoRobBusiness::IController *DataCollectionInterfacePrivate::controller()
{
    return q->controller();
}

DataCollectionInterfacePrivate::~DataCollectionInterfacePrivate()
{
}

void DataCollectionInterfacePrivate::listenStateChanged()
{
    connect(_IConnection, &InoRobBusiness::IConnection::connectionStatusChanged,
            this, &DataCollectionInterfacePrivate::slot_connectionStatusChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::mechLockChanged,
            this, &DataCollectionInterfacePrivate::slot_mechLockStateChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::sigDeviceStateChanged,
            this, &DataCollectionInterfacePrivate::slot_controllerStateChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::enableChanged,
            this, &DataCollectionInterfacePrivate::slot_enableStateChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::emergencyChanged,
            this, &DataCollectionInterfacePrivate::slot_emergecyStateChanged);

    connect(_IMonitor,
            &InoRobBusiness::IMonitor::currentPositionChanged,
            this,
            &DataCollectionInterfacePrivate::slot_currentPositionChanged);

    connect(_IWarnInfo, &InoRobBusiness::IWarnInfo::sigAddWarning,
            this, &DataCollectionInterfacePrivate::slot_warningoccur);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_initTeachPadInfo_result,
            this, &DataCollectionInterfacePrivate::slot_initTeachPadInfo_result);

    connect(_IMonitor, &InoRobBusiness::IMonitor::posFormatChanged,
            this, &DataCollectionInterfacePrivate::slot_posFormatChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::currentCoordTypeChanged,
            this, &DataCollectionInterfacePrivate::slot_coordType);
    connect(_IMonitor, &InoRobBusiness::IMonitor::speedChanged,
            this, &DataCollectionInterfacePrivate::slot_speedChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::toolIdChanged,
            this, &DataCollectionInterfacePrivate::slot_toolidChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::wobjIdChanged,
            this, &DataCollectionInterfacePrivate::slot_wobjidChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::loadIdChanged,
            this, &DataCollectionInterfacePrivate::slot_loadidChanged);
    connect(_IMonitor, &InoRobBusiness::IMonitor::runStatusChanged,
            this, &DataCollectionInterfacePrivate::slot_run_status_changed);
    connect(_ITask, &InoRobBusiness::ITask::sigTaskRunStatusChanged,
            this, &DataCollectionInterfacePrivate::slot_taskRunStatusChanged);

    connect(_IRobotControllerEvents, &InoRobBusiness::IRobotControllerEvents::identifyStatusChanged,
            this, &DataCollectionInterfacePrivate::slot_loadIdentifyStatusChanged);

    connect(_ISafeParaSettingMgr, &InoRobBusiness::ISafeParaSettingMgr::safeParaCabinetStatusUpdate,
            this, &DataCollectionInterfacePrivate::slot_safetyMcuStatusChanged);
    connect(_ISafeParaSettingMgr, &InoRobBusiness::ISafeParaSettingMgr::safeResetStatusUpdate,
            this, &DataCollectionInterfacePrivate::slot_safeResetStatusUpdate);
    connect(_ISafeParaSettingMgr, &InoRobBusiness::ISafeParaSettingMgr::safeIOStatusUpdate,
            this, &DataCollectionInterfacePrivate::slot_safeIOStatusUpdate);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_logic_tree_item,
            this, &DataCollectionInterfacePrivate::slot_logic_tree_item);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_logic_tree_item_Move,
            this, &DataCollectionInterfacePrivate::slot_logic_tree_robotMoveItem);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_tragteach_status,
            this, &DataCollectionInterfacePrivate::slot_tragteach_status);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_tragteach_autorecordpos,
            this, &DataCollectionInterfacePrivate::slot_tragteach_autorecordpos);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_tool_io_description,
            this, &DataCollectionInterfacePrivate::slot_tool_io_description);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_pallet_change,
            this, &DataCollectionInterfacePrivate::slot_pallet_change);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::event_nng_keepalive,
            this, &DataCollectionInterfacePrivate::slot_nng_keepalive);

    connect(_ISubscriber, &InoRobBusiness::ISubscriber::sysevent_timer_value,
            this, &DataCollectionInterfacePrivate::slot_timer_value);

    connect(_IMonitor, &InoRobBusiness::IMonitor::moduleCommStateChanged,
            this, &DataCollectionInterfacePrivate::slot_moduleCommStateChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::moveStepGradeChanged,
            this, &DataCollectionInterfacePrivate::slot_moveStepGradeChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::runModeChanged,
            this, &DataCollectionInterfacePrivate::slot_runmodeChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::coRobotBodyPowerStateChanged,
            this, &DataCollectionInterfacePrivate::slot_robotBodyPowerStateChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigGripperEnableChanged,
            this, &DataCollectionInterfacePrivate::slot_gripperStateChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::toolWobjMatchStatusChanged,
            this, &DataCollectionInterfacePrivate::slot_toolWobjMatchStatusChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::gripperThreePosEnableChanged,
            this, &DataCollectionInterfacePrivate::slot_gripperThreePositionStateChanged);

    connect(_IControlAuthority, &InoRobBusiness::IControlAuthority::sigICtrlAuthorityChanged,
            this, &DataCollectionInterfacePrivate::slot_controlAuthorityChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigControllerWiFiFrequencyBandChanged,
            this, &DataCollectionInterfacePrivate::slot_controllerWiFiFrequencyBandChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigSpeedReduingTriggerdChange,
            this, &DataCollectionInterfacePrivate::slot_speedReducingTriggerdChanged);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigSafetyMonitorStatusChange,
            this, &DataCollectionInterfacePrivate::slot_safetyMonitorStatusChanged);

    QObject::connect(_IResource, &InoRobBusiness::IResource::electricChanged,
                     this, &DataCollectionInterfacePrivate::slot_electricChanged);

    QObject::connect(_IResource, &InoRobBusiness::IResource::avgLoadRateChanged,
                     this, &DataCollectionInterfacePrivate::slot_avgLoadRateChanged);

    QObject::connect(_IResource, &InoRobBusiness::IResource::overLoadChanged,
                     this, &DataCollectionInterfacePrivate::slot_overLoadChanged);

    QObject::connect(_IResource, &InoRobBusiness::IResource::overHeatChanged,
                     this, &DataCollectionInterfacePrivate::slot_overHeatChanged);

    QObject::connect(_IConnection, &InoRobBusiness::IConnection::connnectSuccess,
                     this, &DataCollectionInterfacePrivate::slot_connectSuccess);

    QObject::connect(_IResource, &InoRobBusiness::IResource::modbusConnectStatusChanged,
                     this, &DataCollectionInterfacePrivate::slot_modbus_connectstatus_changed);

    QObject::connect(_IResource, &InoRobBusiness::IResource::ethernetIPStatusChanged,
                     this, &DataCollectionInterfacePrivate::slot_ethernetip_connectstatus_changed);

    QObject::connect(_IResource, &InoRobBusiness::IResource::etherCatStatusChanged,
                     this, &DataCollectionInterfacePrivate::slot_ethercat_connectstatus_changed);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigCollisionRecommendedValueChange,
            this, &DataCollectionInterfacePrivate::slot_collisionRecommendedValueChange);

    connect(_IMonitor, &InoRobBusiness::IMonitor::sigCollisionStatusChange,
            this, &DataCollectionInterfacePrivate::slot_collisionStatusChange);
}

void DataCollectionInterfacePrivate::initdatas()
{
    m_toolId = _IMonitor->GetToolId();
    m_wobjId = _IMonitor->GetWobjId();
    m_loadId = _IMonitor->GetLoadId();
    m_toolWobjMatchStatus = static_cast<int>(_IMonitor->GetToolWobjMatchStatus());
    q->comm()->GetToolItem(m_vToolNames);
    // m_posFormat = q->comm()->GetPosFormat();
    // qDebug() << "init data posformat = " << m_posFormat;
    m_coordType = q->comm()->GetCurrentCoordType();
    q->comm()->setIP(q->comm()->GetConnIp().c_str());
    q->comm()->setPort(q->comm()->GetConnPort());
    m_speed = _IMonitor->GetSpeed();

    quint16 nWobj = q->comm()->GetWObjCount();
    for (int i = 0; i < nWobj; ++i) {
#ifdef INOCOBOTTP_MSVC_QT5
        m_vWobjNames.push_back(q->comm()->WobjIdNameSearch(i));
    #else
        m_vWobjNames.emplace_back(q->comm()->WobjIdNameSearch(i));
    #endif

    }

    quint16 nNumLoad = q->comm()->GetLoadCount();
    for (int i = 0; i < nNumLoad; ++i) {
#ifdef INOCOBOTTP_MSVC_QT5
        m_vLoadNames.push_back(q->comm()->LoadIDNameSearch(i));
#else
        m_vLoadNames.emplace_back(q->comm()->LoadIDNameSearch(i));
#endif
    }

    m_stepGrade = static_cast<InoMoveStepGrade>(_IMonitor->GetMoveStepGrade());
}

void DataCollectionInterfacePrivate::slot_moduleCommStateChanged(bool)
{
    emit CommunicationEngine::instance()
    ->signal_moduleCommStateChanged();
}

void DataCollectionInterfacePrivate::slot_robotBodyPowerStateChanged(InoRobBusiness::CoRobotBodyPowerState state)
{
    m_bodyPowerState = (InoCoRobotBodyPowerState)state;

    emit CommunicationEngine::instance()
        ->signal_robotBodyPowerStateChanged(m_bodyPowerState);
}

void DataCollectionInterfacePrivate::slot_gripperStateChanged(bool Changed)
{
    qDebug() << "gripper state changed : " << Changed;
    emit CommunicationEngine::instance()
        ->signal_gripperStateChanged(Changed);
}

void DataCollectionInterfacePrivate::slot_gripperThreePositionStateChanged(bool Changed)
{
    qDebug() << "gripper three position state changed : " << Changed;
    emit CommunicationEngine::instance()
        ->signal_gripperThreePositionStateChanged(Changed);
}

void DataCollectionInterfacePrivate::slot_controlAuthorityChanged(
    InoRobBusiness::CtrlAuthority authority)
{
    if (!m_isConnected) {
        return;
    }
    m_ctrlAuthority = MetaTypeConversion::tp2InoApi_controlAuthority(authority);

    qDebug() << "control authority changed : " << static_cast<int>(m_ctrlAuthority);

    emit CommunicationEngine::instance()
        ->signal_controlAuthorityChanged(m_ctrlAuthority);
}

void DataCollectionInterfacePrivate::slot_controllerWiFiFrequencyBandChanged(bool Changed)
{
    qDebug() << "WiFi frequency band changed : " << Changed;
    emit CommunicationEngine::instance()
        ->signal_wifiFrequencyBandChanged(Changed);
}

void DataCollectionInterfacePrivate::slot_speedReducingTriggerdChanged(bool Changed)
{
    LOG_INFO(QString("speed reducing status changed, status = %1").arg(QString::number(Changed)));
    emit CommunicationEngine::instance()
        ->signal_speedReducingTriggerdChanged(Changed);

    m_bSpeedReducingTriggered = Changed;
}

void DataCollectionInterfacePrivate::slot_safetyMonitorStatusChanged(bool Changed)
{
    LOG_INFO(QString("safety monitor status changed, status = %1").arg(QString::number(Changed)));

    m_bSafetyMonitorStatus = Changed;
    emit CommunicationEngine::instance()
        ->signal_safety_monitor_status_changed(m_bSafetyMonitorStatus);
}

void DataCollectionInterfacePrivate::slot_runmodeChanged(InoRobBusiness::RunMode rMode)
{
    qDebug() << "run mode changed : " << rMode;
    if (rMode == InoRobBusiness::RUN_MODE_REAPPEAR) {
        Communication::instance()->SetCurDeviceMode(MetaType::RobotDeviceMode_Auto);
    } else {
        Communication::instance()->SetCurDeviceMode(MetaType::RobotDeviceMode_Manual_Low);
    }
    QMetaObject::invokeMethod(Instance::mainWidget(), "updateDeviceMode", Qt::DirectConnection);
    emit Communication::instance()->signal_runmodeChanged(Communication::instance()->GetCurDeviceMode());
}

void DataCollectionInterfacePrivate::slot_loadIdentifyStatusChanged(int status)
{
    LOG_INFO(QString("load identify status changed, status = %1").arg(QString::number(status)));

    emit CommunicationEngine::instance()->signal_loadidentify_status_changed(status);
}

void DataCollectionInterfacePrivate::slot_printModelLayerMsg(
    InoRobLog::PrintInfo::InfoType type, std::string info)
{
    QString temp = QString::fromStdString(info);
    if (Instance::mainWidget() != 0)
        QMetaObject::invokeMethod(
            Instance::mainWidget(),
            "addLogMsg",
            Qt::DirectConnection,
            Q_ARG(const int, type),
            Q_ARG(const QString &, temp));
}

void DataCollectionInterfacePrivate::slot_currentPositionChanged(
    bool Changed)
{
    static int posChangeIdx = 0;
    FREQ_LOG_INFO(QString("*** Frame ***[%1][%2][%3][%4][%5]")
                      .arg(__FILE__, __FUNCTION__, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"),
                           QString::number(posChangeIdx++),
                           QString::number(reinterpret_cast<intptr_t>(QThread::currentThreadId()))));

    if (Changed) {
        static int posChangeUniqueIdx = 0;
        FREQ_LOG_INFO(QString("*** Frame Unique ***[%1][%2][%3][%4]")
                          .arg(__FILE__, __FUNCTION__, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"),
                               QString::number(posChangeUniqueIdx++)));
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_UpdateLocalPosData);
    }
}

void DataCollectionInterfacePrivate::slot_controllerStateChanged(int state)
{
    LOG_INFO(QString("controller state changed, state = %1").arg(QString::number(state)));
    m_controllerstate = static_cast<ControllerState>(state);
    emit CommunicationEngine::instance()
        ->signal_controllerStateChanged(static_cast<ControllerState>(state));
}

void DataCollectionInterfacePrivate::slot_connectSuccess()
{
    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType_ConnectSuccess);
}

void DataCollectionInterfacePrivate::slot_warningoccur(QString time,
                                                       QString errorCode,
                                                       QString content)
{
    emit CobotLog::instance()
    ->signal_addHistoryAlarm(QString(tr("[Error] [%1] [%2] %3")).arg(time, "0x" + errorCode, content));
    // qDebug() << "Warning Occur : errcode = " << errorCode
    //          << ", content = " << content << ", time = " << time;
}

bool DataCollectionInterfacePrivate::isConnected() const
{
    return m_isConnected;
}

bool DataCollectionInterfacePrivate::isMechLocked() const
{
    return m_isMechLocked;
}

ControllerState DataCollectionInterfacePrivate::GetControllerStatus() const
{
    return m_controllerstate;
}

void DataCollectionInterfacePrivate::GetCurToolParams(int toolId, ToolParams &params)
{
    if (m_toolParams.contains(toolId)) {
        params = m_toolParams[toolId];
    }
}

void DataCollectionInterfacePrivate::GetCurWobjParams(int wobjId, WobjParams &params)
{
    if (m_wobjParams.contains(wobjId)) {
        params = m_wobjParams[wobjId];
    }
}

void DataCollectionInterfacePrivate::SetCurToolParams(int toolId, const ToolParams &params)
{
    m_toolParams[toolId] = params;
}

void DataCollectionInterfacePrivate::SetCurWobjParams(int wobjId, const WobjParams &params)
{
    m_wobjParams[wobjId] = params;
}

QString DataCollectionInterfacePrivate::getWifiName()
{
    QString sRet;
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    QJniObject retName = activity.callObjectMethod("getWifiName",
                                                   "()Ljava/lang/String;");
    sRet = retName.toString();

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
    return sRet;
}

QString DataCollectionInterfacePrivate::getDeviceModel()
{
    QString sRet;
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    QJniObject retName = activity.callObjectMethod("getDeviceModel",
                                                   "()Ljava/lang/String;");
    sRet = retName.toString();

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
    return sRet;
}

void DataCollectionInterfacePrivate::pingInterface(AbstractCmd *absCmd)
{
    int nSend = 0, nRecv = 0;
    double nLoss = 100.0, minT = 0.0, maxT = 0.0, aveT = 0.0;
    auto [ip] = ((CmdDatas<QString> *)absCmd)->m_data;

    _IConnection->ping(nSend, nRecv, nLoss, minT, maxT, aveT, ip.toStdString(), 4);
    QString res = tr("Ping statistics for {0}: ").replace("{0}", ip)
                + "\r\n"
                + QString(tr("    Packet: Sent=%1, Accepted=%2, Loss Rate=%3%") + "\r\n")
                      .arg(QString::number(nSend), QString::number(nRecv), QString::number(nLoss, 'f', 2));
    emit CommunicationEngine::instance()->singnal_getPing_result(absCmd->m_object, res);
}

int DataCollectionInterfacePrivate::getToolIndex(const QString &sTool)
{
    QStringList slistTool = getCurToolNames();
    for (int i = 0; i < slistTool.size(); ++i) {
        if (slistTool[i].compare(sTool) == 0) {
            return i;
        }
    }
    return 0;
}

int DataCollectionInterfacePrivate::getWobjIndex(const QString &sWobj)
{
    QStringList slistWobj = getCurWobjNames();
    for (int i = 0; i < slistWobj.size(); ++i) {
        if (slistWobj[i].compare(sWobj) == 0) {
            return i;
        }
    }
    return 0;
}

void DataCollectionInterfacePrivate::installApk(const QString &sApk)
{
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();

    QJniObject obj = QJniObject::fromString(sApk);
    jstring jsApkName = obj.object<jstring>();

    activity.callMethod<void>("installApk", jsApkName);

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

WifiStrength DataCollectionInterfacePrivate::getWifiStrength()
{
    WifiStrength iRet = WifiStrength_0;
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    jint retStrength = activity.callMethod<int>("getWifiStrength");
    if (retStrength < -88) {
        iRet = WifiStrength_0;
    } else if (retStrength <= -77) {
        iRet = WifiStrength_1;
    } else if (retStrength <= -66) {
        iRet = WifiStrength_2;
    } else if (retStrength <= -55) {
        iRet = WifiStrength_3;
    } else {
        iRet = WifiStrength_4;
    }
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
    return iRet;
}

bool DataCollectionInterfacePrivate::isProgramNotRunning()
{
    InoTaskStatusArr taskStatuses = getTaskStatusArr();
    return (InoTaskStatus::TaskStatus_InActived == taskStatuses.status[0]
            || InoTaskStatus::TaskStatus_Free == taskStatuses.status[0]
            || InoTaskStatus::TaskStatus_Finished == taskStatuses.status[0]);
}

bool DataCollectionInterfacePrivate::isProgramRunning()
{
    InoTaskStatusArr taskStatuses = getTaskStatusArr();
    return (InoTaskStatus::TaskStatus_Running == taskStatuses.status[0]);
}

bool DataCollectionInterfacePrivate::isProgramPause()
{
    InoTaskStatusArr taskStatuses = getTaskStatusArr();
    return (InoTaskStatus::TaskStatus_Paused == taskStatuses.status[0]
            || InoTaskStatus::TaskStatus_Stop == taskStatuses.status[0]);
}

QString DataCollectionInterfacePrivate::getBodyRobotName() const
{
    return m_sBodyRobotName;
}

QString DataCollectionInterfacePrivate::getControllerRobotName() const
{
    return m_sControllerRobotName;
}

void DataCollectionInterfacePrivate::setBodyRobotName(const QString &name)
{
    m_sBodyRobotName = name;
}

void DataCollectionInterfacePrivate::setControllerRobotName(const QString &name)
{
    m_sControllerRobotName = name;
}

void DataCollectionInterfacePrivate::realTimeEndSpeedCallback(double speed, void *p)
{
    s_callbackRegistrant = static_cast<Communication *>(p);
    QMetaObject::invokeMethod(
        s_callbackRegistrant, "signal_sendRealTimeEndSpeed",
        Qt::QueuedConnection,
        Q_ARG(double, speed));
}

void DataCollectionInterfacePrivate::slot_enableStateChanged(bool Changed)
{
    m_isEnable = Changed;
    qDebug() << "enableStateChanged : " << Changed;
    emit CommunicationEngine::instance()->signal_enableStateChanged(Changed);

            // q->_IPosition->SetPosFormat(InoRobUtil::FORMAT_JOINT);
    if (Changed) {
        // 刷一下位置
        slot_currentPositionChanged(true);
    }
}

void DataCollectionInterfacePrivate::slot_emergecyStateChanged(bool Changed)
{
    qDebug() << "slot_emergecyStateChanged : " << Changed;
    m_isEmergency = Changed;
    emit CommunicationEngine::instance()->signal_emergecyStateChanged(Changed);
}

void DataCollectionInterfacePrivate::slot_connectionStatusChanged(
    InoRobBusiness::ControllerConnectionStatus status)
{
    m_isConnected
        = InoRobBusiness::ControllerConnectionStatus::
          CONTROLLER_CONNECTION_STATUS_CONNECTED
       == status;

    if (m_isConnected) {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_InitTeachPadInfo);

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_UpdateLocalToolWobjParams);

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_UpdateLocalSafetyMcuData);

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_UpdateLocalPosData);

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_GeneralMatch_readRobotParamMatchInfo);
    }

    ControllerConnectionState tpStatus
        = MetaTypeConversion::api2tp_controllerConnectionStatus(status);
    emit CommunicationEngine::instance()
        ->signal_controllerConnectionStatusChanged(tpStatus);

    if (InoRobBusiness::ControllerConnectionStatus::
        CONTROLLER_CONNECTION_STATUS_CONNECTING
        == status) {
        return;
    }

    QMetaObject::invokeMethod(
        Instance::projectManageForm(), "refreshDatas",
        Qt::QueuedConnection,
        Q_ARG(bool, m_isConnected));

    Communication::instance()->clearProgramFiles();

            // CommunicationEngine::instance()->enqueueCmd_setData(
            //     this, AbstractCmd::CmdType::CmdType_SetWarnInfoEnable, m_isConnected);
}

void DataCollectionInterfacePrivate::slot_mechLockStateChanged(bool changed)
{
    m_isMechLocked = changed;
    emit CommunicationEngine::instance()
        ->signal_mechLockStateChanged(changed);
}

void DataCollectionInterfacePrivate::slot_initTeachPadInfo_result(
    QObject *object, bool isSuccess, const QString &errMsg)
{
    if (this != object) {
        return;
    }

    if (!isSuccess) {
        if (!errMsg.isEmpty()) {
            MessageBox::warning(errMsg);
        }

        return;
    }
}

void DataCollectionInterfacePrivate::slot_electricChanged()
{
    qDebug() << __FUNCTION__;
    emit CommunicationEngine::instance()->signalElectricChanged();
}

void DataCollectionInterfacePrivate::slot_avgLoadRateChanged()
{
    qDebug() << __FUNCTION__;
    emit CommunicationEngine::instance()->signalAvgLoadRateChanged();
}

void DataCollectionInterfacePrivate::slot_overLoadChanged()
{
    qDebug() << __FUNCTION__;
    emit CommunicationEngine::instance()->signalOverLoadChanged();
}

void DataCollectionInterfacePrivate::slot_overHeatChanged()
{
    qDebug() << __FUNCTION__;
    emit CommunicationEngine::instance()->signalOverHeatChanged();
}

void DataCollectionInterfacePrivate::slot_posFormatChanged(PosFormat format)
{
    qDebug() << "slot_posFormatChanged ** format = " << format;
    RobotCoordDisplayFormat disformat = RobotCoordDisplayFormat_Base;
    switch (format) {
    case FORMAT_BASE:
        disformat = RobotCoordDisplayFormat_Base;
        break;
    case FORMAT_WOBJ:
        disformat = RobotCoordDisplayFormat_User;
        break;
    case FORMAT_WORLD:
        disformat = RobotCoordDisplayFormat_World;
        break;
    case FORMAT_FLANGLE:
        disformat = RobotCoordDisplayFormat_Flange;
        break;
    default:
        disformat = RobotCoordDisplayFormat_Base;
        break;
    }
    m_posFormat = disformat;
    emit CommunicationEngine::instance()
        ->signal_posformat_changed(disformat);
}

void DataCollectionInterfacePrivate::slot_speedChanged(quint16 speed)
{
    LOG_INFO(QString("[slot_speedChanged]speed = %1").arg(QString::number(speed)));
    m_speed = speed;

    emit CommunicationEngine::instance()->signal_speed_changed(speed);
}

void DataCollectionInterfacePrivate::slot_coordType(CoordType coordtype)
{
    qDebug() << "** slot_coordType : coordtype = " << coordtype;
    RobotCoordType tp;
    switch (coordtype) {
    case COORD_BASE:
        tp = RobotCoordType_Base;
        break;
    case COORD_JOINT:
        tp = RobotCoordType_Joint;
        break;
    case COORD_TOOL:
        tp = RobotCoordType_Tool;
        break;
    case COORD_WOBJ:
        tp = RobotCoordType_User;
        break;
    case COORD_WORLD:
        tp = RobotCoordType_World;
        break;
    default:
        tp = RobotCoordType_Base;
        break;
    }
    m_coordType = tp;
    qDebug() << "** slot_coordType : tp = " << tp;
    emit CommunicationEngine::instance()
        ->signal_coordtype_changed(tp);
}

void DataCollectionInterfacePrivate::slot_toolidChanged(quint16 id)
{
    m_toolId = id;
    emit CommunicationEngine::instance()->signal_ToolChanged(id);
}

void DataCollectionInterfacePrivate::slot_wobjidChanged(quint16 id)
{
    m_wobjId = id;
    emit CommunicationEngine::instance()->signal_WobjChanged(id);
}

void DataCollectionInterfacePrivate::slot_loadidChanged(quint16 id)
{
    m_loadId = id;
    emit CommunicationEngine::instance()->signal_LoadChanged(id);
}

void DataCollectionInterfacePrivate::slot_safetyMcuStatusChanged(bool status)
{
    qDebug() << "[" << __FUNCTION__ << "]" << status;
    m_safetyMcuStatus = status;
    emit CommunicationEngine::instance()->signal_safetyMcuStatusChanged(status);
}

void DataCollectionInterfacePrivate::slot_moveStepGradeChanged(
    InoRobBusiness::MoveStepGrade grd)
{
    qDebug() << "[" << __FUNCTION__ << "]" << grd;
    m_stepGrade = static_cast<InoMoveStepGrade>(grd);
    emit CommunicationEngine::instance()->signal_stepgrade_changed(m_stepGrade);
}

void DataCollectionInterfacePrivate::slot_taskRunStatusChanged(
    InoRobBusiness::TaskStatusArr statuses)
{
    qDebug() << "DataCollectionInterfacePrivate::slot_taskRunStatusChanged";
    m_statusArr = MetaTypeConversion::tp2InoApi_taskStatusArr(statuses);
    emit CommunicationEngine::instance()->signal_taskRunStatusChanged(m_statusArr);
}

void DataCollectionInterfacePrivate::slot_safeResetStatusUpdate(int status)
{
    qDebug() << "[" << __FUNCTION__ << "]" << status;

    emit CommunicationEngine::instance()->signal_safety_reset_update_status(status);
}

void DataCollectionInterfacePrivate::slot_safeIOStatusUpdate(S_SAFEIO io)
{
    CobotSafeIO cio;
    memcpy(&cio, &io, sizeof(io));

    LOG_INFO(QString("B DI:%1,%2,%3,%4,%5,%6,%7,%8|DO:%9,%10,%11,%12,%13)")
                 .arg(QString::number(io.DI[0].u8BMcuValue),
                      QString::number(io.DI[1].u8BMcuValue),
                      QString::number(io.DI[2].u8BMcuValue),
                      QString::number(io.DI[3].u8BMcuValue),
                      QString::number(io.DI[4].u8BMcuValue),
                      QString::number(io.DI[5].u8BMcuValue),
                      QString::number(io.DI[6].u8BMcuValue),
                      QString::number(io.DI[7].u8BMcuValue),
                      QString::number(io.DO[0].u8BMcuValue),
                      QString::number(io.DO[1].u8BMcuValue),
                      QString::number(io.DO[2].u8BMcuValue),
                      QString::number(io.DO[3].u8BMcuValue),
                      QString::number(io.DO[4].u8BMcuValue)));

    LOG_INFO(QString("A DI:%1,%2,%3,%4,%5,%6,%7,%8|DO:%9,%10,%11,%12,%13)")
                 .arg(QString::number(io.DI[0].u8BMcuValue),
                      QString::number(io.DI[1].u8BMcuValue),
                      QString::number(io.DI[2].u8BMcuValue),
                      QString::number(io.DI[3].u8BMcuValue),
                      QString::number(io.DI[4].u8BMcuValue),
                      QString::number(io.DI[5].u8BMcuValue),
                      QString::number(io.DI[6].u8BMcuValue),
                      QString::number(io.DI[7].u8BMcuValue),
                      QString::number(io.DO[0].u8AMcuValue),
                      QString::number(io.DO[1].u8AMcuValue),
                      QString::number(io.DO[2].u8AMcuValue),
                      QString::number(io.DO[3].u8AMcuValue),
                      QString::number(io.DO[4].u8AMcuValue)));

    emit CommunicationEngine::instance()->signal_safeio_changed(cio);
}

void DataCollectionInterfacePrivate::slot_logic_tree_item(string uuid)
{
    if (!m_isConnected) {
        return;
    }

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (isProjectLoad) {
        // qDebug() << "slot_logic_tree_item :" << uuid;

        QString sContent = QString::fromStdString(uuid);
        QStringList lUid = sContent.split(",");
        for (size_t i = 0; i < lUid.size(); ++i) {
            emit CommunicationEngine::instance()->signal_logic_tree_item(lUid.at(i).toStdString());
        }
    }
}

void DataCollectionInterfacePrivate::slot_logic_tree_robotMoveItem(string uuid)
{
    if (!m_isConnected) {
        return;
    }

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (isProjectLoad) {
        QString sContent = QString::fromStdString(uuid);
        QStringList lUid = sContent.split(",");
        for (size_t i = 0; i < lUid.size(); ++i) {
            emit CommunicationEngine::instance()->signal_logic_tree_robotMove_item(lUid.at(i));
        }
    }
}

void DataCollectionInterfacePrivate::slot_tragteach_status(string content)
{
    LOG_INFO(QString("[DragTeach]status content : %1").arg(content.c_str()));

    QJsonDocument doc(QJsonDocument::fromJson(content.c_str()));
    QJsonObject rootObj = doc.object();
    int iEventStatus = rootObj.value("DragTeachEvent").toVariant().toInt();
    m_bDragTeachStatus = (iEventStatus == 1);
    emit CommunicationEngine::instance()->signal_tragteach_status(iEventStatus == 1);
}

void DataCollectionInterfacePrivate::slot_tragteach_autorecordpos(string content)
{
    if (!Communication::instance()->isConnected()) return;

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (!isProjectLoad) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 0);
        SHOW_MSG(tr("Automatic point recording failed. Please create or open a project first."));
        return;
    }

    LOG_INFO(QString("[DragTeach]recordpos content : %1").arg(content.c_str()));

    QJsonDocument doc(QJsonDocument::fromJson(content.c_str()));
    QJsonObject rootObj = doc.object();

    InoPosType type = InoPosType_P;

    QJsonObject jpos = rootObj.value("JPos").toObject();
    QJsonArray jposData = jpos.value("JPosData").toArray();
    // QJsonArray ejposdata = jpos.value("EJPosData").toArray();

    QJsonObject robpos = rootObj.value("RobPos").toObject();
    QJsonArray robposdata = robpos.value("RobPosData").toArray();
    QJsonArray armparam = robpos.value("ArmParm").toArray();
    // QJsonArray erobposdata = robpos.value("ERobPosData").toArray();

    int status = rootObj.value("Status").toVariant().toInt();
    if (status == -1) {
        return;
    }

    RoadPoint pt;
    pt.m_position.m_x = robposdata[0].toVariant().toDouble();
    pt.m_position.m_y = robposdata[1].toVariant().toDouble();
    pt.m_position.m_z = robposdata[2].toVariant().toDouble();
    pt.m_orientation.m_rz = robposdata[5].toVariant().toDouble();
    pt.m_orientation.m_ry = robposdata[4].toVariant().toDouble();
    pt.m_orientation.m_rx = robposdata[3].toVariant().toDouble();

    pt.m_arm[0] = armparam[0].toVariant().toDouble();
    pt.m_arm[1] = armparam[1].toVariant().toDouble();
    pt.m_arm[2] = armparam[2].toVariant().toDouble();
    pt.m_arm[3] = armparam[3].toVariant().toDouble();

    double dAngles[6] = {0};
    dAngles[0] = jposData[0].toVariant().toDouble();
    dAngles[1] = jposData[1].toVariant().toDouble();
    dAngles[2] = jposData[2].toVariant().toDouble();
    dAngles[3] = jposData[3].toVariant().toDouble();
    dAngles[4] = jposData[4].toVariant().toDouble();
    dAngles[5] = jposData[5].toVariant().toDouble();
    pt.setJointAngle(dAngles);

    pt.m_isSingular = (status == 2);

    qDebug() << "**************** TragTeach RecordPoint ****************";
    pt.print();

    emit CommunicationEngine::instance()->signal_tragteach_autorecordpos(type, pt);
}

void DataCollectionInterfacePrivate::slot_timer_value(std::string content)
{
    if (!m_isConnected) {
        return;
    }

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (isProjectLoad) {

#ifndef INOCOBOTTP_MSVC_QT5
        qDebug() << "slot_timer_value :" << content;
#endif

        InoTimerInfo info = getTimerInfo(content);
        if (info.isValid()) {
            return;
        }

        emit CommunicationEngine::instance()->signal_update_timer_info(info);
    }
}

void DataCollectionInterfacePrivate::slot_pallet_change(std::string content)
{
    emit CommunicationEngine::instance()->signal_sendPalletInfo(content);
}

void DataCollectionInterfacePrivate::slot_nng_keepalive(std::string content)
{
    return;
}

void DataCollectionInterfacePrivate::slot_tool_io_description(std::string content)
{
    if (!m_isConnected) {
        LOG_INFO("update tool io descriptions failed, please connect controller first.");
        return;
    }

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (!isProjectLoad) {
        LOG_INFO("update tool io descriptions failed, please create or open a project first.");
        return;
    }

    if (!Communication::instance()->isConnectVirtualController()) {
        emit CommunicationEngine::instance()
            ->signal_updateToolIOItemDescription(QString::fromStdString(content));
    }
}

void DataCollectionInterfacePrivate::slot_toolWobjMatchStatusChanged(
    InoRobBusiness::ToolWobjMatchStatus status)
{
    qDebug() << "slot_toolWobjMatchStatusChanged status :" << status;
    m_toolWobjMatchStatus = static_cast<int>(status);
}

void DataCollectionInterfacePrivate::slot_run_status_changed(
    InoRobBusiness::ControllerRunStatus status)
{
    m_runstatus = static_cast<MetaType::CobotControllerRunStatus>(status);
}

void DataCollectionInterfacePrivate::slot_modbus_connectstatus_changed()
{
    LOG_INFO("modbus connect status changed.");
    emit CommunicationEngine::instance()->signal_modbus_connectstatus_changed();
}

void DataCollectionInterfacePrivate::slot_ethernetip_connectstatus_changed()
{
    LOG_INFO("ethernetip connect status changed.");
    emit CommunicationEngine::instance()->signal_ethernetip_connectstatus_changed();
}

void DataCollectionInterfacePrivate::slot_ethercat_connectstatus_changed()
{
    LOG_INFO("ethercat connect status changed.");
    emit CommunicationEngine::instance()->signal_ethercat_connectstatus_changed();
}

void DataCollectionInterfacePrivate::slot_collisionRecommendedValueChange(qint16 value)
{
    emit CommunicationEngine::instance()->signal_collisionRecommendedValueChange(value);
}

void DataCollectionInterfacePrivate::slot_collisionStatusChange(bool isChanged)
{
    emit CommunicationEngine::instance()->signal_collisionStatusChange(isChanged);
}

void DataCollectionInterfacePrivate::slot_CompleteFricIdentify(int isFinish)
{
    emit CommunicationEngine::instance()->signal_CompleteFricIdentify(isFinish);
}
}  // namespace Internal

using namespace Internal;

DataCollectionInterface::DataCollectionInterface()
{
    d = new DataCollectionInterfacePrivate(this);
}

DataCollectionInterface::~DataCollectionInterface()
{
    delete d;
    d = 0;
}

void DataCollectionInterface::realTimeEndSpeedCallback(double speed, void *p)
{
    d->realTimeEndSpeedCallback(speed, p);
}

void DataCollectionInterface::pingInterface(AbstractCmd *absCmd)
{
    d->pingInterface(absCmd);
}

int DataCollectionInterface::getToolIndex(const QString &sTool)
{
    return d->getToolIndex(sTool);
}

int DataCollectionInterface::getWobjIndex(const QString &sWobj)
{
    return d->getWobjIndex(sWobj);
}

void DataCollectionInterface::installApk(const QString &sApk)
{
    d->installApk(sApk);
}

void DataCollectionInterface::listenStateChanged()
{
    d->listenStateChanged();
}

void DataCollectionInterface::initdatas()
{
    d->initdatas();
}

bool DataCollectionInterface::isConnected()
{
    return d->isConnected();
}

bool DataCollectionInterface::isMechLocked() const
{
    return d->isMechLocked();
}

int DataCollectionInterface::GetCurToolId() const
{
    return d->GetCurToolId();
}

int DataCollectionInterface::GetCurWObjId() const
{
    return d->GetCurWObjId();
}

int DataCollectionInterface::GetCurLoadId() const
{
    return d->GetCurLoadId();
}

MetaType::CobotControllerRunStatus DataCollectionInterface::getCurRunStatus() const
{
    return d->getCurRunStatus();
}

bool DataCollectionInterface::getSafetyMcuStatus() const
{
    // return true;
    return d->getSafetyMcuStatus();
}

void DataCollectionInterface::setSafetyMcuStatus(bool bStatus)
{
    d->setSafetyMcuStatus(bStatus);
}

QStringList DataCollectionInterface::getCurToolNames() const
{
    return d->getCurToolNames();
}

QStringList DataCollectionInterface::getCurWobjNames() const
{
    return d->getCurWobjNames();
}

QStringList DataCollectionInterface::getLoadNames() const
{
    return d->getLoadNames();
}

bool DataCollectionInterface::IsEnable() const
{
    return d->GetEnable();
}

bool DataCollectionInterface::IsEmergency() const
{
    return d->GetEmergency();
}

quint16 DataCollectionInterface::GetCurSpeed() const
{
    return d->GetCurSpeed();
}

void DataCollectionInterface::SetCurSpeed(quint16 speed)
{
    d->SetCurSpeed(speed);
}

InoCoRobotBodyPowerState DataCollectionInterface::GetBodyPowerState() const
{
    return d->GetBodyPowerState();
}

RobotCoordDisplayFormat DataCollectionInterface::GetCurPosFormat() const
{
    return d->GetCurPosFormat();
}

void DataCollectionInterface::SetCurPosFormat(RobotCoordDisplayFormat format)
{
    d->SetCurPosFormat(format);
}

RobotCoordType DataCollectionInterface::GetCurCoodType() const
{
    return d->GetCurCoodType();
}

MetaType::RobotDeviceMode DataCollectionInterface::GetCurDeviceMode() const
{
    return d->GetCurDeviceMode();
}

void DataCollectionInterface::SetCurDeviceMode(MetaType::RobotDeviceMode mode)
{
    d->SetCurDeviceMode(mode);
}

RoadPoint DataCollectionInterface::GetRealTimePt() const
{
    return d->GetRealTimePt();
}

RoadPoint DataCollectionInterface::GetRealTimeFlange2BasePt() const
{
    return d->GetRealTimeFlange2BasePt();
}

ControllerState DataCollectionInterface::GetControllerStatus() const
{
    return d->GetControllerStatus();
}

void DataCollectionInterface::SetRealTimePt(const RoadPoint &pt)
{
    d->SetRealTimePt(pt);
}

void DataCollectionInterface::SetRealTimeFlage2BasePt(const RoadPoint &pt)
{
    d->SetRealTimeFlage2BasePt(pt);
}

void DataCollectionInterface::setPostureAlphaBeta(double alpha, double beta)
{
    d->setPostureAlphaBeta(alpha, beta);
}

void DataCollectionInterface::getPostureAlphaBeta(double &alpha, double &beta)
{
    d->getPostureAlphaBeta(alpha, beta);
}

WifiStrength DataCollectionInterface::getWifiStrength()
{
    return d->getWifiStrength();
}

bool DataCollectionInterface::getSafetyMonitorStatus() const
{
    return d->getSafetyMonitorStatus();
}

InoTaskStatusArr DataCollectionInterface::getTaskStatusArr() const
{
    return d->getTaskStatusArr();
}

void DataCollectionInterface::setMultiTaskNameList(const QVector<InoTaskInfo> &taskList)
{
    d->setMultiTaskNameList(taskList);
}

QStringList DataCollectionInterface::getMultiTaskNameList() const
{
    return d->getMultiTaskNameList();
}

void DataCollectionInterface::addScript(const QString &name)
{
    d->addScript(name);
}

void DataCollectionInterface::removeScript(const QString &name)
{
    d->removeScript(name);
}

void DataCollectionInterface::clearScriptNameList()
{
    d->clearScriptNameList();
}

QStringList DataCollectionInterface::getScriptNameList() const
{
    return d->getScriptNameList();
}

QStringList DataCollectionInterface::programFiles() const
{
    return d->programFiles();
}

void DataCollectionInterface::addProgramFile(const QString &fileName)
{
    d->addProgramFile(fileName);
}

void DataCollectionInterface::removeProgramFile(const QString &fileName)
{
    d->removeProgramFile(fileName);
}

void DataCollectionInterface::clearProgramFiles()
{
    d->clearProgramFiles();
}

void DataCollectionInterface::setProgramFinished()
{
    d->setProgramFinished();
}

bool DataCollectionInterface::isProgramNotRunning()
{
    return d->isProgramNotRunning();
}

bool DataCollectionInterface::isProgramRunning()
{
    return d->isProgramRunning();
}

bool DataCollectionInterface::isProgramPause()
{
    return d->isProgramPause();
}

InoMoveStepGrade DataCollectionInterface::getMoveStepGrade() const
{
    return d->getMoveStepGrade();
}

void DataCollectionInterface::GetCurToolParams(int toolId, ToolParams &params)
{
    d->GetCurToolParams(toolId, params);
}

void DataCollectionInterface::GetCurWobjParams(int wobjId, WobjParams &params)
{
    d->GetCurWobjParams(wobjId, params);
}

void DataCollectionInterface::SetCurToolParams(int toolId, const ToolParams &params)
{
    return d->SetCurToolParams(toolId, params);
}

void DataCollectionInterface::SetCurWobjParams(int wobjId, const WobjParams &params)
{
    return d->SetCurWobjParams(wobjId, params);
}

QString DataCollectionInterface::getWifiName()
{
    return d->getWifiName();
}

QString DataCollectionInterface::getDeviceModel()
{
    return d->getDeviceModel();
}

InoCtrlAuthority DataCollectionInterface::GetCurCtrlAuthority() const
{
    return d->getCurCtrlAuthority();
}

void DataCollectionInterface::setCurCtrlAuthority(const InoCtrlAuthority &ctrlAuthority)
{
    d->setCurCtrlAuthority(ctrlAuthority);
}

int DataCollectionInterface::getToolWobjMatchStatus() const
{
    return d->getToolWobjMatchStatus();
}

uint8_t DataCollectionInterface::getCurStartReleaseStrategy() const
{
    return d->getCurStartReleaseStrategy();
}

void DataCollectionInterface::setCurStartReleaseStrategy(uint8_t strategy)
{
    d->setCurStartReleaseStrategy(strategy);
}

bool DataCollectionInterface::getCurSpeedReducingTrigger() const
{
    return d->getCurSpeedReducingTrigger();
}

QString DataCollectionInterface::getBodyRobotName() const
{
    return d->getBodyRobotName();
}

QString DataCollectionInterface::getControllerRobotName() const
{
    return d->getControllerRobotName();
}

void DataCollectionInterface::setBodyRobotName(const QString &name)
{
    d->setBodyRobotName(name);
}

void DataCollectionInterface::setControllerRobotName(const QString &name)
{
    d->setControllerRobotName(name);
}

QString DataCollectionInterface::getCurProjectName() const
{
    return d->getCurProjectName();
}

void DataCollectionInterface::setCurProjectName(const QString &name)
{
    d->setCurProjectName(name);
}

QStringList DataCollectionInterface::getTPConfigureFileNames() const
{
    return d->getTPConfigureFileNames();
}

void DataCollectionInterface::setCurDragTeachStatus(bool bStatus)
{
    d->setCurDragTeachStatus(bStatus);
}

bool DataCollectionInterface::getCurDragTeachStatus() const
{
    return d->getCurDragTeachStatus();
}

bool DataCollectionInterface::event(QEvent *event)
{
    switch (static_cast<int>(event->type())) {
    default:
        break;
    }

    return QObject::event(event);
}
