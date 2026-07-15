#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ProjectGrpc.grpc.pb.h"
#include "IProject.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ProjectService final : public ProjectGrpc::Service
{
#pragma region 数据转换

public:
    static ProjectType_Grpc ProjectType_ToGrpc(ProjectType projectType);
    static ProjectType ProjectType_FromGrpc(ProjectType_Grpc projectType_Grpc);

    static bool MultiTaskInfo_ToGrpc(const MultiTaskInfo &multiTaskInfo, MultiTaskInfo_Grpc &multiTaskInfo_Grpc);
    static bool MultiTaskInfo_FromGrpc(const MultiTaskInfo_Grpc &multiTaskInfo_Grpc, MultiTaskInfo &multiTaskInfo);

    static bool ProjectFolderInfo_ToGrpc(const ProjectFolderInfo &projectFolderInfo, ProjectFolderInfo_Grpc &projectFolderInfo_Grpc);
    static bool ProjectFolderInfo_FromGrpc(const ProjectFolderInfo_Grpc &projectFolderInfo_Grpc, ProjectFolderInfo &projectFolderInfo);

    static ProgramType_Grpc ProgramType_ToGrpc(ProgramType programType);
    static ProgramType ProgramType_FromGrpc(ProgramType_Grpc programType_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IProject *_project;

public:
    ProjectService(IProject *project);
    ~ProjectService();

#pragma endregion

#pragma region 业务逻辑

public:
    // *
    // @brief 创建工程（本地）
    // @return 成功返回0，其他请见错误码
    ::grpc::Status CreateLocalProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::CreateLocalProject_Request* request, ::google::protobuf::Int32Value* response) override;
    // *
    // @brief 从本地加载工程
    // @param .prj工程配置文件的路径
    // @return 成功返回0，其他请见错误码
    ::grpc::Status ReadLocalProjcet(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Int32Value* response) override;
    // 从本地导入工程，下发到控制器
    // 成功返回0，其他请见错误码
    ::grpc::Status ImportProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ImportProject_Request* request, ::google::protobuf::Int32Value* response) override;

    // 从控制器读取工程列表
    // 控制器ip
    ::grpc::Status ReadProjectList(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::InoRobBusinessGrpc::ReadProjectList_Response* response) override;
    // 从控制器下载工程并导出到本地文件夹中
    // 成功返回0，其他请见错误码
    ::grpc::Status ExportProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ExportProject_Request* request, ::google::protobuf::Int32Value* response) override;
    // 从控制器加载指定名称的工程
    // 成功返回0，其他请见错误码
    ::grpc::Status ReadProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ReadProject_Request* request, ::google::protobuf::Int32Value* response) override;
    // 创建工程（控制器）
    // 成功返回0，其他请见错误码
    ::grpc::Status CreateProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::CreateProject_Request* request, ::google::protobuf::Int32Value* response) override;
    // 删除工程（控制器）
    // 工程名称
    // 成功返回0，其他请见错误码
    ::grpc::Status DelProject(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Int32Value* response) override;
    // 重命名工程（控制器）
    // 成功返回0，其他请见错误码
    ::grpc::Status RenameProject(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::RenameProject_Request* request, ::google::protobuf::Int32Value* response) override;
    // 拷贝工程（控制器）
    // 工程名称
    // 成功返回0，其他请见错误码
    ::grpc::Status CopyProject(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Empty* response) override;
    // 粘贴工程（控制器）
    // 工程名称
    // 成功返回0，其他请见错误码
    ::grpc::Status PasteProject(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Int32Value* response) override;
    // 设置控制器当前激活的工程
    // 输入，工程名称
    // 成功返回0，其他请见错误码
    ::grpc::Status setActiveProject(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Int32Value* response) override;
    // 获取控制器当前激活的工程
    ::grpc::Status getActiveProject(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getActiveProject_Response* response) override;

    // 新增任务至工程配置中
    ::grpc::Status AddTask(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::AddTask_Request* request, ::google::protobuf::Int32Value* response) override;
    // 从工程配置中移除任务
    // 任务id
    ::grpc::Status DelTask(::grpc::ServerContext* context, const ::google::protobuf::Int32Value* request, ::google::protobuf::Int32Value* response) override;
    // 清空工程配置中的任务信息
    ::grpc::Status ClearTask(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // 保存当前加载的工程的配置信息
    // 成功返回0，其他请见错误码
    ::grpc::Status SaveProjectConfig(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SaveProjectConfig_Request* request, ::google::protobuf::Int32Value* response) override;

    // 获取程序文件列表
    ::grpc::Status GetProgramFileList(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::ProjectGrpc_GetProgramFileList_Response* response) override;
    // 指定的程序文件是否已存在
    // 请求参数：程序文件名称
    // 响应结果：已存在true,不存在false
    ::grpc::Status IsProgramFileExisted(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::BoolValue* response) override;
    // 新建程序文件
    // 成功返回0，其他请见错误码
    ::grpc::Status NewFile(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ProjectGrpc_NewFile_Request* request, ::google::protobuf::Int32Value* response) override;
    // 重命名程序文件
    // 成功返回0，其他请见错误码
    ::grpc::Status RenameFile(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::ProjectGrpc_RenameFile_Request* request, ::google::protobuf::Int32Value* response) override;
    // 删除程序文件
    // 输入，文件名称
    // 成功返回0，其他请见错误码
    ::grpc::Status DelFile(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::Int32Value* response) override;
    // 获取指定序号的全局P点位数据
    ::grpc::Status GetRPoint(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::GetRPoint_Request *request, ::InoRobBusinessGrpc::GetRPoint_Response *response) override;

#pragma endregion

};

}  // namespace InoRobBusiness
