#pragma once
#include <set>
#include "IJPoint.h"

namespace InoRobBusiness
{

class IProject;

/// <summary>
/// 关节点位相关处理类
/// </summary>
class JPoint : public IJPoint
{
    Q_OBJECT

public:
    JPoint(QObject *parent = nullptr);
    virtual ~JPoint();

public:
    /// <summary>
    /// 从文件解析点位数据
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="posArr">输出，点位数据</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(ProjectFileInfo &fileInfo, std::vector<MJPosItem> &posArr, std::string path);
    static int FromFile(ProjectFileInfo &fileInfo, std::string path);
    static int FromFile(std::vector<MJPosItem> &posArr, std::string path);
    /// <summary>
    /// 从文本解析点位数据
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="posArr">输出，点位数据</param>
    /// <param name="content">输入，整个文本</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromStr(ProjectFileInfo &fileInfo, const std::string &content);
    static int FromStr(std::vector<MJPosItem> &posArr, std::string content, const std::string &fileName);
    /// <summary>
    /// 将点位数据写入到文件
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="posArr">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(std::string path, const std::vector<MJPosItem> &posArr);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;
    virtual std::string DefaultFileName() override;
    virtual bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName) override;
    virtual int ImportFiles(const std::vector<std::string> &paths) override;
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) override;

    virtual bool isModified() override;
    virtual void setModifyState(bool state) override;
    virtual int readPoints(const std::string &fileName, bool isAlwaysFromFile = false) override;
    virtual int ReadPoints(std::vector<MJPosItem> &points, const std::string &fileName, bool isAlwaysFromFile = false) override;
    virtual int SavePoints(const std::string &fileName, const std::vector<MJPosItem> &points, bool isNeedEditMode = true) override;
    virtual int SaveViewPoints(const std::string &fileName, bool isNeedEditMode = true) override;
    virtual int SaveAllViewPoints() override;
    virtual void AddViewPoints(const std::string &fileName, const std::vector<MJPosItem> &points) override;
    virtual void DelViewPoints(const std::string &fileName) override;
    virtual void clearViewPoints() override;
    virtual bool isViewPointsExisted(const std::string &fileName) override;
    virtual int getAvailablePointNo(const std::string &fileName, bool isTip = true) override;
    virtual int AddPoint(int &index, const std::string &fileName, MJPosItem &point) override;
    virtual int addPoint(const std::string &fileName, const MJPosItem &point) override;
    virtual int ChangePoint(const std::string &fileName, const MJPosItem &point, bool isNeedEditMode = true) override;
    virtual std::vector<MJPosItem> GetPoints(const std::string &fileName) override;
    virtual std::vector<MJPosItem> GetPoints(const std::string &fileName, const std::vector<int> &indexs) override;
    virtual MJPosItem GetPoint(const std::string &fileName, int index) override;
    virtual MJPosItem GetPoint(const std::vector<MJPosItem> &points, int index) override;
    virtual bool isLabelExisted(const std::string &label) override;
    virtual std::set<std::string> getLabels() override;
    virtual void addLabel(const std::string &label) override;
    virtual void replaceLabel(const std::string &oldLabel, const std::string &newLabel) override;
    virtual void delLabel(const std::string &label) override;
    virtual void clearLabels() override;
    virtual PtLabelAndDes getLabelAndDescription(const std::string &fileName, int index) override;
    virtual std::vector<PtLabelAndDes> getLabelsAndDescriptions(const std::string &fileName, int startNo, int endNo) override;
    virtual std::vector<PtLabelAndDes> getAllLabelsAndDescriptions(const std::string &fileName) override;
    virtual int FindPoint(const std::string &fileName, int index) override;
    virtual int FindPoint(const std::vector<MJPosItem> &points, int index) override;
    virtual void CopyPoints(const std::string &fileName, const std::vector<int> &indexs) override;
    virtual int PastePoints(std::vector<int> &indexs, const std::string &fileName) override;
    virtual int RenamePoint(const std::string &fileName, int srcIndex, int newIndex) override;
    virtual int DelPoint(const std::string &fileName, int index) override;
    virtual int DelPoint(std::vector<MJPosItem> &points, int index) override;

private:
    /**
     * @brief 执行相关操作前的状态检查
     */
    bool checkStatus();
    /// <summary>
    /// 按点位序号升序排序
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    void SortPoints(std::vector<MJPosItem> &points);
    /// <summary>
    /// 按点位序号升序排序比较模板
    /// </summary>
    static bool SortPointsMode(const MJPosItem &point1, const MJPosItem &point2);

private:
    IProject *_pProject = nullptr;  // 工程父对象
    std::string m_Ip;               // 控制器ip地址
    std::string m_ProjectName;      // 当前加载的工程名称
    bool _isModified;               // 是否被修改过

    std::map<std::string, std::vector<MJPosItem>> m_ViewPointsMap;  // 界面的点位文件数据集合
    std::string m_CopiedFileName;                                   // 待拷贝的点位集合所属的文件
    std::vector<int> m_CopiedPointIndexs;                           // 待拷贝的点位序号集合
    std::set<std::string> _labels;                                  // 点位标签集合（元素唯一性，红黑树，支持快速查找）

    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
};
}  // namespace InoRobBusiness
