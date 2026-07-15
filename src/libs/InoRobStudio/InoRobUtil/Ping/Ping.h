#pragma once

#ifdef _WIN32

#include <WinSock2.h>
#include "dllspec.h"
#include "IInoRobUtil.h"

#define MAX_ICMP_PACKET 1024  // 最大ICMP大小
class INOROBUTIL_CLASS CPing
{
public:
    CPing(void);
    ~CPing(void);

    // bool CanPing(const char* pDscAddr);
    void ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT,
              const char *pDscAddr, int nPackNum = 4, int nPackSize = 32);

private:
    bool Init();
    bool FInit();
    bool ConstructIcmpMessage(char *pDataBuff, int nDataSize);
    USHORT CheckSum(USHORT *pBuff, int nSize);
    bool DecodeIpPacket(char *pBuff, int nBuffSize, sockaddr_in *pAddr, float &tempTime);
    bool PingHelper(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT,
                    const char *pDscAddr, int nPackNum = 4, int nPackSize = 64);

private:
    SOCKET m_socketRaw;
    bool m_bPrintInfo;
    char _szIcmpData[MAX_ICMP_PACKET] = { 0 };
    char _szRecvBuff[MAX_ICMP_PACKET] = { 0 };
};

#elif __linux__

#define PACKET_SIZE 4096
class CPing
{
public:
    CPing(void);
    ~CPing(void);

    /**
     * @brief linux下的ping功能
     * @param nSend 发送的包数量
     * @param nRec  接收的包数量
     * @param nLoss  丢失率
     * @param minT   最短时间
     * @param maxT   最长时间
     * @param aveT   平均时间
     * @param pDscAddr  IP地址
     * @param nPackNum  发送包的数量
     * @return
     */
    int ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT, const char *pDscAddr, int nPackNum);

private:
    bool Init();
    bool FInit();
    unsigned short cal_chksum(unsigned short *addr, int len);

private:
    int _nSocketd = 0;  // 套接字
    char _sendpacket[PACKET_SIZE] = { 0 };
    char _recvpacket[PACKET_SIZE] = { 0 };
};

#endif
