#pragma once

#include "pluginengine_global.h"

#include <QObject>
#include <QtPlugin>

class LogicTreeItem;
class AbsCondInfo;

namespace PluginEngine
{

namespace Internal
{
class IPluginPrivate;
class PluginSpecPrivate;
}  // namespace Internal

class PluginManager;
class PluginSpec;

class PLUGINENGINE_EXPORT IPlugin : public QObject
{
    Q_OBJECT

public:
    enum ShutdownFlag {
        SynchronousShutdown,
        AsynchronousShutdown
    };

    IPlugin();
    virtual ~IPlugin();

    virtual bool initialize(
        const QStringList &arguments, QString *errorString)
        = 0;
    virtual void extensionsInitialized() = 0;
    virtual bool delayedInitialize()
    {
        return true;
    }
    virtual ShutdownFlag aboutToShutdown()
    {
        return SynchronousShutdown;
    }
    virtual QObject *remoteCommand(
        const QStringList & /* options */,
        const QString & /* workingDirectory */,
        const QStringList & /* arguments */)
    {
        return 0;
    }
    virtual QList<QObject *> createTestObjects() const;

    PluginSpec *pluginSpec() const;

    void addObject(QObject *obj);
    void addAutoReleasedObject(QObject *obj);
    void removeObject(QObject *obj);

    // plugin common interface
    virtual bool pluginCommonInterface(
        const QString &funcName,
        const QList<QVariant> &params, QList<QVariant> &ret)
    {
        Q_UNUSED(funcName);
        Q_UNUSED(params);
        Q_UNUSED(ret);
        return true;
    }

signals:
    void asynchronousShutdownFinished();

private:
    Internal::IPluginPrivate *d;

    friend class Internal::PluginSpecPrivate;
};

}  // namespace PluginEngine
