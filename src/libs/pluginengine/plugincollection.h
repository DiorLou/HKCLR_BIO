#pragma once

#include "pluginengine_global.h"

#include <QList>
#include <QString>

namespace PluginEngine
{
class PluginSpec;

class PLUGINENGINE_EXPORT PluginCollection
{
public:
    explicit PluginCollection(const QString &name);
    ~PluginCollection();

    QString name() const;
    void addPlugin(PluginSpec *spec);
    void removePlugin(PluginSpec *spec);
    QList<PluginSpec *> plugins() const;

private:
    QString m_name;
    QList<PluginSpec *> m_plugins;
};

}  // namespace PluginEngine
