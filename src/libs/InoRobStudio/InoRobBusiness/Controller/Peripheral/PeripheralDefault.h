#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IndexConfig/ProjectIndexConfig.h"
#include "IndexConfig/RPFileIndexConfig.h"
#include "IRLink/IRLinkDefault.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS PeripheralDefault : public IPeripheral
{
    Q_OBJECT

public:
    PeripheralDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~PeripheralDefault();
    void init() override;
#pragma region IRlink

#pragma endregion

#pragma region 序号配置
    virtual IIndexConfig *getProjectIndexConfigObject();
    virtual IIndexConfig *getRPFileIndexConfigObject();
#pragma endregion

#pragma region IRLink
    virtual IIRLink *getIRLink() const;
#pragma endregion

private:
    IDataSrvBase *_pDataSrv = nullptr;    // 通讯
    IConnection *_pConnection = nullptr;  // 连接
    IProject *_pProject = nullptr;        // 工程
    IMonitor *_pMonitor = nullptr;        // 监控
    IRobotArm *_pRobotArm = nullptr;       // 机械臂

    ProjectIndexConfig *_pProjectIndexCfg = nullptr;  // 工程序号配置操作对象
    RPFileIndexConfig *_pRPFileIndexCfg = nullptr;    // 全局位置点位文件序号配置操作对象

    IIRLink *_pIRLink = nullptr;
};
}  // namespace InoRobBusiness
