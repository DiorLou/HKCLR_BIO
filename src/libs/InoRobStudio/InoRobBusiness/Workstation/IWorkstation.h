#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "../Controller/IController.h"
#include "../Project/IProject.h"
#include "../User/IUser.h"
#include "../RobotParam/IRobotParam.h"
#include"../Controller/Plugin/IInoRobPluginMasterService.h"

#ifdef _WIN32
#include "../GrpcService/IGrpcService.h"
#endif


namespace InoRobBusiness
{
#pragma region 枚举

// 工作站类型
enum class WorkstationType
{
    Unknow = 0,  // 未知
    TP = 1,      // 示教器
    PC = 2,      // PC编程平台
    TP2 = 3,     // 示教器2.0
};

#pragma endregion

/*
    工作站：工作站即上位机，一台PC，一台手持示教器，均视为一个工作站；
    一个工作站可连接多个控制器；

    Create by WuJian at 2023/7/19
*/
class INOROBBUSINESS_CLASS IWorkstation : public QObject
{
    Q_OBJECT

public:
    virtual ~IWorkstation()
    {
    }

#pragma region 基础

    // 工作站ID（唯一标识）
    virtual string GetID() = 0;
    virtual bool SetID(const string &id) = 0;

    // 工作站名称
    virtual string GetName() = 0;
    virtual bool SetName(const string &name) = 0;

    // 当前工作站类型
    virtual WorkstationType GetWorkstationType() = 0;
    virtual bool SetWorkstationType(WorkstationType workstationType) = 0;

    // 程序运行根目录（以反斜杠结尾如 c:\\test\\）
    virtual string GetAppRootPath() = 0;
    virtual bool SetAppRootPath(const string &appRootPath) = 0;

    virtual ILanguage *getLanguage() = 0;
    virtual void setLanguage(ILanguage *lan) = 0;

#pragma endregion

#pragma region 控制器

    // 工作站应支持连接多个控制器，暂实现单控制器版本，后续待完善

    virtual IController *GetController() = 0;
    virtual bool SetController(IController *controller) = 0;

#pragma endregion

#pragma region 工程管理

    virtual IProject *GetProject() = 0;
    virtual bool SetProject(IProject *project) = 0;

#pragma endregion

#pragma region 用户
    virtual IUser *GetUser() = 0;
    virtual bool SetUser(IUser *user) = 0;
#pragma endregion

#pragma region 机型参数
    virtual IRobotParam *getRobotParam() = 0;
    virtual bool setRobotParam(IRobotParam *pRobotParam) = 0;
#pragma endregion
#pragma region 工艺管理
    virtual bool setPluginMasterService(IInoRobPluginMasterService* pPluginMasterService) = 0;
    virtual IInoRobPluginMasterService* getPluginMasterService() = 0;
#pragma endregion

#pragma region Grpc服务
#ifdef _WIN32
    virtual IGrpcService *getGrpcService() = 0;
    virtual bool setGrpcService(IGrpcService *pGrpcService) = 0;
#endif
#pragma endregion
};
}  // namespace InoRobBusiness
