#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define EVENT_MAX_NUMB_V1  100  // 事件最大个数
#define EVENT_DATA_SIZE_V1 4    // 每个事件数据大小

/**
 * @brief 单个事件数据
 */
struct RcEventData_V1
{
    RcEventData_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        iOrder = 0;
        iEventId = 0;
        for (size_t i = 0; i < EVENT_DATA_SIZE_V1; i++)
        {
            eventData[i] = 0;
        }
    }

    RcEventData_V1 &operator=(const RcEventData_V1 &other)
    {
        this->iOrder = other.iOrder;
        this->iEventId = other.iEventId;
        for (int i = 0; i < EVENT_DATA_SIZE_V1; i++)
            this->eventData[i] = other.eventData[i];

        return (*this);
    }

    int16u iOrder;                        // 事件序号
    int16u iEventId;                      // 事件id
    int8u eventData[EVENT_DATA_SIZE_V1];  // 事件数据
};

/**
 * @brief 整体事件数据集合
 */
struct RobotControllerEventData_V1
{
    int16u size;  // 队列中事件个数
    RcEventData_V1 eventDatas[EVENT_MAX_NUMB_V1];
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS RobotControllerEvents_V1 : public QObject
{
    Q_OBJECT
#pragma region 构造与析构

private:
    IRobotControllerEvents *_robotControllerEvents = nullptr;

public:
    RobotControllerEvents_V1(IRobotControllerEvents *robotControllerEvents);
    ~RobotControllerEvents_V1();

#pragma endregion

#pragma region 数据转换

public:
    static bool RcEventData_ToProxy(const RcEventData &rcEventData, RcEventData_V1 &rcEventData_V1);
    static bool RcEventData_FromProxy(const RcEventData_V1 &rcEventData_V1, RcEventData &rcEventData);

    static bool RobotControllerEventData_ToProxy(const RobotControllerEventData &robotControllerEventData, RobotControllerEventData_V1 &robotControllerEventData_V1);
    static bool RobotControllerEventData_FromProxy(const RobotControllerEventData_V1 &robotControllerEventData_V1, RobotControllerEventData &robotControllerEventData);

#pragma endregion

#pragma region 业务逻辑

public:
    // 读取事件数据
    int ReadEventDatas(RobotControllerEventData_V1 &robotControllerEventData);
    // 回复收到的事件数据
    int WriteEventDatas(RobotControllerEventData_V1 &robotControllerEventData);

    // 获取事件轮询的间隔
    int32s GetEventPollingThreadInterval();
    // 设置事件轮询的间隔
    void SetEventPollingThreadInterval(int32s eventPollingThreadInterval);

#pragma endregion

#pragma region 信号

private:
    void IdentifyStatusChangedHandler(int data);
    void WarmUpMachineInfoChangedHandler(WarmUpMachineInfo data);
    void IndAxisStatusChangedHandler(int data);
    void CmdMessageBoxStatusChangedHandler(int data);
    void DowelCheckStatusChangedHandler(int data);
    void LoadRPFileChangedHandler(int data);
    void SignalMasterStateChangedHandler(int data);
    void SignalSlaveStateChangedHandler(int data);
    void SignalMonitorDeviceStateChangedHandler(int data);
    void SignalMonitorMasterDataChangedHandler(int data);
    void SignalMonitorSlaveDataChangedHandler(int data);
    void SignalInterferZonesStatusChangedHandler(int data);
    void SignalECATSlaveManageStatusChangedHandler(int data);
    void SignalEIPSlaveManageStatusChangedHandler(int data);
    void SignalZeroPointSensorStatusChangedHandler(bool data);
    void AuthorityChangedHandler(int data);

public:
    // 工具页面/负载页面的负载辨识状态改变事件
    rsignal<int> IdentifyStatusChanged;
    // 自动热机信息改变事件
    rsignal<WarmUpMachineInfo_V1> WarmUpMachineInfoChanged;
    // 独立轴状态改变事件
    rsignal<int> IndAxisStatusChanged;
    // 指令弹框触发事件
    rsignal<int> CmdMessageBoxStatusChanged;
    // 零点校准定位销检查事件
    rsignal<int> DowelCheckStatusChanged;
    // 当前加载位置点位文件变更事件
    rsignal<int> LoadRPFileChanged;
    // 主控连接状态事件信号
    rsignal<int> SignalMasterStateChanged;
    // 从控连接状态事件
    rsignal<int> SignalSlaveStateChanged;
    // 监控页面远端设备连接状态事件
    rsignal<int> SignalMonitorDeviceStateChanged;
    // 主控视觉监控数据事件
    rsignal<int> SignalMonitorMasterDataChanged;
    // 从控视觉监控数据事件
    rsignal<int> SignalMonitorSlaveDataChanged;
    // 干涉区状态变更事件
    rsignal<int> SignalInterferZonesStatusChanged;
    // ECAT从站管理状态事件
    rsignal<int> SignalECATSlaveManageStatusChanged;
    // EIP从站管理状态事件
    rsignal<int> SignalEIPSlaveManageStatusChanged;
    // 零点校准碰撞传感器状态事件
    rsignal<bool> SignalZeroPointSensorStatusChanged;
    // 控制权改变
    rsignal<int> AuthorityChanged;

#pragma endregion
};
}  // namespace InoRobBusinessProxy
