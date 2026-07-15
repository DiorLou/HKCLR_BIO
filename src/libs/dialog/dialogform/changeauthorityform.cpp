#include "changeauthorityform.h"
#include "ui_changeauthorityform.h"
#include <QVariant>
#include "authoritymanager.h"
#include "cobotlog.h"
#include "communicationengine.h"
#include "dialogcontainerform.h"
#include "instance.h"
#include "messagebox.h"
#include "metatype.h"
#include "stringutils.h"
#include "propertydefine.h"

ChangeAuthorityForm::ChangeAuthorityForm(QWidget *parent) :
    AbstractWidget(parent, 408, 328),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ChangeAuthorityForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    Instance::setChangeAuthorityForm(this);

    ui->le_password->installEventFilter(this);
    ui->le_password->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->le_password->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"), this));

    connect(AuthorityManager::instance(),
            &AuthorityManager::signal_changeAuthoritySuccess,
            this, [this](const QString &sAuthName, bool isAuthorityChanged){
                updateCmbAuthority();
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, [this](ControllerConnectionState state){
                if(state != ControllerConnectionState::ControllerConnectionState_Connected){
                    DialogContainerForm::instance()->hideDialog(
                        DialogContainerForm::DialogStackForm_ChangeAuthorityForm);
                }
            });
    ui->le_password->setProperty(InfoFlow_EditPassWord, "True");
}

ChangeAuthorityForm::~ChangeAuthorityForm()
{
    delete ui;
}

void ChangeAuthorityForm::clearPassword()
{
    ui->le_password->clear();
}

void ChangeAuthorityForm::retranslateUi()
{
    updateCmbAuthority();

    ui->retranslateUi(this);

    setProperty(InfoFlow_Property,tr("Switch authority"));

    ui->pbn_close->setProperty(InfoFlow_HighLevelOperationLog,tr("Close"));
    ui->pbn_back->setProperty(InfoFlow_HighLevelOperationLog,tr("Back"));
}

bool ChangeAuthorityForm::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched == ui->le_password)
    {
        emit qApp->focusChanged(this, ui->le_password);
        return QWidget::eventFilter(watched, event);
    }

    return QWidget::eventFilter(watched, event);
}

void ChangeAuthorityForm::showEvent(QShowEvent *evt)
{
    ui->cmb_authority->blockSignals(true);
    ui->cmb_authority->setCurrentIndex(0);
    ui->cmb_authority->blockSignals(false);

    ui->pbn_eye->setChecked(true);
    ui->le_password->setEchoMode(QLineEdit::Password);

    setPasswordFormVisible(false);
}

void ChangeAuthorityForm::updateCmbAuthority()
{
    const QVector<Authority> vecAuthorities = AuthorityManager::instance()
                                                  ->getAuthorities(AuthorityFilter_Changable);
    const Authority curAuthority = AuthorityManager::instance()->currentAuthority();
    ui->cmb_authority->blockSignals(true);
    ui->cmb_authority->clear();

    for(int i = 0; i < vecAuthorities.count(); i++) {
        Authority auth = vecAuthorities.at(i);
        ui->cmb_authority->addItem(
            Authority::authorityNameStr(auth),
            QVariant::fromValue(auth.authLevel()));
    }

    ui->cmb_authority->setCurrentText(Authority::authorityNameStr(curAuthority));
    ui->cmb_authority->blockSignals(false);

    setPasswordFormVisible(AuthorityManager::instance()
                               ->isAdvancedAuthority(curAuthority.authLevel()));

    setConfirmBtnEnabled(!ui->cmb_authority->currentText().isEmpty());
}

void ChangeAuthorityForm::setPasswordFormVisible(bool isVisible)
{
#if CommonLib_Dialog_DeveloperMode_Enabled == 1
    if (Instance::common()->property("isDeveloperMode").value<bool>()) {
        isVisible = false;
    }
#endif

    ui->widget_password->setVisible(isVisible);
    ui->lbl_password->setVisible(isVisible);
    ui->le_password->clear();
}

void ChangeAuthorityForm::setConfirmBtnEnabled(bool isEnabled)
{
    ui->pbn_confirm->setEnabled(isEnabled);
}

void ChangeAuthorityForm::on_pbn_eye_clicked(bool checked)
{
    ui->le_password->setEchoMode(
        checked ? QLineEdit::Password : QLineEdit::Normal);
}

void ChangeAuthorityForm::on_pbn_confirm_clicked()
{
    QString sAuthName = ui->cmb_authority->currentText();
    const Authority::AuthLevel authLevel
        = ui->cmb_authority->currentData().value<Authority::AuthLevel>();
    if (!AuthorityManager::instance()->isCustomAuthority(authLevel)) {
        sAuthName = Authority::authTypeStrFromLevel(authLevel);
    }

    QString sPasswd = ui->le_password->text();

    bool isDeveloperMode = Instance::common()->property("isDeveloperMode").value<bool>();
    if (!isDeveloperMode) {
        if (AuthorityManager::instance()->isAdvancedAuthority(authLevel)
            && sPasswd.isEmpty()) {
            MessageBox::information(tr("Please input password"));
            return;
        }
    }

    if (AuthorityManager::instance()->currentAuthority().authLevel() == authLevel) {
        MessageBox::information(tr("Current authority is %1.").arg(
            Authority::authorityNameStr(sAuthName, authLevel)));
        return;
    }

    if (!isDeveloperMode) {
        QString encyptPasswd = StringUtils::getEncriptCode(sPasswd);
        if (encyptPasswd.isEmpty()) {
            return;
        }

        Authority authority(sAuthName, authLevel, encyptPasswd);
        if (!AuthorityManager::instance()->checkAuthorityValid(authority)) {
            MessageBox::information(tr("Wrong password."));
            return;
        }
    }

    AuthorityManager::instance()->updateAuthority(authLevel, sAuthName);

    PRINT_MSG(
        tr("Successfully switched to %1.").arg(
            Authority::authorityNameStr(sAuthName, authLevel)));

    on_pbn_close_clicked();
}

void ChangeAuthorityForm::on_cmb_authority_currentTextChanged(const QString &text)
{
    const Authority::AuthLevel authLevel
        = ui->cmb_authority->currentData().value<Authority::AuthLevel>();
    setPasswordFormVisible(
        AuthorityManager::instance()->isAdvancedAuthority(authLevel));
    setConfirmBtnEnabled(!text.isEmpty());
}

void ChangeAuthorityForm::on_pbn_back_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_ChangeAuthorityForm);

    DialogContainerForm::instance()->showDialog(
        DialogContainerForm::DialogStackForm_CurrentAuthorityForm);
}

void ChangeAuthorityForm::on_pbn_close_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_ChangeAuthorityForm);
}
