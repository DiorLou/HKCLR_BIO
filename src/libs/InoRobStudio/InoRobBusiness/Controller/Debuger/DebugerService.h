#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "DebugerGrpc.grpc.pb.h"
#include "IDebuger.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class DebugerService final : public DebugerGrpc::Service
{
#pragma region 数据转换

public:
    static DebugMode_Grpc DebugMode_ToGrpc(DebugMode debugMode);
    static DebugMode DebugMode_FromGrpc(DebugMode_Grpc debugMode_Grpc);

    static TrajectoryRecoveryFlag_Grpc TrajectoryRecoveryFlag_ToGrpc(TrajectoryRecoveryFlag trajectoryRecoveryFlag);
    static TrajectoryRecoveryFlag TrajectoryRecoveryFlag_FromGrpc(TrajectoryRecoveryFlag_Grpc trajectoryRecoveryFlag_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IDebuger *_debuger;

public:
    DebugerService(IDebuger *debuger);
    ~DebugerService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 设置用户的调试模式（编程or调试）
    ::grpc::Status setDebugMode(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::setDebugMode_Request *request, ::google::protobuf::Empty *response) override;
    // 获取当前用户的调试模式（编程or调试）
    ::grpc::Status getDebugMode(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::getDebugMode_Response *response) override;
    // 启动运行（调试）
    ::grpc::Status startRunningInDebug(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::startRunningInDebug_Response *response) override;
    // 启动运行（自动）
    ::grpc::Status startRunningInAuto(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::startRunningInAuto_Response *response) override;
    // 停止运行（调试）
    // isRmtIoEnable，远程IO控制权下是否可以停止
    // 成功返回0，失败请查看错误码
    ::grpc::Status stopRunningInDebug(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::Int32Value *response) override;
    // 停止运行（自动）
    // isRmtIoEnable，远程IO控制权下是否可以停止
    // 成功返回0，失败请查看错误码
    ::grpc::Status stopRunningInAuto(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::Int32Value *response) override;
    // 执行下一步
    ::grpc::Status nextStep(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::nextStep_Response *response) override;
    // 设置轨迹恢复的执行策略
    // mode 0-放弃，1-执行
    // 成功返回0
    ::grpc::Status trajectoryRecoveryExcute(::grpc::ServerContext *context, const ::google::protobuf::Int32Value *request, ::google::protobuf::Int32Value *response) override;

#pragma endregion
};

}  // namespace InoRobBusiness
