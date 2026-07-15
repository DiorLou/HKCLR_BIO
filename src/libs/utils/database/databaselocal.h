#pragma once

#include <QObject>
#include "databaseengine.h"
#include "database_global.h"
using namespace DatabaseEngine;

class User;
class UserAuthority;
class ToolParam;
class RoadPoint;
class DataAccess;
class QSqlQuery;
class ConfigInfo;

class DATABASE_EXPORT DatabaseLocal
{
public:
    static DatabaseLocal *instance();

    DatabaseLocal();
    ~DatabaseLocal();
    bool m_initDatabaseComplete;
    static bool checkDatabase();

    static bool getConfigInfo(
        ConfigInfo &configInfo, QStringList &disabledPlugins);
    static bool setLanguage(const QString &language);

    // system config
    static bool getToolParam(ToolParam &toolParam);
    static bool setToolName(const QString &toolName);

    static bool getLockScreenEnabled(bool &enabled);
    static bool setLockScreenEnabled(const bool enabled);

    static bool getLockScreenTime(int &sec);
    static bool setLockScreenTime(const int sec);

    static bool getEnableDrawTrack(bool &isDrawTrack);
    static bool setEnableDrawTrack(const bool isDrawTrack);

    static bool getEnablePromptForDisclaimer(
        bool &enablePromptForDisclaimer);
    static bool setEnablePromptForDisclaimer(
        const bool enablePromptForDisclaimer);

    static bool getTrackDuration(int &trackDuration);
    static bool setTrackDuration(const int trackDuration);

    static bool getEnableLineNumbers(bool &isDisplayLineNumbers);
    static bool setEnableLineNumbers(const bool isDisplayLineNumbers);

    static bool getEnableModePasswd(bool &isDisplayModePasswd);
    static bool setEnableModePasswd(const bool isDisplayModePasswd);

    static bool getDisplayMove2ReadyPoint(bool &isDisplayMove2ReadyPoint);
    static bool setDisplayMove2ReadyPoint(const bool isDisplayMove2ReadyPoint);

    static bool getAutoSaveLogicTreeItem(bool &isAutoSaveLogicTreeItem);
    static bool setAutoSaveLogicTreeItem(const bool isAutoSaveLogicTreeItem);

    static bool getSimTeachType(QString &value);
    static bool setSimTeachType(const QString &value);

    static bool getAntiShake(QString &value);
    static bool setAntiShake(const QString &value);

    static bool getDeveloperModeEnable(bool &isEnabled);
    static bool setDeveloperModeEnable(bool isEnabled);

    static bool getLanguageIsInFactoryState(bool &isInFactoryState);
    static bool setLanguageIsInFactoryState(bool isEnabled);

    static bool getItemDrop2PlusOperation(QString &value);
    static bool setItemDrop2PlusOperation(const QString &value);

    static bool getItemDrop2ConditionOperation(QString &value);
    static bool setItemDrop2ConditionOperation(const QString &value);

private:
    Control *m_configInfoDb;
    Control *m_systemInfoDb;

    static bool isTableExist(
        Control *controlDb, const QString &tableName,
        QString sqlFileName = QString());

    static void dbCompatibleOperation();
};
