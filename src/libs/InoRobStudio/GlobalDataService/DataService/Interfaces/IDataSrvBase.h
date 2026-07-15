#pragma once
#include <string.h>
#include "signal_slot.h"
#include "FrameDef.h"
#include "DataSrvGlobal.h"

class IDataSrvBase
{
public:
    // 打开设备
    virtual int OpenDev(string strIP, int nPort) = 0;

    // 关闭设备
    virtual int CloseDev() = 0;

    // 设备在线状态
    virtual bool IsDevOnline() = 0;

    // 心跳或获取实时数据失败时需要进行的测试连接
    virtual void TestConnection() = 0;
    // 链路测试(心跳检测)
    virtual int SendDetectFrame() = 0;

    /*读初始化完成状态，nState：
     * -1
     * 0		系统开始启动
     * 1		示教器通信连接成功
     * 2		示教器通信连接成功
     * 3		正在配置DSP参数
     * 4		正在初始化EtherCAT参数
     * 5		正在初始化IRLink
     * 6		正在启动视觉线程
     * 7		正在启动DSP通信线程
     * 8		正在初始化DSP数据
     * 9		正在完成控制器启动
     * 11	控制器启动成功 ★
     * 12	正在读取系统数据
     * 100
     * 101
     */
    virtual int ReadInitState(int &nState) = 0;

    // 获取控制器实时数据
    virtual int ReadRCStsInfo(RCSTS_INFO &rcStsInfo) = 0;

    // 实时指令帧
    virtual int RealCmdIo(REALTIME_CMD &RealCmd) = 0;

    // 非实时指令帧
    virtual int UnRealCmdIo(UNREALTIME_CMD &UnRealCmd) = 0;

    // 附加数据帧
    virtual int ExtraDataIo(EXTRA_DATA &ExtraData, IO_TYPE nIoType) = 0;

    virtual int WriteTasksActiveState(int8u flags[4]) = 0;

    // 上传文件
    // virtual int FtpUpLoadFile(CString strControlFullPath, CString strLocalPath) = 0;

    // 读取文件
    virtual int ReadFileOthers(string strFileSrc, string strFileDest, bool bCreat = false) = 0;

    // 写.pro以外的其他文件
    virtual int WriteFileOthers(string strFileSrc, string strFileDest) = 0;

    //获取设备端文件的MD5
    virtual int GetControllerFileMD5(string strFileSrc, char ans[32]) = 0;

    //比较设备端和本地文件的MD5
    virtual bool CompareControllerAndLoccalFileMd5(string strFileSrc, string strFileDest) = 0;

    // 读取网口IP信息
    virtual int ReadEthConfig(ControllerEthCfg &EthCfg) = 0;

    // 获取机型
    virtual UINT16 GetActualAxisNum(UINT16 u16RobotType) = 0;

    // 初始化读取，只在连接成功后进行一次读取
    virtual int ReadInitData(INIT_DATA &InitData) = 0;

    // 初始化读取，只在连接成功后进行一次读取
    virtual int ReadInitData_0322(INIT_DATA_0322 &InitData) = 0;

    // 22 版本最新实时命令读取
    // 只在主线程和连接成功读取 调用该函数读取
    virtual int ReadRCStsInfo_0322(RCSTS_INFO_0322 &rcStsInfo) = 0;

    // 非实时指令：读数据
    virtual int UnRealReadData(double &dbOutput, const int16u nCmdId) = 0;
    virtual int UnRealReadData(int &nOutput, const int16u nCmdId) = 0;

    // 非实时指令：写数据
    virtual int UnRealWriteData(const double dbInput, const int16u nCmdId) = 0;
    virtual int UnRealWriteData(const int nInput, const int16u nCmdId) = 0;

    // UDP
    // udp发送数据
    virtual int UdpSendTo(int8u *const buffer, int iLen) = 0;
    // get UDP frame data from buffer
    virtual int PeekUdpBuf(int8u *const buffer, int32u offset, int32u len) = 0;
    // udp读取数据
    virtual int UdpReadData(int8u *const buffer, int len, int32u timeout = 3000) = 0;
    // udp读取数据个数
    virtual int32u UdpDataCount() = 0;
    // 初始化udp客户端
    virtual int InitUdpClient(string strIpAddress, unsigned short usPort) = 0;
    virtual int UnInitUdpClient() = 0;

    // 设置单帧超时
    virtual void SetSingleTimeout(int timeOut) = 0;
	
	// 读取机器人控制系统运行模式
    virtual int ReadTestMode_RC(int &nMode) = 0;

    #pragma region 插件接口

    // 插件WRITE文本
    // request 请求内容（注：长度不超过 864 * 32 - 1）
    virtual int PluginTextWrite(const string &request) = 0;
    // 插件READ文本
    // request 请求内容（注：仅支持ASCII，长度不超过 864 - 1）
    // response 响应内容（注：仅支持ASCII，长度不超过 864 * 32 - 1）
    virtual int PluginTextRead(const string &request, string &response) = 0;

    // 插件WRITE二进制
    // name 结构体名称（仅支持ASCII，长度不超过 24 - 1）
    // request 请求内容，不能为空，需要将结构体转换为字节流，长度不超过 840 * 32）
    //         注1：结构体中不能包含不定长成员，比如string成员，指针等
    //         注2：结构体使用4字节对齐
    virtual int PluginBinaryWrite(const string &name, vector<char> &request) = 0;
    // 插件READ二进制
    // name 结构体名称（注：仅支持ASCII，长度不超过24 - 1）
    // responseLength 指定接收数据的长度（提供结构体的字节大小，通信按该大小分帧读取数据，不大于 840 * 32）
    // response 响应内容（注：结构体中不能包含不定长成员，比如string成员，指针等）
    virtual int PluginBinaryRead(const string &name, int responseLength, vector<char> &response) = 0;

#pragma endregion
    // 通知机型参数文件更新
    virtual int RobotParamFileChange(char *info) = 0;
    // 启动伺服监控
    virtual int RobotParamServoStart(char *info) = 0;
    // 停止伺服监控
    virtual int RobotParamServoStop() = 0;
    // 获取当前伺服参数数据
    virtual int RobotParamServoCurrent(string &info) = 0;
    // 读取参数更新状态
    virtual int RobotParamUpdateStatusRead(string &info) = 0;

};

