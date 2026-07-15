#pragma once
#include "dllspec.h"
#include <QObject>
#include "IInoRobBusiness.h"
#include "../../DataService/DataSrvGlobal_V1.h"
#include "../../DataService/Protocol_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

// 控制器连接状态
enum ControllerConnectionStatus_V1 : int32s
{
    CONTROLLER_CONNECTION_STATUS_CLOSED_V1 = 0,      // 未连接
    CONTROLLER_CONNECTION_STATUS_CONNECTING_V1 = 1,  // 连接中
    CONTROLLER_CONNECTION_STATUS_CONNECTED_V1 = 2    // 已连接（控制器启动成功）
};

// 连接类型
enum ConnentType_V1
{
    CONNECT_DEFAULT_TYPE_V1 = 0,  // 初始值
    CONNECT_PC_TYPE_V1 = 1,       // PC 编程平台
    CONNECT_TP_TYPE_V1 = 2,       // 示教器
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Connection_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static ControllerConnectionStatus_V1 ControllerConnectionStatus_ToProxy(ControllerConnectionStatus controllerConnectionStatus);
    static ControllerConnectionStatus ControllerConnectionStatus_FromProxy(ControllerConnectionStatus_V1 controllerConnectionStatusV1);

    static ConnentType_V1 ConnentType_ToProxy(ConnentType connentType);
    static ConnentType ConnentType_FromProxy(ConnentType_V1 connentTypeV1);

#pragma endregion

#pragma region 构造与析构

private:
    IConnection *_connection = nullptr;

public:
    Connection_V1(IConnection *connection);
    ~Connection_V1();

#pragma endregion

#pragma region 业务逻辑

private:
    void ConnectionStatusChangedHandler(ControllerConnectionStatus controllerConnectionStatus);
    void sigConnectDescribeHandler(std::string desc);

public:
    // IP（已测）
    std::string GetIp();
    void SetIp(const std::string &ip);
    // 端口（已测）
    int16u GetPort();
    void setPort(int16u port);
    // 心跳开关（已测）
    // bool GetIsHeartbeat();
    // 心跳间隔时间（已测）
    // int32s GetHeartbeatInterval();
    // 心跳失败后最大尝试次数（已测）
    // int32s GetHeartbeatMaxTryTimes();
    // 控制器连接状态（已测）
    ControllerConnectionStatus_V1 GetConnectionStatus();
    // 连接状态变化信号（已测）
    rsignal<ControllerConnectionStatus_V1> ConnectionStatusChanged;
    // 连接（待完善）
    // 连接类型 (1 PC 连接；2  TP 连接)
    bool Connect(ConnentType_V1 type);
    bool Connect(const std::string &ip, int16u port, ConnentType_V1 type = CONNECT_PC_TYPE_V1);
    // 关闭连接
    // bManual: true-正常断开 false-状态复位,每次连接后立即复位
    bool Close(bool bManual = false);

    // 控制器未连接的Ping操作
    void ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT, std::string strIP, int nPackNum);
    // 控制器连接时写参数自带发送Ping命令
    int writeNetPingParam(net_check_para_V1 pingParaV1);
    // 控制器连接时读取Ping操作的结果
    int readNetPingResult(int16s &completeFlag, net_check_ret_V1 &pingRetV1);
    // 返回设备在线状态（已测）
    bool isDevOnline();

    // 写入设备系统时间 时间同步
    int writeDevSysTime(const GSYSTEMTIME_V1 &sysTimeV1, int nFrame);
    // 读取设备的系统时间
    int readDevSysTime(GSYSTEMTIME_V1 &sysTimeV1);
    // 检查输入的时间是否合法
    bool checkTimeIsValid(GSYSTEMTIME_V1 &sysTimeV1);
    // 检查时间修改权限（已测）
    bool checkModifyTimePermission();

    // 连接过程描述信息
    rsignal<std::string> sigConnectDescribe;

#pragma endregion
};
}  // namespace InoRobBusinessProxy
