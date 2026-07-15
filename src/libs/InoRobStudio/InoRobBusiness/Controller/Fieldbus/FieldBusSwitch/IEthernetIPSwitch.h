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
 * @brief EthernetIP基类
 */
class INOROBBUSINESS_CLASS IEthernetIPSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~IEthernetIPSwitch()
    {
    }

    /**
     * @brief 写入EthernetIp配置
     * @param eipConfig 写入结构体
     * @return 0-成功
     */
    virtual int writeEthernetIpConfig(EthernetIpPara eipConfig) = 0;

    /**
     * @brief 读取EthernetIp状态
     * @param eipPara 读取结构体
     * @return 0-成功
     */
    virtual int readEthernetIpConnStatus(EthernetIpSts &eipPara) = 0;

    /**
     * @brief 设置EIP从站管理状态
     * @param slaveIndex
     * @param isSupportManage
     * @param manageState
     * @return
     */
    virtual int setEIPManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState) = 0;

    /**
     * @brief 获取EIP从站管理状态
     * @param slaveManageState
     * @return
     */
    virtual int getEIPManageState(EIPSlaveManageState &slaveManageState) = 0;

    /**
     * @brief 刷新从站状态 仅用于示教器端
     * @return
     */
    virtual int refreshEIPSlaveState() = 0;

    /**
     * @brief 检查EthernetIP总线开关的操作权限
     * @return true-权限符合
     */
    virtual bool checkEthernetIPOperatePermission() = 0;

    /**
     * @brief 检查EthernetIP总线保存权限
     * @return true-权限符合
     */
    virtual bool checkSaveEthernetIPPermission() = 0;
};
}  // namespace InoRobBusiness
