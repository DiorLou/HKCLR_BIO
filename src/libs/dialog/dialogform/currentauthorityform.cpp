#include "currentauthorityform.h"
#include "ui_currentauthorityform.h"
#include <QPainterPath>
#include "authoritymanager.h"
#include "communicationengine.h"
#include "dialogcontainerform.h"
#include "messagebox.h"
#include "propertydefine.h"

CurrentAuthorityForm::CurrentAuthorityForm(QWidget *parent) :
    AbstractWidget(parent, 408, 328),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::CurrentAuthorityForm),
#else
    ui(AbstractWidget::ui),
#endif
    m_isConnected(false)
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    connect(AuthorityManager::instance(),
            &AuthorityManager::signal_changeAuthoritySuccess,
            this, [this](const QString &sAuthName, bool isAuthorityChanged) {
                updateCurrentAuthority();
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, [this](ControllerConnectionState state) {
                if (state != ControllerConnectionState::ControllerConnectionState_Connected) {
                    m_isConnected = false;
                    DialogContainerForm::instance()->hideDialog(
                        DialogContainerForm::DialogStackForm_CurrentAuthorityForm);
                } else {
                    m_isConnected = true;
                }
            });
}

CurrentAuthorityForm::~CurrentAuthorityForm()
{
    delete ui;
}

void CurrentAuthorityForm::updateCurrentAuthority()
{
    const Authority currentAuth = AuthorityManager::instance()->currentAuthority();
    if (!currentAuth.isValid()) {
        return;
    }

    ui->lbl_currentAuthority->setText(Authority::authorityNameStr(currentAuth));
    ui->pbn_avator->setIcon(QIcon(Authority::authorityAvator(currentAuth.authLevel())));
}

void CurrentAuthorityForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property, tr("Current authority"));

    ui->pbn_close->setProperty(InfoFlow_HighLevelOperationLog, tr("Close"));
}

void CurrentAuthorityForm::on_pbn_close_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_CurrentAuthorityForm);
}

void CurrentAuthorityForm::on_pbn_changeAuthority_clicked()
{
#if CommonLib_Dialog_LoadLocalProject_Enabled != 1
    if (!m_isConnected) {
        MessageBox::information(
            tr("It is not allowed to change authority when disconnected from controller."));
        return;
    }
#endif

    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_CurrentAuthorityForm);

    DialogContainerForm::instance()->showDialog(
        DialogContainerForm::DialogStackForm_ChangeAuthorityForm);
}
