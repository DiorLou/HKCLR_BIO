#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ScriptExtension.grpc.pb.h"
#include "IScriptExtension.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ScriptExtensionService final : public ScriptExtensionGrpc::Service
{
private:
    IScriptExtension *_scriptExtension;

public:
    ScriptExtensionService(IScriptExtension *scriptExtension);
    ~ScriptExtensionService();

public:
    // 开始
    ::grpc::Status Start(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 暂停
    ::grpc::Status Pause(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 停止
    ::grpc::Status Abort(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 单步
    ::grpc::Status StepBlock(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;

};

}  // namespace InoRobBusiness
