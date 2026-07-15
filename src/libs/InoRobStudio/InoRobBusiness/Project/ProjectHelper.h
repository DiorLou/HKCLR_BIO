#pragma once
#include <string>
#include <vector>
#include "comwithTp.h"
#include "../InoRobUtil/Include/InoRobUtil.h"
#include "../InoRobBusiness/Include/GlobalDataTypes.h"
#include "../../GlobalDataService/DataService/DataSrvBase.h"
#include "dllspec.h"

using namespace InoRobUtil;

#define MAX_PROJECT_SIZE    35 * 1024  // 允许加载的工程最大内存大小（单位kb）
#define MAX_NUM_PROGRAMFILE 24         // 最大程序文件数量
#define MAX_NUM_TASK        16         // 最大任务数量
#define MAX_NUM_RPOINTFILE  128        // 最大位置点位文件数量
#define MAX_NUM_POINT       10000      // 单个点位文件最大的点位数量

#define MAX_PROJECT_FILENAME_LENGTH 16   // 工程(配置文件)名称最大长度
#define MAX_PROGRAM_FILENAME_LENGTH 26   // 程序文件名称最大长度
#define MAX_POINT_FILENAME_LENGTH   26   // 点位文件名称最大长度
#define MAX_LABEL_LENGTH            20   // 标签最大长度
#define MAX_CNDES_LENGTH            50   // 包含中文备注最大长度
#define MAX_NCNDES_LENGTH           100  // 非中文备注最大长度

#define PROJECT_MAJOR_VERSION 2  // 工程主版本
#define PROJECT_MINOR_VERSION 0  // 工程次版本

#define PROJECT_FILE_EXTENSION ".prj"  // 工程配置文件后缀
#define PROGRAM_FILE_EXTENSION ".pro"  // pro程序文件后缀
#define LUA_FILE_EXTENSION     ".lua"  // lua程序文件后缀
#define XML_FILE_EXTENSION     ".xml"  // xml程序文件后缀
#define POINT_FILE_EXTENSION   ".pts"  // 点位文件后缀

#define MAIN_PROGRAM_FILE_NAME  "main.pro"         // 主程序文件名称
#define PROGRAM_START_FUNCTION  "Func func1()"     // 通用程序文件开头
#define PROGRAM_END_FUNCTION    "EndFunc;"         // 通用程序文件结尾
#define PROGRAM_START_STARTEND  "Start;"           // 入口程序文件开头
#define PROGRAM_END_STARTEND    "End;"             // 入口程序文件结尾
#define PROGRAM_START_INTERRUPT "Trap TrapFunc()"  // 中断程序文件开头
#define PROGRAM_END_INTERRUPT   "EndTrap;"         // 中断程序文件结尾
#define PROGRAM_START_STATIONFUNC "Func StationEntry()"  // 工位预约程序文件开头
#define PROGRAM_END_STATIONFUNC   "EndFunc;"             // 工位预约通用程序文件结尾

#define STANDARD_IO_BIT_START     0      // 标准IO - bit类型标签起始序号
#define STANDARD_IO_BIT_END       127    // 标准IO - bit类型标签终止序号
#define SLAVE_SCENE_IO_BIT_START  512    // 从站现场IO - bit类型标签起始序号
#define SLAVE_SCENE_IO_BIT_END    4607   // 从站现场IO - bit类型标签终止序号
#define MASTER_SCENE_IO_BIT_START 6656   // 主站现场IO - bit类型标签起始序号
#define MASTER_SCENE_IO_BIT_END   10751  // 主站现场IO - bit类型标签终止序号
#ifdef COBOT
    #define TOOL_SCENE_IO_BIT_START 128   // 工具IO - bit类型标签起始序号
    #define TOOL_SCENE_IO_BIT_END   143  // 工具IO - bit类型标签终止序号
#endif
#define MEMORY_IO_BIT_START       12800  // 内存IO - bit类型标签起始序号
#define MEMORY_IO_BIT_END         13823  // 内存IO - bit类型标签终止序号
#define BYTE_TO_BIT_RATIO         8      // 字节到比特的转换比例
#define WORD_TO_BYTE_RATIO        2      // 字到字节的转换比例
#define WORD_TO_BIT_RATIO         16     // 字到比特的转换比例
#define IRLINK_LABEL_START        0      // IRLink的AD/DA标签起始序号
#define IRLINK_LABEL_END          15     // IRLink的AD/DA标签终止序号
#define ETHERCAT_LABEL_START      64     // EtherCat的AD/DA标签起始序号
#define ETHERCAT_LABEL_END        79     // EtherCat的AD/DA标签终止序号
#define MAX_BRD_LABEL_NUMBER      256    // B/R/D变量标签最大数量

#define MAX_NUM_MODIFY_PTS_NO 430  // 批量改点 - 单次发给控制器的点位序号集合最大个数

#pragma region 工程管理相关结构体定义
/// <summary>
/// 工程相关文件的文件头信息
/// (因历史原因，考虑兼容性，工程文件的文件头暂不升级为最新的)
/// (最新的文件头格式请见StrSerFileInfo类)
/// </summary>
typedef struct _ProjectFileInfo
{
    _ProjectFileInfo()
    {
        systemVersion = "";
        robotName = "";
        time = "";
    }

    _ProjectFileInfo &operator=(const _ProjectFileInfo &other)
    {
        this->systemVersion = other.systemVersion;
        this->robotName = other.robotName;
        this->time = other.time;
        return (*this);
    }

    std::string systemVersion;  // 系统软件主版本
    std::string robotName;      // 机型名
    std::string time;           // 修改时间

} ProjectFileInfo;

/// <summary>
/// 多任务信息
/// </summary>
typedef struct _MultiTaskInfo
{
    _MultiTaskInfo()
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

    _MultiTaskInfo &operator=(const _MultiTaskInfo &other)
    {
        this->taskId = other.taskId;
        this->taskType = other.taskType;
        this->enterProgramFile = other.enterProgramFile;
        this->isActive = other.isActive;
        return (*this);
    }

    bool operator==(const _MultiTaskInfo &other) const
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

} MultiTaskInfo;

/// <summary>
/// 工程配置信息(.prj文件信息)
/// </summary>
typedef struct _ProjectInfo
{
    _ProjectInfo()
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

    _ProjectInfo &operator=(const _ProjectInfo &other)
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

    std::string fileType;                     // 文件类型
    std::string company;                      // 公司名称
    int majorVersion;                         // 文件主版本号
    int minorVersion;                         // 文件次版本号
    bool isMainActive;                        // 是否统一激活任务
    std::string mainFile;                     // 主程序文件
    int multiTaskCount;                       // 多任务数量
    int programFileCount;                     // 程序文件数量
    int robPointFileCount;                    // 位置点位文件数量
    std::vector<MultiTaskInfo> multiTaskArr;  // 多任务集合
    std::vector<string> programFileArr;       // 程序文件集合
    std::vector<string> robPointFileArr;      // 位置点位文件集合

} ProjectInfo;

/// <summary>
/// 工程文件夹信息
/// </summary>
typedef struct _ProjectFolderInfo
{
    _ProjectFolderInfo()
    {
        projectName = "";
        modifyTime = "";
        memorySize = 0;
    }

    _ProjectFolderInfo &operator=(const _ProjectFolderInfo &other)
    {
        this->projectName = other.projectName;
        this->modifyTime = other.modifyTime;
        this->memorySize = other.memorySize;
        return (*this);
    }

    bool operator==(const _ProjectFolderInfo &other)
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

} ProjectFolderInfo;

/**
 * @brief 点位对应的标签和描述信息
 */
typedef struct _PtLabelAndDes
{
    _PtLabelAndDes()
    {
        Initialize();
    }

    void Initialize()
    {
        pointIndex = -1;
        label = std::string();
        description = std::string();
    }

    _PtLabelAndDes &operator=(const _PtLabelAndDes &other)
    {
        this->pointIndex = other.pointIndex;
        this->label = other.label;
        this->description = other.description;
        return (*this);
    }

    int pointIndex;           // 对应的点位序号
    std::string label;        // 点位标签
    std::string description;  // 点位描述
} PtLabelAndDes;

/*******************标签结构体开始 ******************/
// IO类型标签
typedef struct _LabelItem
{
    int nLabelId;
    int nIndex;
    std::string sLabel;
    std::string sDescription;
    std::string sOriginalName;

    _LabelItem()
    {
        nLabelId = 0;
        nIndex = 0;
        sLabel = "";
        sDescription = "";
        sOriginalName = "";
    }

    _LabelItem &operator=(const _LabelItem &other)
    {
        this->nLabelId = other.nLabelId;
        this->nIndex = other.nIndex;
        this->sLabel = other.sLabel;
        this->sDescription = other.sDescription;
        this->sOriginalName = other.sOriginalName;
        return (*this);
    }
} LabelItem;

typedef struct _IoLabelItems
{
    int nNumberOfLabels;
    std::vector<LabelItem> LabelsArray;

    _IoLabelItems()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    void clear()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    _IoLabelItems &operator=(const _IoLabelItems &other)
    {
        this->nNumberOfLabels = other.nNumberOfLabels;
        this->LabelsArray.clear();
        this->LabelsArray.assign(other.LabelsArray.begin(), other.LabelsArray.end());
        return (*this);
    }
} IoLabelItems;

typedef struct _AllIoLabels
{
    IoLabelItems AdLabels;
    IoLabelItems DaLabels;

    IoLabelItems InputBitLabels;
    IoLabelItems OutputBitLabels;

    IoLabelItems InputByteLabels;
    IoLabelItems OutputByteLabels;

    IoLabelItems InputWordLabels;
    IoLabelItems OutputWordLabels;

    IoLabelItems BVarLabels;
    IoLabelItems RVarLabels;
    IoLabelItems DVarLabels;

    _AllIoLabels()
    {
    }

    void clear()
    {
        InputBitLabels.clear();
        OutputBitLabels.clear();
        InputByteLabels.clear();
        OutputByteLabels.clear();
        InputWordLabels.clear();
        OutputWordLabels.clear();
        AdLabels.clear();
        DaLabels.clear();
        BVarLabels.clear();
        RVarLabels.clear();
        DVarLabels.clear();
    }

    _AllIoLabels &operator=(const _AllIoLabels &other)
    {
        this->InputBitLabels = other.InputBitLabels;
        this->OutputBitLabels = other.OutputBitLabels;
        this->InputByteLabels = other.InputByteLabels;
        this->OutputByteLabels = other.OutputByteLabels;
        this->InputWordLabels = other.InputWordLabels;
        this->OutputWordLabels = other.OutputWordLabels;
        this->AdLabels = other.AdLabels;
        this->DaLabels = other.DaLabels;
        this->BVarLabels = other.BVarLabels;
        this->RVarLabels = other.RVarLabels;
        this->DVarLabels = other.DVarLabels;
        return (*this);
    }
} AllIoLabels;

/*******************标签结构体结束 ******************/

/// <summary>
/// 自定义报警
/// </summary>
struct UserDefineWaringsData
{
    std::vector<string> Warings;

    UserDefineWaringsData()
    {
        Warings.clear();
        for (int i = 0; i < 16; i++)
        {
            Warings.push_back("");
        }
    }

    UserDefineWaringsData &operator=(const UserDefineWaringsData &other)
    {
        this->Warings.clear();
        this->Warings.assign(other.Warings.begin(), other.Warings.end());
        return (*this);
    }
};

/**
 * @brief 批量改点 - 点位序号集合，最多430个序号
 */
#pragma pack(push)
#pragma pack(1)
struct ModifyPtsNo
{
    ModifyPtsNo()
    {
        initialize();
    }

    void initialize()
    {
        count = 0;
        memset(arr, 0, MAX_NUM_MODIFY_PTS_NO * sizeof(unsigned short));
    }

    ModifyPtsNo &operator=(const ModifyPtsNo &other)
    {
        this->count = other.count;
        memcpy(this->arr, other.arr, MAX_NUM_MODIFY_PTS_NO * sizeof(unsigned short));
        return (*this);
    }

    unsigned short count;                       // 点序号个数
    unsigned short arr[MAX_NUM_MODIFY_PTS_NO];  // 点序号集合
};
#pragma pack(pop)

/**
 * @brief 批量改点 - 待修改点总个数、文件名称、坐标系、偏移量
 */
#pragma pack(push)
#pragma pack(1)
struct ModifyPtsParam
{
    ModifyPtsParam()
    {
        initialize();
    }

    void initialize()
    {
        ptNumber = 0;
        memset(fileName, 0, 32 * sizeof(char));
        coord = 1;  // 默认为工件坐标系
        memset(robotOffsets, 0, POSE_AXIS_NUM * sizeof(double));
        memset(eOffsets, 0, EXT_AXIS_NUM * sizeof(double));
    }

    ModifyPtsParam &operator=(const ModifyPtsParam &other)
    {
        for (size_t i = 0; i < 32; i++)
        {
            this->fileName[i] = other.fileName[i];
        }
        this->coord = other.coord;
        memcpy(this->robotOffsets, other.robotOffsets, POSE_AXIS_NUM * sizeof(double));
        memcpy(this->eOffsets, other.eOffsets, EXT_AXIS_NUM * sizeof(double));
        return (*this);
    }

    int16u ptNumber;                     // 待修改点总个数
    char fileName[32];                   // 文件名称，带后缀
    int16u coord;                        // 坐标系，0-工具坐标系，1-工件坐标系
    double robotOffsets[POSE_AXIS_NUM];  // 机器人位置偏移量，数组长度6
    double eOffsets[EXT_AXIS_NUM];       // 外部轴位置偏移量，数组长度6
};
#pragma pack(pop)

/**
 * @brief 批量改点 - 每个点对应的偏移量
 */
#pragma pack(push)
#pragma pack(1)
struct PointOffset
{
    PointOffset()
    {
        initialize();
    }

    void initialize()
    {
        pointNo = 0;
        memset(robotOffsets, 0, POSE_AXIS_NUM * sizeof(double));
        memset(eOffsets, 0, EXT_AXIS_NUM * sizeof(double));
    }

    PointOffset &operator=(const PointOffset &other)
    {
        this->pointNo = other.pointNo;
        memcpy(this->robotOffsets, other.robotOffsets, POSE_AXIS_NUM * sizeof(double));
        memcpy(this->eOffsets, other.eOffsets, EXT_AXIS_NUM * sizeof(double));
        return (*this);
    }

    unsigned short pointNo;              // 点序号
    double robotOffsets[POSE_AXIS_NUM];  // 机器人位置偏移量，数组长度6
    double eOffsets[EXT_AXIS_NUM];       // 外部轴位置偏移量，数组长度6
};
#pragma pack(pop)

#pragma endregion

#pragma region 工程管理相关枚举定义
enum class ProjectOperateType
{
    /// <summary>
    /// 创建
    /// </summary>
    Create = 0,
    /// <summary>
    /// 删除
    /// </summary>
    Del,
    /// <summary>
    /// 重命名
    /// </summary>
    Rename,
    /// <summary>
    /// 粘贴
    /// </summary>
    Paste,
};

enum class ProjectOperateState
{
    /// <summary>
    /// 进行中
    /// </summary>
    Doing = -1,
    /// <summary>
    /// 失败
    /// </summary>
    Fail = -10,
    /// <summary>
    /// 发生异常
    /// </summary>
    Error = 0,
    /// <summary>
    /// 成功
    /// </summary>
    Success = 1,
};

enum class ProgramType
{
    /// <summary>
    /// 通用程序
    /// </summary>
    FUNCTION = 0,
    /// <summary>
    /// 入口程序
    /// </summary>
    START_END,
    /// <summary>
    /// 中断程序
    /// </summary>
    INTERRUPT,
    /// <summary>
    /// 工位预约程序
    /// </summary>
    STATIONFUNC
};

enum class LabelType
{
    /// <summary>
    /// IO输入 - bit
    /// </summary>
    IO_INPUT_BIT = 0,
    /// <summary>
    /// IO输出 - bit
    /// </summary>
    IO_OUTPUT_BIT,
    /// <summary>
    /// IO输入 - byte
    /// </summary>
    IO_INPUT_BYTE,
    /// <summary>
    /// IO输出 - byte
    /// </summary>
    IO_OUTPUT_BYTE,
    /// <summary>
    /// IO输入 - word
    /// </summary>
    IO_INPUT_WORD,
    /// <summary>
    /// IO输出 - word
    /// </summary>
    IO_OUTPUT_WORD,
    /// <summary>
    /// DA变量
    /// </summary>
    DA,
    /// <summary>
    /// AD变量
    /// </summary>
    AD,
    /// <summary>
    /// B变量
    /// </summary>
    B,
    /// <summary>
    /// R变量
    /// </summary>
    R,
    /// <summary>
    /// D变量
    /// </summary>
    D,
    /// <summary>
    /// 未知
    /// </summary>
    UNKNOWN,
};

/**
 * @brief AD/DA标签类型
 */
enum class AdDaType
{
    // IRLink
    IRLINK = 0,
    // EtherCat
    ETHERCAT = 1,
};

enum class IoType
{
    /// <summary>
    /// 标准IO
    /// </summary>
    STANDARD = 0,
    /// <summary>
    /// 从站现场IO
    /// </summary>
    SLAVE_SCENE,
    /// <summary>
    /// 主站现场IO
    /// </summary>
    MASTER_SCENE,
#ifdef COBOT
    /// <summary>
    /// 工具IO
    /// </summary>
    TOOL_SCENE,
#endif
    /// <summary>
    /// 内存IO
    /// </summary>
    MEMORY,
};

enum class IoDataType
{
    /// <summary>
    /// 比特
    /// </summary>
    BIT = 0,
    /// <summary>
    /// 字节
    /// </summary>
    BYTE,
    /// <summary>
    /// 字
    /// </summary>
    WORD,
};

enum class TaskType
{
    /// <summary>
    /// 主任务
    /// </summary>
    Main = 0,
    /// <summary>
    /// 静态任务
    /// </summary>
    Static,
    /// <summary>
    /// 动态任务
    /// </summary>
    Dynamic,
    /// <summary>
    /// Xqt任务
    /// </summary>
    Xqt,
};

/**
 * @brief 工程类型
 */
enum class ProjectType
{
    // pro工程(程序文件为.pro)
    PRO = 0,
    // lua工程(程序文件为.lua)
    LUA,
};

/**
 * @brief 工程中所有文件的操作模式
 */
enum class ProjectFileOperateMode
{
    // 需要手动从本地同步到控制器
    LOCAL_TO_CTRL = 0,
    // 操作本地文件时，同时同步到控制器
    ALWAYS_CTRL,
};

/**
 * @brief 批量改点 - 控制器处理状态
 */
enum class ModifyPtsStatus : int
{
    // 准备完成
    READY = 0,
    // 正在处理
    PROCESSING,
    // 成功
    SUCCEED,
    // 失败
    FAIL,
};

#pragma endregion

/// <summary>
/// 工程相关文件的文件头处理
/// </summary>
class INOROBBUSINESS_CLASS StrSerProjectFileInfo
{
public:
    /// <summary>
    /// 将文本解析为文件头信息
    /// </summary>
    /// <param name="content">包含文件头的文本</param>
    /// <returns>文件头信息</returns>
    static ProjectFileInfo FromStr(const std::string &content);
    /// <summary>
    /// 将文件头信息整合为文本
    /// </summary>
    /// <param name="fileInfo">文件头信息</param>
    /// <returns>文本</returns>
    static std::string ToStr(const ProjectFileInfo &fileInfo);
    /// <summary>
    /// 获取文件头在文本中的结束位置(换车换行符计算在内)
    /// </summary>
    /// <param name="content">包含文件头的文本</param>
    /// <returns>文件头结束位置，未找到则返回-1</returns>
    static int EndIndex(const std::string &content);

private:
    std::string getValue(std::string *pContent, const char *key);
    std::string appendValue(std::string content, std::string key, std::string value);
    std::string getSystemVersion(const std::string &vrcVision);

private:
    const std::string m_BeginInfo = "ProgramInfo";
    const std::string m_EndInfo = "EndProgramInfo";
    const std::string m_Indentation = "    ";  // 缩进四个空格
    const std::string m_SystemVersionKey = "Version = \"";
    const std::string m_VRCKey = "VRC = \"";
    const std::string m_TimeKey = "Time = \"";
    const std::string m_RobotNameKey = "RobotName = \"";
    const std::string m_ValueEnd = "\"";
    const std::string m_LineEnd = "\r\n";
    const std::string m_LineEnd2 = "\n";
};

/// <summary>
/// 工程管理相关方法
/// </summary>
class INOROBBUSINESS_CLASS ProjectHelper
{
public:
#pragma region 名称合法性相关
    static bool isContainsChinese(const std::string &str);
    /// <summary>
    /// 检查首字符是否是英文字母
    /// </summary>
    /// <param name="c">输入，单个字符</param>
    /// <returns>是true，否false</returns>
    static bool IsFirstCharEnglishLetter(char c);
    /// <summary>
    /// 名称组合内容是否合格(工程、程序文件、点位文件...)
    /// </summary>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    static bool IsNameCompositionValid(const std::string &name);
    /// <summary>
    /// 名称是否和系统的冲突
    /// </summary>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    static bool IsWindowsFileNameValid(const std::string &name);
    /// <summary>
    /// 检查名称是否合法，全面的检查
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="name">输入，名称</param>
    /// <param name="maxLength">输入，长度限制</param>
    /// <returns>是true，否false</returns>
    static bool IsNameValid(std::string &errMsg, const std::string &name, int maxLength);
    /// <summary>
    /// 检查工程(配置文件)名称是否合法，全面的检查
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    static bool IsProjectFileNameValid(std::string &errMsg, const std::string &name);
    /// <summary>
    /// 检查程序文件名称是否合法，全面的检查
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    static bool IsProgramFileNameValid(std::string &errMsg, const std::string &name);
    /// <summary>
    /// 检查点位文件名称是否合法，全面的检查
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    static bool IsPointFileNameValid(std::string &errMsg, const std::string &name);
    /**
     * @brief 检查标签名称是否合法
     * @param errMsg 输出，错误信息
     * @param name 输入，标签名称
     * @return 是true，否false
     */
    static bool isLabelValid(std::string &errMsg, const std::string &label);
    /**
     * @brief 检查点位的备注信息是否合法
     * @param errMsg 输出，错误信息
     * @param description 输入，备注信息
     * @param maxLength 允许的最大长度
     * @return 是true，否false
     */
    static bool isPointDescriptionValid(std::string &errMsg, const std::string &description, int &maxLength);
    /**
     * @brief 检查标签的备注信息是否合法（AD/DA、IO、BRD标签）
     * @param errMsg 输出，错误信息
     * @param description 输入，备注信息
     * @param maxLength 允许的最大长度
     * @return 是true，否false
     */
    static bool isLabelDescriptionValid(std::string &errMsg, const std::string &description, int &maxLength);
    /**
     * @brief 检查备注长度是否合法
     * @param errMsg 输出，错误信息
     * @param description 输入，备注信息
     * @param maxLength 允许的最大长度
     * @return 是true，否false
     */
    static bool isDescriptionLengthValid(std::string &errMsg, const std::string &description, int &maxLength);

    /**
     * @brief 检查自定义报警是否合法
     * @param errMsg 输出，错误信息
     * @param description 输入，自定义报警信息
     * @return 是true，否false
     */
    static bool isUserDefineWarningValid(std::string &errMsg, const std::string &description);

      /**
     * @brief 判断是否为本地IP地址
     * @param ip IP地址字符串
     * @return true-本地地址，false-远程地址
     */
    static bool IsLocalAddress(const std::string &ip);

#pragma endregion

#pragma region 路径相关
    /// <summary>
    /// 获取本地放置工程文件夹的文件夹路径
    /// </summary>
    static std::string LocalTeachProgramFolder();


    /// <summary>
    /// 获取本地放置虚拟工程文件夹的文件夹路径
    /// </summary>
    static std::string LocalTeachProgramVirtualFolder();
    static std::string LocalTeachProgramVirtualFolder(const std::string &name);

    /// <summary>
    /// 获取加载工程的本地文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string LocalProjectFolder(const std::string &name);
    /**
     * @brief 本地临时路径
     */
    static std::string LocalTempFolder();
    /// <summary>
    /// 获取加载工程的控制器文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string ControllerProjectFolder(const std::string &name);
    /// <summary>
    /// 获取虚拟控制器SDCard路径
    /// </summary>
    static std::string VirtualControllerSDCardFolder();
    /// <summary>
    /// 获取加载工程的虚拟控制器文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string VirtualControllerProjectFolder(const std::string &name);
    /// <summary>
    /// 获取控制器当前激活工程的文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string ControllerActiveProjectFolder(const std::string &name);
    /// <summary>
    /// 获取加载工程Data文件夹的本地文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string LocalDataFolder(const std::string &name);
    /// <summary>
    /// 获取加载工程Data文件夹的控制器文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string ControllerDataFolder(const std::string &name);
    /// <summary>
    /// 获取加载工程Data文件夹的控制器文件夹路径
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    static std::string VirtualControllerDataFolder(const std::string &name);

#pragma endregion

#pragma region 工程整体相关
    /// <summary>
    /// 通知控制器创建指定名称的新工程
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <param name="type">输入，工程类型，0-pro，1-lua</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int WriteCreateNewProject(const std::string &name, const char type);
    /// <summary>
    /// 从控制器读取操作工程的状态
    /// </summary>
    /// <param name="state">输出，状态(-1：进行中，-10：失败，1：成功，0：缺省(发生异常))</param>
    /// <param name="type">输入，操作类型(0：新增，1：删除，2：重命名，3：粘贴)</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ReadProjectOperateState(int16s &state, int16u type);
    /// <summary>
    /// 通知控制器删除指定名称的工程
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int WriteDeleteProject(const std::string &name);
    /// <summary>
    /// 通知控制器重命名指定名称的工程
    /// </summary>
    /// <param name="oldName">输入，原名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int WriteRenameProject(const std::string &oldName, const std::string &newName);
    /// <summary>
    /// 通知控制器粘贴指定名称的工程
    /// </summary>
    /// <param name="srcName">输入，源工程名称</param>
    /// <param name="destName">输入，目标工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int WritePasteProject(const std::string &srcName, const std::string &destName);
    /// <summary>
    /// 设置控制器当前激活的工程
    /// </summary>
    /// <param name="name">输入，工程所在的控制器路径</param>
    /// <param name="softwareType">输入，软件平台类型（区分示教器和PC编程平台，暂时无用）</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int writeActiveProject(const std::string &ctrlPath, char softwareType = '1');
    /// <summary>
    /// 读取控制器中当前激活工程的文件夹路径
    /// </summary>
    /// <param name="ctrlPath">输出，工程所在的控制器文件夹路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int readActiveProjectDir(std::string &ctrlPath);

#pragma endregion

#pragma region 点位文件解析
    /// <summary>
    /// 从所有文本内容中，根据分隔符，提取一段文本(从起始位置开始到分隔符位置)，原输入的字符串中将剔除这段被提取的文本
    /// </summary>
    /// <param name="text">[输出] 提取到的字符串</param>
    /// <param name="content">[输入输出] 总的文本字符串</param>
    /// <param name="separator">[输入] 分隔符</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelOneLine(std::string &line, std::string &content, const std::string &separator = "\n");
    /// <summary>
    /// 处理提取出来的单行文本，剔除空格和指定的字符
    /// </summary>
    /// <param name="line">[输入] 单行文本</param>
    /// <returns>成功true,失败false</returns>
    static bool DealOneLine(std::string &line);
    /// <summary>
    /// 获取点位序号
    /// </summary>
    /// <param name="line">[输入输出] 单行文本</param>
    /// <param name="index">[输出] 点位序号</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelPointIndex(std::string &line, int &index);
    /// <summary>
    /// 获取位置点位数据
    /// </summary>
    /// <param name="line">[输入输出] 单行文本</param>
    /// <param name="point">[输出] 点位数据</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelRobPoint(std::string &line, RobPos &point);
    /// <summary>
    /// 获取关节点位数据
    /// </summary>
    /// <param name="line">[输入输出] 单行文本</param>
    /// <param name="point">[输出] 点位数据</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelJPoint(std::string &line, JPos &point);
    /// <summary>
    /// 获取点位标签
    /// </summary>
    /// <param name="line">[输入输出] 单行文本</param>
    /// <param name="point">[输出] 点位标签</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelLabel(std::string &line, std::string &label);
    /// <summary>
    /// 获取点位描述(注意！描述需要为单行的最后一项)
    /// </summary>
    /// <param name="line">[输入输出] 单行文本</param>
    /// <param name="point">[输出] 点位描述</param>
    /// <returns>成功true,失败false</returns>
    static bool PeelDescription(std::string &line, std::string &des);
    /// <summary>
    /// 获取指定位置之间的字符串，并转化为整型返回
    /// </summary>
    /// <param name="text">[输入] 字符串</param>
    /// <param name="index1">[输入] 位置序号1，包含序号对应的字符</param>
    /// <param name="index2">[输入] 位置序号2(要大于序号1)，不包含序号对应的字符</param>
    /// <returns>整型数值</returns>
    static int GetIntNum(const std::string &text, size_t index1, size_t index2);
    /// <summary>
    /// 获取指定位置之间的字符串，并转化为浮点型返回
    /// </summary>
    /// <param name="text">[输入] 字符串</param>
    /// <param name="index1">[输入] 位置序号1，包含序号对应的字符</param>
    /// <param name="index2">[输入] 位置序号2(要大于序号1)，不包含序号对应的字符</param>
    /// <returns>浮点型数值</returns>
    static double GetDoubleNum(const std::string &text, size_t index1, size_t index2);
    /// <summary>
    /// 从指定的序号开始，截取字符串在该序号往后的所有字符串
    /// </summary>
    /// <param name="text">[输入] 字符串</param>
    /// <param name="index">[输入] 位置序号，包含序号对应的字符</param>
    /// <returns>截取到的字符串</returns>
    static std::string SubRight(const std::string &text, size_t index);
    /// <summary>
    /// 将位置类型点位数据整合为一行文本，按照点位文件中的格式
    /// </summary>
    /// <param name="line">输出，一行文本</param>
    /// <param name="pos">输入，点位数据</param>
    /// <param name="isGlobal">输入，是否全局点位，是为P，不是为LP</param>
    /// <returns>成功true,失败false</returns>
    static void RPointToStr(std::string &line, const MRobPosItem &pos, bool isGlobal = true);
    /// <summary>
    /// 将关节类型点位数据整合为一行文本，按照点位文件中的格式
    /// </summary>
    /// <param name="line">输出，一行文本</param>
    /// <param name="pos">输入，点位数据</param>
    /// <returns>成功true,失败false</returns>
    static void JPointToStr(std::string &line, const MJPosItem &pos);
#pragma endregion

#pragma region FTP相关操作
    /// <summary>
    /// 从控制器读取工程列表
    /// </summary>
    /// <param name="infos">输出，工程文件夹信息合集</param>
    /// <param name="ip">输入，控制器ip</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int ReadProjectList(std::vector<ProjectFolderInfo> &infos, const std::string &ip);

        /**
     * @brief 从本地文件系统读取工程列表
     * @param infos 输出，工程文件夹信息合集
     * @return 成功返回0，其他请见错误码
     */
    static int ReadProjectListFromLocal(std::vector<ProjectFolderInfo> &infos);
    /// <summary>
    /// 在控制器中创建工程目录
    /// </summary>
    /// <param name="ip">输出，控制器ip</param>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int CreateProjectDirectory(const std::string &ip, const std::string &name);
    /// <summary>
    /// 控制器中是否存在指定名称的工程
    /// </summary>
    /// <param name="isExisted">输出，存在true，不存在false</param>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int IsProjectExisted(bool &isExisted, const std::string &ip, const std::string &name);
    /// <summary>
    /// 从控制器下载工程到本地
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    /// <param name="name">输入，工程名称</param>
    /// <param name="folder">输入，本地路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int DownloadProject(const std::string &ip, const std::string &name, const std::string &folder);

    /**
     * @brief 从本地文件系统复制工程到目标文件夹
     * @param name 工程名称
     * @param folder 目标文件夹路径
     * @return 成功返回0，其他请见错误码
     */
    static int CopyProjectFromLocal(const std::string &name, const std::string &folder);
    /// <summary>
    /// 向控制器下发单个文件
    /// </summary>
    /// <param name="localPath">输入，本地路径</param>
    /// <param name="ctrlPath">输入，控制器路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int PutFileToController(const std::string &ip, const std::string &localPath, const std::string &ctrlPath);
    /// <summary>
    /// 向控制器下发多个文件
    /// </summary>
    /// <param name="localPaths">输入，本地路径集合</param>
    /// <param name="ctrlPaths">输入，控制器路径集合</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int PutFilesToController(const std::string &ip, const std::vector<std::string> &localPaths, const std::vector<std::string> &ctrlPaths);
    /// <summary>
    /// 删除控制器中的单个文件
    /// </summary>
    /// <param name="path">输入，控制器路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int DelFileInController(const std::string &ip, const std::string &path);
    /// <summary>
    ///  控制器中是否存在对应的文件
    /// </summary>
    /// <param name="path">输入，查询文件在控制器的目录</param>
    /// <param name="fileName">输入，查询的文件名</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int IsFileInController(const std::string &ip, const std::string &path, const std::string &fileName);
    /// <summary>
    /// 删除控制器中的多个文件
    /// </summary>
    /// <param name="path">输入，控制器路径合集</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int DelFilesInController(const std::string &ip, const std::vector<std::string> &paths);
    /// <summary>
    /// 重命名控制器文件
    /// </summary>
    /// <param name="oldPath">输入，控制器旧路径</param>
    /// <param name="newPath">输入，控制器新路径</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    static int RenameFileInController(const std::string &ip, const std::string &oldPath, const std::string &newPath);

#pragma endregion
};
