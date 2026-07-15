#include "robotcontrolinterface.h"
#include <QDebug>
#include <QThread>
#include <vector>
#include "metatypeconversion.h"
#include "communication.h"
#include "cobotlog.h"
#include "math.h"
#include "instance.h"
#include "commandinfo.h"
#include "InoRobLog.h"
#include "InoRobUtil.h"
#include "InoRobBusiness/Workstation/IWorkstation.h"
#include "InoRobBusiness/Project/IProject.h"
#include "IController.h"
#include "Factory.h"
#include "datacollectioninterface.h"
#include "communicationengine.h"
#include "InoRobBusiness/Controller/Monitor/IWarnInfo.h"
#include "cobotlogex.h"
#include "modulesutils.h"
#include "udf.h"
#include "InoRobUtil/FTP/FileCast.h"
#include "InoRobBusiness/VirtualControllerDeviceManager.h"

namespace Internal
{
class PluginSpecPrivate;

class RobotControlInterfacePrivate
{
public:
    RobotControlInterfacePrivate(
        RobotControlInterface *robotControlInterface);
    virtual ~RobotControlInterfacePrivate();

private:
    RobotControlInterface *q;
};

RobotControlInterfacePrivate::RobotControlInterfacePrivate(
    RobotControlInterface *robotControlInterface) :
    q(robotControlInterface)
{
}

RobotControlInterfacePrivate::~RobotControlInterfacePrivate()
{
}

}  // namespace Internal

using namespace Internal;

static Internal::RobotControlInterfacePrivate *d = 0;

RobotControlInterface::RobotControlInterface()
{
    d = new RobotControlInterfacePrivate(this);
}

RobotControlInterface::~RobotControlInterface()
{
    delete d;
    d = 0;
}

bool RobotControlInterface::robotMoveTeachStartOrStopInterface(
    const TeachMode &teachMode,
    const bool &direction,
    CoordParam coordParam,
    bool isStart)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;

    int axisId;
    // 对于关节运动axisId为轴号，1-6对应关节轴1-6
    if (teachMode >= TeachMode_Joint1 && teachMode <= TeachMode_Joint7) {
        axisId = teachMode;
    }
    // 对于直线运动axisId为移动或旋转方向，1-6对应为X、Y、Z、RX、RY、RZ
    else if (teachMode >= TeachMode_MovX && teachMode <= TeachMode_RotZ) {
        axisId = teachMode - TeachMode_MovX + 1;
    } else {
        return false;
    }

    InoRobUtil::CoordType coordType = _IMonitor->GetCurrentCoordType();
    qDebug() << __FUNCTION__ << "current coordType:" << coordType << "axisId" << axisId;

    // 移动运动
    ret = _IMotion->AxisMove(
        axisId,
        direction ?
            InoRobBusiness::RotateDir::POSITIVE :
            InoRobBusiness::RotateDir::REVERSE,
        isStart ?
            InoRobBusiness::PressState::BTN_DOWN :
            InoRobBusiness::PressState::BTN_UP);
    qDebug() << "robotMoveTeachStartOrStopInterface::axisMove " << (isStart ? "Start" : "Stop") << " ret : " << ret;

    if (ret != 0) {
        LOG_INFO(QString("robotMoveTeachStartOrStopInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveSlowlyStopInterface()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!comm()->isConnected()) {
        return true;
    }

    bool ret;

    ret = _IMotion->MoveToPointStop();

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveJointTeachInterface(
    const RoadPoint &roadPoint)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;

    ret = _IMotion->JointMoveToPointStart(
        MetaTypeConversion::tp2InoApi_roadPoint(roadPoint));

    if (ret != 0) {
        LOG_INFO(QString("robotMoveJointTeachInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveLineInterface(const RoadPoint &destPt)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;
    int16u toolId = comm()->GetCurToolId();
    ReferObj referObj = static_cast<ReferObj>(comm()->GetCurWObjId());
    // if (coordParam.m_coordType == BaseCoordinate) {
    //     referObj = ReferBase;
    // } else if (coordParam.m_coordType == ToolCoordinate) {
    //     referObj = ReferFlange;
    // } else {
    //     QString toolName = coordParam.m_toolName;
    //     // TODO:toolName转换为toolId
    //     referObj = static_cast<ReferObj>(comm()->GetCurWObjId());
    // }
    // referObj = static_cast<ReferObj>(comm()->GetCurWObjId());

    RobPos robPos = MetaTypeConversion::tp2InoApi_roadPoint2RobPos(destPt);
    ret = _IMotion->MovlToPointStart(
        robPos,
        toolId,
        referObj);
    qDebug() << __FUNCTION__ << "MoveLineTeach ret=" << ret
             << robPos.RPosData[0] << robPos.RPosData[1] << robPos.RPosData[2]
             << robPos.RPosData[3] << robPos.RPosData[4] << robPos.RPosData[5]
             << robPos.ArmParm[0] << "|" << toolId;
    if (ret != 0) {
        LOG_INFO(QString("robotMoveLineInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveJointInterface(const InoRobPos &iRobPos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;
    int16u toolId = comm()->GetCurToolId();
    ReferObj referObj = static_cast<ReferObj>(comm()->GetCurWObjId());

    RobPos robPos = MetaTypeConversion::inoApi2tp_robPos(iRobPos);
    ret = _IMotion->MovjToPointStart(
        robPos,
        toolId,
        referObj);

    if (ret != 0) {
        LOG_INFO(QString("robotMoveJointInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveLineInterface(const RoadPoint &destPt, const int &tool, const int &wobj)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;
    int16u toolId = tool;
    ReferObj referObj = static_cast<ReferObj>(wobj);

    RobPos robPos = MetaTypeConversion::tp2InoApi_roadPoint2RobPos(destPt);
    ret = _IMotion->MovlToPointStart(
        robPos,
        toolId,
        referObj);

    if (ret != 0) {
        LOG_INFO(QString("robotMoveLineInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
        return ret;
}

bool RobotControlInterface::robotMoveJointInterface(const InoRobPos &iRobPos, const int &tool, const int &wobj)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;
    int16u toolId = tool;
    ReferObj referObj = static_cast<ReferObj>(wobj);

    RobPos robPos = MetaTypeConversion::inoApi2tp_robPos(iRobPos);
    ret = _IMotion->MovjToPointStart(
        robPos,
        toolId,
        referObj);

    if (ret != 0) {
        LOG_INFO(QString("robotMoveJointInterface ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::robotMoveRotateTeachInterface(
    const CoordParam &coordParam,
    const TeachMode &teachMode,
    const double &rotateAngle)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;

    RoadPoint roadPoint
        = Communication::instance()
              ->GetCurRoadPoint();
    if (teachMode == TeachMode::TeachMode_RotX) {
        roadPoint.m_orientation.m_rx += rotateAngle;
    } else if (teachMode == TeachMode::TeachMode_RotY) {
        roadPoint.m_orientation.m_ry += rotateAngle;
    } else if (teachMode == TeachMode::TeachMode_RotZ) {
        roadPoint.m_orientation.m_rz += rotateAngle;
    } else {
        qDebug() << __FUNCTION__ << __LINE__ << "teachMode not support";
        return ret;
    }

    int16u toolId = comm()->GetCurToolId();
    ReferObj referObj = ReferBase;
    if (coordParam.m_coordType == BaseCoordinate) {
        referObj = ReferBase;
    } else if (coordParam.m_coordType == ToolCoordinate) {
        referObj = ReferFlange;
    } else {
        QString toolName = coordParam.m_toolName;
        // TODO:toolName转换为toolId
        referObj = static_cast<ReferObj>(comm()->GetCurWObjId());
    }

    RobPos robPos = MetaTypeConversion::tp2InoApi_roadPoint2RobPos(roadPoint);
    ret = _IMotion->MoveToPointStart(
        Movl,
        robPos,
        toolId,
        referObj);
    qDebug() << __FUNCTION__ << "MoveRotateTeach ret=" << ret << robPos.RPosData[0] << robPos.RPosData[1] << robPos.RPosData[2]
             << robPos.RPosData[3] << robPos.RPosData[4] << robPos.RPosData[5] << robPos.ArmParm[0];
    ;
    if (ret != 0) {
        LOG_INFO(QString("RobotControlInterface::MoveRotateTeach ret : %1").arg(QString::number(ret)));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::connectController(
    const QString &ip, const int &port)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    comm()->setIP(ip);
    comm()->setPort(port);

    _IConnection->SetIp(ip.toStdString());
    _IConnection->setPort(port);
    bool ret = _IConnection->Connect(
        InoRobBusiness::CONNECT_TP_TYPE);
    if (!ret) {
        InoRobLog::error(
            "connect controller {}:{} failed", ip.toStdString(), port);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotControlInterface::connectVirtualController(AbstractCmd *cmd){
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("connectVirtualController start");
    
    bool isSuccess = false;
    QString msg;
    
    try {

        auto [ip, port, virtualpath] = BIND(cmd, QString, QString, QString);
        
        LOG_INFO(QString("connectVirtualController params: ip=%1, port=%2, virtualpath=%3")
                 .arg(ip).arg(port).arg(virtualpath));
        
        if (_IConnection == nullptr) {
            msg = QObject::tr("connection object is null");
            LOG_ERROR("connectVirtualController: " + msg);
            return false;
        }


        // bool ret = _IConnection->Close(true);
        // if (!ret) {
        //     InoRobLog::error("disconnect controller {}:{} failed");
        //     return false;
        // }

        comm()->setIP(ip);
        comm()->setPort(port.toUInt());
        
        _IConnection->SetIp(ip.toStdString());
        _IConnection->setPort(port.toUInt());

   
        // 执行连接
        bool rt = _IConnection->Connect(InoRobBusiness::CONNECT_TP_TYPE);
        if (!rt) {
            msg = QObject::tr("connect to controller failed");
            LOG_ERROR("connectVirtualController: " + msg);
            return false;
        }
        
        //  设置控制器类型
        if (ip == "127.0.0.1") {
            // 虚拟控制器
            if (!virtualpath.isEmpty()) {
                FileCast filecast;
                filecast.restoreOriginalLocation(virtualpath.toStdString());
            }
            _IConnection->setControllerType(1);
            
            if (_IProject) {
                _IProject->GetName();  // 原代码中有这行，可能用于调试
                // _IProject->SetControllerType(TPPlatform::ControllerType::CONTRL_TYPE_VIRTUAL);
            }
            
            InoRobLog::debug("Connected to virtual controller");
            msg = QObject::tr("Connected to virtual controller");
        }
        else {
            // 真实控制器
            _IConnection->setControllerType(0);
            if (_IProject) {
                // _IProject->SetControllerType(TPPlatform::ControllerType::CONTRL_TYPE_REAL);
            }
            msg = QObject::tr("Connected to real controller");
        }
        
        isSuccess = true;
        LOG_INFO("connectVirtualController: " + msg);
        
    } catch (const std::exception& ex) {
        LOG_ERROR("connectVirtualController Exception: " + QString::fromStdString(std::string(ex.what())));
        isSuccess = false;
    }
    
   
    emit CommunicationEngine::instance()->singal_connectVirtualController_result(cmd->m_object, isSuccess, msg);
    
    LOG_INFO(QString("connectVirtualController end. success=%1").arg(isSuccess));
    FREQ_LOG_PRINT_TIMESTAMP
    
    return isSuccess;
}

int RobotControlInterface::processVirtualControllerDeviceName(AbstractCmd *cmd){
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("processVirtualControllerDeviceName start");
    
    try {
        auto [deviceName] = BIND(cmd, std::string);
        
        LOG_INFO(QString("processVirtualControllerDeviceName params: deviceName=%1")
                 .arg(QString::fromStdString(deviceName)));
        
        VirtualControllerDeviceManager::instance()->setDeviceName(deviceName);
        
    } catch (const std::exception& ex) {
        LOG_ERROR("processVirtualControllerDeviceName Exception: " + QString::fromStdString(std::string(ex.what())));
        return -1;
    }
    
    FREQ_LOG_PRINT_TIMESTAMP
    return 0;

}

bool RobotControlInterface::disconnectController()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IConnection->Close(true);
    if (!ret) {
        InoRobLog::error("disconnect controller {}:{} failed");
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::enableMechLock(const bool &enable)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IControl->SetMechLock(enable);
    qDebug() << "RobotControlInterface::enableMechLock ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::clearAlarm()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->ClearWarning(
        InoRobBusiness::PressState::BTN_DOWN);
    qDebug() << "RobotControlInterface::clearAlarm ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return 0 == ret;
}

bool RobotControlInterface::enableRobot(const bool &enable)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetEnable(enable);
    qDebug() << "RobotControlInterface::enableRobot ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return 0 == ret;
}

bool RobotControlInterface::SetEmergency(bool status)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetEmergency(status);
    qDebug() << "RobotControlInterface::SetEmergency ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return 0 == ret;
}

bool RobotControlInterface::axisMove(
    int axisId, const bool &isPositive, const bool &isPressd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IMotion->AxisMove(
        axisId,
        isPositive ?
            InoRobBusiness::RotateDir::POSITIVE :
            InoRobBusiness::RotateDir::REVERSE,
        isPressd ?
            InoRobBusiness::PressState::BTN_DOWN :
            InoRobBusiness::PressState::BTN_UP);
    LOG_INFO(QString("RobotControlInterface::axisMove ret : %1").arg(QString::number(ret)));
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::putFilesToController(
    const QStringList &srcFileList, const QStringList &destFileList)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = true;

    if (srcFileList.size() != destFileList.size()) {
        ret = false;
    } else {
        std::vector<std::string> srcVector;
        std::vector<std::string> destVector;
        for (int i = 0; i < srcFileList.size(); i++) {
            srcVector.push_back(srcFileList.at(i).toStdString());
            destVector.push_back(destFileList.at(i).toStdString());
        }

        int nRet = ProjectHelper::PutFilesToController(
            comm()->getIP().toStdString(), srcVector, destVector);
        qDebug() << "RobotControlInterface::putFilesToController ret= " << nRet;
        ret = InoRobUtil::OK == nRet;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::programStart()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IScriptExtension->Start();

    // 临时测试用，因功能码新旧不一致
    // bool ret = _IScriptExtension->Pause();
    qDebug() << "RobotControlInterface::programStart ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::programPause()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IScriptExtension->Pause();

    // 临时测试用，因功能码新旧不一致
    // bool ret = _IScriptExtension->Step();
    qDebug() << "RobotControlInterface::programPause ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::programContinue()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return programStart();
}

bool RobotControlInterface::programStop()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IScriptExtension->Abort();
    qDebug() << "RobotControlInterface::programStop ret : " << ret;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::programStep()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
#ifndef INOCOBOTTP_MSVC_QT5
        bool ret = _IScriptExtension->StepBlock();
    #else
    bool ret = 0;
#endif

    // 临时测试用，因功能码新旧不一致
    // bool ret = _IScriptExtension->Abort();
#ifndef INOCOBOTTP_MSVC_QT5
    qDebug() << "RobotControlInterface::programStep ret : " << ret;
#endif
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotControlInterface::SetDeviceMode(MetaType::RobotDeviceMode mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IControl->SetDeviceMode(
        static_cast<InoRobBusiness::DeviceMode>(mode));
}

int RobotControlInterface::GetDeviceMode(MetaType::RobotDeviceMode &mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    InoRobBusiness::RunMode runmode;
    runmode = _IMonitor->GetRunMode();
    if (runmode == InoRobBusiness::RUN_MODE_REAPPEAR) {
        mode = MetaType::RobotDeviceMode_Auto;
    } else {
        mode = MetaType::RobotDeviceMode_Manual_Low;
    }

    // mode = static_cast<MetaType::RobotDeviceMode>(deviceMode);
    // qDebug() << "Current Device Mode = " << static_cast<int>(mode)
    //          << " | iRet = " << iRet;
    FREQ_LOG_PRINT_TIMESTAMP
    return 0;
}

void RobotControlInterface::setRobotBodyPowerState(InoCoRobotBodyPowerState state)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (state == InoCoRobotBodyPowerState::ROBOT_BODY_POWER_OFF || state == InoCoRobotBodyPowerState::ROBOT_BODY_POWER_ON) {
        int ret = _IControl->SetCoRobotBodyPowerState((InoRobBusiness::CoRobotBodyPowerState)state);
        if (ret != ERROR_OK)
            emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to power on/off the robot."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

InoCoRobotBodyPowerState RobotControlInterface::getRobotBodyPowerState()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return (InoCoRobotBodyPowerState)(_IMonitor->GetCoRobotBodyPowerState());
}

bool RobotControlInterface::setControllerWifiPassword(const QString &password)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetControllerWifiPassword(
        password.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::getWifiPasswordModifyResult(InoWifiPasswordModifyResult &result)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    InoRobBusiness::WifiPasswordModifyResult iResult;
    int ret = _IControl->GetWifiPasswordModifyResult(iResult);
    result = static_cast<InoWifiPasswordModifyResult>(iResult);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::setControllerWifiFrequncyBand(bool is24GHz)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetControllerWifiFrequencyBand(is24GHz);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::getControllerWifiInfo(InoCobotWifiInfo &wifiInfo)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::ControllerWifiInfo info;
    int ret = _IControl->GetControllerWifiInfo(info);
    memcpy(&wifiInfo, &info, sizeof(info));

    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::enableGripperThreePosition(bool enable)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetGripperThreePositionEnable(enable);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::setSingleControllerRunModeEnable(bool enable)
{
    qDebug() << "setSingleControllerRunModeEnable: " << enable;
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->SetSingleControllerRunModeEnable(enable);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::getSingleControllerRunModeEnable(bool &enable)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool ret = _IControl->GetSingleControllerRunModeEnable(enable);
    qDebug() << "getSingleControllerRunModeEnable: " << enable;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

bool RobotControlInterface::getSingleControllerRunModeStatus(bool &status)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->GetSingleControllerRunModeStatus(status);
    qDebug() << "getSingleControllerRunModeStatus: " << status;
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

void RobotControlInterface::SetDebugMode(MetaType::RobotDebugMode mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    _IDebuger->setDebugMode(
        static_cast<InoRobBusiness::DebugMode>(mode));
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotControlInterface::getHistoryWarnList(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [old] = BIND(cmd, QStringList);
    if(!Communication::instance()->isConnected()){
        emit CommunicationEngine::instance()->signal_getHistoryAlarmRes(cmd->m_object, QStringList());
        return;
    }
    std::vector<InoRobBusiness::IWarnInfo::WarnData> list
        = _IWarnInfo->getWarningList(0);
    // qDebug() << "list size is" << list.size();
    QStringList ans;
    for (int i = list.size() - 1; i > -1; --i) {
        ans << QString(QObject::tr("[Error] [%1] [%2] %3"))
                   .arg(QString::fromStdString(list[i].time),
                        QString::fromStdString(list[i].errcode),
                        QString::fromStdString(list[i].content));
    }
    if(old != ans)
        emit CommunicationEngine::instance()->signal_getHistoryAlarmRes(cmd->m_object, ans);
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void RobotControlInterface::clearHistoryWarnInfo(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IWarnInfo->clearWarnInfo();
    FREQ_LOG_PRINT_TIMESTAMP
    // 模型层已打印错误日志
}

bool RobotControlInterface::readBrakeState(char stateArray[6])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IControl->readBrakeState(stateArray);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

void RobotControlInterface::releaseBrake(int axisNo)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (axisNo < 1 || axisNo > 6) {
        return;
    }

    _IControl->setBrakeCurAxisNo(axisNo);
    _IControl->cleanBrakeCount();
    _IControl->setBrakeFirstCmd(true);
    _IControl->setBrakeThreadState(true);
    FREQ_LOG_PRINT_TIMESTAMP
}

bool RobotControlInterface::checkControllerUSB()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IMaintenance->checkControllerUSB();
}

void RobotControlInterface::closeBrake(int axisNo)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    _IControl->setBrakeThreadState(false);
    _IControl->cleanBrakeCount();
    _IControl->writeBrakeState(static_cast<char>(1), 0, axisNo, true);
    FREQ_LOG_PRINT_TIMESTAMP
}

bool RobotControlInterface::readFileSaveFlag(int &nMark)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IRCConfig->readFileSaveFlag(nMark);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool RobotControlInterface::controllerFilePathList(const std::string &ctrlPath,
                                                   std::vector<std::string> &filePathList)
{
    if (!comm()->isConnected()) {
        return false;
    }

    std::string controlPath = ctrlPath;
    bool isLocalAddress = comm()->isConnectVirtualController();
    if (isLocalAddress) {
        controlPath = ProjectHelper::VirtualControllerSDCardFolder() + "/" + ctrlPath;
    }

    bool ret = true;
    if (isLocalAddress) {
        InoRobUtil::GetFileList(filePathList, controlPath);
    } else {
        UDF udf;
        ret = udf.fileList(controlPath, filePathList);
    }

    LOG_INFO(QString("controller fileList, ctrlPath = %1, ret = %2")
                 .arg(controlPath.c_str(), QString::number(ret)));
    return ret;
}

bool RobotControlInterface::downloadFile(const std::string &localPath, const std::string &ctrlPath)
{
    std::string slocalPath = localPath;
#ifdef Q_OS_WIN
    if (ProjectHelper::isContainsChinese(localPath)) {
        slocalPath = InoRobUtil::convertSystemEncoding(localPath);
    }
#endif

    bool ret = true;
    if (Communication::instance()->isConnectVirtualController()) {
        ret = FileCopy(ctrlPath, localPath);
    } else {
        UDF udf;
        ret = udf.downloadFile(ctrlPath, slocalPath);
    }

    LOG_INFO(QString("download file, local = %1, ctrl = %2, ret = %3")
                 .arg(slocalPath.c_str(), ctrlPath.c_str(), QString::number(ret)));
    return ret;
}

bool RobotControlInterface::formatMemoryCard()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IRCConfig->writeSDFormatCmd(1);
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

int RobotControlInterface::readMemoryCardFormatState(int &nState)
{
    return _IRCConfig->readSDFormatState(nState);
}

void RobotControlInterface::endFormatMemoryCard()
{
    _IRCConfig->writeSDFormatCmd(0);
}

bool RobotControlInterface::loadPointFile(const QString &filePath)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (filePath.isEmpty()) {
        return false;
    }

    QFileInfo fi(filePath);
    std::string fileDest = CONTROLLER_POINT_FILE_DIR + fi.fileName().toStdString();
    int ret = _IRCConfig->writeFileOthers(
        fi.absoluteFilePath().toStdString(), std::move(fileDest));
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

bool RobotControlInterface::deletePointFile(const QString &fileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (fileName.isEmpty()) {
        return false;
    }

    std::string controllerFileName = CONTROLLER_POINT_FILE_DIR + fileName.toStdString();
    int ret = _IRCConfig->delFile(std::move(controllerFileName));
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERROR_OK);
}

MetaType::ElectricControlCabinetType RobotControlInterface::getElectricControlCabinetType()
{
    return static_cast<MetaType::ElectricControlCabinetType>(
        static_cast<int32s>(_IMonitor->GetElectricControlCabinetType()));
}
