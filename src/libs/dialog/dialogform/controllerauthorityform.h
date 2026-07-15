#pragma once

#include "abstractwidget.h"
#include "ctrlauthority.h"
const int SystemLayout_ControllerAuthorityForm = 4;

class ContainerRadioButton;

namespace Ui
{
class ControllerAuthorityForm;
}
class QButtonGroup;
class ControllerAuthorityForm : public AbstractWidget<Ui::ControllerAuthorityForm>
{
    Q_OBJECT

public:
    static ControllerAuthorityForm *instance();

    explicit ControllerAuthorityForm(QWidget *parent = 0);
    ~ControllerAuthorityForm();

    void initialize();
    void getFunctionEnabledList(QList<QVariant> &list);
private slots:
    void on_pbn_save_clicked();

    void on_rbn_teachpad_clicked();

    void on_rbn_ethernet_clicked();

    void on_rbn_remoteAll_clicked();

    void on_rbn_remoteSome_clicked();

    void on_pbn_update_clicked();

    void on_pbn_close_clicked();

    void slot_getControlAuthorityRes(QObject *obj, InoCtrlAuthority type, int speed);
protected:
    void showEvent(QShowEvent *ev);
    void retranslateUi();


private:
    Ui::ControllerAuthorityForm *ui;
    bool m_isConnected;
    void updateUI();
    int m_currentEditType = -1;
};

