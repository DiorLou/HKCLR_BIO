#pragma once
#include <string>
#include "IInoRobBusiness.h"

using namespace std;

namespace InoRobBusiness
{
class TrajectoryRecoveryDefault : public ITrajectoryRecovery
{
public:
    // 构造与析构
    TrajectoryRecoveryDefault();
    TrajectoryRecoveryDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~TrajectoryRecoveryDefault();
    void init() override;
    // 写入轨迹恢复阈值参数
    virtual int WriteTrajRecoveryParam(TrajRecoveryParam &param);
    // 读取轨迹恢复阈值参数
    virtual int ReadTrajRecoveryParam(TrajRecoveryParam &param);
    // 权限保存检查
    bool checkSavePermission();
    // 检查操作权限
    bool checkOperationPermission(bool isTip);

private:
    // 依赖注入的抽象控制器对象
    IDataSrvBase *m_DataService;
    void Init();
};
}
