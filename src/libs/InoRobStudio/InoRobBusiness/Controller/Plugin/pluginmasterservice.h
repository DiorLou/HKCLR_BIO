#ifndef PLUGINMASTERSERVICE_H
#define PLUGINMASTERSERVICE_H
#include "IInoRobPluginMasterService.h"
#include "IInoRobBusiness.h"
namespace InoRobBusiness
{
class PluginMasterService : public IInoRobPluginMasterService
{
private:
    IDataSrvBase *_pDataService = nullptr;
    // 连接
    IConnection *_pConnection = nullptr;

private:
    QList<InoRobPluginErrorCode> _InoRobPluginErrorCodeList;  // 错误码列表

    QList<InoRobPluginCommandAllInfo> _InoRobPluginCommandAllInfoList;  // 指令列表
    QList<InoRobPluginPageAllInfo> _InoRobPluginPageAllInfoList;        // UI信息列表
    InoRobotInstalledPlugins _currInstalledPlugins;                     // 当前已安装的插件信息
    QList<InoRobPluginStatusInfo>_InoRobPluginStatusInfoList;
public:
    int  Plugin_memcpy(void* _Dst, void const* _Src, size_t _Size)
    {
        // 将指针转换为 char*，因为 char 是大小为 1 的字节  
        char* d = static_cast<char*>(_Dst);
        const char* s = static_cast<const char*>(_Src);

        // 使用循环复制每一个字节  
        for (size_t i = 0; i < _Size; ++i) {
            d[i] = s[i];
        }

        // 返回目标指针  
        return 0;
        // return memcpy_s(_Dst, _Size, _Src, _Size);
    }

    int  Plugin_memcpy(void* _Dst, size_t _Size1, void const* _Src, size_t _Size)
    {
        return Plugin_memcpy(_Dst, _Src, _Size);
        // return memcpy_s(_Dst, _Size, _Src, _Size);
    }
public:
    PluginMasterService(string name, IDataSrvBase *dataService, IConnection *connection);

    // 批量增加插件错误码
    bool ErrorCodeInstall(const QList<InoRobPluginErrorCode> &pluginErrorCodeList);
    // 移除指定插件的所有错误码
    bool ErrorCodeUninstall(const QString &pluginID);
    // 获取报警信息，如果不存在则返回""；
    string GetErrorCode(int iErrSimpleId);

    int UnRegistCmd(InoRobPluginCommandAllInfo inoRobPluginCommandAllInfo);
    virtual int UninstallInoRobPluginCommand(QString pluginID) override;
    virtual int InstallInoRobPluginCommandV2(QString strPath, QString CmdEnTypeName)override;

    // 安装工艺指令
    virtual int InstallInoRobPluginCommand(InoRobPluginCommandAllInfo inoRobPluginCommandAllInfo) override;
    // 获取指令信息
    virtual InoRobPluginCommandAllInfo GetInoRobPluginCommand(QString pluginID) override;

    // 安装工艺UI
    virtual int InstallInoRobPluginUI(InoRobPluginPageAllInfo inoRobPluginPageAllInfo) override;
    // 卸载工艺UI
    virtual int UninstallInoRobPluginUI(QString pluginID) override;
    // 获取工艺UI
    virtual InoRobPluginPageAllInfo GetInoRobPluginUI(QString pluginID) override;
    /// <summary>
    /// 获取安装信息
    /// </summary>
    /// <returns></returns>
    virtual InoRobotInstalledPlugins GetInoRobotInstalledPlugins() override;

    virtual void UpdateInoRobotInstalledPlugins(InoRobotInstalledPlugins inoRobotInstalledPlugins) override;

    virtual InoRobPluginStatusInfo GetStatusInfo(QString pluginID) override;


    // 通过 IInoRobPluginMasterService 继承
    virtual int InstallStatusInfo(InoRobPluginStatusInfo info) override;

    virtual int UnInstallStatusInfo(QString pluginID) override;

};
}  // namespace InoRobBusiness
#endif  // PLUGINMASTERSERVICE_H
