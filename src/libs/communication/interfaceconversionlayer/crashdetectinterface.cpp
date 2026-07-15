#include "crashdetectinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"
#include "modulesutils.h"
int CrashDetectInterface::readColProtectionParams(
    CollisionProtectiontParams &params)
{
    InoRobBusiness::CobotColDetectPara colParams;
    int iret = _IRobotArm->getCrashDetectionObject()->readColDetectPara(colParams);
    memcpy(&params, &colParams, sizeof(colParams));
    return iret;
}

int CrashDetectInterface::writeColProtectionParams(
    const CollisionProtectiontParams &params)
{
    InoRobBusiness::CobotColDetectPara colParams;
    memcpy(&colParams, &params, sizeof(params));
    int iret = _IRobotArm->getCrashDetectionObject()->writeColDetectPara(colParams);
    if (iret != 0) {
        return iret;
    }

    // 通知保存机型参数
    _IRCConfig->SavePf();
    return iret;
}

int CrashDetectInterface::readColProtectionRecommendLevel(qint16 &level)
{
    int iret = _IRobotArm->getCrashDetectionObject()->readColDetectRecommadLevel(level);
    return iret;
}

int CrashDetectInterface::resetColProtectionRecommendLevel()
{
    int iret = _IRobotArm->getCrashDetectionObject()->resetColDetectRecommadLevel();
    return iret;
}
