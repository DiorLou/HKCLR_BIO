#pragma once
#include <mutex>
#include "InoInterfaces.h"
#include "dllspec.h"
#include "FrameDef.h"
#include "../AsyncPing.h"
#include "DataLog.h"

class DATASRV_CLASS CommVersion_0_0 : public ICommVersion
{
public:
    CommVersion_0_0(ICommTransportLayer *transportLayer, IPingDevice *pingDev);
    virtual ~CommVersion_0_0();

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
    void SetSingleTimeout(int timeOut) { return; }

    /* ICommVersion 接口实现部分(结束)
     */

private:
    /************************************************************************/
    /*组帧*/
    /************************************************************************/
    // 实时指令
    int PackRealCmd(int8u *pBuf, REALTIME_CMD &realCmd);

    // 非实时指令
    int PackUnRealCmd(int8u *pBuf, UNREALTIME_CMD &unRealCmd);

    // 附加数据
    int PackExtraData(int8u *pBuf, EXTRA_DATA &extraData);

    /************************************************************************/
    /*解帧*/
    /************************************************************************/
    // 检查上行帧头
    bool CheckUpHeader(int8u *pBuf);

    // 检查上行帧头与通讯ID
    bool CheckUpHeaderAndId(int8u *pBuf, int16u id);

    // 实时指令
    int ParseRealCmd(int8u *pBuf, RESP_INFO &RespInfo);

    // 非实时指令
    int ParseUnRealCmd(int8u *pBuf, UNREALTIME_CMD &UnRealCmd, RESP_INFO &RespInfo);

    // 附加数据
    int ParseExtraData(int8u *pBuf, EXTRA_DATA &ExtraData, RESP_INFO &RespInfo, IO_TYPE nIoType);

    /************************************************************************/
    /*解帧*/
    /************************************************************************/
    // 其他私有
    int ReadExtraEcho(int8u *pBuf, int &nLen, IO_TYPE nIoType, int nCmdId);

    // 获取IP地址
    std::string GetIpAddr();

    bool IsDectectFrame(UNREALTIME_CMD *cmd);

private:
    // 传输层的对象
    ICommTransportLayer *m_transportLayer;

    // 通讯Mutex
    std::mutex _dataIoMutex;

    // 错误信息
    RESP_INFO m_RespInfo;

    // ping指定IP的设备
    IPingDevice *m_asyncPing;

    // IP地址
    std::string m_ipAddr;
};
