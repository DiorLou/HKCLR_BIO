#include "loadidentifyinterface.h"

#include <QDebug>
#include "IController.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

int LoadIdentify::startIdentify(const CobotLoadIdentifyData &data)
{
    InoRobBusiness::LoadIdentifyData args;
    memcpy(&args, &data, sizeof(args));
#if CommonLib_Metatype_DOF7_Enabled == 1
    int iRet = _ILoadIdentify->startSevenIdentify(args);
#else
    int iRet = _ILoadIdentify->startIdentify(args);
    LOG_INFO(QString("[%1]iRet = %2").arg(__FUNCTION__, QString::number(iRet)));
    LOG_INFO(QString("Trace1Start j1 = %1, j2 = %2, j3 = %3, j4 = %4, j5 = %5, j6 = %6")
                 .arg(QString::number(args.pos[0].JointData[0]),
                      QString::number(args.pos[0].JointData[1]),
                      QString::number(args.pos[0].JointData[2]),
                      QString::number(args.pos[0].JointData[3]),
                      QString::number(args.pos[0].JointData[4]),
                      QString::number(args.pos[0].JointData[5])));
    LOG_INFO(QString("Trace1End j1 = %1, j2 = %2, j3 = %3, j4 = %4, j5 = %5, j6 = %6")
                 .arg(QString::number(args.pos[1].JointData[0]),
                      QString::number(args.pos[1].JointData[1]),
                      QString::number(args.pos[1].JointData[2]),
                      QString::number(args.pos[1].JointData[3]),
                      QString::number(args.pos[1].JointData[4]),
                      QString::number(args.pos[1].JointData[5])));
    LOG_INFO(QString("Trace2Start j1 = %1, j2 = %2, j3 = %3, j4 = %4, j5 = %5, j6 = %6")
                 .arg(QString::number(args.pos[2].JointData[0]),
                      QString::number(args.pos[2].JointData[1]),
                      QString::number(args.pos[2].JointData[2]),
                      QString::number(args.pos[2].JointData[3]),
                      QString::number(args.pos[2].JointData[4]),
                      QString::number(args.pos[2].JointData[5])));
    LOG_INFO(QString("Trace2End j1 = %1, j2 = %2, j3 = %3, j4 = %4, j5 = %5, j6 = %6")
                 .arg(QString::number(args.pos[2].JointData[0]),
                      QString::number(args.pos[2].JointData[1]),
                      QString::number(args.pos[2].JointData[2]),
                      QString::number(args.pos[2].JointData[3]),
                      QString::number(args.pos[2].JointData[4]),
                      QString::number(args.pos[2].JointData[5])));
#endif


    return iRet;
}

int LoadIdentify::stopIdentify()
{
    int iRet = _ILoadIdentify->stopIdentify();
    LOG_INFO(QString("[%1]iRet = %2").arg(__FUNCTION__, QString::number(iRet)));
    return iRet;
}

int LoadIdentify::readIdentifyData(CobotLoadIdentifyData &data)
{
    InoRobBusiness::LoadIdentifyData retValue;
    int iRet = _ILoadIdentify->readIdentifyData(retValue);
    memcpy(&data, &retValue, sizeof(data));
    LOG_INFO(QString("[%1]iRet = %2").arg(__FUNCTION__, QString::number(iRet)));
    return iRet;
}

int LoadIdentify::readIdentifyStatus(CobotIdentifyStatus &status)
{
    InoRobBusiness::IdentifyStatus retValue;
    int iRet = _ILoadIdentify->readIdentifyStatus(retValue);
    memcpy(&status, &retValue, sizeof(status));
    LOG_INFO(QString("[%1]iRet = %2").arg(__FUNCTION__, QString::number(iRet)));
    return iRet;
}

int LoadIdentify::readIdentifyResult(CobotLoadIdentifyResult &result)
{
    InoRobBusiness::LoadIdentifyResult retValue;
    int iRet = _ILoadIdentify->readIdentifyResult(retValue);
    memcpy(&result, &retValue, sizeof(result));
    LOG_INFO(QString("[%1]iRet = %2, no = %3, mas = %4").arg(__FUNCTION__, QString::number(iRet),
                                                   QString::number(retValue.toolOrLoadNo),
                                                   QString::number(retValue.resultData.Mass)));
    return iRet;
}

CobotIdentifyType LoadIdentify::getIdentifyType()
{
    CobotIdentifyType iRet =
        static_cast<CobotIdentifyType>(_ILoadIdentify->getIdentifyType());
    return iRet;
}

void LoadIdentify::setIdentifyType(const CobotIdentifyType &type)
{
    _ILoadIdentify->setIdentifyType(
        static_cast<InoRobBusiness::IdentifyType>(type));
}

int LoadIdentify::readIdentifyTrajectoryFromRc(QVector<QVector<float>> &trajPoint)
{
    trajPoint.clear();
    float retValue[6][6] = {0};
    int iRet = _ILoadIdentify->readIdentifyTrajectoryFromRc(retValue);

    for (int i = 0; i < 6; ++i) {
        QVector<float> tmp;

#if defined(INOCOBOTTP_MSVC_QT5)
        for (int j = 0; j < 6; ++j) {
            tmp.push_back(retValue[i][j]);
        }
        trajPoint.push_back(tmp);
#else
        for (int j = 0; j < 6; ++j) {
            tmp.emplace_back(retValue[i][j]);
        }
        trajPoint.emplace_back(tmp);
#endif

    }

    LOG_INFO(QString("[%1]iRet = %2").arg(__FUNCTION__, QString::number(iRet)));
    return iRet;
}

int LoadIdentify::readIdentifyRecommenPoint(
    int pointIndex, CobotLoadIdentifyRecommendTraj recommendTraj, QVector<QVector<float>> &identifyPoint, bool isOneTraj)
{
    identifyPoint.clear();
    InoRobBusiness::LoadIdentifyRecommendTraj args;
    memcpy(&args, &recommendTraj, sizeof(args));
    float retValue[6][6] = {0};
    memcpy(&retValue[0][0], &recommendTraj.recommenPoint[0][0], sizeof(retValue));
    int iRet = _ILoadIdentify->readIdentifyRecommenPoint(pointIndex, args, retValue, isOneTraj);

    for (int i = 0; i < 6; ++i) {
        QVector<float> tmp;
#if defined(INOCOBOTTP_MSVC_QT5)
        for (int j = 0; j < 6; ++j) {
            tmp.push_back(retValue[i][j]);
        }
        identifyPoint.push_back(tmp);
#else
        for (int j = 0; j < 6; ++j) {
            tmp.emplace_back(retValue[i][j]);
        }
        identifyPoint.emplace_back(tmp);
#endif
    }
    LOG_INFO(QString("[%1]isOneTraj = %2, pointdx = %3, iRet = %4")
            .arg(__FUNCTION__, QString::number(isOneTraj), QString::number(pointIndex), QString::number(iRet)));
    return iRet;
}
