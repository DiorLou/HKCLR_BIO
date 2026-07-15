#pragma once

#include "metatype.h"
#include "communication_global.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
class IRobotArm;
class IRobotParamRange;
}  // namespace InoRobBusiness

class Communication;
class ServiceInterface;
class AbstractCmd;


class COMMUNICATION_EXPORT RobotParametersTr : public QObject
{
    Q_OBJECT
};

class COMMUNICATION_EXPORT RobotParameters
{
public:
    RobotParameters()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    InoRobBusiness::IRobotArm* robotArm();

    void getRobotParams(AbstractCmd *absCmd);
    void setRobotParamsForSimulation(AbstractCmd *absCmd);
    void setRobotParams(AbstractCmd *absCmd);
    void readRobotName(AbstractCmd *absCmd);

    void getTeachParams(AbstractCmd *absCmd);
    void setTeachParams(AbstractCmd *absCmd);

    void getMotionParams(AbstractCmd *absCmd);
    void setMotionParams(AbstractCmd *absCmd);

    int RobotParamFileChange(const int &type);
    int RobotParamServoCurrent(QByteArray &info);
    int RobotParamServoStart(char *info);
    int RobotParamServoStop();
    int RobotParamUpdateStatusRead(QByteArray &info);

    void getSevenRobotParams(AbstractCmd *absCmd);
    void setSevenRobotParams(AbstractCmd *absCmd);

    void setSevenLoadMotionStatus(AbstractCmd *absCmd);
    void getSevenLoadMotionStatus(AbstractCmd *absCmd);

    void setRGB(AbstractCmd *absCmd);

private:
    void getParamRangeDoubleValue(
        InoRobBusiness::IRobotParamRange *param,
        const std::string &structName, const std::string &name,
        QList<double> &minList, QList<double> &maxList);
    void getParamRangeDoubleValue(
        InoRobBusiness::IRobotParamRange *param,
        const std::string &structName, const std::vector<std::string> &paraNameVec,
        QList<double> &minList, QList<double> &maxList);
};
