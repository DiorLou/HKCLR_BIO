cmake_minimum_required(VERSION 3.5)

#预编译代码
set(PCH_H pch.h)
set(PCH_C pch.cpp)

# 所有平台共用的源代码
set(InoDataService_Public_Src
    CommVersionMgr/AsyncPing.cpp
    CommVersionMgr/AsyncPing.h CommVersionMgr/CommVersionMgr.cpp
    CommVersionMgr/CommVersionMgr.h CommVersionMgr/CommVersions/CommVersion_0_0.cpp
    CommVersionMgr/CommVersions/CommVersion_0_0.h CommVersionMgr/CommVersions/CommVersion_1_0.cpp
    CommVersionMgr/CommVersions/CommVersion_1_0.h DataSrvBase.cpp
    DataSrvBase.h DataSrvGlobal.h
    Interfaces/ICommVersion.h Interfaces/ICommVersionMgr.h
    Interfaces/IDataService.h Interfaces/IDataSrvBase.h
    Interfaces/IPingDevice.h Protocol.cpp
    Protocol.h )

# 在VS中按目录层级组织源代码
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	file(GLOB_RECURSE SOURCE_FILES "*.h")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\GlobalDataService\\DataService" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
	
	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\GlobalDataService\\DataService" "" SOURCE_PATH ${SOURCE_PATH})
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
