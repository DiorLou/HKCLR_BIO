#include "loginform.h"
#include "ui_loginform.h"
#include <QDebug>
#include "databaselocal.h"
#include "dialogcontainerform.h"
#include "messagebox.h"
#include "instance.h"

static LoginForm *s_instance = 0;

LoginForm *LoginForm::instance()
{
    return s_instance;
}

LoginForm::LoginForm(QWidget *parent) :
    AbstractWidget(parent, 400, 284, 400, 284),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::LoginForm)
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
    Instance::setLoginForm(this);

#if defined(Q_OS_LINUX)
    ui->cmb_userName->setTranslatable(false);
#endif

    ui->le_password->setProperty("Imt", Imt_LatinOnly);
    ui->le_password->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[!-~]{1,16}"), this));
}

LoginForm::~LoginForm()
{
    delete ui;
}

bool LoginForm::isPasswordEqual(const QString &plainCode, QString password)
{
    return encrypt(plainCode)
        == (password.isEmpty() ? m_loginUser.m_password : password);
}

QString LoginForm::encrypt(const QString &plainCode)
{
    return QCryptographicHash::hash(
               plainCode.toLatin1(), QCryptographicHash::Md5)
        .toHex();
}

User LoginForm::getLoginUser() const
{
    return m_loginUser;
}

void LoginForm::setLoginUser(const User &loginUser)
{
    m_loginUser = loginUser;
}

void LoginForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void LoginForm::showEvent(QShowEvent *)
{
    m_loginUser.init();
    initUserList();
    autoLogin();
}

void LoginForm::on_pbn_close_clicked()
{
    qApp->quit();
}

void LoginForm::on_pbn_login_clicked()
{
    qDebug() << "LoginForm::on_pbn_login_clicked()";
    QString userID = ui->cmb_userName->currentData().toString();
    User user;
    if (getCurrentUserInfo(user)) {
        if (isPasswordEqual(ui->le_password->text(), user.m_password)) {
            if (ui->chk_autoLogin->isChecked())
                DatabaseLocal::setUserAutoLogin(userID);
            else
                DatabaseLocal::setUserAutoLogin("");

            login(user);
        } else {
            MessageBox::warning(tr("Incorrect password"));
        }
    }
}

void LoginForm::initUserList()
{
    QString preUserName = ui->cmb_userName->currentText();
    if (DatabaseLocal::getUserList(m_userList)) {
        ui->cmb_userName->clear();
        for (User user : m_userList) {
            ui->cmb_userName->addItem(user.m_userName, user.m_userID);

            if (user.m_isAutoLogin)
                m_autoLoginUser = user;
        }

        if (!m_userList.isEmpty())
            on_cmb_userName_currentTextChanged(
                preUserName.isEmpty() ?
                    m_userList.at(0).m_userName :
                    preUserName);
    }
}

void LoginForm::login(const User &user)
{
    m_loginUser = user;

    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_LoginForm);
}

bool LoginForm::getCurrentUserInfo(User &user)
{
    bool ret;
    int index = m_userList.indexOf(
        User(ui->cmb_userName->currentData().toString()));
    if ((ret = index >= 0))
        user = m_userList.at(index);

    return ret;
}

void LoginForm::autoLogin()
{
    if (!m_autoLoginUser.m_userID.isEmpty())
        login(m_autoLoginUser);
}

void LoginForm::on_cmb_userName_currentTextChanged(const QString &userName)
{
    ui->le_password->clear();
    ui->cmb_userName->setCurrentText(userName);

    User user;
    if (getCurrentUserInfo(user))
        ui->chk_autoLogin->setChecked(user.m_isAutoLogin);
    else
        ui->chk_autoLogin->setChecked(false);
}

void LoginForm::on_pbn_eye_clicked(bool checked)
{
    ui->le_password->setEchoMode(
        checked ? QLineEdit::Password : QLineEdit::Normal);
}
