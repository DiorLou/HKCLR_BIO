#pragma once

#include "pluginspec.h"
#include "iplugin.h"

#include <QJsonObject>
#include <QObject>
#include <QPluginLoader>
#include <QRegularExpression>
#include <QStringList>
#include <QVector>
#include <QXmlStreamReader>

namespace PluginEngine
{

class IPlugin;
class PluginManager;

namespace Internal
{

class PLUGINENGINE_EXPORT PluginSpecPrivate : public QObject
{
    Q_OBJECT

public:
    PluginSpecPrivate(PluginSpec *spec);

    bool read(const QString &fileName);
    bool provides(const QString &pluginName, const QString &version) const;
    bool resolveDependencies(const QList<PluginSpec *> &specs);
    bool loadLibrary();
    bool initializePlugin();
    bool initializeExtensions();
    bool delayedInitialize();
    IPlugin::ShutdownFlag stop();
    void kill();

    void setEnabledBySettings(bool value);
    void setEnabledByDefault(bool value);
    void setForceEnabled(bool value);
    void setForceDisabled(bool value);

    QPluginLoader loader;

    QString name;
    QString version;
    QString compatVersion;
    bool required;
    bool experimental;
    bool enabledByDefault;
    QString vendor;
    QString copyright;
    QString license;
    QString description;
    QString url;
    QString category;
    QRegularExpression platformSpecification;
    QVector<PluginDependency> dependencies;  // 从配置文件读取的插件依赖库
    bool enabledBySettings;
    bool enabledIndirectly;
    bool forceEnabled;
    bool forceDisabled;

    QString location;
    QString filePath;
    QStringList arguments;

    // 当前插件库依赖的其他插件配置信息
    QHash<PluginDependency, PluginSpec *> dependencySpecs;
    PluginSpec::PluginArgumentDescriptions argumentDescriptions;
    IPlugin *plugin;

    PluginSpec::State state;
    bool hasError;
    QString errorString;

    static bool isValidVersion(const QString &version);
    static int versionCompare(const QString &version1, const QString &version2);

    void enableDependenciesIndirectly();

    bool readMetaData(const QJsonObject &metaData);

private:
    PluginSpec *q;

    bool reportError(const QString &err);
    static QRegularExpression &versionRegExp();
};

}  // namespace Internal
}  // namespace PluginEngine
