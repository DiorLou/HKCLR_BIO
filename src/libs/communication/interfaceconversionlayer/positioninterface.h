#pragma once

#include "communication_global.h"
#include "roadpoint.h"
#include "coordparam.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;

/// @brief 位置接口
class COMMUNICATION_EXPORT PositionInterface
{
public:
    PositionInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    RoadPoint GetCurRoadPoint(quint16 toolId, bool isAllowSingular = false);
    RoadPoint GetCurRoadPoint(bool isAllowSingular = false);
    RoadPoint GetCurRoadPoint(quint16 toolId, quint16 wobjId,bool isAllowSingular = false);

    RoadPoint GetCurRoadPointOnBase();
    RoadPoint GetCurRoadPointOnBase(bool isAllowSingular);

    bool KineInverseSolution(short toolId, short wobjId, short loadId,
                             double pos[6], int armArgs[4], int &retCode, double joint[6]);

private:
    int GetCoordRef();
};
