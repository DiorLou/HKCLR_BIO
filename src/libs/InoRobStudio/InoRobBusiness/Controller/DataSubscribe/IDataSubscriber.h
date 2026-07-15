#pragma once

#include <string>

namespace InoRobBusiness
{
/**
 * @brief 数据订阅订阅者
 */
class IDataSubscriber
{
public:
    /**
     * @brief 处理收到的订阅数据
     */
    virtual void recvSubscribeData(unsigned int, std::string)
    {
    }
};
}  // namespace InoRobBusiness
