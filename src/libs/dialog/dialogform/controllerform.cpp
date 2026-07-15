#include "controllerform.h"
#include "ui_controllerform.h"
#include "dialogcontainerform.h"
#include "communicationengine.h"
#include "messagebox.h"
#include "propertydefine.h"

static ControllerForm *s_instance = 0;

ControllerForm *ControllerForm::instance()
{
    return s_instance;
}

ControllerForm::ControllerForm(QWidget *parent) :
    AbstractWidget(parent, 240, 254, 240, 254),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ControllerForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    setAttribute(Qt::WA_StyledBackground);

    s_instance = this;

    ui->le_ip->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->le_port->setProperty("Imt", Imt_FormattedNumbersOnly);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectControllerInterface_result,
            this, &ControllerForm::slot_connectControllerInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_disconnectControllerInterface_result,
            this, &ControllerForm::slot_disconnectControllerInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &ControllerForm::slot_controllerConnectionStatusChanged);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableMechLockInterface_result,
            this, &ControllerForm::slot_enableMechLockInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_mechLockStateChanged,
            this, &ControllerForm::slot_mechLockStateChanged);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_clearAlarmInterface_result,
            this, &ControllerForm::slot_clearAlarmInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableStateChanged,
            this, &ControllerForm::slot_enableStateChanged);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerStateChanged,
            this, &ControllerForm::slot_controllerStateChanged);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_axisMoveInterface_result,
            this, &ControllerForm::slot_axisMoveInterface_result);
}

ControllerForm::~ControllerForm()
{
    delete ui;
}

void ControllerForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Controller"));
}

void ControllerForm::on_pbn_connectController_clicked(bool checked)
{
    ui->pbn_connectController->setChecked(!checked);

    QString ip = ui->le_ip->text().isEmpty() ?
                     ui->le_ip->placeholderText() :
                     ui->le_ip->text();
    int port = ui->le_port->text().isEmpty() ?
                   ui->le_port->placeholderText().toInt() :
                   ui->le_port->text().toInt();

    if (checked)
        CommunicationEngine::instance()->enqueueCmd_connectController(
            this, ip, port);
    else
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_DisconnectController);
}

void ControllerForm::on_pbn_mechLock_clicked(bool checked)
{
    ui->pbn_mechLock->setChecked(!checked);

    if (checked)
        CommunicationEngine::instance()->enqueueCmd_enableMechLock(
            this, true);
    else
        CommunicationEngine::instance()->enqueueCmd_enableMechLock(
            this, false);
}

void ControllerForm::on_pbn_clearAlarm_clicked(bool checked)
{
    ui->pbn_clearAlarm->setChecked(!checked);

    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType_ClearAlarm);
}

void ControllerForm::on_pbn_enable_clicked(bool checked)
{
    ui->pbn_enable->setChecked(!checked);

    CommunicationEngine::instance()->enqueueCmd_enableRobot(this, checked);
}

void ControllerForm::on_pbn_close_clicked()
{
    if (DialogContainerForm::instance()) {
        DialogContainerForm::instance()->hideDialog(
            DialogContainerForm::DialogStackForm_ControllerForm);
    }

    // Fallback: always hide immediately (even if WindowManager queue is busy).
    if (QWidget *top = this->window()) {
        top->hide();
    } else {
        this->hide();
    }
}

void ControllerForm::slot_connectControllerInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning("connectController failed");
    }
}

void ControllerForm::slot_disconnectControllerInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning("disconnectController failed");
    }
}

void ControllerForm::slot_controllerConnectionStatusChanged(
    ControllerConnectionState status)
{
    ui->pbn_connectController->setChecked(
        ControllerConnectionState_Connected == status);
}

void ControllerForm::slot_enableMechLockInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to enable mechanical lock."));
    }
}

void ControllerForm::slot_mechLockStateChanged(bool enable)
{
    ui->pbn_mechLock->setChecked(enable);
}

void ControllerForm::slot_clearAlarmInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to clear alarm."));
    }
}

void ControllerForm::slot_enableRobotInterface_result(
    QObject *object, bool isSuccess)
{

}

void ControllerForm::slot_enableStateChanged(bool enable)
{
    ui->pbn_enable->setChecked(enable);
}

void ControllerForm::slot_controllerStateChanged(ControllerState state)
{
    qDebug() << "state : " << state;

    switch (state) {
    case ControllerState_OFFLINE:
        ui->pbn_connectController->setChecked(false);
        break;
    case ControllerState_ENABLE:
        break;
    case ControllerState_ESTOP:
        break;
    case ControllerState_ERR:
        ui->pbn_clearAlarm->setChecked(false);
        break;
    case ControllerState_WARN:
        ui->pbn_clearAlarm->setChecked(true);
        break;
    case ControllerState_STANDBY:
        ui->pbn_clearAlarm->setChecked(true);
        break;
    default:
        break;
    }
}

void ControllerForm::slot_axisMoveInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Axis motion failed."));
    }
}
