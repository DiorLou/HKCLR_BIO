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
class PluginErrorView;
}
}  // namespace Internal

class PLUGINENGINE_EXPORT PluginErrorView : public QWidget
{
    Q_OBJECT

public:
    PluginErrorView(QWidget *parent = 0);
    ~PluginErrorView();

    void update(PluginSpec *spec);

private:
    Internal::Ui::PluginErrorView *m_ui;
};

}  // namespace PluginEngine
