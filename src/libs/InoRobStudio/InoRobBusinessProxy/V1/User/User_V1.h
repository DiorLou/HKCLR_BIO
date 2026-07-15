#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
// 用户管理（已查）
class INOROBBUSINESSPROXY_CLASS User_V1 : public QObject
{
    Q_OBJECT
#pragma region 构造与析构

private:
    IUser *_user = nullptr;

public:
    User_V1(IUser *user);
    ~User_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取当前用户模式（已测）
    EUSER_MODE_V1 GetCurrentLoginUserMode();
    // 用户登录
    int UserLogin(const EUSER_MODE_V1 &mode, const std::string &pwd);
    // 获取登录状态
    bool GetLoginState();
    // 注销当前登录的用户
    int UserLogOut();
    // 修改用户密码
    int ModifyUserPassWord(const EUSER_MODE_V1 &mode, const std::string &pwd);
    // 设置开发者调试状态
    int SetDevelopDebugState(const DEVELOPER_DEBUG_V1 &state);
    // 获取开发者调试状态
    DEVELOPER_DEBUG_V1 GetDevelopDebugState();
    // 验证用户密码
    bool VerifyUserPassword(const EUSER_MODE_V1 mode, const std::string &pwd);
    // 读取管理模式下密码
    int ReadManagerPwd(USER_PWD_V1 &pwd_V1);

    // 用户登录信号
    rsignal<int> sigUserLogin;
    // 用户登出信号
    rsignal<int> sigUserLogOut;

private:
    // 用户登陆信号转换
    void sigUserLoginHandler(int sigUserLoginData);
    // 用户登出信号转换
    void sigUserLogOutHandler();

#pragma endregion
};

}  // namespace InoRobBusinessProxy
