#pragma once
#include <string>
#include "IController.h"
#include "Container.h"
#include "DataSrvGlobal.h"


namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RobotControllerEvents : public IRobotControllerEvents
{
#pragma region 构造与析构

public:
    RobotControllerEvents(string name, IDataSrvBase *pDataSrv, QObject *parent = nullptr);
    virtual ~RobotControllerEvents();

#pragma endregion

#pragma region 基础

private:
    // 依赖注入的抽象控制器对象
    IDataSrvBase *_pDataSrv = nullptr;    // 通讯
    IConnection *_pConnection = nullptr;  // 连接S
    void init() override;

    // 事件处理线程
    std::shared_ptr<std::thread> _pEventPollingThread;
    void EventPolling();

public:   
    // 处理间隔时间（毫秒，当值小于等于0时会关闭）
    int32s _eventPollingThreadInterval;
    //获取事件轮询的间隔
    int32s GetEventPollingThreadInterval();
    //设置事件轮询的间隔
    void SetEventPollingThreadInterval(int32s eventPollingThreadInterval);

    // 线程关闭标识
    bool _closeThread;
    void CloseThread();

     //读取事件数据
    int ReadEventDatas(RobotControllerEventData &robotControllerEventData);
    //回复收到的事件数据
    int WriteEventDatas(RobotControllerEventData &robotControllerEventData);
    //处理事件数据
    void HandlerEventDatas(RobotControllerEventData &robotControllerEventData);

#pragma endregion
};

}  // namespace InoRobBusiness
