/****************************************************************
 * File Descrip : 用户管理
 * Author       : ldh
 ****************************************************************/
#pragma once
#include "IUser.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS User : public IUser
{
    Q_OBJECT

public:
    User(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~User();

    void init() override;
    EUSER_MODE getCurrentLoginUserMode() override;
    int userLogin(const EUSER_MODE &mode, const std::string &pwd) override;
    int userLogOut() override;
    int modifyUserPassWord(const EUSER_MODE &mode, const std::string &pwd) override;
    bool getLoginState() override;

    int setDevelopDebugState(const DEVELOPER_DEBUG &state) override;
    DEVELOPER_DEBUG getDevelopDebugState() override;

    bool verifyUserPassword(const EUSER_MODE mode, const std::string &pwd) override;
    int readManagerPwd(USER_PWD &pwd);
private:
    // 控制器网络连接状态变更信号处理
    void onConnectionStatusChanged(ControllerConnectionStatus status);
    int readUserPwd(USER_PWD &pwd);
    int writeUserPwd(const USER_PWD &UserPwd);

    IDataSrvBase *_pDataService;
    IConnection *_pConnection;
    EUSER_MODE _curSysLoginMode = USER_CUSTOMER;      // 用户登录权限
    int8u _pwdContent[ALL_PWD_SIZE];                  // 用户密码数据
    DEVELOPER_DEBUG _currDevDebug = DEVELOPER_CLOSE;  // 开发调试模式状态
};

}  // namespace InoRobBusiness
