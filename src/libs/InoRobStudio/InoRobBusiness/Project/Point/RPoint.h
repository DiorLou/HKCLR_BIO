#pragma once
#include <set>
#include "IRPoint.h"

namespace InoRobBusiness
{

class IProject;

/// <summary>
/// 位置点位相关处理类
/// </summary>
class RPoint : public IRPoint
{
    Q_OBJECT

public:
    RPoint(IDataSrvBase *pDataSrv, QObject *parent = nullptr);
    virtual ~RPoint();

public:
    /// <summary>
    /// 从文件解析点位数据
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="posArr">输出，点位数据</param>
    /// <param name="path">输入，文件路径</param>
    /// <param name="isExcludeLabel">输入，是否剔除标签(暂时，因为译码库不支持每个全局点位文件都有独立的标签)</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(ProjectFileInfo &fileInfo, std::vector<MRobPosItem> &posArr, std::string path, bool isExcludeLabel = false);
    static int FromFile(ProjectFileInfo &fileInfo, const std::string &path);
    static int FromFile(std::vector<MRobPosItem> &posArr, const std::string &path, bool isExcludeLabel = false);
    /// <summary>
    /// 从文本解析点位数据
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="posArr">输出，点位数据</param>
    /// <param name="content">输入，整个文本</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="isExcludeLabel">输入，是否剔除标签(暂时，因为译码库不支持每个全局点位文件都有独立的标签)</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromStr(ProjectFileInfo &fileInfo, const std::string &content);
    static int FromStr(std::vector<MRobPosItem> &posArr, std::string &content, const std::string &fileName, bool isExcludeLabel = false);
    /// <summary>
    /// 将点位数据写入到文件
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="posArr">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(const std::string &path, const std::vector<MRobPosItem> &posArr);
    static int ToFile(const std::string &path, const ProjectFileInfo &fileInfo, const std::vector<MRobPosItem> &posArr);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;
    virtual std::string DefaultFileName() override;
    virtual std::string NewDefaultFileName(std::vector<std::string> &names, std::string baseName = "") override;
    virtual bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName) override;
    virtual int NewFile(const std::string &name) override;
    virtual void SetCopyFile(const std::string &name) override;
    virtual std::string GetCopiedName() override;
    virtual int PasteFile(const std::string &srcName, const std::string &targetName) override;
    virtual int RenameFile(const std::string &oldName, const std::string &newName) override;
    virtual int DelFile(const std::string &name) override;
    virtual int ImportFiles(const std::vector<std::string> &paths) override;
    virtual int ImportFiles(const std::vector<std::string> &paths, std::vector<std::string> &realImportFileNames) override;
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) override;

    virtual bool isModified() override;
    virtual bool isModified(const std::string &name) override;
    virtual void setModifyState(const std::string &name, bool state) override;
    virtual void clearModifyStates() override;
    virtual int readPoints(const std::string &fileName) override;
    virtual int ReadPoints(std::vector<MRobPosItem> &points, const std::string &fileName, bool isAlwaysFromFile = false) override;
    virtual int SavePoints(const std::string &fileName, std::vector<MRobPosItem> &points, bool isNeedEditMode = true) override;
    virtual int SaveViewPoints(const std::string &fileName, bool isNeedEditMode = true) override;
    virtual int SavePointsRT(const std::string &fileName, std::vector<MRobPosItem> &points) override;
    virtual int saveViewPointsRT(const std::string &fileName) override;
    virtual int SaveAllViewPoints() override;
#pragma region 复用在局部点位LP
    virtual void AddViewPoints(const std::string &fileName, const std::vector<MRobPosItem> &points) override;
    virtual void DelViewPoints(const std::string &fileName) override;
    virtual void clearViewPoints() override;
    virtual bool isViewPointsExisted(const std::string &fileName) override;
    virtual int getAvailablePointNo(const std::string &fileName, bool isTip = true) override;
    virtual int AddPoint(int &index, const std::string &fileName, MRobPosItem &point) override;
    virtual int addPoint(const std::string &fileName, const MRobPosItem &point) override;
    virtual int ChangePoint(const std::string &fileName, const MRobPosItem &point, bool isNeedEditMode = true) override;
    virtual int changePointRT(const std::string &fileName, const MRobPosItem &point) override;
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName) override;
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName, const std::vector<int> &indexs) override;
    virtual MRobPosItem GetPoint(const std::string &fileName, int index) override;
    virtual MRobPosItem GetPoint(const std::vector<MRobPosItem> &points, int index) override;
    virtual bool isLabelExisted(const std::string &label) override;
    virtual std::vector<std::string> getLabels() override;
    virtual void initLabels() override;
    virtual void replaceLabel(int pointNo, const std::string &newLabel) override;
    virtual std::string getLabel(int pointNo) override;
    virtual PtLabelAndDes getLabelAndDescription(const std::string &fileName, int index) override;
    virtual std::vector<PtLabelAndDes> getLabelsAndDescriptions(const std::string &fileName, int startNo, int endNo) override;
    virtual std::vector<PtLabelAndDes> getAllLabelsAndDescriptions(const std::string &fileName) override;
    virtual int FindPoint(const std::string &fileName, int pointNo) override;
    virtual int FindPoint(const std::vector<MRobPosItem> &points, int pointNo) override;
    virtual void CopyPoints(const std::string &fileName, const std::vector<int> &indexs) override;
    virtual int PastePoints(std::vector<int> &indexs, const std::string &fileName) override;
    virtual int RenamePoint(const std::string &fileName, int srcIndex, int newIndex) override;
    virtual int DelPoint(const std::string &fileName, int index) override;

    virtual int writeModifyPtsData(const ModifyPtsParam &param, const std::vector<unsigned short> &ptNoArr) override;
    virtual int readModifyPtsStatus(ModifyPtsStatus &status) override;
    virtual int modifyPts(ModifyPtsStatus &status, const std::vector<unsigned short> &ptNoData, const ModifyPtsParam &param) override;
    virtual void clearPointOffsets() override;
    virtual std::vector<PointOffset> getPointOffsets() override;
#pragma endregion

private:
    /**
     * @brief 执行相关操作前的状态检查
     */
    bool checkStatus();
    /**
     * @brief 检查缓存中是否存在对应文件名称的数据
     * @param fileName 输入，文件名称
     */
    bool isPointFileExisted(const std::string &fileName);
    /**
     * @brief 检查是否重名，如果有重名则自动重命名
     * @param name 输入，原文件名称
     * @return 如果没有重名，则返回原文件名称，如果有重名，则返回自动重命名后的文件名称
     */
    std::string checkSameNameAndRename(const std::string &name);
    /**
     * @brief 清除文件数据中的标签信息
     * @param path 输入，点位文件本地路径
     * @return 成功返回0，其他请见错误码
     */
    int clearFileLabels(const std::string &path);
    /// <summary>
    /// 按点位序号升序排序
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    void SortPoints(std::vector<MRobPosItem> &points);
    /// <summary>
    /// 按点位序号升序排序比较模板
    /// </summary>
    static bool SortPointsMode(const MRobPosItem &point1, const MRobPosItem &point2);

private:
    IDataSrvBase *_pDataSrv = nullptr;             // 通讯对象
    IProject *_pProject = nullptr;                 // 工程父对象
    std::string m_Ip;                              // 控制器ip地址
    std::string m_ProjectName;                     // 当前加载的工程名称
    std::map<std::string, bool> _modifyStatesMap;  // 点文件修改状态集合

    std::map<std::string, std::vector<MRobPosItem>> m_ViewPointsMap;  // 界面的点位文件数据集合
    std::string _copiedFileName;                                      // 待拷贝的点位文件名称
    std::string m_CopiedPointFileName;                                // 待拷贝的点位集合所属的文件
    std::vector<int> m_CopiedPointIndexs;                             // 待拷贝的点位序号集合
    std::vector<std::string> _labels;                                 // 点位标签集合
    std::vector<PointOffset> _pointOffsets;                           // 批量改点 - 当前操作下所有点位的总偏移量，关闭批量改点页面清空

    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
};
}  // namespace InoRobBusiness
