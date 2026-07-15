#pragma once

#include <QObject>
#include "communication_global.h"
#include "peripheral/ethernertipparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT EthernetIPInterface
{
public:
    EthernetIPInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int writeEthernetIpConfig(CobotEthernetIpPara eipConfig);
    int readEthernetIpConnStatus(CobotEthernetIpSts &eipPara);
    bool checkEthernetIPOperatePermission();
    bool checkSaveEthernetIPPermission();
};
