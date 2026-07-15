#pragma once

#include <QList>
#include "metatype_global.h"

class METATYPE_EXPORT FuncAuthority
{
public:
    FuncAuthority(const QString &sFuncName, bool isEnable);
    FuncAuthority(const FuncAuthority &other);
    FuncAuthority &operator=(const FuncAuthority &other);
    bool operator==(const FuncAuthority &other) const;
    bool operator!=(const FuncAuthority &other) const;

private:
    void copyOthertoSelf(const FuncAuthority &other);

private:
    QString m_sFuncName;
    bool m_isEnable;
};
