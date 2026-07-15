#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <QObject>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "GlobalDataTypesGrpc.pb.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"
#include "..\InoRobBusiness\Controller\Monitor\IMonitor.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class GlobalDataTypesService final 
{
#pragma region 数据转换

public:
    static bool RobPos_ToGrpc(const RobPos &robPos, RobPos_Grpc &robPos_Grpc);
    static bool RobPos_FromGrpc(const RobPos_Grpc &robPos_Grpc, RobPos &robPos);

    static bool JPos_ToGrpc(const JPos &jPos, JPos_Grpc &jPos_Grpc);
    static bool JPos_FromGrpc(const JPos_Grpc &jPos_Grpc, JPos &jPos);

    static bool Pose_ToGrpc(const Pose &pose, Pose_Grpc &pose_Grpc);
    static bool Pose_FromGrpc(const Pose_Grpc &pose_Grpc, Pose &pose);

    static bool LoadData_ToGrpc(const LoadData &loadData, LoadData_Grpc &loadData_Grpc);
    static bool LoadData_FromGrpc(const LoadData_Grpc &loadData_Grpc, LoadData &loadData);

    static bool ToolData_ToGrpc(const ToolData &toolData, ToolData_Grpc &toolData_Grpc);
    static bool ToolData_FromGrpc(const ToolData_Grpc &toolData_Grpc, ToolData &toolData);

    static bool WobjData_ToGrpc(const WobjData &wobjData, WobjData_Grpc &wobjData_Grpc);
    static bool WobjData_FromGrpc(const WobjData_Grpc &wobjData_Grpc, WobjData &wobjData);

    static RBTTYPE_E_Grpc RBTTYPE_E_ToGrpc(RBTTYPE_E rbtTYPE_E);
    static RBTTYPE_E RBTTYPE_E_FromGrpc(RBTTYPE_E_Grpc rbtTYPE_E_Grpc);

    static CoordType_Grpc CoordType_ToGrpc(CoordType coordType);
    static CoordType CoordType_FromGrpc(CoordType_Grpc coordType_Grpc);

    static PosFormat_Grpc PosFormat_ToGrpc(PosFormat posFormat);
    static PosFormat PosFormat_FromGrpc(PosFormat_Grpc posFormat_Grpc);

    static bool ModbusTCP_Para_ToGrpc(const ModbusTCP_Para &modbusTCP_Para, ModbusTCP_Para_Grpc &modbusTCP_Para_Grpc);
    static bool ModbusTCP_Para_FromGrpc(const ModbusTCP_Para_Grpc &modbusTCP_Para_Grpc, ModbusTCP_Para &modbusTCP_Para);

    static bool ModbusRTU_Para_ToGrpc(const ModbusRTU_Para &modbusRTU_Para, ModbusRTU_Para_Grpc &modbusRTU_Para_Grpc);
    static bool ModbusRTU_Para_FromGrpc(const ModbusRTU_Para_Grpc &modbusRTU_Para_Grpc, ModbusRTU_Para &modbusRTU_Para);

    static bool ModbusParaConfig_ToGrpc(const ModbusParaConfig &modbusParaConfig, ModbusParaConfig_Grpc &modbusParaConfig_Grpc);
    static bool ModbusParaConfig_FromGrpc(const ModbusParaConfig_Grpc &modbusParaConfig_Grpc, ModbusParaConfig &modbusParaConfig);

    static bool ModbusConnectSts_ToGrpc(const ModbusConnectSts &modbusConnectSts, ModbusConnectSts_Grpc &modbusConnectSts_Grpc);

    static bool ErrsaveSta_ToGrpc(const ErrsaveSta &errsaveSta, ErrsaveSta_Grpc &errsaveSta_Grpc);
    static bool ErrsaveSta_FromGrpc(const ErrsaveSta_Grpc &errsaveSta_Grpc, ErrsaveSta &errsaveSta);

    static bool ErrexportSta_ToGrpc(const ErrexportSta &errexportSta, ErrexportSta_Grpc &errexportSta_Grpc);
    static bool ErrexportSta_FromGrpc(const ErrexportSta_Grpc &errexportSta_Grpc, ErrexportSta &errexportSta);

    static MechUnitType_Grpc MechUnitType_ToGrpc(MechUnitType mechUnitType);
    static MechUnitType MechUnitType_FromGrpc(MechUnitType_Grpc mechUnitType_Grpc);

    static MechUnitStatus_Grpc MechUnitStatus_ToGrpc(MechUnitStatus mechUnitStatus);
    static MechUnitStatus MechUnitStatus_FromGrpc(MechUnitStatus_Grpc mechUnitStatus_Grpc);

    static bool MechUnitInfo_ToGrpc(const MechUnitInfo &mechUnitInfo, MechUnitInfo_Grpc &mechUnitInfo_Grpc);
    static bool MechUnitInfo_FromGrpc(const MechUnitInfo_Grpc &mechUnitInfo_Grpc, MechUnitInfo &mechUnitInfo);

    static CsCalibPoints_Grpc CsCalibPoints_ToGrpc(CsCalibPoints csCalibPoints);
    static CsCalibPoints CsCalibPoints_FromGrpc(CsCalibPoints_Grpc csCalibPoints_Grpc);

#pragma endregion
};

}  // namespace InoRobBusiness
