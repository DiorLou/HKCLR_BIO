#pragma once
#include "IRCSchedulerUser.h"
#include <QObject>

namespace InoRobBusiness
{
/*
    控制器调度：需要控制器持续执行一段时间的业务逻辑
    Create by WuJian at 2023/8/10 创建。
*/
class INOROBBUSINESS_CLASS IRCScheduler : public QObject
{
    Q_OBJECT
public:
    virtual ~IRCScheduler()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /// <summary>
    /// 注册RC调度使用者
    /// </summary>
    /// <param name="user">使用者</param>
    virtual void registerSchedulerUser(IRCSchedulerUser *user) = 0;

    /// <summary>
    /// 注销RC调度使用者
    /// </summary>
    /// <param name="user">使用者</param>
    virtual void unregisterSchedulerUser(IRCSchedulerUser *user) = 0;
};
}  // namespace InoRobBusiness
