#include "application.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QFileInfo>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QDir>
#include <QPushButton>
#include <QSet>
#include <cstddef>
#include "common.h"
#include "databaselocal.h"
#include "messagebox.h"
#include "roboteventinfo.h"
#include "roadpoint.h"
#include "fileutils.h"
#include "instance.h"
#include "settings.h"
#include <QComboBox>
#include "cobotlog/cobotlog.h"
#include "propertydefine.h"
#include "valuestructdefine.h"
#include <QTabWidget>
#include <QTableView>
#include <QGroupBox>
#if defined(Q_OS_LINUX)
    #include "combobox.h"
    #include "abstractwidget.h"
    #include "dropdownlist.h"
    #include "LogicalExpressionKeyboard/logicalexpressionkeyboard.h"
#endif
#if defined(Q_OS_ANDROID)
    #include <QtCore/private/qandroidextras_p.h>
#endif
#include "metapath.h"
#include "stringutils.h"
#include "virtualkeyboard.h"
#include "simcontainerform.h"
#include <QClipboard>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QTextEdit>
#include "combobox.h"

static QSet<QObject *> specialWidget;

static Application *s_instance = 0;

static QPointer<ComboBox> m_cmb = NULL;

static bool isAllowPaste = true;

const int DEFAULT_LOCK_SCREEN_TIMEOUT_SEC = 500;  // 500s

Application *Application::instance()
{
    return s_instance;
}


Application::~Application()
{
#ifdef PLATFORM_COBOT_TP_MINGW_WIN
    if(m_needDeleteMemory){
        m_singleMemory->detach();
    }
    delete m_singleMemory;
#endif
}

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv),
    m_isRunning(false), m_robotType(MetaType::RobotType_invalid)
{
    s_instance = this;
    Instance::setApplication(this);

    new Instance;

#if defined(Q_OS_ANDROID)
    requestPermission("android.permission.INTERNET");
    requestPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    requestPermission("android.permission.ACCESS_NETWORK_STATE");
    requestPermission("android.permission.READ_EXTERNAL_STORAGE");
    requestPermission("android.permission.MANAGE_EXTERNAL_STORAGE");
    requestPermission("android.permission.ACCESS_CHECKIN_PROPERTIES");
    requestPermission("android.permission.GET_PACKAGE_SIZE");
    requestPermission("android.permission.ACCESS_WIFI_STATE");
    requestPermission("android.permission.CHANGE_WIFI_STATE");
    requestPermission("android.permission.ACCESS_COARSE_LOCATION");
    requestPermission("android.permission.ACCESS_FINE_LOCATION");
    requestPermission("android.permission.READ_PHONE_STATE");
    requestPermission("android.permission.WAKE_LOCK");
    requestPermission("android.permission.LOCK_TASK_AUTH");
    requestPermission("android.permission.REQUEST_IGNORE_BATTERY_OPTIMIZATIONS");
    requestPermission("android.permission.START_ACTIVITIES");
    requestPermission("android.permission.REQUEST_INSTALL_UNKNOWN_APK");
    requestPermission("android.permission.REQUEST_INSTALL_PACKAGES");
    requestPermission("android.permission.ACCESS_BACKGROUND_LOCATION");
#endif

#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
    QDir::setCurrent(QApplication::applicationDirPath());
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
    QDir::setCurrent(QStandardPaths::standardLocations(
                         QStandardPaths::GenericDataLocation)
                         .first());
#endif

    qDebug() << "APPLICATION_DIR_PATH : " << APPLICATION_DIR_PATH;
    setQuitOnLastWindowClosed(false);

    m_lockScreenTimer = new QTimer(this);
    m_lockScreenTimer->setInterval(
        DEFAULT_LOCK_SCREEN_TIMEOUT_SEC * 1000);

    initLocalConnection();
    if (!m_isRunning) {
        // clear shared memory
        // system(QString("ipcs -m | awk '$2 ~ /[0-9]+/{print $2}'"
        //                "|while read s;do ipcrm -m $s;done")
        //            .toStdString()
        //            .c_str());

        initProfile("Displays/Resolution", "1280 * 800");

#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
        createWorkDir(QDir(QString("%1/../").arg(APPLICATION_DIR_PATH)),
                      SHARE_FILE_NAME);
        createWorkDir(QDir(QString("%1/../%2").arg(APPLICATION_DIR_PATH).arg(SHARE_FILE_NAME)),
                      COBOT_TP_ID);
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
#endif
        // copyQrcToGenericDataLocation();
        copyQrcToGenericDataLocation(":/share", "/../", 1, true);
        new CobotLog(this);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), DATABASE_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), TEMPLATE_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), PROJECT_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), SCRIPT_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), PLUGIN_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), RESOURCES_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), SIMULATION_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), TRANSLATION_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), LOG_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), BACKUP_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), AUTHORITY_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), MINIDUMP_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), MANUAL_FILE_NAME);
        createWorkDir(QDir(ABSOLUTE_SHARE_PATH), ROBOTPARAMS_FILE_NAME);


        qRegisterMetaType<RoadPoint>("RoadPoint");
        qRegisterMetaType<QItemSelection>("QItemSelection");
        qRegisterMetaType<RobotEventInfo>("RobotEventInfo");
        qRegisterMetaType<QVector<int>>("QVector<int>");
        qRegisterMetaType<QThread *>("QThread*");
        qRegisterMetaType<QList<QStringList>>("QList<QStringList>");
        qRegisterMetaType<ValueLimit>("ValueLimit");

        QString configDbFilePath = QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, DATABASE_FILE_NAME, DB_CONFIG_INFO);
        bool bConfig_info_exist = QFile::exists(configDbFilePath);

        new DatabaseLocal;
        DatabaseLocal::checkDatabase();
        new Common;

        copyQrcToGenericDataLocation(":/share/studio/Language", "/../", 1, false);
        copyQrcToGenericDataLocation(":/share/teachpendant/translations", "/../", 1, false);

        copyQrcToGenericDataLocation(":/white", "/../", 1, true);


        QList<QLocale> localeList;
        QDir TsDir(QString("%1/%2")
                       .arg(ABSOLUTE_SHARE_PATH, TRANSLATION_FILE_NAME));
        for (QString file : TsDir.entryList(QStringList() << "*.qm", QDir::Files)) {
            localeList.append(QLocale(file.remove(".qm")
                                          .remove(QString("%1_").arg(COBOT_TRANSLATION_PREFIX))));
        }
        QStringList languageList;
        foreach (QLocale local, localeList) {
            languageList << local.name();
        }

#if CommonLib_Common_DeveloperMode_Enabled == 1
        bool isDeveloperMode = false;
        DatabaseLocal::getDeveloperModeEnable(isDeveloperMode);
        Instance::common()->setProperty("isDeveloperMode", isDeveloperMode);
#endif
        if (!bConfig_info_exist) {
            QLocale locale = QLocale::system();
            QString languageName = locale.name();
            if (!languageList.contains(languageName)) {
                languageName = "en_US";
            }
            DatabaseLocal::setLanguage(languageName);
        }

        QMetaObject::invokeMethod(
            Instance::common(), "loadTranslator", Qt::DirectConnection);

#if defined(Q_OS_WIN)
        QDir dir(QString("%1/translations").arg(ABSOLUTE_SHARE_PATH));
        dir.setNameFilters(QStringList() << "*.ts");
        foreach (const QFileInfo &fileInfo, dir.entryInfoList()) {
            QProcess process;
            process.start(
                "cmd.exe",
                QStringList()
                    << "/c"
                    << QString("%1/lrelease %2")
                           .arg(APPLICATION_DIR_PATH)
                           .arg(fileInfo.absoluteFilePath()));
            process.waitForFinished(-1);
        }
#elif (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
        QProcess process1;
        QProcess process2;
        process1.setStandardOutputProcess(&process2);
        process1.start(QString("find %1/%2 -type f -name \"*.ts\"")
                           .arg(ABSOLUTE_SHARE_PATH)
                           .arg(TRANSLATION_FILE_NAME));
        process1.waitForFinished(-1);
        process2.start(QString("xargs %1/lrelease").arg(QT_INSTALL_BINS));
        process2.waitForFinished(-1);
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)

#endif
    }

    setEffectEnabled(Qt::UI_AnimateCombo, false);
}

bool Application::notify(QObject *obj, QEvent *event)
{
    // if(this->property("test").toBool()){
    //     qDebug()<<obj<<event->type();
    //     if(obj){
    //         if(obj->metaObject()->className() == QString("QDefaultAnimationDriver")){
    //             QDefaultAnimationDriver *temp = static_cast<QDefaultAnimationDriver*>(obj);
    //             // temp->stopTimer();
    //             if(temp->parent()){
    //                 qDebug()<<"tttttt"<<temp->parent()->objectName()<<temp->parent()->metaObject()->className();
    //             }else{
    //                 qDebug()<<"tttttt"<<"temp is null";
    //             }
    //             QMetaObject::invokeMethod(temp, "stopTimer", Qt::AutoConnection);

    //         }
    //     }

    // }
    bool ret = true;
    bool isAcceptEvent = false;

    switch (static_cast<int>(event->type())) {
    case QEvent::MouseMove: {
#if defined(PLATFORM_COBOT_TP_ANDROID)
        QWidget *widget = dynamic_cast<QWidget *>(obj);

        if (!m_cmb.isNull()
            && m_cmb->m_dropDownList->isVisible()
            && m_cmb->property(LogicTreeItem_Editor).isValid()
            && obj->objectName() == "MainWidgetWindow") {

            event->accept();
            isAcceptEvent = true;
        }
#endif

        m_lockScreenTimer->start();
        break;
    }

    case QEvent::MouseButtonRelease: {

// #if defined(Q_OS_LINUX)

//         if (!m_cmb.isNull()
//             && m_cmb->m_dropDownList->isVisible()
//             && !QRect(m_cmb->mapToGlobal(QPoint(0, 0)), m_cmb->size())
//                    .contains(dynamic_cast<QMouseEvent *>(event)
//                                  ->globalPosition()
//                                  .toPoint())) {
//             m_cmb->hidePopup();
//         }

// #endif
        m_lockScreenTimer->start();

        break;
    }
    case QEvent::MouseTrackingChange:
        m_lockScreenTimer->start();
        break;
    case QEvent::StyleChange: {
        if (!m_widgetHasConnectOperation.contains(obj)) {
            if (obj->inherits("QAbstractButton")
                && obj->objectName() != "pbn_showLogFlowForm") {
                m_widgetHasConnectOperation.insert(obj);
                connectBtnOperationLog(static_cast<QAbstractButton *>(obj));
            } else if (obj->inherits("QGroupBox")) {
                m_widgetHasConnectOperation.insert(obj);
                connectGropuBoxOperationLog(static_cast<QGroupBox *>(obj));
            } else if (obj->inherits("QTableView")) {
                m_widgetHasConnectOperation.insert(obj);
                connectTableViewOpeartionLog(static_cast<QTableView *>(obj));
            } else if (obj->inherits("QLineEdit")
                       || obj->inherits("QTextEdit")
                       || obj->inherits("QPlainTextEdit")) {
                QWidget *wgt = static_cast<QWidget *>(obj);
                wgt->setFocusPolicy(Qt::ClickFocus);
            }
        }
        break;
    }
    case QEvent::MouseButtonPress: {
        m_lockScreenTimer->stop();


        break;
    }
    case QEvent::KeyPress:{
#ifdef PLATFORM_COBOT_TP_WINDOWS
        if (QKeyEvent *ev = dynamic_cast<QKeyEvent *>(event)) {
            if ((ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return)) {
                if ((ev->modifiers() & Qt::AltModifier) && qApp->primaryScreen()) {
                    int allX = qApp->primaryScreen()->availableGeometry().width();
                    int allY = qApp->primaryScreen()->availableGeometry().height();
                    if (QWidget *temp = dynamic_cast<QWidget *>(Instance::mainWidget())) {
                        int x = (allX - temp->width()) / 2;
                        int y = (allY - temp->height()) / 2;
                        temp->move(x < 0 ? 0 : x, y < 0 ? 0 : y);
                    }
                    Instance::common()->setProperty("currentScreen", QVariant::fromValue(qApp->primaryScreen()));
                } else {
                    if (VirtualKeyboard::instance())
                        VirtualKeyboard::instance()->hideInputPanel();
                }
            }

        }
#endif
        if (!isAllowPaste) {
            QWidget *widget = dynamic_cast<QWidget *>(obj);
            if (NULL != widget
                && widget->property("Imt").toInt() == Imt_LogicExpressionOnly) {
                event->accept();
                isAcceptEvent = true;
            }
        } else {
            if ((obj->inherits("QLineEdit")
                || obj->inherits("QTextEdit")
                || obj->inherits("QPlainTextEdit"))
                && obj->property(KEYBOARD_TYPE).isValid()
                && Imt_LogicExpressionOnly == obj->property(KEYBOARD_TYPE).toInt()) {

                QKeyEvent *ev = dynamic_cast<QKeyEvent *>(event);
                bool isCopy = ev->matches(QKeySequence::Copy);
                bool isPaste = ev->matches(QKeySequence::Paste);

                if (!isCopy && !isPaste) {
                    // 不处理非拷贝粘贴的事件
                    event->accept();
                    isAcceptEvent = true;
                    break;
                }

                if (isCopy) {
                    // 拷贝正常通知
                    break;
                }

                if (isPaste) {
                    // 粘贴前进行合法判断
                    bool isValid = judgeValidBeforePaste(obj);

                    if (!isValid) {
                        event->accept();
                        isAcceptEvent = true;
                        break;
                    }
                }
            }
        }
        break;
    }
#ifdef PLATFORM_COBOT_TP_WINDOWS
    case QEvent::ApplicationDeactivate: {
        if (VirtualKeyboard::instance())
            VirtualKeyboard::instance()->hideInputPanel();
        QMetaObject::invokeMethod(Instance::logForm(),
                                  "hideLogWidget",
                                  Qt::DirectConnection);
        break;
    }
    case QEvent::InputMethod:{
        QWidget *widget = dynamic_cast<QWidget *>(obj);
        if(widget){
            if (widget->property("Imt").toInt() == Imt_LogicExpressionOnly) {
                QInputMethodEvent *pOldEvent = static_cast<QInputMethodEvent *>(event);
                if (!pOldEvent->commitString().isEmpty()) {
                    QInputMethodEvent newEvent(pOldEvent->preeditString(),pOldEvent->attributes());
                    newEvent.setCommitString("");
                    QApplication::sendEvent(obj, &newEvent);
                    isAcceptEvent = true;
                    ret = true;
                }
            }
            else if(widget->property("Imt").toInt() == Imt_LatinOnly){
                QInputMethodEvent *pOldEvent = static_cast<QInputMethodEvent*>(event);
                QString commitStr = pOldEvent->commitString();

                if (!commitStr.isEmpty() && !isPureAscill(commitStr)) {
                    QInputMethodEvent newEvent(pOldEvent->preeditString(),pOldEvent->attributes());
                    newEvent.setCommitString("");
                    QApplication::sendEvent(obj, &newEvent);
                    isAcceptEvent = true;
                    ret = true;
                }
            }
        }
        break;
    }
    case QEvent::ContextMenu:{
        QWidget *widget = focusWidget();
        if(widget){
            if (widget->property("Imt").toInt() == Imt_LogicExpressionOnly) {
                isAcceptEvent = true;
                ret = true;
            }
        }
        break;
    }
#endif
    case QEvent::ScreenChangeInternal: {
        SimContainerForm *pSimContainerForm = dynamic_cast<SimContainerForm *>(obj);
        if (pSimContainerForm) {
            pSimContainerForm->updateViewport();
        }
        break;
    }
    default:
        break;
    }

    if (!isAcceptEvent)
        ret = QApplication::notify(obj, event);

    return ret;
}

bool Application::isRunning()
{
    return m_isRunning;
}

bool Application::checkWorkEnv()
{
#ifdef Q_OS_WIN
    if (StringUtils::isContainChinese(this->applicationDirPath())) {
        MessageBox::information(QObject::tr("Failed to run application, for application path contains chinese character."));
        return false;
    }
#endif
    return true;
}

void Application::initLocalConnection()
{
    QString serverName = "InoCobotTP";
#ifndef QT_NO_DEBUG
    if (serverName.endsWith("_debug"))
        serverName = serverName.remove("_debug");
#endif

#ifdef PLATFORM_COBOT_TP_MINGW_WIN
    m_singleMemory = new QSharedMemory(serverName);
    if (m_singleMemory->create(1)) {
        m_needDeleteMemory = true;
    }else{
        QMessageBox::information(0, "Warning",
                                 tr("%1 can not be started repeatedly")
                                     .arg(serverName));
        QFile file(QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, MINIDUMP_FILE_NAME, "StartRepeatly.txt"));
        if(file.open(QIODeviceBase::Text | QIODeviceBase::Append)){
            file.write((QDateTime::currentDateTime().toString("yyyy-mm-dd hh.mm.ss.zzz") + " shared memory\n").toStdString().c_str());
            file.close();
        }
        m_isRunning = true;
        return;
    }
#endif
    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (socket.waitForConnected(DEFAULT_LOCK_SCREEN_TIMEOUT_SEC)) {
        QMessageBox::information(0, "Warning",
                                 tr("%1 can not be started repeatedly")
                                     .arg(serverName));
        QFile file(QString("%1/%2/%3").arg(ABSOLUTE_SHARE_PATH, MINIDUMP_FILE_NAME, "StartRepeatly.txt"));
#ifdef INOCOBOTTP_MSVC_QT5
        if(file.open(QIODevice::Text | QIODevice::Append)){
#else
        if(file.open(QIODeviceBase::Text | QIODeviceBase::Append)){
#endif
            file.write((QDateTime::currentDateTime().toString("yyyy-mm-dd hh.mm.ss.zzz") + " loacl socket\n").toStdString().c_str());
            file.close();
        }
        m_isRunning = true;
    } else {
        QLocalServer *localServer = new QLocalServer(this);

        if (!localServer->listen(serverName)) {
            if (localServer->serverError()
                == QAbstractSocket::AddressInUseError) {
                QLocalServer::removeServer(serverName);
                localServer->listen(serverName);
            }
        }
    }

}

void Application::createWorkDir(QDir curDir, const QString &dirName)
{
    if (!curDir.cd(dirName))
        curDir.mkdir(dirName);
}

void Application::initProfile(
    const QString &key, const QVariant &value)
{
    if (Settings(m_robotType).value(key).toString().isEmpty())
        Settings(m_robotType).setValue(key, value);

    if (key.contains("Displays")) {  // replace resolution if exist
        Settings(m_robotType).setValue(key, value);
    }
}

void Application::copyQrcToGenericDataLocation()
{
    // copyQrcToGenericDataLocation(":/share", "/../", 1);
    // copyQrcToGenericDataLocation(":/config", "", strlen(":/config"));
}

void Application::copyQrcToGenericDataLocation(
    const QString &src, const QString &destTail, int midIdx, bool jumpLanguageFile)
{
    qDebug() << "start copy folder : " << src << destTail;
    if (!QFile::exists(src)) {
        qDebug() << "src folder isn't exist: " << src;
    }
    QString storagePath;
#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
    storagePath = QDir::cleanPath(APPLICATION_DIR_PATH) + destTail;
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
    // 获取应用的私有目录
    storagePath = QStandardPaths::writableLocation(
        QStandardPaths::GenericDataLocation);
#endif
    qDebug() << "storagePath : " << storagePath;

    // Traversing the share directory
    QString configPath = src;
    QDirIterator it(configPath, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        // get file relative path
        QString relativePath = it.filePath().mid(midIdx);
        // mkdir
        if (it.fileInfo().isDir()) {
            QDir storageSubDir(storagePath + relativePath);
            if (!storageSubDir.exists()) {
                qDebug() << "mkdir : " << storageSubDir.absolutePath();
                storageSubDir.mkpath(".");
            }
        }
        if (relativePath.endsWith(".properties"))
            continue;
        // copy file
        QString destFilePath = storagePath + relativePath;
        qDebug() << "destFilePath:" << src << relativePath << destFilePath;
        if (it.fileInfo().isFile()
            && FileUtils::getFilePathMd5(it.filePath())
                   != FileUtils::getFilePathMd5(destFilePath)) {
            if (it.filePath().contains("/share/teachpendant/translations")
                || it.filePath().contains("/share/studio/Language")) {
                if (jumpLanguageFile) {
                    qDebug() << "jump";
                    continue;
                } else {
                    bool isInFactoryState = false;
                    DatabaseLocal::getLanguageIsInFactoryState(isInFactoryState);
                    qDebug() << "isInFactoryState" << isInFactoryState;
                    if (isInFactoryState || !QFile::exists(destFilePath)) {
                        FileUtils::copyFile(it.filePath(), destFilePath);
                    }
                }
            } else {
                qDebug() << "copyFile:" << src << it.filePath() << destFilePath;
                FileUtils::delFile(destFilePath);
                FileUtils::copyFile(it.filePath(), destFilePath);
            }
            if (destFilePath.contains(AUTHORITY_FILE)) {
                FileUtils::copyFile(it.filePath(),
                                    destFilePath.replace(SETTINGS_FILE_NAME, AUTHORITY_FILE_NAME));
            }
        }
    }
}

void Application::updateLockScreenTime()
{
    if (DatabaseLocal::getLockScreenTime(m_lockScreenTimeoutSec)) {
        m_lockScreenTimer->setInterval(
            m_lockScreenTimeoutSec == 0 ?
                DEFAULT_LOCK_SCREEN_TIMEOUT_SEC * 1000 :
                m_lockScreenTimeoutSec * 1000);
        m_lockScreenTimer->start();
    }
}

void Application::connectBtnOperationLog(QAbstractButton *btn)
{
    if (btn == 0)
        return;
    btn->setFocusPolicy(Qt::ClickFocus);
    connect(btn,
            &QAbstractButton::clicked,
            btn,
            [=](bool checked) {
                QString indexButton = btn->property(InfoFlow_RbnIsWidgetIndex).toString();
                if (!indexButton.isEmpty())
                    return;
                QString state = " -> ";
                if (!indexButton.isEmpty()) {
                    state += QObject::tr("Open Page");
                } else if (btn->inherits("QRadioButton")) {
                    state += checked ? QObject::tr("Selected") : QObject::tr("Unselected");
                } else if (btn->isCheckable()) {
                    state += checked ? QObject::tr("ON") : QObject::tr("OFF");
                } else {
                    state += QObject::tr("Clicked");
                }
                QString text = btn->property(InfoFlow_HighLevelOperationLog).toString();
                if (text.isEmpty()) {
                    text = btn->text();
                    if (text.isEmpty()) {
                        text = btn->property(InfoFlow_LowLevelOperationLog).toString();
                        if (text.isEmpty())
                            text = btn->objectName();
                    }
                }
                state = text + state;
                getParentInfoFlowMsg(btn->parent(), state);
                CobotLog::instance()->printOperation(state);
            });
}

void Application::connectGropuBoxOperationLog(QGroupBox *box)
{
    if (box == 0)
        return;
    connect(box,
            &QGroupBox::clicked,
            this,
            [=](bool checked) {
                if (!box->isCheckable()) {
                    return;
                }
                QString indexButton = box->property(InfoFlow_RbnIsWidgetIndex).toString();
                if (!indexButton.isEmpty())
                    return;
                QString state = " -> " + (checked ? QObject::tr("Selected") : QObject::tr("Unselected"));
                QString text = box->property(InfoFlow_HighLevelOperationLog).toString();
                if (text.isEmpty()) {
                    text = box->title();
                    if (text.isEmpty()) {
                        text = box->property(InfoFlow_LowLevelOperationLog).toString();
                        if (text.isEmpty())
                            text = box->objectName();
                    }
                }
                state = text + state;
                getParentInfoFlowMsg(box->parent(), state);
                CobotLog::instance()->printOperation(state);
            });
}

void Application::connectTableViewOpeartionLog(QTableView *tableView)
{
    connect(tableView,
            &QTableView::pressed,
            this,
            [=](const QModelIndex &index) {
                QString name;
                int count = tableView->model()->columnCount();
                for (int i = 0; i < count; ++i) {
                    QModelIndex colIndex = tableView->model()->index(index.row(), i);
                    bool ok = false;
                    QVariant data = tableView->model()->data(colIndex, Qt::DisplayRole);
                    data.toDouble(&ok);
                    name = data.toString();
                    if (ok) {
                        continue;
                    } else {
                        break;
                    }
                }
                if (name.isEmpty())
                    return;
                QString state = name + InfoFlow_Split + QObject::tr("Clicked");
                getParentInfoFlowMsg(tableView->parent(), state);
                CobotLog::instance()->printOperation(state);
            });
}

void Application::getParentInfoFlowMsg(QObject *parent, QString &state)
{
    while (parent != 0) {
        QTabWidget *table = qobject_cast<QTabWidget *>(parent);
        QGroupBox *box = qobject_cast<QGroupBox *>(parent);
        if (table != 0) {
            state = table->tabText(table->currentIndex()) + InfoFlow_Split + state;
        } else if (box != 0) {
            state = box->title() + InfoFlow_Split + state;
        } else {
            QString temp = parent->property(InfoFlow_Property).toString();
            if (!temp.isEmpty()) {
                state = temp + InfoFlow_Split + state;
            }
        }
        parent = parent->parent();
    }
}

void Application::requestPermission(const QString &permission)
{
#if defined(Q_OS_ANDROID)
    if (QtAndroidPrivate::checkPermission(permission).result()
        != QtAndroidPrivate::Authorized) {
        QtAndroidPrivate::requestPermission(permission).waitForFinished();

        qDebug() << (QString("request permission %1, result:%2").arg(permission, QString::number(QtAndroidPrivate::checkPermission(permission).result())));
    }
#endif
}

bool Application::isPureAscill(const QString &str)
{
    for (const QChar &c : str) {
        if (c.unicode() > 127){
            return false;
        }
    }
    return true;
}

bool Application::judgeValidBeforePaste(QObject *obj)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString pastedText = clipboard->text();
    qDebug() << "pastedText" << pastedText;

    bool isValid = true;
    // QMetaObject::invokeMethod(
    //     Instance::getParseExpressions(),
    //     "xmlExpIsValid",
    //     Qt::DirectConnection,
    //     Q_RETURN_ARG(bool, isValid),
    //     Q_ARG(const QString, pastedText),
    //     Q_ARG(bool, false));

    // if (!isValid) {
    //     event->accept();
    //     isAcceptEvent = true;
    //     SHOW_ERROR(tr("The pasted text [%1] is invalid").arg(pastedText));
    //     break;
    // }

    QString currentText;
    QString selectedText;
    int curPos = 0;
    int startSelectedPos = 0;

    if (obj->inherits("QLineEdit")) {
        QLineEdit *edit = dynamic_cast<QLineEdit *>(obj);
        currentText = edit->text();
        curPos = edit->cursorPosition();
        selectedText = edit->selectedText();
        startSelectedPos = edit->selectionStart();
    } else if (obj->inherits("QTextEdit")) {
        QTextEdit *edit = dynamic_cast<QTextEdit *>(obj);
        currentText = edit->toPlainText();
        auto cursor = edit->textCursor();
        curPos = cursor.position();
        selectedText = cursor.selectedText();
        startSelectedPos = cursor.selectionStart();
    } else if (obj->inherits("QPlainTextEdit")) {
        QPlainTextEdit *edit = dynamic_cast<QPlainTextEdit *>(obj);
        currentText = edit->toPlainText();
        auto cursor = edit->textCursor();
        curPos = cursor.position();
        selectedText = cursor.selectedText();
        startSelectedPos = cursor.selectionStart();
    } else {
        SHOW_ERROR(tr("Input widget is invalid."));
        return false;
    }

    QString textAfterPasted = currentText;
    if (selectedText.isEmpty()) {
        textAfterPasted.insert(curPos, pastedText);
    } else {
        // textAfterPasted.replace(selectedText, pastedText);
        textAfterPasted.replace(startSelectedPos, selectedText.length(), pastedText);
    }

    QString errorMsg;
    QMetaObject::invokeMethod(
        Instance::getParseExpressions(),
        "xmlExpIsValidWithError",
        Qt::DirectConnection,
        Q_RETURN_ARG(bool, isValid),
        Q_ARG(const QString, textAfterPasted),
        Q_ARG(bool, false),
        Q_ARG(QString&, errorMsg));

    if (!isValid) {
        SHOW_ERROR(tr("The expression after being pasted [%1] is invalid.\n").arg(textAfterPasted)
                   + tr(errorMsg.toUtf8().constData()));
        return false;
    }

    return true;
}
