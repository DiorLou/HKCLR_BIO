#pragma once
#include <string>
#include <vector>
#include "DataTypeDef.h"
#include "dllspec.h"

typedef enum _TRASPRO
{
    UDP = 1,
    TCP = 2
} TRASPRO;

/// <summary>
/// 传输层接口定义类，所有通讯类型应该继承该接口类
/// </summary>
class LINKER_CLASS ICommTransportLayer
{
public:
    virtual ~ICommTransportLayer()
    {
    }
    /// <summary>
    /// 打开传输层
    /// </summary>
    /// <param name="params">用字符串数组表示的参数列表</param>
    /// <returns>返回0则为成功</returns>
    virtual int Open(std::vector<std::string> *params) = 0;

    /// <summary>
    /// 关闭传输层
    /// </summary>
    /// <returns></returns>
    virtual int Close() = 0;

    /// <summary>
    /// 是否处于连接状态
    /// </summary>
    /// <returns>true-连接中，false-已断开</returns>
    virtual bool IsConnected() = 0;

    /// <summary>
    /// 增加错误计数
    /// </summary>
    virtual void AddError()
    {
    }

    /// <summary>
    /// 清除错误计数
    /// </summary>
    virtual void ClearErrorCount()
    {
    }

    /// <summary>
    /// 获取当前错误计数
    /// </summary>
    /// <returns>返回当前错误的计数</returns>
    virtual int ErrorCount() = 0;

    /// <summary>
    /// 是否手动关闭的传输
    /// </summary>
    /// <returns>true-手动关闭；false-错误或断网关闭</returns>
    virtual bool IsClosedByManual() = 0;

    /// <summary>
    /// 获取缓冲的计数
    /// </summary>
    /// <returns>返回当前接收到的BUF长度</returns>
    virtual int BufLength() = 0;

    /// <summary>
    /// 清空缓冲
    /// </summary>
    virtual void ResetBuf() = 0;

    /// <summary>
    /// 发送数据
    /// </summary>
    /// <param name="buffer">数据的buf指针</param>
    /// <param name="len">需要发送的字节数长度</param>
    /// <returns>返回成功发送的数据字节长度</returns>
    virtual int WriteBuf(int8u *const buffer, int len) = 0;

    /// <summary>
    /// 读取数据
    /// </summary>
    /// <param name="buffer">目标数据BUF的指针</param>
    /// <param name="len">需要读取的长度</param>
    /// <param name="timeout">读取超时时间</param>
    /// <returns>成功读取的数据长度</returns>
    virtual int ReadBuf(int8u *const buffer, int len, int32u timeout) = 0;

    /// <summary>
    /// 窥应用缓冲，调用后数据仍然在缓冲BUF中
    /// </summary>
    /// <param name="buffer">窥视后存放数据的目标buf指针</param>
    /// <param name="offset">窥视的偏移值</param>
    /// <param name="len">窥视的长度</param>
    /// <returns>成功窥视的数据长度</returns>
    virtual int PeekBuf(int8u *const buffer, int offset, int len) = 0;

    /// <summary>
    /// 传输层错误码
    /// </summary>
    /// <returns>返回错误码值</returns>
    virtual int ErrorCode() = 0;

    /// <summary>
    /// 设置手动断开标志
    /// </summary>
    /// <param name="bDisconnMaunal">true-表示手动断开</param>
    virtual void SetMaunalDisconect(bool bDisconnMaunal)
    {
    }

    /// <summary>
    /// 连接测试
    /// </summary>
    virtual void TestConnection()
    {
    }

    /// <summary>
    /// 获取打开参数
    /// </summary>
    virtual std::vector<std::string> *GetOpenParams() = 0;

    /// <summary>
    /// 上次通讯成功的时间，以ms为单位
    /// </summary>
    virtual ULONGLONG LastSucessTick() = 0;
};