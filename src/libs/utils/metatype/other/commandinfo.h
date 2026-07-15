#pragma once
#include <QModelIndex>
#include <QMetaEnum>
#include <QMetaType>
#include "ctrlauthority.h"
#include "coordparam.h"
#include "pointdata.h"
#include "projectdata.h"
#include "toolparams.h"
#include "wobjparams.h"
#include "peripheral/ethernertipparams.h"
#include "peripheral/ethernertcatparams.h"
#include "peripheral/modbusparams.h"
#include "metatype_global.h"
#include "safety/crashdetectparams.h"
#include "motionparam.h"

#define BIND(cmd, ...)  (static_cast<CmdDatas<__VA_ARGS__>*>(cmd))->m_data;

class METATYPE_EXPORT AbstractCmd : public QObject
{
    Q_OBJECT
public:
    AbstractCmd()
    {
    }
    virtual ~AbstractCmd()
    {
    }

    enum CmdType {
        CmdType_UnKnown,
        CmdType_GetCurJPos,
        // 运动控制命令
        CmdType_RobotMoveTeachStart,  // 示教运动控制
        CmdType_RobotMoveTeachStop,   // 示教运动停止
        CmdType_RobotMoveStop,        // 机械臂停止运动
        CmdType_RobotMoveJointTeach,
        CmdType_RobotMoveJointWithRP,
        CmdType_RobotMoveJointToInitPosture,
        CmdType_RobotMoveLineTeach,
        CmdType_RobotMoveRotateTeach,
        CmdType_RobotMoveLineToTarget,  // Move line to here

        //全局变量命令
        CmdType_GetGlobalVar_B_EveryCol,
        CmdType_GetGlobalVar_R_EveryCol,
        CmdType_GetGlobalVar_D_EveryCol,
        CmdType_GetGlobalVar_PR_EveryCol,
        CmdType_GetGlobalVar_String_EveryCol,
        CmdType_GetGlobalVar_P_EveryColForCurrentShow,
        CmdType_GetGlobalVar_JP_EveryColForCurrentShow,

        CmdType_GetGlobalVar_B_ValuesCol,
        CmdType_GetGlobalVar_R_ValuesCol,
        CmdType_GetGlobalVar_D_ValuesCol,
        CmdType_GetGlobalVar_PR_ValuesCol,
        CmdType_GetGlobalVar_String_ValuesCol,
        CmdType_GetGlobalVar_P_ValuesCol,
        CmdType_GetGlobalVar_JP_ValuesCol,

        CmdType_GetGlobalVar_B_FavorireCol,
        CmdType_GetGlobalVar_R_FavorireCol,
        CmdType_GetGlobalVar_D_FavorireCol,

        CmdType_SetGlobalVar_B_Values,
        CmdType_SetGlobalVar_R_Values,
        CmdType_SetGlobalVar_D_Values,
        CmdType_SetGlobalVar_PR_Values,
        CmdType_SetGlobalVar_String_Values,

        CmdType_SetGlobalVar_B_Favorite,
        CmdType_SetGlobalVar_R_Favorite,
        CmdType_SetGlobalVar_D_Favorite,
        CmdType_SetGlobalVar_String_Favorite,

        CmdType_SetGlobalVar_Scheduler_B,
        CmdType_SetGlobalVar_Scheduler_R,
        CmdType_SetGlobalVar_Scheduler_D,
        CmdType_SetGlobalVar_Scheduler_PR,
        CmdType_SetGlobalVar_Scheduler_String,
        //没有调度接口
        CmdType_SetGlobalVar_Scheduler_P,
        CmdType_SetGlobalVar_Scheduler_JP,

        // 外设
        CmdType_WriteEthernetIpConfig,
        CmdType_ReadEthernetIpConnStatus,
        CmdType_WriteModbusConfig,
        CmdType_ReadModbusConnStatus,
        CmdType_WriteEtherCatConfig,
        CmdType_ReadEtherCatStatus,
        CmdType_CheckOtherFieldBusIsActive,
        CmdType_EnableGripperThreePosition,
        CmdType_GetBusSwitchEnableStatus,
        CmdType_EnableSingleControllerRunMode,
        CmdType_GetSingleControllerRunModeStatus,

        // 松抱闸
        CmdType_ReadBrakeState,
        CmdType_ReleaseBrake,
        CmdType_CloseBrake,

        // device info (version info)
        CmdType_GetRobotDeviceInfo,

        CmdType_Ping,
        CmdType_SetControllerWifiPassword,
        CmdType_SetControllerWifiFrequencyBand,
        CmdType_GetControllerWifiInfo,

        CmdType_ProgramStart,  // 44
        CmdType_ProgramPause,
        CmdType_ProgramContinue,
        CmdType_ProgramStop,
        CmdType_ProgramStep,

        // Inovance Cmd
        CmdType_ConnectController,
        CmdType_ConnectVirtualController,
        CmdType_DisconnectController,
        CmdType_EnableMechLock,
        CmdType_ClearAlarm,
        CmdType_EnableRobot,
        CmdType_AxisMove,
        CmdType_SetEmergency,

        // 功能安全
        CmdType_CheckSafeParaPassword,
        CmdType_CheckLastSafeParaPassword,
        CmdType_ReadSafetyParam2Model,
        CmdType_ReadSafetyParam2GUI,
        CmdType_ReadSafeParamsFromMcuDirect,
        CmdType_WriteSafetyParam2Model,
        CmdType_WriteSafetyParam2MCU,
        CmdType_WriteSafeParamsToMcuDirect,
        CmdType_SafetyReset,
        CmdType_SafetyCheckAStatus,
        CmdType_SafetyGetHardVer,
        CmdType_SafetyQuerySafeIORealTime,
        CmdType_SafetyMultiWrite,
        CmdType_SafetyMultiRead,

        CmdType_SafetySnycIO,
        CmdType_SafetySnycAxisSpeed,
        CmdType_SafetySnycPositionDismatch,
        CmdType_SafetySnycAxisPosition,
        CmdType_SafetySnycAxisTorque,
        CmdType_SafetySnycAxisPower,
        CmdType_SafetySyncCartesianPosition,
        CmdType_SafetySyncZone,
        CmdType_SafetySyncObject,
        CmdType_SafetySyncCartesianSpeed,
        CmdType_SafetySyncCartesianDirection,
        CmdType_SafetySnycSafetyStatic,

        CmdType_SafetyReadSpeedReducing,
        CmdType_SafetyWriteSpeedReducing,
        CmdType_SafetySetInterZoneStatus,

        CmdType_SafetyInterAreaTakePoint,
        CmdType_SafetyEndObjectTakePoint,

        CmdType_SafetyExportConfig,
        CmdType_SafetyImportConfig,

        // 运动
        CmdType_MotionSetMoveStepGrade,
        CmdType_MotionGetMoveStepSizePara,
        CmdType_MotionSetMoveStepSizePara,

        // 工程管理
        CmdType_PutFilesToController,
        CmdType_RemoveFilesFromController,
        CmdType_ImportLocalProject,
        CmdType_ExportProject,
        CmdType_SetActiveProject,
        CmdType_RefreshProjectDatas,
        CmdType_GetProjectList,
        CmdType_ReadProject,
        CmdType_ReadLocalProject,
        CmdType_CreateLocalProject,
        CmdType_CreateProject,
        CmdType_DeleteProject,
        CmdType_CopyProject,
        CmdType_GenPasteProjectName,
        CmdType_PasteProject,
        CmdType_GetDefaultProjectName,
        CmdType_RenameProject,
        CmdType_SaveProject,
        CmdType_SaveAsProject,

        // 工程文件列表
        CmdType_GetProjectFileList,
        CmdType_ReloadActiveProject,

        // 位置点文件
        CmdType_GetDefaultRPointFileName,
        CmdType_GetRobotPointFileList,
        CmdType_SetCurRobotPointFile,
        CmdType_CreateRobotPointFile,
        CmdType_DeleteRobotPointFile,
        CmdType_CopyRobotPointFile,
        CmdType_PasteRobotPointFile,
        CmdType_GenPasteRPointFileName,
        CmdType_ReadRobotPoints,
        CmdType_CheckRobotPointIsExist,
        CmdType_AddRobotPoint,
        CmdType_CopyRobotPoint,
        CmdType_PasteRobotPoint,
        CmdType_DeleteRobotPoint,
        CmdType_ChangeRobotPoint,
        CmdType_ChangeRobotPointPos,
        CmdType_ReplaceRobotPoint,
        CmdType_RenameRobotPoint,
        CmdType_ImportRobotPointFile,
        CmdType_ExportRobotPointFile,
        CmdType_AddRobotPointByIndex,

        // 关节点文件
        CmdType_GetJointPointFileList,
        CmdType_SetCurJointPointFile,
        CmdType_ReadJointPoints,
        CmdType_CheckJointPointIsExist,
        CmdType_AddJointPoint,
        CmdType_CopyJointPoint,
        CmdType_PasteJointPoint,
        CmdType_DeleteJointPoint,
        CmdType_ChangeJointPoint,
        CmdType_ChangeJointPointPos,
        CmdType_ReplaceJointPoint,
        CmdType_RenameJointPoint,
        CmdType_AddJointPointByIndex,

        // 标签
        CmdType_GetLabelTypeList,
        CmdType_GenInitIoItems,
        CmdType_GetIoItems,
        CmdType_GenInitAdDaItems,
        CmdType_GetAdDaItems,
        CmdType_GenInitOtherItems,
        CmdType_GetOtherItems,
        CmdType_ModifyIoItem,
        CmdType_ModifyAdDaItem,
        CmdType_ModifyOtherItem,
        CmdType_UpdateToolIOItemDesc,

        //局部变量
        CmdType_UpdateTempVariablesFile,

        // 用户自定义告警
        CmdType_GetUserDefineWarningFileList,
        CmdType_GetUserDefineWarnings,
        cmdType_ModifyUserDefineWarning,

        // 任务
        CmdType_GetTaskList,
        CmdType_ActiveTask,
        CmdType_TaskManage,

        // 工况监控
        CmdType_WorkCond_ResetHisMaxCurrent,
        CmdType_WorkCond_ReadActCurrent,
        CmdType_WorkCond_ReadHisMaxCurrent,
        CmdType_WorkCond_ReadActLoadrate,
        CmdType_WorkCond_ReadOverHeat,
        CmdType_WorkCond_ReadActualOverLoad,
        CmdType_WorkCond_ReadMaxOverLoad,
        CmdType_WorkCond_ResetMaxOverLoad,
        CmdType_WorkCond_setElectricScheduler,
        CmdType_WorkCond_setAvgLoadRateScheduler,
        CmdType_WorkCond_setOverLoadScheduler,
        CmdType_WorkCond_setOverHeatScheduler,

        // 轴参数设置
        CmdType_AxisParams_ReadTorqueLimit,
        CmdType_AxisParams_ReadAvrLoadLimit,
        CmdType_AxisParams_ReadOverHeatLimit,
        CmdType_AxisParams_ReadOverLoadLimit,
        CmdType_AxisParams_SaveTorqueLimit,
        CmdType_AxisParams_SaveAvrLoadLimit,
        CmdType_AxisParams_SaveOverHeatAndLoadLimit,

        // 安装姿态
        CmdType_InstallationPosture_Read,
        CmdType_InstallationPosture_Write,

        // 总线调度
        CmdType_SetModbusConnectScheduler,
        CmdType_SetEthernetIPConnectScheduler,
        CmdType_SetEthercatConnectScheduler,

        // 负载
        CmdType_Load_Refresh,
        CmdType_Load_Clear,
        CmdType_Load_Save,
        CmdType_Load_GetNames,

        // 工具
        CmdType_Tool_GetCurToolName,
        CmdType_Tool_GetItems,
        CmdType_Tool_Save,
        CmdType_Tool_Refresh,
        CmdType_Tool_Clear,
        CmdType_Tool_IdNameSearch,
        CmdType_Tool_HoldTypeCalibMethodSearch,
        CmdType_Tool_CalibMethodNameSearch,
        CmdType_Tool_Calibrate,
        CmdType_Tool_SaveCalibratePoints,
        CmdType_Tool_RefreshCalibratePoints,
        CmdType_Tool_MoveToPoint,
        CmdType_Tool_ToolExcuteMoveTypeNameSearch,
        CmdType_Tool_ToolPointsNameQuery,
        CmdType_Tool_CalibMethodByName,
        CmdType_Tool_CalibrateTipSearch,

        // 调试
        CmdType_Debugger_StartReleaseRead,
        CmdType_Debugger_StartReleaseWrite,

        // 工件
        CmdType_WObj_GetNames,
        CmdType_WObj_GetWObjCount,
        CmdType_WObj_SetCurrentWObjId,
        CmdType_WObj_GetCurrentWobjParam,
        CmdType_WObj_GetWobjParam,
        CmdType_WObj_SetWobjParam,
        CmdType_WObj_SaveWObjParams,
        CmdType_WObj_RefreshWObjParams,
        CmdType_WObj_ClearWobjParams,
        CmdType_WObj_WObjCalibrate,
        CmdType_WObj_SaveWObjCalibratePoints,
        CmdType_WObj_RefreshWObjCalibratePoints,
        CmdType_WObj_WObjMoveToPoint,
        CmdType_WObj_WobjIdNameSearch,
        CmdType_WObj_CalibUFrameMethodNameSearch,
        CmdType_WObj_CalibOFrameMethodNameSearch,
        CmdType_WObj_HoldTypeUFrameCalibMethodSearch,
        CmdType_WObj_HoldTypeOFrameCalibMethodSearch,
        CmdType_WObj_WObjUFramePointsNameQuery,
        CmdType_WObj_WObjOFramePointsNameQuery,

        // 碰撞检测
        CmdType_CrashDetect_Read,
        CmdType_CrashDetect_Write,
        CmdType_CrashDetect_ReadRecommandValue,
        CmdType_CrashDetect_ResetRecommandValue,

        // Debugger
        CmdType_Debugger_SetDebugMode,
        CmdType_Debugger_GetTrajRecvFlag,
        CmdType_Debugger_SetTrajRecvExecMode,

        // 轨迹恢复
        CmdType_TrajRecv_ReadParams,
        CmdType_TrajRecv_WriteParams,

        // 逆解函数
        CmdType_KineInverseSolution,

        // 系统升级
        CmdType_ExecUpgrade,
        CmdType_ReadSystemUpgradeInfo,

        // 启动释放策略
        CmdType_ReadEmgTrigMethod,
        CmdType_SaveEmgTrigMethod,
        CmdType_SaveEmgStopMode,
        CmdType_ReadEmgStopMode,

        // 控制面板
        CmdType_Control_SetToolId,
        CmdType_Control_SetWObjId,
        CmdType_Control_SetLoadId,
        CmdType_Control_SetSpeed,
        CmdType_Control_SetDeviceMode,
        CmdType_Control_SetCoordType,
        CmdType_Control_SetPosFormat,

        CmdType_Control_JointMoveZeroStart,
        CmdType_Control_JointMoveZeroEnd,

        CmdType_Control_DownloadFile,

        CmdType_InitTeachPadInfo,
        CmdType_Control_Move2Point_GetFileList,
        CmdType_Control_Move2Point_GetPtList,
        CmdType_Control_Move2Point_SetCurrent,

        // 心跳
        CmdType_Connection_SetHeatBeat,
        // 用户管理
        CmdType_UserLogin,
        // 控制器
        CmdType_SetCtlAuthority,

        // IO监控命令
        // in get
        CmdType_Get_Input_CommonIndex,
        CmdType_Get_Input_CommonValues,
        CmdType_Get_Input_ValuesStandard,
        CmdType_Get_Input_ValuesTool,
        CmdType_Get_Input_ValuesFieldBus,
        CmdType_Get_Input_ValuesMemory,
        CmdType_Get_Input_LabelsAndRemark,
        CmdType_Get_Input_ControlAuthority,
        // in set
        CmdType_Set_Input_Values,
        CmdType_Set_Input_ValuesForce,
        CmdType_Set_Input_Schedule,

        // out get
        CmdType_Get_Output_CommonIndex,
        CmdType_Get_Output_CommonValues,
        CmdType_Get_Output_ValuesStandard,
        CmdType_Get_Output_ValuesTool,
        CmdType_Get_Output_ValuesFieldBus,
        CmdType_Get_Output_ValuesMemory,
        CmdType_Get_Output_LabelsAndRemark,
        CmdType_Get_Output_ControlAuthority,
        // out set
        CmdType_Set_Output_Schedule,
        CmdType_Set_Output_Values,
        // AD get
        CmdType_Get_AD_Values,
        // AD set
        CmdType_Set_AD_Schedule,
        // CmdType_Set_AD_Values,
        // DA get
        CmdType_Get_DA_Values,
        // DA set
        CmdType_Set_DA_Schedule,
        CmdType_Set_DA_Values,

        CmdType_Get_Cobot_AD_DA_Values,
        CmdType_Set_Cobot_AD_DA_Values,

        // SystemIn get
        CmdType_Get_SystemIn_Values,
        CmdType_Get_SystemIn_Reamarks,
        // SystemIn Set
        CmdType_Set_SystemIn_Schedule,

        // SystemOut get
        CmdType_Get_SystemOut_Values,
        CmdType_Get_SystemOut_Reamarks,
        // SystemIn Set
        CmdType_Set_SystemOut_Schedule,

        //外设配置
        CmdType_Refresh_IOMapping_Values_FromController,
        CmdType_Get_IOMapping_Values,
        CmdType_Reset_IOMapping_Values,
        CmdType_Save_IOMapping_Values,
        CmdType_Save_IOMapping_Remarks,
        CmdType_Import_IOMapping_Files,
        CmdType_Export_IOMapping_Files,
        //提示补全信息
        CmdType_VirtualKeyBoard_InputNewSuffix,
        CmdType_VirtualKeyBoard_SuffixStringSoucrce,
        CmdType_VirtualKeyBoard_GetALlLabels,
        //通讯设置 ip
        CmdType_Communication_GetEthDatas,
        CmdType_Communication_SetEthDatas,
        CmdType_CommunicationAdmin_ReadAllNetStatus,
        CmdType_Communication_SetOneNetStatus,
        CmdType_Communication_ReadMode,
        CmdType_Communication_SaveMode,
        CmdType_Communication_SetNewPort,
        CmdType_GetAbsoluteZeroCurrentMotorValue,
        CmdType_GetAbsoluteZero,
        CmdType_SetAbsoluteZero,
        CmdType_ResetAbsoluteZero,
        CmdType_GetResetAbsoluteZeroResult,
        CmdType_GetWorkOriginData,
        CmdType_SetWorkOrigin,
        CmdType_SetWorkOriginTriggerData,
        CmdType_GetVersionInfo,
        CmdType_Get_ConrtollerTime,
        CmdType_Set_ConrtollerTime,
        CmdType_SetRobotBodyPowerState,

        // 报警信息
        CmdType_SetWarnInfoEnable,

        // 拖动示教
        CmdType_DragTeach_AutoRecordPointResult,

        CmdType_Control_GetFirstBootStatus,

        // 参数
        CmdType_GetToolParam,
        CmdType_GetWobjParam,
        CmdType_GetLoadParam,

        // 更新本地缓存数据
        CmdType_UpdateLocalPosData,
        CmdType_UpdateLocalToolWobjParams,
        CmdType_UpdateLocalSafetyMcuData,
        CmdType_ConnectSuccess,

        // 通配
        CmdType_GeneralMatch_GetOpenStatus,
        CmdType_GeneralMatch_SetOpenStatus,
        CmdType_GeneralMatch_AllowTracing,
        CmdType_GeneralMatch_GetRecords,
        CmdType_GeneralMatch_GetInfo,
        CmdType_GeneralMatch_GetSyncStatus,
        CmdType_GeneralMatch_StartRobotParamSync,
        CmdType_GeneralMatch_readRobotParamMatchInfo,

        CmdType_GetDragTeach_Status,

        // 负载辨识
        CmdType_LoadIdentity_StartIdentity,
        CmdType_LoadIdentity_StopIdentity,
        CmdType_LoadIdentity_ReadIdentifyData,
        CmdType_LoadIdentity_ReadIdentifyStatus,
        CmdType_LoadIdentity_ReadIdentifyResult,
        CmdType_LoadIdentity_GetIdentifyType,
        CmdType_LoadIdentity_SetIdentifyType,
        CmdType_LoadIdentity_ReadIdentifyTrajectoryFromRc,
        CmdType_LoadIdentity_ReadIdentifyRecommenPoint,



        //读写机器人参数
        CmdType_GetRobotBodyParameters,
        CmdType_WriteRobotBodyParameters,
        CmdType_GetTeachParameters,
        CmdType_WriteTeachParameters,
        CmdType_GetMotionParameters,
        CmdType_WriteMotionParameters,
        CmdType_ReadComState,
        CmdType_WriteComState,
        CmdType_ReadRobotName, 

        CmdType_StartDiagnose,
        CmdType_StopDiagnose,
        CmdType_ReadDiagnosePercent,

        CmdType_StartExportDiagnoseReportToUSB,
        CmdType_StartExportDiagnoseReportToLocal,
        CmdType_ReadErrExportStaToControllerUSB,
        CmdType_ReadErrExportStaToLocal,

        CmdType_SetControlAuthority,
        CmdType_GetControlAuthority,

        CmdType_GetHistoryAlarm,
        CmdType_GetRobotParamForSimulation,
        CmdType_ClearHistoryWarn,

        CmdType_GetToolIOConfig,
        CmdType_SetToolIOConfig,
        CmdType_setToolIOConfigMonitorState,

        CmdType_CheckControllerUSBIsConnected,
        CmdType_FormatMemoryCard,
        CmdType_ReadMemoryCardFormatState,

        CmdType_CheckPointFileIsExist,
        CmdType_LoadPointFile,
        CmdType_DecideReplacePointFile,

        CmdType_SetRS485OrADModel,

        CmdType_ReadRS485Config,
        CmdType_SetRS485Config,

        CmdType_SetRS485Debugging,

        CmdType_GetABZ_Data,

        CmdType_GetFieldBusAddressAssignConfig,
        CmdType_SetFieldBusAddressAssignConfig,

        CmdType_getProjectNoConfig,
        CmdType_setProjectNoConfig,
        CmdType_getPointFileNoConfig,
        CmdType_setPointFileNoConfig,

        // 指定行
        CmdType_setLogicTreeStartLine,
        CmdType_getLogicTreeStartLine,

        CmdType_startRestoreFactory,
        CmdType_readRestoreFactoryState,

        CmdType_startConfigFilesBackupToUsb,
        CmdType_readConfigFilesBackupStateToUsb,

        CmdType_startLoadConfigFilesFromUsb,
        CmdType_readLoadConfigFilesSateFromUsb,

        CmdType_getDeviceConnectionState,
        CmdType_getMobusConnectionState,
        CmdType_getEtherNetIpConnectionState,
        CmdType_getEtherCatIpConnectionState,
        CmdType_getMCConnectionState,
        CmdType_getProfinetConnectionState,

        CmdType_BackupTeachPadConfigures,
        CmdType_ExportTeachPadConfigures,
        CmdType_operationLogicTreeLineNum,
        CmdType_operationLogicTreeBreakPoint,
        CmdType_setEnabledAllLogicTreeBreakPoint,
        CmdType_getEnabledAllLogicTreeBreakPoint,

        CmdType_ExportConfigFileToLocal,
        CmdType_ImportConfigFileFromLocal,
        CmdType_ReadExportConfigFileStatusToLocal,
        CmdType_ReadImportConfigFileStatusFromLocal,

        CmdType_GetAllLogictreeItems,
        CmdType_CheckLogicTreeNode,
        CmdType_WriteLogicTreeNode,
        CmdType_WriteLogicTreeLevel,

        CmdType_ReadLogicTreeLevel,
        CmdType_ReadLogicTreeNodes,
        CmdType_CreateLogicTreeNodes,
        CmdType_SortLogicTreeNodes,
        CmdType_ClearLogicTreeNodesWhenFalid,

        CmdType_Set_ControllerLanguage,
        CmdType_Set_ModelLayerLanguage,
        CmdType_ImportLanguagePackageForTPFromLocal,
        CmdType_ImportLanguagePackageForTPFromController,
        CmdType_ImportLanguagePackageForControllerFromLocal,

        //获取当前位姿点
        CmdType_GetCurPosBaseOnToolAndWobj,
        CmdType_MoveLToPosBaseOnToolAndWobj,
        CmdType_MoveJToPosBaseOnToolAndWobj,

        CmdType_CalPalletItemBackGroundColor,

        //创建码垛箱体
        CmdType_CreatePalletizingBoxes,

        //伺服参数
        CmdType_OperateServoParamFile,
        CmdType_ChangedServoParamFile,
        CmdType_GetCurServoParamValue,
        CmdType_StartServoParams,
        CmdType_StopServoParams,
        CmdType_ServoUpdateStatusRead,

        //七轴机器人
        CmdType_SetSevenDragTeaching,
        CmdType_GetSevenDragTeaching,
        CmdType_SetSevenTaketPoint,
        CmdType_GetSevenRobotBodyParameters,
        CmdType_WriteSevenRobotBodyParameters,

        CmdType_GetLoadMotionStatus,
        CmdType_SetLoadMotionStatus,

        //goto指令
        CmdType_UpdateGotoLabelFile,

        // 机器人模型加载
        CmdType_LoadRobotModel,
        CmdType_LoadRobotModelSegment,

        // 力控
        CmdType_GetFCSensorDataArr,
        CmdType_SaveFCSensorItem,
        CmdType_GetFCCalibData,
        CmdType_SaveFCCalibItem,
        CmdType_ApplyCaliResult,
        // 是否可以标定
        CmdType_isCanCalibrate,
        CmdType_GetFCCoordinateData,
        CmdType_SaveFCCoordinateDataItem,
        CmdType_GetFCConfigPara,
        CmdType_SaveFCConfigPara,
        CmdType_GetFCControlPara,
        CmdType_SaveFCControlPara,
        CmdType_GetFCLimitPara,
        CmdType_SaveFCLimitPara,

        // 主站组态配置文件导入
        CmdType_SendMasterConfigZipFile,
        //力控监控
        CmdType_SetForceCtrlLogForamt,
        CmdType_ReadForceCtrlLogForamt,
        CmdType_SetForceCtrlMonitorSwitch,
        CmdType_ReadForceCtrlMonitorSwitch,
        CmdType_ReadForceCtrlMonitorData,
        CmdType_SetClearSensorForce,
        CmdType_SetForceCtrlCoordinateSetting,
        CmdType_ReadForceCtrlCoordinateSetting,

       
        CmdType_GetToolData,
        CmdType_GetForceCtrlLogList,
        CmdType_CopyFCLogsControllerToLoacl,

        // 摩擦补偿
        CmdType_getCoulombFrictionParams,
        CmdType_getRecommendedTrajectoryEndPoints,
        CmdType_startFricIdentification,
        CmdType_endFricIdentification,
        CmdType_getRecognitionResult,
        CmdType_setRecognitionResult,

        // 间隙补偿
        CmdType_getBacklashParams,
        // CmdType_getRecommendedTrajectoryEndPoints,
        CmdType_startBacklashIdentification,
        CmdType_endBacklashIdentification,
        // CmdType_getBacklashRecognitionResult,
        // CmdType_setBacklashRecognitionResult,

        // 设置RGB
        CmdType_setRGB,

        //虚拟控制器的设备名字
        CmdType_VritualControllerDeviceName,

    };
    Q_ENUM(CmdType)


    template <typename T>
    static T str2Enum(const QString &str)
    {
        std::string temp = str.toStdString();
        return QMetaEnum::fromType<T>()
            .keyToValue(temp.c_str());
    }

    template <typename T>
    static QString enum2Str(const T &enumType)
    {
        return QMetaEnum::fromType<T>().valueToKey(enumType);
    }

    QObject *m_object = nullptr;
    CmdType m_cmdType = CmdType_UnKnown;
};
Q_DECLARE_METATYPE(AbstractCmd::CmdType)

template <typename... Args>
class CmdDatas : public AbstractCmd
{
public:
    CmdDatas(Args... args)
    {
        m_data = std::tuple<Args...>(args...);
    }
    std::tuple<Args...> m_data;
};

// 功能安全
class METATYPE_EXPORT CmdSafetyReadParams : public AbstractCmd
{
public:
    CmdSafetyReadParams()
    {
    }

    int key = 0;
    int offset = 0;
    int num = 0;
};

class METATYPE_EXPORT CmdGetSafeParaCommon : public AbstractCmd
{
public:
    CmdGetSafeParaCommon()
    {
        forceFlag = false;
    }

    int key = 0;
    int offset = 0;
    unsigned char *buf = NULL;
    int len = 0;
    bool forceFlag = false;
};

class METATYPE_EXPORT CmdWriteSafeParamToMcuDirect : public AbstractCmd
{
public:
    CmdWriteSafeParamToMcuDirect()
    {
        forceFlag = false;
    }

    int key = 0;
    int offset = 0;
    int num = 0;
    unsigned char *buf = NULL;
    int len= 0;
    bool forceFlag = false;
};

class METATYPE_EXPORT CmdReadSafeParamFromMcuDirect : public AbstractCmd
{
public:
    CmdReadSafeParamFromMcuDirect()
    {
        forceFlag = false;
    }

    int key = 0;
    int offset = 0;
    int num = 0;
    unsigned char *buf = NULL;
    int len = 0;
    bool forceFlag = false;
};

class METATYPE_EXPORT CmdSetSafeParaCommon : public AbstractCmd
{
public:
    CmdSetSafeParaCommon()
    {
        forceFlag = false;
    }

    int key = 0;
    int offset = 0;
    unsigned char *buf = NULL;
    int len = 0;
    bool forceFlag = false;
};

class METATYPE_EXPORT CmdSafetyWriteParams : public AbstractCmd
{
public:
    CmdSafetyWriteParams()
    {
    }

    int key = 0;
    int offset = 0;
    int num = 0;
};

class METATYPE_EXPORT CmdSafetyCheckAStatus : public AbstractCmd
{
public:
    CmdSafetyCheckAStatus()
    {
    }

    int key = 0;
    int offset = 0;
    int num = 0;
    int status = 0;
};

// 轴参数设置
class METATYPE_EXPORT CmdSaveTorqueLimit : public AbstractCmd
{
public:
    CmdSaveTorqueLimit()
    {
    }

    bool bSwitch = false;
    int IntValue[ROBOT_AXIS_NUM] = {0};
};

class METATYPE_EXPORT CmdSaveAvrLoadLimit : public AbstractCmd
{
public:
    CmdSaveAvrLoadLimit()
    {
    }

    bool bSwitch = false;
    int IntValue[ROBOT_AXIS_NUM] = {0};
};

class METATYPE_EXPORT CmdWriteModbusConfig : public AbstractCmd
{
public:
    CmdWriteModbusConfig()
    {
    }

    CobotModbusParaConfig m_config;
};

class METATYPE_EXPORT CmdWriteEthernetIpConfig : public AbstractCmd
{
public:
    CmdWriteEthernetIpConfig()
    {
    }

    CobotEthernetIpPara m_params;
};

class METATYPE_EXPORT CmdWriteEthernetCatConfig : public AbstractCmd
{
public:
    CmdWriteEthernetCatConfig()
    {
    }

    InoEthcatPara m_params;
    quint16 ARMSetLinkEnhanSwitch = 0;
    quint16 EtherCATXMLReset = 0;
};

class METATYPE_EXPORT CmdSaveOverHeatAndLoadLimit : public AbstractCmd
{
public:
    CmdSaveOverHeatAndLoadLimit()
    {
    }

    bool bOverHeatSwitch = false;
    bool bOverLoadSwitch = false;
};

class METATYPE_EXPORT CmdTeachMoveControl : public AbstractCmd
{
public:
    CmdTeachMoveControl()
    {
    }

    TeachMode m_teachMode = TeachMode_Invalid;
    bool m_direction = false;
    CoordParam m_coordParam;
};

class METATYPE_EXPORT CmdRobotMoveJoint : public AbstractCmd
{
public:
    CmdRobotMoveJoint()
    {
    }

    RoadPoint m_roadPoint;
};

class METATYPE_EXPORT CmdRobotMoveJointWithRP : public AbstractCmd
{
public:
    CmdRobotMoveJointWithRP()
    {
    }

    InoRobPos m_robPos;
};

class METATYPE_EXPORT CmdRobotMoveLine : public AbstractCmd
{
public:
    CmdRobotMoveLine()
    {
    }

    RoadPoint m_destPt;
};

class METATYPE_EXPORT CmdRobotMoveRotate : public AbstractCmd
{
public:
    CmdRobotMoveRotate()
    {
    }

    CoordParam m_coordParam;
    TeachMode m_teachMode = TeachMode_Invalid;
    double m_rotateAngle  = 0;
};

class METATYPE_EXPORT CmdPing : public AbstractCmd
{
public:
    CmdPing()
    {
    }

    QString m_ip;
};

// Inovance Cmd
class METATYPE_EXPORT CmdConnectController : public AbstractCmd
{
public:
    CmdConnectController()
    {
    }

    QString m_ip;
    int m_port = 0;
};

class METATYPE_EXPORT CmdCheckOtherFieldBusIsActive : public AbstractCmd
{
public:
    CmdCheckOtherFieldBusIsActive()
    {
    }

    QObject *m_target = NULL;
    int m_type = 0;
};

class METATYPE_EXPORT CmdEnableMechLock : public AbstractCmd
{
public:
    CmdEnableMechLock()
    {
    }

    bool m_enableMechLock = false;
};

class METATYPE_EXPORT CmdEnableRobot : public AbstractCmd
{
public:
    CmdEnableRobot()
    {
    }

    bool m_enableRobot = false;
};

class METATYPE_EXPORT CmdSetEmergency : public AbstractCmd
{
public:
    CmdSetEmergency()
    {
    }

    bool m_bStatus = false;
};

class METATYPE_EXPORT CmdLoadSave : public AbstractCmd
{
public:
    CmdLoadSave()
    {
    }

    quint16 m_loadId = 0;
    LoadParams m_params;
    bool m_bIsSaveNeed = true;
};

class METATYPE_EXPORT CmdLoadClear : public AbstractCmd
{
public:
    CmdLoadClear()
    {
    }

    quint16 m_loadId = 0;
};

class METATYPE_EXPORT CmdLoadRefresh : public AbstractCmd
{
public:
    CmdLoadRefresh()
    {
    }

    quint16 m_loadId = 0;
};

// 工具
class METATYPE_EXPORT CmdToolSave : public AbstractCmd
{
public:
    CmdToolSave()
    {
    }

    int m_toolId = 0;
    ToolParams m_params;
    bool m_bSaveNeed = false;
};

class METATYPE_EXPORT CmdToolCalibrate : public AbstractCmd
{
public:
    CmdToolCalibrate()
    {
    }

    QString m_sCalibrateName;
    CalibratePoints m_calpts;
};

class METATYPE_EXPORT CmdToolSaveCalibratePoints : public AbstractCmd
{
public:
    CmdToolSaveCalibratePoints()
    {
    }

    int m_toolId = 0;
    CalibratePoints m_calpts;
};

class METATYPE_EXPORT CmdToolMoveToPoint : public AbstractCmd
{
public:
    CmdToolMoveToPoint()
    {
    }

    Robot_ToolCalibrateType m_calibrateType = Robot_ToolCalibrateType_Hold_3TCP;
    Pos m_pos;
    Ori m_ori;
    Robot_MoveType m_moveType = Robot_MoveType_MovJ;
};

// 工件
class METATYPE_EXPORT CmdWObjSave : public AbstractCmd
{
public:
    CmdWObjSave()
    {
    }

    int m_wobjId = 0;
    WobjParams m_params;
};

class METATYPE_EXPORT CmdWObjCalibrate : public AbstractCmd
{
public:
    CmdWObjCalibrate()
    {
    }

    int m_wobjId = 0;
    Robot_WObjType m_wobjType = Robot_WObjType_EXTERN_WOBJ;
    CalibratePoints m_midUFramePos;
    CalibratePoints m_midOFramePos;
    Pos m_oldUFramePos;
    Ori m_oldUFrameOri;
};

class METATYPE_EXPORT CmdWObjSaveCalibratePoints : public AbstractCmd
{
public:
    CmdWObjSaveCalibratePoints()
    {
    }

    int m_wobjId = 0;
    CalibratePoints m_uFramePoint;
    CalibratePoints m_oFramePoint;
};

class METATYPE_EXPORT CmdWObjMoveToPoint : public AbstractCmd
{
public:
    CmdWObjMoveToPoint()
    {
    }

    Robot_WObjType m_method = Robot_WObjType_EXTERN_WOBJ;
    Pos m_pos;
    Ori m_ori;
    int armPara[4];
    Robot_MoveType m_moveType = Robot_MoveType_MovJ;
};

class METATYPE_EXPORT CmdAxisMove : public AbstractCmd
{
public:
    CmdAxisMove()
    {
    }

    int m_axisId = 0;
    bool m_isPositive = false;
    bool m_isPressd = false;
};

class METATYPE_EXPORT CmdPutFilesToController : public AbstractCmd
{
public:
    CmdPutFilesToController()
    {
    }

    QString m_projectName;
    QStringList m_srcFileList;
    QStringList m_destFileList;
    bool m_isProject = false;
};

class METATYPE_EXPORT CmdRemoveFilesFromController : public AbstractCmd
{
public:
    CmdRemoveFilesFromController()
    {
    }

    QString m_projectName;
    QStringList m_fileNameList;
};

class METATYPE_EXPORT CmdCommonValue : public AbstractCmd
{
public:
    CmdCommonValue()
    {
    }

    QVariant m_value;
};

class METATYPE_EXPORT CmdKineInverseSolution : public AbstractCmd
{
public:
    CmdKineInverseSolution()
    {
    }

    short toolId  = 0;
    short wobjId = 0;
    short loadId = 0;
    double pos[6] = {};
    int armArgs[4] = {};
};

class METATYPE_EXPORT CmdCommonToolCalibrate : public AbstractCmd
{
public:
    CmdCommonToolCalibrate()
    {
    }

    QVariant m_value;
};

class METATYPE_EXPORT CmdCommonWObjCalibrate : public AbstractCmd
{
public:
    CmdCommonWObjCalibrate()
    {
    }

    QVariant m_value;
};

class METATYPE_EXPORT CmdSetCtrlAuthority : public AbstractCmd
{
public:
    CmdSetCtrlAuthority()
    {
    }

    InoCtrlAuthority m_ctrlAuthority = InoCtrlAuthority_Unknown;
};

class METATYPE_EXPORT CmdUserLogin : public AbstractCmd
{
public:
    CmdUserLogin()
    {
    }

    InoUserMode m_userMode = InoUserMode_Unknown;
    QString m_sPasswd;
};

class METATYPE_EXPORT CmdSetGlobalVarData : public AbstractCmd
{
public:
    CmdSetGlobalVarData()
    {
    }
    int row = 0;
    QVector<QVariant> data;
};

class METATYPE_EXPORT CmdGetGlobalVarData : public AbstractCmd
{
public:
    CmdGetGlobalVarData()
    {
    }
    int currentRow = 0;
};

class METATYPE_EXPORT CmdGetParam : public AbstractCmd
{
public:
    CmdGetParam()
    {
    }

    int targetNode = 0;
};

class METATYPE_EXPORT CmdReleaseBrake : public AbstractCmd
{
public:
    CmdReleaseBrake()
    {
    }

    int m_axisNo = 0;
};
