#pragma once

#include <QObject>
#include "communication_global.h"
#include "roadpoint.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT InterferenceAreaInterface
{
public:
    InterferenceAreaInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // 读取干涉区设置中当前点位置
    int readCurrPointPosOfInterAreaSetting(RoadPoint &pos);

    // 读取末端监测对象当前点位置
    int readCurrPointPosOfToolObjSetting(RoadPoint &pos);
};
