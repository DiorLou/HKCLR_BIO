#pragma once

#include "abstractwidget.h"
#include "cobotlog.h"
namespace Ui
{
class MainWidgetLogForm;
}
class QTextBrowser;
class LogModel;
class QTimer;
class MainWidgetLogForm : public AbstractWidget<Ui::MainWidgetLogForm>
{
    Q_OBJECT


public:
    explicit MainWidgetLogForm(QWidget *parent = nullptr);
    ~MainWidgetLogForm();
    Q_INVOKABLE void addLogMsg(int type, const QString &msg);
    Q_INVOKABLE void hideLogWidget();
    void logViewEnabled(bool isEnabled);
protected:
    virtual void retranslateUi();
    virtual void showEvent(QShowEvent *ev);
private slots:
    void on_pbn_close_clicked();
    void slot_FoucusChanged(QWidget *old, QWidget *now);
    void slot_print(CobotLog::InoInfoType type, const QString &msg);
    void slot_log(CobotLog::InoLogType type, const QString &msg);

    void on_tabWidget_currentChanged(int index);

    void on_pbn_clear_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_7_clicked();
private:
    void updateUI(bool isMoveCursor = false);
    Ui::MainWidgetLogForm *ui;
    void addLogMsg(QTextBrowser* edit, const QString &msg);
    LogModel *m_model;
    QWidget * m_logWidget;
    QTimer *m_timer;
    QStringList m_historyAlarm;

    // void on_btn_clear_clicked();
    // void on_pbn_clearAll_clicked();
    // void on_pbn_clearInfo_clicked();
    // void on_pbn_clearWarning_clicked();
    // void on_pbn_clearError_clicked();
    // void on_pbn_claerOperation_clicked();
    // void on_pbn_clearLog_clicked();
    bool m_messageBoxShow  = false;
    void setCurrentIndex(int index);
};
