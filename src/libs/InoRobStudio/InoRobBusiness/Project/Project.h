#pragma once
#include "ProjectHelper.h"
#include "IProject.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
/// <summary>
/// 工程处理类
/// </summary>
class INOROBBUSINESS_CLASS Project : public IProject
{
    Q_OBJECT

public:
    Project(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~Project();
    void init() override;

public:
    /// <summary>
    /// 从文件解析工程配置信息
    /// </summary>
    /// <param name="info">输出，工程配置信息</param>
    /// <param name="path">输入，文件路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int FromFile(ProjectInfo &info, std::string path);
    /// <summary>
    /// 将工程配置信息写入文件
    /// </summary>
    /// <param name="path">输入，文件路径</param>
    /// <param name="info">输入，工程配置信息</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ToFile(std::string path, const ProjectInfo &info);

public:
    virtual bool checkStatus() override;
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual int getProjectCount(const std::string &ip) override;
    virtual bool isModified() override;
    virtual int ReadProjectList(std::vector<ProjectFolderInfo> &infos, const std::string &ip) override;
    virtual std::string NewProjectDefaultName(const std::vector<ProjectFolderInfo> &infos, std::string baseName = "") override;
    virtual bool IsProjectExisted(const std::string &name, const std::vector<ProjectFolderInfo> &infos) override;
    virtual bool IsProjectNameValid(std::string &errMsg, const std::string &name) override;
    virtual int CreateLocalProject(const std::string &folder, const std::string &name, ProjectType type) override;
    virtual void setCurrentProjectType(ProjectType type) override;
    virtual ProjectType getCurrentProjectType() override;
    virtual int CreateProject(const std::string &name, ProjectType type = ProjectType::PRO) override;
    virtual int DelProject(const std::string &name, bool isreplace = false) override;
    virtual int RenameProject(const std::string &oldName, const std::string &newName) override;
    virtual void CopyProject(const std::string &name) override;
    virtual std::string GetCopiedProjectName() override;
    virtual int PasteProject(const std::string &name) override;
    virtual int ImportProject(const std::string &ip, const std::string &path) override;
    virtual int ExportProject(const std::string &ip, const std::string &name, const std::string &folder) override;
    virtual void SortProjectsByTime(std::vector<ProjectFolderInfo> &infos) override;
    virtual void SortProjectsByWord(std::vector<ProjectFolderInfo> &infos) override;
    virtual void formatProjectTime(std::vector<ProjectFolderInfo> &infos) override;

    virtual int ReadLocalProjcet(const std::string &prjFilePath) override;
    virtual int ReadProject(const std::string &ip, const std::string &name, bool isReadSamePrj = false) override;
    virtual int saveProject() override;
    virtual void setSaveProgramsStatus(SaveProgramsStauts status) override;
    virtual int setActiveProject(const std::string &name) override;
    virtual int getActiveProject(std::string &name) override;
    virtual int SaveProjectConfig(bool isAllowInDebug = false, bool isPrint = true) override;
    virtual bool IsLoadSuccess() override;
    virtual std::string GetName() override;
    virtual ProjectInfo GetInfo() override;
    virtual std::string ProjectFileExtension() override;
    virtual std::string ProgramFileExtension() override;
    virtual std::string PointFileExtension() override;
    virtual std::vector<std::string> GetProgramFileList() override;
    virtual std::vector<std::string> GetRPointFileList() override;
    virtual std::vector<std::string> GetJPointFileList() override;
    virtual std::vector<std::string> GetLabelTypeList() override;
    virtual std::vector<std::string> GetDefineWarningFileList() override;
    virtual std::vector<MultiTaskInfo> GetTaskManageConfig() override;
    virtual bool isLabelExisted(const std::string &label) override;
    virtual bool IsTaskExisted(int id) override;
    virtual bool IsTaskExisted(const std::string &programFileName) override;
    virtual bool IsProgramFileExisted(const std::string &fileName) override;
    virtual bool IsRPointFileExisted(const std::string &fileName) override;
    virtual bool IsTaskUpperLimit() override;
    virtual bool IsProgramFileUpperLimit() override;
    virtual bool IsRPointFileUpperLimit() override;

    virtual bool checkFileNameTheSameToLabel(std::string &errMsg, const std::string &fileName) override;
    virtual bool checkLabelTheSameToFileName(std::string &errMsg, const std::string &label) override;

    virtual bool isTaskModified() override;
    virtual void setTaskModifyState(bool state) override;
    virtual bool isStaticTaskModified() override;
    virtual bool isStaticProgramModified(int taskId) override;
    virtual void setTaskStateIsSave(const std::string &fileName, bool isSave) override;
    virtual void setTaskStateIsParse(const std::string &fileName, bool isParse) override;
    virtual void setTaskStateIsActive(const std::string &fileName, bool isActive) override;
    virtual void setTaskStateAllSaved(bool isSave) override;
    virtual void setTaskStateAllParsed(bool isParse) override;
    virtual void setStaticProgramState(const std::string &name, bool isSave) override;
    virtual void setStaticProgramState(const std::string &name, bool isSave, bool isParse) override;

    virtual int AddTask(const MultiTaskInfo &task) override;
    virtual int ModifyTaskInfo(int id, int type, const std::string &fileName) override;
    virtual int ModifyTaskState(int id, bool isActive, bool isAllowInDebug = false) override;
    virtual int DelTask(const MultiTaskInfo &task) override;
    virtual int DelTask(int id) override;
    virtual int DelTask(const std::string &programFileName) override;
    virtual int ClearTask() override;

    virtual bool isInfoModified() override;
    virtual void setInfoModifyState(bool state) override;
    virtual void AddProgramConfig(const std::string &fileName) override;
    virtual void replaceProgramConfig(const std::string &oldFileName, const std::string &newFileName) override;
    virtual void DelProgramConfig(const std::string &fileName) override;
    virtual void AddRPointConfig(const std::string &fileName) override;
    virtual void DelRPointConfig(const std::string &fileName) override;

    virtual void getSyncFlags(signed char *flags, unsigned int length) override;
    virtual int sendSyncFlag(int type, bool isFileOperate = false) override;
    virtual int parseLocalProject() override;
    virtual void updateLablesToTransfor() override;
    virtual bool isKeyWord(const std::string &str) override;

    virtual std::string getPointLabel(PointType pointType, const std::string &fileName, int pointNo) override;
    virtual int modifyControllerRPoint(int pointNo, PointType pointType, int taskId,
                                       const std::string &programFileName, RobPos &pos, ModifyPointStatus &status) override;
    virtual int modifyControllerJPoint(int pointNo, JPos &pos, ModifyPointStatus &status) override;
    virtual bool ModifyPointRT(PointType pointType, int16u pointNo, RobPos robPos,
                               const std::string &programFileName, ModifyPointStatus &status);
    virtual std::string getCurrentRPFileName() override;
    virtual int readCurrentRPFileName(std::string &name) override;
    virtual int getProgramFilesMaxCount(int16u &programFilesCount) override;
    virtual int setProgramFilesMaxCount(int16u programFilesCount) override;

    virtual IProgram *GetProgram() override;
    virtual IRPoint *GetRPoint() override;
    virtual IJPoint *GetJPoint() override;
    virtual ILabel *GetLabel() override;
    virtual IDefineWarning *GetDefineWarning() override;
    virtual IStationConfig *GetStationConfig() override;

    virtual void setProjectReadStatus(int status) override;
    virtual void setProjectParseStatus(int status) override;
    virtual unordered_map<int, pair<int, int>> AnaPointToolAndWobj(string fileName, int pointType) override;

    virtual void readAndParseProject(bool isReadSameProjcet = false) override;

    virtual bool getProjectIsCanFTPFlag(int &getFlag) override;
    virtual bool setProjectFTPProgress(int setFlag) override;
    virtual void tellControllerStartPrjFTP() override;

    virtual void setPageUpdateStatus(UpdateEditPageStatus status) override;
    virtual int updateProgramEditPage(std::string projectName, std::string programName) override;

    virtual int requireControllerReloadBreakPointsFile() override;
    virtual int setControllerEnableAllBreakPointsState (int target) override;
    virtual int getControllerEnableAllBreakPointsState (int &target) override;

    virtual int setControllerStartLine(const std::vector<int> &exeFlow, const string &uuid) override;
    virtual int getControllerStartLine(string &uuid) override;
private:
    /// <summary>
    /// 查询控制器操作工程的状态
    /// </summary>
    /// <param name="type">输入，操作类型</param>
    /// <param name="milliseconds">输入，超时时间</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int CheckOperateProjectState(int16u type, int64u milliseconds = 8000);
    /// <summary>
    /// 设置工程加载状态
    /// </summary>
    /// <param name="state">工程加载状态，成功true，失败false</param>
    void SetLoadState(bool state);
    /// <summary>
    /// 设置当前加载的工程名称
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    void SetName(const std::string &name);
    /// <summary>
    /// 设置当前连接的控制器的ip
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    void setIp(const std::string &ip);
    /// <summary>
    /// 设置当前加载工程的配置信息
    /// </summary>
    /// <param name="info">工程配置</param>
    void SetInfo(const ProjectInfo &info);
    /// <summary>
    /// 响应连接状态改变事件
    /// </summary>
    /// <param name="status">连接状态</param>
    void onConnectionStatusChanged(ControllerConnectionStatus status);
    /**
     * @brief 当前加载位置点位文件变更事件（LoadPoints指令等执行后）
     * @param cmd 指令（暂时无效）
     */
    void onLoadRPFileChanged(int cmd);
    /**
     * @brief 解析出工程中的所有标签名
     * @return 成功返回0，其他请见错误码
     */
    int analysisAllLabelsInProject();
    /**
     * @brief 向译码库中添加全局变量标签
     */
    void addAllGlobalVarLabels();
    void addGlobalVarLabels(const IoLabelItems &labels);
    /**
     * @brief 向译码库中添加全局位置点位标签
     */
    void addRPLabels();
    /**
     * @brief 向译码库中添加全局关节点位标签
     */
    void addJPLabels();
    /**
     * @brief 根据点位序号，生成译码库更新标签要用的点位名称
     * @param pointNo 输入，点位序号
     * @return 点位名称
     */
    std::string genRPNameByNo(int pointNo);
    std::string genJPNameByNo(int pointNo);
    /**
     * @brief  输入的文件名后缀检查
     * @param  文件名
     * @return 带后缀的文件名
     */
    std::string checkFileName(std::string fileName);
    /**
     * @brief 按工程日期进行排序（升序）
     */
    static bool ascendingProjectByTime(const ProjectFolderInfo &info1, const ProjectFolderInfo &info2);
    /**
     * @brief 按工程日期进行排序（降序）
     */
    static bool dascendingProjectByTime(const ProjectFolderInfo &info1, const ProjectFolderInfo &info2);
    /**
     * @brief 将工程日期拆解成数字字符串，年月日时分
     * @param year 输出，年份
     * @param month 输出，月份
     * @param day 输出，日
     * @param hour 输出，小时
     * @param minute 输出，分钟
     * @param timeStr 输入，日期字符串，本年内的日期格式为Jan 6 09:33，往年的日期格式为Jan 6 2023
     */
    static void splitProjectTimeStr(std::string &year, std::string &month, std::string &day, std::string &hour, std::string &minute, const std::string &timeStr);
    /**
     * @brief 将日期字符串解析为整型数字
     * @param timeStr 日期字符串，本年内的日期格式为Jan 6 09:33，往年的日期格式为Jan 6 2023
     */
    static long long analysisProjectTimeStr(const std::string &timeStr);
    /**
     * @brief 将从控制器通过ftp读出的工程日期字符串，格式化为纯数字格式，如Jan 6 09:33 -> 2024-01-06 09:33
     * @param timeStr 日期字符串，本年内的日期格式为Jan 6 09:33，往年的日期格式为Jan 6 2023
     * @return 格式化后的日期字符串
     */
    std::string formatProjcetTimeStr(const std::string &timeStr);
    /**
     * @brief 按工程名称进行排序（升序）
     */
    static bool ascendingProjectByWord(const ProjectFolderInfo &info1, const ProjectFolderInfo &info2);
    /**
     * @brief 按工程名称进行排序（降序）
     */
    static bool dascendingProjectByWord(const ProjectFolderInfo &info1, const ProjectFolderInfo &info2);

private:
    bool m_IsLoadSuccess;                               // 工程是否加载成功
    std::string m_PrjName;                              // 工程名称
    ProjectInfo m_PrjInfo;                              // 工程配置信息
    std::string _ip;                                    // 当前连接的控制器的ip
    std::string m_CopyPrjName;                          // 待复制粘贴的工程名称
    const std::string m_PrjDefaultName = "NewProject";  // 新建工程默认名称
    bool _isInfoModified;                               // 工程配置信息是否被修改过
    bool _isTaskModified;                               // 任务配置是否被修改过
    SaveProgramsStauts _saveProgramsStatus;             // 模型层触发UI层保存程序文件状态
    UpdateEditPageStatus _updatePageStatus;             // 更新程序编辑页面的状态

    struct _staticTaskState
    {                          // 管理静态任务状态
        bool Saved = false;    // 是否保存，默认为保存
        bool Parsed = false;   // 是否编译，默认为编译
        bool Actived = false;  // 是否激活，默认是激活状态

        // 构造函数初始化所有成员变量
        _staticTaskState()
            : Saved(false), Parsed(false), Actived(false)
        {
        }
        _staticTaskState(const bool &isSave, const bool &isParse, const bool &isActive)
            : Saved(isSave), Parsed(isParse), Actived(isActive)
        {
        }
    };
    std::map<std::string, _staticTaskState> _staticTaskStatesMap;  // 程序文件状态集合

    IDataSrvBase *_pDataSrv = nullptr;           // 控制器通信
    IConnection *_pConnection = nullptr;         // 控制器连接
    IMonitor *_pMonitor = nullptr;               // 监控
    ITransfor *_pTransfor = nullptr;             // 译码
    IRobotControllerEvents *_pEvents = nullptr;  // 事件机制
    ITask *_pTask = nullptr;                     // 任务

    IProgram *m_pProgram = nullptr;             // 程序处理类指针
    IRPoint *m_pRPoint = nullptr;               // 位置点处理类指针
    IJPoint *m_pJPoint = nullptr;               // 关节点处理类指针
    ILabel *m_pLabel = nullptr;                 // 标签文件处理类对象
    IDefineWarning *_pDefineWarning = nullptr;  // 用户自定义报警处理类指针
    IStationConfig *_pStationConfig = nullptr;  // 工位配置处理类指针

    std::string _currentRPFileName;

    ProjectType _projectType;                 // 当前工程类型
    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
    std::string _fileExtension;               // 文件后缀
    int _readStatus = 0;                      // 0-空闲 1-正在读取
    int _parseStatus = 0;                     // 0-空闲 1-正在解析
};
}  // namespace InoRobBusiness
