#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "Calibrate/Calibrate_V1.h"
#include "Connection/Connection_V1.h"
#include "Control/Control_V1.h"
#include "ControlAuthority/ControlAuthority_V1.h"
#include "Debuger/Debuger_V1.h"
#include "Fieldbus/Fieldbus_V1.h"
#include "FunctionSafe/SafeParaSettingMgr_V1.h"
#include "Load/Load_V1.h"
#include "LoadIdentify/LoadIdentify_V1.h"
#include "Maintenance/Maintenance_V1.h"
#include "MechUnit/MechUnit_V1.h"
#include "MechUnit/MechUnitManage_V1.h"
#include "Monitor/Monitor_V1.h"
#include "Monitor/WarnInfo_V1.h"
#include "Motion/Motion_V1.h"
#include "Peripheral/Peripheral_V1.h"
#include "Position/Position_V1.h"
#include "RCConfig/RCConfig_V1.h"
#include "RCScheduler/RCScheduler_V1.h"
#include "Resource/Resource_V1.h"
#include "RobotArm/RobotArm_V1.h"
#include "RobotControllerEvents/RobotControllerEvents_V1.h"
#include "ScriptExtension/ScriptExtension_V1.h"
#include "Task/Task_V1.h"
#include "Tool/Tool_V1.h"
#include "TrajectoryRecovery/TrajectoryRecovery_V1.h"
#include "Transfor/Transfor_V1.h"
#include "Wobj/Wobj_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Controller_V1
{
#pragma region 构造与析构

private:
    IController *_controller = nullptr;

public:
    Controller_V1(IController *controller);
    ~Controller_V1();

#pragma endregion

#pragma region 子模型

private:
    Calibrate_V1 *_calibrate_V1 = nullptr;
    Connection_V1 *_connection_V1 = nullptr;
    Control_V1 *_control_V1 = nullptr;
    ControlAuthority_V1 *_controlAuthority_V1 = nullptr;
    Debuger_V1 *_debuger_V1 = nullptr;
    Fieldbus_V1 *_fieldbus_V1 = nullptr;
    SafeParaSettingMgr_V1 *_safeParaSettingMgr_V1 = nullptr;
    Load_V1 *_load_V1 = nullptr;
    LoadIdentify_V1 *_loadIdentify_V1 = nullptr;
    Maintenance_V1 *_maintenance_V1 = nullptr;
    MechUnit_V1 *_mechUnit_V1 = nullptr;
    MechUnitManage_V1 *_mechUnitManage_V1 = nullptr;
    Monitor_V1 *_monitor_V1 = nullptr;
    WarnInfo_V1 *_warnInfo_V1 = nullptr;
    Motion_V1 *_motion_V1 = nullptr;
    Peripheral_V1 *_peripheral_V1 = nullptr;
    Position_V1 *_position_V1 = nullptr;
    RCConfig_V1 *_rcConfig_V1 = nullptr;
    RCScheduler_V1 *_rcScheduler_V1 = nullptr;
    Resource_V1 *_resource_V1 = nullptr;
    RobotArm_V1 *_robotArm_V1 = nullptr;
    RobotControllerEvents_V1 *_robotControllerEvents_V1 = nullptr;
    ScriptExtension_V1 *_scriptExtension_V1 = nullptr;
    Task_V1 *_task_V1 = nullptr;
    Tool_V1 *_tool_V1 = nullptr;
    TrajectoryRecovery_V1 *_trajectoryRecovery_V1 = nullptr;
    Transfor_V1 *_transfor_V1 = nullptr;
    Wobj_V1 *_wobj_V1 = nullptr;

public:
    // 标定
    Calibrate_V1 *GetCalibrate();
    bool SetCalibrate(Calibrate_V1 *calibrate_V1);
    // 连接
    Connection_V1 *GetConnection();
    bool SetConnection(Connection_V1 *connection_V1);
    // 操控
    Control_V1 *GetControl();
    bool SetControl(Control_V1 *control_V1);
    // 控制权
    ControlAuthority_V1 *GetControlAuthority();
    bool SetControlAuthority(ControlAuthority_V1 *controlAuthority_V1);
    // 调试
    Debuger_V1 *GetDebuger();
    bool SetDebuger(Debuger_V1 *debuger_V1);
    // 总线
    Fieldbus_V1 *GetFieldbus();
    bool SetFieldbus(Fieldbus_V1 *fieldbus_V1);
    // 功能安全
    SafeParaSettingMgr_V1 *GetSafeParaSettingMgr();
    bool SetSafeParaSettingMgr(SafeParaSettingMgr_V1 *safeParaSettingMgr_V1);
    // 负载
    Load_V1 *GetLoad();
    bool SetLoad(Load_V1 *load_V1);
    // 负载辨识
    LoadIdentify_V1 *GetLoadIdentify();
    bool SetLoadIdentify(LoadIdentify_V1 *loadIdentify_V1);
    // 维护
    Maintenance_V1 *GetMaintenance();
    bool SetMaintenance(Maintenance_V1 *maintenance_V1);
    // 机械单元
    MechUnit_V1 *GetMechUnit();
    bool SetMechUnit(MechUnit_V1 *mechUnit_V1);
    // 机械单元管理
    MechUnitManage_V1 *GetMechUnitManage();
    bool SetMechUnitManage(MechUnitManage_V1 *mechUnitManage_V1);
    // 监控
    Monitor_V1 *GetMonitor();
    bool SetMonitor(Monitor_V1 *monitor_V1);
    // 报警
    WarnInfo_V1 *GetWarnInfo();
    bool SetWarnInfo(WarnInfo_V1 *warnInfo_V1);
    // 运动
    Motion_V1 *GetMotion();
    bool SetMotion(Motion_V1 *motion_V1);
    // 外设
    Peripheral_V1 *GetPeripheral();
    bool SetPeripheral(Peripheral_V1 *peripheral_V1);
    // 位置
    Position_V1 *GetPosition();
    bool SetPosition(Position_V1 *position_V1);
    // 控制器配置
    RCConfig_V1 *GetRCConfig();
    bool SetRCConfig(RCConfig_V1 *rcConfig_V1);
    // 调度
    RCScheduler_V1 *GetRCScheduler();
    bool SetRCScheduler(RCScheduler_V1 *rcScheduler_V1);
    // 资源
    Resource_V1 *GetResource();
    bool SetResource(Resource_V1 *resource_V1);
    // 机械臂
    RobotArm_V1 *GetRobotArm();
    bool SetRobotArm(RobotArm_V1 *robotArm_V1);
    // 控制器事件
    RobotControllerEvents_V1 *GetRobotControllerEvents();
    bool SetRobotControllerEvents(RobotControllerEvents_V1 *robotControllerEvents_V1);
    // 脚本(协作机器人)
    ScriptExtension_V1 *GetScriptExtension();
    bool SetScriptExtension(ScriptExtension_V1 *scriptExtension_V1);
    // 任务
    Task_V1 *GetTask();
    bool SetTask(Task_V1 *task_V1);
    // 工具
    Tool_V1 *GetTool();
    bool SetTool(Tool_V1 *tool_V1);
    // 轨迹恢复阈值设置
    TrajectoryRecovery_V1 *GetTrajectoryRecovery();
    bool SetTrajectoryRecovery(TrajectoryRecovery_V1 *trajectoryRecovery_V1);
    // 译码
    Transfor_V1 *GetTransfor();
    bool SetTransfor(Transfor_V1 *transfor_V1);
    // 工件
    Wobj_V1 *GetWobj();
    bool SetWobj(Wobj_V1 *wobj_V1);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
