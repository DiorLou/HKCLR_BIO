#pragma once
#include "dllspec.h"
#include <QObject>
#include "IInoRobBusiness.h"
#include "../../DataService/DataSrvGlobal_V1.h"
#include "../../InoRobUtil/CommonEnum_V1.h"
#include "../ControlAuthority/ControlAuthority_V1.h"
#include "../../GlobalDataTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

// 设备状态（可用于设备状态灯）
enum class EDevState_V1
{
    OFFLINE_V1 = 0,  // 离线
    ENABLE_V1,       // 使能
    ESTOP_V1,        // 急停
    ERR_V1,          // 报警
    WARN_V1,         // 警告
    STANDBY_V1,      // 待机
};

// 控制器（程序）运行状态
enum ControllerRunStatus_V1 : int32s
{
    CONTROLLER_RUN_STATUS_STOP_V1 = 0,     // 停止
    CONTROLLER_RUN_STATUS_START_V1 = 1,    // 启动
    CONTROLLER_RUN_STATUS_FORWARD_V1 = 2,  // 前进
    CONTROLLER_RUN_STATUS_BACK_V1 = 3,     // 后退
    CONTROLLER_RUN_STATUS_PAUSE_V1 = 4,    // 暂停
};

// 电柜类型
enum ElectricControlCabinetType_V1 : int32s
{
    ELECTRIC_CONTROL_CABINET_TYPE_UNKNOW_V1 = 0,      // 未知
    ELECTRIC_CONTROL_CABINET_TYPE_NORMAL_V1 = 1,      // 默认老电柜
    ELECTRIC_CONTROL_CABINET_TYPE_MULTI_PASS_V1 = 2,  // 小多传
    ELECTRIC_CONTROL_CABINET_TYPE_J6_20KGV_V1 = 3,    // 20公斤6关节立柜
    ELECTRIC_CONTROL_CABINET_TYPE_UNIT_V1 = 4,        // 驱控一体
    ELECTRIC_CONTROL_CABINET_TYPE_JIUZHOU_V1 = 6,     // 九州电柜
};

// 工具工件匹配状态
enum ToolWobjMatchStatus_V1
{
    TOOL_WOBJ_MATCH_V1 = 0,             // 工具与工件匹配
    TOOL_WOBJ_NOT_MATCH_V1 = 1,         // 工具与工件不匹配
    TOOL_WOBJ_NOT_MATCH_IN_WOBJ_V1 = 2  // 工件参数不匹配
};

// 运行模式（参考MODE_TYPE枚举）
enum RunMode_V1 : int32s
{
    RUN_MODE_UNKNOW_V1 = 0,       // 未知
    RUN_MODE_TEACH_V1 = 1,        // 示教
    RUN_MODE_REAPPEAR_V1 = 2,     // 再现
    RUN_MODE_TEACH_CHECK_V1 = 3,  // 单步示教检查
    RUN_MODE_FOUR_V1 = 4,         // 前进
    RUN_MODE_TEACH_RUN_V1 = 5,    // 连续示教运行
    RUN_MODE_HOMING_V1 = 6,       // 回零
    RUN_MODE_TYPE_BUTT_V1,        //
};

// 寸动等级
enum MoveStepGrade_V1 : int8u
{
    MOVE_STEP_GRADE_NONE_V1 = 0,  // 关闭寸动（点动）
    MOVE_STEP_GRADE_G1_V1 = 1,    // 等级1（关节步长0.05°，位置步长0.05mm，姿态步长0.05°）
    MOVE_STEP_GRADE_G2_V1 = 2,    // 等级2（关节步长0.5°，位置步长0.5mm，姿态步长0.5°）
    MOVE_STEP_GRADE_G3_V1 = 3,    // 等级3（关节步长2.0°，位置步长2.0mm，姿态步长2.0°）
    MOVE_STEP_GRADE_U_V1 = 4,     // 自定义
};

// 机械单元类型
enum MechUnitType_V1 : int32s
{
    MECH_UNIT_ROBOT_V1 = 0,              // 机器人
    MECH_UNIT_X_AXIS_TRACK_V1 = 1,       // X轴导轨
    MECH_UNIT_ROT_DEVICE_1_AXIS_V1 = 2,  // 单轴旋转变位机
    MECH_UNIT_ROT_DEVICE_2_AXIS_V1 = 3,  // 双轴旋转变位机
    MECH_UNIT_XYZ_AXIS_TRACK_V1 = 4,     // XYZ轴导轨
    MECH_UNIT_XZ_AXIS_TRACK_V1 = 5,      // XZ轴导轨
    MECH_UNIT_YZ_AXIS_TRACK_V1 = 6,      // YZ轴导轨
    MECH_UNIT_NO_MODEL_1_AXIS_V1 = 101,  // 无模型1轴
    MECH_UNIT_NO_MODEL_2_AXIS_V1 = 102,  // 无模型2轴
    MECH_UNIT_NO_MODEL_3_AXIS_V1 = 103,  // 无模型3轴
    MECH_UNIT_NO_MODEL_4_AXIS_V1 = 104,  // 无模型4轴
    MECH_UNIT_NO_MODEL_5_AXIS_V1 = 105,  // 无模型5轴
    MECH_UNIT_NO_MODEL_6_AXIS_V1 = 106,  // 无模型6轴
};

// 机械单元状态
enum MechUnitStatus_V1 : int32s
{
    MECH_UNIT_STATUS_NORMAL_V1 = 0,            // 普通
    MECH_UNIT_STATUS_ACTIVE_V1 = 1,            // 激活
    MECH_UNIT_STATUS_COORDINATION_V1 = 2,      // 协同
    MECH_UNIT_STATUS_DISABLED_V1 = 3,          // 禁用
    MECH_UNIT_STATUS_NORMAL_HOT_V1 = 4,        // 普通-热机
    MECH_UNIT_STATUS_ACTIVE_HOT_V1 = 5,        // 激活-热机
    MECH_UNIT_STATUS_COORDINATION_HOT_V1 = 6,  // 协同-热机
};

enum CoRobotBodyPowerState_V1 : int8u
{
    ROBOT_BODY_POWER_DISENABLE_V1 = 0,  // 工业机器人 未启用该功能
    ROBOT_BODY_POWER_OFF_V1 = 1,        // 协作 未上电
    ROBOT_BODY_POWERING_ON_IN_PROCESS_V1 = 2,         // 协作 正在上电
    ROBOT_BODY_POWER_ON_V1 = 3,         // 协作 已上电
    ROBOT_BODY_DISCONNECTED_STATE_V1 = 4, // 未连接时的默认值
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE1_V1 = 5,    //控制柜内部状态1
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE2_V1 = 6, //控制柜内部状态2
    ROBOT_BODY_POWER_STATE_CONTROLLER_RESEREVE3_V1 = 7,  //控制柜内部状态3
    ROBOT_BODY_POWERING_OFF_IN_PROCESS_V1 = 8, //协作 本体下电中
};
// 机械单元信息
typedef struct MechUnitInfo_V1
{
    // 名称
    char Name[MECHUNIT_NAME_LENGTH_V1];
    // 类型
    MechUnitType_V1 Type;
    // 轴数量
    int8u AxisNum;
    // 当前状态
    MechUnitStatus_V1 Status;

    MechUnitInfo_V1()
    {
        Init();
    }

    void Init()
    {
        memset(&Name, 0, MECHUNIT_NAME_LENGTH_V1);
        Type = MECH_UNIT_ROBOT_V1;
        AxisNum = 0;
        Status = MECH_UNIT_STATUS_NORMAL_V1;
    }
    void Reset()
    {
        Init();
    }

} MechUnitInfo_V1;

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Monitor_V1 : public QObject
{
    Q_OBJECT

#pragma region 数据转换

public:
    static EDevState_V1 EDevState_ToProxy(EDevState eDevState);
    static EDevState EDevState_FromProxy(EDevState_V1 eDevState_V1);

    static ControllerRunStatus_V1 ControllerRunStatus_ToProxy(ControllerRunStatus controllerRunStatus);
    static ControllerRunStatus ControllerRunStatus_FromProxy(ControllerRunStatus_V1 controllerRunStatus_V1);

    static ElectricControlCabinetType_V1 ElectricControlCabinetType_ToProxy(ElectricControlCabinetType electricControlCabinetType);
    static ElectricControlCabinetType ElectricControlCabinetType_FromProxy(ElectricControlCabinetType_V1 electricControlCabinetType_V1);

    static ToolWobjMatchStatus_V1 ToolWobjMatchStatus_ToProxy(ToolWobjMatchStatus toolWobjMatchStatus);
    static ToolWobjMatchStatus ToolWobjMatchStatus_FromProxy(ToolWobjMatchStatus_V1 toolWobjMatchStatus_V1);

    static RunMode_V1 RunMode_ToProxy(RunMode runMode);
    static RunMode RunMode_FromProxy(RunMode_V1 runMode_V1);

    static MoveStepGrade_V1 MoveStepGrade_ToProxy(MoveStepGrade moveStepGrade);
    static MoveStepGrade MoveStepGrade_FromProxy(MoveStepGrade_V1 moveStepGrade_V1);

    static MechUnitType_V1 MechUnitType_ToProxy(MechUnitType mechUnitType);
    static MechUnitType MechUnitType_FromProxy(MechUnitType_V1 mechUnitType_V1);

    static MechUnitStatus_V1 MechUnitStatus_ToProxy(MechUnitStatus mechUnitStatus);
    static MechUnitStatus MechUnitStatus_FromProxy(MechUnitStatus_V1 mechUnitStatus_V1);

    static CoRobotBodyPowerState_V1 CoRobotBodyPowerState_ToProxy(CoRobotBodyPowerState coRobotBodyPowerState);
    static CoRobotBodyPowerState CoRobotBodyPowerState_FromProxy(CoRobotBodyPowerState_V1 coRobotBodyPowerState_V1);

    static bool MechUnitInfo_ToProxy(const MechUnitInfo &mechUnitInfo, MechUnitInfo_V1 &mechUnitInfo_V1);
    static bool MechUnitInfo_FromProxy(const MechUnitInfo_V1 &mechUnitInfo_V1, MechUnitInfo &mechUnitInfo);

#pragma endregion

#pragma region 构造与析构

private:
    IMonitor *_monitor = nullptr;

public:
    Monitor_V1(IMonitor *monitor);
    ~Monitor_V1();

#pragma endregion

#pragma region 初始化数据

private:
    void InitDataRefreshedHandler(bool data);

public:
    // 机器人名称  --  已测
    bool GetRobotName(char robotName[128]);
    // 机型（机械臂型号）  --  已测
    RBTTYPE_E_V1 GetRobotType();
    // 电柜类型  --  已测
    ElectricControlCabinetType_V1 GetElectricControlCabinetType();
    // 是否掉电保存  --  已测
    bool GetIsPowerDownSave();
    // 控制器控制权  --  已测
    CtrlAuthority_V1 GetControlAuthority();
    // IRLink控制权  --  已测
    IR_CTRL_SET_V1 GetIrLinkAuthority();
    // IO数量  --  已测
    int32s GetInputNum();
    int32s GetOutputNum();
    // AD、DA数量  --  已测
    int32s GetAdNum();
    int32s GetDaNum();
    // 结构参数  --  已测
    bool GetStructParameters(double parameters[LINK_PARM_NUM_V1]);
    // 补偿参数  --  已测
    bool GetCompensationParameters(double parameters[COM_PARM_NUM_V1]);
    // 轴正向极限（单位°）  --  已测
    bool GetAxisPositiveLimit(double limits[JOINT_AXIS_NUM_V1]);
    // 轴负向极限（单位°）  --  已测
    bool GetAxisNegativeLimit(double limits[JOINT_AXIS_NUM_V1]);
    // 伺服轴类型（1-IS620N、2-IS820N、3-IS660N）  --  已测
    bool GetServoAxisType(char axisType[8]);
    // FPGA版本  --  已测
    int32u GetFpgaVersion();
    // 机器人本体型号（带有内部信息）  --  已测
    bool GetRobotBodyModel(char bodyModel[128]);
    // 总线安装标志  --  已测
    bool GetBusInstall(char busInstall[4]);
    // 电控柜硬件版本  --  已测
    int32u GetHardWareVer();
    int readCobotToolIOVersion(std::string &data);
    // 控制器软件版本  --  已测
    string GetRCVersionName();
    // 获取示教器版本信息  --  已测
    string getTeachPadVersion();
    // 获取版本信息
    int getControllerVersionInfo(std::vector<string> &verInfo);
    // 获取VRC策略下的版本号  --  已测
    // tempVersion：传入的版本号，比如V4R24C2B255T12
    // isNeedC：返回的版本是否需要包含C版本
    // 返回值：返回需要的版本号
    string getVRCVersion(string tempVersion, bool isNeedC = true);
    // 判断VRC策略下的版本号是否匹配  --  已测
    bool checkVRCVersion(string tempVersion, int versionVRNum, int versionCNum);
    // 获取版本号，针对24以后的版本.返回值等于0时，获取成功
    int getRcVersionNum(int32s &i32ValV, int32s &i32ValR, int32s &i32ValC);
    /**
     * @brief 获取当前控制器版本比V4R24C3新（包含V4R24C3）  --  已测
     * @return true：是 false：否
     */
    bool rcVersionIsNewerThanV4R24C3();
    /**
     * @brief 获取当前控制器版本比V4R24C3新（包含V4R24C4）  --  已测
     * @return true：是 false：否
     */
    bool rcVersionIsNewerThanV4R24C4();
    // 初始化数据是否已准备就绪（连接后至少成功读取过一次初始化数据）  --  已测
    bool GetInitDataIsReady();
    // 读取初始化数据（注：初始化数据暂时开放外部调用；后续模型逐步完善后，初始化数据过程应迁移至合理的业务场景中，界时关闭外部调用）  --  已测
    // 目前需要调用的业务场景：1、网络连接成功；2、切换控制权限
    bool InitDataRead();
    // 初始化数据更新信号
    // 注：需要实时数据在网络连接成功后至少成功同步过一次，否则初始化数据更新信号会延迟至实时数据同步成功后发出
    rsignal<bool> InitDataRefreshed;

#pragma endregion

#pragma region 周期数据

private:
    void RunStatusChangedHandler(ControllerRunStatus data);
    void WarningIdChangedHandler(int32s data);
    void ErrorIdChangedHandler(int32s data);
    void ModuleCommStateChangedHandler(bool data);
    void OutputStateChangedHandler(bool data);
    void DaStateChangedHandler(bool data);
    void SafeDoorStateChangedHandler(int8u data);
    void PowerLevelChangedHandler(int8u data);
    void ToolWobjMatchStatusChangedHandler(ToolWobjMatchStatus data);
    void RealDataUpdatedHandler(int32s data);

public:
    // 运行状态
    ControllerRunStatus_V1 GetRunStatus();  //  --  已测
    rsignal<ControllerRunStatus_V1> RunStatusChanged;
    // 警告Id
    int32s GetWarningId();  //  --  已测
    rsignal<int32s> WarningIdChanged;
    // 错误Id
    int32s GetErrorId();  //  --  已测
    rsignal<int32s> ErrorIdChanged;
    /* 控制器各个模块的通信状态，参考：MonitorCommStatus.cpp
     * [0] 网络适配器0（0：网线未连接，1：网线已连接，2：禁用）
     * [1] 网络适配器1（0：网线未连接，1：网线已连接，2：禁用）
     * [2] USB控制器（0：设备未连接，1：已连接并成功挂载，2：已连接但挂载失败）
     * [3] 存储卡（0：设备未连接，1：已连接并成功挂载，2：已连接但挂载失败，3：存储卡格式错误）
     * [4] EtherCAT0（0：通信正常，1：从站掉线，2：设备未挂载，3：连接了非EtherCAT设备，4：禁用）
     * [5] IR-Link0（0：通信正常，1：从站掉线，2：设备未挂载，3：连接了非IR-Link设备，4：禁用，5：设备未配置）
     * 注：信号参数无具体含义，实际数据通过模型获取
     */
    void GetModuleCommState(int16u moduleCommState[MODULE_NUM_V1]);  //  --  已测
    rsignal<bool> ModuleCommStateChanged;
    // Output控制状态（参见 IO_CTRL_STATE 枚举）
    // 注：信号参数无具体含义，实际数据通过模型获取
    void GetOutputState(int8u outputState[MAXIONUM_V1]);
    rsignal<bool> OutputStateChanged;
    // DA控制状态（参见 IO_CTRL_STATE 枚举）
    // 注：信号参数无具体含义，实际数据通过模型获取
    void GetDaState(int8u daState[MAXDANUM_V1]);
    rsignal<bool> DaStateChanged;
    // 安全门状态（0-无警示 1-有警示）
    int8u GetSafeDoorState();
    rsignal<int8u> SafeDoorStateChanged;
    // 功率等级（0-低功率 1-高功率）
    int8u GetPowerLevel();
    rsignal<int8u> PowerLevelChanged;
    // 当前工具工件匹配状态
    ToolWobjMatchStatus_V1 GetToolWobjMatchStatus();
    rsignal<ToolWobjMatchStatus_V1> ToolWobjMatchStatusChanged;
    // 实时数据同步开关
    bool GetIsRealData();
    void SetIsRealData(bool isRealData);
    // 实时数据同步间隔时间（毫秒，当值小于等于0时会关闭实时数据获取）
    int32s GetRealDataInterval();
    void SetRealDataInterval(int32s realDataInterval);
    // 实时数据是否已准备就绪（连接后至少成功读取过一次实时数据）
    bool GetRealDataIsReady();
    // 实时数据更新信号（每次实时数据更新至模型时触发，为了兼容TP老代码，后续待优化移除）
    rsignal<int32s> RealDataUpdated;
    // 打包获取实时数据（为了兼容TP老代码，后续待优化移除）
    void GetRcStsInfo0322(RCSTS_INFO_0322_V1 &rcStsInfo0322);   //  --  已测

#pragma endregion

#pragma region 速度

private:
    void SpeedChangedHandler(int16u data);

public:
    // 获取速度值
    int16u GetSpeed();
    // 准备更新速度值（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetSpeed(int16u speed);
    // 速度值变更信号
    rsignal<int16u> SpeedChanged;

#pragma endregion

#pragma region 寸动

private:
    void MoveStepGradeChangedHandler(MoveStepGrade data);

public:
    // 获取当前寸动等级
    MoveStepGrade_V1 GetMoveStepGrade();
    // 准备更新当前寸动等级（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetMoveStepGrade(MoveStepGrade_V1 grade);
    // 寸动等级变更信号
    rsignal<MoveStepGrade_V1> MoveStepGradeChanged;

#pragma endregion

#pragma region 当前坐标系类型

private:
    void CurrentCoordTypeChangedHandler(CoordType data);

public:
    // 获取当前坐标系类型
    CoordType_V1 GetCurrentCoordType();
    // 准备更新当前坐标系类型（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetCurrentCoordType(CoordType_V1 coordType);
    // 当前坐标系类型变更信号
    rsignal<CoordType_V1> CurrentCoordTypeChanged;

#pragma endregion

#pragma region 当前显示的位置格式

private:
    void PosFormatChangedHandler(PosFormat data);

public:
    // 当前位置格式
    PosFormat_V1 GetPosFormat();
    // 准备更新当前位置格式（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetPosFormat(PosFormat_V1 posFormat);
    // 当前位置格式变更信号
    rsignal<PosFormat_V1> PosFormatChanged;

#pragma endregion

#pragma region 当前显示的位置

private:
    void CurrentPositionChangedHandler(bool data);

public:
    // 获取当前位置（机械单元）
    bool GetCurrentPosition(double position[JOINT_AXIS_NUM_V1]);
    // 当前位置变更信号（信号不传递位置数据，当前位置数据需要通过GetCurrentPosition获取）
    rsignal<bool> CurrentPositionChanged;
    // 变更当前位置（自动触发变更事件，注：由周期线程使用，模型外严禁调用）
    bool OnCurrentPositionChange(double position[JOINT_AXIS_NUM_V1]);

#pragma endregion

#pragma region 当前工具号

private:
    void ToolIdChangedHandler(int16u data);

public:
    // 获取当前工具号
    int16u GetToolId();
    // 准备更新当前工具ID（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetToolId(int16u toolID);
    // 当前工具号变更信号
    rsignal<int16u> ToolIdChanged;

#pragma endregion

#pragma region 当前工件号

private:
    void WobjIdChangedHandler(int16u data);

public:
    // 获取当前工件号
    int16u GetWobjId();
    // 准备更新当前工件ID（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetWobjId(int16u wobjID);
    // 当前工件号变更信号
    rsignal<int16u> WobjIdChanged;

#pragma endregion

#pragma region 当前负载号

private:
    void LoadIdChangedHandler(int16u data);

public:
    // 获取当前负载号
    int16u GetLoadId();
    // 准备更新当前负载号（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetLoadId(int16u loadID);
    // 当前负载号变更信号
    rsignal<int16u> LoadIdChanged;

#pragma endregion

#pragma region 机械单元

private:
    void MechUnitStatusChangedHandler(bool data);

public:
    // 机械单元列表
    vector<MechUnitInfo_V1> GetMechUnitList();
    // 获取当前激活（选中）的机械单元
    void GetActiveMechUnit(MechUnitInfo_V1 &mechUnitInfo);
    // 获取当前激活（选中）的机械单元轴数量
    int8u GetActiveMechUnitAxisNum();
    // 获取当前激活（选中）的机械单元索引
    int8u GetActiveMechUnitIndex();
    // 获取机器人机械单元轴数量（辅助）
    int8u GetRobotMechUnitAxisNum();
    // 机械单元状态变更信号（注：参数暂无具体含义，机械单元的状态数据通过 GetMechUnitList() 获取）
    rsignal<bool> MechUnitStatusChanged;

#pragma endregion

#pragma region 使能

private:
    void EnableChangedHandler(bool data);

public:
    // 获取使能状态（true：已上使能，false：已下使能）   //  --  已测
    bool GetEnable();
    // 使能状态变化信号
    rsignal<bool> EnableChanged;

#pragma endregion

#pragma region 协作专用 本体上电

    // 获取本地上电状态
    // CoRobotBodyPowerState GetCoRobotBodyPowerState() = 0;
    // 上电状态状态变化信号
    // rsignal<CoRobotBodyPowerState> CoRobotBodyPowerStateChanged;

#pragma endregion

#pragma region 急停

private:
    void EmergencyChangedHandler(bool data);

public:
    // 获取急停状态（true：已急停，false：未急停）
    bool GetEmergency();
    // 急停状态变化信号
    rsignal<bool> EmergencyChanged;

#pragma endregion

#pragma region 运行模式

private:
    void RunModeChangedHandler(RunMode data);

public:
    // 获取运行模式
    RunMode_V1 GetRunMode();
    // 运行模式变化信号
    rsignal<RunMode_V1> RunModeChanged;

#pragma endregion

#pragma region 机械锁定

private:
    void MechLockChangedHandler(bool data);

public:
    // 获取当前机械锁定状态（true：锁定，false：未锁定）
    bool GetMechLock();
    // 准备更新机械锁定状态（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetMechLock(bool status);
    // 机械锁定状态变化信号
    rsignal<bool> MechLockChanged;

#pragma endregion

#pragma region 动态制动

private:
    void DynamicBrakeChangedHandler(bool data);

public:
    // 获取当前动态制动状态（true：开启，false：关闭）
    bool GetDynamicBrake();
    // 准备更新动态制动状态（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetDynamicBrake(bool status);
    // 动态制动状态变化信号
    rsignal<bool> DynamicBrakeChanged;

#pragma endregion

#pragma region 协调

private:
    void CooperateChangedHandler(string data);

public:
    // 获取机器人当前协调的机械单元名称（为空表示机器人未开启协调）
    string GetCooperate();
    // 准备更新协调的机械单元名称（注：由UI预先更新，然后在延时间后使用控制器数据更新，限模型层内部调用）
    void SetCooperate(const string &mechUnitName);
    // 机器人协调的机械单元名称变更信号
    rsignal<string> CooperateChanged;
    // 当前机械单元是否满足协调条件（可显示协调按钮）
    bool GetCooperateIsReady();

#pragma endregion

#pragma region 设备状态

private:
    void sigDeviceStateChangedHandler(int devState);

public:
    /*!
     * \brief 获取设备状态
     */
    EDevState_V1 getDeviceState();
    /*!
     * \brief 设备状态改变信号
     * \param state 状态枚举值EDevState
     */
    Q_SIGNAL void sigDeviceStateChanged(int devState);

#pragma endregion

#pragma region 夹持器三位置使能

#pragma endregion

#pragma region 协作ABZ监控

#pragma endregion
};
}  // namespace InoRobBusinessProxy
