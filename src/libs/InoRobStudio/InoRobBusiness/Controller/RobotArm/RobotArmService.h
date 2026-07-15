#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "RobotArmGrpc.grpc.pb.h"
#include "IRobotArm.h"
#include "CrashDetection/ICrashDetection.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class RobotArmService final : public RobotArmGrpc::Service
{
#pragma region 数据转换

public:
    static DevModeEnum_Grpc DevModeEnum_ToGrpc(ICrashDetection::DevModeEnum devModeEnum);
    static ICrashDetection::DevModeEnum DevModeEnum_FromGrpc(DevModeEnum_Grpc devModeEnum_Grpc);

    static bool ColDetectPara_ToGrpc(const ColDetectPara &colDetectPara, ColDetectPara_Grpc &colDetectPara_Grpc);
    static bool ColDetectPara_FromGrpc(const ColDetectPara_Grpc &colDetectPara_Grpc, ColDetectPara &colDetectPara);

#pragma endregion

#pragma region 构造与析构

private:
    IRobotArm *_robotArm;

public:
    RobotArmService(IRobotArm *robotArm);
    ~RobotArmService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取当前绝对零点值
    ::grpc::Status getAbsZeroValue(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getAbsZeroValue_Response* response) override;
    // 保存绝对零点值至控制器
    // 返回值：0表示成功，其它表示失败
    ::grpc::Status saveAbsZeroValue(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::saveAbsZeroValue_Request* request, ::google::protobuf::Int32Value* response) override;
    // 从控制器中读取工作原点
    // 参数：工作原点序号
    ::grpc::Status ReadWorkOriginPts(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::InoRobBusinessGrpc::ReadWorkOriginPts_Response* response) override;
    // 保存工作原点的数据
    // 返回值：0表示成功，其它表示失败
    ::grpc::Status saveWorkOriginData(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::saveWorkOriginData_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取最大允许关节速度（运动）
    ::grpc::Status getAxisMaxSpeed(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getAxisMaxSpeed_Response* response) override;
    // 保存最大允许关节速度（运动）
    // 返回值：0表示成功，其它表示失败
    ::grpc::Status saveAxisMaxSpeed(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::saveAxisMaxSpeed_Request* request, ::google::protobuf::Int32Value* response) override;
    // 读碰撞检测参数
    ::grpc::Status readColDetectPara(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::readColDetectPara_Request* request, ::InoRobBusinessGrpc::readColDetectPara_Response* response) override;
    // 写碰撞检测参数
    // @return 0:成功 其他:错误码
    ::grpc::Status writeColDetectPara(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::writeColDetectPara_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取当前电机位置
    ::grpc::Status getCurrMotorPos(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::getCurrMotorPos_Response* response) override;
    // 获取轴正向极限
    ::grpc::Status getPosLimit(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::RobotArmGrpc_getPosLimit_Response* response) override;
    // 获取负极限
    ::grpc::Status getNegLimit(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::RobotArmGrpc_getNegLimit_Response* response) override;
    // 保存设置的正极限和负极限
    // return 0-保存成功
    ::grpc::Status savePosLimitAndNegLimit(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::RobotArmGrpc_savePosLimitAndNegLimit_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取最大允许关节加速度（示教）
    ::grpc::Status getTeachAxisMaxAcc(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::RobotArmGrpc_getAxisMaxAcc_Response* response) override;
    // 保存最大允许关节加速度（示教）
    // @return 0:成功 其他:错误码
    ::grpc::Status saveTeachAxisMaxAcc(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::RobotArmGrpc_saveAxisMaxAcc_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取最大允许关节加速度（运动）
    ::grpc::Status getAxisMaxAcc(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::RobotArmGrpc_getAxisMaxAcc_Response* response) override;
    // 保存最大允许关节加速度（运动）
    // @return 0:成功 其他:错误码
    ::grpc::Status saveAxisMaxAcc(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::RobotArmGrpc_saveAxisMaxAcc_Request* request, ::google::protobuf::Int32Value* response) override;
    // 向控制器发送保存文件命令
    ::grpc::Status saveFileCommond(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::google::protobuf::BoolValue *response) override;

#pragma endregion

};

}  // namespace InoRobBusiness
