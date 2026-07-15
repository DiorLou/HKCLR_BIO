#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <map>
#include <QObject>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ConnectionGrpc.grpc.pb.h"
#include "IConnection.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ConnectionService final : public QObject, public ConnectionGrpc::Service
{
    Q_OBJECT

#pragma region 数据转换

public:
    static ControllerConnectionStatus_Grpc ControllerConnectionStatus_ToGrpc(ControllerConnectionStatus controllerConnectionStatus);
    static ControllerConnectionStatus ControllerConnectionStatus_FromGrpc(ControllerConnectionStatus_Grpc controllerConnectionStatus_Grpc);

    static ConnentType_Grpc ConnentType_ToGrpc(ConnentType connentType);
    static ConnentType ConnentType_FromGrpc(ConnentType_Grpc connentType_Grpc);

    static ConnectVersion_Grpc ConnectVersion_ToGrpc(ConnectVersion connectVersion);
    static ConnectVersion ConnectVersion_FromGrpc(ConnectVersion_Grpc connectVersion_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IConnection *_connection;

public:
    ConnectionService(IConnection *connection);
    ~ConnectionService();

#pragma endregion

#pragma region 业务逻辑

public:
    // IP
    ::grpc::Status GetIp(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::StringValue *response) override;
    ::grpc::Status SetIp(::grpc::ServerContext *context, const ::google::protobuf::StringValue *request, ::google::protobuf::Empty *response) override;
    // 端口
    ::grpc::Status GetPort(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::UInt32Value *response) override;
    ::grpc::Status setPort(::grpc::ServerContext *context, const ::google::protobuf::UInt32Value *request, ::google::protobuf::Empty *response) override;
    // 控制器连接状态
    ::grpc::Status GetConnectionStatus(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::GetConnectionStatus_Response *response) override;
    // 连接
    ::grpc::Status Connect(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::GetConnectionStatus_Request *request, ::google::protobuf::BoolValue *response) override;
    // 关闭连接
    // bManual: true-正常断开 false-状态复位,每次连接后立即复位
    ::grpc::Status Close(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::BoolValue *response) override;
    // 跳过启动软件时的连接过程
    ::grpc::Status skipBootConnect(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;

#pragma endregion

#pragma region 信号

public:
    // 连接状态变化信号
    ::grpc::Status connectionStatusChanged(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::grpc::ServerWriter<::InoRobBusinessGrpc::GetConnectionStatus_Response>* writer) override;
private:
    map<string, ControllerConnectionStatus> connectionStatusChanged_Clients;
    //void connectionStatusChanged_Handler(ControllerConnectionStatus connectionStatus);

#pragma endregion
};

}  // namespace InoRobBusiness
