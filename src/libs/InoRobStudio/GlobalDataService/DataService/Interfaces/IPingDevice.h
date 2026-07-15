#pragma once
#include <string>

// PING设备的接口类
class IPingDevice
{
public:
    virtual ~IPingDevice()
    {
    }
    // 启动PING
    virtual void StartPing(const std::string &ipAddr) = 0;
};
