#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "RCConfigGrpc.grpc.pb.h"
#include "IRCConfig.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class RCConfigService final : public RCConfigGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IRCConfig *_rcConfig;

public:
    RCConfigService(IRCConfig *rcConfig);
    ~RCConfigService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 读取急停触发方式
    ::grpc::Status readEmgTrigMethod(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::readEmgTrigMethod_Response *response) override;
    // 保存急停触发方式
    // 参数：0-手持示教器触发 1-PC软急停触发
    // 返回：0表示成功，其它表示失败
    ::grpc::Status saveEmgTrigMethod(::grpc::ServerContext *context, const ::google::protobuf::UInt32Value *request, ::google::protobuf::Int32Value *response) override;
    // 保存急停触发方式权限检查
    // 返回：true通过，false未通过
    ::grpc::Status checkPermissionBeforeSaveEmgTrigMethod(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // 设置控制器为服务器或客户端，0-作为客户端，1-作为服务器, 2-作为客户端和服务器
    // 返回：0表示成功，其它表示失败
    ::grpc::Status setControllerAsClientOrServe(::grpc::ServerContext *context, const ::google::protobuf::UInt32Value *request, ::google::protobuf::Int32Value *response) override;

    // 检查控制器USB是否挂载
    ::grpc::Status checkControllerUSBIsConnected(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // 检查配置文件备份与加载权限
    ::grpc::Status checkProfileBackupAndLoadPermission(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    // 系统备份加载：nMark=2为进行中、nMakr=1到10为系统繁忙
    // 系统备份加载返回成功的标志集合{ 61, 71, 81, 91 };
    ::grpc::Status readFileSaveFlag(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // 参数配置文件保存标示
    // 参数： 6-备份配置文件、7-加载配置文件、8-备份程序、9-加载程序
    ::grpc::Status writeFileSaveFlag(::grpc::ServerContext *context, const ::google::protobuf::Int32Value *request, ::google::protobuf::Int32Value *response) override;
    // 保存急停停机方式
    ::grpc::Status saveEmgStopMode(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::saveEmgStopMode_Request *request, ::google::protobuf::Int32Value *response) override;

#pragma endregion
};

}  // namespace InoRobBusiness
