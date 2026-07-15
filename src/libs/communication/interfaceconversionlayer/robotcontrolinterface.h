#pragma once

#include "communication_global.h"
#include "coordparam.h"
#include "commandinfo.h"
#include "pointdata.h"
#include "metatype.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
}  // namespace InoRobBusiness

class Communication;
class RoadPoint;
class AbstractCmd;
namespace Internal
{
class RobotControlInterfacePrivate;
}

class COMMUNICATION_EXPORT RobotControlInterface
{
public:
    RobotControlInterface();
    ~RobotControlInterface();

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;
    // 示教非单步运动
    bool robotMoveTeachStartOrStopInterface(
        const TeachMode &teachMode,
        const bool &direction,
        CoordParam coordParam = CoordParam(), bool isStart = true);

    bool robotMoveSlowlyStopInterface();

    bool robotMoveJointTeachInterface(const RoadPoint &roadPoint);

    bool robotMoveLineInterface(const RoadPoint &destPt);
    bool robotMoveJointInterface(const InoRobPos &iRobPos);

    bool robotMoveLineInterface(const RoadPoint &destPt,const int &tool,const int &wobj);
    bool robotMoveJointInterface(const InoRobPos &iRobPos,const int &tool,const int &wobj);

    bool robotMoveRotateTeachInterface(
        const CoordParam &coordParam,
        const TeachMode &teachMode,
        const double &rotateAngle);

    // inovance interface
    bool connectController(const QString &ip, const int &port);
    bool disconnectController();

    int connectVirtualController(AbstractCmd *cmd);

    bool enableMechLock(const bool &enable);

    bool clearAlarm();

    bool enableRobot(const bool &enable);

    bool SetEmergency(bool status);

    bool axisMove(int axisId, const bool &isPositive, const bool &isPressd);

    bool putFilesToController(const QStringList &srcFileList,
                              const QStringList &destFileList);

    bool programStart();
    bool programPause();
    bool programContinue();
    bool programStop();
    bool programStep();

    int SetDeviceMode(MetaType::RobotDeviceMode mode);
    int GetDeviceMode(MetaType::RobotDeviceMode &mode);
    void setRobotBodyPowerState(InoCoRobotBodyPowerState);
    InoCoRobotBodyPowerState getRobotBodyPowerState();

    bool setControllerWifiPassword(const QString &password);
    bool getWifiPasswordModifyResult(InoWifiPasswordModifyResult &status);

    bool setControllerWifiFrequncyBand(bool is24GHz);
    bool getControllerWifiInfo(InoCobotWifiInfo &wifiInfo);

    bool enableGripperThreePosition(bool enable);

    bool setSingleControllerRunModeEnable(bool enable);
    bool getSingleControllerRunModeEnable(bool &enable);

    bool getSingleControllerRunModeStatus(bool &status);

    void SetDebugMode(MetaType::RobotDebugMode mode);

    void getHistoryWarnList(AbstractCmd *cmd);
    void clearHistoryWarnInfo(AbstractCmd *cmd);

    bool readBrakeState(char stateArray[6]);
    void releaseBrake(int axisNo);
    void closeBrake(int axisNo);

    bool checkControllerUSB();

    bool readFileSaveFlag(int &nMark);

    bool controllerFilePathList(const std::string &ctrlPath,
                                std::vector<std::string> &filePathList);
    bool downloadFile(const std::string &localPath, const std::string &ctrlPath);

    bool formatMemoryCard();
    int readMemoryCardFormatState(int &nState);
    void endFormatMemoryCard();

    bool loadPointFile(const QString &filePath);
    bool deletePointFile(const QString &fileName);

    MetaType::ElectricControlCabinetType getElectricControlCabinetType();

    int processVirtualControllerDeviceName(AbstractCmd *cmd);


private:
    friend class Internal::RobotControlInterfacePrivate;
};
