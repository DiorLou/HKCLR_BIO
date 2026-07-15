#pragma once
#include <string>
#include <thread>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RCSchedulerDefault : public IRCScheduler
{
public:
    RCSchedulerDefault(string name, QObject *parent = nullptr);
    ~RCSchedulerDefault();
    void init() override;
    void registerSchedulerUser(IRCSchedulerUser *user);

    void unregisterSchedulerUser(IRCSchedulerUser *user);

    /// <summary>
    /// 线程执行函数
    /// </summary>
    void workThread();

private:
    std::shared_ptr<std::thread> _pThread;
    std::vector<IRCSchedulerUser *> _schedulerUsers;
    bool _usersChanged = false;
    bool _exitWorkThread = true;
};
}  // namespace InoRobBusiness
