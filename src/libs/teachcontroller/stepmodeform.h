#ifndef STEPMODEFORM_H
#define STEPMODEFORM_H

#include "abstractwidget.h"
#include "teachcontroller_global.h"
#include "motionparam.h"
#include "metatype.h"

namespace Ui
{
class StepModeForm;
}

class TEACHCONTROLLER_EXPORT StepModeForm : public AbstractWidget<Ui::StepModeForm>
{
    Q_OBJECT

public:
    explicit StepModeForm(QWidget *parent = nullptr);
    ~StepModeForm();

public:
    bool IsChecked();
    double GetPosValue();
    double GetOriValue();
    double GetJointValue();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void retranslateUi();

private slots:
    void on_radio_inchingmove_g1_clicked();
    void on_radio_inchingmove_g2_clicked();
    void on_radio_inchingmove_g3_clicked();
    void on_radio_inchingmove_u_clicked();

    void slot_setstepgrade_result(QObject *object, bool isSuccess);
    void slot_setstepparams_result(QObject *object, bool isSuccess);
    void slot_getstepparams_result(QObject *object, bool isSuccess,
                                   const InoMoveStepSizePara &params);
    void slot_stepgrade_changed(InoMoveStepGrade grade);

    void on_grp_stepMode_clicked(bool checked);

    void slot_contimotion();

    void slot_controllerConnectionStatusChanged(ControllerConnectionState status);

    void on_pbn_posdown_clicked();
    void on_pbn_oridown_clicked();
    void on_pbn_jointdown_clicked();
    void on_pbn_posup_clicked();
    void on_pbn_oriup_clicked();
    void on_pbn_jointup_clicked();

    void slot_vk_ok_clicked();

private:
    void setInchingMovement(double g1, double g2, double g3, bool bEnable);
    void setStepGrade(InoMoveStepGrade grd, double posoff = 0,
                      double orioff = 0, double jointoff = 0);
    void setUGradeOnly();
    void setStepParams(const InoMoveStepSizePara &params);
    void updateGradeGUI();
    void refreshEnable();

private:
    Ui::StepModeForm *ui;

    static InoMoveStepGrade m_grd;
    bool m_bSetParamsing = false;
    InoMoveStepSizePara m_params;

    bool bContiMotion = false;
};

#endif  // STEPMODEFORM_H
