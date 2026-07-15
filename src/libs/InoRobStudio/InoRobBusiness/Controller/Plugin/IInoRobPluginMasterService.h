#pragma once
#include <string>
#include <vector>
#include "dllspec.h"
#include "IInoRobPlugin.h"
#include <QObject>
using namespace std;

namespace InoRobBusiness
{
/*
    汇川工业机器人工艺插件宿主服务契约
    Create by lingbinzhi at 2024/9/29
*/
class INOROBBUSINESS_CLASS IInoRobPluginMasterService : public QObject
{
    Q_OBJECT
public:
    virtual ~IInoRobPluginMasterService()
    {
    }
    
    //安装工艺指令
    virtual int InstallInoRobPluginCommand(InoRobPluginCommandAllInfo inoRobPluginCommandAllInfo) = 0;
    //安装工艺指令
    virtual int InstallInoRobPluginCommandV2(QString strPath,QString CmdEnTypeName) = 0;

    //卸载工艺指令
    virtual int UninstallInoRobPluginCommand(QString pluginID) = 0;

    //获取工艺指令集
    virtual InoRobPluginCommandAllInfo GetInoRobPluginCommand(QString pluginID) = 0;

    // 批量增加插件错误码
    virtual bool ErrorCodeInstall(const QList<InoRobPluginErrorCode> &pluginErrorCodeList) = 0;
    // 移除指定插件的所有错误码
    virtual bool ErrorCodeUninstall(const QString &pluginID) = 0;
    //获取报警信息，如果不存在则返回""；
    virtual string GetErrorCode(int iErrSimpleId) = 0;


    //安装工艺UI
    virtual int InstallInoRobPluginUI(InoRobPluginPageAllInfo inoRobPluginPageAllInfo) = 0;

    //卸载工艺UI
    virtual int UninstallInoRobPluginUI(QString pluginID) = 0;

    //获取工艺UI
    virtual InoRobPluginPageAllInfo GetInoRobPluginUI(QString pluginID) = 0;

    /// <summary>
/// 获取安装信息
/// </summary>
/// <returns></returns>
    virtual InoRobotInstalledPlugins GetInoRobotInstalledPlugins()=0;

    virtual void UpdateInoRobotInstalledPlugins(InoRobotInstalledPlugins inoRobotInstalledPlugins) = 0;

    //状态信息
    virtual InoRobPluginStatusInfo GetStatusInfo(QString pluginID) = 0;
    //安装状态信息
    virtual int InstallStatusInfo(InoRobPluginStatusInfo info) = 0;
    //卸载状态信息
    virtual int UnInstallStatusInfo(QString pluginID) = 0;

Q_SIGNALS:
    // 同步工艺指令信号
    void syncInoRobPluginCommand(QString strPluginID);
    // 同步工艺指令信号
    void syncInoRobPluginCommandV2(QString strPluginID, QString strPath);
    // 卸载工艺指令信号
    void unInoRobPluginCommand(QString strPluginID);

    // 同步工艺UI信号
    void syncInoRobPluginUI(QString strPluginID);
    // 卸载工艺UI信号
    void unInoRobPluginUI(QString strPluginID);
    //打开指令编辑页面 strInfo格式用#分割如"ArcData#1"
    void openCmdUI(QString strInfo);
    /// <summary>
    /// 更新标题栏信息
    /// </summary>
    /// <param name="strPluginID">工艺strPluginID，如果为""则全部不显示 </param>
    void updateStatusInfo(QString strPluginID);

    //通用消息 strInfo格式用#分割如"ArcData#1"
    void universalMessage(QString strInfo);
};
}  // namespace InoRobBusiness
