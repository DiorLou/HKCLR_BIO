#pragma once
#include "IModbusSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class ModbusDefaut : public IModbusSwitch
{
    Q_OBJECT
public:
    ModbusDefaut(IDataSrvBase *dataService);
    ~ModbusDefaut();

    // 写入Modbus配置
    int writeModbusConfig(MODBUS_PARA_CONFIG modbusConfig);

    // 读取Modbus的连接状态
    int readModbusConnStatus(MODBUS_CONNECT_STS &modbusPara);

    // 检查Modbus总线开关的操作权限
    bool checkModbusOperatePermission();

    // 检查保存Modbus总线配置的权限
    bool checkSaveModbusPermission();

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
};
}  // namespace InoRobBusiness
