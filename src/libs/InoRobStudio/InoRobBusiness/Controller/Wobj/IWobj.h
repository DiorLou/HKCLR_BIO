#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"

#define WOBJ_COUNT 16  //  工具参数套数
/*
    工件
    Create by WuJian at 2022/5/2
*/
namespace InoRobBusiness
{
// 标定方法枚举
enum WobjUFrameCalibMethod
{
    USER_NO_MODIFY = 0,    // uframe无修改
    USER_THREE_POINT = 1,  // uframe三点法
    ROTARY = 2,            // uframe旋转法
};

enum WobjOFrameCalibMethod
{
    OBJ_NO_MODIFY = 0,    // Oframe无修改
    OBJ_THREE_POINT = 1,  // Oframe三点法
};

enum RobotHoldWobjType
{
    WOBJ_TYPE_FIXED_WOBJ = 0,  // 固定工件
    WOBJ_TYPE_ROBOT_HOLD = 1,  // 机器人夹持工件
};

enum WobjId
{
    WOBJ_ID_WOBJ0 = 0,
    WOBJ_ID_WOBJ1 = 1,
    WOBJ_ID_WOBJ2 = 2,
    WOBJ_ID_WOBJ3 = 3,
    WOBJ_ID_WOBJ4 = 4,
    WOBJ_ID_WOBJ5 = 5,
    WOBJ_ID_WOBJ6 = 6,
    WOBJ_ID_WOBJ7 = 7,
    WOBJ_ID_WOBJ8 = 8,
    WOBJ_ID_WOBJ9 = 9,
    WOBJ_ID_WOBJ10 = 10,
    WOBJ_ID_WOBJ11 = 11,
    WOBJ_ID_WOBJ12 = 12,
    WOBJ_ID_WOBJ13 = 13,
    WOBJ_ID_WOBJ14 = 14,
    WOBJ_ID_WOBJ15 = 15,
};

enum UserFrameFixed
{
    USER_FRAME_FIXED_FALSE = 0,  //  用户坐标系不固定
    USER_FRAME_FIXED_TRUE = 1,   //  用户坐标系固定
};

typedef struct _WobjItem_
{
    WobjId WobjNo;
    string ItemName;

} WobjItem;

typedef struct _WobjExcuteMoveTypeItem_
{
    MoveType type;
    string ItemName;
} WobjExcuteMoveTypeItem;

typedef struct _UserFrameFixedItem_
{
    UserFrameFixed fixedType;
    string ItemName;
} UserFrameFixedItem;

typedef struct _WobjUFrameCalibMethodNameItem_
{
    WobjUFrameCalibMethod method;
    string ItemName;
} WobjUFrameCalibMethodNameItem;

typedef struct _WobjOFrameCalibMethodNameItem_
{
    WobjOFrameCalibMethod method;
    string ItemName;
} WobjOFrameCalibMethodNameItem;

typedef struct _WobjHoldTypeCalibMethodItem_
{
    RobotHoldWobjType type;
    string methodList;
} WobjHoldTypeCalibMethodItem;

typedef struct _WobjUFrameCalibMethodTeachPointNameItem_
{
    WobjUFrameCalibMethod method;
    string nameList;
} WobjUFrameCalibMethodTeachPointNameItem;

typedef struct _WobjOFrameCalibMethodTeachPointNameItem_
{
    WobjOFrameCalibMethod method;
    string nameList;
} WobjOFrameCalibMethodTeachPointNameItem;

class INOROBBUSINESS_CLASS IWobj : public QObject
{
    Q_OBJECT

public:
    virtual ~IWobj()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 通用

    // 获取工件号总数量
    virtual int16u GetCount() = 0;
#pragma endregion

    // 获取当前工件号
    virtual int16u getCurrentId() = 0;

    // 设定当前工件号
    virtual bool SetCurrentId(int16u currentId) = 0;

    // 变更当前工件号
    virtual void onCurrentIdChange(int16u currentId) = 0;

    // 当前工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    virtual bool currentIsRobotHold(bool &result) = 0;

    // 指定工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    virtual bool someoneIsRobotHold(int16u toolNo, bool &result) = 0;

    // 指定工件是否为固定（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    virtual bool someoneIsFixed(int16u toolNo, bool &result) = 0;

#pragma region 工件参数

    // 获取当前的工件参数
    virtual bool GetCurrentWobjParam(WobjData &wobjData) = 0;
    // 读取工件参数
    virtual bool GetWobjParam(int16u wobjNo, WobjData &wobjData) = 0;
    // 设置工件参数
    virtual bool SetWobjParam(int16u wobjNo, WobjData wobjData) = 0;

#pragma endregion

#pragma region 其它（请分类）

    // 保存工具参数
    virtual bool Save(int wobjNo, WobjData *data) = 0;
    // 刷新工具参数
    virtual bool Refresh(int wobjNo, WobjData *data) = 0;
    // 清0
    virtual bool Clear(int wobjNo) = 0;
    // 标定
    virtual bool Calibrate(string mechUnitName, RobotHoldWobjType type, bool isUFFix, const CsCalibPoints &midUFramePos, const CsCalibPoints &midOFramePos, Pose oldUFrame, Pose &uFrameCalibResult, Pose &oFrameCalibResult) = 0;
    // 检查控制权
    virtual bool CheckAuthority() = 0;

    // 相关操作控制权检查
    virtual bool checkWobjOperatePermission() = 0;

    // 保存标定中间点
    virtual bool SaveCalibratePoints(int16u wobjNo, const CsCalibPoints &uFramePoint, const CsCalibPoints &oFramePoint) = 0;
    // 读取标定中间点
    virtual bool RefreshCalibratePoints(WobjCalibData &wobjCalibData) = 0;

    // 保存用户安装参数（备注）
    virtual bool SaveUserInstallParam(int16u wobjNo, const UserInstallParam &userInstallParam) = 0;

    // 取当前位置
    virtual bool GetCurPos(RobotHoldWobjType method, RobPos &pos) = 0;
    // 运动到点
    virtual bool MoveToPoint(RobPos pos, MoveType type, RobotHoldWobjType method, double lh = 0.0, double mh = 0.0, double rh = 0.0) = 0;
    // 停止到点
    virtual bool StopToPoint() = 0;

    /***************************************提供字符串给页面****************************************/
    // 工具Id对应名称查询
    virtual string WobjIdNameSearch(WobjId id) = 0;
    // 运动到点类型名称查询
    virtual string WobjExcuteMoveTypeNameSearch(MoveType type) = 0;
    // 用户坐标系是否固定名称查询
    virtual string UserFrameFixedNameSearch(UserFrameFixed type) = 0;
    // 标定方法名称查询
    virtual string CalibMethodNameSearch(WobjUFrameCalibMethod method) = 0;
    // 标定方法名称查询
    virtual string CalibMethodNameSearch(WobjOFrameCalibMethod method) = 0;
    // 机器人夹持工件类型UFrame标定方法查询
    virtual vector<string> HoldTypeUFrameCalibMethodSearch(RobotHoldWobjType type) = 0;
    // 机器人夹持工件类型OFrame标定方法查询
    virtual vector<string> HoldTypeOFrameCalibMethodSearch(RobotHoldWobjType type) = 0;
    // UFrame标定方法对应点名称查询
    virtual vector<string> CalibMethodTeachPointNameSearch(WobjUFrameCalibMethod method) = 0;
    // OFrame标定方法对应点名称查询
    virtual vector<string> CalibMethodTeachPointNameSearch(WobjOFrameCalibMethod method) = 0;

#pragma endregion

Q_SIGNALS:
    // 当前工件号变更信号
    void currentIdChanged(int16u id);
    // 工件数据改变事件
    void wobjDataChanged(int16u id);
};
}  // namespace InoRobBusiness
