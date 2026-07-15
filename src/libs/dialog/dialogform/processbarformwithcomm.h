#pragma once

#include "abstractwidget.h"
#include "dialog_global.h"
class RobotEventInfo;

namespace Ui {
class ProcessBarFormWithComm;
}

class DIALOG_EXPORT ProcessBarFormWithComm : public AbstractWidget<Ui::ProcessBarFormWithComm>
{
    Q_OBJECT

public:
    explicit ProcessBarFormWithComm(QWidget *parent = 0);
    ~ProcessBarFormWithComm();

    static ProcessBarFormWithComm* instance();

    void processEvent(const RobotEventInfo &robotEventInfo);

    //应当在显示前设置AbstractCmd::CmdType,
    //percentType用于通讯获取当前进度，stopType用于终止
    //进度为100 或者终止成功自动隐藏当前dialog
    //当stopType = -1时，禁用停止按键
    void setCommunicationType(QString title,
                              int percentType, int stopType = -1,
                              QVariant percentVariant = QVariant(), QVariant stopVariant= QVariant());
    void setAutoProcessbarBaseOnTimer(bool isAuto);
protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void slot_timeout();

    void on_pbn_stop_clicked();

private:
    Ui::ProcessBarFormWithComm *ui;

    QTimer *m_timer;

    void showDialog();
    void hideDialog(QString tips);

    QString m_taskName;
    int m_percentType;
    int m_stopType;
    QVariant m_stopVariant;
    QVariant m_percentVariant;
    bool m_isConnected = false;
    bool m_autoProcessbarBaseOnTimer = false;
};
