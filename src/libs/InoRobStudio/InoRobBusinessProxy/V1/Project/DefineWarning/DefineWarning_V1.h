#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../ProjectHelper_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
// 用户自定义报警
class INOROBBUSINESSPROXY_CLASS DefineWarning_V1
{
#pragma region 构造与析构

private:
    IDefineWarning *_defineWarning;

public:
    DefineWarning_V1(IDefineWarning *defineWarning);
    ~DefineWarning_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 设置工程的文件操作模式
    void setProjectOperateMode(ProjectFileOperateMode_V1 mode);
    // 设置控制器ip地址(依赖注入)
    void SetControllerIp(const std::string &ip);
    // 设置当前加载的工程名称(依赖注入)
    void SetProjectName(const std::string &name);
    // 默认文件名称
    std::string DefaultFileName();
    // 是否被修改过
    bool isModified();
    // 设置修改状态
    void setModifyState(bool state);
    // 从文件中读取自定义报警数据
    int ReadWarnings();
    // 将自定义报警数据写入到文件中
    int SaveWarnings();
    // 获取自定义报警数据
    UserDefineWaringsData_V1 GetWarnings();
    // 获取指定序号的自定义报警数据
    std::string GetWarning(int index);
    // 修改指定序号的自定义报警数据
    int ModifyWarning(int index, const std::string &warning);
    // 检查自定义报警内容是否合格
    bool IsWarningValid(std::string &errMsg, const std::string &warning);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
