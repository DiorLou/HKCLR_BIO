#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include "IRobotParamRange.h"
#include "../Controller/Connection/IConnection.h"
#include "../Controller/Monitor/IMonitor.h"
#include <unordered_map>
#include <thread>
#include <boost/asio.hpp>

namespace InoRobBusiness
{
// 机型本体的类型
enum RobotBodyType : int
{
    // Scara_A
    SCARA_A = 1,

    // Scara_R
    SCARA_R = 2,

    // 六关节
    ArticulatedArm_A = 3,
};

// 参数范围
struct ParamRangeModel
{
    ParamRangeModel()
    {
        Initialize();
    }

    void Initialize()
    {
        StructureName = std::string();
        Description = std::string();
        NodePath = std::string();
        NodePathName = std::string();
        MinValue = std::string();
        MaxValue = std::string();
        defautValue = std::string();
    }

    ParamRangeModel &operator=(const ParamRangeModel &other)
    {
        this->StructureName = other.StructureName;
        this->Description = other.Description;
        this->NodePath = other.NodePath;
        this->NodePathName = other.NodePathName;
        this->MinValue = other.MinValue;
        this->MaxValue = other.MaxValue;
        this->defautValue = other.defautValue;

        return (*this);
    }

    std::string StructureName;  // 参数结构体名称, eg: ReductionRatio
    std::string Description;    // 参数描述, eg: 减速比
    std::string NodePath;       // 参数节点路径, eg: 关节参数->减速比
    std::string NodePathName;   // 参数节点路径定义, eg: ReductionRatio->J1
    std::string MinValue;       // 最小值
    std::string MaxValue;       // 最大值
    std::string defautValue;    // 默认值
};

// 机型参数(原始机型文件)
struct RobotParamNode
{
    RobotParamNode()
    {
        Initialize();
    }

    void Initialize()
    {
        ID = std::string();
        Parent = std::string();
        IsLeafParam = false;
        Indexes = -1;
        SubIndexes = -1;
        Definition = std::string();
        Name = std::string();
        DefinitionPath = std::string();
        NamePath = std::string();
        Value.clear();
        MinValue = std::string();
        MaxValue = std::string();
        ObjectType = 1;
        DataLength = std::string();
        DataType = 0;
        AccessType = 0;
        Update = false;
        Install = true;
        Remark = std::string();
        RobotParamValueType = 0;
        // Items.clear();
    }

    RobotParamNode &operator=(const RobotParamNode &other)
    {
        this->ID = other.ID;
        this->Parent = other.Parent;
        this->IsLeafParam = other.IsLeafParam;
        this->Indexes = other.Indexes;
        this->SubIndexes = other.SubIndexes;
        this->Definition = other.Definition;
        this->Name = other.Name;
        this->DefinitionPath = other.DefinitionPath;
        this->NamePath = other.NamePath;
        this->Value = other.Value;
        this->MinValue = other.MinValue;
        this->MaxValue = other.MaxValue;
        this->ObjectType = other.ObjectType;
        this->DataLength = other.DataLength;
        this->DataType = other.DataType;
        this->AccessType = other.AccessType;
        this->Update = other.Update;
        this->Install = other.Install;
        this->Remark = other.Remark;
        this->RobotParamValueType = other.RobotParamValueType;

        return (*this);
    }

    string ID;                     // 根据NamePath计算MD5值（16位16进制字符串）
    string Parent;                 // Parent编号
    bool IsLeafParam;              // 是否叶子参数（非结构体）
    long Indexes;                  // 索引
    long SubIndexes;               // 子索引
    string Definition;             // 参数定义
    string Name;                   // 参数名称
    string DefinitionPath;         // 参数定义的路径，eg：stJoint->dAbsZero
    string NamePath;               // 参数名称的路径，eg：关节参数->绝对零点位置
    string MinValue;               // 最小值，如果是数组型数据则用英文逗号分隔
    string MaxValue;               // 最大值
    int ObjectType;                // 对象类型,1:变量；2：数组；3：复杂对象
    string DataLength;             // 数据长度，位长度
    int DataType;                  // 数据类型
    int AccessType;                // 访问类型,0:未知,1:只读,2:只写,3:可读可写
    bool Update;                   // 是否随版本升级
    bool Install;                  // 是否随版本刷机
    string Remark;                 // 备注
    int RobotParamValueType;       // 机器人参数值类型
    vector<vector<string>> Value;  // 默认值
    // vector<RobotParamNode> Items;  // 子参数
};

/**
 * @brief 机器人参数解析
 * @birth created by mzw on 2024-05-07
 */
class INOROBBUSINESS_CLASS RobotParamRange : public IRobotParamRange
{
public:
    RobotParamRange(IConnection *pConnection, IMonitor *pMonitor);
    ~RobotParamRange();

    // 更新参数范围
    void refreshParamRangeDataFromFile();

    // 获取参数最小值(double类型)
    double getDoubleMinValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最大值(double类型)
    double getDoubleMaxValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最小值(int类型)
    int getIntMinValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最大值(int类型)
    int getIntMaxValue(const std::string &paraStructName, const std::string &paramName);

    // 获取机型参数默认值
    std::string getDefaultParamValue(const std::string &paraStructName, const std::string &paramName);

    // 机型文件解析
    int robotParamFileParse(const std::string &robotName);

private:
    // 导入文件
    // int importFile(std::string &fullFileName, std::string &dataStr);

    // 是否为旧的机器人名称
    bool isOldRobotName(const std::string &robotName);

    // 裁剪字符串并转码
    std::string cropAndConvert(const std::string &input, size_t startPos, size_t length);

    // 从控制器中获取MachineParamsUI.json文件
    int getMachineParamsUIFileFromController();
#ifdef COBOT
    // 获取备份机器参数文件
    int getBackupMachineParamsFiles(const string &ip);
#endif
    // 解析json文件至结构体
    int parseJsonDataToParamNode(nlohmann::json &obj);

    // 获取参数范围列表
    int getParameterRangeList(RobotBodyType robotType);

    // 解析参数至对应的参数范围
    void addParamRangeModelBasedParamNode(const vector<std::string> &names, const RobotParamNode &paramNode, const std::string &paraStructName, bool isGetValue = false);

    // 获取数组型参数范围，根据index获取指定位置值
    void addParamRangeModelBasedSpecialIndex(int index, const RobotParamNode &paramNode, const std::string &paraName, const std::string &paraStructName);

    // 平均负载率限制（平均转矩）, 最大值是通过计算得到
    void addParamRangeModelForRunAvgLoadRate(const vector<std::string> &names, const std::string &paraStructName);

    // 电流限制（最大转矩）, 最大值是通过计算得到
    void addParamRangeModelForRunTorqueLimit(const vector<std::string> &names, const std::string &paraStructName);

    // 添加单个参数的参数范围
    void addParamRangeModelBasedSimpleParam(const std::string &paraName, const RobotParamNode &paramNode, const std::string &paraStructName);

    // 增加干涉区的参数范围
    void addParamRangeModelForInterference(const RobotParamNode &paramNode);

    // 查找组合键存在的个数
    int findCombinedKeyNum(const std::string &keyName1, const std::string &keyName2);

    // 从控制器内部拷贝机型参数文件至控制器临时目录
    int copyMachineFileToDestination(const string &ip);

    // 读取响应信息结果
    int readResponseResult(boost::asio::ip::tcp::socket &socket, const string &waitStr);

    // 获取名称
    vector<std::string> &getNames(vector<std::string> &fourNames, vector<std::string> &sixNames, RobotBodyType robotType);

    // 获取机器人本体类型
    RobotBodyType getRobotBodyType(const string &robotBodyName);


 
    static const std::string& getMachineParamsUIFilePathVC(); // 虚拟控制器文件路径



    // RobotParamRange(const RobotParamRange &robotParamRange) = delete;
    // const RobotParamRange &operator=(const RobotParamRange &robotParamRange) = delete;

    IConnection *_pConnection = nullptr;
    IMonitor *_pMonitor = nullptr;

    static const std::string _machineParamsUIFilePath;   // 控制器文件路径
    static const std::string _machineParamsUIFilePathVC; // 虚拟控制器文件路径
    static const std::string _localFilePath;             // 本地文件路径
    static const std::string _fileName;                  // 文件名称
    static const std::string _internalFilepath_28;       // 28版本控制器内部机型文件路径
    static const std::string _internalFilepath_below28;  // 低于28版本控制器内部机型文件路径
    static const std::string _telnetFinishFlag;          // telnet结束标志
    static const std::string _telnetLoginMsg;            // telnet登录结束标志
    static const std::string _telnetPasswordMsg;         // telnet密码输入结束标志
    static const std::string _telnetPort;                // telnet端口号，默认23
#ifdef COBOT
    static const std::string _machineParamsUIBackFilePath;      // 控制器备份文件路径
    static const std::string _absolutemachineParamsUIFilePath; // 控制器文件绝对路径
#endif
    std::string _strRobotName;                                        // 机器人名称
    std::unordered_map<std::string, RobotParamNode> _paramNodeMap;    // 机型参数结构体映射
    std::unordered_map<std::string, ParamRangeModel> _paramRangeMap;  // 参数范围结构体映射
    std::string _parameterRangeFileName;                              // 参数范围文件名称

    std::shared_ptr<std::thread> _pthread = nullptr;
};
}  // namespace InoRobBusiness
