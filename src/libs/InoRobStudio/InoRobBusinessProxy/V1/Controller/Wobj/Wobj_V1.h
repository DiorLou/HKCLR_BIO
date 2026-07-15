#pragma once
#include "dllspec.h"
#include "../../GlobalDataTypes_V1.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define WOBJ_COUNT_V1 16  //  工具参数套数

// 标定方法枚举
enum WobjUFrameCalibMethod_V1
{
    USER_NO_MODIFY_V1 = 0,    // uframe无修改
    USER_THREE_POINT_V1 = 1,  // uframe三点法
    ROTARY_V1 = 2,            // uframe旋转法
};

enum WobjOFrameCalibMethod_V1
{
    OBJ_NO_MODIFY_V1 = 0,    // Oframe无修改
    OBJ_THREE_POINT_V1 = 1,  // Oframe三点法
};

enum RobotHoldWobjType_V1
{
    WOBJ_TYPE_FIXED_WOBJ_V1 = 0,  // 固定工件
    WOBJ_TYPE_ROBOT_HOLD_V1 = 1,  // 机器人夹持工件
};

enum WobjId_V1
{
    WOBJ_ID_WOBJ0_V1 = 0,
    WOBJ_ID_WOBJ1_V1 = 1,
    WOBJ_ID_WOBJ2_V1 = 2,
    WOBJ_ID_WOBJ3_V1 = 3,
    WOBJ_ID_WOBJ4_V1 = 4,
    WOBJ_ID_WOBJ5_V1 = 5,
    WOBJ_ID_WOBJ6_V1 = 6,
    WOBJ_ID_WOBJ7_V1 = 7,
    WOBJ_ID_WOBJ8_V1 = 8,
    WOBJ_ID_WOBJ9_V1 = 9,
    WOBJ_ID_WOBJ10_V1 = 10,
    WOBJ_ID_WOBJ11_V1 = 11,
    WOBJ_ID_WOBJ12_V1 = 12,
    WOBJ_ID_WOBJ13_V1 = 13,
    WOBJ_ID_WOBJ14_V1 = 14,
    WOBJ_ID_WOBJ15_V1 = 15,
};

enum UserFrameFixed_V1
{
    USER_FRAME_FIXED_FALSE_V1 = 0,  //  用户坐标系不固定
    USER_FRAME_FIXED_TRUE_V1 = 1,   //  用户坐标系固定
};

typedef struct _WobjItem_V1
{
    WobjId_V1 WobjNo;
    string ItemName;

} WobjItem_V1;

typedef struct _WobjExcuteMoveTypeItem_V1
{
    MoveType_V1 type;
    string ItemName;
} WobjExcuteMoveTypeItem_V1;

typedef struct _UserFrameFixedItem_V1
{
    UserFrameFixed_V1 fixedType;
    string ItemName;
} UserFrameFixedItem_V1;

typedef struct _WobjUFrameCalibMethodNameItem_V1
{
    WobjUFrameCalibMethod_V1 method;
    string ItemName;
} WobjUFrameCalibMethodNameItem_V1;

typedef struct _WobjOFrameCalibMethodNameItem_V1
{
    WobjOFrameCalibMethod_V1 method;
    string ItemName;
} WobjOFrameCalibMethodNameItem_V1;

typedef struct _WobjHoldTypeCalibMethodItem_V1
{
    RobotHoldWobjType_V1 type;
    string methodList;
} WobjHoldTypeCalibMethodItem_V1;

typedef struct _WobjUFrameCalibMethodTeachPointNameItem_V1
{
    WobjUFrameCalibMethod_V1 method;
    string nameList;
} WobjUFrameCalibMethodTeachPointNameItem_V1;

typedef struct _WobjOFrameCalibMethodTeachPointNameItem_V1
{
    WobjOFrameCalibMethod_V1 method;
    string nameList;
} WobjOFrameCalibMethodTeachPointNameItem_V1;

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Wobj_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static WobjUFrameCalibMethod_V1 WobjUFrameCalibMethod_ToProxy(WobjUFrameCalibMethod wobjUFrameCalibMethod);
    static WobjUFrameCalibMethod WobjUFrameCalibMethod_FromProxy(WobjUFrameCalibMethod_V1 wobjUFrameCalibMethod_V1);

    static WobjOFrameCalibMethod_V1 WobjOFrameCalibMethod_ToProxy(WobjOFrameCalibMethod wobjOFrameCalibMethod);
    static WobjOFrameCalibMethod WobjOFrameCalibMethod_FromProxy(WobjOFrameCalibMethod_V1 wobjOFrameCalibMethod_V1);

    static RobotHoldWobjType_V1 RobotHoldWobjType_ToProxy(RobotHoldWobjType robotHoldWobjType);
    static RobotHoldWobjType RobotHoldWobjType_FromProxy(RobotHoldWobjType_V1 robotHoldWobjType_V1);

    static WobjId_V1 WobjId_ToProxy(WobjId wobjId);
    static WobjId WobjId_FromProxy(WobjId_V1 wobjId_V1);

    static UserFrameFixed_V1 UserFrameFixed_ToProxy(UserFrameFixed userFrameFixed);
    static UserFrameFixed UserFrameFixed_FromProxy(UserFrameFixed_V1 userFrameFixed_V1);

    static bool WobjItem_ToProxy(const WobjItem &wobjItem, WobjItem_V1 &wobjItem_V1);
    static bool WobjItem_FromProxy(const WobjItem_V1 &wobjItem_V1, WobjItem &wobjItem);

    static bool WobjExcuteMoveTypeItem_ToProxy(const WobjExcuteMoveTypeItem &wobjExcuteMoveTypeItem, WobjExcuteMoveTypeItem_V1 &wobjExcuteMoveTypeItem_V1);
    static bool WobjExcuteMoveTypeItem_FromProxy(const WobjExcuteMoveTypeItem_V1 &wobjExcuteMoveTypeItem_V1, WobjExcuteMoveTypeItem &wobjExcuteMoveTypeItem);

    static bool UserFrameFixedItem_ToProxy(const UserFrameFixedItem &userFrameFixedItem, UserFrameFixedItem_V1 &userFrameFixedItem_V1);
    static bool UserFrameFixedItem_FromProxy(const UserFrameFixedItem_V1 &userFrameFixedItem_V1, UserFrameFixedItem &userFrameFixedItem);

    static bool WobjUFrameCalibMethodNameItem_ToProxy(const WobjUFrameCalibMethodNameItem &wobjUFrameCalibMethodNameItem, WobjUFrameCalibMethodNameItem_V1 &wobjUFrameCalibMethodNameItem_V1);
    static bool WobjUFrameCalibMethodNameItem_FromProxy(const WobjUFrameCalibMethodNameItem_V1 &wobjUFrameCalibMethodNameItem_V1, WobjUFrameCalibMethodNameItem &wobjUFrameCalibMethodNameItem);

    static bool WobjOFrameCalibMethodNameItem_ToProxy(const WobjOFrameCalibMethodNameItem &wobjOFrameCalibMethodNameItem, WobjOFrameCalibMethodNameItem_V1 &wobjOFrameCalibMethodNameItem_V1);
    static bool WobjOFrameCalibMethodNameItem_FromProxy(const WobjOFrameCalibMethodNameItem_V1 &wobjOFrameCalibMethodNameItem_V1, WobjOFrameCalibMethodNameItem &wobjOFrameCalibMethodNameItem);

    static bool WobjHoldTypeCalibMethodItem_ToProxy(const WobjHoldTypeCalibMethodItem &wobjHoldTypeCalibMethodItem, WobjHoldTypeCalibMethodItem_V1 &wobjHoldTypeCalibMethodItem_V1);
    static bool WobjHoldTypeCalibMethodItem_FromProxy(const WobjHoldTypeCalibMethodItem_V1 &wobjHoldTypeCalibMethodItem_V1, WobjHoldTypeCalibMethodItem &wobjHoldTypeCalibMethodItem);

    static bool WobjUFrameCalibMethodTeachPointNameItem_ToProxy(const WobjUFrameCalibMethodTeachPointNameItem &wobjUFrameCalibMethodTeachPointNameItem, WobjUFrameCalibMethodTeachPointNameItem_V1 &wobjUFrameCalibMethodTeachPointNameItem_V1);
    static bool WobjUFrameCalibMethodTeachPointNameItem_FromProxy(const WobjUFrameCalibMethodTeachPointNameItem_V1 &wobjUFrameCalibMethodTeachPointNameItem_V1, WobjUFrameCalibMethodTeachPointNameItem &wobjUFrameCalibMethodTeachPointNameItem);

    static bool WobjOFrameCalibMethodTeachPointNameItem_ToProxy(const WobjOFrameCalibMethodTeachPointNameItem &wobjOFrameCalibMethodTeachPointNameItem, WobjOFrameCalibMethodTeachPointNameItem_V1 &wobjOFrameCalibMethodTeachPointNameItem_V1);
    static bool WobjOFrameCalibMethodTeachPointNameItem_FromProxy(const WobjOFrameCalibMethodTeachPointNameItem_V1 &wobjOFrameCalibMethodTeachPointNameItem_V1, WobjOFrameCalibMethodTeachPointNameItem &wobjOFrameCalibMethodTeachPointNameItem);

#pragma endregion

#pragma region 构造与析构

private:
    IWobj *_wobj = nullptr;

public:
    Wobj_V1(IWobj *wobj);
    ~Wobj_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 获取工件号总数量
    int16u GetCount();
    // 获取当前工件号
    int16u getCurrentId();
    // 设定当前工件号
    bool SetCurrentId(int16u currentId);
    // 当前工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool currentIsRobotHold(bool &result);
    // 指定工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsRobotHold(int16u toolNo, bool &result);
    // 指定工件是否为固定（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsFixed(int16u toolNo, bool &result);
    // 获取当前的工件参数
    bool GetCurrentWobjParam(WobjData_V1 &wobjData);
    // 读取工件参数
    bool GetWobjParam(int16u wobjNo, WobjData_V1 &wobjData);
    // 设置工件参数
    bool SetWobjParam(int16u wobjNo, WobjData_V1 wobjData);
    // 保存工具参数
    bool Save(int wobjNo, WobjData_V1 &data);
    // 刷新工具参数
    bool Refresh(int wobjNo, WobjData_V1 &data);
    // 清0
    bool Clear(int wobjNo);
    // 标定
    bool Calibrate(string mechUnitName, RobotHoldWobjType_V1 type, bool isUFFix, const CsCalibPoints_V1 &midUFramePos, const CsCalibPoints_V1 &midOFramePos, Pose_V1 oldUFrame, Pose_V1 &uFrameCalibResult, Pose_V1 &oFrameCalibResult);
    // 检查控制权
    bool CheckAuthority();
    // 相关操作控制权检查
    bool checkWobjOperatePermission();
    // 保存标定中间点
    bool SaveCalibratePoints(int16u wobjNo, const CsCalibPoints_V1 &uFramePoint, const CsCalibPoints_V1 &oFramePoint);
    // 读取标定中间点
    bool RefreshCalibratePoints(WobjCalibData_V1 &wobjCalibData);
    // 保存用户安装参数（备注）
    bool SaveUserInstallParam(int16u wobjNo, const UserInstallParam_V1 &userInstallParam);
    // 取当前位置
    bool GetCurPos(RobotHoldWobjType_V1 method, RobPos_V1 &pos);
    // 运动到点
    bool MoveToPoint(RobPos_V1 pos, MoveType_V1 type, RobotHoldWobjType_V1 method, double lh = 0.0, double mh = 0.0, double rh = 0.0);
    // 停止到点
    bool StopToPoint();
    // 工具Id对应名称查询
    string WobjIdNameSearch(WobjId_V1 id);
    // 运动到点类型名称查询
    string WobjExcuteMoveTypeNameSearch(MoveType_V1 type);
    // 用户坐标系是否固定名称查询
    string UserFrameFixedNameSearch(UserFrameFixed_V1 type);
    // 标定方法名称查询
    string CalibMethodNameSearch(WobjUFrameCalibMethod_V1 method);
    // 标定方法名称查询
    string CalibMethodNameSearch(WobjOFrameCalibMethod_V1 method);
    // 机器人夹持工件类型UFrame标定方法查询
    vector<string> HoldTypeUFrameCalibMethodSearch(RobotHoldWobjType_V1 type);
    // 机器人夹持工件类型OFrame标定方法查询
    vector<string> HoldTypeOFrameCalibMethodSearch(RobotHoldWobjType_V1 type);
    // UFrame标定方法对应点名称查询
    vector<string> CalibMethodTeachPointNameSearch(WobjUFrameCalibMethod_V1 method);
    // OFrame标定方法对应点名称查询
    vector<string> CalibMethodTeachPointNameSearch(WobjOFrameCalibMethod_V1 method);

#pragma endregion

#pragma region 信号

private:
    void currentIdChangedHandler(int16u data);

public:
    // 当前工件号变更信号
    rsignal<int16u> currentIdChanged;

#pragma endregion
};
}  // namespace InoRobBusinessProxy
