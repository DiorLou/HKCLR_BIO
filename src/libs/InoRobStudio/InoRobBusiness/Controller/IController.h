#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "IDataSrvBase.h"

#include "Connection/IConnection.h"
#include "Monitor/IMonitor.h"
#include "Monitor/IWarnInfo.h"
#include "DataSubscribe/IDataSubscribe.h"
#include "RCScheduler/IRCScheduler.h"
#include "Control/IControl.h"
#include "Position/IPosition.h"
#include "RCConfig/IRCConfig.h"
#include "Resource/IResource.h"
#include "Motion/IMotion.h"
#include "RobotArm/IRobotArm.h"
#include "Calibrate/ICalibrate.h"
#include "Load/ILoad.h"
#include "Tool/ITool.h"
#include "Wobj/IWobj.h"
#include "LoadIdentify/ILoadIdentify.h"
#include "MechUnit/IMechUnit.h"
#include "MechUnit/IMechUnitManage.h"
#include "Peripheral/IPeripheral.h"
#include "Fieldbus/IFieldbus.h"
#include "Maintenance/IMaintenance.h"
#include "Debuger/IDebuger.h"
#include "Task/ITask.h"
#include "Transfor/ITransfor.h"
#include "ScriptExtension/IScriptExtension.h"
#include "PubSub/ISubscriber.h"
#include "ControlAuthority/IControlAuthority.h"
#include "RobotControllerEvents/IRobotControllerEvents.h"
#include "FunctionSafe/ISafeParaSettingMgr.h"
#include "TrajectoryRecovery/ITrajectoryRecovery.h"
#include "Language/ILanguage.h"
#include "ForceCtrl/IForceCtrl.h"

namespace InoRobBusiness
{
#pragma region 枚举

// 控制器启动状态（参考M_EBOOT_STATE枚举）
enum ControllerBootStatus : int32s
{
    CONTROLLER_BOOT_STATUS_START = -1,
    CONTROLLER_BOOT_STATUS_INSTALL = 0,         // 系统开始启动
    CONTROLLER_BOOT_STATUS_CONNECTED = 1,       // 示教器通信连接成功
    CONTROLLER_BOOT_STATUS_FPGAOK,              // FPGA就绪
    CONTROLLER_BOOT_STATUS_DSPOK,               // 正在配置DSP参数
    CONTROLLER_BOOT_STATUS_ETHCATOK,            // 正在初始化EtherCAT参数
    CONTROLLER_BOOT_STATUS_IRLINKOK,            // 正在初始化IRLink
    CONTROLLER_BOOT_STATUS_VISIONOK,            // 正在启动视觉线程
    CONTROLLER_BOOT_STATUS_DSPCONECTOK,         // 正在启动DSP通信线程
    CONTROLLER_BOOT_STATUS_DSPINSTALL,          // 正在初始化DSP数据
    CONTROLLER_BOOT_STATUS_ARMOK,               // 正在完成控制器启动
    CONTROLLER_BOOT_STATUS_COMPLETE = 11,       // 控制器启动完成 ★
    CONTROLLER_BOOT_STATUS_INIT_ERR = 12,       // 初始化错误
    CONTROLLER_BOOT_STATUS_CONNECT_FAIL = 100,  // 连接设备失败
    CONTROLLER_BOOT_STATUS_CONNECT_OK,          //
};

// 功能模块枚举
enum class FunctionModuleID
{
    CONNECTION = 0,
    MONITOR,
    CONTROLAUTHORITY,
    DATASUBSCRIBE,
    RCSCHEDULER,
    CONTROL,
    POSITION,
    RCCONFIG,
    WARNINFO,
    RESOURCE,
    MOTION,
    CALIBRATE,
    ROBOTARM,
    LOAD,
    TOOL,
    WOBJ,
    LOADIDENTIFY,
    MECHUNIT,
    MECHUNITMANAGE,
    PERIPHERAL,
    FIELDBUS,
    MAINTENANCE,
    DEBUGER,
    TASK,
    TRANSFOR,
    SCRIPTEXTENSION,
    SUBSCRIBER,
    ROBOTCONTROLLEREVENTS,
    SAFEPARASETTINGMGR,
    TRAJECTORYRECOVERY,
    USER,
    PROJECT,
    ROBOTPARAM,
    PLUGINMANAGE,
    FORCECTRL,
    FRICTIONCOMPENSATION,
    BACKLASHCOMPENSATION
};

#pragma endregion

/*
    控制器接口（抽象），成员定义注意事项：
    1、建议使用子模型包装相关的数据、行为与信号
    2、接口是面向所有实现的通用抽象，因此接口成员的定义应考虑其通用性
*/
class INOROBBUSINESS_CLASS IController : public QObject
{
    Q_OBJECT

public:
    virtual ~IController()
    {
    }

#pragma region 基础

    // 控制器ID（唯一）
    virtual string GetID() = 0;
    virtual void SetID(string id) = 0;
    // 控制器名称
    virtual string GetName() = 0;
    virtual void SetName(string name) = 0;
    virtual void getMap(map<FunctionModuleID, string> &objNameMap) = 0;
    // 根据名称获得对象
    virtual QObject *getObjectByName(FunctionModuleID id) = 0;
    virtual void initAsyncModule() = 0;
#pragma endregion

};  // end class
}  // namespace InoRobBusiness
