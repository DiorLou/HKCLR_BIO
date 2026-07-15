#pragma once
#include <string>
#include <vector>
#include <map>
#include <QObject>
#include "../Controller/DataSubscribe/DataSubscribeTypes.h"

namespace InoRobBusinessProxy
{
// 操作码(OpCode)
enum DataSubscribeOpCode_V1 : int8u
{
    DS_OP_ADD_V1 = 0x01,     // 添加
    DS_OP_DELETE_V1 = 0x02,  // 删除
    DS_OP_CLEAR_V1 = 0x03    // 清除
};

// 资源类型(ResourceType)
enum DataSubscribeResType_V1 : int16u
{
    DS_RES_SYSTEM_VAR_V1 = 0x0001,
    DS_RES_USER_VAR_V1 = 0x0002,
    DS_RES_RC_MSG_V1 = 0x0003  // 控制器消息
};

// 业务类型(BusinessType)
enum DataSubscribeBusType_V1 : int16u
{
    DS_BUSI_PERIODIC_V1 = 0x0100,
    DS_BUSI_STATUS_CHANGED_V1 = 0x0200
};

// 变量监控标志位
#define DS_VAR_MONITOR_BIT_FLAG_V1 (0x01 << 15)

// 对象ID(BusinessType)
enum DataSubscribeObjId_V1 : int8u
{
    DS_OBJ_ID_ALL_V1 = 0,
    DS_OBJ_ID_VAR_MONITOR_V1 = 1,
    DS_OBJ_ID_GLOBAL_VAR_MONITOR_V1 = 2,
    DS_OBJ_ID_RC_MESSAGE_V1 = 3,  // 控制器
};

// 订阅请求内容
struct DataSubscribeReq_V1
{
    unsigned char OpCode;
    unsigned int Id;
    unsigned short Type;
    std::string JsonObj;

    DataSubscribeReq_V1()
    {
        OpCode = (int8u)DS_OP_ADD_V1;
        Id = DS_OBJ_ID_VAR_MONITOR_V1;
        Type = (int8u)DS_RES_SYSTEM_VAR_V1 + (int8u)DS_BUSI_STATUS_CHANGED_V1;
        JsonObj = "{}";
    }
};

/**
 * @brief 变量监控范围类型
 */
enum VarMonitorScopeType_V1
{
    VMST_GLOBAL_VAR_V1 = 0,   // 全局变量
    VMST_MODULE_VAR_V1 = 1,   // 模块内变量
    VMST_FUNCTION_VAR_V1 = 2  // 函数内变量
};

/**
 * @brief 变量监控值类型
 */
enum VarMonitorValueType_V1 : int8u
{
    VMVT_INT_V1 = 0,
    VMVT_FLOAT_V1 = 1,
    VMVT_STRING_V1 = 2,
    VMVT_BOOL_V1 = 3,
    VMVT_NULL_V1 = 4
};

VarMonitorValueType_V1 VarMonitorValueType_ToProxy(VarMonitorValueType varMonitorValueType);
VarMonitorValueType VarMonitorValueType_FromProxy(VarMonitorValueType_V1 varMonitorValueType_V1);

struct VarMonitorValue_V1
{
    VarMonitorValueType_V1 valueType = VMVT_INT_V1;  // 值类型

    int intValue = 0;
    double doubleValue = 0.0;
    bool boolValue = false;
    std::string strValue;

    VarMonitorValue_V1()
    {
        Init();
    }

    void Init()
    {
        valueType = VMVT_INT_V1;
        intValue = 0;
        doubleValue = 0.0;
        boolValue = false;
        strValue = "";
    }
};

bool VarMonitorValue_ToProxy(const VarMonitorValue &varMonitorValue, VarMonitorValue_V1 &varMonitorValue_V1);
bool VarMonitorValue_FromProxy(const VarMonitorValue_V1 &varMonitorValue_V1, VarMonitorValue &varMonitorValue);

/**
 * @brief 变量监控任务项
 */
struct VarMonitorTaskItem_V1
{
    int varType;
    int taskId;
    std::string moduleName;
    std::string functionName;
    int varCount;
    std::map<std::string, VarMonitorValue_V1> vars;

    VarMonitorTaskItem_V1()
    {
        varType = (int)VMST_GLOBAL_VAR_V1;
        taskId = 0;
        moduleName = "";
        functionName = "";
        varCount = 0;
    }

    void clear()
    {
        varType = (int)VMST_GLOBAL_VAR_V1;
        taskId = 0;
        moduleName = "";
        functionName = "";
        varCount = 0;
        vars.clear();
    }

    bool equal(VarMonitorTaskItem_V1 *other)
    {
        return varType == other->varType
               && taskId == other->taskId
               && moduleName == other->moduleName
               && functionName == other->functionName;
    }
};

/**
 * @brief 变量监控Json
 */
struct VarMonitorJson_V1
{
    int itemCount;
    std::vector<VarMonitorTaskItem_V1> items;

    VarMonitorJson_V1()
    {
        itemCount = 0;
    }

    void clear()
    {
        itemCount = 0;
        items.clear();
    }

    void add(VarMonitorTaskItem_V1 *item)
    {
        for (std::vector<VarMonitorTaskItem_V1>::iterator it = items.begin(); it != items.end(); it++)
        {
            if (!it->equal(item))
                continue;

            std::map<std::string, VarMonitorValue_V1>::iterator vit;
            for (vit = item->vars.begin(); vit != item->vars.end(); vit++)
            {
                it->vars[vit->first] = vit->second;
            }
            return;
        }

        items.push_back(*item);
        itemCount = items.size();
    }
};

enum InoMessageLevel_V1
{
    MSG_LEVEL_NORMAL_V1 = 0,    // 控制器普通消息
    MSG_LEVEL_PRINT_V1 = 1,     // 控制器打印消息
    MSG_LEVEL_ERROR_V1 = 2,     // 错误，上下都适用
    MSG_LEVEL_WARNING_V1 = 3,   // 警告，上下都适用
    MSG_LEVEL_MESSAGE_V1 = 10,  // PC软件或者示教器普通消息
};

struct RcMessageJson_V1
{
    InoMessageLevel_V1 Level;
    unsigned short SequenceNum;
    unsigned short MessagesCount;
    std::vector<std::string> Messages;

    RcMessageJson_V1()
    {
        SequenceNum = 0;
        Level = MSG_LEVEL_PRINT_V1;
        MessagesCount = 0;
    }

    void Clear()
    {
        SequenceNum = 0;
        MessagesCount = 0;
        Messages.clear();
        Level = MSG_LEVEL_PRINT_V1;
    }
};
}  // namespace InoRobBusinessProxy