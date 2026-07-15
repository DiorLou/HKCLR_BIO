#include "simulationformplugin.h"
#include "simulationform.h"
#include "metatype.h"
#include <QDebug>

SimulationFormPlugin::SimulationFormPlugin(
    QObject *)
{
}

bool SimulationFormPlugin::initialize(
    const QStringList &arguments, QString *errorString)
{
    qDebug() << "#### SimulationFormPlugin::initialize";
    new SimulationForm();
    SimulationForm::instance()->initialize();
    return true;
}

void SimulationFormPlugin::extensionsInitialized()
{
    SimulationForm::instance()->extensionsInitialized();
}

bool SimulationFormPlugin::pluginCommonInterface(
    const QString &funcName,
    const QList<QVariant> &params, QList<QVariant> &retList)
{
    bool ret = true;

    return ret;
}
