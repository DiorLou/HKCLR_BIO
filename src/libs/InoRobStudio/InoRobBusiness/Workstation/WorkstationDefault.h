#pragma once
#include "IWorkstation.h"
#include "Container.h"

namespace InoRobBusiness
{
/*
    默认工作站
*/
class INOROBBUSINESS_CLASS WorkstationDefault : public IWorkstation
{
    Q_OBJECT

#pragma region 构造与析构

public:
    WorkstationDefault();
    ~WorkstationDefault();

#pragma endregion

#pragma region 基础

private:
    string m_ID;
    string m_Name;
    // 当前工作站类型
    WorkstationType m_WorkstationType;
    // 程序运行根目录
    string m_AppRootPath;

public:
    string GetID();
    bool SetID(const string &id);

    string GetName();
    bool SetName(const string &name);

    WorkstationType GetWorkstationType();
    bool SetWorkstationType(WorkstationType workstationType);

    string GetAppRootPath();
    bool SetAppRootPath(const string &appRootPath);

    ILanguage *getLanguage() override;
    void setLanguage(ILanguage *lan) override;

#pragma endregion

#pragma region 控制器

private:
    IController *m_Controller;
    ILanguage *_pLanguag = nullptr;

public:
    IController *GetController();
    bool SetController(IController *controller);

#pragma endregion

#pragma region 工程管理

private:
    IProject *m_Project;

public:
    IProject *GetProject();
    bool SetProject(IProject *project);

#pragma endregion

#pragma region 用户
private:
    IUser *_pUser = nullptr;

public:
    IUser *GetUser();
    bool SetUser(IUser *user);
#pragma endregion

#pragma region 机型参数
private:
    IRobotParam *_pRobotParam = nullptr;

public:
    IRobotParam *getRobotParam() override;
    bool setRobotParam(IRobotParam *pRobotParam) override;
#pragma endregion

#pragma region 工艺管理
private:
    IInoRobPluginMasterService* _pluginMasterService = NULL;
public:
    bool setPluginMasterService(IInoRobPluginMasterService* pPluginMasterService) override;
    IInoRobPluginMasterService* getPluginMasterService() override;
#pragma endregion

#pragma region Grpc服务
#ifdef _WIN32
private:
    IGrpcService *_pGrpcService = nullptr;

public:
    IGrpcService *getGrpcService();
    bool setGrpcService(IGrpcService *pGrpcService);
#endif
#pragma endregion

};

// 声明工作站单例对象
INOROBBUSINESS_CLASS extern CContainer<WorkstationDefault> gs_Workstation;
}  // namespace InoRobBusiness
