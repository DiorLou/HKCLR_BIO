#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../Project/Project_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

/// <summary>
/// 译码状态
/// </summary>
enum class ParseStatus_V1
{
    /// <summary>
    /// 未知
    /// </summary>
    PARSE_UNKNOW_V1 = -99,
    /// <summary>
    /// 部分工程文件未找到
    /// </summary>
    PARSE_PROGRAM_UNFOUND_V1 = -3,
    /// <summary>
    /// .prj文件名称与工程文件夹名称不匹配
    /// </summary>
    PARSE_PRJ_UNMATCH_V1 = -2,
    /// <summary>
    /// 解析出错
    /// </summary>
    PARSE_ERR_V1 = -1,
    /// <summary>
    /// 解析中
    /// </summary>
    PARSE_BUSY_V1 = 0,
    /// <summary>
    /// 解析完成
    /// </summary>
    PARSE_FINISHI_V1 = 1,
};

enum class ParseDemand_V1
{
    /// <summary>
    /// 不需要译码
    /// </summary>
    NOT_NEED_V1 = 0,
    /// <summary>
    /// 需要译码
    /// </summary>
    NEED_V1,
};

/// <summary>
/// 译码类型
/// </summary>
enum class SyncProjcetInfoType_V1
{
    /// <summary>
    /// 工程配置文件信息（包括静态任务）
    /// </summary>
    SYNC_PROJECT_INFO_V1 = 0,  // 工程配置文件信息(包括静态任务)
    /// <summary>
    /// 程序文件
    /// </summary>
    SYNC_PROGRAM_FILES_V1,  // 程序文件
    /// <summary>
    /// 全局P点位
    /// </summary>
    SYNC_GOBAL_POINT_V1,  // 全局P点位
    /// <summary>
    /// 全局JP点位
    /// </summary>
    SYNC_GOBAL_JPOINT_V1,  // 全局JP点位
    /// <summary>
    /// 标签信息
    /// </summary>
    SYNC_LABEL_INFO_V1,  // 标签信息
    /// <summary>
    /// 用户自定义报警
    /// </summary>
    SYNC_USER_DEFINE_WARNING_V1,  // 用户自定义报警
    /// <summary>
    /// 插件修改编译
    /// </summary>
    SYNC_PLUGIN_V1,  // 插件修改编译
    /// <summary>
    /// 程序是否译码，0-不编译，1-非静态任务编译（示教器编程切调试/自动，全部保存），2-全部编译
    /// </summary>
    SYNC_PROGRAM_COMPILE_V1 = 15,
};

/// <summary>
/// function函数参数的类型
/// </summary>
enum class FunctionParamType_V1
{
    /// <summary>
    /// 布尔型
    /// </summary>
    BOOL_V1 = 0,
    /// <summary>
    /// 字节型
    /// </summary>
    BYTE_V1,
    /// <summary>
    /// 整型
    /// </summary>
    INT_V1,
    /// <summary>
    /// 单精度浮点型
    /// </summary>
    FLOAT_V1,
    /// <summary>
    /// 双精度浮点型
    /// </summary>
    DOUBLE_V1,
    /// <summary>
    /// curve曲线数据类型
    /// </summary>
    CURVE_V1,
    /// <summary>
    /// 未知类型
    /// </summary>
    UNKNOW_V1,
};

struct FunctionInfo_V1
{
    FunctionInfo_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        name = std::string();
        paramTypes.clear();
        paramNames.clear();
    }

    FunctionInfo_V1 &operator=(const FunctionInfo_V1 &other)
    {
        this->name = other.name;
        this->paramTypes = other.paramTypes;
        this->paramNames = other.paramNames;
        return (*this);
    }

    std::string name;                              // 函数方法名称
    std::vector<FunctionParamType_V1> paramTypes;  // 函数方法具有的参数类型集合
    std::vector<std::string> paramNames;           // 函数方法具有的参数名称集合
};

/// <summary>
/// 译码内容类型数量，表示有几种类型
/// </summary>
#define SYNC_TYPE_NUMBER_V1 16

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Transfor_V1
{
#pragma region 构造与析构

private:
    ITransfor *_transfor = nullptr;

public:
    Transfor_V1(ITransfor *transfor);
    ~Transfor_V1();

#pragma endregion

#pragma region 数据转换

public:
    static ParseStatus_V1 ParseStatus_ToProxy(ParseStatus parseStatus);
    static ParseStatus ParseStatus_FromProxy(ParseStatus_V1 parseStatus_V1);

    static ParseDemand_V1 ParseDemand_ToProxy(ParseDemand parseDemand);
    static ParseDemand ParseDemand_FromProxy(ParseDemand_V1 parseDemand_V1);

    static SyncProjcetInfoType_V1 SyncProjcetInfoType_ToProxy(SyncProjcetInfoType syncProjcetInfoType);
    static SyncProjcetInfoType SyncProjcetInfoType_FromProxy(SyncProjcetInfoType_V1 syncProjcetInfoType_V1);

    static FunctionParamType_V1 FunctionParamType_ToProxy(FunctionParamType functionParamType);
    static FunctionParamType FunctionParamType_FromProxy(FunctionParamType_V1 functionParamType_V1);

    static bool FunctionInfo_ToProxy(const FunctionInfo &functionInfo, FunctionInfo_V1 &functionInfo_V1);
    static bool FunctionInfo_FromProxy(const FunctionInfo_V1 &functionInfo_V1, FunctionInfo &functionInfo);

#pragma endregion

#pragma region 业务逻辑

public:
    /// <summary>
    /// 初始化译码库
    /// </summary>
    // void initParseDll(IProject *pProject);
    /// <summary>
    /// 设置机器人信息
    /// </summary>
    /// <param name="axisNum">输入，轴数</param>
    /// <param name="robotName">输入，机器人名称</param>
    void setRobotInformation(uint axisNum, const std::string &robotName);
    /// <summary>
    /// 编译工程
    /// </summary>
    /// <param name="taskFilePaths">输入，任务相关程序文件路径集合</param>
    /// <param name="pInfo">输出，编译结果信息</param>
    // bool parseProject(const std::string taskFilePaths[MAX_TASK_NUM], Project_Info *pInfo);
    /// <summary>
    /// 编译单个程序文件
    /// </summary>
    /// <param name="taskFilePath">输入，程序文件路径集合</param>
    /// <param name="pInfo">输出，编译结果信息</param>
    // bool parseProgram(const std::string &taskFilePath, PraseInfo *pInfo);
    /// <summary>
    /// 编译临时程序文件（不属于任何任务的公共程序文件）
    /// </summary>
    /// <param name="programFilePath">输入，程序文件路径</param>
    /// <param name="proArr">输入，程序文件对应的程序文本集合</param>
    bool parseTempProgram(const string &programFilePath, std::vector<std::string> &proArr);

    /// <summary>
    /// 通知控制器译码
    /// </summary>
    /// <param name="ctrlPath">输入，当前激活的工程路径</param>
    /// <param name="flags">输入，各类文件是否需要译码的状态以及整体的译码状态，对应枚举SyncProjcetInfoType</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int syncProjectInfo(std::string ctrlPath, signed char flags[SYNC_TYPE_NUMBER_V1]);
    /// <summary>
    /// 读取控制器的译码状态
    /// </summary>
    /// <param name="flag">输出，控制器译码状态</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int readCtrlProjectParseFlag(ParseStatus_V1 &flag);
    /// <summary>
    /// 等待控制器译码结束并获取译码结果
    /// </summary>
    /// <returns>true-成功，false-失败</returns>
    bool waitForCtrlParseResult();
    /// <summary>
    /// 读取控制器是否需要执行译码
    /// </summary>
    /// <param name="flag">输出，控制器是否需要译码的状态</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int readCtrlProjectNeedTrans(ParseDemand_V1 &flag);

    /// <summary>
    /// 检查代码行是否正确
    /// </summary>
    bool isTrueLine(std::string cmdString);

    // void getStmtNote(std::string cmdString, STMT_NOTE **pStmt);

    /**
     * @brief 通过变量名获取变量值类型及范围
     * @param varName 变量名
     * @param[out] range 范围
     * @return 值类型
     */
    // ValueKind getVarValueKindAndRangeForRobotLab(char *varName, double range[2]);

    /**
     * @brief 清除变量监控Table缓存
     */
    void clearLineVarTable();

    /**
     * @brief 更新指定程序文件中，指定行的所有变量信息
     *        影响getSelectedLineVarInfos函数
     * @param 程序文件名称(可带后缀也可不带后缀)
     * @param 指定的程序文件中的行号
     * @param 程序文件所属的任务id
     * @return true成功 false失败
     */
    bool updateLineVarInfos(const std::string &proFileName, int lineNo, int taskId);

    /**
     * @brief 获取选中行的变量信息
     * @return
     */
    // std::vector<VarInLineInfo_stu> getSelectedLineVarInfos();

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
    bool getCmdPointInfo(const std::string &programFileName, int lineNo,
                         PointType_V1 &pointType, int &pointNo, int &toolNo, int &wobjNo);

    /**
     * @brief 清除所有缓存数据，如变量、函数名等
     */
    void clearAllTable();
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
    void updateVarNames(const std::string &proFileName, int lineNo, bool forceRefresh);
    /// <summary>
    /// 获取所有变量的名称
    /// </summary>
    std::vector<std::string> getAllVarNames();
    /// <summary>
    /// 获取全局变量的名称
    /// </summary>
    std::vector<std::string> getGlobalVarNames();
    /// <summary>
    /// 获取局部变量的名称
    /// </summary>
    std::vector<std::string> getLocalVarNames();
    /// <summary>
    /// 获取模块变量的名称
    /// </summary>
    std::vector<std::string> getModuleVarNames();
    /// <summary>
    /// 获取模块的名称
    /// </summary>
    std::vector<std::string> getModuleNames();
    /// <summary>
    /// 获取字符串变量的名称
    /// </summary>
    std::vector<std::string> getStringVarNames();
    /// <summary>
    /// 获取布尔变量的名称
    /// </summary>
    std::vector<std::string> getBoolVarNames();
    /// <summary>
    /// 获取Byte变量的名称
    /// </summary>
    std::vector<std::string> getByteVarNames();
    /// <summary>
    /// 获取整型变量的名称
    /// </summary>
    std::vector<std::string> getIntVarNames();
    /// <summary>
    /// 获取单精度浮点型变量的名称
    /// </summary>
    std::vector<std::string> getFloatVarNames();
    /// <summary>
    /// 获取双精度浮点型变量的名称
    /// </summary>
    std::vector<std::string> getDoubleVarNames();
    /// <summary>
    /// 获取结构体变量的名称
    /// </summary>
    std::vector<std::string> getStructVarNames();
    /// <summary>
    /// 获取结构体的名称
    /// </summary>
    std::vector<std::string> getStructNames();
    /// <summary>
    /// 获取speed变量的名称
    /// </summary>
    std::vector<std::string> getSpeedNames();
    /// <summary>
    /// 获取数组变量的名称
    /// </summary>
    std::vector<ArrayVarInfo_stu> getArrayVarNames();
    /// <summary>
    /// 获取Curve曲线变量名
    /// </summary>
    std::vector<std::string> getCurveVarNames();

    /// <summary>
    /// 获取结构体信息
    /// </summary>
    std::map<std::string, int> getStructInfos();

    /// <summary>
    /// 获取方法信息
    /// </summary>
    // std::vector<SyntaxInfo> getFunctionInfos(const std::string &module, const std::string &filePath = "");
    std::vector<FunctionInfo_V1> getFunctionParamTypes();
    /// <summary>
    /// 获取Curve曲线组
    /// </summary>
    // std::vector<SyntaxInfo> getCurveInfos();
    std::vector<FunctionInfo_V1> getCurveParamTypes();
    /**
     * @brief 缩进检查
     */
    // PraseALineInfo *praseLineDegree(const std::string &cmdstring);

    /**
     * @brief 向译码库添加标签名称信息
     * @param labelName 输入，标签名称
     * @param realName 输入，原始名称，如P[000]
     */
    void addLabel(const std::string &labelName, const std::string &realName);
    /**
     * @brief 刷新译码库中的标签信息
     */
    void refreshLabels();
    /**
     * @brief 清空译码库中的标签信息
     */
    void clearLables();

    /**
     * @brief 判断字符串是否为关键字
     * @param str 输入，想要判断的字符串
     */
    bool isKeyWord(const std::string &str);

    /**
     * @brief 设置是否打印译码库的信息
     */
    void setPrintSwitch(bool isPrint);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
