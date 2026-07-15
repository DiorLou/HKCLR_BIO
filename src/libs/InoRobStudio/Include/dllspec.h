/*! @file
********************************************************************************
<PRE>
模块名       : All
文件名       : dllspec.h
相关文件     :
文件实现功能 : 动态链接库接口类接口函数导入导出声明宏定义
作者         : 许健古
版本         : 1.0
--------------------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期         版本        修改人          修改内容
2014/07/30    1.0
</PRE>
********************************************************************************/

#pragma once

#ifdef _WIN32
    #ifdef INOROBLOG_EXPORTS
        #define INOROBLOG_CLASS __declspec(dllexport)
    #else
        #define INOROBLOG_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define INOROBLOG_CLASS
#else
    #define INOROBLOG_CLASS
#endif

#ifdef _WIN32
    #ifdef INOROBUTIL_EXPORTS
        #define INOROBUTIL_CLASS __declspec(dllexport)
    #else
        #define INOROBUTIL_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define INOROBUTIL_CLASS
#else
    #define INOROBUTIL_CLASS
#endif

#ifdef _WIN32
    #ifdef LINKER_EXPORT
        #define LINKER_CLASS __declspec(dllexport)
    #else
        #define LINKER_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define LINKER_CLASS
#else
    #define LINKER_CLASS
#endif

#ifdef _WIN32
    #ifdef DATASRV_EXPORT
        #define DATASRV_CLASS __declspec(dllexport)
        #define DATASRV_VAR   __declspec(dllexport)
    #else
        #define DATASRV_CLASS __declspec(dllimport)
        #define DATASRV_VAR   __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define DATASRV_CLASS
    #define DATASRV_VAR
#else
    #define DATASRV_CLASS
    #define DATASRV_VAR
#endif  // _WIN32

#ifdef _WIN32
    #ifdef INOROBBUSINESS_EXPORTS
        #define INOROBBUSINESS_CLASS __declspec(dllexport)
    #else
        #define INOROBBUSINESS_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define INOROBBUSINESS_CLASS
#else
    #define INOROBBUSINESS_CLASS
#endif  // _WIN32

#ifdef _WIN32
    #ifdef INOROBBUSINESSPROXY_EXPORTS
        #define INOROBBUSINESSPROXY_CLASS __declspec(dllexport)
    #else
        #define INOROBBUSINESSPROXY_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define INOROBBUSINESSPROXY_CLASS
#else
    #define INOROBBUSINESSPROXY_CLASS
#endif  // _WIN32
