#pragma once

#include "multithreadtools_global.h"
#include <QObject>

class QMutex;
class QWaitCondition;

class MULTITHREADTOOLS_EXPORT MainThreadEngine : public QObject
{
    Q_OBJECT

public:
    static MainThreadEngine *instance();
    explicit MainThreadEngine(QObject *parent = 0);

    Q_INVOKABLE void showApp();
    Q_INVOKABLE void hideApp();
};
