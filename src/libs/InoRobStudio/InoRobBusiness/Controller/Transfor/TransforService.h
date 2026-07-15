#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "TransforGrpc.grpc.pb.h"
#include "ITransfor.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class TransforService final : public TransforGrpc::Service
{
#pragma region 数据转换

public:
    static bool Project_Info_ToGrpc(const Project_Info &project_Info, Project_Info_Grpc &project_Info_Grpc);
    static bool Project_Info_FromGrpc(const Project_Info_Grpc &project_Info_Grpc, Project_Info &project_Info);

    static ParseDemand_Grpc ParseDemand_ToGrpc(ParseDemand parseDemand);
    static ParseDemand ParseDemand_FromGrpc(ParseDemand_Grpc parseDemand_Grpc);

    static SyncProjcetInfoType_Grpc SyncProjcetInfoType_ToGrpc(SyncProjcetInfoType syncProjcetInfoType);
    static SyncProjcetInfoType SyncProjcetInfoType_FromGrpc(SyncProjcetInfoType_Grpc syncProjcetInfoType_Grpc);

    static ParseStatus_Grpc ParseStatus_ToGrpc(ParseStatus parseStatus);
    static ParseStatus ParseStatus_FromGrpc(ParseStatus_Grpc parseStatus_Grpc);

    static bool PraseInfo_ToGrpc(const PraseInfo &praseInfo, PraseInfo_Grpc &praseInfo_Grpc);
    static bool PraseInfo_FromGrpc(const PraseInfo_Grpc &praseInfo_Grpc, PraseInfo &praseInfo);

#pragma endregion

#pragma region 构造与析构

private:
    ITransfor *_transfor;
    IProject *_project;

public:
    TransforService(ITransfor *transfor, IProject *project);
    ~TransforService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 编译工程
    ::grpc::Status parseProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::parseProject_Request* request, ::InoRobBusinessGrpc::parseProject_Response* response) override;
    // 设置机器人信息
    ::grpc::Status setRobotInformation(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::TransforGrpc_setRobotInformation_Request* request, ::google::protobuf::Empty* response) override;
    // 编译单个程序文件
    // 请求：程序文件路径
    ::grpc::Status parseProgram(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::InoRobBusinessGrpc::TransforGrpc_parseProgram_Response* response) override;
    // 编译临时程序文件（不属于任何任务的公共程序文件）
    ::grpc::Status parseTempProgram(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::TransforGrpc_parseTempProgram_Request* request, ::google::protobuf::BoolValue* response) override;
    // 通知控制器译码
    // 成功返回0，其他请见错误码
    ::grpc::Status syncProjectInfo(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::TransforGrpc_syncProjectInfo_Request* request, ::google::protobuf::Int32Value* response) override;
    // 任务变更后通知控制器译码（注：非业务模型层方法，单独为测试API添加）
    ::grpc::Status syncProjectInfoAfterChanged(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 读取控制器的译码状态
    ::grpc::Status readCtrlProjectParseFlag(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::TransforGrpc_readCtrlProjectParseFlag_Response* response) override;
    // 等待控制器译码结束并获取译码结果
    // true-成功，false-失败
    ::grpc::Status waitForCtrlParseResult(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 读取控制器是否需要执行译码
    ::grpc::Status readCtrlProjectNeedTrans(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::TransforGrpc_readCtrlProjectNeedTrans_Response* response) override;

#pragma endregion

};

}  // namespace InoRobBusiness
