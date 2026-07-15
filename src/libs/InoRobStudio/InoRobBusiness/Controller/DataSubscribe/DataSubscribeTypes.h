#pragma once
#include <string>
#include <vector>
#include <map>
#include "DataTypeDef.h"

//////////////////////////////////////////////////////////////////////////
// 数据订阅相关类型----BEGIN
//////////////////////////////////////////////////////////////////////////
// 操作码(OpCode)
enum DataSubscribeOpCode : int8u
{
    DS_OP_ADD = 0x01,     // 添加
    DS_OP_DELETE = 0x02,  // 删除
    DS_OP_CLEAR = 0x03    // 清除
};

// 资源类型(ResourceType)
enum DataSubscribeResType : int16u
{
    DS_RES_SYSTEM_VAR = 0x0001,
    DS_RES_USER_VAR = 0x0002,
    DS_RES_RC_MSG = 0x0003  // 控制器消息
};

// 业务类型(BusinessType)
enum DataSubscribeBusType : int16u
{
    DS_BUSI_PERIODIC = 0x0100,
    DS_BUSI_STATUS_CHANGED = 0x0200
};

// 变量监控标志位
#define DS_VAR_MONITOR_BIT_FLAG (0x01 << 15)

// 对象ID(BusinessType)
enum DataSubscribeObjId : int8u
{
    DS_OBJ_ID_ALL = 0,
    DS_OBJ_ID_VAR_MONITOR = 1,
    DS_OBJ_ID_GLOBAL_VAR_MONITOR = 2,
    DS_OBJ_ID_RC_MESSAGE = 3,  // 控制器
};

// 订阅请求内容
struct DataSubscribeReq
{
    unsigned char OpCode;
    unsigned int Id;
    unsigned short Type;
    std::string JsonObj;

    DataSubscribeReq()
    {
        OpCode = (int8u)DS_OP_ADD;
        Id = DS_OBJ_ID_VAR_MONITOR;
        Type = (int8u)DS_RES_SYSTEM_VAR + (int8u)DS_BUSI_STATUS_CHANGED;
        JsonObj = "{}";
    }
};

//////////////////////////////////////////////////////////////////////////
// 数据订阅相关类型----END
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 变量监控数据类型定义----BEGIN
//////////////////////////////////////////////////////////////////////////

/**
 * @brief 变量监控范围类型
 */
enum VarMonitorScopeType
{
    VMST_GLOBAL_VAR = 0,   // 全局变量
    VMST_MODULE_VAR = 1,   // 模块内变量
    VMST_FUNCTION_VAR = 2  // 函数内变量
};

/**
 * @brief 变量监控值类型
 */
enum VarMonitorValueType : int8u
{
    VMVT_INT = 0,
    VMVT_FLOAT = 1,
    VMVT_STRING = 2,
    VMVT_BOOL = 3,
    VMVT_NULL = 4
};

struct VarMonitorValue
{
    VarMonitorValueType valueType = VMVT_INT;  // 值类型

    int intValue = 0;
    double doubleValue = 0.0;
    bool boolValue = false;
    std::string strValue;
};

/**
 * @brief 变量监控任务项
 */
struct VarMonitorTaskItem
{
    int varType;
    int taskId;
    std::string moduleName;
    std::string functionName;
    int varCount;
    std::map<std::string, VarMonitorValue> vars;

    VarMonitorTaskItem()
    {
        varType = (int)VMST_GLOBAL_VAR;
        taskId = 0;
        moduleName = "";
        functionName = "";
        varCount = 0;
    }

    void clear()
    {
        varType = (int)VMST_GLOBAL_VAR;
        taskId = 0;
        moduleName = "";
        functionName = "";
        varCount = 0;
        vars.clear();
    }

    bool equal(VarMonitorTaskItem *other)
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
struct VarMonitorJson
{
    int itemCount;
    std::vector<VarMonitorTaskItem> items;

    VarMonitorJson()
    {
        itemCount = 0;
    }

    void clear()
    {
        itemCount = 0;
        items.clear();
    }

    void add(VarMonitorTaskItem *item)
    {
        for (std::vector<VarMonitorTaskItem>::iterator it = items.begin(); it != items.end(); it++)
        {
            if (!it->equal(item))
                continue;

            std::map<std::string, VarMonitorValue>::iterator vit;
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

//////////////////////////////////////////////////////////////////////////
// 变量监控数据类型定义----END
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 控制器消息数据类型定义----BEGIN
//////////////////////////////////////////////////////////////////////////
enum InoMessageLevel
{
    MSG_LEVEL_NORMAL = 0,    // 控制器普通消息
    MSG_LEVEL_PRINT = 1,     // 控制器打印消息
    MSG_LEVEL_ERROR = 2,     // 错误，上下都适用
    MSG_LEVEL_WARNING = 3,   // 警告，上下都适用
    MSG_LEVEL_MESSAGE = 10,  // PC软件或者示教器普通消息
};

struct RcMessageJson
{
    InoMessageLevel Level;
    unsigned short SequenceNum;
    unsigned short MessagesCount;
    std::vector<std::string> Messages;

    RcMessageJson()
    {
        SequenceNum = 0;
        Level = MSG_LEVEL_PRINT;
        MessagesCount = 0;
    }

    void Clear()
    {
        SequenceNum = 0;
        MessagesCount = 0;
        Messages.clear();
        Level = MSG_LEVEL_PRINT;
    }
};

//////////////////////////////////////////////////////////////////////////
// 控制器消息数据类型定义----END
//////////////////////////////////////////////////////////////////////////
