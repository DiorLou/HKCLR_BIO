#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../Controller/Controller_V1.h"
#include "../Project/Project_V1.h"
#include "../User/User_V1.h"
#include "../RobotParam/RobotParam_V1.h"
#include "../DataService/DataSrvBase_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

// 工作站类型
enum class WorkstationType_V1
{
    Unknow_V1 = 0,  // 未知
    TP_V1 = 1,      // 示教器
    PC_V1 = 2,      // PC编程平台
    TP2_V1 = 3,     // 示教器2.0
};

#pragma endregion

// 工作站（请使用工厂获取单例对象）
class INOROBBUSINESSPROXY_CLASS Workstation_V1
{
#pragma region 构造与析构
private:
    IWorkstation *_workstation = nullptr;
    //是否已完成所有模型及子模型的实例化
    bool _isInstantiated;

    Workstation_V1(const Workstation_V1 &) = delete;
    Workstation_V1 &operator=(const Workstation_V1 &) = delete;

public:
    Workstation_V1();
    ~Workstation_V1();
    void SetWorkstation(IWorkstation *workstation);
    bool GetIsInstantiated();
    void SetIsInstantiated(bool val);

#pragma endregion

#pragma region 数据转换

public:
    static WorkstationType_V1 WorkstationTypeToProxy(WorkstationType workstationType);
    static WorkstationType WorkstationTypeFromProxy(WorkstationType_V1 workstationTypeV1);

#pragma endregion

#pragma region 业务逻辑

public:
    string GetID();
    string GetName();
    WorkstationType_V1 GetWorkstationType();
    string GetAppRootPath();

#pragma endregion

#pragma region 子模型

private:
    Controller_V1 *_controller_V1 = nullptr;
    Project_V1 *_project_V1 = nullptr;
    User_V1 *_user_V1 = nullptr;
    RobotParam_V1 *_robotParam_V1 = nullptr;
    DataSrvBase_V1 *_dataSrvBase_V1 = nullptr;

public:
    // 控制器
    Controller_V1 *GetController();
    bool SetController(Controller_V1 *controllerV1);

    // 工程管理
    Project_V1 *GetProject();
    bool SetProject(Project_V1 *projectV1);

    // 用户
    User_V1 *GetUser();
    bool SetUser(User_V1 *userV1);

    // 机型参数
    RobotParam_V1 *GetRobotParam();
    bool SetRobotParam(RobotParam_V1 *robotParamV1);

    // 控制器通信
    DataSrvBase_V1 *GetDataSrvBase();
    bool SetDataSrvBase(DataSrvBase_V1 *dataSrvBase_V1);

#pragma endregion
};

// 声明工作站单例对象
INOROBBUSINESSPROXY_CLASS extern CContainer<Workstation_V1> gs_Workstation_V1;

}  // namespace InoRobBusinessProxy
