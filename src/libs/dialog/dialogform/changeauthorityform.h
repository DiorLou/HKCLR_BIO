#pragma once

#include "abstractwidget.h"
#include "dialog_global.h"

namespace Ui
{
class ChangeAuthorityForm;
}

class DIALOG_EXPORT ChangeAuthorityForm
    : public AbstractWidget<Ui::ChangeAuthorityForm>
{
    Q_OBJECT

public:
    explicit ChangeAuthorityForm(QWidget *parent = nullptr);
    ~ChangeAuthorityForm();

    void clearPassword();

     Q_INVOKABLE void updateCmbAuthority();

protected:
    virtual void retranslateUi();
    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent *evt);

private:
    void setPasswordFormVisible(bool isVisible);
    void setConfirmBtnEnabled(bool isEnabled);

private slots:
    void on_pbn_eye_clicked(bool checked);
    void on_pbn_confirm_clicked();
    void on_cmb_authority_currentTextChanged(const QString &text);

    void on_pbn_back_clicked();
    void on_pbn_close_clicked();

private:
    Ui::ChangeAuthorityForm *ui;
};
