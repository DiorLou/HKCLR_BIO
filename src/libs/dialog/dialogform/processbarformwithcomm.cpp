#include "processbarformwithcomm.h"
#include "ui_processbarformwithcomm.h"
#include <QTimer>
#include <QDebug>
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include "commandinfo.h"
#include "communicationengine.h"
#include <algorithm>
#include "messagebox.h"
#include "communication.h"
#include "cobotlog.h"
#include "propertydefine.h"
ProcessBarFormWithComm *s_instance = 0;

ProcessBarFormWithComm *ProcessBarFormWithComm::instance()
{
    return s_instance;
}

ProcessBarFormWithComm::ProcessBarFormWithComm(QWidget *parent) :
    AbstractWidget(parent, 431, 140, 431, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::ProcessBarFormWithComm)
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
    m_timer = new QTimer;
    m_timer->setInterval(500);
    ui->progressBar->setRange(0, 100);
    connect(m_timer, &QTimer::timeout, this, &ProcessBarFormWithComm::slot_timeout);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::singnal_processBarFormWithComm_currentState,
            this,
            [=](QObject *obj, bool isSuccess, int percent, InoTaskState state, QString errorStr) {
                if (obj != this)
                    return;
                QString tips;
                if (!isSuccess) {
                    m_isConnected = Communication::instance()->isConnected();
                    m_timer->stop();
                    if (!m_isConnected) {
                        QString tmp = tr("Not connected to controller, failed to read task status.");
                        hideDialog(tmp);
                    } else {
                        QString tmp = tr("Communication with controller falid.") + "\r\n"
                                    + tr("If you choose Yes, teach pendant will retry.") + "\r\n"
                                    + tr("If you choose No, teach pendant will try to close current task.");
                        int ret = MessageBox::question(tmp);
                        if (MessageBox::Yes == ret) {
                            m_timer->start();
                        } else if (MessageBox::No == ret) {
                            on_pbn_stop_clicked();
                        }
                    }
                    return;
                }
                if (errorStr.isEmpty()) {
                    switch (state) {
                    case (Task_Falid): {
                        tips = tr("%1 falid!").arg(m_taskName);
                        break;
                    }
                    case (Task_UnknowState): {
                        tips = tr("The controller is starting the task...");
                        break;
                    }
                    case (Task_InProcess): {
                        tips = tr("%1 in processing...").arg(m_taskName);
                        if (percent == 100)
                            percent = 99;
                        break;
                    }
                    case (Task_FineshedSuccess): {
                        tips = tr("%1 completed successfully.").arg(m_taskName);
                        percent = 100;
                        break;
                    }
                    case (Task_WasForciblyTerminated): {
                        tips = tr("%1 was forcibly terminated.").arg(m_taskName);
                        break;
                    }
                    default:
                        tips = tr("The controller is starting the task...");
                        break;
                    }
                } else {
                    tips = errorStr;
                }

                if (m_autoProcessbarBaseOnTimer) {
                    ui->progressBar->setValue((ui->progressBar->value() + 10) % 99);
                } else {
                    ui->progressBar->setValue(std::max(ui->progressBar->value(), percent));
                }

                switch (state) {
                case (Task_UnknowState):
                case (Task_InProcess): {
                    ui->label_tips->setText(tr("State:") + " " + tips);
                    break;
                }
                case (Task_Falid): {
                    m_timer->stop();
                    PRINT_ERROR(tips);
                    hideDialog(tips);
                    break;
                }
                case (Task_FineshedSuccess): {
                    m_timer->stop();
                    PRINT_MSG(tips);
                    hideDialog(tips);
                    break;
                }
                case (Task_WasForciblyTerminated): {
                    m_timer->stop();
                    PRINT_ERROR(tips);
                    hideDialog(tips);
                    break;
                }
                default: {
                    break;
                }
                }
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::singnal_processBarFormWithComm_stopResult,
            this,
            [=](QObject *obj, bool isStopSuccess, QString tips) {
                if (obj != this)
                    return;
                if (!isStopSuccess) {
                    if (tips.isEmpty())
                        tips = tr("Failed to stop %1.").arg(m_taskName);
                    PRINT_ERROR(tips);
                    if (QMessageBox::Yes == MessageBox::question(tips + " " + tr("Try again?")))
                        on_pbn_stop_clicked();
                    else
                        hideDialog("");
                } else {
                    if (tips.isEmpty())
                        tips = tr("%1 stopped successfully.").arg(m_taskName);
                    PRINT_MSG(tips);
                    hideDialog(tips);
                }
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this,
            [=](ControllerConnectionState state) {
                if (state == ControllerConnectionState::ControllerConnectionState_Connected) {
                    m_isConnected = true;
                } else {
                    m_isConnected = false;
                }
                // if(isVisible() && !m_isConnected)
                //     hideDialog(tr("Connect was closed! Task states unknown!"));
            });
}

ProcessBarFormWithComm::~ProcessBarFormWithComm()
{
    delete ui;
}

void ProcessBarFormWithComm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property, tr("Progress bar"));
}

void ProcessBarFormWithComm::showEvent(QShowEvent *)
{
    // ui->progressBar->setValue(ui->progressBar->minimum());
    ui->progressBar->setValue(0);
    if (!m_timer->isActive())
        m_timer->start();
}

void ProcessBarFormWithComm::hideEvent(QHideEvent *)
{
    if (DialogContainerForm::instance()->property("isNeedLogicProcess").toBool()) {
        if (m_timer->isActive())
            m_timer->stop();
        m_autoProcessbarBaseOnTimer = false;
        m_percentType = -1;
        m_stopType = -1;
        m_stopVariant = QVariant();
        m_percentVariant = QVariant();
    }
}

void ProcessBarFormWithComm::slot_timeout()
{
    // qDebug()<<(AbstractCmd::CmdType)m_percentType<<m_percentType<<"slot_timeout";
    CommunicationEngine::instance()->enqueueCmd_setData(this, (AbstractCmd::CmdType)m_percentType, m_percentVariant);
}

void ProcessBarFormWithComm::on_pbn_stop_clicked()
{
    if (m_stopType != -1 && Communication::instance()->isConnected())
        CommunicationEngine::instance()->enqueueCmd_setData(this, (AbstractCmd::CmdType)m_stopType, m_stopVariant);
    else
        hideDialog(tr("Not connected to controller, failed to stop %1.").arg(m_taskName));
}

void ProcessBarFormWithComm::showDialog()
{
    ui->progressBar->setValue(0);
    DialogContainerForm::instance()->showDialog(
        DialogContainerForm::DialogStackForm_ProcessBarFormWithComm);
}

void ProcessBarFormWithComm::hideDialog(QString tips)
{
    m_timer->stop();
    if (!isVisible())
        return;
    if (!tips.isEmpty())
        MessageBox::information(tips, QMessageBox::Ok, QMessageBox::NoButton, false);
    ui->label_tips->setText("");
    DialogContainerForm::instance()->hideDialog(
        DialogContainerForm::DialogStackForm_ProcessBarFormWithComm);
}

void ProcessBarFormWithComm::setCommunicationType(QString taskName, int percentType, int stopType,
                                                  QVariant percentVariant, QVariant stopVariant)
{
    m_autoProcessbarBaseOnTimer = false;
    m_percentType = -1;
    m_stopType = -1;
    m_stopVariant = QVariant();
    m_percentVariant = QVariant();
    // 应当在显示前设置AbstractCmd::CmdType,
    // percentType用于通讯获取当前进度，stopType用于终止
    // 进度为100 或者任务结束 终止成功 隐藏当前dialog
    // 当stopType = -1时，禁用停止按键
    if (isVisible())
        return;
    m_taskName = taskName;
    m_percentType = percentType;
    m_stopType = stopType;
    qDebug() << (int)AbstractCmd::CmdType_ReadErrExportStaToLocal << m_percentType << "m_percentType is";
    ui->pbn_stop->setVisible(m_stopType != -1);
    ui->pbn_stop->setEnabled(m_stopType != -1);
    ui->pbn_stop->setText(m_stopType != -1 ? tr("Stop") : tr("%1 cannot be manually stopped.").arg(m_taskName));
    m_stopVariant = stopVariant;
    m_percentVariant = percentVariant;
    ui->lbl_title->setText(m_taskName);
    this->update();
}

void ProcessBarFormWithComm::setAutoProcessbarBaseOnTimer(bool isAuto)
{
    m_autoProcessbarBaseOnTimer = isAuto;
}

void ProcessBarFormWithComm::processEvent(const RobotEventInfo &robotEventInfo)
{
    // switch (static_cast<int>(robotEventInfo.m_eventType)) {
    // case RobotEventInfo::UserEvent_RobotShutDown:
    //     m_taskName = tr("Shutdown in progress");
    //     showDialog();
    //     break;
    // case RobotEventInfo::UserEvent_ProgramIsStopping:
    //     m_taskName = tr("Program is stopping");
    //     showDialog();
    //     break;
    // case RobotEventInfo::UserEvent_ProgramStopped:
    //     hideDialog();
    //     break;
    // case RobotEventInfo::UserEvent_LoadingLanguage:
    //     m_taskName = tr("Loading language");
    //     showDialog();
    //     break;
    // case RobotEventInfo::UserEvent_LoadLanguageFinish:
    //     hideDialog();
    //     break;
    // case RobotEventInfo::UserEvent_DuringExecuteCmd:
    //     m_taskName = tr("During the execute command");
    //     showDialog();
    //     break;
    // case RobotEventInfo::UserEvent_CmdExecCompleted:
    //     hideDialog();
    //     break;
    // default:
    //     break;
    // }
}
