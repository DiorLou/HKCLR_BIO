#pragma once

#include "pluginengine_global.h"

#include <QObject>
#include <QStringList>
#include <QReadWriteLock>
#include <QHash>
QT_BEGIN_NAMESPACE
class QTextStream;
class QSettings;
QT_END_NAMESPACE

class AbsCondInfo;

namespace PluginEngine
{
class PluginCollection;
class IPlugin;
class PluginSpec;

namespace Internal
{
class PluginManagerPrivate;
}

class PLUGINENGINE_EXPORT PluginManager : public QObject
{
    Q_OBJECT

public:
    static PluginManager *instance();

    PluginManager();
    ~PluginManager();

    // Object pool operations
    static void addObject(QObject *obj);
    static void removeObject(QObject *obj);
    static QList<QObject *> allObjects();
    static QReadWriteLock *listLock();
    template <typename T>
    static QList<T *> getObjects()
    {
        QReadLocker lock(listLock());
        QList<T *> results;
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            T *result = qobject_cast<T *>(obj);
            if (result)
                results += result;
        }
        return results;
    }
    template <typename T, typename Predicate>
    static QList<T *> getObjects(Predicate predicate)
    {
        QReadLocker lock(listLock());
        QList<T *> results;
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            T *result = qobject_cast<T *>(obj);
            if (result && predicate(result))
                results += result;
        }
        return results;
    }
    template <typename T>
    static T *getObject()
    {
        QReadLocker lock(listLock());
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                return result;
        }
        return 0;
    }
    template <typename T, typename Predicate>
    static T *getObject(Predicate predicate)
    {
        QReadLocker lock(listLock());
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                if (predicate(result))
                    return result;
        }
        return 0;
    }
    //请使用getPluginAddressByConditionType getPluginAddressByPluginName替换getPluginAddressByPluginName
    static QObject *getObjectByName(const QString &name);
    static QObject *getObjectByClassName(const QString &className);

    // Plugin operations
    static QList<PluginSpec *> loadQueue();
    static void loadPlugins();
    static QStringList pluginPaths();
    static void setPluginPaths(const QStringList &paths);
    static QString pluginIID();
    static void setPluginIID(const QString &iid);
    static QList<PluginSpec *> plugins();
    static QHash<QString, PluginCollection *> pluginCollections();
    static bool hasError();
    static QSet<PluginSpec *> pluginsRequiringPlugin(PluginSpec *spec);
    static QSet<PluginSpec *> pluginsRequiredByPlugin(PluginSpec *spec);
    static QStringList pluginNames();
    static PluginSpec *pluginByName(const QString &pluginName);

    // Settings
    static void setSettings(QSettings *settings);
    static QSettings *settings();
    static void setGlobalSettings(QSettings *settings);
    static QSettings *globalSettings();
    static void writeSettings();

    // command line arguments
    static QStringList arguments();
    static bool parseOptions(const QStringList &args,
                             const QMap<QString, bool> &appOptions,
                             QMap<QString, QString> *foundAppOptions,
                             QString *errorString);
    static void formatOptions(QTextStream &str, int optionIndentation, int descriptionIndentation);
    static void formatPluginOptions(QTextStream &str, int optionIndentation, int descriptionIndentation);
    static void formatPluginVersions(QTextStream &str);

    static QString serializedArguments();

    static bool testRunRequested();

    static void profilingReport(const char *what, const PluginSpec *spec = 0);

    static QString platformName();

    static bool isInitializationDone();

    static bool registerDelayInit(PluginSpec *spec);

    static bool registerAddXmlConfigToActiveProjectWhenSaveProject(PluginSpec *spec);
    static QList<PluginSpec *> getRegisterAddXmlConfigToActiveProjectWhenSaveProject();

    static bool registerConditionTypeToPlugin(const QString &type, IPlugin *plugin);
    static QHash<QString, IPlugin*> gethashConditionTypeToPluginAddress();

    static IPlugin * getPluginAddressByConditionType(const QString &type);
    static IPlugin * getPluginAddressByPluginName(const QString &name);

signals:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

    void pluginsChanged();
    void initializationDone();
    void testsFinished(int failedTests);

public slots:
    void remoteArguments(const QString &serializedArguments, QObject *socket);
    void shutdown();

    friend class Internal::PluginManagerPrivate;
};

}  // namespace PluginEngine
