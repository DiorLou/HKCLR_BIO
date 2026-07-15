#pragma once
#include "DataSrvGlobal.h"
#include "LHBConvert.hpp"

enum LOG_LEVEL
{
    LOG_OFF = 0,   // 关闭日志
    LOG_INFO = 1,  // 打印普通调试信息,错误信息
    LOG_BUF = 2,   // 打印IO数据流
};

class CDataLog
{
public:
    CDataLog(void);
    virtual ~CDataLog(void);

public:
    /*
    功能:数据指令或函数功能描述
    参数:
      nCmdId:指令ID
      nRWFlag: 仅用于标识非实时指令读或写
    */
    void OutCmd(int nCmdId, int nRWFlag = -1);

    /*
    功能: 输出字节流信息
    参数:
        nIoType:上行帧, 下行帧标识
    */
    void OutIoData(int8u *pBuf, int nLen, int nIoType);

    /*
    功能: 输出普通调试信息
    */
    void OutInfo(const char *szBuf);

    /*
    功能: 输出错误描述
    */
    void OutErro(int nErroCode);

    // 错误码描述
    string GetErroDescribe(int nErroCode);

private:
    string GetFuncDescribe(int nCmdId, int nRWFlag);  // 功能描述
    string GetRealDescribe(int nCmdId);               // 实时指令
    string GetUnRealFuncDescribe(int nCmdId);         // 非实时指令
    string GetExtraDescribe(int nCmdId);              // 附加数据

private:
    CConvert m_Convert;
    int m_nLogLevel;
};
