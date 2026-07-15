#include "progressbarform.h"
#include "ui_progressbarform.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include "propertydefine.h"
#include "communicationengine.h"
const int PROCESS_TIME = 30 * 1000;

ProgressBarForm::ProgressBarForm(QWidget *parent) :
    AbstractWidget(parent, 400, 144, 400, 144),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ProgressBarForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    m_processInterval = PROCESS_TIME;

    m_timerIsTaskTimeOut = new QTimer;
    m_timerIsTaskTimeOut->setSingleShot(true);
    connect(m_timerIsTaskTimeOut, &QTimer::timeout,
            this, &ProgressBarForm::slot_waitTimeout);

    m_timerUpdateUI = new QTimer;
    m_timerUpdateUI->setInterval(300);
    connect(m_timerUpdateUI, &QTimer::timeout,
            this, &ProgressBarForm::slot_timeout);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_ProcessBarFormBaseOnTimerEvent,
            this,
            &ProgressBarForm::processEvent);
}

ProgressBarForm::~ProgressBarForm()
{
    delete ui;

    if (m_timerIsTaskTimeOut) {
        stopTaskIsTimeOutTimer();

        delete m_timerIsTaskTimeOut;
        m_timerIsTaskTimeOut = Q_NULLPTR;
    }

    if (m_timerUpdateUI) {
        stopUpdateUiTimer();

        delete m_timerUpdateUI;
        m_timerUpdateUI = Q_NULLPTR;
    }
}

void ProgressBarForm::initData()
{
    ui->pbn_close->setVisible(false);
    ui->lbl_msg->setStyleSheet("color: black;");
    m_processInterval = PROCESS_TIME;
}

void ProgressBarForm::processEvent(const RobotEventInfo &robotEventInfo)
{
    initData();

    switch (static_cast<int>(robotEventInfo.m_eventType)) {
    case RobotEventInfo::UserEvent_RobotShutDown:
        m_msg = tr("Robot is shuting down...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ProgramStart:
        m_msg = tr("Program is starting...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ProgramPause:
        m_msg = tr("Program is pausing...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ProgramContinue:
        m_msg = tr("Program is resuming...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ProgramStop:
        m_msg = tr("Program is stopping...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_LoadingLanguage:
        m_msg = "Loading language...";
        showDialog();
        break;
    case RobotEventInfo::UserEvent_DuringExecuteCmd:
        m_msg = tr("Executing commands...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ConnectController: {
        m_msg = tr("Connecting, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
    }
        break;
    case RobotEventInfo::UserEvent_LoadIdentify:
        m_msg = tr("Load tuning, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_DownLoadApk: {
        m_msg = tr("Downloading InoCobotTP installer file, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
    }
        break;
    case RobotEventInfo::UserEvent_ExportTechpadConfigures: {
        m_msg = tr("Exporting teach pendant backup config file, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_DisconnectController:
        m_msg = tr("Disconnecting, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_WriteData:
        m_msg = tr("Syncing data, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ReadData:
        m_msg = tr("Refreshing data, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_LoadingFile: {
        m_msg = tr("Loading file, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_EmergeStop:
        m_msg = tr("Emergency stop, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_ChangeControlAuthority:
        m_msg = tr("Changing control authority, please wait...");
        showDialog();
        break;
    case RobotEventInfo::UserEvent_CreateProject:{
        m_msg = tr("Creating project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_DeleteProject:{
        m_msg = tr("Deleting project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_RenameProject:{
        m_msg = tr("Renaming project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_PasteProject: {
        m_msg = tr("Pasting project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_LoadProject: {
        m_msg = tr("Loading project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_SyncProject: {
        m_msg = tr("Synchronizing project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_ExportProject: {
        m_msg = tr("Exporting project, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_UpdateApp: {
        m_msg = tr("Updating app, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_GeneralMatchSync: {
        m_msg = tr("Syncing universality parameters, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_LoadRobotModel: {
        m_msg = tr("Loading robot model, please wait...");
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval < PROCESS_TIME ? PROCESS_TIME : interval;
        showDialog();
        break;
    }
    case RobotEventInfo::UserEvent_LoadLanguageFinish:
    case RobotEventInfo::UserEvent_CmdExecCompleted:
    case RobotEventInfo::UserEvent_ProgramStartFinish:
    case RobotEventInfo::UserEvent_ProgramPauseFinish:
    case RobotEventInfo::UserEvent_ProgramContinueFinish:
    case RobotEventInfo::UserEvent_ProgramStopFinish:
    case RobotEventInfo::UserEvent_ConnectFinish:
    case RobotEventInfo::UserEvent_LoadIdentifyFinish:
    case RobotEventInfo::UserEvent_DownLoadApkFinish:
    case RobotEventInfo::UserEvent_ExportTechpadConfiguresFinish:
    case RobotEventInfo::UserEvent_DisconnectFinish:
    case RobotEventInfo::UserEvent_WriteDataFinished:
    case RobotEventInfo::UserEvent_ReadDataFinished:
    case RobotEventInfo::UserEvent_LoadFileFinish:
    case RobotEventInfo::UserEvent_EmergeStopFinish:
    case RobotEventInfo::UserEvent_ChangeControlAuthorityFinish:
    case RobotEventInfo::UserEvent_CreateProjectFinish:
    case RobotEventInfo::UserEvent_DeleteProjectFinish:
    case RobotEventInfo::UserEvent_RenameProjectFinish:
    case RobotEventInfo::UserEvent_PasteProjectFinish:
    case RobotEventInfo::UserEvent_LoadProjectFinish:
    case RobotEventInfo::UserEvent_SyncProjectFinish:
    case RobotEventInfo::UserEvent_ExportProjectFinish:
    case RobotEventInfo::UserEvent_UpdateAppFinish:
    case RobotEventInfo::UserEvent_GeneralMatchSyncFinished:
    case RobotEventInfo::UserEvent_ImportLanguagePackageFinish:
    case RobotEventInfo::UserEvent_LoadRobotModelFinished:
        hideDialog();
        break;
    case RobotEventInfo::UserEvent_Timeout:
        this->setVisible(true);
        ui->pbn_close->setVisible(true);
        ui->progressBar->setValue(ui->progressBar->maximum());
        ui->lbl_msg->setText(tr("Operation timed out."));
        ui->lbl_msg->setStyleSheet("color: red;");
        break;
    case RobotEventInfo::UserEvent_Error:
        this->setVisible(true);
        stopTaskIsTimeOutTimer();
        stopUpdateUiTimer();
        ui->progressBar->setValue(ui->progressBar->maximum());
        ui->pbn_close->setVisible(true);
        ui->lbl_msg->setText(robotEventInfo.m_eventContent);
        ui->lbl_msg->setStyleSheet("color: red;");
        break;
    default:
        m_msg = robotEventInfo.m_eventTitle;
        int interval = robotEventInfo.m_eventContent.toInt() * 1000;
        m_processInterval = interval > 0 ? interval : PROCESS_TIME;
        showDialog();
        break;
    }
}

void ProgressBarForm::startTaskIsTimeOutTimer()
{
    if (!m_timerIsTaskTimeOut->isActive()) {
        m_timerIsTaskTimeOut->start(m_processInterval);
        connect(m_timerIsTaskTimeOut, &QTimer::timeout,
                this, &ProgressBarForm::slot_waitTimeout, Qt::UniqueConnection);
    }
}

void ProgressBarForm::stopTaskIsTimeOutTimer()
{
    if (m_timerIsTaskTimeOut->isActive()) {
        m_timerIsTaskTimeOut->stop();
    }

    disconnect(m_timerIsTaskTimeOut, &QTimer::timeout, Q_NULLPTR, Q_NULLPTR);
}

void ProgressBarForm::startUpdateUiTimer()
{
    if (!m_timerUpdateUI->isActive()) {
        m_timerUpdateUI->start();
        connect(m_timerUpdateUI, &QTimer::timeout,
                this, &ProgressBarForm::slot_timeout, Qt::UniqueConnection);
    }
}

void ProgressBarForm::stopUpdateUiTimer()
{
    if (m_timerUpdateUI->isActive()) {
        m_timerUpdateUI->stop();
    }

    disconnect(m_timerUpdateUI, &QTimer::timeout, Q_NULLPTR, Q_NULLPTR);
}

void ProgressBarForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Progress bar"));

    ui->pbn_close->setProperty(InfoFlow_HighLevelOperationLog,tr("Close"));
}

void ProgressBarForm::showDialog()
{
    ui->lbl_msg->setText(m_msg);
    ui->progressBar->setValue(ui->progressBar->minimum());

    DialogContainerForm::instance()->showDialog(
        DialogContainerForm::DialogStackForm_ProgressBarForm);

    startUpdateUiTimer();
    startTaskIsTimeOutTimer();
}

void ProgressBarForm::hideDialog()
{
    stopTaskIsTimeOutTimer();
    stopUpdateUiTimer();

    ui->progressBar->setValue(ui->progressBar->maximum());

    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_ProgressBarForm);
}

void ProgressBarForm::slot_timeout()
{
    int value = ui->progressBar->value();
    int maximum = ui->progressBar->maximum();

    if (value < maximum - 1) {
        ui->progressBar->setValue((value + 1) % maximum + 1);
    }
}

void ProgressBarForm::slot_waitTimeout()
{
    stopTaskIsTimeOutTimer();
    stopUpdateUiTimer();

    DialogContainerForm::instance()
        ->processRobotEventInfo(RobotEventInfo::UserEvent_Timeout);
}

void ProgressBarForm::on_pbn_close_clicked()
{
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_ProgressBarForm);
}
