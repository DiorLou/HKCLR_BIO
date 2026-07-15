#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
#include "../../../GlobalDataTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS EthernetIP_V1
{
#pragma region 构造与析构

private:
    IEthernetIPSwitch *_ethernetIPSwitch = nullptr;

public:
    EthernetIP_V1(IEthernetIPSwitch *ethernetIPSwitch);
    ~EthernetIP_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 写入EthernetIp配置
     * @param eipConfig 写入结构体
     * @return 0-成功
     */
    int writeEthernetIpConfig(EthernetIpPara_V1 eipConfig);

    /**
     * @brief 读取EthernetIp状态
     * @param eipPara 读取结构体
     * @return 0-成功
     */
    int readEthernetIpConnStatus(EthernetIpSts_V1 &eipPara);

    /**
     * @brief 设置EIP从站管理状态
     * @param slaveIndex
     * @param isSupportManage
     * @param manageState
     * @return
     */
    int setEIPManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState);

    /**
     * @brief 获取EIP从站管理状态
     * @param slaveManageState
     * @return
     */
    int getEIPManageState(EIPSlaveManageState_V1 &slaveManageState);

    /**
     * @brief 刷新从站状态 仅用于示教器端
     * @return
     */
    int refreshEIPSlaveState();

    /**
     * @brief 检查EthernetIP总线开关的操作权限
     * @return true-权限符合
     */
    bool checkEthernetIPOperatePermission();

    /**
     * @brief 检查EthernetIP总线保存权限
     * @return true-权限符合
     */
    bool checkSaveEthernetIPPermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
