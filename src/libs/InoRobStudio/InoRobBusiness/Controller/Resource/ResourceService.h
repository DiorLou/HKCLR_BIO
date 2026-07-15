#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ResourceGrpc.grpc.pb.h"
#include "IResource.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ResourceService final : public ResourceGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IResource *_resource = nullptr;

public:
    ResourceService(IResource *resource);
    ~ResourceService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 读取所有全局变量String
    ::grpc::Status readGlobalVarStringValues(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::ResourceGrpc_readGlobalVarStringValues_Response *response) override;
    // 写入全局变量String的值
    ::grpc::Status writeGlobalVarStringValue(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::ResourceGrpc_writeGlobalVarStringValue_Request *request, ::google::protobuf::Int32Value *response) override;
    // 读取IO状态-Output
    // 返回：指定读取范围的byte数组
    ::grpc::Status readOutputStatusByByte(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::ResourceGrpc_readOutputStatusByByte_Reuest *request, ::InoRobBusinessGrpc::ResourceGrpc_readOutputStatusByByte_Response *response) override;
    // 读取所有全局B变量值
    ::grpc::Status readGlobalVarBValues(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::ReadGlobalVarBValues_Response *response) override;
    // 写入一个全局B变量值
    ::grpc::Status writeGlobalVarBValue(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::WriteGlobalVarBValue_Request *request, ::google::protobuf::Int32Value *response) override;
#pragma endregion

};

}  // namespace InoRobBusiness
