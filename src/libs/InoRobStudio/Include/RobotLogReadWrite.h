/*
 *  记录和读取日志文件
 *  功能：用户可以记录日志，可以读取记录下的任意一条记录。
 *  调用：1、设置日志文件名SetLogFileName()
          2、添加一条日志AddWarningRecord()或读取一条记录ReadLogRecord()
          3、关闭日志SaveLogFile()
 *  V1.0  2015/1/19
 */

#pragma once
#include "dllspec.h"
#include "Singleton.h"
#include "Container.h"

// 日志记录类型
#define WARN_RECORD      1
#define USER_RECORD      2
#define ROBOTLOGTIMESIZE 24  // 日志时间长度

typedef unsigned char byte;
typedef struct tagRobotLog
{
    tagRobotLog()
    {
        LogID = 0;
        LogType = WARN_RECORD;
    }

    int LogID;                       // 日志ID
    int LogType;                     // 日志类型
    char LogTime[ROBOTLOGTIMESIZE];  // 报警时间 YYYY-MM-DD HH:MM:SS.MMM
} RobotLogRecord;

class ROBOTLOG_CLASS CRobotLogReadWrite
{
public:
    CRobotLogReadWrite(void);
    virtual ~CRobotLogReadWrite(void);

    bool SetLogFileName(LPCTSTR pFileName);
    int GetRecordCount(void);
    bool ReadLogRecord(int index, RobotLogRecord &record);                  // 序号从0开始
    bool AddWarningRecord(RobotLogRecord &record, bool bAutoTime = false);  // 设备端警告信息
    void AddUserOperRecord(int nOperId);                                    // 添加用户操作记录: nOperId-操作码
    void SaveLogFile(void);

    void ReMoveWarningRecord();

protected:
    bool CreateFileLi(LPCTSTR pFileName);
    bool CreateFileMappingLi(void);
    bool MapViewOfFileLi(void);
    // 内存映射文件
    bool OpenFileMap(LPCTSTR pFileName);
    void CloseMap(void);

    // 操作内存数据
    void MergeRobotLogRecord(const byte *mem, RobotLogRecord &record);
    void SplitRobotLogRecord(byte *mem, const RobotLogRecord &record);

    // 计算一条日志记录占用的字节数
    int sizeofRecord(void);

    // 获取当前系统时间
    void GetCurTime(char *pCurTime);
    // 转换时间字符串格式
    void FormatLogTime(char *pTime);
    void FormatLogTime(RobotLogRecord &record, bool bAutoTime);

    // 互斥操作
    bool Lock(void);
    void UnLock(void);

    // 初始化队列
    void InitQueue(void);

private:
    HANDLE m_hEvent;
    HANDLE m_hFile;
    HANDLE m_hFileMap;
    PVOID m_pFileMap;
    int m_nQueueHead;   // 队列头
    int m_nQueueTail;   // 队列尾
    bool m_bQueueFull;  // 队列满或空判断标记
};

ROBOTLOG_VAR extern CContainer<CRobotLogReadWrite> gs_RobotLog;  // 声明Robot日志单例对象，操作日志文件。