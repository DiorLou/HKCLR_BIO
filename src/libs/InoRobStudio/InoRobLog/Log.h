/****************************************************************
 * File Descrip : spdlog日志封装
 * Author       : jinsheng
 * example      :
    // 设置总level开关，默认为info
    InoRobLog::logger()->set_level(spdlog::level::trace);
    // 设置独立sink开关，只有总开关+sink开关都满足的sink，才会输出
    InoRobLog::getSink(InoRobLog::SinkType::FILE)->set_level(spdlog::level::debug);     // 日志文件logs/YYMMDD.txt
    InoRobLog::getSink(InoRobLog::SinkType::CONSOLE)->set_level(spdlog::level::trace);  // 控制台输出
    InoRobLog::getSink(InoRobLog::SinkType::MSVC)->set_level(spdlog::level::trace);     // Microsoft Visual Studio IDE 调试输出
    // 打印日志
    InoRobLog::info("log test by info level");
    InoRobLog::debug("log test by info level {}", __FUNCTION__);
    InoRobLog::trace("{1} {0}", "world", "hello");  // hello world
 ****************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <spdlog/spdlog.h>
#include "dllspec.h"

using memory_buf_t = fmt::basic_memory_buffer<char, 250>;
using wmemory_buf_t = fmt::basic_memory_buffer<wchar_t, 250>;

namespace InoRobLog
{

// 日志种类(logger)
enum class LogType
{
    DEFAULT,
    NETWORK,
    OPERATION
};

// sink类型
enum class SinkType
{
    FILE,
    CONSOLE,
    MSVC
};

// 创建logger
INOROBLOG_CLASS void createDefaultLogger();
INOROBLOG_CLASS void createNetworkLogger();
INOROBLOG_CLASS void createOperationLogger();
INOROBLOG_CLASS std::string getLoggerPath(LogType logType);

INOROBLOG_CLASS void shutdownLog();

// 获取logger, ex: auto logger = InoRobLog::logger();
INOROBLOG_CLASS std::shared_ptr<spdlog::logger> logger(LogType logType = LogType::DEFAULT);

// 获取sink
INOROBLOG_CLASS spdlog::sink_ptr getSink(SinkType sinkType);

/**
 * @brief 设置是否打印系统日志
 * @param isPrintLog 是否打印日志
 */
INOROBLOG_CLASS void setPrintLog(bool isPrintLog);

INOROBLOG_CLASS bool isPrintLog();


#ifndef COBOT_CUSTOM_LOG

INOROBLOG_CLASS void printInfoToLog(const std::string &printInfo);
#pragma region 日志打印函数

template <typename... Args>
void trace(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->trace(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_TRACE)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->debug(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_DEBUG)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void info(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->info(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_INFO)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->warn(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_WARN)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void error(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->error(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_ERROR)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void critical(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->critical(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_CRITICAL)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

#pragma endregion
#else

INOROBLOG_CLASS void printInfoToLog(int type, const std::string &printInfo);
#pragma region 日志打印函数
template <typename... Args>
void trace(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->trace(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_TRACE)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_TRACE, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->debug(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_DEBUG)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_DEBUG, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void info(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->info(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_INFO)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_INFO, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->warn(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_WARN)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_WARN, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void error(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->error(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_ERROR)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_ERROR, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

template <typename... Args>
void critical(spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    try
    {
        logger()->critical(fmt, std::forward<Args>(args)...);

        if (isPrintLog() && logger()->level() <= SPDLOG_LEVEL_CRITICAL)
        {
            memory_buf_t buf;
            fmt::vformat_to(fmt::appender(buf), fmt, fmt::make_format_args(args...));
            printInfoToLog(SPDLOG_LEVEL_CRITICAL, std::string(buf.data(), buf.size()));
        }
    }
    catch (...)
    {
    }
}

#pragma endregion
#endif

}  // namespace InoRobLog
