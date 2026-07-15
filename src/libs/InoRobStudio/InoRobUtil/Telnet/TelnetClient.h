#pragma once
#include "Include/IUtil.h"
#include <mutex>
#include <string>
#include <thread>
#include <boost/asio.hpp>

namespace InoRobUtil
{
class INOROBUTIL_CLASS TelnetClientV2 {
public:
    TelnetClientV2(const std::string &host, const std::string &port);
    ~TelnetClientV2();

    bool connect();

    bool login(const std::string &username, const std::string &password);
    void logout();

    bool copy_files(const std::string &remote_src_files,
                   const std::string &remote_dst_file_path);

private:
    std::string make_command(std::vector<std::string> strings);

    void process_command(const std::string &cmd);
    bool process_command(const std::string &cmd, const std::string &waitMsg);

    void send(const std::string &cmd);
    bool waitForRsp(const std::string &msg);

    void waitTime(int millonSeconds);

private:
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::ip::tcp::resolver _resolver;
    boost::asio::ip::tcp::resolver::results_type _endpoints;

    static const int _tryCnt;                // 重试次数
    static const std::string _loginFlag;     // 登录提示
    static const std::string _passWordFlag;  // 密码提示
    static const std::string _userFlag;      // 用户提示
};

} // namespace InoRobUtil
