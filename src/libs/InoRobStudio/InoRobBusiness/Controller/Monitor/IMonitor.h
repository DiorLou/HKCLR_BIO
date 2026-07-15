#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"
#include "../Controller/ControlAuthority/IControlAuthority.h"

namespace InoRobBusiness
{
#pragma region 枚举

// 设备状态（可用于设备状态灯）
enum class EDevState
{
    OFFLINE = 0,  // 离线
    ENABLE,       // 使能
    ESTOP,        // 急停
    ERR,          // 报警
    WARN,         // 警告
    STANDBY,      // 待机
};

// 控制器（程序）运行状态
enum ControllerRunStatus : int32s
{
    CONTROLLER_RUN_STATUS_STOP = 0,     // 停止
    CONTROLLER_RUN_STATUS_START = 1,    // 启动
    CONTROLLER_RUN_STATUS_FORWARD = 2,  // 前进
    CONTROLLER_RUN_STATUS_BACK = 3,     // 后退
    CONTROLLER_RUN_STATUS_PAUSE = 4,    // 暂停
};

// 电柜类型
enum ElectricControlCabinetType : int32s
{
    ELECTRIC_CONTROL_CABINET_TYPE_UNKNOW = 0,      // 未知
    ELECTRIC_CONTROL_CABINET_TYPE_NORMAL = 1,      // 默认老电柜
    ELECTRIC_CONTROL_CABINET_TYPE_MULTI_PASS = 2,  // 小多传
    ELECTRIC_CONTROL_CABINET_TYPE_J6_20KGV = 3,    // 20公斤6关节立柜
    ELECTRIC_CONTROL_CABINET_TYPE_UNIT = 4,        // 驱控一体
    ELECTRIC_CONTROL_CABINET_TYPE_JIUZHOU = 6,     // 九州电柜
    ELECTRIC_CONTROL_CABINET_TYPE_UROBOT = 8,      // 协作U8电柜类型
};

// 工具工件匹配状态
enum ToolWobjMatchStatus
{
    TOOL_WOBJ_MATCH = 0,             // 工具与工件匹配
    TOOL_WOBJ_NOT_MATCH = 1,         // 工具与工件不匹配
    TOOL_WOBJ_NOT_MATCH_IN_WOBJ = 2  // 工件参数不匹配
};

// 运行模式（参考MODE_TYPE枚举）
enum RunMode : int32s
{
    RUN_MODE_UNKNOW = 0,       // 未知
    RUN_MODE_TEACH = 1,        // 示教
    RUN_MODE_REAPPEAR = 2,     // 再现
    RUN_MODE_TEACH_CHECK = 3,  // 单步示教检查
    RUN_MODE_FOUR = 4,         // 前进
    RUN_MODE_TEACH_RUN = 5,    // 连续示教运行
    RUN_MODE_HOMING = 6,       // 回零
    RUN_MODE_TYPE_BUTT,        //
};

// 寸动等级
enum MoveStepGrade : int8u
{
    MOVE_STEP_GRADE_NONE = 0,  // 关闭寸动（点动）
    MOVE_STEP_GRADE_G1 = 1,    // 等级1（关节步长0.05°，位置步长0.05mm，姿态步长0.05°）
    MOVE_STEP_GRADE_G2 = 2,    // 等级2（关节步长0.5°，位置步长0.5mm，姿态步长0.5°）
    MOVE_STEP_GRADE_G3 = 3,    // 等级3（关节步长2.0°，位置步长2.0mm，姿态步长2.0°）
    MOVE_STEP_GRADE_U = 4,     // 自定义
};

// 机械单元类型
enum MechUnitType : int32s
{
    MECH_UNIT_ROBOT = 0,              // 机器人
    MECH_UNIT_X_AXIS_TRACK = 1,       // X轴导轨
    MECH_UNIT_ROT_DEVICE_1_AXIS = 2,  // 单轴旋转变位机
    MECH_UNIT_ROT_DEVICE_2_AXIS = 3,  // 双轴旋转变位机
    MECH_UNIT_XYZ_AXIS_TRACK = 4,     // XYZ轴导轨
    MECH_UNIT_XZ_AXIS_TRACK = 5,      // XZ轴导轨
    MECH_UNIT_YZ_AXIS_TRACK = 6,      // YZ轴导轨
    MECH_UNIT_NO_MODEL_1_AXIS = 101,  // 无模型1轴
    MECH_UNIT_NO_MODEL_2_AXIS = 102,  // 无模型2轴
    MECH_UNIT_NO_MODEL_3_AXIS = 103,  // 无模型3轴
    MECH_UNIT_NO_MODEL_4_AXIS = 104,  // 无模型4轴
    MECH_UNIT_NO_MODEL_5_AXIS = 105,  // 无模型5轴
    MECH_UNIT_NO_MODEL_6_AXIS = 106,  // 无模型6轴
};

// 机械单元状态
enum MechUnitStatus : int32s
{
    MECH_UNIT_STATUS_NORMAL = 0,            // 普通
    MECH_UNIT_STATUS_ACTIVE = 1,            // 激活
    MECH_UNIT_STATUS_COORDINATION = 2,      // 协同
    MECH_UNIT_STATUS_DISABLED = 3,          // 禁用
    MECH_UNIT_STATUS_NORMAL_HOT = 4,        // 普通-热机
    MECH_UNIT_STATUS_ACTIVE_HOT = 5,        // 激活-热机
    MECH_UNIT_STATUS_COORDINATION_HOT = 6,  // 协同-热机
};

enum CoRobotBodyPowerState : int8u
{
    ROBOT_BODY_POWER_DISENABLE = 0,     // 工业机器人 未启用该功能
    ROBOT_BODY_POWER_OFF = 1,           // 协作 未上电
    ROBOT_BODY_POWERING_ON_IN_PROCESS = 2,            // 协作 正在上电
    ROBOT_BODY_POWER_ON = 3,            // 协作 已上电
    ROBOT_BODY_DISCONNECTED_STATE = 4, // 未连接时的默认值
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE1 = 5,    //控制柜内部状态1
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE2 = 6, //控制柜内部状态2
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE3 = 7,  //控制柜内部状态3
    ROBOT_BODY_POWERING_OFF_IN_PROCESS = 8, //协作 本体下电中
};
// 机械单元信息
typedef struct MechUnitInfo
{
    // 名称
    char Name[MECHUNIT_NAME_LENGTH];
    // 类型
    MechUnitType Type;
    // 轴数量
    int8u AxisNum;
    // 当前状态
    MechUnitStatus Status;

    MechUnitInfo()
    {
        Init();
    }

    void Init()
    {
        memset(&Name, 0, MECHUNIT_NAME_LENGTH);
        Type = MECH_UNIT_ROBOT;
        AxisNum = 0;
        Status = MECH_UNIT_STATUS_NORMAL;
    }
    void Reset()
    {
        Init();
    }

} MechUnitInfo;

#pragma endregion

/*
    控制器监控
    Create by WuJian at 2023/7/20 创建，从控制器模型中剥离初始化数据与周期数据。
*/
class INOROBBUSINESS_CLASS IMonitor : public QObject
{
    Q_OBJECT

public:
    virtual ~IMonitor()
    {
    }

    // 在对象释放前，关闭线程，以避免线程中内存访问出错（MFC线程机制缺陷）
    virtual void CloseThread() = 0;

    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

#pragma region 初始化数据

    // 在控制器连接成功、权限切换（其它补充）时获取一次的数据为初始化数据

    // 机器人名称
    virtual bool GetRobotName(char robotName[128]) = 0;
    // 机型（机械臂型号）
    virtual RBTTYPE_E GetRobotType() = 0;
    // 电柜类型
    virtual ElectricControlCabinetType GetElectricControlCabinetType() = 0;
    // 是否掉电保存
    virtual bool GetIsPowerDownSave() = 0;
    // 控制器控制权
    virtual CtrlAuthority GetControlAuthority() = 0;
    // IRLink控制权
    virtual IR_CTRL_SET GetIrLinkAuthority() = 0;
    // IO数量
    virtual int32s GetInputNum() = 0;
    virtual int32s GetOutputNum() = 0;
    // AD、DA数量
    virtual int32s GetAdNum() = 0;
    virtual int32s GetDaNum() = 0;
    // 结构参数
    virtual bool GetStructParameters(double parameters[LINK_PARM_NUM]) = 0;
    // 补偿参数
    virtual bool GetCompensationParameters(double parameters[COM_PARM_NUM]) = 0;
    // 轴正向极限（单位°）
    virtual bool GetAxisPositiveLimit(double limits[JOINT_AXIS_NUM]) = 0;
    // 轴负向极限（单位°）
    virtual bool GetAxisNegativeLimit(double limits[JOINT_AXIS_NUM]) = 0;
    // 伺服轴类型（1-IS620N、2-IS820N、3-IS660N）
    virtual bool GetServoAxisType(char axisType[8]) = 0;
    // FPGA版本
    virtual int32u GetFpgaVersion() = 0;
    // 机器人本体型号（带有内部信息）
    virtual bool GetRobotBodyModel(char bodyModel[128]) = 0;
    // 总线安装标志
    virtual bool GetBusInstall(char busInstall[4]) = 0;
    // 电控柜硬件版本
    virtual int32u GetHardWareVer() = 0;

    virtual int readCobotToolIOVersion(std::string &data) = 0;
    // 控制器软件版本
    virtual string GetRCVersionName() = 0;

    // 获取示教器版本信息
    virtual string getTeachPadVersion() = 0;

    // 获取版本信息
    virtual int getControllerVersionInfo(std::vector<string> &verInfo) = 0;

    // 获取VRC策略下的版本号
    // tempVersion：传入的版本号，比如V4R24C2B255T12
    // isNeedC：返回的版本是否需要包含C版本
    // 返回值：返回需要的版本号
    virtual string getVRCVersion(string tempVersion, bool isNeedC = true) = 0;

    /**
     * @brief 获取tempVersion中的VRC版本，并转为数字
     * @param V号 例如V4R24为4024
     * @param R号
     * @param C号
     * @return
     */
    virtual int getVRCVersion(string tempVersion, int &versionVNum, int &versionRNum, int &versionCNum) = 0;

    // 判断VRC策略下的版本号是否匹配
    virtual bool checkVRCVersion(string tempVersion, int versionVRNum, int versionCNum) = 0;

    // 获取版本号，针对24以后的版本.返回值等于0时，获取成功
    virtual int getRcVersionNum(int32s &i32ValV, int32s &i32ValR, int32s &i32ValC) = 0;

    /**
     * @brief 获取当前控制器版本比V4R24C3新（包含V4R24C3）
     * @return true：是 false：否
     */
    virtual bool rcVersionIsNewerThanV4R24C3() = 0;

    /**
     * @brief 获取当前控制器版本比V4R24C4新（包含V4R24C4）
     * @return true：是 false：否
     */
    virtual bool rcVersionIsNewerThanV4R24C4() = 0;

    /**
     * @brief 获取当前控制器版本比V4R24C5新（包含V4R24C5）
     * @return true：是 false：否
     */
    virtual bool rcVersionIsNewerThanV4R24C5() = 0;

    /**
     * @brief 获取当前控制器版本比V4R25C1新（包含V4R25C1）
     * @return true：是 false：否
     */
    virtual bool rcVersionIsNewerThanV4R25C1() = 0;

    /**
     * @brief 获取当前控制器版本比指定版本新（包含指定版本）
     * @param VR号 例如V4R24为4024
     * @param C号
     * @return
     */
    virtual bool rcVersionIsNewerThan(int versionVRNum, int versionCNum) = 0;

    /**
     * @brief 获取控制器中指定文件夹或者文件的内存大小（单位：kb）
     * @param path 输入，文件夹或者文件路径
     * @return 返回内存大小，失败则为小于0
     */
    virtual int readFileOrFolderSizeInRc(const std::string &path) = 0;

    // 初始化数据是否已准备就绪（连接后至少成功读取过一次初始化数据）
    virtual bool GetInitDataIsReady() = 0;
    // 读取初始化数据（注：初始化数据暂时开放外部调用；后续模型逐步完善后，初始化数据过程应迁移至合理的业务场景中，界时关闭外部调用）
    // 目前需要调用的业务场景：1、网络连接成功；2、切换控制权限
    virtual bool InitDataRead() = 0;

#pragma endregion

#pragma region 周期数据

    // 模型以一定频率与控制器保持同步的数据为周期数据
    // 周期数据在初始化数据就绪后开始同步

    // 运行状态
    virtual ControllerRunStatus GetRunStatus() = 0;
    // 警告Id
    virtual int32s GetWarningId() = 0;
    // 错误Id
    virtual int32s GetErrorId() = 0;
    /* 控制器各个模块的通信状态，参考：MonitorCommStatus.cpp
     * [0] 网络适配器0（0：网线未连接，1：网线已连接，2：禁用）
     * [1] 网络适配器1（0：网线未连接，1：网线已连接，2：禁用）
     * [2] USB控制器（0：设备未连接，1：已连接并成功挂载，2：已连接但挂载失败）
     * [3] 存储卡（0：设备未连接，1：已连接并成功挂载，2：已连接但挂载失败，3：存储卡格式错误）
     * [4] EtherCAT0（0：通信正常，1：从站掉线，2：设备未挂载，3：连接了非EtherCAT设备，4：禁用）
     * [5] IR-Link0（0：通信正常，1：从站掉线，2：设备未挂载，3：连接了非IR-Link设备，4：禁用，5：设备未配置）
     * 注：信号参数无具体含义，实际数据通过模型获取
     */
    virtual void GetModuleCommState(int16u moduleCommState[MODULE_NUM]) = 0;
    // Output控制状态（参见 IO_CTRL_STATE 枚举）
    // 注：信号参数无具体含义，实际数据通过模型获取
    virtual void GetOutputState(int8u outputState[MAXIONUM]) = 0;
    // DA控制状态（参见 IO_CTRL_STATE 枚举）
    // 注：信号参数无具体含义，实际数据通过模型获取
    virtual void GetDaState(int8u daState[MAXDANUM]) = 0;
    // 安全门状态（0-无警示 1-有警示）
    virtual int8u GetSafeDoorState() = 0;
    // 功率等级（0-低功率 1-高功率）
    virtual int8u GetPowerLevel() = 0;
    // 当前工具工件匹配状态
    virtual ToolWobjMatchStatus GetToolWobjMatchStatus() = 0;

    // 实时数据同步开关
    virtual bool GetIsRealData() = 0;
    virtual void SetIsRealData(bool isRealData) = 0;
    // 实时数据同步间隔时间（毫秒，当值小于等于0时会关闭实时数据获取）
    virtual int32s GetRealDataInterval() = 0;
    virtual void SetRealDataInterval(int32s realDataInterval) = 0;
    // 实时数据是否已准备就绪（连接后至少成功读取过一次实时数据）
    virtual bool GetRealDataIsReady() = 0;
    // 打包获取实时数据（为了兼容TP老代码，后续待优化移除）
    virtual void GetRcStsInfo0322(RCSTS_INFO_0322 &rcStsInfo0322) = 0;

#pragma endregion

#pragma region 速度

    // 获取速度值
    virtual int16u GetSpeed() = 0;
    // 准备更新速度值（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetSpeed(int16u speed) = 0;

#pragma endregion

#pragma region 寸动

    // 获取当前寸动等级
    virtual MoveStepGrade GetMoveStepGrade() = 0;
    // 准备更新当前寸动等级（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetMoveStepGrade(MoveStepGrade grade) = 0;

#pragma endregion

#pragma region 当前坐标系类型

    // 获取当前坐标系类型
    virtual CoordType GetCurrentCoordType() = 0;
    // 准备更新当前坐标系类型（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetCurrentCoordType(CoordType coordType) = 0;

#pragma endregion

#pragma region 当前显示的位置格式

    // 当前位置格式
    virtual InoRobUtil::PosFormat GetPosFormat() = 0;
    // 准备更新当前位置格式（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetPosFormat(InoRobUtil::PosFormat posFormat) = 0;

#pragma endregion

#pragma region 当前显示的位置

    // 获取当前位置（机械单元）
    virtual bool GetCurrentPosition(double position[JOINT_AXIS_NUM]) = 0;
    // 变更当前位置（自动触发变更事件，注：由周期线程使用，模型外严禁调用）
    virtual bool OnCurrentPositionChange(double position[JOINT_AXIS_NUM]) = 0;

#pragma endregion

#pragma region 当前工具号

    // 获取当前工具号
    virtual int16u GetToolId() = 0;
    // 准备更新当前工具ID（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetToolId(int16u toolID) = 0;

#pragma endregion

#pragma region 当前工件号

    // 获取当前工件号
    virtual int16u GetWobjId() = 0;
    // 准备更新当前工件ID（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetWobjId(int16u wobjID) = 0;

#pragma endregion

#pragma region 当前负载号

    // 获取当前负载号
    virtual int16u GetLoadId() = 0;
    // 准备更新当前负载号（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetLoadId(int16u loadID) = 0;

#pragma endregion

#pragma region 机械单元

    // 机械单元列表
    virtual vector<MechUnitInfo> *GetMechUnitList() = 0;
    // 获取当前激活（选中）的机械单元
    virtual void GetActiveMechUnit(MechUnitInfo &mechUnitInfo) = 0;
    // 获取当前激活（选中）的机械单元轴数量
    virtual int8u GetActiveMechUnitAxisNum() = 0;
    // 获取当前激活（选中）的机械单元索引
    virtual int8u GetActiveMechUnitIndex() = 0;
    // 获取机器人机械单元轴数量（辅助）
    virtual int8u GetRobotMechUnitAxisNum() = 0;
    // 开启机械单元状态变更轮询（注：限模型层内部调用）
    virtual void MechUnitStatusChange() = 0;

#pragma endregion

#pragma region 使能

    // 获取使能状态（true：已上使能，false：已下使能）
    virtual bool GetEnable() = 0;

#pragma endregion

#pragma region 协作专用 本体上电
    // 获取本地上电状态
    virtual CoRobotBodyPowerState GetCoRobotBodyPowerState() = 0;
#pragma endregion

#pragma region 急停

    // 获取急停状态（true：已急停，false：未急停）
    virtual bool GetEmergency() = 0;

#pragma endregion

#pragma region 运行模式

    // 获取运行模式
    virtual RunMode GetRunMode() = 0;

#pragma endregion

#pragma region 机械锁定

    // 机械锁定：锁定机器人的物理运动

    // 获取当前机械锁定状态（true：锁定，false：未锁定）
    virtual bool GetMechLock() = 0;
    // 准备更新机械锁定状态（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetMechLock(bool status) = 0;

#pragma endregion

#pragma region 动态制动

    // 动态制动：动态制动目前适用于SCARA机器人，默认是开启的，在非使能状态下关闭动态制动会使机器人关节更容易推动

    // 获取当前动态制动状态（true：开启，false：关闭）
    virtual bool GetDynamicBrake() = 0;
    // 准备更新动态制动状态（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetDynamicBrake(bool status) = 0;

#pragma endregion

#pragma region 协调

    // 协调：机器人跟随某个外部机械单元的运动而运动

    // 获取机器人当前协调的机械单元名称（为空表示机器人未开启协调）
    virtual string GetCooperate() = 0;
    // 准备更新协调的机械单元名称（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    virtual void SetCooperate(const string &mechUnitName) = 0;
    // 当前机械单元是否满足协调条件（可显示协调按钮）
    virtual bool GetCooperateIsReady() = 0;

#pragma endregion

#pragma region 设备状态
    /*!
     * \brief 获取设备状态
     */
    virtual EDevState getDeviceState() = 0;
#pragma endregion

#pragma region 协作ABZ监控
    /**
     * @brief 获取ABZ
     * @return true成功 false失败
     */
    virtual int readCobotABZDatas(std::string &data) = 0;
#pragma endregion


#pragma region 文件管理
    // 通知控制器对要导出的文件进行备份
    virtual int exportDocumentsToLocal(int32u docusNum, vector<string> &docuMentsName) = 0;
    // 通知控制器对要删除的文件进行删除
    virtual int deleteDocumentsFromRc(int32u docusNum, vector<string> &docuMentsName) = 0;
    // 读取控制器操作状态
    virtual int readDocumentsStatus(int32u status[10]) = 0;
#pragma endregion

Q_SIGNALS:
    // 注：需要实时数据在网络连接成功后至少成功同步过一次，否则初始化数据更新信号会延迟至实时数据同步成功后发出
    /**
     * @brief 数据更新信号
     */
    void initDataRefreshed(bool data);

    /**
     * @brief 运行状态改变信号
     */
    void runStatusChanged(ControllerRunStatus status);

    /**
     * @brief 警告码改变信号
     */
    void warningIdChanged(int32s id);

    /**
     * @brief 错误码改变信号
     */
    void errorIdChanged(int32s id);

    /**
     * @brief 模块通讯状态改变信号
     */
    void moduleCommStateChanged(bool state);

    /**
     * @brief 输出状态改变信号
     */
    void outputStateChanged(bool state);

    /**
     * @brief DA状态改变信号
     */
    void daStateChanged(bool state);

    /**
     * @brief 安全门状态改变信号
     */
    void safeDoorStateChanged(int8u state);

    /**
     * @brief 功率等级改变信号
     */
    void powerLevelChanged(int8u state);

    /**
     * @brief 工具工件匹配状态
     */
    void toolWobjMatchStatusChanged(ToolWobjMatchStatus status);

    /**
     * @brief 实时数据更新信号（每次实时数据更新至模型时触发，为了兼容TP老代码，后续待优化移除）
     */
    void realDataUpdated(int32s data);

    /**
     * @brief 速度值变更信号
     */
    void speedChanged(int16u speed);

    /**
     * @brief 寸动等级变更信号
     */
    void moveStepGradeChanged(MoveStepGrade stepGrade);

    /**
     * @brief 当前坐标系类型变更信号
     */
    void currentCoordTypeChanged(CoordType status);

    /**
     * @brief 当前位置格式变更信号
     */
    void posFormatChanged(PosFormat posFormat);

    /**
     * @brief 当前位置变更信号（信号不传递位置数据，当前位置数据需要通过GetCurrentPosition获取）
     */
    void currentPositionChanged(bool position);

    /**
     * @brief 当前工具号变更信号
     */
    void toolIdChanged(int16u id);

    /**
     * @brief 当前工件号变更信号
     */
    void wobjIdChanged(int16u id);

    /**
     * @brief 当前负载号变更信号
     */
    void loadIdChanged(int16u id);

    /**
     * @brief 机械单元状态变更信号（注：参数暂无具体含义，机械单元的状态数据通过 GetMechUnitList() 获取）
     */
    void mechUnitStatusChanged(bool status);

    /**
     * @brief 使能状态变化信号
     */
    void enableChanged(bool enable);

    /**
     * @brief 上电状态状态变化信号
     */
    void coRobotBodyPowerStateChanged(CoRobotBodyPowerState state);

    /**
     * @brief 急停状态变化信号
     */
    void emergencyChanged(bool emergency);

    /**
     * @brief 运行模式变化信号
     */
    void runModeChanged(RunMode mode);

    /**
     * @brief 机械锁定状态变化信号
     */
    void mechLockChanged(bool mechLock);

    /**
     * @brief 动态制动状态变化信号
     */
    void dynamicBrakeChanged(bool dynBrake);

    /**
     * @brief 机器人协调的机械单元名称变更信号
     */
    void cooperateChanged(std::string cooperate);

    /**
     * @brief 使能状态变化信号
     */
    void gripperThreePosEnableChanged(bool enable);

    /**
     * @brief 设备状态改变信号
     */
    void sigDeviceStateChanged(int devState);

    /**
     * @brief 切换测试模式
     * @param testmode 0-非测试模式，1-测试模式
     */
    void sigTestMode(int testMode);

    /**
     * @brief 协作控制器WiFi频段变更
     * @param bool 是否变更
     */
    void sigControllerWiFiFrequencyBandChanged(bool);

    /**
     * @brief 功能安全缩减模式触发信号（协作）
     * @param bool 是否变更
     */
    void sigSpeedReduingTriggerdChange(bool);

    /**
     * @brief 夹持器状态变化（协作）
     * @param bool 是否变更
     */
    void sigGripperEnableChanged(bool);

    /**
     * @brief 安全监控状态触发信号（协作）
     * @param bool 是否变更
     */
    void sigSafetyMonitorStatusChange(bool);

    /**
     * @brief 碰撞检测推荐值变化（协作）
     * @param int16s 推荐值
     */
    void sigCollisionRecommendedValueChange(int16s);

    /**
     * @brief 碰撞检测状态发生变化（协作）
     * @param bool 是否变更
     */
    void sigCollisionStatusChange(bool);

};
}  // namespace InoRobBusiness
