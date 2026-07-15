#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../Project/Project_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

/// <summary>
/// 调试模式
/// </summary>
enum class DebugMode_V1
{
    /// <summary>
    /// 编程
    /// </summary>
    EDIT_V1 = 0,
    /// <summary>
    /// 调试
    /// </summary>
    DEBUG_V1 = 1,
};

/// <summary>
/// 轨迹恢复标识
/// </summary>
enum class TrajectoryRecoveryFlag_V1
{
    /// <summary>
    /// 当前处于运行中，不允许清除轨迹，也不允许发启动命令
    /// </summary>
    INVALID_V1 = -1,
    /// <summary>
    /// 已设置过了轨迹恢复的执行策略，后者不需要执行轨迹恢复
    /// </summary>
    SETTED_OR_NEEDLESS_V1 = 0,
    /// <summary>
    /// 需要轨迹恢复，且在运动行
    /// </summary>
    IN_MOVELINE_V1 = 1,
    /// <summary>
    /// 需要轨迹恢复，但不在运动行
    /// </summary>
    NOT_IN_MOVELINE_V1 = 2,
    /// <summary>
    /// ARM缓存区有数据，但DSP未保存轨迹信息
    /// </summary>
    DSP_NOT_HAVE_MSG_V1 = 3,
};

/// <summary>
/// 轨迹恢复执行策略
/// </summary>
enum class TrajectoryRecoveryExcuteMode_V1
{
    /// <summary>
    /// 放弃
    /// </summary>
    GIVEUP_V1 = 0,
    /// <summary>
    /// 执行
    /// </summary>
    EXCUTE_V1,
};

/// <summary>
/// 启动释放策略对应的对象类型
/// </summary>
enum class StartReleaseObjType_V1
{
    /// <summary>
    /// 示教器
    /// </summary>
    TP_V1 = 0,
    /// <summary>
    /// PC编程平台
    /// </summary>
    PC_V1,
};

/// <summary>
/// 启动释放策略
/// </summary>
enum class StartReleaseMode_V1
{
    /// <summary>
    /// 需要长按维持运行状态
    /// </summary>
    PRESSING_V1 = 0,
    /// <summary>
    /// 单击则会一直保持运行，需按停止按钮进行停止
    /// </summary>
    CLICK_V1,
};

#define CONTROLLER_LOG_TYPE_COUNT_V1 8  // 控制器日志类型个数

/**
 * @brief 控制器日志类型
 */
enum class ControllerLogType_V1 : short
{
    // 机器人
    ROBOT_V1 = 0,
    // EtherCat
    ETHERCAT_V1,
    // IRlink
    IRLINK_V1,
    // 译码
    TRANS_V1,
    // arm&dsp
    ARMDSP_V1,
    // RtKine
    RTKINE_V1,
    // shm
    SHM_V1,
    // 资源
    GD_V1,
    // 控制器日志类型数量
    COUNT_V1,
};

/**
 * @brief 控制器日志等级
 */
enum class ControllerLogLevel_V1 : short
{
    // 无
    NONE_V1 = 0,
    // 警报
    ALERT_V1,
    // 临界值
    CRIT_V1,
    // 错误
    ERR_V1,
    // 报警
    WARNING_V1,
    // 通知
    NOTICE_V1,
    // 信息
    INFO_V1,
    // 调试
    DEBUG_V1,
    // 控制器日志等级类型个数
    COUNT_V1,
};

/**
 * @brief 控制器日志开关
 */
struct ControllerLogSwitchInfo_V1
{
    ControllerLogSwitchInfo_V1()
    {
        initialize();
    }

    void initialize()
    {
        mode = 0;
        level = 0;
    }

    ControllerLogSwitchInfo_V1 &operator=(const ControllerLogSwitchInfo_V1 &other)
    {
        this->mode = other.mode;
        this->level = other.level;

        return (*this);
    }

    bool operator==(const ControllerLogSwitchInfo_V1 &other) const
    {
        if (this->mode != other.mode)
        {
            return false;
        }

        if (this->level != other.level)
        {
            return false;
        }

        return true;
    }

    short mode;   // 日志开关
    short level;  // 日志等级
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Debuger_V1: public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static DebugMode_V1 DebugMode_ToProxy(DebugMode debugMode);
    static DebugMode DebugMode_FromProxy(DebugMode_V1 debugMode_V1);

    static TrajectoryRecoveryFlag_V1 TrajectoryRecoveryFlag_ToProxy(TrajectoryRecoveryFlag trajectoryRecoveryFlag);
    static TrajectoryRecoveryFlag TrajectoryRecoveryFlag_FromProxy(TrajectoryRecoveryFlag_V1 trajectoryRecoveryFlag_V1);

    static TrajectoryRecoveryExcuteMode_V1 TrajectoryRecoveryExcuteMode_ToProxy(TrajectoryRecoveryExcuteMode trajectoryRecoveryExcuteMode);
    static TrajectoryRecoveryExcuteMode TrajectoryRecoveryExcuteMode_FromProxy(TrajectoryRecoveryExcuteMode_V1 trajectoryRecoveryExcuteMode_V1);

    static StartReleaseObjType_V1 StartReleaseObjType_ToProxy(StartReleaseObjType startReleaseObjType);
    static StartReleaseObjType StartReleaseObjType_FromProxy(StartReleaseObjType_V1 startReleaseObjType_V1);

    static StartReleaseMode_V1 StartReleaseMode_ToProxy(StartReleaseMode startReleaseMode);
    static StartReleaseMode StartReleaseMode_FromProxy(StartReleaseMode_V1 startReleaseMode_V1);

    static ControllerLogType_V1 ControllerLogType_ToProxy(ControllerLogType controllerLogType);
    static ControllerLogType ControllerLogType_FromProxy(ControllerLogType_V1 controllerLogType_V1);

    static ControllerLogLevel_V1 ControllerLogLevel_ToProxy(ControllerLogLevel controllerLogLevel);
    static ControllerLogLevel ControllerLogLevel_FromProxy(ControllerLogLevel_V1 controllerLogLevel_V1);

    static bool ControllerLogSwitchInfo_ToProxy(const ControllerLogSwitchInfo &controllerLogSwitchInfo, ControllerLogSwitchInfo_V1 &controllerLogSwitchInfo_V1);
    static bool ControllerLogSwitchInfo_FromProxy(const ControllerLogSwitchInfo_V1 &controllerLogSwitchInfo_V1, ControllerLogSwitchInfo &controllerLogSwitchInfo);

#pragma endregion

#pragma region 构造与析构

private:
    IDebuger *_debuger = nullptr;

public:
    Debuger_V1(IDebuger *debuger);
    ~Debuger_V1();

#pragma endregion

#pragma region 业务逻辑

private:
    void DebugModeChangedHandler(DebugMode debugMode);

public:
    /// <summary>
    /// 设置用户的调试模式（编程or调试）
    /// </summary>
    /// <param name="mode">输入，任务id</param>
    void setDebugMode(DebugMode_V1 mode);
    /// <summary>
    /// 获取当前用户的调试模式（编程or调试）
    /// </summary>
    /// <returns>当前调试模式</returns>
    DebugMode_V1 getDebugMode();
    // 调试模式变化信号
    rsignal<DebugMode_V1> DebugModeChanged;

    /// <summary>
    /// 启动运行（调试）
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int startRunningInDebug(TrajectoryRecoveryFlag_V1 &flag);
    int startRunningInAuto(TrajectoryRecoveryFlag_V1 &flag);
    int writeStartRunning();
    /// <summary>
    /// 停止运行（调试）
    /// </summary>
    /// <param name="isRmtIoEnable">输入，远程IO控制权下是否可以停止</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int stopRunningInDebug(bool isRmtIoEnable);
    int stopRunningInAuto(bool isRmtIoEnable);
    int writeStopRunning();
    /// <summary>
    /// 执行上一步
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int backStep();
    /// <summary>
    /// 执行下一步
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int nextStep(TrajectoryRecoveryFlag_V1 &flag);
    int writeNextStep();
    /// <summary>
    /// 暂停
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int pause();

    /// <summary>
    /// 获取轨迹恢复标识（可执行状态）
    /// </summary>
    /// <param name="flag">输出，标识（可执行状态）</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int trajectoryRecoveryFlag(TrajectoryRecoveryFlag_V1 &flag);
    /// <summary>
    /// 设置轨迹恢复的执行策略
    /// </summary>
    /// <param name="mode">输入，执行策略（执行或放弃）</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int trajectoryRecoveryExcute(TrajectoryRecoveryExcuteMode_V1 mode);

    /// <summary>
    /// 设置指定类型对象的启动释放策略
    /// </summary>
    /// <param name="objType">输入，对象类型</param>
    /// <param name="mode">输入，启动释放策略</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int writeStartReleaseMode(const StartReleaseObjType_V1 &objType, const StartReleaseMode_V1 &mode);
    /// <summary>
    /// 获取指定类型对象的启动释放策略
    /// </summary>
    /// <param name="objType">输入，对象类型</param>
    /// <param name="mode">输出，启动释放策略</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    int readStartReleaseMode(const StartReleaseObjType_V1 &objType, StartReleaseMode_V1 &mode);
    /// <summary>
    /// 设置当前的启动释放策略
    /// </summary>
    void setCurStartReleaseMode(const StartReleaseObjType_V1 &objType, const StartReleaseMode_V1 &mode);
    /// <summary>
    /// 获取当前的启动释放策略
    /// </summary>
    StartReleaseMode_V1 getCurStartReleaseMode(const StartReleaseObjType_V1 &objType);

    /**
     * @brief 检查启动释放策略保存权限
     * @return true-权限符合
     */
    bool checkStartReleaseSavePermission();

    /**
     * @brief 修改指令中的点位（调试中修改点）
     * @param programFileName 输入，所属程序文件名称
     * @param taskId 输入，所属任务id
     * @param pointType 输入，点位类型
     * @param pointNo 输入，点位序号
     * @param toolNo 输入，指令中包含的工具号
     * @param wobjNo 输入，指令中包含的工件号
     * @param proArr 输入，程序指令内容（当局部点位在调试中修改时，需要自动保存文件是需要用到）
     * @return 成功返回0，其他请见错误码
     */
    int modifyCmdPoint(const std::string &programFileName, int taskId, PointType_V1 pointType, int pointNo,
                       int toolNo, int wobjNo, const std::vector<string> &proArr = std::vector<string>());

    /**
     * @brief 获取运行持续时间
     * @return 运行时间 格式 00:00:00
     */
    std::string getRunningTime();

    /**
     * @brief 将控制器日志开关参数集合下发到控制器
     * @param infos 输入，控制器日志开关参数集合
     */
    int writeControllerLogSwitchInfo(ControllerLogSwitchInfo_V1 infos[CONTROLLER_LOG_TYPE_COUNT_V1]);
    /**
     * @brief 从控制器读取控制器日志开关参数集合
     * @param infos 输出，控制器日志开关参数集合
     */
    int readControllerLogSwitchInfo(ControllerLogSwitchInfo_V1 infos[CONTROLLER_LOG_TYPE_COUNT_V1]);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
