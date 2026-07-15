#pragma once
#include "IDataSrvBase.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS MonitorDefault : public IMonitor
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 线程关闭标识
    bool _closeThread = false;
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;
    // 连接
    IConnection *_pConnection = nullptr;
    // 译码库
    ITransfor *_pTransfor = nullptr;

    // 控制器网络连接状态变更信号处理
    void ConnectionStatusOnChange(ControllerConnectionStatus status);

public:
    MonitorDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~MonitorDefault();

    void init() override;
    void CloseThread() override;

#pragma endregion

#pragma region 初始化数据

private:
    // 机器人名称
    char *m_RobotName;
    // 机型（机械臂型号）
    RBTTYPE_E m_RobotType;
    // 电柜类型
    ElectricControlCabinetType m_ElectricControlCabinetType;
    // 是否掉电保存
    bool m_IsPowerDownSave;
    // 控制器控制权
    CtrlAuthority m_ControlAuthority;
    // 控制器IRLink控制权
    IR_CTRL_SET m_IrLinkAuthority;
    // IO数量
    int32s m_InputNum;
    int32s m_OutputNum;
    // AD、DA数量
    int32s m_AdNum;
    int32s m_DaNum;
    // 结构参数
    double *m_StructParameters;
    // 补偿参数
    double *m_CompensationParameters;
    // 轴正向极限（单位°）
    double *m_AxisPositiveLimit;
    // 轴负向极限（单位°）
    double *m_AxisNegativeLimit;
    // 伺服轴类型（1-IS620N、2-IS820N、3-IS660N）
    char *m_ServoAxisType;
    // FPGA版本
    int32u m_FpgaVersion;
    // 机器人本体型号（带有内部信息）
    char *m_RobotBodyModel;
    // 总线安装标志
    char *m_BusInstall;
    // 电控柜硬件版本
    int32u m_HardWareVer;

    // 控制器版本名（在其他地方不要直接使用该变量，用getRCVersion和setRCVersion来替代，这两个函数加锁，避免线程安全问题）
    string m_rcVersionName;
    // 控制器版本名线程安全互斥锁
    std::mutex _rcVersionMtx;
    // 示教器版本
    InoVersion _teachPadVersion = 0;

    //  更新控制器的版本名称
    bool UpdateRcVersionName();
    // 检查版本是否匹配
    bool IsVersionMatch();

    // 初始化数据是否已准备就绪（连接后至少成功读取过一次初始化数据）
    // 实时数据必须依赖初始化数据准备就绪
    bool m_InitDataIsReady;
    // 初始化数据更新信号是否延迟发出
    // 当初始化数据完成更新，但实时数据尚未准备就绪时（网络连接成功后从未成功同步过），初始化数据更新信号将延迟至实时数据就绪时发出
    bool m_IsInitDataRefreshedSignalDelay;

    // 21版本及以前的版本初始化数据
    bool InitDataReadEx();
    // S03.22版本初始化数据
    bool InitDataReadV0322();

    /**
     * @brief 获取控制器版本名称
     */
    std::string getRCVersion();

    /**
     * @brief 设置控制器版本名称
     * @param version 输入，控制器版本名称
     */
    void setRCVersion(const std::string &version);

public:
    bool GetRobotName(char robotName[128]) override;
    RBTTYPE_E GetRobotType() override;
    ElectricControlCabinetType GetElectricControlCabinetType() override;
    bool GetIsPowerDownSave() override;
    CtrlAuthority GetControlAuthority() override;
    IR_CTRL_SET GetIrLinkAuthority() override;
    int32s GetInputNum() override;
    int32s GetOutputNum() override;
    int32s GetAdNum() override;
    int32s GetDaNum() override;
    bool GetStructParameters(double parameters[LINK_PARM_NUM]) override;
    bool GetCompensationParameters(double parameters[COM_PARM_NUM]) override;
    bool GetAxisPositiveLimit(double limits[JOINT_AXIS_NUM]) override;
    bool GetAxisNegativeLimit(double limits[JOINT_AXIS_NUM]) override;
    bool GetServoAxisType(char axisType[8]) override;
    int32u GetFpgaVersion() override;
    bool GetRobotBodyModel(char bodyModel[128]) override;
    bool GetBusInstall(char busInstall[4]) override;
    int32u GetHardWareVer() override;
    string GetRCVersionName() override;
    bool GetInitDataIsReady() override;
    bool InitDataRead() override;

    // 获取示教器版本信息
    string getTeachPadVersion() override;

    // 读取示教器版本信息
    int readTeachPadVersion();

    // 向控制器写入示教器版本信息
    int WriteTeachPadVerInfo(const char TeachPadVerInfo[40]);

    /**
     * @brief 判断A版本是否比B版本新（传入的版本号需要经过getVRCVersion格式化或是标准的VRC版本，如VXRXXCX）
     * @versionA A版本
     * @versionB B版本
     * @return
     */
    int checkVersionAIsNewerThanVersionB(string versionA, string versionB);

    // 获取版本信息
    int getControllerVersionInfo(std::vector<string> &verInfo) override;

    string getVRCVersion(string tempVersion, bool isNeedC = true) override;

    int getVRCVersion(string tempVersion, int &versionVNum, int &versionRNum, int &versionCNum) override;

    int getRcVersionNum(int32s &i32ValV, int32s &i32ValR, int32s &i32ValC);

    bool checkVRCVersion(string tempVersion, int versionVRNum, int versionCNum) override;

    bool rcVersionIsNewerThanV4R24C3() override;

    bool rcVersionIsNewerThanV4R24C4() override;

    virtual bool rcVersionIsNewerThanV4R24C5() override;

    virtual bool rcVersionIsNewerThanV4R25C1() override;

    bool rcVersionIsNewerThan(int versionVRNum, int versionCNum) override;

    int readCobotToolIOVersion(std::string &data) override;

    virtual int readFileOrFolderSizeInRc(const std::string &path) override;
#pragma endregion

#pragma region 周期数据

private:
    std::vector<string> _verInfo;  // 版本信息
    // 运行状态
    ControllerRunStatus m_RunStatus;
    void OnRunStatusChange(ControllerRunStatus runStatus);
    // 警告Id
    int32s m_WarningId;
    void OnWarningIdChange(int32s warningId);
    // 错误Id
    int32s m_ErrorId;
    void OnErrorIdChange(int32s errorId);
    // 控制器模块通信状态
    int16u *m_ModuleCommState;
    void OnModuleCommStateChange(int16u moduleCommState[MODULE_NUM]);
    // Output控制状态
    int8u *m_OutputState;
    void OnOutputStateChange(int8u outputState[MAXIONUM]);
    // DA控制状态
    int8u *m_DAState;
    void OnDAStateChange(int8u daState[MAXDANUM]);
    // 安全门状态（0-无警示 1-有警示）
    int8u m_SafeDoorState;
    void OnSafeDoorStateChange(int8u safeDoorState);
    // 功率等级（0-低功率 1-高功率）
    int8u m_PowerLevel;
    void OnPowerLevelChange(int8u powerLevel);
    // 当前工具工件匹配状态
    ToolWobjMatchStatus m_ToolWobjMatchStatus;
    void OnToolWobjMatchStatusChange(ToolWobjMatchStatus status);

    // 实时数据同步开关
    bool m_IsRealData;
    // 实时数据同步间隔时间（毫秒，小于等于0时会不进行实时数据同步）
    int32s m_RealDataInterval = 100;
    // 实时数据同步线程
    std::shared_ptr<std::thread> _pRealDataThread;
    void RealData();
    // 22之前的版本的实时数据
    bool RealDataEx();
    // 22版本的实时数据
    bool RealDataV0322();

    // 重置控制器实时数据
    void RealDataReset(bool isResetAll);
    // 实时数据是否已准备就绪（连接后至少成功读取过一次实时数据）
    // 初始化数据更新信号依赖于实时数据准备就绪，否则初始化数据更新信号将在实时数据线程中发出
    bool m_RealDataIsReady;

    // 打包获取实时数据（为了兼容TP老代码，后续待优化移除）
    RCSTS_INFO_0322 m_RcStsInfo0322;

public:
    ControllerRunStatus GetRunStatus() override;
    int32s GetWarningId() override;
    int32s GetErrorId() override;
    void GetModuleCommState(int16u moduleCommState[MODULE_NUM]) override;
    void GetOutputState(int8u outputState[MAXIONUM]) override;
    void GetDaState(int8u daState[MAXDANUM]) override;
    int8u GetSafeDoorState() override;
    int8u GetPowerLevel() override;
    ToolWobjMatchStatus GetToolWobjMatchStatus() override;

    bool GetIsRealData() override;
    void SetIsRealData(bool isRealData) override;
    int32s GetRealDataInterval() override;
    void SetRealDataInterval(int32s realDataInterval) override;
    bool GetRealDataIsReady() override;

    void GetRcStsInfo0322(RCSTS_INFO_0322 &rcStsInfo0322) override;

#pragma endregion

#pragma region 速度

private:
    // 速度值
    int16u m_Speed;
    // 速度值延时更新开关
    bool m_SpeedDelayRefresh;
    // 设定发生时间
    int64u m_SpeedSetTime;
    // 速度值延时更新时间（毫秒，在指定时长范围内周期数据不能更新速度值）
    int32u m_SpeedDelayRefreshTime;
    // 变更速度值（自动判断并触发变更事件）
    void SpeedOnChange(int16u speed);

public:
    int16u GetSpeed() override;
    void SetSpeed(int16u speed) override;

#pragma endregion

#pragma region 寸动

private:
    // 当前寸动等级
    MoveStepGrade m_MoveStepGrade;
    // 寸动等级更新延时开关
    bool m_MoveStepGradeDelayRefresh;
    // 设定发生时间
    int64u m_MoveStepGradeSetTime;
    // 寸动等级延时更新时间（毫秒，在指定时长范围内周期数据不能更新寸动等级）
    int32u m_MoveStepGradeDelayRefreshTime;
    // 变更当前寸动等级（自动判断并触发变更信号）
    void MoveStepGradeOnChange(MoveStepGrade grade);

public:
    MoveStepGrade GetMoveStepGrade() override;
    void SetMoveStepGrade(MoveStepGrade grade) override;

#pragma endregion

#pragma region 当前坐标系类型

private:
    // 当前坐标系类型
    InoRobUtil::CoordType m_CurrentCoordType;
    // 当前坐标系类型延时更新开关
    bool m_DelayRefreshCurrentCoordType;
    // 当前坐标系类型设定时间
    int64u m_CurrentCoordTypeSetTime;
    // 当前坐标系类型延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前坐标系类型）
    int32u m_RefreshCurrentCoordTypeDelayTime;
    // 变更当前坐标系类型（自动判断并触发变更事件）
    void OnCurrentCoordTypeChange(InoRobUtil::CoordType coordType);

public:
    InoRobUtil::CoordType GetCurrentCoordType() override;
    void SetCurrentCoordType(InoRobUtil::CoordType coordType) override;

#pragma endregion

#pragma region 当前显示的位置格式

private:
    // 位置格式
    InoRobUtil::PosFormat m_PosFormat;
    // 位置格式延时更新开关
    bool m_DelayRefreshPosFormat;
    // 位置格式设定时间
    int64u m_PosFormatSetTime;
    // 位置格式延时更新时间（毫秒，在指定时长范围内周期数据不能更新位置格式）
    int32u m_RefreshPosFormatDelayTime;
    // 变更当前位置格式（自动判断并触发变更事件）
    void OnPosFormatChange(InoRobUtil::PosFormat posFormat);

public:
    InoRobUtil::PosFormat GetPosFormat() override;
    void SetPosFormat(InoRobUtil::PosFormat posFormat) override;

#pragma endregion

#pragma region 当前显示的位置

private:
    // 当前位置（机械单元）
    double m_CurrentPosition[JOINT_AXIS_NUM];
    bool OnCurrentPositionChange(double position[JOINT_AXIS_NUM]) override;

public:
    bool GetCurrentPosition(double position[JOINT_AXIS_NUM]) override;

#pragma endregion

#pragma region 当前工具号

private:
    // 当前工具号
    int16u m_ToolId;
    // 当前工具号更新延时开关
    bool m_ToolIdDelayRefresh;
    // 设定发生时间
    int64u m_ToolIdSetTime;
    // 当前工具号延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前工具号）
    int32u m_ToolIdDelayRefreshTime;
    // 变更当前工具号（自动判断并触发变更事件）
    void ToolIdOnChange(int16u toolId);

public:
    int16u GetToolId() override;
    void SetToolId(int16u toolID) override;

#pragma endregion

#pragma region 当前工件号

private:
    // 当前工件号
    int16u m_WobjId;
    // 设定发生时间
    int64u m_WobjIdSetTime;
    // 当前工件号延时更新开关
    bool m_WobjIdDelayRefresh;
    // 当前工件号延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前工件号）
    int32u m_WobjIdDelayRefreshTime;
    // 变更当前工件号（自动判断并触发变更事件）
    void WobjIdOnChange(int16u wobjId);

public:
    int16u GetWobjId() override;
    void SetWobjId(int16u wobjID) override;

#pragma endregion

#pragma region 当前负载号

private:
    // 当前负载号
    int16u m_LoadId;
    // 设定发生时间
    int64u m_LoadIdSetTime;
    // 当前负载号延时更新开关
    bool m_LoadIdDelayRefresh;
    // 当前负载号延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前负载号）
    int32u m_LoadIdDelayRefreshTime;
    // 变更当前负载号（自动判断并触发变更事件）
    void LoadIdOnChange(int16u loadId);

public:
    int16u GetLoadId() override;
    void SetLoadId(int16u loadID) override;

#pragma endregion

#pragma region 机械单元

private:
    // 机械单元列表（通过初始化数据构造）
    vector<MechUnitInfo> *m_MechUnitList;
    // 当前机械单元状态延时更新开关
    bool m_MechUnitStatusDelayRefresh;
    // 机械单元状态切换发生时间
    int64u m_MechUnitStatusChangeTime;
    // 当前机械单元状态延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前机械单元状态）
    int32u m_MechUnitStatusDelayRefreshTime;
    // 机械单元初始化
    void MechUnitInit(int8u mechUnitNum, int8u mechUnitAxis[MAX_MECHUNIT_NUM], int8u mechUnitShowType[MAX_MECHUNIT_NUM], char mechUnitName[MAX_MECHUNIT_NUM][MECHUNIT_NAME_LENGTH]);
    // 变更机械单元状态（自动判断并触发变更事件）
    void MechUnitStatusOnChange(int8u mechUnitState[MAX_MECHUNIT_NUM]);

public:
    vector<MechUnitInfo> *GetMechUnitList() override;
    void GetActiveMechUnit(MechUnitInfo &mechUnitInfo) override;
    int8u GetActiveMechUnitAxisNum() override;
    int8u GetActiveMechUnitIndex() override;
    int8u GetRobotMechUnitAxisNum() override;
    void MechUnitStatusChange() override;

#pragma endregion

#pragma region 使能

private:
    // 使能状态
    bool m_Enable;
    // 使能状态延时更新开关
    bool m_EnableDelayRefresh;
    // 使能状态切换发生时间
    int64u m_EnableSetTime;
    // 使能状态延时更新时间（毫秒，在指定时长范围内周期数据不能更新使能状态）
    int32u m_EnableDelayRefreshTime;
    // 变更使能状态（自动判断并触发变更事件）
    void EnableOnChange(bool status);

public:
    bool GetEnable() override;

#pragma endregion

#pragma region 急停

private:
    // 急停状态
    bool m_Emergency;
    // 急停状态延时更新开关
    bool m_EmergencyDelayRefresh;
    // 急停状态切换发生时间
    int64u m_EmergencySetTime;
    // 急停状态延时更新时间（毫秒，在指定时长范围内周期数据不能更新急停状态）
    int32u m_EmergencyDelayRefreshTime;
    // 变更急停状态（自动判断并触发变更事件）
    void EmergencyOnChange(bool status);

public:
    bool GetEmergency() override;

#pragma endregion

#pragma region 协作专用 本体上电
private:
    CoRobotBodyPowerState m_CoRobotBodyPowerState;
    void CoRobotBodyPowerStateChange(const CoRobotBodyPowerState status);

public:
    // 获取本地上电状态（true：已打开电源，false：已关闭电源）
    virtual CoRobotBodyPowerState GetCoRobotBodyPowerState() override;
#pragma endregion

#pragma region 运行模式

private:
    // 运行模式
    RunMode m_RunMode;
    // 运行模式更新延时开关
    bool m_RunModeDelayRefresh;
    // 设定发生时间
    int64u m_RunModeSetTime;
    // 运行模式延时更新时间（毫秒，在指定时长范围内周期数据不能更新运行模式）
    int32u m_RunModeDelayRefreshTime;
    // 变更运行模式（自动判断并触发变更事件）
    void RunModeOnChange(RunMode runMode);

public:
    RunMode GetRunMode() override;

#pragma endregion

#pragma region 机械锁定

private:
    // 锁定状态
    bool m_MechLock;
    // 状态延时更新开关
    bool m_MechLockDelayRefresh;
    // 切换发生时间
    int32u m_MechLockSetTime;
    // 单次切换的最长等待时间（毫秒）
    int32u m_MechLockDelayRefreshTime;
    // 变更机械锁定状态（自动判断并触发变更事件）
    void MechLockOnChange(bool status);

public:
    bool GetMechLock() override;
    void SetMechLock(bool status) override;

#pragma endregion

#pragma region 动态制动

private:
    // 动态制动状态
    bool m_DynamicBrake;
    // 当前状态延时更新开关
    bool m_DynamicBrakeDelayRefresh;
    // 切换发生时间
    int64u m_DynamicBrakeSetTime;
    // 当前状态延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前状态）
    int32u m_DynamicBrakeDelayRefreshTime;
    // 变更动态制动状态（自动判断并触发变更事件）
    void DynamicBrakeOnChange(bool status);

public:
    bool GetDynamicBrake() override;
    void SetDynamicBrake(bool status) override;

#pragma endregion

#pragma region 协调

private:
    // 机器人当前协调的机械单元名称（为空表示关闭协调）
    string m_CooperateMechUnitName;
    // 机器人当前协调的机械单元名称延时更新开关
    bool m_CooperateDelayRefresh;
    // 开启/关闭协调发生时间
    int64u m_CooperateSetTime;
    // 机器人当前协调的机械单元名称延时更新时间（毫秒，在指定时长范围内周期数据不能更新当前名称）
    int32u m_CooperateDelayRefreshTime;
    // 当前机械单元是否满足协调条件（可显示协调按钮）
    bool m_CooperateIsReady;
    // 变更机器人协调的机械单元名称（自动判断并触发变更事件）
    void CooperateOnChange(const string &mechUnitName);
    // 当前机械单元是否满足协调条件（可显示协调按钮）
    void SetCooperateIsReady(bool isReady);

public:
    string GetCooperate() override;
    void SetCooperate(const string &mechUnitName) override;
    bool GetCooperateIsReady() override;

#pragma endregion

#pragma region 控制器设备状态
public:
    EDevState getDeviceState() override;

private:
    EDevState _deviceSate = EDevState::OFFLINE;
    // 设备实时状态检测（离线 使能 急停 报警 警告 待机）
    void onDeviceStateChange(const int16u enable, const int16u emerg, const int32s warnId, const int32s errId);
#pragma endregion

#pragma region 夹持器
private:
    // 是否接入
    bool m_GripperEnable;
    // 三位置使能状态
    bool m_GripperThreePositionEnable;
    // 变更接入状态
    void GripperEnableChange(bool status);
    // 变更使能状态（自动判断并触发变更事件）
    void GripperThreePositionEnableChange(bool status);
#pragma endregion

public:
#pragma region 协作ABZ监控
    int readCobotABZDatas(std::string &datas) override;
#pragma endregion

#pragma region 协作WiFi频段
private:
    // 控制器WiFi是否2.4GHz频段
    bool m_ControllerWiFiFrequencyBandEnable;
    // 控制器WiFi是否启用2.4GHz频段
    void ControllerWiFiFrequencyBandChange(bool enable);
#pragma endregion

#pragma region 文件管理
public:
    // 通知控制器对要导出的文件进行备份
    int exportDocumentsToLocal(int32u docusNum, vector<string> &docuMentsName) override;
    // 通知控制器对要删除的文件进行删除
    int deleteDocumentsFromRc(int32u docusNum, vector<string> &docuMentsName) override;
    // 读取控制器操作状态
    int readDocumentsStatus(int32u status[10]) override;
#pragma endregion

#pragma region 协作缩减模式触发
private:
    bool m_SpeedReduingTriggerd;
    // 功能安全缩减模式触发信号（协作）
    void SpeedReduingTriggerdChange(bool enable);
#pragma endregion

#pragma region 协作安全监控状态
private:
    bool m_SafetyMonitorStatus;
    // 功能安全监控状态触发信号（协作）
    void SafetyMonitorStatusChange(bool enable);
#pragma endregion

#pragma region 碰撞检测推荐值
private:
    void CollisionRecommendedValueChange(int16s value);
#pragma endregion

#pragma region 碰撞检测状态改变
private:
    void CollisionStatusChange(bool isChanged);
#pragma endregion
};
}  // namespace InoRobBusiness
