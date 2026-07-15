#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS MC_V1
{
#pragma region 构造与析构

private:
    IMCSwitch *_mcSwitch = nullptr;

public:
    MC_V1(IMCSwitch *mcSwitch);
    ~MC_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 写入MC配置
     * @param mcActiveCfg 写入结构体
     * @return 0-成功
     */
    int writeMcActivePara(McActivePara_V1 mcActiveCfg);

    /**
     * @brief 读取MC配置
     * @param mcActiveCfg 读取结构体
     * @return 0-成功
     */
    int readMcActivePara(McActivePara_V1 &mcActiveCfg);

    /**
     * @brief 写入单个MC连接配置参数
     * @param connectPara 连接参数
     * @return 0-成功
     */
    int writeSingleMcConnectSts(McConnectPara_V1 connectPara);

    /**
     * @brief 读取所有的MC连接配置参数
     * @param connectParas 连接参数
     * @return 0-成功
     */
    int readAllMcConnectSts(McConnectPara_V1 connectParas[4]);

    /**
     * @brief 检查MC总线开关的操作权限
     * @return true-权限符合
     */
    bool checkMCOperatePermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
