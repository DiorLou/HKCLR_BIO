#pragma once
#include "IProfinetSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class ProfinetDefault : public IProfinetSwitch
{
public:
    ProfinetDefault(IDataSrvBase *dataService);
    ~ProfinetDefault();

    // 写入Profinet激活状态
    int writeProfinetConfig(PnActiveCfg pnConfig);

    // 读取Profinet连接信息
    int readProfinetConnSts(PnConnectSts &pnPara);

    // 检查Profinet总线开关的操作权限
    bool checkProfinetOperatePermission();

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
};
}  // namespace InoRobBusiness
