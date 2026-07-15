# CMake最低版本要求
cmake_minimum_required(VERSION 3.5)

if(NOT PROJECT_NAME)
   project(Model LANGUAGES CXX)
   # 设置平台属性
   message("CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
   message("CMAKE_SYSTEM_PROCESSOR : ${CMAKE_SYSTEM_PROCESSOR}")

   # 设置C++17支持
   set(CMAKE_CXX_STANDARD 17)
	
   # 严格遵循指定C++版本
   set(CMAKE_CXX_STANDARD_REQUIRED ON)
   
   # windows下使用unicode宽字符编码
   if(CMAKE_SYSTEM_NAME MATCHES "Windows")
       add_definitions("-DUNICODE" "-D_UNICODE")
   endif()
   
   #_开头为cmake系统保留变量 为了方便辨识平台属性使用_开头定义变量
   if(CMAKE_SYSTEM_NAME MATCHES "Windows")
       if(MSVC)
           set(Platform_Industy_TP_2_0_Msvc_Win OFF)
           set(Platform_Cobot_TP_Msvc_Win ON)
       elseif(MINGW)
           set(Platform_Cobot_TP_MinGW_Win ON)
           add_definitions(-DPLATFORM_COBOT_TP_MINGW_WIN)
           set(CMAKE_CXX_FLAGS "-mwindows")
       else()
           message(FATAL_ERROR "ERROR: unknown Windows platform config")
       endif()
   elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
       if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
           set(Platform_Industy_TP_2_0_Linux_Arm_Gcc ON)
       elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
           set(Platform_Industy_TP_2_0_Linux_Gcc_X86_64 ON)
       else()
           message(FATAL_ERROR "ERROR: unknown Linux platform config")
       endif()
   elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
       set(COBOT_ANDROID ON)
       if (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7-a")
           set(Platform_Cobot_TP_Android_Arm_V7a ON)
           set(COBOT_TP_ANDROID_ABI "armeabi-v7a")
           add_definitions(-DPLATFORM_COBOT_TP_ANDROID_ARM_V7A)
       elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
           set(Platform_Cobot_TP_Android_Arm_64_V8a ON)
           add_definitions(-DPLATFORM_COBOT_TP_ANDROID_ARM_64_V8A)
           set(COBOT_TP_ANDROID_ABI "arm64-v8a")
       elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
           set(Platform_Cobot_TP_Android_X86 ON)
           add_definitions(-DPLATFORM_COBOT_TP_ANDROID_X86)
           set(COBOT_TP_ANDROID_ABI "x86")
       elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
           set(Platform_Cobot_TP_Android_X86_64 ON)
           add_definitions(-DPLATFORM_COBOT_TP_ANDROID_X86_64)
           set(COBOT_TP_ANDROID_ABI "x86_64")
       else()
           message(FATAL_ERROR "ERROR: unknown Android platform config")
       endif()
   else()
       message(FATAL_ERROR "ERROR: unknown CMAKE_SYSTEM_NAME")
   endif()
   #引入平台文件
   # 示教器2.0
   if(Platform_Industy_TP_2_0_Msvc_Win)
       include(tools/msvc-config.cmake)
   elseif(Platform_Industy_TP_2_0_Linux_Arm_Gcc)
       include(tools/armgcc-config.cmake)
   elseif(Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
        include(tools/linux-gcc-config.cmake)
   #协作
   elseif(Platform_Cobot_TP_MinGW_Win)
       include(tools/mingw-config.cmake)
   elseif(Platform_Cobot_TP_Msvc_Win)
       include(tools/msvc_tp-config.cmake)
   elseif(Platform_Cobot_TP_Android_Arm_V7a)
       include(tools/android-config.cmake)
   elseif(Platform_Cobot_TP_Android_Arm_64_V8a)
       include(tools/android-config.cmake)
   elseif(Platform_Cobot_TP_Android_X86)
       include(tools/android-config.cmake)
   elseif(Platform_Cobot_TP_Android_X86_64)
        include(tools/android-config.cmake)
   endif()

   if(platform_link_dir)
       link_directories(${platform_link_dir})
   endif()
   message("BOOST_DIR: ${BOOST_DIR}")
   
   if (QTDIR)
       set(CMAKE_PREFIX_PATH ${QTDIR})
       message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
   endif()
   
   find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
   find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
endif()

# 将模型层作为源代码引入
set(InoRobStudio_Path ${CMAKE_CURRENT_SOURCE_DIR})
# 工业 示教器2.0配置
if(  Platform_Industy_TP_2_0_Msvc_Win
 OR Platform_Industy_TP_2_0_Linux_Arm_Gcc
 OR Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
   # 头文件搜索位置
   INCLUDE_DIRECTORIES(.)
   INCLUDE_DIRECTORIES(Include)
   INCLUDE_DIRECTORIES(third_party/include)
   INCLUDE_DIRECTORIES(InoRobBusiness/Include)
   INCLUDE_DIRECTORIES(${platform_include_dir})
   # 库文件搜索位置
   link_directories(${platform_link_dir})
   # 主站文件拷贝(切勿删除)
   file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static_config/ DESTINATION ${STATIC_CONFIG_OUTPUT_PATH})
endif()

# 协作示教器配置
if(	 Platform_Cobot_TP_MinGW_Win
	 OR Platform_Cobot_TP_Msvc_Win
	 OR Platform_Cobot_TP_Android_Arm_V7a
	 OR Platform_Cobot_TP_Android_Arm_64_V8a
	 OR Platform_Cobot_TP_Android_X86
	 OR Platform_Cobot_TP_Android_X86_64)
   # boost路径
   set(BOOST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/boost)
   # boost头文件路径
   set(boost_include_dir ${BOOST_DIR}/include)
   # 创建公用头文件依赖列表 供子项目使用
   set(InoRobStudio_Public_Include_List
		 ${CMAKE_CURRENT_SOURCE_DIR}
		 ${CMAKE_CURRENT_SOURCE_DIR}/Include
         ${CMAKE_CURRENT_SOURCE_DIR}/InoRobBusiness
		 ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
		 ${BOOST_DIR}/include
		 CACHE INTERNAL "InoRobStudio_Public_Include_List" FORCE)
   add_subdirectory(InoRobUdf)
   add_definitions(-DOPEN_INOROUDF)
   add_definitions(-DOPEN_INOROBUTIL)
   message("InoRobStudio_Public_Include_List is ${InoRobStudio_Public_Include_List}")
endif()

# 添加模块代码路径
add_subdirectory(InoRobLog)
add_subdirectory(InoRobUtil)
add_subdirectory(GlobalDataService)
add_subdirectory(InoRobBusiness)
add_subdirectory(InoRobBusinessProxy)

