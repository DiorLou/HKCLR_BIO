#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ToolDefault : public ITool
{
#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService;
    // 连接
    IConnection *_pConnection;
    // 监控
    IMonitor *_pMonitor;
    // 位置
    IPosition *_pPosition;
    // 运动
    IMotion *_pMotion;
    // 标定
    ICalibrate *_pCalibrate;
    // 负载
    ILoad *_pLoad;
    // 功能安全
    ISafeParaSettingMgr *_pSafeParaSettingMgr;

public:
    ToolDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~ToolDefault();
    void init() override;
#pragma endregion

#pragma region 通用

    int16u GetCount();

#pragma endregion

    // 获取当前工具号
    int16u GetCurrentId();

    bool SetCurrentId(int16u currentId);
    bool CurrentIsRobotHold(bool &result);

    // 变更当前工具号（自动判断并触发变更事件，注：由周期线程使用，模型外严禁调用）
    void onCurrentIdChange(int16u currentId);

    // 指定工具是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsRobotHold(int16u toolNo, bool &result);

#pragma region 工具参数

    bool GetToolParam(int16u toolNo, ToolData &toolData);
    bool SetToolParam(int16u toolNo, const ToolData &toolData);

#pragma endregion

    // 保存工具参数
    bool Save(int toolNo, ToolData *data, bool isSaveIDResult = false);
    // 刷新工具参数
    bool Refresh(int toolNo, ToolData *data);
    // 清0
    bool Clear(int toolNo);
    // 工具标定
    bool Calibrate(const CsCalibPoints &midPos, Pose &calibResult);
    // 检查控制权
    bool CheckAuthority();

    // 保存参数控制权检查
    bool checkToolOperatePermission();

    // 保存标定中间点
    bool SaveCalibratePoints(int16u toolNo, const CsCalibPoints &point);
    // 读取标定中间点
    bool RefreshCalibratePoints(ToolCalibData &toolCalibData);

    // 保存用户安装数据（备注等）
    bool SaveUserInstallParam(int16u toolNo, const UserInstallParam &userInstallParam);

    // 取当前点
    bool GetCurPos(RobPos &pos, ToolCalibMethod method);
    // 运动到点
    bool MoveToPoint(ToolCalibMethod method, RobPos pos, MoveType type, double lh = 0.0, double mh = 0.0, double rh = 0.0);
    // 停止到点
    bool StopToPoint();

    // 检查描述字段
    bool checkDescriptionValueValid(const std::string &description);

    /***********************字符串查询***********************/
    string ToolIdNameSearch(ToolId id);
    string CalibMethodNameSearch(ToolCalibMethod method);
    ToolCalibMethod CalibMethodByName(string name);
    // 机器人夹持工具类型标定方法查询
    vector<string> HoldTypeCalibMethodSearch(RobotHoldToolType type);
    // 运动到点类型名称查询
    string ToolExcuteMoveTypeNameSearch(MoveType type);

    // 标定方法对应点名称查询
    vector<string> CalibMethodTeachPointNameSearch(ToolCalibMethod method);

    // 界面标定方法查询
    string ToolCalibrateTitleSearch(RobotHoldToolType type);
    // 界面提示查询
    string ToolCalibrateTipSearch(ToolCalibMethod method);
    // 获取工具下拉框
    vector<ToolItem> GetToolItem();
    // 获取夹持下拉框
    vector<RobHoldItem> GetRobHoldItem();

private:
    /**************夹持工具标定**************/
    // 获取标定结果：夹持工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool GripToolParmBy3P(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：夹持工具三点法TCP+ZX)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool GripToolParmBy3PZX(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：夹持工具三点法TCP+X)(四轴机器人)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool GripToolParmBy3PX(const CsCalibPoints &midPos, Pose &calibResult);

    /**************外部工具标定**************/
    // 获取标定结果：外部工具已知工具一点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy1P(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：外部工具已知工具一点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy1PZX(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：外部工具未知工具三点法TCP
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy3P(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：外部工具未知工具三点法TCP+ZX
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy3PZX(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：外部工具已知工具一点法TCP+X(四轴机器人)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy1PX(const CsCalibPoints &midPos, Pose &calibResult);

    // 获取标定结果：外部工具未知工具三点法TCP+X(四轴机器人)
    // 输入：midPos 中间点
    // 返回值：true 表示成功 false 表示失败
    bool ExternToolParmBy3PX(const CsCalibPoints &midPos, Pose &calibResult);

    // 放置标定点中间文件到控制器
    bool PutToolCalibPointFile();
    // 从控制器获取标定点中间文件
    bool GetToolCalibPointFile();
    // 写标定中间点数据到文件
    bool WriteToolCalibPointDataToFile();
    // 从文件中获取标定点中间点数据
    bool ReadToolCalibPointDataFromFile();

    // 标定结果相关状态
    CalibrateState m_State;
    // 工具参数
    Pose m_ToolCrd;
    // 工具标定错误标识
    ToolCalibError m_CalibErr;

    // 所有工具标定点
    ToolCalibData *_toolCalibData;

    // 当前工具号
    int16u _currentId;

    // 打印标定结果信息
    bool PrintClibrateResult(bool bRet, CalibrateState state);

    // 连接状态变化
    void OnConnectionStatusChange(ControllerConnectionStatus status);

    // 功能安全保存工具参数
    bool SetToolParam_SPVer(int16u toolNo, const ToolData &toolData);

private:
    // 工具名称数组
    static const ToolItem _toolNameStrArray[TOOL_COUNT];
    // 标定方法名称数组
    static const vector<CalibMethodItem> _toolCalibMethodNameArray();
    // 四轴机器人夹持类型标定方法查询
    static const vector<HoldTypeCalibMethodItem> _fourAxisHoldTypeCalibMethodArray();
    // 六轴机器人夹持类型标定方法查询
    static const vector<HoldTypeCalibMethodItem> _sixAxisHoldTypeCalibMethodArray();
    // 运动到点类型名称数组
    static const ToolExcuteMoveTypeItem _toolExcuteMoveTypeNameArray[3];
    // 工具标定标题
    static const vector<ToolCalibrateTitle> ToolCalibrateTitleArray();
    // 工具标定提示
    static const vector<ToolCalibrateTip> ToolCalibrateTipArray();
    // 标定方法对应关系
    static const vector<ToolCalibMethodTeachPointNameItem> _toolCalibMethodTeachPointNameArray();

    static const std::string _localFilePath;

    static const std::string _remoteFilePath;

    static const std::string _calibFileName;

    static const std::string _tmpCalibFileName;
};
}  // namespace InoRobBusiness
