#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Modbus_V1
{
#pragma region 构造与析构

private:
    IModbusSwitch *_modbusSwitch = nullptr;

public:
    Modbus_V1(IModbusSwitch *modbusSwitch);
    ~Modbus_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 写入Modbus配置
     * @param modbusConfig 写入结构体
     * @return 0-成功
     */
    int writeModbusConfig(MODBUS_PARA_CONFIG_V1 modbusConfig);

    /**
     * @brief 读取Modbus的连接状态
     * @param modbusPara 读取结构体
     * @return 0-成功
     */
    int readModbusConnStatus(MODBUS_CONNECT_STS_V1 &modbusPara);

    /**
     * @brief 检查Modbus总线开关的操作权限
     * @return true-权限符合
     */
    bool checkModbusOperatePermission();

    /**
     * @brief 检查保存Modbus总线配置的权限
     * @return true-权限符合
     */
    bool checkSaveModbusPermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
