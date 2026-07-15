#include "passwordconfirmform.h"
#include "ui_passwordconfirmform.h"
#include <QTimer>
#include <QDebug>
#include "messagebox.h"
#include "dialogcontainerform.h"
#include "metatype.h"
#include "instance.h"
#include "communicationengine.h"
#include "propertydefine.h"

const int PASSWD_TRY_TIME_LIMIT = 3;

static PasswordConfirmForm *s_instance = 0;

PasswordConfirmForm *PasswordConfirmForm::instance()
{
    return s_instance;
}

PasswordConfirmForm::PasswordConfirmForm(QWidget *parent) :
    AbstractWidget(parent, 346, 200, 346, 200),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::PasswordConfirmForm)
#else
    ui(AbstractWidget::ui)
#endif
{
    s_instance = this;

#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    setAttribute(Qt::WA_StyledBackground);

    ui->edit_passwd->setProperty("Imt", Imt_FormattedNumbersOnly);
    ui->edit_passwd->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("\\b[0-9]{6}\\b"), this));

    ui->edit_passwd->installEventFilter(this);
    ui->edit_passwd->setProperty(InfoFlow_EditPassWord, "True");

    // DialogContainerForm::instance()->registDialog(this, 375, 136);

    ui->pbn_close->setIcon(QIcon(":/components/image/components/window/close_window.svg"));
}

PasswordConfirmForm::~PasswordConfirmForm()
{
    delete ui;
}

void PasswordConfirmForm::setArgs(const QString &sFuncId, const QString &sTitle, const char *sPasswd)
{
    s_funcId = sFuncId;
    s_passwd = sPasswd == nullptr ? SAFETY_PASSWD : sPasswd;

    ui->lbl_title->setText(sTitle);
}

void PasswordConfirmForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Confirm password"));
}

void PasswordConfirmForm::showEvent(QShowEvent *event)
{
    ui->edit_passwd->clear();
    this->setFocus();

    ui->pbn_eye->setChecked(true);
    ui->edit_passwd->setEchoMode(QLineEdit::Password);

    connect(ui->edit_passwd,
            &LineEdit::focusOut,
            this,
            &PasswordConfirmForm::slot_edit_finished);
}

void PasswordConfirmForm::hideEvent(QHideEvent *event)
{
    disconnect(ui->edit_passwd,
            &LineEdit::focusOut,
            this,
            &PasswordConfirmForm::slot_edit_finished);
}


bool PasswordConfirmForm::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched == ui->edit_passwd)
    {
        emit qApp->focusChanged(this, ui->edit_passwd);
        return QWidget::eventFilter(watched, event);
    }
    return QWidget::eventFilter(watched, event);
}

void PasswordConfirmForm::on_pbn_cancel_clicked()
{
    emit signal_passwd_confirm_result(s_funcId, false);
    m_inputIncorrectTimes = 0;
}

void PasswordConfirmForm::on_pbn_submit_clicked()
{
    if (ui->edit_passwd->text().compare(s_passwd) == 0) {
        emit signal_passwd_confirm_result(s_funcId, true);
        m_inputIncorrectTimes = 0;
    } else {
        ++m_inputIncorrectTimes;
        if (m_inputIncorrectTimes >= PASSWD_TRY_TIME_LIMIT) {
            emit signal_passwd_confirm_result(s_funcId, false);
            m_inputIncorrectTimes = 0;
        } else {
            MessageBox::warning(
                tr("Invalid password. You have %1 more chance!")
                    .arg(PASSWD_TRY_TIME_LIMIT - m_inputIncorrectTimes));
        }
    }
}

void PasswordConfirmForm::slot_edit_finished()
{
    qDebug() << "PasswordConfirmForm::slot_edit_finished";
}

void PasswordConfirmForm::on_pbn_eye_clicked(bool checked)
{
    if (!checked) {
        ui->edit_passwd->setEchoMode(QLineEdit::Normal);
    } else {
        ui->edit_passwd->setEchoMode(QLineEdit::Password);
    }
}

void PasswordConfirmForm::on_pbn_close_clicked()
{
    emit signal_passwd_confirm_result(s_funcId, false);
    m_inputIncorrectTimes = 0;
}

