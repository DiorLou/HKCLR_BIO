cmake_minimum_required(VERSION 3.5)

#预编译代码
set(PCH_H pch.h)
set(PCH_C pch.cpp)

# 所有平台共用的源代码
set(InoRobLog_Public_Src
    GlobalTip/GlobalTip.cpp
    GlobalTip/GlobalTip.h Include/GlobalTip.h
    Include/IInoRobLog.h InoRobLog.cpp
    InoRobLog.h Log.cpp Log.h 
	InoVersion.cpp InoVersion.h
	PrintInfo/PrintInfo.cpp
    PrintInfo/PrintInfo.h
)

# 在VS中按目录层级组织源代码
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	file(GLOB_RECURSE SOURCE_FILES "*.h")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobLog" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)
	
	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
	foreach(SOURCE_FILE ${SOURCE_FILES})
		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
		string(REPLACE "\\src\\Model\\InoRobLog" "" SOURCE_PATH ${SOURCE_PATH})
		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
	endforeach(SOURCE_FILE)

#	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#	source_group("" FILES Log.h Log.cpp
#						  InoRobLog.h InoRobLog.cpp
#						  pch.h pch.cpp)
#	source_group("Include" FILES Include/IInoRobLog.h Include/GlobalTip.h)
#	source_group("GlobalTip" FILES GlobalTip/GlobalTip.h GlobalTip/GlobalTip.cpp)
#	source_group("PrintInfo" FILES PrintInfo/PrintInfo.h PrintInfo/PrintInfo.cpp)
endif()

# 工业 示教器2.0配置
if(  Platform_Industy_TP_2_0_Msvc_Win
  OR Platform_Industy_TP_2_0_Linux_Arm_Gcc
  OR Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
    include(cmake/Industry_TP_2_0.cmake)
# 协作示教器配置
elseif( Platform_Cobot_TP_MinGW_Win
      OR Platform_Cobot_TP_Msvc_Win
      OR Platform_Cobot_TP_Android_Arm_V7a
      OR Platform_Cobot_TP_Android_Arm_64_V8a
      OR Platform_Cobot_TP_Android_X86
      OR Platform_Cobot_TP_Android_X86_64)
    include(cmake/Cobot_TP.cmake)
endif()
