#pragma once
#include <QApplication>
#include <QScreen>
#include <QDir>
#include <QMetaEnum>
#include <QStandardPaths>
#include <QSysInfo>
#include <QMetaType>
const char SHARE_FILE_NAME[] = "share";
const char DATABASE_FILE_NAME[] = "database";
const char CONTROLLER_PROJECT_FOLDER[] = "TeachProgram";
const char PROJECT_FILE_NAME[] = "project";
const char TEMPLATE_FILE_NAME[] = "template";
const char SCRIPT_FILE_NAME[] = "script";
const char RESOURCES_FILE_NAME[] = "resources";
const char SIMULATION_FILE_NAME[] = "simulation";
const char PLUGIN_FILE_NAME[] = "plugins";
const char TRANSLATION_FILE_NAME[] = "translations";
const char LOG_FILE_NAME[] = "log";
const char BACKUP_FILE_NAME[] = "backup";
const char SETTINGS_FILE_NAME[] = "settings";
const char AUTHORITY_FILE_NAME[] = "authority";
const char MINIDUMP_FILE_NAME[] = "minidump";
const char MANUAL_FILE_NAME[] = "manual";
const char ROBOTPARAMS_FILE_NAME[] = "RobotParams";

const QString DB_CONFIG_INFO = "config_info.db";
const QString DB_SYSTEM_INFO = "system_info.db";
const QString AUTHORITY_FILE = "authority.xml";

#define LOCAL_PROJECT_DIR_PATH \
QDir::cleanPath(ABSOLUTE_SHARE_PATH + '/' + PROJECT_FILE_NAME)

#define LOCAL_PROJECT_PATH(projectName) \
    QDir::cleanPath(LOCAL_PROJECT_DIR_PATH + '/' + projectName)

#define LOCAL_PROJECT_FILE_PATH(projectName) \
    QDir::cleanPath(LOCAL_PROJECT_PATH(projectName) + '/' + projectName + PROJECT_FILE_NAME_SUFFIX)

#define LOCAL_PROJECT_MAIN_XML_FILE(projectName) \
    QDir::cleanPath(LOCAL_PROJECT_PATH(projectName) + "/main" + XML_FILE_NAME_SUFFIX)

#define LOCAL_PROJECT_MAIN_SCRIPT_FILE(projectName) \
    QDir::cleanPath(LOCAL_PROJECT_PATH(projectName) + "/main" + SCRIPT_FILE_NAME_SUFFIX)

#define CPU_ARCHITECTURE QSysInfo::currentCpuArchitecture()

#define APPLICATION_DIR_PATH QApplication::applicationDirPath()

#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
    #define ABSOLUTE_SHARE_PATH \
    QDir::cleanPath(APPLICATION_DIR_PATH + '/' + RELATIVE_SHARE_PATH)
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
#define ABSOLUTE_SHARE_PATH                                  \
    QDir::cleanPath(QStandardPaths::writableLocation(        \
                        QStandardPaths::GenericDataLocation) \
                    + "/share/" + COBOT_TP_ID)

#endif

#if defined(Q_OS_WIN) || (defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID))
    #define ABSOLUTE_DATA_PATH qApp->applicationDirPath()
#elif defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
    #define ABSOLUTE_DATA_PATH                            \
    QDir::cleanPath(QStandardPaths::writableLocation( \
        QStandardPaths::GenericDataLocation)) + "/share/studio"

#endif

#define ABSOLUTE_SDK_SHARE_PATH \
    QDir::cleanPath(APPLICATION_DIR_PATH + '/' + RELATIVE_SDK_SHARE_PATH)

#define ABSOLUTE_PLUGIN_SHARE_PATH \
    QDir::cleanPath(APPLICATION_DIR_PATH + '/' + RELATIVE_PLUGIN_PATH)

#define ABSOLUTE_SDK_SHARE_PATH_BACKUP_WRITEPROJECT(time) \
    QDir::cleanPath(APPLICATION_DIR_PATH + '/' + RELATIVE_SHARE_PATH + '/' + "backup_writeProject" + '/' + time)

#define ABSOLUTE_DEP_LIB_PATH \
    QDir::cleanPath(QString("%1/plugins").arg(RELATIVE_DEP_LIB_PATH))

#define CONTROLLER_TMP_DIR_PATH \
    QDir::cleanPath(ABSOLUTE_DATA_PATH + '/' + TMP_FILE_NAME)

#define CONTROLLER_PROJECT_PATH(projectName) \
    QDir::cleanPath(CONTROLLER_PROJECT_DIR_PATH + '/' + projectName)

#define CONTROLLER_PROJECT_FILE_PATH(projectName) \
    QDir::cleanPath(CONTROLLER_PROJECT_PATH(projectName) + '/' + projectName + PROJECT_FILE_NAME_SUFFIX)

#define CONTROLLER_PROJECT_DIR_PATH \
    QDir::cleanPath(ABSOLUTE_DATA_PATH + '/' + CONTROLLER_PROJECT_FOLDER)

#define CONTROLLER_AUTHORITY_PATH \
    QDir::cleanPath(ABSOLUTE_SHARE_PATH + '/' + AUTHORITY_FILE_NAME);

#define BACKUP_AUTHORITY_PATH \
QDir::cleanPath(ABSOLUTE_SHARE_PATH + '/' + BACKUP_FILE_NAME);
