#pragma once
#include "IEthernetIPSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class EthernetIPDefault : public IEthernetIPSwitch
{
    Q_OBJECT
public:
    EthernetIPDefault(IDataSrvBase *dataService);
    ~EthernetIPDefault();

    // 写入EthernetIp配置
    int writeEthernetIpConfig(EthernetIpPara eipConfig);

    // 读取EthernetIp状态
    int readEthernetIpConnStatus(EthernetIpSts &eipPara);

    // 设置EIP从站管理状态
    int setEIPManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState);

    // 获取EIP从站管理状态
    int getEIPManageState(EIPSlaveManageState &slaveManageState);

    // 刷新从站状态 仅用于示教器端
    int refreshEIPSlaveState();

    // 检查EthernetIP总线开关的操作权限
    bool checkEthernetIPOperatePermission();

    // 检查EthernetIP总线保存权限
    bool checkSaveEthernetIPPermission();

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
};
}  // namespace InoRobBusiness
