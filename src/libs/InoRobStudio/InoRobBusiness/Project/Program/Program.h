#pragma once
#include "IProgram.h"
#include "../ProjectHelper.h"
#include "../Point/RPoint.h"

namespace InoRobBusiness
{

class IProject;

/// <summary>
/// 程序相关处理类
/// </summary>
class INOROBBUSINESS_CLASS Program : public IProgram
{
    Q_OBJECT

public:
    Program(IDataSrvBase *pDataSrv, QObject *parent = nullptr);
    virtual ~Program();

public:
    /// <summary>
    /// 从文件解析程序数据(只适用于pro工程)
    /// </summary>
    /// <param name="posArr">输出，局部点位数据</param>
    /// <param name="proArr">输出，程序文本</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(std::vector<MRobPosItem> &posArr, std::vector<string> &proArr, std::string path);
    /// <summary>
    /// 从文件获取文件头信息(只适用于pro工程)
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(ProjectFileInfo &fileInfo, std::string path);
    /// <summary>
    /// 将程序数据写入到文件(只适用于pro工程)
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="posArr">输入，局部点位数据</param>
    /// <param name="proArr">输入，程序文本</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(std::string path, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;

    virtual void setProjectType(ProjectType type) override;
    virtual bool isModified() override;
    virtual bool isModified(const std::string &name) override;
    virtual void setModifyState(const std::string &name, bool state) override;
    virtual void clearModifyStates() override;
    virtual int ReadProgramFileInfo(ProjectFileInfo &fileInfo, const std::string &name) override;
    virtual int ReadProgram(std::vector<MRobPosItem> &posArr, std::vector<string> &proArr, const std::string &name, bool cacheOrNot = false) override;
    virtual int SaveProgram(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr, bool isNeedEditMode = true) override;
    virtual int saveProgramRT(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr) override;
    virtual int saveLocalFile(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr) override;
    virtual std::string getLocalFilePath(const std::string &name) override;
    virtual std::string NewProgramDefaultName(std::vector<std::string> &names, std::string baseName = "") override;
    virtual std::string FileNameWithoutExtension(const std::string &name) override;
    virtual bool IsProgramFileNameValid(std::string &errMsg, const std::string &name) override;
    virtual int NewFile(const std::string &name, const ProgramType &type) override;
    virtual void SetCopyFile(const std::string &name) override;
    virtual std::string GetCopiedName() override;
    virtual int PasteFile(const std::string &srcName, const std::string &targetName) override;
    virtual int RenameFile(const std::string &oldName, const std::string &newName) override;
    virtual int DelFile(const std::string &name) override;
    virtual int ImportFiles(const std::vector<std::string> &paths) override;
    virtual int ImportFiles(const std::vector<std::string> &paths, std::vector<std::string> &realImportFileNames) override;
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) override;

    virtual void delProgramBuffer(const std::string &fileName) override;
    virtual int insertProgramLines(const std::string &fileName, int lineNo, const std::vector<std::string> &lines) override;
    virtual int changeProgramLines(const std::string &fileName, const std::vector<int> &lineNoArr, const std::vector<std::string> &lines) override;
    virtual int delProgramLines(const std::string &fileName, const std::vector<int> &lineNoArr) override;
    virtual int saveProgramBuffer(const std::string &fileName) override;
    virtual int saveAllProgramBuffer() override;

    virtual void AddViewPoints(const std::string &fileName, const std::vector<MRobPosItem> &points) override;
    virtual void DelViewPoints(const std::string &fileName) override;
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
    virtual void addLabel(const std::string &fileName, const std::string &label) override;
    virtual void replaceLabel(const std::string &fileName, const std::string &oldLabel, const std::string &newLabel) override;
    virtual void delLabel(const std::string &fileName, const std::string &label) override;
    virtual void clearLabels() override;
    virtual int FindPoint(const std::string &fileName, int index) override;
    virtual int FindPoint(const std::vector<MRobPosItem> &points, int index) override;
    virtual void CopyPoints(const std::string &fileName, const std::vector<int> &indexs) override;
    virtual int PastePoints(std::vector<int> &indexs, const std::string &fileName) override;
    virtual int RenamePoint(const std::string &fileName, int srcIndex, int newIndex) override;
    virtual int DelPoint(const std::string &fileName, int index) override;

    virtual int writeModifyPtsData(const ModifyPtsParam &param, const std::vector<unsigned short> &ptNoArr) override;
    virtual int readModifyPtsStatus(ModifyPtsStatus &status) override;

private:
    /**
     * @brief 执行相关操作前的状态检查
     */
    bool checkStatus();
    /**
     * @brief 逐行读取文本
     * @param name 输入，文件路径
     * @return 成功返回0，其他请见错误码
     */
    int readLines(std::vector<std::string> &lines, const std::string &path);
    /**
     * @brief 检查是否重名，如果有重名则自动重命名
     * @param name 输入，原文件名称
     * @return 如果没有重名，则返回原文件名称，如果有重名，则返回自动重命名后的文件名称
     */
    std::string checkSameNameAndRename(const std::string &name);

private:
    IProject *_pProject = nullptr;                 // 工程父对象
    std::string m_Ip;                              // 控制器ip地址
    std::string m_ProjectName;                     // 当前加载的工程名称
    std::string m_CopiedName;                      // 待复制文件名称
    std::map<std::string, bool> _modifyStatesMap;  // 程序文件修改状态集合

    IRPoint *_pLPoint = nullptr;  // 局部点操作，复用全局位置点位方法

    std::map<std::string, std::vector<std::string>> _programLinesMap;  // 程序文本缓存集合
    std::map<std::string, std::set<std::string>> _labelsMap;           // 局部点位标签结合映射表，每个程序文件的局部点位集合需要分开存储

    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
    ProjectType _projectType;                 // 当前工程类型
    std::string _fileExtension;               // 程序文件后缀
};
}  // namespace InoRobBusiness
