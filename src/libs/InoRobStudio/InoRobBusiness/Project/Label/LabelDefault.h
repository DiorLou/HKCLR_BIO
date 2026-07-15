#pragma once
#include "ILabel.h"

namespace InoRobBusiness
{

class IProject;

/// <summary>
/// 全局标签处理类
/// </summary>
class LabelDefault : public ILabel
{
    Q_OBJECT

public:
    LabelDefault(QObject *parent = nullptr);
    virtual ~LabelDefault();

public:
    /// <summary>
    /// 从文件中解析出所有标签数据
    /// </summary>
    /// <param name="labels">输出，标签数据</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(AllIoLabels &labels, const std::string &path);
    /// <summary>
    /// 将所有标签数据写入到文件中
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="labels">输入，标签数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(const std::string &path, const AllIoLabels &labels);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;
    virtual std::string DefaultFileName() override;

    virtual bool isModified() override;
    virtual void setModifyState(bool state) override;
    virtual int ReadLabels() override;
    virtual int SaveLabels() override;
    virtual bool isLabelExisted(const std::string &label) override;
    virtual LabelItem GetLabelItem(const IoLabelItems &items, int index) override;
    virtual LabelItem GetLabelItem(LabelType type, int index) override;
    virtual IoLabelItems GetItems(LabelType type) override;
    virtual void SetItems(const IoLabelItems &items, LabelType type) override;
    virtual int ModifyItemLabel(LabelType type, int index, const std::string &label) override;
    virtual int ModifyItemDescription(LabelType type, int index, const std::string &des) override;
    virtual int GetIoStartIndex(IoType ioType, IoDataType dataType) override;
    virtual int GetIoEndIndex(IoType ioType, IoDataType dataType) override;
    virtual IoLabelItems GetIoItems(LabelType labelType, IoType ioType, IoDataType dataType) override;
    virtual IoLabelItems getAdDaItems(LabelType labelType, AdDaType addaType) override;
    virtual std::vector<LabelItem> GenInitIoItems(LabelType labelType, IoType ioType, IoDataType dataType) override;
    virtual std::vector<LabelItem> GenInitAdDaItems(LabelType labelType, AdDaType addaType) override;
    virtual std::vector<LabelItem> GenInitOtherItems(LabelType labelType) override;

    virtual void removeDescription(LabelType type, const std::string &description) override;

private:
    /**
     * @brief 执行相关操作前的状态检查
     */
    bool checkStatus();
    // 将Json对象解析为数据
    int static ItemsFromObj(cJSON *obj, IoLabelItems &items);
    // 将数据转换为Json对象
    int static ItemsToObj(IoLabelItems items, cJSON *obj);
    // 对应类型的标签序号是否超出范围
    bool isIndexInRange(LabelType type, int index);
    // 排序
    void sortItems(std::vector<LabelItem> &items);
    // 排序模板(升序)
    static bool sortItemsMode(const LabelItem &item1, const LabelItem &item2);
    // 给id和org成员变量赋值
    void perfectItems(LabelType type, std::vector<LabelItem> &items);
    void perfectOriginalName(LabelType type, LabelItem &item);
    // 转换文本编码格式
    void convertGB2312ToUTF8(IoLabelItems &labels);
    void convertUTF8ToGB2312(IoLabelItems &labels);
    // 从集合中移除掉指定的备注
    void removeItemsDescription(IoLabelItems &items, const std::string &description);

private:
    IProject *_pProject = nullptr;  // 工程父对象
    std::string m_Ip;               // 控制器ip地址
    std::string m_ProjectName;      // 当前加载的工程名称
    bool _isModified;               // 是否被修改过

    AllIoLabels m_Labels;  // 所有标签集合

    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
};
}  // namespace InoRobBusiness
