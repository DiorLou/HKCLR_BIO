#include "debuginterface.h"

#include <QDebug>
#include "IController.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"
int DebuggerInterface::writeStartReleaseMode(uint8_t mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int iRet = _IDebuger->writeStartReleaseMode(
        InoRobBusiness::StartReleaseObjType::TP, static_cast<InoRobBusiness::StartReleaseMode>(mode));

    LOG_INFO(QString("[writeStartReleaseMode]iRet = %1").arg(QString::number(iRet)));

    if (iRet != 0) {
        return iRet;
    }

    _IDebuger->setCurStartReleaseMode(
        InoRobBusiness::StartReleaseObjType::TP, static_cast<InoRobBusiness::StartReleaseMode>(mode));

    return 0;
}

int DebuggerInterface::readStartReleaseMode(uint8_t &mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::StartReleaseMode retMode;
    int iRet = _IDebuger->readStartReleaseMode(
        InoRobBusiness::StartReleaseObjType::TP, retMode);

    LOG_INFO(QString("[readStartReleaseMode]retMode = %1, ret = %2").arg(
        QString::number(static_cast<uint8_t>(retMode)), QString::number(iRet)));

    mode = static_cast<uint8_t>(retMode);
    return iRet;
}

int DebuggerInterface::trajectoryRecoveryFlag(TrajRecvFlag &flag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::TrajectoryRecoveryFlag retValue;
    int iRet = _IDebuger->trajectoryRecoveryFlag(retValue);
    // retValue = InoRobBusiness::TrajectoryRecoveryFlag::SETTED_OR_NEEDLESS;
    LOG_INFO(QString("trajectory recover flag, iret = %1, flag = %2")
                 .arg(QString::number(iRet), QString::number(static_cast<int>(retValue))));
    flag = static_cast<TrajRecvFlag>(retValue);
    return iRet;
}

int DebuggerInterface::trajectoryRecoveryExcute(TrajRecvExecMode mode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::TrajectoryRecoveryExcuteMode arg =
        static_cast<InoRobBusiness::TrajectoryRecoveryExcuteMode>(mode);
    int iRet = _IDebuger->trajectoryRecoveryExcute(arg);
    LOG_INFO(QString("trajectory recover flag, iret = %1").arg(QString::number(iRet)));
    return iRet;
}
