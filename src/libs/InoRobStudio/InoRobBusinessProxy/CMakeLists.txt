cmake_minimum_required(VERSION 3.5)

#预编译代码
set(PCH_H pch.h)
set(PCH_C pch.cpp)

# 所有平台共用的源代码
set(InoRobotBussinessProxy_Public_Src
	pch.h pch.cpp
	FactoryV1.h FactoryV1.cpp
	Include/InoRobBusinessProxy.h Include/ICommonData.h
	V1/GlobalDataTypes_V1.h V1/GlobalDataTypes_V1.cpp
	V1/Interpretate_V1.h V1/Interpretate_V1.cpp
	V1/CommonDataConvert.h V1/CommonDataConvert.cpp
	V1/DataService/DataSrvGlobal_V1.h V1/DataService/DataSrvGlobal_V1.cpp
	V1/DataService/Protocol_V1.h V1/DataService/Protocol_V1.cpp
	V1/DataService/DataSrvBase_V1.h V1/DataService/DataSrvBase_V1.cpp
	V1/InoRobUtil/CommonEnum_V1.h V1/InoRobUtil/CommonEnum_V1.cpp
	V1/InoRobUtil/FTP/FtpDefault_V1.h V1/InoRobUtil/FTP/FtpDefault_V1.cpp
	V1/InoRobLog/Log_V1.h V1/InoRobLog/Log_V1.cpp
	V1/InoRobLog/PrintInfo_V1.h V1/InoRobLog/PrintInfo_V1.cpp
    V1/Workstation/Workstation_V1.h V1/Workstation/Workstation_V1.cpp
	V1/Project/Project_V1.h V1/Project/Project_V1.cpp
	V1/Project/ProjectHelper_V1.h V1/Project/ProjectHelper_V1.cpp
	V1/Project/DefineWarning/DefineWarning_V1.h V1/Project/DefineWarning/DefineWarning_V1.cpp
	V1/Project/Label/Label_V1.h V1/Project/Label/Label_V1.cpp
	V1/Project/Point/JPoint_V1.h V1/Project/Point/JPoint_V1.cpp
	V1/Project/Point/RPoint_V1.h V1/Project/Point/RPoint_V1.cpp
	V1/Project/Program/Program_V1.h V1/Project/Program/Program_V1.cpp
	V1/User/User_V1.h V1/User/User_V1.cpp
	V1/RobotParam/RobotParam_V1.h V1/RobotParam/RobotParam_V1.cpp
	V1/RobotParam/GeneralMatch/GeneralMatch_V1.h V1/RobotParam/GeneralMatch/GeneralMatch_V1.cpp
	V1/RobotParam/RobotParamRange/RobotParamRange_V1.h V1/RobotParam/RobotParamRange/RobotParamRange_V1.cpp
	V1/Controller/Controller_V1.h V1/Controller/Controller_V1.cpp
	V1/Controller/Connection/Connection_V1.h V1/Controller/Connection/Connection_V1.cpp
	V1/Controller/Calibrate/Calibrate_V1.h V1/Controller/Calibrate/Calibrate_V1.cpp
	V1/Controller/Control/Control_V1.h V1/Controller/Control/Control_V1.cpp
	V1/Controller/ControlAuthority/ControlAuthority_V1.h V1/Controller/ControlAuthority/ControlAuthority_V1.cpp
	V1/Controller/DataSubscribe/DataSubscribeTypes_V1.h V1/Controller/DataSubscribe/DataSubscribeTypes_V1.cpp
	V1/Controller/Debuger/Debuger_V1.h V1/Controller/Debuger/Debuger_V1.cpp
	V1/Controller/Fieldbus/Fieldbus_V1.h V1/Controller/Fieldbus/Fieldbus_V1.cpp V1/Controller/Fieldbus/FieldbusTypes_V1.h V1/Controller/Fieldbus/FieldbusTypes_V1.cpp
	V1/Controller/Fieldbus/IOMap/IOMap_V1.h V1/Controller/Fieldbus/IOMap/IOMap_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/Modbus_V1.h V1/Controller/Fieldbus/FieldBusSwitch/Modbus_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/CANopen_V1.h V1/Controller/Fieldbus/FieldBusSwitch/CANopen_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/EtherCAT_V1.h V1/Controller/Fieldbus/FieldBusSwitch/EtherCAT_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/EthernetIP_V1.h V1/Controller/Fieldbus/FieldBusSwitch/EthernetIP_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/MC_V1.h V1/Controller/Fieldbus/FieldBusSwitch/MC_V1.cpp
	V1/Controller/Fieldbus/FieldBusSwitch/Profinet_V1.h V1/Controller/Fieldbus/FieldBusSwitch/Profinet_V1.cpp
	V1/Controller/FunctionSafe/SafeParaSettingMgr_V1.h V1/Controller/FunctionSafe/SafeParaSettingMgr_V1.cpp
	V1/Controller/Load/Load_V1.h V1/Controller/Load/Load_V1.cpp
	V1/Controller/LoadIdentify/LoadIdentify_V1.h V1/Controller/LoadIdentify/LoadIdentify_V1.cpp
	V1/Controller/Maintenance/Maintenance_V1.h V1/Controller/Maintenance/Maintenance_V1.cpp
	V1/Controller/MechUnit/MechUnit_V1.h V1/Controller/MechUnit/MechUnit_V1.cpp
	V1/Controller/MechUnit/MechUnitManage_V1.h V1/Controller/MechUnit/MechUnitManage_V1.cpp
	V1/Controller/Monitor/Monitor_V1.h V1/Controller/Monitor/Monitor_V1.cpp
	V1/Controller/Monitor/WarnInfo_V1.h V1/Controller/Monitor/WarnInfo_V1.cpp
	V1/Controller/Motion/Motion_V1.h V1/Controller/Motion/Motion_V1.cpp
	V1/Controller/Motion/SafeIOAction/SafeIOAction_V1.h V1/Controller/Motion/SafeIOAction/SafeIOAction_V1.cpp
	V1/Controller/Peripheral/Peripheral_V1.h V1/Controller/Peripheral/Peripheral_V1.cpp
	V1/Controller/Peripheral/IndexConfig/IndexConfig_V1.h V1/Controller/Peripheral/IndexConfig/IndexConfig_V1.cpp
	V1/Controller/Peripheral/IndexConfig/ProjectIndexConfig_V1.h V1/Controller/Peripheral/IndexConfig/ProjectIndexConfig_V1.cpp
	V1/Controller/Peripheral/IndexConfig/RPFileIndexConfig_V1.h V1/Controller/Peripheral/IndexConfig/RPFileIndexConfig_V1.cpp
	V1/Controller/Peripheral/IRLink/IRLink_V1.h V1/Controller/Peripheral/IRLink/IRLink_V1.cpp
	V1/Controller/Position/Position_V1.h V1/Controller/Position/Position_V1.cpp
	V1/Controller/RCConfig/RCConfig_V1.h V1/Controller/RCConfig/RCConfig_V1.cpp
	V1/Controller/RCConfig/SelfLearningVibrationSuppression/SelfLearningVibrationSuppression_V1.h V1/Controller/RCConfig/SelfLearningVibrationSuppression/SelfLearningVibrationSuppression_V1.cpp
	V1/Controller/RCScheduler/RCScheduler_V1.h V1/Controller/RCScheduler/RCScheduler_V1.cpp
	V1/Controller/Resource/Resource_V1.h V1/Controller/Resource/Resource_V1.cpp
	V1/Controller/Resource/GlobalVar/VarMonitor_V1.h V1/Controller/Resource/GlobalVar/VarMonitor_V1.cpp
	V1/Controller/RobotArm/RobotArm_V1.h V1/Controller/RobotArm/RobotArm_V1.cpp
	V1/Controller/RobotArm/CrashDetection/CrashDetection_V1.h V1/Controller/RobotArm/CrashDetection/CrashDetection_V1.cpp
	V1/Controller/RobotArm/InstallParameter/InstallParam_V1.h V1/Controller/RobotArm/InstallParameter/InstallParam_V1.cpp
	V1/Controller/RobotArm/InterferenceArea/InterferenceArea_V1.h V1/Controller/RobotArm/InterferenceArea/InterferenceArea_V1.cpp
	V1/Controller/RobotArm/ZeroPoint/ZeroPoint_V1.h V1/Controller/RobotArm/ZeroPoint/ZeroPoint_V1.cpp
	V1/Controller/RobotControllerEvents/RobotControllerEvents_V1.h V1/Controller/RobotControllerEvents/RobotControllerEvents_V1.cpp
	V1/Controller/ScriptExtension/ScriptExtension_V1.h V1/Controller/ScriptExtension/ScriptExtension_V1.cpp
	V1/Controller/StatusChecks/StatusChecks_V1.h V1/Controller/StatusChecks/StatusChecks_V1.cpp
	V1/Controller/Task/Task_V1.h V1/Controller/Task/Task_V1.cpp
	V1/Controller/Tool/Tool_V1.h V1/Controller/Tool/Tool_V1.cpp
	V1/Controller/TrajectoryRecovery/TrajectoryRecovery_V1.h V1/Controller/TrajectoryRecovery/TrajectoryRecovery_V1.cpp
	V1/Controller/Transfor/Interpreter_V1.h V1/Controller/Transfor/Interpreter_V1.cpp
	V1/Controller/Transfor/Transfor_V1.h V1/Controller/Transfor/Transfor_V1.cpp
	V1/Controller/Wobj/Wobj_V1.h V1/Controller/Wobj/Wobj_V1.cpp
	
)

# 在VS中按目录层级组织源代码
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	file(GLOB_RECURSE SOURCE_FILES "*.h")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobBusinessProxy" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
	
	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobBusinessProxy" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
endif()

# 工业 示教器2.0配置
if(  Platform_Industy_TP_2_0_Msvc_Win
  OR Platform_Industy_TP_2_0_Linux_Arm_Gcc
  OR Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
    include(cmake/Industry_TP_2_0.cmake)
# 协作示教器配置
#elseif(  Platform_Cobot_TP_MinGW_Win
#      OR Platform_Cobot_TP_Android_Arm_V7a
#      OR Platform_Cobot_TP_Android_Arm_64_V8a
#      OR Platform_Cobot_TP_Android_X86
#     OR Platform_Cobot_TP_Android_X86_64)
#    include(cmake/Cobot_TP.cmake)
endif()
