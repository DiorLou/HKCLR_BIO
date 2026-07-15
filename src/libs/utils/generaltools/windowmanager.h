#pragma once

#include "generaltools_global.h"
#include <QObject>
#include <QQueue>

class QTimer;

enum WindowCmd {
    WindowCmd_MainWidgetShow,
    WindowCmd_MainWidgetHide,
    WindowCmd_MainWidgetMinimize,
    WindowCmd_DialogContainerFormShow,
    WindowCmd_DialogContainerFormHide
};

class GENERALTOOLS_EXPORT WindowManager : public QObject
{
    Q_OBJECT

public:
    static WindowManager *instance();
    explicit WindowManager(QObject *parent = 0);

    void enqueueCmdInfo(const WindowCmd &cmdType);

private slots:
    void slot_processTasks();

private:
    QQueue<WindowCmd> m_mainWidgetCmdQueue;
    QQueue<WindowCmd> m_dialogContainerFormCmdQueue;
    QTimer *m_timer;
};
