#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Profinet_V1
{
#pragma region 构造与析构

private:
    IProfinetSwitch *_profinetSwitch = nullptr;

public:
    Profinet_V1(IProfinetSwitch *profinetSwitch);
    ~Profinet_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 写入Profinet激活状态
     * @param pnConfig 写入结构体
     * @return 0-成功
     */
    int writeProfinetConfig(PnActiveCfg_V1 pnConfig);

    /**
     * @brief 读取Profinet连接信息
     * @param pnPara 读取结构体
     * @return 0-成功
     */
    int readProfinetConnSts(PnConnectSts_V1 &pnPara);

    /**
     * @brief 检查Profinet总线开关的操作权限
     * @return true-成功
     */
    bool checkProfinetOperatePermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
