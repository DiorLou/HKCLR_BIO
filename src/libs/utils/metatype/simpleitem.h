#pragma once

#include "metatype_global.h"
#include <QVariant>
#ifdef INOCOBOTTP_MSVC_QT5
class METATYPE_EXPORT SimpleItem
{
public:
    SimpleItem();
    virtual ~SimpleItem();
    virtual QVariant data(int column);
    virtual bool setData(int column, const QVariant &data);
};
#else
class METATYPE_EXPORT SimpleItem
{
public:
    SimpleItem()
    {
    }
    virtual ~SimpleItem()
    {
    }
    virtual QVariant data(int column)
    {
        Q_UNUSED(column);
        return QVariant();
    }
    virtual bool setData(int column, const QVariant &data)
    {
        Q_UNUSED(column);
        Q_UNUSED(data);
        return true;
    }
};
#endif

