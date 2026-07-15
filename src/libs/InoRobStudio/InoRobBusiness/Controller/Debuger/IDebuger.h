#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "../../Project/IProject.h"
#include "CmdMessageBox/ICmdMessageBox.h"

/*
    Create by LiaoChuanMing at 2023/11/13，调试功能实现
*/
namespace InoRobBusiness
{

#pragma region 常量与数据类型

/// <summary>
/// 调试模式
/// </summary>
enum class DebugMode
{
    /// <summary>
    /// 编程
    /// </summary>
    EDIT = 0,
    /// <summary>
    /// 调试
    /// </summary>
    DEBUG,
};

/// <summary>
/// 轨迹恢复标识
/// </summary>
enum class TrajectoryRecoveryFlag
{
    /// <summary>
    /// 当前处于运行中，不允许清除轨迹，也不允许发启动命令
    /// </summary>
    INVALID = -1,
    /// <summary>
    /// 已设置过了轨迹恢复的执行策略，后者不需要执行轨迹恢复
    /// </summary>
    SETTED_OR_NEEDLESS = 0,
    /// <summary>
    /// 需要轨迹恢复，且在运动行
    /// </summary>
    IN_MOVELINE = 1,
    /// <summary>
    /// 需要轨迹恢复，但不在运动行
    /// </summary>
    NOT_IN_MOVELINE = 2,
    /// <summary>
    /// ARM缓存区有数据，但DSP未保存轨迹信息
    /// </summary>
    DSP_NOT_HAVE_MSG = 3,
};

/// <summary>
/// 轨迹恢复执行策略
/// </summary>
enum class TrajectoryRecoveryExcuteMode
{
    /// <summary>
    /// 放弃
    /// </summary>
    GIVEUP = 0,
    /// <summary>
    /// 执行
    /// </summary>
    EXCUTE,
};

/// <summary>
/// 启动释放策略对应的对象类型
/// </summary>
enum class StartReleaseObjType
{
    /// <summary>
    /// 示教器
    /// </summary>
    TP = 0,
    /// <summary>
    /// PC编程平台
    /// </summary>
    PC,
};

/// <summary>
/// 启动释放策略
/// </summary>
enum class StartReleaseMode
{
    /// <summary>
    /// 需要长按维持运行状态
    /// </summary>
    PRESSING = 0,
    /// <summary>
    /// 单击则会一直保持运行，需按停止按钮进行停止
    /// </summary>
    CLICK,
};

#define CONTROLLER_LOG_TYPE_COUNT 8  // 控制器日志类型个数

/**
 * @brief 控制器日志类型
 */
enum class ControllerLogType : short
{
    // 机器人
    ROBOT = 0,
    // EtherCat
    ETHERCAT,
    // IRlink
    IRLINK,
    // 译码
    TRANS,
    // arm&dsp
    ARMDSP,
    // RtKine
    RTKINE,
    // shm
    SHM,
    // 资源
    GD,
    // 控制器日志类型数量
    COUNT,
};

/**
 * @brief 控制器日志等级
 */
enum class ControllerLogLevel : short
{
    // 无
    NONE = 0,
    // 警报
    ALERT,
    // 临界值
    CRIT,
    // 错误
    ERR,
    // 报警
    WARNING,
    // 通知
    NOTICE,
    // 信息
    INFO,
    // 调试
    DEBUG,
    // 控制器日志等级类型个数
    COUNT,
};

/// <summary>
/// 光标跟随模式
/// </summary>
enum class CursorFollowMode
{
    /// <summary>
    /// 光标和程序
    /// </summary>
    CURSOR_AND_PROG,
    /// <summary>
    /// 光标和程序都不跟随
    /// </summary>
    NONE
};

/// <summary>
/// 程序跟随光标的模式
/// </summary>
enum class ProgCursorMode
{
    /// <summary>
    /// 跟随编译行（黄色光标）
    /// </summary>
    PROG_FOLLOW_RUNNING = 0,
    /// <summary>
    /// 跟随机器人运动行（蓝色光标）
    /// </summary>
    PROG_FOLLOW_MOTION
};

/**
 * @brief 控制器日志开关
 */
struct ControllerLogSwitchInfo
{
    ControllerLogSwitchInfo()
    {
        initialize();
    }

    void initialize()
    {
        mode = 0;
        level = 0;
    }

    ControllerLogSwitchInfo &operator=(const ControllerLogSwitchInfo &other)
    {
        this->mode = other.mode;
        this->level = other.level;

        return (*this);
    }

    bool operator==(const ControllerLogSwitchInfo &other) const
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

#pragma endregion 常量与数据类型

class INOROBBUSINESS_CLASS IDebuger : public QObject
{
    Q_OBJECT

public:
    virtual ~IDebuger()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /// <summary>
    /// 设置用户的调试模式（编程or调试）
    /// </summary>
    /// <param name="mode">输入，任务id</param>
    virtual void setDebugMode(DebugMode mode) = 0;
    /// <summary>
    /// 获取当前用户的调试模式（编程or调试）
    /// </summary>
    /// <returns>当前调试模式</returns>
    virtual DebugMode getDebugMode() = 0;

    /// <summary>
    /// 启动运行（调试）
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int startRunningInDebug(TrajectoryRecoveryFlag &flag) = 0;
    virtual int startRunningInAuto(TrajectoryRecoveryFlag &flag) = 0;
    virtual int writeStartRunning() = 0;
    /// <summary>
    /// 停止运行（调试）
    /// </summary>
    /// <param name="isRmtIoEnable">输入，远程IO控制权下是否可以停止</param>
    /// <param name="isCheck">输入，是否检查权限等</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int stopRunningInDebug(bool isRmtIoEnable, bool isCheck = true) = 0;
    virtual int stopRunningInAuto(bool isRmtIoEnable, bool isCheck = true) = 0;
    virtual int writeStopRunning() = 0;
    /// <summary>
    /// 执行上一步
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int backStep() = 0;
    /// <summary>
    /// 执行下一步
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int nextStep(TrajectoryRecoveryFlag &flag) = 0;
    virtual int writeNextStep() = 0;
    /// <summary>
    /// 暂停
    /// </summary>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int pause() = 0;

    /// <summary>
    /// 获取轨迹恢复标识（可执行状态）
    /// </summary>
    /// <param name="flag">输出，标识（可执行状态）</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int trajectoryRecoveryFlag(TrajectoryRecoveryFlag &flag) = 0;
    /// <summary>
    /// 设置轨迹恢复的执行策略
    /// </summary>
    /// <param name="mode">输入，执行策略（执行或放弃）</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int trajectoryRecoveryExcute(TrajectoryRecoveryExcuteMode mode) = 0;

    /// <summary>
    /// 设置指定类型对象的启动释放策略
    /// </summary>
    /// <param name="objType">输入，对象类型</param>
    /// <param name="mode">输入，启动释放策略</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int writeStartReleaseMode(const StartReleaseObjType &objType, const StartReleaseMode &mode) = 0;
    /// <summary>
    /// 获取指定类型对象的启动释放策略
    /// </summary>
    /// <param name="objType">输入，对象类型</param>
    /// <param name="mode">输出，启动释放策略</param>
    /// <returns>成功返回0，失败请查看错误码</returns>
    virtual int readStartReleaseMode(const StartReleaseObjType &objType, StartReleaseMode &mode) = 0;
    /// <summary>
    /// 设置当前的启动释放策略
    /// </summary>
    virtual void setCurStartReleaseMode(const StartReleaseObjType &objType, const StartReleaseMode &mode) = 0;
    /// <summary>
    /// 获取当前的启动释放策略
    /// </summary>
    virtual StartReleaseMode getCurStartReleaseMode(const StartReleaseObjType &objType) = 0;

    /**
     * @brief 检查启动释放策略保存权限
     * @return true-权限符合
     */
    virtual bool checkStartReleaseSavePermission() = 0;

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
    virtual int modifyCmdPoint(const std::string &programFileName, int taskId, PointType pointType, int pointNo,
                               int toolNo, int wobjNo, const std::vector<std::string> &proArr = std::vector<std::string>()) = 0;
    /**
     * @brief 热调点模式下修改点位数据
     * @param programFileName 所属程序文件名称
     * @param point 点位数据
     * @param pointType 点类型
     * @param proArr 输入，程序指令内容（当局部点位在调试中修改时，需要自动保存文件是需要用到）
     * @return 成功返回0，其他请见错误码
     */
    virtual int modifyPointRT(const std::string &fileName, const MRobPosItem &point, PointType pointType,
                              const std::vector<std::string> &proArr = std::vector<std::string>()) = 0;
    /**
     * @brief 获取运行持续时间
     * @return 运行时间 格式 00:00:00
     */
    virtual std::string getRunningTime() = 0;

    /**
     * @brief 将控制器日志开关参数集合下发到控制器
     * @param infos 输入，控制器日志开关参数集合
     */
    virtual int writeControllerLogSwitchInfo(ControllerLogSwitchInfo infos[CONTROLLER_LOG_TYPE_COUNT]) = 0;
    /**
     * @brief 从控制器读取控制器日志开关参数集合
     * @param infos 输出，控制器日志开关参数集合
     */
    virtual int readControllerLogSwitchInfo(ControllerLogSwitchInfo infos[CONTROLLER_LOG_TYPE_COUNT]) = 0;

    /**
     * @brief 检查修改范围
     * @param pos1 点位数据1
     * @param pos2 点位数据2
     * @return
     */
    virtual bool checkModifyRange(std::vector<double> &pos1, std::vector<double> &pos2) = 0;

    /**
     * @brief checkUSBFlashDrive 手持上需检查示教器U盘挂载
     * @return
     */
    virtual bool checkUSBFlashDrive() = 0;
    /**
     * @brief 读取程序光标跟随模式
     * @return int 返回光标跟随模式的值。
     */
    virtual int readProgramCursorMode() = 0;

    /**
     * @brief 写入程序光标跟随模式
     * @param mode 光标跟随，0：跟随预编译行 1：跟随运动行
     * @param isNeedPrint 是否需要打印提示
     * @return 如果设置成功返回true，否则返回false
     */
    virtual bool writeProgramCursorMode(int mode, bool isNeedPrint = true) = 0;
#pragma region 指令弹框
    /**
     * @brief 指令弹框
     */
    virtual ICmdMessageBox *getCmdMessageBox() = 0;

Q_SIGNALS:
    // 调试模式变化信号
    void debugModeChanged(DebugMode mode);
};
}  // namespace InoRobBusiness
