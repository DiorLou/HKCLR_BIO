#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IrSub.h"


namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS SubscriberDefault : public ISubscriber
{
    
public:
    SubscriberDefault(string name, QObject *parent = nullptr);
    ~SubscriberDefault();
    void init() override;

private: // 数据 
    // 连接实例
    IConnection *_pConnection = nullptr;
    // 订阅这实例
    IrSub* m_sub = nullptr;

private:// 槽函数
    void OnRcConnectionChanged(ControllerConnectionStatus status);

private:
    static void OnRecv(std::string content);

};

}
