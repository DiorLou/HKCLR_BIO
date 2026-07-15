#pragma once

#include "communication_global.h"

#include "safety/crashdetectparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT CrashDetectInterface
{
public:
    CrashDetectInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    /** 协作 **/
    int readColProtectionParams(CollisionProtectiontParams &params);
    int writeColProtectionParams(const CollisionProtectiontParams &params);
    int readColProtectionRecommendLevel(qint16 &level);
    int resetColProtectionRecommendLevel();
};
