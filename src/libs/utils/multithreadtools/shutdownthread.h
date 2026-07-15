#pragma once

#include "multithreadtools_global.h"
#include <QThread>

class QMutex;
class QWaitCondition;

class MULTITHREADTOOLS_EXPORT ShutdownThread : public QThread
{
    Q_OBJECT

public:
    static ShutdownThread *instance();
    explicit ShutdownThread(QObject *parent = 0);
    ~ShutdownThread();
    Q_INVOKABLE void quit();

protected:
    void run();

private:
    QMutex *m_quitConditionMutex;
    QWaitCondition *m_quitCondition;
};
