#include "modelessdialogcontainerform.h"
#include <QApplication>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractButton>
#include <QTimer>
#include <messagebox.h>
#include <authoritymanager.h>
#include "cobotlog.h"
#include "instance.h"
#include "resolutionutils.h"
#include "virtualkeyboard.h"
static ModellessDialogContainerForm *s_instance = 0;

static const QSet<QString> logicTreeOperationKeys {
    "pbn_startProject",
    "pbn_stopProject",
    "pbn_stepProject",
    "pbn_stepOver",
    "pbn_clearBreakPoint",
    "pbn_enableAllBreakPoint",
    "pbn_editBreakPoint"
};

static const QSet<QString> detailPages {
    "MoveJConditionForm",
    "MoveCConditionForm",
    "MoveLConditionForm",
    "WaypointConditionForm",
    "SetConditionForm",
    "SocketConditionForm",
    "SPrintfConditionForm",
    "ScriptConditionForm",
    "PalletizingConditionForm"
};

ModellessDialogContainerForm *ModellessDialogContainerForm::instance()
{
    return s_instance;
}

ModellessDialogContainerForm::ModellessDialogContainerForm(QWidget *parent) :
    AbstractWidget(parent),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ModellessDialogContainerForm)
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
    Instance::setModellessDialogContainerForm(this);
    m_mapDialogs.clear();

    this->setFocusPolicy(Qt::ClickFocus);
    this->setObjectName("ModellessDialogContainerForm");

#ifdef Q_OS_ANDROID
    this->hide();
#else
    setWindowFlags(
        // Qt::WindowDoesNotAcceptFocus
        Qt::Tool
        | Qt::FramelessWindowHint
        | Qt::BypassWindowManagerHint
        );
#endif
    // connect(qApp, &QApplication::focusChanged,
    //         this, &ModellessDialogContainerForm::slot_FoucusChanged);

    connect(ui->pbn_close, &QPushButton::clicked,
            this, [this] {
                this->hide();
            });
    ui->widget_tools->hide();
}

ModellessDialogContainerForm::~ModellessDialogContainerForm()
{
    delete ui;
}

void ModellessDialogContainerForm::showDialog(const QString &name)
{
    if (!m_mapDialogs.contains(name)) return;
    registDialogInfo& info = m_mapDialogs[name];

    if (!info.isExit) {
        bool callSuccess = QMetaObject::invokeMethod(
            Instance::programmingContainerForm(),
            "exchangeStackWidget",
            Qt::DirectConnection,
            Q_ARG(QString, name));

        if (!callSuccess) return;
    }

    if (ui->widget_tools->isVisible()) {
        this->setFixedSize(ResolutionUtils::getRatioSize(info.width, info.height + ui->widget_tools->height()));
    } else {
        this->setFixedSize(ResolutionUtils::getRatioSize(info.width, info.height));
    }
    QWidget *pWidget = info.widget;
    if (!pWidget) return;
    ui->m_stackedWidget->setCurrentWidget(pWidget);

    if (!this->isVisible()
        || pWidget != ui->m_stackedWidget->currentWidget()) {
        int width = Instance::common()->property("actualAppWidth").value<int>();
        int height = Instance::common()->property("actualAppHeight").value<int>();
        int startX = Instance::common()->property("actualAppX").value<int>();
        int startY = Instance::common()->property("actualAppY").value<int>();
        QPoint pos;
        // pos.setX(startX + (width - this->width()) / 2);
        pos.setX(startX + (width - this->width()) - 20);
        pos.setY(startY + (height - this->height()) / 2);
        QScreen *screen = qApp->screenAt(QPoint(pos.x() + this->width(), pos.y() + this->height()));
        if (!screen && Instance::mainWidget()) {
            int x = 0, y = 0;
            QWidget *main = static_cast<QWidget *>(Instance::mainWidget());
            if(qApp->primaryScreen()){
                x = (qApp->primaryScreen()->availableGeometry().width() - main->width()) / 2;
                y = (qApp->primaryScreen()->availableGeometry().height() - main->height()) / 2;
            }
            main->move(x, y);
            // pos.setX(x + (main->width() - this->width()) / 2);
            pos.setX(x + (main->width() - this->width()) - 20);
            pos.setY(y + (main->height() - this->height()) / 2);
        }
        this->show();
        this->move(pos);
        // PRINT_MSG(QString("this->move(pos): %1, %2").arg(pos.x()).arg(pos.y()));
    }
}

bool ModellessDialogContainerForm::isVisible() const
{
    return QWidget::isVisible();
}

void ModellessDialogContainerForm::registDialog(const QString &name, QWidget *widget, int width, int height, bool isExit)
{
    if (m_mapDialogs.contains(name)) {
        qDebug() << __FUNCTION__ << "The name already exists.";
        return;
    }

    if (!widget) {
        // widget = new QWidget(this);
        return;
    }

    registDialogInfo info;
    info.width = width;
    info.height = height;
    info.widget = widget;
    info.isExit = isExit;

    m_mapDialogs.insert(name, info);
    ui->m_stackedWidget->addWidget(widget);
}

bool ModellessDialogContainerForm::isExit(const QString &pluginName)
{
    if (!m_mapDialogs.contains(pluginName)) {
        return false;
    }
    registDialogInfo info = m_mapDialogs[pluginName];
    return info.isExit;
}

QWidget* ModellessDialogContainerForm::replacePluginWidget(const QString &pluginName, QWidget *newWidget)
{

    if (!newWidget) {
        return nullptr;
    }

    if (!m_mapDialogs.contains(pluginName)) {
        return nullptr;
    }

    registDialogInfo info = m_mapDialogs.value(pluginName);
    QWidget *oldWidget = info.widget;
    int stackFormIndex = ui->m_stackedWidget->indexOf(oldWidget);

    if (newWidget == oldWidget) {
        return nullptr;
    }

    // 更新信息
    m_mapDialogs[pluginName].widget = newWidget;

    ui->m_stackedWidget->removeWidget(oldWidget);
    ui->m_stackedWidget->insertWidget(stackFormIndex, newWidget);

    if (newWidget->objectName() == pluginName) {
        m_mapDialogs[pluginName].isExit = true;
    } else {
        m_mapDialogs[pluginName].isExit = false;
    }
    return oldWidget;
}

void ModellessDialogContainerForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void ModellessDialogContainerForm::showEvent(QShowEvent *event)
{
    qApp->installEventFilter(this);
    QWidget::showEvent(event);
}

void ModellessDialogContainerForm::hideEvent(QHideEvent *event)
{
    qApp->removeEventFilter(this);
    QWidget::hideEvent(event);
}

bool ModellessDialogContainerForm::eventFilter(QObject *obj, QEvent *event)
{
    if (!QWidget::isVisible()) {
        return QWidget::eventFilter(obj, event);
    }

    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        if (VirtualKeyboard::instance()->isVisible()) {
            return QWidget::eventFilter(obj, event);
        }

        if (QApplication::activeModalWidget()
            && QApplication::activeModalWidget() != this) {
            return QWidget::eventFilter(obj, event);
        }

        QPoint globalPos = QCursor::pos();
        QWidget* widget = QApplication::widgetAt(globalPos);

        if (!this->rect().contains(this->mapFromGlobal(globalPos))) {

            if (!widget) {
                return QWidget::eventFilter(obj, event);
            }

            if (logicTreeOperationKeys.contains(widget->objectName())) {
                return QWidget::eventFilter(obj, event);
            }

            QObject *parent = widget->parent();
            while (parent) {
                if (parent == this) {
                    return QWidget::eventFilter(obj, event);
                }
                parent = parent->parent();
            }

            const Authority authority = AuthorityManager::instance()->currentAuthority();
            if (detailPages.contains(ui->m_stackedWidget->currentWidget()->objectName())
                && authority.authLevel() > Authority::UserAccess) {
                int ret = MessageBox::question(tr("This will close the condition page. Please confirm that the data has been saved. Do you want to continue?"));
                if (ret == MessageBox::Yes) {
                    this->hide();
                    QMetaObject::invokeMethod(
                        Instance::logicTreeModel(),
                        "closeCurItemEditMode",
                        Qt::DirectConnection);
                }
                return true;
            }

            this->hide();
        }


        break;
    }

    default:
        break;
    }

    return QWidget::eventFilter(obj, event);
}

void ModellessDialogContainerForm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPos() - this->frameGeometry().topLeft();
        m_isDragging = true;
    }
    QWidget::mouseMoveEvent(event);
}

void ModellessDialogContainerForm::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        QPoint newPos = event->globalPos() - m_dragPos;
        this->move(newPos);
    }
    QWidget::mouseMoveEvent(event);
}

void ModellessDialogContainerForm::mouseReleaseEvent(QMouseEvent *event)
{

    m_isDragging = false;
    QWidget::mouseReleaseEvent(event);
}

void ModellessDialogContainerForm::slot_FoucusChanged(QWidget *old, QWidget *now)
{
    if (!isVisible()) {
        return;
    }

    if (old != now) {
        QWidget::hide();
    }
    if (nullptr != now
        && isAncestorOf(now)
        && now->inherits("QWidget")) {
        setFocusObject(now);
    }
}

void Ui_ModellessDialogContainerForm::setupUi(QWidget *MonitoringContainerForm)
{
    mainLayout = new QVBoxLayout(MonitoringContainerForm);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    widget_tools = new QWidget(MonitoringContainerForm);
    widget_tools->setObjectName("widget_tools");
    widget_tools->setMinimumSize(QSize(0, 40));
    widget_tools->setMaximumSize(QSize(16777215, 40));

    hLayout_tools = new QHBoxLayout(widget_tools);
    hLayout_tools->setSpacing(33);
    hLayout_tools->setObjectName("hLayout_tools");
    hLayout_tools->setContentsMargins(10, 0, 10, 0);

    QSpacerItem *horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout_tools->addSpacerItem(horizontalSpacer);

    pbn_close = new QPushButton(widget_tools);
    pbn_close->setIcon(QIcon(":/mainwidget/image/mainwidget/logformclose.svg"));
    pbn_close->setIconSize(QSize(24, 24));
    pbn_close->setObjectName("pbn_close");
    pbn_close->setFixedSize(24, 24);
    hLayout_tools->addWidget(pbn_close);

    mainLayout->addWidget(widget_tools);

    m_stackedWidget = new QStackedWidget(MonitoringContainerForm);
    m_stackedWidget->setObjectName("m_stackedWidget");
    MonitoringContainerForm->setStyleSheet(QString::fromUtf8(
        "QWidget#widget_tools {"
        "   background: rgb(255, 255, 255);"
        "   border-top: 3px solid rgb(230, 230, 239);"
        "   border-right: 3px solid rgb(230, 230, 239);"
        "   border-bottom: 0px solid rgb(230, 230, 239);"
        "   border-left: 3px solid rgb(230, 230, 239);"
        "}"
        "QWidget#widget_tools QPushButton {"
        "   color: black;"
        "   background-color: rgb(255, 255, 255);"
        "   border:none;"
        "}"
        "QWidget#m_stackedWidget {"
        "   background: rgb(255, 255, 255);"
        "   border-top: 0px solid rgb(230, 230, 239);"
        "   border-right: 3px solid rgb(230, 230, 239);"
        "   border-bottom: 3px solid rgb(230, 230, 239);"
        "   border-left: 3px solid rgb(230, 230, 239);"
        "}"
        "QWidget#m_stackedWidget QPushButton {"
        "   background: rgb(255, 255, 255);"
        "   border: 1px solid rgb(217, 217, 217);"
        "   border-radius: 4px;"
        "   color: rgb(20, 20, 20);"
        "}"
        "QWidget#m_stackedWidget QPushButton:pressed {"
        "   background-color: rgb(235, 235, 237);"
        "}"
        "QWidget#m_stackedWidget QPushButton:disabled {"
        "   background: rgb(255, 255, 255);"
        "   border: 1px solid rgb(232, 232, 232);"
        "   border-radius: 4px;"
        "   color: rgb(191, 191, 191);"
        "}"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"left\"] {"
        "   background: rgb(255, 255, 255);"
        "   color: rgb(20, 20, 20);"
        "   border-style: solid;"
        "   border-width: 1px;"
        "   border-color: rgb(217, 217, 217);"
        "   border-top-left-radius: 4px;"
        "   border-bottom-left-radius: 4px;"
        "   border-top-right-radius: 0px;"
        "   border-bottom-right-radius: 0px;"
        "}"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"right\"] {"
        "   background: rgb(255, 255, 255);"
        "   color: rgb(20, 20, 20);"
        "   border-style: solid;"
        "   border-width: 1px;"
        "   border-color: rgb(217, 217, 217);"
        "   border-top-right-radius: 4px;"
        "   border-bottom-right-radius: 4px;"
        "   border-top-left-radius: 0px;"
        "   border-bottom-left-radius: 0px;"
        "}"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"left\"]:checked,"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"right\"]:checked {"
        "   color: rgb(41, 90, 176);"
        "   border-color: rgb(41, 90, 176);"
        "}"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"left\"]:disabled,"
        "QWidget#m_stackedWidget QPushButton[checkableButton=\"right\"]:disabled {"
        "   color: rgb(191, 191, 191);"
        "   border-color: rgb(217, 217, 217);"
        "}"
        "QWidget#m_stackedWidget QPushButton[highlight=\"true\"]{"
        "   color: red;"
        "   background-color: qlineargradient("
        "       spread:pad, x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 rgb(234, 226, 169), "
        "       stop:1 rgb(229, 205, 32)"
        "   );"
        "}"
        "QWidget#m_stackedWidget MessageBox QPushButton{"
        "   background-color: qlineargradient("
        "       spread:pad, x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 rgb(255, 141, 122), "
        "       stop:1 rgb(228, 16, 71)"
        "       );"
        "   width: 80px;"
        "   height: 26px"
        "}"
        "QWidget#m_stackedWidget MessageBox QPushButton:pressed{"
        "   background-color: qlineargradient("
        "       spread:pad, x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 rgb(228, 16, 71), "
        "       stop:1 rgb(255, 141, 122)"
        "   );"
        "}"
        "QWidget#m_stackedWidget QTextEdit {"
        "    border: 1px solid rgb(217, 217, 217);"
        "    border-radius: 4px;"
        "    color: rgb(20, 20, 20);"
        "}"
        ""));

    mainLayout->addWidget(m_stackedWidget);
}

void Ui_ModellessDialogContainerForm::retranslateUi(QWidget *MonitoringContainerForm)
{
}
