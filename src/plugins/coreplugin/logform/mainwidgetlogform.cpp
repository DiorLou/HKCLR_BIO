#include "mainwidgetlogform.h"
#include "ui_mainwidgetlogform.h"
#include "dialogcontainerform.h"
#include "mainwidget.h"
#include "cobotlog.h"
#include "mainwidget.h"
#include "communicationengine.h"
#include "propertydefine.h"
#include "authoritytr.h"
#include "messagebox.h"
#include <QScrollBar>
#include <QTimer>
#include "instance.h"
#include "communication.h"
const int LOG_FORM_WIDTH = 620;
const int LOG_FORM_HEIGHT = 664;
const int MAX_ROW_COUNT = 1000;
inline QString HTML_SOURCE = QString(R"(<p style="color: %1; ">%2</p>)");  // line-height: 0.7687;
#define GETDATA CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_GetHistoryAlarm, m_historyAlarm);
static void setMargin(QTextBrowser *edit)
{
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(100, QTextBlockFormat::ProportionalHeight);
    blockFormat.setBottomMargin(-4);
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
}

inline void setTextForEdit(QTextBrowser *edit, const QString &msg, bool isMoveCursor)
{
    if (!msg.isEmpty()) {
        edit->append(msg);
        if (isMoveCursor)
            edit->moveCursor(QTextCursor::End);
    }
}

MainWidgetLogForm::MainWidgetLogForm(QWidget *parent) :
    AbstractWidget(parent, LOG_FORM_WIDTH, LOG_FORM_HEIGHT),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::MainWidgetLogForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    //m_logWidget = ui->tab_log;
    Instance::setLogForm(this);
    setWindowFlags(
        Qt::WindowDoesNotAcceptFocus
        | Qt::Tool
        | Qt::FramelessWindowHint
        | Qt::WindowStaysOnTopHint
        | Qt::BypassWindowManagerHint);
    connect(qApp, &QApplication::focusChanged,
            this, &MainWidgetLogForm::slot_FoucusChanged);
    resize(ResolutionUtils::getRatioSize(LOG_FORM_WIDTH, LOG_FORM_HEIGHT));
    // connect(CobotLog::instance(),
    //         &CobotLog::signal_addPrint,
    //         this,
    //         &MainWidgetLogForm::slot_print);
    // connect(CobotLog::instance(),
    //         &CobotLog::signal_addLog,
    //         this,
    //         &MainWidgetLogForm::slot_log);
    // connect(CobotLog::instance(),
    //         &CobotLog::signal_addHistoryAlarm,
    //         this,
    //         [=](const QString &msg){
    //             addLogMsg(ui->edit_historyAlarm, msg);
    //         });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_getHistoryAlarmRes,
            this,
            [=](QObject *obj, const QStringList &alarm) {
                if (obj != this)
                    return;
                if (m_historyAlarm != alarm) {
                    ui->edit_historyAlarm->clear();
                    for (int i = 0; i < alarm.size(); ++i) {
                        addLogMsg(ui->edit_historyAlarm,
                                  HTML_SOURCE.arg("#FF0000", alarm[i]));
                    }
                    m_historyAlarm = alarm;
                }
            });

    ui->edit_log->setUndoRedoEnabled(false);
    ui->edit_operation->setUndoRedoEnabled(false);
    ui->edit_outputError->setUndoRedoEnabled(false);
    ui->edit_outputWarning->setUndoRedoEnabled(false);
    ui->edit_outputInfornation->setUndoRedoEnabled(false);
    ui->edit_outputAll->setUndoRedoEnabled(false);
    ui->edit_historyAlarm->setUndoRedoEnabled(false);

    ui->edit_log->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    ui->edit_operation->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    ui->edit_outputError->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    ui->edit_outputWarning->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    ui->edit_outputInfornation->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    ui->edit_outputAll->document()->setMaximumBlockCount(MAX_ROW_COUNT);
    // ui->edit_historyAlarm->document()->setMaximumBlockCount(MAX_ROW_COUNT);

    // ui->edit_log->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_operation->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_outputError->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_outputWarning->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_outputInfornation->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_outputAll->setSrcollAreaMargins(0, 0, 0, 12);
    // ui->edit_historyAlarm->setSrcollAreaMargins(0, 0, 0, 12);

    ui->edit_log->verticalScrollBar()->setSingleStep(28);
    ui->edit_operation->verticalScrollBar()->setSingleStep(28);
    ui->edit_outputError->verticalScrollBar()->setSingleStep(28);
    ui->edit_outputWarning->verticalScrollBar()->setSingleStep(28);
    ui->edit_outputInfornation->verticalScrollBar()->setSingleStep(28);
    ui->edit_outputAll->verticalScrollBar()->setSingleStep(28);
    ui->edit_historyAlarm->verticalScrollBar()->setSingleStep(28);

    setMargin(ui->edit_log);
    setMargin(ui->edit_operation);
    setMargin(ui->edit_outputError);
    setMargin(ui->edit_outputWarning);
    setMargin(ui->edit_outputInfornation);
    setMargin(ui->edit_outputAll);
    setMargin(ui->edit_historyAlarm);

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    m_timer->setSingleShot(false);
    connect(m_timer, &QTimer::timeout, this, [=]() {
        updateUI(false);
    });
    QIcon autoIcon;
    autoIcon.addFile(":/mainwidget/image/mainwidget/logformpin.svg", QSize(24,24), QIcon::Normal, QIcon::Off);
    autoIcon.addFile(":/mainwidget/image/mainwidget/logformpined.svg", QSize(24,24), QIcon::Normal, QIcon::On);
    //autoIcon.addFile(":/mainwidget/image/mainwidget/logformpined.svg", QSize(20,20), QIcon::Disabled, QIcon::On);
    ui->pbn_fixed->setIcon(autoIcon);
    setCurrentIndex(0);
}

void MainWidgetLogForm::updateUI(bool isMoveCursor)
{
    if (!isVisible())
        m_timer->stop();
    switch (ui->stackedWidget->currentIndex()) {
    case 0:
        setTextForEdit(ui->edit_outputAll, CobotLog::instance()->getAll(), isMoveCursor);
        CobotLog::instance()->clearAll();
        break;
    case 1:
        setTextForEdit(ui->edit_outputInfornation, CobotLog::instance()->getMsg(), isMoveCursor);
        CobotLog::instance()->clearMsg();
        break;
    case 2:
        setTextForEdit(ui->edit_outputWarning, CobotLog::instance()->getWarn(), isMoveCursor);
        CobotLog::instance()->clearWarn();
        break;
    case 3:
        setTextForEdit(ui->edit_outputError, CobotLog::instance()->getError(), isMoveCursor);
        CobotLog::instance()->clearError();
        break;
    case 4:
        setTextForEdit(ui->edit_operation, CobotLog::instance()->getOperation(), isMoveCursor);
        CobotLog::instance()->clearOperation();
        break;
    case 5:
        GETDATA;
        break;
    case 6:
        setTextForEdit(ui->edit_log, CobotLog::instance()->getLog(), isMoveCursor);
        CobotLog::instance()->clearLog();
        break;
    }
}

void MainWidgetLogForm::showEvent(QShowEvent *ev)
{
    GETDATA;
    updateUI(true);
    // ui->edit_log->moveCursor(QTextCursor::End);
    // ui->edit_operation->moveCursor(QTextCursor::End);
    // ui->edit_outputError->moveCursor(QTextCursor::End);
    // ui->edit_outputWarning->moveCursor(QTextCursor::End);
    // ui->edit_outputInfornation->moveCursor(QTextCursor::End);
    // ui->edit_outputAll->moveCursor(QTextCursor::End);
    // ui->edit_historyAlarm->moveCursor(QTextCursor::End);
    m_timer->start();
}

MainWidgetLogForm::~MainWidgetLogForm()
{
    delete ui;
}

void MainWidgetLogForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property, AuthorityTr::tr("Log"));
}

void MainWidgetLogForm::slot_FoucusChanged(QWidget *old, QWidget *now)
{
    if (!isVisible()) {
        return;
    }
    if (old != now && !m_messageBoxShow && !ui->pbn_fixed->isChecked()) {
        QWidget::hide();
    }
}

void MainWidgetLogForm::slot_print(CobotLog::InoInfoType type, const QString &msg)
{
    QString temp = msg;
    if (type != CobotLog::InoInfoType::Operation_Info)
        MainWidget::instance()->setBtnLogText(msg);
    if (type != CobotLog::Operation_Info)
        temp.replace('<', "&lt;").replace('>', "&gt;");
    switch (type) {
    case CobotLog::Message_Info: {
        temp = HTML_SOURCE.arg("#295AB0", tr("[Message] ") + temp);
        addLogMsg(ui->edit_outputInfornation, temp);
        addLogMsg(ui->edit_outputWarning, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Warning_Info: {
        temp = HTML_SOURCE.arg("#E3C232", tr("[Warning] ") + temp);
        addLogMsg(ui->edit_outputWarning, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Error_Info: {
        temp = HTML_SOURCE.arg("#F04848", tr("[Error] ") + temp);
        addLogMsg(ui->edit_outputError, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Operation_Info: {
        temp = HTML_SOURCE.arg("#000000", tr("[Operation] ") + temp);
        addLogMsg(ui->edit_operation, temp);
        break;
    }
    default: break;
    }
}

void MainWidgetLogForm::slot_log(CobotLog::InoLogType type, const QString &msg)
{
    QString temp = msg;
    temp.replace('<', "&lt;").replace('>', "&gt;");
    switch (type) {
    case CobotLog::Trace_Log: {
        temp = HTML_SOURCE.arg("#000000", tr("[Trace] ") + temp);
        break;
    }
    case CobotLog::Debug_Log: {
        temp = HTML_SOURCE.arg("#000000", tr("[Debug] ") + temp);
        break;
    }
    case CobotLog::Info_Log: {
        temp = HTML_SOURCE.arg("#295AB0", tr("[Info] ") + temp);
        break;
    }
    case CobotLog::Warn_Log: {
        temp = HTML_SOURCE.arg("#E3C232", tr("[Warning] ") + temp);
        break;
    }
    case CobotLog::Error_Log: {
        temp = HTML_SOURCE.arg("#F04848", tr("[Error] ") + temp);
        break;
    }
    case CobotLog::Critical_Log: {
        temp = HTML_SOURCE.arg("#F04848", tr("[Critical] ") + temp);
        break;
    }
    default: break;
    }
    addLogMsg(ui->edit_log, temp);
}

void MainWidgetLogForm::addLogMsg(QTextBrowser *edit, const QString &msg)
{
    QString temp = msg;
    edit->append(temp.replace("\r\n", "<br>").replace("\n", "<br>"));

    if (!edit->isVisible())
        edit->moveCursor(QTextCursor::End);
}

void MainWidgetLogForm::on_pbn_close_clicked()
{
    QWidget::hide();
}

void MainWidgetLogForm::addLogMsg(int type, const QString &msg)
{
    QString temp = msg;
    // m_model->addLog(type,msg);
    switch (type) {
    case CobotLog::Message_Info: {
        temp = HTML_SOURCE.arg("#295AB0", msg);
        addLogMsg(ui->edit_outputInfornation, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Warning_Info: {
        temp = HTML_SOURCE.arg("#E3C232", msg);
        addLogMsg(ui->edit_outputWarning, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Error_Info: {
        temp = HTML_SOURCE.arg("#F04848", msg);
        addLogMsg(ui->edit_outputError, temp);
        addLogMsg(ui->edit_outputAll, temp);
        break;
    }
    case CobotLog::Operation_Info: {
        temp = HTML_SOURCE.arg("#000000", msg);
        addLogMsg(ui->edit_operation, temp);
    }
    default: break;
    }
}

void MainWidgetLogForm::logViewEnabled(bool isEnabled)
{
    // isEnabled = true;
    if (isEnabled) {
        ui->radioButton_7->show();
    } else {
        //ui->tabWidget->removeTab(ui->tabWidget->indexOf(m_logWidget));
        if(ui->radioButton_7->isChecked())
            setCurrentIndex(0);
        ui->radioButton_7->hide();
    }
}

void MainWidgetLogForm::on_tabWidget_currentChanged(int index)
{
    updateUI(true);
    // m_timer->start();
    // if (index == 5) {
    //     m_timer->start();
    //     GETDATA;
    // } else {
    //     m_timer->stop();
    // }
}

void MainWidgetLogForm::hideLogWidget()
{
    QWidget::hide();
}

void MainWidgetLogForm::on_pbn_clear_clicked()
{
    // #ifdef PLATFORM_COBOT_TP_WINDOWS
    //     QWidget::hide();
    // #endif
    QString tips;
    switch (ui->stackedWidget->currentIndex()) {
    case 0:
        tips = tr("Are you sure you want to clear all the information?");
        break;
    case 1:
        tips = tr("Are you sure you want to clear output information?");
        break;
    case 2:
        tips = tr("Are you sure you want to clear warning information?");
        break;
    case 3:
        tips = tr("Are you sure you want to clear error information?");
        break;
    case 4:
        tips = tr("Are you sure you want to clear operation information?");
        break;
    case 5:
        tips = tr("Are you sure you want to clear alarm history information?");
        break;
    case 6:
        tips = tr("Are you sure you want to clear log information?");
        break;
    }
    if (ui->stackedWidget->currentIndex() == 5) {
        if (Communication::instance()->GetCurCtrlAuthority() == InoCtrlAuthority_IO
            || Communication::instance()->GetCurCtrlAuthority() == InoCtrlAuthority_IO_AUTO) {
            m_messageBoxShow = true;
            MessageBox::warning(tr("Clearing historical alarms is not allowed in remote IO mode."));
            show();
            m_messageBoxShow = false;
            return;
        }
    }
    m_messageBoxShow = true;
    if (MessageBox::Yes != MessageBox::question(tips)) {
        m_messageBoxShow = false;
        show();
        return;
    }
    m_messageBoxShow = false;
    switch (ui->stackedWidget->currentIndex()) {
    case 0:
        ui->edit_outputError->clear();
        ui->edit_outputWarning->clear();
        ui->edit_outputInfornation->clear();
        ui->edit_outputAll->clear();
        break;
    case 1:
        ui->edit_outputInfornation->clear();
        break;
    case 2:
        ui->edit_outputWarning->clear();
        break;
    case 3:
        ui->edit_outputError->clear();
        break;
    case 4:
        ui->edit_operation->clear();
        break;
    case 5:
        CommunicationEngine::instance()->enqueueCmd(this,
                                                    AbstractCmd::CmdType_ClearHistoryWarn);
        GETDATA;
        break;
    case 6:
        ui->edit_log->clear();
        break;
    }
    show();
}
// void MainWidgetLogForm::on_btn_clear_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear alarm history information?"))) {
//         show();
//         return;
//     }
//     CommunicationEngine::instance()->enqueueCmd(this,
//                                                 AbstractCmd::CmdType_ClearHistoryWarn);
//     GETDATA;
//     show();
// }
// void MainWidgetLogForm::on_pbn_clearAll_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear all the information?"))) {
//         show();
//         return;
//     }
//     ui->edit_outputError->clear();
//     ui->edit_outputWarning->clear();
//     ui->edit_outputInfornation->clear();
//     ui->edit_outputAll->clear();
//     show();
// }

// void MainWidgetLogForm::on_pbn_clearInfo_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear output information?"))) {
//         show();
//         return;
//     }
//     ui->edit_outputInfornation->clear();
//     show();
// }

// void MainWidgetLogForm::on_pbn_clearWarning_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear warning information?"))) {
//         show();
//         return;
//     }
//     ui->edit_outputWarning->clear();
//     show();
// }

// void MainWidgetLogForm::on_pbn_clearError_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear error information?"))) {
//         show();
//         return;
//     }
//     ui->edit_outputError->clear();
//     show();
// }

// void MainWidgetLogForm::on_pbn_claerOperation_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear operation information?"))) {
//         show();
//         return;
//     }
//     ui->edit_operation->clear();
//     show();
// }

// void MainWidgetLogForm::on_pbn_clearLog_clicked()
// {
// #ifdef PLATFORM_COBOT_TP_WINDOWS
//     QWidget::hide();
// #endif
//     if (MessageBox::Yes != MessageBox::question(tr("Are you sure you want to clear log information?"))) {
//         show();
//         return;
//     }
//     ui->edit_log->clear();
//     ui->edit_operation->clear();
//     ui->edit_outputError->clear();
//     ui->edit_outputWarning->clear();
//     ui->edit_outputInfornation->clear();
//     ui->edit_outputAll->clear();
//     show();
// }

void MainWidgetLogForm::on_radioButton_clicked()
{
    setCurrentIndex(0);
}

void MainWidgetLogForm::on_radioButton_2_clicked()
{
    setCurrentIndex(1);
}

void MainWidgetLogForm::on_radioButton_3_clicked()
{
    setCurrentIndex(2);
}
void MainWidgetLogForm::on_radioButton_4_clicked()
{
    setCurrentIndex(3);
}
void MainWidgetLogForm::on_radioButton_5_clicked()
{
    setCurrentIndex(4);
}
void MainWidgetLogForm::on_radioButton_6_clicked()
{
    setCurrentIndex(5);
}
void MainWidgetLogForm::on_radioButton_7_clicked()
{
    setCurrentIndex(6);
}
void MainWidgetLogForm::setCurrentIndex(int index)
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_5->setChecked(false);
    ui->radioButton_6->setChecked(false);
    ui->radioButton_7->setChecked(false);
    switch (index) {
    case 0: ui->radioButton->setChecked(true); break;
    case 1: ui->radioButton_2->setChecked(true); break;
    case 2: ui->radioButton_3->setChecked(true); break;
    case 3: ui->radioButton_4->setChecked(true); break;
    case 4: ui->radioButton_5->setChecked(true); break;
    case 5: ui->radioButton_6->setChecked(true); break;
    case 6: ui->radioButton_7->setChecked(true); break;
    }
    ui->stackedWidget->setCurrentIndex(index);
}
