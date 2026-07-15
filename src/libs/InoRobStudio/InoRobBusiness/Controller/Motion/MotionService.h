#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "MotionGrpc.grpc.pb.h"
#include "../Monitor/MonitorService.h"
#include "IMotion.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class MotionService final : public MotionGrpc::Service
{
#pragma region 数据转换

public:
    static MotionStatus_Grpc MotionStatus_ToGrpc(MotionStatus motionStatus);
    static MotionStatus MotionStatus_FromGrpc(MotionStatus_Grpc motionStatus_Grpc);

    static MoveStatus_Grpc MoveStatus_ToGrpc(MoveStatus moveStatus);
    static MoveStatus MoveStatus_FromGrpc(MoveStatus_Grpc moveStatus_Grpc);

    static MotionType_Grpc MotionType_ToGrpc(MotionType motionType);
    static MotionType MotionType_FromGrpc(MotionType_Grpc motionType_Grpc);

    static RotateDir_Grpc RotateDir_ToGrpc(RotateDir rotateDir);
    static RotateDir RotateDir_FromGrpc(RotateDir_Grpc rotateDir_Grpc);

    static PressState_Grpc PressState_ToGrpc(PressState pressState);
    static PressState PressState_FromGrpc(PressState_Grpc pressState_Grpc);

    static bool MoveStepSizePara_ToGrpc(const MoveStepSizePara &moveStepSizePara, MoveStepSizePara_Grpc &moveStepSizePara_Grpc);
    static bool MoveStepSizePara_FromGrpc(const MoveStepSizePara_Grpc &moveStepSizePara_Grpc, MoveStepSizePara &moveStepSizePara);

#pragma endregion

#pragma region 构造与析构

private:
    IMotion *_motion;

public:
    MotionService(IMotion *motion);
    ~MotionService();

#pragma endregion

#pragma region 业务逻辑

public:
    // *
    // @brief 设置全局速度
    // @param speed 输入，速度（百分比）
    // @return 成功true，失败false
    ::grpc::Status SetSpeed(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::google::protobuf::BoolValue* response) override;
    // 获取当前运动到点的状态（实时获取）
    ::grpc::Status GetMoveToPointStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetMoveToPointStatus_Response* response) override;
    // 设置寸动等级
    ::grpc::Status SetMoveStepGrade(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SetMoveStepGrade_Request* request, ::google::protobuf::BoolValue* response) override;
    // 设置当前寸动步长参数
    ::grpc::Status SetMoveStepSizePara(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::SetMoveStepSizePara_Request* request, ::google::protobuf::BoolValue* response) override;
    // 获取当前寸动步长参数
    ::grpc::Status GetMoveStepSizePara(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::GetMoveStepSizePara_Response* response) override;
    // 开始关节回零
    ::grpc::Status JointMoveToZeroStart(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 停止关节回零
    ::grpc::Status JointMoveToZeroStop(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 轴运动（开始/停止）
    // axisId:轴编号
    // turnDir:运动方向
    // pressState:运动/停止）
    ::grpc::Status AxisMove(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::AxisMove_Request* request, ::google::protobuf::BoolValue* response) override;
    // 与控制器通信 读取奇异穿越状态（由于奇异穿越并不属于实时数据，所以在某些情景下状态并不准确）
    // @return true开启 false关闭
    ::grpc::Status getSingAreaHandleStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;
    // 与控制器通信 设置奇异穿越状态
    // @param true开启 false关闭
    // @return true成功 false失败
    ::grpc::Status setSingAreaHandleStatus(::grpc::ServerContext* context, const ::google::protobuf::BoolValue* request, ::google::protobuf::BoolValue* response) override;
    // 开始对准
    ::grpc::Status AlignStart(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::MotionGrpc_AlignStart_Request* request, ::google::protobuf::BoolValue* response) override;
    // 停止对准
    ::grpc::Status AlignStop(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::google::protobuf::BoolValue* response) override;

    // 开始Movj运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    ::grpc::Status movjToPointStart(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::MovjToPointStart_Request *request, ::google::protobuf::BoolValue *response) override;
    // 停止运动到点
    ::grpc::Status moveToPointStop(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;

    // 开始Movl运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    ::grpc::Status movlToPointStart(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::MovlToPointStart_Request *request, ::google::protobuf::BoolValue *response) override;
    // 开始Jump运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    ::grpc::Status jumpToPointStart(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::JumpToPointStart_Request *request, ::google::protobuf::BoolValue *response) override;
    // 开始Jumpl运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    ::grpc::Status jumplToPointStart(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::JumplToPointStart_Request *request, ::google::protobuf::BoolValue *response) override;

#pragma endregion
};

}  // namespace InoRobBusiness
