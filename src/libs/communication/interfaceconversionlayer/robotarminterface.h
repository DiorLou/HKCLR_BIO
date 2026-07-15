#pragma once

#include "communication_global.h"
#include "metatype.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT RobotArmInterface
{
public:
    RobotArmInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int ReadTorqueLimit(bool &bSwitch, int IntValue[ROBOT_AXIS_NUM]);
    int saveTorqueLimit(bool bSwitch, int IntValue[ROBOT_AXIS_NUM]);

    int saveAvrLoadLimit(bool bSwitch, int IntValue[ROBOT_AXIS_NUM]);
    int ReadAvrLoadLimit(bool &bSwitch, int IntValue[ROBOT_AXIS_NUM]);

    int saveOverHeatAndLoadLimit(bool heatSwitch, bool loadSwitch);
    int ReadOverHeatLimit(bool &bSwitch);
    int ReadOverLoadLimit(bool &bSwitch);

    int ReadOverHeatSupportFlag(bool &bSupport);

    int getRobotCompParam(double compParam[16]);
    int saveRobotCompensationParam(double compParam[16], bool autoSaveFileCommd = true);
};
