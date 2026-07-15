#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "FieldBusGrpc.grpc.pb.h"
#include "IFieldbus.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class FieldBusService final : public FieldBusGrpc::Service
{
#pragma region 数据转换

public:
    static IOType_Grpc IOType_ToGrpc(IOType ioType);
    static IOType IOType_FromGrpc(IOType_Grpc ioType_Grpc);

    static MemoryLength_Grpc MemoryLength_ToGrpc(MemoryLength memoryLength);
    static MemoryLength MemoryLength_FromGrpc(MemoryLength_Grpc memoryLength_Grpc);

    static bool FieldbusIOMapData_ToGrpc(const FieldbusIOMapData &fieldbusIOMapData, FieldbusIOMapData_Grpc &fieldbusIOMapData_Grpc);
    static bool FieldbusIOMapData_FromGrpc(const FieldbusIOMapData_Grpc &fieldbusIOMapData_Grpc, FieldbusIOMapData &fieldbusIOMapData);

    static IOMapResetMethod_Grpc IOMapResetMethod_ToGrpc(IOMapResetMethod ioMapResetMethod);
    static IOMapResetMethod IOMapResetMethod_FromGrpc(IOMapResetMethod_Grpc ioMapResetMethod_Grpc);

#pragma endregion

#pragma region 构造与析构

private:
    IFieldbus *_fieldbus;

public:
    FieldBusService(IFieldbus *fieldbus);
    ~FieldBusService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 读取Modbus的连接状态
    ::grpc::Status readModbusConnStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::FieldBusGrpc_readModbusConnStatus_Response* response) override;
    // 写入Modbus配置
    // 返回：0-成功
    ::grpc::Status writeModbusConfig(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::FieldBusGrpc_writeModbusConfig_Request* request, ::google::protobuf::Int32Value* response) override;
    // 获取IO映射数据
    ::grpc::Status getFieldbusIOMapDatas(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::InoRobBusinessGrpc::FieldBusGrpc_getFieldbusIOMapDatas_Response* response) override;
    // 保存IO映射
    ::grpc::Status saveFieldbusIOMap(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::FieldBusGrpc_saveFieldbusIOMap_Request* request, ::google::protobuf::BoolValue* response) override;
    // 重置IO映射
    // true成功 false失败
    ::grpc::Status resetFieldbusIOMap(::grpc::ServerContext* context, const ::InoRobBusinessGrpc::FieldBusGrpc_resetFieldbusIOMap_Request* request, ::google::protobuf::BoolValue* response) override;
    // 将总线主站配置文件放入控制器中
    ::grpc::Status putFieldBusMasterCfgToController(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::FieldBusGrpc_putFieldBusMasterCfgToController_Request *request, ::google::protobuf::Int32Value *response) override;

#pragma endregion

};

}  // namespace InoRobBusiness
