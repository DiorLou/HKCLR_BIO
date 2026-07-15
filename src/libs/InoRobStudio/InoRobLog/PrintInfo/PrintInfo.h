#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/fmt/bundled/core.h>
#include <bitset>
#include "dllspec.h"
#include "InoRobLog.h"
#include "GlobalTip.h"
using memory_buf_t = fmt::basic_memory_buffer<char, 250>;

#ifndef COBOT_CUSTOM_LOG
namespace InoRobLog
{
/**
 * @brief 消息输出条件
 */
enum MsgCond : unsigned short
{
    PRINT = 0b001,              // 打印输出
    WRITE = 0b010,              // 日志保存
    POPUP = 0b100,              // 弹出提示
    PRINT_WRITE = 0b011,        // 打印并写
    PRINT_POPUP = 0b101,        // 打印并弹出
    WRITE_POPUP = 0b110,        // 写并弹出
    PRINT_WRITE_POPUP = 0b111,  // 打印、写、弹出
    ALL = 0xFF                  // 全部
};

/**
 * @brief 消息输出类型
 */
enum class MsgType : unsigned short
{
    MESSAGE_OPUTPUT = 0,  // 消息
    SUCCESS_OPUTPUT,      // 成功
    WARNING_OPUTPUT,      // 警告
    ERROR_OPUTPUT         // 错误
};

class INOROBLOG_CLASS PrintInfo : public QObject
{
    Q_OBJECT
public:
    // 信息类型
    enum InfoType : char
    {
        MESSAGE_INFO = 0,  // 消息
        WARNING_INFO,      // 警告信息
        ERROR_INFO         // 错误信息
    };
    Q_ENUM(InfoType)
    static PrintInfo *getInstance()
    {
        static PrintInfo instance;
        return &instance;
    }

    PrintInfo(const PrintInfo &) = delete;
    PrintInfo &operator=(const PrintInfo &) = delete;

Q_SIGNALS:
    /**
     * @brief 打印信息信号
     * @param type  信息类型
     * @param info  信息内容
     */
    void printInfoSignal(InfoType type, std::string info);

    /**
     * @brief 显示阻塞提示信息 必须主动关闭
     * @param info 显示内容 ""表示关闭
     */
    void waitingInfoSignal(std::string info);

    /**
     * @brief 记录操作日志
     * @param info 内容
     */
    void sigRecordOperation(std::string info);

private:
    PrintInfo();
    ~PrintInfo();
};

    #pragma region 工艺插件

INOROBLOG_CLASS void outputInfoForPlugin(MsgCond type, std::string &msg);
INOROBLOG_CLASS void outputWarningForPlugin(MsgCond type, std::string &msg);
INOROBLOG_CLASS void outputErrorForPlugin(MsgCond type, std::string &msg);
INOROBLOG_CLASS void outputSuccessForPlugin(MsgCond type, std::string &msg);
INOROBLOG_CLASS void outputWaitingForPlugin(std::string &msg);
INOROBLOG_CLASS void outputCloseInfoForPlugin(MsgCond condType, MsgType msgType, std::string &msg);
INOROBLOG_CLASS void printMessageInfoForPlugin(std::string &msg);
INOROBLOG_CLASS void printWarningInfoForPlugin(std::string &msg);
INOROBLOG_CLASS void printErrorInfoForPlugin(std::string &msg);

    #pragma endregion

/**
 * @brief 输出信息
 * @param type 消息输出条件
 */
template <typename... Args>
void outputInfo(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
    }
    if (flags.test(1))
    {
        logger()->info(fmt, std::forward<Args>(args)...);
    }
    if (flags.test(2))
    {
        popMessageTip(info);
    }
}

/**
 * @brief 输出警告
 * @param type 消息输出条件
 */
template <typename... Args>
void outputWarning(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
    }
    if (flags.test(1))
    {
        logger()->warn(fmt, std::forward<Args>(args)...);
    }
    if (flags.test(2))
    {
        popWarningTip(info);
    }
}

/**
 * @brief 输出错误
 * @param type 消息输出条件
 */
template <typename... Args>
void outputError(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
    }
    if (flags.test(1))
    {
        logger()->error(fmt, std::forward<Args>(args)...);
    }
    if (flags.test(2))
    {
        popErrorTip(info);
    }
}

/**
 * @brief 输出成功
 * @param type 消息输出条件
 */
template <typename... Args>
void outputSuccess(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
    }
    if (flags.test(1))
    {
        logger()->info(fmt, std::forward<Args>(args)...);
    }
    if (flags.test(2))
    {
        popSuccessTip(info);
    }
}

/**
 * @brief 输出阻塞等待过程提示信息,必须主动关闭,内容空表示关闭
 */
template <typename... Args>
void outputWaiting(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->waitingInfoSignal(info);
}
/*
template <typename... Args>
void outputWaiting(spdlog::wformat_string_t<Args...> fmt, Args &&...args)
{
    wmemory_buf_t wbuf;
    fmt::vformat_to(std::back_inserter(wbuf), spdlog::details::to_string_view(fmt), fmt::make_format_args<fmt::wformat_context>(args...));
    memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(wbuf.data(), wbuf.size()), buf);
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->waitingInfoSignal(info);
}*/

/**
 * @brief 记录到操作日志
 */
template <typename... Args>
void outputOperation(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->sigRecordOperation(info);
}
/*template <typename... Args>
void outputOperation(spdlog::wformat_string_t<Args...> fmt, Args &&...args)
{
    wmemory_buf_t wbuf;
    fmt::vformat_to(std::back_inserter(wbuf), spdlog::details::to_string_view(fmt), fmt::make_format_args<fmt::wformat_context>(args...));
    memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(wbuf.data(), wbuf.size()), buf);
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->sigRecordOperation(info);
}*/

/**
 * @brief 输出关闭信息
 * @param condType 消息输出条件
 * @param msgType 消息输出类型
 */
template <typename... Args>
void outputCloseInfo(MsgCond condType, MsgType msgType, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    std::bitset<3> cond(condType);
    if (cond.test(0))
    {
        switch (msgType)
        {
            case MsgType::WARNING_OPUTPUT:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
                break;
            case MsgType::ERROR_OPUTPUT:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
                break;
            default:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
                break;
        }
    }

    if (cond.test(1))
    {
        switch (msgType)
        {
            case MsgType::WARNING_OPUTPUT:
                logger()->warn(fmt, std::forward<Args>(args)...);
                break;
            case MsgType::ERROR_OPUTPUT:
                logger()->error(fmt, std::forward<Args>(args)...);
                break;
            default:
                logger()->info(fmt, std::forward<Args>(args)...);
                break;
        }
    }

    if (cond.test(2))
    {
        switch (msgType)
        {
            case MsgType::SUCCESS_OPUTPUT:
                popSuccessCloseTip(info);
                break;
            case MsgType::WARNING_OPUTPUT:
                popWarningCloseTip(info);
                break;
            case MsgType::ERROR_OPUTPUT:
                popErrorCloseTip(info);
                break;
            default:
                popMessageCloseTip(info);
                break;
        }
    }
}

/**
 * @brief 打印消息信息
 */
template <typename... Args>
void printMessageInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, std::string(buf.data(), buf.size()));
}
/*
template <typename... Args>
void printMessageInfo(spdlog::wformat_string_t<Args...> fmt, Args &&...args)
{
    wmemory_buf_t wbuf;
    fmt::vformat_to(std::back_inserter(wbuf), spdlog::details::to_string_view(fmt), fmt::make_format_args<fmt::wformat_context>(args...));
    memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(wbuf.data(), wbuf.size()), buf);
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
}*/

/**
 * @brief 打印警告信息
 */
template <typename... Args>
void printWarningInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, std::string(buf.data(), buf.size()));
}
/*
template <typename... Args>
void printWarningInfo(spdlog::wformat_string_t<Args...> fmt, Args &&...args)
{
    wmemory_buf_t wbuf;
    fmt::vformat_to(std::back_inserter(wbuf), spdlog::details::to_string_view(fmt), fmt::make_format_args<fmt::wformat_context>(args...));
    memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(wbuf.data(), wbuf.size()), buf);
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
}*/

/**
 * @brief 打印错误信息
 */
template <typename... Args>
void printErrorInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, std::string(buf.data(), buf.size()));
}
/*
template <typename... Args>
void printErrorInfo(spdlog::wformat_string_t<Args...> fmt, Args &&...args)
{
    wmemory_buf_t wbuf;
    fmt::vformat_to(std::back_inserter(wbuf), spdlog::details::to_string_view(fmt), fmt::make_format_args<fmt::wformat_context>(args...));
    memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(wbuf.data(), wbuf.size()), buf);
    std::string info(buf.data(), buf.size());
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
}*/
}  // namespace InoRobLog
#else
namespace InoRobLog
{
/**
 * @brief 消息输出条件
 */
enum MsgCond : unsigned short
{
    PRINT = 0b001,              // 打印输出
    WRITE = 0b010,              // 日志保存
    POPUP = 0b100,              // 弹出提示
    PRINT_WRITE = 0b011,        // 打印并写
    PRINT_POPUP = 0b101,        // 打印并弹出
    WRITE_POPUP = 0b110,        // 写并弹出
    PRINT_WRITE_POPUP = 0b111,  // 打印、写、弹出
    ALL = 0xFF                  // 全部
};

/**
 * @brief 消息输出类型
 */
enum class MsgType : unsigned short
{
    MESSAGE_OPUTPUT = 0,  // 消息
    SUCCESS_OPUTPUT,      // 成功
    WARNING_OPUTPUT,      // 警告
    ERROR_OPUTPUT         // 错误
};

/**
 * @brief 打印信息类。 所有打印到信息栏的信息通过该类进行打印
 */
class INOROBLOG_CLASS PrintInfo : public QObject
{
    Q_OBJECT
public:
    // 信息类型
    enum InfoType : char
    {
        MESSAGE_INFO = 0,  // 消息
        WARNING_INFO,      // 警告信息
        ERROR_INFO         // 错误信息
    };
    // 日志类型
    enum LogType : char
    {
        TRACE_LOG = SPDLOG_LEVEL_TRACE,
        DEBUG_Log = SPDLOG_LEVEL_DEBUG,
        INFO_Log = SPDLOG_LEVEL_INFO,
        WARN_Log = SPDLOG_LEVEL_WARN,
        ERROR_Log = SPDLOG_LEVEL_ERROR,
        CRITICAL_Log = SPDLOG_LEVEL_ERROR
    };

    Q_ENUM(InfoType)
    Q_ENUM(LogType)
    static PrintInfo *getInstance();
    PrintInfo();
    ~PrintInfo();

Q_SIGNALS:
    /**
     * @brief 打印信息信号
     * @param type  信息类型
     * @param info  信息内容
     */
    void printInfoSignal(InfoType type, std::string info);
    /**
     * @brief 打印日志的信号
     * @param type  信息类型
     * @param log  信息内容
     */
    void logInfoSignal(LogType type, std::string log);
    /**
     * @brief 显示阻塞提示信息 必须主动关闭
     * @param info 显示内容 ""表示关闭
     */
    void waitingInfoSignal(std::string info);
};
INOROBLOG_CLASS extern CContainer<InoRobLog::PrintInfo> ILOG;

/**
 * @brief 输出信息
 * @param type 消息输出条件
 */
template <typename... Args>
void outputInfo(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
    }
    logger()->info(fmt, std::forward<Args>(args)...);
    if (isPrintLog())
        emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::INFO_Log, info);
    if (flags.test(2))
    {
        popMessageTip(info);
    }
}
/**
 * @brief 输出警告
 * @param type 消息输出条件
 */
template <typename... Args>
void outputWarning(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
    }

    logger()->warn(fmt, std::forward<Args>(args)...);
    if (isPrintLog())
        emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::WARN_Log, info);

    if (flags.test(2))
    {
        popWarningTip(info);
    }
}

/**
 * @brief 输出错误
 * @param type 消息输出条件
 */
template <typename... Args>
void outputError(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
    }

    logger()->error(fmt, std::forward<Args>(args)...);
    if (isPrintLog())
        emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::ERROR_Log, info);

    if (flags.test(2))
    {
        popErrorTip(info);
    }
}

/**
 * @brief 输出成功
 * @param type 消息输出条件
 */
template <typename... Args>
void outputSuccess(MsgCond type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    std::bitset<3> flags(type);
    if (flags.test(0))
    {
        emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
    }

    logger()->info(fmt, std::forward<Args>(args)...);
    if (isPrintLog())
        emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::INFO_Log, info);

    if (flags.test(2))
    {
        popSuccessTip(info);
    }
}

/**
 * @brief 输出阻塞等待过程提示信息,必须主动关闭,内容空表示关闭
 */
template <typename... Args>
void outputWaiting(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    emit PrintInfo::getInstance()->waitingInfoSignal(info);
}

/**
 * @brief 输出关闭信息
 * @param condType 消息输出条件
 * @param msgType 消息输出类型
 */
template <typename... Args>
void outputCloseInfo(MsgCond condType, MsgType msgType, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());

    if (info.empty())
    {
        return;
    }

    std::bitset<3> cond(condType);
    if (cond.test(0))
    {
        switch (msgType)
        {
            case MsgType::WARNING_OPUTPUT:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
                break;
            case MsgType::ERROR_OPUTPUT:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
                break;
            default:
                emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
                break;
        }
    }

    switch (msgType)
    {
        case MsgType::WARNING_OPUTPUT:
            logger()->warn(fmt, std::forward<Args>(args)...);
            if (isPrintLog())
                emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::WARN_Log, info);
            break;
        case MsgType::ERROR_OPUTPUT:
            logger()->error(fmt, std::forward<Args>(args)...);
            if (isPrintLog())
                emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::WARN_Log, info);
            break;
        default:
            logger()->info(fmt, std::forward<Args>(args)...);
            if (isPrintLog())
                emit PrintInfo::getInstance()->logInfoSignal(PrintInfo::INFO_Log, info);
            break;
    }

    if (cond.test(2))
    {
        switch (msgType)
        {
            case MsgType::SUCCESS_OPUTPUT:
                popSuccessCloseTip(info);
                break;
            case MsgType::WARNING_OPUTPUT:
                popWarningCloseTip(info);
                break;
            case MsgType::ERROR_OPUTPUT:
                popErrorCloseTip(info);
                break;
            default:
                popMessageCloseTip(info);
                break;
        }
    }
}

/**
 * @brief 打印消息信息
 */
template <typename... Args>
void printMessageInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());
    if (info.empty())
    {
        return;
    }
    logger()->info(fmt, std::forward<Args>(args)...);
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::MESSAGE_INFO, info);
}

/**
 * @brief 打印警告信息
 */
template <typename... Args>
void printWarningInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());
    if (info.empty())
    {
        return;
    }
    logger()->warn(fmt, std::forward<Args>(args)...);
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::WARNING_INFO, info);
}

/**
 * @brief 打印错误信息
 */
template <typename... Args>
void printErrorInfo(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
    std::string info(buf.data(), buf.size());
    if (info.empty())
    {
        return;
    }
    logger()->error(fmt, std::forward<Args>(args)...);
    emit PrintInfo::getInstance()->printInfoSignal(PrintInfo::ERROR_INFO, info);
}
}  // namespace InoRobLog
#endif
