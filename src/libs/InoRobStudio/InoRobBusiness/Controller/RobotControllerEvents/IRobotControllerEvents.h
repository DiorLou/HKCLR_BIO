#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "dllspec.h"
#include "IDataSrvBase.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
#pragma region 类型与常量

#define EVENT_MAX_NUMB  100  // 事件最大个数
#define EVENT_DATA_SIZE 4    // 每个事件数据大小

#pragma pack(1)
/**
 * @brief 单个事件数据
 */
struct RcEventData
{
    RcEventData()
    {
        Initialize();
    }

    void Initialize()
    {
        iOrder = 0;
        iEventId = 0;
        for (size_t i = 0; i < EVENT_DATA_SIZE; i++)
        {
            eventData[i] = 0;
        }
    }

    RcEventData &operator=(const RcEventData &other)
    {
        this->iOrder = other.iOrder;
        this->iEventId = other.iEventId;
        for (int i = 0; i < EVENT_DATA_SIZE; i++)
            this->eventData[i] = other.eventData[i];

        return (*this);
    }

    int16u iOrder;                     // 事件序号
    int16u iEventId;                   // 事件id
    int8u eventData[EVENT_DATA_SIZE];  // 事件数据
};

/**
 * @brief 整体事件数据集合
 */
struct RobotControllerEventData
{
    int16u size;  // 队列中事件个数
    RcEventData eventDatas[EVENT_MAX_NUMB];
};
#pragma pack()

#pragma endregion

/*
    控制器接口（抽象），成员定义注意事项：
    1、建议使用子模型包装相关的数据、行为与信号
    2、接口是面向所有实现的通用抽象，因此接口成员的定义应考虑其通用性
*/
class INOROBBUSINESS_CLASS IRobotControllerEvents : public QObject
{
    Q_OBJECT

public:
    virtual ~IRobotControllerEvents()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 读取事件数据
    virtual int ReadEventDatas(RobotControllerEventData &robotControllerEventData) = 0;
    // 回复收到的事件数据
    virtual int WriteEventDatas(RobotControllerEventData &robotControllerEventData) = 0;

    // 获取事件轮询的间隔
    virtual int32s GetEventPollingThreadInterval() = 0;
    // 设置事件轮询的间隔
    virtual void SetEventPollingThreadInterval(int32s eventPollingThreadInterval) = 0;

Q_SIGNALS:
    // 控制权改变
    void authorityChanged(int authrity);
    // 工具页面/负载页面的负载辨识状态改变事件
    void identifyStatusChanged(int isFinish);
    // 自动热机信息改变事件
    void warmUpMachineInfoChanged(WarmUpMachineInfo info);
    // 独立轴状态改变事件
    void indAxisStatusChanged(int flag);
    // 指令弹框触发事件
    void cmdMessageBoxStatusChanged(int msgBoxStatus);
    // 零点校准定位销检查事件
    void dowelCheckStatusChanged(int isDisassembled);
    // 当前加载位置点位文件变更事件
    void loadRPFileChanged(int flag);
    // 主控连接状态事件信号
    void signalMasterStateChanged(int data);
    // 从控连接状态事件
    void signalSlaveStateChanged(int data);
    // 监控页面远端设备连接状态事件
    void signalMonitorDeviceStateChanged(int data);
    // 主控视觉监控数据事件
    void signalMonitorMasterDataChanged(int data);
    // 从控视觉监控数据事件
    void signalMonitorSlaveDataChanged(int data);
    // 干涉区状态变更事件
    void signalInterferZonesStatusChanged(int data);
    // ECAT从站管理状态事件
    void signalECATSlaveManageStatusChanged(int data);
    // EIP从站管理状态事件
    void signalEIPSlaveManageStatusChanged(int data);
    // 零点校准碰撞传感器状态事件
    void signalZeroPointSensorStatusChanged(bool data);
    // 文件读写指令
    void signalFileOperateStart(int data);
    // 工位状态改变
    void signalStationStatusChanged(unsigned int data);
    // 减速机寿命结果计算
    void signalReducerLifeCal(int data);
    // 丝杆寿命结果计算
    void signalScrewLifeCal(int data);
    // 力控接收日志导出路径并相应导出日志的请求
    void signalForceCtrlExportLogRequest(int data);
    // 完成摩擦辨识计算事件
    void signalCompleteFricIdentify(int isFinish);
    // 完成间隙辨识计算事件
    void signalCompleteBacklashIdentify(int isFinish);
};  // end class
}  // namespace InoRobBusiness
