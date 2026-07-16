#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QCloseEvent>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QIcon>
#include <QTimer>
#include "authoritymanager.h"
#include "authoritytr.h"
#include "communication.h"
#include "messagebox.h"
#include "communicationengine.h"
#include "dialogcontainerform.h"
// #include "glcameraoperation.h"
#include "roboteventinfo.h"
#include "cobotlog.h"
#include "pluginmanager.h"
#include "databaselocal.h"
#include "tcpclientengine.h"
#include "tcpserverengine.h"
#include "windowmanager.h"
#include "instance.h"
#include "configinfo.h"
#include "plugindialog.h"
#include "logform/mainwidgetlogform.h"
#include "passwordconfirmform.h"
#include "cobotlog.h"
#include "lineedit.h"
#include "authoritytr.h"
#if defined(__ANDROID__)
    #include <QJniObject>
    #include <QJniEnvironment>

#endif
#include <qdatetime.h>
#include "metapath.h"
#include "projectdata.h"
#include "propertydefine.h"
#include "flowwidgetmanager.h"
#include "common.h"
#include <QScreen>
#include "splashscreen.h"
#include "pluginspec.h"
#define TitleIconSize ResolutionUtils::getRatioSize(QSize(28, 28))
static MainWidget *s_instance = 0;

MainWidget *MainWidget::instance()
{
    return s_instance;
}

MainWidget::MainWidget(QWidget *parent) :
    AbstractWidget(parent, 1280, 800),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::MainWidget)
#else
    ui(AbstractWidget::ui)
#endif
{
    m_delayInit = true;
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

#ifdef Q_OS_WIN
    ui->pbn_minimize->setVisible(true);
#else
    ui->pbn_minimize->setVisible(false);
    ui->lbl_line->setVisible(false);
#endif

    s_instance = this;
    Instance::setMainWidget(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    updateBottomWidgetHeight();
    processAfterInitUi(this);

    new PasswordConfirmForm;

    connect(Communication::instance(),
            &DataCollectionInterface::signal_sendRealTimeEndSpeed,
            this, &MainWidget::slot_recvRealTimeEndSpeed);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_robotShutdownInterface_result,
            this, &MainWidget::slot_robotShutdownInterface_result);

    connect(Instance::instance(), &Instance::enabledChanged,
            MainWidget::instance(), &MainWidget::slot_enableEdit);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &MainWidget::slot_controllerConnectionStatusChanged);

    connect(PasswordConfirmForm::instance(),
            &PasswordConfirmForm::signal_passwd_confirm_result,
            this, &MainWidget::slot_passwd_confirm_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_clearAlarmInterface_result,
            this, &MainWidget::slot_clearAlarmInterface_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_speed_changed,
            this, &MainWidget::slot_speed_changed);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableRobotInterface_result,
            this, &MainWidget::slot_enableRobotInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableStateChanged,
            this, &MainWidget::slot_enableStateChanged);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerStateChanged,
            this, &MainWidget::slot_controllerStateChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setEmergecyInterface_result,
            this, &MainWidget::slot_setEmergecyInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_emergecyStateChanged,
            this, &MainWidget::slot_emergecyStateChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_tragteach_status,
            this, &MainWidget::slot_tragteach_status);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_needMainWidgetInfo,
            this,
            &MainWidget::slot_infoMessageBox);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_needMainWidgetWarning,
            this,
            &MainWidget::slot_warningMessageBox);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_needMainWidgetError,
            this,
            &MainWidget::slot_errorMessageBox);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setspeed_result,
            this, &MainWidget::slot_setspeed_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setdevicemode_result,
            this, &MainWidget::slot_setdevicemode_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectSuccess,
            this, &MainWidget::slot_connectSuccess);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_robotBodyPowerStateChanged,
            this,
            &MainWidget::slot_robotBodyPowerStateChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controlAuthorityChanged,
            this, [this](InoCtrlAuthority type) {
                AuthorityManager::instance()->updateAuthority();
            });

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_speedReducingTriggerdChanged,
            this,
            &MainWidget::slot_speedReducingTriggerdChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_generalmatch_getinfo,
            this, &MainWidget::slot_generalmatch_getinfo);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_generalmatch_getparamsyncstatus,
            this, &MainWidget::slot_generalmatch_getparamsyncstatus);

    connect(ui->tabWidget, &QTabWidget::currentChanged,
            this, &MainWidget::currentChanged);

    connect(ui->pbn_enable,
            &SwitchButtonInside::Clicked,
            this,
            &MainWidget::slot_pbn_enable_clicked);
    connect(AuthorityManager::instance(),
            &AuthorityManager::signal_changeAuthoritySuccess,
            this, &MainWidget::slot_changeAuthoritySuccess);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controlAuthorityChanged,
            this, &MainWidget::slot_controllerAuthorityChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_getfirstbootstatus_result,
            this, &MainWidget::slot_getfirstbootstatus_result);

    connect(qApp, &QApplication::applicationStateChanged,
            this, [this](Qt::ApplicationState state){
                if (state == Qt::ApplicationInactive && !isVisible() && !isActiveWindow()
                    && !SplashScreen::instance()->isVisible()) {
                        power();
                    }
                });

    m_timerRefreshTime = new QTimer();
    m_timerRefreshTime->setInterval(100);
    m_timerRefreshTime->setSingleShot(false);
    m_timerRefreshTime->start();
    connect(m_timerRefreshTime,
            &QTimer::timeout,
            this,
            [=]() {
                // m_timerRefreshTime->stop();
                QString temp = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
                ui->lbl_time->setText(temp);
            });
    m_logForm = new MainWidgetLogForm();

    QIcon icon;

    QSize tempSize = ResolutionUtils::getRatioSize(QSize(40, 40));
    icon.addFile(":/mainwidget/image/mainwidget/emergestopon.svg", tempSize, QIcon::Normal, QIcon::On);
    icon.addFile(":/mainwidget/image/mainwidget/emergestopondisabled.svg", tempSize, QIcon::Disabled, QIcon::On);
    icon.addFile(":/mainwidget/image/mainwidget/emergestopoff.svg", tempSize, QIcon::Normal, QIcon::Off);
    icon.addFile(":/mainwidget/image/mainwidget/emergestopoffdisabled.svg", tempSize, QIcon::Disabled, QIcon::Off);
    ui->pbn_emergeStop->setIcon(icon);
    ui->pbn_emergeStop->setIconSize(tempSize);

    ui->pbn_pluginManager->setVisible(false);
    slot_robotBodyPowerStateChanged(m_robotBodyPowerState);
    slot_controllerAuthorityChanged(InoCtrlAuthority_Unknown);

    ui->pbn_dragteach->setVisible(false);
    ui->edit_robotspeed->setRange(1, 100);

}

MainWidget::~MainWidget()
{
    qDebug() << "MainWidget::~MainWidget()";
    delete ui;
}

void MainWidget::requestRoadPoint(QObject *object, TakePointMode mode)
{
    setTakePointUI(true);

    if (mode == TakePointMode_Normal) {
        ui->pbn_cancel->setText(tr("Cancel"));
        ui->pbn_setRoadPoint->setText(tr("OK"));
        ui->pbn_cancel->setVisible(true);
    } else if (mode == TakePointMode_WaypointTeach) {
        // 路点示教
        ui->pbn_cancel->setVisible(false);
        ui->pbn_setRoadPoint->setText(tr("Back"));
    }

    m_requestRoadPointInstance = object;
    m_preTabWidgetIndex = ui->tabWidget->currentIndex();
    setCurrentTab(TAB_TEACH_INDEX);

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (i == TAB_TEACH_INDEX) continue;
        ui->tabWidget->setTabEnabled(i, false);
    }

    AuthorityManager::instance()->autoChangeAuthority(Authority::GetPoint);
}

void MainWidget::power(bool isNotConfirmShutdown)
{
#if defined(WIN32)
    Q_UNUSED(isNotConfirmShutdown);
    // Exit through Qt's event loop. Killing our own executable with taskkill
    // bypasses normal thread/plugin cleanup and can leave the file locked.
    QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
#elif defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    if (activity.isValid()) {
        jint pid = activity.callStaticObjectMethod("android/os/Process", "myPid", "()I")
                       .callMethod<jint>("intValue", "()I");
        activity.callStaticMethod<void>("android/os/Process", "killProcess", "(I)V", pid);
    }

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

bool MainWidget::isVisible() const
{
    return QWidget::isVisible();
}

void MainWidget::updateDeviceMode()
{
    MetaType::RobotDeviceMode curMode = Communication::instance()->GetCurDeviceMode();
    if (MetaType::RobotDeviceMode_Unknow == curMode) {
        return;
    }

    if (!Communication::instance()->getCurDragTeachStatus()) {
        AuthorityManager::instance()->updateAuthority();
    }

    UpdateDeviceModeStatus(curMode);
}

int MainWidget::addTabWidget(QWidget *widget, const QString &tabText,
                             const QString &tabIcon)
{
    static int index = 0;
    while (m_hashTabIndexAndWidget.contains(index)) {
        ++index;
    }
    m_hashTabIndexAndWidget[index++]
        = QPair<QWidget *, QString>(widget, tabText);
    m_hashTabIndexAndIcon[index++] = tabIcon;
    return index - 1;
}

int MainWidget::addTabWidget(int index, QWidget *widget,
                             const QString &tabText, const QString &tabIcon)
{
    if (!m_hashTabIndexAndWidget.contains(index)) {
        m_hashTabIndexAndWidget.insert(
            index, QPair<QWidget *, QString>(widget, tabText));
        m_hashTabIndexAndIcon.insert(index, tabIcon);
        return index;
    }
    QPair<QWidget *, QString> p = m_hashTabIndexAndWidget[index];
    m_hashTabIndexAndWidget[index] = QPair<QWidget *, QString>(widget, tabText);
    m_hashTabIndexAndIcon[index] = tabIcon;
    return addTabWidget(p.first, p.second, tabIcon);
}

void MainWidget::setTabEnable(int index, bool bEnable, bool directEffect)
{
    if (index < 0 || index >= ui->tabWidget->count()) {
        return;
    }

    if (directEffect) {
        ui->tabWidget->setTabEnabled(index, bEnable);
        ui->tabWidget->widget(index)->setEnabled(bEnable);
    } else {
        m_mapWidgetEnable[index] = bEnable;
    }
}

void MainWidget::initialize()
{
    setTakePointUI(false);

    ui->lbl_time->setLimit(10, 5);
    connect(ui->lbl_time, &ClickableLabel::signal_Clicked,
            this, [this] {
                CobotLog::instance()->setFreqLogPrint(true);
            });

    connect(ui->edit_robotspeed, &IntLineEdit::focusOut,
            this, [=]{
                int curSpeed = ui->edit_robotspeed->text().toInt();
                ui->hSlider_speed->setValue(curSpeed);
                setRobotSpeed(curSpeed);
            });

    ui->hSlider_speed->installEventFilter(this);
    ui->pbn_zeroPose->setMoveStopSlotDisable();
}

void MainWidget::retranslateUi()
{
    ui->retranslateUi(this);
    ui->pbn_enable->SetText(tr("Enable"));
    ui->widget_title->setProperty(InfoFlow_Property, tr("Navigation bar"));
    ui->bottomWidget->setProperty(InfoFlow_Property, tr("Tool bar"));

    ui->pbn_emergeStop->setProperty(InfoFlow_HighLevelOperationLog,
                                    tr("Emergency stop"));
    ui->pbn_poweroff->setProperty(InfoFlow_HighLevelOperationLog,
                                  tr("Power off"));
    ui->pbn_minimize->setProperty(InfoFlow_HighLevelOperationLog,
                                  tr("Minimize"));
    ui->pbn_wifi->setProperty(InfoFlow_HighLevelOperationLog,
                              tr("WiFi"));
    ui->pbn_controllerAuthority->setProperty(InfoFlow_HighLevelOperationLog,
                                             tr("Controller permission"));

    retranslateTitleBar();
    updateCurrentAuthorityInfo();
    ui->edit_robotspeed->setText(QString::number(ui->hSlider_speed->value()));
    this->setWindowTitle(tr("Inovance Cobot Teach Pendant"));
}

void MainWidget::on_pbn_setRoadPoint_clicked()
{
    ui->tabWidget->setCurrentIndex(m_preTabWidgetIndex);
    setTakePointUI(false);

    for (int i = 0;
         i < ui->tabWidget->count(); i++)
        ui->tabWidget->setTabEnabled(i, true);

    SHOW_MSG(tr("Successfully retrieved the current point, please save or confirm the configuration."));
    QMetaObject::invokeMethod(
        m_requestRoadPointInstance, "setRoadPoint",
        Qt::DirectConnection,
        Q_ARG(RoadPoint,
              Communication::instance()
                  ->GetRealTimePt()));

    // 恢复原权限
    if (Communication::instance()->isProgramPause()) {
        AuthorityManager::instance()->updateAuthority(Authority::ProjectPause);
    } else {
        AuthorityManager::instance()->updateAuthority();
    }
    // SHOW_MSG(tr("Successfully retrieved the current point, please save or confirm the configuration."));
}

void MainWidget::slot_recvRealTimeEndSpeed(double endSpeed)
{
    m_endSpeed = endSpeed;
}

void MainWidget::setRobotSpeed(int value)
{
    qDebug() << "MainWidget::on_hSlider_speed_valueChanged :" << value;
    if (Communication::instance()->isConnected()) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType::CmdType_Control_SetSpeed, value);
    }
}

void MainWidget::slot_speedReducingTriggerdChanged(bool enable)
{
    if (!m_bSliderAuthorityEnable) {
        ui->hSlider_speed->setEnabled(false);
        ui->edit_robotspeed->setEnabled(false);
        return;
    }
    ui->hSlider_speed->setEnabled(!enable);
    ui->edit_robotspeed->setEnabled(!enable);
}

void MainWidget::slot_generalmatch_getinfo(
    QObject *object, bool bSuccess, const CobotGeneralMatchInfo &info)
{
    if (object != this) return;

    if (!bSuccess) return;

    if (!info.generalOpen) return;

    QString directionInfo = tr("sync model params in manipulator to controller");
    if (info.direction == 1) {
        directionInfo = tr("sync model params in controller to manipulator");
    } else if (info.direction == 2) {
        directionInfo = tr("selected directly by user");
    }

    m_generalMatchDirect = info.direction;
    QString sBodyRobotName = QString("\r\n") + tr("Model saved in manipulator:") + splitMergeName(Communication::instance()->getBodyRobotName());
    QString sControllerRobotName = QString("\r\n") + tr("Model saved in controller:") + splitMergeName(Communication::instance()->getControllerRobotName());

    if (m_robotBodyPowerState != ROBOT_BODY_POWER_ON && (info.matchState == 2 || info.matchState == 8)) {
        MessageBox::information(tr("Universality failed as the manipulator is not powered on. Please power on the manipulator first."));
        return;
    }

    switch (info.matchState){
    // switch (2){
        case 0:  {
            PRINT_MSG(tr("Checking parameters..."));
            break;
        }
        case 2:  {
            QString tipInfo = tr("The model parameters in the manipulator do not match those in the controller.");
            QString sMessboxTip = QString(tr("%1, whether to %2?").arg(tipInfo, directionInfo));
            if (info.direction == 1) {
            // if (true) {
                tipInfo = tr("No parameters in the manipulator");
                sMessboxTip = QString(tr("%1, whether to %2? %3").arg(tipInfo, directionInfo, sControllerRobotName));
            }
            if (MessageBox::question(sMessboxTip) != QMessageBox::Yes) {
                break;
            }
            startGeneralMatchSync(info.factoryFlag);
            break;
        }
        case 3:  {
            PRINT_MSG(tr("The universality function requires that the remote software version be at least 1.0.14."));
            break;
        }
        case 4:  {
            MessageBox::information(tr("The controller power does not match the manipulator**s load. Please replace the controller or the manipulator."));
            break;
        }
        case 7:  {
            MessageBox::information(tr("The controller software is incompatible with the manipulator parameters. Please disable the universality function or upgrade the software."));
            break;
        }
        case 8:  {
            QString tipInfo = tr("The model in the manipulator does not match the model in the controller");
            QString sMessboxTip = QString(tr("%1, whether to %2?%3%4").arg(tipInfo, directionInfo, sBodyRobotName, sControllerRobotName));
            if (MessageBox::question(sMessboxTip) != QMessageBox::Yes) {
                break;
            }
            startGeneralMatchSync(info.factoryFlag);
            break;
        }
        case 9:  {
            PRINT_MSG(tr("The controller has been refrshed, statring syncing parameters to the manipulator."));
            startGeneralMatchSync(info.factoryFlag);
            break;
        }
        default: {
            PRINT_MSG(tr("The controller and manipulator parameters are matched."));
            break;
        }
        }
}

void MainWidget::slot_generalmatch_getparamsyncstatus(QObject *object, bool bSuccess, bool bTimeout)
{
    if (object != this) return;

    DialogContainerForm::instance()->processRobotEventInfo(
        RobotEventInfo(RobotEventInfo::UserEvent_GeneralMatchSyncFinished));

    if (bSuccess) {
        if (bTimeout) {
            MessageBox::information(tr("Model parameter sync timeout. Contact manufacturer support."));
            return;
        }

        if (m_generalMatchDirect == 1) {
            MessageBox::information(tr("Parameters synced successfully."));
        } else {
            MessageBox::information(tr("Parameters synced successfully, please restart the controller."));
        }
    } else {
        MessageBox::information(tr("Parameter sync failed."));
    }
}

void MainWidget::slot_handleProject_result(
    QObject *object, const AbstractCmd::CmdType type, const QVariant &value,
    bool isSuccess, const QString &errMsg)
{
    if (this != object) {
        return;
    }

    if (!isSuccess) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 0);

        if (!errMsg.isEmpty()) {
            if (isVisible()) {
                MessageBox::information(errMsg);
            } else {
                PRINT_WARN(errMsg);
            }
        }

        return;
    }

    switch (type) {
    case AbstractCmd::CmdType_AddJointPoint:
        PRINT_MSG(tr("Points successfully recorded during hand-guiding teaching and saved in file JP.pts."));
        break;
    case AbstractCmd::CmdType_AddRobotPoint: {
        QString sFileName = Communication::instance()->curRPointFile();
        PRINT_MSG(tr("Points successfully recorded during hand-guiding teaching and saved in file %1.").arg(sFileName));
    }
    break;
    default:
        break;
    }

    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 1);
}

void MainWidget::slot_tragteach_autorecordpos(InoPosType type, const RoadPoint &pt)
{
    Q_UNUSED(pt)

    if (m_robotBodyPowerState != ROBOT_BODY_POWER_ON) {
        SHOW_MSG(tr("Failed to record points during hand-guiding teaching as the manipulator is not powered on."));
        return;
    }

    if (Communication::instance()->GetCurDeviceMode() == MetaType::RobotDeviceMode_Auto) {
        SHOW_MSG(tr("current is auto mode, drag teach auto record point failed."));
        return;
    }

    if (!Communication::instance()->IsEnable()) {
        SHOW_MSG(tr("Failed to record points during hand-guiding teaching as the controller is not enabled."));
        return;
    }

    if (AuthorityManager::instance()->isUsingUserAuthority()) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 0);
        SHOW_MSG(tr("Failed to record points during hand-guiding teaching as it is not allowed to record points under user permission."));
        return;
    };

    bool isPDetailShow = Instance::common()->property("isPDetailShow").value<bool>();
    bool isJPDetailShow = Instance::common()->property("isJPDetailShow").value<bool>();

    if (isJPDetailShow) {
        QMetaObject::invokeMethod(Instance::pointFileForm(), "addDragPoint",
                                  Qt::DirectConnection, Q_ARG(const QString &, "JP"));
        return;
    }

    if (isPDetailShow) {
        QMetaObject::invokeMethod(Instance::pointFileForm(), "addDragPoint",
                                  Qt::DirectConnection, Q_ARG(const QString &, "P"));
        return;
    }

    int tabIdx = ui->tabWidget->currentIndex();
    if (ui->tabWidget->tabText(tabIdx).compare(tr("Programming")) != 0) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 0);
        SHOW_MSG(tr("Auto point recording failed, please open the programming page first."));
        return;
    };

    int ptFileCount = 0;
    QMetaObject::invokeMethod(Instance::educationContainerForm(),
                              "getPtFileCount",
                              Qt::DirectConnection, Q_RETURN_ARG(int, ptFileCount));

    if (ptFileCount > 2) {
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_DragTeach_AutoRecordPointResult, 0);
        SHOW_MSG(tr("Automatic point recording failed. Please open the point file before getting the point."));
        return;
    } else {
        QMetaObject::invokeMethod(Instance::pointFileForm(), "showDetailPointList",
                                  Qt::DirectConnection, Q_ARG(const QString &, "P"));
    }
}

void MainWidget::slot_getfirstbootstatus_result(QObject *obj, bool bSuccess, bool status)
{
    if (obj != this || !bSuccess) return;
    if (status) {
        MessageBox::information(tr("this is first time start after doing system upgrade operatiion, please set the absolute zero position first.") + "\n" +
                                tr("safety monitor would open automaticly after setting absolute zero position."));
    }
}

void MainWidget::on_pbn_zeroPose_pressed()
{
    m_bStepModeClose = false;

    CommunicationEngine::instance()
        ->enqueueCmd(this, AbstractCmd::CmdType_Control_JointMoveZeroStart);
}

void MainWidget::on_pbn_initPose_pressed()
{
    // emit CommunicationEngine::instance()->signal_tragteach_autorecordpos(InoPosType_JP, RoadPoint());
    // static int count = 0;
    // ++count;
    // if (count % 2 == 0) {
    //     emit CommunicationEngine::instance()->signal_robotBodyPowerStateChanged(ROBOT_BODY_POWER_ON);
    // } else {
    //     emit CommunicationEngine::instance()->signal_robotBodyPowerStateChanged(ROBOT_BODY_POWER_OFF);
    // }

    m_bStepModeClose = false;

    qDebug() << "******* on_pbn_initPose_pressed *********";

    CommunicationEngine::instance()
        ->enqueueCmd(this, AbstractCmd::CmdType_RobotMoveJointToInitPosture);

    // 临时使用
    // RoadPoint rp;
    // double joints[ROBOT_DOF]
    //     = {0.000000, -7.291862, 75.694714, 21.596727, -90.000000, 0.000000};
    // rp.setJointAngle(joints, ROBOT_DOF);
    // CommunicationEngine::instance()
    //     ->enqueueCmd_robotMoveJointTeach(this, rp);
}

void MainWidget::slot_enableEdit(bool enabled)
{
    setCurrentTab(TAB_TEACH_INDEX);

    ui->bottomWidget->setEnabled(enabled);

    if (!enabled) {
        setCurrentTab("Programming");
    }
}

void MainWidget::slot_controllerConnectionStatusChanged(
    ControllerConnectionState status)
{
    if (ControllerConnectionState_Connected == status) {
        ui->pbn_connectstatus->setIcon(
            QIcon(":/mainwidget/image/mainwidget/connected.svg"));
        ui->pbn_connectstatus->setText(tr("Connected"));
        ui->pbn_connectstatus->setChecked(true);

        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_ConnectFinish));

        QTimer::singleShot(500, [this](){
            const QString verName = QString::fromStdString(
                Communication::instance()->getRcVersionName()).trimmed();
            const QRegularExpression versionPattern(
                QStringLiteral("V(\\d+)R(\\d+)"),
                QRegularExpression::CaseInsensitiveOption);
            const QRegularExpressionMatch versionMatch
                = versionPattern.match(verName);

            if (!versionMatch.hasMatch()) {
                qWarning() << "Cannot parse controller version:" << verName;
            } else {
                const int V = versionMatch.captured(1).toInt();
                const int R = versionMatch.captured(2).toInt();
                qInfo() << "Controller version:" << verName
                        << "parsed V" << V << "R" << R
                        << "minimum supported: V4R26";

                if (V == 4 && R < 26) {
                // 控制版本低于26，则断连
                    MessageBox::warning(
                        tr("The version of the teaching pendant does not match that of the controller. Please upgrade the controller")
                        + QStringLiteral("\nController: %1\nMinimum: V4R26")
                              .arg(verName));
                    if (Communication::instance()->isConnected()) {
                        CommunicationEngine::instance()->enqueueCmd(
                            this, AbstractCmd::CmdType_DisconnectController);
                    }

                    return;
                }
            }

            CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_GetDragTeach_Status);

            CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_Control_GetFirstBootStatus);

            CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_GetControlAuthority);
        });

    } else {
        ui->pbn_connectstatus->setIcon(
            QIcon(":/mainwidget/image/mainwidget/disconnected.svg"));
        ui->pbn_connectstatus->setText(tr("Disconnected"));
        ui->pbn_dragteach->setVisible(false);
        setAlarmChecked(ControllerState_STANDBY);
        ui->pbn_connectstatus->setChecked(false);

        UpdateDeviceModeStatus(MetaType::RobotDeviceMode_Manual_Low);

        if (ControllerConnectionState_Closed == status) {
            DialogContainerForm::instance()->processRobotEventInfo(
                RobotEventInfo(RobotEventInfo::UserEvent_DisconnectFinish));
        }

        if (ui->pbn_cancel->isVisible()) {
            on_pbn_cancel_clicked();
        }
    }
}

void MainWidget::slot_clearAlarmInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to clear alarm."));
    }
}

void MainWidget::slot_enableRobotInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to enable robot."));
        ui->pbn_enable->SetStatus(false);
    }
}

void MainWidget::slot_setEmergecyInterface_result(QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to set emergency stop status."));

        DialogContainerForm::instance()
            ->processRobotEventInfo(RobotEventInfo(RobotEventInfo::UserEvent_Error,
                                                   tr("Failed to set emergency stop status.")));
    }
}

void MainWidget::slot_enableStateChanged(bool enable)
{
    ui->pbn_enable->SetStatus(enable);
}

void MainWidget::slot_emergecyStateChanged(bool enable)
{
    QIcon icon;

    QSize tempSize = ResolutionUtils::getRatioSize(QSize(40, 40));

    ui->pbn_emergeStop->setChecked(enable);
    if (enable) {
        icon.addFile(":/mainwidget/image/mainwidget/emergestopon.svg", tempSize, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopondisabled.svg", tempSize, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopon.svg", tempSize, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopondisabled.svg", tempSize, QIcon::Disabled, QIcon::Off);

        PRINT_MSG(tr("Emergency stop pressed."));
    } else {
        icon.addFile(":/mainwidget/image/mainwidget/emergestopoff.svg", tempSize, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopoffdisabled.svg", tempSize, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopoff.svg", tempSize, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/emergestopoffdisabled.svg", tempSize, QIcon::Disabled, QIcon::Off);
        PRINT_MSG(tr("Emergency stop released."));
    }
    ui->pbn_emergeStop->setIcon(icon);
    ui->pbn_emergeStop->setIconSize(tempSize);
}

void MainWidget::slot_tragteach_status(bool bDragging)
{
    if (!Communication::instance()->isConnected()) return;

    if (bDragging) {
        SHOW_MSG(tr("Entered hand-guiding teaching mode."));
        ui->pbn_dragteach->setVisible(true);
        slot_controllerAuthorityChanged(InoCtrlAuthority_TeachPad);
        AuthorityManager::instance()->updateAuthority(Authority::DragTeaching);
    } else {
        if (!ui->pbn_dragteach->isVisible()) {
            return;
        }

        SHOW_MSG(tr("Exited hand-guiding teaching mode."));
        ui->pbn_dragteach->setVisible(false);

        AuthorityManager::instance()->updateAuthority();
    }
}

void MainWidget::slot_controllerStateChanged(ControllerState state)
{
    setAlarmChecked(state);
}

void MainWidget::showMainWidget()
{
    WindowManager::instance()->enqueueCmdInfo(WindowCmd_MainWidgetShow);
    LOG_INFO("~~MainWidget show");

    QMetaObject::invokeMethod(
        Instance::application(), "updateLockScreenTime",
        Qt::DirectConnection);

    QMetaObject::invokeMethod(
        Instance::displayForm(), "setEnableLineNumber", Qt::DirectConnection);
}

void MainWidget::setCurrentTab(int tabPage)
{
    ui->tabWidget->setCurrentIndex(tabPage);
}

void MainWidget::setCurrentTab(const QString &tabText)
{
    int index = getTabIndexByText(tabText);
    setCurrentTab(index);
}

void MainWidget::setSpeedEnable(bool bEnable)
{
    ui->hSlider_speed->setEnabled(bEnable);
    ui->edit_robotspeed->setEnabled(bEnable);
}

int MainWidget::getTabIndexByText(const QString &tabText)
{
    for (auto it = m_hashTabIndexAndWidget.begin();
         it != m_hashTabIndexAndWidget.end(); ++it) {
        QPair<QWidget *, QString> pWidget = it.value();
        if (pWidget.second.compare(tabText) == 0) {
            return it.key();
        }
    }
    return -1;
}

int MainWidget::getTabIndexByWidget(QWidget *pWidget)
{
    for (auto it = m_hashTabIndexAndWidget.begin();
         it != m_hashTabIndexAndWidget.end(); ++it) {
        QPair<QWidget *, QString> pairValue = it.value();
        if (pairValue.first == pWidget) {
            return it.key();
        }
    }
    return -1;
}

void MainWidget::checkAppRunBackground()
{
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    activity.callMethod<void>("registWifiListenerCb");

    jboolean retObj = activity.callMethod<jboolean>("isIgnoringBatteryOptimizations");
    if (!static_cast<bool>(retObj)) {
        if (MessageBox::question(tr("Allow InoCobotTP to run in the background?")) == QMessageBox::Yes) {
            activity.callMethod<void>("requestIgnoreBatteryOptimizations");
        }
    }

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

bool MainWidget::checkAllFilesAccessPermission()
{
    bool ret = true;
#ifdef Q_OS_ANDROID
    QJniEnvironment env;
    ret = QJniObject::callStaticMethod<jboolean>(
        "android/os/Environment",
        "isExternalStorageManager",
        "()Z"
        );
    if (env.checkAndClearExceptions()) {
        LOG_INFO("Permission check failed, defaulting to false");
        return false;
    }

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif

    return ret;
}

void MainWidget::requestAllFilesAccessPermission()
{
#ifdef Q_OS_ANDROID
    QJniEnvironment env;
    // [1] 获取上下文
    QJniObject context = QNativeInterface::QAndroidApplication::context();
    if (!context.isValid()) {
        LOG_INFO("Invalid Android context!");
        return;
    }

    // [2] 获取包名
    QJniObject packageName = context.callObjectMethod("getPackageName", "()Ljava/lang/String;");
    if (env.checkAndClearExceptions()) {
        LOG_INFO("Failed to get package name!");
        return;
    }

    // [3] 构建 URI
    QJniObject uriString = QJniObject::fromString("package:" + packageName.toString());
    QJniObject uri = QJniObject::callStaticObjectMethod(
        "android/net/Uri",
        "parse",
        "(Ljava/lang/String;)Landroid/net/Uri;",
        uriString.object()
        );
    if (env.checkAndClearExceptions() || !uri.isValid()) {
        LOG_INFO("URI parsing failed!");
        return;
    }

    // [4] 创建 Intent
    QJniObject action = QJniObject::getStaticObjectField(
        "android/provider/Settings",
        "ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION",
        "Ljava/lang/String;"
        );
    QJniObject intent("android/content/Intent", "(Ljava/lang/String;)V", action.object());
    if (env.checkAndClearExceptions() || !intent.isValid()) {
        LOG_INFO("Intent creation failed!");
        return;
    }

    // [5] 设置 Data
    intent.callObjectMethod("setData",
                            "(Landroid/net/Uri;)Landroid/content/Intent;",
                            uri.object());
    if (env.checkAndClearExceptions()) {
        LOG_INFO("Failed to set intent data!");
        return;
    }

    // [6] 启动 Activity
    context.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", intent.object());
    if (env.checkAndClearExceptions()) {
        LOG_INFO("Failed to start activity!");
    }

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

void MainWidget::changeEvent(QEvent *event)
{
    AbstractWidget::changeEvent(event);
}

void MainWidget::showEvent(QShowEvent *event)
{
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectControllerInterface_result,
            this, &MainWidget::slot_connectControllerInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_disconnectControllerInterface_result,
            this, &MainWidget::slot_disconnectControllerInterface_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_handleProject_result,
            this, &MainWidget::slot_handleProject_result);

    connect(CommunicationEngine::instance(), &CommunicationEngine::signal_tragteach_autorecordpos,
            this, &MainWidget::slot_tragteach_autorecordpos);

    UpdateWifiStatus();
    FlowWidgetManager::instance()->setMainWidgetShow(true);

#ifdef __ANDROID__

    this->setGeometry(0, 0, this->width(), this->height());
    showFullScreen();
#endif
    // updateBottomWidgetHeight();
}

void MainWidget::hideEvent(QHideEvent *event)
{
    disconnect(CommunicationEngine::instance(),
               &CommunicationEngine::signal_connectControllerInterface_result,
               this, &MainWidget::slot_connectControllerInterface_result);
    disconnect(CommunicationEngine::instance(),
               &CommunicationEngine::signal_disconnectControllerInterface_result,
               this, &MainWidget::slot_disconnectControllerInterface_result);

    disconnect(CommunicationEngine::instance(),
               &CommunicationEngine::signal_handleProject_result,
               this, &MainWidget::slot_handleProject_result);

    disconnect(CommunicationEngine::instance(), &CommunicationEngine::signal_tragteach_autorecordpos,
               this, &MainWidget::slot_tragteach_autorecordpos);

    FlowWidgetManager::instance()->setMainWidgetShow(false);
}

void MainWidget::closeEvent(QCloseEvent *closeEvent)
{
#ifndef Q_OS_ANDROID
    if (Instance::common()
            ->property("isCloseDialogContainerForm")
            .value<bool>()) {
        Instance::common()->setProperty("isCloseDialogContainerForm", false);
        closeEvent->ignore();
        return;
    }

    const QMessageBox::StandardButton result = QMessageBox::question(
        this, QString(), tr("Are you sure you want to exit the app?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (result == QMessageBox::Yes) {
        closeEvent->accept();
        // Queue quit so it is handled by the main application event loop
        // after this close event and the confirmation dialog have returned.
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
    } else {
        closeEvent->ignore();
    }
#else
    closeEvent->accept();
#endif
}

void MainWidget::resizeEvent(QResizeEvent* ev)
{
    if(!ui->lbl_logo->m_isMove)
        AbstractWidgetBase::resizeEvent(ev);
}

void MainWidget::moveEvent(QMoveEvent *event)
{
    Common::instance()->setProperty("actualAppX", this->x());
    Common::instance()->setProperty("actualAppY", this->y());
    if(m_logForm->isVisible())
        on_pbn_showLogFlowForm_clicked();
    FlowWidgetManager::instance()->updateGeometry();
}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease && watched == ui->hSlider_speed) {
        if (!ui->hSlider_speed->isEnabled()) {
            return true;
        }
        QMouseEvent *evt = static_cast<QMouseEvent *>(event);
        int value = QStyle::sliderValueFromPosition(ui->hSlider_speed->minimum(), ui->hSlider_speed->maximum(), evt->pos().x(), ui->hSlider_speed->width());
        setRobotSpeed(value);
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void MainWidget::slot_connectSuccess()
{
    MetaType::RobotDeviceMode mode
        = Communication::instance()->GetCurDeviceMode();
    UpdateDeviceModeStatus(mode);

    AuthorityManager::instance()->updateAuthority();

    // 通配判定
    CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_GeneralMatch_GetInfo);
}

void MainWidget::slot_robotShutdownInterface_result(QObject *object)
{
    if (this == object)
        dynamic_cast<QThread *>(Instance::shutdownThread())->start();
}

void MainWidget::on_pbn_switchAuthority_clicked()
{
    DialogContainerForm::instance()->showDialog(
        DialogContainerForm::DialogStackForm_CurrentAuthorityForm);
}

void MainWidget::extensionsInitialized()
{
    ui->tabWidget->clear();

    for (auto it = m_hashTabIndexAndWidget.begin();
         it != m_hashTabIndexAndWidget.end(); it++) {
        QPair<QWidget *, QString> pair = it.value();
        ui->tabWidget->addTab(pair.first,
                              QIcon(m_hashTabIndexAndIcon.value(it.key())),
                              pair.second);
    }
    setCurrentTab(TAB_TEACH_INDEX);

    for (auto it = m_mapWidgetEnable.begin(); it != m_mapWidgetEnable.end();
         ++it) {
        ui->tabWidget->widget(it.key())->setEnabled(it.value());
    }
#if PluginLib_Core_AdminAuthority_Enabled == 1
    ui->pbn_minimize->setVisible(false);
    ui->lbl_line->setVisible(false);
    ui->pbn_wifi->setVisible(false);
    ui->pbn_controllerAuthority->setVisible(false);
    ui->pbn_connectstatus->setVisible(false);
    ui->pbn_switchAuthority->setVisible(false);
    ui->pbn_mode->setVisible(false);
    ui->pbn_robotpower->setVisible(false);
    ui->pbn_enable->setVisible(false);
    ui->pbn_clearAlarm->setVisible(false);
    ui->pbn_emergeStop->setVisible(false);

    ui->pbn_zeroPose->setVisible(false);
    ui->pbn_initPose->setVisible(false);
    ui->lbl_time->setVisible(false);
    ui->pbn_showLogFlowForm->setVisible(false);
    ui->lbl_speed->setVisible(false);
    ui->hSlider_speed->setVisible(false);
    ui->edit_robotspeed->setVisible(false);
    ui->pbn_cancel->setVisible(false);
    ui->pbn_setRoadPoint->setVisible(false);

    AuthorityManager::instance()->updateAuthority(Authority::FactoryAccess);

    DatabaseLocal::setLanguage("zh_CN");
    QMetaObject::invokeMethod(
        Instance::common(), "loadTranslator", Qt::DirectConnection);
    QMetaObject::invokeMethod(
        Instance::common(), "loadTranslator", Qt::DirectConnection);

#endif

    qDebug() << "******************** Path Print *************************";
    qDebug() << "ABSOLUTE_SHARE_PATH:" << ABSOLUTE_SHARE_PATH;
    qDebug() << "ABSOLUTE_PLUGIN_SHARE_PATH:" << ABSOLUTE_PLUGIN_SHARE_PATH;
    qDebug() << "APPLICATION_DIR_PATH:" << APPLICATION_DIR_PATH;
    qDebug() << "RELATIVE_SHARE_PATH:" << RELATIVE_SHARE_PATH;
    qDebug() << "RELATIVE_PLUGIN_PATH:" << RELATIVE_PLUGIN_PATH;

    DialogContainerForm::instance()->registDialog(PasswordConfirmForm::instance(), 346, 200);
}

void MainWidget::setTabText(int index, const QString &tabText)
{
    int inIdx = 0;
    for (auto it = m_hashTabIndexAndWidget.begin();
         it != m_hashTabIndexAndWidget.end(); ++it, ++inIdx) {
        if (it.key() == index) break;
    }
    ui->tabWidget->setTabText(inIdx, tabText);
}

void MainWidget::on_pbn_pluginManager_clicked()
{
    PluginEngine::PluginDialog dialog(this);
    dialog.exec();
}

void MainWidget::setBtnLogText(const QString &msg)
{
    QFontMetrics metrics(ui->pbn_showLogFlowForm->font());
    QString temp = msg;
    temp.replace("<br>", " ").replace("\r\n", " ").replace("\n", " ")
        .replace("&lt","<").replace("&gt",">");
    ui->pbn_showLogFlowForm->setText(
        metrics.elidedText(temp,
                           Qt::ElideRight,
                           ui->pbn_showLogFlowForm->rect().width() - 12
                               - ui->pbn_showLogFlowForm->iconSize().width()));
}

void MainWidget::on_pbn_showLogFlowForm_clicked()
{
    m_logForm->show();
    m_logForm->move(x() + width() - m_logForm->width() ,
                    y() + height() - m_logForm->height() - ui->bottomWidget->height() - 1);
}

void MainWidget::UpdateWifiStatus()
{
    WifiStrength wifiStrenth = Communication::instance()->getWifiStrength();
    if (wifiStrenth == WifiStrength_0) {
        ui->pbn_wifi->setIcon(
            QIcon(":/mainwidget/image/mainwidget/wifi_zero.svg"));
    }
    if (wifiStrenth == WifiStrength_1) {
        ui->pbn_wifi->setIcon(
            QIcon(":/mainwidget/image/mainwidget/wifi_one.svg"));
    }
    if (wifiStrenth == WifiStrength_2) {
        ui->pbn_wifi->setIcon(
            QIcon(":/mainwidget/image/mainwidget/wifi_two.svg"));
    }
    if (wifiStrenth == WifiStrength_3) {
        ui->pbn_wifi->setIcon(
            QIcon(":/mainwidget/image/mainwidget/wifi_three.svg"));
    }
    if (wifiStrenth == WifiStrength_4) {
        ui->pbn_wifi->setIcon(
            QIcon(":/mainwidget/image/mainwidget/wifi_full.svg"));
    }
}

void MainWidget::UpdateWifiOnSSidUnknow()
{
    ui->pbn_wifi->setIcon(
        QIcon(":/mainwidget/image/mainwidget/wifi_zero.png"));
}

void MainWidget::SetHeartBeat(bool bSwitch)
{
    CommunicationEngine::instance()->enqueueCmd_setData(this,
                                                        AbstractCmd::CmdType_Connection_SetHeatBeat,
                                                        bSwitch);
}

void MainWidget::SafetyExit()
{
    if (Communication::instance()->isConnected()) {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_DisconnectController);
    }

    qApp->quit();
}

void MainWidget::UpdateDeviceModeStatus(MetaType::RobotDeviceMode mode)
{
    QSize temp = TitleIconSize;
    if (mode == MetaType::RobotDeviceMode_Auto) {
        QIcon autoIcon;
        autoIcon.addFile(":/mainwidget/image/mainwidget/auto.svg", temp, QIcon::Normal, QIcon::On);
        autoIcon.addFile(":/mainwidget/image/mainwidget/auto_disabled.svg", temp, QIcon::Disabled, QIcon::On);
        autoIcon.addFile(":/mainwidget/image/mainwidget/auto.svg", temp, QIcon::Normal, QIcon::Off);
        autoIcon.addFile(":/mainwidget/image/mainwidget/auto_disabled.svg", temp, QIcon::Disabled, QIcon::Off);
        ui->pbn_mode->setIcon(autoIcon);
        ui->pbn_mode->setText(tr("Auto"));
    }
    if (mode == MetaType::RobotDeviceMode_Manual_Low) {
        QIcon manuallowIcon;
        manuallowIcon.addFile(":/mainwidget/image/mainwidget/manuallow.svg", temp, QIcon::Normal, QIcon::On);
        manuallowIcon.addFile(":/mainwidget/image/mainwidget/manuallow_disabled.svg", temp, QIcon::Disabled, QIcon::On);
        manuallowIcon.addFile(":/mainwidget/image/mainwidget/manuallow.svg", temp, QIcon::Normal, QIcon::Off);
        manuallowIcon.addFile(":/mainwidget/image/mainwidget/manuallow_disabled.svg", temp, QIcon::Disabled, QIcon::Off);
        ui->pbn_mode->setIcon(manuallowIcon);
        ui->pbn_mode->setText(tr("Manual Low"));
    }
    if (mode == MetaType::RobotDeviceMode_Manual_High) {
        QIcon icon;
        icon.addFile(":/mainwidget/image/mainwidget/manualhigh.svg", temp, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/manualhigh_disabled.svg", temp, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/manualhigh.svg", temp, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/manualhigh_disabled.svg", temp, QIcon::Disabled, QIcon::Off);
        ui->pbn_mode->setIcon(icon);
        ui->pbn_mode->setText(tr("Manual High"));
    }
}

void MainWidget::slot_pbn_enable_clicked(bool checked)
{
    QString state;
    // 机械锁定没开且本地未上电的情况下不能上使能
    if (m_robotBodyPowerState != ROBOT_BODY_POWER_ON && !Communication::instance()->isMechLocked()) {
        PRINT_MSG(tr("Robot powered off"));
        state = QObject::tr("Enable") + " -> " + QObject::tr("Clicked");
        CobotLog::instance()->printOperation(state);
        return;
    }

#if PluginLib_Core_BlockSafeMonitor_DOF7_Enabled == 1
    // 安全监控未打开的情况下不能上使能
    if (!Communication::instance()->isMechLocked() &&
        !Communication::instance()->getSafetyMonitorStatus()) {
        PRINT_MSG(tr("Safety Monitor Is Not On, Please Open The Monitor First"));
        return;
    }
#endif

    // 打印输出
    if (checked) {
        PRINT_MSG(tr("Controller enabled"));
        state = QObject::tr("Enable") + " -> " + QObject::tr("ON");
    } else {
        PRINT_MSG(tr("Controller disabled"));
        state = QObject::tr("Enable") + " -> " + QObject::tr("OFF");
    }
    CobotLog::instance()->printOperation(state);
    CommunicationEngine::instance()->enqueueCmd_enableRobot(this, checked);
}

void MainWidget::on_pbn_clearAlarm_clicked(bool checked)
{
    ui->pbn_clearAlarm->setChecked(!checked);
    if (checked) {
        PRINT_MSG(tr("Clear alarm"));
    }
    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType_ClearAlarm);
}

void MainWidget::setAlarmChecked(ControllerState state)
{
    QSize tempSize = TitleIconSize;
    switch (state) {
    case ControllerState_WARN: {
        QIcon icon;
        icon.addFile(":/mainwidget/image/mainwidget/lightwarnoccur.svg", tempSize, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/lightwarnoccur.svg", tempSize, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/lightwarnoccur_disabled.svg", tempSize, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/lightwarnoccur_disabled.svg", tempSize, QIcon::Disabled, QIcon::Off);
        ui->pbn_clearAlarm->setIcon(icon);
        ui->pbn_clearAlarm->setText(tr("Warning"));
        ui->pbn_clearAlarm->setChecked(false);
    } break;
    case ControllerState_ERR:
    case ControllerState_ESTOP: {
        QIcon icon;
        icon.addFile(":/mainwidget/image/mainwidget/warnoccur.svg", tempSize, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/warnoccur.svg", tempSize, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/warnoccur_disabled.svg", tempSize, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/warnoccur_disabled.svg", tempSize, QIcon::Disabled, QIcon::Off);
        ui->pbn_clearAlarm->setIcon(icon);
        ui->pbn_clearAlarm->setText(tr("Error"));
        ui->pbn_clearAlarm->setChecked(false);
    } break;
    case ControllerState_STANDBY:
    case ControllerState_ENABLE: {
        QIcon icon;
        icon.addFile(":/mainwidget/image/mainwidget/nowarn.svg", tempSize, QIcon::Normal, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/nowarn.svg", tempSize, QIcon::Normal, QIcon::Off);
        icon.addFile(":/mainwidget/image/mainwidget/nowarn_disabled.svg", tempSize, QIcon::Disabled, QIcon::On);
        icon.addFile(":/mainwidget/image/mainwidget/nowarn_disabled.svg", tempSize, QIcon::Disabled, QIcon::Off);
        ui->pbn_clearAlarm->setIcon(icon);
        ui->pbn_clearAlarm->setText(tr("Normal"));
        ui->pbn_clearAlarm->setChecked(true);
    } break;
    default:
        break;
    }
}

void MainWidget::setTakePointUI(bool bTakePoint)
{
    ui->pbn_cancel->setVisible(bTakePoint);
    ui->pbn_setRoadPoint->setVisible(bTakePoint);
    if (bTakePoint) {
#ifdef __ANDROID__
        // ui->edit_robotspeed->setMinimumWidth(36);
        // ui->edit_robotspeed->setMaximumWidth(36);
        ui->lbl_percent->setMinimumWidth(20);
        ui->lbl_percent->setMaximumWidth(20);
#endif
    } else {
#ifdef __ANDROID__
        // ui->edit_robotspeed->setMinimumWidth(36);
        // ui->edit_robotspeed->setMaximumWidth(36);
        ui->lbl_percent->setMinimumWidth(64);
        ui->lbl_percent->setMaximumWidth(64);
#endif
    }
}

void MainWidget::retranslateTitleBar()
{
    /// 重新翻译模式
    MetaType::RobotDeviceMode mode = Communication::instance()->GetCurDeviceMode();
    UpdateDeviceModeStatus(mode);

    /// 重新翻译连接状态
    ControllerConnectionState connstatus
        = Communication::instance()->isConnected() ?
              ControllerConnectionState_Connected :
              ControllerConnectionState_Closed;
    if (ControllerConnectionState_Connected == connstatus) {
        ui->pbn_connectstatus->setText(tr("Connected"));
    } else {
        ui->pbn_connectstatus->setText(tr("Disconnected"));
        setAlarmChecked(ControllerState_STANDBY);
    }

    /// 重新翻译报警状态
    ControllerState controllerState = Communication::instance()->GetControllerStatus();
    slot_controllerStateChanged(controllerState);

    slot_robotBodyPowerStateChanged(m_robotBodyPowerState);
}

void MainWidget::updateBottomWidgetHeight()
{
#ifdef __ANDROID__
    // showFullScreen();
    // ui->edit_robotspeed->setMinimumWidth(36);
    // ui->edit_robotspeed->setMaximumWidth(36);
    ui->lbl_percent->setMinimumWidth(64);
    ui->lbl_percent->setMaximumWidth(64);
#else
    ui->edit_robotspeed->setMinimumWidth(36);
    ui->edit_robotspeed->setMaximumWidth(36);

    ui->bottomWidget->setMinimumHeight(36);
    ui->bottomWidget->setMaximumHeight(36);

    ui->pbn_initPose->setMaximumHeight(28);
    ui->pbn_initPose->setMinimumHeight(28);

    ui->pbn_zeroPose->setMaximumHeight(28);
    ui->pbn_zeroPose->setMinimumHeight(28);

    ui->pbn_showLogFlowForm->setMaximumHeight(28);
    ui->pbn_showLogFlowForm->setMinimumHeight(28);

    ui->pbn_cancel->setMinimumHeight(28);
    ui->pbn_cancel->setMaximumHeight(28);

    ui->pbn_setRoadPoint->setMinimumHeight(28);
    ui->pbn_setRoadPoint->setMaximumHeight(28);

    ui->hSlider_speed->setMinimumHeight(28);
    ui->hSlider_speed->setMaximumHeight(28);

    ui->contentWidget->setMinimumSize(1280, 720);
    ui->contentWidget->setMaximumSize(1280, 720);

    ui->tabWidget->setMinimumSize(1280, 720);
    ui->tabWidget->setMaximumSize(1280, 720);
    updateGeometry();

#endif
}

void MainWidget::doModeChanged()
{
    MetaType::RobotDeviceMode mode;
    if (Communication::instance()->GetCurDeviceMode() == MetaType::RobotDeviceMode_Auto) {
        mode = MetaType::RobotDeviceMode_Manual_Low;
    } else {
        mode = MetaType::RobotDeviceMode_Auto;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetDeviceMode, mode);
}

void MainWidget::startGeneralMatchSync(int factoryFlag)
{
    if (Communication::instance()->GetCurCtrlAuthority() != InoCtrlAuthority_TeachPad) {
        PRINT_MSG(tr("The control authority is not on the teach pendant."));
        return;
    }

#if PluginLib_Core_DeveloperMode_Enabled == 1
    if (Instance::common()->property("isDeveloperMode").value<bool>()) {
        doGeneralMatchSync();
        return;
    }
#endif

    if (factoryFlag != 1) {
        DialogContainerForm::instance()->showDialog(PasswordConfirmForm::staticMetaObject.className());
        std::string temp = QString(FACTORY_MODE_PASSWD).toStdString();
        PasswordConfirmForm::instance()->setArgs(FUNCID_FACTORY_AUTHORITY,
                                                 tr("ManuFacturer authority"),
                                                 temp.c_str());
    } else {
        doGeneralMatchSync();
    }
}

void MainWidget::doGeneralMatchSync()
{
    int direct = m_generalMatchDirect;
    if (direct != 0 && direct != 1) {
        MessageBox directChooseMsgBox;
        directChooseMsgBox.setWindowTitle(tr("Direction selection"));
        directChooseMsgBox.setText(tr("Please select the sync direction."));

        QPushButton *sync2CtrlPbn = directChooseMsgBox.addButton(tr("Sync to controller"), QMessageBox::AcceptRole);
        QPushButton *sync2BodyPbn = directChooseMsgBox.addButton(tr("Sync to manipulator"), QMessageBox::RejectRole);

        directChooseMsgBox.exec();

        if (directChooseMsgBox.clickedButton() == sync2CtrlPbn) {
            direct = 0;
        } else if (directChooseMsgBox.clickedButton() == sync2BodyPbn) {
            direct = 1;
        }
    }

    // 二次确认
    QString directionInfo = tr("sync model params in manipulator to controller");
    if (direct == 1) {
        directionInfo = tr("sync model params in controller to manipulator");
    }

    QString sMessboxTip = QString(tr("%1 is about to start. Please keep the connection stable during the synchronization process. A disconnection in the middle may cause system abnormalities.").arg(directionInfo));
    if (MessageBox::information(sMessboxTip, QMessageBox::Ok, QMessageBox::Cancel, false) != QMessageBox::Ok) {
        return;
    }

    string dir = "{\"Direction\":}";
    dir.insert(dir.length() - 1, std::to_string(direct));
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType_GeneralMatch_StartRobotParamSync, dir);

    CommunicationEngine::instance()->enqueueCmd_getData(
        this, AbstractCmd::CmdType_GeneralMatch_GetSyncStatus, direct);

    DialogContainerForm::instance()->processRobotEventInfo(
        RobotEventInfo(RobotEventInfo::UserEvent_GeneralMatchSync, "90"));
}

QString MainWidget::splitMergeName(const QString &sName)
{
    if (sName.isEmpty()) return "";

    QString sRet;
    QStringList sNameList = sName.split("-");
    if (sNameList.size() < 3) {
        return sRet;
    }

    sRet += sNameList[0];
    sRet += "-";
    sRet += sNameList[1];
    sRet += "-";
    sRet += sNameList[2];

    return sRet;
}

void MainWidget::on_pbn_mode_clicked()
{
    if (!Communication::instance()->isConnected()) {
        PRINT_MSG(tr("Not connected to controller, operation invalid"));
        return;
    }

    if (!Communication::instance()->isMechLocked() &&
        m_robotBodyPowerState != ROBOT_BODY_POWER_ON &&
        Communication::instance()->GetCurDeviceMode() != MetaType::RobotDeviceMode_Auto) {
        SHOW_MSG(tr("robot body not poweron, switch to automatic mode would cause alarm, please poweron the robot."));
        // return;
    }

#if PluginLib_Core_BlockSafeMonitor_DOF7_Enabled == 1
    if (!Communication::instance()->isMechLocked() &&
        !Communication::instance()->getSafetyMonitorStatus() &&
        Communication::instance()->GetCurDeviceMode() != MetaType::RobotDeviceMode_Auto) {
        SHOW_MSG(tr("Safety Monitor Is Not On, Please Open The Monitor First Then Switch The Mode"));
        return;
    }
#endif

    if (Communication::instance()->GetCurDeviceMode() != MetaType::RobotDeviceMode_Auto
        && !Instance::common()->property("isProjectLoaded").value<bool>()) {
        SHOW_MSG(tr("project is not load, please create or load one project first."));
        return;
    }

#if PluginLib_Core_DeveloperMode_Enabled == 1
    if (Instance::common()->property("isDeveloperMode").value<bool>()) {
        doModeChanged();
        return;
    }
#endif

    if (!Instance::common()->property("isDisplayModePasswd").value<bool>()) {
        doModeChanged();
        return;
    }

    DialogContainerForm::instance()->showDialog(PasswordConfirmForm::staticMetaObject.className());
    PasswordConfirmForm::instance()->setArgs(FUNCID_MODECHANGED, tr("Switch mode"));
}

void MainWidget::getVirtualKeyBoardBottomRight(int &x, int &y)
{
    x = this->width();
    // y = ui->bottomWidget->y();
    y = this->height();
}

void MainWidget::on_pbn_wifi_clicked()
{
#ifdef Q_OS_ANDROID
    QJniEnvironment env;

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    activity.callMethod<void>("openSystemWifi");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

void MainWidget::slot_setspeed_result(bool isSuccess, int speed)
{
    if (!isSuccess) {
        qDebug() << "speed set failed.";
    } else {
        ui->edit_robotspeed->setText(QString::number(speed));
        ui->hSlider_speed->setValue(speed);
    }
}

void MainWidget::on_pbn_emergeStop_clicked(bool checked)
{
    if (Communication::instance()->GetCurCtrlAuthority() == InoCtrlAuthority_IO) {
        if (checked) {
            CommunicationEngine::instance()->enqueueCmd_setEmergecy(this, checked);
        } else {
            ui->pbn_emergeStop->setChecked(!checked);
            MessageBox::warning(tr("It is not allowed to release the emergency stop in remote IO mode."));
            return;
        }
    }
    else if(Communication::instance()->GetCurCtrlAuthority() == InoCtrlAuthority_IO_AUTO){
        if (checked) {
            CommunicationEngine::instance()->enqueueCmd_setEmergecy(this, checked);
        } else {
            if (Communication::instance()->GetCurDeviceMode() == MetaType::RobotDeviceMode_Auto) {
                ui->pbn_emergeStop->setChecked(!checked);
                MessageBox::warning(tr("It is not allowed to release the emergency stop in remote IO auto mode."));
                return;
            }
            else{
                CommunicationEngine::instance()->enqueueCmd_setEmergecy(this, checked);
            }
        }
    }
    else{
        CommunicationEngine::instance()->enqueueCmd_setEmergecy(this, checked);
    }
}

void MainWidget::on_pbn_connectstatus_clicked(bool checked)
{
    QString sIp;
    QMetaObject::invokeMethod(
        Instance::connectControllerForm(), "getIP",
        Qt::DirectConnection,
        Q_RETURN_ARG(QString, sIp));
    int port = Communication::instance()->getPort();
    if (!Communication::instance()->isConnected()) {
        DialogContainerForm::instance()->showDialog(
            DialogContainerForm::DialogStackForm_ConnectControllerForm);
    } else {
        if (MessageBox::question(tr("Are you sure you want to disconnect from the controller?")) == QMessageBox::Yes) {
            CommunicationEngine::instance()->enqueueCmd(
                this, AbstractCmd::CmdType_DisconnectController);
            DialogContainerForm::instance()->processRobotEventInfo(
                RobotEventInfo(RobotEventInfo::UserEvent_DisconnectController));
        } else {
            ui->pbn_connectstatus->setChecked(!checked);
        }
    }
}

void MainWidget::on_pbn_poweroff_clicked()
{
    // Custom MessageBox may only log to the info flow without a real modal dialog
    // (user sees "确定退出应用?" in the status bar but cannot answer Yes/No).
    // Reuse closeEvent so both exit controls share one graceful shutdown path.
    close();
}

void MainWidget::slot_setdevicemode_result(
    bool isSuccess, MetaType::RobotDeviceMode mode)
{
    if (!isSuccess) {
        MessageBox::warning(tr("Failed to set run mode."));
        return;
    }
}

void MainWidget::slot_passwd_confirm_result(const QString &sFuncId, bool isCorrect)
{
    if (sFuncId.compare(FUNCID_MODECHANGED) != 0 && sFuncId.compare(FUNCID_FACTORY_AUTHORITY) != 0) {
        return;
    }
    qDebug() << "MainWidget::slot_passwd_confirm_result : " << isCorrect;
    if (!isCorrect) {
        DialogContainerForm::instance()->hideDialog(PasswordConfirmForm::staticMetaObject.className());
        return;
    }

    if (sFuncId.compare(FUNCID_MODECHANGED) == 0) {
        doModeChanged();
    } else {
        doGeneralMatchSync();
    }

    DialogContainerForm::instance()->hideDialog(PasswordConfirmForm::staticMetaObject.className());
}

void MainWidget::slot_connectControllerInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        ui->pbn_connectstatus->setChecked(false);
        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_Error, tr("Failed to connect to the controller.")));
    }
}

void MainWidget::slot_disconnectControllerInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        ui->pbn_connectstatus->setChecked(true);
        DialogContainerForm::instance()->processRobotEventInfo(
            RobotEventInfo(RobotEventInfo::UserEvent_Error, tr("Failed to disconnect from the controller.")));
    }
}

void MainWidget::slot_speed_changed(quint16 speed)
{
    ui->edit_robotspeed->setText(QString::number(speed));
    ui->hSlider_speed->setValue(speed);
}

void MainWidget::on_pbn_robotpower_clicked()
{
    InoCoRobotBodyPowerState state;
    if(m_robotBodyPowerState ==ROBOT_BODY_POWER_OFF_IN_PROCESS){
        MessageBox::warning(tr("The manipulator power is being turned off. Please try again later."));
        return;
    }else if (m_robotBodyPowerState == ROBOT_BODY_POWER_ON || m_robotBodyPowerState == ROBOT_BODY_POWER_OFF) {
        if (ui->pbn_enable->GetStatus()) {
            MessageBox::warning(tr("Not allowed to set the manipulator to power off status when the controller is enabled."));
            return;
        } else if (Communication::instance()->isMechLocked()) {
            MessageBox::warning(tr("Not allowed to set the power status of the manipulator when in the mechanical lock status."));
            return;
        }
    }
    if (m_robotBodyPowerState == ROBOT_BODY_POWER_ON){
        if (MessageBox::_question(tr("Are you sure you want to power off the robot?"))) {
            state = ROBOT_BODY_POWER_OFF;
        } else {
            return;
        }
    } else if (m_robotBodyPowerState == ROBOT_BODY_POWER_OFF) {
        if (MessageBox::_question(tr("Are you sure you want to power on the manipulator?"))) {
            state = ROBOT_BODY_POWER_ON;
        } else {
            return;
        }
    } else
        return;

    CommunicationEngine::instance()->enqueueCmd_setData(this, AbstractCmd::CmdType_SetRobotBodyPowerState, state);
}

void MainWidget::slot_robotBodyPowerStateChanged(InoCoRobotBodyPowerState state)
{
    QSize tempSize = TitleIconSize;
    m_robotBodyPowerState = state;
    QString svgName = "";
    QString btnText = "";
    switch (state) {
    case ROBOT_BODY_POWERING_ON_IN_PROCESS:
        svgName = "robotbodypoweringon.svg";
        btnText = tr("Robot powering on");
        break;
    case ROBOT_BODY_POWER_OFF_IN_PROCESS:
        svgName = "robotbodypoweringoff.svg";
        btnText = tr("Robot powering off");
        break;
    case ROBOT_BODY_POWER_ON:
        svgName = "robotbodypoweron.svg";
        btnText = tr("Robot powered on");
        break;
    case ROBOT_BODY_POWER_DISENABLE:
    case ROBOT_BODY_POWER_OFF:
    case ROBOT_BODY_DISCONNECTED_STATE:
    default:
        svgName = "robotbodypoweroff.svg";
        btnText = tr("Robot powered off");
        break;
    }
    QIcon icon;
    icon.addFile(":/mainwidget/image/mainwidget/" + svgName, tempSize, QIcon::Normal, QIcon::On);
    icon.addFile(":/mainwidget/image/mainwidget/" + svgName, tempSize, QIcon::Normal, QIcon::Off);
    icon.addFile(":/mainwidget/image/mainwidget/disabled" + svgName, tempSize, QIcon::Disabled, QIcon::On);
    icon.addFile(":/mainwidget/image/mainwidget/disabled" + svgName, tempSize, QIcon::Disabled, QIcon::Off);
    ui->pbn_robotpower->setIcon(icon);
    ui->pbn_robotpower->setText(btnText);
}

void MainWidget::on_hSlider_speed_sliderReleased()
{
    int curValue = ui->hSlider_speed->value();
    setRobotSpeed(curValue);
}

void MainWidget::slot_changeAuthoritySuccess(const QString &sAuthName, bool isAuthorityChanged)
{
    Q_UNUSED(sAuthName)
    updateCurrentAuthorityInfo();

	if (!isAuthorityChanged) {
        return;
    }

    auto authorityList = AuthorityManager::instance()->usingAuthorityList();
    if (authorityList.isEmpty()) {
        return;
    }

    QString authorityTip = "";
    bool isContainsBuiltInAuth = false;
    for (auto authority : authorityList) {
        if (AuthorityManager::instance()->isBuiltInAuthority(authority)) {
            isContainsBuiltInAuth = true;
            break;
        }
    }

    if (isContainsBuiltInAuth) {
        authorityList.removeAll(AuthorityManager::instance()->currentAuthority());
        for (int i = 0; i < authorityList.count(); i++) {
            authorityTip += Authority::authorityNameStr(authorityList.at(i));
            if (i != authorityList.count() - 1) {
                authorityTip.append("&&");
            }
        }
    } else {
        authorityTip = Authority::authorityNameStr(AuthorityManager::instance()->currentAuthority());
    }

    PRINT_MSG(tr("Current authority is %1.").arg(authorityTip));
}

void MainWidget::updateCurrentAuthorityInfo()
{
    const Authority authority = AuthorityManager::instance()->currentAuthority();
    if (!authority.isValid()) {
        return;
    }

    ui->pbn_switchAuthority->setText(Authority::authorityNameStr(authority));


    QSize tempSize = TitleIconSize;
    QString iconName = QString("%1.svg").arg(Authority::authorityIcon(authority.authLevel()));
    QString disabledIconName = QString("%1_disabled.svg").arg(Authority::authorityIcon(authority.authLevel()));
    QIcon icon;
    icon.addFile(iconName, tempSize, QIcon::Normal, QIcon::On);
    icon.addFile(iconName, tempSize, QIcon::Normal, QIcon::Off);
    icon.addFile(disabledIconName, tempSize, QIcon::Disabled, QIcon::On);
    icon.addFile(disabledIconName, tempSize, QIcon::Disabled, QIcon::Off);
    ui->pbn_switchAuthority->setIcon(icon);
}

void MainWidget::zeroPoseEnabled(bool isEnabled)
{
    qDebug() << "MainWidget::zeroPoseEnabled: " << isEnabled;
    ui->pbn_zeroPose->setEnabled(isEnabled);
}

void MainWidget::initPoseEnabled(bool isEnabled)
{
    qDebug() << "MainWidget::initPoseEnabled: " << isEnabled;
    ui->pbn_initPose->setEnabled(isEnabled);
}

void MainWidget::sliderEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    m_bSliderAuthorityEnable = isEnabled;
    if (Communication::instance()->getCurSpeedReducingTrigger()) {
        ui->hSlider_speed->setEnabled(false);
        ui->edit_robotspeed->setEnabled(false);
        return;
    }
    ui->hSlider_speed->setEnabled(isEnabled);
    ui->edit_robotspeed->setEnabled(isEnabled);
}

void MainWidget::clearAlarmEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->pbn_clearAlarm->setEnabled(isEnabled);
}

void MainWidget::robotPowerEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->pbn_robotpower->setEnabled(isEnabled);
}

void MainWidget::robotEnableEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->pbn_enable->setEnabled(isEnabled);
}

void MainWidget::robotModeEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->pbn_mode->setEnabled(isEnabled);
}

void MainWidget::robotEmergecyStopEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->pbn_emergeStop->setEnabled(isEnabled);
}

void MainWidget::outPutViewEnabled(bool isEnabled)
{
    ui->pbn_showLogFlowForm->setEnabled(isEnabled);
}

void MainWidget::logViewEnabled(bool isEnabled)
{
    m_logForm->logViewEnabled(isEnabled);
}

void MainWidget::switchAuthorityEnabled(bool isEnabled)
{
    ui->pbn_switchAuthority->setEnabled(isEnabled);
}

void MainWidget::switchControllerAuthorityEnabled(bool isEnabled)
{
    ui->pbn_controllerAuthority->setEnabled(isEnabled);
}

void MainWidget::getFunctionEnabledList(QList<QVariant> &retList)
{
    retList.clear();
    retList.append(QVariant::fromValue(QPair<QString, QString>("zeroPoseEnabled", AuthorityTr::tr("Enable absolute zero button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("initPoseEnabled", AuthorityTr::tr("Enable initial pose button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("sliderEnabled", AuthorityTr::tr("Enable speed setting slider"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("clearAlarmEnabled", AuthorityTr::tr("Enable alarm clear button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("robotPowerEnabled", AuthorityTr::tr("Enable robot power button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("robotEnableEnabled", AuthorityTr::tr("Enable robot enable button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("robotModeEnabled", AuthorityTr::tr("Enable manual/auto mode button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("robotEmergecyStopEnabled", AuthorityTr::tr("Enable emergency stop button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("outPutViewEnabled", AuthorityTr::tr("View output page"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("logViewEnabled", AuthorityTr::tr("View log page"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("switchAuthorityEnabled", AuthorityTr::tr("Enable authority switch button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("switchControllerAuthorityEnabled", AuthorityTr::tr("Enable controller authority switch button"))));
}

void MainWidget::on_pbn_cancel_clicked()
{
    ui->tabWidget->setCurrentIndex(m_preTabWidgetIndex);
    setTakePointUI(false);

    for (int i = 0;
         i < ui->tabWidget->count(); i++)
        ui->tabWidget->setTabEnabled(i, true);

    // 恢复原权限
    if (Communication::instance()->isProgramPause()) {
        AuthorityManager::instance()->updateAuthority(Authority::ProjectPause);
    } else {
        AuthorityManager::instance()->updateAuthority();
    }
}

void MainWidget::on_pbn_zeroPose_released()
{
    CommunicationEngine::instance()
        ->enqueueCmd(this, AbstractCmd::CmdType_Control_JointMoveZeroEnd);
}

void MainWidget::on_pbn_minimize_clicked()
{
    WindowManager::instance()->enqueueCmdInfo(WindowCmd_MainWidgetMinimize);
}

void MainWidget::on_pbn_controllerAuthority_clicked()
{
    DialogContainerForm::instance()->showDialog(DialogContainerForm::DialogStackForm_ControllerAuthorityForm);
}

void MainWidget::slot_controllerAuthorityChanged(InoCtrlAuthority type)
{
    QSize tempSize = TitleIconSize;
    QIcon icon;
    if (type == InoCtrlAuthority_TeachPad || type == InoCtrlAuthority_Unknown) {
        icon.addFile(":/mainwidget/image/mainwidget/authorityunlock.svg", tempSize, QIcon::Normal);
        icon.addFile(":/mainwidget/image/mainwidget/authorityunlockdisabled.svg", tempSize, QIcon::Disabled);
    } else {
        icon.addFile(":/mainwidget/image/mainwidget/authoritylock.svg", tempSize, QIcon::Normal);
        icon.addFile(":/mainwidget/image/mainwidget/authoritylockdisabled.svg", tempSize, QIcon::Disabled);
    }
    ui->pbn_controllerAuthority->setIcon(icon);
}

void MainWidget::slot_infoMessageBox(const QString str, bool isPrint)
{
    MessageBox::warning(str, QMessageBox::Ok, QMessageBox::NoButton, isPrint);
}

void MainWidget::slot_warningMessageBox(const QString str, bool isPrint)
{
    MessageBox::information(str, QMessageBox::Ok, QMessageBox::NoButton, isPrint);
}

void MainWidget::slot_errorMessageBox(const QString str, bool isPrint)
{
    MessageBox::critical(str, QMessageBox::Ok, QMessageBox::NoButton, isPrint);
}


void MainWidget::cleanupVirtualControllerProcesses()
{
    qDebug() << "[VirtualController] Starting cleanup of virtual controller processes...";
    
    // 获取需要清理的进程列表
    QStringList processList = getVirtualControllerProcessList();
    
    if (processList.isEmpty()) {
        qDebug() << "[VirtualController] No virtual controller processes to clean up.";
        return;
    }
    
    qDebug() << "[VirtualController] Found" << processList.size() << "processes to clean up:" << processList;
    
    // 尝试关闭进程
    int successCount = 0;
    int failCount = 0;
    
    for (const QString& processName : processList) {
        if (closeProcessWithRetry(processName, 1, 500)) {
            successCount++;
            qDebug() << "[VirtualController] Successfully closed process:" << processName;
        } else {
            failCount++;
            qWarning() << "[VirtualController] Failed to close process:" << processName;
        }
    }
    
    qDebug() << "[VirtualController] Cleanup completed. Success:" << successCount << "Failed:" << failCount;
    
    // 如果有进程关闭失败，记录警告
    if (failCount > 0) {
        qWarning() << "[VirtualController]" << failCount << "processes could not be closed.";
    }
}

QStringList MainWidget::getVirtualControllerProcessList() const
{
    // 统一的进程列表，确保检查和关闭使用相同的列表
    return {
        "dsp_Colla_A.exe",
        "controller.exe"
    };
}

bool MainWidget::closeProcessWithRetry(const QString& processName, int maxRetries, int retryDelayMs)
{
    for (int attempt = 1; attempt <= maxRetries; ++attempt) {
        qDebug() << "[VirtualController] Attempt" << attempt << "to close process:" << processName;
        
        if (closeSingleProcess(processName)) {
            return true;
        }
        
        if (attempt < maxRetries) {
            qDebug() << "[VirtualController] Retrying in" << retryDelayMs << "ms...";
            QThread::msleep(retryDelayMs);
        }
    }
    
    return false;
}

bool MainWidget::closeSingleProcess(const QString& processName)
{
    QProcess process;
    
#ifdef Q_OS_WIN
    // Windows: 使用 taskkill
    QString program = "taskkill";
    QStringList arguments = {"/F", "/IM", processName};
#else
    // Linux/macOS: 使用 pkill
    QString program = "pkill";
    QStringList arguments = {"-f", processName};
#endif
    
    process.start(program, arguments);
    
    if (!process.waitForStarted(1000)) {
        qWarning() << "[VirtualController] Failed to start process killer for:" << processName;
        return false;
    }
    
    if (!process.waitForFinished(3000)) {
        qWarning() << "[VirtualController] Process killer timed out for:" << processName;
        process.kill();
        return false;
    }
    
    int exitCode = process.exitCode();
    QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
    QString error = QString::fromLocal8Bit(process.readAllStandardError());
    
    if (exitCode == 0) {
        return true;
    } else {
        qDebug() << "[VirtualController] Process killer exit code:" << exitCode 
                 << "for process:" << processName;
        qDebug() << "[VirtualController] Output:" << output;
        qDebug() << "[VirtualController] Error:" << error;
        return false;
    }
}


void MainWidget::updateVirtualControllerStatusOnExit()
{
    // 通过插件管理器获取 VirtualControllerAttribute 实例
    PluginEngine::PluginManager* pluginManager = PluginEngine::PluginManager::instance();
    if (!pluginManager) return;
    
 
    

     // 方法1：尝试使用正确的插件名
    PluginEngine::IPlugin* vcPlugin = pluginManager->getPluginAddressByPluginName("VirtualControllerFrom");
    if (!vcPlugin) {
        // 方法2：尝试通过PluginSpec获取
        PluginEngine::PluginSpec* spec = pluginManager->pluginByName("VirtualControllerFrom");
        if (spec && spec->plugin()) {
            vcPlugin = spec->plugin();
        }
    }
    
    if (!vcPlugin) {
        qWarning() << "[VirtualController] VirtualControllerFrom plugin not loaded or not found";
        return;
    }
 

    // 使用pluginCommonInterface调用
    QList<QVariant> params;
    QList<QVariant> retList;
    
    bool success = vcPlugin->pluginCommonInterface(
        "updateAllControllersToDisconnected",
        params,
        retList);
    
    if (!success) {
        qWarning() << "[VirtualController] Failed to update virtual controller status";
    } else {
        qDebug() << "[VirtualController] Successfully updated all virtual controllers to disconnected";
    }
}
