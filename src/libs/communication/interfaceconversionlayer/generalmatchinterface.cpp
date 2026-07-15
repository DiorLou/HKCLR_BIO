#include "generalmatchinterface.h"

#include <QDebug>
#include "IController.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "RobotParam/IRobotParam.h"

#include "cobotlogex.h"
#include "modulesutils.h"
bool GeneralMatchInterface::getGeneralMatchOpen()
{
    return robotParam()->getGeneralMatch()->getGeneralMatchOpen();
}

bool GeneralMatchInterface::setGeneralMatchOpen(bool open)
{
    bool bRet = robotParam()->getGeneralMatch()->setGeneralMatchOpen(open);
    LOG_INFO(QString("[setGeneralMatchOpen]open = %1, bret = %2")
                 .arg(QString::number(open), QString::number(bRet)));
    return bRet;
}

bool GeneralMatchInterface::allowTracingGeneralMatch()
{
    return robotParam()->getGeneralMatch()->allowTracingGeneralMatch();
}

int GeneralMatchInterface::getGeneralMatchRecord(const std::string &fileName)
{
    int iRet = robotParam()->getGeneralMatch()->getGeneralMatchRecord(fileName);
    LOG_INFO(QString("[getGeneralMatchRecord]filename = %1, iRet = %2")
                 .arg(QString::fromStdString(fileName), QString::number(iRet)));
    return iRet;
}

bool GeneralMatchInterface::getGeneralMatchInfo(CobotGeneralMatchInfo &retinfo)
{
    InoRobBusiness::IGeneralMatch::GeneralMatchInfo modelvalue;

    int iRet = robotParam()->getGeneralMatch()->getGeneralMatchInfo(modelvalue);
    LOG_INFO(QString("[getGeneralMatchInfo]bret = %2").arg(QString::number(iRet)));

    retinfo.bodyRobotName = modelvalue.bodyRobotName;
    retinfo.controllerRobotName = modelvalue.controllerRobotName;
    retinfo.matchState = modelvalue.matchState;
    retinfo.factoryFlag = modelvalue.factoryFlag;
    retinfo.direction = modelvalue.direction;
    retinfo.bodyHardwareVersion = modelvalue.bodyHardwareVersion;
    retinfo.bodySoftwareVersion = modelvalue.bodySoftwareVersion;
    retinfo.bodySN = modelvalue.bodySN;
    retinfo.mainFPGAHardwareVersion = modelvalue.mainFPGAHardwareVersion;
    retinfo.mainFPGASoftwareVersion = modelvalue.mainFPGASoftwareVersion;
    retinfo.controllerSN = modelvalue.controllerSN;
    memcpy(&retinfo.bodyDB[0], &modelvalue.bodyDB[0], sizeof(modelvalue.bodyDB));
    memcpy(&retinfo.bodyBrakeType[0], &modelvalue.bodyBrakeType[0], sizeof(modelvalue.bodyBrakeType));
    memcpy(&retinfo.bodyPower[0], &modelvalue.bodyPower[0], sizeof(modelvalue.bodyPower));
    retinfo.bodyParamVersion = modelvalue.bodyParamVersion;
    retinfo.bodyParamCompatibilityVersion = modelvalue.bodyParamCompatibilityVersion;
    retinfo.controllerParamCompatibilityVersion = modelvalue.controllerParamCompatibilityVersion;
    retinfo.generalOpen = modelvalue.generalOpen;

    return true;
}

bool GeneralMatchInterface::getRobotParamSyncStatus(CobotRobotParamSyncStatus &status)
{
    InoRobBusiness::IGeneralMatch::RobotParamSyncStatus sts;

    int iRet = robotParam()->getGeneralMatch()->getRobotParamSyncStatus(sts);
    LOG_INFO(QString("[getRobotParamSyncStatus]iRet = %1, bodyStatus = %2, servoStatus = %3, controllerStatus = %4, isValid = %5")
                 .arg(QString::number(iRet), QString::number(sts.bodyStatus), QString::number(sts.servoStatus),
                      QString::number(sts.controllerStatus), QString::number(sts.isValid)));

    status.bodyStatus = sts.bodyStatus;
    status.servoStatus = sts.servoStatus;
    status.controllerStatus = sts.controllerStatus;
    status.isValid = sts.isValid;

    return iRet;
}

int GeneralMatchInterface::startRobotParamSync(const std::string &info)
{
    int iRet = robotParam()->getGeneralMatch()->startRobotParamSync(info);
    LOG_INFO(QString("[startRobotParamSync]info = %1, iRet = %2")
                 .arg(QString::fromStdString(info), QString::number(iRet)));
    return 0;
}

int GeneralMatchInterface::readRobotParamMatchInfo(std::string &info)
{
    int iRet = robotParam()->getGeneralMatch()->readRobotParamMatchInfo(info);
    LOG_INFO(QString("[readRobotParamMatchInfo]iRet = %1").arg(QString::number(iRet)));
    return 0;
}
