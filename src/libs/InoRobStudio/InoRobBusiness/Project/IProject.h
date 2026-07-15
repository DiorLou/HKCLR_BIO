#pragma once
#include <string.h>
#include <QObject>
#include "ProjectHelper.h"
#include "Program/Program.h"
#include "Point/RPoint.h"
#include "Point/JPoint.h"
#include "Label/LabelDefault.h"
#include "DefineWarning/DefineWarningDefault.h"
#include "Station/StationConfig.h"
#include "dllspec.h"

namespace InoRobBusiness
{

/// <summary>
/// 业务的处理状态（如加载工程、编译工程等）
/// </summary>
enum class ProcessingStatus
{
    /// <summary>
    /// 处理中
    /// </summary>
    PROCESSING = 0,
    /// <summary>
    /// 成功
    /// </summary>
    SUCCEED,
    /// <summary>
    /// 失败
    /// </summary>
    FAILED,
};

/**
 * @brief 点位类型
 */
enum class PointType
{
    // 局部点位
    LP = 0,
    // 全局位置点位
    RP,
    // 全局关节点位
    JP,
    // 未知
    UNKNOW,
};

/**
 * @brief 调试中修改点状态
 */
enum class ModifyPointStatus : signed char
{
    // 出错
    ERR = -1,
    // 修改中
    ING,
    // 成功
    OK,
};

/**
 * @brief UI层保存程序文件的状态
 */
enum class SaveProgramsStauts
{
    // 正在保存
    SAVING = 0,
    // 保存成功
    SUCCEED,
    // 保存失败
    FAILED,
};

/**
 * @brief 程序数量类型
 */
enum class ProgramNumType
{
    // 默认设置
    DEFAULT_PRONUM = 24,
    // 扩展设置
    EXTENDED_PRONUM = 256,
};

/**
 * @brief 程序页面更新状态
 */
enum class UpdateEditPageStatus
{
    // 正在更新
    UPDATING = 0,
    // 更新成功
    SUCCEED,
    // 保更新失败
    FAILED,
};

/// <summary>
/// 工程处理基类
/// </summary>
class INOROBBUSINESS_CLASS IProject : public QObject
{
    Q_OBJECT

public:
    /// <summary>
    /// 虚析构函数，确保指针对象释放时，该类的资源能被释放
    /// </summary>
    virtual ~IProject()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**
     * @brief 执行相关操作前的状态检查
     */
    virtual bool checkStatus() = 0;

    /**
     * @brief 设置工程的文件操作模式
     */
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) = 0;
    /*!
     * \brief 获取控制器工程数量
     */
    virtual int getProjectCount(const std::string &ip) = 0;

    /**
     * @brief  工程是否被修改过
     */
    virtual bool isModified() = 0;
    /// 从控制器读取工程列表
    /// </summary>
    /// <param name="infos">输出，工程文件夹信息合集</param>
    /// <param name="ip">输入，控制器ip</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadProjectList(std::vector<ProjectFolderInfo> &infos, const std::string &ip) = 0;
    /// <summary>
    /// 获取默认的工程名称
    /// </summary>
    /// <param name="infos">输入，工程信息列表</param>
    /// <param name="baseName">输入，基础名称字段，为空的话默认返回新建默认名称</param>
    /// <returns>默认的工程名称</returns>
    virtual std::string NewProjectDefaultName(const std::vector<ProjectFolderInfo> &infos, std::string baseName = "") = 0;
    /// <summary>
    /// 工程是否已存在
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <param name="infos">输入，工程列表</param>
    /// <returns>存在true，不存在false</returns>
    virtual bool IsProjectExisted(const std::string &name, const std::vector<ProjectFolderInfo> &infos) = 0;
    /// <summary>
    /// 工程名称是否合法
    /// </summary>
    /// <param name="name">工程名称</param>
    /// <returns>合法true，非法false</returns>
    virtual bool IsProjectNameValid(std::string &errMsg, const std::string &name) = 0;
    /**
     * @brief 创建工程（本地）
     * @param folder 输入，目标文件夹路径
     * @param name 输入，工程名称
     * @param type 输入，工程类型
     * @return 成功返回0，其他请见错误码
     */
    virtual int CreateLocalProject(const std::string &folder, const std::string &name, ProjectType type) = 0;
    /**
     * @brief 设置当前的工程类型
     * @param type 输入，工程类型
     */
    virtual void setCurrentProjectType(ProjectType type) = 0;
    /**
     * @brief 获取当前的工程类型
     */
    virtual ProjectType getCurrentProjectType() = 0;
    /// <summary>
    /// 创建工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <param name="type">输入，工程类型</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int CreateProject(const std::string &name, ProjectType type = ProjectType::PRO) = 0;
    /// <summary>
    /// 删除工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int DelProject(const std::string &name, bool isreplace = false) = 0;
    /// <summary>
    /// 重命名工程（控制器）
    /// </summary>
    /// <param name="oldName">输入，原名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int RenameProject(const std::string &oldName, const std::string &newName) = 0;
    /// <summary>
    /// 拷贝工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual void CopyProject(const std::string &name) = 0;
    /// <summary>
    /// 获取待拷贝的工程名称
    /// </summary>
    virtual std::string GetCopiedProjectName() = 0;
    /// <summary>
    /// 粘贴工程（控制器）
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int PasteProject(const std::string &name) = 0;
    /// <summary>
    /// 从本地导入工程，下发到控制器
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="path">输入，本地工程路径(.prj文件路径)</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ImportProject(const std::string &ip, const std::string &path) = 0;
    /// <summary>
    /// 从控制器下载工程并导出到本地文件夹中
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称(不带后缀)</param>
    /// <param name="folder">输入，本地路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ExportProject(const std::string &ip, const std::string &name, const std::string &folder) = 0;
    /// <summary>
    /// 按时间排序工程列表
    /// </summary>
    /// <param name="infos">输入输出，工程列表信息集合</param>
    virtual void SortProjectsByTime(std::vector<ProjectFolderInfo> &infos) = 0;
    /// <summary>
    /// 按首字母排序工程列表
    /// </summary>
    /// <param name="infos">输入输出，工程列表信息集合</param>
    virtual void SortProjectsByWord(std::vector<ProjectFolderInfo> &infos) = 0;
    /**
     * @brief 格式化工程日期显示
     * @param infos 输入输出，工程列表信息集合
     */
    virtual void formatProjectTime(std::vector<ProjectFolderInfo> &infos) = 0;

    /**
     * @brief 从本地加载工程
     * @param prjFilePath 输入，.prj工程配置文件的路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int ReadLocalProjcet(const std::string &prjFilePath) = 0;
    /// <summary>
    /// 从控制器加载指定名称的工程
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称</param>
    /// <param name="isReadSamePrj">输入，如果是和当前工程相同的，是否依旧从控制器读取</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadProject(const std::string &ip, const std::string &name, bool isReadSamePrj = false) = 0;
    /**
     * @brief 保存当前工程缓存数据到本地以及控制器，是否保存到控制器，由文件操作类型决定
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveProject() = 0;
    /**
     * @brief 设置保存程序文件的状态
     */
    virtual void setSaveProgramsStatus(SaveProgramsStauts status) = 0;
    /// <summary>
    /// 设置控制器当前激活的工程
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int setActiveProject(const std::string &name) = 0;
    /// <summary>
    /// 获取控制器当前激活的工程
    /// </summary>
    /// <param name="name">输出，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int getActiveProject(std::string &name) = 0;
    /// <summary>
    /// 保存当前加载的工程的配置信息
    /// </summary>
    /// <param name="isAllowInDebug">输入，是否允许在调试或者自动模式执行</param>
    /// <param name="isPrint">输入，是否打印输出</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveProjectConfig(bool isAllowInDebug = false, bool isPrint = true) = 0;
    /// <summary>
    /// 工程是否加载成功
    /// </summary>
    /// <returns>成功true,失败false</returns>
    virtual bool IsLoadSuccess() = 0;
    /// <summary>
    /// 获取当前加载的工程名称
    /// </summary>
    virtual std::string GetName() = 0;
    /// <summary>
    /// 获取当前加载工程的配置信息
    /// </summary>
    virtual ProjectInfo GetInfo() = 0;
    /// <summary>
    /// 工程配置文件后缀
    /// </summary>
    virtual std::string ProjectFileExtension() = 0;
    /// <summary>
    /// 程序文件后缀
    /// </summary>
    virtual std::string ProgramFileExtension() = 0;
    /// <summary>
    /// 点文件后缀
    /// </summary>
    virtual std::string PointFileExtension() = 0;
    /// <summary>
    /// 获取程序文件列表
    /// </summary>
    virtual std::vector<std::string> GetProgramFileList() = 0;
    /// <summary>
    /// 获取位置点文件列表
    /// </summary>
    virtual std::vector<std::string> GetRPointFileList() = 0;
    /// <summary>
    /// 获取关节点文件列表
    /// </summary>
    virtual std::vector<std::string> GetJPointFileList() = 0;
    /// <summary>
    /// 获取标签类型集合
    /// </summary>
    virtual std::vector<std::string> GetLabelTypeList() = 0;
    /// <summary>
    /// 获取自定义报警列表
    /// </summary>
    virtual std::vector<std::string> GetDefineWarningFileList() = 0;
    /// <summary>
    /// 获取任务管理配置信息
    /// </summary>
    virtual std::vector<MultiTaskInfo> GetTaskManageConfig() = 0;
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    virtual bool isLabelExisted(const std::string &label) = 0;
    /// <summary>
    /// 指定任务是否已存在
    /// </summary>
    /// <param name="programFileName">输入，任务id</param>
    /// <returns>已存在true,不存在false</returns>
    virtual bool IsTaskExisted(int id) = 0;
    /// <summary>
    /// 指定任务是否已存在
    /// </summary>
    /// <param name="programFileName">任务绑定的程序文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    virtual bool IsTaskExisted(const std::string &programFileName) = 0;
    /// <summary>
    /// 指定的程序文件是否已存在
    /// </summary>
    /// <param name="fileName">程序文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    virtual bool IsProgramFileExisted(const std::string &fileName) = 0;
    /// <summary>
    /// 指定的位置点位文件是否已存在
    /// </summary>
    /// <param name="fileName">位置点位文件名称</param>
    /// <returns>已存在true,不存在false</returns>
    virtual bool IsRPointFileExisted(const std::string &fileName) = 0;
    /// <summary>
    /// 任务数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    virtual bool IsTaskUpperLimit() = 0;
    /// <summary>
    /// 程序文件数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    virtual bool IsProgramFileUpperLimit() = 0;
    /// <summary>
    /// 位置点位文件数量是否已满
    /// </summary>
    /// <returns>达到上限true,未达到上限false</returns>
    virtual bool IsRPointFileUpperLimit() = 0;

    /**
     * @brief 检查工程中的文件名称是否和标签相同，如果相同则弹窗提示
     * @param errMsg 输出，错误描述
     * @param fileName 输入，文件名称
     * @return 相同true，不相同false
     */
    virtual bool checkFileNameTheSameToLabel(std::string &errMsg, const std::string &fileName) = 0;
    /**
     * @brief 检查标签是否和工程中的文件名称相同，如果相同则弹窗提示
     * @param errMsg 输出，错误描述
     * @param fileName 输入，标签名称
     * @return 相同true，不相同false
     */
    virtual bool checkLabelTheSameToFileName(std::string &errMsg, const std::string &label) = 0;

    /**
     * @brief  任务配置是否被修改过
     */
    virtual bool isTaskModified() = 0;
    /**
     * @brief 设置任务配置修改状态
     * @param state 输入，修改状态
     */
    virtual void setTaskModifyState(bool state) = 0;
    /**
     * @brief  静态任务是否被修改过
     */
    virtual bool isStaticTaskModified() = 0;
    /**
     * @brief  静态任务程序是否被修改过
     */
    virtual bool isStaticProgramModified(int taskId) = 0;
    /**
     * @brief 设置任务配置修改状态
     * @param fileName 输入程序名，修改状态：isSave设置是否保存、isParse设置是否编译、isActive设置是否激活
     */
    virtual void setTaskStateIsSave(const std::string &fileName, bool isSave) = 0;
    virtual void setTaskStateIsParse(const std::string &fileName, bool isParse) = 0;
    virtual void setTaskStateIsActive(const std::string &fileName, bool isActive) = 0;
    /**
     * @brief 设置任务配置修改状态
     * @param state 输入程序名，修改状态：isSave设置全部程序是否保存、isParse设置全程程序是否编译
     */
    virtual void setTaskStateAllSaved(bool isSave) = 0;
    virtual void setTaskStateAllParsed(bool isParse) = 0;
    /**
     * @brief 设置程序状态
     * @param name 输入程序名，修改状态
     */
    virtual void setStaticProgramState(const std::string &name, bool isSave) = 0;
    virtual void setStaticProgramState(const std::string &name, bool isSave, bool isParse) = 0;
    /// <summary>
    /// 新增任务至工程配置中
    /// </summary>
    /// <param name="task">任务</param>
    virtual int AddTask(const MultiTaskInfo &task) = 0;
    /// <summary>
    /// 修改对应任务配置
    /// </summary>
    /// <param name="id">输入，任务id</param>
    /// <param name="type">输入，任务类型</param>
    /// <param name="fileName">输入，对应的程序文件名称</param>
    virtual int ModifyTaskInfo(int id, int type, const std::string &fileName) = 0;
    /// <summary>
    /// 修改对应任务状态
    /// </summary>
    /// <param name="id">输入，任务id</param>
    /// <param name="isActive">输入，任务激活状态</param>
    /// <param name="isAllowInDebug">输入，是否允许在调试或者自动模式执行</param>
    virtual int ModifyTaskState(int id, bool isActive, bool isAllowInDebug = false) = 0;
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="task">任务</param>
    virtual int DelTask(const MultiTaskInfo &task) = 0;
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="task">任务id</param>
    virtual int DelTask(int id) = 0;
    /// <summary>
    /// 从工程配置中移除任务
    /// </summary>
    /// <param name="programFileName">任务绑定的程序文件名称</param>
    virtual int DelTask(const std::string &programFileName) = 0;
    /// <summary>
    /// 清空工程配置中的任务信息
    /// </summary>
    virtual int ClearTask() = 0;

    /**
     * @brief  工程配置信息是否被修改过
     */
    virtual bool isInfoModified() = 0;
    /**
     * @brief 设置工程配置信息修改状态
     * @param state 输入，修改状态
     */
    virtual void setInfoModifyState(bool state) = 0;
    /// <summary>
    /// 新增程序文件至工程配置中
    /// </summary>
    /// <param name="fileName">程序文件名称或者路径</param>
    virtual void AddProgramConfig(const std::string &fileName) = 0;
    /// <summary>
    /// 替换工程配置中已有的程序文件配置
    /// </summary>
    /// <param name="oldFileName">输入，原程序文件名称或者路径</param>
    /// <param name="newFileName">输入，新程序文件名称或者路径</param>
    virtual void replaceProgramConfig(const std::string &oldFileName, const std::string &newFileName) = 0;
    /// <summary>
    /// 从工程配置中移除程序文件
    /// </summary>
    /// <param name="fileName">程序文件名称或者路径</param>
    virtual void DelProgramConfig(const std::string &fileName) = 0;
    /// <summary>
    /// 新增位置点位文件至工程配置中
    /// </summary>
    /// <param name="fileName">位置点位文件名称或者路径</param>
    virtual void AddRPointConfig(const std::string &fileName) = 0;
    /// <summary>
    /// 从工程配置中移除位置点位文件
    /// </summary>
    /// <param name="fileName">位置点位文件名称或者路径</param>
    virtual void DelRPointConfig(const std::string &fileName) = 0;

    /**
     * @brief 获取工程中各文件的同步(修改)状态
     * @param flags 输出，工程中各文件同步(修改)状态数组，参考枚举SyncProjcetInfoType和常量SYNC_TYPE_NUMBER
     * @param length 输入，数组大小
     */
    virtual void getSyncFlags(signed char *flags, unsigned int length) = 0;
    /**
     * @brief 向控制器发送同步标志（示教器专用，不触发编译）
     * @param type 输入，需同步的数据类型(对应枚举SyncProjcetInfoType)
     * @param isFileOperate 输入，是否为文件操作，如程序文件的新建、复制粘贴等需要输入为true
     * @return 成功返回0，其他请见错误码
     */
    virtual int sendSyncFlag(int type, bool isFileOperate = false) = 0;
    /**
     * @brief 编译本地工程
     * @return 成功返回0，其他请见错误码
     */
    virtual int parseLocalProject() = 0;
    /**
     * @brief 更新全局变量标签到译码库(仅工业老译码库)
     */
    virtual void updateLablesToTransfor() = 0;
    /**
     * @brief 判断字符串是否为关键字
     * @param str 输入，想要判断的字符串
     */
    virtual bool isKeyWord(const std::string &str) = 0;

    /**
     * @brief 获取指定点位类型和所属文件的对应序号点的标签名
     * @param pointType 输入，点位类型
     * @param fileName 输入，所属文件名称
     * @param pointNo 输入，点位序号
     * @return 点的标签名
     */
    virtual std::string getPointLabel(PointType pointType, const std::string &fileName, int pointNo) = 0;
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
    virtual int modifyControllerRPoint(int pointNo, PointType pointType, int taskId,
                                       const std::string &programFileName, RobPos &pos, ModifyPointStatus &status) = 0;
    /**
     * @brief 修改控制器的关节点位
     * @param pointNo 输入，点位序号
     * @param pos 输出，点位数据
     * @param status 输出，修改状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int modifyControllerJPoint(int pointNo, JPos &pos, ModifyPointStatus &status) = 0;
    /**
     * @brief 热调点模式下修改控制器的位置点位
     * @param 点类型
     * @param 点序号
     * @param 点位数据
     * @param 所属程序文件名称
     * @param 修改状态
     * @return
     */
    virtual bool ModifyPointRT(PointType pointType, int16u pointNo, RobPos robPos,
                               const std::string &programFileName, ModifyPointStatus &status) = 0;

    /**
     * @brief 获取缓存中当前加载的位置点位文件名称
     */
    virtual std::string getCurrentRPFileName() = 0;
    /**
     * @brief 读取当前加载的位置点位文件名称
     * @param name 输出，点位文件名称
     * @return 成功返回0，其他请见错误码
     */
    virtual int readCurrentRPFileName(std::string &name) = 0;

    /**
     * @brief 获取当前工程最大支持的程序数量
     * @param programFilesCount 程序文件数量
     * @return 成功返回0，其他请见错误码
     */
    virtual int getProgramFilesMaxCount(int16u &programFilesCount) = 0;

    /**
     * @brief 设置当前工程最大支持的程序数量
     * @param programFilesCount 程序文件数量
     * @return 成功返回0，其他请见错误码
     */
    virtual int setProgramFilesMaxCount(int16u programFilesCount) = 0;

    /// <summary>
    /// 获取程序处理对象
    /// </summary>
    virtual IProgram *GetProgram() = 0;
    /// <summary>
    /// 获取位置点位处理对象
    /// </summary>
    virtual IRPoint *GetRPoint() = 0;
    /// <summary>
    /// 获取关节点位处理对象
    /// </summary>
    virtual IJPoint *GetJPoint() = 0;
    /// <summary>
    /// 获取全局标签处理对象
    /// </summary>
    virtual ILabel *GetLabel() = 0;
    /// <summary>
    /// 获取用户自定义报警处理对象
    /// </summary>
    virtual IDefineWarning *GetDefineWarning() = 0;
    /// <summary>
    /// 获取工位配置处理对象
    /// </summary>
    virtual IStationConfig *GetStationConfig() = 0;

    /**
     * @brief 设置工程读取状态
     * @param status 0:空闲 1:正在被读取
     */
    virtual void setProjectReadStatus(int status) = 0;
    /**
     * @brief 设置工程解析状态
     * @param status 0:空闲 1:正在被解析
     */
    virtual void setProjectParseStatus(int status) = 0;

    /**
     * @brief 加载并本地编译工程
     * @param isReadSameProjcet 输入，是否允许加载相同的工程，如加载完A工程，再次触发，还是会从控制器中读取，而不是直接返回
     */
    virtual void readAndParseProject(bool isReadSameProjcet = false) = 0;

    /**
     * @brief 解析文件运动指令中点位信息对应的工具工件号
     * @param fileName 文件名
     * @param pointType 点类型
     * @return
     */
    virtual unordered_map<int, pair<int, int>> AnaPointToolAndWobj(string fileName, int pointType) = 0;

    /**
     * @brief 获取当前是否能通过FTP拿工程文件
     * @param getFlag 标识
     * @return
     */
    virtual bool getProjectIsCanFTPFlag(int &getFlag) = 0;

    /**
     * @brief 设置当前通过FTP拿工程的状态
     * @param getFlag 标识
     * @return
     */
    virtual bool setProjectFTPProgress(int setFlag) = 0;

    /**
     * @brief 告诉控制器开始通过FTP获取工程
     */
    virtual void tellControllerStartPrjFTP() = 0;

    /**
     * @brief 设置页面更新状态
     */
    virtual void setPageUpdateStatus(UpdateEditPageStatus status) = 0;

    /**
     * @brief 设置页面更新状态
     * @param projectName 输入 工程名称
     * @param programName 输入 需要更新的程序名称
     * @return 0 成功，其他 失败
     */
    virtual int updateProgramEditPage(std::string projectName, std::string programName) = 0;

    /**
     * @brief 通知控制器重新读取断点文件
     * @return 0 成功，其他 失败
     */
    virtual int requireControllerReloadBreakPointsFile() = 0;

    /**
     * @brief 通知控制器禁用所有断点
     * @param target 0 禁用 非0启用
     * @return 0 成功，其他 失败
     */
    virtual int setControllerEnableAllBreakPointsState(int target) = 0;
    /**
     * @brief 读取禁用所有断点状态
     * @param target 0 禁用 非0启用
     * @return 0 成功，其他 失败
     */
    virtual int getControllerEnableAllBreakPointsState(int &target) = 0;

    /**
     * @brief 设置控制器工程启动行
     * @param exeFlow 输入 包含判断条件的执行流行号
     * @param uuid 输入 启动行item uid
     * @return 0 成功，其他 失败
     */
    virtual int setControllerStartLine(const std::vector<int> &exeFlow, const string &uuid) = 0;
    /**
     * @brief 读取控制器工程启动行
     * @param uuid 输出 启动行item uid
     * @return 0 成功，其他 失败
     */
    virtual int getControllerStartLine(string &uuid) = 0;
Q_SIGNALS:
    /// <summary>
    /// 在连接控制器后加载工程的状态
    /// true-正在加载，false-加载完成
    /// </summary>
    void sigReadProjectStatusOnConnected(ProcessingStatus status);
    /// <summary>
    /// 在连接控制器后译码本地编译工程的状态
    /// true-正在编译，false-编译完成
    /// </summary>
    void sigParseProjectStatusOnConnected(ProcessingStatus status);
    /**
     * @brief 工程已切换
     * 发送数据 - 切换到的工程名称
     */
    void sigProjectSwitched(std::string name);
    /**
     * @brief 触发UI层保存程序文件(要保证后面一系列槽函数要是同步执行的)
     */
    void sigSavePrograms(int flag);
    /**
     * @brief 当前加载的位置点位文件变更事件
     */
    void loadRPFileNameChanged(std::string name);
    /**
     * @brief 工程将切换的信号（译码库编译冲突
     */
    void sigSwitchProject();
    /**
     * @brief 工程将解析的信号（译码库编译冲突
     */
    void sigParseProject();
    /**
     * @brief 触发页面刷新程序的数据
     */
    void sigUpdateProgramPage(std::string projectName, std::string programName);
};

}  // namespace InoRobBusiness
