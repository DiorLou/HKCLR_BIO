#pragma once
#include "../Interfaces/IPingDevice.h"
#include <memory>
#include <thread>

class AsyncPing : public IPingDevice
{
public:
    AsyncPing();
    ~AsyncPing();

    // 异步PING，并记录数据
    void StartPing(const std::string &ipAddr);

public:
    // 异步记录PING的线程
    void AsyncLogPingData();

    // 记录Ping数据
    void LogPingData();

    // PING命令
    void Ping(int &nSend, int &nRec, double &nLoss, double &minT, double &maxT, double &aveT, const std::string &strIP, int nPackNum /*=4*/);

public:
    std::string m_ipAddr;
    bool m_isPinging;
    std::shared_ptr<std::thread> _pThreadAsyncLogPingData;
};
