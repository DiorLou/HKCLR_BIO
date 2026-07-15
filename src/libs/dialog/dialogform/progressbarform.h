#pragma once

#include "abstractwidget.h"
#include "dialog_global.h"

class RobotEventInfo;
class QTimer;

namespace Ui {
class ProgressBarForm;
}

class DIALOG_EXPORT ProgressBarForm : public AbstractWidget<Ui::ProgressBarForm>
{
    Q_OBJECT

public:
    explicit ProgressBarForm(QWidget *parent = 0);
    ~ProgressBarForm();

public slots:
    void processEvent(const RobotEventInfo &robotEventInfo);

protected:
    virtual void retranslateUi();

private:
    void startTaskIsTimeOutTimer();
    void stopTaskIsTimeOutTimer();

    void startUpdateUiTimer();
    void stopUpdateUiTimer();

    void showDialog();
    void hideDialog();

    void initData();

private slots:
    void slot_timeout();
    void slot_waitTimeout();

    void on_pbn_close_clicked();

private:
    Ui::ProgressBarForm *ui;

    QTimer *m_timerIsTaskTimeOut;  // 窗口执行定时器，超时自动隐藏
    QTimer *m_timerUpdateUI; // 进度条刷新定时器

    QString m_msg;
    int m_processInterval;
};
