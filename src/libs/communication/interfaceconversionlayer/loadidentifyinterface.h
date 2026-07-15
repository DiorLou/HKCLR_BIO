#pragma once

#include <QObject>
#include "communication_global.h"
#include "calibrate/loadidentifydefines.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT LoadIdentify
{
public:
    LoadIdentify()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int startIdentify(const CobotLoadIdentifyData &data);
    int stopIdentify();

    int readIdentifyData(CobotLoadIdentifyData &data);
    int readIdentifyStatus(CobotIdentifyStatus &status);
    int readIdentifyResult(CobotLoadIdentifyResult &result);

    CobotIdentifyType getIdentifyType();
    void setIdentifyType(const CobotIdentifyType &type);

    int readIdentifyTrajectoryFromRc(QVector<QVector<float> > &trajPoint);
    int readIdentifyRecommenPoint(int pointIndex,
                                  CobotLoadIdentifyRecommendTraj recommendTraj,
                                  QVector<QVector<float> > &identifyPoint,
                                  bool isOneTraj);
};
