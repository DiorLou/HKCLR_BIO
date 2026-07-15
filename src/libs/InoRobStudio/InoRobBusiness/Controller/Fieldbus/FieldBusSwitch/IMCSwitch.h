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
 * @brief MC基类
 */
class INOROBBUSINESS_CLASS IMCSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~IMCSwitch()
    {
    }

    /**
     * @brief 写入MC配置
     * @param mcActiveCfg 写入结构体
     * @return 0-成功
     */
    virtual int writeMcActivePara(McActivePara mcActiveCfg) = 0;

    /**
     * @brief 读取MC配置
     * @param mcActiveCfg 读取结构体
     * @return 0-成功
     */
    virtual int readMcActivePara(McActivePara &mcActiveCfg) = 0;

    /**
     * @brief 写入单个MC连接配置参数
     * @param connectPara 连接参数
     * @return 0-成功
     */
    virtual int writeSingleMcConnectSts(McConnectPara connectPara) = 0;

    /**
     * @brief 读取所有的MC连接配置参数
     * @param connectParas 连接参数
     * @return 0-成功
     */
    virtual int readAllMcConnectSts(McConnectPara connectParas[4]) = 0;

    /**
     * @brief 检查MC总线开关的操作权限
     * @return true-权限符合
     */
    virtual bool checkMCOperatePermission() = 0;
};
}  // namespace InoRobBusiness
