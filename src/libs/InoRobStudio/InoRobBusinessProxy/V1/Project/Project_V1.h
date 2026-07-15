#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "DefineWarning/DefineWarning_V1.h"
#include "Label/Label_V1.h"
#include "Point/JPoint_V1.h"
#include "Point/RPoint_V1.h"
#include "Program/Program_V1.h"
#include "ProjectHelper_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
/// <summary>
/// 工程处理类
/// </summary>

#pragma region 枚举

// 处理状态
enum class ProcessingStatus_V1
{
    PROCESSING_V1 = 0,  // 处理中
    SUCCEED_V1,         // 成功
    FAILED_V1,          // 失败
};

// 点位类型
enum class PointType_V1
{
    LP_V1 = 0,  // 局部点位
    RP_V1,      // 全局位置点位
    JP_V1,      // 全局关节点位
    UNKNOW_V1,  // 未知
};

// 调试中修改点状态
enum class ModifyPointStatus_V1
{
    ERR_V1 = 0,  // 出错
    ING_V1,      // 修改中
    OK_V1,       // 成功
};

// UI层保存程序文件的状态
enum class SaveProgramsStauts_V1
{
    SAVING_V1 = 0,  // 正在保存
    SUCCEED_V1,     // 保存成功
    FAILED_V1,      // 保存失败
};

// 程序数量类型
enum class ProgramNumType_V1
{
    DEFAULT_PRONUM_V1 = 24,    // 默认设置
    EXTENDED_PRONUM_V1 = 256,  // 扩展设置
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Project_V1 : public QObject
{
    Q_OBJECT
#pragma region 构造与析构

private:
    IProject *_project = nullptr;

    // 子模型
    Program_V1 *_program_V1 = nullptr;
    RPoint_V1 *_rPoint_V1 = nullptr;
    JPoint_V1 *_jPoint_V1 = nullptr;
    Label_V1 *_label_V1 = nullptr;
    DefineWarning_V1 *_defineWarning_V1 = nullptr;

public:
    Project_V1(IProject *project);
    ~Project_V1();

#pragma endregion

#pragma region 数据转换

public:
    static ProcessingStatus_V1 ProcessingStatus_ToProxy(ProcessingStatus processingStatus);
    static ProcessingStatus ProcessingStatus_FromProxy(ProcessingStatus_V1 processingStatus_V1);

    static PointType_V1 PointType_ToProxy(PointType pointType);
    static PointType PointType_FromProxy(PointType_V1 pointType_V1);

    static ModifyPointStatus_V1 ModifyPointStatus_ToProxy(ModifyPointStatus modifyPointStatus);
    static ModifyPointStatus ModifyPointStatus_FromProxy(ModifyPointStatus_V1 modifyPointStatus_V1);

    static SaveProgramsStauts_V1 SaveProgramsStauts_ToProxy(SaveProgramsStauts saveProgramsStauts);
    static SaveProgramsStauts SaveProgramsStauts_FromProxy(SaveProgramsStauts_V1 saveProgramsStauts_V1);

    static ProgramNumType_V1 ProgramNumType_ToProxy(ProgramNumType programNumType);
    static ProgramNumType ProgramNumType_FromProxy(ProgramNumType_V1 programNumType_V1);

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 设置工程的文件操作模式
     */
    void setProjectOperateMode(ProjectFileOperateMode_V1 mode);
    /*!
     * \brief 获取控制器工程数量
     */
    int getProjectCount(const std::string &ip);
    /**
     * @brief  工程是否被修改过
     */
    bool isModified();
    /// 从控制器读取工程列表（已测）
    /// </summary>
    /// <param name="infos">输出，工程文件夹信息合集</param>
    /// <param name="ip">输入，控制器ip</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ReadProjectList(std::vector<ProjectFolderInfo_V1> &infos, const std::string &ip);
    /// <summary>
    /// 获取默认的工程名称
    /// </summary>
    /// <param name="infos">输入，工程信息列表</param>
    /// <param name="baseName">输入，基础名称字段，为空的话默认返回新建默认名称</param>
    /// <returns>默认的工程名称</returns>
    std::string NewProjectDefaultName(const std::vector<ProjectFolderInfo_V1> &infos, std::string baseName = "");
    /// <summary>
    /// 工程是否已存在
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <param name="infos">输入，工程列表</param>
    /// <returns>存在true，不存在false</returns>
    bool IsProjectExisted(const std::string &name, const std::vector<ProjectFolderInfo_V1> &infos);  //  --  已测
    /// <summary>
    /// 工程名称是否合法
    /// </summary>
    /// <param name="name">工程名称</param>
    /// <returns>合法true，非法false</returns>
    bool IsProjectNameValid(std::string &errMsg, const std::string &name);
    /**
     * @brief 创建工程（本地）
     * @param folder 输入，目标文件夹路径
     * @param name 输入，工程名称
     * @param type 输入，工程类型
     * @return 成功返回0，其他请见错误码
     */
    int CreateLocalProject(const std::string &folder, const std::string &name, ProjectType_V1 type);
    /**
     * @brief 设置当前的工程类型
     * @param type 输入，工程类型
     */
    void setCurrentProjectType(ProjectType_V1 type);
    /**
     * @brief 获取当前的工程类型
     */
    ProjectType_V1 getCurrentProjectType();
    /// <summary>
    /// 创建工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <param name="type">输入，工程类型</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int CreateProject(const std::string &name, ProjectType_V1 type = ProjectType_V1::PRO_V1);
    /// <summary>
    /// 删除工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int DelProject(const std::string &name);
    /// <summary>
    /// 重命名工程（控制器）
    /// </summary>
    /// <param name="oldName">输入，原名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int RenameProject(const std::string &oldName, const std::string &newName);
    /// <summary>
    /// 拷贝工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    void CopyProject(const std::string &name);
    /// <summary>
    /// 获取待拷贝的工程名称
    /// </summary>
    std::string GetCopiedProjectName();
    /// <summary>
    /// 粘贴工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int PasteProject(const std::string &name);
    /// <summary>
    /// 从本地导入工程，下发到控制器
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="path">输入，本地工程路径(.prj文件路径)</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ImportProject(const std::string &ip, const std::string &path);
    /// <summary>
    /// 从控制器下载工程并导出到本地文件夹中
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称(不带后缀)</param>
    /// <param name="folder">输入，本地路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ExportProject(const std::string &ip, const std::string &name, const std::string &folder);
    /// <summary>
    /// 按时间排序工程列表
    /// </summary>
    /// <param name="infos">输入输出，工程列表</param>
    void SortProjectsByTime(std::vector<ProjectFolderInfo_V1> &infos);
    /// <summary>
    /// 按首字母排序工程列表
    /// </summary>
    /// <param name="infos">输入输出，工程列表</param>
    void SortProjectsByWord(std::vector<ProjectFolderInfo_V1> &infos);

    /// <summary>
    /// 在连接控制器后加载工程的状态
    /// true-正在加载，false-加载完成
    /// </summary>
    rsignal<ProcessingStatus_V1> sigReadProjectStatusOnConnected;
    void sigReadProjectStatusOnConnectedHandler(ProcessingStatus sigReadProjectStatusOnConnectedData);
    /// <summary>
    /// 在连接控制器后译码本地编译工程的状态
    /// true-正在编译，false-编译完成
    /// </summary>
    rsignal<ProcessingStatus_V1> sigParseProjectStatusOnConnected;
    void sigParseProjectStatusOnConnectedHandler(ProcessingStatus sigParseProjectStatusOnConnectedData);
    /**
     * @brief 工程已切换
     * 发送数据 - 切换到的工程名称
     */
    rsignal<std::string> sigProjectSwitched;
    void sigProjectSwitchedHandler(std::string sigProjectSwitchedData);
    /**
     * @brief 从本地加载工程
     * @param prjFilePath 输入，.prj工程配置文件的路径
     * @return 成功返回0，其他请见错误码
     */
    int ReadLocalProjcet(const std::string &prjFilePath);
    /// <summary>
    /// 从控制器加载指定名称的工程
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ReadProject(const std::string &ip, const std::string &name);
    /**
     * @brief 保存当前工程缓存数据到本地以及控制器，是否保存到控制器，由文件操作类型决定
     * @return 成功返回0，其他请见错误码
     */
    int saveProject();
    /**
     * @brief 触发UI层保存程序文件(要保证后面一系列槽函数要是同步执行的)
     */
    rsignal<int> sigSavePrograms;
    void sigSaveProgramsHandler(int sigSaveProgramsData);
    /**
     * @brief 设置保存程序文件的状态
     */
    void setSaveProgramsStatus(SaveProgramsStauts_V1 status);
    /// <summary>
    /// 设置控制器当前激活的工程
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int setActiveProject(const std::string &name);
    /// <summary>
    /// 获取控制器当前激活的工程
    /// </summary>
    /// <param name="name">输出，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int getActiveProject(std::string &name);
    /// <summary>
    /// 保存当前加载的工程的配置信息
    /// </summary>
    /// <param name="isAllowInDebug">输入，是否允许在调试或者自动模式执行</param>
    /// <param name="isPrint">输入，是否打印输出</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int SaveProjectConfig(bool isAllowInDebug = false, bool isPrint = true);
    /// <summary>
    /// 工程是否加载成功
    /// </summary>
    /// <returns>成功true,失败false</returns>
    bool IsLoadSuccess();
    /// <summary>
    /// 获取当前加载的工程名称
    /// </summary>
    std::string GetName();
    /// <summary>
    /// 获取当前加载工程的配置信息
    /// </summary>
    ProjectInfo_V1 GetInfo();
    /// <summary>
    /// 工程配置文件后缀
    /// </summary>
    std::string ProjectFileExtension();
    /// <summary>
    /// 程序文件后缀
    /// </summary>
    std::string ProgramFileExtension();
    /// <summary>
    /// 点文件后缀
    /// </summary>
    std::string PointFileExtension();
    /// <summary>
    /// 获取程序文件列表
    /// </summary>
    std::vector<std::string> GetProgramFileList();
    /// <summary>
    /// 获取位置点文件列表
    /// </summary>
    std::vector<std::string> GetRPointFileList();
    /// <summary>
    /// 获取关节点文件列表
    /// </summary>
    std::vector<std::string> GetJPointFileList();
    /// <summary>
    /// 获取标签类型集合
    /// </summary>
    std::vector<std::string> GetLabelTypeList();
    /// <summary>
    /// 获取自定义报警列表
    /// </summary>
    std::vector<std::string> GetDefineWarningFileList();
    /// <summary>
    /// 获取任务管理配置信息
    /// </summary>
    std::vector<MultiTaskInfo_V1> GetTaskManageConfig();
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    bool isLabelExisted(const std::string &label);
    /// <summary>
    /// 指定任务是否已存在
    /// </summary>
    /// <param name="programFileName">输入，任务id</param>
    /// <returns>已存在true,不存在false</returns>
    bool IsTaskExisted(int id);
    /// <summary>
    /// 指定任务是否已存在
    /// </summary>
    /// <param name="programFileName">任务绑定的程序文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    bool IsTaskExisted(const std::string &programFileName);
    /// <summary>
    /// 指定的程序文件是否已存在
    /// </summary>
    /// <param name="fileName">程序文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    bool IsProgramFileExisted(const std::string &fileName);
    /// <summary>
    /// 指定的位置点位文件是否已存在
    /// </summary>
    /// <param name="fileName">位置点位文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    bool IsRPointFileExisted(const std::string &fileName);
    /// <summary>
    /// 任务数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    bool IsTaskUpperLimit();
    /// <summary>
    /// 程序文件数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    bool IsProgramFileUpperLimit();
    /// <summary>
    /// 位置点位文件数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    bool IsRPointFileUpperLimit();

    /**
     * @brief 检查工程中的文件名称是否和标签相同，如果相同则弹窗提示
     * @param errMsg 输出，错误描述
     * @param fileName 输入，文件名称
     * @return 相同true，不相同false
     */
    bool checkFileNameTheSameToLabel(std::string &errMsg, const std::string &fileName);
    /**
     * @brief 检查标签是否和工程中的文件名称相同，如果相同则弹窗提示
     * @param errMsg 输出，错误描述
     * @param fileName 输入，标签名称
     * @return 相同true，不相同false
     */
    bool checkLabelTheSameToFileName(std::string &errMsg, const std::string &label);

    /**
     * @brief  任务配置是否被修改过
     */
    bool isTaskModified();
    /**
     * @brief 设置任务配置修改状态
     * @param state 输入，修改状态
     */
    void setTaskModifyState(bool state);
    /// <summary>
    /// 新增任务至工程配置中
    /// </summary>
    /// <param name="task">任务</param>
    int AddTask(const MultiTaskInfo_V1 &task);
    /// <summary>
    /// 修改对应任务配置
    /// </summary>
    /// <param name="id">输入，任务id</param>
    /// <param name="type">输入，任务类型</param>
    /// <param name="fileName">输入，对应的程序文件名称</param>
    int ModifyTaskInfo(int id, int type, const std::string &fileName);
    /// <summary>
    /// 修改对应任务状态
    /// </summary>
    /// <param name="id">输入，任务id</param>
    /// <param name="isActive">输入，任务激活状态</param>
    /// <param name="isAllowInDebug">输入，是否允许在调试或者自动模式执行</param>
    int ModifyTaskState(int id, bool isActive, bool isAllowInDebug = false);
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="task">任务</param>
    int DelTask(const MultiTaskInfo_V1 &task);
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="task">任务id</param>
    int DelTask(int id);
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="programFileName">任务绑定的程序文件名称</param>
    int DelTask(const std::string &programFileName);
    /// <summary>
    /// 清空工程配置中的任务信息
    /// </summary>
    int ClearTask();

    /**
     * @brief  工程配置信息是否被修改过
     */
    bool isInfoModified();
    /**
     * @brief 设置工程配置信息修改状态
     * @param state 输入，修改状态
     */
    void setInfoModifyState(bool state);
    /// <summary>
    /// 新增程序文件至工程配置中
    /// </summary>
    /// <param name="fileName">程序文件名称或者路径</param>
    void AddProgramConfig(const std::string &fileName);
    /// <summary>
    /// 替换工程配置中已有的程序文件配置
    /// </summary>
    /// <param name="oldFileName">输入，原程序文件名称或者路径</param>
    /// <param name="newFileName">输入，新程序文件名称或者路径</param>
    void replaceProgramConfig(const std::string &oldFileName, const std::string &newFileName);
    /// <summary>
    /// 从工程配置中移除程序文件
    /// </summary>
    /// <param name="fileName">程序文件名称或者路径</param>
    void DelProgramConfig(const std::string &fileName);
    /// <summary>
    /// 新增位置点位文件至工程配置中
    /// </summary>
    /// <param name="fileName">位置点位文件名称或者路径</param>
    void AddRPointConfig(const std::string &fileName);
    /// <summary>
    /// 从工程配置中移除位置点位文件
    /// </summary>
    /// <param name="fileName">位置点位文件名称或者路径</param>
    void DelRPointConfig(const std::string &fileName);

    /**
     * @brief 获取工程中各文件的同步(修改)状态
     * @param flags 输出，工程中各文件同步(修改)状态数组，参考枚举SyncProjcetInfoType和常量SYNC_TYPE_NUMBER
     * @param length 输入，数组大小
     */
    void getSyncFlags(signed char *flags, unsigned int length);
    /**
     * @brief 向控制器发送同步标志（示教器专用，不触发编译）
     * @param type 输入，需同步的数据类型(对应枚举SyncProjcetInfoType)
     * @param isFileOperate 输入，是否为文件操作，如程序文件的新建、复制粘贴等需要输入为true
     * @return 成功返回0，其他请见错误码
     */
    int sendSyncFlag(int type, bool isFileOperate = false);
    /**
     * @brief 编译本地工程
     * @return 成功返回0，其他请见错误码
     */
    int parseLocalProject();
    /**
     * @brief 更新全局变量标签到译码库(仅工业老译码库)
     */
    void updateLablesToTransfor();

    /**
     * @brief 获取指定点位类型和所属文件的对应序号点的标签名
     * @param pointType 输入，点位类型
     * @param fileName 输入，所属文件名称
     * @param pointNo 输入，点位序号
     * @return 点的标签名
     */
    std::string getPointLabel(PointType_V1 pointType, const std::string &fileName, int pointNo);
    /**
     * @brief 修改控制器的位置点位
     * @param pointNo 输入，点位序号
     * @param pointType 输入，点位类型
     * @param taskId 输入，所属任务id
     * @param programFileName 输入，所属程序文件名称
     * @param pos 输出，点位数据
     * @param status 输出，修改状态
     * @return 成功返回0，其他请见错误码
     */
    int modifyControllerRPoint(int pointNo, PointType_V1 pointType, int taskId, const std::string &programFileName,
                               RobPos_V1 &pos, ModifyPointStatus_V1 &status);
    /**
     * @brief 修改控制器的关节点位
     * @param pointNo 输入，点位序号
     * @param pos 输出，点位数据
     * @param status 输出，修改状态
     * @return 成功返回0，其他请见错误码
     */
    int modifyControllerJPoint(int pointNo, JPos_V1 &pos, ModifyPointStatus_V1 &status);

    /**
     * @brief 获取缓存中当前加载的位置点位文件名称
     */
    std::string getCurrentRPFileName();
    /**
     * @brief 读取当前加载的位置点位文件名称
     * @param name 输出，点位文件名称
     * @return 成功返回0，其他请见错误码
     */
    int readCurrentRPFileName(std::string &name);

    /**
     * @brief 获取当前工程最大支持的程序数量
     * @param programFilesCount 程序文件数量
     * @return 成功返回0，其他请见错误码
     */
    int getProgramFilesMaxCount(int16u &programFilesCount);

    /**
     * @brief 设置当前工程最大支持的程序数量
     * @param programFilesCount 程序文件数量
     * @return 成功返回0，其他请见错误码
     */
    int setProgramFilesMaxCount(int16u programFilesCount);

    /**
     * @brief 当前加载的位置点位文件变更事件
     */
    rsignal<std::string> LoadRPFileNameChanged;
    void LoadRPFileNameChangedHandler(std::string LoadRPFileNameChangedData);

#pragma endregion

#pragma region 子模型

public:
    // 程序处理对象
    Program_V1 *GetProgram();
    bool SetProgram(Program_V1 *program_V1);

    // 位置点位处理对象
    RPoint_V1 *GetRPoint();
    bool SetRPoint(RPoint_V1 *rPoint_V1);

    // 关节点位处理对象
    JPoint_V1 *GetJPoint();
    bool SetJPoint(JPoint_V1 *jPoint_V1);

    // 全局标签处理对象
    Label_V1 *GetLabel();
    bool SetLabel(Label_V1 *label_V1);

    // 用户自定义报警处理对象
    DefineWarning_V1 *GetDefineWarning();
    bool SetDefineWarning(DefineWarning_V1 *defineWarning_V1);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
