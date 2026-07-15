#pragma once

#include <string>
#include <mutex>
#include "dllspec.h"

class INOROBBUSINESS_CLASS VirtualControllerDeviceManager
{
public:
    static VirtualControllerDeviceManager* instance();
    
    // 设置当前虚拟控制器设备名称
    void setDeviceName(const std::string& deviceName);
    
    // 获取当前虚拟控制器设备名称
    std::string getDeviceName() const;
    
    // 检查是否已设置设备名称
    bool hasDeviceName() const;
    
    // 获取虚拟控制器路径
    std::string getVirtualControllerPath() const;
    std::string getVirtualControllerTeachProgramPath() const;
    
private:
    VirtualControllerDeviceManager() = default;
    ~VirtualControllerDeviceManager() = default;
    
    VirtualControllerDeviceManager(const VirtualControllerDeviceManager&) = delete;
    VirtualControllerDeviceManager& operator=(const VirtualControllerDeviceManager&) = delete;
    
private:
    mutable std::mutex m_mutex;
    std::string m_deviceName;
    const std::string DEFAULT_DEVICE_NAME = "xiezuo";
};
