#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "WobjGrpc.grpc.pb.h"
#include "IWobj.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class WobjService final : public WobjGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IWobj *_wobj;

public:
    WobjService(IWobj *wobj);
    ~WobjService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取当前工件号
    ::grpc::Status getCurrentId(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::UInt32Value* response) override;
    // 设定当前工件号
    ::grpc::Status SetCurrentId(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::google::protobuf::BoolValue* response) override;
    // 当前工件是否为机器人夹持
    ::grpc::Status currentIsRobotHold(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::WobjGrpc_currentIsRobotHold_Response* response) override;
    // 指定工件是否为机器人夹持
    ::grpc::Status someoneIsRobotHold(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::WobjGrpc_someoneIsRobotHold_Response* response) override;
    // 指定工件是否为固定
    ::grpc::Status someoneIsFixed(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::WobjGrpc_someoneIsFixed_Response* response) override;
    // 获取当前的工件参数
    ::grpc::Status GetCurrentWobjParam(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::WobjGrpc_GetCurrentWobjParam_Response* response) override;
    // 读取工件参数
    ::grpc::Status GetWobjParam(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::WobjGrpc_GetWobjParam_Response* response) override;
    // 设置工件参数
    ::grpc::Status SetWobjParam(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::WobjGrpc_SetWobjParam_Request* request, ::google::protobuf::BoolValue* response) override;
         
#pragma endregion

};

}  // namespace InoRobBusiness
