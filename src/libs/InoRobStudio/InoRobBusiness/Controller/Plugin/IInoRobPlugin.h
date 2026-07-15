#pragma once
#include <string>
#include <vector>
#include "PluginConfigModel.h"
using namespace std;

namespace InoRobBusiness
{

// 工艺插件错误码
typedef struct InoRobPluginErrorCode
{
    // 指令名称
    QString ErroCodeInfoID;   // 工艺ID
    QString ID;               // 报警码
    QList<QString> DescList;  // 语言表，0是中文，1-英文
    void Init()
    {
        ID = "";
        ErroCodeInfoID = "";
        DescList.clear();
    }

    InoRobPluginErrorCode()
    {
        Init();
    }
} InoRobPluginErrorCode;

// 工艺插件服务通用返回码
enum class InoRobPluginRespCode
{
    Success = 0,         // 成功
    Failure = 1,         // 失败
    UnknowError = 2,     // 未知错误
    Exception = 3,       // 发生异常
    ParameterError = 4,  // 请求参数有误
    Timeout = 5,         // 处理超时
    Unsupport = 6,       // 不支持的功能
};

// 工艺插件事件数据
typedef struct InoRobPluginEventData
{
    // 插件ID，用于区分不同的插件
    string PluginID;
    // 插件服务码，用于区分同一插件中的不同功能
    string ServiceCode;
    // 插件服务对应的业务数据
    string ServiceData;

    void Init()
    {
        PluginID = "";
        ServiceCode = "";
        ServiceData = "";
    }

    InoRobPluginEventData()
    {
        Init();
    }

} InoRobPluginEventData;


}  // namespace InoRobBusiness
