#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ControlAuthorityGrpc.grpc.pb.h"
#include "IControlAuthority.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ControlAuthorityService final : public ControlAuthorityGrpc::Service
{
#pragma region 数据转换

public:
    static CtrlAuthority_Grpc CtrlAuthority_ToGrpc(CtrlAuthority ctrlAuthority);
    static CtrlAuthority CtrlAuthority_FromGrpc(CtrlAuthority_Grpc ctrlAuthority_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IControlAuthority *_controlAuthority;

public:
    ControlAuthorityService(IControlAuthority *controlAuthority);
    ~ControlAuthorityService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取当前控制权
    ::grpc::Status getCurrentAuthority(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::ControlAuthorityGrpc_getCurrentAuthority_Response* response) override;
    // 切换控制权
    // 成功返回0，其他请见错误码
    ::grpc::Status changeAuthority(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ControlAuthorityGrpc_changeAuthority_Request* request, ::google::protobuf::Int32Value* response) override;
         
#pragma endregion

};

}  // namespace InoRobBusiness
