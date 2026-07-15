#include "communicationengine.h"
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include "communication.h"
#include "messagebox.h"
#include "communicationthread.h"
#include "instance.h"
#include "cobotlog.h"
#include <QMetaType>
#include "metalogictree.h"
static CommunicationEngine *s_instance = 0;

CommunicationEngine *CommunicationEngine::instance()
{
    return s_instance;
}

CommunicationEngine::CommunicationEngine(int threadCountForLocalTask, int threadCountForCommunication, bool bFIFOKeep) :
    m_bFIFOKeep(bFIFOKeep), m_isQuit(false)
{
    qRegisterMetaType<AbstractCmd::CmdType>("AbstractCmd::CmdType");
    s_instance = this;
    Instance::setCommEngine(this);
    if (threadCountForLocalTask < 2)
        threadCountForLocalTask = 2;
    int all = threadCountForLocalTask + threadCountForCommunication;
    CommunicationThread *thread = nullptr;
    for (int i = 0; i < all; i++) {
        if (i < threadCountForCommunication) {
            thread = new CommunicationThread(CommunicationThread::Thread_Communication);
            m_listThreadsForCommunicationTask.push_back(thread);
        } else {
            thread = new CommunicationThread(CommunicationThread::Thread_LocalTask);
            m_listThreadsForLocalTask.push_back(thread);
        }
        thread->start();
        m_mapThreadToTaskCount[thread] = 0;
    }
    m_mutex = new QMutex;

    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_GetAllLogictreeItems);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_CheckLogicTreeNode);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_WriteLogicTreeNode);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_WriteLogicTreeLevel);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_operationLogicTreeLineNum);

    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_ReadLogicTreeLevel);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_ReadLogicTreeNodes);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_CreateLogicTreeNodes);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_SortLogicTreeNodes);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_ClearLogicTreeNodesWhenFalid);

    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_CalPalletItemBackGroundColor);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_LoadRobotModel);
    m_setLogictreeTaskType.insert(AbstractCmd::CmdType_LoadRobotModelSegment);
}

CommunicationEngine::~CommunicationEngine()
{
    delete m_mutex;
    QList<CommunicationThread *> threads;
    for (int i = 0; i < threads.size(); ++i) {
        delete threads[i];
    }
}

void CommunicationEngine::operateLogicTreeAsynTaskCount(bool isAdd, const QString &reason)
{
    LOG_INFO(QString("operateLogicTreeAsynTaskCount count=%1, add=%2, reason=%3").arg(m_logicTreeTaskTypeCount).arg(isAdd).arg(reason));
    m_logicTreeTaskTypeCount += (isAdd ? 1 : -1);//m_logicTreeTaskTypeFun
    if(isAdd){
        m_logicTreeTaskFun.push_back(reason);
    }else{
        int index = m_logicTreeTaskFun.indexOf(reason);
        if(index >= 0){
#if defined(INOCOBOTTP_MSVC_QT5)
            m_logicTreeTaskFun.erase(m_logicTreeTaskFun.begin() + index);
#else
            m_logicTreeTaskFun.erase(m_logicTreeTaskFun.cbegin() + index);
#endif
        }else{
            LOG_ERROR("Falta error, can't find reason for " + reason);
        }
    }
    emit signal_logicTreeAsynTaskCountChanged(m_logicTreeTaskTypeCount);
}

void CommunicationEngine::printLogicTreeTaskFun(){
    LOG_INFO(QString("LogicTreeTaskFun:%1").arg(m_logicTreeTaskFun.join(",")));
}

bool CommunicationEngine::logictreeAsynTaskIsInProcess()
{
    if (m_logicTreeTaskTypeCount != 0) {
        printLogicTreeTaskFun();
    }
    return m_logicTreeTaskTypeCount != 0;
}

QList<CommunicationThread *> CommunicationEngine::getCommunicationThreadPool() const
{
    return m_listThreadsForCommunicationTask;
}

QList<CommunicationThread *> CommunicationEngine::getLoacalTaskThreadPool() const
{
    return m_listThreadsForLocalTask;
}

void CommunicationEngine::stopThreadTool()
{
    m_isQuit = true;

    for (QMap<CommunicationThread *, qint32>::iterator p
         = m_mapThreadToTaskCount.begin();
         p != m_mapThreadToTaskCount.end(); p++)
        p.key()->stopThread();
}

void CommunicationEngine::taskFinish(
    CommunicationThread *thread, AbstractCmd *absCmd)
{
    m_mutex->lock();
    processTaskFinish(thread, absCmd);
    m_mutex->unlock();
}

// 必须在函数外加锁
void CommunicationEngine::processTaskFinish(CommunicationThread *thread, AbstractCmd *absCmd)
{
    if (!absCmd)
        return;
    QMap<QObject *, CommunicationThread *>* mapObjectToThread = nullptr;
    QMap<QObject *, qint32>* mapObjectToCount = nullptr;
    if(m_setLogictreeTaskType.contains(absCmd->m_cmdType)){
        mapObjectToThread = &m_mapMapObjectToLocalTaskThread;
        mapObjectToCount = &m_mapObjectToLocalTaskCount;
    }else{
        mapObjectToThread = &m_mapMapObjectToCommunicationThread;
        mapObjectToCount = &m_mapObjectToCommunicationTaskCount;
    }

    if (m_mapThreadToTaskCount.find(thread) != m_mapThreadToTaskCount.end())
        m_mapThreadToTaskCount[thread]--;

    if (m_bFIFOKeep && mapObjectToCount->find(absCmd->m_object) != mapObjectToCount->end()) {
        (*mapObjectToCount)[absCmd->m_object]--;
        if ((*mapObjectToCount)[absCmd->m_object] <= 0) {
            mapObjectToCount->remove(absCmd->m_object);
            mapObjectToThread->remove(absCmd->m_object);
        }
    }
    if (absCmd) {
        delete absCmd;
        absCmd = NULL;
    }
}

bool CommunicationEngine::appendCmdInfo(AbstractCmd *absCmd)
{
    bool appendSuccess = true;
    QMap<QObject *, CommunicationThread *>* mapObjectToThread = nullptr;
    QMap<QObject *, qint32>* mapObjectToCount = nullptr;
    if(m_setLogictreeTaskType.contains(absCmd->m_cmdType)){
        mapObjectToThread = &m_mapMapObjectToLocalTaskThread;
        mapObjectToCount = &m_mapObjectToLocalTaskCount;
    }else{
        mapObjectToThread = &m_mapMapObjectToCommunicationThread;
        mapObjectToCount = &m_mapObjectToCommunicationTaskCount;
    }
    CommunicationThread *idleThread = NULL;
    m_mutex->lock();
    // 对来自一个界面的数据使用相同的线程处理，
    // 以免发生多线程扰乱单个界面的数据通信的FIFO时序
    if (m_bFIFOKeep) {
        if (mapObjectToCount->find(absCmd->m_object)
            != mapObjectToCount->end()) {
            idleThread = (*mapObjectToThread)[absCmd->m_object];
            (*mapObjectToCount)[absCmd->m_object]++;
        } else {
            idleThread = getIdleThread(absCmd);
            if (idleThread) {
                (*mapObjectToCount)[absCmd->m_object] = 1;
                (*mapObjectToThread)[absCmd->m_object]= idleThread;
            }
        }
    } else {
        idleThread = getIdleThread(absCmd);
    }
    // qDebug()<<"idleThread is"<<idleThread<<absCmd->m_cmdType;
    if (NULL != idleThread) {
        // qDebug()<<"try to add new cmd,type is"<<absCmd;
        m_mapThreadToTaskCount[idleThread]++;
        AbstractCmd *cmd = idleThread->enqueueCmdInfo(absCmd);
        if (cmd != 0) {
            // qDebug()<<"need delete cmd,type is"<<absCmd->m_cmdType;
            processTaskFinish(idleThread, cmd);
            appendSuccess = false;
        }
        // qDebug() << "TaskCount : " << m_mapThreadToTaskCount[idleThread];
    } else {
        LOG_ERROR("idleThread == NULL, Failed! to append cmd");
        appendSuccess = false;
    }

    m_mutex->unlock();
    return appendSuccess;
}

CommunicationThread *CommunicationEngine::getIdleThread(AbstractCmd *cmd)
{
    CommunicationThread *idleThread = NULL;
    // find idle thread
    if (cmd->m_object && cmd->m_object->metaObject()->className() == QString("CommunicationThread"))
        return static_cast<CommunicationThread *>(cmd->m_object);

    QList<CommunicationThread *> *threadList = nullptr;
    if(m_setLogictreeTaskType.contains(cmd->m_cmdType)){
        threadList = &m_listThreadsForLocalTask;
    }else{
        threadList = &m_listThreadsForCommunicationTask;
    }
    qint32 nMinCost = 0x7fffffff;
    int size = threadList->size();
    for(int i=0; i<size; ++i){
        int count = m_mapThreadToTaskCount[(*threadList)[i]];
        if(count < nMinCost){
            nMinCost = count;
            idleThread = (*threadList)[i];
        }
    }
    return idleThread;
}

void CommunicationEngine::enqueueCmd(
    QObject *object, const AbstractCmd::CmdType &robotCommandType)
{
    if (!m_isQuit) {
        AbstractCmd *cmd = new AbstractCmd;
        cmd->m_object = object;
        cmd->m_cmdType = robotCommandType;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd(QObject *object, const int cmdType)
{
    if (!m_isQuit) {
        AbstractCmd *cmd = new AbstractCmd;
        cmd->m_object = object;
        cmd->m_cmdType = (AbstractCmd::CmdType)cmdType;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd(QObject *object, const AbstractCmd::CmdType &type,
                                     const QVariant &data)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_value = data;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveTeachStart(
    QObject *object,
    const TeachMode &teachMode,
    const bool &direction,
    const CoordParam &coordParam)
{
    if (!m_isQuit) {
        CmdTeachMoveControl *cmd
            = new CmdTeachMoveControl;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveTeachStart;
        cmd->m_teachMode = teachMode;
        cmd->m_direction = direction;
        cmd->m_coordParam = coordParam;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveTeachStop(
    QObject *object,
    const TeachMode &teachMode,
    const bool &direction,
    const CoordParam &coordParam)
{
    if (!m_isQuit) {
        CmdTeachMoveControl *cmd
            = new CmdTeachMoveControl;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveTeachStop;
        cmd->m_teachMode = teachMode;
        cmd->m_direction = direction;
        cmd->m_coordParam = coordParam;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveJointTeach(
    QObject *object, const RoadPoint &roadPoint)
{
    if (!m_isQuit) {
        CmdRobotMoveJoint *cmd = new CmdRobotMoveJoint;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveJointTeach;
        cmd->m_roadPoint = roadPoint;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveLine(QObject *object,
                                                   const RoadPoint &destPt)
{
    if (!m_isQuit) {
        CmdRobotMoveLine *cmd
            = new CmdRobotMoveLine;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveLineTeach;
        cmd->m_destPt = destPt;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveJoint(QObject *object,
                                                    const InoRobPos &iRobPos)
{
    if (!m_isQuit) {
        CmdRobotMoveJointWithRP *cmd
            = new CmdRobotMoveJointWithRP;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveJointWithRP;
        cmd->m_robPos = iRobPos;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_robotMoveRotateTeach(
    QObject *object, const CoordParam &coordParam,
    const TeachMode &teachMode,
    const double &rotateAngle)
{
    if (!m_isQuit) {
        CmdRobotMoveRotate *cmd
            = new CmdRobotMoveRotate;
        cmd->m_object = object;
        cmd->m_cmdType
            = AbstractCmd::CmdType_RobotMoveRotateTeach;
        // cmd->m_coordParam = coordParam;
        cmd->m_teachMode = teachMode;
        cmd->m_rotateAngle = rotateAngle;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ping(
    QObject *object, const QString &ip)
{
    if (!m_isQuit) {
        CmdPing *cmd = new CmdPing;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Ping;
        cmd->m_ip = ip;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_setControllerWifiPassword(
    QObject *object, const QString &sPassword)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_SetControllerWifiPassword;
        cmd->m_value = sPassword;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_setControllerWifiFrequencyBand(
    QObject *object, bool is24GHz)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_SetControllerWifiFrequencyBand;
        cmd->m_value = is24GHz;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_connectController(
    QObject *object, const QString &ip, const int &port)
{
    if (!m_isQuit) {
        CmdConnectController *cmd = new CmdConnectController;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_ConnectController;
        cmd->m_ip = ip;
        cmd->m_port = port;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_enableMechLock(
    QObject *object, const bool &enable)
{
    if (!m_isQuit) {
        CmdEnableMechLock *cmd = new CmdEnableMechLock;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_EnableMechLock;
        cmd->m_enableMechLock = enable;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_enableRobot(
    QObject *object, const bool &enable)
{
    if (!m_isQuit) {
        CmdEnableRobot *cmd = new CmdEnableRobot;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_EnableRobot;
        cmd->m_enableRobot = enable;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_setEmergecy(
    QObject *object, const bool &status)
{
    if (!m_isQuit) {
        CmdSetEmergency *cmd = new CmdSetEmergency;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_SetEmergency;
        cmd->m_bStatus = status;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_LoadSave(QObject *object, quint16 loadId, const LoadParams &params, bool bSaveNeed)
{
    if (!m_isQuit) {
        CmdLoadSave *cmd = new CmdLoadSave;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Load_Save;
        cmd->m_loadId = loadId;
        cmd->m_params = params;
        cmd->m_bIsSaveNeed = bSaveNeed;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_LoadClear(QObject *object, quint16 loadId)
{
    if (!m_isQuit) {
        CmdLoadClear *cmd = new CmdLoadClear;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Load_Clear;
        cmd->m_loadId = loadId;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_LoadRefresh(QObject *object, quint16 loadId)
{
    if (!m_isQuit) {
        CmdLoadRefresh *cmd = new CmdLoadRefresh;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Load_Refresh;
        cmd->m_loadId = loadId;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WriteSafetyParams(
    QObject *object, int key, int offset, int num)
{
    if (!m_isQuit) {
        CmdSafetyWriteParams *cmd = new CmdSafetyWriteParams;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->num = num;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteSafetyParam2MCU;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ReadSafetyParams(
    QObject *object, int key, int offset, int num)
{
    if (!m_isQuit) {
        CmdSafetyReadParams *cmd = new CmdSafetyReadParams;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->num = num;
        cmd->m_cmdType = AbstractCmd::CmdType_ReadSafetyParam2Model;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_GetSafeParaCommon(
    QObject *object, int key, int offset, int length, unsigned char *buf,
    bool forceFlag)
{
    if (!m_isQuit) {
        CmdGetSafeParaCommon *cmd = new CmdGetSafeParaCommon;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->len = length;
        cmd->buf = buf;
        cmd->forceFlag = forceFlag;
        cmd->m_cmdType = AbstractCmd::CmdType_ReadSafetyParam2GUI;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_SetSafeParaCommon(
    QObject *object, int key, int offset, int length, unsigned char *buf,
    bool forceFlag)
{
    if (!m_isQuit) {
        CmdSetSafeParaCommon *cmd = new CmdSetSafeParaCommon;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->len = length;
        cmd->buf = buf;
        cmd->forceFlag = forceFlag;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteSafetyParam2Model;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ReadSafetyParamsFromMcuDirect(
    QObject *object, int key, int offset, int num, int length, unsigned char *buf,
    bool forceFlag)
{
    if (!m_isQuit) {
        CmdReadSafeParamFromMcuDirect *cmd = new CmdReadSafeParamFromMcuDirect;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->len = length;
        cmd->buf = buf;
        cmd->num = num;
        cmd->forceFlag = forceFlag;
        cmd->m_cmdType = AbstractCmd::CmdType_ReadSafeParamsFromMcuDirect;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WriteSafetyParamsToMcuDirect(
    QObject *object, int key, int offset, int num, int length, unsigned char *buf,
    bool forceFlag)
{
    if (!m_isQuit) {
        CmdWriteSafeParamToMcuDirect *cmd = new CmdWriteSafeParamToMcuDirect;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->len = length;
        cmd->buf = buf;
        cmd->num = num;
        cmd->forceFlag = forceFlag;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteSafeParamsToMcuDirect;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_CheckAStatus(
    QObject *object, int key, int offset, int num, int status)
{
    if (!m_isQuit) {
        CmdSafetyCheckAStatus *cmd = new CmdSafetyCheckAStatus;
        cmd->m_object = object;
        cmd->key = key;
        cmd->offset = offset;
        cmd->num = num;
        cmd->status = status;
        cmd->m_cmdType = AbstractCmd::CmdType_SafetyCheckAStatus;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_handleToolCalibrate(
    QObject *object, const AbstractCmd::CmdType &type, const QVariant &value)
{
    if (!m_isQuit) {
        CmdCommonToolCalibrate *cmd = new CmdCommonToolCalibrate;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_value = value;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ToolSave(QObject *object, quint16 toolId,
                                              const ToolParams &params, bool bSaveNeed)
{
    if (!m_isQuit) {
        CmdToolSave *cmd = new CmdToolSave;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Tool_Save;
        cmd->m_toolId = toolId;
        cmd->m_params = params;
        cmd->m_bSaveNeed = bSaveNeed;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ToolCalibrate(
    QObject *object, const QString &sCalibrateName, CalibratePoints &pts)
{
    if (!m_isQuit) {
        CmdToolCalibrate *cmd = new CmdToolCalibrate;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Tool_Calibrate;
        cmd->m_sCalibrateName = sCalibrateName;
        cmd->m_calpts = pts;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ToolCalibratePoints(
    QObject *object, quint16 toolId, CalibratePoints &pts)
{
    if (!m_isQuit) {
        CmdToolSaveCalibratePoints *cmd = new CmdToolSaveCalibratePoints;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Tool_SaveCalibratePoints;
        cmd->m_toolId = toolId;
        cmd->m_calpts = pts;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_ToolMoveToPoint(
    QObject *object, Robot_ToolCalibrateType calibrateType, const Pos &pos,
    const Ori &ori, Robot_MoveType moveType)
{
    if (!m_isQuit) {
        CmdToolMoveToPoint *cmd = new CmdToolMoveToPoint;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_Tool_MoveToPoint;
        cmd->m_calibrateType = calibrateType;
        cmd->m_pos = pos;
        cmd->m_ori = ori;
        cmd->m_moveType = moveType;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WObjSave(QObject *object, quint16 wobjId,
                                              const WobjParams &params)
{
    if (!m_isQuit) {
        CmdWObjSave *cmd = new CmdWObjSave;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WObj_SaveWObjParams;
        cmd->m_wobjId = wobjId;
        cmd->m_params = params;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WObjCalibrate(
    QObject *object, int wobjId, Robot_WObjType type,
    const CalibratePoints &midUFramePos,
    const CalibratePoints &midOFramePos, const Pos &oldUFramePos,
    const Ori &oldUFrameOri)
{
    if (!m_isQuit) {
        CmdWObjCalibrate *cmd = new CmdWObjCalibrate;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WObj_WObjCalibrate;
        cmd->m_wobjType = type;
        cmd->m_midUFramePos = midUFramePos;
        cmd->m_midOFramePos = midOFramePos;
        cmd->m_oldUFramePos = oldUFramePos;
        cmd->m_oldUFrameOri = oldUFrameOri;
        cmd->m_wobjId = wobjId;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WObjCalibratePoints(
    QObject *object, quint16 wobjNo, const CalibratePoints &uFramePoint,
    const CalibratePoints &oFramePoint)
{
    if (!m_isQuit) {
        CmdWObjSaveCalibratePoints *cmd = new CmdWObjSaveCalibratePoints;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WObj_SaveWObjCalibratePoints;
        cmd->m_wobjId = wobjNo;
        cmd->m_uFramePoint = uFramePoint;
        cmd->m_oFramePoint = oFramePoint;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_WObjMoveToPoint(
    QObject *object, const Pos &pos, const Ori &ori, int ArmParm[4],
    Robot_MoveType type, Robot_WObjType method)
{
    if (!m_isQuit) {
        CmdWObjMoveToPoint *cmd = new CmdWObjMoveToPoint;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WObj_WObjMoveToPoint;
        cmd->m_method = method;
        cmd->m_pos = pos;
        cmd->m_ori = ori;
        memcpy(&cmd->armPara[0], &ArmParm[0], sizeof(int) * 4);
        cmd->m_moveType = type;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_handleWObjCalibrate(
    QObject *object, const AbstractCmd::CmdType &type, const QVariant &value)
{
    if (!m_isQuit) {
        CmdCommonWObjCalibrate *cmd = new CmdCommonWObjCalibrate;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_value = value;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_axisMove(
    QObject *object,
    int axisId, const bool &isPositive, const bool &isPressd)
{
    if (!m_isQuit) {
        CmdAxisMove *cmd = new CmdAxisMove;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_AxisMove;
        cmd->m_axisId = axisId;
        cmd->m_isPositive = isPositive;
        cmd->m_isPressd = isPressd;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_putFilesToController(
    QObject *object, const QString &sProjectName,
    const QStringList &srcFileList, const QStringList &destFileList, bool isProject)
{
    if (!m_isQuit) {
        CmdPutFilesToController *cmd = new CmdPutFilesToController;
        cmd->m_object = object;
        cmd->m_projectName = sProjectName;
        cmd->m_cmdType = AbstractCmd::CmdType_PutFilesToController;
        cmd->m_srcFileList = srcFileList;
        cmd->m_destFileList = destFileList;
        cmd->m_isProject = isProject;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_removeFilesFromController(
    QObject *object, const QString &projectName, const QStringList &fileNameList)
{
    if (!m_isQuit) {
        CmdRemoveFilesFromController *cmd = new CmdRemoveFilesFromController;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_RemoveFilesFromController;
        cmd->m_projectName = projectName;
        cmd->m_fileNameList = fileNameList;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_handleProject(
    QObject *object, const AbstractCmd::CmdType &type, const QVariant &value)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_value = value;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_userLogin(
    QObject *object, const InoUserMode mode, const QString &sPasswd)
{
    if (!m_isQuit) {
        CmdUserLogin *cmd = new CmdUserLogin;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_UserLogin;
        cmd->m_userMode = mode;
        cmd->m_sPasswd = sPasswd;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_setCtlAuthority(
    QObject *object, InoCtrlAuthority authority)
{
    if (!m_isQuit) {
        CmdSetCtrlAuthority *cmd = new CmdSetCtrlAuthority;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_SetCtlAuthority;
        cmd->m_ctrlAuthority = authority;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_CheckOtherFieldBusIsActive(
    QObject *object, QObject *target, int switchtype)
{
    if (!m_isQuit) {
        CmdCheckOtherFieldBusIsActive *cmd = new CmdCheckOtherFieldBusIsActive;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_CheckOtherFieldBusIsActive;
        cmd->m_target = target;
        cmd->m_type = switchtype;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_saveTorqueLimit(QObject *object,
                                                     const AbstractCmd::CmdType &type, bool bSwitch, int values[ROBOT_AXIS_NUM])
{
    if (!m_isQuit) {
        CmdSaveTorqueLimit *cmd = new CmdSaveTorqueLimit;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->bSwitch = bSwitch;
        memcpy(cmd->IntValue, values, sizeof(cmd->IntValue));

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_saveAvrLoadLimit(QObject *object,
                                                      const AbstractCmd::CmdType &type, bool bSwitch, int values[ROBOT_AXIS_NUM])
{
    if (!m_isQuit) {
        CmdSaveAvrLoadLimit *cmd = new CmdSaveAvrLoadLimit;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->bSwitch = bSwitch;
        memcpy(cmd->IntValue, values, sizeof(cmd->IntValue));

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_writeEthernetIpConfig(
    QObject *object, const CobotEthernetIpPara &params)
{
    if (!m_isQuit) {
        CmdWriteEthernetIpConfig *cmd = new CmdWriteEthernetIpConfig;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteEthernetIpConfig;
        memcpy(&cmd->m_params, &params, sizeof(cmd->m_params));

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_writeEthernetCatConfig(
    QObject *object, const InoEthcatPara &params,
    quint16 ARMSetLinkEnhanSwitch, quint16 EtherCATXMLReset)
{
    if (!m_isQuit) {
        CmdWriteEthernetCatConfig *cmd = new CmdWriteEthernetCatConfig;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteEtherCatConfig;
        memcpy(&cmd->m_params, &params, sizeof(cmd->m_params));
        cmd->EtherCATXMLReset = EtherCATXMLReset;
        cmd->ARMSetLinkEnhanSwitch = ARMSetLinkEnhanSwitch;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_writeModbusConfig(
    QObject *object, const CobotModbusParaConfig &config)
{
    if (!m_isQuit) {
        CmdWriteModbusConfig *cmd = new CmdWriteModbusConfig;
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_WriteModbusConfig;
        memcpy(&cmd->m_config, &config, sizeof(cmd->m_config));

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_saveOverHeatAndLoadLimit(QObject *object,
                                                              const AbstractCmd::CmdType &type, bool bOverHeat, bool bOverLoad)
{
    if (!m_isQuit) {
        CmdSaveOverHeatAndLoadLimit *cmd = new CmdSaveOverHeatAndLoadLimit;
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->bOverHeatSwitch = bOverHeat;
        cmd->bOverLoadSwitch = bOverLoad;

        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_setGlobalVarData(
    QObject *object,
    const AbstractCmd::CmdType type,
    const int row,
    const QVector<QVariant> &data)
{
    if (!m_isQuit) {
        CmdSetGlobalVarData *cmd = new CmdSetGlobalVarData();
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->data = data;
        cmd->row = row;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_getGlobalVarData(
    QObject *object,
    const AbstractCmd::CmdType type,
    const int currentRow)
{
    if (!m_isQuit) {
        CmdGetGlobalVarData *cmd = new CmdGetGlobalVarData();
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->currentRow = currentRow;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_getParam(
    QObject *object, const AbstractCmd::CmdType type, int targetNode)
{
    if (!m_isQuit) {
        CmdGetParam *cmd = new CmdGetParam();
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->targetNode = targetNode;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_KineInverseSolution(
    QObject *object, short toolId, short wobjId, short loadId, double pts[6], int armArgs[4])
{
    if (!m_isQuit) {
        CmdKineInverseSolution *cmd = new CmdKineInverseSolution();
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_KineInverseSolution;
        cmd->toolId = toolId;
        cmd->wobjId = wobjId;
        cmd->loadId = loadId;
        memcpy(cmd->pos, pts, sizeof(double) * 6);
        memcpy(cmd->armArgs, armArgs, sizeof(int) * 4);
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_enableGripperThreePosition(
    QObject *object, bool enable)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue();
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_EnableGripperThreePosition;
        cmd->m_value = enable;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_enableSingleControllerRunMode(
    QObject *object, bool enable)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue();
        cmd->m_object = object;
        cmd->m_cmdType = AbstractCmd::CmdType_EnableSingleControllerRunMode;
        cmd->m_value = enable;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_handleReleaseBrake(
    QObject *object, const AbstractCmd::CmdType type, int axisNo)
{
    if (!m_isQuit) {
        CmdReleaseBrake *cmd = new CmdReleaseBrake();
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_axisNo = axisNo;
        appendCmdInfo(cmd);
    }
}

void CommunicationEngine::enqueueCmd_handleSystemBackupAndLoad(
    QObject *object, const AbstractCmd::CmdType type, const QString &filePath)
{
    if (!m_isQuit) {
        CmdCommonValue *cmd = new CmdCommonValue();
        cmd->m_object = object;
        cmd->m_cmdType = type;
        cmd->m_value = filePath;
        appendCmdInfo(cmd);
    }
}
