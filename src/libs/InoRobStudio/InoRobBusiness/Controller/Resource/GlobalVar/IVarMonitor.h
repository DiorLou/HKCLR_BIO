#pragma once
#include <QObject>
#include <GlobalDataTypes.h>
#include "DataSubscibeTypes.h"

namespace InoRobBusiness
{
#define VARMONITOR_MAX_SIZE 10  // 变量监控最大大小

/**
 * @brief 变量监控对象类型
 *        与instrution/GlobalsData.h中IDSTR_KIND枚举保持一致（必须）
 */
enum VarMonitorObjectType : int16u
{
    VMOT_STRING = 0,  // 简单字符串
    VMOT_STRINGVAR,   // 字符串变量
    VMOT_B,           // B变量
    VMOT_R,           // R变量
    VMOT_D,           // D变量
    VMOT_LB,          // LB变量
    VMOT_LR,          // LR变量
    VMOT_LD,          // LD变量
    VMOT_PR,          // PR变量
    VMOT_LPR,         // 局部PR变量
    VMOT_PRMEB,       // PR变量成员变量
    VMOT_LPRMEB,      // 局部PR变量成员变量
    VMOT_P,           // 全局P
    VMOT_PMEB,        // 全局P成员变量
    VMOT_JP,          // 全局JP
    VMOT_JPMEB,       // 全局JP成员变量
    VMOT_LP,          // GP变量
    VMOT_LPMEB,       // GP变量成员变量
    VMOT_FILENAME,    // 文件名
    VMOT_GSTRING,     // 全局字符串变量
    VMOT_BOOL,        // bool变量
    VMOT_BYTE,        // byte变量
    VMOT_INT,         // int变量
    VMOT_FLOAT,       // float变量
    VMOT_DOUBLE,      // double变量
    VMOT_SPEED,       // Speed类型变量
    VMOT_SPEEDMEB,    // SPeed类型成员变量
    VMOT_MEBBIT,
    VMOT_MEBINT,
    VMOT_MEBFLOAT,
    VMOT_MEBDOUBLE,
    VMOT_FUNNAME,     // 函数名
    VMOT_DEFNAME,     // 宏定义名
    VMOT_MODELNAME,   // 模块名
    VMOT_STRUCTNAME,  // 结构体名
    VMOT_STRUCTVAR,   // 结构体变量名

    // 以下供示教器使用
    VMOT_IN = 100,  // In
    VMOT_OUT,       // Out
    VMOT_INB,       // InB
    VMOT_OUTB,      // OutB
    VMOT_INW,       // InW
    VMOT_OUTW,      // OutW
    VMOT_IGVAR,
    VMOT_OGVAR,
    VMOT_TOOL,  // 工具
    VMOT_WOBJ,  // 工件
    VMOT_TOOLMEB,
    VMOT_WOBJMEB,
    VMOT_LOAD,  // 负载
    VMOT_LOADMEB
};

/**
 * @brief 变量监控操作数据
 */
struct VarMonitorOperateData
{
    VarMonitorObjectType type = VMOT_STRING;  // 变量类型
    std::string name;                         // 变量名
};

/**
 * @brief 变量监控展示数据
 */
struct VarMonitorShowData
{
    VarMonitorValue value;    // 监控值
    std::string name;         // 名称
    unsigned int index = -1;  // 下标（在vector<VarMonitorOperateData>下标）
    bool edit = false;        // 是否可编辑

    VarMonitorShowData(VarMonitorValue &_value, std::string &_name,
                       unsigned int _index, bool _edit)
        : value(_value), name(_name), index(_index), edit(_edit)
    {
    }
};

// 变量监控-变量设置
/**
 * @brief 变量设置类型
 */
enum VAR_SET_KIND
{
    VAR_SET_ERR,
    VAR_SET_BOOL,
    VAR_SET_BYTE,
    VAR_SET_INT,
    VAR_SET_FLOAT,
    VAR_SET_DOUBLE,
    VAR_SET_CHAR,
    VAR_SET_SWITCH,
};

/**
 * @brief 变量设置信息
 */
struct VAR_SET_INFO
{
    char varName[255];     // 变量名
    VAR_SET_KIND varKind;  // 变量类型
    union                  // 变量值
    {
        bool bVal;
        unsigned char ucVal;
        int iVal;
        float fVal;
        double dVal;
        char spValue[255];
    };
};

/**
 * @brief 变量监控基类
 */
class INOROBBUSINESS_CLASS IVarMonitor : public QObject
{
    Q_OBJECT

public:
    virtual ~IVarMonitor()
    {
    }

    /**
     * @brief 获取所有变量监控展示数据
     */
    virtual std::vector<VarMonitorShowData> getVarMonitorShowDatas() const = 0;

    /**
     * @brief 设置当前任务ID（编程调试界面任务ID）
     * @param taskId 任务ID
     * @return true成功 false失败
     */
    virtual bool setCurrentTaskId(const int taskId) = 0;

    /**
     * @brief 添加一个变量监控
     * @param data 添加的变量监控
     * @return true成功 false失败
     */
    virtual bool addVarMonitor(VarMonitorOperateData data) = 0;

    /**
     * @brief 删除一个变量监控
     * @param index 下标（在vector中的下标）
     * @return true成功 false失败
     */
    virtual bool deleteVarMonitor(const unsigned int index) = 0;

    /**
     * @brief 清除所有变量监控
     * @return true成功 false失败
     */
    virtual bool clearVarMonitor(bool isBtnClicked = true) = 0;

    /**
     * @brief 订阅拾取监控
     * @param fileName 工程文件名
     * @param lineNo 行号
     * @return true成功 false失败
     */
    virtual bool subcribePickupMonitor(const string &fileName, int lineNo) = 0;

    /**
     * @brief 与控制器通信，设置某个任务中的变量值
     * @param value 变量信息
     * @return true成功 false失败
     */
    virtual bool setVarValueInTask(const VAR_SET_INFO &info) = 0;

Q_SIGNALS:
    // 变量监控改变信号
    void varMonitorChanged();
};
}  // namespace InoRobBusiness
