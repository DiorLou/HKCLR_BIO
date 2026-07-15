#include "customauthorityform.h"
#include "ui_customauthorityform.h"
#include <QVariant>
#include "authoritymanager.h"
#include "communicationengine.h"
#include "dialogcontainerform.h"
#include "instance.h"
#include "messagebox.h"
#include "metatype.h"
#include "propertydefine.h"

CustomAuthorityForm::CustomAuthorityForm(QWidget *parent) :
    AbstractWidget(parent, 408, 284),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::CustomAuthorityForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    Instance::setCustomAuthorityForm(this);

    ui->le_customAuhorityName->installEventFilter(this);
    ui->le_customAuhorityName->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[A-Za-z]{1}[A-Za-z0-9_]{1,19}"), this));
    ui->le_customAuhorityName->setProperty("Imt", Imt_LatinOnly);

    connect(AuthorityManager::instance(),
            &AuthorityManager::signal_changeAuthoritySuccess,
            this, [this](const QString &sAuthName, bool isAuthorityChanged){
                updateParentAuthorityTypeCmb();
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, [this](ControllerConnectionState state){
                if(state != ControllerConnectionState::ControllerConnectionState_Connected){
                    DialogContainerForm::instance()->hideDialog(
                        DialogContainerForm::DialogStackForm_CustomAuthorityForm);
                }
            });
}

CustomAuthorityForm::~CustomAuthorityForm()
{
    delete ui;
}

void CustomAuthorityForm::clearAuthorityName()
{
    ui->le_customAuhorityName->clear();
}

void CustomAuthorityForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Custom authority"));
}

bool CustomAuthorityForm::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched == ui->le_customAuhorityName)
    {
        emit qApp->focusChanged(this, ui->le_customAuhorityName);
        return QWidget::eventFilter(watched, event);
    }
    return QWidget::eventFilter(watched, event);
}

void CustomAuthorityForm::updateParentAuthorityTypeCmb()
{
    const QVector<Authority> vecAuthorities =
        AuthorityManager::instance()->getAuthorities(AuthorityFilter_Inheritable);
    Authority curAuthority = AuthorityManager::instance()->currentAuthority();
    if (!curAuthority.isValid()) {
        return;
    }

    ui->cmb_parentAuthorityType->blockSignals(true);
    ui->cmb_parentAuthorityType->clear();

    for(int i = 0; i < vecAuthorities.count(); i++) {
        Authority auth = vecAuthorities.at(i);
        ui->cmb_parentAuthorityType->addItem(
            Authority::authorityNameStr(auth),
            QVariant::fromValue(auth.authLevel()));
    }

    ui->cmb_parentAuthorityType->setCurrentText(
        Authority::authorityNameStr(curAuthority));
    ui->cmb_parentAuthorityType->blockSignals(false);
}

void CustomAuthorityForm::on_pbn_close_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_CustomAuthorityForm);
}

void CustomAuthorityForm::on_pbn_cancel_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_CustomAuthorityForm);
}

void CustomAuthorityForm::on_pbn_confirm_clicked()
{
    QString sParentAuthName = ui->cmb_parentAuthorityType->currentText();
    const Authority::AuthLevel parentAuthLevel
        = ui->cmb_parentAuthorityType->currentData().value<Authority::AuthLevel>();
    if (!AuthorityManager::instance()->isCustomAuthority(parentAuthLevel)) {
        sParentAuthName = Authority::authTypeStrFromLevel(parentAuthLevel);
    }

    if (sParentAuthName.isEmpty() || parentAuthLevel == Authority::Unknown) {
        MessageBox::information(tr("Please select inheritable authority"));
        return;
    }

    const QString sAuthName = ui->le_customAuhorityName->text().trimmed();
    if (sAuthName.isEmpty()) {
        MessageBox::information(tr("Please input new authority name"));
        return;
    }

    Authority parentAuth =
        AuthorityManager::instance()->getAuthority(sParentAuthName, parentAuthLevel);
    const Authority::AuthLevel authLevel =
        AuthorityManager::instance()->getCustomAuthLevel(parentAuthLevel);
    // 新增
    QString msg;
    bool ret = AuthorityManager::instance()->addCustomAuthority(
        Authority{sAuthName, authLevel, parentAuth.authPassword()}, parentAuth,
        msg);
    if (!ret) {
        if (msg.isEmpty()) {
            msg = tr("Failed to add %1.").arg(sAuthName);
        }

        MessageBox::information(msg);
        return;
    }

    ret = AuthorityManager::instance()->saveAllAuthorityInfo(msg);
    if (!ret) {
        if (msg.isEmpty()) {
            msg = tr("Failed to save authority info.");
        }

        MessageBox::information(msg);
        return;
    }

    updateParentAuthorityTypeCmb();

    QMetaObject::invokeMethod(Instance::changeAuthorityForm(),
                              "updateCmbAuthority", Qt::DirectConnection);
    QMetaObject::invokeMethod(Instance::authorityManageForm(),
                              "updateAuthorityTypes", Qt::DirectConnection,
                              Q_ARG(bool, false));

    on_pbn_close_clicked();

    MessageBox::information(tr("Authority %1 added successfully.").arg(sAuthName));
}

