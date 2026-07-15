#include "connectioninterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"
#include "communicationengine.h"
#include "communication/communication.h"
#include "modulesutils.h"
std::string ConnectionInterface::GetConnIp()
{
    return _IConnection->GetIp();
}

quint16 ConnectionInterface::GetConnPort()
{
    return _IConnection->GetPort();
}

void ConnectionInterface::getDeviceConnectionState(AbstractCmd *cmd)
{
    QStringList value;
    ushort eth0State = 0, eth1State = 0;
    int16u moduleCommState[MODULE_NUM];
    _IMonitor->GetModuleCommState(moduleCommState);
    eth0State = moduleCommState[0];
    eth1State = moduleCommState[1];

    if (eth0State == 0 && eth1State == 0) {
        for (int i = 0; i < 6; ++i)
            value << ConnectionInterfaceTr::tr("Unknown state", "No punctuation required");
        emit CommunicationEngine::instance()->signal_getDeviceConnectionResult(cmd->m_object, value);
        return;
    }

    ControllerEthCfg cfg;
    int ret = _IRCConfig->getEthConfig(cfg);
    if (ret != ERROR_OK) {
        MWARNING(ConnectionInterfaceTr::tr("Failed to get controll IP address."));
        for (int i = 0; i < 6; ++i)
            value << ConnectionInterfaceTr::tr("Unknown state", "No punctuation required");
        emit CommunicationEngine::instance()->signal_getDeviceConnectionResult(cmd->m_object, value);
        return;
    }

    switch (moduleCommState[0]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Disconnected");
        break;
    case 1:
        value << ((cfg.strcEth0.strDHCP == "1" ?
                       ConnectionInterfaceTr::tr("Dynamic IP:") :
                       ConnectionInterfaceTr::tr("Static IP:"))
                  + " " + cfg.strcEth0.strIP.c_str());
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Disabled");
        break;
    case 3:
        value << ConnectionInterfaceTr::tr("Unknown state");
        break;
    }
    switch (moduleCommState[1]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Disconnected");
        break;
    case 1:
        value << ((cfg.strcEth1.strDHCP == "1" ?
                       ConnectionInterfaceTr::tr("Dynamic IP:") :
                       ConnectionInterfaceTr::tr("Static IP:"))
                  + " " + cfg.strcEth1.strIP.c_str());
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Disabled");
        break;
    case 3:
        value << ConnectionInterfaceTr::tr("Unknown state");
        break;
    }

    switch (moduleCommState[2]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Device not connected", "No punctuation required");
        break;
    case 1:
        value << ConnectionInterfaceTr::tr("Connected and successfully mounted", "No punctuation required");
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Connected but failed to mount", "No punctuation required");
        break;
    default:
        value << ConnectionInterfaceTr::tr("Unknown state", "No punctuation required");
        break;
    }
    switch (moduleCommState[3]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Device not connected", "No punctuation required");
        break;
    case 1:
        value << ConnectionInterfaceTr::tr("Connected and successfully mounted", "No punctuation required");
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Connected but failed to mount", "No punctuation required");
        break;
    case 3:
        value << ConnectionInterfaceTr::tr("Storage card format error", "No punctuation required");
        break;
    default:
        value << ConnectionInterfaceTr::tr("Unknown state", "No punctuation required");
        break;
    }
    switch (moduleCommState[4]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Communication is normal", "No punctuation required");
        break;
    case 1:
        value << ConnectionInterfaceTr::tr("Slave disconnected", "No punctuation required");
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Device not mounted", "No punctuation required");
        break;
    case 3:
        value << ConnectionInterfaceTr::tr("Non-EtherCAT device connected", "No punctuation required");
        break;
    case 4:
        value << ConnectionInterfaceTr::tr("Disabled", "No punctuation required");
        break;
    default:
        value << ConnectionInterfaceTr::tr("Unknown state", "No punctuation required");
        break;
    }
    switch (moduleCommState[5]) {
    case 0:
        value << ConnectionInterfaceTr::tr("Communication is normal", "No punctuation required");
        break;
    case 1:
        value << ConnectionInterfaceTr::tr("Slave disconnected", "No punctuation required");
        break;
    case 2:
        value << ConnectionInterfaceTr::tr("Device not mounted", "No punctuation required");
        break;
    case 3:
        value << ConnectionInterfaceTr::tr("Non-IR-Link device connected", "No punctuation required");
        break;
    case 4:
        value << ConnectionInterfaceTr::tr("Disabled", "No punctuation required");
        break;
    case 5:
        value << ConnectionInterfaceTr::tr("Device not configured", "No punctuation required");
        break;
    default:
        value << ConnectionInterfaceTr::tr("Unknown state");
        break;
    }
    emit CommunicationEngine::instance()->signal_getDeviceConnectionResult(cmd->m_object, value);
}

void ConnectionInterface::getModbusConnectionState(AbstractCmd *cmd)
{
    bool ok = _IResource->updateModbusConnectStatus();
    if (!ok)
        return;

    InoRobBusiness::ModbusConnectStatus status = _IResource->getModbusConnectStatus();
    QStringList labelAns;
    switch (status.modbusRtuCS.status) {
    case 1:
        labelAns << ConnectionInterfaceTr::tr("Slave activated");
        break;
    case 2:
        labelAns << ConnectionInterfaceTr::tr("Master activated");
        break;
    default:
        labelAns << ConnectionInterfaceTr::tr("Not activated");
        break;
    }
    switch (status.modbusTcpCS.status) {
    case 1:
        labelAns << ConnectionInterfaceTr::tr("Slave activated");
        break;
    case 2:
        labelAns << ConnectionInterfaceTr::tr("Master activated");
        break;
    default:
        labelAns << ConnectionInterfaceTr::tr("Not activated");
        break;
    }
    bool activeRtu = (status.modbusRtuCS.status == 1 || status.modbusRtuCS.status == 2);
    bool activeTcp = (status.modbusTcpCS.status == 1 || status.modbusTcpCS.status == 2);

    labelAns << QString::number(status.modbusTcpCS.port);
    QList<QStringList> tableAns;
    tableAns << QStringList() << QStringList() << QStringList();
    for (int i = 0; i < TCP_CLIENT_NUM; i++) {
        if (status.modbusTcpConnectFlag[i] == 1) {
            tableAns[0] << (char *)(status.modbusTcpClientIP[i]);
            tableAns[1] << QString::number(status.modbusTcpClientPort[i]);
            tableAns[2] << ConnectionInterfaceTr::tr("Connected");
        } else {
            tableAns[0] << "----";
            tableAns[1] << "----";
            tableAns[2] << ConnectionInterfaceTr::tr("Disconnected");
        }
    }
    char busInstall[4];
    _IMonitor->GetBusInstall(busInstall);
    bool isHasEthercat = (busInstall[0]>>0) & 0x01;
    emit CommunicationEngine::instance()->signal_getModbusConnectionResult(cmd->m_object,
                                                                            activeRtu,
                                                                            activeTcp,
                                                                            status.modbusAddrType ==1,
                                                                            status.modbusAddrType ==1 && isHasEthercat ,
                                                                            labelAns,
                                                                            tableAns);
}

void ConnectionInterface::getMCConnectionState(AbstractCmd *cmd)
{
    bool ok = _IResource->updateMCStatus();
    if (!ok)
        return;
    bool _mcActiveStatus = _IResource->getMCActiveStatus();
    std::array<InoRobBusiness::MCConnectStatus, MC_CONNECT_NUM>
        _mcConnectStatus = _IResource->getMCConnectStatus();
    QList<QStringList> ans;
    ans << QStringList() << QStringList() << QStringList();
    for (int i = 0; i < MC_CONNECT_NUM; i++) {
        QString ip((char *)_mcConnectStatus[i].serverIP);
        if (!ip.isEmpty())
            ans[0] << ip + " : " + QString::number(_mcConnectStatus[i].port);
        else
            ans[0] << "----";
        ans[1] << (_mcConnectStatus[i].connect == 1 ? ConnectionInterfaceTr::tr("Connected") : ConnectionInterfaceTr::tr("Disconnected"));
        ans[2] << (_mcConnectStatus[i].autoReconnect == 1 ? ConnectionInterfaceTr::tr("Yes") : ConnectionInterfaceTr::tr("No"));
    }

    emit CommunicationEngine::instance()->signal_getMCConnectionResult(
        cmd->m_object,
        _mcActiveStatus,
        _mcActiveStatus ? ConnectionInterfaceTr::tr("Active") : ConnectionInterfaceTr::tr("Inactive"),
        ans);
}

void ConnectionInterface::getProfinetConnectionState(AbstractCmd *cmd)
{
    bool ok = _IResource->updateProfinetConnectStatus();
    if (!ok)
        return;
    QStringList ans;
    InoRobBusiness::ProfinetConnectStatus status = _IResource->getProfinetConnectStatus();
    ans << (status.activeStatus ? ConnectionInterfaceTr::tr("Active") : ConnectionInterfaceTr::tr("Inactive"));
    if (status.activeStatus) {
        ans << QString((char *)status.ip);
        ans << QString((char *)status.defaultGateWay);
        ans << QString((char *)status.macAddress);
        ans << QString::number(status.version);
    } else {
        ans << "----";
        ans << "----";
        ans << "----";
        ans << "----";
    }
    ans << (status.connectStatus ? ConnectionInterfaceTr::tr("Connected") : ConnectionInterfaceTr::tr("Disconnected"));
    emit CommunicationEngine::instance()->signal_getProfinetConnectionResult(
        cmd->m_object,
        status.activeStatus,
        status.connectStatus,
        ans);
}

void ConnectionInterface::getEtherNetIpConnectionState(AbstractCmd *cmd)
{
    _IResource->updateEthernetIPStatus();
    InoRobBusiness::EthernetIPStatus status = _IResource->getEthernetIPStatus();
    emit CommunicationEngine::instance()->signal_getEtherNetIpConnectionResult(
        cmd->m_object,
        status.active,
        status.active?ConnectionInterfaceTr::tr("Active") : ConnectionInterfaceTr::tr("Inactive"),
        QString::number(status.slavePort),
        status.connect,
        status.connect ? QString("%1 : %2").arg(QString((char*)status.masterIP),
                                                QString::number(status.masterPort))
                       : ConnectionInterfaceTr::tr("Disconnected"));
}

void ConnectionInterface::getEtherCatIpConnectionState(AbstractCmd *cmd)
{
    _IResource->updateEtherCatStatus();
    InoRobBusiness::EtherCATStatus status = _IResource->getEtherCatStatus();
    QStringList ans;
    ans<<(status.active?ConnectionInterfaceTr::tr("Active") : ConnectionInterfaceTr::tr("Inactive"));
    ans<<(status.connect?ConnectionInterfaceTr::tr("Connected") : ConnectionInterfaceTr::tr("Disconnected"));
    emit CommunicationEngine::instance()->signal_getEtherCatConnectionResult(
        cmd->m_object,
        status.active,
        status.connect,
        ans);
}

void ConnectionInterface::SetIsHeartbeat(bool isHeartbeat)
{
    _IConnection->SetIsHeartbeat(isHeartbeat);
}
