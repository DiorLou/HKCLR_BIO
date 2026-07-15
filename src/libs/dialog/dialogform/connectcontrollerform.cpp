#include <QDebug>
#include "connectcontrollerform.h"
#include "ui_connectcontrollerform.h"
#include "propertydefine.h"
#include "messagebox.h"
#include "communicationengine.h"
#include "authoritytr.h"
#include <QRadioButton>
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include "communication.h"
#include "cobotlog.h"

static ConnectControllerForm *s_instance = 0;

ConnectControllerForm *ConnectControllerForm::instance()
{
    return s_instance;
}

ConnectControllerForm::ConnectControllerForm(QWidget *parent) :
    AbstractWidget(parent, 370, 259),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ConnectControllerForm)
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

    Instance::setConnectControllerForm(this);

    ui->le_ip->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->le_port->setProperty("Imt", Imt_FormattedNumbersOnly);

    ui->le_ip->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$"), this));

    ui->le_port->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("\\d{1,8}"), this));

#if defined(__ANDROID__)
    ui->le_ip->setPlaceholderText("192.168.22.1");
#else
    ui->le_ip->setPlaceholderText("192.168.23.25");
#endif

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectControllerInterface_result,
            this, &ConnectControllerForm::slot_connectControllerInterface_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_disconnectControllerInterface_result,
            this, &ConnectControllerForm::slot_disconnectControllerInterface_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &ConnectControllerForm::slot_controllerConnectionStatusChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerStateChanged,
            this, &ConnectControllerForm::slot_controllerStateChanged);

#ifndef __ANDROID__
    ui->lbl_wifi->setVisible(false);
    ui->lbl_wifiname->setVisible(false);
    ui->grp_connect->setMaximumHeight(150);
#endif

    initialize();
}

ConnectControllerForm::~ConnectControllerForm()
{
    delete ui;
}

void ConnectControllerForm::initialize()
{
    QString sIp = Communication::instance()->getIP();
#if defined(__ANDROID__)
    if (sIp.compare("192.168.23.25") == 0) {
        sIp = "192.168.22.1";
    }
#endif
    int iPort = Communication::instance()->getPort();
    ui->le_ip->setText(sIp);
    ui->le_port->setText(
        QString::number(iPort));
}

void ConnectControllerForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void ConnectControllerForm::showEvent(QShowEvent *event)
{
    ui->pbn_connectController->setChecked(Communication::instance()->isConnected());
#ifdef __ANDROID__
    refreshWifiName();
#endif
}

void ConnectControllerForm::on_pbn_connectController_clicked(bool checked)
{
    QString ip = ui->le_ip->text().isEmpty() ?
                     ui->le_ip->placeholderText() :
                     ui->le_ip->text();
    int port = ui->le_port->text().isEmpty() ?
                   ui->le_port->placeholderText().toInt() :
                   ui->le_port->text().toInt();
    if (checked) {
        DialogContainerForm::instance()->hideDialog(
            DialogContainerForm::DialogStackForm_ConnectControllerForm);

        CommunicationEngine::instance()->enqueueCmd_connectController(
            this, ip, port);
        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_ConnectController, "90"));
    } else {
        if (MessageBox::question(tr("Are you sure you want to disconnect from the controller?")) == QMessageBox::Yes) {
            CommunicationEngine::instance()->enqueueCmd(
                this, AbstractCmd::CmdType_DisconnectController);
            DialogContainerForm::instance()->processRobotEventInfo(
                RobotEventInfo(RobotEventInfo::UserEvent_DisconnectController));
        }
    }
}

void ConnectControllerForm::slot_connectControllerInterface_result(QObject *object, bool isSuccess)
{
    ui->pbn_connectController->setChecked(isSuccess);
    if (this == object && !isSuccess) {
        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_Error, tr("Failed to connect to the controller.")));
    }
}

void ConnectControllerForm::slot_disconnectControllerInterface_result(QObject *object, bool isSuccess)
{
    ui->pbn_connectController->setChecked(!isSuccess);
    if (this == object && !isSuccess) {
        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_Error, tr("Failed to disconnect from the controller.")));
    }
}

void ConnectControllerForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    bool isConnected = (ControllerConnectionState_Connected == status);
    ui->pbn_connectController->setChecked(isConnected);

    if (isConnected) {
        refreshWifiName();
    }
}

void ConnectControllerForm::slot_controllerStateChanged(ControllerState state)
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
    default:
        break;
    }
}

void ConnectControllerForm::on_le_ip_textChanged(const QString &arg1)
{
    Communication::instance()->setIP(arg1);
}

void ConnectControllerForm::getFunctionEnabledList(QList<QVariant> &retList)
{
    retList.clear();
    retList << QVariant::fromValue(QPair<QString, QString>("viewEnabled", AuthorityTr::tr("Enable view")));
}

void ConnectControllerForm::viewEnabled(bool isEnabled)
{
   // pbn_connectBtn->setEnabled(isEnabled);
}

void ConnectControllerForm::triggerAutoConnect()
{
    qDebug() << "Trigger Auto Connect.";
    on_pbn_connectController_clicked(true);
}

QString ConnectControllerForm::getIP() const
{
    if (!ui->le_ip->text().isEmpty()) {
        return ui->le_ip->text();
    }

    return ui->le_ip->placeholderText();
}

void ConnectControllerForm::refreshWifiName()
{
    QString sWifiName = Communication::instance()->getWifiName();
    LOG_INFO(QString("refresh wifiname, name = %1").arg(sWifiName));
    if (sWifiName.compare("<unknown ssid>") == 0) {
        QMetaObject::invokeMethod(
            Instance::mainWidget(), "UpdateWifiOnSSidUnknow", Qt::DirectConnection);
    }
    ui->lbl_wifiname->setText(sWifiName);
    ui->lbl_wifiname->update();
}

void ConnectControllerForm::on_pbn_close_clicked()
{
    if (DialogContainerForm::instance()) {
        DialogContainerForm::instance()->hideDialog(
            DialogContainerForm::DialogStackForm_ConnectControllerForm);
    }

    // Fallback: always hide immediately.
    if (QWidget *top = this->window()) {
        top->hide();
    } else {
        this->hide();
    }
}

