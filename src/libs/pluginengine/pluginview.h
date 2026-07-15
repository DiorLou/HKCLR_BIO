#pragma once

#include "pluginengine_global.h"

#include <QWidget>
#include <QSet>
#include <QHash>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
QT_END_NAMESPACE

namespace Utils
{
class TreeItem;
class TreeModel;
class TreeView;
}  // namespace Utils

namespace PluginEngine
{

class PluginManager;
class PluginSpec;

namespace Internal
{
class PluginItem;
class CollectionItem;
}  // namespace Internal

class PLUGINENGINE_EXPORT PluginView : public QWidget
{
    Q_OBJECT

public:
    explicit PluginView(QWidget *parent = 0);
    ~PluginView();

    PluginSpec *currentPlugin() const;
    void setFilter(const QString &filter);

signals:
    void currentPluginChanged(PluginEngine::PluginSpec *spec);
    void pluginActivated(PluginEngine::PluginSpec *spec);
    void pluginSettingsChanged(PluginEngine::PluginSpec *spec);

private:
    PluginSpec *pluginForIndex(const QModelIndex &index) const;
    void updatePlugins();
    bool setPluginsEnabled(const QSet<PluginSpec *> &plugins, bool enable);

    Utils::TreeView *m_categoryView;
    Utils::TreeModel *m_model;
    QSortFilterProxyModel *m_sortModel;

    friend class Internal::CollectionItem;
    friend class Internal::PluginItem;
};

}  // namespace PluginEngine
