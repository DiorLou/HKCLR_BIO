#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../ProjectHelper_V1.h"
using namespace InoRobBusiness;

/*
    全局标签处理基类
    2024/08/14
*/
namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Label_V1
{
#pragma region 构造与析构

private:
    ILabel *_label = nullptr;

public:
    Label_V1(ILabel *label);
    ~Label_V1();

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
    // 从文件中读取所有类型的标签数据
    int ReadLabels();
    // 将所有类型的标签数据保存到文件中
    int SaveLabels();
    // 查询标签名是否已经存在
    bool isLabelExisted(const std::string &label);
    // 获取具体的单个数据
    LabelItem_V1 GetLabelItem(const IoLabelItems_V1 &items, int index);
    // 获取具体的单个数据
    LabelItem_V1 GetLabelItem(LabelType_V1 type, int index);
    // 获取指定类型的标签集合
    IoLabelItems_V1 GetItems(LabelType_V1 type);
    // 设置指定类型的标签集合
    void SetItems(const IoLabelItems_V1 &items, LabelType_V1 type);
    // 修改对应类型和序号的数据标签
    int ModifyItemLabel(LabelType_V1 type, int index, const std::string &label);
    // 修改对应类型和序号的数据描述
    int ModifyItemDescription(LabelType_V1 type, int index, const std::string &des);
    // 获取IO标签中对应类型的起始序号
    int GetIoStartIndex(IoType_V1 ioType, IoDataType_V1 dataType);
    // 获取IO标签中对应类型的终止序号
    int GetIoEndIndex(IoType_V1 ioType, IoDataType_V1 dataType);
    // 获取指定类型的IO标签集合
    IoLabelItems_V1 GetIoItems(LabelType_V1 labelType, IoType_V1 ioType, IoDataType_V1 dataType);
    // 获取一个指定类型且满数量的初始化IO标签集合
    std::vector<LabelItem_V1> GenInitIoItems(LabelType_V1 labelType, IoType_V1 ioType, IoDataType_V1 dataType);
    // 获取一个指定类型且满数量的初始化标签集合
    std::vector<LabelItem_V1> GenInitOtherItems(LabelType_V1 labelType);
    // 去除掉指定的标签备注（主要给IO配置使用）
    void removeDescription(LabelType_V1 type, const std::string &description);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
