#include "dialogcontainerform.h"
#include <QStackedWidget>
#include <QLayout>
#include <QMutex>
#include <QCloseEvent>
#include <QTimer>
#include <QDebug>
#include <QPainterPath>
#include "changeauthorityform.h"
#include "currentauthorityform.h"
#include "customauthorityform.h"
#include "connectcontrollerform.h"
#include "lockscreenform.h"
#include "communicationengine.h"
#include "progressbarform.h"
#include "roboteventinfo.h"
#include "cobotlog.h"
#include "tcpserverengine.h"
#include "tcpclientengine.h"
#include "windowmanager.h"
#include "instance.h"
#include "resolutionutils.h"
#include "configinfo.h"
#include "controllerform.h"
#include "processbarformwithcomm.h"
#include "controllerauthorityform.h"
#include <QMessageBox>
static DialogContainerForm *s_instance = 0;

DialogContainerForm *DialogContainerForm::instance()
{
    return s_instance;
}

DialogContainerForm::DialogContainerForm(QWidget *parent) :
    GeneralCustomWidget(parent)
{
    s_instance = this;
    Instance::setDialogContainerForm(this);

    m_mutex = new QMutex;
    m_dialogStack.clear();

    m_stackedWidget = new QStackedWidget(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_stackedWidget);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Widget);
    setWindowModality(Qt::WindowModal);
    m_stackedWidget->insertWidget(
        DialogStackForm_LockScreenForm,
        m_lockScreenForm = new LockScreenForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ProgressBarForm,
        m_progressBarForm = new ProgressBarForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ProcessBarFormWithComm,
        m_processBarFormWithComm = new ProcessBarFormWithComm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_CurrentAuthorityForm,
        m_currentAuthorityForm = new CurrentAuthorityForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ChangeAuthorityForm,
        m_changeAuthorityForm = new ChangeAuthorityForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_CustomAuthorityForm,
        m_customAuthorityForm = new CustomAuthorityForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ControllerAuthorityForm,
        m_controllerAuthorityForm = new ControllerAuthorityForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ConnectControllerForm,
        m_connectControllerForm = new ConnectControllerForm(m_stackedWidget));
    m_stackedWidget->insertWidget(
        DialogStackForm_ControllerForm,
        m_controllerForm = new ControllerForm(m_stackedWidget));

    m_stackedWidget->setObjectName("m_stackedWidget");
    m_stackedWidget->setStyleSheet("#m_stackedWidget {background: rgb(230, 230, 239);}");
}

void DialogContainerForm::showDialog()
{
    if (!this->isVisible() && !m_dialogStack.isEmpty())
        WindowManager::instance()->enqueueCmdInfo(
            WindowCmd_DialogContainerFormShow);
}

void DialogContainerForm::showDialog(int dialogType)
{
    if (!this->isVisible()
        || dialogType != m_stackedWidget->currentIndex()) {
        switch (dialogType) {
        case DialogStackForm_LockScreenForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(752, 372));
            break;
        case DialogStackForm_ProgressBarForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(400, 144));
            break;
        case DialogStackForm_ProcessBarFormWithComm:
            this->setFixedSize(ResolutionUtils::getRatioSize(431, 189));
            break;
        case DialogStackForm_CurrentAuthorityForm:
            m_currentAuthorityForm->updateCurrentAuthority();
            this->setFixedSize(ResolutionUtils::getRatioSize(408, 328));
            break;
        case DialogStackForm_ChangeAuthorityForm:
            m_changeAuthorityForm->clearPassword();
            this->setFixedSize(ResolutionUtils::getRatioSize(408, 328));
            break;
        case DialogStackForm_CustomAuthorityForm:
            m_customAuthorityForm->clearAuthorityName();
            this->setFixedSize(ResolutionUtils::getRatioSize(408, 284));
            break;
        case DialogStackForm_ControllerAuthorityForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(515, 416));
            break;
        case DialogStackForm_ConnectControllerForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(370, 259));
            break;
        case DialogStackForm_ControllerForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(370, 259));
            break;
        case DialogStackForm_BasicConditionContainerForm:
            this->setFixedSize(ResolutionUtils::getRatioSize(515, 416));
            break;
        default: {
                for (auto it = m_mapDialogs.begin(); it != m_mapDialogs.end(); ++it) {
                    if (it.value().index == dialogType) {
                        this->setFixedSize(ResolutionUtils::getRatioSize(it.value().width, it.value().height));
                        break;
                    }
                }
            }
            qDebug() << "dialog type does not exist";
            break;
        }

        m_stackedWidget->setFixedSize(this->size());
        m_stackedWidget->setCurrentIndex(dialogType);
        int width = Instance::common()->property("actualAppWidth").value<int>();
        int height = Instance::common()->property("actualAppHeight").value<int>();
        int startX = Instance::common()->property("actualAppX").value<int>();
        int startY = Instance::common()->property("actualAppY").value<int>();
        QPoint pos;
        pos.setX(startX + (width - this->width()) / 2);
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
            pos.setX(x + (main->width() - this->width()) / 2);
            pos.setY(y + (main->height() - this->height()) / 2);
        }
        this->move(pos);
        // this->move((width - this->width()) / 2 + startX, (height - this->height()) / 2 + startY);

        m_mutex->lock();
        if (!m_dialogStack.contains(dialogType)) {
            m_dialogStack.push(dialogType);
        } else {
            m_dialogStack.removeOne(dialogType);
            m_dialogStack.push(dialogType);
        }
        m_mutex->unlock();

        WindowManager::instance()->enqueueCmdInfo(
            WindowCmd_DialogContainerFormShow);
    }
}

void DialogContainerForm::hideDialog(int dialogType)
{
    m_mutex->lock();

    if (m_dialogStack.contains(dialogType))
        m_dialogStack.removeOne(dialogType);

    m_mutex->unlock();

    if (m_dialogStack.isEmpty()) {
        // Make closing immediate even if WindowManager queue is busy.
        if (this->isVisible()) {
            this->hide();
        }
        WindowManager::instance()->enqueueCmdInfo(
            WindowCmd_DialogContainerFormHide);
    } else if (this->isVisible()) {
        qDebug() << m_dialogStack.top();
        showDialog(m_dialogStack.top());
    }
}

void DialogContainerForm::showPasswordValidationForm(QWidget *widgetCaller)
{
    m_lockScreenForm->setWidgetCaller(widgetCaller);
    showLockScreenForm();
}

void DialogContainerForm::slot_showLockScreenForm()
{
#if CommonLib_Dialog_DeveloperMode_Enabled == 1
    if (Instance::common()->property("isDeveloperMode").value<bool>()) {
        return;
    }
#endif

    if (Instance::common()->property("lockScreenEnabled").value<bool>()) {
        showLockScreenForm();
    }
}

void DialogContainerForm::showLockScreenForm()
{
    showDialog(DialogStackForm_LockScreenForm);
}

void DialogContainerForm::processRobotEventInfo(
    const RobotEventInfo &robotEventInfo)
{
    LOG_INFO(robotEventInfo.getPrintInfo());

    switch (static_cast<int>(robotEventInfo.m_eventType)) {
    case RobotEventInfo::UserEvent_RobotShutDown:
    case RobotEventInfo::UserEvent_DuringExecuteCmd:
    case RobotEventInfo::UserEvent_CmdExecCompleted:
    case RobotEventInfo::UserEvent_ProgramStart:
    case RobotEventInfo::UserEvent_ProgramStartFinish:
    case RobotEventInfo::UserEvent_ProgramPause:
    case RobotEventInfo::UserEvent_ProgramPauseFinish:
    case RobotEventInfo::UserEvent_ProgramContinue:
    case RobotEventInfo::UserEvent_ProgramContinueFinish:
    case RobotEventInfo::UserEvent_ProgramStop:
    case RobotEventInfo::UserEvent_ProgramStopFinish:
    case RobotEventInfo::UserEvent_LoadingLanguage:
    case RobotEventInfo::UserEvent_LoadLanguageFinish:
    case RobotEventInfo::UserEvent_ConnectController:
    case RobotEventInfo::UserEvent_ConnectFinish:
    case RobotEventInfo::UserEvent_LoadIdentify:
    case RobotEventInfo::UserEvent_LoadIdentifyFinish:
    case RobotEventInfo::UserEvent_DownLoadApk:
    case RobotEventInfo::UserEvent_DownLoadApkFinish:
    case RobotEventInfo::UserEvent_ExportTechpadConfigures:
    case RobotEventInfo::UserEvent_ExportTechpadConfiguresFinish:
    case RobotEventInfo::UserEvent_DisconnectController:
    case RobotEventInfo::UserEvent_DisconnectFinish:
    case RobotEventInfo::UserEvent_WriteData:
    case RobotEventInfo::UserEvent_WriteDataFinished:
    case RobotEventInfo::UserEvent_ReadData:
    case RobotEventInfo::UserEvent_ReadDataFinished:
    case RobotEventInfo::UserEvent_LoadingFile:
    case RobotEventInfo::UserEvent_LoadFileFinish:
    case RobotEventInfo::UserEvent_EmergeStop:
    case RobotEventInfo::UserEvent_EmergeStopFinish:
    case RobotEventInfo::UserEvent_Timeout:
    case RobotEventInfo::UserEvent_Error:
    case RobotEventInfo::UserEvent_ChangeControlAuthority:
    case RobotEventInfo::UserEvent_ChangeControlAuthorityFinish:
    case RobotEventInfo::UserEvent_CreateProject:
    case RobotEventInfo::UserEvent_CreateProjectFinish:
    case RobotEventInfo::UserEvent_DeleteProject:
    case RobotEventInfo::UserEvent_DeleteProjectFinish:
    case RobotEventInfo::UserEvent_RenameProject:
    case RobotEventInfo::UserEvent_RenameProjectFinish:
    case RobotEventInfo::UserEvent_PasteProject:
    case RobotEventInfo::UserEvent_PasteProjectFinish:
    case RobotEventInfo::UserEvent_LoadProject:
    case RobotEventInfo::UserEvent_LoadProjectFinish:
    case RobotEventInfo::UserEvent_SyncProject:
    case RobotEventInfo::UserEvent_SyncProjectFinish:
    case RobotEventInfo::UserEvent_ExportProject:
    case RobotEventInfo::UserEvent_ExportProjectFinish:
    case RobotEventInfo::UserEvent_UpdateApp:
    case RobotEventInfo::UserEvent_UpdateAppFinish:
    case RobotEventInfo::UserEvent_GeneralMatchSync:
    case RobotEventInfo::UserEvent_GeneralMatchSyncFinished:
    case RobotEventInfo::UserEvent_LoadRobotModel:
    case RobotEventInfo::UserEvent_LoadRobotModelFinished:
        m_progressBarForm->processEvent(robotEventInfo);
        break;
    default:
        break;
    }
}

bool DialogContainerForm::isVisible() const
{
    return QWidget::isVisible();
}

void DialogContainerForm::registDialog(QWidget *widget, int width, int height, int index)
{
    if (widget == nullptr) return;

    bool bIndexExist = false;
    for (auto it = m_mapDialogs.begin(); it != m_mapDialogs.end(); ++it) {
        if (it.value().index == index) {
            bIndexExist = true;
            break;
        }
    }
    if (index == -1 || bIndexExist) {
        index = m_stackedWidget->count();
    }

    DialogInfo info;
    info.width = width;
    info.height = height;
    info.index = index;
    info.widget = widget;

    m_stackedWidget->insertWidget(info.index, widget);
    m_mapDialogs[widget->metaObject()->className()] = info;

    qDebug() << "######################## index = " << info.index << ", name = " << info.widget->metaObject()->className();
}

void DialogContainerForm::showDialog(const QString &sName)
{
    if (!m_mapDialogs.contains(sName)) return;

    DialogInfo info = m_mapDialogs[sName];
    this->setFixedSize(ResolutionUtils::getRatioSize(info.width, info.height));
    showDialog(info.index);
}

void DialogContainerForm::hideDialog(const QString &sName)
{
    if (!m_mapDialogs.contains(sName)) return;

    DialogInfo info = m_mapDialogs[sName];
    hideDialog(info.index);
}

QWidget *DialogContainerForm::getReigstedDialog(const QString &sName)
{
    if (!m_mapDialogs.contains(sName)) return nullptr;

    return m_mapDialogs[sName].widget;
}

void DialogContainerForm::closeEvent(QCloseEvent *closeEvent)
{
    Instance::common()->setProperty("isCloseDialogContainerForm", true);
    closeEvent->ignore();

#ifdef QT_DEBUG
    if (!dynamic_cast<QWidget *>(Instance::mainWidget())->isVisible()) {
        QMetaObject::invokeMethod(
            Instance::mainWidget(), "power", Qt::DirectConnection);
    } else {
        WindowManager::instance()->enqueueCmdInfo(
            WindowCmd_DialogContainerFormHide);
        m_dialogStack.clear();
    }
#endif
}
