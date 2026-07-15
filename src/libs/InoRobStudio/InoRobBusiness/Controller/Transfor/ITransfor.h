#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "../../Project/IProject.h"
#include "../../Controller/Task/ITask.h"
#include "../../third_party/include/instruction/GlobalsData.h"
#ifdef TRANSFOR_WIN32
    #include "Interpreter.h"
    #include "../../third_party/include/instruction/CmdForInoRobotLab.h"
#endif  // TRANSFOR_WIN32

/*
    Create by LiaoChuanMing at 2023/11/13，译码库接口
*/
namespace InoRobBusiness
{

#pragma region 常量与数据类型

/// <summary>
/// 译码状态
/// </summary>
enum class ParseStatus
{
    /// <summary>
    /// 未知
    /// </summary>
    PARSE_UNKNOW = -99,
    /// <summary>
    /// 部分工程文件未找到
    /// </summary>
    PARSE_PROGRAM_UNFOUND = -3,
    /// <summary>
    /// .prj文件名称与工程文件夹名称不匹配
    /// </summary>
    PARSE_PRJ_UNMATCH = -2,
    /// <summary>
    /// 解析出错
    /// </summary>
    PARSE_ERR = -1,
    /// <summary>
    /// 解析中
    /// </summary>
    PARSE_BUSY = 0,
    /// <summary>
    /// 解析完成
    /// </summary>
    PARSE_FINISHI = 1,
};

enum class ParseDemand
{
    /// <summary>
    /// 不需要译码
    /// </summary>
    NOT_NEED = 0,
    /// <summary>
    /// 需要译码
    /// </summary>
    NEED,
};

/// <summary>
/// 译码类型
/// </summary>
enum class SyncProjcetInfoType
{
    /// <summary>
    /// 工程配置文件信息（包括静态任务）
    /// </summary>
    SYNC_PROJECT_INFO = 0,  // 工程配置文件信息(包括静态任务)
    /// <summary>
    /// 程序文件
    /// </summary>
    SYNC_PROGRAM_FILES,  // 程序文件
    /// <summary>
    /// 全局P点位
    /// </summary>
    SYNC_GOBAL_POINT,  // 全局P点位
    /// <summary>
    /// 全局JP点位
    /// </summary>
    SYNC_GOBAL_JPOINT,  // 全局JP点位
    /// <summary>
    /// 标签信息
    /// </summary>
    SYNC_LABEL_INFO,  // 标签信息
    /// <summary>
    /// 用户自定义报警
    /// </summary>
    SYNC_USER_DEFINE_WARNING,  // 用户自定义报警
    /// <summary>
    /// 插件修改编译
    /// </summary>
    SYNC_PLUGIN,  // 插件修改编译
    /// <summary>
    /// 工位配置
    /// </summary>
    SYNC_STATION, // 工位配置
    /// <summary>
    /// 程序是否译码，0-不编译，1-非静态任务编译（示教器编程切调试/自动，全部保存），2-全部编译
    /// </summary>
    SYNC_PROGRAM_COMPILE = 15,
};

/// <summary>
/// function函数参数的类型
/// </summary>
enum class FunctionParamType
{
    /// <summary>
    /// 布尔型
    /// </summary>
    BOOL = 0,
    /// <summary>
    /// 字节型
    /// </summary>
    BYTE,
    /// <summary>
    /// 整型
    /// </summary>
    INT,
    /// <summary>
    /// 单精度浮点型
    /// </summary>
    FLOAT,
    /// <summary>
    /// 双精度浮点型
    /// </summary>
    DOUBLE,
    /// <summary>
    /// curve曲线数据类型
    /// </summary>
    CURVE,
    /// <summary>
    /// 未知类型
    /// </summary>
    UNKNOW,
};

struct FunctionInfo
{
    FunctionInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        name = std::string();
        paramTypes.clear();
        paramNames.clear();
    }

    FunctionInfo &operator=(const FunctionInfo &other)
    {
        this->name = other.name;
        this->paramTypes = other.paramTypes;
        this->paramNames = other.paramNames;
        return (*this);
    }

    std::string name;                           // 函数方法名称
    std::vector<FunctionParamType> paramTypes;  // 函数方法具有的参数类型集合
    std::vector<std::string> paramNames;        // 函数方法具有的参数名称集合
};

/// <summary>
/// 译码内容类型数量，表示有几种类型
/// </summary>
#define SYNC_TYPE_NUMBER 16

// 解决非示教器2.0的编译问题，剥离开译码库
#ifndef TRANSFOR_WIN32
#ifndef COBOT
// 工程信息
typedef struct PROJECT_INFO
{
    unsigned int iErrorNum;  // 错误总个数
    unsigned int iProNum;    // 程序文件数
    char prjFileName[32];    // 工程配置prj文件名称
} Project_Info;

typedef struct PRASE_INFO
{
    unsigned int iErrorNum;  // 是否有语法报错
    unsigned int iLineNum;   // 程序总行数
} PraseInfo;
#endif
#endif  // !TRANSFOR_WIN32

#pragma endregion 常量与数据类型

class INOROBBUSINESS_CLASS ITransfor : public QObject
{
    Q_OBJECT

public:
    virtual ~ITransfor()
    {
    }

    /// <summary>
    /// 初始化译码库
    /// </summary>
    virtual void initParseDll(IProject *pProject) = 0;
    /// <summary>
    /// 设置机器人信息
    /// </summary>
    /// <param name="axisNum">输入，轴数</param>
    /// <param name="robotName">输入，机器人名称</param>
    virtual void setRobotInformation(uint axisNum, const std::string &robotName) = 0;
    /// <summary>
    /// 编译工程
    /// </summary>
    /// <param name="taskFilePaths">输入，任务相关程序文件路径集合</param>
    /// <param name="pInfo">输出，编译结果信息</param>
    virtual bool parseProject(const std::string taskFilePaths[MAX_TASK_NUM], Project_Info *pInfo) = 0;
    /// <summary>
    /// 编译单个程序文件
    /// </summary>
    /// <param name="taskFilePath">输入，程序文件路径集合</param>
    /// <param name="pInfo">输出，编译结果信息</param>
    virtual bool parseProgram(const std::string &taskFilePath, PraseInfo *pInfo) = 0;
    /// <summary>
    /// 编译临时程序文件（不属于任何任务的公共程序文件）
    /// </summary>
    /// <param name="programFilePath">输入，程序文件路径</param>
    /// <param name="proArr">输入，程序文件对应的程序文本集合</param>
    virtual bool parseTempProgram(const string &programFilePath, std::vector<std::string> &proArr) = 0;

    /// <summary>
    /// 通知控制器译码
    /// </summary>
    /// <param name="ctrlPath">输入，当前激活的工程路径</param>
    /// <param name="flags">输入，各类文件是否需要译码的状态以及整体的译码状态，对应枚举SyncProjcetInfoType</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int syncProjectInfo(std::string ctrlPath, signed char flags[SYNC_TYPE_NUMBER]) = 0;
    /// <summary>
    /// 读取控制器的译码状态
    /// </summary>
    /// <param name="flag">输出，控制器译码状态</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int readCtrlProjectParseFlag(ParseStatus &flag) = 0;
    /// <summary>
    /// 等待控制器译码结束并获取译码结果
    /// </summary>
    /// <returns>true-成功，false-失败</returns>
    virtual bool waitForCtrlParseResult() = 0;
    /// <summary>
    /// 读取控制器是否需要执行译码
    /// </summary>
    /// <param name="flag">输出，控制器是否需要译码的状态</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int readCtrlProjectNeedTrans(ParseDemand &flag) = 0;

    /// <summary>
    /// 检查代码行是否正确
    /// </summary>
    virtual bool isTrueLine(std::string cmdString) = 0;

    virtual void getStmtNote(std::string cmdString, STMT_NOTE **pStmt) = 0;

    /**
     * @brief 通过变量名获取变量值类型及范围
     * @param varName 变量名
     * @param[out] range 范围
     * @return 值类型
     */
    virtual ValueKind getVarValueKindAndRangeForRobotLab(char *varName, double range[2]) = 0;

    /**
     * @brief 清除变量监控Table缓存
     */
    virtual void clearLineVarTable() = 0;

    /**
     * @brief 更新指定程序文件中，指定行的所有变量信息
     *        影响getSelectedLineVarInfos函数
     * @param 程序文件名称(可带后缀也可不带后缀)
     * @param 指定的程序文件中的行号
     * @param 程序文件所属的任务id
     * @return true成功 false失败
     */
    virtual bool updateLineVarInfos(const std::string &proFileName, int lineNo, int taskId) = 0;

    /**
     * @brief 获取选中行的变量信息
     * @return
     */
    virtual std::vector<VarInLineInfo_stu> getSelectedLineVarInfos() = 0;

    /**
     * @brief 获取指令中的点位信息
     * @param programFileName 输入，程序文件名称（不带后缀）
     * @param lineNo 输入，当前选中的程序行号
     * @param pointType 输出，点位类型
     * @param pointNo 输出，点位序号
     * @param toolNo 输出，指令中指定的工具号
     * @param wobjNo 输出，指令中指定的工件号
     * @return true-成功获取到了点位信息，false-没有获取到点位信息
     */
    virtual bool getCmdPointInfo(const std::string &programFileName, int lineNo,
                                 PointType &pointType, int &pointNo, int &toolNo, int &wobjNo) = 0;

    /**
     * @brief 清除所有缓存数据，如变量、函数名等
     */
    virtual void clearAllTable() = 0;
    /// <summary>
    /// 更新指定程序文件中，在指定行之前的所有变量名称信息
    /// 影响以下获取变量名称的函数：
    /// getAllVarNames、getGlobalVarNames、getLocalVarNames
    /// getModuleVarNames、getModuleNames
    /// getStringVarNames、getBoolVarNames、getByteVarNames、getIntVarNames、getFloatVarNames、getDoubleVarNames
    /// getStructVarNames、getStructNames
    /// getSpeedNames、getCurveVarNames
    /// </summary>
    /// <param name="proFileName">输入，程序文件名称(可带后缀也可不带后缀)</param>
    /// <param name="curLineNo">输入，指定的程序文件中的行号</param>
    /// <param name="forceRefresh">输入，是否强制触发译码库刷新。
    /// 如果不强制刷新，则译码库会在某些条件触发后进行刷新</param>
    virtual void updateVarNames(const std::string &proFileName, int lineNo, bool forceRefresh) = 0;
    /// <summary>
    /// 获取所有变量的名称
    /// </summary>
    virtual std::vector<std::string> getAllVarNames() = 0;
    /// <summary>
    /// 获取全局变量的名称
    /// </summary>
    virtual std::vector<std::string> getGlobalVarNames() = 0;
    /// <summary>
    /// 获取局部变量的名称
    /// </summary>
    virtual std::vector<std::string> getLocalVarNames() = 0;
    /// <summary>
    /// 获取模块变量的名称
    /// </summary>
    virtual std::vector<std::string> getModuleVarNames() = 0;
    /// <summary>
    /// 获取模块的名称
    /// </summary>
    virtual std::vector<std::string> getModuleNames() = 0;
    /// <summary>
    /// 获取字符串变量的名称
    /// </summary>
    virtual std::vector<std::string> getStringVarNames() = 0;
    /// <summary>
    /// 获取布尔变量的名称
    /// </summary>
    virtual std::vector<std::string> getBoolVarNames() = 0;
    /// <summary>
    /// 获取Byte变量的名称
    /// </summary>
    virtual std::vector<std::string> getByteVarNames() = 0;
    /// <summary>
    /// 获取整型变量的名称
    /// </summary>
    virtual std::vector<std::string> getIntVarNames() = 0;
    /// <summary>
    /// 获取单精度浮点型变量的名称
    /// </summary>
    virtual std::vector<std::string> getFloatVarNames() = 0;
    /// <summary>
    /// 获取双精度浮点型变量的名称
    /// </summary>
    virtual std::vector<std::string> getDoubleVarNames() = 0;
    /// <summary>
    /// 获取结构体变量的名称
    /// </summary>
    virtual std::vector<std::string> getStructVarNames() = 0;
    /// <summary>
    /// 获取结构体的名称
    /// </summary>
    virtual std::vector<std::string> getStructNames() = 0;
    /// <summary>
    /// 获取speed变量的名称
    /// </summary>
    virtual std::vector<std::string> getSpeedNames() = 0;
    /// <summary>
    /// 获取数组变量的名称
    /// </summary>
    virtual std::vector<ArrayVarInfo_stu> getArrayVarNames() = 0;
    /// <summary>
    /// 获取Curve曲线变量名
    /// </summary>
    virtual std::vector<std::string> getCurveVarNames() = 0;

    virtual std::vector<std::string> getFileHandleVarNames() = 0;
    virtual std::vector<std::string> getFileDirHandleVarNames() = 0;

    /// <summary>
    /// 获取结构体信息
    /// </summary>
    virtual std::map<std::string, int> getStructInfos() = 0;

    /// <summary>
    /// 获取方法信息
    /// </summary>
    virtual std::vector<SyntaxInfo> getFunctionInfos(const std::string &module, const std::string &filePath = "") = 0;
    virtual std::vector<FunctionInfo> getFunctionParamTypes() = 0;
    /// <summary>
    /// 获取Curve曲线组
    /// </summary>
    virtual std::vector<SyntaxInfo> getCurveInfos() = 0;
    virtual std::vector<FunctionInfo> getCurveParamTypes() = 0;
    /**
     * @brief 缩进检查
     */
    virtual PraseALineInfo *praseLineDegree(const std::string &cmdstring) = 0;

    /**
     * @brief 向译码库添加标签名称信息
     * @param labelName 输入，标签名称
     * @param realName 输入，原始名称，如P[000]
     */
    virtual void addLabel(const std::string &labelName, const std::string &realName) = 0;
    /**
     * @brief 刷新译码库中的标签信息
     */
    virtual void refreshLabels() = 0;
    /**
     * @brief 清空译码库中的标签信息
     */
    virtual void clearLables() = 0;

    /**
     * @brief 判断字符串是否为关键字
     * @param str 输入，想要判断的字符串
     */
    virtual bool isKeyWord(const std::string &str) = 0;

    /**
     * @brief 设置是否打印译码库的信息
     */
    virtual void setPrintSwitch(bool isPrint) = 0;

    /**
     * @brief 获得程序文件的行数
     * @param pNowModelName 模块名
     * @param lineNum 行数
     */
    virtual bool getLineNumFromModeName(const std::string &pNowModelName, int &lineNum) = 0;

    /**
     * @brief 识别运动指令中的工具工件号
     * @param pNowModelName 模块名
     * @param lineNo 行号
     * @param pointType 点类型
     * @param pointLeftNo 返回范围左侧点号
     * @param pointRightNo 返回范围右侧点号
     * @param wobjNo 工件号
     * @param toolNo 工具号
     */
    virtual bool getCmdPointInfoTW(const std::string &pNowModelName, int lineNo,
                                   int &pointType, int &pointLeftNo, int &pointRightNo, int &wobjNo, int &toolNo) = 0;

    /**
     * @brief 获取某一个任务对应的所有程序名，不带路径以及后缀
     * @param TaskNo  任务号
     * @param pProName 模块名称数组
     * @return 程序文件数量
     */
    virtual int getTaskAllProName(int TaskNo, std::string pProName[MAX_QUE_SIZE]) = 0;

    /**
     * @brief 译码库是否正在执行处理，因为译码库滥用全局变量，线程不安全，同时调用接口的时候会触发崩溃
     */
    virtual bool isTransforWorking() = 0;

    /**
     * @brief 是否可以设置启动行
     */
    virtual int isCanSetRunLineNo(const std::string &pNowModelName, int lineNo) = 0;
};
}  // namespace InoRobBusiness
