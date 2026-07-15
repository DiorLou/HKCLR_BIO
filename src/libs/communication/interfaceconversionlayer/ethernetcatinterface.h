#pragma once

#include <QObject>
#include "communication_global.h"
#include "peripheral/ethernertcatparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT EthernetCatInterface
{
public:
    EthernetCatInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    int writeEthernetCatConfig(InoEthcatPara ecatConfig);
    int readEthernetCatConnStatus(InoEthcatSts &ecatPara);
    bool checkEthernetCatOperatePermission();
    bool checkSaveEthernetCatPermission();

    int ReadEtherCATProperties(INO_ETHCAT_PROP& buf);
    int WriteEtherCATEnhan(quint16 &ARMSetLinkEnhanSwitch, quint16 &EtherCATXMLReset);
};
