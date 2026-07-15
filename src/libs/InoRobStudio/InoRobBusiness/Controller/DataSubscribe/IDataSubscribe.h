#pragma once

#include <QObject>
#include <string>
#include <vector>
#include "dllspec.h"
#include "IDataSubscriber.h"
#include "DataSubscribeTypes.h"

namespace InoRobBusiness
{
/**
 * @brief  数据订阅
 *
 * @todo 数据订阅枚举、结构体优化
 *       数据订阅接受、发送数据代码逻辑、及接口优化
 *       保存订阅者数据类型优化
 */
class INOROBBUSINESS_CLASS IDataSubscribe : public QObject
{
    Q_OBJECT

public:
    virtual ~IDataSubscribe()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**
     * @brief 停止订阅
     * @return true成功 false失败
     */
    virtual bool stop() = 0;

    /**
     * @brief 订阅
     * @param subscriber 订阅者
     * @param reqData 订阅请求数据
     * @return true成功 false失败
     */
    virtual bool subscribe(IDataSubscriber *subscriber, DataSubscribeReq *reqData) = 0;

    /**
     * @brief 取消订阅
     * @param objId 订阅者ID
     * @return true成功 false失败
     */
    virtual bool unsubscribe(int32u objId) = 0;

    /**
     * @brief 清除所有订阅
     */
    virtual void clearAllSubscibe() = 0;

    /**
     * @brief 通过对象id判断是否已经订阅
     * @param objId 对象id
     * @return true订阅 false没有订阅
     */
    virtual bool existSubscriber(int32u objId) = 0;
};
}  // namespace InoRobBusiness
