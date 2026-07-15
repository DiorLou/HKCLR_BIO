#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "../ProjectHelper.h"
#include "dllspec.h"

/// <summary>
/// 全局标签处理基类
/// </summary>
class INOROBBUSINESS_CLASS ILabel : public QObject
{
    Q_OBJECT

public:
    virtual ~ILabel()
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
    /// 从文件中读取所有类型的标签数据
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadLabels() = 0;
    /// <summary>
    /// 将所有类型的标签数据保存到文件中
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveLabels() = 0;
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    virtual bool isLabelExisted(const std::string &label) = 0;
    /// <summary>
    /// 获取具体的单个数据
    /// </summary>
    /// <param name="items">输入，单类型的标签集合</param>
    /// <param name="index">输入，下标序号</param>
    /// <returns>成功返回正常的数据，失败则数据中id和index会被置为-1</returns>
    virtual LabelItem GetLabelItem(const IoLabelItems &items, int index) = 0;
    /// <summary>
    /// 获取具体的单个数据
    /// </summary>
    /// <param name="type">输入，指定的标签集合类型</param>
    /// <param name="index">输入，下标序号</param>
    /// /// <returns>成功返回正常的数据，失败则数据中id和index会被置为-1</returns>
    virtual LabelItem GetLabelItem(LabelType type, int index) = 0;
    /// <summary>
    /// 获取指定类型的标签集合
    /// </summary>
    /// <param name="type">输入，标签类型</param>
    virtual IoLabelItems GetItems(LabelType type) = 0;
    /// <summary>
    /// 设置指定类型的标签集合
    /// </summary>
    /// <param name="items">输入，标签集合</param>
    /// <param name="type">输入，标签类型</param>
    virtual void SetItems(const IoLabelItems &items, LabelType type) = 0;
    /// <summary>
    /// 修改对应类型和序号的数据标签
    /// </summary>
    /// <param name="type">输入，标签类型</param>
    /// <param name="index">输入，下标序号</param>
    /// <param name="label">输入，标签字符串</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ModifyItemLabel(LabelType type, int index, const std::string &label) = 0;
    /// <summary>
    /// 修改对应类型和序号的数据描述
    /// </summary>
    /// <param name="type">输入，标签类型</param>
    /// <param name="index">输入，下标序号</param>
    /// <param name="des">输入，描述字符串</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ModifyItemDescription(LabelType type, int index, const std::string &des) = 0;
    /// <summary>
    /// 获取IO标签中对应类型的起始序号
    /// </summary>
    /// <param name="ioType">输入，IO类型</param>
    /// <param name="showType">输入，IO数据类型</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int GetIoStartIndex(IoType ioType, IoDataType dataType) = 0;
    /// <summary>
    /// 获取IO标签中对应类型的终止序号
    /// </summary>
    /// <param name="ioType">输入，IO类型</param>
    /// <param name="showType">输入，IO数据类型</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int GetIoEndIndex(IoType ioType, IoDataType dataType) = 0;
    /// <summary>
    /// 获取指定类型的IO标签集合
    /// </summary>
    /// <param name="LabelType">输入，IO类型</param>
    /// <param name="ioType">输入，IO类型</param>
    /// <param name="showType">输入，IO数据类型</param>
    /// <returns>成功返回对应类型IO标签集合，失败则数组为空</returns>
    virtual IoLabelItems GetIoItems(LabelType labelType, IoType ioType, IoDataType dataType) = 0;
    /**
     * @brief 获取指定类型的AD/DA标签集合
     * @param labelType 输入，标签类型
     * @param addaType 输入，AD/DA类型
     * @return
     */
    virtual IoLabelItems getAdDaItems(LabelType labelType, AdDaType addaType) = 0;
    /// <summary>
    /// 获取一个指定类型且满数量的初始化IO标签集合
    /// </summary>
    /// <param name="labelType">输入，标签类型</param>
    /// <param name="ioType">输入，IO类型</param>
    /// <param name="dataType">输入，IO数据类型</param>
    virtual std::vector<LabelItem> GenInitIoItems(LabelType labelType, IoType ioType, IoDataType dataType) = 0;
    /**
     * @brief 获取一个指定类型且满数量的初始化AD/DA标签集合
     * @param labelType 输入，标签类型
     * @param addaType 输入，AD/DA类型(总线类型)
     * @return
     */
    virtual std::vector<LabelItem> GenInitAdDaItems(LabelType labelType, AdDaType addaType) = 0;
    /// <summary>
    /// 获取一个指定类型且满数量的初始化标签集合
    /// </summary>
    /// <param name="labelType">输入，标签类型</param>
    virtual std::vector<LabelItem> GenInitOtherItems(LabelType labelType) = 0;

    /**
     * @brief 去除掉指定的标签备注（主要给IO配置使用）
     * @param type 输入，标签类型
     * @param description 输入，备注文本
     */
    virtual void removeDescription(LabelType type, const std::string &description) = 0;
};
