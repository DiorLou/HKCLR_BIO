#include "controllersystemconfig.h"
#include "controllersystemconfig_p.h"
#include <QDebug>
#include "communication.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Connection/IConnection.h"
#include "communicationengine.h"
#include "InoRobBusiness/RobotParam/IRobotParam.h"
#include "InoRobBusiness/RobotParam/GeneralMatch/IGeneralMatch.h"
#include "InoRobBusiness/Controller/IController.h"
#include "cobotlog.h"
#include "communicationtr.h"
#include "rs485type.h"
#include "communicationtr.h"
#include "Crc/Crc16.h"
#include "templateutils.h"
#include "cobotlogex.h"
#include "udf.h"
#include "modulesutils.h"
#include "InoRobBusiness/Controller/Language/ILanguage.h"
#include "Workstation/IWorkstation.h"
#include <Workstation/WorkstationDefault.h>
#include "stringutils.h"
#include "metapath.h"
#include "databaselocal.h"
#include "fileutils.h"
#include "roboteventinfo.h"
#define MIANWARNING(x) CommunicationEngine::instance()->signal_needMainWidgetWarning(x);

// 保存网络配置
namespace  Internal{


IController *ControllerSystemConfigPrivate::controller()
{
    return q->controller();
}

ControllerSystemConfigPrivate::ControllerSystemConfigPrivate(ControllerSystemConfig *config) :
    q(config)
{

}

int ControllerSystemConfigPrivate::saveEthConfig(const InoControllerEthCfg &ethCfg)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    ControllerEthCfg cfg;
    cfg.strcEth0.strDHCP = ethCfg.strcEth0.strDHCP.toStdString();
    cfg.strcEth0.strIP = ethCfg.strcEth0.strIP.toStdString();
    cfg.strcEth1.strDHCP = ethCfg.strcEth1.strDHCP.toStdString();
    cfg.strcEth1.strIP = ethCfg.strcEth1.strIP.toStdString();
    return _IRCConfig->saveEthConfig(cfg);

    FREQ_LOG_PRINT_TIMESTAMP
}

// 获取网络IP
void ControllerSystemConfigPrivate::getEthConfig(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoControllerEthCfg ethCfg;
    ushort eth0State = 0, eth1State = 0;

    int16u moduleCommState[MODULE_NUM];
    _IMonitor->GetModuleCommState(moduleCommState);
    eth0State = moduleCommState[0];
    eth1State = moduleCommState[1];
    ControllerEthCfg cfg;
    int ret = _IRCConfig->getEthConfig(cfg);
    ethCfg.strcEth0.strDHCP = QString::fromStdString(cfg.strcEth0.strDHCP);
    ethCfg.strcEth0.strIP = QString::fromStdString(cfg.strcEth0.strIP);
    ethCfg.strcEth1.strDHCP = QString::fromStdString(cfg.strcEth1.strDHCP);
    ethCfg.strcEth1.strIP = QString::fromStdString(cfg.strcEth1.strIP);

    if (ret != ERROR_OK) {
        emit CommunicationEngine::instance()
            ->signal_needMainWidgetWarning(
                ControllerSystemConfigTr::tr("Failed to get Ethernet configuration."));
    } else {
        emit CommunicationEngine::instance()
            ->signal_getEthcfg_result(cmd->m_object, ethCfg, eth0State, eth1State);
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

// 读取网络配置
int ControllerSystemConfigPrivate::readCommonNetStatusInfo(
    QList<InoCommonNetStatus> &datas,
    unsigned char &serverState)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    CommonNetStatus source[TCP_MAX_NUM];
    int ret = _IRCConfig->readCommonNetStatusInfo(source, serverState);
    if (ret != ERR_OK)
        return ret;
    datas.clear();
    for (int i = 0; i < TCP_MAX_NUM; ++i) {
        InoCommonNetStatus temp;
        temp.netStatus = source[i].NetStatus;
        temp.localNetType = source[i].LocalNetType;
        temp.localAddrInfo.IP = QString(source[i].LocalAddrInfo.IP);
        temp.localAddrInfo.port = source[i].LocalAddrInfo.Port;
        temp.peerAddrInfo.IP = QString(source[i].PeerAddrInfo.IP);
        temp.peerAddrInfo.port = source[i].PeerAddrInfo.Port;
        datas.push_back(temp);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

// 网络参数配置
void ControllerSystemConfigPrivate::writeEthCommonOperation(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [source] = ((CmdDatas<InoCommonNetStatus> *)cmd)->m_data;
    CommonNetStatus temp;
    temp.NetStatus = source.netStatus;
    temp.LocalNetType = source.localNetType;
    string tempIp = source.localAddrInfo.IP.toStdString();

    temp.LocalAddrInfo.Port = source.localAddrInfo.port;
    memcpy(temp.LocalAddrInfo.IP, tempIp.c_str(), 16);

    tempIp = source.peerAddrInfo.IP.toStdString();
    temp.PeerAddrInfo.Port = source.peerAddrInfo.port;
    memcpy(temp.PeerAddrInfo.IP, tempIp.c_str(), 16);

    std::string errorInfo;
    int ret = _IRCConfig->checkNetPortIsValid(temp.LocalAddrInfo.Port, "", errorInfo);
    if (ret != ERROR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(CommTr::tr("Client: ") + QString::fromStdString(errorInfo));
        return;
    }

    ret = _IRCConfig->writeEthCommonOperation(temp);

    if (ERROR_OK != ret) {
        emit CommunicationEngine::instance()
            ->signal_needMainWidgetWarning(CommTr::tr("Failed to save network configuration."));
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

// 读取UI显示模式 0，客户端 1 服务器; serverPort:服务器端口号
int ControllerSystemConfigPrivate::readVisionMode(unsigned short &visionMode, unsigned short &serverPort)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IRCConfig->readVisionMode(visionMode, serverPort);
}

// 保存UI显示模式, 0-客户端,1-服务器 2服务器加客户端
int ControllerSystemConfigPrivate::saveVisionMode(unsigned short visionMode, unsigned short port)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IRCConfig->saveVisionMode(visionMode, port);
}

// 保存新的端口号
void ControllerSystemConfigPrivate::saveNewPort(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [currPort, newPort] = ((CmdDatas<int, int> *)cmd)->m_data;
    std::string errorInfo;
    int ret = _IRCConfig->checkNetPortIsValid(newPort, "", errorInfo);
    if (ret != ERROR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(CommTr::tr("Server: ") + QString::fromStdString(errorInfo));
        return;
    }
    ret = _IRCConfig->saveNewPort(currPort, newPort);
    if (ERROR_OK != ret) {
        emit CommunicationEngine::instance()
            ->signal_needMainWidgetWarning(QObject::tr("Failed to save network configuration."));
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

#define S2Q(x) QString::fromStdString(x)
void ControllerSystemConfigPrivate::getVersionInfo(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    QStringList res;
    QString errorStr;
    InoRobBusiness::ControllerConnectionStatus state = _IConnection->GetConnectionStatus();

    // 示教器版本 0.1
    auto teachPadVersion = _IMonitor->getTeachPadVersion();
    res.push_back(S2Q(teachPadVersion));
    if (state != InoRobBusiness::ControllerConnectionStatus::CONTROLLER_CONNECTION_STATUS_CONNECTED) {
        emit CommunicationEngine::instance()->signal_getVersionInfoResult(cmd->m_object, true, res);
        return;
    }
    std::vector<std::string> version;
    // int ret = _IMonitor->getControllerVersionInfo(version);
    //失败重读
    int ret = 0;
    int nTime = 0;
    while (true) {
        ret = _IMonitor->getControllerVersionInfo(version);
        nTime++;
        if (ret == ERR_OK || nTime >= 10) {
            break;
        }
    }

    if (ret != ERR_OK || version.size() < 8) {
        errorStr += QObject::tr("Failed to get controller version.");
        LOG_ERROR(QString("ret is %1, size is %2").arg(QString::number(ret), QString::number(version.size())));
        for (int i = 0; i < 9; ++i)
            res.push_back("----");
    } else {
        // 控制器版本 0.2
        res.push_back(S2Q(version[4]));
        // 控制器类型 1
        res.push_back(S2Q(version[0]));
        // 系统软件版本 3
        res.push_back(S2Q(version[1]));
        // 软件掉电保存类型 4
        bool isPowerDownSave = _IMonitor->GetIsPowerDownSave();
        res.push_back(isPowerDownSave ? QObject::tr("ON") : QObject::tr("OFF"));
        // 内核版本 5
        res.push_back(S2Q(version[2]));
        // 示教器系统版本 6
        res.push_back("----");
        // 引导软件版本 7
        res.push_back(S2Q(version[3]));
        // 控制器硬件版本 8
        int32u hardWareVer = _IMonitor->GetHardWareVer();
        res.push_back(QString::number(hardWareVer));
        // 控制系统固件版本 9
        res.push_back(S2Q(version[5]));
    }
    // 机器人型号 2
    char robotStructName[128] = {0};
    if (_IMonitor->GetRobotName(robotStructName)) {
        res.insert(res.begin() + 3, robotStructName);
    } else {
        errorStr += (errorStr.isEmpty() ? "" : "\r\n") + QObject::tr("Failed to get robot name.");
        res.push_back("----");
    }
    // 通配信息
    if (!Communication::instance()->isConnectVirtualController()) {
        InoRobBusiness::IGeneralMatch::GeneralMatchInfo matchInfo;
        if (!q->comm()
                 ->robotParam()
                 ->getGeneralMatch()
                 ->getGeneralMatchInfo(matchInfo)) {
            for (int i = 0; i < 7; ++i)
                res.push_back("----");
            errorStr += ((errorStr.isEmpty() ? "" : "\r\n") + QObject::tr("Failed to get universality info."));
        } else {
            res.push_back(S2Q(matchInfo.controllerParamCompatibilityVersion));  // 10
            res.push_back(S2Q(matchInfo.mainFPGAHardwareVersion));              // 11
            res.push_back(S2Q(matchInfo.mainFPGASoftwareVersion));              // 12
            res.push_back(S2Q(matchInfo.bodyHardwareVersion));                  // 13
            res.push_back(S2Q(matchInfo.bodySoftwareVersion));                  // 14
            res.push_back(S2Q(matchInfo.bodyParamVersion));                     // 15
            res.push_back(S2Q(matchInfo.bodyParamCompatibilityVersion));        // 16
        }
    }

    std::string toolIOVersion;
    ret = _IMonitor->readCobotToolIOVersion(toolIOVersion);
    if (ret != ERROR_OK) {
        toolIOVersion.clear();
        errorStr += (errorStr.isEmpty() ? "" : "\r\n") + QObject::tr("Failed to get tool I/O version info.");
        for (int i = 0; i < 4; ++i)
            res.push_back("----");
    } else {
        QJsonObject json = QJsonDocument::fromJson(toolIOVersion.c_str()).object();
        res.push_back(QString::number(json["ComVersion"].toInt()));   // 17
        res.push_back(QString::number(json["BootVersion"].toInt()));  // 18
        res.push_back(QString::number(json["XmlVersion"].toInt()));   // 19
        res.push_back(QString::number(json["TioVersion"].toInt()));   // 20
    }
    if (version.size() >= 10)
        res.push_back(S2Q(version[9]));
    if (!errorStr.isEmpty())
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(errorStr);
    for (auto &i : res)
        if (i.isEmpty() || i == "\r\n" || i == "\n")
            i = "----";
    emit CommunicationEngine::instance()->signal_getVersionInfoResult(cmd->m_object, true, res);

    FREQ_LOG_PRINT_TIMESTAMP
}

// 是否需要本地时间同步到控制器 同时获取了当前控制器时间
void ControllerSystemConfigPrivate::isNeedTimeSynToController()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    GSYSTEMTIME systemTime;
    int ret = _IConnection->readDevSysTime(systemTime);
    if (ret != ERROR_OK)
        return;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime controllerTime;
    controllerTime.setDate(QDate(systemTime.wYear, systemTime.wMonth, systemTime.wDay));
    controllerTime.setTime(QTime(systemTime.wHour, systemTime.wMinute, systemTime.wSecond));
    if (qAbs(currentDateTime.secsTo(controllerTime)) >= 180) {
        emit CommunicationEngine::instance()->signal_controllerTimeIsNeedSysnFromLocal(true, controllerTime);
    } else {
        emit CommunicationEngine::instance()->signal_controllerTimeIsNeedSysnFromLocal(false, controllerTime);
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

// 写控制器时间
void ControllerSystemConfigPrivate::setControllerTime(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [currentDateTime] = ((CmdDatas<QDateTime> *)cmd)->m_data;
    // QDateTime currentDateTime = QDateTime::currentDateTime();
    GSYSTEMTIME systemTime;
    systemTime.wYear = currentDateTime.date().year();
    systemTime.wMonth = currentDateTime.date().month();
    systemTime.wDay = currentDateTime.date().day();
    systemTime.wHour = currentDateTime.time().hour();
    systemTime.wMinute = currentDateTime.time().minute();
    systemTime.wSecond = currentDateTime.time().second();
    if (_IConnection->writeDevSysTime(systemTime, 1) != ERROR_OK) {
        QString str = QObject::tr("Failed to synchronize time to the controller.");
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(str);
        PRINT_MSG(str);
    } else
        PRINT_MSG(QObject::tr("Controller time synchronized successfully."));

    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

int ControllerSystemConfigPrivate::delDir(const std::string &dir)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IControl->delDir(dir);
}

int ControllerSystemConfigPrivate::createDir(const std::string &dir)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IControl->createDir(dir);
}

int ControllerSystemConfigPrivate::systemUpgrade(bool isUpdateBsp)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int iRet = _IControl->systemUpgrade(isUpdateBsp);
    LOG_INFO(QString("system upgrade : iret = %1").arg(QString::number(iRet)));
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return iRet;
}

int ControllerSystemConfigPrivate::readSystemUpdateInfo(CobotSystemUpdateInfo &info)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::SystemUpdateInfo rInfo;
    int iRet = _IControl->readSystemUpdateInfo(rInfo);

    LOG_INFO(QString("[read update info]ret = %1, status = %2, progress = %3, msg = %4")
                 .arg(QString::number(iRet), QString::number(rInfo.status), QString::number(rInfo.progress),
                      rInfo.msg));

    memcpy(&info, &rInfo, sizeof(rInfo));

    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return iRet;
}

void ControllerSystemConfigPrivate::writeToolReuseModel(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [type, activeRc485] = ((CmdDatas<ToolIO_RS485OrAD_ReuseMode, bool> *)cmd)->m_data;
    QString errorStr;
    QJsonObject object;
    object["GPIOMode"] = type;
    int ret = _IRCConfig->writeCobotToolRs485ReuseMode(QJsonDocument(object).toJson(QJsonDocument::Compact).toStdString());
    if (ret != ERROR_OK) {
        errorStr = CommTr::tr("Failed to set GPIO reuse model.");
    }

    ret = _IRCConfig->writeCobotRcRs485State(activeRc485);
    if (ret != ERROR_OK) {
        combinErrorStr(errorStr, CommTr::tr("Failed to set controller RS485 status."));
    }

    if (!errorStr.isEmpty())
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(errorStr);
    else
        PRINT_MSG(ControllerSystemConfigTr::tr("RS485 enabled status saved successfully."));
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void ControllerSystemConfigPrivate::writeRs485Config(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [type, activeRc485, isWriteToolRS485, toolConfig, config] = BIND(cmd, ToolIO_RS485OrAD_ReuseMode, bool, bool, ToolIO_RS485_Config, ToolIO_RS485_Config);
    QString errorStr;
    int ret = _IRCConfig->writeCobotRcRs485State(activeRc485);
    if (ret != ERROR_OK) {
        errorStr = CommTr::tr("Failed to set controller RS485 status.");
    }

    QJsonObject object;
    object["GPIOMode"] = type;
    ret = _IRCConfig->writeCobotToolRs485ReuseMode(QJsonDocument(object).toJson(QJsonDocument::Compact).toStdString());
    if (ret != ERROR_OK) {
        combinErrorStr(errorStr, CommTr::tr("Failed to set GPIO reuse model."));
    }

    bool ans = true;
    if (isWriteToolRS485) {
        QJsonObject object;
        object["Type"] = config.type;
        object["Baudrate"] = config.baudrate;
        object["DataBit"] = config.dataBit;
        object["StopBit"] = config.stopBit;
        object["CheckWay"] = config.checkWay;
        qDebug() << QJsonDocument(object).toJson(QJsonDocument::Compact);
        int ret = _IRCConfig->writeCobotToolRs485Config(QJsonDocument(object).toJson(QJsonDocument::Compact).toStdString());
        if (ret != ERROR_OK) {
            combinErrorStr(errorStr, CommTr::tr("Failed to set tool RS485 config."));
        }
    }
    QJsonObject object2;
    object2["Type"] = config.type;
    object2["Baudrate"] = config.baudrate;
    object2["DataBit"] = config.dataBit;
    object2["StopBit"] = config.stopBit;
    object2["CheckWay"] = config.checkWay;
    qDebug() << QJsonDocument(object2).toJson(QJsonDocument::Compact);
    ret = _IRCConfig->writeCobotToolRs485Config(QJsonDocument(object2).toJson(QJsonDocument::Compact).toStdString());
    if (ret != ERROR_OK) {
        combinErrorStr(errorStr, CommTr::tr("Failed to set controller RS485 config."));
    }
    if (!errorStr.isEmpty())
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(errorStr);
    else
        PRINT_MSG(ControllerSystemConfigTr::tr("RS485 config saved successfully."));
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void ControllerSystemConfigPrivate::writeRs485Debugging(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [config] = ((CmdDatas<ToolIO_RS485_Debugging> *)cmd)->m_data;
    QList<char> datain[20];
    QStringList contentList = config.content.split(' ');

    int size = contentList.size();
    if (size > 65535)
        return;
    QList<unsigned char> inputData;
    inputData.push_back(config.type);
    inputData.push_back(0);
    inputData.push_back(0);
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (contentList[i].size() > 2) {
            return;
        }
        if (contentList[i].size() == 0)
            continue;
        if (contentList[i].size() == 1) {
            contentList[i] = "0" + contentList[i];
        }
        inputData.push_back(contentList[i].toUShort(0, 16));
        ++count;
    }
    quint16 realSize = count + sizeof(quint16);
    memcpy(&inputData[1], &realSize, sizeof(quint16));
    InoRobUtil::Crc16 caluator;
    quint16 verificaton = caluator.CRC16_MODBUS(&inputData[3], count);

    inputData.push_back(0);
    inputData.push_back(0);
    memcpy(&inputData[inputData.size() - sizeof(quint16)], &verificaton, sizeof(quint16));
    qDebug() << inputData;
    std::vector<quint8> ans;
    int ret = _IRCConfig->writeCobotToolRs485Debugging(&inputData[0], inputData.size(), ans);
    if (ret != ERROR_OK || ans.size() < sizeof(quint16)) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(CommTr::tr("RS485 debugging failed."));
        return;
    }
    QList<quint8> ansList(ans.begin(), ans.end());
    qDebug() << ansList;
    quint16 len = 0;
    quint16 errorCode = 0;
    memcpy(&errorCode, &ansList[0], sizeof(quint16));
    memcpy(&len, &ansList[sizeof(quint16)], sizeof(quint16));
    QString errorStr;
    switch (errorCode) {
    case 0: {
        QString printStr;
        if (ansList.size() != len + sizeof(quint16) * 2) {
            errorStr = CommTr::tr("RS485 debugging attempt failed because the data length does not match the actual cache length.");
        } else {
            if (len == 0)
                printStr = CommTr::tr("The data was sent successfully, but the data received is empty.");
            else {
                for (int i = sizeof(quint16) * 2; i < ansList.size(); ++i) {
                    QString temp = QString::number(ansList[i], 16).toUpper();
                    printStr += ((temp.size() == 1 ? "0" : "") + temp + " ");
                }
            }
            QString time = QDateTime::currentDateTime().toString("hh:mm:ss:");
            emit CommunicationEngine::instance()->signal_tryRs485DebuggingResult(cmd->m_object, time + "\r\n" + printStr);
            return;
        }
        break;
    }
    case 1:
        errorStr = CommTr::tr("RS485 debugging attempt failed because the length of data sent exceeds the maximum limit.");
        break;
    case 2:
        errorStr = CommTr::tr("RS485 debugging attempt failed because the target device did not respond.");
        break;
    default:
        errorStr = CommTr::tr("RS485 debugging attempt failed due to unknown error: %1.").arg(QString::number(errorCode));
        break;
    }
    PRINT_ERROR(errorStr);
    emit CommunicationEngine::instance()->signal_needMainWidgetWarning(errorStr);
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void ControllerSystemConfigPrivate::readRs485Config(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool readToolIsSuccess = false, readRcIsSuccess = false, read485ConfigIsSuccess = false;

    std::string ans;
    int ret = _IRCConfig->readCobotToolRs485Config(ans);
#ifndef INOCOBOTTP_MSVC_QT5
    qDebug() << ans;
#endif
    QString errorStr = "";
    ToolIO_RS485_Config controllerType;
    ToolIO_RS485_Config tool;
    if (ret != ERROR_OK) {
        errorStr = CommTr::tr("Failed to read RS485 configuration");
    } else {
        QJsonObject object = QJsonDocument::fromJson(ans.c_str()).object();
        QJsonObject cObj = object["RC485"].toObject();
        QJsonObject tObj = object["Tool485"].toObject();
        controllerType.type = Controller_RS485;
        controllerType.baudrate = cObj["Baudrate"].toInt();
        controllerType.checkWay = cObj["CheckWay"].toVariant().value<DataVerificationMethod>();
        controllerType.dataBit = cObj["DataBit"].toInt();
        controllerType.stopBit = cObj["StopBit"].toInt();

        tool.type = TOOLIO_RS485;
        tool.baudrate = tObj["Baudrate"].toInt();
        tool.checkWay = tObj["CheckWay"].toVariant().value<DataVerificationMethod>();
        tool.dataBit = tObj["DataBit"].toInt();
        tool.stopBit = tObj["StopBit"].toInt();
        read485ConfigIsSuccess = true;
    }
    ans.clear();
    ToolIO_RS485OrAD_ReuseMode model = ReuseMode_Unknown;
    ret = _IRCConfig->readCobotToolRs485ReuseMode(ans);
    if (ret != ERROR_OK) {
        combinErrorStr(errorStr, CommTr::tr("Failed to read GPIO reuse model."));
    } else {
        QJsonObject object = QJsonDocument::fromJson(ans.c_str()).object();
        model = object["GPIOMode"].toVariant().value<ToolIO_RS485OrAD_ReuseMode>();
        readToolIsSuccess = true;
    }

    bool state = false;
    ret = _IRCConfig->readCobotRcRs485State(state);
    if (ret != ERROR_OK) {
        combinErrorStr(errorStr, CommTr::tr("Failed to read controller RS485 status."));
    } else {
        readRcIsSuccess = true;
    }

    emit CommunicationEngine::instance()->signal_getRS485Result(cmd->m_object,
                                                                read485ConfigIsSuccess, controllerType, tool,
                                                                readToolIsSuccess, model,
                                                                readRcIsSuccess, state);

    if (!errorStr.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetError(errorStr, false);
        return;
    }
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void ControllerSystemConfigPrivate::startRestoreFactory(AbstractCmd *cmd)
{
    int nMark1 = 0;
    int nRet = _IRCConfig->readFileSaveFlag(nMark1);
    if (nRet != ERR_OK || (nMark1 >= 1 && nMark1 <= 10)) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("System busy, please try again later."));
        return;
    }
    // 检查2
    int nMark2 = 0;
    nRet = _IRCConfig->readDefValueMark(nMark2);
    if (nRet != ERR_OK || (nMark2 == 1 || nMark2 == 2)) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("System busy, please try again later."));
        return;
    }

    // 发送恢复出厂设置命令
    nRet = _IRCConfig->writeDefValueMark(1);
    if (nRet != ERR_OK) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("Failed to send command."));
        return;
    }
    emit CommunicationEngine::instance()->signal_handleSystemBackupAndLoad(cmd->m_object, cmd->m_cmdType, QVariant(), true, "");
}

void ControllerSystemConfigPrivate::readRestoreFactoryState(AbstractCmd *cmd)
{
    int nMark = 0;
    int nRet = _IRCConfig->readDefValueMark(nMark);
    QString tips = ControllerSystemConfigTr::tr("Communictaion with controller failed.");
    InoTaskState state = Task_Falid;
    if (nRet == ERR_OK) {
        switch (nMark) {
        case 1:
        case 2:
            state = Task_InProcess;
            tips = ControllerSystemConfigTr::tr("In progress, please do not turn off the power.");
            break;
        case 0:
            state = Task_FineshedSuccess;
            tips = ControllerSystemConfigTr::tr("Factory reset successful, please restart the controller.");
            break;
        default:
            break;
        }
    }
    qDebug()<<__FUNCTION__<<nMark<<nRet;
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
        cmd->m_object, cmd->m_cmdType, 0, state, tips);
}

QString ControllerSystemConfigPrivate::getErrorStr(int code)
{
    QString ans;
    switch (code) {
    case 60: ans = ControllerSystemConfigTr::tr("Unknown error."); break;
    case 61: ans = ControllerSystemConfigTr::tr("Configuration file backup complete."); break;
    case 62: ans = ControllerSystemConfigTr::tr("No USB device inserted into the controller detected."); break;
    case 63: ans = ControllerSystemConfigTr::tr("Backup configuration area on controller USB device not found."); break;
    case 64: ans = ControllerSystemConfigTr::tr("Copy failed during backup process."); break;
    case 65: ans = ControllerSystemConfigTr::tr("Parameter file processing failed."); break;
    // 加载配置文件
    case 70: ans = ControllerSystemConfigTr::tr("Unknown error."); break;
    case 71: ans = ControllerSystemConfigTr::tr("Successfully loaded configuration file, please restart the controller."); break;
    case 72: ans = ControllerSystemConfigTr::tr("No USB device inserted into the controller detected."); break;
    case 73: ans = ControllerSystemConfigTr::tr("Configuration file named robotcfg.cfg.bk not found on controller USB device."); break;
    case 74: ans = ControllerSystemConfigTr::tr("Configuration file packages not recognized or parsing error."); break;
    case 75: ans = ControllerSystemConfigTr::tr("Copy failed during loading process."); break;
    case 76: ans = ControllerSystemConfigTr::tr("Robot model mismatch, failed to load configuration file."); break;
    case 77: ans = ControllerSystemConfigTr::tr("Failed to load InoRobShop configuration."); break;
    case 78: ans = ControllerSystemConfigTr::tr("Parameter file processing failed."); break;
    // // 备份程序文件
    // case 80: ans = CommTr::tr("未知错误"); break;
    // case 81: ans = CommTr::tr("成功备份程序文件"); break;
    // case 82: ans = CommTr::tr("没有识别到控制器USB设备插入"); break;
    // case 83: ans = CommTr::tr("未找到控制器USB设备上的备份程序区"); break;
    // case 84: ans = CommTr::tr("备份过程中拷贝失败"); break;
    // // 加载程序文件
    // case 90: ans = CommTr::tr("未知错误"); break;
    // case 91: ans = CommTr::tr("成功加载程序文件,请重新上电!"); break;
    // case 92: ans = CommTr::tr("没有识别到控制器USB设备插入"); break;
    // case 93: ans = CommTr::tr("未找到控制器USB设备上的程序文件"); break;
    // case 94: ans = CommTr::tr("加载过程中拷贝失败"); break;
    // case 95: ans = CommTr::tr("控制器版本过低（需S01.15或以上版本）"); break;
    // 通信异常
    case -1: ans = ControllerSystemConfigTr::tr("Failed to read current status due to communication error."); break;
    // 结束标示
    case 0: ans = ""; break;
    default: ans = ControllerSystemConfigTr::tr("Processing, please wait..."); break;
    }
    return ans;
}

void ControllerSystemConfigPrivate::startConfigFilesStateToUsb(AbstractCmd *cmd)
{
    startConfigFileOperation(6, cmd);
}

void ControllerSystemConfigPrivate::readConfigFilesBackupStateToUsb(AbstractCmd *cmd)
{
    readConfigFileToUsbOperationState(cmd);
}

void ControllerSystemConfigPrivate::startLoadConfigFilesFromUsb(AbstractCmd *cmd)
{
    startConfigFileOperation(7, cmd);
}

void ControllerSystemConfigPrivate::readLoadConfigFilesStateFromUsb(AbstractCmd *cmd)
{
    readConfigFileToUsbOperationState(cmd);
}

void ControllerSystemConfigPrivate::startConfigFileOperation(int funCode, AbstractCmd *cmd)
{
    // 检查USB是否连接
    if (_IMaintenance->checkControllerUSB() == false) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("The controller USB is not ready yet and the operation is invalid."));
        return;
    }
    // 读取状态
    int _funMark = funCode;
    int nMark = 0;
    int nRet = _IRCConfig->readFileSaveFlag(nMark);
    if (nRet != ERR_OK) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("System busy, please try again later."));
        return;
    }
    // 检查状态是否为进行中
    if (nMark == 2) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("System busy, please try again later."));
        return;
    }
    if (nMark >= 1 && nMark <= 10) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("System busy, please try again later."));
        return;
    }

    // 发送指令
    nRet = _IRCConfig->writeFileSaveFlag(_funMark);
    qDebug() << "nRet is" << nRet << cmd->m_cmdType << funCode << _funMark;
    if (nRet != ERR_OK) {
        emit MIANWARNING(ControllerSystemConfigTr::tr("Communictaion with controller failed."));
        return;
    }
    m_lastControllerBackUpFileWithUsbHasFinish = false;
    emit CommunicationEngine::instance()->signal_handleSystemBackupAndLoad(cmd->m_object, cmd->m_cmdType, QVariant(), true, "");
}

void ControllerSystemConfigPrivate::readConfigFileToUsbOperationState(AbstractCmd *cmd)
{
    if(m_lastControllerBackUpFileWithUsbHasFinish)
        return;
    int nMark = 0;
    int nRet = _IRCConfig->readFileSaveFlag(nMark);
    QString tips = getErrorStr(nMark);
    InoTaskState state = Task_Falid;
    if (nRet == ERR_OK) {
        switch (nMark) {
        case 2:
            state = Task_InProcess;
            break;
        case 61:
            state = Task_FineshedSuccess;
            m_lastControllerBackUpFileWithUsbHasFinish = true;
            break;
        default:
            m_lastControllerBackUpFileWithUsbHasFinish = true;
            break;
        }
    }else{
        m_lastControllerBackUpFileWithUsbHasFinish = true;
    }
    qDebug() << "state is" << state << cmd->m_cmdType << tips;
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
        cmd->m_object, cmd->m_cmdType, 0, state, tips);
}

void ControllerSystemConfigPrivate::startExportConfigFileToLocal(AbstractCmd *cmd)
{
    bool ans = _IRCConfig->checkSystemIsReadyForBackupConfigFile();
    if (!ans)
        return;
    int ret = _IRCConfig->exportConfigFileToLocal();
    if (ret != ERROR_OK) {
        return;
    }
    m_hasDownLoadConfigFile = false;
    timeForExportFile = QDateTime::currentDateTime();
    emit CommunicationEngine::instance()->signal_handleSystemBackupAndLoad(cmd->m_object, cmd->m_cmdType, "", true, "");
}

void ControllerSystemConfigPrivate::startImportConfigFileFromLocal(AbstractCmd *cmd)
{
    bool ans = _IRCConfig->checkSystemIsReadyForBackupConfigFile();
    if (!ans)
        return;

    UDF udf;
    auto [path] = BIND(cmd, QString);
    ans = udf.uploadFile("./Exchange/robotcfg.cfg.bk", path.toStdString());
    if (!ans){
        emit MIANWARNING(ControllerSystemConfigTr::tr("Failed to upload config file to the controller."));
        return;
    }

    int ret = _IRCConfig->importConfigFileToController();
    if (ret != ERROR_OK) {
        return;
    }
    m_hasfinishLastImport = false;
    timeForImportFile = QDateTime::currentDateTime();
    emit CommunicationEngine::instance()->signal_handleSystemBackupAndLoad(cmd->m_object, cmd->m_cmdType, "", true, "");
}

void ControllerSystemConfigPrivate::readExportConfigFileOperateStatusToLocal(AbstractCmd *cmd)
{
    if (m_hasDownLoadConfigFile)
        return;
    InoTaskState state = Task_Falid;
    QString errorStr;
    if (timeForExportFile.secsTo(QDateTime::currentDateTime()) < 180) {
        int flag = 0;
        int ret = _IRCConfig->checkConfigFileStatus(flag);
        if (ret != ERROR_OK) {
            state = Task_Falid;
            m_hasDownLoadConfigFile = true;
        } else {
            if (flag == 1)
                state = Task_FineshedSuccess;
            else if (flag == 100)
                state = Task_InProcess;
            else
                m_hasDownLoadConfigFile = true;
        }
        if (!m_hasDownLoadConfigFile && state == Task_FineshedSuccess) {
            UDF udf;
            auto [path] = BIND(cmd, QString);
            bool ans = udf.downloadFile("./Exchange/robotcfg.cfg.bk", path.toStdString());
            if (!ans)
                state = Task_Falid;
            m_hasDownLoadConfigFile = true;
        }
    } else {
        errorStr = ControllerSystemConfigTr::tr("Operation timeout.");
        m_hasDownLoadConfigFile = true;
    }
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
        cmd->m_object, cmd->m_cmdType, 0, state, errorStr);
}

void ControllerSystemConfigPrivate::readImportConfigFileOperateStatusFromLocal(AbstractCmd *cmd)
{
    if (m_hasfinishLastImport)
        return;
    InoTaskState state = Task_Falid;
    QString tips;
    if (timeForImportFile.secsTo(QDateTime::currentDateTime()) < 180) {
        int flag = 0;
        int ret = _IRCConfig->checkConfigFileStatus(flag);
        if (ret != ERROR_OK) {
            state = Task_Falid;
            m_hasfinishLastImport = true;
        } else {
            if (flag == 1) {
                tips = ControllerSystemConfigTr::tr("Successfully loaded configuration file, please restart the controller.");
                state = Task_FineshedSuccess;
                m_hasfinishLastImport = true;
            } else if (flag == 100) {
                state = Task_InProcess;
            } else {
                m_hasfinishLastImport = true;
            }
        }
    } else {
        m_hasfinishLastImport = true;
        tips = ControllerSystemConfigTr::tr("Operation timeout.");
    }
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
        cmd->m_object, cmd->m_cmdType, 0, state, tips);
}

void ControllerSystemConfigPrivate::setModelLayerLanguage(AbstractCmd *cmd)
{
    auto [languge] = BIND(cmd, QString);
    LOG_INFO(QString("setModelLayerLanguage(AbstractCmd *cmd) %1").arg(languge));
    ILanguage *language = gs_Workstation.GetObject()->getLanguage();
    QString code = "EN";
    if (languge == "en_US")
        code = "EN";
    else
        code = languge.toUpper().replace('_', '-');
    // if(language->ChangeCurrentLanguage(code.toStdString()))
    //     SHOW_MSG("TP language load success.");
    bool ans = language->ChangeCurrentLanguage(code.toStdString());
    // static bool once = true;
    // if(once){
    //     emit CommunicationEngine::instance()->siganl_modelLayerHasLoadLanguage(ans);
    //     once = false;
    // }
    emit CommunicationEngine::instance()->siganl_modelLayerHasLoadLanguage(ans);
    LOG_INFO(QString("Load language package is %1").arg(ans?"true":"false"));
}

int ControllerSystemConfigPrivate::autoRecordPoint(int status)
{
    int iRet = _IControl->autoRecordPoint(status);
    LOG_INFO(QString("[autoRecordPoint]ret = %1, status = %2")
                 .arg(QString::number(iRet), QString::number(status)));
    return iRet;
}

int ControllerSystemConfigPrivate::getFirstBootStatus(bool &status)
{
    int iRet = _IControl->getFirstBootStatus(status);
    LOG_INFO(QString("[getFirstBootStatus]ret = %1, status = %2")
                 .arg(QString::number(iRet), QString::number(status)));
    return iRet;
}

void ControllerSystemConfigPrivate::ControllerSystemConfigPrivate::setControllerLanguage(AbstractCmd *cmd)
{
    auto [code] = BIND(cmd, QString);
    ILanguage *language = gs_Workstation.GetObject()->getLanguage();
    QString mapCode = "EN";
    if (code == "en_US")
        mapCode = "EN";
    else
        mapCode = code.toUpper().replace('_', '-');
    language->SetControllerLanguage(mapCode.toStdString());
}

void ControllerSystemConfigPrivate::importLanguagePackageFromLocal(AbstractCmd *cmd)
{
    auto [fileName] = BIND(cmd, QString);
    ILanguage *language = gs_Workstation.GetObject()->getLanguage();
    string code;
    wstring name;
    if (language->LanguagePackageValid(fileName.toStdString(), code, name) == LANGUAGE_PACKAGE_VALID_SUCCESS) {
        bool success = true;
        if (language->LanguagePackageImport(fileName.toStdString(), code, name)) {
            if (!DatabaseLocal::setLanguageIsInFactoryState(false)) {
                emit MWARNING(ControllerSystemConfigTr::tr("Failed to write database."));
            }
            QString directoryPath = ABSOLUTE_SHARE_PATH + "/../studio/Language/" + QString::fromStdString(code);
            QStringList filters;
            filters << "*.qm";
            QDir directory(directoryPath);
            QStringList fileList = directory.entryList(filters, QDir::Files);
            foreach (const QString &file, fileList) {
                QString src = QString("%1/%2").arg(directoryPath, file);
                QString dest = QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, TRANSLATION_FILE_NAME, file);
                if (QFile::exists(dest))
                    success &= QFile::remove(dest);
                success &= QFile::copy(src, dest);
                success &= QFile::remove(src);
                if (!success) {
                    LOG_ERROR("copy falied " + src + " " + dest);
                }
            }
            if (success) {
                SHOW_MSG(ControllerSystemConfigTr::tr("Language pack imported successfully."));
            } else {
                emit MWARNING(ControllerSystemConfigTr::tr("Failed to copy language files."));
            }
        } else{
            success = false;
            emit MWARNING(ControllerSystemConfigTr::tr("Failed to import language pack."));
        }
        emit CommunicationEngine::instance()->siganl_loadLanguageAns(cmd->m_cmdType, success);
    } else {
        emit MWARNING(ControllerSystemConfigTr::tr("Failed to import language pack for file is invalid."));
    }
}

void ControllerSystemConfigPrivate::importLanguagePackageFromController(AbstractCmd *cmd)
{
    ILanguage *language = gs_Workstation.GetObject()->getLanguage();
    bool success = language->synchronizeFromController() == ERROR_OK;
    if (success) {
        QString directoryPath = ABSOLUTE_SHARE_PATH + "/../studio/Language/";
        QStringList fileList;
        if (!FileUtils::recursiveFolderForFileList(directoryPath, fileList)) {
            success = false;
            LOG_ERROR("recursiveFolderForFileList failed " + directoryPath);
        } else {
            foreach (const QString &file, fileList) {
                QFileInfo info(file);
                if (info.isFile() && info.suffix() == "qm") {
                    QString dest = QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, TRANSLATION_FILE_NAME, info.fileName());
                    if (QFile::exists(dest)) {
                        if (!QFile::remove(dest)) {
                            success = false;
                            LOG_ERROR("remove failed" + dest);
                            continue;
                        }
                    }
                    if (!QFile::copy(file, dest)) {
                        success = false;
                        LOG_ERROR("copy failed" + file + "  " + dest);
                        continue;
                    }
                    if (!QFile::remove(file)) {
                        LOG_ERROR("remove failed" + file);
                    }
                }
            }
        }
    }

    if (success) {
        SHOW_MSG(ControllerSystemConfigTr::tr("Language pack synced successfully."));
        emit CommunicationEngine::instance()->signal_ProcessBarFormBaseOnTimerEvent(
            RobotEventInfo(RobotEventInfo::UserEvent_ImportLanguagePackageFinish));
    } else {
        emit CommunicationEngine::instance()->signal_ProcessBarFormBaseOnTimerEvent(
            RobotEventInfo(RobotEventInfo::UserEvent_Error,
                           ControllerSystemConfigTr::tr("Failed to sync language pack.")));
    }
    emit CommunicationEngine::instance()->siganl_loadLanguageAns(cmd->m_cmdType, success);
}

void ControllerSystemConfigPrivate::importLanguagePackageForController(AbstractCmd *cmd)
{
    auto [fileName] = BIND(cmd, QString);
    ILanguage *language = gs_Workstation.GetObject()->getLanguage();
    bool success = language->importLanguagePackage2Controller(fileName.toStdString()) == ERROR_OK;
    if (success) {
        QString directoryPath = ABSOLUTE_SHARE_PATH + "/../studio/Language/";
        QStringList filters;
        filters << "*.qm";
        QDir directory(directoryPath);
        QStringList fileList = directory.entryList(filters, QDir::Files);
        foreach (const QString &file, fileList) {
            QString src = QString("%1/%2").arg(directoryPath, file);
            QString dest = QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, TRANSLATION_FILE_NAME, file);
            if (QFile::exists(dest)) {
                if (!QFile::remove(dest)) {
                    LOG_ERROR("remove failed" + dest);
                    success = false;
                    continue;
                }
            }
            if (!QFile::copy(src, dest)) {
                LOG_ERROR("copy failed " + src + " to " + dest);
                success = false;
                continue;
            }
            if (!QFile::remove(src)) {
                LOG_ERROR("remove failed " + src);
                continue;
            }
        }
    }
    if (success) {
        SHOW_MSG(ControllerSystemConfigTr::tr("Import successful."));
        emit CommunicationEngine::instance()->signal_ProcessBarFormBaseOnTimerEvent(
            RobotEventInfo(RobotEventInfo::UserEvent_ImportLanguagePackageFinish));
    } else {
        emit CommunicationEngine::instance()->signal_ProcessBarFormBaseOnTimerEvent(
            RobotEventInfo(RobotEventInfo::UserEvent_Error,
                           ControllerSystemConfigTr::tr("Failed to import language to the controller.")));
    }
}
}

ControllerSystemConfig::ControllerSystemConfig()
{
    d = new Internal::ControllerSystemConfigPrivate(this);
}

ControllerSystemConfig::~ControllerSystemConfig()
{
    delete d;
    d = nullptr;
}

int ControllerSystemConfig::saveEthConfig(const InoControllerEthCfg &EthCfg)
{
    return d->saveEthConfig(EthCfg);
}

void ControllerSystemConfig::getEthConfig(AbstractCmd *cmd)
{
    d->getEthConfig(cmd);
}

int ControllerSystemConfig::readCommonNetStatusInfo(QList<InoCommonNetStatus> &data, unsigned char &serverState)
{
    return d->readCommonNetStatusInfo(data, serverState);
}

void ControllerSystemConfig::writeEthCommonOperation(AbstractCmd *cmd)
{
    return d->writeEthCommonOperation(cmd);
}

int ControllerSystemConfig::readVisionMode(unsigned short &VisionMode, unsigned short &serverPort)
{
    return d->readVisionMode(VisionMode, serverPort);
}

int ControllerSystemConfig::saveVisionMode(unsigned short visionMode, unsigned short port)
{
    return d->saveVisionMode(visionMode, port);
}

void ControllerSystemConfig::saveNewPort(AbstractCmd *cmd)
{
    d->saveNewPort(cmd);
}

void ControllerSystemConfig::getVersionInfo(AbstractCmd *cmd)
{
    d->getVersionInfo(cmd);
}

void ControllerSystemConfig::isNeedTimeSynToController()
{
    d->isNeedTimeSynToController();
}

void ControllerSystemConfig::setControllerTime(AbstractCmd *cmd)
{
    d->setControllerTime(cmd);
}

int ControllerSystemConfig::delDir(const std::string &dir)
{
    return d->delDir(dir);
}

int ControllerSystemConfig::createDir(const std::string &dir)
{
    return d->createDir(dir);
}

int ControllerSystemConfig::systemUpgrade(bool isUpdateBsp)
{
    return d->systemUpgrade(isUpdateBsp);
}

int ControllerSystemConfig::readSystemUpdateInfo(CobotSystemUpdateInfo &info)
{
    return d->readSystemUpdateInfo(info);
}

void ControllerSystemConfig::readRs485Config(AbstractCmd *cmd)
{
    d->readRs485Config(cmd);
}

void ControllerSystemConfig::writeToolReuseModel(AbstractCmd *cmd)
{
    d->writeToolReuseModel(cmd);
}

void ControllerSystemConfig::writeRs485Config(AbstractCmd *cmd)
{
    d->writeRs485Config(cmd);
}

void ControllerSystemConfig::writeRs485Debugging(AbstractCmd *cmd)
{
    d->writeRs485Debugging(cmd);
}

void ControllerSystemConfig::startRestoreFactory(AbstractCmd *cmd)
{
    d->startRestoreFactory(cmd);
}

void ControllerSystemConfig::readRestoreFactoryState(AbstractCmd *cmd)
{
    d->readRestoreFactoryState(cmd);
}

void ControllerSystemConfig::startConfigFilesStateToUsb(AbstractCmd *cmd)
{
    d->startConfigFilesStateToUsb(cmd);
}

void ControllerSystemConfig::readConfigFilesBackupStateToUsb(AbstractCmd *cmd)
{
    d->readConfigFilesBackupStateToUsb(cmd);
}

void ControllerSystemConfig::startLoadConfigFilesFromUsb(AbstractCmd *cmd)
{
    d->startLoadConfigFilesFromUsb(cmd);
}

void ControllerSystemConfig::readLoadConfigFilesStateFromUsb(AbstractCmd *cmd)
{
    d->readLoadConfigFilesStateFromUsb(cmd);
}

void ControllerSystemConfig::startExportConfigFileToLocal(AbstractCmd *cmd)
{
    d->startExportConfigFileToLocal(cmd);
}

void ControllerSystemConfig::startImportConfigFileFromLocal(AbstractCmd *cmd)
{
    d->startImportConfigFileFromLocal(cmd);
}

void ControllerSystemConfig::readExportConfigFileOperateStatusToLocal(AbstractCmd *cmd)
{
    d->readExportConfigFileOperateStatusToLocal(cmd);
}

void ControllerSystemConfig::readImportConfigFileOperateStatusFromLocal(AbstractCmd *cmd)
{
    d->readImportConfigFileOperateStatusFromLocal(cmd);
}

void ControllerSystemConfig::setModelLayerLanguage(AbstractCmd *cmd)
{
    d->setModelLayerLanguage(cmd);
}

void ControllerSystemConfig::setControllerLanguage(AbstractCmd *cmd)
{
    d->setControllerLanguage(cmd);
}

void ControllerSystemConfig::importLanguagePackageForController(AbstractCmd *cmd)
{
    d->importLanguagePackageForController(cmd);
}

void ControllerSystemConfig::importLanguagePackageFromLocal(AbstractCmd *cmd)
{
    d->importLanguagePackageFromLocal(cmd);
}

void ControllerSystemConfig::importLanguagePackageFromController(AbstractCmd *cmd)
{
    d->importLanguagePackageFromController(cmd);
}

int ControllerSystemConfig::autoRecordPoint(int status)
{
    return d->autoRecordPoint(status);
}

int ControllerSystemConfig::getFirstBootStatus(bool &status)
{
    return d->getFirstBootStatus(status);
}
