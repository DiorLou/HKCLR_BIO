#pragma once
#include "IInoRobUtil.h"
#include <memory>

namespace InoRobUtil
{

/**
 * @brief Telnet错误码
 */
enum class TelnetErrorCode
{
    // 正常OK
    OK = 0,
    // 连接失败
    CONNECT_FAILED,
    // 发送信息失败
    SEND_FAILED,
    // 接受消息失败
    RECEIVE_FAILED,
    // 接受消息超时
    RECEIVE_TIMEOUT,
    // 在接受消息时，连接断开了
    DISCONNECT_WHEN_RECEIVING,
    // 触发异常
    CATCH_ERROR,
};

class TelnetClientSocket;
/**
 * @brief Telnet二次封装类，使用boost实现，只针对与机器人控制器的通信，当作局部变量使用
 */
class INOROBUTIL_CLASS TelnetClient
{
public:
    TelnetClient(const std::string &ip);
    ~TelnetClient();

public:
    /**
     * @brief 发送信息到控制器，控制器返回后执行完成，如果输入了期望的回复标识，会同时对控制器的返回进行校验，如果不是期望的，会一直读取，直到超时
     * @param cmd 输入，要发送的信息指令
     * @param targetFlag 输入，期望的回复标识，输入空字符串“”时，不触发校验
     * @param timeoutMs 输入，等待控制器返回超时时间
     * @return 成功返回TelnetErrorCode::OK，其他请查看错误码
     */
    TelnetErrorCode sendCmd(const std::string &cmd, const std::string &targetFlag = "", int timeoutMs = 3000);

    /**
     * @brief 发送信息到控制器，控制器返回后执行完成，同时输出控制器的返回信息，不对信息进行校验
     * @param response 输出，控制器的返回信息
     * @param cmd 输入，要发送的信息指令
     * @param timeoutMs 输入，等待控制器返回超时时间
     * @return 成功返回TelnetErrorCode::OK，其他请查看错误码
     */
    TelnetErrorCode trySendCmd(std::string &response, const std::string &cmd, int timeoutMs = 3000);

    /**
     * @brief 获取控制器处理脚本返回的指令
     */
    std::string getEchoCmd();

    /**
     * @brief 获取控制器通常情况下回复信息的标识，即"[root@Inovance"
     */
    std::string getResponseFlag();

private:
    /**
     * @brief 发送信息到控制器
     * @param cmd 输入，要发送的信息指令
     * @return 成功返回TelnetErrorCode::OK，其他请查看错误码
     */
    TelnetErrorCode writeCmd(const std::string &cmd);

    /**
     * @brief 以阻塞的形式，读取控制器的返回信息
     * @param response 输出，控制器的返回信息
     * @param timeoutMs 输入，等待控制器返回超时时间
     * @param targetFlag 输入，期望的回复标识，输入空字符串“”时，不触发校验
     * @return 成功返回TelnetErrorCode::OK，其他请查看错误码
     */
    TelnetErrorCode readResponseAndCheck(std::string &response, int timeoutMs, const std::string &targetFlag = "");

    /**
     * @brief 登录root权限
     */
    void login(const std::string &ip);

private:
    std::shared_ptr<TelnetClientSocket> _socketObj;  // 套接字对象

    const std::string PORT = "23";                       // 机器人Telnet对应端口号
    const std::string RESPONSE_FLAG = "[root@Inovance";  // 机器人控制器返回标识
    const std::string LOGIN_FLAG = "Inovance login:";    // 机器人控制器登陆输入用户名标识
    const std::string PASSWORD_FLAG = "Password:";       // 机器人控制器登陆输入密码标识
    const std::string LOGIN = "root\n";                  // 机器人控制器登陆用户名
    const std::string PASSWORD = "r\n";                  // 机器人控制器登陆密码
    const std::string ENTER = "\n";                      // 回车
    const std::string ECHO_CMD = "echo $?\n";            // 通常用于获取控制器处理脚本的返回
};

}  // namespace InoRobUtil
