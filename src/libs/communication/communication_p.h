#pragma once

#include "datacollectioninterface.h"
#include "definewarninginterface.h"
#include "jointpointinterface.h"
#include "labelinterface.h"
#include "projectinterface.h"
#include "robotcontrolinterface.h"
#include "robotpointinterface.h"
#include "iointerface.h"
#include "globalvarinterface.h"
#include "toolcalibrateinterface.h"
#include "wobjcalibrateinterface.h"
#include "monitorinterface.h"
#include "positioninterface.h"
#include "resourceinterface.h"
#include "userinterface.h"
#include "peripheralconfiginterface.h"
#include "robotarminterface.h"
#include "connectioninterface.h"
#include "controllersystemconfig.h"
#include "modbusinterface.h"
#include "ethernetipinterface.h"
#include "ethernetcatinterface.h"
#include "taskinterface.h"
#include "robotparameters.h"
#include "safetyinterface.h"
#include "motioninterface.h"
#include "fieldbusinterface.h"
#include "crashdetectinterface.h"
#include "loadidentifyinterface.h"
#include "robotdebug.h"
#include "controlauthority.h"
#include "warninfointerface.h"
#include "interferenceareainterface.h"
#include "debuginterface.h"
#include "generalmatchinterface.h"
#include "trajrecoveryinterface.h"

class IUser;

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IRobotParam;
}  // namespace InoRobBusiness
class Communication;
namespace  Internal{

class COMMUNICATION_EXPORT CommunicationPrivate : public QObject
{
    Q_OBJECT
public:
    // static CommunicationPrivate *instance();
    CommunicationPrivate(Communication *comm);
    ~CommunicationPrivate();

    InoRobBusiness::IController *controller();
    InoRobBusiness::IProject *project();
    InoRobBusiness::IRobotParam *robotParam();
    IUser *user();

    bool loginAllClient();
    Q_INVOKABLE void logoutAllClient();

    QString getIP() const;
    void setIP(const QString &newIP);
    bool isConnectVirtualController();

    int getPort() const;
    void setPort(int newPort);

    CoordParam getCurCoordParams();
    bool login();

private:
    QString getCoordTypeStr();
    void loadRPFileNameChanged(std::string);

private:
    Communication *q;
    QString m_ip;
    int m_port = 0;

    InoRobBusiness::IWorkstation *m_pWorkstation = nullptr;
    InoRobBusiness::IController *m_pController = nullptr;
    InoRobBusiness::IProject *m_pProject = nullptr;
    InoRobBusiness::IRobotParam *m_pRobotParam = nullptr;

    IUser *m_pUser = nullptr;

};
}
