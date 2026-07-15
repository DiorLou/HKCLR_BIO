#ifndef PLUGINCONFIGMODEL_H
#define PLUGINCONFIGMODEL_H
#include <GlobalDataTypes.h>
#include <QList>
#include <QString>
#include <vector>
#include "dllspec.h"

using namespace std;

// 参数值信息
struct PluginParaValue
{
    PluginParaValue()
    {
        Initialize();
    }
    void Initialize()
    {
        Value = "";
        ValueDescription = "";
        ValueType = 0;
        Range = "";
        IsEnableEdit = true;
    }

    bool operator==(const struct PluginParaValue other) const
    {
        if (Value == other.Value
            && ValueDescription == other.ValueDescription
            && ValueType == other.ValueType
            && Range == other.Range
            && IsEnableEdit == other.IsEnableEdit)
            return true;

        return false;
    }

    QString Value;             // 参数列表的值
    QString ValueDescription;  // 值的描述
    int ValueType;             // 编辑值的类型 0-String；    1 - int； 2 - Double； 3 - 表示罗列参数范围里面的值；
    QString Range;             // 参数范围 []、()代表区间范围;    ArcData[0 - 15] ：代表显示0 - 15 的ArcData;   Acc[0; 25; 75; 100] ：表示显示不同的值；
    bool IsEnableEdit;         // 参数是否允许编辑  True：是；    False：否；    点击该列表是否需要出来编辑页面； (默认是 True)
};
// 参数分类信息
struct PluginParaTypeInfo
{
    PluginParaTypeInfo()
    {
        Initialize();
    }
    void Initialize()
    {
        ParaTypeDescrition = "";
        VecParaValues.clear();
    }

    bool operator==(const struct PluginParaTypeInfo other) const
    {
        if (ParaTypeDescrition == other.ParaTypeDescrition
            && VecParaValues == other.VecParaValues)
            return true;

        return false;
    }

    QString ParaTypeDescrition;             // 参数分类描述
    vector<PluginParaValue> VecParaValues;  // 指令分类
};

// 参数信息
struct PluginCmdParaInfo
{
    PluginCmdParaInfo()
    {
        Initialize();
    }
    void Initialize()
    {
        ParaName = "";
        RadioGroup = "";
        Seperator = "";
        MatchKeyWord = "";
        IsEnableClick = true;
        IsOptional = false;
        IsShow = true;
        TP2DataType = 0;
        TP2Label = "";
        IsFastUpdate = 0;
        VecParaTypeInfos.clear();
    }

    bool operator==(const struct PluginCmdParaInfo other) const
    {
        if (ParaName == other.ParaName
            && Seperator == other.Seperator
            && MatchKeyWord == other.MatchKeyWord
            && IsEnableClick == other.IsEnableClick
            && IsOptional == other.IsOptional
            && IsShow == other.IsShow
            && VecParaTypeInfos == other.VecParaTypeInfos
            && IsFastUpdate == other.IsFastUpdate
            && RadioGroup == other.RadioGroup)
            return true;

        return false;
    }

    QString ParaName;                            // 参数名称
    QString RadioGroup;                          // 是否和其他参数互斥 如果是""则不互斥
    QString Seperator;                           // 紧邻参数的分隔符 类似于","、"、"，";"
    QString MatchKeyWord;                        // 匹配的关键字字符串    类似：“V[”“P[” “Tool[”
    bool IsEnableClick;                          // 参数是否可以点击,    确定点击是否有响应；    （True 是可以点击、False 是无法点击）; 默认是 true
    bool IsOptional;                             // 参数是否可以选择  1.True 是参数可选择、False是不可选择(必选)    （默认是 Flase）
    bool IsShow;                                 // 参数是否显示 只有IsOptional为True(可选参数)时，参数值才有效；    默认是：True
    int TP2DataType;                            /* 用于TP2.0转换指示 0-默认；1-单独关键字类型、2-单独的无参数指令、3-类型中参数非数字[x]、4-存在互斥、5-其中单独整型，参数0和1应注明类型
                                                  6-指令后加一个（）包含参数的为一种情况、7-Out类型，支持第三个参数（T[0]）、8-Out类型，不支持第三个参数（T[0]）
                                                */
    QString TP2Label;//TP2.0
    int IsFastUpdate;//是否为快速修改           //0否 1支持
    QList<PluginParaTypeInfo> VecParaTypeInfos;  // 指令参数属性集合;
};

// 指令信息
struct InoRobPluginCommand
{
    InoRobPluginCommand()
    {
        Initialize();
    }
    void Initialize()
    {
        CmdName = "";
        CmdDefaultFormat = "";
        IsCommonCmd = false;
        IsPlatformCmd = 0;
        CmdDialogIndex = -1;
        IsFastAdd = 0;
        VecParaInfos.clear();
    }

    bool operator==(const struct InoRobPluginCommand other) const
    {
        if (CmdName == other.CmdName
            && CmdDefaultFormat == other.CmdDefaultFormat
            && IsCommonCmd == other.IsCommonCmd
            && IsPlatformCmd == other.IsPlatformCmd
            && IsFastAdd == other.IsFastAdd
            && CmdDialogIndex == other.CmdDialogIndex
            && VecParaInfos == other.VecParaInfos)
            return true;

        return false;
    }

    QString CmdName;                         // 指令的名称；
    QString CmdDefaultFormat;                // 指令默认的显示格式;
    bool IsCommonCmd;                        // 是否是常用指令 True: 需要写入到常用指令的配置里；    False : 不需要写入到常用指令的配置文件里；            默认值：False
    int CmdDialogIndex;                      // 指令对应的自定义页面索引 当CmdDialogTypex 为 1 时，才生效，表示扩展的指令页面索引，通过这个字段，找到应该对应打开哪个插件里的指令页面； 默认为 -1
    int IsPlatformCmd;                      //是否平台指令 0否、1是
    int IsFastAdd;                          //是否快速添加指令 0否、1是
    vector<PluginCmdParaInfo> VecParaInfos;  // 指令参数属性集合;
};

struct InoRobPluginCommandAllInfo
{
    QString CmdTypeName;                  // 工艺名
    QString CmdEnTypeName;                // 指令ID
    QList<InoRobPluginCommand> CmdInfos;  // 指令列表
};

// 工艺插件UI信息
struct InoRobPluginPageInfo
{
    InoRobPluginPageInfo()
    {
        Init();
    }

    void Init()
    {
        /*
        titleName = "";
        qmlPath = "";
        strModule = "";
        */
        Infos.clear();
    }
  //  QString titleName;  // 页面标题及所属标题，例如 工况监控->插件1
  //  QString qmlPath;    // 页面的qml路径
  //  QString strModule;  // 显示所在模块，例如:监控-MonitorArea，设置-SettingArea，控制面板-ControlPanel
    map<string, string>Infos;//消息汇总
};

struct InoRobPluginPageAllInfo
{
    QString strPluginId;                                   // 工艺ID
    QList<InoRobPluginPageInfo> InoRobPluginPageInfoList;  // 页面信息列表
};
//标题栏图标信息
struct InoRobPluginStatusInfo
{
    QString strPluginId;//工艺包ID
    map<string, string>m_StatusInfos;//key为 iconTop1-4  values为 图片地址
};

struct InstalledPluginInfo
{
    QString pluginId;
};
// 当前已安装插件相关信息
struct InoRobotInstalledPlugins
{
    InoRobotInstalledPlugins()
    {
        Init();
    }

    void Init()
    {
        InstalledPluginInfoList.clear();
    }

    QList<InstalledPluginInfo>InstalledPluginInfoList;
};

#endif  // PLUGINCONFIGMODEL_H
