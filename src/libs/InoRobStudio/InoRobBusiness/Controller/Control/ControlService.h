#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "ControlGrpc.grpc.pb.h"
#include "../Motion/MotionService.h"
#include "../Monitor/MonitorService.h"
#include "IControl.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class ControlService final : public ControlGrpc::Service
{
#pragma region 数据转换

public:
    static DeviceMode_Grpc DeviceMode_ToGrpc(DeviceMode deviceMode);
    static DeviceMode DeviceMode_FromGrpc(DeviceMode_Grpc deviceMode_Grpc);

    static CoordinationStateEnum_Grpc CoordinationStateEnum_ToGrpc(CoordinationStateEnum coordinationStateEnum);
    static CoordinationStateEnum CoordinationStateEnum_FromGrpc(CoordinationStateEnum_Grpc coordinationStateEnum_Grpc);

    static bool SystemUpdateInfo_ToGrpc(const SystemUpdateInfo &systemUpdateInfo, SystemUpdateInfo_Grpc &systemUpdateInfo_Grpc);
    static bool SystemUpdateInfo_FromGrpc(const SystemUpdateInfo_Grpc &systemUpdateInfo_Grpc, SystemUpdateInfo &systemUpdateInfo);

#pragma endregion

#pragma region 构造与析构

private:
    IControl *_control;

public:
    ControlService(IControl *control);
    ~ControlService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 使能（true：上使能，false：下使能）
    ::grpc::Status SetEnable(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::Int32Value *response) override;
    // 急停（true：急停，false：去急停）
    ::grpc::Status SetEmergency(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::Int32Value *response) override;
    // 清除报警
    ::grpc::Status ClearWarning(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::ClearWarning_Request *request, ::google::protobuf::Int32Value *response) override;
    // 运行模式
    //::grpc::Status SetRunMode(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::SetRunMode_Request *request, ::google::protobuf::BoolValue *response) override;
    // 设置设备（机器人）模式
    ::grpc::Status SetDeviceMode(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::SetDeviceMode_Request *request, ::google::protobuf::Int32Value *response) override;
    // 获取设备（机器人）模式
    ::grpc::Status GetDeviceMode(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::GetDeviceMode_Response *response) override;
    // *
    // @brief 开启限速
    // @return 成功返回0，其他请见错误码
    ::grpc::Status activateSpeedLimit(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // *
    // @brief 关闭限速
    // @return 成功返回0，其他请见错误码
    ::grpc::Status turnoffSpeedLimit(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // *
    // @brief 是否已经开启限速
    ::grpc::Status isActivatedSpeedLimit(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // 机械锁定
    ::grpc::Status SetMechLock(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::BoolValue *response) override;
    // 动态制动（true：开启，false：关闭）
    ::grpc::Status SetDynamicBrake(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::BoolValue *response) override;
    // 机器人协调机械单元
    // name：机械单元名称（为空表示关闭机器人协调）
    ::grpc::Status SetCooperate(::grpc::ServerContext *context, const ::google::protobuf::StringValue *request, ::google::protobuf::BoolValue *response) override;
    // *
    // @brief 设置协调状态
    // @param coordSts 协调状态
    ::grpc::Status setCoordinationState(::grpc::ServerContext *context, const ::google::protobuf::Int32Value *request, ::google::protobuf::Empty *response) override;
    // *
    // @brief 获取协调状态
    // @return 协调状态
    ::grpc::Status getCoordinationState(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // !
    // \brief 设置协调
    // \param status 状态
    // \return true成功 false失败
    ::grpc::Status setCooperate(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::BoolValue *response) override;
    // *
    // @brief 系统升级（控制器升级）
    // @param isUpdateBsp 是否更新bsp底层系统镜像，25版本及以后才能设置不更新
    // @return 成功返回0，其他请见错误码
    ::grpc::Status systemUpgrade(::grpc::ServerContext *context, const ::google::protobuf::BoolValue *request, ::google::protobuf::Int32Value *response) override;
    // *
    // @brief 将系统（控制器）降级为一个固定版本
    // @return 成功返回0，其他请见错误码
    ::grpc::Status systemDegrade(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::Int32Value *response) override;
    // *
    // @brief 状态检查，是否可以进行系统升降级
    ::grpc::Status isSystemCanUpdate(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;
    // *
    // @brief 获取系统升降级的过程信息
    // @param info 过程信息
    // @return 成功返回0，其他请见错误码
    ::grpc::Status readSystemUpdateInfo(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::InoRobBusinessGrpc::readSystemUpdateInfo_Response *response) override;
    // *
    // @brief 设置本体上下电(协作)
    ::grpc::Status SetCoRobotBodyPowerState(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SetCoRobotBodyPowerState_Request* request, ::google::protobuf::Int32Value* response) override;
    // *
    // @brief 设置WIFI频段(协作)
    ::grpc::Status SetControllerWifiFrequencyBand(::grpc::ServerContext* context, const ::google::protobuf::BoolValue* request, ::google::protobuf::Int32Value* response) override;
    // *
    // @brief 获取Wifi信息
    ::grpc::Status GetControllerWifiInfo(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::ControllerWifiInfo_Response* response) override;
#pragma endregion
};

}  // namespace InoRobBusiness
