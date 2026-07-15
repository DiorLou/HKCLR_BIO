#pragma once
#include <vector>
#include <mutex>
#include "dllspec.h"
#include "InoInterfaces.h"

/*************************************************
类名：通讯版本管理器
用途：采用版本机制，与控制器匹配，当主次版本号完全
      匹配时，采用这个版本；
      否则使用最新的大版本号，例如0.0，1.0，2.0；
      比如,TP版本1.3，控制器版本2.1，那么采用1.0；
**************************************************/
class DATASRV_CLASS CommVersionMgr : public ICommVersionMgr
{
public:
    CommVersionMgr(ICommTransportLayer *transportLayer, IPingDevice *pingDev);
    ~CommVersionMgr();

    /*************************************************
    接口类 ICommVersionMgr 各函数
    **************************************************/
    // 打开传输层
    int Open(std::vector<std::string> *params);

    // 关闭传输层
    int Close();

    // 版本匹配
    bool VersionMatch();

    // 是否处于连接状态
    bool IsConnected();

    // 设置手动断开标志
    void SetMaunalDisconect(bool bDisconnMaunal);

    // 是否手动关闭的传输
    bool IsClosedByManual();

    // 获取所包含的最新的主次版本号
    void LatestVersion(int8u &majorV, int8u &minorV);

    // 获取当前的主次版本号（即匹配后的版本号）
    void CurVersion(int8u &majorV, int8u &minorV);

    // 实时命令
    int RealCmdIo(REALTIME_CMD &realCmd);

    // 非实时命令
    int UnRealCmdIo(UNREALTIME_CMD &unRealCmd);

    // 附加数据
    int ExtraDataIo(EXTRA_DATA &extraData, IO_TYPE nIoType);

    // 传输层错误码
    int ErrorCode();

    // 连接测试
    void TestConnection();

    // 错误信息
    RESP_INFO *GetFrameErroCode();

    // 设置单帧超时
    void SetSingleTimeout(int timeOut);

private:
    ICommVersion *GetLatestVersion();

    ICommVersion *GetCurVersion();

private:
    ICommTransportLayer *m_transportLayer;
    IPingDevice *m_pingDev;

    // 旧版本，V0.0
    ICommVersion *m_oldVersion;
    // 当前使用版本
    ICommVersion *m_curVersion;

    // 版本池
    std::vector<ICommVersion *> m_versionPool;

    // 版本池的数据Mutex
    std::mutex _versionPool;

    // 版本匹配的锁
    std::mutex _versionMatch;
};
