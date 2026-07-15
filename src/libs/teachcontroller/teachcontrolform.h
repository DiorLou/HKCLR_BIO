#ifndef TEACHCONTROLFORM_H
#define TEACHCONTROLFORM_H

#include "abstractwidget.h"

#include "motionparam.h"
#include "metatype.h"
#include "teachcontroller_global.h"
#include <QTimer>
#include <QPushButton>
class CoordParam;
class StepModeForm;
class CoordDisplayForm;
class CoordSelectForm;

namespace Ui
{
class TeachControlForm;
}

class TEACHCONTROLLER_EXPORT TeachControlForm : public AbstractWidget<Ui::TeachControlForm>
{
    Q_OBJECT

public:
    explicit TeachControlForm(QWidget *parent = nullptr);
    ~TeachControlForm();

public:
    void SetReleativeWidgets(StepModeForm *stepModeForm,
                             CoordSelectForm *coordSelectForm,
                             CoordDisplayForm *coordDisplayForm);

    void UpdateUI();

    void setJointBtnSize(const QSize & size);
protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void retranslateUi();
signals:
    void singal_format_changed(int index);

private slots:
    void slot_pbn_joint_pressed();
    void on_pbn_joint_released();
    void slot_pbn_position_pressed();
    void slot_pbn_ori_pressed();

    void slot_teachMoveStop();

    void slot_axisMoveInterface_result(QObject *object, bool isSuccess);
    void slot_teachMoveControlInterface_result(bool isSuccess);

    void slot_mechine_unit_changed();

    void on_cmb_coordType_display_currentIndexChanged(int index);

    void slot_controllerConnectionStatusChanged(ControllerConnectionState status);

private:
    void setGroupBtnsEnable(QWidget *wgt, bool bEnable);

    void teachMoveStart(TeachMode teachMode, bool direction);
    void teachMoveStop(TeachMode teachMode, bool direction);

    CoordParam getCoordParamFromUI();
    QString getCoordTypeFromUI();

private:
    Ui::TeachControlForm *ui;

    StepModeForm *m_stepModeForm = nullptr;
    CoordSelectForm *m_coordSelectForm = nullptr;
    CoordDisplayForm *m_coordDisplayForm = nullptr;
    QTimer* m_timer;
    QPushButton* m_curButton;
};

#endif  // TEACHCONTROLFORM_H
