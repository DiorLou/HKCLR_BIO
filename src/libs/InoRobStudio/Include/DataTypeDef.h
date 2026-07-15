#pragma once
#include <cstring>
#include <thread>

typedef unsigned char int8u;        // 8位无符号整数
typedef signed char int8s;          // 8位有符号整数
typedef unsigned short int int16u;  // 16位无符号整数
typedef short int int16s;           // 16位有符号整数
typedef unsigned int int32u;        // 32位无符号整数
typedef int int32s;                 // 32位有符号整数
typedef unsigned long long int64u;  // 64位无符号整数
typedef long long int64s;           // 64位有符号整数
typedef float floats;               // 单精度浮点数
typedef double floatd;              // 双精度浮点数

typedef signed char INT8;
typedef signed short INT16;
typedef signed int INT32;
typedef long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef int INT;
typedef unsigned int UINT;

#ifndef _MINWINDEF_
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
#endif  // !_MINWINDEF_

#if defined(__linux__)
inline void Sleep(DWORD dwMilliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(dwMilliseconds));
}

constexpr WORD MAX_PATH = 260;
constexpr WORD _MAX_FNAME = 256;
#endif
