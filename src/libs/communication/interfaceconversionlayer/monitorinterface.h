#pragma once

#include <QObject>
#include "DataTypeDef.h"
#include "communication_global.h"
#include "toolparams.h"
#include "coordparam.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT MonitorInterface
{
public:
    MonitorInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    quint16 GetToolId();
    bool SetToolId(quint16 toolID);

    quint16 GetWobjId();
    bool SetWobjId(quint16 wobjID);

    quint16 GetLoadId();
    bool SetLoadId(quint16 loadID);

    RobotCoordType GetCurrentCoordType();
    void SetCurrentCoordType(RobotCoordType coordType);

    RobotCoordDisplayFormat GetPosFormat();
    void SetPosFormat(RobotCoordDisplayFormat posFormat);

    quint16 GetSpeed();
    bool SetSpeed(quint16 speed);

    bool getDragTeachStatus();

    void getRcVersionNum(int32s &i32ValV, int32s &i32ValR, int32s &i32ValC);

    std::string getRcVersionName();
};
