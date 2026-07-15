#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "DataSrvGlobal.h"
#include "Protocol.h"

namespace InoRobBusiness
{
// 控制器连接状态
enum ControllerConnectionStatus : int32s
{
    CONTROLLER_CONNECTION_STATUS_CLOSED,      // 未连接
    CONTROLLER_CONNECTION_STATUS_CONNECTING,  // 连接中
    CONTROLLER_CONNECTION_STATUS_CONNECTED    // 已连接（控制器启动成功）
};

// 连接类型
enum ConnentType
{
    CONNECT_DEFAULT_TYPE = 0,  // 初始值
    CONNECT_PC_TYPE = 1,       // PC 编程平台
    CONNECT_TP_TYPE = 2,       // PC 示教器
    CONNECT_HAND_TP_TYPE = 3,  // 手持 示教器
};

//连接版本
enum ConnectVersion
{
	CONNECT_DEFAULT_VER = 0X0000,  // 初始值 默认为TP1.0
	CONNECT_TP_1_0 = 0X0100,        // TP 1.0
	CONNECT_TP_2_0 = 0X0200,        // TP 2.0
};

/*
    连接
    Create by WuJian at 2022/5/12
*/
class INOROBBUSINESS_CLASS IConnection : public QObject
{
    Q_OBJECT

public:
    virtual ~IConnection()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // IP
    virtual std::string GetIp() = 0;
    virtual void SetIp(const std::string &ip) = 0;
    // 端口
    virtual int16u GetPort() = 0;
    virtual void setPort(int16u port) = 0;
    // 心跳开关
    virtual bool GetIsHeartbeat() = 0;
    virtual void SetIsHeartbeat(bool isHeartbeat) = 0;
    // 心跳间隔时间（毫秒，当值小于等于0时会关闭心跳）
    virtual int32s GetHeartbeatInterval() = 0;
    virtual void SetHeartbeatInterval(int32s heartbeatInterval) = 0;
    // 心跳失败后最大尝试次数（注：超过最大尝试次数后，心跳将终止并置控制器连接状态为断开）
    virtual int32s GetHeartbeatMaxTryTimes() = 0;
    virtual void SetHeartbeatMaxTryTimes(int32s heartbeatMaxTryTimes) = 0;
    // 控制器连接状态
    virtual ControllerConnectionStatus GetConnectionStatus() = 0;
    // 连接（待完善）
    // 连接类型 (1 PC 连接；2  TP 连接)
    virtual bool Connect(ConnentType type, ConnectVersion version = CONNECT_DEFAULT_VER) = 0;
    virtual bool Connect(const std::string &ip, int16u port, ConnentType type = CONNECT_PC_TYPE, ConnectVersion version = CONNECT_DEFAULT_VER) = 0;
    // 关闭连接
    // bManual: true-正常断开 false-状态复位,每次连接后立即复位
    virtual bool Close(bool bManual = false) = 0;
    // 在对象释放前，关闭线程，以避免线程中内存访问出错（MFC线程机制缺陷）
    virtual void CloseThread() = 0;

    // 控制器未连接的Ping操作
    virtual void ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT, std::string strIP, int nPackNum) = 0;
    // 控制器连接时写参数自带发送Ping命令
    virtual int writeNetPingParam(net_check_para_t pingPara) = 0;
    // 控制器连接时读取Ping操作的结果
    virtual int readNetPingResult(int16s &completeFlag, net_check_ret_t &pingRet) = 0;
    // 返回设备在线状态
    virtual bool isDevOnline() = 0;

#pragma region 设置系统时间

    // 写入设备系统时间 时间同步
    virtual int writeDevSysTime(const GSYSTEMTIME &sysTime, int nFrame) = 0;
    // 读取设备的系统时间
    virtual int readDevSysTime(GSYSTEMTIME &sysTime) = 0;
    // 检查输入的时间是否合法
    virtual bool checkTimeIsValid(GSYSTEMTIME &sysTime) = 0;
    // 检查时间修改权限
    virtual bool checkModifyTimePermission() = 0;

#pragma endregion

    // 获取控制器类型
    virtual int getControllerType() = 0;

    // 设置控制器类型
    virtual void setControllerType(int typeFlag = 0) = 0;

    // 跳过启动软件时的连接过程
    virtual int skipBootConnect() = 0;

    // 连接成功检查版本信息是否一致
    rsignal<int> sigCheckVersionIsConsistent;

Q_SIGNALS:
    // 连接成功信号
    void connnectSuccess();
    // 连接状态变化信号（注：因rsignal信号槽存在lock_guard异常，因此开辟该信号槽供代理层专用）
    void connectionStatusChangedForProxy(ControllerConnectionStatus status);
    // 连接状态变化信号
    void connectionStatusChanged(ControllerConnectionStatus connectionStatus);
    // 连接过程描述信息
    void sigConnectDescribe(std::string describe);
    // 跳过启动软件时的连接过程
    void sigSkipBootConnect();
};
}  // namespace InoRobBusiness
