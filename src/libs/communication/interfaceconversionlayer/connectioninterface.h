#pragma once

#include "communication_global.h"
#include "QObject"
namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;

class COMMUNICATION_EXPORT ConnectionInterfaceTr : public QObject
{
    Q_OBJECT
};


/// @brief 控制器接口
class COMMUNICATION_EXPORT ConnectionInterface
{
public:
    ConnectionInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    std::string GetConnIp();
    quint16 GetConnPort();
    void getDeviceConnectionState(AbstractCmd * cmd);
    void getModbusConnectionState(AbstractCmd * cmd);
    void getMCConnectionState(AbstractCmd * cmd);
    void getProfinetConnectionState(AbstractCmd * cmd);
    void getEtherNetIpConnectionState(AbstractCmd * cmd);
    void getEtherCatIpConnectionState(AbstractCmd * cmd);

    void SetIsHeartbeat(bool isHeartbeat);
};
