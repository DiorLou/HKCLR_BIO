#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../GlobalDataTypes_V1.h"
#include "../../DataService/DataSrvGlobal_V1.h"

using namespace InoRobBusiness;

/*
    工具
    2024/08/19
*/
namespace InoRobBusinessProxy
{
#define TOOL_COUNT_V1                            16                                                          // 工具参数套数
#define TOOL_CALIBRATE_POINTS_CONTROLLER_PATH_V1 _T("/media/sdcard1/robotUserParameter/ToolCalibData.json")  // 控制器文件路径
#define TooTOOL_CALIBRATE_POINTS_FILE_NAME_V1    _T("ToolCalibData.json")                                    // 中间点文件名称

// 工具标定方法
enum ToolCalibMethod_V1
{
    ROB_HOLD_TOOL_3TCP_V1 = 0,    // 夹持工具：0-三点TCP
    ROB_HOLD_TOOL_3TCPZX_V1 = 1,  // 夹持工具：1-三点TCP+ZX
    EXTERN_TOOL_1TCP_V1 = 2,      // 外部工具：2-已知工具一点TCP
    EXTERN_TOOL_1TCPZX_V1 = 3,    // 外部工具：3-已知工具一点TCP+ZX
    EXTERN_TOOL_3TCP_V1 = 4,      // 外部工具：4-未知工具三点TCP
    EXTERN_TOOL_3TCPZX_V1 = 5,    // 外部工具：5-未知工具三点TCP+ZX
    ROB_HOLD_TOOL_3TCPX_V1 = 6,   // 夹持工具：6-三点TCP+X（适用于四轴机器人）
    EXTERN_TOOL_1TCPX_V1 = 7,     // 外部工具：7-已知工具一点TCP+X（适用于四轴机器人）
    EXTERN_TOOL_3TCPX_V1 = 8,     // 外部工具：8-未知工具三点TCP+X（适用于四轴机器人）
};

enum RobotHoldToolType_V1
{
    TOOL_TYPE_EXTERN_TOOL_V1 = 0,  // 外部工具
    TOOL_TYPE_ROBOT_HOLD_V1 = 1,   // 夹持工具
};

enum ToolId_V1
{
    TOOL_ID_TOOL0_V1 = 0,
    TOOL_ID_TOOL1_V1 = 1,
    TOOL_ID_TOOL2_V1 = 2,
    TOOL_ID_TOOL3_V1 = 3,
    TOOL_ID_TOOL4_V1 = 4,
    TOOL_ID_TOOL5_V1 = 5,
    TOOL_ID_TOOL6_V1 = 6,
    TOOL_ID_TOOL7_V1 = 7,
    TOOL_ID_TOOL8_V1 = 8,
    TOOL_ID_TOOL9_V1 = 9,
    TOOL_ID_TOOL10_V1 = 10,
    TOOL_ID_TOOL11_V1 = 11,
    TOOL_ID_TOOL12_V1 = 12,
    TOOL_ID_TOOL13_V1 = 13,
    TOOL_ID_TOOL14_V1 = 14,
    TOOL_ID_TOOL15_V1 = 15,
};

// 工具下拉框
typedef struct _ToolItem_V1
{
    ToolId_V1 ToolNo;
    string ItemName;

} ToolItem_V1;

typedef struct _RobHoldItem_V1
{
    int16s Id;
    string ItemName;

} RobHoldItem_V1;

typedef struct _CalibMethodItem_V1
{
    ToolCalibMethod_V1 calibMethod;
    string ItemName;
} CalibMethodItem_V1;

typedef struct _HoldTypeCalibMethodItem_V1
{
    RobotHoldToolType_V1 type;
    string methodList;
} HoldTypeCalibMethodItem_V1;

typedef struct _ToolCalibMethodTeachPointNameItem_V1
{
    ToolCalibMethod_V1 method;
    string nameList;
} ToolCalibMethodTeachPointNameItem_V1;

typedef struct _ToolExcuteMoveTypeItem_V1
{
    MoveType_V1 type;
    string ItemName;
} ToolExcuteMoveTypeItem_V1;

// 标定类型
typedef struct _ToolCalibrateTitle_V1
{
    RobotHoldToolType_V1 Type;
    string Title;
} ToolCalibrateTitle_V1;

// 标定方法对应的提示
typedef struct _ToolCalibrateTip_V1
{
    ToolCalibMethod_V1 CalibMethod;
    string Tip;
} ToolCalibrateTip_V1;

class INOROBBUSINESSPROXY_CLASS Tool_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static ToolCalibMethod_V1 ToolCalibMethod_ToProxy(ToolCalibMethod toolCalibMethod);
    static ToolCalibMethod ToolCalibMethod_FromProxy(ToolCalibMethod_V1 toolCalibMethod_V1);

    static RobotHoldToolType_V1 RobotHoldToolType_ToProxy(RobotHoldToolType robotHoldToolType);
    static RobotHoldToolType RobotHoldToolType_FromProxy(RobotHoldToolType_V1 robotHoldToolType_V1);

    static ToolId_V1 ToolId_ToPRoxy(ToolId toolId);
    static ToolId ToolId_FromProxy(ToolId_V1 toolId_V1);

    static bool ToolItem_ToProxy(const ToolItem &toolItem, ToolItem_V1 &toolItem_V1);
    static bool toolItem_FromProxy(const ToolItem_V1 &toolItem_V1, ToolItem &toolItem);

    static bool RobHoldItem_ToProxy(const RobHoldItem &robHoldItem, RobHoldItem_V1 &robHoldItem_V1);
    static bool RobHoldItem_FromProxy(const RobHoldItem_V1 &robHoldItem_V1, RobHoldItem &robHoldItem);

    static bool CalibMethodItem_ToProxy(const CalibMethodItem &calibMethodItem, CalibMethodItem_V1 &calibMethodItem_V1);
    static bool CalibMethodItem_FromProxy(const CalibMethodItem_V1 &calibMethodItem_V1, CalibMethodItem &calibMethodItem);

    static bool HoldTypeCalibMethodItem_ToProxy(const HoldTypeCalibMethodItem &holdTypeCalibMethodItem, HoldTypeCalibMethodItem_V1 &holdTypeCalibMethodItem_V1);
    static bool HoldTypeCalibMethodItem_FromProxy(const HoldTypeCalibMethodItem_V1 &holdTypeCalibMethodItem_V1, HoldTypeCalibMethodItem &holdTypeCalibMethodItem);

    static bool ToolCalibMethodTeachPointNameItem_ToProxy(const ToolCalibMethodTeachPointNameItem &toolCalibMethodTeachPointNameItem, ToolCalibMethodTeachPointNameItem_V1 &toolCalibMethodTeachPointNameItem_V1);
    static bool ToolCalibMethodTeachPointNameItem_FromProxy(const ToolCalibMethodTeachPointNameItem_V1 &toolCalibMethodTeachPointNameItem_V1, ToolCalibMethodTeachPointNameItem &toolCalibMethodTeachPointNameItem);

    static bool ToolExcuteMoveTypeItem_ToProxy(const ToolExcuteMoveTypeItem &toolExcuteMoveTypeItem, ToolExcuteMoveTypeItem_V1 &toolExcuteMoveTypeItem_V1);
    static bool ToolExcuteMoveTypeItem_FromProxy(const ToolExcuteMoveTypeItem_V1 &toolExcuteMoveTypeItem_V1, ToolExcuteMoveTypeItem &toolExcuteMoveTypeItem);

    static bool ToolCalibrateTitle_ToProxy(const ToolCalibrateTitle &toolCalibrateTitle, ToolCalibrateTitle_V1 &toolCalibrateTitle_V1);
    static bool ToolCalibrateTitle_FromProxy(const ToolCalibrateTitle_V1 &toolCalibrateTitle_V1, ToolCalibrateTitle &toolCalibrateTitle);

    static bool ToolCalibrateTip_ToProxy(const ToolCalibrateTip &toolCalibrateTip, ToolCalibrateTip_V1 &toolCalibrateTip_V1);
    static bool ToolCalibrateTip_FromProxy(const ToolCalibrateTip_V1 &toolCalibrateTip_V1, ToolCalibrateTip &toolCalibrateTip);

#pragma endregion

#pragma region 构造与析构

private:
    ITool *_tool = nullptr;

public:
    Tool_V1(ITool *tool);
    ~Tool_V1();

#pragma endregion

#pragma region 通用

public:
    // 信号转换
    void currentIdChangedHandler(int16u currentIdChangedData);

    // 获取工具号总数量
    int16u GetCount();

    // 获取当前工具号
    int16u GetCurrentId();

    // 设定当前工具号
    bool SetCurrentId(int16u currentId);

    // 当前工具号变更信号
    rsignal<int16u> currentIdChanged;

    // 变更当前工具号（自动判断并触发变更事件，注：由周期线程使用，模型外严禁调用）
    void onCurrentIdChange(int16u currentId);

    // 当前工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool CurrentIsRobotHold(bool &result);

    // 指定工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsRobotHold(int16u toolNo, bool &result);

#pragma endregion

#pragma region 工具参数

public:
    // 读取工具参数
    bool GetToolParam(int16u toolNo, ToolData_V1 &toolData);  //  --  已测

    // 设置工具参数
    bool SetToolParam(int16u toolNo, const ToolData_V1 &toolData);

#pragma endregion

#pragma region 其他

public:
    // 保存工具参数
    bool Save(int toolNo, ToolData_V1 *data, bool isSaveIDResult = false);

    // 刷新工具参数
    bool Refresh(int toolNo, ToolData_V1 *data);

    // 清0
    bool Clear(int toolNo);

    // 标定
    bool Calibrate(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    // 检查控制权
    bool CheckAuthority();

    // 保存参数控制权检查
    bool checkToolOperatePermission();

    // 保存标定中间点
    bool SaveCalibratePoints(int16u toolNo, const CsCalibPoints_V1 &point);

    // 读取标定中间点
    bool RefreshCalibratePoints(ToolCalibData_V1 &point);

    // 保存用户安装参数（备注）
    bool SaveUserInstallParam(int16u toolNo, const UserInstallParam_V1 &userInstallParam);

    // 取当前位置
    bool GetCurPos(RobPos_V1 &pos, ToolCalibMethod_V1 method);

    // 运动到点
    bool MoveToPoint(ToolCalibMethod_V1 method, RobPos_V1 pos, MoveType_V1 type, double lh = 0.0, double mh = 0.0, double rh = 0.0);

    // 停止到点
    bool StopToPoint();

    // 检查描述字段
    bool checkDescriptionValueValid(const std::string &description);

    /***********************************提供字符串给页面***********************************/
    // 工具Id对应名称查询
    string ToolIdNameSearch(ToolId_V1 id);

    // 标定方法名称查询
    string CalibMethodNameSearch(ToolCalibMethod_V1 method);

    // 根据标定名称，查询类型
    ToolCalibMethod_V1 CalibMethodByName(string name);

    // 机器人夹持工具类型标定方法查询
    vector<string> HoldTypeCalibMethodSearch(RobotHoldToolType_V1 type);

    vector<string> CalibMethodTeachPointNameSearch(ToolCalibMethod_V1 method);

    // 运动到点类型名称查询
    string ToolExcuteMoveTypeNameSearch(MoveType_V1 type);

    // 界面标定方法查询
    string ToolCalibrateTitleSearch(RobotHoldToolType_V1 type);

    // 界面提示查询
    string ToolCalibrateTipSearch(ToolCalibMethod_V1 method);

    // 工具数据改变事件
    rsignal<int16u> ToolDataChanged;
    void ToolDataChangedHandler(int16u ToolDataChangedSig);

    /**************夹持工具标定**************/
    // 获取标定结果：夹持工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool GripToolParmBy3P(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    // 获取标定结果：夹持工具三点法TCP+ZX)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool GripToolParmBy3PZX(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    /**************外部工具标定**************/
    // 获取标定结果：外部工具已知工具一点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy1P(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    // 获取标定结果：外部工具已知工具一点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy1PZX(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    // 获取标定结果：外部工具未知工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy3P(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    // 获取标定结果：外部工具未知工具三点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy3PZX(const CsCalibPoints_V1 &midPos, Pose_V1 &calibResult);

    rsignal<ToolCalibError_V1> ToolCalibErr;
    void ToolCalibErrHandler(ToolCalibError ToolCalibErrData);

    // 获取工具下拉框
    vector<ToolItem_V1> GetToolItem();

    // 获取夹持下拉框
    vector<RobHoldItem_V1> GetRobHoldItem();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
