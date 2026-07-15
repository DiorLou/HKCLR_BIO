#pragma once

#include "backlashcompensationinterface.h"
#include "datacollectioninterface.h"
#include "definewarninginterface.h"
#include "frictioncompensationinterface.h"
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
#include "forcecontrolinterface.h"

class IUser;

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IRobotParam;
}  // namespace InoRobBusiness

namespace Internal {
class CommunicationPrivate;
}

class COMMUNICATION_EXPORT Communication
    : public DataCollectionInterface,
      public RobotControlInterface,
      public GlobalVarInterface,
      public IOInterface,
      public ForceControlInterface,
      public FrictionCompensationInterface,
      public BacklashCompensationInterface,
      public LoadInterface,
      public ToolCalibrateInterface,
      public WObjCalibrateInterface,
      public MonitorInterface,
      public PositionInterface,
      public ProjectInterface,
      public JointPointInterface,
      public RobotPointInterface,
      public DefineWarningInterface,
      public ResourceInterface,
      public UserInterface,
      public PeripheralConfigInterface,
      public RobotArmInterface,
      public ConnectionInterface,
      public LabelInterface,
      public ControllerSystemConfig,
      public ModbusInterface,
      public EthernetIPInterface,
      public EthernetCatInterface,
      public TaskInterface,
      public RobotParameters,
      public MotionInterface,
      public SafetyInterface,
      public FieldBusInterface,
      public WarnInfoInterface,
      public RobotDebug,
      public ControlAuthority,
      public CrashDetectInterface,
      public InterferenceAreaInterface,
      public DebuggerInterface,
      public GeneralMatchInterface,
      public TrajRecoveryInterface,
      public LoadIdentify
{
    Q_OBJECT
public:
    static Communication *instance();
    explicit Communication();
    ~Communication();

    InoRobBusiness::IController *controller();
    InoRobBusiness::IProject *project();
    InoRobBusiness::IRobotParam *robotParam();
    IUser *user();
    virtual Communication *comm();

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
    Internal::CommunicationPrivate *d;
    friend class Internal::CommunicationPrivate;
};
