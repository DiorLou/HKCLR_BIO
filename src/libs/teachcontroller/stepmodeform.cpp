#include "stepmodeform.h"
#include "ui_stepmodeform.h"
#include "cobotlog.h"
#include "communicationengine.h"
#include "messagebox.h"
#include "communication.h"
#include <QRegularExpressionValidator>

static const double NUM_STEP_VALUE = 0.001;
static const double NUM_MAX_STEP_VALUE = 10.000;
static const double NUM_MIN_STEP_VALUE = 0.010;

InoMoveStepGrade StepModeForm::m_grd = InoMoveStepGrade_None;

StepModeForm::StepModeForm(QWidget *parent) :
    AbstractWidget(0, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::StepModeForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    ui->pbn_posdown->setIconSize(ResolutionUtils::getRatioSize(28, 28));
    ui->pbn_posup->setIconSize(ResolutionUtils::getRatioSize(28, 28));
    ui->pbn_oridown->setIconSize(ResolutionUtils::getRatioSize(28, 28));
    ui->pbn_oriup->setIconSize(ResolutionUtils::getRatioSize(28, 28));
    ui->pbn_jointdown->setIconSize(ResolutionUtils::getRatioSize(28, 28));
    ui->pbn_jointup->setIconSize(ResolutionUtils::getRatioSize(28, 28));

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setstepgrade_result,
            this,
            &StepModeForm::slot_setstepgrade_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setstepparams_result,
            this,
            &StepModeForm::slot_setstepparams_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_getstepparams_result,
            this,
            &StepModeForm::slot_getstepparams_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_contimotion,
            this,
            &StepModeForm::slot_contimotion, Qt::DirectConnection);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_stepgrade_changed,
            this,
            &StepModeForm::slot_stepgrade_changed, Qt::UniqueConnection);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &StepModeForm::slot_controllerConnectionStatusChanged);

    ui->edit_position->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->edit_ori->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->edit_joint->setProperty("Imt", Imt_FormattedNumbersOnly);

    ui->edit_position->setRange(0.01, 10);
    ui->edit_ori->setRange(0.01, 10);
    ui->edit_joint->setRange(0.01, 10);

    ui->grp_valus->setEnabled(false);
}

StepModeForm::~StepModeForm()
{
    delete ui;
}

bool StepModeForm::IsChecked()
{
    return ui->grp_stepMode->isChecked();
}

double StepModeForm::GetPosValue()
{
    return ui->edit_position->text().toDouble();
}

double StepModeForm::GetOriValue()
{
    return ui->edit_ori->text().toDouble();
}

double StepModeForm::GetJointValue()
{
    return ui->edit_joint->text().toDouble();
}

void StepModeForm::showEvent(QShowEvent *event)
{
    updateGradeGUI();

    // connect(CommunicationEngine::instance(),
    //         &CommunicationEngine::signal_stepgrade_changed,
    //         this,
    //         &StepModeForm::slot_stepgrade_changed, Qt::UniqueConnection);

    // connect(CommunicationEngine::instance(),
    //         &CommunicationEngine::signal_controllerConnectionStatusChanged,
    //         this, &StepModeForm::slot_controllerConnectionStatusChanged);

    connect(ui->edit_position,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);

    connect(ui->edit_ori,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);

    connect(ui->edit_joint,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);
}

void StepModeForm::hideEvent(QHideEvent *event)
{
    // disconnect(CommunicationEngine::instance(),
    //         &CommunicationEngine::signal_stepgrade_changed,
    //         this,
    //         &StepModeForm::slot_stepgrade_changed);

    // disconnect(CommunicationEngine::instance(),
    //         &CommunicationEngine::signal_controllerConnectionStatusChanged,
    //         this, &StepModeForm::slot_controllerConnectionStatusChanged);

    disconnect(ui->edit_position,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);

    disconnect(ui->edit_ori,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);

    disconnect(ui->edit_joint,
            &LineEdit::focusOut,
            this,
            &StepModeForm::slot_vk_ok_clicked);
}

void StepModeForm::on_radio_inchingmove_g1_clicked()
{
    setStepGrade(InoMoveStepGrade_G1);
}

void StepModeForm::on_radio_inchingmove_g2_clicked()
{
    setStepGrade(InoMoveStepGrade_G2);
}

void StepModeForm::on_radio_inchingmove_g3_clicked()
{
    setStepGrade(InoMoveStepGrade_G3);
}

void StepModeForm::on_radio_inchingmove_u_clicked()
{
    setUGradeOnly();
}

void StepModeForm::slot_setstepgrade_result(QObject *object, bool isSuccess)
{
    if (object != this) return;

    if (!isSuccess) {
        MessageBox::warning(tr("Failed to set jog level."));
        return;
    }

    if (m_grd == InoMoveStepGrade_G1) {
        ui->radio_inchingmove_g1->setChecked(true);
        setInchingMovement(0.050, 0.050, 0.050, false);
    } else if (m_grd == InoMoveStepGrade_G2) {
        ui->radio_inchingmove_g2->setChecked(true);
        setInchingMovement(0.500, 0.500, 0.500, false);
    } else if (m_grd == InoMoveStepGrade_G3) {
        ui->radio_inchingmove_g3->setChecked(true);
        setInchingMovement(2.000, 2.000, 2.000, false);
    } else if (m_grd == InoMoveStepGrade_U) {
        ui->radio_inchingmove_u->setChecked(true);
        ui->grp_stepMode->setChecked(true);
    } else {
        ui->grp_stepMode->setChecked(false);
    }
}

void StepModeForm::slot_setstepparams_result(QObject *object, bool isSuccess)
{
    if (object != this) return;

    qDebug() << "[StepModeForm::slot_setstepparams_result]" << (object == this)
             << "|" << isSuccess;

    if (!isSuccess) {
        MessageBox::warning(tr("Failed to set jog parameters."));
        return;
    }

    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType::CmdType_MotionGetMoveStepSizePara);
}

void StepModeForm::slot_getstepparams_result(QObject *object, bool isSuccess,
                                             const InoMoveStepSizePara &params)
{
    if (object != this) return;

    qDebug() << "[StepModeForm::slot_setstepparams_result]" << (object == this)
             << "|" << isSuccess;

    if (!isSuccess) {
        if (isVisible()) {
            MessageBox::warning(tr("Failed to get jog parameters."));
        } else {
            PRINT_WARN(tr("Failed to get jog parameters."));
        }
        return;
    }

    m_params = params;
    if (ui->radio_inchingmove_u->isChecked()) {
        setInchingMovement(params.PositionSize, params.PoseSize,
                           params.JointSize, true);
    }
}

void StepModeForm::slot_stepgrade_changed(InoMoveStepGrade grade)
{
    qDebug() << "[StepModeForm::slot_stepgrade_changed]" << grade << "|" << m_grd<<"|"<<bContiMotion;
    // if (grade != m_grd && !bContiMotion) {
    //     setStepGrade(m_grd);
    // }
    m_grd = grade;
    updateGradeGUI();
}

void StepModeForm::setInchingMovement(double g1, double g2,
                                      double g3, bool bEnable)
{
    ui->edit_position->setText(QString::number(g1, 'f', 3));
    ui->edit_ori->setText(QString::number(g2, 'f', 3));
    ui->edit_joint->setText(QString::number(g3, 'f', 3));

    ui->grp_valus->setEnabled(bEnable);
    ui->grp_stepMode->setChecked(true);
}

void StepModeForm::setStepGrade(InoMoveStepGrade grd,
                                double posoff, double orioff, double jointoff)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (grd != InoMoveStepGrade_None) {
        bContiMotion = false;
    }
    m_grd = grd;
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_MotionSetMoveStepGrade,
        grd);

    if (grd == InoMoveStepGrade_U) {
        InoMoveStepSizePara params;
        params.PositionSize = m_params.PositionSize + posoff;
        params.PoseSize = m_params.PoseSize + orioff;
        params.JointSize = m_params.JointSize + jointoff;
        setStepParams(params);
    }
}

void StepModeForm::setUGradeOnly()
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    bContiMotion = false;
    m_grd = InoMoveStepGrade_U;
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_MotionSetMoveStepGrade,
        InoMoveStepGrade_U);

    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType::CmdType_MotionGetMoveStepSizePara);
}

void StepModeForm::setStepParams(const InoMoveStepSizePara &params)
{
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_MotionSetMoveStepSizePara,
        static_cast<InoMoveStepSizePara>(params));
}

void StepModeForm::updateGradeGUI()
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    InoMoveStepGrade grd = Communication::instance()->getMoveStepGrade();

    if (grd == InoMoveStepGrade_None) {
        ui->grp_stepMode->setChecked(false);
        return;
    }

    ui->grp_stepMode->setChecked(true);
    if (grd == InoMoveStepGrade_G1) {
        ui->radio_inchingmove_g1->setChecked(true);
        setInchingMovement(0.050, 0.050, 0.050, false);
    }
    if (grd == InoMoveStepGrade_G2) {
        ui->radio_inchingmove_g2->setChecked(true);
        setInchingMovement(0.500, 0.500, 0.500, false);
    }
    if (grd == InoMoveStepGrade_G3) {
        ui->radio_inchingmove_g3->setChecked(true);
        setInchingMovement(2.000, 2.000, 2.000, false);
    }
    if (grd == InoMoveStepGrade_U) {
        ui->radio_inchingmove_u->setChecked(true);
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType::CmdType_MotionGetMoveStepSizePara);
    }

    refreshEnable();
}

void StepModeForm::refreshEnable()
{
    if (m_grd != InoMoveStepGrade_U) {
        ui->grp_valus->setEnabled(false);
    } else {
        ui->grp_valus->setEnabled(true);
    }
}

void StepModeForm::on_grp_stepMode_clicked(bool checked)
{
    if (!Communication::instance()->isConnected()) {
        MessageBox::warning(tr("Controller not connected."));
        return;
    }

    qDebug() << "[StepModeForm::on_grp_stepMode_clicked]checked = " << checked;
    ui->grp_stepMode->setChecked(checked);
    if (checked) {
        if (ui->radio_inchingmove_g1->isChecked()) {
            setStepGrade(InoMoveStepGrade_G1);
        } else if (ui->radio_inchingmove_g2->isChecked()) {
            setStepGrade(InoMoveStepGrade_G2);
        } else if (ui->radio_inchingmove_g3->isChecked()) {
            setStepGrade(InoMoveStepGrade_G3);
        } else if (ui->radio_inchingmove_u->isChecked()) {
            setStepGrade(InoMoveStepGrade_U);
        }
    } else {
        setStepGrade(InoMoveStepGrade_None);
    }
}

void StepModeForm::slot_contimotion()
{
    if (ui->grp_stepMode->isChecked()) {
        ui->grp_stepMode->setChecked(false);
        // setStepGrade(InoMoveStepGrade_None);
        bContiMotion = true;
    }
}

void StepModeForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    // if (ControllerConnectionState_Connected == status) {
    //     CommunicationEngine::instance()->enqueueCmd(
    //         this, AbstractCmd::CmdType::CmdType_MotionGetMoveStepSizePara);
    // }

    // if (ControllerConnectionState_Connected == status && ui->grp_stepMode->isChecked()) {
    //     setStepGrade(InoMoveStepGrade_None);
    // }

    updateGradeGUI();
    if (ControllerConnectionState_Closed == status) {
        ui->radio_inchingmove_g1->setChecked(true);
        ui->edit_position->setText(QString::number(0.050, 'f', 3));
        ui->edit_ori->setText(QString::number(0.050, 'f', 3));
        ui->edit_joint->setText(QString::number(0.050, 'f', 3));
        ui->grp_stepMode->setChecked(false);
    }
}

void StepModeForm::on_pbn_posdown_clicked()
{
    double value = ui->edit_position->text().toDouble();
    value -= NUM_STEP_VALUE;
    if (value <= NUM_MIN_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, 0 - NUM_STEP_VALUE, 0, 0);
}

void StepModeForm::on_pbn_oridown_clicked()
{
    double value = ui->edit_ori->text().toDouble();
    value -= NUM_STEP_VALUE;
    if (value <= NUM_MIN_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, 0, 0 - NUM_STEP_VALUE, 0);
}

void StepModeForm::on_pbn_jointdown_clicked()
{
    double value = ui->edit_joint->text().toDouble();
    value -= NUM_STEP_VALUE;
    if (value <= NUM_MIN_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, 0, 0, 0 - NUM_STEP_VALUE);
}

void StepModeForm::on_pbn_posup_clicked()
{
    double value = ui->edit_position->text().toDouble();
    value += NUM_STEP_VALUE;
    if (value >= NUM_MAX_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, NUM_STEP_VALUE, 0, 0);
}

void StepModeForm::on_pbn_oriup_clicked()
{
    double value = ui->edit_ori->text().toDouble();
    value += NUM_STEP_VALUE;
    if (value >= NUM_MAX_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, 0, NUM_STEP_VALUE, 0);
}

void StepModeForm::on_pbn_jointup_clicked()
{
    double value = ui->edit_joint->text().toDouble();
    value += NUM_STEP_VALUE;
    if (value >= NUM_MAX_STEP_VALUE) {
        return;
    }
    setStepGrade(InoMoveStepGrade_U, 0, 0, NUM_STEP_VALUE);
}

void StepModeForm::slot_vk_ok_clicked()
{
    if (ui->edit_position->text().isEmpty()) {
        ui->edit_position->setText(QString::number(m_params.PositionSize));
    }
    if (ui->edit_ori->text().isEmpty()) {
        ui->edit_ori->setText(QString::number(m_params.PoseSize));
    }
    if (ui->edit_joint->text().isEmpty()) {
        ui->edit_joint->setText(QString::number(m_params.JointSize));
    }
    double dPos = ui->edit_position->text().toDouble();
    double dOri = ui->edit_ori->text().toDouble();
    double dJoint = ui->edit_joint->text().toDouble();
    setStepGrade(InoMoveStepGrade_U,
                 dPos - m_params.PositionSize,
                 dOri - m_params.PoseSize,
                 dJoint - m_params.JointSize);
}

void StepModeForm::retranslateUi()
{
    ui->retranslateUi(this);
}
