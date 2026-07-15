#pragma once

#include <QObject>
#include <QMetaEnum>
#include <QMetaType>
#include <QString>
#include "authority_global.h"

enum AuthorityFilter {
    AuthorityFilter_All = 0,
    AuthorityFilter_Default,
    AuthorityFilter_Advanced,
    AuthorityFilter_Manage,
    AuthorityFilter_Factory,
    AuthorityFilter_Editable,
    AuthorityFilter_Inheritable,
    AuthorityFilter_Changable,
};

class AUTHORITY_EXPORT Authority : public QObject
{
    Q_OBJECT

public:
    enum AuthLevel {
        VirtualController = -9,
        Disconnect,
        DragTeaching,
        TPLostControl1,
        TPLostControl2,
        ProjectStartContinue,
        ProjectPause,
        AutoMode,
        GetPoint,
        Unknown,
        CustomUser,
        UserAccess,
        CustomEdit,
        EditAccess,
        CustomManage,
        ManageAccess,
        FactoryAccess
    };
    Q_ENUM(AuthLevel)

    Authority();
    Authority(const QString &sAuthName, const Authority::AuthLevel &authLevel,
              const QString &sPassword = QString());
    Authority(const Authority &other);
    Authority &operator=(const Authority &other);
    bool operator==(const Authority &other) const;
    bool operator!=(const Authority &other) const;
    bool operator<(const Authority &other) const;

    bool isValid() const;

    QString authName() const;
    void setAuthName(const QString &sAuthName);

    Authority::AuthLevel authLevel() const;
    void setAuthLevel(const Authority::AuthLevel &authLevel);

    QString authPassword() const;
    void setAuthPassword(const QString &sPassword);

    static QString authTypeStrFromLevel(const Authority::AuthLevel &level);
    static Authority::AuthLevel authLevelFromType(const QString &sType);

    static QString authorityNameStr(const Authority &authority);
    static QString authorityNameStr(const QString &sName,
                                    const Authority::AuthLevel &level);
    static QString authorityAvator(const Authority::AuthLevel &level);
    static QString authorityIcon(const Authority::AuthLevel &level);
    static QString authorityTip(const QString &sName,
                                const Authority::AuthLevel &level);

private:
    void copyOthertoSelf(const Authority &other);

private:
    QString     m_sAuthName;
    AuthLevel   m_authLevel;
    QString     m_sPassword;
};

uint qHash(const Authority &value);

class AUTHORITY_EXPORT FuncAuthority
{
public:
    enum FuncAuth {
        FuncAuth_Unknow = -1,
        FuncAuth_Disable,
        FuncAuth_Enable,
        FuncAuth_Inherit,
    };

    FuncAuthority();
    FuncAuthority(const QString &sFuncName, const FuncAuth &funcAuth);
    FuncAuthority(const FuncAuthority &other);
    FuncAuthority &operator=(const FuncAuthority &other);
    bool operator==(const FuncAuthority &other) const;
    bool operator!=(const FuncAuthority &other) const;

    QString funcName() const;
    void setFuncName(const QString &sFuncName);

    FuncAuth funcAuth() const;
    void setFuncAuth(const FuncAuth &auth);

    QString funcAuthStr() const;

private:
    void copyOthertoSelf(const FuncAuthority &other);

private:
    QString m_sFuncName;
    FuncAuth m_funcAuth;
};

class AUTHORITY_EXPORT PluginAuthority
{
public:
    PluginAuthority();
    explicit PluginAuthority(const QString &pluginName);
    virtual ~PluginAuthority();

    PluginAuthority(const PluginAuthority &other);
    PluginAuthority &operator=(const PluginAuthority &other);
    bool operator==(const PluginAuthority &other) const;
    bool operator!=(const PluginAuthority &other) const;

    bool isValid() const;
    bool isFuncAuthorityExist(const FuncAuthority &funcAuth);

    bool addFuncAuthority(const FuncAuthority &funcAuth);
    bool removeFuncAuthority(const FuncAuthority &funcAuth);
    void modifyFuncAuthority(const QString &funcName,
                             const FuncAuthority::FuncAuth &funcAuth);
    void modifyFuncAuthority(const FuncAuthority &funcAuth);

    QString pluginName() const;
    void setPluginName(const QString &pluginName);

    QVector<FuncAuthority> funcAuthorities() const;
    QStringList funcNames();

    FuncAuthority::FuncAuth getFuncAuthority(const QString &funcName);

private:
    void copyOthertoSelf(const PluginAuthority &other);

private:
    QString m_sPluginName;
    QVector<FuncAuthority>        m_vecFuncAuthorities;
};
