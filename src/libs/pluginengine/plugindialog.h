#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include "pluginengine_global.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
QT_END_NAMESPACE

namespace PluginEngine
{
class PluginSpec;
class PluginView;

class PLUGINENGINE_EXPORT PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(QWidget *parent);

private:
    void updateRestartRequired();
    void updateButtons();
    void openDetails(PluginEngine::PluginSpec *spec);
    void openErrorDetails();
    void closeDialog();

    PluginEngine::PluginView *m_view;

    QPushButton *m_detailsButton;
    QPushButton *m_errorDetailsButton;
    QPushButton *m_closeButton;
    QLabel *m_restartRequired;
};

}  // namespace PluginEngine

#endif  // PLUGINDIALOG_H
