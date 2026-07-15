#pragma once

#include "GlobalDataTypes.h"
#include "labeldata.h"
#include "communication_global.h"
#include "iostruct.h"
#include "Controller/FrictionCompensation/IFrictionCompensation.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
class COMMUNICATION_EXPORT FrictionCompensationInterface
{
public:
    FrictionCompensationInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void getCoulomFrictionParams(AbstractCmd *cmd);
    bool setFricCompensationStatus(const InoRobBusiness::FricIdentifyResult &array);

    bool restoreFactorySettings();

    void getRecommendedTrajectoryEndPoints(AbstractCmd *cmd);

    void startFricIdentification(AbstractCmd *cmd);

    void endFricIdentification(AbstractCmd *cmd);

    void getRecognitionResult(AbstractCmd *cmd);

    void setRecognitionResult(AbstractCmd *cmd);

private slots:
    void slot_CompleteFricIdentify();

};
