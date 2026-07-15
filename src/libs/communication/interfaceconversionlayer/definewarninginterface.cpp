#include "definewarninginterface.h"
#include "communication.h"
#include "IController.h"
#include "cobotlogex.h"
#include "modulesutils.h"
bool DefineWarningInterface::readWarnings()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetDefineWarning()->ReadWarnings();
    LOG_TRACE(QString("[%1][%2][%3]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return (ret == ERR_OK);
}

bool DefineWarningInterface::saveWarnings()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetDefineWarning()->SaveWarnings();
    if (ret != ERR_OK) {
        return false;
    }

    comm()->project()->sendSyncFlag(static_cast<int>(
        InoRobBusiness::SyncProjcetInfoType::SYNC_LABEL_INFO));
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

std::vector<string> DefineWarningInterface::getWarnings()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> datas =
        comm()->project()->GetDefineWarning()->GetWarnings().Warings;
    FREQ_LOG_PRINT_TIMESTAMP
    return datas;
}

bool DefineWarningInterface::modifyWarning(int index, const QString &warning)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int ret = comm()->project()->GetDefineWarning()->ModifyWarning(
        index, warning.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool DefineWarningInterface::isWarningValid(const QString &warning)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string errMsg;
    bool bRet = comm()->project()->GetDefineWarning()->IsWarningValid(errMsg, warning.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return (bRet && errMsg.empty());
}
