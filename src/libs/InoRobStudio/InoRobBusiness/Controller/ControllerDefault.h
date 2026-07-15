#pragma once
#include <string>
#include "IController.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
// 控制器默认实现
class INOROBBUSINESS_CLASS ControllerDefault : public IController
{
    Q_OBJECT

#pragma region 构造与析构

public:
    ControllerDefault();
    ~ControllerDefault();

#pragma endregion

#pragma region 基础

private:
    // 控制器唯一Id
    string _ID;
    // 控制器名称
    string _Name;
    // 关闭限速时的时间戳
    long long _turnOffSpeedLimitTime;
    // 创建映射表
    void createMap();
    // 功能模块ID映射表
    map<FunctionModuleID, string> _objNameMap;
   //获取FTP登录所需令牌
    void getFtpLoginToken(std::string& ip, int& port, std::string& userName, std::string& password);

public:
    string GetID();
    void SetID(string id);
    string GetName();
    void SetName(string name);
    void initAsyncModule();
#pragma endregion

#pragma region 异步指令处理(目前只能放在Controller中，因为轮询线程里会同时用到多个子模型，后面再尝试优化到事件机制中)
public:
    // 线程退出开关
    bool _isCloseAsyncCommandThread;
    // 异步指令处理开关
    bool _isAsyncCommand;
    // 异步指令处理间隔时间（毫秒，当值小于等于0时会关闭异步指令处理）
    int32s _asyncCommandInterval;
    // 异步指令处理线程（注：使用单独的线程来处理在实时数据中不包含的数据项；以及与控制器交互的异步指令）
    std::shared_ptr<std::thread> _pAsyncCommandThread;
    void AsyncCommand();

    // 获取异步指令处理线程开启状态
    bool GetIsAsyncCommand();
    // 设置异步指令处理线程开启状态
    void SetIsAsyncCommand(bool isAsyncCommand);
    // 获取异步指令处理线程轮询时间间隔
    int32s GetAsyncCommandInterval();
    // 设置异步指令处理线程轮询时间间隔
    void SetAsyncCommandInterval(int32s asyncCommandInterval);
#pragma endregion

#pragma region 子模型

private:
    // 连接
    IConnection *_pConnection = nullptr;
    // 监控
    IMonitor *_pMonitor = nullptr;
    // 操控
    IControl *_pControl = nullptr;
    // 运动
    IMotion *_pMotion = nullptr;
    // 调试
    IDebuger *_pDebuger = nullptr;
    // 任务
    ITask *_pTask = nullptr;

public:
    void getMap(map<FunctionModuleID, string> &objNameMap);
    // 根据名称获得对象
    QObject *getObjectByName(FunctionModuleID id);
#pragma endregion
};
}  // namespace InoRobBusiness
