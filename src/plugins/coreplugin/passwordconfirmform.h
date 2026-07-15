#pragma once

#include "abstractwidget.h"
#include "core_global.h"
namespace Ui {
class PasswordConfirmForm;
}

#define FUNCID_MODECHANGED          "FuncId_ModeChanged"
#define FUNCID_SAFETY               "FuncId_Safety"
#define FUNCID_FACTORY_AUTHORITY    "FuncId_FactoryAuthority"

const QString SAFETY_PASSWD = "240115";

class CORE_EXPORT PasswordConfirmForm : public AbstractWidget<Ui::PasswordConfirmForm>
{
    Q_OBJECT

public:
    static PasswordConfirmForm *instance();

    explicit PasswordConfirmForm(QWidget *parent = 0);
    ~PasswordConfirmForm();

    void setArgs(const QString &sFuncId, const QString &sTitle, const char *sPasswd = nullptr);

protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void signal_passwd_confirm_result(const QString &sFuncId, bool isCorrect);

private slots:
    void on_pbn_cancel_clicked();
    void on_pbn_submit_clicked();

    void slot_edit_finished();

    void on_pbn_eye_clicked(bool checked);

    void on_pbn_close_clicked();

private:
    Ui::PasswordConfirmForm *ui;

    int m_inputIncorrectTimes = 0;
    QString s_passwd = SAFETY_PASSWD;
    QString s_funcId;
};
