cmake_minimum_required(VERSION 3.5)

# 分组：ftp
set(Ftp_Cpp_Without_Prefix
    ascii_istream.cpp ascii_ostream.cpp binary_istream.cpp
    binary_ostream.cpp client.cpp control_connection.cpp data_connection.cpp
    file_list_reply.cpp file_size_reply.cpp istream_adapter.cpp net_utils.cpp
    ostream_adapter.cpp replies.cpp reply.cpp utils.cpp
)
set(Ftp_Header_Without_Prefix
    client.hpp detail/ascii_istream.hpp detail/ascii_ostream.hpp
    detail/binary_istream.hpp detail/binary_ostream.hpp
    detail/control_connection.hpp detail/data_connection.hpp
    detail/net_utils.hpp detail/utils.hpp
    file_list_reply.hpp file_size_reply.hpp
    ftp.hpp ftp_exception.hpp ftp_global.hpp observer.hpp
    replies.hpp reply.hpp stream/input_stream.hpp stream/istream_adapter.hpp
    stream/ostream_adapter.hpp stream/output_stream.hpp
    transfer_callback.hpp transfer_mode.hpp transfer_type.hpp
)

foreach(file IN LISTS Ftp_Cpp_Without_Prefix)
    list(APPEND Ftp_Src ${InoRobStudio_Path}/third_party/ftp/${file})
endforeach()

foreach(file IN LISTS Ftp_Header_Without_Prefix)
    list(APPEND Ftp_Src ${InoRobStudio_Path}/third_party/include/ftp/${file})
endforeach()

# 预编译代码
set(PCH_H pch.h)
set(PCH_C pch.cpp)

# 所有平台共用的源代码
set(InoRoUtil_Public_Src

    BusinessFiles/BusinessFileCommon.cpp
    BusinessFiles/BusinessFileCommon.h BusinessFiles/BusinessFiles.h
    BusinessFiles/FieldBusFunIoCfgFile.cpp BusinessFiles/FieldBusFunIoCfgFile.h
    BusinessFiles/LoadUserFile.cpp BusinessFiles/LoadUserFile.h
    BusinessFiles/MechUnitsCalibFile.cpp BusinessFiles/MechUnitsCalibFile.h
    BusinessFiles/MechUnitsConfigFile.cpp BusinessFiles/MechUnitsConfigFile.h
    BusinessFiles/SelfLearningVibrationControlFile.cpp BusinessFiles/SelfLearningVibrationControlFile.h
    BusinessFiles/ToolCalibFile.cpp BusinessFiles/ToolCalibFile.h
    BusinessFiles/WobjCalibFile.cpp BusinessFiles/WobjCalibFile.h
    BusinessFiles/FunctionSafeConfigFile.h BusinessFiles/FunctionSafeConfigFile.cpp
    BusinessFiles/ZeroPointRepairCalibFile.h BusinessFiles/ZeroPointRepairCalibFile.cpp
    BusinessFiles/FCSensorFile.h BusinessFiles/FCSensorFile.cpp
    BusinessFiles/ForceCtrlCalibFile.h BusinessFiles/ForceCtrlCalibFile.cpp
    BusinessFiles/FCCoordinateFile.h BusinessFiles/FCCoordinateFile.cpp
    BusinessFiles/ForceCtrlConfigFile.h BusinessFiles/ForceCtrlConfigFile.cpp
    BusinessFiles/ForceCtrlMoveFile.h BusinessFiles/ForceCtrlMoveFile.cpp
    BusinessFiles/ForceCtrlLimitFile.h BusinessFiles/ForceCtrlLimitFile.cpp
    Crc/Crc.h Crc/Crc16.cpp
    Crc/Crc16.h Crc/Crc32.cpp
    Crc/Crc32.h DateTime/DateTimeTool.cpp
    ACL/acl_base64.h ACL/acl_base64.cpp
    DateTime/DateTimeTool.h FileHelper.cpp
    FTP/FtpDefault.h FTP/FtpDefault.cpp
    FTP/FileCast.h FTP/FileCast.cpp
    Telnet/Telnet.h Telnet/Telnet.cpp
    FileHelper.h Include/CommonEnum.h 
    Include/IFtp.h Include/IInoRobUtil.h
    Include/IUtil.h Include/InoRobUtil.h
    Include/cJsonType.h JsonBase/JsonObjOp.cpp
    JsonBase/JsonObjOp.h JsonBase/cJSON.cpp
    JsonBase/cJSON.h JsonSerializers/DataSubscribe/JsonSerDataSubscribe.cpp
    JsonSerializers/DataSubscribe/JsonSerDataSubscribe.h JsonSerializers/JsonSerJPos.cpp
    JsonSerializers/JsonSerJPos.h JsonSerializers/JsonSerPose.cpp
    JsonSerializers/JsonSerPose.h JsonSerializers/JsonSerRobPos.cpp
    JsonSerializers/JsonSerRobPos.h JsonSerializers/JsonSerializers.h
    JsonSerializers/Load/JsonSerLoadUserData.cpp JsonSerializers/Load/JsonSerLoadUserData.h
    JsonSerializers/Load/JsonSerLoadUserParam.cpp JsonSerializers/Load/JsonSerLoadUserParam.h
    JsonSerializers/FieldBus/JsonSerDeviceNet.h JsonSerializers/FieldBus/JsonSerDeviceNet.cpp
    JsonSerializers/FieldBus/JsonSerDeviceNetSlave.h JsonSerializers/FieldBus/JsonSerDeviceNetSlave.cpp
    JsonSerializers/FieldBus/JsonSerDeviceNetInOut.h JsonSerializers/FieldBus/JsonSerDeviceNetInOut.cpp
    JsonSerializers/FieldBus/JsonSerDeviceNetMaster.h JsonSerializers/FieldBus/JsonSerDeviceNetMaster.cpp
    JsonSerializers/MechUnit/JsonSerExtAxisParam.cpp JsonSerializers/MechUnit/JsonSerExtAxisParam.h
    JsonSerializers/MechUnit/JsonSerExtAxisParamItem.cpp JsonSerializers/MechUnit/JsonSerExtAxisParamItem.h
    JsonSerializers/MechUnit/JsonSerIndAxisParam.cpp JsonSerializers/MechUnit/JsonSerIndAxisParam.h
    JsonSerializers/MechUnit/JsonSerIndAxisParamItem.cpp JsonSerializers/MechUnit/JsonSerIndAxisParamItem.h
    JsonSerializers/MechUnit/JsonSerMechUnit.cpp JsonSerializers/MechUnit/JsonSerMechUnit.h
    JsonSerializers/MechUnit/JsonSerMechUnitsCalibData.cpp JsonSerializers/MechUnit/JsonSerMechUnitsCalibData.h
    JsonSerializers/MechUnit/JsonSerMechUnitsCalibDataItem.cpp JsonSerializers/MechUnit/JsonSerMechUnitsCalibDataItem.h
    JsonSerializers/MechUnit/JsonSerMechUnitsCalibMethodDataItem.cpp JsonSerializers/MechUnit/JsonSerMechUnitsCalibMethodDataItem.h
    JsonSerializers/MechUnit/JsonSerMechUnitsCfgData.cpp JsonSerializers/MechUnit/JsonSerMechUnitsCfgData.h
    JsonSerializers/MechUnit/JsonSerRelativeTransformat.cpp JsonSerializers/MechUnit/JsonSerRelativeTransformat.h
    JsonSerializers/ToolWobj/JsonSerCsCalibPoints.cpp JsonSerializers/ToolWobj/JsonSerCsCalibPoints.h
    JsonSerializers/ToolWobj/JsonSerToolCalibData.cpp JsonSerializers/ToolWobj/JsonSerToolCalibData.h
    JsonSerializers/ToolWobj/JsonSerWobjCalibData.cpp JsonSerializers/ToolWobj/JsonSerWobjCalibData.h
    JsonSerializers/ToolWobj/JsonSerWobjData.cpp JsonSerializers/ToolWobj/JsonSerWobjData.h
    JsonSerializers/JsonSerInterferenceZone.h JsonSerializers/JsonSerInterferenceZone.cpp
    JsonSerializers/FunctionSafe/JsonSerFunctionSafeData.h JsonSerializers/FunctionSafe/JsonSerFunctionSafeData.cpp
    JsonSerializers/Language/JsonSerLanguage.h JsonSerializers/Language/JsonSerLanguage.cpp
    JsonSerializers/Language/JsonSerLanguageItem.h JsonSerializers/Language/JsonSerLanguageItem.cpp
    JsonSerializers/ZeroPoint/JsonSerZeroPointRepairCalibData.h JsonSerializers/ZeroPoint/JsonSerZeroPointRepairCalibData.cpp
    JsonSerializers/ZeroPoint/JsonSerZeroPointRepairCalibResult.h JsonSerializers/ZeroPoint/JsonSerZeroPointRepairCalibResult.cpp
    JsonSerializers/ZeroPoint/JsonSerZeroPointRepairPosData.h JsonSerializers/ZeroPoint/JsonSerZeroPointRepairPosData.cpp
    JsonSerializers/ForceCtrl/JsonSerForceCtrlPosData.h JsonSerializers/ForceCtrl/JsonSerForceCtrlPosData.cpp
    JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibResult.h JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibResult.cpp
    JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibItem.h JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibItem.cpp
    JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibData.h JsonSerializers/ForceCtrl/JsonSerForceCtrlCalibData.cpp
    JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonSensorChannelPara.h JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonSensorChannelPara.cpp
    JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceSensorOutputSignal.h JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceSensorOutputSignal.cpp
    JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceSensorInputSignal.h JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceSensorInputSignal.cpp
    JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceCtrlSensorPara.h JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonForceCtrlSensorPara.cpp
    JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonFCSensorParaArr.h JsonSerializers/ForceCtrl/ForceCtrlSensor/JsonFCSensorParaArr.cpp
    JsonSerializers/ForceCtrl/ForceCtrlLimit/JsonForceCtrlLimitPara.h JsonSerializers/ForceCtrl/ForceCtrlLimit/JsonForceCtrlLimitPara.cpp
    JsonSerializers/ForceCtrl/ForceCtrlLimit/JsonForceCtrlLimitParaArr.h JsonSerializers/ForceCtrl/ForceCtrlLimit/JsonForceCtrlLimitParaArr.cpp
    JsonSerializers/ForceCtrl/ForceCtrlCoordinate/JsonFCCoordinatePara.h JsonSerializers/ForceCtrl/ForceCtrlCoordinate/JsonFCCoordinatePara.cpp
    JsonSerializers/ForceCtrl/ForceCtrlCoordinate/JsonFCCoordinateParaArr.h JsonSerializers/ForceCtrl/ForceCtrlCoordinate/JsonFCCoordinateParaArr.cpp
    JsonSerializers/ForceCtrl/ForceCtrControl/JsonForceCtrlMovePara.h JsonSerializers/ForceCtrl/ForceCtrControl/JsonForceCtrlMovePara.cpp
    JsonSerializers/ForceCtrl/ForceCtrControl/JsonForceCtrlMoveParaArr.h JsonSerializers/ForceCtrl/ForceCtrControl/JsonForceCtrlMoveParaArr.cpp
    JsonSerializers/ForceCtrl/ForceCtrConfig/JsonForceCtrlConfigPara.h JsonSerializers/ForceCtrl/ForceCtrConfig/JsonForceCtrlConfigPara.cpp
    JsonSerializers/ForceCtrl/ForceCtrConfig/JsonForceCtrlConfigParaArr.h JsonSerializers/ForceCtrl/ForceCtrConfig/JsonForceCtrlConfigParaArr.cpp

    CallbackManager/CallbackManager.cpp CallbackManager/CallbackManager.h

    NumHelper.cpp NumHelper.h
    Ping/Ping.cpp Ping/Ping.h
    StringHelper.cpp StringHelper.h
    StringSerializers/StrSerFileInfo.cpp StringSerializers/StrSerFileInfo.h
    StringSerializers/StrSerHex.cpp StringSerializers/StrSerHex.h
    StringSerializers/StrSerJson.cpp StringSerializers/StrSerJson.h
    StringSerializers/StrSerTime.cpp StringSerializers/StrSerTime.h
    StringSerializers/StringSerializers.h TestHelper.cpp
    TestHelper.h
    RCMD5/rcmd5.cpp RCMD5/rcmd5.h
    ${Ftp_Src}
)

# 在VS中按目录层级组织源代码
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	file(GLOB_RECURSE SOURCE_FILES "*.h")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobUtil" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
	
	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobUtil" "" SOURCE_PATH ${SOURCE_PATH})
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
      set(InoRoUtil_Public_Cobot_TP_Src
          Telnet/TelnetClient.cpp Telnet/TelnetClient.h)
    include(cmake/Cobot_TP.cmake)
endif()
