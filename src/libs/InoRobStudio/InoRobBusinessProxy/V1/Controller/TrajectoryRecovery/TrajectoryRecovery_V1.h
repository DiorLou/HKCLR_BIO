#pragma once
#include "dllspec.h"
#include "../../GlobalDataTypes_V1.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS TrajectoryRecovery_V1
{
#pragma region 构造与析构

private:
    ITrajectoryRecovery *_trajectoryRecovery = nullptr;

public:
    TrajectoryRecovery_V1(ITrajectoryRecovery *trajectoryRecovery);
    ~TrajectoryRecovery_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 写入轨迹恢复阈值设置参数
    int WriteTrajRecoveryParam(TrajRecoveryParam_V1 &param);
    // 读取轨迹恢复阈值设置参数
    int ReadTrajRecoveryParam(TrajRecoveryParam_V1 &param);
    // 权限保存检查
    bool checkSavePermission();
    // 检查操作权限
    bool checkOperationPermission(bool isTip);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
