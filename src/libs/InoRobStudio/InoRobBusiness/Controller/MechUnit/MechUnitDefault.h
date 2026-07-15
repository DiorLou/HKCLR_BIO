#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
// 机械单元默认实现
class INOROBBUSINESS_CLASS MechUnitDefault : public IMechUnit
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService;
    // 连接
    IConnection *m_Connection;
    // 监控
    IMonitor *m_Monitor;

public:
    MechUnitDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~MechUnitDefault();
    void init() override;
#pragma endregion

public:
    bool MechUnitActive(string name);
};
}  // namespace InoRobBusiness
