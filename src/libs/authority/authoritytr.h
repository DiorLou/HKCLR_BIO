#pragma once
#include <QObject>
#include "authority_global.h"

class AUTHORITY_EXPORT AuthorityTr : public QObject
{
    Q_OBJECT
public:
    AuthorityTr(QObject* parent) : QObject(parent)
    {
    }
    ~AuthorityTr()
    {
    }
};


