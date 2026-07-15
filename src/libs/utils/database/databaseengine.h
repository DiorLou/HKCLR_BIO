#pragma once

// C++ lib import
#include <functional>

// Qt lib import
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "database_global.h"
#define PropertyDeclare(Type, Name, setName, ...) \
private:                                          \
    Type m_##Name __VA_ARGS__;                    \
                                                  \
public:                                           \
    inline const Type &Name(void) const           \
    {                                             \
        return m_##Name;                          \
    }                                             \
    inline void setName(const Type &Name)         \
    {                                             \
        m_##Name = Name;                          \
    }                                             \
                                                  \
private:

namespace DatabaseEngine
{

enum DatabaseModeEnum { DatabaseNameMode,
                        DatabaseHostMode };

enum QueryMode { QueryAutoMode,
                 QueryMultiMode,
                 QuerySingleMode };

class DATABASE_EXPORT DatabaseSettings
{
private:
    PropertyDeclare(DatabaseModeEnum, databaseMode, setDatabaseMode)

    PropertyDeclare(QString, databaseType, setDatabaseType)
    PropertyDeclare(QString, connectionName, setConnectionName)

    // File mode
    PropertyDeclare(QString, nameModeName, setNameModeName)

    // Host mode
    PropertyDeclare(QString, hostModeHostName, setHostModeHostName)
    PropertyDeclare(QString, hostModeDatabaseName, setHostModeDatabaseName)
    PropertyDeclare(QString, hostModeUserName, setHostModeUserName)
    PropertyDeclare(QString, hostModePassword, setHostModePassword)

    DatabaseSettings(const DatabaseModeEnum &databastMode,
                    const QString &databaseType,
                    const QString &connectionName);

public:
    DatabaseSettings(const QString &databaseType,
                     const QString &connectionName,
                     const QString &nameModeName);

    DatabaseSettings(const QString &databaseType,
                     const QString &connectionName,
                     const QString &hostModeHostName,
                     const QString &hostModeDatabaseName,
                     const QString &hostModeUserName,
                     const QString &hostModePassword);
};

class DATABASE_EXPORT ConnectSettings
{
private:
    PropertyDeclare(int, maxOpenTime, setMaxOpenTime)
        PropertyDeclare(QueryMode, queryMode, setQueryMode)
            PropertyDeclare(int, minWaitTime, setMinWaitTime)

                public : ConnectSettings(const int &maxOpenTime = 60 * 1000,
                                         const QueryMode &queryMode = QueryAutoMode,
                                         const int &minWaitTime = -1);
};

class DATABASE_EXPORT SqlQuery : public QSqlQuery
{
public:
    explicit SqlQuery(QSqlDatabase db);

    bool exec(const QString &query, bool isPromptError = true);
};

class DATABASE_EXPORT Query
{
private:
    SqlQuery *m_query;
    QRecursiveMutex *m_mutex = NULL;

public:
    Query(QSqlDatabase &dataBase, QRecursiveMutex *mutex = NULL);
    Query(Query &&other);
    ~Query(void);

    inline SqlQuery *operator->(void)
    {
        return m_query;
    }

    inline SqlQuery *operator*(void)
    {
        return m_query;
    }

    SqlQuery *takeQuery(void);

    QRecursiveMutex *takeMutex(void);
};

class DATABASE_EXPORT ConnectNode : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase *m_database = NULL;
    QString m_connectionName;

    DatabaseSettings m_dataBaseSettings;
    ConnectSettings m_connectSettings;

    QTimer *m_autoClose = NULL;
    QRecursiveMutex *m_mutex = NULL;

public:
    ConnectNode(const DatabaseSettings &dataBaseSettings,
                const ConnectSettings &connectSettings);

    ~ConnectNode(void);

public:
    Query query(void);

    QSqlDatabase *database()
    {
        return m_database;
    }

public slots:
    bool addDataBase(void);

    void removeDataBase(void);

    bool open(void);

    void close(void);

signals:
    void controlStartAutoClose(void);

    void controlStopAutoClose(void);
};

class DATABASE_EXPORT Control : public QObject
{
    Q_OBJECT
public:
    Control(const DatabaseSettings &databaseSettings,
            const ConnectSettings &connectSettings = ConnectSettings());
    Control(const Control &) = delete;

    ~Control(void);

    void removeAll(void);
    Query query(void);
    bool exec(const QString &query, bool isPromptError = true);

private:
    void insert(const qint64 &key);
    QSqlDatabase *database();

    void backupModifiedDatabaseFile();

    DatabaseSettings m_databaseSettings;
    ConnectSettings m_connectSettings;

    QMap<qint64, ConnectNode *> m_node;

    QMutex m_mutex;
    QElapsedTimer *m_wait = NULL;
};

}  // namespace DatabaseEngine
