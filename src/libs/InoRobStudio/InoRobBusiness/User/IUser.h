/****************************************************************
 * File Descrip : 用户管理基类
 * Author       : ldh
 ****************************************************************/
#pragma once
#include <string.h>
#include <QObject>
#include "signal_slot.h"
#include "dllspec.h"
#include "DataSrvGlobal.h"

class INOROBBUSINESS_CLASS IUser : public QObject
{
    Q_OBJECT

public:
    virtual ~IUser()
    {
    }

    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

    /*!
     * \brief 获取当前用户模式
     * \return 当前用户模式
     */
    virtual EUSER_MODE getCurrentLoginUserMode() = 0;

    /*!
     * \brief 用户登录
     * \param mode 用户模式
     * \param pwd 用户密码
     * \return 0-成功
     */
    virtual int userLogin(const EUSER_MODE &mode, const std::string &pwd) = 0;

    /*!
     * \brief 获取登录状态
     * \return true-已登录
     */
    virtual bool getLoginState() = 0;

    /*!
     * \brief 注销当前登录的用户
     * \return 0-成功
     */
    virtual int userLogOut() = 0;

    /*!
     * \brief 修改用户密码
     * \param mode 用户模式
     * \param pwd 用户密码
     * \return 0-成功
     */
    virtual int modifyUserPassWord(const EUSER_MODE &mode, const std::string &pwd) = 0;

    /**
     * @brief 设置开发者调试状态
     * @param state 状态
     * @return 0-成功
     */
    virtual int setDevelopDebugState(const DEVELOPER_DEBUG &state) = 0;

    /**
     * @brief 获取开发者调试状态
     * @return 状态信息
     */
    virtual DEVELOPER_DEBUG getDevelopDebugState() = 0;

    /**
     * @brief 验证用户密码
     * @param mode 用户类型
     * @param pwd 密码
     * @return true验证通过 false验证不通过
     */
    virtual bool verifyUserPassword(const EUSER_MODE mode, const std::string &pwd) = 0;
    /**
     * @brief 读取管理模式下密码
     * @USER_PWD 返回值带密码
     * @return 0读取成功 非0读取失败
     */
    virtual int readManagerPwd(USER_PWD &pwd) = 0;

Q_SIGNALS:  // 尽量不使用下方Qt信号
    /*!
     * \brief 用户登录信号
     * \param mode 用户模式
     */
    void sigLogin(int mode);

    /*!
     * \brief 用户登出信号
     */
    void sigLogOut();
};
