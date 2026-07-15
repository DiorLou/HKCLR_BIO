#pragma once
#include "FrameDef.h"

// 通讯版本的接口定义
class ICommVersion
{
public:
    // 获取当前的主版本号
    virtual int8u MajorV() = 0;

    // 获取当前的次版本号
    virtual int8u MinorV() = 0;

    // 实时命令
    virtual int RealCmdIo(REALTIME_CMD &realCmd) = 0;

    // 非实时命令，不需要连接时是指在建立连接时的命令
    virtual int UnRealCmdIo(UNREALTIME_CMD &unRealCmd) = 0;

    // 附加数据
    virtual int ExtraDataIo(EXTRA_DATA &extraData, IO_TYPE nIoType) = 0;

    // 错误信息
    virtual RESP_INFO *GetFrameErroCode() = 0;

    // 设置单帧超时
    virtual void SetSingleTimeout(int timeOut) = 0;
};