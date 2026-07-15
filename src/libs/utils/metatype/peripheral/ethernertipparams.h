#pragma once

// EthernetIp 写入状态
typedef struct _COBOT_ETHERNET_IP_PARA_
{
    _COBOT_ETHERNET_IP_PARA_()
    {
        ActiveCmd = 0;  // 0表示关闭
    }
    unsigned char ActiveCmd;  // 0表示关闭，1表示激活
} CobotEthernetIpPara;

// EthernetIp 读取状态
typedef struct _COBOT_ETHERNET_IP_STS_
{
    _COBOT_ETHERNET_IP_STS_()
    {
        ActiveSts = 0;  // 0-未开启
        ConnectSts = 0;
        for (int i = 0; i < 16; i++)
        {
            MsterIp[i] = 0;  // 0-未连接
        }
        MasterPort = 502;   // EIP主站(客户端)的端口
        SlavePort = 44818;  // 固定为44818
    }
    unsigned char ActiveSts;    // EIP激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;   // EIP连接状态:0-未连接，1-已连接
    char MsterIp[16];           // EIP主站(客户端)IP地址
    unsigned short MasterPort;  // EIP主站(客户端)的端口
    unsigned short SlavePort;   // EIP从站(服务器)端口,暂时固定为44818
} CobotEthernetIpSts;
