#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "TaskGrpc.grpc.pb.h"
#include "ITask.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class TaskService final : public TaskGrpc::Service
{
#pragma region 数据转换

public:
    static TaskStatus_Grpc TaskStatus_ToGrpc(TaskStatus taskStatus);
    static TaskStatus TaskStatus_FromGrpc(TaskStatus_Grpc taskStatus_Grpc);

    static bool TaskRunInfoItem_ToGrpc(const TaskRunInfoItem &taskRunInfoItem, TaskRunInfoItem_Grpc &taskRunInfoItem_Grpc);
    static bool TaskRunInfoItem_FromGrpc(const TaskRunInfoItem_Grpc &taskRunInfoItem_Grpc, TaskRunInfoItem &taskRunInfoItem);

    static bool TaskRunInfo_ToGrpc(const TaskRunInfo &taskRunInfo, TaskRunInfo_Grpc &taskRunInfo_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    ITask *_task;

public:
    TaskService(ITask *task);
    ~TaskService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 所有任务返回起始行
    // 成功返回0，失败请查看错误码
    ::grpc::Status returnStartLineAll(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // 单个任务返回起始行
    // 任务id
    // 成功返回0，失败请查看错误码
    ::grpc::Status returnStartLineSingle(::grpc::ServerContext* context, const ::google::protobuf::Int32Value* request, ::google::protobuf::Int32Value* response) override;
    // 获取单个任务的运行状态
    // 任务id
    ::grpc::Status getTaskStatus(::grpc::ServerContext* context, const ::google::protobuf::Int32Value* request, ::InoRobBusinessGrpc::getTaskStatus_Response* response) override;
    // 获取单个任务的运行信息
    // 任务id
    ::grpc::Status getTaskInfo(::grpc::ServerContext* context, const ::google::protobuf::Int32Value* request, ::InoRobBusinessGrpc::getTaskInfo_Response* response) override;
    // 设置起始行
    // 成功返回0，失败请查看错误码
    ::grpc::Status setStartLine(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::setStartLine_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取所有任务的运行信息
    ::grpc::Status getAllTaskInfo(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::TaskGrpc_getAllTaskInfo_Response* response) override;
    // 设置所有任务的激活状态
    // 成功返回0，失败请查看错误码
    ::grpc::Status setTaskActiveFlag(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::TaskGrpc_setTaskActiveFlag_Request* request, ::google::protobuf::Int32Value* response) override;
    // 设置指定任务的激活状态
    // 成功返回0，失败请查看错误码
    ::grpc::Status setTaskActiveFlagForSingle(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::TaskGrpc_setTaskActiveFlagForSingle_Request* request, ::google::protobuf::Int32Value* response) override;
         
#pragma endregion

};

}  // namespace InoRobBusiness
