#pragma once
#include <string.h>
#include "signal_slot.h"
#include "FrameDef.h"
#include "DataSrvGlobal.h"

class IDataService
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
    // virtual int ReadRCStsInfo(RCSTS_INFO& rcStsInfo) = 0;

    // 实时指令帧
    virtual int RealCmdIo(REALTIME_CMD &RealCmd) = 0;

    // 非实时指令帧
    virtual int UnRealCmdIo(UNREALTIME_CMD &UnRealCmd) = 0;

    // 附加数据帧
    virtual int ExtraDataIo(EXTRA_DATA &ExtraData, IO_TYPE nIoType) = 0;
};
