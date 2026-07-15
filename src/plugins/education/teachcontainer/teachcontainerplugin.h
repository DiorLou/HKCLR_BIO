#pragma once

#include "iplugin.h"

class QTranslator;

class TeachContainerPlugin : public PluginEngine::IPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "com.qt-project.Inovance.InoCobotTPPlugin" FILE
                         COBOT_TP_PLUGIN_JSON_FILE_NAME)

public:
    explicit TeachContainerPlugin(QObject *parent = 0);

    virtual bool initialize(
        const QStringList &arguments, QString *errorString);
    virtual void extensionsInitialized();  // show widget

    virtual bool pluginCommonInterface(
        const QString &funcName,
        const QList<QVariant> &params, QList<QVariant> &retList);
};
