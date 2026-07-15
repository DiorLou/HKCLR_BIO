/****************************************************************************
 *
 * CopyRight © Shenzhen Inovance Technology Co., Ltd. All Rights Reserved
 * Contact: https://www.inovance.com/
 *
 ****************************************************************************/

#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QDir>
#include <QFontDatabase>
#include <QProcess>
#include <QScopedPointer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMetaType>
#include <vector>
#include "application.h"
#include "authoritymanager.h"
#include "dialogcontainerform.h"
#include "communication.h"
#include "databaselocal.h"
#include "cobotlogex.h"
#include "pluginmanager.h"
#include "iplugin.h"
#include "tcpserverengine.h"
#include "tcpclientengine.h"
#include "mainthreadengine.h"
#include "shutdownthread.h"
#include "windowmanager.h"
#include "virtualkeyboard.h"
#include "hostosinfo.h"
#include "communicationengine.h"
#include "metapath.h"
#include "splashscreen.h"
#if defined(Q_OS_WIN)
    #ifndef INOCOBOTTP_MSVC_QT5
        // #  include "client/windows/handler/exception_handler.h"
    #else
        #include "client/windows/handler/exception_handler.h"
        #include "commandinfo.h"
        #include "DataTypeDef.h"
        #include "PrintInfo.h"
        #include "labeldata.h"
        #include "iostruct.h"
    #include <QMetaType>
    #endif
#else
#  include "client/linux/handler/exception_handler.h"
#endif
#include "flowwidget/flowwidgetmanager.h"

#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(QList<InoLabelItem>)
Q_DECLARE_METATYPE(QList<quint8>)
Q_DECLARE_METATYPE(QList<bool>)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(Ino_Cobot_ADDA_Data)
Q_DECLARE_METATYPE(QList<Ino_Cobot_ADDA_Data>)
#endif
const char SETTINGS_OPTION[] = "-settingspath";
const char TEST_OPTION[] = "-test";
const char PLUGINPATH_OPTION[] = "-pluginpath";

static QSettings *createUserSettings()
{
    return new QSettings(QSettings::IniFormat, QSettings::UserScope,
                         QLatin1String("InovanceProject"),
                         QLatin1String("InoCobotTP"));
}

static inline QSettings *userSettings()
{
    QSettings *settings = createUserSettings();
    const QString fromVariant = QLatin1String("Inovance");
    if (fromVariant.isEmpty())
        return settings;

    // Copy old settings to new ones:
    QFileInfo pathFi = QFileInfo(settings->fileName());
    if (pathFi.exists())  // already copied.
        return settings;

    QDir destDir = pathFi.absolutePath();
    if (!destDir.exists())
        destDir.mkpath(pathFi.absolutePath());

    QDir srcDir = destDir;
    srcDir.cdUp();
    if (!srcDir.cd(fromVariant))
        return settings;

    if (srcDir == destDir)  // Nothing to copy and no settings yet
        return settings;

    // Make sure to use the copied settings:
    delete settings;
    return createUserSettings();
}

static const char *SHARE_PATH
    = Utils::HostOsInfo::isMacHost() ?
          "/../Resources" :
          "/../share/teachpendant";

static void installFont()
{
#ifdef Q_OS_WIN
    QStringList fontFiles = {
        ":/font/SourceHanSansCN-Bold.otf",
        ":/font/SourceHanSansCN-ExtraLight.otf",
        ":/font/SourceHanSansCN-Heavy.otf",
        ":/font/SourceHanSansCN-Light.otf",
        ":/font/SourceHanSansCN-Medium.otf",
        ":/font/SourceHanSansCN-Normal.otf",
        ":/font/SourceHanSansCN-Regular.otf"};

    for (const QString &fileName : fontFiles) {
        int ret = QFontDatabase::addApplicationFont(fileName);
        if (ret < 0) {
            qDebug() << __FUNCTION__ << QObject::tr("Failed to install %1").arg(fileName);
        }
    }
#endif

    QFont font;
    font.setFamily("Source Han Sans CN");
    font.setWeight(QFont::Normal);
    qApp->setFont(font);
}

void registerMetaType()
{
    qRegisterMetaType<ToolIOConfigContent>("ToolIOConfigContent");
    qRegisterMetaType<QList<QList<ToolIOConfigContent>>>("QList<QList<ToolIOConfigContent>>");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<AbstractCmd::CmdType>("AbstractCmd::CmdType");

#ifdef INOCOBOTTP_MSVC_QT5
    qRegisterMetaType<QSet<QString>*>("QSet<QString>*");
    qRegisterMetaType<QSet<QString>>("QSet<QString>");
    qRegisterMetaType<QMap<int, void*>>("QMap<int,void*>");
    qRegisterMetaType<QVector<QVariant>>("QVector<QVariant>");
    qRegisterMetaType<QVariant>("QVariant");
    qRegisterMetaType<QStringList*>("QStringList*");
    qRegisterMetaType<QList<double>>("QList<double>");
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QList<int>>("QList<int>");

    qRegisterMetaType<InoCtrlAuthority>("InoCtrlAuthority");
    qRegisterMetaType<InoMoveStepSizePara>("InoMoveStepSizePara");
    qRegisterMetaType<ToolParams>("ToolParams");
    qRegisterMetaType<WobjParams>("WobjParams");
    qRegisterMetaType<InoCobotWifiInfo>("InoCobotWifiInfo");
    qRegisterMetaType<CobotGeneralMatchInfo>("CobotGeneralMatchInfo");
    qRegisterMetaType<LoadParams>("LoadParams");
    qRegisterMetaType<CobotTrajRecoveryParam>("CobotTrajRecoveryParam");
    qRegisterMetaType<CobotModbusConnectSts>("CobotModbusConnectSts");
    qRegisterMetaType<PointFileChangeType>("PointFileChangeType");
    qRegisterMetaType<int16u>("int16u");
    qRegisterMetaType<int16s>("int16s");
    qRegisterMetaType<QList<InoLabelItem>>("QList<InoLabelItem>");
    qRegisterMetaType<QList<quint8>>("QList<quint8>");
    qRegisterMetaType<QList<bool>>("QList<bool>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    qRegisterMetaType<Ino_Cobot_ADDA_Data>("Ino_Cobot_ADDA_Data");
    qRegisterMetaType<QList<Ino_Cobot_ADDA_Data>>("QList<Ino_Cobot_ADDA_Data>");
    qRegisterMetaType<InoRobLog::PrintInfo::LogType>();
    qRegisterMetaType<InoRobLog::PrintInfo::InfoType>();

#endif

}

int main(int argc, char *argv[])
{


    bool ret = true;
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

#if defined(Q_OS_LINUX) || defined(Q_OS_ANDROID)
    qputenv("QT_IM_MODULE", QByteArray("inovance"));
#endif

    Application app(argc, argv);

    app.setWindowIcon(QIcon(":/mainwidget/image/mainwidget/inocobottp.png"));

    qDebug() << "********* Minidump Path = " << QDir::cleanPath(ABSOLUTE_SHARE_PATH).toStdWString() + L"/minidump";


    if ((ret = !app.isRunning())
        && DatabaseLocal::instance()->m_initDatabaseComplete) {
        qDebug() << "From main thread: " << QThread::currentThread();

        // installFont();
        registerMetaType();
        SplashScreen::instance()->showDialog();
        new Communication;
        new CommunicationEngine(QThread::idealThreadCount() - 1, 3, true);

        new ShutdownThread();
        new MainThreadEngine();
        TcpServerEngine::uiInstance();
        TcpServerEngine::scriptRuntimeInstance();
        TcpServerEngine::uiInstance()->listen(COBOT_TP_MONITORING_PORT);
        new TcpClientEngine(2);
        new FlowWidgetManager();
        if ((ret = Communication::instance()->loginAllClient())) {
            new VirtualKeyboard();
            // Manually determine -settingspath command line option
            // We can't use the regular way of the plugin manager,
            // because that needs to parse plugin meta data
            // but the settings path can influence which plugins are enabled
            QString settingsPath;
            QStringList customPluginPaths;
            // adapted arguments list is passed to plugin manager later
            QStringList arguments = app.arguments();
            QMutableStringListIterator it(arguments);
            bool testOptionProvided = false;
            while (it.hasNext()) {
                const QString &arg = it.next();
                if (arg == QLatin1String(SETTINGS_OPTION)) {
                    it.remove();
                    if (it.hasNext()) {
                        settingsPath = QDir::fromNativeSeparators(it.next());
                        it.remove();
                    }
                } else if (arg == QLatin1String(PLUGINPATH_OPTION)) {
                    it.remove();
                    if (it.hasNext()) {
                        customPluginPaths
                            << QDir::fromNativeSeparators(it.next());
                        it.remove();
                    }
                } else if (arg == QLatin1String(TEST_OPTION)) {
                    testOptionProvided = true;
                }
            }
            QScopedPointer<QTemporaryDir> temporaryCleanSettingsDir;
            if (settingsPath.isEmpty() && testOptionProvided) {
                const QString settingsPathTemplate
                    = QDir::cleanPath(
                        QDir::tempPath()
                        + QString::fromLatin1("/inocobottp-test-settings"));
                temporaryCleanSettingsDir.reset(
                    new QTemporaryDir(settingsPathTemplate));
                if (!temporaryCleanSettingsDir->isValid())
                    return 1;
                settingsPath = temporaryCleanSettingsDir->path();
            }
            if (!settingsPath.isEmpty())
                QSettings::setPath(
                    QSettings::IniFormat, QSettings::UserScope,
                    settingsPath);

            // Must be done before any QSettings class is created
            QSettings::setPath(
                QSettings::IniFormat, QSettings::SystemScope,
                QCoreApplication::applicationDirPath()
                    + QLatin1String(SHARE_PATH));
            QSettings::setDefaultFormat(QSettings::IniFormat);
            // plugin manager takes control of this settings object
            QSettings *settings = userSettings();

            QSettings *globalSettings
                = new QSettings(QSettings::IniFormat,
                                QSettings::SystemScope,
                                QLatin1String("InoProject"),
                                QLatin1String("InoCobotTP"));

            new PluginEngine::PluginManager;
            PluginEngine::PluginManager::setPluginIID(
                QLatin1String("com.qt-project.Inovance.InoCobotTPPlugin"));
            PluginEngine::PluginManager::setGlobalSettings(
                globalSettings);
            PluginEngine::PluginManager::setSettings(settings);

            qDebug() << "@@@@ settings->fileName() : "
                     << settings->fileName();

#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
            PluginEngine::PluginManager::setPluginPaths(
                QStringList() << ABSOLUTE_PLUGIN_SHARE_PATH);
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
            PluginEngine::PluginManager::setPluginPaths(
                QStringList() << APPLICATION_DIR_PATH);
#endif
            /* 解析完插件管理器，加载插件之前加载权限列表 */
            ret = AuthorityManager::instance()->loadAllAuthorityInfo();
            if (!ret) {
                // PRINT_WARN(QObject::tr("Failed to load authority management info"));
                // return -1;
            }

            PluginEngine::PluginManager::loadPlugins();

            LOG_INFO(QString("%1 Start").arg(COBOT_TP_CASED_ID));
            FREQ_LOG_PRINT_TIMESTAMP_THREAD

            QObject::connect(
                Application::instance()->m_lockScreenTimer,
                &QTimer::timeout,
                DialogContainerForm::instance(),
                &DialogContainerForm::slot_showLockScreenForm);

            CobotLog::instance()->setEnableOperationLog(true);
        }

        int appRet = app.exec();
        ret = (0 == appRet);
    }

    return ret ? 0 : -1;
}
