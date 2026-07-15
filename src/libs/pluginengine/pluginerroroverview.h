#pragma once

#include "pluginengine_global.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace PluginEngine
{

namespace Internal
{
namespace Ui
{
class PluginErrorOverview;
}
}  // namespace Internal

class PLUGINENGINE_EXPORT PluginErrorOverview : public QDialog
{
    Q_OBJECT

public:
    explicit PluginErrorOverview(QWidget *parent = 0);
    ~PluginErrorOverview();

private slots:
    void showDetails(QListWidgetItem *item);

private:
    Internal::Ui::PluginErrorOverview *m_ui;
};

}  // namespace PluginEngine
