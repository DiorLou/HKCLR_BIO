#pragma once
#include <string>
#include "dllspec.h"
#include "LHBCircleBuffer.hpp"
#include "Interfaces/ICommTransportLayer.h"

class UdpTransportLayer_imp;
class LINKER_CLASS UdpTransportLayer : public ICommTransportLayer
{
public:
    UdpTransportLayer();
    ~UdpTransportLayer();

    /// <summary>
    /// 打开传输层
    /// </summary>
    /// <param name="params">用字符串数组表示的参数列表</param>
    /// <returns>返回0则为成功</returns>
    int Open(std::vector<std::string> *params);

    /// <summary>
    /// 关闭传输层
    /// </summary>
    /// <returns></returns>
    int Close();

    /// <summary>
    /// 是否处于连接状态
    /// </summary>
    /// <returns>true-连接中，false-已断开</returns>
    bool IsConnected();

    /// <summary>
    /// 增加错误计数
    /// </summary>
    void AddError();

    /// <summary>
    /// 清除错误计数
    /// </summary>
    void ClearErrorCount();

    /// <summary>
    /// 获取当前错误计数
    /// </summary>
    /// <returns>返回当前错误的计数</returns>
    int ErrorCount();

    /// <summary>
    /// 是否手动关闭的传输
    /// </summary>
    /// <returns>true-手动关闭；false-错误或断网关闭</returns>
    bool IsClosedByManual();

    /// <summary>
    /// 获取缓冲的计数
    /// </summary>
    /// <returns>返回当前接收到的BUF长度</returns>
    int BufLength();

    /// <summary>
    /// 清空缓冲
    /// </summary>
    void ResetBuf();

    /// <summary>
    /// 发送数据
    /// </summary>
    /// <param name="buffer">数据的buf指针</param>
    /// <param name="len">需要发送的字节数长度</param>
    /// <returns>返回成功发送的数据字节长度</returns>
    int WriteBuf(int8u *const buffer, int len);

    /// <summary>
    /// 读取数据
    /// </summary>
    /// <param name="buffer">目标数据BUF的指针</param>
    /// <param name="len">需要读取的长度</param>
    /// <param name="timeout">读取超时时间</param>
    /// <returns>成功读取的数据长度</returns>
    int ReadBuf(int8u *const buffer, int len, int32u timeout);

    /// <summary>
    /// 窥应用缓冲，调用后数据仍然在缓冲BUF中
    /// </summary>
    /// <param name="buffer">窥视后存放数据的目标buf指针</param>
    /// <param name="offset">窥视的偏移值</param>
    /// <param name="len">窥视的长度</param>
    /// <returns>成功窥视的数据长度</returns>
    int PeekBuf(int8u *const buffer, int offset, int len);

    /// <summary>
    /// 传输层错误码
    /// </summary>
    /// <returns>返回错误码值</returns>
    int ErrorCode();

    /// <summary>
    /// 设置手动断开标志
    /// </summary>
    /// <param name="bDisconnMaunal">true-表示手动断开</param>
    void SetMaunalDisconect(bool bDisconnMaunal);

    /// <summary>
    /// 连接测试
    /// </summary>
    void TestConnection();

    /// <summary>
    /// 获取打开参数
    /// </summary>
    std::vector<std::string> *GetOpenParams()
    {
        return &m_openParams;
    }

    /// <summary>
    /// 上次通讯成功的时间，以ms为单位
    /// </summary>
    ULONGLONG LastSucessTick()
    {
        return m_LastSucessTick;
    };

    // 写缓冲区
    uint WriteDataToCirleBuf(const char *data, size_t size);

private:
    void UdpWorkThread();

    void UdpThreadRelease();

private:
    // UDP client circle buffer
    CLHBCircleBuffer m_BufferUdpClient;

    bool m_bOnReadUdpClient = false;
    bool m_bUdpStop = false;
    bool m_bDisconnMaunal = false;

    // 嵌套字错误
    int m_iWSAErrCode = 0;

    std::string _ip;
    std::string _port;

    // 打开参数
    std::vector<std::string> m_openParams;

    // 上次通讯成功的时间，以ms为单位
    ULONGLONG m_LastSucessTick = 0;

    std::shared_ptr<std::thread> _pUdpWorkThread;
    bool _exitUdpWorkThread = true;

private:
    std::shared_ptr<UdpTransportLayer_imp> _pImp;
};
