#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "MechUnitGrpc.grpc.pb.h"
#include "IMechUnit.h"
#include "IMechUnitManage.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class MechUnitService final : public MechUnitGrpc::Service
{
#pragma region 数据转换

public:
    static ExternalPropName_Grpc ExternalPropName_ToGrpc(ExternalPropName externalPropType);
    static ExternalPropName ExternalPropName_FromGrpc(ExternalPropName_Grpc externalPropType_Grpc);
    static MechUnitData_Grpc MechUnitData_ToGrpc(MechUnitData externalPropType);
    static MechUnitData MechUnitData_FromGrpc(MechUnitData_Grpc externalPropType_Grpc);
    static MechUnitCalibMethod_Grpc MechUnitCalibMethod_ToGrpc(MechUnitCalibMethod calibMethod);
    static MechUnitCalibMethod MechUnitCalibMethod_FromGrpc(MechUnitCalibMethod_Grpc calibMethod_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IMechUnit *_mechUnit = nullptr;
    IMechUnitManage *_mechUnitManage = nullptr;


public:
    MechUnitService(IMechUnit *mechUnit, IMechUnitManage *mechUnitManage);
    ~MechUnitService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 激活机械单元
    ::grpc::Status MechUnitActive(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::google::protobuf::BoolValue* response) override;
    // 删除robot以外的所有机械单元
    // @return 0:成功 其他:错误码
    ::grpc::Status DelAllMechUnit(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // 设置机器人独立轴属性
    ::grpc::Status setRobotIndAxisAttribute(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::setRobotIndAxisAttribute_Request *request, ::google::protobuf::Int32Value *response) override;
    // 添加机械单元
    ::grpc::Status addMechUnit(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::AddMechUnit_Request *request, ::google::protobuf::BoolValue *response) override;
    // 获取所有机械单元的独立轴信息
    ::grpc::Status getAllMechUnitIsSupportIndAxisData(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::MechUnitIsSupportIndList_Grpc *response) override;
    // 删除机械单元
    ::grpc::Status RemoveMechUnit(::grpc::ServerContext *context, const ::google::protobuf::StringValue *request, ::google::protobuf::BoolValue *response) override;
    // 设置轴属性表的值
    ::grpc::Status setAxisAttributeValue(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::setAxisAttributeValue_Request *request, ::google::protobuf::Int32Value *response) override;
    // 取当前值作为零点
    // guideIndex 机械单元的索引号
    // curAxisIndex 当前的轴号,0-轴1, 1-轴2, 2-轴3
    ::grpc::Status setCurValueAsHome(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::setCurValueAsHome_Request *request, ::google::protobuf::Int32Value *response) override;

    // 获取所有机械单元列表
    ::grpc::Status GetMechUnitList(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::MechUnitGrpc_GetMechUnitList_Response *response) override;

    // 设置机器人的安装类型及移动导轨名称
    ::grpc::Status setRobotInstallType(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::SetRobotInstallType_Request *request, ::google::protobuf::Int32Value *response) override;

    // 机械单元标定
    ::grpc::Status calibrate(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::MechUnitCalibrate_Request *request, ::InoRobBusinessGrpc::MechUnitCalibrate_Response *response) override;

#pragma endregion

};

}  // namespace InoRobBusiness
