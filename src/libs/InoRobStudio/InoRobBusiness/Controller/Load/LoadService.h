#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "LoadGrpc.grpc.pb.h"
#include "ILoad.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class LoadService final : public LoadGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    ILoad *_load;

public:
    LoadService(ILoad *load);
    ~LoadService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 设定当前负载号
    ::grpc::Status SetCurrentId(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::google::protobuf::BoolValue* response) override;
    // 读取负载参数
    ::grpc::Status GetLoadParam(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::LoadGrpc_GetLoadParam_Response* response) override;
    // 设置负载参数
    ::grpc::Status SetLoadParam(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::LoadGrpc_SetLoadParam_Request* request, ::google::protobuf::BoolValue* response) override;
             
#pragma endregion

};

}  // namespace InoRobBusiness
