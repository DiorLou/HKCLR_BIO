cmake_minimum_required(VERSION 3.5)

#预编译代码
set(PCH_H pch.h)
set(PCH_C pch.cpp)

# 所有平台共用的源代码
set(InoRobotBussiness_Public_Src

    Controller/Calibrate/CalibrateDefault.cpp
    Controller/Calibrate/CalibrateDefault.h Controller/Calibrate/ICalibrate.h
    Controller/Connection/ConnectionDefault.cpp Controller/Connection/ConnectionDefault.h
    Controller/Connection/IConnection.h Controller/Control/ControlDefault.cpp
    Controller/Control/ControlDefault.h Controller/Control/IControl.h
    Controller/ControlAuthority/ControlAuthorityDefault.cpp Controller/ControlAuthority/ControlAuthorityDefault.h
    Controller/ControlAuthority/IControlAuthority.h Controller/ControllerDefault.cpp
    Controller/ControllerDefault.h Controller/DataSubscribe/DataSubscribeDefault.cpp
    Controller/DataSubscribe/DataSubscribeDefault.h Controller/DataSubscribe/DataSubscribeTypes.h
    Controller/DataSubscribe/IDataSubscribe.h Controller/DataSubscribe/IDataSubscriber.h
    Controller/Debuger/DebugerDefault.cpp Controller/Debuger/DebugerDefault.h
    Controller/Debuger/IDebuger.h
    Controller/Debuger/CmdMessageBox/ICmdMessageBox.h
    Controller/Debuger/CmdMessageBox/CmdMessageBox.h Controller/Debuger/CmdMessageBox/CmdMessageBox.cpp
    Controller/Fieldbus/FieldBusSwitch/CANopenDefault.cpp
    Controller/Fieldbus/FieldBusSwitch/CANopenDefault.h Controller/Fieldbus/FieldBusSwitch/EtherCATDefault.cpp
    Controller/Fieldbus/FieldBusSwitch/EtherCATDefault.h Controller/Fieldbus/FieldBusSwitch/EthernetIPDefault.cpp
    Controller/Fieldbus/FieldBusSwitch/EthernetIPDefault.h Controller/Fieldbus/FieldBusSwitch/ICANopenSwitch.h
    Controller/Fieldbus/FieldBusSwitch/IEtherCATSwitch.h Controller/Fieldbus/FieldBusSwitch/IEthernetIPSwitch.h
    Controller/Fieldbus/FieldBusSwitch/IMCSwitch.h Controller/Fieldbus/FieldBusSwitch/IModbusSwitch.h
    Controller/Fieldbus/FieldBusSwitch/IProfinetSwitch.h Controller/Fieldbus/FieldBusSwitch/MCDefault.cpp
    Controller/Fieldbus/FieldBusSwitch/MCDefault.h Controller/Fieldbus/FieldBusSwitch/ModbusDefaut.cpp
    Controller/Fieldbus/FieldBusSwitch/ModbusDefaut.h Controller/Fieldbus/FieldBusSwitch/ProfinetDefault.cpp
    Controller/Fieldbus/FieldBusSwitch/ProfinetDefault.h Controller/Fieldbus/FieldbusDefault.cpp
    Controller/Fieldbus/FieldbusDefault.h Controller/Fieldbus/FieldbusTypes.h
    Controller/Fieldbus/IFieldbus.h Controller/Fieldbus/IOMap/IIOMap.h
    Controller/Fieldbus/IOMap/IOMapDefault.cpp Controller/Fieldbus/IOMap/IOMapDefault.h
    Controller/IController.h Controller/Load/ILoad.h
    Controller/Load/LoadDefault.cpp Controller/Load/LoadDefault.h
    Controller/LoadIdentify/ILoadIdentify.h Controller/LoadIdentify/LoadIdentifyDefault.cpp
    Controller/LoadIdentify/LoadIdentifyDefault.h Controller/Maintenance/IMaintenance.h
    Controller/Maintenance/MaintenanceDefault.cpp Controller/Maintenance/MaintenanceDefault.h
    Controller/Maintenance/RemainLifeCalculate/IRemainLifeCalculate.h
    Controller/Maintenance/RemainLifeCalculate/RemainLifeCalculateDefault.h
    Controller/Maintenance/RemainLifeCalculate/RemainLifeCalculateDefault.cpp
    Controller/MechUnit/IMechUnit.h Controller/MechUnit/IMechUnitManage.h
    Controller/MechUnit/MechUnitDefault.cpp Controller/MechUnit/MechUnitDefault.h
    Controller/MechUnit/MechUnitManageDefault.cpp Controller/MechUnit/MechUnitManageDefault.h
    Controller/Monitor/IMonitor.h Controller/Monitor/IWarnInfo.h
    Controller/Monitor/MonitorDefault.cpp Controller/Monitor/MonitorDefault.h
    Controller/Monitor/WarnInfoDefault.cpp Controller/Monitor/WarnInfoDefault.h
    Controller/Motion/SafeIOAction/ISafeIOAction.h
    Controller/Motion/SafeIOAction/SafeIOActionDefault.h Controller/Motion/SafeIOAction/SafeIOActionDefault.cpp
    Controller/Motion/IMotion.h Controller/Motion/MotionDefault.cpp
    Controller/Motion/MotionDefault.h Controller/Peripheral/IPeripheral.h
    Controller/Peripheral/IRLink/IIRLink.h Controller/Peripheral/IRLink/IRLinkDefault.cpp
    Controller/Peripheral/IRLink/IRLinkDefault.h Controller/Peripheral/IndexConfig/IIndexConfig.h
    Controller/Peripheral/IndexConfig/IndexConfigDefault.cpp Controller/Peripheral/IndexConfig/IndexConfigDefault.h
    Controller/Peripheral/IndexConfig/ProjectIndexConfig.cpp Controller/Peripheral/IndexConfig/ProjectIndexConfig.h
    Controller/Peripheral/IndexConfig/RPFileIndexConfig.cpp Controller/Peripheral/IndexConfig/RPFileIndexConfig.h
    Controller/Peripheral/PeripheralDefault.cpp Controller/Peripheral/PeripheralDefault.h
    Controller/Position/IPosition.h Controller/Position/PositionDefault.cpp
    Controller/Position/PositionDefault.h Controller/PubSub/ISubscriber.h
    Controller/PubSub/IrSub.cpp Controller/PubSub/IrSub.h
    Controller/PubSub/SubscriberDefault.cpp Controller/PubSub/SubscriberDefault.h
    Controller/RCConfig/IRCConfig.h Controller/RCConfig/RCConfigDefault.cpp
    Controller/RCConfig/RCConfigDefault.h Controller/RCConfig/SelfLearningVibrationSuppression/ISelfLearningVibrationSuppression.h
    Controller/RCConfig/SelfLearningVibrationSuppression/SelfLearningVibrationSuppression.cpp Controller/RCConfig/SelfLearningVibrationSuppression/SelfLearningVibrationSuppression.h
    Controller/RCScheduler/IRCScheduler.h Controller/RCScheduler/IRCSchedulerUser.h
    Controller/RCScheduler/RCSchedulerDefault.cpp Controller/RCScheduler/RCSchedulerDefault.h
    Controller/Resource/GlobalVar/IVarMonitor.h Controller/Resource/GlobalVar/VarMonitorDefault.cpp
    Controller/Resource/GlobalVar/VarMonitorDefault.h Controller/Resource/IResource.h
    Controller/Resource/IO/SysIOCfgFile.h Controller/Resource/IO/SysIOCfgFile.cpp
    Controller/Resource/ResourceDefault.cpp Controller/Resource/ResourceDefault.h
    Controller/RobotArm/CrashDetection/CrashDetectionDefault.cpp Controller/RobotArm/CrashDetection/CrashDetectionDefault.h
    Controller/RobotArm/CrashDetection/ICrashDetection.h Controller/RobotArm/IRobotArm.h
    Controller/RobotArm/InstallParameter/IInstallParameter.h Controller/RobotArm/InstallParameter/InstallParamDefault.cpp
    Controller/RobotArm/InstallParameter/InstallParamDefault.h Controller/RobotArm/InterferenceArea/IInterferenceArea.h
    Controller/RobotArm/InterferenceArea/InterferenceAreaDefault.cpp Controller/RobotArm/InterferenceArea/InterferenceAreaDefault.h
    Controller/RobotArm/ZeroPoint/IZeroPoint.h Controller/RobotArm/ZeroPoint/ZeroPointDefault.h Controller/RobotArm/ZeroPoint/ZeroPointDefault.cpp
    Controller/RobotArm/ZeroPointRepair/IZeroPointRepair.h Controller/RobotArm/ZeroPointRepair/ZeroPointRepair.h Controller/RobotArm/ZeroPointRepair/ZeroPointRepair.cpp
    Controller/RobotArm/RobotArmDefault.cpp Controller/RobotArm/RobotArmDefault.h
    Controller/RobotControllerEvents/IRobotControllerEvents.h Controller/RobotControllerEvents/RobotControllerEvents.cpp
    Controller/RobotControllerEvents/RobotControllerEvents.h Controller/ScriptExtension/IScriptExtension.h
    Controller/ScriptExtension/ScriptExtensionDefault.cpp Controller/ScriptExtension/ScriptExtensionDefault.h
    Controller/FunctionSafe/ISafeParaSettingMgr.h Controller/FunctionSafe/SafeParaSettingMgrDefault.h Controller/FunctionSafe/SafeParaSettingMgrDefault.cpp
    Controller/StatusChecks/StatusChecks.cpp Controller/StatusChecks/StatusChecks.h
    Controller/Task/ITask.h Controller/Task/TaskDefault.cpp
    Controller/Task/TaskDefault.h Controller/Tool/ITool.h
    Controller/Tool/ToolDefault.cpp Controller/Tool/ToolDefault.h
    Controller/Transfor/ITransfor.h Controller/Transfor/Interpreter.cpp
    Controller/Transfor/Interpreter.h Controller/Transfor/TransforDefault.cpp
    Controller/Transfor/TransforDefault.h Controller/Wobj/IWobj.h
    Controller/Wobj/WobjDefault.cpp Controller/Wobj/WobjDefault.h
    Controller/TrajectoryRecovery/ITrajectoryRecovery.h Controller/TrajectoryRecovery/TrajectoryRecoveryDefault.h Controller/TrajectoryRecovery/TrajectoryRecoveryDefault.cpp
    Controller/Language/ILanguage.h Controller/Language/LanguageDefault.h Controller/Language/LanguageDefault.cpp
    Controller/Language/LanguageService.h Controller/Language/LanguageService.cpp
    Controller/ForceCtrl/IForceCtrl.h Controller/ForceCtrl/ForceCtrlDefault.h Controller/ForceCtrl/ForceCtrlDefault.cpp
    Controller/FrictionCompensation/IFrictionCompensation.h Controller/FrictionCompensation/FrictionCompensationDefault.h Controller/FrictionCompensation/FrictionCompensationDefault.cpp
    Controller/BacklashCompensation/IBacklashCompensation.h Controller/BacklashCompensation/BacklashCompensationDefault.h Controller/BacklashCompensation/BacklashCompensationDefault.cpp

    Include/EventTypes.h Include/GlobalDataTypes.h
    Include/IInoRobBusiness.h Include/InoRobBusiness.h
    Include/ParaData.h Include/UParaData.h Include/comwithTp.h
    Project/DefineWarning/DefineWarningDefault.cpp Project/DefineWarning/DefineWarningDefault.h
    Project/DefineWarning/IDefineWarning.h Project/IProject.h
    Project/Label/ILabel.h Project/Label/LabelDefault.cpp
    Project/Label/LabelDefault.h Project/Point/IJPoint.h
    Project/Point/IRPoint.h Project/Point/JPoint.cpp
    Project/Point/JPoint.h Project/Point/RPoint.cpp
    Project/Point/RPoint.h Project/Program/IProgram.h
    Project/Program/Program.cpp Project/Program/Program.h
    Project/Project.cpp Project/Project.h
    Project/ProjectHelper.cpp Project/ProjectHelper.h
    Project/Station/IStationConfig.h Project/Station/StationConfig.cpp
    Project/Station/StationConfig.h
    RobotParam/GeneralMatch/GeneralMatchDefault.cpp RobotParam/GeneralMatch/GeneralMatchDefault.h
    RobotParam/GeneralMatch/IGeneralMatch.h RobotParam/IRobotParam.h
    RobotParam/RobotParamDefault.cpp RobotParam/RobotParamDefault.h
    RobotParam/RobotParamRange/IRobotParamRange.h RobotParam/RobotParamRange/RobotParamRange.cpp
    RobotParam/RobotParamRange/RobotParamRange.h User/IUser.h
    User/User.cpp User/User.h
    FactoryDefault.cpp FactoryDefault.h
    VirtualControllerDeviceManager.h  VirtualControllerDeviceManager.cpp
    Workstation/IWorkstation.h Workstation/WorkstationDefault.cpp
    Workstation/WorkstationDefault.h
)

set(InoRobotBussiness_InoRobotTp_PluginService_Src
    Controller/Plugin/PluginConfigModel.h
    Controller/Plugin/IInoRobPlugin.h
    Controller/Plugin/pluginmasterservice.h
    Controller/Plugin/pluginmasterservice.cpp
    Controller/Plugin/IInoRobPluginMasterService.h)
	
# 为Windows增加Grpc相关源代码
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(NOT Platform_Cobot_TP_Msvc_Win)
	message("APPEND InoRobotBussiness_Public_Src")
	list(APPEND InoRobotBussiness_Public_Src

	    GrpcService/IGrpcService.h GrpcService/GrpcService.h GrpcService/GrpcService.cpp
	    GrpcService/GlobalDataTypesGrpc.pb.h GrpcService/GlobalDataTypesGrpc.pb.cc GrpcService/GlobalDataTypesGrpc.grpc.pb.h GrpcService/GlobalDataTypesGrpc.grpc.pb.cc GrpcService/GlobalDataTypesService.h GrpcService/GlobalDataTypesService.cpp
	    GrpcService/TechnologyGrpc.grpc.pb.cc GrpcService/TechnologyGrpc.grpc.pb.h GrpcService/TechnologyGrpc.pb.cc GrpcService/TechnologyGrpc.pb.h
	    GrpcService/TechnologyService.cpp GrpcService/TechnologyService.h
	    User/UserService.h User/UserService.cpp User/UserGrpc.pb.h User/UserGrpc.pb.cc User/UserGrpc.grpc.pb.h User/UserGrpc.grpc.pb.cc
	    Workstation/WorkstationGrpc.pb.h Workstation/WorkstationGrpc.pb.cc Workstation/WorkstationGrpc.grpc.pb.h Workstation/WorkstationGrpc.grpc.pb.cc Workstation/WorkstationService.h Workstation/WorkstationService.cpp
	    Project/ProjectService.h Project/ProjectService.cpp Project/ProjectGrpc.pb.h Project/ProjectGrpc.pb.cc Project/ProjectGrpc.grpc.pb.h Project/ProjectGrpc.grpc.pb.cc
	    Controller/Connection/ConnectionService.h Controller/Connection/ConnectionService.cpp Controller/Connection/ConnectionGrpc.pb.h Controller/Connection/ConnectionGrpc.pb.cc Controller/Connection/ConnectionGrpc.grpc.pb.h Controller/Connection/ConnectionGrpc.grpc.pb.cc
	    Controller/Motion/MotionService.h Controller/Motion/MotionService.cpp Controller/Motion/MotionGrpc.pb.h Controller/Motion/MotionGrpc.pb.cc Controller/Motion/MotionGrpc.grpc.pb.h Controller/Motion/MotionGrpc.grpc.pb.cc
	    Controller/Monitor/MonitorService.h Controller/Monitor/MonitorService.cpp Controller/Monitor/MonitorGrpc.pb.h Controller/Monitor/MonitorGrpc.pb.cc Controller/Monitor/MonitorGrpc.grpc.pb.h Controller/Monitor/MonitorGrpc.grpc.pb.cc
	    Controller/Control/ControlService.h Controller/Control/ControlService.cpp Controller/Control/ControlGrpc.pb.h Controller/Control/ControlGrpc.pb.cc Controller/Control/ControlGrpc.grpc.pb.h Controller/Control/ControlGrpc.grpc.pb.cc
	    Controller/ControlAuthority/ControlAuthorityService.h Controller/ControlAuthority/ControlAuthorityService.cpp Controller/ControlAuthority/ControlAuthorityGrpc.pb.h Controller/ControlAuthority/ControlAuthorityGrpc.pb.cc Controller/ControlAuthority/ControlAuthorityGrpc.grpc.pb.h Controller/ControlAuthority/ControlAuthorityGrpc.grpc.pb.cc
	    Controller/Tool/ToolService.h Controller/Tool/ToolService.cpp Controller/Tool/ToolGrpc.pb.h Controller/Tool/ToolGrpc.pb.cc Controller/Tool/ToolGrpc.grpc.pb.h Controller/Tool/ToolGrpc.grpc.pb.cc
	    Controller/Wobj/WobjService.h Controller/Wobj/WobjService.cpp Controller/Wobj/WobjGrpc.pb.h Controller/Wobj/WobjGrpc.pb.cc Controller/Wobj/WobjGrpc.grpc.pb.h Controller/Wobj/WobjGrpc.grpc.pb.cc
	    Controller/Load/LoadService.h Controller/Load/LoadService.cpp Controller/Load/LoadGrpc.pb.h Controller/Load/LoadGrpc.pb.cc Controller/Load/LoadGrpc.grpc.pb.h Controller/Load/LoadGrpc.grpc.pb.cc
	    Controller/Position/PositionService.h Controller/Position/PositionService.cpp Controller/Position/PositionGrpc.pb.h Controller/Position/PositionGrpc.pb.cc Controller/Position/PositionGrpc.grpc.pb.h Controller/Position/PositionGrpc.grpc.pb.cc
	    Controller/MechUnit/MechUnitService.h Controller/MechUnit/MechUnitService.cpp Controller/MechUnit/MechUnitGrpc.pb.h Controller/MechUnit/MechUnitGrpc.pb.cc Controller/MechUnit/MechUnitGrpc.grpc.pb.h Controller/MechUnit/MechUnitGrpc.grpc.pb.cc
	    Controller/Transfor/TransforService.h Controller/Transfor/TransforService.cpp Controller/Transfor/TransforGrpc.pb.h Controller/Transfor/TransforGrpc.pb.cc Controller/Transfor/TransforGrpc.grpc.pb.h Controller/Transfor/TransforGrpc.grpc.pb.cc
	    Controller/Debuger/DebugerService.h Controller/Debuger/DebugerService.cpp Controller/Debuger/DebugerGrpc.pb.h Controller/Debuger/DebugerGrpc.pb.cc Controller/Debuger/DebugerGrpc.grpc.pb.h Controller/Debuger/DebugerGrpc.grpc.pb.cc
	    Controller/FunctionSafe/SafeParaSettingMgrService.h Controller/FunctionSafe/SafeParaSettingMgrService.cpp Controller/FunctionSafe/SafeParaSettingMgr.pb.h Controller/FunctionSafe/SafeParaSettingMgr.pb.cc Controller/FunctionSafe/SafeParaSettingMgr.grpc.pb.h Controller/FunctionSafe/SafeParaSettingMgr.grpc.pb.cc
	    Controller/Task/TaskService.h Controller/Task/TaskService.cpp Controller/Task/TaskGrpc.pb.h Controller/Task/TaskGrpc.pb.cc Controller/Task/TaskGrpc.grpc.pb.h Controller/Task/TaskGrpc.grpc.pb.cc
	    Controller/Resource/ResourceService.h Controller/Resource/ResourceService.cpp Controller/Resource/ResourceGrpc.pb.h Controller/Resource/ResourceGrpc.pb.cc Controller/Resource/ResourceGrpc.grpc.pb.h Controller/Resource/ResourceGrpc.grpc.pb.cc
	    Controller/RCConfig/RCConfigService.h Controller/RCConfig/RCConfigService.cpp Controller/RCConfig/RCConfigGrpc.pb.h Controller/RCConfig/RCConfigGrpc.pb.cc Controller/RCConfig/RCConfigGrpc.grpc.pb.h Controller/RCConfig/RCConfigGrpc.grpc.pb.cc
	    Controller/RobotArm/RobotArmService.h Controller/RobotArm/RobotArmService.cpp Controller/RobotArm/RobotArmGrpc.pb.h Controller/RobotArm/RobotArmGrpc.pb.cc Controller/RobotArm/RobotArmGrpc.grpc.pb.h Controller/RobotArm/RobotArmGrpc.grpc.pb.cc
	    Controller/Fieldbus/FieldbusService.h Controller/Fieldbus/FieldbusService.cpp Controller/Fieldbus/FieldBusGrpc.pb.h Controller/Fieldbus/FieldBusGrpc.pb.cc Controller/Fieldbus/FieldBusGrpc.grpc.pb.h Controller/Fieldbus/FieldBusGrpc.grpc.pb.cc
	    Controller/Maintenance/MaintenanceService.h Controller/Maintenance/MaintenanceService.cpp Controller/Maintenance/MaintenanceGrpc.pb.h Controller/Maintenance/MaintenanceGrpc.pb.cc Controller/Maintenance/MaintenanceGrpc.grpc.pb.h Controller/Maintenance/MaintenanceGrpc.grpc.pb.cc
	)
    else()
	message("NOT APPEND InoRobotBussiness_Public_Src")
    endif()
endif()

if(Platform_Industy_TP_2_0_Msvc_Win)
    set(grpc_libs
	debug absl_bad_optional_access_debug.lib
	debug absl_bad_variant_access_debug.lib
	debug absl_base_debug.lib
	debug absl_city_debug.lib
	debug absl_cordz_handle_debug.lib
	debug absl_cordz_info_debug.lib
	debug absl_cord_debug.lib
	debug absl_cord_internal_debug.lib
	debug absl_crc32c_debug.lib
	debug absl_crc_cord_state_debug.lib
	debug absl_crc_internal_debug.lib
	debug absl_examine_stack_debug.lib
	debug absl_flags_commandlineflag_debug.lib
	debug absl_flags_commandlineflag_internal_debug.lib
	debug absl_flags_config_debug.lib
	debug absl_flags_internal_debug.lib
	debug absl_flags_marshalling_debug.lib
	debug absl_flags_private_handle_accessor_debug.lib
	debug absl_flags_program_name_debug.lib
	debug absl_flags_reflection_debug.lib
	debug absl_graphcycles_internal_debug.lib
	debug absl_hash_debug.lib
	debug absl_int128_debug.lib
	debug absl_kernel_timeout_internal_debug.lib
	debug absl_log_globals_debug.lib
	debug absl_log_internal_check_op_debug.lib
	debug absl_log_internal_conditions_debug.lib
	debug absl_log_internal_fnmatch_debug.lib
	debug absl_log_internal_format_debug.lib
	debug absl_log_internal_globals_debug.lib
	debug absl_log_internal_log_sink_set_debug.lib
	debug absl_log_internal_message_debug.lib
	debug absl_log_internal_nullguard_debug.lib
	debug absl_log_internal_proto_debug.lib
	debug absl_log_sink_debug.lib
	debug absl_low_level_hash_debug.lib
	debug absl_malloc_internal_debug.lib
	debug absl_random_internal_platform_debug.lib
	debug absl_random_internal_pool_urbg_debug.lib
	debug absl_random_internal_randen_debug.lib
	debug absl_random_internal_randen_slow_debug.lib
	debug absl_random_internal_seed_material_debug.lib
	debug absl_random_seed_gen_exception_debug.lib
	debug absl_raw_hash_set_debug.lib
	debug absl_raw_logging_internal_debug.lib
	debug absl_spinlock_wait_debug.lib
	debug absl_stacktrace_debug.lib
	debug absl_status_debug.lib
	debug absl_statusor_debug.lib
	debug absl_str_format_internal_debug.lib
	debug absl_strerror_debug.lib
	debug absl_string_view_debug.lib
	debug absl_strings_debug.lib
	debug absl_strings_internal_debug.lib
	debug absl_symbolize_debug.lib
	debug absl_synchronization_debug.lib
	debug absl_throw_delegate_debug.lib
	debug absl_time_debug.lib
	debug absl_time_zone_debug.lib
	debug absl_vlog_config_internal_debug.lib
	debug address_sorting_debug.lib
	debug cares_debug.lib
	debug crypto_debug.lib
	debug gpr_debug.lib
	debug grpc_unsecure_debug.lib
	debug grpc++_reflection_debug.lib
	debug grpc++_unsecure_debug.lib
	debug libprotobuf_debug.lib
	debug upb_mem_lib_debug.lib
	debug upb_message_lib_debug.lib
	debug upb_wire_lib_debug.lib
	debug utf8_validity_debug.lib
	debug zlibstatic_debug.lib
	optimized absl_bad_optional_access.lib
	optimized absl_bad_variant_access.lib
	optimized absl_base.lib
	optimized absl_city.lib
	optimized absl_cord.lib
	optimized absl_cord_internal.lib
	optimized absl_cordz_handle.lib
	optimized absl_cordz_info.lib
	optimized absl_crc_cord_state.lib
	optimized absl_crc_internal.lib
	optimized absl_crc32c.lib
	optimized absl_examine_stack.lib
	optimized absl_flags_commandlineflag.lib
	optimized absl_flags_commandlineflag_internal.lib
	optimized absl_flags_config.lib
	optimized absl_flags_internal.lib
	optimized absl_flags_marshalling.lib
	optimized absl_flags_private_handle_accessor.lib
	optimized absl_flags_program_name.lib
	optimized absl_flags_reflection.lib
	optimized absl_graphcycles_internal.lib
	optimized absl_hash.lib
	optimized absl_int128.lib
	optimized absl_kernel_timeout_internal.lib
	optimized absl_log_globals.lib
	optimized absl_log_internal_check_op.lib
	optimized absl_log_internal_conditions.lib
	optimized absl_log_internal_fnmatch.lib
	optimized absl_log_internal_format.lib
	optimized absl_log_internal_globals.lib
	optimized absl_log_internal_log_sink_set.lib
	optimized absl_log_internal_message.lib
	optimized absl_log_internal_nullguard.lib
	optimized absl_log_internal_proto.lib
	optimized absl_log_sink.lib
	optimized absl_low_level_hash.lib
	optimized absl_malloc_internal.lib
	optimized absl_random_internal_platform.lib
	optimized absl_random_internal_pool_urbg.lib
	optimized absl_random_internal_randen.lib
	optimized absl_random_internal_randen_slow.lib
	optimized absl_random_internal_seed_material.lib
	optimized absl_random_seed_gen_exception.lib
	optimized absl_raw_hash_set.lib
	optimized absl_raw_logging_internal.lib
	optimized absl_spinlock_wait.lib
	optimized absl_stacktrace.lib
	optimized absl_status.lib
	optimized absl_statusor.lib
	optimized absl_strerror.lib
	optimized absl_strings.lib
	optimized absl_strings_internal.lib
	optimized absl_string_view.lib
	optimized absl_str_format_internal.lib
	optimized absl_symbolize.lib
	optimized absl_synchronization.lib
	optimized absl_throw_delegate.lib
	optimized absl_time.lib
	optimized absl_time_zone.lib
	optimized absl_vlog_config_internal.lib
	optimized address_sorting.lib
	optimized cares.lib
	optimized crypto.lib
	optimized gpr.lib
	optimized grpc_unsecure.lib
	optimized grpc++_reflection.lib
	optimized grpc++_unsecure.lib
	optimized libprotobuf.lib
	optimized upb_mem_lib.lib
	optimized upb_message_lib.lib
	optimized upb_wire_lib.lib
	optimized utf8_validity.lib
	optimized zlibstatic.lib
    )
elseif(NOT Platform_Cobot_TP_Msvc_Win)
    set(grpc_libs
	libgrpc_unsecure.a
	libgrpc++_reflection.a
	libgrpc++_unsecure.a
	libgpr.a
	libprotobuf.a
	libabsl_bad_optional_access.a
	libabsl_bad_variant_access.a
	libabsl_base.a
	libabsl_city.a
	libabsl_cord.a
	libabsl_cord_internal.a
	libabsl_cordz_handle.a
	libabsl_cordz_info.a
	libabsl_crc_cord_state.a
	libabsl_crc_internal.a
	libabsl_crc32c.a
	libabsl_examine_stack.a
	libabsl_flags_commandlineflag.a
	libabsl_flags_commandlineflag_internal.a
	libabsl_flags_config.a
	libabsl_flags_internal.a
	libabsl_flags_marshalling.a
	libabsl_flags_private_handle_accessor.a
	libabsl_flags_program_name.a
	libabsl_flags_reflection.a
	libabsl_graphcycles_internal.a
	libabsl_hash.a
	libabsl_int128.a
	libabsl_kernel_timeout_internal.a
	libabsl_log_globals.a
	libabsl_log_internal_check_op.a
	libabsl_log_internal_conditions.a
	libabsl_log_internal_fnmatch.a
	libabsl_log_internal_format.a
	libabsl_log_internal_globals.a
	libabsl_log_internal_log_sink_set.a
	libabsl_log_internal_message.a
	libabsl_log_internal_nullguard.a
	libabsl_log_internal_proto.a
	libabsl_log_sink.a
	libabsl_low_level_hash.a
	libabsl_malloc_internal.a
	libabsl_random_internal_platform.a
	libabsl_random_internal_pool_urbg.a
	libabsl_random_internal_randen.a
	libabsl_random_internal_randen_hwaes.a
	libabsl_random_internal_randen_hwaes_impl.a
	libabsl_random_internal_randen_slow.a
	libabsl_random_internal_seed_material.a
	libabsl_random_seed_gen_exception.a
	libabsl_raw_hash_set.a
	libabsl_raw_logging_internal.a
	libabsl_spinlock_wait.a
	libabsl_stacktrace.a
	libabsl_status.a
	libabsl_statusor.a
	libabsl_strerror.a
	libabsl_strings.a
	libabsl_strings_internal.a
	libabsl_string_view.a
	libabsl_str_format_internal.a
	libabsl_symbolize.a
	libabsl_synchronization.a
	libabsl_throw_delegate.a
	libabsl_time.a
	libabsl_time_zone.a
	libabsl_vlog_config_internal.a
	libaddress_sorting.a
	libcares.a
	libcrypto.a
	libupb_mem_lib.a
	libupb_message_lib.a
	libupb_wire_lib.a
	libutf8_validity.a
	libzlibstatic.a
	dbghelp
	bcrypt
	ws2_32
	pthread
	iphlpapi
    )
endif()

# 在VS中按目录层级组织源代码
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	file(GLOB_RECURSE SOURCE_FILES "*.h")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobBusiness" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
	
	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobBusiness" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
endif()

# 工业 示教器2.0配置
if(  Platform_Industy_TP_2_0_Msvc_Win
  OR Platform_Industy_TP_2_0_Linux_Arm_Gcc
  OR Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
    include(cmake/Industry_TP_2_0.cmake)
# 协作示教器配置
elseif(  Platform_Cobot_TP_MinGW_Win
	OR Platform_Cobot_TP_Msvc_Win
	OR Platform_Cobot_TP_Android_Arm_V7a
	OR Platform_Cobot_TP_Android_Arm_64_V8a
	OR Platform_Cobot_TP_Android_X86
	OR Platform_Cobot_TP_Android_X86_64)
    include(cmake/Cobot_TP.cmake)
endif()
