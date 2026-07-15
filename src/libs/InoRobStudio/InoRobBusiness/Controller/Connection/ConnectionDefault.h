#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ConnectionDefault : public IConnection
{
    Q_OBJECT

public:
    // 构造与析构
    ConnectionDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~ConnectionDefault();
    void init() override;
    std::string GetIp();
    void SetIp(const std::string &ip);
    int16u GetPort();
    void setPort(int16u port);
    bool GetIsHeartbeat();
    void SetIsHeartbeat(bool isHeartbeat);
    int32s GetHeartbeatInterval();
    void SetHeartbeatInterval(int32s heartbeatInterval);
    int32s GetHeartbeatMaxTryTimes();
    void SetHeartbeatMaxTryTimes(int32s heartbeatMaxTryTimes);
    ControllerConnectionStatus GetConnectionStatus();
    bool Connect(ConnentType type, ConnectVersion version = CONNECT_DEFAULT_VER);
    bool Connect(const std::string &ip, int16u port, ConnentType type = CONNECT_PC_TYPE, ConnectVersion version = CONNECT_DEFAULT_VER);
    bool Close(bool bManual = false);
    void CloseThread();

    // 读写网络参数文件
    void ReadNetworkParameter(std::string &sIP, int16u &nPort);
    void WriteConectIPToFile(std::string strConectIP, int16u port);

    // Ping操作
    void ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT, std::string strIP, int nPackNum);

    /*!
     * \brief 控制器连接时写参数自带发送Ping命令
     * \param 输入IP地址
     * \return 是否写入成功
     */
    int writeNetPingParam(net_check_para_t pingPara);

    /*!
     * \brief 控制器连接时读取Ping操作的结果
     * \param 完成标识completeFlag, 1-成功，表示Ping完成, -1-错误，表示Ping错误
     * \param 读取的Ping结果
     * \return 获取是否成功
     */
    int readNetPingResult(int16s &completeFlag, net_check_ret_t &pingRet);

    /*!
     * \brief 返回设备在线状态
     * \return 设备是否在线
     */
    bool isDevOnline();

#pragma region 设置时间

    int writeDevSysTime(const GSYSTEMTIME &sysTime, int nFrame);
    int readDevSysTime(GSYSTEMTIME &sysTime);
    bool checkTimeIsValid(GSYSTEMTIME &sysTime);
    bool checkModifyTimePermission();

#pragma endregion

    /*!
     * \brief 跳过启动软件时的连接过程
     */
    int skipBootConnect();

#pragma region 虚拟控制器相关
private:
    int _controllerTypeFlag;
    string _VCRootLocation;
    string _VCDeviceName;
public:
    // 获取控制器类型
    int getControllerType();

    // 设置控制器类型
    void setControllerType(int typeFlag = 0);

    std::string GetVCDeviceName();

    void SetVCDeviceName(std::string VCName);
#pragma endregion

private:
    /**
     * @brief 连接后的同步初始化操作，写进syncInit或绑定连接信号处理
     * @param type
     */
    int syncInit(ConnentType type = CONNECT_TP_TYPE, ConnectVersion version = CONNECT_DEFAULT_VER);

    /**
     * @brief 设置当前控制器连接上位机类型
     */
    void setConnectType(ConnentType type, ConnectVersion version = CONNECT_DEFAULT_VER);

    /**
     * @brief 写入上位机连接类型
     * @param connectType 参考ConnentType
     * @param ver 参考ConnectVersion 
     */
    int writeConnectType(unsigned char connectType,unsigned short ver = 0X0000);

    /**
     * @brief 读取上位机连接类型
     * @param connectType 参考ConnentType
     */
    int readConnectType(unsigned char &connectType);

    // 读初始化完成状态
    // 返回值：0-成功
    int readInitState(int &nState);

    // 等待控制器初始化完成
    int waitInitFinish();

    // 读取存储卡初始化状态  -1：初始化过程中 0-老版本 1-初始化完成
    int readSDInitialSts(int8s &sts);

    // 设置主动断开连接标识(错误码)
    /*
    1:正常断开
    0:状态复位,每次连接后立即复位
    */
    int setDisconErro(int nErro);

    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService;

    // 互斥锁
    static std::timed_mutex _mutex;

    // 连接类型
    ConnentType m_ConnectType;
    // IP
    std::string m_Ip;
    // 端口
    int16u m_Port;
    // 心跳开关
    bool m_IsHeartbeat;
    // 心跳间隔时间（毫秒，小于等于0时会不进行心跳）
    int32s m_HeartbeatInterval;
    // 心跳失败后最大尝试次数
    int32s m_HeartbeatMaxTryTimes;
    // 连接状态
    ControllerConnectionStatus m_ConnectionStatus;
    // 变更连接状态（自动判断触发状态变更事件）
    void OnConnectionStatusChange(ControllerConnectionStatus connectionStatus);
    // 心跳线程
    std::shared_ptr<std::thread> _pHeartbeatThread;
    void Heartbeat();
    // 线程关闭标识
    static bool _closeThread;

    // 应用协议对象
    CProtocol _protocol;
};
}  // namespace InoRobBusiness
