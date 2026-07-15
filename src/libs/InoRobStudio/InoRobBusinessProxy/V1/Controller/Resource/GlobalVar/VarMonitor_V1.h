#pragma once
#include "dllspec.h"
#include <QObject>
#include "IInoRobBusiness.h"
#include "../../DataSubscribe/DataSubscribeTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define VARMONITOR_MAX_SIZE_V1 10  // 变量监控最大大小

/**
 * @brief 变量监控对象类型
 *        与instrution/GlobalsData.h中IDSTR_KIND枚举保持一致（必须）
 */
enum VarMonitorObjectType_V1 : int16u
{
    VMOT_STRING_V1 = 0,  // 简单字符串
    VMOT_STRINGVAR_V1,   // 字符串变量
    VMOT_B_V1,           // B变量
    VMOT_R_V1,           // R变量
    VMOT_D_V1,           // D变量
    VMOT_LB_V1,          // LB变量
    VMOT_LR_V1,          // LR变量
    VMOT_LD_V1,          // LD变量
    VMOT_PR_V1,          // PR变量
    VMOT_LPR_V1,         // 局部PR变量
    VMOT_PRMEB_V1,       // PR变量成员变量
    VMOT_LPRMEB_V1,      // 局部PR变量成员变量
    VMOT_P_V1,           // 全局P
    VMOT_PMEB_V1,        // 全局P成员变量
    VMOT_JP_V1,          // 全局JP
    VMOT_JPMEB_V1,       // 全局JP成员变量
    VMOT_LP_V1,          // GP变量
    VMOT_LPMEB_V1,       // GP变量成员变量
    VMOT_FILENAME_V1,    // 文件名
    VMOT_GSTRING_V1,     // 全局字符串变量
    VMOT_BOOL_V1,        // bool变量
    VMOT_BYTE_V1,        // byte变量
    VMOT_INT_V1,         // int变量
    VMOT_FLOAT_V1,       // float变量
    VMOT_DOUBLE_V1,      // double变量
    VMOT_SPEED_V1,       // Speed类型变量
    VMOT_SPEEDMEB_V1,    // SPeed类型成员变量
    VMOT_MEBBIT_V1,
    VMOT_MEBINT_V1,
    VMOT_MEBFLOAT_V1,
    VMOT_MEBDOUBLE_V1,
    VMOT_FUNNAME_V1,     // 函数名
    VMOT_DEFNAME_V1,     // 宏定义名
    VMOT_MODELNAME_V1,   // 模块名
    VMOT_STRUCTNAME_V1,  // 结构体名
    VMOT_STRUCTVAR_V1,   // 结构体变量名

    // 以下供示教器使用
    VMOT_IN_V1 = 100,  // In
    VMOT_OUT_V1,       // Out
    VMOT_INB_V1,       // InB
    VMOT_OUTB_V1,      // OutB
    VMOT_INW_V1,       // InW
    VMOT_OUTW_V1,      // OutW
    VMOT_IGVAR_V1,
    VMOT_OGVAR_V1,
    VMOT_TOOL_V1,  // 工具
    VMOT_WOBJ_V1,  // 工件
    VMOT_TOOLMEB_V1,
    VMOT_WOBJMEB_V1,
    VMOT_LOAD_V1,  // 负载
    VMOT_LOADMEB_V1
};

/**
 * @brief 变量监控操作数据
 */
struct VarMonitorOperateData_V1
{
    VarMonitorObjectType_V1 type = VMOT_STRING_V1;  // 变量类型
    std::string name;                               // 变量名
};

/**
 * @brief 变量监控展示数据
 */
struct VarMonitorShowData_V1
{
    VarMonitorValue_V1 value;  // 监控值
    std::string name;          // 名称
    unsigned int index = -1;   // 下标（在vector<VarMonitorOperateData>下标）
    bool edit = false;         // 是否可编辑

    VarMonitorShowData_V1()
    {
        Init();
    }

    void Init()
    {
        value.Init();
        name = "";
        index = -1;
        edit = false;
    }

    VarMonitorShowData_V1(VarMonitorValue_V1 &_value, std::string &_name,
                          unsigned int _index, bool _edit)
        : value(_value), name(_name), index(_index), edit(_edit)
    {
    }
};

/**
 * @brief 变量设置类型
 */
enum VAR_SET_KIND_V1
{
    VAR_SET_ERR_V1,
    VAR_SET_BOOL_V1,
    VAR_SET_BYTE_V1,
    VAR_SET_INT_V1,
    VAR_SET_FLOAT_V1,
    VAR_SET_DOUBLE_V1,
    VAR_SET_CHAR_V1,
    VAR_SET_SWITCH_V1,
};

/**
 * @brief 变量设置信息
 */
struct VAR_SET_INFO_V1
{
    char varName[255];        // 变量名
    VAR_SET_KIND_V1 varKind;  // 变量类型
    union                     // 变量值
    {
        bool bVal;
        unsigned char ucVal;
        int iVal;
        float fVal;
        double dVal;
        char spValue[255];
    };
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS VarMonitor_V1 : public QObject
{
    Q_OBJECT

#pragma region 构造与析构

private:
    IVarMonitor *_varMonitor = nullptr;

public:
    VarMonitor_V1(IVarMonitor *varMonitor);
    ~VarMonitor_V1();

#pragma endregion

#pragma region 数据转换

public:
    static VarMonitorObjectType_V1 VarMonitorObjectType_ToProxy(VarMonitorObjectType varMonitorObjectType);
    static VarMonitorObjectType VarMonitorObjectType_FromProxy(VarMonitorObjectType_V1 varMonitorObjectType_V1);

    static VAR_SET_KIND_V1 VAR_SET_KIND_ToProxy(VAR_SET_KIND var_SET_KIND);
    static VAR_SET_KIND VAR_SET_KIND_FromProxy(VAR_SET_KIND_V1 var_SET_KIND_V1);

    static bool VarMonitorOperateData_ToProxy(const VarMonitorOperateData &varMonitorOperateData, VarMonitorOperateData_V1 &varMonitorOperateData_V1);
    static bool VarMonitorOperateData_FromProxy(const VarMonitorOperateData_V1 &varMonitorOperateData_V1, VarMonitorOperateData &varMonitorOperateData);

    static bool VarMonitorShowData_ToProxy(const VarMonitorShowData &varMonitorShowData, VarMonitorShowData_V1 &varMonitorShowData_V1);
    static bool VarMonitorShowData_FromProxy(const VarMonitorShowData_V1 &varMonitorShowData_V1, VarMonitorShowData &varMonitorShowData);

    static bool VAR_SET_INFO_ToProxy(const VAR_SET_INFO &var_SET_INFO, VAR_SET_INFO_V1 &var_SET_INFO_V1);
    static bool VAR_SET_INFO_FromProxy(const VAR_SET_INFO_V1 &var_SET_INFO_V1, VAR_SET_INFO &var_SET_INFO);

#pragma endregion

#pragma region 业务逻辑

private:
    void varMonitorChangedHandler();

public:
    /**
     * @brief 获取所有变量监控展示数据
     */
    std::vector<VarMonitorShowData_V1> getVarMonitorShowDatas();

    /**
     * @brief 设置当前任务ID（编程调试界面任务ID）
     * @param taskId 任务ID
     * @return true成功 false失败
     */
    bool setCurrentTaskId(const int taskId);

    /**
     * @brief 添加一个变量监控
     * @param data 添加的变量监控
     * @return true成功 false失败
     */
    bool addVarMonitor(VarMonitorOperateData_V1 data);

    /**
     * @brief 删除一个变量监控
     * @param index 下标（在vector中的下标）
     * @return true成功 false失败
     */
    bool deleteVarMonitor(const unsigned int index);

    /**
     * @brief 清除所有变量监控
     * @return true成功 false失败
     */
    bool clearVarMonitor();

    /**
     * @brief 订阅拾取监控
     * @param fileName 工程文件名
     * @param lineNo 行号
     * @return true成功 false失败
     */
    bool subcribePickupMonitor(const string &fileName, int lineNo);

    /**
     * @brief 与控制器通信，设置某个任务中的变量值
     * @param value 变量信息
     * @return true成功 false失败
     */
    bool setVarValueInTask(const VAR_SET_INFO_V1 &info);

Q_SIGNALS:
    // 变量监控改变信号
    void varMonitorChanged();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
