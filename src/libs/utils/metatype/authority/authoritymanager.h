#pragma once

#include <QHash>
#include "authority.h"
#include "metatype_global.h"
#include "metatype.h"

class PluginAuthority;

class METATYPE_EXPORT AuthorityManager
{
public:
    static AuthorityManager *instance();
    virtual ~AuthorityManager();

    // 是否存在
    bool isAuthorityExist(const Authority &auth) const;
    bool isAuthorityExist(const QString &authName, const AuthType &authType) const;
    // 新增自定义权限
    bool addCustomAuthority(const Authority &auth,
                            const Authority &parentAuth);
    // 获取权限
    Authority getAuthority(const QString &authName, const AuthType &authType);
    // 移除自定义权限
    bool removeCustomAuthority(const QString &authName, const AuthType &authType);
    // 权限列表
    QVector<Authority> authorities() const;
    // 当前权限
    void setCurrentAuthority(const Authority &auth);
    Authority currentAuthority() const;

    // 权限对应的插件权限
    PluginAuthority pluginAuthority(const QString &authName,
                                    const AuthType &authType);
    PluginAuthority pluginAuthority(const Authority &auth);

    void readAuthXmlFile();
    void writeAuthXmlFile();

private:
    AuthorityManager();

private:
    Authority m_curAuthority = {QObject::tr("Edit access"), AuthType_Edit, ""};
    QHash<Authority, PluginAuthority> m_hashAuthorities;
};
