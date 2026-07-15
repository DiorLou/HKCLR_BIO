#pragma once
#include "Workstation/IWorkstation.h"

namespace InoRobBusiness
{
/*
    默认工厂（抽象工厂模式）
    Create by WuJian at 2022/4
*/
class INOROBBUSINESS_CLASS FactoryDefault
{
public:
    FactoryDefault();
    ~FactoryDefault();

public:
    // 构造工作站实例（自动初始化）
    // workstationType：工作站类型
    // appRootPath：程序运行根目录
    IWorkstation *WorkstationBuild(bool isInit, WorkstationType workstationType, const string &appRootPath);

    // 构造工作站实例（自动初始化）
    // workstationType：工作站类型
    // appRootPath：程序运行根目录
    IWorkstation *WorkstationBuild(WorkstationType workstationType, const string &appRootPath);
};

}  // namespace InoRobBusiness