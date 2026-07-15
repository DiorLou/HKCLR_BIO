#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "UserGrpc.grpc.pb.h"
#include "IUser.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class UserService final : public UserGrpc::Service
{
#pragma region 数据转换

public:
    static EUSER_MODE_Grpc EUSER_MODE_ToGrpc(EUSER_MODE eUSER_MODE);
    static EUSER_MODE EUSER_MODE_FromGrpc(EUSER_MODE_Grpc eUSER_MODE_Grpc);

    static DEVELOPER_DEBUG_Grpc DEVELOPER_DEBUG_ToGrpc(DEVELOPER_DEBUG developer_DEBUG);
    static DEVELOPER_DEBUG DEVELOPER_DEBUG_FromGrpc(DEVELOPER_DEBUG_Grpc developer_DEBUG_Grpc);

    static bool USER_PWD_ToGrpc(const USER_PWD &user_PWD, USER_PWD_Grpc &user_PWD_Grpc);
    static bool USER_PWD_FromGrpc(const USER_PWD_Grpc &user_PWD_Grpc, USER_PWD &user_PWD);

#pragma endregion

#pragma region 构造与析构

private:
    IUser *_user;

public:
    UserService(IUser *user);
    ~UserService();

#pragma endregion

#pragma region 业务逻辑

public:
    // !
    // \brief 获取当前用户模式
    // \return 当前用户模式
    ::grpc::Status getCurrentLoginUserMode(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getCurrentLoginUserMode_Response* response) override;
    // !
    // \brief 用户登录
    // \param mode 用户模式
    // \param pwd 用户密码
    // \return 0-成功
    ::grpc::Status userLogin(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::userLogin_Request* request, ::google::protobuf::Int32Value* response) override;
    // !
    // \brief 获取登录状态
    // \return true-已登录
    ::grpc::Status getLoginState(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // !
    // \brief 注销当前登录的用户
    // \return 0-成功
    ::grpc::Status userLogOut(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // !
    // \brief 修改用户密码
    // \param mode 用户模式
    // \param pwd 用户密码
    // \return 0-成功
    ::grpc::Status modifyUserPassWord(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::modifyUserPassWord_Request* request, ::google::protobuf::Int32Value* response) override;
    // *
    // @brief 设置开发者调试状态
    // @param state 状态
    // @return 0-成功
    ::grpc::Status setDevelopDebugState(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::setDevelopDebugState_Request* request, ::google::protobuf::Int32Value* response) override;
    // *
    // @brief 获取开发者调试状态
    // @return 状态信息
    ::grpc::Status getDevelopDebugState(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getDevelopDebugState_Response* response) override;
    // *
    // @brief 验证用户密码
    // @param mode 用户类型
    // @param pwd 密码
    // @return true验证通过 false验证不通过
    ::grpc::Status verifyUserPassword(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::verifyUserPassword_Request* request, ::google::protobuf::BoolValue* response) override;
    // *
    // @brief 读取管理模式下密码
    // @USER_PWD 返回值带密码
    // @return 0读取成功 非0读取失败
    ::grpc::Status readManagerPwd(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::readManagerPwd_Response* response) override;

#pragma endregion
};

}  // namespace InoRobBusiness
