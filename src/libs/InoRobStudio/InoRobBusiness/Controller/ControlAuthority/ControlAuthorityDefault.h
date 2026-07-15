#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IControlAuthority.h"

namespace InoRobBusiness
{
/*
    控制权管理
    Create by lcm at 2024/04/11 创建。
*/
class INOROBBUSINESS_CLASS ControlAuthorityDefault : public IControlAuthority
{
    Q_OBJECT

public:
    ControlAuthorityDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~ControlAuthorityDefault();
    void init() override;

public:
    virtual int changeAuthority(CtrlAuthority authority, int speed) override;

    virtual void setCurrentAuthority(CtrlAuthority authority) override;
    virtual CtrlAuthority getCurrentAuthority() override;

    virtual bool isChangingAuthority() override;

    virtual int writeAuthority(CtrlAuthority authority) override;
    virtual int readAuthority(CtrlAuthority &authority) override;
    virtual int writeRmtDefaultSpeed(int speed) override;
    virtual int readRmtDefaultSpeed(int &speed) override;

    virtual int writeRmtIoSubMode(RmtIoSubMode mode) override;
    virtual int readRmtIoSubMode(RmtIoSubMode &mode) override;
    virtual int writeRmtRunLineResetMode(RmtRunLineResetMode mode) override;
    virtual int readRmtRunLineResetMode(RmtRunLineResetMode &mode) override;
    virtual int writeRmtStopEnableState(RmtStopEnableState state) override;
    virtual int readRmtStopEnableState(RmtStopEnableState &state) override;

    // 读取机器人0编程状态
    virtual bool getZeroProgramMode(int16u &mode) override;

private:
    bool checkBaseStatus();
    bool checkStatus(CtrlAuthority authority);
    bool checkModbusStatus();
    bool checkRmtIoStatus();

    int doChangeAuthority(CtrlAuthority authority, int speed = 0);
    int changeRmtDefaultSpeed(int speed);
    int waitAuthorityChanged(CtrlAuthority remoteAuthority);

    void onConnectionStatusChanged(ControllerConnectionStatus status);

    // 控制器导致的控制权变更（机器人0编程被触发）
    void onCtrlAuthorityChangedFromController(int authority);

private:
    CtrlAuthority _authority = CtrlAuthority::TEACHPAD;

    bool _isChangingAuthority = false;  // 是否正在切换控制权

    IDataSrvBase *_pDataSrv = nullptr;                // 通讯
    IConnection *_pConnection = nullptr;              // 连接
    IProject *_pProject = nullptr;                    // 工程
    ITransfor *_pTransfor = nullptr;                  // 译码
    IMonitor *_pMonitor = nullptr;                    // 监控
    IMotion *_pMotion = nullptr;                      // 运动
    IDebuger *_pDebuger = nullptr;                    // 调试
    IRCConfig *_pRCConfig = nullptr;                  // 控制器配置
    IFieldbus *_pFieldbus = nullptr;                  // 总线
    IRobotControllerEvents *_pRobotevents = nullptr;  // 事件机制
};
}  // namespace InoRobBusiness
