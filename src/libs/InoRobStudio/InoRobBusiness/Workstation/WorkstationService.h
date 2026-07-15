#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <boost/circular_buffer.hpp>
#include <QObject>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "WorkstationGrpc.grpc.pb.h"
#include "IWorkstation.h"
#include "PrintInfo.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;
using namespace InoRobLog;

namespace InoRobBusiness
{
class WorkstationService final : public QObject, public WorkstationGrpc::Service
{
    Q_OBJECT

#pragma region 数据转换

public:
    static WorkstationType_Grpc WorkstationType_ToGrpc(WorkstationType workstationType);
    static WorkstationType WorkstationType_FromGrpc(WorkstationType_Grpc workstationType_Grpc);

    static InfoType_Grpc InfoType_ToGrpc(PrintInfo::InfoType infoType);
    static PrintInfo::InfoType InfoType_FromGrpc(InfoType_Grpc infoType_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IWorkstation *_workstation;
    PrintInfo *_printInfo;
    void printInfoSignal_Handler(const InoRobLog::PrintInfo::InfoType type, const std::string &printInfo);

public:
    WorkstationService(IWorkstation *workstation, PrintInfo *printInfo);
    ~WorkstationService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 工作站ID（唯一标识）
    ::grpc::Status GetID(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::StringValue *response) override;
    // 工作站名称
    ::grpc::Status GetName(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::StringValue *response) override;
    // 当前工作站类型
    ::grpc::Status GetWorkstationType(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::GetWorkstationType_Response *response) override;
    // 程序运行根目录（以反斜杠结尾如 c:\\test\\）
    ::grpc::Status GetAppRootPath(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::StringValue *response) override;
    // 获取打印信息
    ::grpc::Status GetPrintInfo(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::GetPrintInfo_Request* request, ::InoRobBusinessGrpc::GetPrintInfo_Response* response) override;

private:
    // 打印消息环形队列
    boost::circular_buffer<PrintInfoItem_Grpc> _printInfoList;

#pragma endregion
};

}  // namespace InoRobBusiness
