#include "frictioncompensationinterface.h"
#include "communication.h"
#include "IController.h"
#include "communicationengine.h"
#include "cobotlog.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "cobotlog.h"
#include <QJsonArray>
#include <QObject>

#include "cobotlogex.h"
#include "modulesutils.h"

void FrictionCompensationInterface::getCoulomFrictionParams(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("FrictionCompensationInterface::getCoulomFrictionParams start");
    // auto [array] = BIND(cmd, InoRobBusiness::FricIdentifyResult*);
    FricIdentifyResult array;
    memset(&array, 0, sizeof(FricIdentifyResult));
    int nRet = _IFrictionCompensation->getCoulombFrictionParams(array);
    if (nRet != ERR_OK) {
        LOG_ERROR("FrictionCompensationInterface::getCoulomFrictionParams ERROR, nRet=" + QString::number(nRet));
    }
    emit CommunicationEngine::instance()->singal_getCoulombFrictionParams_result(cmd->m_object, nRet == ERR_OK, array);
    LOG_INFO("FrictionCompensationInterface::getCoulomFrictionParams end. ");
    FREQ_LOG_PRINT_TIMESTAMP
}

bool FrictionCompensationInterface::setFricCompensationStatus(const InoRobBusiness::FricIdentifyResult &array)
{
    int nRet = _IFrictionCompensation->setFricCompensationStatus(array);
    if (nRet != ERR_OK) {
        LOG_ERROR("FrictionCompensationInterface::setFricCompensationStatus ERROR, nRet=" + QString::number(nRet));
    }

    return nRet == ERR_OK;
}

bool FrictionCompensationInterface::restoreFactorySettings()
{
    int nRet = _IFrictionCompensation->restoreFactorySettings();
    if (nRet != ERR_OK) {
        LOG_ERROR("FrictionCompensationInterface::restoreFactorySettings ERROR, nRet=" + QString::number(nRet));
    }
    return nRet == ERR_OK;
}

void FrictionCompensationInterface::getRecommendedTrajectoryEndPoints(AbstractCmd *cmd)
{
    LOG_INFO("FrictionCompensationInterface::getRecommendedTrajectoryEndPoints start");
    auto[startPointAngless] = BIND(cmd, QStringList);
    int axisNum = 6;
    if (_IMonitor->GetRobotMechUnitAxisNum() > 0) {
        axisNum = _IMonitor->GetRobotMechUnitAxisNum();
    }

    FricIdentifyRecommendTraj jointAngless;
    memset(&jointAngless, 0, sizeof(FricIdentifyRecommendTraj));

    for (int i=0; i<startPointAngless.size(); ++i) {
        jointAngless.recommenPoint[0][i] = startPointAngless.at(i).toDouble();
    }
    int nRet = _IFrictionCompensation->getRecommendedTrajectoryEndPoints(jointAngless);
    QStringList params;
    if (nRet == ERR_OK) {
        for (int i=0; i<axisNum; ++i) {
            params.append(QString::number(jointAngless.recommenPoint[1][i]));
        }
    }

    emit CommunicationEngine::instance()->signal_getRecommendedTrajectoryEndPoints_result(cmd->m_object, nRet == ERR_OK, params);
    LOG_INFO("FrictionCompensationInterface::getRecommendedTrajectoryEndPoints end. ");
}

void FrictionCompensationInterface::startFricIdentification(AbstractCmd *cmd)
{
    auto[speedItems, startPoints, endPoints] = BIND(cmd, QStringList, QStringList, QStringList);
    QString msg;
    // 先设置速度
    FricIdentTrajVel trajVel;
    memset(&trajVel, 0, sizeof(FricIdentTrajVel));

    for (int i = 0; i < speedItems.size(); ++i)
    {
        if(i >= (sizeof(trajVel.vel) / sizeof(trajVel.vel[0])))
        {
            // 目前仅支持最多4个摩擦辨识轨迹速度
            break;
        }
        double speed = speedItems.at(i).toDouble() * 0.01;
        trajVel.vel[i] = speed;
    }

    int nRet = _IFrictionCompensation->setFricIdentTraj4Vel(trajVel);
    if(nRet != ERR_OK)
    {
        msg = CommTr::tr("Failed to set the friction trajectory identification speed %1").arg(nRet);
        CommunicationEngine::instance()->signal_startFricIdentification_result(cmd->m_object, false, msg);
        return;
    }

    // 开始摩擦辨识
    FricIdentifyCalcTraj calcTraj;
    memset(&calcTraj, 0, sizeof(FricIdentifyCalcTraj));

    if(startPoints.size() != endPoints.size())
    {
        LOG_ERROR("startPoints.size() != endPoints.size()");
        CommunicationEngine::instance()->signal_startFricIdentification_result(cmd->m_object, false, msg);
        return;
    }

    for(int i=0; i<startPoints.size(); i++)
    {
        if(i < _IMonitor->GetRobotMechUnitAxisNum())
        {
            // 最多支持6关节
            calcTraj.point[0][i] = startPoints.at(i).toDouble();
            calcTraj.point[1][i] = startPoints.at(i).toDouble() + endPoints.at(i).toDouble();
        }
    }

    nRet = _IFrictionCompensation->startFricIdentification(calcTraj);

    if(nRet != ERR_OK)
    {
        msg = CommTr::tr("Failed to start the friction identification");
    }

    CommunicationEngine::instance()->signal_startFricIdentification_result(cmd->m_object, nRet == ERR_OK, msg);
}

void FrictionCompensationInterface::endFricIdentification(AbstractCmd *cmd)
{
    _IFrictionCompensation->endFricIdentification();
    _IMotion->MoveToPointStop();
}

void FrictionCompensationInterface::getRecognitionResult(AbstractCmd *cmd)
{
    QString msg;
    FricCompParam result;
    memset(&result, 0, sizeof(FricCompParam));

    int nRet = _IFrictionCompensation->getRecognitionResult(result);
    if (nRet != ERR_OK) {
        msg = CommTr::tr("Failed to get recognition result");
    }

    CommunicationEngine::instance()->signal_getRecognitionResult_result(cmd->m_object, nRet == ERR_OK, result, msg);
}

void FrictionCompensationInterface::setRecognitionResult(AbstractCmd *cmd)
{
    auto[flags, fricRecognitionResult] = BIND(cmd, QList<bool>, FricCompParam);

    ToArmFricParam coulombArray;
    memset(&coulombArray, 0, sizeof(ToArmFricParam));

    for (int i = 0; i < flags.size(); ++i)
    {
        if(i >= _IMonitor->GetRobotMechUnitAxisNum())
        {
            // 目前最多支持6关节的摩擦补偿设置
            break;
        }
        bool isUse = flags.at(i);
        coulombArray.coulombIsSelectFlag[i] = isUse ? 1 : 0;
        coulombArray.coulomb[i] = fricRecognitionResult.coulomb[i];
    }

    int nRet = _IFrictionCompensation->setRecognitionResult(coulombArray);
    bool isOk = false;
    QString msg;
    if (nRet != ERR_OK) {
        msg = CommTr::tr("Failed to set recognition result");
    }
    CommunicationEngine::instance()->signal_setRecognitionResult_result(cmd->m_object, nRet == ERR_OK, msg);
}
