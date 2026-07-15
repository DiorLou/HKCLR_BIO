#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "MonitorGrpc.grpc.pb.h"
#include "IMonitor.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class MonitorService final : public MonitorGrpc::Service
{
#pragma region 数据转换

public:
    static EDevState_Grpc EDevState_ToGrpc(EDevState eDevState);
    static EDevState EDevState_FromGrpc(EDevState_Grpc eDevState_Grpc);

    static ControllerRunStatus_Grpc ControllerRunStatus_ToGrpc(ControllerRunStatus controllerRunStatus);
    static ControllerRunStatus ControllerRunStatus_FromGrpc(ControllerRunStatus_Grpc controllerRunStatus_Grpc);

    static ElectricControlCabinetType_Grpc ElectricControlCabinetType_ToGrpc(ElectricControlCabinetType electricControlCabinetType);
    static ElectricControlCabinetType ElectricControlCabinetType_FromGrpc(ElectricControlCabinetType_Grpc electricControlCabinetType_Grpc);

    static ToolWobjMatchStatus_Grpc ToolWobjMatchStatus_ToGrpc(ToolWobjMatchStatus toolWobjMatchStatus);
    static ToolWobjMatchStatus ToolWobjMatchStatus_FromGrpc(ToolWobjMatchStatus_Grpc toolWobjMatchStatus_Grpc);

    static RunMode_Grpc RunMode_ToGrpc(RunMode runMode);
    static RunMode RunMode_FromGrpc(RunMode_Grpc runMode_Grpc);

    static MoveStepGrade_Grpc MoveStepGrade_ToGrpc(MoveStepGrade moveStepGrade);
    static MoveStepGrade MoveStepGrade_FromGrpc(MoveStepGrade_Grpc moveStepGrade_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IMonitor *_monitor;

public:
    MonitorService(IMonitor *monitor);
    ~MonitorService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 机器人名称
    ::grpc::Status GetRobotName(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetRobotName_Response* response) override;
    // 机型（机械臂型号）
    ::grpc::Status GetRobotType(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetRobotType_Response* response) override;
    // 电柜类型
    ::grpc::Status GetElectricControlCabinetType(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetElectricControlCabinetType_Response* response) override;
    // 是否掉电保存
    ::grpc::Status GetIsPowerDownSave(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // IO数量
    ::grpc::Status GetInputNum(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    ::grpc::Status GetOutputNum(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // AD、DA数量
    ::grpc::Status GetAdNum(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    ::grpc::Status GetDaNum(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // 控制器软件版本
    ::grpc::Status GetRCVersionName(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::StringValue* response) override;
    // 运行状态
    ::grpc::Status GetRunStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetRunStatus_Response* response) override;
    // 警告Id
    ::grpc::Status GetWarningId(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // 错误Id
    ::grpc::Status GetErrorId(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::Int32Value* response) override;
    // 获取速度值
    ::grpc::Status GetSpeed(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::UInt32Value* response) override;
    // 获取当前寸动等级
    ::grpc::Status GetMoveStepGrade(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetMoveStepGrade_Response* response) override;
    // 获取当前坐标系类型
    ::grpc::Status GetCurrentCoordType(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetCurrentCoordType_Response* response) override;
    // 当前位置格式
    ::grpc::Status GetPosFormat(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetPosFormat_Response* response) override;
    // 获取当前位置（机械单元）
    ::grpc::Status GetCurrentPosition(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetCurrentPosition_Response* response) override;
    // 获取当前负载号
    ::grpc::Status GetLoadId(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::UInt32Value* response) override;
    // 获取使能状态（true：已上使能，false：已下使能）
    ::grpc::Status GetEnable(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 获取急停状态（true：已急停，false：未急停）
    ::grpc::Status GetEmergency(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 获取运行模式
    ::grpc::Status GetRunMode(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetRunMode_Response* response) override;
    // 获取当前机械锁定状态（true：锁定，false：未锁定）
    ::grpc::Status GetMechLock(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 获取当前动态制动状态（true：开启，false：关闭）
    ::grpc::Status GetDynamicBrake(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 获取机器人当前协调的机械单元名称（为空表示机器人未开启协调）
    ::grpc::Status GetCooperate(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::StringValue* response) override;
    // 获取设备状态
    ::grpc::Status getDeviceState(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getDeviceState_Response* response) override;
    // 机械单元列表
    ::grpc::Status GetMechUnitList(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetMechUnitList_Response* response) override;
    // 获取当前激活（选中）的机械单元
    ::grpc::Status GetActiveMechUnit(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetActiveMechUnit_Response* response) override;
    // 当前机械单元是否满足协调条件
    ::grpc::Status GetCooperateIsReady(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // 获取本体上下电(协作)
    ::grpc::Status GetCoRobotBodyPowerState(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::SetCoRobotBodyPowerState_Response* response) override;
#pragma endregion
};

}  // namespace InoRobBusiness
