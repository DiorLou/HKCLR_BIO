#pragma once
#include "signal_slot.h"
#include "dllspec.h"

namespace InoRobLog
{
/// <summary>
/// 打印类型
/// </summary>
enum PRINT_TYPE : char
{
    PRINT_TYPE_MSG = 0,       // 输出栏打印 [Message]消息
    PRINT_TYPE_WARNING,       // 输出栏打印 [Warning]消息
    PRINT_TYPE_ERR,           // 输出栏打印 [Error  ]消息
    PRINT_TYPE_LOGMSG,        // 写日志文件 [Message]消息
    PRINT_TYPE_LOGERR,        // 写日志文件 [Error  ]消息
    PRINT_TYPE_LOGEXCEPTiON,  // 写异常日志文件 [Error  ]消息
    PRINT_TYPE_LOGA,          // 写日志文件A类别，开发者模式下
    PRINT_TYPE_LOGB,          // 写日志文件B类别，开发者模式下
    PRINT_TYPE_LOGC,          // 写日志文件C类别，开发者模式下
    PRINT_TYPE_LOGD,          // 写日志文件D类别，开发者模式下
    PRINT_TYPE_LOGE,          // 写日志文件E类别，开发者模式下
    PRINT_TYPE_LOGF,          // 写日志文件F类别，开发者模式下
};

/// <summary>
/// 打印的项数据结构
/// </summary>
struct PrintItem
{
    char Type;
    char *Conent;

    PrintItem()
    {
        Type = (char)PRINT_TYPE_MSG;
        Conent = nullptr;
    }
};

/// <summary>
/// LOG的接口类
/// </summary>
class INOROBLOG_CLASS IInoRobLog
{
public:
    // 自由格式化打印或输出日志
    virtual void Print(PRINT_TYPE type, const char *fmt, ...) = 0;

public:
    rsignal<PrintItem> PrintSignal;  // 消息打印事件
};
}  // namespace InoRobLog
