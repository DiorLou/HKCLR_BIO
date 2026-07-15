#pragma once
#include "IDefineWarning.h"


namespace InoRobBusiness
{

class IProject;

/// <summary>
/// 用户自定义报警处理类
/// </summary>
class DefineWarningDefault : public IDefineWarning
{
    Q_OBJECT

public:
    DefineWarningDefault(QObject *parent = nullptr);
    virtual ~DefineWarningDefault();

public:
    /// <summary>
    /// 从文件中解析出所有标签数据
    /// </summary>
    /// <param name="labels">输出，标签数据</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(UserDefineWaringsData &data, const std::string &path);
    /// <summary>
    /// 将所有标签数据写入到文件中
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="labels">输入，标签数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(const std::string &path, const UserDefineWaringsData &data);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;
    virtual std::string DefaultFileName() override;

    virtual bool isModified() override;
    virtual void setModifyState(bool state) override;
    virtual int ReadWarnings() override;
    virtual int SaveWarnings() override;
    virtual UserDefineWaringsData GetWarnings() override;
    virtual std::string GetWarning(int index) override;
    virtual int ModifyWarning(int index, const std::string &warning) override;
    virtual bool IsWarningValid(std::string &errMsg, const std::string &warning) override;

private:
    /**
     * @brief 执行相关操作前的状态检查
    */
    bool checkStatus();

private:
    IProject *_pProject = nullptr; // 工程父对象
    std::string _ip;           // 控制器ip地址
    std::string _projectName;  // 当前加载的工程名称
    bool _isModified;          // 是否被修改过

    UserDefineWaringsData m_Warnings;  // 用户自定义报警数据

    ProjectFileOperateMode _fileOperateMode;    // 工程文件操作模式

    const int MAX_LENGTH_CHINESE_STR = 20;       // 含有中文时，允许的最大字符串长度
    const int MAX_LENGTH_NOTCHINESE_STR = 40;    // 不含中文时，允许的最大字符串长度
};
}  // namespace InoRobBusiness
