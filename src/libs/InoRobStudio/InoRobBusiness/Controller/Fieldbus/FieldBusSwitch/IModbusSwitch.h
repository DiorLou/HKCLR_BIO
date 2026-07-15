/****************************************************************
 * File Descrip : 总线开关
 * Author       : mzw
 ****************************************************************/
#pragma once
#include <QObject>
#include <string>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
/**
 * @brief Modbus基类
 */
class INOROBBUSINESS_CLASS IModbusSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~IModbusSwitch()
    {
    }

    /**
     * @brief 写入Modbus配置
     * @param modbusConfig 写入结构体
     * @return 0-成功
     */
    virtual int writeModbusConfig(MODBUS_PARA_CONFIG modbusConfig) = 0;

    /**
     * @brief 读取Modbus的连接状态
     * @param modbusPara 读取结构体
     * @return 0-成功
     */
    virtual int readModbusConnStatus(MODBUS_CONNECT_STS &modbusPara) = 0;

    /**
     * @brief 检查Modbus总线开关的操作权限
     * @return true-权限符合
     */
    virtual bool checkModbusOperatePermission() = 0;

    /**
     * @brief 检查保存Modbus总线配置的权限
     * @return true-权限符合
     */
    virtual bool checkSaveModbusPermission() = 0;
};
}  // namespace InoRobBusiness
