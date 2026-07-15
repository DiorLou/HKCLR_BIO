#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../Monitor/Monitor_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define LISTTOTAL_ROW_NUM_V1 24                // 轴属性列表总行数, 22版本为18, 后续版本为24
constexpr int INDAXIS_STATUS_MAX_NUM_V1 = 14;  // 独立轴状态最大数量
constexpr int INDAXIS_MAX_NUM_V1 = 7;          // 独立轴最大数量

// 机器人安装类型
enum RobotInstallType_V1 : int32s
{
    INSTALL_TYPE_ROBOT_FIXED_V1 = 0,             // 固定安装
    INSTALL_TYPE_ROBOT_INSTALL_TO_TRACK_V1 = 1,  // 在可移动的导轨上
};

// 轴编号ID
enum ExternalAxisNum_V1 : int32s
{
    EXTER_AXIS_NUM_NULL_V1 = 0xff,  // 逻辑轴为空，目前功能上暂不支持，可以用为初始化数据，页面不显示，请注意
    EXTER_AXIS_NUM_E1_V1 = 0,       // 作为E1
    EXTER_AXIS_NUM_E2_V1 = 1,       // 作为E2
    EXTER_AXIS_NUM_E3_V1 = 2,       // 作为E3
    EXTER_AXIS_NUM_E4_V1 = 3,       // 作为E4
    EXTER_AXIS_NUM_E5_V1 = 4,       // 作为E5
    EXTER_AXIS_NUM_E6_V1 = 5,       // 作为E6
};

// 转换关系
enum RelativeObject_V1 : int32s
{
    RELATIVE_OBJ_WORLD_V1 = -1,  // 到世界坐标
    RELATIVE_OBJ_BASE_V1 = 0,    // 机器人基坐标
    RELATIVE_OBJ_J1_V1 = 1,      // J1轴
    RELATIVE_OBJ_J2_V1 = 2,      // J2轴
    RELATIVE_OBJ_J3_V1 = 3,      // J3轴
    RELATIVE_OBJ_J4_V1 = 4,      // J4轴
    RELATIVE_OBJ_J5_V1 = 5,      // J5轴
    RELATIVE_OBJ_J6_V1 = 6,      // J6轴
};

// 外部轴类型
enum ExternalAxisType_V1 : int32s
{
    EXTER_AXIS_TYPE_ROTATE_AXIS_V1 = 0,  // 旋转轴
    EXTER_AXIS_TYPE_LINEAR_AXIS_V1 = 1,  // 线性轴
};

enum ExternalAxisMoveType_V1 : int32s
{
    EXTER_AXIS_MOVE_TYPE_ROTATE_TO_ROTATE_V1 = 0,  // 旋转-旋转
    EXTER_AXIS_MOVE_TYPE_ROTATE_TO_LINEAR_V1 = 1,  // 旋转-直线
    EXTER_AXIS_MOVE_TYPE_LINEAR_TO_ROTATE_V1 = 2,  // 直线-旋转
    EXTER_AXIS_MOVE_TYPE_LINEAR_TO_LINEAR_V1 = 3   // 直线-直线
};

// 外部轴驱动器类型
enum ExternalAxisDeviceType_V1 : int32s
{
    DEVICE_SV620N_V1 = 0,      // SV620
    DEVICE_SV660N_V1 = 1,      // SV660
    DEVICE_SV680N_V1 = 2,      // SV680
    DEVICE_SV680LN_V1 = 3,     // SV680LN
    DEVICE_SV660N_STOP_V1 = 4  // SV660 点焊
};

// 独立轴支持标志
enum IndependantAxisSupportFlag_V1 : int32s
{
    NOT_SUPPORT_V1 = 0,
    SUPPORT_V1 = 1,
};

// 外部轴伺服控制模式类型
enum ExternalAxisServoControlType_V1 : int32s
{
    SERVO_LOCATION_TYPE_V1 = 8,  // 位置模式
    SERVO_SPEED_TYPE_V1 = 9,     // 速度模式
    SERVO_TORQUE_TYPE_V1 = 10,   // 转矩模式
};

// 标定方法
enum MechUnitCalibMethod_V1 : int32s
{
    MECH_UNIT_CALIB_METHOD_THREE_POINT_V1 = 0,             // 三点法
    MECH_UNIT_CALIB_METHOD_THREE_POINT_ROTATE_V1 = 1,      // 三点旋转法
    MECH_UNIT_CALIB_METHOD_KNOWN_ONE_POINT_ZX_V1 = 2,      // 已知工具一点TCP+ZX
    MECH_UNIT_CALIB_METHOD_UNKNOWN_THREE_POINT_ZX_V1 = 3,  // 未知工具三点TCP+ZX
    MECH_UNIT_CALIB_METHOD_SIX_POINT_V1 = 4,               // 六点法
    MECH_UNIT_CALIB_METHOD_NINE_POINT_V1 = 5,              // 九点法
};

// 示教点
enum MechUnitTeachingPoint_V1 : int32s
{
    MECH_UNIT_TEACHING_POINT_ONE_V1 = 0,    // 点1
    MECH_UNIT_TEACHING_POINT_TWO_V1 = 1,    // 点2
    MECH_UNIT_TEACHING_POINT_THREE_V1 = 2,  // 点3
    MECH_UNIT_TEACHING_POINT_DATUM_V1 = 3,  // 基准点
    MECH_UNIT_TEACHING_POINT_Z_POS_V1 = 4,  // 点Z+
    MECH_UNIT_TEACHING_POINT_X_POS_V1 = 5,  // 点X+
};

// 独立轴电机转向类型结构体
enum IndAxisMotorRotationType_V1 : int16u
{
    MOTOR_ROTATION_TYPE_REVERSE_V1 = 0,  // 逆向
    MOTOR_ROTATION_TYPE_FORWARD_V1 = 1   // 正向
};

// 机械单元常用数据结构体
typedef struct _MECH_UNIT_DATA_V1
{
    string mechUnitName;              // 机械单元名称
    MechUnitType_V1 mechUnitType;     // 机械单元类型
    int axisCount;                    // 轴数
    RobotInstallType_V1 installType;  // 安装类型（针对机器人）
    string moveMechName;              // 移动机械名称
} MechUnitData_V1;

// 提示信息结构体
typedef struct _PROMPT_MSG_V1
{
    string Caption;
    string TextMessage;
} PromptMsg_V1;

// 机械单元类型名称结构体
typedef struct _MECH_UNIT_TYPE_NAME_STRUCT_V1
{
    MechUnitType_V1 type;
    string name;
} MechUnitTypeNameStruct_V1;

// 机械单元类型对应轴数结构体
typedef struct _MECH_UNIT_TYPE_AXIS_COUNT_V1
{
    MechUnitType_V1 type;
    int axisCount;
} MechUnitTypeAxisCountStruct_V1;

// 外部轴的逻辑轴对应名称结构体
typedef struct _EXTERNAL_AXIS_NUM_STRUCT_V1
{
    ExternalAxisNum_V1 axisNum;
    string str;
} ExternalAxisNumStruct_V1;

// 转换关系对应名称结构体
typedef struct _RELATIVE_OBJ_STRUCT_V1
{
    RelativeObject_V1 obj;
    string relativeObjName;
} RelativeObjStruct_V1;

// 外部轴类型对应名称结构体
typedef struct _EXTERNAL_AXIS_TYPE_STRUCT_V1
{
    ExternalAxisType_V1 type;
    string name;
} ExternalAxisTypeStruct_V1;

// 外部轴运动类型对应名称结构体
typedef struct _EXTERNAL_AXIS_MOVE_TYPE_STRUCT_V1
{
    ExternalAxisMoveType_V1 type;
    string name;
} ExternalAxisMoveTypeStruct_V1;

// 外部轴设备类型对应名称结构体
typedef struct _EXTERNAL_AXIS_DRVICE_TYPE_STRUCT_V1
{
    ExternalAxisDeviceType_V1 type;
    string name;
} ExternalAxisDrviceTypeStruct_V1;

// 独立轴支持标志
typedef struct _INDEPENDANT_AXIS_SUPPORT_FLAG_STRUCT_V1
{
    IndependantAxisSupportFlag_V1 type;
    string name;
} IndependantAxisSupportFlagStruct_V1;

// 外部轴伺服控制类型对应名称结构体
typedef struct _EXTERNAL_AXIS_SERVO_CONTROL_TYPE_STRUCT_V1
{
    ExternalAxisServoControlType_V1 type;
    string name;
} ExternalAxisServoControlTypeStruct_V1;

// 运动类型对应名称结构体
typedef struct _EXECUTE_MOVE_TYPE_STRUCT_V1
{
    MoveType_V1 type;
    string name;
} ExecuteMoveTypeStruct_V1;

// 标定方法对应点数结构体
typedef struct _CALIB_POINT_COUNT_STRUCT_V1
{
    MechUnitCalibMethod_V1 method;
    int count;
} CalibPointCountStruct_V1;

// 标定方法对应名称结构体
typedef struct _CALIB_METHOD_NAME_STRUCT_V1
{
    MechUnitCalibMethod_V1 method;
    string name;
} CalibMethodNameStruct_V1;

// 机械单元对应的标定方法结构体
typedef struct _MECH_UNIT_CALIB_METHOD_STRUCT_V1
{
    MechUnitType_V1 type;
    string methodList;
} MechUnitCalibMethodStruct_V1;

// 示教点对应名称结构体
typedef struct _TEACHING_POINT_NAME_STRUCT_V1
{
    MechUnitTeachingPoint_V1 point;
    string name;
} MechUnitTeachingPointNameStruct_V1;

typedef struct _MECH_UNIT_CALIB_METHOD_TEACH_POINT_STRUCT_V1
{
    MechUnitCalibMethod_V1 method;
    string name;
} MechUnitCalibMethodTeachPointStruct_V1;

// 独立轴电机轴转向类型名称结构体
typedef struct _MECH_UNIT_IND_MOTOR_TYPE_STRUCT_V1
{
    IndAxisMotorRotationType_V1 type;
    string name;
} IndAxisMotorRotationTypeStruct_V1;

// 轴属性中的列表名
typedef struct _BUS_EXT_AXIS_PARAM_LIST_V1
{
    std::string strParamName;  // 参数名
    std::string strValue;      // 值
    std::string strRange;      // 范围
} BUS_EXT_AXIS_PARAM_LIST_V1;

// 独立轴中的列表名
typedef struct _BUS_IND_AXIS_PARAM_LIST_V1
{
    std::string mechName;          // 机械单元名称
    std::string axisIndexName;     // 轴名称
    std::string isSupportIndAxis;  // 是否支持独立轴
} BUS_IND_AXIS_PARAM_LIST_V1;

typedef unsigned char IndAxisStatus_V1[14];

// 轴属性每一行意义
enum ExternalPropName_V1
{
    SV_TYPE_V1 = 0,              // 伺服类型620N = 0,660N = 1(默认值660N)
    OP_MODE_V1,                  // 伺服驱动模式  8-位置模式；9-速度模式;10-转矩模式 （待定）
    AXIS_TYPE_V1,                // 电机轴属性 0-旋转轴;线性轴不开放（1-线性轴）
    MOVE_TYPE_V1,                // 传动方向 0、转动-转动  1、转动-直线
    PHY_TRANS_RATIO_V1,          // 物理传动化
    ABS_ZERO_POINT_V1,           // 零点
    POS_LMT_V1,                  // 正限位
    NEG_LMT_V1,                  // 负限位
    PARA_VEL_V1,                 // 示教速度
    PARA_ACC_V1,                 // 示教加速度
    MAX_SPEED_V1,                // 最大速度
    MAX_ACC_SPEED_V1,            // 最大加速度
    STOP_DEC_SPEED_V1,           // 停机减速度
    FOLLOW_ERR_V1,               // 跟随误差
    INPOS_ERR_V1,                // 到位误差
    INPOS_TIME_V1,               // 到位时间
    CURRENT_LIMIT_V1,            // 最大电流报警阈值
    AVERAGE_LOAD_RATE_LIMIT_V1,  // 平均负载率报警阈值
    IS_SUPPORT_INDAXIS_V1,       // 是否支持独立轴
    INDAXIS_NEGLIMIT_V1,         // 独立轴负限位
    INDAXIS_POSLIMIT_V1,         // 独立轴正限位
    SPEED_ARRIVAL_ERROR_V1,      // 速度到位误差
    SPEED_ARRIVAL_TIME_V1,       // 速度到位时间
    SPEED_TRACKING_ERROR_V1,     // 速度跟随误差阈值
};

// 可变的属性范围结构体
typedef struct _VariableAxisAttribute_V1
{
    // 机械单元
    MechUnitType_V1 mechUnitType;
    // 电机轴属性集合
    vector<ExternalAxisTypeStruct_V1> vecVariableAxisType;
    // 外部轴运动类型集合
    vector<ExternalAxisMoveTypeStruct_V1> vecVariableAxisMoveType;
} VariableAxisAttribute_V1;

#pragma endregion

class INOROBBUSINESSPROXY_CLASS MechUnitManage_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static RobotInstallType_V1 RobotInstallType_ToProxy(RobotInstallType robotInstallType);
    static RobotInstallType RobotInstallType_FromProxy(RobotInstallType_V1 robotInstallType_V1);

    static ExternalAxisNum_V1 ExternalAxisNum_ToProxy(ExternalAxisNum externalAxisNum);
    static ExternalAxisNum ExternalAxisNum_FromProxy(ExternalAxisNum_V1 externalAxisNum_V1);

    static RelativeObject_V1 RelativeObject_ToProxy(RelativeObject relativeObject);
    static RelativeObject RelativeObject_FromProxy(RelativeObject_V1 relativeObject_V1);

    static ExternalAxisType_V1 ExternalAxisType_ToProxy(ExternalAxisType externalAxisType);
    static ExternalAxisType ExternalAxisType_FromProxy(ExternalAxisType_V1 externalAxisType_V1);

    static ExternalAxisMoveType_V1 ExternalAxisMoveType_ToProxy(ExternalAxisMoveType externalAxisMoveType);
    static ExternalAxisMoveType ExternalAxisMoveType_FromProxy(ExternalAxisMoveType_V1 externalAxisMoveType_V1);

    static ExternalAxisDeviceType_V1 ExternalAxisDeviceType_ToProxy(ExternalAxisDeviceType externalAxisDeviceType);
    static ExternalAxisDeviceType ExternalAxisDeviceType_FromProxy(ExternalAxisDeviceType_V1 externalAxisDeviceType_V1);

    static IndependantAxisSupportFlag_V1 IndependantAxisSupportFlag_ToProxy(IndependantAxisSupportFlag independantAxisSupportFlag);
    static IndependantAxisSupportFlag IndependantAxisSupportFlag_FromProxy(IndependantAxisSupportFlag_V1 independantAxisSupportFlag_V1);

    static ExternalAxisServoControlType_V1 ExternalAxisServoControlType_ToProxy(ExternalAxisServoControlType externalAxisServoControlType);
    static ExternalAxisServoControlType ExternalAxisServoControlType_FromProxy(ExternalAxisServoControlType_V1 externalAxisServoControlType_V1);

    static MechUnitCalibMethod_V1 MechUnitCalibMethod_ToProxy(MechUnitCalibMethod mechUnitCalibMethod);
    static MechUnitCalibMethod MechUnitCalibMethod_FromProxy(MechUnitCalibMethod_V1 mechUnitCalibMethod_V1);

    static MechUnitTeachingPoint_V1 MechUnitTeachingPoint_ToProxy(MechUnitTeachingPoint mechUnitTeachingPoint);
    static MechUnitTeachingPoint MechUnitTeachingPoint_FromProxy(MechUnitTeachingPoint_V1 mechUnitTeachingPoint_V1);

    static IndAxisMotorRotationType_V1 IndAxisMotorRotationType_ToProxy(IndAxisMotorRotationType indAxisMotorRotationType);
    static IndAxisMotorRotationType IndAxisMotorRotationType_FromProxy(IndAxisMotorRotationType_V1 indAxisMotorRotationType_V1);

    static ExternalPropName_V1 ExternalPropName_ToProxy(ExternalPropName externalPropName);
    static ExternalPropName ExternalPropName_FromProxy(ExternalPropName_V1 externalPropName_V1);

    static bool MechUnitData_ToProxy(const MechUnitData &mechUnitData, MechUnitData_V1 &mechUnitData_V1);
    static bool MechUnitData_FromProxy(const MechUnitData_V1 &mechUnitData_V1, MechUnitData &mechUnitData);

    static bool PromptMsg_ToProxy(const PromptMsg &promptMsg, PromptMsg_V1 &promptMsg_V1);
    static bool PromptMsg_FromProxy(const PromptMsg_V1 &promptMsg_V1, PromptMsg &promptMsg);

    static bool MechUnitTypeNameStruct_ToProxy(const MechUnitTypeNameStruct &mechUnitTypeNameStruct, MechUnitTypeNameStruct_V1 &mechUnitTypeNameStruct_V1);
    static bool MechUnitTypeNameStruct_FromProxy(const MechUnitTypeNameStruct_V1 &mechUnitTypeNameStruct_V1, MechUnitTypeNameStruct &mechUnitTypeNameStruct);

    static bool MechUnitTypeAxisCountStruct_ToProxy(const MechUnitTypeAxisCountStruct &mechUnitTypeAxisCountStruct, MechUnitTypeAxisCountStruct_V1 &mechUnitTypeAxisCountStruct_V1);
    static bool MechUnitTypeAxisCountStruct_FromProxy(const MechUnitTypeAxisCountStruct_V1 &mechUnitTypeAxisCountStruct_V1, MechUnitTypeAxisCountStruct &mechUnitTypeAxisCountStruct);

    static bool ExternalAxisNumStruct_ToProxy(const ExternalAxisNumStruct &externalAxisNumStruct, ExternalAxisNumStruct_V1 &externalAxisNumStruct_V1);
    static bool ExternalAxisNumStruct_FromProxy(const ExternalAxisNumStruct_V1 &externalAxisNumStruct_V1, ExternalAxisNumStruct &externalAxisNumStruct);

    static bool RelativeObjStruct_ToProxy(const RelativeObjStruct &relativeObjStruct, RelativeObjStruct_V1 &relativeObjStruct_V1);
    static bool RelativeObjStruct_FromProxy(const RelativeObjStruct_V1 &relativeObjStruct_V1, RelativeObjStruct &relativeObjStruct);

    static bool ExternalAxisTypeStruct_ToProxy(const ExternalAxisTypeStruct &externalAxisTypeStruct, ExternalAxisTypeStruct_V1 &externalAxisTypeStruct_V1);
    static bool ExternalAxisTypeStruct_FromProxy(const ExternalAxisTypeStruct_V1 &externalAxisTypeStruct_V1, ExternalAxisTypeStruct &externalAxisTypeStruct);

    static bool ExternalAxisMoveTypeStruct_ToProxy(const ExternalAxisMoveTypeStruct &externalAxisMoveTypeStruct, ExternalAxisMoveTypeStruct_V1 &externalAxisMoveTypeStruct_V1);
    static bool ExternalAxisMoveTypeStruct_FromProxy(const ExternalAxisMoveTypeStruct_V1 &externalAxisMoveTypeStruct_V1, ExternalAxisMoveTypeStruct &externalAxisMoveTypeStruct);

    static bool ExternalAxisDrviceTypeStruct_ToProxy(const ExternalAxisDrviceTypeStruct &externalAxisDrviceTypeStruct, ExternalAxisDrviceTypeStruct_V1 &externalAxisDrviceTypeStruct_V1);
    static bool ExternalAxisDrviceTypeStruct_FromProxy(const ExternalAxisDrviceTypeStruct_V1 &externalAxisDrviceTypeStruct_V1, ExternalAxisDrviceTypeStruct &externalAxisDrviceTypeStruct);

    static bool IndependantAxisSupportFlagStruct_ToProxy(const IndependantAxisSupportFlagStruct &independantAxisSupportFlagStruct, IndependantAxisSupportFlagStruct_V1 &independantAxisSupportFlagStruct_V1);
    static bool IndependantAxisSupportFlagStruct_FromProxy(const IndependantAxisSupportFlagStruct_V1 &independantAxisSupportFlagStruct_V1, IndependantAxisSupportFlagStruct &independantAxisSupportFlagStruct);

    static bool ExternalAxisServoControlTypeStruct_ToProxy(const ExternalAxisServoControlTypeStruct &externalAxisServoControlTypeStruct, ExternalAxisServoControlTypeStruct_V1 &externalAxisServoControlTypeStruct_V1);
    static bool ExternalAxisServoControlTypeStruct_FromProxy(const ExternalAxisServoControlTypeStruct_V1 &externalAxisServoControlTypeStruct_V1, ExternalAxisServoControlTypeStruct &externalAxisServoControlTypeStruct);

    static bool ExecuteMoveTypeStruct_ToProxy(const ExecuteMoveTypeStruct &executeMoveTypeStruct, ExecuteMoveTypeStruct_V1 &executeMoveTypeStruct_V1);
    static bool ExecuteMoveTypeStruct_FromProxy(const ExecuteMoveTypeStruct_V1 &executeMoveTypeStruct_V1, ExecuteMoveTypeStruct &executeMoveTypeStruct);

    static bool CalibPointCountStruct_ToProxy(const CalibPointCountStruct &calibPointCountStruct, CalibPointCountStruct_V1 &calibPointCountStruct_V1);
    static bool CalibPointCountStruct_FromProxy(const CalibPointCountStruct_V1 &calibPointCountStruct_V1, CalibPointCountStruct &calibPointCountStruct);

    static bool CalibMethodNameStruct_ToProxy(const CalibMethodNameStruct &calibMethodNameStruct, CalibMethodNameStruct_V1 &calibMethodNameStruct_V1);
    static bool CalibMethodNameStruct_FromProxy(const CalibMethodNameStruct_V1 &calibMethodNameStruct_V1, CalibMethodNameStruct &calibMethodNameStruct);

    static bool MechUnitCalibMethodStruct_ToProxy(const MechUnitCalibMethodStruct &mechUnitCalibMethodStruct, MechUnitCalibMethodStruct_V1 &mechUnitCalibMethodStruct_V1);
    static bool MechUnitCalibMethodStruct_FromProxy(const MechUnitCalibMethodStruct_V1 &mechUnitCalibMethodStruct_V1, MechUnitCalibMethodStruct &mechUnitCalibMethodStruct);

    static bool MechUnitTeachingPointNameStruct_ToProxy(const MechUnitTeachingPointNameStruct &mechUnitTeachingPointNameStruct, MechUnitTeachingPointNameStruct_V1 &mechUnitTeachingPointNameStruct_V1);
    static bool MechUnitTeachingPointNameStruct_FromProxy(const MechUnitTeachingPointNameStruct_V1 &mechUnitTeachingPointNameStruct_V1, MechUnitTeachingPointNameStruct &mechUnitTeachingPointNameStruct);

    static bool MechUnitCalibMethodTeachPointStruct_ToProxy(const MechUnitCalibMethodTeachPointStruct &mechUnitCalibMethodTeachPointStruct, MechUnitCalibMethodTeachPointStruct_V1 &mechUnitCalibMethodTeachPointStruct_V1);
    static bool MechUnitCalibMethodTeachPointStruct_FromProxy(const MechUnitCalibMethodTeachPointStruct_V1 &mechUnitCalibMethodTeachPointStruct_V1, MechUnitCalibMethodTeachPointStruct &mechUnitCalibMethodTeachPointStruct);

    static bool IndAxisMotorRotationTypeStruct_ToProxy(const IndAxisMotorRotationTypeStruct &indAxisMotorRotationTypeStruct, IndAxisMotorRotationTypeStruct_V1 &indAxisMotorRotationTypeStruct_V1);
    static bool IndAxisMotorRotationTypeStruct_FromProxy(const IndAxisMotorRotationTypeStruct_V1 &indAxisMotorRotationTypeStruct_V1, IndAxisMotorRotationTypeStruct &indAxisMotorRotationTypeStruct);

    static bool BUS_EXT_AXIS_PARAM_LIST_ToProxy(const BUS_EXT_AXIS_PARAM_LIST &bus_EXT_AXIS_PARAM_LIST, BUS_EXT_AXIS_PARAM_LIST_V1 &bus_EXT_AXIS_PARAM_LIST_V1);
    static bool BUS_EXT_AXIS_PARAM_LIST_FromProxy(const BUS_EXT_AXIS_PARAM_LIST_V1 &bus_EXT_AXIS_PARAM_LIST_V1, BUS_EXT_AXIS_PARAM_LIST &bus_EXT_AXIS_PARAM_LIST);

    static bool BUS_IND_AXIS_PARAM_LIST_ToProxy(const BUS_IND_AXIS_PARAM_LIST &bus_IND_AXIS_PARAM_LIST, BUS_IND_AXIS_PARAM_LIST_V1 &bus_IND_AXIS_PARAM_LIST_V1);
    static bool BUS_IND_AXIS_PARAM_LIST_FromProxy(const BUS_IND_AXIS_PARAM_LIST_V1 &bux_IND_AXIS_PARAM_LIST_V1, BUS_IND_AXIS_PARAM_LIST &bus_IND_AXIS_PARAM_LIST);

    static bool VariableAxisAttribute_ToProxy(const VariableAxisAttribute &variableAxisAttribute, VariableAxisAttribute_V1 &variableAxisAttribute_V1);
    static bool VariableAxisAttribute_FromProxy(const VariableAxisAttribute_V1 &variableAxisAttribute_V1, VariableAxisAttribute &variableAxisAttribute);

#pragma endregion

#pragma region 构造与析构

private:
    IMechUnitManage *_mechUnitManage = nullptr;

public:
    MechUnitManage_V1(IMechUnitManage *mechUnitManage);
    ~MechUnitManage_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取机械单元数量
    int GetMechUnitCount();
    // 获取机械单元列表
    vector<MechUnitData_V1> GetMechUnitList();
    // 添加机械单元
    bool AddMechUnit(int type, char *name);
    // 删除机械单元
    bool RemoveMechUnit(char *name);
    // 获取数据
    // void GetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData);
    // 设置数据
    // void SetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData);
    // 取当前工具号
    int GetCurTool();
    // 取机器人当前点
    bool GetCurRobPos(MechUnitCalibMethod_V1 calibMethod, RobPos_V1 &pos);
    // 外部轴取当前点做为零点值
    bool RecordAbsZero(string mechUnitName, int axisIndex, int &value);
    // 运动到点
    bool MoveToPoint(MechUnitCalibMethod_V1 calibMethod, MoveType_V1 moveType, RobPos_V1 mPos, double lH, double mH, double rH);
    // 停止运动到点
    bool StopToPoint();
    //(PC)检查使用权限(管理员以上、控制权：PC)
    bool PCCheckAuthority();
    //(TP)检查使用权限(管理员以上、控制权：TP)
    bool TPCheckAuthority();
    // 检查保存许可（需要急停、示教模式下）
    bool CheckSavePermission();
    // 检查数据是否有修改(单个机械单元级别)
    bool CheckMechUnitDataModified(string mechUnitName);
    // 检查更新机械单元名称许可
    bool checkModifyMechUnitNamePerm(const std::string &newMechName);
    // 创建机械单元默认名称(相同类型，都使用默认名称，往后加索引)
    string CreateDefaultNameByMechUnitType(MechUnitType_V1 mechUnitType);
    // 计算标定结果(传入数组指针和数据数量，标定类型)
    bool CalculateCalibResult(RobPos_V1 calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT_V1], MechUnitCalibMethod_V1 calibMethod, string unitName, Pose_V1 previousAxisPos, int axisNum, Pose_V1 &pos);
    // 计算XYZ和XZ导轨标定结果(传入数组指针和数据数量，标定类型)
    bool CalculateTrackCalibResult(RobPos_V1 calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT_V1], MechUnitCalibMethod_V1 calibMethod, string unitName, int axisNum, Pose_V1 *pos, int16u mechUnitType);
    // 从控制器获取机械单元配置文件和标定文件并反序列化
    bool ReadMechUnitCfgAndCalibDataFromFile();
    // 将机械单元配置和标定数据序列化并下载到控制器
    bool WriteMechUnitCfgAndCalibDataToFile();
    // 发送非实时命令让控制器解析
    bool WriteMechUnitsCfg();
    // 读机械单元配置控制器是否配置成功信息
    int readMechUnitsCfg();
    // 修改机械单元名称
    void modifyMechName(const std::string &currMechName, const std::string &newMechName);
    // 根据机械单元下标号及选中的轴号更新轴属性数据
    vector<BUS_EXT_AXIS_PARAM_LIST_V1> updateAxisDefaultDataByMechType(const int guideIndex, const int curSelectAxisIndex);
    // 获取机器人独立轴数据
    vector<BUS_EXT_AXIS_PARAM_LIST_V1> getRobotIndAxisData();
    // 获取机械单元各轴的独立轴信息
    vector<BUS_IND_AXIS_PARAM_LIST_V1> getAllMechUnitIsSupportIndAxisData();
    // 设置机器人独立轴属性
    void setRobotIndAxisAttribute(const int indAxisEnum, string &value);
    // 根据机械单元及轴号获取未使用的轴逻辑
    // vector<int> readUnusedAxisLogicByMechUnit(const MechUnit &mechUnit, const int axisIndex);
    // 更新机械单元的轴映射和外部轴ID
    void updateMechUnitAxisMapAndAxisID(int8u curAxisLogic[EXT_AXIS_NUM_V1], int guideIndex);
    // 检查机械转换表格中的XYZABC数据是否合理，超出则返回边界值
    double checkMechTransValueIsValid(const int column, const double value);
    // 检查轴属性表双击处是否需要修改
    int checkAxisAttributeIsNeedChanged(const int row);
    // 设置轴属性表中要修改的值，不符合要求自动设置一个合理值，并返回
    void setAxisAttributeValue(const int row, string &value, const int guideIndex, const int curSelectAxisIndex);
    // 取当前值为零点值
    void setCurrValueAsHomePoint(const int guideIndex, const int currAxisIndex);
    // 外部轴组态文件配置
    int externalAxisForceConfig();
    // 标定权限检查
    bool checkPermissionInCalib();
    // 保存机械单元配置文件及标定文件至系统前的权限检查
    bool checkPermissionBeforeSaveToSystem();
    // 机械单元操作权限检查
    bool checkMechUnitOperatePermission();
    // 强制组态权限检查
    bool checkExtAxisConfigPermission();
    // 保存机械单元文件至系统中
    int saveMechUnitFileToSystem();
    // 检查平台是否有权限修改机械单元参数
    bool checkPlatformModifAuthority(string mechUnitName, bool tooltip = true);
    // 机械单元名称查询(例：机器人基座导轨)
    string MechUnitTypeNameSearch(MechUnitType_V1 type);
    // 机械单元类型查询
    MechUnitType_V1 mechUnitTypeSearch(char *name);
    // 机械单元名称列表查询
    vector<string> mechUnitNameListSearch();
    // 机械单元轴数查询
    int MechUnitTypeAxisCountSearch(MechUnitType_V1 type);
    // 机械单元默认名称查询(例：RotDev_1Axis)
    string MechUnitDefaultNameSearch(MechUnitType_V1 type);
    // 外部轴的编号对应的逻辑轴字符串查询（例：作为E1）
    string ExternalAxisNumNameSearch(ExternalAxisNum_V1 axisNum);
    // 转换关系名称查询(例：Base-World)
    string RelativeObjNameSearch(MechUnitType_V1 type, RelativeObject_V1 obj);
    // 外部轴类型名称查询(线性轴、旋转轴)
    string ExternalAxisTypeNameSearch(ExternalAxisType_V1 type);
    // 外部轴运动类型名称查询(旋转-旋转、旋转-直线)
    string ExternalAxisMoveTypeNameSearch(ExternalAxisMoveType_V1 type);
    // 外部轴设备类型名称查询(例：SV620N)
    string ExternalAxisDeviceTypeNameSearch(ExternalAxisDeviceType_V1 type);
    // 外部轴伺服控制类型名称查询(例：位置模式)
    string ExternalAxisServoControlTypeNameSearch(ExternalAxisServoControlType_V1 type);
    // 运动类型名称查询(例：Jump)
    string ExecuteMoveTypeNameSearch(MoveType_V1 type);
    // 标定点数查询
    int CalibPointCountSearch(MechUnitCalibMethod_V1 method);
    // 标定方法名称查询(例：已知工具一点TCP+ZX)
    string CalibMethodNameSearch(MechUnitCalibMethod_V1 method);
    // 根据标定方法名称查询对应的类型MechUnitCalibMethod
    MechUnitCalibMethod_V1 calibMethodTypeSearchBasedName(const std::string &calibMethodName);
    // 机械单元对应的标定方法集合查询(例：{MechUnitType::MECH_UNIT_ROBOT, {"已知工具一点TCP+ZX", "未知工具三点TCP+ZX"}})
    vector<string> MechUnitCalibMethodSearch(MechUnitType_V1 type);
    // 标定方法对应示教点名称数组
    vector<string> CalibMethodTeachPointNameSearch(MechUnitCalibMethod_V1 method);
    // 独立轴电机轴转向名称查询
    string IndAxisMotorRotationSearch(IndAxisMotorRotationType_V1 type);
    /*!
     * \brief 获取实时运行的独立轴
     * \param status 状态
     * \param size  数量
     * \return ERR_OK成功，其他请见错误码
     */
    int readIndAxisInUsing(unsigned char *status, int size);
    /*!
     * \brief 独立轴重置
     * \param status 状态
     * \param size 数量
     * \return ERR_OK成功，其他请见错误码
     */
    int writeIndAxisReset(IndAxisStatus_V1 buf);
    // 机械单元数据改变事件
    rsignal<bool> MechUnitDataChanged;
    // 机械单元错误信息事件
    rsignal<PromptMsg_V1> MechUnitPromptMsg;

private:
    void MechUnitDataChangedHandler(bool data);
    void MechUnitPromptMsgHandler(PromptMsg data);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
