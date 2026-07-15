#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../InoRobUtil/CommonEnum_V1.h"
#include "../../GlobalDataTypes_V1.h"
#include "../../DataService/DataSrvGlobal_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

enum CalibrateState_V1 : int32s
{
    // 标定成功
    CALIBRATE_SUCCESS_V1 = 0,
    // 失败（非 0）
};

// 标定模式
enum VisionCalibMode_V1 : int8u
{
    // 手动标定
    MAMUAL_CALIB_V1 = 0,
    // 半自动标定
    SEMI_AUTO_CALIB_V1 = 1,
    // 全自动标定
    FULL_AUTO_CALIB_V1 = 2,
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Calibrate_V1
{
#pragma region 构造与析构

private:
    ICalibrate *_calibrate = nullptr;

public:
    Calibrate_V1(ICalibrate *calibrate);
    ~Calibrate_V1();

#pragma endregion

#pragma region 数据转换

public:
    static CalibrateState_V1 CalibrateState_ToProxy(CalibrateState calibrateState);
    static CalibrateState CalibrateState_FromProxy(CalibrateState_V1 calibrateState_V1);

    static VisionCalibMode_V1 VisionCalibMode_ToProxy(VisionCalibMode visionCalibMode);
    static VisionCalibMode VisionCalibMode_FromProxy(VisionCalibMode_V1 visionCalibMode_V1);

#pragma endregion

#pragma region 业务逻辑

public:
    bool GetCalibRet_GripToolParmBy3P(RobPos_V1 pos1, RobPos_V1 pos2, RobPos_V1 pos3,
                                      CalibrateState_V1 &state, Pose_V1 &toolCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_GripToolParmBy3PZX(RobPos_V1 pos1, RobPos_V1 pos2, RobPos_V1 pos3, RobPos_V1 pos_o, RobPos_V1 pos_z, RobPos_V1 pos_x,
                                        CalibrateState_V1 &state, Pose_V1 &toolCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_ExternToolParmBy1P(RobPos_V1 pos_o,
                                        CalibrateState_V1 &state, Pose_V1 &toolCrd);
    bool GetCalibRet_ExternToolParmBy1PZX(RobPos_V1 pos_o, RobPos_V1 pos_z, RobPos_V1 pos_x,
                                          CalibrateState_V1 &state, Pose_V1 &toolCrd);
    bool GetCalibRet_ExternToolParmBy3P(RobPos_V1 pos1, RobPos_V1 pos2, RobPos_V1 pos3,
                                        CalibrateState_V1 &state, Pose_V1 &toolCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_ExternToolParmBy3PZX(RobPos_V1 pos1, RobPos_V1 pos2, RobPos_V1 pos3, RobPos_V1 pos_o, RobPos_V1 pos_z, RobPos_V1 pos_x,
                                          CalibrateState_V1 &state, Pose_V1 &toolCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_ExternWobj_UserParmBy3P(RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y,
                                             CalibrateState_V1 &state, Pose_V1 &usrCrd, double &offsAngle);
    bool GetCalibRet_ExternWobj_ObjParmBy3PCircle(RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y,
                                                  CalibrateState_V1 &state, Pose_V1 &usrCrd);
    bool GetCalibRet_ExternWobj_ObjParmBy3P(RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y, Pose_V1 usrCrd,
                                            CalibrateState_V1 &state, Pose_V1 &objCrd, double &offsAngle);
    bool GetCalibRet_UnFixed_ExternWobj_ObjParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y,
                                                    CalibrateState_V1 &state, Pose_V1 &objCrd, double &offsAngle);
    bool GetCalibRet_GripWobj_UserParmBy3P(RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y,
                                           CalibrateState_V1 &state, Pose_V1 &usrCrd, double &offsAngle);
    bool GetCalibRet_GripWobj_ObjParmBy3P(RobPos_V1 pos_o, RobPos_V1 pos_x, RobPos_V1 pos_y, Pose_V1 usrCrd,
                                          CalibrateState_V1 &state, Pose_V1 &objCrd, double &offsAngle);
    bool GetCalibRet_TrackBaseOnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], RobPos_V1 pos0[3],
                                                 CalibrateState_V1 &state, Pose_V1 &trackBaseCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_TrackXZOnRobBase_ParmBy6P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], RobPos_V1 pos0[6], CalibrateState_V1 &state, Pose_V1 &trackBaseCrd, ToolCalibError_V1 &calibErr, int16u mechUnitType);
    bool GetCalibRet_TrackXYZOnRobBase_ParmBy9P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], RobPos_V1 pos0[9],
                                                CalibrateState_V1 &state, Pose_V1 &trackBaseCrd, ToolCalibError_V1 &calibErr);
    bool GetCalibRet_PositionerJ1OnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], RobPos_V1 pos[3],
                                                    CalibrateState_V1 &state, Pose_V1 &positionerCrd);
    bool GetCalibRet_PositionerJnOnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH_V1], int8u curAxisNo, RobPos_V1 pos[3], Pose_V1 positionerJn_1Crd,
                                                    CalibrateState_V1 &state, Pose_V1 &positionerJnCrd);
    bool GetCalibRet_Calcu9Point(VisionCalibMode_V1 calibMode, double robotInputPoint[3][6], double distance, CalibrateState_V1 &state, double robotOutputPoint[9][6]);
    bool GetCalibRet_EyeHandCalibN(int8u cameraStyle, int8u basePointKind, double robotPoint[9][6], double robotBasePoint[2][6], double imagePoint[9][2], CalibrateState_V1 &state, double calMatrix[9], VISION_ERR_PARAM_V1 &errParam);
    bool GetCalibRet_EyeHandCalibN2(int8u cameraStyle, int8u basePointKind, double robotPoint[9][6], double robotBasePoint[3][6], double imagePoint[9][2], WobjData_V1 wObjParam, CalibrateState_V1 &state, double calMatrix[9], VISION_ERR_PARAM_V1 &errParam);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
