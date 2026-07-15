#pragma once

#include <QObject>
#include <QHash>
#include "authority.h"
#include "authority_global.h"
#include "builtinauthoritymanager.h"

class PluginAuthority;

enum AuthorityFileType {
    AuthorityFileType_Unknown = 0,
    AuthorityFileType_Default,
    AuthorityFileType_Backup,
    AuthorityFileType_User,
    AuthorityFileTypeCount
};

enum ModifyType {
    ModifyType_Unknown = 0, // 未知
    ModifyType_Not,         // 不能修改
    ModifyType_False,       // 只能改为false,适用于自身权限
    ModifyType_ALL,         // 任意修改
    ModifyTypeCount
};

enum FileError {
    NoError = 0,
    DefaultXmlNotExist,     // 出厂默认权限管理信息xml文件不存在
    CopyToUserXmlError,     // 拷贝权限管理信息xml文件为用户xml失败
    CopyToBackupXmlError,   // 拷贝文件权限管理信息xml文件为备份xml失败
    FileErrorCount
};

class AUTHORITY_EXPORT AuthorityManager : public QObject
{
    Q_OBJECT
public:
    static AuthorityManager *instance();
    virtual ~AuthorityManager();

    // 默认权限
    void setDefaultAuthority(const Authority &auth);
    Authority defaultAuthority();

    // 当前用户权限
    void setCurrentAuthority(const Authority &auth);
    Authority currentAuthority() const;

    // 是否启用内置权限
    bool isUseBuiltInAuthority();

    void clearUsingAuthority();
    void appendUsingAuthority(const Authority &authority);
    QList<Authority> usingAuthorityList() const;

    // 权限管理xml版本
    void setVersion(const QString &version);
    QString version() const;

    // 是否存在
    bool isAuthorityExist(const Authority &auth) const;
    bool isAuthorityExist(const QString &sAuthName,
                          const Authority::AuthLevel &authLevel) const;

    bool isCustomManageAuthority(const Authority::AuthLevel &authLevel);
    bool isCustomAuthority(const Authority::AuthLevel &authLevel);
    bool isInheritableAuthority(const Authority::AuthLevel &authLevel);

    bool isBuiltInAuthority(const Authority::AuthLevel &authLevel);
    bool isBuiltInAuthority(const Authority &authority);

    bool isDefaultAuthority(const Authority::AuthLevel &authLevel);
    bool isAdvancedAuthority(const Authority::AuthLevel &authLevel) const;

    bool isCurrentManageAuthority();
    bool isCurrentFactoryAuthority();
    bool isUsingUserAuthority();
    bool isUsingAdvancedAuthority();
    bool isUsingDisconnectAuthority();

    // 根据内置、常规类型获取自定义等级
    Authority::AuthLevel getCustomAuthLevel(const Authority::AuthLevel &authLevel);

    // 新增自定义权限
    bool addCustomAuthority(const Authority &auth,
                            const Authority &parentAuth, QString &msg);

    void updateFuncList(const QString &sPluginName,
                        const QList<QVariant> funcNameList);
    void updateFuncAuthority(const QString &sPluginName,
                             const QList<QString> funcNameList);

    void modifyFuncAuthority(
        const QString &sAuthName, const Authority::AuthLevel &authLevel,
        const QString &sPluginName, const QString &sFuncName,
        const FuncAuthority::FuncAuth &funcAuth);

    bool isAuthorityModified();
    void clearModifiedAuthority();

    // 获取权限
    Authority getAuthority(const Authority::AuthLevel &authLevel);
    Authority getAuthority(const QString &sAuthName,
                           const Authority::AuthLevel &authLevel);

    // 移除自定义权限
    bool removeCustomAuthority(
        const QString &sAuthName, const Authority::AuthLevel &authLevel,
        QString &msg);
    // 权限过滤
    QVector<Authority> getAuthorities(
        const AuthorityFilter &filter = AuthorityFilter_All) const;

    // 更新权限
    void updateAuthority(const Authority::AuthLevel &authLevel = Authority::Unknown,
                         const QString &authName = QString());

    // 自动切换权限
    bool autoChangeAuthority(
        const Authority::AuthLevel &authLevel = Authority::Unknown,
        const QString &authName = QString(),
        bool isInit = false);

    // 验证类型和密码
    bool checkAuthorityValid(const Authority &authority);

    // 所有权限
    QMap<Authority, QVector<PluginAuthority> > allAuthorities();

    // 权限对应的插件权限
    QVector<PluginAuthority> pluginAuthority(
        const QString &sAuthName, const Authority::AuthLevel &authLevel);
    QVector<PluginAuthority> pluginAuthority(const Authority &auth);

    // 逻辑与，确定功能最终的权限启用情况
    QVector<PluginAuthority> logicalPluginAuthority(const QList<Authority> &authList);

    // 加载
    bool loadAllAuthorityInfo();

    // 保存
    bool saveAllAuthorityInfo(
        QString &msg,
        QMap<Authority, QVector<PluginAuthority>> mapAuthorities = {});
    // 检查修改并保存
    bool checkAndSaveAuthorityInfo(QString &msg);

    // 获取权限函数名
    QList<QVariant> getPluginFuncAuthorities(const QString &sPluginName);

    // 通知
    void notifyPluginApplyAuthorities(bool isInit = false);

    // 修改权限类型
    ModifyType currentModifyType(const Authority::AuthLevel &authLevel);

    QString funcAuthNameStr(const QString &sFuncAuthName);

    // 恢复出厂默认权限管理信息
    bool restoreDefaultAuthorityInfo();

    void retranslateAuthoritySpec();

private:
    AuthorityManager();

    QList<Authority::AuthLevel> getBuiltInAuthLevels() const;
    QList<Authority::AuthLevel> getDefaultAuthLevels() const;
    QList<Authority::AuthLevel> getAdvanceAuthLevels() const;
    QList<Authority::AuthLevel> getEditableAuthLevels() const;
    QList<Authority::AuthLevel> getInheritableAuthLevels() const;
    QList<Authority::AuthLevel> getChangableAuthLevels() const;

    QString getAuthorityFileName(int type);
    void backupAuthorityFile(const QString &sAuthFileName);

    // 检查当前使用的权限
    Authority checkUsingAuthority();

    bool updatePluginAuthority();
    // xml升级
    bool upgradePluginAuthorities();

    FuncAuthority::FuncAuth getCurAuthorityFuncAuth(const QString &sPluginName,
                                                    const QString &sFuncName);

    bool isUsingAuthorityChanged();

Q_SIGNALS:
    void signal_changeAuthoritySuccess(const QString &sAuthName,
                                       bool isAuthorityChanged);

private:
    QString m_sVersion;

    Authority m_defaultAuthority;
    Authority m_curAuthority;   // 当前非内置权限
    QList<Authority> m_usingAuthorityList; // 正在使用的权限列表
    QList<Authority> m_prevUsedAuthorityList; // 用于存放上一轮生效的权限，防止重复

    QMap<Authority, QVector<PluginAuthority>> m_mapAuthorities; // xml中权限树数据
    QMap<Authority, QVector<PluginAuthority>> m_mapModifiedAuthorities; // 权限树修改中数据
    QList<QVariant> m_authorityNameAndStrList; // 国际化

    bool m_isUseBuiltInAuth;
    bool m_isConnected;
};
