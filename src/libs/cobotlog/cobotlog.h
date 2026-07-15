#pragma once

#include "cobotlog_global.h"
#include "QObject"

//输出提示消息到 屏幕气泡 + 日志栏 + 写日志
//错误 警告应使用messageBox
#define SHOW_MSG(x)       CobotLog::instance()->showMsg(x)
#define SHOW_ERROR(x)       CobotLog::instance()->showErrorMsg(x)

// 输出消息到 日志栏 + 写日志
// 如果想仅打印到屏幕 调用CobotLog::instance()->printxxx(x,PRINT);
#define PRINT_MSG(x)       CobotLog::instance()->printMsg(x)
#define PRINT_WARN(x)      CobotLog::instance()->printWarn(x)
#define PRINT_ERROR(x)     CobotLog::instance()->printError(x)
#define PRINT_MSG_ONLY(x)  CobotLog::instance()->printMsg(x, CobotLog::InoMsgCond::Print);

// 输出消息到 写日志
#define LOG_TRACE(x)       CobotLog::instance()->logTrace(x)
#define LOG_DEBUG(x)       CobotLog::instance()->logDebug(x)
#define LOG_INFO(x)        CobotLog::instance()->logInfo(x)
#define LOG_WARN(x)        CobotLog::instance()->logWarn(x)
#define LOG_ERROR(x)       CobotLog::instance()->logError(x)
#define LOG_FATAL(x)       CobotLog::instance()->logFatal(x)
#define LOG_CRITICAL(x)    CobotLog::instance()->logPrint(x)

// 仅写入日志(高频日志,仅厂家模式可以打开,默认关闭)
#define FREQ_LOG_INFO(x)     CobotLog::instance()->freqLogInfo(x)
#define FREQ_LOG_WARN(x)      CobotLog::instance()->freqLogWarn(x)
#define FREQ_LOG_ERROR(x)     CobotLog::instance()->freqLogError(x)
#define FREQ_LOG_FATAL(x)     CobotLog::instance()->freqLogFatal(x)

// 上层调用日志打印函数会到CobotLog类，然后再下发到InoRobtLog
// InoRobtLog再传信号上来
// 做了一次隔离
class QTimer;
class COBOTLOG_EXPORT CobotLog : public QObject
{
    Q_OBJECT
public:
    enum InoInfoType : char
    {
        Message_Info = 0,  // 消息
        Warning_Info,      // 警告信息
        Error_Info,         // 错误信息
        Operation_Info     //操作日志
    };

    //一般不需要下面两个枚举
    enum InoMsgCond : unsigned short
    {
        Print = 0b001,              // 打印输出
        Write = 0b010,              // 日志保存
        Popup = 0b100,              // 弹出提示
        Print_Write = 0b011,        // 打印并写
        Print_Popup = 0b101,        // 打印并弹出
        Write_Popup = 0b110,        // 写并弹出
        Print_Write_Popup = 0b111,  // 打印、写、弹出
        All = 0xFF,                  // 全部
    };

    enum InoLogType : unsigned short
    {
        Trace_Log = 0,
        Debug_Log = 1,
        Info_Log = 2,
        Warn_Log = 3,
        Error_Log = 4,
        Critical_Log = 5
    };

    static CobotLog *instance();
    CobotLog(QObject *parent = 0);
    void setEnableOperationLog(bool);
    void setFreqLogPrint(bool bPrint);

    void showMsg(const QString &str);
    void showErrorMsg(const QString &str);

    void printMsg(const QString &str, InoMsgCond type = All);
    void printWarn(const QString &str, InoMsgCond type = All);
    void printError(const QString &str, InoMsgCond type = All);
    void printOperation(const QString &str);

    void logTrace(const QString &str);
    void logDebug(const QString &str);
    void logInfo(const QString &str);
    void logWarn(const QString &str);
    void logError(const QString &str);
    void logFatal(const QString &str);
    void logCritical(const QString &str);

    void freqLogInfo(const QString &str);
    void freqLogWarn(const QString &str);
    void freqLogError(const QString &str);
    void freqLogFatal(const QString &str);

    QString getAll();
    QString getMsg();
    QString getWarn();
    QString getError();
    QString getOperation();
    QString getLog();

    void clearAll();
    void clearMsg();
    void clearWarn();
    void clearError();
    void clearOperation();
    void clearLog();
signals:
    void signal_addPrint(InoInfoType type, const QString &msg);
    void signal_addLog(InoLogType type, const QString &msg);
    void signal_addHistoryAlarm(const QString &msg);
    void signal_showFlowWidget(const QString &msg, const int &type);
private:
    bool m_isEnableOperationLog = false;
    bool m_bFreqLogPrint = false;
    QTimer *m_timer = nullptr;

    QString m_all;
    QString m_msg;
    QString m_warnning;
    QString m_error;
    QString m_operation;
    QString m_log;
    void addNewForPrint(int type, const QString &newData);

};


