#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"

namespace InoRobBusinessProxy
{
#pragma region 工程管理相关结构体定义

/// <summary>
/// 工程相关文件的文件头信息
/// (因历史原因，考虑兼容性，工程文件的文件头暂不升级为最新的)
/// (最新的文件头格式请见StrSerFileInfo类)
/// </summary>
typedef struct _ProjectFileInfo_V1
{
    _ProjectFileInfo_V1()
    {
        systemVersion = "";
        robotName = "";
        time = "";
    }

    _ProjectFileInfo_V1 &operator=(const _ProjectFileInfo_V1 &other)
    {
        this->systemVersion = other.systemVersion;
        this->robotName = other.robotName;
        this->time = other.time;
        return (*this);
    }

    std::string systemVersion;  // 系统软件主版本
    std::string robotName;      // 机型名
    std::string time;           // 修改时间

} ProjectFileInfo_V1;

#pragma endregion

// 工程中所有文件的操作模式
enum class ProjectFileOperateMode_V1
{
    // 需要手动从本地同步到控制器
    LOCAL_TO_CTRL_V1 = 0,
    // 操作本地文件时，同时同步到控制器
    ALWAYS_CTRL_V1,
};

// 自定义报警
struct UserDefineWaringsData_V1
{
    std::vector<string> Warings;

    UserDefineWaringsData_V1()
    {
        Warings.clear();
        for (size_t i = 0; i < 16; i++)
        {
            Warings.push_back("");
        }
    }

    UserDefineWaringsData_V1 &operator=(const UserDefineWaringsData_V1 &other)
    {
        this->Warings.clear();
        this->Warings.assign(other.Warings.begin(), other.Warings.end());
        return (*this);
    }
};

typedef struct _LabelItem_V1
{
    int nLabelId;
    int nIndex;
    std::string sLabel;
    std::string sDescription;
    std::string sOriginalName;

    _LabelItem_V1()
    {
        nLabelId = 0;
        nIndex = 0;
        sLabel = "";
        sDescription = "";
        sOriginalName = "";
    }

    _LabelItem_V1 &operator=(const _LabelItem_V1 &other)
    {
        this->nLabelId = other.nLabelId;
        this->nIndex = other.nIndex;
        this->sLabel = other.sLabel;
        this->sDescription = other.sDescription;
        this->sOriginalName = other.sOriginalName;
        return (*this);
    }
} LabelItem_V1;

typedef struct _IoLabelItems_V1
{
    int nNumberOfLabels;
    std::vector<LabelItem_V1> LabelsArray;

    _IoLabelItems_V1()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    void clear()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    _IoLabelItems_V1 &operator=(const _IoLabelItems_V1 &other)
    {
        this->nNumberOfLabels = other.nNumberOfLabels;
        this->LabelsArray.clear();
        this->LabelsArray.assign(other.LabelsArray.begin(), other.LabelsArray.end());
        return (*this);
    }
} IoLabelItems_V1;

enum class LabelType_V1
{
    // IO输入 - bit
    IO_INPUT_BIT_V1 = 0,
    // IO输出 - bit
    IO_OUTPUT_BIT_V1,
    // IO输入 - byte
    IO_INPUT_BYTE_V1,
    // IO输出 - byte
    IO_OUTPUT_BYTE_V1,
    // IO输入 - word
    IO_INPUT_WORD_V1,
    // IO输出 - word
    IO_OUTPUT_WORD_V1,
    // DA变量
    DA_V1,
    // AD变量
    AD_V1,
    // B变量
    B_V1,
    // R变量
    R_V1,
    // D变量
    D_V1,
    // 未知
    UNKNOWN_V1,
};

enum class IoType_V1
{
    /// <summary>
    /// 标准IO
    /// </summary>
    STANDARD_V1 = 0,
    /// <summary>
    /// 从站现场IO
    /// </summary>
    SLAVE_SCENE_V1,
    /// <summary>
    /// 主站现场IO
    /// </summary>
    MASTER_SCENE_V1,
    /// <summary>
    /// 内存IO
    /// </summary>
    MEMORY_V1,
};

enum class IoDataType_V1
{
    // 比特
    BIT_V1 = 0,
    // 字节
    BYTE_V1,
    // 字
    WORD_V1,
};

typedef struct _PtLabelAndDes_V1
{
    _PtLabelAndDes_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        pointIndex = -1;
        label = std::string();
        description = std::string();
    }

    _PtLabelAndDes_V1 &operator=(const _PtLabelAndDes_V1 &other)
    {
        this->pointIndex = other.pointIndex;
        this->label = other.label;
        this->description = other.description;
        return (*this);
    }

    int pointIndex;           // 对应的点位序号
    std::string label;        // 点位标签
    std::string description;  // 点位描述
} PtLabelAndDes_V1;

#pragma region 工程管理相关枚举定义

enum class TaskType_V1
{
    /// <summary>
    /// 主任务
    /// </summary>
    Main_V1 = 0,
    /// <summary>
    /// 静态任务
    /// </summary>
    Static_V1,
    /// <summary>
    /// 动态任务
    /// </summary>
    Dynamic_V1,
    /// <summary>
    /// Xqt任务
    /// </summary>
    Xqt_V1,
};

/**
 * @brief 工程类型
 */
enum class ProjectType_V1
{
    // pro工程(程序文件为.pro)
    PRO_V1 = 0,
    // lua工程(程序文件为.lua)
    LUA_V1,
};

enum class ProgramType_V1
{
    /// <summary>
    /// 通用程序
    /// </summary>
    FUNCTION_V1 = 0,
    /// <summary>
    /// 入口程序
    /// </summary>
    START_END_V1,
};

#pragma endregion

/// <summary>
/// 工程文件夹信息
/// </summary>
typedef struct _ProjectFolderInfo_V1
{
    _ProjectFolderInfo_V1()
    {
        projectName = "";
        modifyTime = "";
        memorySize = 0;
    }

    _ProjectFolderInfo_V1 &operator=(const _ProjectFolderInfo_V1 &other)
    {
        this->projectName = other.projectName;
        this->modifyTime = other.modifyTime;
        this->memorySize = other.memorySize;
        return (*this);
    }

    bool operator==(const _ProjectFolderInfo_V1 &other)
    {
        if (this->projectName == other.projectName
            && this->modifyTime == other.modifyTime
            && this->memorySize == other.memorySize)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string projectName;  // 工程名称
    std::string modifyTime;   // 修改时间
    int memorySize;           // 工程文件夹内存大小(kb)

} ProjectFolderInfo_V1;

/// <summary>
/// 多任务信息
/// </summary>
typedef struct _MultiTaskInfo_V1
{
    _MultiTaskInfo_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        taskId = 0;
        taskType = 1;
        enterProgramFile = "";
        isActive = false;
    }

    _MultiTaskInfo_V1 &operator=(const _MultiTaskInfo_V1 &other)
    {
        this->taskId = other.taskId;
        this->taskType = other.taskType;
        this->enterProgramFile = other.enterProgramFile;
        this->isActive = other.isActive;
        return (*this);
    }

    bool operator==(const _MultiTaskInfo_V1 &other) const
    {
        bool isEqual = true;

        if (this->taskId != other.taskId)
        {
            isEqual = false;
        }

        if (this->taskType != other.taskType)
        {
            isEqual = false;
        }

        if (this->enterProgramFile != other.enterProgramFile)
        {
            isEqual = false;
        }

        if (this->isActive != other.isActive)
        {
            isEqual = false;
        }

        return isEqual;
    }

    int taskId;                    // 任务id
    int taskType;                  // 任务类型（0：主任务， 1：静态任务， 2：动态任务， 3: Xqt任务）
    std::string enterProgramFile;  // 对应的程序文件名称
    bool isActive;                 // 是否激活

} MultiTaskInfo_V1;

/// <summary>
/// 工程配置信息(.prj文件信息)
/// </summary>
typedef struct _ProjectInfo_V1
{
    _ProjectInfo_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        fileType = "RobotProjectConfigFile";
        company = "Inovance";
        majorVersion = 1;
        minorVersion = 0;
        isMainActive = true;
        mainFile = "";
        multiTaskCount = 0;
        programFileCount = 0;
        robPointFileCount = 0;
        multiTaskArr.clear();
        programFileArr.clear();
        robPointFileArr.clear();
    }

    _ProjectInfo_V1 &operator=(const _ProjectInfo_V1 &other)
    {
        this->fileType = other.fileType;
        this->company = other.company;
        this->majorVersion = other.majorVersion;
        this->minorVersion = other.minorVersion;
        this->isMainActive = other.isMainActive;
        this->mainFile = other.mainFile;
        this->multiTaskCount = other.multiTaskCount;
        this->programFileCount = other.programFileCount;
        this->robPointFileCount = other.robPointFileCount;
        this->multiTaskArr.clear();
        this->programFileArr.clear();
        this->robPointFileArr.clear();
        this->multiTaskArr.assign(other.multiTaskArr.begin(), other.multiTaskArr.end());
        this->programFileArr.assign(other.programFileArr.begin(), other.programFileArr.end());
        this->robPointFileArr.assign(other.robPointFileArr.begin(), other.robPointFileArr.end());
        return (*this);
    }

    std::string fileType;                        // 文件类型
    std::string company;                         // 公司名称
    int majorVersion;                            // 文件主版本号
    int minorVersion;                            // 文件次版本号
    bool isMainActive;                           // 是否统一激活任务
    std::string mainFile;                        // 主程序文件
    int multiTaskCount;                          // 多任务数量
    int programFileCount;                        // 程序文件数量
    int robPointFileCount;                       // 位置点位文件数量
    std::vector<MultiTaskInfo_V1> multiTaskArr;  // 多任务集合
    std::vector<string> programFileArr;          // 程序文件集合
    std::vector<string> robPointFileArr;         // 位置点位文件集合

} ProjectInfo_V1;

#pragma region 数据转换

bool ProjectFileInfo_ToProxy(const ProjectFileInfo &projectFileInfo, ProjectFileInfo_V1 &projectFileInfo_V1);
bool ProjectFileInfo_FromProxy(const ProjectFileInfo_V1 &projectFileInfo_V1, ProjectFileInfo &projectFileInfo);

ProjectFileOperateMode_V1 ProjectFileOperateMode_ToProxy(ProjectFileOperateMode projectFileOperateMode);
ProjectFileOperateMode ProjectFileOperateMode_FromProxy(ProjectFileOperateMode_V1 projectFileOperateMode_V1);

bool UserDefineWaringsData_ToProxy(const UserDefineWaringsData &userDefineWaringsData, UserDefineWaringsData_V1 &userDefineWaringsData_V1);
bool UserDefineWaringData_FromProxy(const UserDefineWaringsData_V1 &userDefineWaringsData_V1, UserDefineWaringsData &userDefineWaringsData);

bool LabelItem_ToProxy(const LabelItem &labelItem, LabelItem_V1 &labelItem_V1);
bool LabelItem_FromProxy(const LabelItem_V1 &labelItem_V1, LabelItem &labelItem);

bool IoLabelItems_ToProxy(const IoLabelItems &ioLabelItems, IoLabelItems_V1 &ioLabelItems_V1);
bool IoLabelItems_FromProxy(const IoLabelItems_V1 &ioLabelItems_V1, IoLabelItems &ioLabelItems);

LabelType_V1 LabelType_ToProxy(LabelType labelType);
LabelType LabelType_FromProxy(LabelType_V1 labelType_V1);

IoType_V1 IoType_ToProxy(IoType ioType);
IoType IoType_FromProxy(IoType_V1 ioType_V1);

IoDataType_V1 IoDataType_ToProxy(IoDataType ioDataType);
IoDataType IoDataType_FromProxy(IoDataType_V1 ioDataType_V1);

bool PtLabelAndDes_ToProxy(const PtLabelAndDes &ptLabelAndDes, PtLabelAndDes_V1 &ptLabelAndDes_V1);
bool PtLabelAndDes_FromProxy(const PtLabelAndDes_V1 &ptLabelAndDes_V1, PtLabelAndDes &ptLabelAndDes);

TaskType_V1 TaskType_ToProxy(TaskType taskType);
TaskType TaskType_FromProxy(TaskType_V1 taskType_V1);

ProjectType_V1 ProjectType_ToProxy(ProjectType projectType);
ProjectType ProjectType_FromProxy(ProjectType_V1 projectType_V1);

ProgramType_V1 ProgramType_ToProxy(ProgramType programType);
ProgramType ProgramType_FromProxy(ProgramType_V1 programType_V1);

bool ProjectFolderInfo_ToProxy(const ProjectFolderInfo &projectFolderInfo, ProjectFolderInfo_V1 &projectFolderInfo_V1);
bool ProjectFolderInfo_FromProxy(const ProjectFolderInfo_V1 &projectFolderInfo_V1, ProjectFolderInfo &projectFolderInfo);

bool MultiTaskInfo_ToProxy(const MultiTaskInfo &multiTaskInfo, MultiTaskInfo_V1 multiTaskInfo_V1);
bool MultiTaskInfo_FromProxy(const MultiTaskInfo_V1 multiTaskInfo_V1, MultiTaskInfo &multiTaskInfo);

bool ProjectInfo_ToProxy(const ProjectInfo &projectInfo, ProjectInfo_V1 &projectInfo_V1);
bool ProjectInfo_FromProxy(const ProjectInfo_V1 &projectInfo_V1, ProjectInfo &projectInfo);

#pragma endregion

}  // namespace InoRobBusinessProxy
