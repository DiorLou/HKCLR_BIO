#pragma once

#include "abstractwidget.h"
#include "dialog_global.h"
namespace Ui
{
class LockScreenForm;
}

class DIALOG_EXPORT LockScreenForm : public AbstractWidget<Ui::LockScreenForm>
{
    Q_OBJECT

public:
    explicit LockScreenForm(QWidget *parent = 0);
    ~LockScreenForm();

    void setWidgetCaller(QWidget *senderWidget);

protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_pbn_enter_clicked();

    void on_pbn_capsLock_clicked(bool checked);

    void on_pbn_leftShift_clicked(bool checked);

    void on_pbn_rightShift_clicked(bool checked);

    void slot_keyClicked();

    void on_pbn_clear_clicked();

    void on_pbn_backspace_clicked();

    void on_pbn_space_clicked();

    void on_pbn_left_clicked();

    void on_pbn_right_clicked();

    void on_pbn_table_clicked();

    void on_pbn_eye_clicked(bool checked);

private:
    Ui::LockScreenForm *ui;

    void capsLockEnable(bool enable);

    void keyClicked(QString key);
    void funcKeyClicked(int key);

    QWidget *m_widgetCaller;
};
