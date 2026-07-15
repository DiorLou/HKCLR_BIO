#pragma once

#include "abstractwidget.h"
#include "dialog_global.h"

namespace Ui
{
class CustomAuthorityForm;
}

class DIALOG_EXPORT CustomAuthorityForm
    : public AbstractWidget<Ui::CustomAuthorityForm>
{
    Q_OBJECT

public:
    explicit CustomAuthorityForm(QWidget *parent = nullptr);
    ~CustomAuthorityForm();

    void clearAuthorityName();

    Q_INVOKABLE void updateParentAuthorityTypeCmb();

protected:
    virtual void retranslateUi();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pbn_close_clicked();
    void on_pbn_cancel_clicked();
    void on_pbn_confirm_clicked();

private:
    Ui::CustomAuthorityForm *ui;
};
