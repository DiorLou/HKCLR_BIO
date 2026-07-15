#pragma once
#include <QEvent>
#include <QMap>
#include <QIcon>
#include "toolparam.h"
#include "configinfo.h"
#include "common_global.h"

const int BASE_SCROLL_BAR_SIZE = 20;

namespace Internal
{
class CommonPrivate;
}
class QScreen;
class QTimer;
class COMMON_EXPORT Common : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConfigInfo configInfo MEMBER m_configInfo)
    Q_PROPERTY(QStringList disabledPlugins MEMBER m_disabledPlugins)
    Q_PROPERTY(double teachSpeedPercentage MEMBER m_teachSpeedPercentage)
    Q_PROPERTY(double moveSpeedLimitForOnlineProgramming
                   MEMBER m_moveSpeedLimitForOnlineProgramming)
    Q_PROPERTY(QList<int> collisionClass MEMBER m_collisionClass)
    Q_PROPERTY(bool isRealRobotExist MEMBER m_isRealRobotExist)
    Q_PROPERTY(bool isEnableJoint6Rot360 MEMBER m_isEnableJoint6Rot360)
    Q_PROPERTY(bool isDuringStartupProcess MEMBER m_isDuringStartupProcess)
    Q_PROPERTY(bool isCloseDialogContainerForm
                   MEMBER m_isCloseDialogContainerForm)
    Q_PROPERTY(bool isNotConfirmShutdown MEMBER m_isNotConfirmShutdown)
    Q_PROPERTY(bool isShutdownAfterPowerOff MEMBER m_isShutdownAfterPowerOff)
    Q_PROPERTY(bool isRestart MEMBER m_isRestart)
    Q_PROPERTY(bool isEnableSafetyModeByTriStateSwitch
                   MEMBER m_isEnableSafetyModeByTriStateSwitch)
    Q_PROPERTY(bool isEnableSafetyModeByExternalSafetyIO
                   MEMBER m_isEnableSafetyModeByExternalSafetyIO)
    Q_PROPERTY(bool isEnableSafetyModeByLinkedIO
                   MEMBER m_isEnableSafetyModeByLinkedIO)
    Q_PROPERTY(bool isEnableCollision MEMBER m_isEnableCollision)
    Q_PROPERTY(bool isLoadingLanguage MEMBER m_isLoadingLanguage)
    Q_PROPERTY(ToolParam toolParam MEMBER m_toolParam)
    Q_PROPERTY(bool lockScreenEnabled MEMBER m_lockScreenEnabled)
    Q_PROPERTY(QMap<int, QMap<QString, double>>
                   mapDHParms MEMBER m_mapDHParms)
    Q_PROPERTY(double horRatio MEMBER m_horRatio)
    Q_PROPERTY(double verRatio MEMBER m_verRatio)
    Q_PROPERTY(double minRatio MEMBER m_minRatio)
    Q_PROPERTY(int scrollBarWidth MEMBER m_scrollBarWidth)
    Q_PROPERTY(int defaultSectionSize MEMBER m_defaultSectionSize)
    Q_PROPERTY(int availableGeometryX MEMBER m_availableGeometryX)
    Q_PROPERTY(int availableGeometryY MEMBER m_availableGeometryY)
    Q_PROPERTY(int actualAppWidth MEMBER m_actualAppWidth)
    Q_PROPERTY(int actualAppHeight MEMBER m_actualAppHeight)
    Q_PROPERTY(int actualAppX MEMBER m_actualAppX)
    Q_PROPERTY(int actualAppY MEMBER m_actualAppY)
    Q_PROPERTY(bool isPDetailShow MEMBER m_isPDetailShow)
    Q_PROPERTY(bool isJPDetailShow MEMBER m_isJPDetailShow)
    Q_PROPERTY(bool isProjectLoaded MEMBER m_isProjectLoaded)
    Q_PROPERTY(QVariant currentScreen MEMBER m_currentScreen)
signals:
    void languageChanged();
public:
    static Common *instance();
    Common();

    Q_INVOKABLE void loadTranslator();

    Q_INVOKABLE void updateConfigInfo();

    Q_INVOKABLE ConfigInfo getConfigInfo() const;
    Q_INVOKABLE void setConfigInfo(const ConfigInfo &configInfo);

    Q_INVOKABLE ToolParam getToolParam() const;
    Q_INVOKABLE void setToolParam(const ToolParam &toolParam);

private:
    Q_INVOKABLE int getRatioWidth(const int &width);
    Q_INVOKABLE int getRatioHeight(const int &height);
    Q_INVOKABLE int getMinRatioSize(const int &size);
    Q_INVOKABLE QSize getRatioSize(const int &width, const int &height);
    Q_INVOKABLE int getRatioFontWidth(const QString &content,
                                      int pixelSize = 16);
    Q_INVOKABLE void setRatioStyleSheet(QWidget *widget);
    ConfigInfo m_configInfo;
    QStringList m_disabledPlugins;

    double m_teachSpeedPercentage;  // 0.00 ~ 1.00

    double m_moveSpeedLimitForOnlineProgramming;

    QList<int> m_collisionClass;

    bool m_isRealRobotExist;
    bool m_isEnableJoint6Rot360;

    bool m_isDuringStartupProcess;

    bool m_isCloseDialogContainerForm;

    bool m_isShutdownAfterPowerOff;
    bool m_isRestart;

    bool m_isEnableSafetyModeByTriStateSwitch;
    bool m_isEnableSafetyModeByExternalSafetyIO;
    bool m_isEnableSafetyModeByLinkedIO;
    bool m_isEnableCollision;

    bool m_isLoadingLanguage;

    ToolParam m_toolParam;

    bool m_lockScreenEnabled;

public:
    /*
     * I5 DH parms
     *
     * 连杆i  a(mm)  α(°)  d(mm)  θ(°)
     * 1	 0	    0	  98.5	 180
     * 2	 0	    -90   121.5  -90
     * 3	 408	180   0	     0
     * 4	 376	180   0	     -90
     * 5	 0	    -90   102.5  0
     * 6	 0	    90	  94	 0
     */
    QMap<int, QMap<QString, double>> m_mapDHParms;

    QIcon m_iconZoomOut, m_iconZoomIn, m_iconUpMove, m_iconDownMove,
        m_iconLeftMove, m_iconRightMove,
        m_iconLeftRotate, m_iconRightRotate, m_iconFrontView,
        m_iconGround, m_iconCoord,
        m_iconRealtimeModel, m_iconTargetModel, m_iconModel;

private:
    double m_horRatio;
    double m_verRatio;
    double m_minRatio;
    int m_scrollBarWidth;
    int m_defaultSectionSize;
    int m_availableGeometryX;
    int m_availableGeometryY;
    int m_actualAppWidth;
    int m_actualAppHeight;

    int m_actualAppX = 0;
    int m_actualAppY = 0;
    QTranslator *m_translator;

    bool m_isNotConfirmShutdown;

    bool m_isProjectLoaded;
    bool m_isPDetailShow = false;
    bool m_isJPDetailShow = false;

public slots:
    void slot_screenAviableChanged(const QRect &geometry);
    void refreshScreenData();
private:
    // bool m_hasSendEvent = false;
    void screenAviableChanged(QScreen *screen);
    bool m_needTips = false;
    QScreen *m_primaryScreen = 0;
    QVariant m_currentScreen = 0;
    QTimer *m_timerRefreshScreen = 0;
    QTimer *m_timerShowMsgBox = 0;
    QTimer *m_timerResizeMain = 0;
    bool m_isNeedRestartMust = false;
    bool m_isCurrentNoScreen = false;
};
