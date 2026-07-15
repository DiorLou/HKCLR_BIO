#pragma once
#include <mutex>
#include "InoInterfaces.h"
#include "dllspec.h"
#include "FrameDef.h"
#include "../AsyncPing.h"

/* 数据类型定义(开始)
 */

#pragma pack(1)  // 开启单字节对齐

// 通讯返回的的头(通讯版本1.0)
typedef struct tagRespBeginV1_0
{
    tagRespBeginV1_0()
    {
        Type = 0;
        ErroCode = 0;
        FrameNumb = 0;
        CmdId = 0;
    }

    tagRespBeginV1_0 &operator=(const tagRespBeginV1_0 &other)
    {
        this->Type = other.Type;
        this->ErroCode = other.ErroCode;
        this->FrameNumb = other.FrameNumb;
        this->CmdId = other.CmdId;

        return (*this);
    }

    int8u Type;        // 通讯类型
    int16u ErroCode;   // 错误码或者状态码
    int32u FrameNumb;  // 帧号
    int16u CmdId;      // 指令ID
} RESP_BEGIN_V1_0;

#pragma pack()  // 取消单字节对齐

/* 数据类型定义(结束)
 */

class DATASRV_CLASS CommVersion_1_0 : public ICommVersion
{
public:
    CommVersion_1_0(ICommTransportLayer *transportLayer, IPingDevice *pingDev);
    virtual ~CommVersion_1_0();

    /* ICommVersion 接口实现部分(开始)
     */

    // 获取当前的主版本号
    int8u MajorV();

    // 获取当前的次版本号
    int8u MinorV();

    // 实时命令
    int RealCmdIo(REALTIME_CMD &realCmd);

    // 非实时命令
    int UnRealCmdIo(UNREALTIME_CMD &unRealCmd);

    // 附加数据
    int ExtraDataIo(EXTRA_DATA &extraData, IO_TYPE nIoType);

    // 帧错误信息
    RESP_INFO *GetFrameErroCode();

    // 设置单帧超时
    void SetSingleTimeout(int timeOut) { m_singleTimeout = timeOut; }

    /* ICommVersion 接口实现部分(结束)
     */

public:
    /************************************************************************/
    /*一次上下行通讯循环(如果控制器异步处理了，可能发生多次通讯循环)*/
    /************************************************************************/
    // 实时命令
    int RealCmdIoSingle(REALTIME_CMD &realCmd);

    // 非实时命令
    int UnrealCmdIoSingle(UNREALTIME_CMD &unRealCmd);

    // 附加数据
    int ExtraDataIoSingle(EXTRA_DATA &extraData, IO_TYPE nIoType);

    /************************************************************************/
    /*组帧*/
    /************************************************************************/
    // 实时指令
    int PackRealCmd(int8u *pBuf, REALTIME_CMD &realCmd);

    // 非实时指令
    int PackUnRealCmd(int8u *pBuf, UNREALTIME_CMD &unRealCmd);

    // 附加数据
    int PackExtraData(int8u *pBuf, EXTRA_DATA &extraData, IO_TYPE nIoType);

    /************************************************************************/
    /*解帧(开始)*/
    /************************************************************************/

    // 检查上行帧头(实时命令只返回起始部分，非实时命令和大数据：起始部分+其他)
    bool CheckUpHeader(int8u *pBuf);

    // 解析起始部分(当收到的数据字节长度不小于11，才可以解析帧头)
    RESP_BEGIN_V1_0 ParseBeginPart(int8u *pBuf);

    // 检查CRC，bufSize是含校验数据的长度
    bool CheckCrc(int8u *pBuf, int16u bufSize);

    // 非实时指令
    int ParseUnRealCmd(int8u *pBuf, UNREALTIME_CMD &UnRealCmd);

    // 附加数据
    int ParseExtraData(int8u *pBuf, EXTRA_DATA &ExtraData, IO_TYPE nIoType);

    /************************************************************************/
    /*解帧（结束）*/
    /************************************************************************/

    // 设置异步业务超时时间
    void SetAsyncBusinessTimeout(int timeout)
    {
        m_asyncBusinessTimeout = timeout;
    }

private:
    // 其他私有
    // 获取IP地址
    std::string GetIpAddr();

    int64u GetSingleTimeout();

    int64u GetAsyncBusinessTimeout();

    bool IsDectectFrame(UNREALTIME_CMD *cmd);

    void LogCrcErr(int16u cmdId);

    void LogHeaderErr(int16u cmdId);

    void LogAsyncTimeoutErr(int16u cmdId);

    void ResetErrs();

private:
    // 传输层的对象
    ICommTransportLayer *m_transportLayer;

    // 通讯Mutex
    std::mutex _dataIoMutex;

    // 错误信息
    RESP_INFO m_RespInfo;

    // 回应帧的起始部分
    RESP_BEGIN_V1_0 m_respBeginPart;

    // ping指定IP的设备
    IPingDevice *m_asyncPing;

    // IP地址
    std::string m_ipAddr;

    // 单次超时时间
    int64u m_singleTimeout;

    // 异步业务超时时间
    int64u m_asyncBusinessTimeout;

    // CRC错误
    bool m_crcErr;

    // 帧头错误
    bool m_headerErr;

    // 异步超时错误
    bool m_asyncTimeoutErr;

    // 异步忙碌
    bool m_asyncBusy;

    // 异步开始时间
    DWORD m_asyncStartTime;
};
