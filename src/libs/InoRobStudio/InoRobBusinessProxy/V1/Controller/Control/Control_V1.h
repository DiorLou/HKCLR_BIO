#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
/// <summary>
/// 设备模式
/// </summary>
enum class DeviceMode_V1 : int
{
    /// <summary>
    /// 未知
    /// </summary>
    DEV_MODE_UNKNOW_V1 = 0,
    /// <summary>
    /// 手动低速模式
    /// </summary>
    DEV_MODE_MANUAL_LOW_V1,
    /// <summary>
    /// 手动高速模式
    /// </summary>
    DEV_MODE_MANUAL_HIGH_V1,
    /// <summary>
    /// 自动模式
    /// </summary>
    DEV_MODE_AUTO_V1,
};

// 协调状态
enum CoordinationStateEnum_V1
{
    COORDINATION_SWITCH_DONE_V1 = 0,  // 协调切换完成
    COORDINATION_ON_V1 = 1,           // 协调开启中
    COORDINATION_OFF_V1 = 2           // 协调关闭中
};

/// <summary>
/// wifi密码修改结果
/// </summary>
enum class WifiPasswordModifyResult_V1 : int
{
    /// <summary>
    /// 未知
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_UNKNOW_V1 = -1,
    /// <summary>
    /// 修改失败
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_FAIL_V1,
    /// <summary>
    /// 修改成功
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_SUCCESS_V1,
    /// <summary>
    /// 两次密码一样，修改失败
    /// </summary>
    WIFI_PASSWORD_MODIFY_RESULT_EQUAL_V1,
};

#pragma pack(1)

/**
 * @brief 系统更新信息（控制器升降级进度信息）
 */
struct SystemUpdateInfo_V1
{
    SystemUpdateInfo_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        status = 0;
        progress = 0;
        memset(msg, 0, sizeof(msg));
    }

    SystemUpdateInfo_V1 &operator=(const SystemUpdateInfo_V1 &other)
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

class INOROBBUSINESSPROXY_CLASS Control_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

private:
    static DeviceMode_V1 DeviceMode_ToProxy(DeviceMode deviceMode);
    static DeviceMode DeviceMode_FromProxy(DeviceMode_V1 deviceMode_V1);

    static CoordinationStateEnum_V1 CoordinationStateEnum_ToProxy(CoordinationStateEnum coordinationStateEnum);
    static CoordinationStateEnum CoordinationStateEnum_FromProxy(CoordinationStateEnum_V1 coordinationStateEnum_V1);

    static WifiPasswordModifyResult_V1 WifiPasswordModifyResult_ToProxy(WifiPasswordModifyResult wifiPasswordModifyResult);
    static WifiPasswordModifyResult WifiPasswordModifyResult_FromProxy(WifiPasswordModifyResult_V1 wifiPasswordModifyResult_V1);

    static bool SystemUpdateInfo_ToProxy(const SystemUpdateInfo &systemUpdateInfo, SystemUpdateInfo_V1 &systemUpdateInfo_V1);
    static bool SystemUpdateInfo_FromProxy(const SystemUpdateInfo_V1 &systemUpdateInfo_V1, SystemUpdateInfo &systemUpdateInfo);

#pragma endregion

#pragma region 构造与析构

private:
    IControl *_control = nullptr;

public:
    Control_V1(IControl *control);
    ~Control_V1();

#pragma endregion

#pragma region 业务逻辑

private:
    void deviceModeChangedHandler(DeviceMode data);

public:
    // 使能（true：上使能，false：下使能）  -----  已测
    int SetEnable(bool status);

    // 急停（true：急停，false：去急停）  -----  已测
    int SetEmergency(bool status);

    // 协作专用 本体上电
    // int SetCoRobotBodyPowerState(CoRobotBodyPowerState status);

    // 设置wifi密码
    int SetControllerWifiPassword(const std::string &password);

    // 获取wifi密码修改结果  -----  已测
    int GetWifiPasswordModifyResult(WifiPasswordModifyResult_V1 &result_V1);

    // 设置夹持器三位置使能状态  -----  已测
    int SetGripperThreePositionEnable(bool enable);

    // 清除报警
    // int ClearWarning(PressState state);

    // 运行模式
    // bool SetRunMode(RunMode mode);

    // 设置设备（机器人）模式
    int SetDeviceMode(DeviceMode_V1 mode);

    // 获取设备（机器人）模式
    int GetDeviceMode(DeviceMode_V1 &mode_V1);

    /**
     * @brief 开启限速  -----  已测
     * @return 成功返回0，其他请见错误码
     */
    int activateSpeedLimit();

    /**
     * @brief 关闭限速  -----  已测
     * @return 成功返回0，其他请见错误码
     */
    int turnoffSpeedLimit();

    /**
     * @brief 是否已经开启限速  -----  已测
     */
    bool isActivatedSpeedLimit();

    // 机械锁定  -----  已测
    bool SetMechLock(bool status);

    // 动态制动（true：开启，false：关闭）  -----  已测
    bool SetDynamicBrake(bool status);

    // 机器人协调机械单元
    // name：机械单元名称（为空表示关闭机器人协调）
    bool SetCooperate(const string &mechUnitName);

    /**
     * @brief 设置协调状态  -----  已测
     * @param coordSts 协调状态
     */
    void setCoordinationState(int coordSts);

    /**
     * @brief 获取协调状态  -----  已测
     * @return 协调状态
     */
    int getCoordinationState();

    /*!
     * \brief 设置协调  -----  已测
     * \param status 状态
     * \return true成功 false失败
     */
    bool setCooperate(const bool status);

    /**
     * @brief 系统升级（控制器升级）  -----  已测
     * @param isUpdateBsp 是否更新bsp底层系统镜像，25版本及以后才能设置不更新
     * @return 成功返回0，其他请见错误码
     */
    int systemUpgrade(bool isUpdateBsp = true);
    /**
     * @brief 将系统（控制器）降级为一个固定版本  -----  已测
     * @return 成功返回0，其他请见错误码
     */
    int systemDegrade();
    /**
     * @brief 状态检查，是否可以进行系统升降级  -----  已测
     */
    bool isSystemCanUpdate();
    /**
     * @brief 获取系统升降级的过程信息  -----  已测
     * @param info 过程信息
     * @return 成功返回0，其他请见错误码
     */
    int readSystemUpdateInfo(SystemUpdateInfo_V1 &infoV1);

    /* 控制器文件夹与文件操作相关 */
    /**
     * @brief 创建控制器文件夹
     * @param dir 控制器文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    int createDir(const std::string &dir);
    /**
     * @brief 拷贝控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    int copyDir(const std::string &src, const std::string &dest);
    /**
     * @brief 剪切控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    int cutDir(const std::string &src, const std::string &dest);
    /**
     * @brief 重命名控制器文件夹
     * @param src 控制器原文件夹路径
     * @param dest 控制器目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    int renameDir(const std::string &src, const std::string &dest);
    /**
     * @brief 删除控制器文件夹
     * @param dir 控制器文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    int delDir(const std::string &dir);
    /**
     * @brief 拷贝控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    int copyFile(const std::string &src, const std::string &dest);
    /**
     * @brief 剪切控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    int cutFile(const std::string &src, const std::string &dest);
    /**
     * @brief 重命名控制器文件
     * @param src 控制器原文件路径
     * @param dest 控制器目标文件路径
     * @return 成功返回0，其他请见错误码
     */
    int renameFile(const std::string &src, const std::string &dest);
    /**
     * @brief 删除控制器文件
     * @param path 控制器文件路径
     * @return 成功返回0，其他请见错误码
     */
    int delFile(const std::string &path);

    /**
     * @brief 读取松抱闸状态  -----  已测
     * @param stateArray 松抱闸状态数组，代表J1-J6的 抱闸状态
     * @return 成功返回0，其他请见错误码
     */
    int readBrakeState(char stateArray[6]);

    /**
     * @brief 发送松抱闸指令  -----  已测
     * @param brake_cmd 传入指令类型（1-合抱闸，0-松抱闸）
     * @param brake_count 传入当前计数值，用于判断程序崩溃或是断开连接
     * @param axis_number 当前轴号
     * @return 成功返回0，其他请见错误码
     */
    int writeBrakeState(char brake_cmd, int32u brake_count, int axis_number, bool isPrintMessage = true);

    /**
     * @brief 清除松抱闸计数
     */
    void cleanBrakeCount();

    /**
     * @brief 设置为第一条松抱闸指令
     */
    void setBrakeFirstCmd(bool bFlag);

    /**
     * 设置为第一条松抱闸指令
     */
    void setBrakeCurAxisNo(int axisNo);

    /**
     * @brief 设置松抱闸线程状态
     * @param isRun 是否运行  true - 运行  false - 挂起
     */
    void setBrakeThreadState(bool isRun);

    /**
     * @brief 关闭松抱闸线程
     */
    void closeBrakeThread();

    /**
     * @brief 设备模式改变信号
     */
    rsignal<DeviceMode_V1> deviceModeChanged;

#pragma endregion
};
}  // namespace InoRobBusinessProxy
