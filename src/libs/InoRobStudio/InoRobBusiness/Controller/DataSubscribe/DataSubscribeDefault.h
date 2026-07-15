#pragma once

#include <mutex>
#include <map>
#include <thread>
#include "IDataSubscribe.h"
#include "IInoRobBusiness.h"

constexpr int DS_UDP_BUFF_LEN = 10240;  // upd数据buf长度

namespace InoRobBusiness
{
class DataSubscribeDefault : public IDataSubscribe
{
public:
    DataSubscribeDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~DataSubscribeDefault();
    void init() override;
    // 停止订阅，断开连接时需要发送；非正常断开时也需要发送
    bool stop();
    // 订阅某对象
    bool subscribe(IDataSubscriber *subscriber, DataSubscribeReq *reqData);
    // 取消订阅某对象
    bool unsubscribe(int32u objId);
    // 清除所有订阅
    void clearAllSubscibe();
    // 判断是否某对象存在订阅列表当中
    bool existSubscriber(int32u objId);

private:
    IDataSrvBase *_pDataService;
    IConnection *_pConnection;

    // 数据订阅工作线程函数
    void workThread();
    // 启动订阅，重连上后需要重新启动
    bool start();
    /**
     * @brief 发送请求消息
     * @param reqData 请求数据
     * @return true成功 false失败
     */
    bool sendReqMsg(DataSubscribeReq *reqData);
    /**
     * @brief udp发送消息
     * @param buf 消息起始地址
     * @param len  消息长度
     * @return 发送消息长度
     */
    int udpSendTo(int8u *buf, int len);
    /**
     * @brief 读取订阅消息
     * @param buf 存储读取到的消息地址
     * @param len 应该读取消息的长度
     * @return true成功 false失败
     */
    bool readSubscribeData(int8u *buf, int len);

    void onConnectionStatusChanged(ControllerConnectionStatus status);

    std::map<int32u, IDataSubscriber *> _subscribersMap;
    std::thread _thread;
    std::mutex _mapMutex;
    std::mutex _udpMutex;
    unsigned char _recvBuf[DS_UDP_BUFF_LEN] = { 0 };
    unsigned char _sendBuf[DS_UDP_BUFF_LEN] = { 0 };
    bool _isWorking;
};
}  // namespace InoRobBusiness
