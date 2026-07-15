#pragma once
#include <vector>
#include <string>
#include "FrameDef.h"
#include "ICommVersion.h"

// 通讯版本管理器的接口定义
class DATASRV_CLASS ICommVersionMgr
{
public:
    virtual ~ICommVersionMgr()
    {
    }

    // 打开传输层
    virtual int Open(std::vector<std::string> *params) = 0;

    // 关闭传输层
    virtual int Close() = 0;

    // 版本匹配
    virtual bool VersionMatch() = 0;

    // 是否处于连接状态
    virtual bool IsConnected() = 0;

    // 设置手动断开标志
    virtual void SetMaunalDisconect(bool bDisconnMaunal)
    {
    }

    // 是否手动关闭的传输
    virtual bool IsClosedByManual() = 0;

    // 获取所包含的最新的主次版本号
    virtual void LatestVersion(int8u &majorV, int8u &minorV)
    {
    }

    // 获取当前的主次版本号（即匹配后的版本号）
    virtual void CurVersion(int8u &majorV, int8u &minorV)
    {
    }

    // 实时命令
    virtual int RealCmdIo(REALTIME_CMD &realCmd) = 0;

    // 非实时命令
    virtual int UnRealCmdIo(UNREALTIME_CMD &unRealCmd) = 0;

    // 附加数据
    virtual int ExtraDataIo(EXTRA_DATA &extraData, IO_TYPE nIoType) = 0;

    // 传输层错误码
    virtual int ErrorCode() = 0;

    // 连接测试
    virtual void TestConnection()
    {
    }

    // 错误信息
    virtual RESP_INFO *GetFrameErroCode() = 0;

    // 设置单帧超时
    virtual void SetSingleTimeout(int timeOut) = 0;
};