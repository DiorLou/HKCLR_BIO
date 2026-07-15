#pragma once

#include "abstractwidget.h"
#include "authority.h"
#include "dialog_global.h"

namespace Ui
{
class CurrentAuthorityForm;
}

class DIALOG_EXPORT CurrentAuthorityForm
    : public AbstractWidget<Ui::CurrentAuthorityForm>
{
    Q_OBJECT

public:
    explicit CurrentAuthorityForm(QWidget *parent = nullptr);
    ~CurrentAuthorityForm();

    void updateCurrentAuthority();

protected:
    virtual void retranslateUi();

private slots:
    void on_pbn_close_clicked();
    void on_pbn_changeAuthority_clicked();

private:
    Ui::CurrentAuthorityForm *ui;

    bool m_isConnected;
};
