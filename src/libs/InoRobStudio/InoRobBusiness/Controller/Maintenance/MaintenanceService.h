#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "MaintenanceGrpc.grpc.pb.h"
#include "IMaintenance.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class MaintenanceService final : public MaintenanceGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IMaintenance *_maintenance;

public:
    MaintenanceService(IMaintenance *maintenance);
    ~MaintenanceService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 检查控制器USB是否连接
    // return 连接状态
    ::grpc::Status checkControllerUSB(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 启动诊断
    // return 是否诊断成功（0表示成功）
    ::grpc::Status startDiagnose(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::MaintenanceGrpc_startDiagnose_Request* request, ::google::protobuf::Int32Value* response) override;
    // 停止诊断
    // return 是否停止成功（0表示成功）
    ::grpc::Status stopDiagnose(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::MaintenanceGrpc_stopDiagnose_Request* request, ::google::protobuf::Int32Value* response) override;
    // 启动导出报告
    // return 是否成功（0表示成功）
    ::grpc::Status startExportReport(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::MaintenanceGrpc_startExportReport_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取诊断的保存状态
    ::grpc::Status ReadErrSaveSta(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::MaintenanceGrpc_ReadErrSaveSta_Response* response) override;
    // 获取诊断报告的导出状态
    ::grpc::Status ReadErrExportSta(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::MaintenanceGrpc_ReadErrExportSta_Response* response) override;
     
#pragma endregion

};

}  // namespace InoRobBusiness
