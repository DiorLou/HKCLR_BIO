#pragma once

#include "GlobalDataTypes.h"
#include "labeldata.h"
#include "communication_global.h"
#include "iostruct.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
class COMMUNICATION_EXPORT ForceControlInterface
{
public:
    ForceControlInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void getFCSensorDataArr(AbstractCmd *cmd);
    void saveFCSensorItem(AbstractCmd *cmd);

    void getFCCalibData(AbstractCmd *cmd);
    bool refreshCalibData(ForceCtrlCalibData &data);
    void saveFCCalibItem(AbstractCmd *cmd);
    void applyCaliResult(AbstractCmd *cmd);

    void isCanCalibrate(AbstractCmd *cmd);

    bool getFCForceValue(int sensorNo, QList<float> &forceArray);
    // void getFCForceValue(AbstractCmd *cmd);
    bool getFCCalibrateCalc(ForceCtrlCalibItem &item);

    void getFCCoordinateData(AbstractCmd *cmd);
    void saveFCCoordinateDataItem(AbstractCmd *cmd);

    void getFCConfigParam(AbstractCmd *cmd);
    void saveFCConfigParam(AbstractCmd *cmd);

    void getFCControlParam(AbstractCmd *cmd);
    void saveFCControlParam(AbstractCmd *cmd);

    void getFCLimitData(AbstractCmd *cmd);
    void saveFCLimitData(AbstractCmd *cmd);

    //力控日志和力控监控
    void readForceCtrlLogFormat(AbstractCmd *cmd);
    void writeForceCtrlLogFormat(AbstractCmd *cmd);
    void readForceCtrlMonitorSwitch(AbstractCmd *cmd);
    void writeForceCtrlMonitorSwitch(AbstractCmd *cmd);
    void readForceCtrlMonitorData(AbstractCmd *cmd);
    void writeClearSensorForce(AbstractCmd *cmd);
    void readForceCtrlCoodinateSetting(AbstractCmd *cmd);
    void writeForceCtrlCoodinateSetting(AbstractCmd *cmd);

    //得到工具参数
    void getToolData(AbstractCmd *cmd);

    //得到力控文件日志列表
    void getForceCtrlLogList(AbstractCmd *cmd);
    
    void copyLogFilesFromControlToLocal(AbstractCmd *cmd);

};
