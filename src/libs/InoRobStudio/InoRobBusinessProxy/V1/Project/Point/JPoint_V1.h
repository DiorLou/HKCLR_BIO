#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../ProjectHelper_V1.h"
#include "../../GlobalDataTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS JPoint_V1
{
#pragma region 构造与析构

private:
    IJPoint *_jPoint = nullptr;

public:
    JPoint_V1(IJPoint *jPoint);
    ~JPoint_V1();

#pragma endregion

#pragma region 业务逻辑

    // 设置工程的文件操作模式
    void setProjectOperateMode(ProjectFileOperateMode_V1 mode);
    // 设置控制器ip地址(依赖注入)
    void SetControllerIp(const std::string &ip);
    // 设置当前加载的工程名称(依赖注入)
    void SetProjectName(const std::string &name);
    // 默认点位文件名称
    std::string DefaultFileName();
    // 判断点位文件名称是否合法
    bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName);
    // 导入程序文件
    int ImportFiles(const std::vector<std::string> &paths);
    // 导出程序文件
    int ExportFiles(const std::vector<std::string> &names, const std::string &folder);
    // 是否被修改过
    bool isModified();
    // 设置修改状态
    void setModifyState(bool state);
    // 读取点位文件数据
    int readPoints(const std::string &fileName);
    int ReadPoints(std::vector<MJPosItem_V1> &points, const std::string &fileName);
    // 保存点位数据到点位文件中
    int SavePoints(const std::string &fileName, const std::vector<MJPosItem_V1> &points);
    // 保存指定名称的页面缓存的点位数据
    int SaveViewPoints(const std::string &fileName);
    // 保存所有页面缓存的点位数据
    int SaveAllViewPoints();
    // 添加页面点位数据到缓存中
    void AddViewPoints(const std::string &fileName, const std::vector<MJPosItem_V1> &points);
    // 从点位数据缓存中删除对应的点位数据
    void DelViewPoints(const std::string &fileName);
    // 点位缓存中是否存在对应点位文件名称的数据
    bool isViewPointsExisted(const std::string &fileName);
    // 获取对应文件中可用点位序号
    int getAvailablePointNo(const std::string &fileName, bool isTip = true);
    // 新增点
    int AddPoint(int &index, const std::string &fileName, MJPosItem_V1 &point);
    // 新增点（此接口需要使用前先确定点位数据，如序号等）
    int addPoint(const std::string &fileName, const MJPosItem_V1 &point);
    // 修改点位数据
    int ChangePoint(const std::string &fileName, const MJPosItem_V1 &point);
    // 获取对应点位文件的点位数据
    std::vector<MJPosItem_V1> GetPoints(const std::string &fileName);
    // 获取对应点位文件，指定序号的点位数据
    std::vector<MJPosItem_V1> GetPoints(const std::string &fileName, const std::vector<int> &indexs);
    // 获取指定序号的点位数据
    MJPosItem_V1 GetPoint(const std::string &fileName, int index);
    // 获取指定序号的点位数据
    MJPosItem_V1 GetPoint(const std::vector<MJPosItem_V1> &points, int index);
    // 查询标签名是否已经存在
    bool isLabelExisted(const std::string &label);
    // 获取标签名集合
    std::set<std::string> getLabels();
    // 添加标签名至缓存中
    void addLabel(const std::string &label);
    // 替换缓存中已经存在的标签名
    void replaceLabel(const std::string &oldLabel, const std::string &newLabel);
    // 从缓存中删除指定的标签名
    void delLabel(const std::string &label);
    // 清空标签缓存
    void clearLabels();
    // 获取指定序号的点位的标签和备注
    PtLabelAndDes_V1 getLabelAndDescription(const std::string &fileName, int index);
    // 获取指定序号区间的点位的标签和备注集合
    std::vector<PtLabelAndDes_V1> getLabelsAndDescriptions(const std::string &fileName, int startNo, int endNo);
    // 获取指定点位文件的所有点位的标签和备注集合
    std::vector<PtLabelAndDes_V1> getAllLabelsAndDescriptions(const std::string &fileName);
    // 查找指定序号的点位
    int FindPoint(const std::string &fileName, int index);
    // 查找指定序号的点位
    int FindPoint(const std::vector<MJPosItem_V1> &points, int index);
    // 复制点位
    void CopyPoints(const std::string &fileName, const std::vector<int> &indexs);
    // 粘贴点位
    int PastePoints(std::vector<int> &indexs, const std::string &fileName);
    // 重新设置点位序号
    int RenamePoint(const std::string &fileName, int srcIndex, int newIndex);
    // 删除点位
    int DelPoint(const std::string &fileName, int index);
    // 删除点位
    int DelPoint(std::vector<MJPosItem_V1> &points, int index);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
