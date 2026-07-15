#include "teachcontainerplugin.h"
#include <QDebug>
#include <QDir>
#include <QTranslator>
#include <QTimer>
#include <QApplication>
#include "teachcontainerform.h"
#include "mainwidget.h"
#include "metatype.h"

TeachContainerPlugin::TeachContainerPlugin(QObject *)
{
}

bool TeachContainerPlugin::initialize(
    const QStringList &arguments, QString *errorString)
{
    qDebug() << "#### TeachContainerPlugin::initialize";
    new TeachContainerForm(MainWidget::instance());
    TeachContainerForm::instance()->initialize();
    return true;
}

void TeachContainerPlugin::extensionsInitialized()
{
    qDebug() << "TeachContainerPlugin::extensionsInitialized()";
    TeachContainerForm::instance()->delayInitialized();
}

bool TeachContainerPlugin::pluginCommonInterface(
    const QString &funcName, const QList<QVariant> &params, QList<QVariant> &retList)
{
    bool ret = true;

    if (FuncName_GetFunctionEnabledList == funcName
        && 0 == params.size()) {
        retList.clear();
        TeachContainerForm::instance()->getFunctionEnabledList(retList);
    } else if (FuncName_SetFunctionEnabledList == funcName
               && 1 == params.size()) {
        TeachContainerForm::instance()->setFunctionEnabledList(params.at(0));
    }

    return ret;
}
