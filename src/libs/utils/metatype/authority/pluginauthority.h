#pragma once

#include <QList>
#include "metatype_global.h"

class FuncAuthority;

class METATYPE_EXPORT PluginAuthority
{
public:
    PluginAuthority();
    explicit PluginAuthority(const QString &sPluginName);
    virtual ~PluginAuthority();

    PluginAuthority(const PluginAuthority &other);
    PluginAuthority &operator=(const PluginAuthority &other);
    bool operator==(const PluginAuthority &other) const;
    bool operator!=(const PluginAuthority &other) const;

    bool isValid();

private:
    void copyOthertoSelf(const PluginAuthority &other);

private:
    QString m_sPluginName;
    QVector<FuncAuthority>        m_vecFuncAuthorities;
};
