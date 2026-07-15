#pragma once
#include "IInoRobBusiness.h"


namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS ScriptExtensionDefault : public IScriptExtension
{
    Q_OBJECT

public:
    // 构造与析构
    ScriptExtensionDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~ScriptExtensionDefault();
    void init() override;
    // 依赖注入
    void SetController(IDataSrvBase* dataService, IConnection* connection, IMonitor* monitor);
    // 开始
    virtual bool Start() override;
    // 暂停
    virtual bool Pause() override;
    // 单步
    virtual bool Step() override;
    // 终止
    virtual bool Abort() override;
#if (defined(_WIN32) && defined(__GNUC__)) || defined(__ANDROID__)
    // 单步
    virtual bool StepBlock() override;
#endif // 协作示教器平台

private:
    // 状态确认
    bool CheckStartPermision();
    // 命令下发
    int SendCmd(int16u cmdId);

    // 依赖注入对象
    IDataSrvBase* _pDataSrv;
    IConnection* _pConnection;
    IMonitor* _pMonitor;

};
}

