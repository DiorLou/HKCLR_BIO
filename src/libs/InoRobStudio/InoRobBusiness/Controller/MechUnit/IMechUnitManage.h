#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "DataSrvGlobal.h"
#include "../Monitor/IMonitor.h"

namespace InoRobBusiness
{
#pragma region 枚举

#define LISTTOTAL_ROW_NUM 24                // 轴属性列表总行数, 22版本为18, 后续版本为24
constexpr int INDAXIS_STATUS_MAX_NUM = 14;  // 独立轴状态最大数量
constexpr int INDAXIS_MAX_NUM = 7;          // 独立轴最大数量

// 机器人安装类型
enum RobotInstallType : int32s
{
    INSTALL_TYPE_ROBOT_FIXED = 0,             // 固定安装
    INSTALL_TYPE_ROBOT_INSTALL_TO_TRACK = 1,  // 在可移动的导轨上
};

// 轴编号ID
enum ExternalAxisNum : int32s
{
    EXTER_AXIS_NUM_NULL = 0xff,  // 逻辑轴为空，目前功能上暂不支持，可以用为初始化数据，页面不显示，请注意
    EXTER_AXIS_NUM_E1 = 0,       // 作为E1
    EXTER_AXIS_NUM_E2 = 1,       // 作为E2
    EXTER_AXIS_NUM_E3 = 2,       // 作为E3
    EXTER_AXIS_NUM_E4 = 3,       // 作为E4
    EXTER_AXIS_NUM_E5 = 4,       // 作为E5
    EXTER_AXIS_NUM_E6 = 5,       // 作为E6
};

// 转换关系
enum RelativeObject : int32s
{
    RELATIVE_OBJ_WORLD = -1,  // 到世界坐标
    RELATIVE_OBJ_BASE = 0,    // 机器人基坐标
    RELATIVE_OBJ_J1 = 1,      // J1轴
    RELATIVE_OBJ_J2 = 2,      // J2轴
    RELATIVE_OBJ_J3 = 3,      // J3轴
    RELATIVE_OBJ_J4 = 4,      // J4轴
    RELATIVE_OBJ_J5 = 5,      // J5轴
    RELATIVE_OBJ_J6 = 6,      // J6轴
};

// 外部轴类型
enum ExternalAxisType : int32s
{
    EXTER_AXIS_TYPE_ROTATE_AXIS = 0,  // 旋转轴
    EXTER_AXIS_TYPE_LINEAR_AXIS = 1,  // 线性轴
};

enum ExternalAxisMoveType : int32s
{
    EXTER_AXIS_MOVE_TYPE_ROTATE_TO_ROTATE = 0,  // 旋转-旋转
    EXTER_AXIS_MOVE_TYPE_ROTATE_TO_LINEAR = 1,  // 旋转-直线
    EXTER_AXIS_MOVE_TYPE_LINEAR_TO_ROTATE = 2,  // 直线-旋转
    EXTER_AXIS_MOVE_TYPE_LINEAR_TO_LINEAR = 3   // 直线-直线
};

// 外部轴驱动器类型
enum ExternalAxisDeviceType : int32s
{
    DEVICE_SV620N = 0,      // SV620
    DEVICE_SV660N = 1,      // SV660
    DEVICE_SV680N = 2,      // SV680
    DEVICE_SV680LN = 3,     // SV680LN
    DEVICE_SV660N_STOP = 4  // SV660 点焊
};

// 独立轴支持标志
enum IndependantAxisSupportFlag : int32s
{
    NOT_SUPPORT = 0,
    SUPPORT = 1,
};

// 外部轴伺服控制模式类型
enum ExternalAxisServoControlType : int32s
{
    SERVO_LOCATION_TYPE = 8,  // 位置模式
    SERVO_SPEED_TYPE = 9,     // 速度模式
    SERVO_TORQUE_TYPE = 10,   // 转矩模式
};

// 标定方法
enum MechUnitCalibMethod : int32s
{
    MECH_UNIT_CALIB_METHOD_THREE_POINT = 0,             // 三点法
    MECH_UNIT_CALIB_METHOD_THREE_POINT_ROTATE = 1,      // 三点旋转法
    MECH_UNIT_CALIB_METHOD_KNOWN_ONE_POINT_ZX = 2,      // 已知工具一点TCP+ZX
    MECH_UNIT_CALIB_METHOD_UNKNOWN_THREE_POINT_ZX = 3,  // 未知工具三点TCP+ZX
    MECH_UNIT_CALIB_METHOD_SIX_POINT = 4,               // 六点法
    MECH_UNIT_CALIB_METHOD_NINE_POINT = 5,              // 九点法
};

// 示教点
enum MechUnitTeachingPoint : int32s
{
    MECH_UNIT_TEACHING_POINT_ONE = 0,    // 点1
    MECH_UNIT_TEACHING_POINT_TWO = 1,    // 点2
    MECH_UNIT_TEACHING_POINT_THREE = 2,  // 点3
    MECH_UNIT_TEACHING_POINT_DATUM = 3,  // 基准点
    MECH_UNIT_TEACHING_POINT_Z_POS = 4,  // 点Z+
    MECH_UNIT_TEACHING_POINT_X_POS = 5,  // 点X+
};

// 独立轴电机转向类型结构体
enum IndAxisMotorRotationType : int16u
{
    MOTOR_ROTATION_TYPE_REVERSE = 0,  // 逆向
    MOTOR_ROTATION_TYPE_FORWARD = 1   // 正向
};

#pragma endregion

#pragma region 结构体

// 机械单元常用数据结构体
typedef struct _MECH_UNIT_DATA
{
    string mechUnitName;           // 机械单元名称
    MechUnitType mechUnitType;     // 机械单元类型
    int axisCount;                 // 轴数
    RobotInstallType installType;  // 安装类型（针对机器人）
    string moveMechName;           // 移动机械名称
} MechUnitData;

// 提示信息结构体
typedef struct _PROMPT_MSG_
{
    string Caption;
    string TextMessage;
} PromptMsg;

// 机械单元类型名称结构体
typedef struct _MECH_UNIT_TYPE_NAME_STRUCT_
{
    MechUnitType type;
    string name;
} MechUnitTypeNameStruct;

// 机械单元类型对应轴数结构体
typedef struct _MECH_UNIT_TYPE_AXIS_COUNT_
{
    MechUnitType type;
    int axisCount;
} MechUnitTypeAxisCountStruct;

// 外部轴的逻辑轴对应名称结构体
typedef struct _EXTERNAL_AXIS_NUM_STRUCT_
{
    ExternalAxisNum axisNum;
    string str;
} ExternalAxisNumStruct;

// 转换关系对应名称结构体
typedef struct _RELATIVE_OBJ_STRUCT
{
    RelativeObject obj;
    string relativeObjName;
} RelativeObjStruct;

// 外部轴类型对应名称结构体
typedef struct _EXTERNAL_AXIS_TYPE_STRUCT_
{
    ExternalAxisType type;
    string name;
} ExternalAxisTypeStruct;

// 外部轴运动类型对应名称结构体
typedef struct _EXTERNAL_AXIS_MOVE_TYPE_STRUCT_
{
    ExternalAxisMoveType type;
    string name;
} ExternalAxisMoveTypeStruct;

// 外部轴设备类型对应名称结构体
typedef struct _EXTERNAL_AXIS_DRVICE_TYPE_STRUCT_
{
    ExternalAxisDeviceType type;
    string name;
} ExternalAxisDrviceTypeStruct;

// 独立轴支持标志
typedef struct _INDEPENDANT_AXIS_SUPPORT_FLAG_STRUCT_
{
    IndependantAxisSupportFlag type;
    string name;
} IndependantAxisSupportFlagStruct;

// 外部轴伺服控制类型对应名称结构体
typedef struct _EXTERNAL_AXIS_SERVO_CONTROL_TYPE_STRUCT_
{
    ExternalAxisServoControlType type;
    string name;
} ExternalAxisServoControlTypeStruct;

// 运动类型对应名称结构体
typedef struct _EXECUTE_MOVE_TYPE_STRUCT_
{
    MoveType type;
    string name;
} ExecuteMoveTypeStruct;

// 标定方法对应点数结构体
typedef struct _CALIB_POINT_COUNT_STRUCT_
{
    MechUnitCalibMethod method;
    int count;
} CalibPointCountStruct;

// 标定方法对应名称结构体
typedef struct _CALIB_METHOD_NAME_STRUCT_
{
    MechUnitCalibMethod method;
    string name;
} CalibMethodNameStruct;

// 机械单元对应的标定方法结构体
typedef struct _MECH_UNIT_CALIB_METHOD_STRUCT_
{
    MechUnitType type;
    string methodList;
} MechUnitCalibMethodStruct;

// 示教点对应名称结构体
typedef struct _TEACHING_POINT_NAME_STRUCT
{
    MechUnitTeachingPoint point;
    string name;
} MechUnitTeachingPointNameStruct;

typedef struct _MECH_UNIT_CALIB_METHOD_TEACH_POINT_STRUCT_
{
    MechUnitCalibMethod method;
    string name;
} MechUnitCalibMethodTeachPointStruct;

// 独立轴电机轴转向类型名称结构体
typedef struct _MECH_UNIT_IND_MOTOR_TYPE_STRUCT_
{
    IndAxisMotorRotationType type;
    string name;
} IndAxisMotorRotationTypeStruct;

// 轴属性中的列表名
typedef struct _BUS_EXT_AXIS_PARAM_LIST
{
    std::string strParamName;  // 参数名
    std::string strValue;      // 值
    std::string strRange;      // 范围
} BUS_EXT_AXIS_PARAM_LIST;

// 独立轴中的列表名
typedef struct _BUS_IND_AXIS_PARAM_LIST
{
    std::string mechName;          // 机械单元名称
    std::string axisIndexName;     // 轴名称
    std::string isSupportIndAxis;  // 是否支持独立轴
} BUS_IND_AXIS_PARAM_LIST;

typedef unsigned char IndAxisStatus[14];

// 轴属性每一行意义
enum ExternalPropName
{
    SV_TYPE = 0,              // 伺服类型620N = 0,660N = 1(默认值660N)
    OP_MODE,                  // 伺服驱动模式  8-位置模式；9-速度模式;10-转矩模式 （待定）
    AXIS_TYPE,                // 电机轴属性 0-旋转轴;线性轴不开放（1-线性轴）
    MOVE_TYPE,                // 传动方向 0、转动-转动  1、转动-直线
    PHY_TRANS_RATIO,          // 物理传动化
    ABS_ZERO_POINT,           // 零点
    POS_LMT,                  // 正限位
    NEG_LMT,                  // 负限位
    PARA_VEL,                 // 示教速度
    PARA_ACC,                 // 示教加速度
    MAX_SPEED,                // 最大速度
    MAX_ACC_SPEED,            // 最大加速度
    STOP_DEC_SPEED,           // 停机减速度
    FOLLOW_ERR,               // 跟随误差
    INPOS_ERR,                // 到位误差
    INPOS_TIME,               // 到位时间
    CURRENT_LIMIT,            // 最大电流报警阈值
    AVERAGE_LOAD_RATE_LIMIT,  // 平均负载率报警阈值
    IS_SUPPORT_INDAXIS,       // 是否支持独立轴
    INDAXIS_NEGLIMIT,         // 独立轴负限位
    INDAXIS_POSLIMIT,         // 独立轴正限位
    SPEED_ARRIVAL_ERROR,      // 速度到位误差
    SPEED_ARRIVAL_TIME,       // 速度到位时间
    SPEED_TRACKING_ERROR,     // 速度跟随误差阈值
};

// 可变的属性范围结构体
typedef struct _VariableAxisAttribute_
{
    // 机械单元
    MechUnitType mechUnitType;
    // 电机轴属性集合
    vector<ExternalAxisTypeStruct> vecVariableAxisType;
    // 外部轴运动类型集合
    vector<ExternalAxisMoveTypeStruct> vecVariableAxisMoveType;
} VariableAxisAttribute;

#pragma endregion

/**********************************************************
 * 机械单元接口，定义机械单元模型通用方法
 * 包括机械单元添加、删除、数据读写、序列化、反序列化
 ***********************************************************/
class INOROBBUSINESS_CLASS IMechUnitManage : public QObject
{
    Q_OBJECT

public:
    virtual ~IMechUnitManage()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 属性

    // 获取机械单元数量
    virtual int GetMechUnitCount() = 0;

    // 获取机械单元列表
    virtual vector<MechUnitData> GetMechUnitList() = 0;

#pragma endregion

#pragma region 方法

    // 添加机械单元
    virtual bool AddMechUnit(int type, const char *name) = 0;

    // 添加机械单元前的数量检查
    virtual int checkMechUnitNumBeforeAddMechUnit() = 0;

    // 删除机械单元
    virtual bool RemoveMechUnit(const char *name) = 0;

    // 获取数据
    virtual void GetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData) = 0;

    // 设置数据
    virtual void SetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData) = 0;

    // 取当前工具号
    virtual int GetCurTool() = 0;

    // 取机器人当前点
    virtual bool GetCurRobPos(MechUnitCalibMethod calibMethod, RobPos &pos) = 0;

    // 外部轴取当前点做为零点值
    virtual bool RecordAbsZero(string mechUnitName, int axisIndex, int &value) = 0;

    // 运动到点
    virtual bool MoveToPoint(MechUnitCalibMethod calibMethod, MoveType moveType, RobPos mPos, double lH, double mH, double rH) = 0;

    // 停止运动到点
    virtual bool StopToPoint() = 0;

    //(PC)检查使用权限(管理员以上、控制权：PC)
    virtual bool PCCheckAuthority() = 0;

    //(TP)检查使用权限(管理员以上、控制权：TP)
    virtual bool TPCheckAuthority() = 0;

    // 检查保存许可（需要急停、示教模式下）
    virtual bool CheckSavePermission() = 0;

    // 检查数据是否有修改(单个机械单元级别)
    virtual bool CheckMechUnitDataModified(string mechUnitName) = 0;

    // 检查更新机械单元名称许可
    virtual bool checkModifyMechUnitNamePerm(const std::string &newMechName) = 0;

    // 创建机械单元默认名称(相同类型，都使用默认名称，往后加索引)
    virtual string CreateDefaultNameByMechUnitType(MechUnitType mechUnitType) = 0;

    // 计算标定结果(传入数组指针和数据数量，标定类型)
    virtual bool CalculateCalibResult(RobPos calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT], MechUnitCalibMethod calibMethod, string unitName, Pose previousAxisPos, int axisNum, Pose &pos) = 0;

    // 计算XYZ和XZ导轨标定结果(传入数组指针和数据数量，标定类型)
    virtual bool CalculateTrackCalibResult(RobPos calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT], MechUnitCalibMethod calibMethod, string unitName, int axisNum, Pose *pos, int16u mechUnitType) = 0;

    // 从控制器获取机械单元配置文件和标定文件并反序列化(0-成功，1-控制器中没有相关配置文件（如刷机后），小于0为失败)
    virtual int ReadMechUnitCfgAndCalibDataFromFile() = 0;

    // 将机械单元配置和标定数据序列化并下载到控制器
    virtual bool WriteMechUnitCfgAndCalibDataToFile() = 0;

    // 发送非实时命令让控制器解析
    virtual bool WriteMechUnitsCfg() = 0;

    // 读机械单元配置控制器是否配置成功信息
    virtual int readMechUnitsCfg() = 0;

    // 修改机械单元名称
    virtual void modifyMechName(const std::string &currMechName, const std::string &newMechName) = 0;

    // 根据机械单元下标号及选中的轴号更新轴属性数据
    virtual vector<BUS_EXT_AXIS_PARAM_LIST> updateAxisDefaultDataByMechType(const int guideIndex, const int curSelectAxisIndex) = 0;

    // 获取机器人独立轴数据
    virtual vector<BUS_EXT_AXIS_PARAM_LIST> getRobotIndAxisData() = 0;

    // 获取机械单元各轴的独立轴信息
    virtual vector<BUS_IND_AXIS_PARAM_LIST> getAllMechUnitIsSupportIndAxisData() = 0;

    // 设置机器人独立轴属性
    virtual void setRobotIndAxisAttribute(const int indAxisEnum, string &value) = 0;

    // 根据机械单元及轴号获取未使用的轴逻辑
    virtual vector<int> readUnusedAxisLogicByMechUnit(const MechUnit &mechUnit, const int axisIndex) = 0;

    // 更新机械单元的轴映射和外部轴ID
    virtual void updateMechUnitAxisMapAndAxisID(int8u curAxisLogic[EXT_AXIS_NUM], int guideIndex) = 0;

    // 检查机械转换表格中的XYZABC数据是否合理，超出则返回边界值
    virtual double checkMechTransValueIsValid(const int column, const double value) = 0;

    // 检查轴属性表双击处是否需要修改
    virtual int checkAxisAttributeIsNeedChanged(const int row) = 0;

    // 设置轴属性表中要修改的值，不符合要求自动设置一个合理值，并返回
    virtual void setAxisAttributeValue(const int row, string &value, const int guideIndex, const int curSelectAxisIndex) = 0;

    // 取当前值为零点值
    virtual int setCurrValueAsHomePoint(const int guideIndex, const int currAxisIndex) = 0;

    // 外部轴组态文件配置
    virtual int externalAxisForceConfig() = 0;

    // 标定权限检查
    virtual bool checkPermissionInCalib() = 0;

    // 保存机械单元配置文件及标定文件至系统前的权限检查
    virtual bool checkPermissionBeforeSaveToSystem() = 0;

    // 机械单元操作权限检查
    virtual bool checkMechUnitOperatePermission() = 0;

    // 强制组态权限检查
    virtual bool checkExtAxisConfigPermission() = 0;

    // 保存机械单元文件至系统中
    virtual int saveMechUnitFileToSystem() = 0;

    // 检查平台是否有权限修改机械单元参数
    virtual bool checkPlatformModifAuthority(string mechUnitName, bool tooltip = true) = 0;

    /*******************************数据查询接口*************************/

    // 机械单元名称查询(例：机器人基座导轨)
    virtual string MechUnitTypeNameSearch(MechUnitType type) = 0;

    // 机械单元类型查询
    virtual MechUnitType mechUnitTypeSearch(const char *name) = 0;

    // 机械单元名称列表查询
    virtual vector<string> mechUnitNameListSearch() = 0;

    // 机械单元轴数查询
    virtual int MechUnitTypeAxisCountSearch(MechUnitType type) = 0;

    // 机械单元默认名称查询(例：RotDev_1Axis)
    virtual string MechUnitDefaultNameSearch(MechUnitType type) = 0;

    // 外部轴的编号对应的逻辑轴字符串查询（例：作为E1）
    virtual string ExternalAxisNumNameSearch(ExternalAxisNum axisNum) = 0;

    // 转换关系名称查询(例：Base-World)
    virtual string RelativeObjNameSearch(MechUnitType type, RelativeObject obj) = 0;

    // 外部轴类型名称查询(线性轴、旋转轴)
    virtual string ExternalAxisTypeNameSearch(ExternalAxisType type) = 0;

    // 外部轴运动类型名称查询(旋转-旋转、旋转-直线)
    virtual string ExternalAxisMoveTypeNameSearch(ExternalAxisMoveType type) = 0;

    // 外部轴设备类型名称查询(例：SV620N)
    virtual string ExternalAxisDeviceTypeNameSearch(ExternalAxisDeviceType type) = 0;

    // 外部轴伺服控制类型名称查询(例：位置模式)
    virtual string ExternalAxisServoControlTypeNameSearch(ExternalAxisServoControlType type) = 0;

    // 运动类型名称查询(例：Jump)
    virtual string ExecuteMoveTypeNameSearch(MoveType type) = 0;

    // 标定点数查询
    virtual int CalibPointCountSearch(MechUnitCalibMethod method) = 0;

    // 标定方法名称查询(例：已知工具一点TCP+ZX)
    virtual string CalibMethodNameSearch(MechUnitCalibMethod method) = 0;

    // 根据标定方法名称查询对应的类型MechUnitCalibMethod
    virtual MechUnitCalibMethod calibMethodTypeSearchBasedName(const std::string &calibMethodName) = 0;

    // 机械单元对应的标定方法集合查询(例：{MechUnitType::MECH_UNIT_ROBOT, {"已知工具一点TCP+ZX", "未知工具三点TCP+ZX"}})
    virtual vector<string> MechUnitCalibMethodSearch(MechUnitType type) = 0;

    // 标定方法对应示教点名称数组
    virtual vector<string> CalibMethodTeachPointNameSearch(MechUnitCalibMethod method) = 0;

    // 独立轴电机轴转向名称查询
    virtual string IndAxisMotorRotationSearch(IndAxisMotorRotationType type) = 0;

    /*!
     * \brief 获取实时运行的独立轴
     * \param status 状态
     * \param size  数量
     * \return ERR_OK成功，其他请见错误码
     */
    virtual int readIndAxisInUsing(unsigned char *status, int size) = 0;

    /*!
     * \brief 独立轴重置
     * \param status 状态
     * \param size 数量
     * \return ERR_OK成功，其他请见错误码
     */
    virtual int writeIndAxisReset(IndAxisStatus buf) = 0;
#pragma endregion

#pragma region 事件

Q_SIGNALS:
    // 机械单元数据改变事件
    void mechUnitDataChanged(bool data);
    // 机械单元错误信息事件
    void mechUnitPromptMsg(PromptMsg data);
    // 机械单元误差提示
    void sigMechCalibError(double maxError, double minError, double aveError);
#pragma endregion
};

}  // namespace InoRobBusiness
