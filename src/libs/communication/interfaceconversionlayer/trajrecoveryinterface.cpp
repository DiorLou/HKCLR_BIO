#include "trajrecoveryinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"
#include "modulesutils.h"
#include "cobotlog.h"

int TrajRecoveryInterface::WriteTrajRecoveryParam(CobotTrajRecoveryParam &param)
{
    TrajRecoveryParam innerParams;
    memcpy(&innerParams, &param, sizeof(param));
    int iRet = _ITrajectoryRecovery->WriteTrajRecoveryParam(innerParams);
    LOG_INFO(QString("iRet = %1").arg(QString::number(iRet)));
    return iRet;
}

int TrajRecoveryInterface::ReadTrajRecoveryParam(CobotTrajRecoveryParam &param)
{
    TrajRecoveryParam innerParams;
    int iRet = _ITrajectoryRecovery->ReadTrajRecoveryParam(innerParams);
    memcpy(&param, &innerParams, sizeof(param));
    LOG_INFO(QString("iRet = %1").arg(QString::number(iRet)));
    return iRet;
}
