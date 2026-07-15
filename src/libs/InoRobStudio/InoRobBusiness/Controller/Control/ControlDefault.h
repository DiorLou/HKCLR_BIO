#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ControlDefault : public IControl
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;
    // 控制器配置
    IRCConfig *_pRcConfig = nullptr;
    // 连接
    IConnection *_pConnection = nullptr;
    // 监控
    IMonitor *_pMonitor = nullptr;
    // 调试
    IDebuger *_pDebuger = nullptr;
    // 当前的设备（机器人）模式
    DeviceMode _curMode;
    // 松抱闸线程
    std::shared_ptr<std::thread> _pReleaseBrakeThread;

public:
    ControlDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~ControlDefault();
    void init() override;
#pragma endregion
public:
    // 使能（适用小多传/20kg立柜/驱控一体）
    virtual int SetEnable(bool status) override;
    // 急停
    virtual int SetEmergency(bool status) override;
    // 协作专用 本体上电
    virtual int SetCoRobotBodyPowerState(const CoRobotBodyPowerState status) override;
    // 设置wifi密码
    virtual int SetControllerWifiPassword(const std::string &password) override;
    // 获取wifi密码修改结果
    virtual int GetWifiPasswordModifyResult(WifiPasswordModifyResult &result) override;
    // 设置Wifi频段（协作）
    virtual int SetControllerWifiFrequencyBand(bool enable) override;
    // 获取控制器WiFi信息（协作）
    virtual int GetControllerWifiInfo(ControllerWifiInfo &info) override;
    // 设置夹持器三位置使能状态
    virtual int SetGripperThreePositionEnable(bool enable) override;
    // 获取单电柜运行模式使能状态（协作）
    virtual int GetSingleControllerRunModeStatus(bool &status) override;
    // 设置单电柜运行模式使能（协作）
    virtual int SetSingleControllerRunModeEnable(bool enable) override;
    // 获取单电柜运行模式使能设置结果（协作）
    virtual int GetSingleControllerRunModeEnable(bool &enable) override;
    // 清除报警
    virtual int ClearWarning(PressState state) override;
    // 运行模式
    virtual bool SetRunMode(RunMode mode) override;
    // 设置设备（机器人）模式
    virtual int SetDeviceMode(DeviceMode mode) override;
    // 获取设备（机器人）模式
    virtual int GetDeviceMode(DeviceMode &mode) override;
    // 开启限速
    virtual int activateSpeedLimit() override;
    // 关闭限速
    virtual int turnoffSpeedLimit() override;
    // 是否已经开启限速
    virtual bool isActivatedSpeedLimit() override;
    // 机械锁定
    virtual bool SetMechLock(bool status) override;
    // 动态制动
    virtual bool SetDynamicBrake(bool status) override;
    // 协调
    virtual bool SetCooperate(const string &mechUnitName) override;
    virtual bool setCooperate(const bool status) override;

    // 设置协调状态
    virtual void setCoordinationState(int coordSts) override;

    // 获取协调状态
    virtual int getCoordinationState() override;

    // 系统升级
    virtual int systemUpgrade(bool isUpdateBsp = true, bool isTP = true) override;
    // 系统降级
    virtual int systemDegrade() override;
    // 状态检查，是否可以进行系统升降级
    virtual bool isSystemCanUpdate() override;
    // 获取系统升降级的过程信息
    virtual int readSystemUpdateInfo(SystemUpdateInfo &info) override;

    /* 控制器文件夹与文件操作相关 */
    virtual int createDir(const std::string &dir) override;
    virtual int copyDir(const std::string &src, const std::string &dest) override;
    virtual int cutDir(const std::string &src, const std::string &dest) override;
    virtual int renameDir(const std::string &src, const std::string &dest) override;
    virtual int delDir(const std::string &dir) override;
    virtual int copyFile(const std::string &src, const std::string &dest) override;
    virtual int cutFile(const std::string &src, const std::string &dest) override;
    virtual int renameFile(const std::string &src, const std::string &dest) override;
    virtual int delFile(const std::string &path) override;

    virtual int readBrakeState(char stateArray[6]) override;
    virtual int writeBrakeState(char brake_cmd, int32u brake_count, int axis_number, bool isPrintMessage = true) override;
    virtual void cleanBrakeCount() override;
    virtual void setBrakeFirstCmd(bool bFlag) override;
    virtual void setBrakeCurAxisNo(int axisNo) override;
    virtual void setBrakeThreadState(bool isRun) override;
    virtual void closeBrakeThread() override;

    // 询问控制器指定的操作类型是否被允许
    virtual bool ControllerOperationValid(ControllerOperationType controllerOperationType) override;

    // 从控制柜下载文件到本地
    virtual int downloadFile(const std::string &localPath, const std::string &ctrlPath) override;

    // 拖动示教记点结果反馈
    virtual int autoRecordPoint(int status) override;

    // 获取是否刷机后第一次启动状态
    virtual int getFirstBootStatus(bool &status) override;

    // 通知机型参数文件更新
    virtual int RobotParamFileChange(char *info) override;

    // 启动伺服监控
    virtual int RobotParamServoStart(char *info) override;

    // 停止伺服监控
    virtual int RobotParamServoStop() override;

    // 获取当前伺服参数数据
    virtual int RobotParamServoCurrent(string &info) override;

    // 读取参数更新状态
    virtual int RobotParamUpdateStatusRead(string &info) override;

private:
    /// <summary>
    /// 响应连接状态改变事件
    /// </summary>
    /// <param name="status">连接状态</param>
    void onConnectionStatusChanged(ControllerConnectionStatus status);
    /// <summary>
    /// 系统强制IO设置（适用小多传/20kg立柜/驱控一体）
    /// </summary>
    /// <param name="inH">输入，输入高电平</param>
    /// <param name="inL">输入，输入低电平</param>
    /// <param name="outH">输入，输出高电平</param>
    /// <param name="outL">输入，输出低电平</param>
    /// <returns>成功返回0，其他请查看错误码</returns>
    int writeSysForceIoData(int16u inH, int16u inL, int16u outH, int16u outL);
    /// <summary>
    /// 系统强制IO读取（适用小多传/20kg立柜/驱控一体）
    /// </summary>
    /// <param name="inH">输出，输入高电平</param>
    /// <param name="inL">输出，输入低电平</param>
    /// <param name="outH">输出，输出高电平</param>
    /// <param name="outL">输出，输出低电平</param>
    /// <returns>成功返回0，其他请查看错误码</returns>
    int readSysForceIoData(int16u &inH, int16u &inL, int16u &outH, int16u &outL);
    /// <summary>
    /// 设置设备（机器人）模式
    /// </summary>
    /// <param name="mode">输入，模式</param>
    /// <returns>成功返回0，其他请查看错误码</returns>
    int writeDeviceMode(const DeviceMode &mode);
    /// <summary>
    /// 设置限速配置（状态）
    /// </summary>
    /// <param name="state">输入，状态，0-开启限速，1-关闭限速</param>
    /// <returns>成功返回0，其他请查看错误码</returns>
    int writeModeSpeedLimitState(const int &state);
    /// <summary>
    /// 读取限速配置（状态）
    /// </summary>
    /// <param name="state">输出，状态，0-开启限速，1-关闭限速</param>
    /// <returns>成功返回0，其他请查看错误码</returns>
    int readModeSpeedLimitState(int &state);

    /**
     * @brief 往控制器写文件/文件夹路径
     * @param cmdId 输入，命令id
     * @param src 输入，源目录或文件
     * @param dest 输入，目标目录或文件
     * @param isOnlyOperateSrc 输入，是否仅操作源目录或文件，如删除操作...
     * @return 成功返回0，其他请查看错误码
     */
    int writePathToController(int16u cmdId, const std::string &src, const std::string &dest, bool isOnlyOperateSrc = false);

    // 协调状态
    int _nCoordinationState = COORDINATION_SWITCH_DONE;

    /**
     * @brief 松抱闸心跳线程
     */
    void releaseBrakeCountThread();

    // 松抱闸心跳计数
    int32u _brakeCount = 0;

    // 是否运行松抱闸心跳计数
    bool _isRunCountThread = false;

    // 是否是第一条松抱闸指令
    bool _isFirstCmd = true;

    // 松抱闸当前轴号
    int _releaseBrakeCurAxisNo = 0;

    // 是否退出松抱闸线程
    bool _isCloseBrakeThread = false;

    // 第一条松抱闸指令锁
    std::mutex _firstCmdMtx;
};
}  // namespace InoRobBusiness
