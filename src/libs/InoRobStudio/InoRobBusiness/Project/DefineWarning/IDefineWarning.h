#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "../ProjectHelper.h"
#include "dllspec.h"

/// <summary>
/// 用户自定义报警处理基类
/// </summary>
class INOROBBUSINESS_CLASS IDefineWarning : public QObject
{
    Q_OBJECT

public:
    virtual ~IDefineWarning()
    {
    }

    /**
     * @brief 设置工程的文件操作模式
    */
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) = 0;
    /// <summary>
    /// 设置控制器ip地址(依赖注入)
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    virtual void SetControllerIp(const std::string &ip) = 0;
    /// <summary>
    /// 设置当前加载的工程名称(依赖注入)
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    virtual void SetProjectName(const std::string &name) = 0;

    /// <summary>
    /// 默认文件名称
    /// </summary>
    virtual std::string DefaultFileName() = 0;

    /**
     * @brief  是否被修改过
    */
    virtual bool isModified() = 0;
    /**
     * @brief 设置修改状态
     * @param state 输入，修改状态
    */
    virtual void setModifyState(bool state) = 0;
    /// <summary>
    /// 从文件中读取自定义报警数据
    /// </summary>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadWarnings() = 0;
    /// <summary>
    /// 将自定义报警数据写入到文件中
    /// </summary>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveWarnings() = 0;
    /// <summary>
    /// 获取自定义报警数据
    /// </summary>
    virtual UserDefineWaringsData GetWarnings() = 0;
    /// <summary>
    /// 获取指定序号的自定义报警数据
    /// </summary>
    virtual std::string GetWarning(int index) = 0;
    /// <summary>
    /// 修改指定序号的自定义报警数据
    /// </summary>
    /// <param name="index">输入，序号</param>
    /// <param name="warning">输入，报警内容</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ModifyWarning(int index, const std::string &warning) = 0;
    /// <summary>
    /// 检查自定义报警内容是否合格
    /// </summary>
    /// <param name="errMsg">输出，错误描述</param>
    /// <param name="warning">输入，报警内容</param>
    /// <returns>合格true，不合格false</returns>
    virtual bool IsWarningValid(std::string &errMsg, const std::string &warning) = 0;
};
