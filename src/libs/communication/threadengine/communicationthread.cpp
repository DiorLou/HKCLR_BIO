#include "communicationthread.h"
#include <QMutex>
#include <QDebug>
#include <QVariant>
#include <QWaitCondition>
#include <functional>
#include "communicationengine.h"
#include "communication.h"
#include "fileutils.h"
#include "projectinterface.h"
#include "project/projectinfo.h"
#include "stringutils.h"
#include "cobotlog.h"
#include "commandinfo.h"
#include "InoRobBusiness/Project/IProject.h"
#include "InoRobBusiness/RobotParam/IRobotParam.h"
#include "cobotlog/cobotlog.h"
#include "safety/safetydefines.h"
#include "safety/crashdetectparams.h"
#include "templateutils.h"
#include "debuggerdefines.h"
#include "metapath.h"
#include "simpleitem.h"
#include "palletitemdefine.h"
#include <QBrush>
#include "udf.h"
#ifdef Q_OS_ANDROID
    #include <QJniEnvironment>
    #include <QJniObject>
#endif

#ifdef INOCOBOTTP_MSVC_QT5
    #include <QDateTime>
#endif

using namespace std;

const quint16 MAX_REMOVE_REPETIVE_COUNT = 3;  //最多筛3个
const char TeachPad_CONFIGURE_FILE_DIR[] = "TecParameter";

CommunicationThread::CommunicationThread(ThreadType threadType) :
    m_isQuitThread(false), m_threadType(threadType)
{
    m_queueMutex = new QMutex;

    m_waitConditionMutex = new QMutex;
    m_waitCondition = new QWaitCondition;

    m_quitConditionMutex = new QMutex;
    m_quitCondition = new QWaitCondition;

    //?=
    // m_commInstance = new Communication;
    m_commInstance = Communication::instance();
    m_cmdQueue.clear();

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetRS485Config] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadRS485Config] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_WriteRobotBodyParameters] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadDiagnosePercent] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_readRestoreFactoryState] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_startConfigFilesBackupToUsb] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_readConfigFilesBackupStateToUsb] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_startLoadConfigFilesFromUsb] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_readLoadConfigFilesSateFromUsb] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetControlAuthority] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_InstallationPosture_Write] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SaveEmgTrigMethod] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Debugger_StartReleaseWrite] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_StartExportDiagnoseReportToUSB] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_StartExportDiagnoseReportToLocal] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadErrExportStaToControllerUSB] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadErrExportStaToLocal] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetAbsoluteZero] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetWorkOriginTriggerData] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetWorkOrigin] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_setPointFileNoConfig] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_setProjectNoConfig] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Save_IOMapping_Values] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetFieldBusAddressAssignConfig] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Set_ConrtollerTime] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Communication_SetEthDatas] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Communication_SetNewPort] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Communication_SetOneNetStatus] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetRS485Debugging] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_GetHistoryAlarm] = 1;

    // m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetRS485OrADModel] = 1;
    // m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_SetRS485Config] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ExportConfigFileToLocal] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ImportConfigFileFromLocal] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadExportConfigFileStatusToLocal] = 1;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_ReadImportConfigFileStatusFromLocal] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_WriteSevenRobotBodyParameters] = 1;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Input_ValuesStandard] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Input_ValuesTool] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Input_ValuesFieldBus] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Input_ValuesMemory] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Output_ValuesStandard] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Output_ValuesTool] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Output_ValuesFieldBus] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_Get_Output_ValuesMemory] = 5;

    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getDeviceConnectionState] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getMobusConnectionState] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getEtherNetIpConnectionState] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getEtherCatIpConnectionState] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getMCConnectionState] = 5;
    m_hash_Type_MapTo_MaxCount[AbstractCmd::CmdType_getProfinetConnectionState] = 5;

}

CommunicationThread::ThreadType CommunicationThread::getThreadType()
{
    return m_threadType;
}

CommunicationThread::~CommunicationThread()
{
    delete m_queueMutex;
    delete m_waitConditionMutex;
    delete m_waitCondition;
    delete m_quitConditionMutex;
    delete m_quitCondition;
}

AbstractCmd *CommunicationThread::enqueueCmdInfo(AbstractCmd *absCmd)
{
    QPair<int, QObject *> temp
        = QPair<int, QObject *>(absCmd->m_cmdType, absCmd->m_object);
    AbstractCmd *tempCmd = absCmd;
    int limitCount = -1;
    bool addSuccess = true;
    if (m_hash_Type_MapTo_MaxCount.contains(absCmd->m_cmdType))
        limitCount = m_hash_Type_MapTo_MaxCount[absCmd->m_cmdType];

    m_queueMutex->lock();
    if (limitCount > 0
        && m_Hash_TypeAndObject_MapTo_QueueCount.contains(temp)
        && m_Hash_TypeAndObject_MapTo_QueueCount[temp] == limitCount) {
        QList<int> index;
        int size = m_cmdQueue.size();
        for (int i = 0; i < size; ++i) {
            if (m_cmdQueue[i]->m_cmdType == absCmd->m_cmdType
                && m_cmdQueue[i]->m_object == absCmd->m_object) {
                index.push_back(i);
            }
        }
        if (index.size() == limitCount) {
            tempCmd = m_cmdQueue[index[0]];
            for (int i = 1; i < limitCount; ++i) {
                m_cmdQueue[index[i - 1]] = m_cmdQueue[index[i]];
            }
            m_cmdQueue[index[limitCount - 1]] = absCmd;
        } else {
            PRINT_ERROR("Count isn't same! Size is"
                        + QString::number(index.size())
                        + ". Limit is" + QString::number(limitCount));
        }
        addSuccess = false;
    } else if(limitCount == 0 && m_lastTasktype == absCmd->m_cmdType && m_lastTaskObject == absCmd->m_object){
        addSuccess = false;
    } else {
        tempCmd = 0;
        m_cmdQueue.push_back(absCmd);
        ++m_Hash_TypeAndObject_MapTo_QueueCount[temp];
    }
    m_queueMutex->unlock();

    if (addSuccess) {
        m_waitConditionMutex->lock();
        m_waitCondition->wakeAll();
        m_waitConditionMutex->unlock();
    }
    return tempCmd;
}

void CommunicationThread::stopThread()
{
    m_isQuitThread = true;

    bool isTimeOut = false;

    m_quitConditionMutex->lock();
    isTimeOut = m_quitCondition->wait(m_quitConditionMutex, 1000) ?
                    false :
                    true;
    m_quitConditionMutex->unlock();

    if (isTimeOut) {
        qDebug() << "Timed out waiting for thread to exit";
        this->terminate();
        this->wait(1000);
    }

    int size = m_cmdQueue.size();
    for (int i = 0; i < size; ++i) {
        delete m_cmdQueue[i];
    }
    m_cmdQueue.clear();
}

void CommunicationThread::run()
{
    FREQ_LOG_INFO(
        QString("*** Interface ***[%1][%2][%3][%4]")
            .arg(__FILE__, __FUNCTION__,
                 QString::number(QDateTime::currentMSecsSinceEpoch()),
                 QString::number(reinterpret_cast<intptr_t>(
                     QThread::currentThreadId()))));

    while (!m_isQuitThread) {
        m_waitConditionMutex->lock();
        m_waitCondition->wait(m_waitConditionMutex, 50);
        m_waitConditionMutex->unlock();

        while (!m_cmdQueue.isEmpty()) {
            m_queueMutex->lock();
            AbstractCmd *absCmd = m_cmdQueue[0];
            m_lastTasktype = absCmd->m_cmdType;
            m_lastTaskObject = absCmd->m_object;

#if defined(INOCOBOTTP_MSVC_QT5)
                m_cmdQueue.erase(m_cmdQueue.begin());
#else
                m_cmdQueue.erase(m_cmdQueue.cbegin());
#endif
            --m_Hash_TypeAndObject_MapTo_QueueCount
                [QPair<int, QObject *>(absCmd->m_cmdType, absCmd->m_object)];
            m_queueMutex->unlock();

            if (CommunicationThread::Thread_LocalTask == m_threadType) {
                CommunicationEngine *engine = CommunicationEngine::instance();
                LOG_ERROR(QString("Start process cmd type=%1, exeThread index=%2")
                              .arg(absCmd->m_cmdType)
                              .arg(engine ? engine->getLoacalTaskThreadPool().indexOf(this) : -1));
            }
            processTasks(absCmd);
            if (CommunicationThread::Thread_LocalTask == m_threadType) {
                CommunicationEngine *engine = CommunicationEngine::instance();
                LOG_ERROR(QString("End process cmd type=%1, exeThread index=%2")
                              .arg(absCmd->m_cmdType)
                              .arg(engine ? engine->getLoacalTaskThreadPool().indexOf(this) : -1));
            }

            m_queueMutex->lock();
            m_lastTasktype = -1;
            m_lastTaskObject = nullptr;
            m_queueMutex->unlock();

            CommunicationEngine *engine = CommunicationEngine::instance();
            if (engine) {
                engine->taskFinish(this, absCmd);
            } else {
                LOG_ERROR(QStringLiteral("CommunicationThread::run engine is null, cmdType=%1 cmd=0x%2 obj=0x%3")
                              .arg(static_cast<int>(absCmd->m_cmdType))
                              .arg(reinterpret_cast<quintptr>(absCmd), 0, 16)
                              .arg(reinterpret_cast<quintptr>(absCmd->m_object), 0, 16));
                delete absCmd;
            }
            // qDebug()<<"delete(absCmd)"<<absCmd->m_cmdType;
        }
    }

    m_quitConditionMutex->lock();
    m_quitCondition->wakeAll();
    m_quitConditionMutex->unlock();

    qDebug() << "Quit thread: " << QThread::currentThread();
}


void CommunicationThread::processTasks(AbstractCmd *absCmd)
{
    switch (absCmd->m_cmdType) {
    case AbstractCmd::CmdType_setRGB: {
        setRGB(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getBacklashParams: {
        m_commInstance->getBacklashParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_startBacklashIdentification: {
        m_commInstance->startBacklashIdentification(absCmd);
        break;
    }
    case AbstractCmd::CmdType_endBacklashIdentification: {
        m_commInstance->endBacklashIdentification(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getCoulombFrictionParams: {
        m_commInstance->getCoulomFrictionParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getRecommendedTrajectoryEndPoints: {
        m_commInstance->getRecommendedTrajectoryEndPoints(absCmd);
        break;
    }
    case AbstractCmd::CmdType_startFricIdentification: {
        m_commInstance->startFricIdentification(absCmd);
        break;
    }
    case AbstractCmd::CmdType_endFricIdentification: {
        m_commInstance->endFricIdentification(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SendMasterConfigZipFile:{
        m_commInstance->sendMasterConfigFile(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCSensorDataArr:{
        m_commInstance->getFCSensorDataArr(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCSensorItem:{
        m_commInstance->saveFCSensorItem(absCmd);
        break;
    }
    case AbstractCmd::CmdType_isCanCalibrate:{
        m_commInstance->isCanCalibrate(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCCalibData:{
        m_commInstance->getFCCalibData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCCalibItem:{
        m_commInstance->saveFCCalibItem(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ApplyCaliResult:{
        m_commInstance->applyCaliResult(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCCoordinateData:{
        m_commInstance->getFCCoordinateData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCCoordinateDataItem:{
        m_commInstance->saveFCCoordinateDataItem(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCConfigPara:{
        m_commInstance->getFCConfigParam(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCConfigPara:{
        m_commInstance->saveFCConfigParam(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCControlPara:{
        m_commInstance->getFCControlParam(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCControlPara:{
        m_commInstance->saveFCControlParam(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFCLimitPara:{
        m_commInstance->getFCLimitData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SaveFCLimitPara:{
        m_commInstance->saveFCLimitData(absCmd);
        break;
    }
    // 力控监控命令
    case AbstractCmd::CmdType_ReadForceCtrlLogForamt: {
        m_commInstance->readForceCtrlLogFormat(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetForceCtrlLogForamt: {
        m_commInstance->writeForceCtrlLogFormat(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadForceCtrlMonitorSwitch: {
        m_commInstance->readForceCtrlMonitorSwitch(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetForceCtrlMonitorSwitch: {
        m_commInstance->writeForceCtrlMonitorSwitch(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadForceCtrlMonitorData: {
        m_commInstance->readForceCtrlMonitorData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetClearSensorForce: {
        m_commInstance->writeClearSensorForce(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadForceCtrlCoordinateSetting: {
        m_commInstance->readForceCtrlCoodinateSetting(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetForceCtrlCoordinateSetting: {
        m_commInstance->writeForceCtrlCoodinateSetting(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetToolData: {
        m_commInstance->getToolData(absCmd);
        break;
    }
    case AbstractCmd:: CmdType_GetForceCtrlLogList: {
        m_commInstance->getForceCtrlLogList(absCmd);
        break;
    }
    case AbstractCmd:: CmdType_CopyFCLogsControllerToLoacl: {
        m_commInstance->copyLogFilesFromControlToLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_LoadRobotModelSegment:{
        loadRobotModelSegment(absCmd);
        break;
    }
    case AbstractCmd::CmdType_LoadRobotModel:{
        loadRobotModel(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getLogicTreeStartLine:{
        getLogicTreeStartLine(absCmd);
        break;
    }
    case AbstractCmd::CmdType_setLogicTreeStartLine:{
        setLogicTreeStartLine(absCmd);
        break;
    }
    case AbstractCmd::CmdType_operationLogicTreeLineNum:{
        calLineNum(absCmd);
        break;
    }
    case AbstractCmd::CmdType_operationLogicTreeBreakPoint:{
        logicTreeBreakPointOperation(absCmd);
        break;
    }
    case AbstractCmd::CmdType_setEnabledAllLogicTreeBreakPoint:{
        setEnabledAllBreakPoints(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getEnabledAllLogicTreeBreakPoint:{
        getEnabledAllBreakPoints(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetRobotDeviceInfo: {
        getRobotPointFileList(absCmd);
        break;
    }
    case AbstractCmd::CmdType_RobotMoveTeachStart: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        CmdTeachMoveControl *cmd
            = static_cast<CmdTeachMoveControl *>(absCmd);
        bool isSuccess
            = m_commInstance->robotMoveTeachStartOrStopInterface(
                cmd->m_teachMode, cmd->m_direction, cmd->m_coordParam, true);
        emit CommunicationEngine::instance()
            ->signal_robotMoveTeachStartInterface_result(isSuccess);

        break;
    }
    case AbstractCmd::CmdType_RobotMoveTeachStop: {
        CmdTeachMoveControl *cmd
            = static_cast<CmdTeachMoveControl *>(absCmd);
        bool isSuccess
            = m_commInstance->robotMoveTeachStartOrStopInterface(
                cmd->m_teachMode, cmd->m_direction, cmd->m_coordParam, false);
        // m_commInstance->robotMoveTeachStopInterface();
        break;
    }
    case AbstractCmd::CmdType_RobotMoveStop: {
        m_commInstance->robotMoveSlowlyStopInterface();
        break;
    }
    case AbstractCmd::CmdType_RobotMoveJointToInitPosture: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        emit CommunicationEngine::instance()->signal_contimotion();

        InoJPos pos;
        QList<double> min, max;
        if (m_commInstance->getWorikOriginPoint(0, pos, min, max)) {
            RoadPoint point;
            point.setJointAngle(pos.JointData);
            bool isSuccess
                = m_commInstance->robotMoveJointTeachInterface(point);
            if (isSuccess)
                 return;
        }
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
            tr("Failed to move to initial pose."));
        break;
    }
    case AbstractCmd::CmdType_RobotMoveJointTeach: {
        qDebug() << "CmdType_RobotMoveJointTeach";
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        emit CommunicationEngine::instance()->signal_contimotion();

        CmdRobotMoveJoint *cmd
            = static_cast<CmdRobotMoveJoint *>(absCmd);
        bool isSuccess = m_commInstance->robotMoveJointTeachInterface(
            cmd->m_roadPoint);
        emit CommunicationEngine::instance()
            ->signal_axisMoveInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_RobotMoveJointWithRP: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        emit CommunicationEngine::instance()->signal_contimotion();

        CmdRobotMoveJointWithRP *cmd
            = static_cast<CmdRobotMoveJointWithRP *>(absCmd);
        bool isSuccess = m_commInstance->robotMoveJointInterface(
            cmd->m_robPos);
        emit CommunicationEngine::instance()
            ->signal_axisMoveInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_RobotMoveLineTeach: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        emit CommunicationEngine::instance()->signal_contimotion();

        CmdRobotMoveLine *cmd
            = static_cast<CmdRobotMoveLine *>(absCmd);
        bool isSuccess
            = m_commInstance->robotMoveLineInterface(cmd->m_destPt);
        emit CommunicationEngine::instance()
            ->signal_axisMoveInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_RobotMoveRotateTeach: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        CmdRobotMoveRotate *cmd
            = static_cast<CmdRobotMoveRotate *>(absCmd);
        bool isSuccess = m_commInstance->robotMoveRotateTeachInterface(
            cmd->m_coordParam, cmd->m_teachMode, cmd->m_rotateAngle);
        emit CommunicationEngine::instance()
            ->signal_axisMoveInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_WriteEthernetIpConfig: {
        bool isSuccess = m_commInstance->checkSaveEthernetIPPermission();
        if (!isSuccess) {
            emit CommunicationEngine::instance()
                ->signal_writeEthernetIpConfig_result(isSuccess);
            break;
        }

        CmdWriteEthernetIpConfig *cmd
            = static_cast<CmdWriteEthernetIpConfig *>(absCmd);
        isSuccess = m_commInstance->writeEthernetIpConfig(cmd->m_params);
        emit CommunicationEngine::instance()
            ->signal_writeEthernetIpConfig_result(isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ReadEthernetIpConnStatus: {
        CobotEthernetIpSts status;
        bool bSuccess = m_commInstance->readEthernetIpConnStatus(status);
        emit CommunicationEngine::instance()
            ->signal_readEthernetIpConnStatus_result(bSuccess, status);
        break;
    }
    case AbstractCmd::CmdType_WriteEtherCatConfig: {
        CmdWriteEthernetCatConfig *cmd
            = static_cast<CmdWriteEthernetCatConfig *>(absCmd);

        bool isSuccess = m_commInstance->checkSaveEthernetCatPermission();
        qDebug() << "checkpermission = " << isSuccess;
        if (!isSuccess) {
            emit CommunicationEngine::instance()
                ->signal_writeEthernetCatConfig_result(
                    cmd->m_object, isSuccess);
            break;
        }

        int iRet = m_commInstance->WriteEtherCATEnhan(
            cmd->ARMSetLinkEnhanSwitch, cmd->EtherCATXMLReset);
        isSuccess = (isSuccess && (iRet == 0));
        if (!isSuccess) {
            emit CommunicationEngine::instance()
                ->signal_writeEthernetCatConfig_result(
                    cmd->m_object, isSuccess);
            break;
        }

        isSuccess = m_commInstance->writeEthernetCatConfig(cmd->m_params);
        emit CommunicationEngine::instance()
            ->signal_writeEthernetCatConfig_result(cmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ReadEtherCatStatus: {
        InoEthcatSts status;
        INO_ETHCAT_PROP prop;
        bool bSuccess = m_commInstance->readEthernetCatConnStatus(status);
        int iRet = m_commInstance->ReadEtherCATProperties(prop);
        bSuccess = (bSuccess && (iRet == 0));
        emit CommunicationEngine::instance()
            ->signal_readEthernetCatConnStatus_result(
                absCmd->m_object, bSuccess, status, prop);
        break;
    }
    case AbstractCmd::CmdType_CheckOtherFieldBusIsActive: {
        CmdCheckOtherFieldBusIsActive *cmd
            = static_cast<CmdCheckOtherFieldBusIsActive *>(absCmd);
        bool bRet = Communication::instance()->checkOtherFieldBusIsActive(
            cmd->m_type);
        emit CommunicationEngine::instance()
            ->signal_checkOtherFieldBusIsActive_result(
                absCmd->m_object, cmd->m_target, bRet);
        break;
    }
    case AbstractCmd::CmdType_WriteModbusConfig: {
        CmdWriteModbusConfig *cmd
            = static_cast<CmdWriteModbusConfig *>(absCmd);

        bool isSuccess = m_commInstance->checkSaveModbusPermission();
        if (!isSuccess) {
            emit CommunicationEngine::instance()
                ->signal_writeModbusConfig_result(isSuccess);
            break;
        }

        isSuccess = m_commInstance->writeModbusConfig(cmd->m_config);
        emit CommunicationEngine::instance()
            ->signal_writeModbusConfig_result(isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ReadModbusConnStatus: {
        CobotModbusConnectSts status;
        bool isSuccess = m_commInstance->readModbusConnStatus(status);
        emit CommunicationEngine::instance()
            ->signal_readModbusConnStatus_result(isSuccess, status);
        break;
    }
    case AbstractCmd::CmdType_Ping: {
        m_commInstance->ping(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetControllerWifiPassword: {
        CmdCommonValue *cmd = static_cast<CmdCommonValue *>(absCmd);
        QString sPassword = cmd->m_value.toString();
        bool isSuccess = m_commInstance->setControllerWifiPassword(sPassword);
        InoWifiPasswordModifyResult result = WifiPasswordModifyResult_Unknown;
        if (isSuccess) {
            isSuccess = m_commInstance->getWifiPasswordModifyResult(result);
        }

        emit CommunicationEngine::instance()
            ->signal_setControllerWifiPassword_result(
                absCmd->m_object, isSuccess, result);
        break;
    }
    case AbstractCmd::CmdType_SetControllerWifiFrequencyBand: {
        CmdCommonValue *cmd = dynamic_cast<CmdCommonValue *>(absCmd);
        bool is24GHz = cmd->m_value.toBool();
        bool isSuccess = m_commInstance->setControllerWifiFrequncyBand(is24GHz);

        emit CommunicationEngine::instance()
            ->signal_setControllerWifiFrequencyBand_result(
                absCmd->m_object, isSuccess, is24GHz);
        break;
    }
    case AbstractCmd::CmdType_GetControllerWifiInfo: {
        InoCobotWifiInfo wifiInfo;
        bool isSuccess = m_commInstance->getControllerWifiInfo(wifiInfo);
        emit CommunicationEngine::instance()
            ->signal_getControllerWifiInfoResult(
                absCmd->m_object, isSuccess, wifiInfo);
        break;
    }
    case AbstractCmd::CmdType_EnableGripperThreePosition: {
        CmdCommonValue *cmd = static_cast<CmdCommonValue *>(absCmd);
        if (cmd) {
            bool isSuccess = m_commInstance->enableGripperThreePosition(cmd->m_value.toBool());
            emit CommunicationEngine::instance()
                ->signal_gripperThreePositionEnabled_result(
                    absCmd->m_object, isSuccess);
        }

        break;
    }
    case AbstractCmd::CmdType_GetSingleControllerRunModeStatus: {
        bool status = false;
        bool isSuccess = m_commInstance->getSingleControllerRunModeStatus(status);

        emit CommunicationEngine::instance()
            ->signal_handleSingleControllerRunMode_result(
                absCmd->m_object, absCmd->m_cmdType, isSuccess, status);
        break;
    }
    case AbstractCmd::CmdType_EnableSingleControllerRunMode: {
        CmdCommonValue *cmd = static_cast<CmdCommonValue *>(absCmd);
        if (cmd) {
            bool status = cmd->m_value.toBool();
            bool isSuccess = m_commInstance->setSingleControllerRunModeEnable(status);
            if (isSuccess) {
                isSuccess = m_commInstance->getSingleControllerRunModeEnable(status);

                emit CommunicationEngine::instance()
                    ->signal_handleSingleControllerRunMode_result(
                        absCmd->m_object, absCmd->m_cmdType, isSuccess, isSuccess ? status : !status);
            }
        }
        break;
    }
    case AbstractCmd::CmdType_GetBusSwitchEnableStatus: {
        bool ethernetipEnable = true;
        bool ethercatEnable = true;
        bool isSuccess = m_commInstance->getSwitchEnableStatus(ethernetipEnable, ethercatEnable);

        emit CommunicationEngine::instance()
            ->signal_getBusSwitchEnableStatus_result(
                absCmd->m_object, isSuccess, ethernetipEnable, ethercatEnable);
        break;
    }
    case AbstractCmd::CmdType_ReadBrakeState: {
        QVector<char> vecStates;

        char stateArray[6] = {1, 1, 1, 1, 1, 1};
        bool isOk = m_commInstance->readBrakeState(stateArray);
        if (isOk) {
            for (int i = 0; i < 6; i++) {
                vecStates.append(stateArray[i]);
            }
        }

        emit CommunicationEngine::instance()
            ->signal_handleReleaseBrake(absCmd->m_object, absCmd->m_cmdType,
                                        QVariant::fromValue(vecStates), isOk,
                                        QString());
        break;
    }
    case AbstractCmd::CmdType_ReleaseBrake: {
        bool isOk = true;
        QString sErrMsg;

        if (!m_commInstance->robotArm()) {
            isOk = false;
            sErrMsg = QObject::tr("Please connect to robot first.");
        }

        if (isOk) {
            MetaType::ElectricControlCabinetType type
                = m_commInstance->getElectricControlCabinetType();
            // 松抱闸功能仅支持驱控一体电柜
            isOk = (type == MetaType::ELECTRIC_CONTROL_CABINET_TYPE_UNIT
                    || type == MetaType::ELECTRIC_CONTROL_CABINET_TYPE_UROBOT);
            if (!isOk) {
                sErrMsg = QObject::tr("The current controller does not support brakes.");
            }
        }

        if (isOk) {
            bool isEnable = m_commInstance->IsEnable();
            if (isEnable) {
                sErrMsg = QObject::tr("Please set Enable off.");
                isOk = false;
            }
        }

        if (isOk) {
            bool isEmergency = m_commInstance->IsEmergency();
            if (!isEmergency) {
                sErrMsg = QObject::tr("Please turn on Emergency Stop.");
                isOk = false;
            }
        }

        if (isOk) {
            InoCoRobotBodyPowerState state = m_commInstance->getRobotBodyPowerState();
            if (ROBOT_BODY_POWERING_ON_IN_PROCESS == state) {
                sErrMsg = QObject::tr("Please wait for power on completely, and try again.");
                isOk = false;
            } else if (ROBOT_BODY_POWER_ON != state) {
                sErrMsg = QObject::tr("Please power on the robot first.");
                isOk = false;
            }
        }

        if (isOk) {
            CmdReleaseBrake *cmd = static_cast<CmdReleaseBrake *>(absCmd);
            if (cmd) {
                m_commInstance->releaseBrake(cmd->m_axisNo);

                isOk = false;
                int nReqRetryTimes = REQUEST_RETRY_TIMES;
                while (nReqRetryTimes--) {
                    char stateArray[6] = {1, 1, 1, 1, 1, 1};
                    bool ret = m_commInstance->readBrakeState(stateArray);
                    if (ret) {
                        if (0 == stateArray[cmd->m_axisNo - 1]) {
                            isOk = true;
                            nReqRetryTimes = 0;
                            break;
                        }
                    }

                    QThread::msleep(300);
                }

                if (!isOk) {
                    sErrMsg = QObject::tr("Failed to release brake. The release brake function is not available.");
                }
            } else {
                sErrMsg = QObject::tr("Failed to release brake. An error occurred while converting parameters.");
                isOk = false;
            }
        }

        emit CommunicationEngine::instance()
            ->signal_handleReleaseBrake(absCmd->m_object, absCmd->m_cmdType,
                                        QVariant(), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_CloseBrake: {
        bool isOk = true;
        QString sErrMsg;
        CmdReleaseBrake *cmd = nullptr;

        if (!m_commInstance->robotArm()) {
            isOk = false;
            sErrMsg = QObject::tr("Please connect to robot first.");
        }

        if (isOk) {
            MetaType::ElectricControlCabinetType type
                = m_commInstance->getElectricControlCabinetType();
            // 松抱闸功能仅支持驱控一体电柜
            isOk = (type == MetaType::ELECTRIC_CONTROL_CABINET_TYPE_UNIT
                    || type == MetaType::ELECTRIC_CONTROL_CABINET_TYPE_UROBOT);
            if (!isOk) {
                sErrMsg = QObject::tr("The current controller does not support closing brakes.");
            }
        }

        if (isOk) {
            cmd = static_cast<CmdReleaseBrake *>(absCmd);
            if (!cmd) {
                sErrMsg = QObject::tr("Failed to close brake. An error occurred while converting parameters.");
                isOk = false;
            }
        }

        if (isOk) {
            m_commInstance->closeBrake(cmd->m_axisNo);
        }

        emit CommunicationEngine::instance()
            ->signal_handleReleaseBrake(absCmd->m_object, absCmd->m_cmdType,
                                        QVariant(), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_ConnectController: {
        CmdConnectController *cmd
            = static_cast<CmdConnectController *>(absCmd);
        bool isSuccess
            = m_commInstance->connectController(cmd->m_ip, cmd->m_port);
        emit CommunicationEngine::instance()
            ->signal_connectControllerInterface_result(
                absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ConnectVirtualController: {
        m_commInstance->connectVirtualController(absCmd);
        break;
    }
    case AbstractCmd::CmdType_VritualControllerDeviceName: {
        m_commInstance->processVirtualControllerDeviceName(absCmd);
        break;
    }
    case AbstractCmd::CmdType_DisconnectController: {
        m_commInstance->setAvgLoadRateScheduler(false);
        m_commInstance->setElectricScheduler(false);
        m_commInstance->setModbusConnectScheduler(false);
        m_commInstance->setEthernetIPScheduler(false);
        m_commInstance->setEtherCatScheduler(false);

        bool isSuccess = m_commInstance->disconnectController();
        emit CommunicationEngine::instance()
            ->signal_disconnectControllerInterface_result(
                absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_EnableMechLock: {
        bool isSuccess = m_commInstance->enableMechLock(
            static_cast<CmdEnableMechLock *>(absCmd)->m_enableMechLock);
        emit CommunicationEngine::instance()
            ->signal_enableMechLockInterface_result(
                absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ClearAlarm: {
        bool isSuccess = m_commInstance->clearAlarm();
        emit CommunicationEngine::instance()
            ->signal_clearAlarmInterface_result(
                absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_EnableRobot: {
        bool isSuccess = m_commInstance->enableRobot(
            static_cast<CmdEnableRobot *>(absCmd)->m_enableRobot);
        emit CommunicationEngine::instance()
            ->signal_enableRobotInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_SetEmergency: {
        bool isSuccess = m_commInstance->SetEmergency(
            static_cast<CmdSetEmergency *>(absCmd)->m_bStatus);
        emit CommunicationEngine::instance()
            ->signal_setEmergecyInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_AxisMove: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        CmdAxisMove *cmd = static_cast<CmdAxisMove *>(absCmd);
        bool isSuccess = m_commInstance->axisMove(
            cmd->m_axisId, cmd->m_isPositive, cmd->m_isPressd);
        emit CommunicationEngine::instance()
            ->signal_axisMoveInterface_result(absCmd->m_object, isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ImportLocalProject:
        importLocalProject(absCmd);
        break;
    case AbstractCmd::CmdType_ExportProject:
        exportProject(absCmd);
        break;
    case AbstractCmd::CmdType_RenameProject:
        renameProject(absCmd);
        break;
    case AbstractCmd::CmdType_PutFilesToController:
        uploadFilesToController(absCmd);
        break;
    case AbstractCmd::CmdType_RemoveFilesFromController:
        deleteFilesFromController(absCmd);
        break;
    case AbstractCmd::CmdType_ProgramStart: {
        if (needDealTrajectoryRecovery()) {
            break;
        }

        bool isSuccess = m_commInstance->programStart();
        emit CommunicationEngine::instance()
            ->signal_handleProgram_result(absCmd->m_object, absCmd->m_cmdType,
                                          isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ProgramPause: {
        bool isSuccess = m_commInstance->programPause();
        emit CommunicationEngine::instance()
            ->signal_handleProgram_result(absCmd->m_object, absCmd->m_cmdType,
                                          isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ProgramContinue: {
        bool isSuccess = m_commInstance->programContinue();
        emit CommunicationEngine::instance()
            ->signal_handleProgram_result(absCmd->m_object, absCmd->m_cmdType,
                                          isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ProgramStop: {
        bool isSuccess = m_commInstance->programStop();
        emit CommunicationEngine::instance()
            ->signal_handleProgram_result(absCmd->m_object, absCmd->m_cmdType,
                                          isSuccess);
        break;
    }
    case AbstractCmd::CmdType_ProgramStep: {
        if (needDealTrajectoryRecovery()) {
            break;
        }

        bool isSuccess = m_commInstance->programStep();
        emit CommunicationEngine::instance()
            ->signal_handleProgram_result(absCmd->m_object, absCmd->m_cmdType,
                                          isSuccess);
        break;
    }
    case AbstractCmd::CmdType_SetActiveProject:
        setActiveProject(absCmd);
        break;
    case AbstractCmd::CmdType_RefreshProjectDatas:
    case AbstractCmd::CmdType_GetProjectList:
        getProjectList(absCmd);
        break;
    case AbstractCmd::CmdType_ReadProject:
        readProject(absCmd);
        break;
    case AbstractCmd::CmdType_ReadLocalProject:
        readLocalProject(absCmd);
        break;
    case AbstractCmd::CmdType_CreateLocalProject:
        createLocalProject(absCmd);
        break;
    case AbstractCmd::CmdType_CreateProject:
        createProject(absCmd);
        break;
    case AbstractCmd::CmdType_DeleteProject:
        deleteProject(absCmd);
        break;
    case AbstractCmd::CmdType_CopyProject:
        copyProject(absCmd);
        break;
    case AbstractCmd::CmdType_GenPasteProjectName:
        genPasteProjectName(absCmd);
        break;
    case AbstractCmd::CmdType_PasteProject:
        pasteProject(absCmd);
        break;
    case AbstractCmd::CmdType_GetDefaultProjectName:
        getDefaultProjectName(absCmd);
        break;
    case AbstractCmd::CmdType_SaveProject:
        saveProject(absCmd);
        break;
    case AbstractCmd::CmdType_SaveAsProject:
        saveAsProject(absCmd);
        break;
    case AbstractCmd::CmdType_GetProjectFileList:
        getProjectFileList(absCmd);
        break;
    case AbstractCmd::CmdType_ReloadActiveProject:
        reloadActiveProject(absCmd);
        break;
    case AbstractCmd::CmdType_GetDefaultRPointFileName:
        getDefaultRPointFileName(absCmd);
        break;
    case AbstractCmd::CmdType_GetRobotPointFileList:
        getRobotPointFileList(absCmd);
        break;
    case AbstractCmd::CmdType_GetJointPointFileList:
        getJointPointFileList(absCmd);
        break;
    case AbstractCmd::CmdType_SetCurJointPointFile:
        setCurJointPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_SetCurRobotPointFile:
        setCurRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_CreateRobotPointFile:
        createRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_DeleteRobotPointFile:
        deleteRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_CopyRobotPointFile:
        copyRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_GenPasteRPointFileName:
        genPasteRobotFileName(absCmd);
        break;
    case AbstractCmd::CmdType_PasteRobotPointFile:
        pasteRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_CheckRobotPointIsExist:
        checkRobotPointIsExist(absCmd);
        break;
    case AbstractCmd::CmdType_ReadRobotPoints:
        readRobotPoints(absCmd);
        break;
    case AbstractCmd::CmdType_AddRobotPoint:
        addRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_CopyRobotPoint:
        copyRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_PasteRobotPoint:
        pasteRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_DeleteRobotPoint:
        deleteRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_ChangeRobotPoint:
        changeRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_ChangeRobotPointPos:
        changeRobotPointPos(absCmd);
        break;
    case AbstractCmd::CmdType_ReplaceRobotPoint:
        replaceRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_RenameRobotPoint:
        renameRobotPoint(absCmd);
        break;
    case AbstractCmd::CmdType_ImportRobotPointFile:
        importRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_ExportRobotPointFile:
        exportRobotPointFile(absCmd);
        break;
    case AbstractCmd::CmdType_AddRobotPointByIndex:
        addRobotPointByIndex(absCmd);
        break;
    case AbstractCmd::CmdType_CheckJointPointIsExist:
        checkJointPointIsExist(absCmd);
        break;
    case AbstractCmd::CmdType_ReadJointPoints:
        readJointPoints(absCmd);
        break;
    case AbstractCmd::CmdType_AddJointPoint:
        addJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_CopyJointPoint:
        copyJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_PasteJointPoint:
        pasteJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_DeleteJointPoint:
        deleteJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_ChangeJointPoint:
        changeJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_ChangeJointPointPos:
        changeJointPointPos(absCmd);
        break;
    case AbstractCmd::CmdType_ReplaceJointPoint:
        replaceJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_RenameJointPoint:
        renameJointPoint(absCmd);
        break;
    case AbstractCmd::CmdType_AddJointPointByIndex:
        addJointPointByIndex(absCmd);
        break;
    case AbstractCmd::CmdType_GetUserDefineWarningFileList:
        getUserDefineWaringFileList(absCmd);
        break;
    case AbstractCmd::CmdType_GetUserDefineWarnings:
        getUserDefineWarnings(absCmd);
        break;
    case AbstractCmd::cmdType_ModifyUserDefineWarning:
        modifyUserDefineWarnig(absCmd);
        break;
    case AbstractCmd::CmdType_GetTaskList:
        getTaskList(absCmd);
        break;
    case AbstractCmd::CmdType_ActiveTask:
        activeTask(absCmd);
        break;
    case AbstractCmd::CmdType_TaskManage:
        manageTaskInfos(absCmd);
        break;
    case AbstractCmd::CmdType_Control_Move2Point_GetFileList: {
        QStringList fileList;
        std::vector<std::string> vecFiles = m_commInstance->getRPointFileList();
        for (const std::string &file : vecFiles) {
            fileList << QString::fromStdString(file);
        }

        vecFiles = m_commInstance->getJPointFileList();
        for (const std::string &file : vecFiles) {
            fileList << QString::fromStdString(file);
        }

        emit CommunicationEngine::instance()->signal_getPtFileList_result(absCmd->m_object, fileList);
        break;
    }
    case AbstractCmd::CmdType_Control_Move2Point_GetPtList: {
        auto [filename] = ((CmdDatas<QString> *)absCmd)->m_data;
        QVector<InoRPointInfo> vecRPointInfos;
        QVector<InoJPointInfo> vecJPointInfos;
        if (filename.compare("JP.pts") == 0) {
            vecJPointInfos = m_commInstance->readJPoints(filename.toStdString());
        } else {
            vecRPointInfos = m_commInstance->readRPoints(filename.toStdString());
        }
        emit CommunicationEngine::instance()
            ->signal_control_getPtList_result(absCmd->m_object, vecRPointInfos, vecJPointInfos);
        break;
    }
    case AbstractCmd::CmdType_Control_Move2Point_SetCurrent: {
        auto [type, rp, jp, filename]
            = ((CmdDatas<int, InoRPointInfo, InoJPointInfo, std::string> *)absCmd)->m_data;
        bool bRet = false;
        if (type == 0) {
            bRet = m_commInstance->changeRPoint(rp, filename);

            if (bRet) {
                bRet = m_commInstance->saveRPoints();
            }
        } else {
            bRet = m_commInstance->changeJPoint(jp, filename);

            if (bRet) {
                bRet = m_commInstance->saveJPoints();
            }
        }
        emit CommunicationEngine::instance()
            ->signal_control_setcurrent_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_InitTeachPadInfo: {
        initTeachPadInfo(absCmd);
        //解析机型参数
        // m_commInstance->comm()
        //     ->robotParam()
        //     ->getRobotParamRange()
        //     ->refreshParamRangeDataFromFile();

        m_commInstance->SetCurSpeed(m_commInstance->GetSpeed());
        // m_commInstance->setCurDragTeachStatus(m_commInstance->getDragTeachStatus());
        qDebug() << "******* posformat = " << m_commInstance->GetPosFormat();
        m_commInstance->SetCurPosFormat(m_commInstance->GetPosFormat());

        uint8_t strategy = 0;
        if (m_commInstance->readStartReleaseMode(strategy) == 0) {
            m_commInstance->setCurStartReleaseStrategy(strategy);
        }

        double params[16] = {0.0f};
        int iRet = m_commInstance->getRobotCompParam(params);
        qDebug() << "alpha = " << params[10] << "|beta" << params[11];
        if (iRet != 0) {
            break;
        }
        m_commInstance->setPostureAlphaBeta(params[10], params[11]);
    }
        break;
    case AbstractCmd::CmdType_UserLogin:
        userLogin(absCmd);
        break;
    case AbstractCmd::CmdType_SetCtlAuthority:
        setCtlAuthority(absCmd);
        break;
    case AbstractCmd::CmdType_GetLabelTypeList:
        getLabelTypeList(absCmd);
        break;
    case AbstractCmd::CmdType_GenInitIoItems:
        genInitIoItems(absCmd);
        break;
    case AbstractCmd::CmdType_GetIoItems:
        getIoItems(absCmd);
        break;
    case AbstractCmd::CmdType_GenInitAdDaItems:
        genInitAdDaItems(absCmd);
        break;
    case AbstractCmd::CmdType_GetAdDaItems:
        getAdDaItems(absCmd);
        break;
    case AbstractCmd::CmdType_GenInitOtherItems:
        genInitOtherItems(absCmd);
        break;
    case AbstractCmd::CmdType_GetOtherItems:
        getOtherItems(absCmd);
        break;
    case AbstractCmd::CmdType_ModifyIoItem:
        modifyIoItem(absCmd);
        break;
    case AbstractCmd::CmdType_ModifyAdDaItem:
        modifyAdDaItem(absCmd);
        break;
    case AbstractCmd::CmdType_ModifyOtherItem:
        modifyOtherItem(absCmd);
        break;
    case AbstractCmd::CmdType_UpdateToolIOItemDesc:
        updateToolIOItemDesc(absCmd);
        break;
    case AbstractCmd::CmdType_GetGlobalVar_B_EveryCol: {
 #if defined(INOCOBOTTP_MSVC_QT5)
        auto [address]
            = ((CmdDatas<QVector<QVector<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;

        if (m_commInstance->getGlobalVar_B_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_B_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_B_GetDatas_result(-1, index, different);
        }
#else
        auto [address]
            = ((CmdDatas<QList<QList<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;

        if (m_commInstance->getGlobalVar_B_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_B_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_B_GetDatas_result(-1, index, different);
        }
#endif
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_R_EveryCol: {
#if defined(INOCOBOTTP_MSVC_QT5)
        auto [address]
            = ((CmdDatas<QVector<QVector<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_R_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_R_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_R_GetDatas_result(-1, index, different);
        }
#else
        auto [address]
            = ((CmdDatas<QList<QList<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_R_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_R_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_R_GetDatas_result(-1, index, different);
        }
#endif
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_D_EveryCol: {
#if defined(INOCOBOTTP_MSVC_QT5)
        auto [address]
            = ((CmdDatas<QVector<QVector<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_D_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_D_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_D_GetDatas_result(-1, index, different);
        }
#else
        auto [address]
            = ((CmdDatas<QList<QList<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_D_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_D_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_D_GetDatas_result(-1, index, different);
        }
#endif
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_String_EveryCol: {
#if defined(INOCOBOTTP_MSVC_QT5)
        auto [address]
            = ((CmdDatas<QVector<QVector<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_String_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_String_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_String_GetDatas_result(
                    -1, index, different);
        }
#else
        auto [address]
            = ((CmdDatas<QList<QList<QVariant>> *> *)absCmd)->m_data;

        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_String_everyCol(data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                if (compareAndObtainDifferentDatas(
                        (*address)[i], data[i], index, different)) {
                    emit CommunicationEngine::instance()
                        ->signal_globalVar_String_GetDatas_result(
                            i, index, different);
                }
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_String_GetDatas_result(
                    -1, index, different);
        }
#endif
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_P_EveryColForCurrentShow: {
#if defined(INOCOBOTTP_MSVC_QT5)
        auto [currentRow, address]
            = ((CmdDatas<int, QVector<QVector<QVariant>> *> *)absCmd)->m_data;
#else
        auto [currentRow, address]
            = ((CmdDatas<int, QList<QList<QVariant>> *> *)absCmd)->m_data;
#endif
        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_P_everyColForCurrentShow(
                currentRow, data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                for (int j = 0; j < data[0].size(); ++j) {
                    int row = data[0][j].toInt();
                    if (data[i][j] != (*address)[i][row]) {
                        index.push_back(row);
                        different.push_back(data[i][j]);
                    }
                }
                emit CommunicationEngine::instance()
                    ->signal_globalVar_P_GetDatas_result(i, index, different);
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_P_GetDatas_result(-1, index, different);
        }
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_JP_EveryColForCurrentShow: {
#if defined(INOCOBOTTP_MSVC_QT5)
        auto [currentRow, address]
            = ((CmdDatas<int, QVector<QVector<QVariant>> *> *)absCmd)->m_data;
#else
        auto [currentRow, address]
            = ((CmdDatas<int, QList<QList<QVariant>> *> *)absCmd)->m_data;
#endif
        QVector<QVector<QVariant>> data;
        QVector<int> index;
        QVector<QVariant> different;
        if (m_commInstance->getGlobalVar_JP_everyColForCurrentShow(
                currentRow, data)) {
            for (int i = 1; i < data.size(); ++i) {
                index.clear();
                different.clear();
                for (int j = 0; j < data[0].size(); ++j) {
                    int row = data[0][j].toInt();
                    if (data[i][j] != (*address)[i][row]) {
                        index.push_back(row);
                        different.push_back(data[i][j]);
                    }
                }
                emit CommunicationEngine::instance()
                    ->signal_globalVar_JP_GetDatas_result(i, index, different);
            }
        } else {
            emit CommunicationEngine::instance()
                ->signal_globalVar_JP_GetDatas_result(-1, index, different);
        }
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_B_ValuesCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_B_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_B_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_R_ValuesCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_R_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_R_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_D_ValuesCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_D_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_D_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_B_FavorireCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_D_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_D_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_R_FavorireCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_D_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_D_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_D_FavorireCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_D_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_D_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_GetGlobalVar_String_ValuesCol: {
        auto [address] = ((CmdDatas<QList<QVariant> *> *)absCmd)->m_data;
        getListDatas("",
                     *address,
                     &Communication::getGlobalVar_String_valuesCol,
                     &CommunicationEngine::
                         signal_globalVar_String_GetOnlyValues_result);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_B_Values: {
        auto [row, data] = ((CmdDatas<int, unsigned char> *)absCmd)->m_data;
        m_commInstance->setGlobalVar_B_values(row, data);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_R_Values: {
        auto [row, data] = ((CmdDatas<int, int> *)absCmd)->m_data;
        m_commInstance->setGlobalVar_R_values(row, data);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_D_Values: {
        auto [row, data] = ((CmdDatas<int, double> *)absCmd)->m_data;
        m_commInstance->setGlobalVar_D_values(row, data);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_String_Values: {
        auto [row, data] = ((CmdDatas<int, QString> *)absCmd)->m_data;
        m_commInstance->setGlobalVar_String_values(row, data);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_B_Favorite: {
        auto [row, data] = ((CmdDatas<int, bool> *)absCmd)->m_data;
        if (!m_commInstance->setGlobalVar_B_favorite(row, data)) {
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(
                    tr("Failed to save favorites."));
        }
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_R_Favorite: {
        auto [row, data] = ((CmdDatas<int, bool> *)absCmd)->m_data;
        if (!m_commInstance->setGlobalVar_R_favorite(row, data)) {
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(
                    tr("Failed to save favorites."));
        }
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_D_Favorite: {
        auto [row, data] = ((CmdDatas<int, bool> *)absCmd)->m_data;
        if (!m_commInstance->setGlobalVar_D_favorite(row, data)) {
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(
                    tr("Failed to save favorites."));
        }
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_Scheduler_B: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setGlobalVarScheduler_B(state);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_Scheduler_R: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setGlobalVarScheduler_R(state);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_Scheduler_D: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setGlobalVarScheduler_D(state);
        break;
    }
    case AbstractCmd::CmdType_SetGlobalVar_Scheduler_String: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setGlobalVarScheduler_String(state);
        break;
    }
    // in
    case AbstractCmd::CmdType_Set_Input_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerInput(state);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_CommonIndex: {
        QList<unsigned short> data;
        if (m_commInstance->getCommonInputIndexs(data))
            emit CommunicationEngine::instance()
                ->signal_input_getCommIndex_result(absCmd->m_object, data);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_CommonIndex: {
        QList<unsigned short> data;
        if (m_commInstance->getCommonOutputIndexs(data))
            emit CommunicationEngine::instance()
                ->signal_input_getCommIndex_result(absCmd->m_object, data);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_CommonValues: {
        QList<quint8> data;
        if (m_commInstance->getCommonInputValues(data)) {
            QList<int> index;
            for (int i = 0; i < data.size(); ++i)
                index.push_back(i);
            emit CommunicationEngine::instance()
                ->signal_input_getCommValues_result(
                    absCmd->m_object, index, data);
        }
        break;
    }
    case AbstractCmd::CmdType_Get_Output_CommonValues: {
        QList<quint8> data;
        if (m_commInstance->getCommonOutputValues(data)) {
            QList<int> index;
            for (int i = 0; i < data.size(); ++i)
                index.push_back(i);
            emit CommunicationEngine::instance()
                ->signal_output_getCommValues_result(
                    absCmd->m_object, index, data);
        }
        break;
    }
    case AbstractCmd::CmdType_Get_Input_ControlAuthority: {
        m_commInstance->getInputControlAuthority(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_ControlAuthority: {
        m_commInstance->getOutputControlAuthority(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_ValuesStandard: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_StandardIO),
                     *address,
                     &Communication::getInputValuesStandard,
                     &CommunicationEngine::signal_input_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_ValuesTool: {
        m_commInstance->getInputValuesTool(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_ValuesFieldBus: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_FieldbusIO),
                     *address,
                     &Communication::getInputValuesFieldbus,
                     &CommunicationEngine::signal_input_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_ValuesMemory: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_MemoryIO),
                     *address,
                     &Communication::getInputValuesMemory,
                     &CommunicationEngine::signal_input_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_Input_LabelsAndRemark: {
        auto [type] = ((CmdDatas<int> *)absCmd)->m_data;
        m_commInstance->setInputShowType((ShowType)(type));

    #if defined(INOCOBOTTP_MSVC_QT5)
        QList<InoLabelItem> data;
        if (m_commInstance->getInputLabelAndRemarkForCurrentShow(data.toVector())) {
            emit CommunicationEngine::instance()
            ->signal_input_getLabelAndRemark_result(
                absCmd->m_object, type, data);
        }
    #else
        QVector<InoLabelItem> data;
        if (m_commInstance->getInputLabelAndRemarkForCurrentShow(data)) {
            emit CommunicationEngine::instance()
            ->signal_input_getLabelAndRemark_result(
                absCmd->m_object, type, data);
        }
    #endif

        break;
    }
    case AbstractCmd::CmdType_Set_Input_Values: {
        // auto [row,state] = ((CmdDatas<int, bool> *)absCmd)->m_data;
        // emit CommunicationEngine::instance()
        //     ->signal_input_saveDatas_result(
        //         );
        m_commInstance->writeInputStatusByBit(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Set_Input_ValuesForce: {
        // auto [row] = ((CmdDatas<int> *)absCmd)->m_data;
        // emit CommunicationEngine::instance()
        //     ->signal_input_saveDatas_result(
        //         m_commInstance->writeInputStatusForce(row));
        m_commInstance->writeInputStatusForce(absCmd);
        break;
    }
    // out
    case AbstractCmd::CmdType_Set_Output_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerOutput(state);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_ValuesStandard: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_StandardIO),
                     *address,
                     &Communication::getOutputValuesStandard,
                     &CommunicationEngine::signal_output_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_ValuesTool: {
        m_commInstance->getOutputValuesTool(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_ValuesFieldBus: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_FieldbusIO),
                     *address,
                     &Communication::getOutputValuesFieldbus,
                     &CommunicationEngine::signal_output_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_Output_LabelsAndRemark: {
        auto [type] = ((CmdDatas<int> *)absCmd)->m_data;
        m_commInstance->setOutputShowType((ShowType)type);
    #if defined(INOCOBOTTP_MSVC_QT5)
        QList<InoLabelItem> data;
        if (m_commInstance->getOutputLabelAndRemarkForCurrentShow(data.toVector())) {
            emit CommunicationEngine::instance()
            ->signal_output_getLabelAndRemark_result(
                absCmd->m_object, type, data);
        }
    #else
        QVector<InoLabelItem> data;
        if (m_commInstance->getOutputLabelAndRemarkForCurrentShow(data)) {
            emit CommunicationEngine::instance()
            ->signal_output_getLabelAndRemark_result(
                absCmd->m_object, type, data);
        }
    #endif


        break;
    }
    case AbstractCmd::CmdType_Get_Output_ValuesMemory: {
        auto [address] = ((CmdDatas<QList<quint8> *> *)absCmd)->m_data;
        getListDatas(QVariant(InoIOType_MemoryIO),
                     *address,
                     &Communication::getOutputValuesMemory,
                     &CommunicationEngine::signal_output_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Set_Output_Values: {
        m_commInstance->writeOutputStatusByBit(absCmd);
        break;
    }
    // AD
    case AbstractCmd::CmdType_Get_AD_Values: {
        auto [address]
            = ((CmdDatas<QList<Ino_AD_DA_Data> *> *)absCmd)->m_data;
        getListDatas(QVariant(),
                     *address,
                     &Communication::getDatasAD,
                     &CommunicationEngine::signal_AD_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Set_AD_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerAD(state);
        break;
    }
    // DA
    case AbstractCmd::CmdType_Get_DA_Values: {
        auto [address]
            = ((CmdDatas<QList<Ino_AD_DA_Data> *> *)absCmd)->m_data;
        getListDatas(QVariant(),
                     *address,
                     &Communication::getDatasDA,
                     &CommunicationEngine::signal_DA_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Set_DA_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerAD(state);
        break;
    }
    case AbstractCmd::CmdType_Set_DA_Values: {
        auto [data, index]
            = ((CmdDatas<Ino_AD_DA_Data, int> *)absCmd)->m_data;
        bool first = m_commInstance->setDataDA(index, 0, data);
        bool second = m_commInstance->setDataDA(index, 1, data);
        emit CommunicationEngine::instance()
            ->signal_DA_setDatas_result(first && second);
        break;
    }
    // SYSTEM IN
    case AbstractCmd::CmdType_Get_SystemIn_Values: {
        auto [address] = ((CmdDatas<QList<bool> *> *)absCmd)->m_data;
        getListDatas(QVariant(),
                     *address,
                     &Communication::getDatasSystemIn,
                     &CommunicationEngine::signal_SystemIn_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_SystemIn_Reamarks: {
        auto [address] = ((CmdDatas<QList<QString> *> *)absCmd)->m_data;

#if defined(INOCOBOTTP_MSVC_QT5)
        getListDatas(QVariant(),
                     *address,
                     &Communication::getSysInputRemarkList,
                     &CommunicationEngine::signal_SystemIn_getRemarks_result);
#else
        getListDatas(QVariant(),
                     *address,
                     &Communication::getSysInputRemark,
                     &CommunicationEngine::signal_SystemIn_getRemarks_result);
#endif
        break;
    }
    case AbstractCmd::CmdType_Set_SystemIn_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerSysInput(state);
        break;
    }
    // SYSTEM OUT
    case AbstractCmd::CmdType_Get_SystemOut_Values: {
        auto [address] = ((CmdDatas<QList<bool> *> *)absCmd)->m_data;
        getListDatas(QVariant(),
                     *address,
                     &Communication::getDatasSystemOut,
                     &CommunicationEngine::signal_SystemOut_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Get_SystemOut_Reamarks: {
        auto [address] = ((CmdDatas<QList<QString> *> *)absCmd)->m_data;
        #if defined(INOCOBOTTP_MSVC_QT5)
        getListDatas(QVariant(),
                     *address,
                     &Communication::getSysOutputRemarkList,
                     &CommunicationEngine::
                     signal_SystemOut_getRemarks_result);
        #else
        getListDatas(QVariant(),
                     *address,
                     &Communication::getSysOutputRemark,
                     &CommunicationEngine::
                     signal_SystemOut_getRemarks_result);
        #endif

        break;
    }
    case AbstractCmd::CmdType_Set_SystemOut_Schedule: {
        auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setSchedulerSysOutput(state);
        break;
    }
    case AbstractCmd::CmdType_Refresh_IOMapping_Values_FromController: {
        emit CommunicationEngine::instance()
            ->signal_IOMapping_cmd_result(
                absCmd->m_cmdType,
                m_commInstance->refreshFieldbusFromControllerDatas());
        break;
    }
    case AbstractCmd::CmdType_Get_IOMapping_Values: {
        auto [address]
            = ((CmdDatas<QList<Ino_FieldbusIOMapData> *> *)absCmd)->m_data;
        getListDatas(QVariant(),
                     *address,
                     &Communication::getFieldbusIOMapDatas,
                     &CommunicationEngine::signal_IOMapping_getDatas_result);
        break;
    }
    case AbstractCmd::CmdType_Reset_IOMapping_Values: {
        auto [method] = ((CmdDatas<Ino_IOMapResetMethod> *)absCmd)->m_data;
        emit CommunicationEngine::instance()
            ->signal_IOMapping_cmd_result(
                absCmd->m_cmdType, m_commInstance->resetFieldbusIOMap(method));
        break;
    }
    case AbstractCmd::CmdType_Save_IOMapping_Values: {
        auto [data]
            = ((CmdDatas<QVector<Ino_FieldbusIOMapData>> *)absCmd)->m_data;
        emit CommunicationEngine::instance()
            ->signal_IOMapping_cmd_result(
                absCmd->m_cmdType,
                m_commInstance->saveIOMappingData(data));
        break;
    }
    case AbstractCmd::CmdType_Save_IOMapping_Remarks: {
        m_commInstance->saveIOMappingRemarks(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Import_IOMapping_Files: {
        auto [filename] = ((CmdDatas<QString> *)absCmd)->m_data;
        emit CommunicationEngine::instance()
            ->signal_IOMapping_cmd_result(
                absCmd->m_cmdType,
                                          m_commInstance->importIOMappingFile(filename));
        break;
    }
    case AbstractCmd::CmdType_Export_IOMapping_Files: {
        auto [filename] = ((CmdDatas<QString> *)absCmd)->m_data;
        emit CommunicationEngine::instance()
            ->signal_IOMapping_cmd_result(
                absCmd->m_cmdType,
                m_commInstance->exportIOMappingFile(filename));
        break;
    }
    case AbstractCmd::CmdType_VirtualKeyBoard_InputNewSuffix: {
        processNewStr(absCmd);
        break;
    }
    case AbstractCmd::CmdType_VirtualKeyBoard_SuffixStringSoucrce: {
        setQStringListSource(absCmd);
        break;
    }
    case AbstractCmd::CmdType_VirtualKeyBoard_GetALlLabels: {
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ResetHisMaxCurrent: {
        int iRet = m_commInstance->resetHisMaxCurrent();
        emit CommunicationEngine::instance()
            ->signal_resetHisMaxCurrent_result(iRet);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadActCurrent: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readActCurrent(retArr);
        emit CommunicationEngine::instance()
            ->signal_readActCurrent_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadHisMaxCurrent: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readHisMaxCurrent(retArr);
        emit CommunicationEngine::instance()
            ->signal_readHisMaxCurrent_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadActLoadrate: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readActLoadrate(retArr);
        emit CommunicationEngine::instance()
            ->signal_readActLoadrate_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadOverHeat: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readOverHeat(retArr);
        emit CommunicationEngine::instance()
            ->signal_readOverHeat_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadActualOverLoad: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readActualOverLoad(retArr);
        emit CommunicationEngine::instance()
            ->signal_readActualOverLoad_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ReadMaxOverLoad: {
        std::vector<double> retArr(6, 0.0);
        int iRet = m_commInstance->readMaxOverLoad(retArr);
        emit CommunicationEngine::instance()
            ->signal_readMaxOverLoad_result(iRet, retArr);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_ResetMaxOverLoad: {
        int iRet = m_commInstance->resetMaxOverLoad();
        emit CommunicationEngine::instance()
            ->signal_resetMaxOverLoad_result(iRet);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_setElectricScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setElectricScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_setAvgLoadRateScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setAvgLoadRateScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_setOverLoadScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setOverLoadScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_WorkCond_setOverHeatScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setOverHeatScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_ReadTorqueLimit: {
        bool bCurrentSwitch = false;
        int retCurrentValue[ROBOT_AXIS_NUM] = {100, 100, 100, 100, 100, 100};
        int iRet = m_commInstance->ReadTorqueLimit(bCurrentSwitch,
                                                   retCurrentValue);
        QVector<int> vecRet;
        for (int i = 0; i < ROBOT_AXIS_NUM; ++i) {
            vecRet.push_back(retCurrentValue[i]);
        }
        emit CommunicationEngine::instance()
            ->signal_readTorqueLimit_result(iRet, bCurrentSwitch, vecRet);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_ReadAvrLoadLimit: {
        bool bLoadRateSwitch = false;
        int retLoadRatValue[ROBOT_AXIS_NUM] = {100, 100, 100, 100, 100, 100};
        int iRet = m_commInstance->ReadAvrLoadLimit(bLoadRateSwitch,
                                                    retLoadRatValue);
        QVector<int> vecRet;
        for (int i = 0; i < ROBOT_AXIS_NUM; ++i) {
            vecRet.push_back(retLoadRatValue[i]);
        }
        emit CommunicationEngine::instance()
            ->signal_readAvrLoadLimit_result(iRet, bLoadRateSwitch, vecRet);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_ReadOverHeatLimit: {
        bool bOverHeatSwitch = false;
        int iRet = m_commInstance->ReadOverHeatLimit(bOverHeatSwitch);
        emit CommunicationEngine::instance()
            ->signal_readOverHeatLimit_result(iRet, bOverHeatSwitch);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_ReadOverLoadLimit: {
        bool bOverLoadSwitch = false;
        int iRet = m_commInstance->ReadOverLoadLimit(bOverLoadSwitch);
        emit CommunicationEngine::instance()
            ->signal_readOverLoadLimit_result(iRet, bOverLoadSwitch);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_SaveTorqueLimit: {
        CmdSaveTorqueLimit *cmd = static_cast<CmdSaveTorqueLimit *>(absCmd);
        int iRet
            = m_commInstance->saveTorqueLimit(cmd->bSwitch, cmd->IntValue);
        emit CommunicationEngine::instance()
            ->signal_saveTorqueLimit_result(iRet);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_SaveAvrLoadLimit: {
        CmdSaveAvrLoadLimit *cmd = static_cast<CmdSaveAvrLoadLimit *>(absCmd);
        int iRet
            = m_commInstance->saveAvrLoadLimit(cmd->bSwitch, cmd->IntValue);
        emit CommunicationEngine::instance()
            ->signal_saveAvrLoadLimit_result(iRet);
        break;
    }
    case AbstractCmd::CmdType_AxisParams_SaveOverHeatAndLoadLimit: {
        CmdSaveOverHeatAndLoadLimit *cmd
            = static_cast<CmdSaveOverHeatAndLoadLimit *>(absCmd);
        int iRet = m_commInstance->saveOverHeatAndLoadLimit(
            cmd->bOverHeatSwitch, cmd->bOverLoadSwitch);
        emit CommunicationEngine::instance()
            ->signal_saveOverHeatAndLoadLimit_result(iRet);
        break;
    }
    case AbstractCmd::CmdType_InstallationPosture_Read: {
        double params[16] = {0.0f};
        int iRet = m_commInstance->getRobotCompParam(params);
        if (iRet != 0) {
            qDebug() << "alpha = " << params[10] << "|beta" << params[11];
            break;
        }
        emit CommunicationEngine::instance()
            ->signal_installationposture_read_result(absCmd->m_object, iRet == 0, params);
        break;
    }
    case AbstractCmd::CmdType_InstallationPosture_Write: {
        auto [params] = ((CmdDatas<double *> *)absCmd)->m_data;

        double retReadArgs[16] = {0.0f};
        int iRet = m_commInstance->getRobotCompParam(retReadArgs);
        if (iRet != 0) {
            LOG_INFO("write install posture read old params failed.");
            break;
        }

        retReadArgs[10] = params[10];
        retReadArgs[11] = params[11];

        iRet = m_commInstance->saveRobotCompensationParam(retReadArgs);
        if (iRet == 0) {
            emit CommunicationEngine::instance()
                ->signal_intallposture_changed(params[10], params[11]);
            m_commInstance->setPostureAlphaBeta(params[10], params[11]);
        }
        emit CommunicationEngine::instance()
            ->signal_installationposture_write_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SetModbusConnectScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setModbusConnectScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_SetEthernetIPConnectScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setEthernetIPScheduler(scheduler);
        break;
    }
    case AbstractCmd::CmdType_SetEthercatConnectScheduler: {
        auto [scheduler] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setEtherCatScheduler(scheduler);
        break;
    }
    // 心跳
    case AbstractCmd::CmdType_Connection_SetHeatBeat: {
        auto [bHearBeat] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->SetIsHeartbeat(bHearBeat);
        break;
    }
    // 运动
    case AbstractCmd::CmdType_MotionSetMoveStepGrade: {
        auto [grade] = ((CmdDatas<InoMoveStepGrade> *)absCmd)->m_data;
        bool bRet = m_commInstance->SetMoveStepGrade(grade);
        emit CommunicationEngine::instance()
            ->signal_setstepgrade_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_MotionGetMoveStepSizePara: {
        AbstractCmd *cmd = static_cast<AbstractCmd *>(absCmd);
        InoMoveStepSizePara params;
        bool bRet = m_commInstance->GetMoveStepSizePara(params);
        emit CommunicationEngine::instance()
            ->signal_getstepparams_result(cmd->m_object, bRet, params);
        break;
    }
    case AbstractCmd::CmdType_MotionSetMoveStepSizePara: {
        auto [params] = ((CmdDatas<InoMoveStepSizePara> *)absCmd)->m_data;
        bool bRet = m_commInstance->SetMoveStepSizePara(params);
        emit CommunicationEngine::instance()
            ->signal_setstepparams_result(absCmd->m_object, bRet);
        break;
    }
    // 功能安全
    case AbstractCmd::CmdType_CheckSafeParaPassword: {
        auto [passwd] = ((CmdDatas<unsigned int> *)absCmd)->m_data;
        int bRet = m_commInstance->CheckSafeParaPassword(passwd);
        emit CommunicationEngine::instance()
            ->signal_check_passwd(absCmd->m_object,
                                  AbstractCmd::CmdType_CheckSafeParaPassword,
                                  bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_CheckLastSafeParaPassword: {
        int bRet = m_commInstance->CheckSafeParaPassword();
        emit CommunicationEngine::instance()
            ->signal_check_passwd(
                absCmd->m_object,
                AbstractCmd::CmdType_CheckLastSafeParaPassword,
                bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_ReadSafetyParam2Model: {
        CmdSafetyReadParams *cmd
            = static_cast<CmdSafetyReadParams *>(absCmd);

        int iRet = m_commInstance->SafetyReadParams(
            cmd->key, cmd->offset, cmd->num);
        emit CommunicationEngine::instance()
            ->signal_safetyreadparams(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_ReadSafetyParam2GUI: {
        CmdGetSafeParaCommon *cmd
            = static_cast<CmdGetSafeParaCommon *>(absCmd);

        int iRet = m_commInstance->GetSafeParaCommon(cmd->key, cmd->offset,
                                                     cmd->len, cmd->buf,
                                                     cmd->forceFlag);
        emit CommunicationEngine::instance()
            ->signal_safetygetsafeparacomm(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_WriteSafetyParam2Model: {
        CmdSetSafeParaCommon *cmd
            = static_cast<CmdSetSafeParaCommon *>(absCmd);

        int iRet = m_commInstance->SetSafeParaCommon(cmd->key, cmd->offset,
                                                     cmd->len, cmd->buf,
                                                     cmd->forceFlag);
        emit CommunicationEngine::instance()
            ->signal_safetysetsafeparacomm(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_WriteSafetyParam2MCU: {
        CmdSafetyWriteParams *cmd
            = static_cast<CmdSafetyWriteParams *>(absCmd);

        int iRet = m_commInstance->SafetyWriteParams(
            cmd->key, cmd->offset, cmd->num);
        emit CommunicationEngine::instance()
            ->signal_safetywriteparams(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_ReadSafeParamsFromMcuDirect: {
        CmdReadSafeParamFromMcuDirect *cmd
            = static_cast<CmdReadSafeParamFromMcuDirect *>(absCmd);

        int iRet = m_commInstance->SafetyReadParams(cmd->key, cmd->offset,
                                                    cmd->num);
        if (iRet != 0) {
            emit CommunicationEngine::instance()
                ->signal_safety_readparamsfrommcudirect(
                    absCmd->m_object, false, cmd->key);
            break;
        }

        // 将模型层数据读取到GUI
        bool bRet = true;
        for (int i = 0; i < cmd->num; ++i) {
            iRet = m_commInstance->GetSafeParaCommon(
                cmd->key, cmd->offset + i,
                cmd->len, cmd->buf + cmd->len * i,
                cmd->forceFlag);
            bRet &= (iRet == 0);
        }

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_readparamsfrommcudirect(
                    absCmd->m_object, false, cmd->key);
            break;
        }

        emit CommunicationEngine::instance()
            ->signal_safety_readparamsfrommcudirect(
                absCmd->m_object, iRet    == 0, cmd->key);
        break;
    }
    case AbstractCmd::CmdType_WriteSafeParamsToMcuDirect: {
        CmdWriteSafeParamToMcuDirect *cmd
            = static_cast<CmdWriteSafeParamToMcuDirect *>(absCmd);

        bool bRet = true;
        for (int i = 0; i < cmd->num; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                cmd->key, cmd->offset + i,
                cmd->len, cmd->buf + cmd->len * i,
                cmd->forceFlag);

            bRet &= (iRet == 0);
        }

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_writeparamstomcudirect(
                    absCmd->m_object, false, cmd->key);
            break;
        }

        int iRet = m_commInstance->SafetyWriteParams(cmd->key, cmd->offset,
                                                     cmd->num);
        emit CommunicationEngine::instance()
            ->signal_safety_writeparamstomcudirect(
                absCmd->m_object, iRet == 0, cmd->key);
        break;
    }
    case AbstractCmd::CmdType_SafetyReset: {
        AbstractCmd *cmd = static_cast<AbstractCmd *>(absCmd);
        int iRet = m_commInstance->SafeParaReset();
        emit CommunicationEngine::instance()
            ->signal_safety_comm_result(cmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyCheckAStatus: {
        CmdSafetyCheckAStatus *cmd
            = static_cast<CmdSafetyCheckAStatus *>(absCmd);

        int iRet = m_commInstance->CheckAStatus(cmd->key, cmd->offset,
                                                cmd->num, cmd->status);
        emit CommunicationEngine::instance()
            ->signal_safetycheckattr(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyGetHardVer: {
        AbstractCmd *cmd = static_cast<AbstractCmd *>(absCmd);
        std::string system;
        std::string moni;
        std::string commu;
        int iRet = m_commInstance->GetSafeHardVer(system, moni, commu);
        emit CommunicationEngine::instance()
            ->signal_safety_hardver_result(cmd->m_object, iRet == 0,
                                           QString::fromStdString(system),
                                           QString::fromStdString(moni),
                                           QString::fromStdString(commu));
        break;
    }
    case AbstractCmd::CmdType_SafetyQuerySafeIORealTime: {
        auto [switchFlag] = ((CmdDatas<bool> *)absCmd)->m_data;
        int bRet = m_commInstance->QuerySafeIORealTime(switchFlag);
        emit CommunicationEngine::instance()
            ->signal_querysafeIOrealtime(
                absCmd->m_object, bRet == 0, switchFlag);
        break;
    }
    case AbstractCmd::CmdType_SafetyMultiWrite: {
        auto [params]
            = ((CmdDatas<QVector<SafeReadWriteCmdParam>> *)absCmd)->m_data;
        int bRet = m_commInstance->WriteParamsDirect2Mcu(params);
        emit CommunicationEngine::instance()
            ->signal_safety_multiwrite_result(absCmd->m_object, bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyMultiRead: {
        auto [params]
            = ((CmdDatas<QVector<SafeReadWriteCmdParam>> *)absCmd)->m_data;
        int bRet = m_commInstance->ReadParamsDirectFromMcu(params);
        emit CommunicationEngine::instance()
            ->signal_safety_multiread_result(absCmd->m_object, bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyReadSpeedReducing: {
        auto [config] = ((CmdDatas<SpeedReducingConf> *)absCmd)->m_data;
        int bRet = m_commInstance->ReadSpeedReducing(config);
        qDebug() << __FUNCTION__ << ", l1" << config.speedLevel1
                 << ", l2" << config.speedLevel2;
        emit CommunicationEngine::instance()
            ->signal_safety_readspeedreducing_result(
                absCmd->m_object, bRet == 0, config);
        break;
    }
    case AbstractCmd::CmdType_SafetyWriteSpeedReducing: {
        auto [config] = ((CmdDatas<SpeedReducingConf> *)absCmd)->m_data;
        int bRet = m_commInstance->WriteSpeedReducing(config);
        emit CommunicationEngine::instance()
            ->signal_safety_writespeedreducing_result(
                absCmd->m_object, bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySetInterZoneStatus: {
        auto [status] = ((CmdDatas<quint8> *)absCmd)->m_data;
        int bRet = m_commInstance->SetInterZoneSendStatus(status);
        emit CommunicationEngine::instance()
            ->signal_safety_setInterZoneStatus_result(
                absCmd->m_object, bRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyInterAreaTakePoint: {
        RoadPoint pt;
        int iRet = m_commInstance->readCurrPointPosOfInterAreaSetting(pt);
        emit CommunicationEngine::instance()
            ->signal_safety_interarea_takepoint_result(absCmd->m_object, iRet == 0, pt);
        break;
    }
    case AbstractCmd::CmdType_SafetyEndObjectTakePoint: {
        RoadPoint pt;
        int iRet = m_commInstance->readCurrPointPosOfToolObjSetting(pt);
        emit CommunicationEngine::instance()
            ->signal_safety_endobject_takepoint_result(absCmd->m_object, iRet == 0, pt);
        break;
    }
    case AbstractCmd::CmdType_SafetyExportConfig: {
        auto &[path] = ((CmdDatas<std::string> *)absCmd)->m_data;
        int iRet = m_commInstance->ExportFunctionSafeParaFile(path);
        emit CommunicationEngine::instance()
            ->signal_safety_exportconfig_result(
                absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetyImportConfig: {
        auto &[path] = ((CmdDatas<std::string> *)absCmd)->m_data;
        int iRet = m_commInstance->ImportFunctionSafeParaFile(path);
        emit CommunicationEngine::instance()
            ->signal_safety_importconfig_result(
                absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycIO: {
        auto [io, diTiggerLimit, stopconfigdata, bPowerOn] =
            ((CmdDatas<CobotSafeIO, unsigned int, CobotStopConfig, bool> *)absCmd)->m_data;

        bool bRet = true;
        // 将DI数据写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_DI, 0, sizeof(CobotIO) * COBOT_DI_NUM,
            (unsigned char *)&io.DI[0], false);

        bRet &= (iRet == 0);

        // 将DO数据写入模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_DO, 0, sizeof(CobotIO) * COBOT_DO_NUM,
            (unsigned char *)&io.DO[0], false);

        bRet &= (iRet == 0);

        // // 将DI触发阈值写入模型层
        // iRet = m_commInstance->SetSafeParaCommon(
        //     Cobot_EEP_SAFEIO_DITRIGGER, 0, sizeof(unsigned int),
        //     (unsigned char *)&diTiggerLimit, false);

        // bRet &= (iRet == 0);

        if (bPowerOn) {
            // 将停机配置写入模型层
            iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_STOPCONF, 0, sizeof(stCobotStopConfig),
                (unsigned char *)&stopconfigdata, false);

            bRet &= (iRet == 0);
        }

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncio_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        if (bPowerOn) {
            int keyArr[3]
                = {Cobot_EEP_DI, Cobot_EEP_DO, Cobot_EEP_STOPCONF};
            iRet = m_commInstance->SafetyWriteParams(keyArr, 3);
        } else {
            int keyArr[2]
                = {Cobot_EEP_DI, Cobot_EEP_DO};
            iRet = m_commInstance->SafetyWriteParams(keyArr, 2);
        }

        emit CommunicationEngine::instance()
            ->signal_safety_syncio_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycAxisSpeed: {
        auto [params, reducemodeParams] = ((CmdDatas<CobotSAxis, CobotReduceMode> *)absCmd)->m_data;

        bool bRet = true;
        // 将轴速度参数写入模型层
        for (int i = 0; i < COBOT_AVEL_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_AVEL_0, i, sizeof(CobotAVel),
                (unsigned char *)&params.AVelGroup[0] + sizeof(CobotAVel) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将缩减模式轴速度
        for (int i = 0; i < COBOT_AVEL_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_REDUCEMODE_AVEL_0, i, sizeof(CobotReduceModeAVel),
                (unsigned char *)&reducemodeParams.stReduceModeAvel[0] + sizeof(CobotReduceModeAVel) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_AVELWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8AVelWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncAxisSpeed_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[17]
            = {Cobot_EEP_AVEL_0, Cobot_EEP_AVEL_0 + 1, Cobot_EEP_AVEL_0 + 2,
               Cobot_EEP_AVEL_0 + 3, Cobot_EEP_AVEL_0 + 4, Cobot_EEP_AVEL_0 + 5,
               Cobot_EEP_AVEL_0 + 6, Cobot_EEP_AVEL_0 + 7,
               Cobot_EEP_REDUCEMODE_AVEL_0, Cobot_EEP_REDUCEMODE_AVEL_0 + 1,
               Cobot_EEP_REDUCEMODE_AVEL_0 + 2, Cobot_EEP_REDUCEMODE_AVEL_0 + 3,
               Cobot_EEP_REDUCEMODE_AVEL_0 + 4, Cobot_EEP_REDUCEMODE_AVEL_0 + 5,
               Cobot_EEP_REDUCEMODE_AVEL_0 + 6, Cobot_EEP_REDUCEMODE_AVEL_0 + 7,
               Cobot_EEP_AVELWAY};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 17);

        emit CommunicationEngine::instance()
            ->signal_safety_syncAxisSpeed_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycPositionDismatch: {
        auto [params] = ((CmdDatas<CobotPosDismatch> *)absCmd)->m_data;

        bool bRet = true;
        // 将轴速度参数写入模型层
        for (int i = 0; i < COBOT_POSDISMATCH_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_POSITIONDISMATCH_0, i, sizeof(CobotPosDismatchUnit),
                (unsigned char *)&params.stPosMatchGrop[0] + sizeof(CobotPosDismatchUnit) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_POSITIONDISMATCHWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8PdmActiveWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncPositionDismatch_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[9]
            = {Cobot_EEP_POSITIONDISMATCH_0, Cobot_EEP_POSITIONDISMATCH_0 + 1, Cobot_EEP_POSITIONDISMATCH_0 + 2,
               Cobot_EEP_POSITIONDISMATCH_0 + 3, Cobot_EEP_POSITIONDISMATCH_0 + 4, Cobot_EEP_POSITIONDISMATCH_0 + 5,
               Cobot_EEP_POSITIONDISMATCH_0 + 6, Cobot_EEP_POSITIONDISMATCH_0 + 7,
               Cobot_EEP_POSITIONDISMATCHWAY};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 9);

        emit CommunicationEngine::instance()
            ->signal_safety_syncPositionDismatch_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycSafetyStatic: {
        auto [params] = ((CmdDatas<CobotStaticMonitor> *)absCmd)->m_data;

        bool bRet = true;
        // 将轴速度参数写入模型层
        for (int i = 0; i < COBOT_STATIC_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_STATIC_0, i, sizeof(CobotStaticMonitorUnit),
                (unsigned char *)&params.stSafeBodyStaticGroup[0] + sizeof(CobotStaticMonitorUnit) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_STATICWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8ActiveWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncSafetyStatic_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[9]
            = {Cobot_EEP_STATIC_0, Cobot_EEP_STATIC_0 + 1, Cobot_EEP_STATIC_0 + 2,
               Cobot_EEP_STATIC_0 + 3, Cobot_EEP_STATIC_0 + 4, Cobot_EEP_STATIC_0 + 5,
               Cobot_EEP_STATIC_0 + 6, Cobot_EEP_STATIC_0 + 7, Cobot_EEP_STATICWAY};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 9);

        emit CommunicationEngine::instance()
            ->signal_safety_syncSafetyStatic_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycAxisTorque: {
        // auto [params] = ((CmdDatas<CobotJointTorque> *)absCmd)->m_data;

        // bool bRet = true;
        // // 将轴位置参数写入模型层
        // for (int i = 0; i < COBOT_ATORQUE_GROUP_NUM; ++i) {
        //     int iRet = m_commInstance->SetSafeParaCommon(
        //         Cobot_EEP_ATORQUE_0, i, sizeof(CobotAxisTorque),
        //         (unsigned char *)&params.stJtGroup[0] + sizeof(CobotAxisTorque) * i,
        //         false);

        //     bRet &= (iRet == 0);
        // }

        // // 将生效方式值写入模型层
        // int iRet = m_commInstance->SetSafeParaCommon(
        //     Cobot_EEP_ATORQUEWAY, 0, sizeof(quint8),
        //     (unsigned char *)&params.u8JTActiveWay, false);

        // bRet &= (iRet == 0);

        // if (!bRet) {
        //     emit CommunicationEngine::instance()
        //         ->signal_safety_syncAxisTorque_result(
        //             absCmd->m_object, false);
        //     break;
        // }

        // // 将多条模型层的数据写入到mcu
        // int keyArr[9]
        //     = {Cobot_EEP_ATORQUE_0, Cobot_EEP_ATORQUE_1, Cobot_EEP_ATORQUE_2,
        //        Cobot_EEP_ATORQUE_3, Cobot_EEP_ATORQUE_4, Cobot_EEP_ATORQUE_4 + 1,
        //        Cobot_EEP_ATORQUE_6, Cobot_EEP_ATORQUE_7, Cobot_EEP_ATORQUEWAY};
        // iRet = m_commInstance->SafetyWriteParams(keyArr, 9);

        // emit CommunicationEngine::instance()
        //     ->signal_safety_syncAxisTorque_result(
        //         absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycAxisPower: {
        // auto [params] = ((CmdDatas<CobotJointPower> *)absCmd)->m_data;

        // bool bRet = true;
        // // 将轴位置参数写入模型层
        // for (int i = 0; i < COBOT_APOWER_GROUP_NUM; ++i) {
        //     int iRet = m_commInstance->SetSafeParaCommon(
        //         Cobot_EEP_APOWER_0, i, sizeof(CobotAxisPower),
        //         (unsigned char *)&params.stJointPowerGrop[0] + sizeof(CobotAxisPower) * i,
        //         false);

        //     bRet &= (iRet == 0);
        // }

        // // 将生效方式值写入模型层
        // int iRet = m_commInstance->SetSafeParaCommon(
        //     Cobot_EEP_APOWERWAY, 0, sizeof(quint8),
        //     (unsigned char *)&params.u8JpActiveWay, false);

        // bRet &= (iRet == 0);

        // if (!bRet) {
        //     emit CommunicationEngine::instance()
        //         ->signal_safety_syncAxisPower_result(
        //             absCmd->m_object, false);
        //     break;
        // }

        // // 将多条模型层的数据写入到mcu
        // int keyArr[9]
        //     = {Cobot_EEP_APOWER_0, Cobot_EEP_APOWER_1, Cobot_EEP_APOWER_2,
        //        Cobot_EEP_APOWER_3, Cobot_EEP_APOWER_4, Cobot_EEP_APOWER_4 + 1,
        //        Cobot_EEP_APOWER_6, Cobot_EEP_APOWER_7, Cobot_EEP_APOWERWAY};
        // iRet = m_commInstance->SafetyWriteParams(keyArr, 9);

        // emit CommunicationEngine::instance()
        //     ->signal_safety_syncAxisPower_result(
        //         absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySnycAxisPosition: {
        auto [params, reduceParams] = ((CmdDatas<CobotSAxis, CobotReduceMode> *)absCmd)->m_data;

        bool bRet = true;
        // 将轴位置参数写入模型层
        for (int i = 0; i < COBOT_AVEL_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_APOS_0, i, sizeof(CobotAPos),
                (unsigned char *)&params.APosGroup[0] + sizeof(CobotAPos) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将轴位置缩减模式参数写入模型层
        for (int i = 0; i < COBOT_AVEL_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_REDUCEMODE_APOS_0, i, sizeof(CobotReduceModeAPos),
                (unsigned char *)&reduceParams.stReduceModeApos[0] + sizeof(CobotReduceModeAPos) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_APOSWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8APosWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncAxisPosition_result(
                    absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[17]
            = {Cobot_EEP_APOS_0, Cobot_EEP_APOS_1, Cobot_EEP_APOS_2,
               Cobot_EEP_APOS_3, Cobot_EEP_APOS_4, Cobot_EEP_APOS_4 + 1,
               Cobot_EEP_APOS_6, Cobot_EEP_APOS_7,
               Cobot_EEP_REDUCEMODE_APOS_0, Cobot_EEP_REDUCEMODE_APOS_0 + 1,
               Cobot_EEP_REDUCEMODE_APOS_0 + 2, Cobot_EEP_REDUCEMODE_APOS_0 + 3,
               Cobot_EEP_REDUCEMODE_APOS_0 + 4, Cobot_EEP_REDUCEMODE_APOS_0 + 5,
               Cobot_EEP_REDUCEMODE_APOS_0 + 6, Cobot_EEP_REDUCEMODE_APOS_0 + 7,
               Cobot_EEP_APOSWAY};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 17);

        emit CommunicationEngine::instance()
            ->signal_safety_syncAxisPosition_result(
                absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySyncCartesianPosition: {
        auto [params, vecZone, vecObject] = ((CmdDatas<CobotCcartesian, QVector<int>, QVector<int> > *)absCmd)->m_data;

        bool bRet = true;
        // 将干涉区概览信息写入模型层
        for (int i = 0; i < CO_IZONE_INTERFERZONESSTATUSLENGTH; ++i) {
            if (!vecZone.contains(i)) continue;
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_IZONE_STATUS_0, i, sizeof(CoInterZoneStatus),
                (unsigned char *)&params.CPosGroup.IZONES_STATUS[0]
                    + sizeof(CoInterZoneStatus) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将末端监测对象概览写入模型层
        for (int i = 0; i < CO_IZONE_INTERFERZONESSTATUSLENGTH; ++i) {
            if (!vecObject.contains(i)) continue;
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_ITOOL_STATUS_0, i, sizeof(CoInterZoneStatus),
                (unsigned char *)&params.CPosGroup.ITOOLS_STATUS[0]
                    + sizeof(CoInterZoneStatus) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将笛卡尔位置生效写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_CPOSWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8CPosWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncCartesianPosition_result(
                    absCmd->m_object, false);
            break;
        }

        QVector<int> vecIdxes;
        for (size_t i = 0; i < vecZone.size(); ++i) {
            iRet = m_commInstance->SafetyWriteParams(Cobot_EEP_IZONE_STATUS_0, vecZone[i], 1);
            bRet &= (iRet == 0);
        }
        for (size_t i = 0; i < vecObject.size(); ++i) {
            iRet = m_commInstance->SafetyWriteParams(Cobot_EEP_ITOOL_STATUS_0, vecObject[i], 1);
            bRet &= (iRet == 0);
        }
        vecIdxes.push_back(Cobot_EEP_CPOSWAY);
        iRet = m_commInstance->SafetyWriteParams(Cobot_EEP_CPOSWAY, 0, 1);
        bRet &= (iRet == 0);

        emit CommunicationEngine::instance()
            ->signal_safety_syncCartesianPosition_result(
                absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_SafetySyncZone: {
        auto [params]
            = ((CmdDatas<std::tuple<int, CoInterZone, CoInterZoneWObjParam,
                                    CoInterZoneStatus>> *)absCmd)
                  ->m_data;

        int index = std::get<0>(params);
        CoInterZone zone = std::get<1>(params);
        CoInterZoneWObjParam wobj = std::get<2>(params);
        CoInterZoneStatus cartesian = std::get<3>(params);

        bool bRet = true;
        // 将干涉区数据写入到模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_IZONE_PARA_0, index, sizeof(CoInterZone),
            (unsigned char *)&zone, false);

        bRet &= (iRet == 0);

        // 将工件数据写入到模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_IZONE_WOBJ_0, index, sizeof(CoInterZoneWObjParam),
            (unsigned char *)&wobj, false);

        bRet &= (iRet == 0);

        // 将干涉区概览信息写入到模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_IZONE_STATUS_0, index, sizeof(CoInterZoneStatus),
            (unsigned char *)&cartesian, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncZone_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[3]
            = {Cobot_EEP_IZONE_PARA_0 + index, Cobot_EEP_IZONE_WOBJ_0 + index,
               Cobot_EEP_IZONE_STATUS_0 + index};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 3);

        emit CommunicationEngine::instance()
            ->signal_safety_syncZone_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySyncObject: {
        auto [params, elbowSwitchParams, mtcpToolParams]
            = ((CmdDatas<std::tuple<int, CoInterTool, CoInterZoneStatus>, CobotElbowSwitch, CoInterZoneMTcpToolParam> *)
                   absCmd)
                  ->m_data;

        int index = std::get<0>(params);
        CoInterTool object = std::get<1>(params);
        CoInterZoneStatus cartesian = std::get<2>(params);

        qDebug() << "******** elbow = " << elbowSwitchParams.u8ElbowMonitor[index];

        LOG_INFO("********* mtcp value ********");
        for (int i = 0; i < CO_IZONE_MTCPTOOLPARAMSNUM * CO_IZONE_MTCP_UINTARRAYLENGTH; ++i) {
            LOG_INFO(QString("mtcp tool value : %1").arg(mtcpToolParams.InterTFramePos[i]));
        }

        bool bRet = true;
        // 将末端对象数据写入到模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_ITOOL_PARA_0, index, sizeof(CoInterTool),
            (unsigned char *)&object, false);

        bRet &= (iRet == 0);

        // 将末端对象概览信息写入到模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_ITOOL_STATUS_0, index, sizeof(CoInterZoneStatus),
            (unsigned char *)&cartesian, false);

        bRet &= (iRet == 0);

        // 将MTCP工具参数数据写入到模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_ITOOL_MTCPTOOL_0, index, sizeof(CoInterZoneMTcpToolParam),
            (unsigned char *)&mtcpToolParams, false);

        bRet &= (iRet == 0);

        // 将肘部检测参数写入模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_ELBOW_SWITCH, 0, sizeof(CobotElbowSwitch),
            (unsigned char *)&elbowSwitchParams, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncObject_result(absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[4] = {Cobot_EEP_ITOOL_PARA_0 + index,
                         Cobot_EEP_ITOOL_STATUS_0 + index,
                         Cobot_EEP_ITOOL_MTCPTOOL_0 + index,
                         Cobot_EEP_ELBOW_SWITCH};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 4);

        emit CommunicationEngine::instance()
            ->signal_safety_syncObject_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySyncCartesianSpeed: {
        auto [params, reduceParams] = ((CmdDatas<CobotCcartesian, CobotReduceModeCVel> *)absCmd)->m_data;

        // m_commInstance->WriteParamsDirect2Mcu()

        bool bRet = true;
        // 将笛卡尔速度限制写入模型层
        for (int i = 0; i < COBOT_IZONE_CVEL_ARRAY_LENGTH; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_CVEL_0, i, sizeof(CobotCVel),
                (unsigned char *)&params.CVelGroup[0] + sizeof(CobotCVel) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_CVELWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8CVelWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncCartesianSpeed_result(
                    absCmd->m_object, false);
            break;
        }

        // 将缩减模式值写入模型层
        iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_REDUCEMODE_CVEL, 0, sizeof(CobotReduceModeCVel),
            (unsigned char *)&reduceParams, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncCartesianSpeed_result(
                    absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[10]
            = {Cobot_EEP_CVEL_0, Cobot_EEP_CVEL_0 + 1, Cobot_EEP_CVEL_0 + 2,
               Cobot_EEP_CVEL_0 + 3, Cobot_EEP_CVEL_0 + 4, Cobot_EEP_CVEL_0 + 5,
               Cobot_EEP_CVEL_0 + 6, Cobot_EEP_CVEL_0 + 7, Cobot_EEP_CVELWAY,
               Cobot_EEP_REDUCEMODE_CVEL};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 10);

        emit CommunicationEngine::instance()
            ->signal_safety_syncCartesianSpeed_result(
                absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SafetySyncCartesianDirection: {
        auto [params] = ((CmdDatas<CobotTcpDirection> *)absCmd)->m_data;

        bool bRet = true;
        // 将笛卡尔速度限制写入模型层
        for (int i = 0; i < COBOT_TCP_DIRECT_GROUP_NUM; ++i) {
            int iRet = m_commInstance->SetSafeParaCommon(
                Cobot_EEP_TCPDIRECTION_0, i, sizeof(CobotTcpDirectionUnit),
                (unsigned char *)&params.stTcpDeGroup[0] + sizeof(CobotTcpDirectionUnit) * i,
                false);

            bRet &= (iRet == 0);
        }

        // 将生效方式值写入模型层
        int iRet = m_commInstance->SetSafeParaCommon(
            Cobot_EEP_TCPDIRECTIONWAY, 0, sizeof(quint8),
            (unsigned char *)&params.u8ActiveWay, false);

        bRet &= (iRet == 0);

        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_safety_syncCartesianDirection_result(
                    absCmd->m_object, false);
            break;
        }

        // 将多条模型层的数据写入到mcu
        int keyArr[9]
            = {Cobot_EEP_TCPDIRECTION_0, Cobot_EEP_TCPDIRECTION_0 + 1, Cobot_EEP_TCPDIRECTION_0 + 2,
               Cobot_EEP_TCPDIRECTION_0 + 3, Cobot_EEP_TCPDIRECTION_0 + 4, Cobot_EEP_TCPDIRECTION_0 + 5,
               Cobot_EEP_TCPDIRECTION_0 + 6, Cobot_EEP_TCPDIRECTION_0 + 7, Cobot_EEP_TCPDIRECTIONWAY};
        iRet = m_commInstance->SafetyWriteParams(keyArr, 9);

        emit CommunicationEngine::instance()
            ->signal_safety_syncCartesianDirection_result(
                absCmd->m_object, iRet == 0);
        break;
    }
    // 负载
    case AbstractCmd::CmdType_Load_Refresh: {
        CmdLoadRefresh *cmd = static_cast<CmdLoadRefresh *>(absCmd);

        LoadParams params;
        bool bRet = m_commInstance->LoadRefresh(cmd->m_loadId, params);
        emit CommunicationEngine::instance()
            ->signal_loadRefresh_result(absCmd->m_object, bRet, params);
        break;
    }
    case AbstractCmd::CmdType_Load_Clear: {
        CmdLoadClear *cmd = static_cast<CmdLoadClear *>(absCmd);

        bool bRet = m_commInstance->LoadClear(cmd->m_loadId);
        emit CommunicationEngine::instance()->signal_loadClear_result(bRet);
        break;
    }
    case AbstractCmd::CmdType_Load_Save: {
        CmdLoadSave *cmd = static_cast<CmdLoadSave *>(absCmd);

        bool bRet = m_commInstance->CheckCurLoadValid(cmd->m_params);
        if (!bRet) {
            emit CommunicationEngine::instance()
                ->signal_loadSave_result(cmd->m_object, false);
            break;
        }

        bRet = m_commInstance->LoadSave(cmd->m_loadId, cmd->m_params, cmd->m_bIsSaveNeed);
        emit CommunicationEngine::instance()->signal_loadSave_result(cmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_Load_GetNames: {
        QStringList sNames;
        quint16 nNumLoad = m_commInstance->GetLoadCount();
        for (int i = 0; i < nNumLoad; ++i) {
            #if defined(INOCOBOTTP_MSVC_QT5)
            sNames.push_back(m_commInstance->LoadIDNameSearch(i));
            #else
            sNames.emplace_back(m_commInstance->LoadIDNameSearch(i));
            #endif
        }
        emit CommunicationEngine::instance()
            ->signal_loadGetNames_result(sNames);
        break;
    }
    // 工具
    case AbstractCmd::CmdType_Tool_GetCurToolName: {
        QString sCurToolName
            = m_commInstance->ToolIdNameSearch(m_commInstance->GetToolId());
        emit CommunicationEngine::instance()
            ->signal_tool_GetCurToolName_result(sCurToolName);
        break;
    }
    case AbstractCmd::CmdType_Tool_GetItems: {
        QVector<QString> vecTools;
        m_commInstance->GetToolItem(vecTools);
        emit CommunicationEngine::instance()
            ->signal_tool_GetItems_result(vecTools);
        break;
    }
    case AbstractCmd::CmdType_Tool_Save: {
        CmdToolSave *cmd = static_cast<CmdToolSave *>(absCmd);

        ToolParams oldToolParam;
        Communication::instance()->GetCurToolParams(cmd->m_toolId, oldToolParam);

        bool bRet = Communication::instance()
                        ->Save(cmd->m_toolId, &cmd->m_params, cmd->m_bSaveNeed);
        if (bRet == true) {
            m_commInstance->comm()->SetCurToolParams(
                cmd->m_toolId, cmd->m_params);
        }
        emit CommunicationEngine::instance()->signal_tool_Save_result(
            cmd->m_object, bRet);
        if (m_commInstance->GetCurToolId() == cmd->m_toolId) {
            // 如果修改的是当前工具,需要通知3d刷新工具坐标
            emit CommunicationEngine::instance()->signal_ToolChanged(
                cmd->m_toolId);
        }

        if(!(oldToolParam == cmd->m_params)){
            emit CommunicationEngine::instance()->signal_toolParamChanged(cmd->m_toolId);
        }
        break;
    }
    case AbstractCmd::CmdType_Tool_Refresh: {
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        ToolParams toolParams;
        bool bRet = Communication::instance()
                        ->Refresh(cmd->m_value.toInt(), &toolParams);
        emit CommunicationEngine::instance()
            ->signal_tool_Refresh_result(cmd->m_object, bRet, toolParams);
        break;
    }
    case AbstractCmd::CmdType_Tool_Clear: {
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        bool bRet = Communication::instance()->Clear(cmd->m_value.toInt());
        emit CommunicationEngine::instance()->signal_tool_clear_result(bRet);
        break;
    }
    case AbstractCmd::CmdType_Tool_IdNameSearch: {
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        QString sRet = m_commInstance->ToolIdNameSearch(cmd->m_value.toInt());
        emit CommunicationEngine::instance()
            ->signal_tool_IdNameSearch_result(sRet);
        break;
    }
    case AbstractCmd::CmdType_Tool_HoldTypeCalibMethodSearch: {
        QVector<QString> vecMethods;
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        m_commInstance->HoldTypeCalibMethodSearch(
            static_cast<Robot_ToolType>(cmd->m_value.toInt()), vecMethods);
        emit CommunicationEngine::instance()
            ->signal_tool_HoldTypeCalibMethodSearch_result(vecMethods);
        break;
    }
    case AbstractCmd::CmdType_Tool_RefreshCalibratePoints: {
        CalibratePoints calPoints;
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        bool bRet = m_commInstance->RefreshCalibratePoints(
            cmd->m_value.toInt(), calPoints);
        emit CommunicationEngine::instance()
            ->signal_tool_RefreshCalibratePoints_result(bRet, calPoints);
        break;
    }
    case AbstractCmd::CmdType_Tool_CalibMethodNameSearch: {
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        QString curMethod = m_commInstance->CalibMethodNameSearch(
            static_cast<Robot_ToolCalibrateType>(cmd->m_value.toInt()));
        emit CommunicationEngine::instance()
            ->signal_tool_CalibMethodNameSearch_result(curMethod);
        break;
    }
    case AbstractCmd::CmdType_Tool_CalibMethodByName: {
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        int methodType = m_commInstance->CalibMethodByName(
            cmd->m_value.toString());
        emit CommunicationEngine::instance()
            ->signal_tool_CalibMethodByName_result(methodType);
        break;
    }
    case AbstractCmd::CmdType_Tool_CalibrateTipSearch: {
        auto [method] = ((CmdDatas<Robot_ToolCalibrateType> *)absCmd)->m_data;
        std::string sTips = m_commInstance->ToolCalibrateTipSearch(method);
        emit CommunicationEngine::instance()
            ->signal_tool_calibrate_tipsearch_result(absCmd->m_object, sTips.data());
        break;
    }
    case AbstractCmd::CmdType_Debugger_StartReleaseRead: {
        uint8_t mode;
        int iRet = m_commInstance->readStartReleaseMode(mode);
        emit CommunicationEngine::instance()
            ->signal_debugger_read_start_release_result(absCmd->m_object, iRet == 0, mode);
        break;
    }
    case AbstractCmd::CmdType_Debugger_StartReleaseWrite: {
        auto [mode] = ((CmdDatas<uint8_t> *)absCmd)->m_data;
        int iRet = m_commInstance->writeStartReleaseMode(mode);
        if (iRet == 0) {
            m_commInstance->setCurStartReleaseStrategy(mode);
        }
        emit CommunicationEngine::instance()
            ->signal_debugger_write_start_release_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_Tool_Calibrate: {
        Pos pos;
        Ori ori;
        CmdToolCalibrate *cmd = static_cast<CmdToolCalibrate *>(absCmd);
        cmd->m_calpts.MethodType
            = static_cast<int>(
                m_commInstance->CalibMethodByName(cmd->m_sCalibrateName));
        bool bRet = m_commInstance->Calibrate(cmd->m_calpts, pos, ori);
        emit CommunicationEngine::instance()
            ->signal_tool_Calibrate_result(bRet, pos, ori);
        break;
    }
    case AbstractCmd::CmdType_Tool_SaveCalibratePoints: {
        CmdToolSaveCalibratePoints *cmd
            = static_cast<CmdToolSaveCalibratePoints *>(absCmd);
        bool bRet = m_commInstance->SaveCalibratePoints(
            cmd->m_toolId, cmd->m_calpts);
        emit CommunicationEngine::instance()
            ->signal_tool_SaveCalibratePoints_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_Tool_ToolExcuteMoveTypeNameSearch: {
        QStringList sNames;
        for (int i = 0; i < 2; ++i) {
            QString sName = m_commInstance->ToolExcuteMoveTypeNameSearch(
                static_cast<Robot_MoveType>(i));
            sNames.push_back(sName);
        }
        emit CommunicationEngine::instance()
            ->signal_tool_ToolExcuteMoveTypeNameSearch_result(
                absCmd->m_object, sNames);
        break;
    }
    case AbstractCmd::CmdType_Tool_MoveToPoint: {
        emit CommunicationEngine::instance()->signal_contimotion();

        CmdToolMoveToPoint *cmd = static_cast<CmdToolMoveToPoint *>(absCmd);
        bool bRet = m_commInstance->MoveToPoint(
            cmd->m_calibrateType, cmd->m_pos, cmd->m_ori, cmd->m_moveType);
        emit CommunicationEngine::instance()
            ->signal_tool_MoveToPoint_result(bRet);
        break;
    }
    case AbstractCmd::CmdType_Tool_ToolPointsNameQuery: {
        QVector<QString> vecNames;
        CmdCommonToolCalibrate *cmd
            = static_cast<CmdCommonToolCalibrate *>(absCmd);
        m_commInstance->ToolPointsNameQuery(
            static_cast<Robot_ToolCalibrateType>(
                cmd->m_value.toInt()),
            vecNames);
        emit CommunicationEngine::instance()
            ->signal_tool_ToolPointsNameQuery_result(vecNames);
        break;
    }
    // 工件
    case AbstractCmd::CmdType_WObj_GetNames: {
        QStringList sNames;
        quint16 nWobj = m_commInstance->GetWObjCount();
        for (int i = 0; i < nWobj; ++i) {
            sNames.push_back(m_commInstance->WobjIdNameSearch(i));
        }
        emit CommunicationEngine::instance()
            ->signal_wobj_GetNames_result(sNames);
        break;
    }
    case AbstractCmd::CmdType_WObj_SaveWObjParams: {
        CmdWObjSave *cmd = static_cast<CmdWObjSave *>(absCmd);

        WobjParams oldWobJParam;
        Communication::instance()->GetCurWobjParams(cmd->m_wobjId, oldWobJParam);

        bool bRet = Communication::instance()->SaveWObjParams(
            cmd->m_wobjId, &cmd->m_params);
        if (bRet == true) {
            m_commInstance->comm()->SetCurWobjParams(
                cmd->m_wobjId, cmd->m_params);
        }
        emit CommunicationEngine::instance()->signal_wobj_Save_result(bRet);
        if (m_commInstance->GetCurWObjId() == cmd->m_wobjId) {
            // 如果修改的是当前工件需要通知3d模型刷新工件坐标
            emit CommunicationEngine::instance()->signal_WobjChanged(
                cmd->m_wobjId);
        }
        if(!(oldWobJParam == cmd->m_params)){
            emit CommunicationEngine::instance()->signal_wobjParamChanged(cmd->m_wobjId);
        }
        break;
    }
    case AbstractCmd::CmdType_WObj_RefreshWObjParams: {
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        WobjParams wobjParams;
        bool bRet = Communication::instance()
                        ->RefreshWObjParams(cmd->m_value.toInt(), &wobjParams);
        emit CommunicationEngine::instance()
            ->signal_wobj_Refresh_result(cmd->m_object, bRet, wobjParams);
        break;
    }
    case AbstractCmd::CmdType_WObj_ClearWobjParams: {
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        bool bRet = Communication::instance()
                        ->ClearWobjParams(cmd->m_value.toInt());
        emit CommunicationEngine::instance()->signal_wobj_clear_result(bRet);
        break;
    }
    case AbstractCmd::CmdType_WObj_WobjIdNameSearch: {
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        QString sRet = m_commInstance->WobjIdNameSearch(cmd->m_value.toInt());
        emit CommunicationEngine::instance()
            ->signal_wobj_WobjIdNameSearch_result(sRet);
        break;
    }
    case AbstractCmd::CmdType_WObj_HoldTypeUFrameCalibMethodSearch: {
        QVector<QString> vecMethods;
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        m_commInstance->HoldTypeUFrameCalibMethodSearch(
            static_cast<Robot_WObjType>(cmd->m_value.toInt()), vecMethods);
        emit CommunicationEngine::instance()
            ->signal_wobj_HoldTypeUFrameCalibMethodSearch_result(vecMethods);
        break;
    }
    case AbstractCmd::CmdType_WObj_HoldTypeOFrameCalibMethodSearch: {
        QVector<QString> vecMethods;
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        m_commInstance->HoldTypeOFrameCalibMethodSearch(
            static_cast<Robot_WObjType>(cmd->m_value.toInt()), vecMethods);
        emit CommunicationEngine::instance()
            ->signal_wobj_HoldTypeOFrameCalibMethodSearch_result(vecMethods);
        break;
    }
    case AbstractCmd::CmdType_WObj_RefreshWObjCalibratePoints: {
        CalibratePoints uFramePoints, oFramePoints;
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        bool bRet = m_commInstance->RefreshWObjCalibratePoints(
            cmd->m_value.toInt(), uFramePoints, oFramePoints);
        emit CommunicationEngine::instance()
            ->signal_wobj_RefreshWObjCalibratePoints_result(
                bRet, uFramePoints, oFramePoints);
        break;
    }
    case AbstractCmd::CmdType_WObj_CalibUFrameMethodNameSearch: {
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        QString curMethod = m_commInstance->CalibUFrameMethodNameSearch(
            static_cast<Robot_WObj_UFrame_CalMethod>(cmd->m_value.toInt()));
        emit CommunicationEngine::instance()
            ->signal_wobj_CalibUFrameMethodNameSearch_result(curMethod);
        break;
    }
    case AbstractCmd::CmdType_WObj_CalibOFrameMethodNameSearch: {
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        QString curMethod = m_commInstance->CalibOFrameMethodNameSearch(
            static_cast<Robot_WObj_OFrame_CalMethod>(cmd->m_value.toInt()));
        emit CommunicationEngine::instance()
            ->signal_wobj_CalibOFrameMethodNameSearch_result(curMethod);
        break;
    }
    case AbstractCmd::CmdType_WObj_WObjCalibrate: {
        CmdWObjCalibrate *cmd = static_cast<CmdWObjCalibrate *>(absCmd);
        WobjParams params;
        Communication::instance()->GetWobjParam(cmd->m_wobjId, params);

        Pos uFramepos, oFramepos;
        Ori uFrameori, oFrameori;
        bool bRet = m_commInstance->WObjCalibrate(
            params.UFMec, cmd->m_wobjType,
            params.UFFix,
            cmd->m_midUFramePos, cmd->m_midOFramePos,
            cmd->m_oldUFramePos, cmd->m_oldUFrameOri,
            uFramepos, uFrameori,
            oFramepos, oFrameori);
        emit CommunicationEngine::instance()
            ->signal_wobj_WObjCalibrate_result(bRet, uFramepos, uFrameori,
                                               oFramepos, oFrameori);
        break;
    }
    case AbstractCmd::CmdType_WObj_SaveWObjCalibratePoints: {
        CmdWObjSaveCalibratePoints *cmd
            = static_cast<CmdWObjSaveCalibratePoints *>(absCmd);
        bool bRet = m_commInstance->SaveWObjCalibratePoints(
            cmd->m_wobjId, cmd->m_uFramePoint, cmd->m_oFramePoint);
        emit CommunicationEngine::instance()
            ->signal_wobj_SaveWObjCalibratePoints_result(
                absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_WObj_WObjMoveToPoint: {
        emit CommunicationEngine::instance()->signal_contimotion();

        CmdWObjMoveToPoint *cmd = static_cast<CmdWObjMoveToPoint *>(absCmd);
        bool bRet = m_commInstance->WObjMoveToPoint(
            cmd->m_pos, cmd->m_ori, cmd->armPara, cmd->m_moveType, cmd->m_method);
        emit CommunicationEngine::instance()
            ->signal_wobj_WObjMoveToPoint_result(bRet);
        break;
    }
    case AbstractCmd::CmdType_WObj_WObjUFramePointsNameQuery: {
        QVector<QString> vecNames;
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        m_commInstance->WObjUFramePointsNameQuery(
            static_cast<Robot_WObj_UFrame_CalMethod>(
                cmd->m_value.toInt()),
            vecNames);
        emit CommunicationEngine::instance()
            ->signal_wobj_WObjUFramePointsNameQuery_result(vecNames);
        break;
    }
    case AbstractCmd::CmdType_WObj_WObjOFramePointsNameQuery: {
        QVector<QString> vecNames;
        CmdCommonWObjCalibrate *cmd
            = static_cast<CmdCommonWObjCalibrate *>(absCmd);
        m_commInstance->WObjOFramePointsNameQuery(
            static_cast<Robot_WObj_OFrame_CalMethod>(
                cmd->m_value.toInt()),
            vecNames);
        emit CommunicationEngine::instance()
            ->signal_wobj_WObjOFramePointsNameQuery_result(vecNames);
        break;
    }
    case AbstractCmd::CmdType_CrashDetect_Read: {
        CollisionProtectiontParams params;
        int iRet = Communication::instance()->readColProtectionParams(params);
        if (iRet != 0) {
            msleep(500);
            int iRet = Communication::instance()->readColProtectionParams(params);
        }
        emit CommunicationEngine::instance()
            ->signal_readColProtectionParams_result(absCmd->m_object, iRet == 0, params);
        break;
    }
    case AbstractCmd::CmdType_CrashDetect_Write: {
        auto [params] = ((CmdDatas<CollisionProtectiontParams> *)absCmd)->m_data;
        int iret = Communication::instance()->writeColProtectionParams(params);
        emit CommunicationEngine::instance()
            ->signal_writeColProtectionParams_result(absCmd->m_object, iret == 0);
        break;
    }
    case AbstractCmd::CmdType_CrashDetect_ReadRecommandValue: {
        qint16 level = 0;
        int iRet = Communication::instance()->readColProtectionRecommendLevel(level);
        emit CommunicationEngine::instance()
            ->signal_readColProtectionRecommendLevel_result(absCmd->m_object, iRet == 0, level);
        break;
    }
    case AbstractCmd::CmdType_CrashDetect_ResetRecommandValue: {
        int iRet = Communication::instance()->resetColProtectionRecommendLevel();

        if (iRet != 0) {
            emit CommunicationEngine::instance()
                ->signal_resetColProtectionRecommendLevel_result(absCmd->m_object, iRet == 0, 0);
            break;
        }

        qint16 level = 0;
        iRet = Communication::instance()->readColProtectionRecommendLevel(level);
        emit CommunicationEngine::instance()
            ->signal_resetColProtectionRecommendLevel_result(absCmd->m_object, iRet == 0, level);
        break;
    }
    // 示教面板
    case AbstractCmd::CmdType_Control_JointMoveZeroStart: {
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }

        emit CommunicationEngine::instance()->signal_contimotion();

        bool bRet = Communication::instance()->JointMoveToZeroStart();
        emit CommunicationEngine::instance()
            ->signal_jointmovezerostart_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_Control_JointMoveZeroEnd: {
        bool bRet = Communication::instance()->JointMoveToZeroStop();
        emit CommunicationEngine::instance()
            ->signal_jointmovezeroend_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_Control_SetToolId: {
        auto [toolId] = ((CmdDatas<int> *)absCmd)->m_data;
        bool bRet = Communication::instance()->SetToolId(toolId);
        emit CommunicationEngine::instance()
            ->signal_settool_result(absCmd->m_object, bRet, toolId);
        break;
    }
    case AbstractCmd::CmdType_Control_SetWObjId: {
        auto [wobjId] = ((CmdDatas<int> *)absCmd)->m_data;
        bool bRet = Communication::instance()->SetWobjId(wobjId);
        emit CommunicationEngine::instance()
            ->signal_setwobj_result(absCmd->m_object, bRet, wobjId);
        break;
    }
    case AbstractCmd::CmdType_Control_SetLoadId: {
        auto [loadId] = ((CmdDatas<int> *)absCmd)->m_data;
        bool bRet = Communication::instance()->SetLoadId(loadId);
        emit CommunicationEngine::instance()
            ->signal_setload_result(absCmd->m_object, bRet, loadId);
        break;
    }
    case AbstractCmd::CmdType_Control_SetCoordType: {
        auto [coordType] = ((CmdDatas<RobotCoordType> *)absCmd)->m_data;
        Communication::instance()->SetCurrentCoordType(coordType);
        break;
    }
    case AbstractCmd::CmdType_Control_SetPosFormat: {
        auto [posFormat]
            = ((CmdDatas<RobotCoordDisplayFormat> *)absCmd)->m_data;
        Communication::instance()->SetPosFormat(
            static_cast<RobotCoordDisplayFormat>(posFormat));
        break;
    }
    case AbstractCmd::CmdType_Control_DownloadFile: {
        auto [args]
            = ((CmdDatas<QPair<std::string, std::string>> *)absCmd)->m_data;

#ifndef INOCOBOTTP_MSVC_QT5
        qDebug() << "[CmdType_Control_DownloadFile]" << args.first << "," << args.second;
#endif
        bool bRet = m_commInstance->downloadFile(args.first, args.second);
        emit CommunicationEngine::instance()->signal_downloadfile_result(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_Control_SetSpeed: {
        auto [speed] = ((CmdDatas<int> *)absCmd)->m_data;
        bool bRet = Communication::instance()->SetSpeed(speed);
        emit CommunicationEngine::instance()->signal_setspeed_result(
            bRet, speed);
        break;
    }
    case AbstractCmd::CmdType_Control_SetDeviceMode: {
        auto [deviceMode]
            = ((CmdDatas<MetaType::RobotDeviceMode> *)absCmd)->m_data;
        int iRet = Communication::instance()->SetDeviceMode(deviceMode);
        emit CommunicationEngine::instance()
            ->signal_setdevicemode_result(iRet == 0, deviceMode);
        break;
    }
    case AbstractCmd::CmdType_Debugger_SetDebugMode: {
        auto [debugMode]
            = ((CmdDatas<MetaType::RobotDebugMode> *)absCmd)->m_data;
        Communication::instance()->SetDebugMode(debugMode);
        break;
    }
    case AbstractCmd::CmdType_Debugger_GetTrajRecvFlag: {
        TrajRecvFlag flag;
        int iRet = Communication::instance()->trajectoryRecoveryFlag(flag);
        emit CommunicationEngine::instance()->signal_debugger_getTrajRecvFlag(
            absCmd->m_object, iRet == 0, flag);
        break;
    }
    case AbstractCmd::CmdType_Debugger_SetTrajRecvExecMode: {
        auto [execMode]
            = ((CmdDatas<TrajRecvExecMode> *)absCmd)->m_data;
        int iRet = Communication::instance()->trajectoryRecoveryExcute(execMode);
        emit CommunicationEngine::instance()
            ->signal_debugger_setTrajRecvExecMode(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_TrajRecv_ReadParams: {
        CobotTrajRecoveryParam params;
        int iRet = Communication::instance()->ReadTrajRecoveryParam(params);
        emit CommunicationEngine::instance()
            ->signal_trajrecovery_readparams(absCmd->m_object, iRet == 0, params);
        break;
    }
    case AbstractCmd::CmdType_TrajRecv_WriteParams: {
        auto [params]
            = ((CmdDatas<CobotTrajRecoveryParam> *)absCmd)->m_data;
        int iRet = Communication::instance()->WriteTrajRecoveryParam(params);
        emit CommunicationEngine::instance()
            ->signal_trajrecovery_writeparams(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_KineInverseSolution: {
        CmdKineInverseSolution *cmd
            = static_cast<CmdKineInverseSolution *>(absCmd);
        int retCode = -1;
        double joint[6] = {0};
        bool bRet = m_commInstance->KineInverseSolution(
            cmd->toolId, cmd->wobjId, cmd->loadId, cmd->pos, cmd->armArgs,
            retCode, joint);
        QVector<double> vecJoint;
        for (int i = 0; i < 6; ++i) {
            vecJoint.push_back(joint[i]);
        }
        emit CommunicationEngine::instance()
            ->signal_KineInverseSolution_result(
                cmd->m_object, bRet, retCode, vecJoint);
        break;
    }
    case AbstractCmd::CmdType_ReadSystemUpgradeInfo: {
        CobotSystemUpdateInfo info;
        memset(&info, 0, sizeof(info));
        int iRet = m_commInstance->readSystemUpdateInfo(info);
        emit CommunicationEngine::instance()
            ->signal_readSystemUpgradeResult(
                absCmd->m_object, iRet == 0, info);
        break;
    }
    case AbstractCmd::CmdType_ReadEmgTrigMethod: {
        quint8 method = 0;
        int iRet = m_commInstance->readEmgTrigMethod(method);
        emit CommunicationEngine::instance()
            ->signal_readEmgTrigMethod_result(
                absCmd->m_object, iRet == 0, method);
        break;
    }
    case AbstractCmd::CmdType_SaveEmgTrigMethod: {
        auto [method] = ((CmdDatas<quint8> *)absCmd)->m_data;
        int iRet = m_commInstance->saveEmgTrigMethod(method);
        emit CommunicationEngine::instance()
            ->signal_saveEmgTrigMethod_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_SaveEmgStopMode: {
        auto [args] = ((CmdDatas<QPair<quint8, quint8>> *)absCmd)->m_data;
        int iRet = m_commInstance->saveEmgStopMode(args.first, args.second);
        emit CommunicationEngine::instance()
            ->signal_saveEmgStopMode_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_ReadEmgStopMode: {
        quint8 nMode = 0;
        quint8 nSecondMode = 0;
        int iRet = m_commInstance->readEmgStopMode(nMode, nSecondMode);
        emit CommunicationEngine::instance()
            ->signal_readEmgStopMode_result(
                absCmd->m_object, iRet == 0, nMode, nSecondMode);
        break;
    }
    case AbstractCmd::CmdType_ExecUpgrade: {
        auto [args] = ((CmdDatas<QPair<QString, bool> > *)absCmd)->m_data;

        QString fileSelected = args.first;
        bool bUpgradeBsp = args.second;

        const QString CTRL_UPGRADE_FOLDER = "/media/sdcard1/tmp_update/";
        std::string tempFolder = CTRL_UPGRADE_FOLDER.toStdString();
        if (m_commInstance->delDir(tempFolder.c_str()) != 0) {
            LOG_INFO(tr("exec upgrade delete dir failed, folder = %1.").arg(CTRL_UPGRADE_FOLDER));
            emit CommunicationEngine::instance()
                ->signal_execUpgradeResult(absCmd->m_object, false);
            break;
        }
        if (m_commInstance->createDir(tempFolder.c_str()) != 0) {
            LOG_INFO(tr("exec upgrade create dir failed, folder = %1.").arg(CTRL_UPGRADE_FOLDER));
            emit CommunicationEngine::instance()
                ->signal_execUpgradeResult(absCmd->m_object, false);
            break;
        }

        const QString CTRL_UPGRADE_FOLDER_FOR_FTP = "./tmp_update/";
        const QString UPGRADE_FILE_NAME = "update.zip";

        QString ip = Communication::instance()->getIP();
        QString ctrlPath = CTRL_UPGRADE_FOLDER_FOR_FTP + UPGRADE_FILE_NAME;

        QStringList srcFiles;
        srcFiles << fileSelected;
        QStringList destFiles;
        destFiles << ctrlPath;
        if (!m_commInstance->putFilesToController(srcFiles, destFiles)) {
            LOG_INFO(tr("exec upgrade transfer file to controller failed, srcFiles = %1, destFiles = %2.").arg(srcFiles[0], destFiles[0]));
            emit CommunicationEngine::instance()
                ->signal_execUpgradeResult(absCmd->m_object, false);
            break;
        }

        emit CommunicationEngine::instance()->signal_startUpdate();
        if (m_commInstance->systemUpgrade(bUpgradeBsp) != 0) {
            LOG_INFO(tr("exec upgrade do upgrade failed."));
            emit CommunicationEngine::instance()
                ->signal_execUpgradeResult(absCmd->m_object, false);
            break;
        }

        emit CommunicationEngine::instance()
            ->signal_execUpgradeResult(absCmd->m_object, true);
        break;
    }
    case AbstractCmd::CmdType_Communication_GetEthDatas: {
        m_commInstance->getEthConfig(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Communication_SetEthDatas: {
        auto [data] = ((CmdDatas<InoControllerEthCfg> *)absCmd)->m_data;
        if (m_commInstance->saveEthConfig(data) != 0)
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(
                    tr("Failed to save Ethernet configuration."));
        break;
    }
    case AbstractCmd::CmdType_CommunicationAdmin_ReadAllNetStatus: {
        auto [data]
            = ((CmdDatas<QList<InoCommonNetStatus> *> *)absCmd)->m_data;
        QList<InoCommonNetStatus> source;
        uchar state;
        ushort visionModel = 0, serverPort = 0;
        if (ERROR_OK == m_commInstance->readCommonNetStatusInfo(source, state)
            && ERROR_OK == m_commInstance->readVisionMode(
                   visionModel, serverPort)) {
            QList<InoCommonNetStatus> newData;
            QList<int> index;
            compareAndObtainDifferentDatas(*data, source, index, newData);
            emit CommunicationEngine::instance()
                ->signal_getNetStatus_result(absCmd->m_object,
                                             index, newData,
                                             state,
                                             visionModel, serverPort);
        }
        break;
    }
    case AbstractCmd::CmdType_Communication_SetOneNetStatus: {
        m_commInstance->writeEthCommonOperation(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Communication_ReadMode: {
        break;
    }
    case AbstractCmd::CmdType_Communication_SaveMode: {
        auto [data, port] = BIND(absCmd,uint,ushort);
        if (ERROR_OK != m_commInstance->saveVisionMode(data, port)) {
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(
                    tr("Failed to save network configuration."));
        } else {
        }
        break;
    }
    case AbstractCmd::CmdType_Communication_SetNewPort: {
        m_commInstance->saveNewPort(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetCurJPos: {
        auto [type] = ((CmdDatas<int> *)absCmd)->m_data;
        InoJPos pos;
        bool ret = m_commInstance->getCurrentJPoint(pos);
        emit CommunicationEngine::instance()
            ->signal_getCurPoint(absCmd->m_object, type, ret, pos);
        break;
    }
    case AbstractCmd::CmdType_GetAbsoluteZero: {
        QList<double> data;
        QList<int> min, max;
        if (m_commInstance->getAbsoluteZeroPoint(data, min, max)) {
            emit CommunicationEngine::instance()
                ->signal_getAbsoluteZero_result(
                    absCmd->m_object, data, min, max);
        } else {
            emit CommunicationEngine::instance()
                ->signal_needMainWidgetWarning(tr("Failed to get absolute zero parameters."));
        }
        break;
    }
    case AbstractCmd::CmdType_SetAbsoluteZero: {
        m_commInstance->setAbsoluteZeroPoint(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetAbsoluteZeroCurrentMotorValue: {
        m_commInstance->getAbsoluteZeroCurrentValue(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ResetAbsoluteZero:{
        m_commInstance->resetAbsoluteZeroPointByAxisNo(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetResetAbsoluteZeroResult:{
        m_commInstance->getResetAbsoluteZeroPointByAxisNo(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetWorkOriginData: {
        m_commInstance->getWorikOriginData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetWorkOrigin: {
        auto [index, data] = ((CmdDatas<int, InoJPos> *)absCmd)->m_data;
        m_commInstance->setWorikOriginPoint(index, data);
        break;
    }
    case AbstractCmd::CmdType_SetWorkOriginTriggerData: {
        m_commInstance->setWorikOriginPointTriggerData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetVersionInfo: {
        m_commInstance->getVersionInfo(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_ConrtollerTime: {
        m_commInstance->isNeedTimeSynToController();
        break;
    }
    case AbstractCmd::CmdType_Set_ConrtollerTime: {
        m_commInstance->setControllerTime(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetRobotBodyPowerState: {
        auto [state] = ((CmdDatas<InoCoRobotBodyPowerState> *)absCmd)->m_data;
        m_commInstance->setRobotBodyPowerState(state);
        break;
    }
    case AbstractCmd::CmdType_SetWarnInfoEnable: {
        auto [bEnable] = ((CmdDatas<bool> *)absCmd)->m_data;
        m_commInstance->setWarnMonitorEnable(bEnable);
        break;
    }
    case AbstractCmd::CmdType_DragTeach_AutoRecordPointResult: {
        auto [status] = ((CmdDatas<int> *)absCmd)->m_data;
        int iRet = m_commInstance->autoRecordPoint(status);
        emit CommunicationEngine::instance()
            ->singnal_dragteach_recordpointfeedback_result(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_Control_GetFirstBootStatus: {
        bool bStatus = false;
        int iRet = m_commInstance->getFirstBootStatus(bStatus);
        emit CommunicationEngine::instance()->signal_getfirstbootstatus_result(absCmd->m_object, iRet == 0, bStatus);
        break;
    }
    case AbstractCmd::CmdType_GetToolParam: {
        CmdGetParam *cmd = static_cast<CmdGetParam *>(absCmd);
        ToolParams tData;
        bool isSuccess = Communication::instance()->GetToolParam(
            cmd->targetNode, tData);
        emit CommunicationEngine::instance()
            ->signal_getToolParam_result(
                absCmd->m_object, isSuccess, cmd->targetNode, tData);
        break;
    }
    case AbstractCmd::CmdType_GetWobjParam: {
        CmdGetParam *cmd = static_cast<CmdGetParam *>(absCmd);
        WobjParams wData;
        bool isSuccess = Communication::instance()->GetWobjParam(
            cmd->targetNode, wData);
        emit CommunicationEngine::instance()
            ->signal_getWobjParam_result(
                absCmd->m_object, isSuccess, cmd->targetNode, wData);
        break;
    }
    case AbstractCmd::CmdType_UpdateLocalToolWobjParams: {
        for (int i = 0; i < 16; ++i) {
            ToolParams tParams;
            m_commInstance->GetToolParam(i, tParams);

            WobjParams wParams;
            m_commInstance->GetWobjParam(i, wParams);

            m_commInstance->SetCurToolParams(i, tParams);
            m_commInstance->SetCurWobjParams(i, wParams);
        }
        break;
    }
    case AbstractCmd::CmdType_ConnectSuccess: {
        MetaType::RobotDeviceMode dMode;
        m_commInstance->GetDeviceMode(dMode);
        m_commInstance->SetCurDeviceMode(dMode);
        qDebug() << "dmode = " << dMode;
        emit CommunicationEngine::instance()->signal_connectSuccess();
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_GetOpenStatus: {
        bool bRet = m_commInstance->getGeneralMatchOpen();
        emit CommunicationEngine::instance()
            ->signal_generalmatch_getopenstatus(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_SetOpenStatus: {
        auto [status] = ((CmdDatas<bool> *)absCmd)->m_data;
        bool ret = m_commInstance->setGeneralMatchOpen(status);
        emit CommunicationEngine::instance()
            ->signal_generalmatch_setopenstatus(absCmd->m_object, ret);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_readRobotParamMatchInfo: {
        std::string sRet;
        int ret = m_commInstance->readRobotParamMatchInfo(sRet);
        if (ret == 0) {
            parseGeneralMatchParam(sRet);
        }

        break;
    }
    case AbstractCmd::CmdType_GetDragTeach_Status: {
        bool bStatus = m_commInstance->getDragTeachStatus();
        m_commInstance->setCurDragTeachStatus(bStatus);
        emit CommunicationEngine::instance()
            ->signal_tragteach_status(bStatus);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_AllowTracing: {
        bool bRet = m_commInstance->allowTracingGeneralMatch();
        emit CommunicationEngine::instance()
            ->signal_generalmatch_allowtracing(absCmd->m_object, bRet);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_GetRecords: {
        if (!m_commInstance->allowTracingGeneralMatch()) {
            PRINT_MSG(tr("Not allowed to get universality record."));
            emit CommunicationEngine::instance()
                ->signal_generalmatch_getRecord(absCmd->m_object, false);
            break;
        }
        auto [filename] = ((CmdDatas<std::string> *)absCmd)->m_data;
        int iRet = m_commInstance->getGeneralMatchRecord(filename);
        emit CommunicationEngine::instance()
            ->signal_generalmatch_getRecord(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_GetInfo: {
        CobotGeneralMatchInfo info;
        bool bRet = m_commInstance->getGeneralMatchInfo(info);
        emit CommunicationEngine::instance()
            ->signal_generalmatch_getinfo(absCmd->m_object, bRet, info);
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_GetSyncStatus: {
        auto [direct] = ((CmdDatas<int> *)absCmd)->m_data;
        bool bRet = false;
        int count = 0;
        while (1) {
            if (count >= 90) break;
            CobotRobotParamSyncStatus info;
            bRet = m_commInstance->getRobotParamSyncStatus(info);

            if (!bRet) break;

            if (info.isValid && direct == 1 && (info.bodyStatus == 100 || info.bodyStatus == 255)) {
                bRet = true;
                break;
            }

            if (info.isValid && direct == 0 && (info.controllerStatus == 100 || info.controllerStatus == 255)) {
                bRet = true;
                break;
            }

            QThread::msleep(1000);
            ++count;
        }

        if (count >= 90) {
            emit CommunicationEngine::instance()
                ->signal_generalmatch_getparamsyncstatus(absCmd->m_object, bRet, true);
        } else {
            emit CommunicationEngine::instance()
                ->signal_generalmatch_getparamsyncstatus(absCmd->m_object, bRet, false);
        }
        break;
    }
    case AbstractCmd::CmdType_GeneralMatch_StartRobotParamSync: {
        auto [filename] = ((CmdDatas<std::string> *)absCmd)->m_data;
        int iRet = m_commInstance->startRobotParamSync(filename);
        emit CommunicationEngine::instance()
            ->signal_generalmatch_startparamsync(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_StartIdentity: {
        auto [arg] = ((CmdDatas<CobotLoadIdentifyData> *)absCmd)->m_data;
        int iRet = m_commInstance->startIdentify(arg);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_startIdentify(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_StopIdentity: {
        int iRet = m_commInstance->stopIdentify();
        emit CommunicationEngine::instance()
            ->signal_loadidentify_stopIdentify(absCmd->m_object, iRet == 0);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_ReadIdentifyData: {
        CobotLoadIdentifyData retValue;
        int iRet = m_commInstance->readIdentifyData(retValue);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_readIdentifyData(absCmd->m_object, iRet == 0, retValue);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_ReadIdentifyStatus: {
        CobotIdentifyStatus retValue;
        int iRet = m_commInstance->readIdentifyStatus(retValue);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_readIdentifyStatus(absCmd->m_object, iRet == 0, retValue);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_ReadIdentifyResult: {
        CobotLoadIdentifyResult retValue;
        int iRet = m_commInstance->readIdentifyResult(retValue);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_readIdentifyResult(absCmd->m_object, iRet == 0, retValue);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_GetIdentifyType: {
        CobotIdentifyType retValue = m_commInstance->getIdentifyType();
        emit CommunicationEngine::instance()
            ->signal_loadidentify_getIdentifyType(absCmd->m_object, retValue);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_SetIdentifyType: {
        auto [arg] = ((CmdDatas<CobotIdentifyType> *)absCmd)->m_data;
        m_commInstance->setIdentifyType(arg);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_ReadIdentifyTrajectoryFromRc: {
        QVector<QVector<float> > retValue;
        int iRet = m_commInstance->readIdentifyTrajectoryFromRc(retValue);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_readIdentifyTrajectoryFromRc(absCmd->m_object, iRet == 0, retValue);
        break;
    }
    case AbstractCmd::CmdType_LoadIdentity_ReadIdentifyRecommenPoint: {
        auto [pointIndex, recommendTraj, isOneTraj] = ((CmdDatas<int, CobotLoadIdentifyRecommendTraj, bool> *)absCmd)->m_data;
        QVector<QVector<float> > retValue;
        int iRet = m_commInstance->readIdentifyRecommenPoint(pointIndex, recommendTraj, retValue, isOneTraj);
        emit CommunicationEngine::instance()
            ->signal_loadidentify_readIdentifyRecommenPoint(absCmd->m_object, iRet == 0, retValue);
        break;
    }
    case AbstractCmd::CmdType_UpdateLocalSafetyMcuData: {
        bool bSafetyMcuExist = false;
        if (m_commInstance->QuerySafeParaCabinetProcess(false) == 0) {
            bSafetyMcuExist = (m_commInstance->QuerySafeParaCabinet() == 0);
            qDebug() << "safety mcu status = " << bSafetyMcuExist;
        } else {
            qDebug() << "safety mcu status query failed.";
        }
        m_commInstance->setSafetyMcuStatus(bSafetyMcuExist);
        break;
    }
    case AbstractCmd::CmdType_UpdateLocalPosData: {
        RoadPoint pt = m_commInstance->GetCurRoadPoint(true);
        m_commInstance->SetRealTimePt(pt);

        // pt = m_commInstance->GetCurRoadPoint(true);
        m_commInstance->SetRealTimeFlage2BasePt(pt);

        QMetaObject::invokeMethod(
            Communication::instance(), "signal_sendRealTimeRoadPoint",
            Qt::AutoConnection,
            Q_ARG(RoadPoint, pt));
        break;
    }
    case AbstractCmd::CmdType_GetLoadParam: {
        CmdGetParam *cmd = static_cast<CmdGetParam *>(absCmd);
        LoadParams lData;
        bool isSuccess = Communication::instance()->GetLoadParam(
            cmd->targetNode, lData);
        emit CommunicationEngine::instance()
            ->signal_getLoadParam_result(
                absCmd->m_object, isSuccess, cmd->targetNode, lData);
        break;
    }
    case AbstractCmd::CmdType_GetRobotBodyParameters: {
        m_commInstance->getRobotParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteRobotBodyParameters: {
        m_commInstance->setRobotParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetTeachParameters: {
        m_commInstance->getTeachParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteTeachParameters: {
        m_commInstance->setTeachParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetMotionParameters: {
        m_commInstance->getMotionParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteMotionParameters: {
        m_commInstance->setMotionParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadComState: {
        m_commInstance->readComState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteComState: {
        m_commInstance->writeComState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_StartDiagnose: {
        m_commInstance->startDiagnose(absCmd);
        break;
    }
    case AbstractCmd::CmdType_StopDiagnose: {
        m_commInstance->stopDiagnose(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadDiagnosePercent: {
        m_commInstance->readDiagnosePercent(absCmd);
        break;
    }
    case AbstractCmd::CmdType_StartExportDiagnoseReportToUSB: {
        m_commInstance->startExportReportToControllerUSB(absCmd);
        break;
    }
    case AbstractCmd::CmdType_StartExportDiagnoseReportToLocal: {
        m_commInstance->startExportReportToLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadErrExportStaToControllerUSB: {
        m_commInstance->readErrExportStaPercentToControllerUSB(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadErrExportStaToLocal:{
        m_commInstance->readErrExportStaPercentToLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetControlAuthority: {
        m_commInstance->getCurrentAuthority(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetControlAuthority: {
        m_commInstance->setCurrentAuthority(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetHistoryAlarm: {
        m_commInstance->getHistoryWarnList(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetRobotParamForSimulation: {
        m_commInstance->setRobotParamsForSimulation(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadRobotName: {
        m_commInstance->readRobotName(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ClearHistoryWarn: {
        m_commInstance->clearHistoryWarnInfo(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetToolIOConfig: {
        m_commInstance->readToolIOConfig(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetToolIOConfig: {
        m_commInstance->writeToolIOConfig(absCmd);
        break;
    }
    case AbstractCmd::CmdType_setToolIOConfigMonitorState: {
        m_commInstance->setToolIOConfigMonitorState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetRS485OrADModel: {
        m_commInstance->writeToolReuseModel(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetRS485Config: {
        m_commInstance->writeRs485Config(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetRS485Debugging: {
        m_commInstance->writeRs485Debugging(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadRS485Config: {
        m_commInstance->readRs485Config(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Get_Cobot_AD_DA_Values: {
        m_commInstance->getCobotDatasADDA(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Set_Cobot_AD_DA_Values: {
        m_commInstance->setCobotDatasADDA(absCmd);
        break;
    }
    case AbstractCmd::CmdType_CheckControllerUSBIsConnected: {
        QString sErrMsg;
        bool isOk = m_commInstance->checkControllerUSB();
        if (!isOk) {
            sErrMsg = tr("The controller USB device is not ready. Please check the device connection status.");
        }

        emit CommunicationEngine::instance()
            ->signal_handleSystemBackupAndLoad(
                absCmd->m_object, absCmd->m_cmdType,
                QVariant(), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_FormatMemoryCard: {
        QString sErrMsg;

        int flag = 0;
        bool isOk = m_commInstance->readFileSaveFlag(flag);
        if (!isOk || (flag >= 1 && flag <= 10)) {
            sErrMsg = tr("System busy, please try again later.");
        }

        if (isOk && flag == 2) {
            isOk = false;
            sErrMsg = tr("The memory card is being formatted, please do not repeat the operation.");
        }

        if (isOk) {
            isOk = m_commInstance->formatMemoryCard();
            if (!isOk) {
                sErrMsg = tr("System busy, please try again later.");
            }
        }

        emit CommunicationEngine::instance()
            ->signal_handleSystemBackupAndLoad(
                absCmd->m_object, absCmd->m_cmdType,
                QVariant(), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_ReadMemoryCardFormatState: {
        QString sErrMsg;
        int nState = 0;
        bool isOk = true;

        nState = 9;
        while (1) {
            int ret = m_commInstance->readMemoryCardFormatState(nState);
            if (ret == ERROR_OK) {
                if (1 == nState) {
                    QThread::msleep(500);
                    isOk = true;

                    emit CommunicationEngine::instance()
                        ->signal_handleSystemBackupAndLoad(
                            absCmd->m_object, absCmd->m_cmdType,
                            nState, isOk, sErrMsg);
                } else if (11 == nState) {
                    isOk = true;
                    break;
                } else {
                    isOk = false;
                    break;
                }
            } else {
                isOk = false;
                break;
            }
        }

        m_commInstance->endFormatMemoryCard();

        emit CommunicationEngine::instance()
            ->signal_handleSystemBackupAndLoad(
                absCmd->m_object, absCmd->m_cmdType, nState, isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_CheckPointFileIsExist: {
        CmdCommonValue *cmd = nullptr;
        QString sErrMsg;
        int ret = 0;
        QString sFilePath;
        bool isOk = true;

        cmd = static_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg
                = tr("Failed to check whether the point file exists due to parameter conversion error.");
            isOk = false;
        }

        if (isOk) {
            sFilePath = cmd->m_value.toString();
            QFileInfo fi(sFilePath);
            ret = m_commInstance->isFileNameRepeat(fi.fileName());
        }

        emit CommunicationEngine::instance()->signal_checkFileIsExist(
            absCmd->m_object, absCmd->m_cmdType, sFilePath, QVariant(ret));
        break;
    }
    case AbstractCmd::CmdType_LoadPointFile: {
        CmdCommonValue *cmd = nullptr;
        QString sErrMsg;
        bool isOk = true;

        cmd = static_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg
                = tr("Failed to load point file due to parameter conversion error.");
            isOk = false;
        }

        if (isOk) {
            QString sFilePath = cmd->m_value.toString();
            isOk = m_commInstance->loadPointFile(sFilePath);
            if (!isOk) {
                sErrMsg = tr("Failed to load point file.");
            }
        }

        emit CommunicationEngine::instance()
            ->signal_handleSystemBackupAndLoad(
                absCmd->m_object, absCmd->m_cmdType,
                QVariant(), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_DecideReplacePointFile: {
        CmdCommonValue *cmd = nullptr;
        QString sErrMsg;
        QString sFilePath;
        bool isOk = true;

        cmd = static_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg
                = tr("Failed to replace point file due to parameter conversion error.");
            isOk = false;
        }

        if (isOk) {
            sFilePath = cmd->m_value.toString();
            QFileInfo fi(sFilePath);
            isOk = m_commInstance->deletePointFile(fi.fileName());
            if (!isOk) {
                sErrMsg = tr("Failed to delete point file in controller.");
            }
        }

        if (isOk) {
            isOk = m_commInstance->loadPointFile(sFilePath);
            if (!isOk) {
                sErrMsg = tr("Failed to load point file.");
            }
        }

        emit CommunicationEngine::instance()
            ->signal_handleSystemBackupAndLoad(
                absCmd->m_object, absCmd->m_cmdType,
                QVariant(sFilePath), isOk, sErrMsg);
        break;
    }
    case AbstractCmd::CmdType_GetABZ_Data: {
        m_commInstance->getCobotABZData(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetFieldBusAddressAssignConfig: {
        m_commInstance->getAddressAssignMsg(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetFieldBusAddressAssignConfig: {
        m_commInstance->setAddressAssignMsg(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getProjectNoConfig: {
        m_commInstance->getProjectNoAssign(absCmd);
        break;
    }
    case AbstractCmd::CmdType_setProjectNoConfig: {
        m_commInstance->setProjectNoAssign(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getPointFileNoConfig: {
        m_commInstance->getPointFileNoAssign(absCmd);
        break;
    }
    case AbstractCmd::CmdType_setPointFileNoConfig: {
        m_commInstance->setPointFileNoAssign(absCmd);
        break;
    }
    case AbstractCmd::CmdType_startRestoreFactory: {
        m_commInstance->startRestoreFactory(absCmd);
        break;
    }
    case AbstractCmd::CmdType_readRestoreFactoryState: {
        m_commInstance->readRestoreFactoryState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_startConfigFilesBackupToUsb: {
        m_commInstance->startConfigFilesStateToUsb(absCmd);
        break;
    }
    case AbstractCmd::CmdType_readConfigFilesBackupStateToUsb: {
        m_commInstance->readConfigFilesBackupStateToUsb(absCmd);
        break;
    }
    case AbstractCmd::CmdType_startLoadConfigFilesFromUsb: {
        m_commInstance->startLoadConfigFilesFromUsb(absCmd);
        break;
    }
    case AbstractCmd::CmdType_readLoadConfigFilesSateFromUsb:{
        m_commInstance->readLoadConfigFilesStateFromUsb(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getDeviceConnectionState: {
        m_commInstance->getDeviceConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getMobusConnectionState: {
        m_commInstance->getModbusConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getEtherNetIpConnectionState: {
        m_commInstance->getEtherNetIpConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getEtherCatIpConnectionState: {
        m_commInstance->getEtherCatIpConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getMCConnectionState: {
        m_commInstance->getMCConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_getProfinetConnectionState: {
        m_commInstance->getProfinetConnectionState(absCmd);
        break;
    }
    case AbstractCmd::CmdType_BackupTeachPadConfigures: {
        if (!m_commInstance->isConnected()) {
            break;
        }

        CmdCommonValue *cmd = nullptr;
        QString sFilePath;
        QString fileName;
        QString sErrMsg;
        bool isOk = true;

        cmd = static_cast<CmdCommonValue *>(absCmd);
        if (!cmd) {
            sErrMsg = tr("Failed to upload teach pendant config file for parameter conversion error.");
            isOk = false;
        }

        if (isOk) {
            sFilePath = cmd->m_value.toString();
            fileName = FileUtils::getFileName(sFilePath);
            if (fileName.isEmpty()) {
                isOk = false;
                sErrMsg = tr("Failed to upload teach pendant config file for error getting file name.");
            }
        }

        if (isOk) {
            QString sDestFilePath = QString("%1/%2").arg(TeachPad_CONFIGURE_FILE_DIR, fileName);
            isOk = m_commInstance->putFilesToController(QStringList() << sFilePath, QStringList() << sDestFilePath);
            if (!isOk) {
                sErrMsg = tr("Failed to upload teach pendant config file.");
            }
        }

        if (isOk) {
            LOG_INFO("Success to upload teach pendant configure file.");
        } else {
            LOG_INFO(sErrMsg);
        }

        break;
    }
    case AbstractCmd::CmdType_ExportTeachPadConfigures: {
        CmdCommonValue *cmd = nullptr;
        QString sFilePath;
        QString sErrMsg;

        LOG_DEBUG(QString("[ExportTeachPadConfigures] Start processing export teach pendant configures command."));

        bool isOk = m_commInstance->isConnected();
        if (!isOk) {
            sErrMsg = tr("Failed to export teach pendant config file as the teach pendant is disconnect from controller.");
        }

        if (isOk) {
            cmd = static_cast<CmdCommonValue *>(absCmd);
            if (!cmd) {
                sErrMsg = tr("Failed to export teach pendant config file for parameter conversion error.");
                isOk = false;
            }
        }

        if (isOk) {
            sFilePath = cmd->m_value.toString();
            if (sFilePath.isEmpty()) {
                sErrMsg = tr("Failed to parse export path.");
                isOk = false;
            }
        }

        if (isOk) {
            std::vector<std::string> filePathList;
            isOk = m_commInstance->controllerFilePathList(
                QString(TeachPad_CONFIGURE_FILE_DIR).toStdString(), filePathList);

                LOG_DEBUG(QString("[ExportTeachPadConfigures] controllerFilePathList, dir = %1, isOk = %2, fileCount = %3")
                      .arg(TeachPad_CONFIGURE_FILE_DIR)
                      .arg(isOk)
                      .arg(filePathList.size()));
            if (!isOk) {
                sErrMsg = tr("Failed to get configure files in controller, please wait and try again.");
            } else {
                const QStringList configureFileList = m_commInstance->getTPConfigureFileNames();
                bool isExist = false;
                QVector<bool> retList;

                QString prefix = QString(TeachPad_CONFIGURE_FILE_DIR) + "/";
                if (m_commInstance->isConnectVirtualController()) {
                    prefix = QString::fromStdString(ProjectHelper::VirtualControllerSDCardFolder()) + "\\" + TeachPad_CONFIGURE_FILE_DIR + "\\";
                    prefix = prefix.replace("/", "\\");
                }

                for (const std::string &filePath : filePathList) {
                    QString fileName = QString::fromStdString(filePath).remove(prefix);
                    if (!configureFileList.contains(fileName)) {
                        continue;
                    }

                    isOk = m_commInstance->downloadFile(
                        QString(sFilePath + "/" + fileName).toStdString(), filePath);
                    retList << isOk;

                    isExist = true;
                }

                isOk = retList.contains(true);

                if (!isExist) {
                    sErrMsg = tr("There is no configure files, please restart application and try again.");
                }
            }
        }

        emit CommunicationEngine::instance()
            ->signal_exportTeachPadConfuguresResult(absCmd->m_object, isOk, sErrMsg);

        break;
    }
    case AbstractCmd::CmdType_ExportConfigFileToLocal:
    {
        m_commInstance->startExportConfigFileToLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ImportConfigFileFromLocal:
    {
        m_commInstance->startImportConfigFileFromLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadExportConfigFileStatusToLocal:{
        m_commInstance->readExportConfigFileOperateStatusToLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadImportConfigFileStatusFromLocal:{
        m_commInstance->readImportConfigFileOperateStatusFromLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetAllLogictreeItems:{
        getAllTreeItems(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteLogicTreeNode:{
        wirteLogicTreeNodes(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteLogicTreeLevel:{
        wirteLogicTreeLevel(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadLogicTreeLevel:{
        readLogicTreeLevel(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ReadLogicTreeNodes:{
        createLogicTreeNodesXmlCache(absCmd);
        break;
    }
    case AbstractCmd::CmdType_CreateLogicTreeNodes:{
        readLogicTreeNodes(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SortLogicTreeNodes:{
        sortLogicTreeNodes(absCmd);
        break;
    }
    case AbstractCmd::CmdType_CheckLogicTreeNode:{
        checkLogicTreeNodes(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ClearLogicTreeNodesWhenFalid:{
        clearLogicTreeNodesWhenReadXmlFalid(absCmd);
        break;
    }case AbstractCmd::CmdType_Set_ControllerLanguage:{
        m_commInstance->setControllerLanguage(absCmd);
        break;
    }
    case AbstractCmd::CmdType_Set_ModelLayerLanguage:{
        m_commInstance->setModelLayerLanguage(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ImportLanguagePackageForTPFromLocal:{
        m_commInstance->importLanguagePackageFromLocal(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ImportLanguagePackageForTPFromController:{
        m_commInstance->importLanguagePackageFromController(absCmd);
        break;
    }
    case AbstractCmd::CmdType_ImportLanguagePackageForControllerFromLocal:
    {
        m_commInstance->importLanguagePackageForController(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetCurPosBaseOnToolAndWobj:{
        auto [toolId, wobjId, type] = ((CmdDatas<int, int, QString> *)absCmd)->m_data;
        RoadPoint rp = m_commInstance->GetCurRoadPoint(toolId, wobjId, true);
        emit CommunicationEngine::instance()->signal_getCurPosBaseOnToolAndWobj(rp,type);
        break;
    }
    case AbstractCmd::CmdType_MoveJToPosBaseOnToolAndWobj:{
        auto [toolId, wobjId, pos] = ((CmdDatas<int, int, InoRobPos> *)absCmd)->m_data;
        if (!Communication::instance()->IsEnable()) {
            PRINT_MSG(tr("Please enable the robot first."));
            break;
        }
        bool isSuccess = m_commInstance->robotMoveJointInterface(pos, toolId, wobjId);
        break;
    }
    case AbstractCmd::CmdType_UpdateTempVariablesFile:{
        auto [projectName] = ((CmdDatas<QString> *)absCmd)->m_data;
        QString filePath = QString("%1/%2/Data/LuaVariables.jsn").arg(CONTROLLER_PROJECT_DIR_PATH)
                               .arg(projectName);
        std::string remotePath = "./TeachProgram/" + projectName.toStdString() + "/Data/LuaVariables.jsn";
        bool isLocalAddress = m_commInstance->isConnectVirtualController();
        if (isLocalAddress) {
            remotePath = ProjectHelper::VirtualControllerDataFolder(projectName.toStdString()) + "LuaVariables.jsn";
        }

        if (isLocalAddress) {
            if (FileExist(remotePath)) {
                FileDelete(remotePath);
            }
            if (!FileCopy(filePath.toStdString(), remotePath)) {
                qDebug() << "upload file error";
            }
        } else {
            UDF udf;
            if (!udf.uploadFile(remotePath, filePath.toStdString())) {
                qDebug() << "upload file error";
            }
        }
        break;
    }
    case AbstractCmd::CmdType_CalPalletItemBackGroundColor:{
        auto [tray, rects, items] = BIND(absCmd, QRectF, QList<QRectF>, QList<SimpleItem*>);
        int size = items.size();
        bool temp = true;
        for (int i = 0; i < size; ++i) {
            if (items[i]->data(PalletItemColumnType_IsSpecial).toBool())
                continue;
            temp = items[i]->data(PalletItemColumnType_IsPosValidFromOthers).toBool();
            QRectF rect = rects[i];
            if (rect.left() < tray.left()
                || rect.top() < tray.top()
                || rect.right() > tray.right()
                || rect.bottom() > tray.bottom()) {
                temp = false;
            }
            for (int j = i + 1; j < size; ++j) {
                if (items[i]->data(PalletItemColumnType_Index).toInt() < 0) {
                    continue;
                }
                QRectF rect2 = rects[j];;
                if (rect.intersects(rect2)) {
                    temp &= false;
                    items[j]->setData(PalletItemColumnType_IsPosValidFromOthers, false);
                }
            }
            if (temp) {
                if (!items[i]->data(PalletItemColumnType_IsPosValid).toBool()) {
                    items[i]->setData(PalletItemColumnType_IsPosValid, true);
                    items[i]->setData(PalletItemColumnType_Brush, QVariant::fromValue(QBrush(QColor(0, 255, 0))));
                }
            } else {
                if (items[i]->data(PalletItemColumnType_IsPosValid).toBool()) {
                    items[i]->setData(PalletItemColumnType_IsPosValid, false);
                    items[i]->setData(PalletItemColumnType_Brush, QVariant::fromValue(QBrush(QColor(255, 0, 0))));
                }
            }
        }
        emit CommunicationEngine::instance()->signal_calPalletBackgroundColorOver();
        break;
    }
    case AbstractCmd::CmdType_CreatePalletizingBoxes:{
        auto [uuid, isVisible] = ((CmdDatas<QString, bool> *)absCmd)->m_data;

        if(Instance::palletizingForm()){

            QMap<int, void *> map;
            LOG_INFO("start creat box");
    #ifdef INOCOBOTTP_MSVC_QT5
            typedef QMap<int, void*> IntVoidPtrMap;
            QMetaObject::invokeMethod(Instance::palletizingForm(),
                                      "createPalletizingBox",
                                      Qt::DirectConnection,
                                      Q_RETURN_ARG(IntVoidPtrMap, map),
                                      Q_ARG(QString, uuid),
                                      Q_ARG(bool, false));
    #else
            QMetaObject::invokeMethod(Instance::palletizingForm(),
                                      "createPalletizingBox",
                                      Qt::DirectConnection,
                                      Q_RETURN_ARG(, map),
                                      uuid,
                                      false);
    #endif

            LOG_INFO("end creta box");
            emit CommunicationEngine::instance()->signal_createPalletizingBoxes(uuid,map);
        }
        break;
    }
    case AbstractCmd::CmdType_OperateServoParamFile:{
        auto [operaType] = ((CmdDatas<QString> *)absCmd)->m_data;

        QString filePath = QString("%1/%2/MachineParams.json").arg(ABSOLUTE_SHARE_PATH).arg(ROBOTPARAMS_FILE_NAME);
        QString fileUIPath = QString("%1/%2/MachineParamsUI.json").arg(ABSOLUTE_SHARE_PATH).arg(ROBOTPARAMS_FILE_NAME);
        qDebug() << "CmdType_OperateServoParamFile" << filePath;
        UDF udf;
        if(operaType == "Get") {
            if(!udf.downloadFile("./RobotParams/MachineParams.json", filePath.toStdString())) {
                LOG_WARN("Download MachineParams.json file faile.");
                emit CommunicationEngine::instance()->signal_downloadServoFileStatus(0);
                return;
            }

            if(!udf.downloadFile("./RobotParams/MachineParamsUI.json", fileUIPath.toStdString())) {
                LOG_WARN("Download MachineParamsUI.json file faile.");
                emit CommunicationEngine::instance()->signal_downloadServoFileStatus(0);
                return;
            }
            emit CommunicationEngine::instance()->signal_downloadServoFileStatus(1);
        } else if(operaType == "Put") {
            if(!udf.uploadFile("./RobotParams/MachineParams.json", filePath.toStdString())) {
                LOG_WARN("Put MachineParams.json file faile.");
            }
        }
        break;
    }
    case AbstractCmd::CmdType_ChangedServoParamFile:{
        int ret = m_commInstance->RobotParamFileChange(1);
        emit CommunicationEngine::instance()->signal_changedServoParamFile(ret);
        break;
    }
    case AbstractCmd::CmdType_GetCurServoParamValue:{
        QByteArray json;
        int ret = m_commInstance->RobotParamServoCurrent(json);
        emit CommunicationEngine::instance()->signal_getServoParamsCurValue(ret, json);
        break;
    }
    case AbstractCmd::CmdType_StartServoParams:{
        auto [startJson] = ((CmdDatas<QByteArray> *)absCmd)->m_data;

        char *info = startJson.data();
        int ret = m_commInstance->RobotParamServoStart(info);
        emit CommunicationEngine::instance()->signal_startRobotServoParams(ret);
        break;
    }
    case AbstractCmd::CmdType_StopServoParams:{
        int ret = m_commInstance->RobotParamServoStop();
        emit CommunicationEngine::instance()->signal_stopRobotServoParams(ret);
        break;
    }
    case AbstractCmd::CmdType_ServoUpdateStatusRead:{
        QByteArray json;
        qDebug() << "CmdType_ServoUpdateStatusRead";
        int ret = m_commInstance->RobotParamUpdateStatusRead(json);
        emit CommunicationEngine::instance()->signal_readServoParamsStatus(ret, json);
        break;
    }
    case AbstractCmd::CmdType_GetSevenDragTeaching: {

    }
    case AbstractCmd::CmdType_SetSevenDragTeaching: {
        qDebug() << "AbstractCmd::CmdType_SetSevenDragTeaching";
        m_commInstance->setSevenDragTeaching(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetSevenTaketPoint: {
        m_commInstance->setSevenTakePoint(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetSevenRobotBodyParameters: {
        m_commInstance->getSevenRobotParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_WriteSevenRobotBodyParameters: {
        m_commInstance->setSevenRobotParams(absCmd);
        break;
    }
    case AbstractCmd::CmdType_GetLoadMotionStatus: {
        m_commInstance->getSevenLoadMotionStatus(absCmd);
        break;
    }
    case AbstractCmd::CmdType_SetLoadMotionStatus: {
        m_commInstance->setSevenLoadMotionStatus(absCmd);
        break;
    }

    case AbstractCmd::CmdType_UpdateGotoLabelFile:{
        auto [projectName] = ((CmdDatas<QString> *)absCmd)->m_data;
        QString filePath = QString("%1/%2/Data/GoLabels.jsn").arg(CONTROLLER_PROJECT_DIR_PATH)
                               .arg(projectName);
        std::string remotePath = "./TeachProgram/" + projectName.toStdString() + "/Data/GoLabels.jsn";
        bool isLocalAddress = m_commInstance->isConnectVirtualController();
        if (isLocalAddress) {
            remotePath = ProjectHelper::VirtualControllerDataFolder(projectName.toStdString()) + "GoLabels.jsn";
        }

        if (isLocalAddress) {
            if (FileExist(remotePath)) {
                FileDelete(remotePath);
            }
            if (!FileCopy(filePath.toStdString(), remotePath)) {
                LOG_INFO("upload goto file error");
            }
        } else {
            UDF udf;
            if (!udf.uploadFile(remotePath, filePath.toStdString())) {
                LOG_INFO("upload goto file error");
            }
        }
        break;
    }
    default:
        break;
    }
}

bool CommunicationThread::needDealTrajectoryRecovery()
{
    TrajRecvFlag flag;
    int iRet = m_commInstance->trajectoryRecoveryFlag(flag);
    if (iRet != 0) {
        return false;
    }

    if (flag == TrajRecvFlag_SETTED_OR_NEEDLESS) {
        return false;
    }

    TrajRecvExecMode mode = TrajRecvExecMode_EXCUTE;
    if (flag == TrajRecvFlag_IN_MOVELINE) {
        emit CommunicationEngine::instance()->signal_debugger_trajmsg();
        return true;
    } else if (flag == TrajRecvFlag_NOT_IN_MOVELINE) {
        mode = TrajRecvExecMode_GIVEUP;
        PRINT_MSG(tr("Trajectory recovery has been abandoned. The trajectory recovery will not be executed when Start or Step is clicked again."));
    } else if (flag == TrajRecvFlag_DSP_NOT_HAVE_MSG) {
        mode = TrajRecvExecMode_EXCUTE;
        PRINT_MSG(tr("The trajectory recovery will not be executed when Start or Step."));
    }

    m_commInstance->trajectoryRecoveryExcute(mode);

    return true;
}

void CommunicationThread::parseGeneralMatchParam(const std::string &sJsonText)
{
    QJsonDocument doc(QJsonDocument::fromJson(sJsonText.c_str()));
    QJsonObject rootObj = doc.object();
    QString sBodyRobotName = rootObj.value("BodyRobotName").toVariant().toString();
    QString sControllerRobotName = rootObj.value("ControllerRobotName").toVariant().toString();
    LOG_INFO(QString("[parseGeneralMatchParam]sBodyRobotName = %1, sControllerRobotName = %2")
                 .arg(sBodyRobotName, sControllerRobotName));
    m_commInstance->setBodyRobotName(sBodyRobotName);
    m_commInstance->setControllerRobotName(sControllerRobotName);
}
