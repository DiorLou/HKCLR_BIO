#include "coreplugin.h"
#include <QDebug>
#include <QDir>
#include <QTranslator>
#include <QTimer>
#include <QApplication>
#include "firstcontainerform.h"
#include "mainwidget.h"
#include "metatype.h"
#include "splashscreen.h"
#include "instance.h"
#include "flowwidgetmanager.h"
#include "common.h"
#include "dialogcontainerform.h"
#include "modelessdialogcontainerform.h"
#include "windowmanager.h"
#ifdef PLATFORM_COBOT_TP_WINDOWS
    #include <windows.h>
#endif
#include "pluginmanager.h"
#include "communicationengine.h"
CorePlugin::CorePlugin(QObject *)
{
}

bool CorePlugin::initialize(
    const QStringList &arguments, QString *errorString)
{
    qDebug() << "CorePlugin::initialize()";
    // new MainWidget;
    MainWidget::instance()->initialize();

    new DialogContainerForm(MainWidget::instance());
    new ModellessDialogContainerForm(MainWidget::instance());
    new WindowManager(this);
    return true;
}

bool CorePlugin::delayedInitialize()
{
    qDebug() << "CorePlugin::delayedInitialize()";
    return true;
}

void CorePlugin::extensionsInitialized()
{
    PluginEngine::PluginManager::instance()->registerDelayInit(this->pluginSpec());
    MainWidget::instance()->extensionsInitialized();

    auto list = FirstContainerForm::FirstContainerFormInstances();
    for (auto i : list)
        i->setCurrentToolBoxWidget(0);

#ifdef PLATFORM_COBOT_TP_WINDOWS
    int width = Instance::common()->property("actualAppWidth").value<int>();
    int height = Instance::common()->property("actualAppHeight").value<int>();
    int startX = 0;
    int startY = 0;
    int x = 0;
    int y = 0;
    if (qApp->primaryScreen()) {
        startX = qApp->primaryScreen()->availableGeometry().width();
        startY = qApp->primaryScreen()->availableGeometry().height();
        x = (startX - MainWidget::instance()->width()) / 2;
        y = (startY - MainWidget::instance()->height()) / 2;
    }
    MainWidget::instance()->move(x, y);
    Common::instance()->setProperty("actualAppX", x);
    Common::instance()->setProperty("actualAppY", y);
#endif

    MainWidget::instance()->showMainWidget();
    SplashScreen::instance()->hideDialog();

#ifdef Q_OS_ANDROID
    MainWidget::instance()->checkAppRunBackground();

    if (QNativeInterface::QAndroidApplication::sdkVersion() >= 30
        && !MainWidget::instance()->checkAllFilesAccessPermission()) {
        MainWidget::instance()->requestAllFilesAccessPermission();
    }
#endif

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::siganl_modelLayerHasLoadLanguage,
            this, [=]() {
                static bool once = true;
                if (once) {
                    once = false;
                    QMetaObject::invokeMethod(
                        Instance::connectControllerForm(), "triggerAutoConnect", Qt::DirectConnection);
                }
            });

    QMetaObject::invokeMethod(
        Instance::languageForm(), "updateLanguage", Qt::DirectConnection,
        Q_ARG(bool, false));

    FlowWidgetManager::instance()->updateGeometry();
}

bool CorePlugin::pluginCommonInterface(
    const QString &funcName,
    const QList<QVariant> &params, QList<QVariant> &retList)
{
    bool ret = true;

    if (FuncName_GetFunctionEnabledList == funcName
        && 0 == params.size()) {
        retList.clear();
        MainWidget::instance()->getFunctionEnabledList(retList);
    } else if (FuncName_SetFunctionEnabledList == funcName
               && 1 == params.size()) {
        MainWidget::instance()->setFunctionEnabledList(params.at(0));
    }

    return ret;
}
