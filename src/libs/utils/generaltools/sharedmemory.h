#pragma once

#include "generaltools_global.h"
#include <QSharedMemory>
#include <QMap>

class QMutex;

class GENERALTOOLS_EXPORT SharedMemory : public QSharedMemory
{
    Q_OBJECT

public:
    explicit SharedMemory(const QString &key = QString());
    ~SharedMemory();
    void setKey(const QString &key);

    static void readInfo(const QString &key, QString &info);
    void writeInfo(const QString &info);

private:
    QMutex *m_mutex;
};
