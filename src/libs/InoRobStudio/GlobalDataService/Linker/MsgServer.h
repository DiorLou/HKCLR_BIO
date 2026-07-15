#pragma once

/*
 * MsgServer.h
 *
 * Created on: 2021/7/23
 * Author: Xiong Riwei
 */

#include "dllspec.h"
#include "signal_slot.h"
#include "DataTypeDef.h"
#include "LHBCircleBuffer.hpp"

// 消息服务器信号数据
struct MsSignalData
{
    unsigned char *data;
    int len;

    void Init()
    {
        data = NULL;
        len = 0;
    }
};

class MsgServer_imp;

// 消息服务器(给外部提供消息)
class LINKER_CLASS MsgServer
{
public:
    MsgServer(void);
    virtual ~MsgServer(void);

    void Active(int port);            // 消息服务工作
    void Deactive();                  // 消息服务器停止
    bool IsActive();                  // 是否处于激活状态
    int Output(char *msg, int len);   // 消息输出
    int CmdResp(char *msg, int len);  // 对远程命令回应，回应格式 =>xxxx\r\n

    rsignal<MsSignalData> DataReceived;  // 数据已接收
private:
    void WorkThread();  // 消息服务器的工作线程

    // 对环形BUF解包，如果解出一个完整包则返回true
    // 数据包形式如下:
    // Begin\r\n
    // Controller.IP\r\n
    // JsonStr\r\n
    // End\r\n
    bool Unpack();

private:
    bool _exitMsgWorkThread = true;
    bool m_msgServerEnable = false;
    bool m_bClientWorking = false;
    int m_msgServerPort = 0;

    // 收到的数据
    MsSignalData m_signalData;

    // 接收解包后的数据
    int8u *m_recvData = nullptr;

private:
    MsgServer_imp *_pImp;
};
