#pragma once

#include <QObject>
#include <QString>
#include <set>
#include "authority.h"

class BuiltInAuthorityManager
{
public:
    explicit BuiltInAuthorityManager();
    ~BuiltInAuthorityManager();

    void addBuiltInAuthority(const Authority &authority);
    void deleteBuiltInAuthority(const Authority &authority);
    void clearBuiltInAuthority();

    bool isEmpty();
    Authority useBuiltInAuthority();
    Authority getBuiltInAuthority(const Authority::AuthLevel &authLevel);

private:
    bool isContainsAuthority(const Authority::AuthLevel &authLevel);

private:
    std::set<Authority> m_setBuiltInAuthorities;
};

