#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"

#define TOOL_COUNT                            16                                                          // 工具参数套数
#define TOOL_CALIBRATE_POINTS_CONTROLLER_PATH _T("/media/sdcard1/robotUserParameter/ToolCalibData.json")  // 控制器文件路径
#define TooTOOL_CALIBRATE_POINTS_FILE_NAME    _T("ToolCalibData.json")                                    // 中间点文件名称

/*
    工具
    Create by WuJian at 2022/5/2
*/
namespace InoRobBusiness
{
// 工具标定方法
enum ToolCalibMethod
{
    /****工具标定****/
    ROB_HOLD_TOOL_3TCP = 0,    // 夹持工具：0-三点TCP
    ROB_HOLD_TOOL_3TCPZX = 1,  // 夹持工具：1-三点TCP+ZX
    EXTERN_TOOL_1TCP = 2,      // 外部工具：2-已知工具一点TCP
    EXTERN_TOOL_1TCPZX = 3,    // 外部工具：3-已知工具一点TCP+ZX
    EXTERN_TOOL_3TCP = 4,      // 外部工具：4-未知工具三点TCP
    EXTERN_TOOL_3TCPZX = 5,    // 外部工具：5-未知工具三点TCP+ZX
    ROB_HOLD_TOOL_3TCPX = 6,   // 夹持工具：6-三点TCP+X（适用于四轴机器人）
    EXTERN_TOOL_1TCPX = 7,     // 外部工具：7-已知工具一点TCP+X（适用于四轴机器人）
    EXTERN_TOOL_3TCPX = 8,     // 外部工具：8-未知工具三点TCP+X（适用于四轴机器人）
};

enum RobotHoldToolType
{
    TOOL_TYPE_EXTERN_TOOL = 0,  // 外部工具
    TOOL_TYPE_ROBOT_HOLD = 1,   // 夹持工具
};

enum ToolId
{
    TOOL_ID_TOOL0 = 0,
    TOOL_ID_TOOL1 = 1,
    TOOL_ID_TOOL2 = 2,
    TOOL_ID_TOOL3 = 3,
    TOOL_ID_TOOL4 = 4,
    TOOL_ID_TOOL5 = 5,
    TOOL_ID_TOOL6 = 6,
    TOOL_ID_TOOL7 = 7,
    TOOL_ID_TOOL8 = 8,
    TOOL_ID_TOOL9 = 9,
    TOOL_ID_TOOL10 = 10,
    TOOL_ID_TOOL11 = 11,
    TOOL_ID_TOOL12 = 12,
    TOOL_ID_TOOL13 = 13,
    TOOL_ID_TOOL14 = 14,
    TOOL_ID_TOOL15 = 15,
};

// 工具下拉框
typedef struct _ToolItem_
{
    ToolId ToolNo;
    string ItemName;

} ToolItem;
//
typedef struct _RobHoldItem_
{
    int16s Id;
    string ItemName;

} RobHoldItem;

typedef struct _CalibMethodItem_
{
    ToolCalibMethod calibMethod;
    string ItemName;
} CalibMethodItem;

typedef struct _HoldTypeCalibMethodItem_
{
    RobotHoldToolType type;
    string methodList;
} HoldTypeCalibMethodItem;

typedef struct _ToolCalibMethodTeachPointNameItem_
{
    ToolCalibMethod method;
    string nameList;
} ToolCalibMethodTeachPointNameItem;

typedef struct _ToolExcuteMoveTypeItem_
{
    MoveType type;
    string ItemName;
} ToolExcuteMoveTypeItem;

// 标定类型
typedef struct _ToolCalibrateTitle_
{
    RobotHoldToolType Type;
    string Title;
} ToolCalibrateTitle;

// 标定方法对应的提示
typedef struct _ToolCalibrateTip_
{
    ToolCalibMethod CalibMethod;
    string Tip;
} ToolCalibrateTip;

class INOROBBUSINESS_CLASS ITool : public QObject
{
    Q_OBJECT

public:
    virtual ~ITool()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 通用

    // 获取工具号总数量
    virtual int16u GetCount() = 0;

#pragma endregion

    // 获取当前工具号
    virtual int16u GetCurrentId() = 0;

    // 设定当前工具号
    virtual bool SetCurrentId(int16u currentId) = 0;

    // 变更当前工具号（自动判断并触发变更事件，注：由周期线程使用，模型外严禁调用）
    virtual void onCurrentIdChange(int16u currentId) = 0;

    // 当前工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    virtual bool CurrentIsRobotHold(bool &result) = 0;

    // 指定工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    virtual bool someoneIsRobotHold(int16u toolNo, bool &result) = 0;

#pragma region 工具参数

    // 读取工具参数
    virtual bool GetToolParam(int16u toolNo, ToolData &toolData) = 0;
    // 设置工具参数
    virtual bool SetToolParam(int16u toolNo, const ToolData &toolData) = 0;

#pragma endregion

#pragma region 其它（请分类）

    // 保存工具参数
    virtual bool Save(int toolNo, ToolData *data, bool isSaveIDResult = false) = 0;
    // 刷新工具参数
    virtual bool Refresh(int toolNo, ToolData *data) = 0;
    // 清0
    virtual bool Clear(int toolNo) = 0;
    // 标定
    virtual bool Calibrate(const CsCalibPoints &midPos, Pose &calibResult) = 0;
    // 检查控制权
    virtual bool CheckAuthority() = 0;

    // 保存参数控制权检查
    virtual bool checkToolOperatePermission() = 0;

    // 保存标定中间点
    virtual bool SaveCalibratePoints(int16u toolNo, const CsCalibPoints &point) = 0;
    // 读取标定中间点
    virtual bool RefreshCalibratePoints(ToolCalibData &point) = 0;

    // 保存用户安装参数（备注）
    virtual bool SaveUserInstallParam(int16u toolNo, const UserInstallParam &userInstallParam) = 0;

    // 取当前位置
    virtual bool GetCurPos(RobPos &pos, ToolCalibMethod method) = 0;
    // 运动到点
    virtual bool MoveToPoint(ToolCalibMethod method, RobPos pos, MoveType type, double lh = 0.0, double mh = 0.0, double rh = 0.0) = 0;
    // 停止到点
    virtual bool StopToPoint() = 0;

    // 检查描述字段
    virtual bool checkDescriptionValueValid(const std::string &description) = 0;

    /***********************************提供字符串给页面***********************************/
    // 工具Id对应名称查询
    virtual string ToolIdNameSearch(ToolId id) = 0;
    // 标定方法名称查询
    virtual string CalibMethodNameSearch(ToolCalibMethod method) = 0;

    // 根据标定名称，查询类型
    virtual ToolCalibMethod CalibMethodByName(string name) = 0;

    // 机器人夹持工具类型标定方法查询
    virtual vector<string> HoldTypeCalibMethodSearch(RobotHoldToolType type) = 0;

    virtual vector<string> CalibMethodTeachPointNameSearch(ToolCalibMethod method) = 0;

    // 运动到点类型名称查询
    virtual string ToolExcuteMoveTypeNameSearch(MoveType type) = 0;
    // 界面标定方法查询
    virtual string ToolCalibrateTitleSearch(RobotHoldToolType type) = 0;
    // 界面提示查询
    virtual string ToolCalibrateTipSearch(ToolCalibMethod method) = 0;

    /**************夹持工具标定**************/
    // 获取标定结果：夹持工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool GripToolParmBy3P(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    // 获取标定结果：夹持工具三点法TCP+ZX)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool GripToolParmBy3PZX(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    /**************外部工具标定**************/
    // 获取标定结果：外部工具已知工具一点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool ExternToolParmBy1P(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    // 获取标定结果：外部工具已知工具一点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool ExternToolParmBy1PZX(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    // 获取标定结果：外部工具未知工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool ExternToolParmBy3P(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    // 获取标定结果：外部工具未知工具三点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    virtual bool ExternToolParmBy3PZX(const CsCalibPoints &midPos, Pose &calibResult) = 0;

    // 获取工具下拉框
    virtual vector<ToolItem> GetToolItem() = 0;

    // 获取夹持下拉框
    virtual vector<RobHoldItem> GetRobHoldItem() = 0;

#pragma endregion

Q_SIGNALS:
    // 当前工具号变更信号
    void currentIdChanged(int16u id);

    // 工具数据改变事件
    void toolDataChanged(int16u id);

    void toolCalibErr(ToolCalibError err);
};
}  // namespace InoRobBusiness
