#pragma once

#include "iomapping.h"
#include "ioenum.h"
#include "communication_global.h"

namespace InoRobBusiness
{
class IIOMap;
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness
class AbstractCmd;
class Communication;

class COMMUNICATION_EXPORT PeripheralConfigInterface
{
public:
    PeripheralConfigInterface()
    {
    }
    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;
    bool getFieldbusIOMapDatas(QList<Ino_FieldbusIOMapData> &);

    bool resetFieldbusIOMap(Ino_IOMapResetMethod method);
    bool importIOMappingFile(const QString &);
    bool exportIOMappingFile(const QString &);
    bool saveIOMappingData(const QVector<Ino_FieldbusIOMapData> &);
    void saveIOMappingRemarks(AbstractCmd *cmd);
    bool refreshFieldbusFromControllerDatas();

    bool getSwitchEnableStatus(bool &ethernetipEnable, bool &ethercatEnable);

};
