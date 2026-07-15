#pragma once
#include "ISafeParaSettingMgr.h"
#include "DataSrvGlobal.h"
#include "IDataSrvBase.h"
#include "IInoRobBusiness.h"
#include <thread>
#include <memory>

using namespace std;

namespace InoRobBusiness
{
class SafeParaSettingMgrDefault : public ISafeParaSettingMgr
{
public:
    SafeParaSettingMgrDefault();
    SafeParaSettingMgrDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~SafeParaSettingMgrDefault();
    void init() override;
    int QuerySafeParaCabinet() override;
    int QuerySafeParaHardWareExist() override;
    int QuerySafeParaHardWareSynchro() override;
    int QuerySafeParaCabinetProcess(bool printFlag) override;

    int CheckSafeParaPassword() override;
    int CheckSafeParaPassword(const unsigned int password) override;

    int Read(int key, int offset, int num) override;
    int GetSafeParaCommon(int key, int offset, int length, unsigned char* buf, bool forceFlag/* = false*/) override;

    int Write(int *range, int num) override;
    int Write(int key, int offset, int num) override;
    int SetSafeParaCommon(int key, int offset, int length, unsigned char *buf, bool forceFlag  = false) override;

    int CheckAStatus(int8u status = SPS_EDITED) override;
    int CheckAStatus(int key, int offset, int num, int8u status = SPS_EDITED) override;

    int SafeParaMapBuild() override;
    vector<SafeParaMapEle>& GetSafeParaMap() override;

    int SafeToolModeOccupied(const short DO[DO_NUM]) override;

    string GetErrorText(string caption, int ret, int readFlag) override;
    int PrintErrorText(string caption, int ret, int readFlag) override;

    int GetSafeHardVer(string &system, string &moni, string &commu) override;

    int SafeParaReset(unsigned char flag) override;

    int QuerySafeIORealTime(bool switchFlag) override;

    int ExportFunctionSafeParaFile(const string exportRoute) override;
    int ImportFunctionSafeParaFile(const string importRoute) override;

#ifdef COBOT
    int SetInterZoneSendStatus(int8u status = SAFETYINTERZONESENDSTATUS_SENDING) override;

    int WriteSpeedReducing(const S_SPEEDREDUCINGCONF &conf) override;
    int ReadSpeedReducing(S_SPEEDREDUCINGCONF &conf) override;
#endif // COBOT

private:
    /// <summary>
    /// 透传写数据之前, 逻辑/数据 组合
    /// 1. 写密码; 2.组合数据; 3.透传写数据; 4.透传会读数据并校验; 5.安全MCU checkYes; 6.同步命令至DSP
    /// </summary>
    /// <param name="range"></param>
    /// <param name="num"></param>
    /// <returns></returns>
    int WriteDataToMCU(int *range, int num);
    /// <summary>
    /// 透传读取, 含有错误冗余
    /// </summary>
    /// <param name="key"></param>
    /// <param name="offset"></param>
    /// <param name="num"></param>
    /// <param name="checkFlag"></param>
    /// <returns></returns>
    int RecvDataFromMCU(int key, int offset, int num, bool checkFlag /* = false*/);
    /// <summary>
    /// 透传读数据
    /// </summary>
    /// <param name="key"></param>
    /// <param name="offset"></param>
    /// <param name="num"></param>
    /// <param name="checkFlag">true: 回读内容校验; false: 将内容memcpy至上位机内存</param>
    /// <returns></returns>
    int RecvDataFromMCU_Single(int key, int offset, int num, bool checkFlag/* = false*/);
    /// <summary>
    /// 透传写数据
    /// </summary>
    /// <param name="key"></param>
    /// <param name="offset"></param>
    /// <param name="num"></param>
    /// <returns></returns>
    int SendDataToMCU(int key, int offset, int num);
    /// <summary>
    /// 透传写数据之后的同步操作
    /// 对数据地图中所有状态为status的数据执行操作
    /// </summary>
    /// <param name="syncFlag">是否同步</param>
    /// <param name="status">数据地图状态</param>
    /// <returns></returns>
    int SyncToDSP(bool syncFlag, int8u status);
    int SyncToDSP(int key, int offset, int num, bool syncFlag, int8u status);
    /// <summary>
    /// 透传写数据之后的同步操作
    /// 每个数据都要计算出, 相对于同类第0个数据的偏移
    /// </summary>
    /// <param name="syncFlag">是否同步</param>
    /// <param name="commu">透传通讯码, 可在SafeParaMap中获取</param>
    /// <param name="offset">偏移</param>
    /// <returns></returns>
    int SyncToDSPSingle(bool syncFlag, int16u commu, int8u offset);
    /// <summary>
    /// 透传写入的参数, 对安全硬件checkYes
    /// </summary>
    /// <param name="key"></param>
    /// <param name="offset"></param>
    /// <param name="num"></param>
    /// <returns></returns>
    int SyncCheckYes(int key, int offset, int num);
    int SyncCheckYes(int range[], int num);
    /// <summary>
    /// 设置数据地图的状态
    /// </summary>
    int SetSafeParaStatus(int targetStatus);
    int SetSafeParaStatus(int checkStatus, int targetStatus);
    int SetSafeParaStatus(int key, int num, int checkStatus, int targetStatus);
    /// <summary>
    /// 安全数据初始化指令发送
    /// </summary>
    /// <param name="flag"></param>
    /// <returns></returns>
    int SafeParaReset_Send(unsigned char flag);
    /// <summary>
    /// 安全数据初始化进度轮训
    /// </summary>
    /// <param name="flag"></param>
    /// <returns></returns>
    int SafeParaReset_Query(unsigned char &flag);
    /// <summary>
    /// 连接状态变化后续逻辑
    /// </summary>
    void OnConnectionStatusChange(ControllerConnectionStatus status);
    /// <summary>
    // 多线程轮训安全参数初始化进度
    /// <summary>
    void SafeParaReset_Polling();
    /// <summary>
    /// 多线程轮训安全IO 物理电平
    /// <summary>
    void QuerySafeIORealTime_Polling();
    /// <summary>
    /// 对下位机告知上位机型别
    /// <summary>
    int InformWorkStationType();
    /// <summary>
    /// 静态检查修复, 避免10000字节以上堆栈空间
    /// <summary>
    void MemberInit1();
    void MemberInit2();
    void MemberInit3();
public:
    vector<SafeParaMapEle> SafeParaMap;

private:
    //通讯基类指针
    IDataSrvBase* _pDataService;
    // 连接
    IConnection *_pConnection;
    // 监控
    IMonitor *_pMonitor;
    // 互斥锁
    static std::timed_mutex _SafeParaLock;
    static std::timed_mutex _SafeParaResetLock;
    // 功能安全IO线程轮询标志
    static bool _pollingFlag;
    // 功能安全IO轮询线程
    std::shared_ptr<std::thread> _ThreadSafeIO;
};
}

