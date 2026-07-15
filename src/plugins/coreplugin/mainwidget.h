#pragma once

#include <QHash>
#include <QVector>
#include <QListWidget>
#include <mutex>
#include <QProcess>
#include <condition_variable>
#include "core_global.h"
#include "abstractwidget.h"
#include "metatype.h"
#include "ctrlauthority.h"
#include "generalmatchdefines.h"
#include "commandinfo.h"
#include "roadpoint.h"
#include "pluginmanager.h"
#include "iplugin.h"

static const int TAB_TEACH_INDEX = 0;

namespace Ui
{
class MainWidget;
}
class MainWidgetLogForm;

class CORE_EXPORT MainWidget : public AbstractWidget<Ui::MainWidget>
{
    Q_OBJECT

public:
    enum TakePointMode
    {
        TakePointMode_Normal,
        TakePointMode_WaypointTeach
    };

public:
    static MainWidget *instance();

    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    Q_INVOKABLE void showMainWidget();
    Q_INVOKABLE void setCurrentTab(int tabPage);
    Q_INVOKABLE void setCurrentTab(const QString &tabText);
    Q_INVOKABLE void setSpeedEnable(bool bEnable);
    Q_INVOKABLE void getVirtualKeyBoardBottomRight(int &x, int &y);
    Q_INVOKABLE int getTabIndexByText(const QString &tabText);
    Q_INVOKABLE int getTabIndexByWidget(QWidget *pWidget);

    void requestRoadPoint(QObject *object, TakePointMode mode = TakePointMode_Normal);

    Q_INVOKABLE void power(bool isNotConfirmShutdown = false);

    Q_INVOKABLE bool isVisible() const;
    Q_INVOKABLE void updateDeviceMode();
    Q_INVOKABLE void setBtnLogText(const QString &msg);

    Q_INVOKABLE void UpdateWifiStatus();
    Q_INVOKABLE void UpdateWifiOnSSidUnknow();
    Q_INVOKABLE void SetHeartBeat(bool bSwitch);
    Q_INVOKABLE void SafetyExit();

    InoCoRobotBodyPowerState GetRobotBodyPowerStatus() const { return m_robotBodyPowerState; }

    int addTabWidget(QWidget *widget,
                     const QString &tabText, const QString &tabIcon);
    int addTabWidget(int index, QWidget *widget,
                     const QString &tabText, const QString &tabIcon);
    void setTabEnable(int index, bool bEnable, bool directEffect = false);

    void initialize();
    void extensionsInitialized();

    void setTabText(int index, const QString &tabText);
    void checkAppRunBackground();
    bool checkAllFilesAccessPermission();
    void requestAllFilesAccessPermission();

    // 权限管理
    void getFunctionEnabledList(QList<QVariant> &retList);
    // 权限管理
    Q_INVOKABLE void zeroPoseEnabled(bool isEnabled);
    Q_INVOKABLE void initPoseEnabled(bool isEnabled);
    Q_INVOKABLE void sliderEnabled(bool isEnabled);
    Q_INVOKABLE void clearAlarmEnabled(bool isEnabled);
    Q_INVOKABLE void robotPowerEnabled(bool isEnabled);
    Q_INVOKABLE void robotEnableEnabled(bool isEnabled);
    Q_INVOKABLE void robotModeEnabled(bool isEnabled);
    Q_INVOKABLE void robotEmergecyStopEnabled(bool isEnabled);
    Q_INVOKABLE void outPutViewEnabled(bool isEnabled);
    Q_INVOKABLE void logViewEnabled(bool isEnabled);
    Q_INVOKABLE void switchAuthorityEnabled(bool isEnabled);
    Q_INVOKABLE void switchControllerAuthorityEnabled(bool isEnabled);
signals:
    void currentChanged(int index);

protected:
    virtual void retranslateUi();
    void changeEvent(QEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void moveEvent(QMoveEvent *event);
    void closeEvent(QCloseEvent *closeEvent);
    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent* );
public slots:
    void slot_infoMessageBox(const QString str, bool isPrint);
    void slot_warningMessageBox(const QString str, bool isPrint);
    void slot_errorMessageBox(const QString str, bool isPrint);
private slots:
    void slot_clearAlarmInterface_result(QObject *object, bool isSuccess);
    void slot_enableRobotInterface_result(QObject *object, bool isSuccess);
    void slot_setEmergecyInterface_result(QObject *object, bool isSuccess);
    void slot_connectSuccess();
    void slot_enableEdit(bool isEnabled);
    void slot_recvRealTimeEndSpeed(double endSpeed);

    void slot_robotShutdownInterface_result(QObject *object);
    void slot_changeAuthoritySuccess(const QString &sAuthName,
                                     bool isAuthorityChanged);
    void slot_setdevicemode_result(
        bool isSuccess, MetaType::RobotDeviceMode mode);
    void slot_setspeed_result(bool isSuccess, int speed);
    void slot_passwd_confirm_result(const QString &sFuncId, bool isCorrect);

    void slot_connectControllerInterface_result(QObject *object,
                                                bool isSuccess);
    void slot_disconnectControllerInterface_result(QObject *object,
                                                   bool isSuccess);
    void slot_controllerConnectionStatusChanged(
        ControllerConnectionState status);
    void slot_controllerStateChanged(ControllerState state);
    void slot_enableStateChanged(bool enable);
    void slot_emergecyStateChanged(bool enable);
    void slot_tragteach_status(bool bDragging);
    void slot_robotBodyPowerStateChanged(InoCoRobotBodyPowerState state);
    void slot_speed_changed(quint16 speed);
    void slot_controllerAuthorityChanged(InoCtrlAuthority type);
    void setRobotSpeed(int value);
    void slot_speedReducingTriggerdChanged(bool enable);
    void slot_generalmatch_getinfo(QObject *object, bool bSuccess, const CobotGeneralMatchInfo &info);
    void slot_generalmatch_getparamsyncstatus(QObject *object, bool bSuccess, bool bTimeout);

    void slot_handleProject_result(
        QObject *object, const AbstractCmd::CmdType type,
        const QVariant &value, bool isSuccess, const QString &errMsg);

    void slot_tragteach_autorecordpos(InoPosType type, const RoadPoint &pt);

    void slot_getfirstbootstatus_result(QObject *obj, bool bSuccess, bool status);

    void slot_pbn_enable_clicked(bool checked);

    void on_pbn_zeroPose_pressed();
    void on_pbn_zeroPose_released();
    void on_pbn_initPose_pressed();
    void on_pbn_setRoadPoint_clicked();
    void on_pbn_switchAuthority_clicked();
    void on_pbn_pluginManager_clicked();
    void on_pbn_showLogFlowForm_clicked();
    void on_pbn_clearAlarm_clicked(bool checked);
    void on_pbn_mode_clicked();
    void on_pbn_wifi_clicked();
    void on_pbn_emergeStop_clicked(bool checked);
    void on_pbn_connectstatus_clicked(bool checked);
    void on_pbn_poweroff_clicked();
    void on_pbn_robotpower_clicked();
    void on_hSlider_speed_sliderReleased();
    void on_pbn_cancel_clicked();
    void on_pbn_minimize_clicked();
    void on_pbn_controllerAuthority_clicked();

private:
    void UpdateDeviceModeStatus(MetaType::RobotDeviceMode mode);
    void updateCurrentAuthorityInfo();
    void setAlarmChecked(ControllerState state);
    void setTakePointUI(bool bTakePoint);
    void retranslateTitleBar();
    void updateBottomWidgetHeight();
    void doModeChanged();
    void startGeneralMatchSync(int factoryFlag);
    void doGeneralMatchSync();
    QString splitMergeName(const QString &sName);


    //虚拟控制器相关进程关闭
    void cleanupVirtualControllerProcesses();
    QStringList getVirtualControllerProcessList() const;
    bool closeProcessWithRetry(const QString& processName, int maxRetries, int retryDelayMs);
    bool closeSingleProcess(const QString& processName);

    void updateVirtualControllerStatusOnExit();



private:
    Ui::MainWidget *ui;

    bool m_bStepModeClose = false;
    double m_endSpeed = 0;
    int m_preTabWidgetIndex = 0;
    InoCoRobotBodyPowerState m_robotBodyPowerState = ROBOT_BODY_DISCONNECTED_STATE;

    QMap<int, QPair<QWidget *, QString> > m_hashTabIndexAndWidget;
    QMap<int, QString> m_hashTabIndexAndIcon;
    QMap<int, bool> m_mapWidgetEnable;
    QHash<int, int> m_winId2index;

    QTimer *m_timerRefreshTime = nullptr;
    QObject *m_requestRoadPointInstance = nullptr;
    MainWidgetLogForm *m_logForm = nullptr;
    bool m_bSliderAuthorityEnable = false;
    int m_generalMatchDirect = -1;
};
