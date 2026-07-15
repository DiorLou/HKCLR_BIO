#ifndef COORDSELECTFORM_H
#define COORDSELECTFORM_H

#include "abstractwidget.h"
#include "coordparam.h"
#include "teachcontroller_global.h"

namespace Ui
{
class CoordSelectForm;
}

class TEACHCONTROLLER_EXPORT CoordSelectForm
    : public AbstractWidget<Ui::CoordSelectForm>
{
    Q_OBJECT

public:
    explicit CoordSelectForm(QWidget *parent = nullptr);
    ~CoordSelectForm();

    QString GetToolName();
    QString GetWObjName();
    int GetCoordIndex();

    void setConnectionsDefault(bool bEnable);
    void setConnectionsEnable(bool bEnable);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void retranslateUi();
signals:
    void signal_mechine_unit_changed();

private slots:
    void on_cmb_coordType_activated(int index);
    void on_cmb_toolNo_activated(int index);
    void on_cmb_wobjNo_activated(int index);
    void on_cmb_LoadNo_activated(int index);

    void slot_control_toolNo_Changed(int index);
    void slot_control_wobjNo_Changed(int index);
    void slot_control_LoadNo_Changed(int index);
    void slot_control_coordtype_changed(RobotCoordType type);

    void slot_settool_result(QObject *object, bool isSuccess, int toolId);
    void slot_setwobj_result(QObject *object, bool isSuccess, int wobjId);
    void slot_setload_result(QObject *object, bool isSuccess, int loadId);

    void slot_controllerConnectionStatusChanged(ControllerConnectionState status);

private:
    void updateUI();

private:
    Ui::CoordSelectForm *ui;

    bool m_bFistUpdate = true;
    bool m_bDefaultEnable = true;
};

#endif  // COORDSELECTFORM_H
