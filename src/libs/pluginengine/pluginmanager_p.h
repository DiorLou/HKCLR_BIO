#pragma once

#include "pluginspec.h"

#include <algorithm.h>

#include <QSet>
#include <QStringList>
#include <QObject>
#include <QScopedPointer>
#include <QReadWriteLock>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
class QTime;
class QTimer;
class QSettings;
class QEventLoop;
QT_END_NAMESPACE

namespace PluginEngine
{

class PluginManager;
class PluginCollection;

namespace Internal
{

class PluginSpecPrivate;

class PLUGINENGINE_EXPORT PluginManagerPrivate : QObject
{
    Q_OBJECT
public:
    PluginManagerPrivate(PluginManager *pluginManager);
    virtual ~PluginManagerPrivate();

    // Object pool operations
    void addObject(QObject *obj);
    void removeObject(QObject *obj);

    // Plugin operations
    void loadPlugins();
    void shutdown();
    void setPluginPaths(const QStringList &paths);
    QList<PluginSpec *> loadQueue();
    void loadPlugin(PluginSpec *spec, PluginSpec::State destState);
    void resolveDependencies();
    void enableOnlyTestedSpecs();
    void initProfiling();
    void profilingSummary() const;
    void profilingReport(const char *what, const PluginSpec *spec = 0);
    void setSettings(QSettings *settings);
    void setGlobalSettings(QSettings *settings);
    void readSettings();
    void writeSettings();

    class TestSpec
    {
    public:
        TestSpec(PluginSpec *pluginSpec, const QStringList &testFunctionsOrObjects = QStringList()) :
            pluginSpec(pluginSpec), testFunctionsOrObjects(testFunctionsOrObjects)
        {
        }
        PluginSpec *pluginSpec;
        QStringList testFunctionsOrObjects;
    };

    bool containsTestSpec(PluginSpec *pluginSpec) const
    {
        return Utils::contains(testSpecs, [pluginSpec](const TestSpec &s) { return s.pluginSpec == pluginSpec; });
    }

    void removeTestSpec(PluginSpec *pluginSpec)
    {
        testSpecs = Utils::filtered(testSpecs, [pluginSpec](const TestSpec &s) { return s.pluginSpec != pluginSpec; });
    }

    QHash<QString, PluginCollection *> pluginCategories;
    QList<PluginSpec *> pluginSpecs;  // 全部插件库的配置信息类
    QList<TestSpec> testSpecs;
    QStringList pluginPaths;
    QString pluginIID;
    QList<QObject *> allObjects;         // ### make this a QList<QPointer<QObject> > > ?
    QStringList defaultDisabledPlugins;  // Plugins/Ignored from install settings
    QStringList defaultEnabledPlugins;   // Plugins/ForceEnabled from install settings
    QStringList disabledPlugins;
    QStringList forceEnabledPlugins;
    // delayed initialization
    QTimer *delayedInitializeTimer;
    QList<PluginSpec *> delayedInitializeQueue;
    QList<PluginSpec *> m_registerAddXmlConfigToActiveProjectWhenSaveProjectQueue;
    // ansynchronous shutdown
    QList<PluginSpec *> asynchronousPlugins;  // plugins that have requested async shutdown
    QEventLoop *shutdownEventLoop;            // used for async shutdown

    QStringList arguments;
    QScopedPointer<QElapsedTimer> m_profileTimer;
    QHash<const PluginSpec *, int> m_profileTotal;
    int m_profileElapsedMS;
    unsigned m_profilingVerbosity;
    QSettings *settings;
    QSettings *globalSettings;

    // Look in argument descriptions of the specs for the option.
    PluginSpec *pluginForOption(const QString &option, bool *requiresArgument) const;
    PluginSpec *pluginByName(const QString &name) const;

    // used by tests
    static PluginSpec *createSpec();
    static PluginSpecPrivate *privateSpec(PluginSpec *spec);

    mutable QReadWriteLock m_lock;

    bool m_isInitializationDone = false;

    bool registerDelayInit(PluginSpec *spec);
    bool registerAddXmlConfigToActiveProjectWhenSaveProject(PluginSpec *spec);

    bool registerConditionNameToPlugin(const QString &name, IPlugin *spec);
    QHash<QString, IPlugin*> hashConditionTypeToPlugin;
    QHash<QString, IPlugin*> hashPluginNameToPluginAddress;
private slots:
    void nextDelayedInitialize();
    void asyncShutdownFinished();

private:
    PluginCollection *defaultCollection = nullptr;
    PluginManager *q;
    void readPluginPaths();
    bool loadQueue(PluginSpec *spec,
                   QList<PluginSpec *> &queue,
                   QList<PluginSpec *> &circularityCheckQueue);
    void stopAll();
    void deleteAll();
    bool isAllowResigterDelayInit = false;
};

}  // namespace Internal
}  // namespace PluginEngine
