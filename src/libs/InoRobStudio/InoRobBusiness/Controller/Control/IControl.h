#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "../Monitor/IMonitor.h"
#include "../Motion/IMotion.h"

namespace InoRobBusiness
{
#pragma region 常量与数据类型

/// <summary>
/// 设备模式
/// </summary>
enum class DeviceMode : int
{
    /// <summary>
    /// 未知
    /// </summary>
    DEV_MODE_UNKNOW = 0,
    /// <summary>
    /// 手动低速模式
    /// </summary>
    DEV_MODE_MANUAL_LOW,
    /// <summary>
    /// 手动高速模式
    /// </summary>
    DEV_MODE_MANUAL_HIGH,
    /// <summary>
    /// 自动模式
    /// </summary>
    DEV_MODE_AUTO,
};

/// <summary>
/// 钥匙触发方式
/// </summary>
enum class KeyTrigMethod : int8u
{
    /// <summary>
    /// 仅示教器权限有效
    /// </summary>
    KEY_TRIG_LOCAL = 0,
    /// <summary>
    /// 所有控制权有效
    /// </summary>
    KEY_TRIG_ALL = 1,
};

// 协调状态
enum CoordinationStateEnum
{
    COORDINATION_SWITCH_DONE = 0,  // 协调切换完成
    COORDINATION_ON = 1,           // 协调开启中
    COORDINATION_OFF = 2           // 协调关闭中
};

// 控制器操作类型（询问控制器指定的操作类型是否被允许）
enum ControllerOperationType : int16u
{
    CONTROLLER_OPERATION_TYPE_MAINT_SETTING = 0,    // 维保设置
    CONTROLLER_OPERATION_TYPE_MAINT_THRESHOLD = 1,  // 维保设置阈值
    CONTROLLER_OPERATION_TYPE_MAINT_BACKUP = 2,     // 维保备份加载
};

/// <summary>
/// wifi密码修改结果
/// </summary>
enum class WifiPasswordModifyResult : int
{
    /// <summary>
    /// 未知
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_UNKNOW = -1,
    /// <summary>
    /// 修改失败
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_FAIL,
    /// <summary>
    /// 修改成功
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_SUCCESS,
    /// <summary>
    /// 两次密码一样，修改失败
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_EQUAL,
};

#pragma pack(1)

/**
 * @brief 系统更新信息（控制器升降级进度信息）
 */
struct SystemUpdateInfo
{
    SystemUpdateInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        status = 0;
        progress = 0;
        memset(msg, 0, sizeof(msg));
    }

    SystemUpdateInfo &operator=(const SystemUpdateInfo &other)
    {
        this->status = other.status;
        this->progress = other.progress;
        memcpy(&this->msg[0], &other.msg[0], 80 * sizeof(char));

        return (*this);
    }

    short status;    // 下位机通信：0正在升降级；1升降级成功；其它表示失败见文档
    short progress;  // 进度信息 0~100 %
    char msg[80];    // 描述信息
};

#pragma pack()

#pragma pack(1)

/**
 * @brief 控制器Wifi信息
 */
struct ControllerWifiInfo
{
    ControllerWifiInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(wifiName, 0, sizeof(wifiName));
        memset(wifiIp, 0, sizeof(wifiIp));
        wifiLinkStatus = 0;
    }

    ControllerWifiInfo &operator=(const ControllerWifiInfo &other)
    {
        memcpy(&this->wifiName[0], &other.wifiName[0], 32 * sizeof(char));
        memcpy(&this->wifiIp[0], &other.wifiIp[0], 16 * sizeof(char));
        this->wifiLinkStatus = other.wifiLinkStatus;

        return (*this);
    }

    char wifiName[32];  // Wifi SSID
    char wifiIp[16];
    int wifiLinkStatus;
};

#pragma pack()

#pragma endregion 常量与数据类型

/*
    操控
    Create by WuJian at 2023/7/27 创建，合并使能、急停、运行模式、机械锁定、动态制动、协调功能。
*/
class INOROBBUSINESS_CLASS IControl : public QObject
{
    Q_OBJECT

public:
    virtual ~IControl()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 使能（true：上使能，false：下使能）
    virtual int SetEnable(bool status) = 0;

    // 急停（true：急停，false：去急停）
    virtual int SetEmergency(bool status) = 0;

    // 协作专用 本体上电
    virtual int SetCoRobotBodyPowerState(CoRobotBodyPowerState status) = 0;

    // 设置wifi密码
    virtual int SetControllerWifiPassword(const std::string &password) = 0;

    // 获取wifi密码修改结果
    virtual int GetWifiPasswordModifyResult(WifiPasswordModifyResult &result) = 0;

    // 设置Wifi频段（协作）
    virtual int SetControllerWifiFrequencyBand(bool enable) = 0;

    // 获取控制器WiFi信息（协作）
    virtual int GetControllerWifiInfo(ControllerWifiInfo &info) = 0;

    // 设置夹持器三位置使能状态
    virtual int SetGripperThreePositionEnable(bool enable) = 0;

    // 获取单电柜运行模式使能状态（协作）
    virtual int GetSingleControllerRunModeStatus(bool &status) = 0;

    // 设置单电柜运行模式使能（协作）
    virtual int SetSingleControllerRunModeEnable(bool enable) = 0;

    // 获取单电柜运行模式使能设置结果（协作）
    virtual int GetSingleControllerRunModeEnable(bool &enable) = 0;

    // 清除报警
    virtual int ClearWarning(PressState state) = 0;

    // 运行模式
    virtual bool SetRunMode(RunMode mode) = 0;

    // 设置设备（机器人）模式
    virtual int SetDeviceMode(DeviceMode mode) = 0;

    // 获取设备（机器人）模式
    virtual int GetDeviceMode(DeviceMode &mode) = 0;

    //通知机型参数文件更新
    virtual int RobotParamFileChange(char *info) = 0;

    // 启动伺服监控
    virtual int RobotParamServoStart(char *info) = 0;

    // 停止伺服监控
    virtual int RobotParamServoStop() = 0;

    // 获取当前伺服参数数据
    virtual int RobotParamServoCurrent(string &info) = 0;

    // 读取参数更新状态
    virtual int RobotParamUpdateStatusRead(string &info) = 0;

    /**
     * @brief 开启限速
     * @return 成功返回0，其他请见错误码
     */
    virtual int activateSpeedLimit() = 0;

    /**
     * @brief 关闭限速
     * @return 成功返回0，其他请见错误码
     */
    virtual int turnoffSpeedLimit() = 0;

    /**
     * @brief 是否已经开启限速
     */
    virtual bool isActivatedSpeedLimit() = 0;

    // 机械锁定
    virtual bool SetMechLock(bool status) = 0;

    // 动态制动（true：开启，false：关闭）
    virtual bool SetDynamicBrake(bool status) = 0;

    // 机器人协调机械单元
    // name：机械单元名称（为空表示关闭机器人协调）
    virtual bool SetCooperate(const string &mechUnitName) = 0;

    /**
     * @brief 设置协调状态
     * @param coordSts 协调状态
     */
    virtual void setCoordinationState(int coordSts) = 0;

    /**
     * @brief 获取协调状态
     * @return 协调状态
     */
    virtual int getCoordinationState() = 0;

    /*!
     * \brief 设置协调
     * \param status 状态
     * \return true成功 false失败
     */
    virtual bool setCooperate(const bool status) = 0;

    /**
     * @brief 系统升级（控制器升级）
     * @param isUpdateBsp 是否更新bsp底层系统镜像，25版本及以后才能设置不更新
     * @param isTP 是否执行示教器相关的系统升级，示教器与PC编程平台走的通讯码和发送的内容不同
     * @return 成功返回0，其他请见错误码
     */
    virtual int systemUpgrade(bool isUpdateBsp = true, bool isTP = true) = 0;
    /**
     * @brief 将系统（控制器）降级为一个固定版本
     * @return 成功返回0，其他请见错误码
     */
    virtual int systemDegrade() = 0;
    /**
     * @brief 状态检查，是否可以进行系统升降级
     */
    virtual bool isSystemCanUpdate() = 0;
    /**
     * @brief 获取系统升降级的过程信息
     * @param info 过程信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int readSystemUpdateInfo(SystemUpdateInfo &info) = 0;

    /* 控制器文件夹与文件操作相关 */
    /**
     * @brief 创建控制器文件夹
     * @param dir 控制器文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int createDir(const std::string &dir) = 0;
    /**
     * @brief 拷贝控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int copyDir(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 剪切控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int cutDir(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 重命名控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int renameDir(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 删除控制器文件夹
     * @param dir 控制器文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int delDir(const std::string &dir) = 0;
    /**
     * @brief 拷贝控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int copyFile(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 剪切控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int cutFile(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 重命名控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int renameFile(const std::string &src, const std::string &dest) = 0;
    /**
     * @brief 删除控制器文件
     * @param path 控制器文件路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int delFile(const std::string &path) = 0;

    /**
     * @brief 读取松抱闸状态
     * @param stateArray 松抱闸状态数组，代表J1-J6的 抱闸状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int readBrakeState(char stateArray[6]) = 0;

    /**
     * @brief 发送松抱闸指令
     * @param brake_cmd 传入指令类型（1-合抱闸，0-松抱闸）
     * @param brake_count 传入当前计数值，用于判断程序崩溃或是断开连接
     * @param axis_number 当前轴号
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeBrakeState(char brake_cmd, int32u brake_count, int axis_number, bool isPrintMessage = true) = 0;

    /**
     * @brief 清除松抱闸计数
     */
    virtual void cleanBrakeCount() = 0;

    /**
     * @brief 设置为第一条松抱闸指令
     */
    virtual void setBrakeFirstCmd(bool bFlag) = 0;

    /**
     * @brief 设置为第一条松抱闸指令
     */
    virtual void setBrakeCurAxisNo(int axisNo) = 0;

    /**
     * @brief 设置松抱闸线程状态
     * @param isRun 是否运行  true - 运行  false - 挂起
     */
    virtual void setBrakeThreadState(bool isRun) = 0;

    /**
     * @brief 关闭松抱闸线程
     */
    virtual void closeBrakeThread() = 0;

    // 询问控制器指定的操作类型是否被允许
    virtual bool ControllerOperationValid(ControllerOperationType controllerOperationType) = 0;

    /**
     * @brief 从控制器下载文件到本地
     * @param localPath 输入，文件本地路径
     * @param ctrlPath 输入，文件控制器路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int downloadFile(const std::string &localPath, const std::string &ctrlPath) = 0;

    /**
     * @brief 拖动示教记点结果反馈(协作)
     * @param status 1-记点成功 0-记点失败
     */
    virtual int autoRecordPoint(int status) = 0;

    /**
     * @brief 获取是否刷机后第一次启动状态(协作)
     * @param status 是否刷机后第一次启动状态
     */
    virtual int getFirstBootStatus(bool &status) = 0;
Q_SIGNALS:
    /**
     * @brief 设备模式改变信号
     */
    void deviceModeChanged(DeviceMode mode);
};
}  // namespace InoRobBusiness
