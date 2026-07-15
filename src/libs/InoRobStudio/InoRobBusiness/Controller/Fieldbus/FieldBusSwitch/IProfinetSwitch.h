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
 * @brief Profinet基类
 */
class INOROBBUSINESS_CLASS IProfinetSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~IProfinetSwitch()
    {
    }

    /**
     * @brief 写入Profinet激活状态
     * @param pnConfig 写入结构体
     * @return 0-成功
     */
    virtual int writeProfinetConfig(PnActiveCfg pnConfig) = 0;

    /**
     * @brief 读取Profinet连接信息
     * @param pnPara 读取结构体
     * @return 0-成功
     */
    virtual int readProfinetConnSts(PnConnectSts &pnPara) = 0;

    /**
     * @brief 检查Profinet总线开关的操作权限
     * @return true-成功
     */
    virtual bool checkProfinetOperatePermission() = 0;
};
}  // namespace InoRobBusiness
