#include <QDebug>

#include "controllerauthorityform.h"
#include "ui_controllerauthorityform.h"
#include "messagebox.h"
#include "communicationengine.h"
#include "propertydefine.h"
#include "cobotlog.h"
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include "communication.h"
static ControllerAuthorityForm *s_instance = 0;

ControllerAuthorityForm *ControllerAuthorityForm::instance()
{
    return s_instance;
}

ControllerAuthorityForm::ControllerAuthorityForm(QWidget *parent) :
    AbstractWidget(parent, 515, 416),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ControllerAuthorityForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    s_instance = this;

    ui->edit_speed->setValueMin(1);
    ui->edit_speed->setValueMax(100);
#if CommonLib_Metatype_DOF7_Enabled != 1
    ui->rbn_ethernet->hide();
#endif
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this,
            [=](ControllerConnectionState state) {
                if (state == ControllerConnectionState::ControllerConnectionState_Connected) {
                    m_isConnected = true;
                } else {
                    m_isConnected = false;
                }
                updateUI();
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controlAuthorityChanged,
            this,
            [=](InoCtrlAuthority type) {
                updateUI();
                QString controlType = tr("Unknown");
                if (!m_isConnected)
                    return;
                switch (type) {
                case InoCtrlAuthority_TeachPad: controlType = tr("TeachPad"); break;
                case InoCtrlAuthority_IO: controlType = tr("Remote I/O unit (effective in both auto and manual modes)"); break;
                case InoCtrlAuthority_IO_AUTO: controlType = tr("Remote I/O unit (only effective in auto mode)"); break;
                case InoCtrlAuthority_Ethernet: controlType = tr("Remote Ethernet client"); break;
                default: controlType = tr("Unknown"); break;
                }
                PRINT_MSG(tr("Current controller control: %1").arg(controlType));
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::singnal_setControlAuthorityRes,
            this,
            [=](QObject *obj, bool isSuccess) {
                if(obj != this)
                    return;
                DialogContainerForm::instance()->processRobotEventInfo(
                    isSuccess ? RobotEventInfo(RobotEventInfo::UserEvent_ChangeControlAuthorityFinish )
                              : RobotEventInfo(RobotEventInfo::UserEvent_Error, tr("Set control authority failed.")));
                if(isSuccess){
                    MessageBox::information(tr("Set control authority success."));
                    on_pbn_close_clicked();
                }

            });

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::singnal_getControlAuthorityRes,
            this, &ControllerAuthorityForm::slot_getControlAuthorityRes);
}

ControllerAuthorityForm::~ControllerAuthorityForm()
{
    delete ui;
}

void ControllerAuthorityForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property, tr("Control permission"));
    ui->pbn_close->setProperty(InfoFlow_HighLevelOperationLog,tr("Close"));

}

void ControllerAuthorityForm::showEvent(QShowEvent *ev)
{
    AbstractWidget::showEvent(ev);
    updateUI();
}

void ControllerAuthorityForm::updateUI()
{
    if (isVisible()) {
        if (m_isConnected) {
            CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_GetControlAuthority);
        } else {
            slot_getControlAuthorityRes(this, InoCtrlAuthority_Unknown, 0);
        }
    }
}

void ControllerAuthorityForm::on_pbn_save_clicked()
{
    // if(Communication::instance()->isProgramRunning() || Communication::instance()->isProgramPause() ){
    //     updateUI();
    //     MessageBox::warning(QObject::tr("Currently in project running/pause mode, permission switching is not allowed."));
    //     return;
    // }
    if(Communication::instance()->isProgramRunning()){
        updateUI();
        MessageBox::warning(QObject::tr("Currently in project running mode, permission switching is not allowed."));
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(this,
                                                        AbstractCmd::CmdType_SetControlAuthority,
                                                        (InoCtrlAuthority)m_currentEditType,
                                                        ui->edit_speed->getQVariant().toInt());
    DialogContainerForm::instance()->processRobotEventInfo(RobotEventInfo::UserEvent_ChangeControlAuthority);
    // updateUI();
}

void ControllerAuthorityForm::on_rbn_teachpad_clicked()
{
    m_currentEditType = InoCtrlAuthority_TeachPad;
    ui->edit_speed->setEnabled(false);
    ui->edit_speed->setText("");
}

void ControllerAuthorityForm::on_rbn_ethernet_clicked()
{
    m_currentEditType = InoCtrlAuthority_Ethernet;
    ui->edit_speed->setEnabled(false);
    ui->edit_speed->setText("");
}

void ControllerAuthorityForm::on_rbn_remoteAll_clicked()
{
    m_currentEditType = InoCtrlAuthority_IO;
    ui->edit_speed->setEnabled(true);
    if (ui->edit_speed->text().isEmpty())
        ui->edit_speed->setText("30");
}

void ControllerAuthorityForm::on_rbn_remoteSome_clicked()
{
    MessageBox::warning(tr("Under this control, the remote emergency stop command will become invalid in manual mode."));
    m_currentEditType = InoCtrlAuthority_IO_AUTO;
    ui->edit_speed->setEnabled(true);
    if (ui->edit_speed->text().isEmpty())
        ui->edit_speed->setText("30");
}

void ControllerAuthorityForm::on_pbn_update_clicked()
{
    updateUI();
}

void ControllerAuthorityForm::on_pbn_close_clicked()
{
    DialogContainerForm::instance()->hideDialog(DialogContainerForm::DialogStackForm_ControllerAuthorityForm);
}

void ControllerAuthorityForm::slot_getControlAuthorityRes(QObject *obj, InoCtrlAuthority type, int speed)
{
    if(obj != this)
        return;
    QRadioButton *rbn;
    m_currentEditType = type;
    switch (type) {
    case InoCtrlAuthority_TeachPad: rbn = ui->rbn_teachpad; break;
    case InoCtrlAuthority_IO: rbn = ui->rbn_remoteAll; break;
    case InoCtrlAuthority_IO_AUTO: rbn = ui->rbn_remoteSome; break;
    case InoCtrlAuthority_Ethernet: rbn = ui->rbn_ethernet; break;
    default: {
        // ui->rbn_teachpad->setChecked(true);
        ui->label_name->setText(tr("Unknown"));
        ui->label_speedValue->setText("--");
        ui->edit_speed->setEnabled(false);
        return;
    }
    }
    rbn->setChecked(true);
    ui->label_name->setText(rbn->text());
    if (type == InoCtrlAuthority_IO || type == InoCtrlAuthority_IO_AUTO) {
        ui->edit_speed->setEnabled(true);
        ui->label_speedValue->setText(QString::number(speed));
        ui->edit_speed->setText(QString::number(speed));
    } else {
        ui->label_speedValue->setText("--");
        ui->edit_speed->setEnabled(false);
    }
}
