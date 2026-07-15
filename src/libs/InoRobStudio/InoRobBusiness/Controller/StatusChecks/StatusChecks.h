#pragma once
#include "IInoRobBusiness.h"
#include <QObject>
namespace InoRobBusiness
{
/**
 * @brief 用于综合状态的判断
 * 在x32操作系统下最多只能有64个成员，x64位操作系统下128个成员
 */
enum StatusItemGroup : unsigned long long
{
    /**
     * @brief 未知 - 用于处理一些异常情况
     */
    UNKNOW = 0,

    /**
     * @brief 用户权限 - 编辑
     */
    USER_AUTHORITY_EDIT = (1 << 0),
    /**
     * @brief 用户权限 - 管理员
     */
    USER_AUTHORITY_MANAGER = (1 << 1),
    /**
     * @brief 用户权限 - 厂家
     */
    USER_AUTHORITY_FACTORY = (1 << 2),
    /**
     * @brief 用户权限 - 开发者
     */
    USER_AUTHORITY_DEVELOPER = (1 << 3),

    /**
     *@brief 控制权限 - 机器人应用软件
     */
    CTRL_AUTHORITY_TEACHPAD = (1 << 4),
    /**
     *@brief 控制权限 - 远程以太网
     */
    CTRL_AUTHORITY_RMT_ETHERNET = (1 << 5),
    /**
     *@brief 控制权限 - 远程IO单元(手动与自动模式均生效)
     */
    CTRL_AUTHORITY_RMT_IO = (1 << 6),
    /**
     *@brief 控制权限 - 远程IO单元(仅自动模式下升序)
     */
    CTRL_AUTHORITY_RMT_IO_ONLY_AUTO = (1 << 7),
    /**
     *@brief 控制权限 - 远程Modbus
     */
    CTRL_AUTHORITY_RMT_MODBUS = (1 << 8),

    /**
     * @brief 控制器状态 - 已连接
     */
    CTRL_STATUS_CONNECTED = (1 << 9),
    /**
     * @brief 控制器状态 - 上使能
     */
    CTRL_STATUS_ENABLE = (1 << 10),
    /**
     * @brief 控制器状态 - 下使能
     */
    CTRL_STATUS_DISENABLE = (1 << 11),
    /**
     * @brief 控制器状态 - 不在运行状态
     */
    CTRL_STATUS_NOT_RUNNING = (1 << 12),
    /**
     * @brief 控制器状态 - 不在急停状态
     */
    CTRL_STATUS_NOT_EMERGENCY = (1 << 13),
    /**
     * @brief 控制器状态 - 在急停状态
     */
    CTRL_STATUS_EMERGENCY = (1 << 14),
    /**
     * @brief 控制器状态 - 无报警
     */
    CTRL_STATUS_NOERROR = (1 << 15),

    /**
     * @brief 软件端模式 - 编程
     */
    DEBUG_MODE_EDIT = (1 << 16),
    /**
     * @brief 软件端模式 - 调试
     */
    DEBUG_MODE_DEBUG = (1 << 17),

    /**
     * @brief 运行模式 - 手动低速
     */
    DEVICE_MODE_MANUAL_LOW = (1 << 18),
    /**
     * @brief 运行模式 - 手动高速
     */
    DEVICE_MODE_MANUAL_HIGH = (1 << 19),
    /**
     * @brief 运行模式 - 自动
     */
    DEVICE_MODE_AUTO = (1 << 20),

    /**
     * @brief 工程状态 - 已同步到控制器
     */
    PROJECT_STATUS_SYNCED = (1 << 21),
    /**
     * @brief 工程状态 - 当前存在已激活的工程
     */
    PROJECT_STATUS_HAVE_ACTIVE = (1 << 22),

    /**
     * @brief 非静态任务不在运行状态
     */
    NONSTATIC_TASK_RUNNING = (1 << 23),
    /**
     * @brief 控制器状态 - 不在运动中
     */
    CTRL_STATUS_NOT_IN_MOTION = (1 << 24),
};

/**
 * @brief 综合状态检查类（包括用户权限、控制权限、运行状态等）
 * @birth created by liaochuanming on 2024-01-19
 */
class INOROBBUSINESS_CLASS StatusChecks : public QObject
{
	Q_OBJECT
public:
    /**
     * @brief 单例
     */
    static StatusChecks &getInstance();
    /**
     * @brief 依赖注入，在初始化时调用一次即可
     */
    void setDependencies(IUser *pUser, IRCConfig *pRCConfig, IConnection *pConnection, IMonitor *pMonitor,
                         IDebuger *pDebuger, IControl *pControl, IProject *pProject, ITask *pTask, IMotion *pMotion, IControlAuthority *pCtrlAuthority);
    /**
     * @brief 执行检查（内置消息打印）
     * @param statusGroup 状态组合。
     * 如在管理员权限以上并且控制权在机器人应用软件端USER_AUTHORITY_MANAGER | CTRL_AUTHORITY_TEACHPAD
     * @param isTip 是否提示信息
     * @return false - 状态不符合，true - 状态符合
     */
    bool check(unsigned long long statusGroup, bool isTip = true);
    /**
     * @brief 某些特殊功能协作示教器需要检查一定状态使用
     * @brief 参数意义与名称和上述check一致
     */
    bool cobotCheck(unsigned long long statusGroup, bool isTip = true);

private:  // 禁止外部操作
    StatusChecks();
    ~StatusChecks();
	void InitErrorMsg();
    StatusChecks(const StatusChecks &statusCheck) = delete;
    const StatusChecks &operator=(const StatusChecks &statusCheck) = delete;
	
private slots:
    void retranslateMessageCache(const string &languge);
	
private:
    /**
     * @brief 是否需要检查用户权限
     */
    bool isNeedCheckUserAuthority(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查控制权限
     */
    bool isNeedCheckCtrlAuthority(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查控制器状态
     */
    bool isNeedCheckCtrlStatus(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查软件调试模式
     */
    bool isNeedCheckDebugMode(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查设备运行模式
     */
    bool isNeedCheckDeviceMode(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查工程状态
     */
    bool isNeedCheckProjectStatus(unsigned long long statusGroup);
    /**
     * @brief 是否需要检查非静态任务运行状态
     * @param statusGroup
     * @return
     */
    bool isNeedCheckTaskRunning(unsigned long long statusGroup);
    /**
     * @brief 检查用户权限
     * @param authorityGroup 用户权限
     * @return false - 权限不符合，true - 权限符合
     */
    bool checkUserAuthority(StatusItemGroup authority, bool isTip);
    /**
     * @brief 检查控制权限
     * @param authorityGroup 控制权限组合
     * @return false - 权限不符合，true - 权限符合
     */
    bool checkCtrlAuthority(unsigned long long authorityGroup, bool isTip);
    /**
     * @brief 检查控制器状态
     * @param statusGroup 控制器状态组合
     * @return false - 控制器状态不符合，true - 控制器状态符合
     */
    bool checkCtrlStatus(unsigned long long statusGroup, bool isTip);
    /**
     * @brief 检查软件调试模式
     * @param mode 调试模式
     * @return false - 模式不符合，true - 模式符合
     */
    bool checkDebugMode(StatusItemGroup mode, bool isTip);
    /**
     * @brief 检查运行模式
     * @param modeGroup 运行模式
     * @return false - 模式不符合，true - 模式符合
     */
    bool checkDeviceMode(unsigned long long modeGroup, bool isTip);
    /**
     * @brief 检查工程状态
     * @param statusGroup 工程状态组合
     * @return false - 工程状态不符合，true - 工程状态符合
     */
    bool checkProjectStatus(unsigned long long statusGroup, bool isTip);
    /**
     * @brief 检查非静态任务的运行状态
     * @param taskGroup
     * @return
     */
    bool chechNoStaticTaskRunning(unsigned long long taskGroup, bool isTip);
    /**
     * @brief 转换用户权限
     */
    StatusItemGroup convertUserAuthority(EUSER_MODE userMode);
    /**
     * @brief 转换控制权限
     */
    StatusItemGroup convertCtrlAuthority(CtrlAuthority ctrlAuthority);
    /**
     * @brief 转换调试模式
     */
    StatusItemGroup convertDebugMode(DebugMode debugMode);
    /**
     * @brief 转换运行模式
     */
    StatusItemGroup convertDeviceMode(DeviceMode deviceMode);
    /**
     * @brief 从检查项集合中提取出具体需要的用户权限
     * @param statusGroup 检查项集合
     */
    StatusItemGroup extractRealUserAuthority(unsigned long long statusGroup);
    /**
     * @brief 从检查项集合中提取出具体需要的软件调试模式
     * @param statusGroup 检查项集合
     */
    StatusItemGroup extractRealDebugMode(unsigned long long statusGroup);

private:
    IUser *_pUser = nullptr;
    IRCConfig *_pRCConfig = nullptr;
    IConnection *_pConnection = nullptr;
    IMonitor *_pMonitor = nullptr;
    IDebuger *_pDebuger = nullptr;
    IControl *_pControl = nullptr;
    IProject *_pProject = nullptr;
    ITask *_pTask = nullptr;
    IMotion *_pMotion = nullptr;
    IControlAuthority *_pCtrlAuthority = nullptr;

    std::map<StatusItemGroup, std::string> _statusTipMap;

};  // class StatusChecks

}  // namespace InoRobBusiness
