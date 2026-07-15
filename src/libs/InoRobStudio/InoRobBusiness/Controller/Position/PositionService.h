#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "PositionGrpc.grpc.pb.h"
#include "IPosition.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class PositionService final : public PositionGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IPosition *_position;

public:
    PositionService(IPosition *position);
    ~PositionService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 设定当前坐标系类型
    ::grpc::Status SetCurrentCoordType(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::SetCurrentCoordType_Request *request, ::google::protobuf::BoolValue *response) override;

#pragma endregion
};

}  // namespace InoRobBusiness
