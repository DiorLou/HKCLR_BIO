#pragma once

#include <QObject>
#include "communication_global.h"
#include "peripheral/modbusparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT ModbusInterface
{
public:
    ModbusInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int writeModbusConfig(CobotModbusParaConfig modbusConfig);
    int readModbusConnStatus(CobotModbusConnectSts &modbusPara);
    bool checkModbusOperatePermission();
    bool checkSaveModbusPermission();
};
