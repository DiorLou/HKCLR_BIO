cmake_minimum_required(VERSION 3.5)

set(targetName InoRobLog)

# 设置Qt预处理
set(CMAKE_AUTOMOC ON)


# 配置MSVC预编译
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	# msvcpch.cmake的路径
	set(MSVCCMAKE_PCH ${CMAKE_SOURCE_DIR}/tools/)
	
	# 添加预编译cmake的路径
	LIST(APPEND CMAKE_MODULE_PATH ${MSVCCMAKE_PCH})
	
	# 包含msvcpch.cmake
	INCLUDE(msvcpch)
endif()

add_library(${targetName} SHARED ${InoRobLog_Public_Src} ${PCH_C})
target_link_libraries(${targetName} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(${targetName} PRIVATE INOROBLOG_EXPORTS)

# 开启MSVC预编译
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
	USE_MSVC_PCH(${targetName} ${PCH_H} ${PCH_C})
endif ()
