#include "lockscreenform.h"
#include "ui_lockscreenform.h"
#include <QSignalMapper>
#include <QInputMethodEvent>
#include "authoritymanager.h"
#include "dialogcontainerform.h"
#include "stringutils.h"
#include "propertydefine.h"
LockScreenForm::LockScreenForm(QWidget *parent) :
    AbstractWidget(parent, 752, 372, 752, 372),
    m_widgetCaller(NULL),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::LockScreenForm)
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

    ui->le_password->setValidator(new QIntValidator(this));

    QList<QPushButton*> pbnList = this->findChildren<QPushButton*>();
    for (const QPushButton *pbn : pbnList) {
        connect(pbn, &QPushButton::clicked,
                this, &LockScreenForm::slot_keyClicked);
    }
    for(QAbstractButton *btn : findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively)){
        btn->setProperty(InfoFlow_RbnIsWidgetIndex, "NoLog");
    }
}

LockScreenForm::~LockScreenForm()
{
    delete ui;
}

void LockScreenForm::hideEvent(QHideEvent *)
{
    ui->le_password->clear();
}

void LockScreenForm::on_pbn_enter_clicked()
{
    Authority currentAuth = AuthorityManager::instance()->currentAuthority();
    bool ret = AuthorityManager::instance()->checkAuthorityValid(
        Authority{currentAuth.authName(), currentAuth.authLevel(),
                  StringUtils::getEncriptCode(ui->le_password->text().trimmed())});
    if (ret) {
        ui->le_password->clear();
        DialogContainerForm::instance()->hideDialog(
            DialogContainerForm::DialogStackForm_LockScreenForm);

        if (NULL != m_widgetCaller) {
            QMetaObject::invokeMethod(
                m_widgetCaller, "passwordVerificationPassed",
                Qt::DirectConnection);

            m_widgetCaller = NULL;
        }
    } else {
        ui->le_password->clear();
        ui->le_password->setPlaceholderText(tr("Password input error"));
    }
}

void LockScreenForm::setWidgetCaller(QWidget *widgetCaller)
{
    m_widgetCaller = widgetCaller;
}

void LockScreenForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Lockscreen"));
}

void LockScreenForm::showEvent(QShowEvent *)
{
    if (NULL != m_widgetCaller)
        ui->lbl_title->setText(tr("Password authentication"));
    else
        ui->lbl_title->setText(tr("Lock screen"));

    ui->le_password->clear();
    ui->le_password->setEchoMode(QLineEdit::Password);
    ui->pbn_eye->setChecked(true);

    Authority currentAuth = AuthorityManager::instance()->currentAuthority();
    bool isAdvancedAuth = AuthorityManager::instance()
                              ->isAdvancedAuthority(currentAuth.authLevel());
    ui->lbl_tip->setText(
        isAdvancedAuth ? tr("Enter your authority password to unlock the screen.")
                         : tr("Press Enter to unlock the screen"));
}

void LockScreenForm::on_pbn_capsLock_clicked(bool checked)
{
    capsLockEnable(checked);
    if (checked) {
        ui->pbn_leftShift->setChecked(false);
        ui->pbn_rightShift->setChecked(false);
    }
}

void LockScreenForm::capsLockEnable(bool enable)
{
    if (enable) {
        ui->pbn_backquoteOrTilde->setText("~");
        ui->pbn_1OrExclamationMark->setText("!");
        ui->pbn_2OrAt->setText("@");
        ui->pbn_3OrHash->setText("#");
        ui->pbn_4OrDollarSign->setText("$");
        ui->pbn_5OrPercentSign->setText("%");
        ui->pbn_6OrCircumflex->setText("^");
        ui->pbn_7OrAmpersand->setText("&&");
        ui->pbn_8OrAsterisk->setText("*");
        ui->pbn_9OrLeftParentheses->setText("(");
        ui->pbn_0OrRightParentheses->setText(")");
        ui->pbn_hyphenOrUnderline->setText("_");
        ui->pbn_equalsSignOrPlusSign->setText("+");

        ui->pbn_q->setText("Q");
        ui->pbn_w->setText("W");
        ui->pbn_e->setText("E");
        ui->pbn_r->setText("R");
        ui->pbn_t->setText("T");
        ui->pbn_y->setText("Y");
        ui->pbn_u->setText("U");
        ui->pbn_i->setText("I");
        ui->pbn_o->setText("O");
        ui->pbn_p->setText("P");
        ui->pbn_leftBracketsOrBrace->setText("{");
        ui->pbn_rightBracketsOrBrace->setText("}");
        ui->pbn_backslashOrPipe->setText("|");

        ui->pbn_a->setText("A");
        ui->pbn_s->setText("S");
        ui->pbn_d->setText("D");
        ui->pbn_f->setText("F");
        ui->pbn_g->setText("G");
        ui->pbn_h->setText("H");
        ui->pbn_j->setText("J");
        ui->pbn_k->setText("K");
        ui->pbn_l->setText("L");
        ui->pbn_semicolonOrColon->setText(":");
        ui->pbn_apostropheOrDoubleQuote->setText("\"");

        ui->pbn_z->setText("Z");
        ui->pbn_x->setText("X");
        ui->pbn_c->setText("C");
        ui->pbn_v->setText("V");
        ui->pbn_b->setText("B");
        ui->pbn_n->setText("N");
        ui->pbn_m->setText("M");
        ui->pbn_commaOrLeftAngleBrackets->setText("<");
        ui->pbn_dotOrRightAngleBrackets->setText(">");
        ui->pbn_slashOrQuestionMark->setText("?");
    } else {
        ui->pbn_backquoteOrTilde->setText("`");
        ui->pbn_1OrExclamationMark->setText("1");
        ui->pbn_2OrAt->setText("2");
        ui->pbn_3OrHash->setText("3");
        ui->pbn_4OrDollarSign->setText("4");
        ui->pbn_5OrPercentSign->setText("5");
        ui->pbn_6OrCircumflex->setText("6");
        ui->pbn_7OrAmpersand->setText("7");
        ui->pbn_8OrAsterisk->setText("8");
        ui->pbn_9OrLeftParentheses->setText("9");
        ui->pbn_0OrRightParentheses->setText("0");
        ui->pbn_hyphenOrUnderline->setText("-");
        ui->pbn_equalsSignOrPlusSign->setText("=");

        ui->pbn_q->setText("q");
        ui->pbn_w->setText("w");
        ui->pbn_e->setText("e");
        ui->pbn_r->setText("r");
        ui->pbn_t->setText("t");
        ui->pbn_y->setText("y");
        ui->pbn_u->setText("u");
        ui->pbn_i->setText("i");
        ui->pbn_o->setText("o");
        ui->pbn_p->setText("p");
        ui->pbn_leftBracketsOrBrace->setText("[");
        ui->pbn_rightBracketsOrBrace->setText("]");
        ui->pbn_backslashOrPipe->setText("\\");

        ui->pbn_a->setText("a");
        ui->pbn_s->setText("s");
        ui->pbn_d->setText("d");
        ui->pbn_f->setText("f");
        ui->pbn_g->setText("g");
        ui->pbn_h->setText("h");
        ui->pbn_j->setText("j");
        ui->pbn_k->setText("k");
        ui->pbn_l->setText("l");
        ui->pbn_semicolonOrColon->setText(";");
        ui->pbn_apostropheOrDoubleQuote->setText("'");

        ui->pbn_z->setText("z");
        ui->pbn_x->setText("x");
        ui->pbn_c->setText("c");
        ui->pbn_v->setText("v");
        ui->pbn_b->setText("b");
        ui->pbn_n->setText("n");
        ui->pbn_m->setText("m");
        ui->pbn_commaOrLeftAngleBrackets->setText(",");
        ui->pbn_dotOrRightAngleBrackets->setText(".");
        ui->pbn_slashOrQuestionMark->setText("/");
    }
}

void LockScreenForm::keyClicked(QString key)
{
    QPushButton *pbn = qobject_cast<QPushButton*>(sender());
    if (!pbn) {
        return;
    }

    qDebug() << pbn->text();

    const QString objName = pbn->objectName().toLower();
    const QString pbnText = pbn->text();
    QStringList specialObjNames;
    specialObjNames << "caps" << "enter" << "clear" << "space"
                    << "left" << "right" << "table" << "eye";
    for (const QString &name : specialObjNames){
        if (objName.contains(name) && !StringUtils::isDigital(pbnText))
            return;
    }
    qDebug() << objName;

    QInputMethodEvent event;
    event.setCommitString(key);

    QGuiApplication::sendEvent(ui->le_password, &event);
}

void LockScreenForm::funcKeyClicked(int key)
{
    switch (key) {
    case Qt::Key_Clear:
        ui->le_password->clear();
        break;
    case Qt::Key_Left:
        ui->le_password->setCursorPosition(
            ui->le_password->cursorPosition() - 1);
        break;
    case Qt::Key_Right:
        ui->le_password->setCursorPosition(
            ui->le_password->cursorPosition() + 1);
        break;
    default:
        QGuiApplication::postEvent(
            ui->le_password,
            new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier));
        QGuiApplication::postEvent(
            ui->le_password,
            new QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier));
        break;
    }
}

void LockScreenForm::on_pbn_leftShift_clicked(bool checked)
{
    ui->pbn_rightShift->setChecked(checked);
    capsLockEnable(checked);
    if (checked)
        ui->pbn_capsLock->setChecked(false);
}

void LockScreenForm::on_pbn_rightShift_clicked(bool checked)
{
    ui->pbn_leftShift->setChecked(checked);
    capsLockEnable(checked);
    if (checked)
        ui->pbn_capsLock->setChecked(false);
}

void LockScreenForm::slot_keyClicked()
{
    QPushButton *pbn = (QPushButton *)this->sender();
    keyClicked(pbn->text().mid(0, 1));

    if (ui->pbn_leftShift->isChecked()) {
        ui->pbn_leftShift->setChecked(false);
        ui->pbn_rightShift->setChecked(false);
        capsLockEnable(false);
    }
}

void LockScreenForm::on_pbn_clear_clicked()
{
    funcKeyClicked(Qt::Key_Clear);
}

void LockScreenForm::on_pbn_backspace_clicked()
{
    funcKeyClicked(Qt::Key_Backspace);
}

void LockScreenForm::on_pbn_space_clicked()
{
    on_pbn_enter_clicked();
}

void LockScreenForm::on_pbn_left_clicked()
{
    funcKeyClicked(Qt::Key_Left);
}

void LockScreenForm::on_pbn_right_clicked()
{
    funcKeyClicked(Qt::Key_Right);
}

void LockScreenForm::on_pbn_table_clicked()
{
    funcKeyClicked(Qt::Key_Tab);
}

void LockScreenForm::on_pbn_eye_clicked(bool checked)
{
    ui->le_password->setEchoMode(
        checked ? QLineEdit::Password : QLineEdit::Normal);
}
