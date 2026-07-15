#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "SafeParaSettingMgr.grpc.pb.h"
#include "ISafeParaSettingMgr.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class SafeParaSettingMgrService final : public SafeParaSettingMgrGrpc::Service
{
private:
    ISafeParaSettingMgr *_safeParaSettingMgr;

public:
    SafeParaSettingMgrService(ISafeParaSettingMgr *safeParaSettingMgr);
    ~SafeParaSettingMgrService();

public:
    // 写入缩减模式速度缩减数值到A40i
    ::grpc::Status WriteSpeedReducing(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SpeedReduceConfig_Request* request, ::google::protobuf::Int32Value* response) override;
    // 从A40i读取缩减模式速度缩减数值
    ::grpc::Status ReadSpeedReducing(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::SpeedReduceConfig_Response* response) override;

};

}  // namespace InoRobBusiness
