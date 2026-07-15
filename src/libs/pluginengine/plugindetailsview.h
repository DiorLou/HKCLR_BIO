#pragma once

#include "pluginengine_global.h"

#include <QWidget>

namespace PluginEngine
{

class PluginSpec;

namespace Internal
{
namespace Ui
{
class PluginDetailsView;
}
}  // namespace Internal

class PLUGINENGINE_EXPORT PluginDetailsView : public QWidget
{
    Q_OBJECT

public:
    PluginDetailsView(QWidget *parent = 0);
    ~PluginDetailsView();

    void update(PluginSpec *spec);

private:
    Internal::Ui::PluginDetailsView *m_ui;
};

}  // namespace PluginEngine
