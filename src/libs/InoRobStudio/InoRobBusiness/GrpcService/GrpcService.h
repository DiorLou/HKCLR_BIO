#pragma once
#include "IGrpcService.h"
#include "../Workstation/IWorkstation.h"
#include "../Workstation/WorkstationDefault.h"

#include "../Workstation/WorkstationService.h"
#include "../User/UserService.h"
#include "../Project/ProjectService.h"
#include "../Controller/Connection/ConnectionService.h"
#include "../Controller/Motion/MotionService.h"
#include "../Controller/Monitor/MonitorService.h"
#include "../Controller/Control/ControlService.h"
#include "../Controller/ControlAuthority/ControlAuthorityService.h"
#include "../Controller/Tool/ToolService.h"
#include "../Controller/Wobj/WobjService.h"
#include "../Controller/Load/LoadService.h"
#include "../Controller/Position/PositionService.h"
#include "../Controller/MechUnit/MechUnitService.h"
#include "../Controller/Transfor/TransforService.h"
#include "../Controller/Debuger/DebugerService.h"
#include "../Controller/Task/TaskService.h"
#include "../Controller/RCConfig/RCConfigService.h"
#include "../Controller/RobotArm/RobotArmService.h"
#include "../Controller/Fieldbus/FieldbusService.h"
#include "../Controller/Maintenance/MaintenanceService.h"
#include "../Controller/Resource/ResourceService.h"
#include "TechnologyService.h"

#ifdef COBOT
#include "../Controller/ScriptExtension/ScriptExtensionService.h"
#include "../Controller/FunctionSafe/SafeParaSettingMgrService.h"
#endif

namespace InoRobBusiness
{
class GrpcService : public IGrpcService
{
public:
    GrpcService();
    ~GrpcService();
    
    bool Start(std::string appRootPath);

private:
    //gRPC服务对象
    WorkstationService *_pWorkstationService = nullptr;
    UserService *_pUserService = nullptr;
    ProjectService *_pProjectService = nullptr;
    ConnectionService *_pConnectionService = nullptr;
    MotionService *_pMotionService = nullptr;
    MonitorService *_pMonitorService = nullptr;
    ControlService *_pControlService = nullptr;
    ControlAuthorityService *_pControlAuthorityService = nullptr;
    ToolService *_pToolService = nullptr;
    WobjService *_pWobjService = nullptr;
    LoadService *_pLoadService = nullptr;
    PositionService *_pPositionService = nullptr;
    MechUnitService *_pMechUnitService = nullptr;
    TransforService *_pTransforService = nullptr;
    DebugerService *_pDebugerService = nullptr;
    TaskService *_pTaskService = nullptr;
    RCConfigService *_pRCConfigService = nullptr;
    RobotArmService *_pRobotArmService = nullptr;
    FieldBusService *_pFieldBusService = nullptr;
    MaintenanceService *_pMaintenanceService = nullptr;
    ResourceService *_pResourceService = nullptr;
    TechnologyService *_pTechnologyService = nullptr;
#ifdef COBOT
    ScriptExtensionService *_pScriptExtensionService = nullptr;
    SafeParaSettingMgrService *_pSafeParaSettingMgrService = nullptr;
#endif

    //线程
    bool _isStarted;
    std::shared_ptr<std::thread> _pThread;
    void threadRun();
};
}  // namespace InoRobBusiness
