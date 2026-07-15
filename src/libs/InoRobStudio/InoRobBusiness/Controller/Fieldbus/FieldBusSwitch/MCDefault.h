#pragma once
#include "IMCSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class MCDefault : public IMCSwitch
{
    Q_OBJECT
public:
    MCDefault(IDataSrvBase *dataService);
    ~MCDefault();

    // 写入MC配置
    int writeMcActivePara(McActivePara mcActiveCfg);

    // 读取MC配置
    int readMcActivePara(McActivePara &mcActiveCfg);

    // 写入单个MC连接配置参数
    int writeSingleMcConnectSts(McConnectPara connectPara);

    // 读取所有的MC连接配置参数
    int readAllMcConnectSts(McConnectPara connectParas[4]);

    // 检查MC总线开关的操作权限
    bool checkMCOperatePermission();

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
};
}  // namespace InoRobBusiness
