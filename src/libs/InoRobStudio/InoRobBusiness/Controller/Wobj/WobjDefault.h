#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS WobjDefault : public IWobj
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService;
    // 连接
    IConnection *m_Connection;
    // 监控
    IMonitor *m_Monitor;
    // 位置
    IPosition *m_Position;
    // 运动
    IMotion *m_Motion;
    // 标定
    ICalibrate *m_Calibrate;
    // 工具
    ITool *m_Tool;
    // 功能安全
    ISafeParaSettingMgr *m_SafeParaSettingMgr;

public:
    WobjDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~WobjDefault();
    void init() override;
#pragma endregion

#pragma region 通用

    int16u GetCount();

#pragma endregion
    // 获取当前工件号
    int16u getCurrentId();

    bool SetCurrentId(int16u currentId);

    // 变更当前工件号
    void onCurrentIdChange(int16u currentId);

    // 当前工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool currentIsRobotHold(bool &result);

    // 指定工件是否为机器人夹持（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsRobotHold(int16u toolNo, bool &result);

    // 指定工件是否为固定（注：通过参数返回是否夹持结果，函数返回值表示是否获取成功）
    bool someoneIsFixed(int16u toolNo, bool &result);

#pragma region 工件参数

    bool GetCurrentWobjParam(WobjData &wobjData);
    bool GetWobjParam(int16u wobjNo, WobjData &wobjData);
    bool SetWobjParam(int16u wobjNo, WobjData wobjData);

#pragma endregion

#pragma region 其它（请分类）

    // 保存工件参数
    bool Save(int wobjNo, WobjData *data);
    // 刷新工件参数
    bool Refresh(int wobjNo, WobjData *data);
    // 清0
    bool Clear(int wobjNo);
    // 标定
    bool Calibrate(string mechUnitName, RobotHoldWobjType type, bool isUFFix, const CsCalibPoints &midUFramePos, const CsCalibPoints &midOFramePos, Pose oldUFrame, Pose &uFrameCalibResult, Pose &oFrameCalibResult);
    // 检查控制权
    bool CheckAuthority();

    // 相关操作控制权检查
    bool checkWobjOperatePermission();

    // 保存标定中间点
    bool SaveCalibratePoints(int16u wobjNo, const CsCalibPoints &uFramePoint, const CsCalibPoints &oFramePoint);
    // 读取标定中间点
    bool RefreshCalibratePoints(WobjCalibData &wobjCalibData);

    // 保存用户安装参数（备注）
    bool SaveUserInstallParam(int16u wobjNo, const UserInstallParam &userInstallParam);

    // 取当前位置
    bool GetCurPos(RobotHoldWobjType robotHoldType, RobPos &pos);
    // 运动到点
    bool MoveToPoint(RobPos pos, MoveType type, RobotHoldWobjType robotHoldType, double lh = 0.0, double mh = 0.0, double rh = 0.0);
    // 停止到点
    bool StopToPoint();

    // 工件Id对应名称查询
    string WobjIdNameSearch(WobjId id);
    // 运动到点类型名称查询
    string WobjExcuteMoveTypeNameSearch(MoveType type);
    // 用户坐标系固定名称查询
    string UserFrameFixedNameSearch(UserFrameFixed type);
    // UFrame标定方法名称查询
    string CalibMethodNameSearch(WobjUFrameCalibMethod method);
    // OFrame标定方法名称查询
    string CalibMethodNameSearch(WobjOFrameCalibMethod method);

    // 机器人夹持工件类型UFrame标定方法查询
    vector<string> HoldTypeUFrameCalibMethodSearch(RobotHoldWobjType type);
    // 机器人夹持工件类型OFrame标定方法查询
    vector<string> HoldTypeOFrameCalibMethodSearch(RobotHoldWobjType type);
    // UFrame标定方法对应点名称查询
    vector<string> CalibMethodTeachPointNameSearch(WobjUFrameCalibMethod method);
    // OFrame标定方法对应点名称查询
    vector<string> CalibMethodTeachPointNameSearch(WobjOFrameCalibMethod method);

#pragma endregion

private:
    // 打印标定结果信息
    bool PrintClibrateResult(bool ret, bool isUFrame, CalibrateState state);
    // 非夹持UFrame三点法
    bool ExternWobjUFrame3P(const CsCalibPoints &midPos, Pose &calibResult);
    // 非夹持UFrame旋转法
    bool ExternWobjUFrameRotary(const CsCalibPoints &midPos, Pose &calibResult);
    // 非夹持OFrame三点法
    bool ExternWobjOFrame3P(const CsCalibPoints &midPos, Pose uFrameCrd, Pose &calibResult);
    // 非夹持非固定OFrame三点法
    bool ExternUnFixedWobjOFrame3P(const string &unitName, const CsCalibPoints &midPos, Pose &calibResult);
    // 夹持UFrame三点法
    bool GripWobjUFrame3P(const CsCalibPoints &midPos, Pose &calibResult);
    // 夹持OFrame三点法
    bool GripWobjOFrame3P(const CsCalibPoints &midPos, Pose uFrameCrd, Pose &calibResult);

    // 放置标定点中间文件到控制器
    bool PutWobjCalibPointFile();
    // 从控制器获取标定点中间文件
    bool GetWobjCalibPointFile();
    // 写标定中间点数据到文件
    bool WriteWobjCalibPointDataToFile();
    // 从文件中获取标定点中间点数据
    bool ReadWobjCalibPointDataFromFile();

    // 连接状态变化
    void OnConnectionStatusChange(ControllerConnectionStatus status);

    // 功能安全保存工件参数
    bool SetWobjParam_SPVer(int16u wobjNo, WobjData wobjData);

private:
    // 所有工件标定点
    WobjCalibData *_wobjCalibData;

private:
    // 工具名称数组
    static const WobjItem _wobjNameStrArray[WOBJ_COUNT];
    // 运动到点类型名称数组
    static const WobjExcuteMoveTypeItem _wobjExcuteMoveTypeNameArray[3];
    // 用户坐标系是否固定数组
    static const UserFrameFixedItem _userFrameFixedNameArray[2];
    // UFrame标定方法名称数组
    static const vector<WobjUFrameCalibMethodNameItem> _wobjUFrameCalibMethodNameArray();
    // OFrame标定方法名称数组
    static const vector<WobjOFrameCalibMethodNameItem> _wobjOFrameCalibMethodNameArray();
    // 夹持类型对应UFrame标定方法数组
    static const vector<WobjHoldTypeCalibMethodItem> _wobjHoldTypeUFrameCalibMethodArray();
    // 夹持类型对应OFrame标定方法数组
    static const vector<WobjHoldTypeCalibMethodItem> _wobjHoldTypeOFrameCalibMethodArray();
    // 标定方法对应点名称数组
    static const vector<WobjUFrameCalibMethodTeachPointNameItem> _wobjUFrameCalibMethodTeachPointNameArray();
    // 标定方法对应点名称数组
    static const vector<WobjOFrameCalibMethodTeachPointNameItem> _wobjOFrameCalibMethodTeachPointNameArray();
    // 本地标定点文件路径
    static const std::string _localCalibrateFilePath;
    // 控制器标定点文件路径
    static const std::string _remoteCalibrateFilePath;
    // 标定点文件名称
    static const std::string _calibFileName;
    // 标定点文件零时名称
    static const std::string _tmpCalibFileName;
};
}  // namespace InoRobBusiness
