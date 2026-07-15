#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <QObject>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ToolGrpc.grpc.pb.h"
#include "ITool.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ToolService final : public QObject, public ToolGrpc::Service
{
    Q_OBJECT

#pragma region 数据转换

public:
    static RobotHoldToolType_Grpc RobotHoldToolType_ToGrpc(RobotHoldToolType robotHoldToolType);
    static RobotHoldToolType RobotHoldToolType_FromGrpc(RobotHoldToolType_Grpc robotHoldToolType_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    ITool *_tool;

public:
    ToolService(ITool *tool);
    ~ToolService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取当前工具号
    ::grpc::Status GetCurrentId(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::UInt32Value* response) override;
    // 设定当前工具号
    ::grpc::Status SetCurrentId(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::google::protobuf::BoolValue* response) override;
    // 当前工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    ::grpc::Status CurrentIsRobotHold(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::CurrentIsRobotHold_Response* response) override;
    // 指定工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    ::grpc::Status someoneIsRobotHold(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::someoneIsRobotHold_Response* response) override;
    // 读取工具参数
    ::grpc::Status GetToolParam(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::GetToolParam_Response* response) override;
    // 设置工具参数
    ::grpc::Status SetToolParam(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SetToolParam_Request* request, ::google::protobuf::BoolValue* response) override;
    // 工具标定
    ::grpc::Status ToolCalibrate(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::ToolCalibrate_Request *request, ::InoRobBusinessGrpc::ToolCalibrate_Response *response) override;

#pragma endregion

#pragma region 信号

#pragma endregion
};

}  // namespace InoRobBusiness
