#include "robotarminterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

int RobotArmInterface::ReadTorqueLimit(bool &bSwitch, int IntValue[ROBOT_AXIS_NUM])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    quint16 uSwitch = 0;
    int value[8] = {0};
    int ret = _IRobotArm->readTorqueLimit(uSwitch, value);
    memcpy(IntValue, value, ROBOT_AXIS_NUM * sizeof(int));
    bSwitch = static_cast<bool>(uSwitch);
    qDebug() << "[ReadTorqueLimit]ret = " << ret << "| switch = " << bSwitch;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotArmInterface::saveTorqueLimit(bool bSwitch,
                                       int IntValue[ROBOT_AXIS_NUM])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int value[8] = {0};
    memcpy(value, IntValue, ROBOT_AXIS_NUM * sizeof(int));
    int iRet = _IRobotArm
        ->saveTorqueLimit(static_cast<quint16>(bSwitch), value);
    qDebug() << __FUNCTION__ << iRet;
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int RobotArmInterface::saveAvrLoadLimit(bool bSwitch,
                                        int IntValue[ROBOT_AXIS_NUM])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int value[8] = {0};
    memcpy(value, IntValue, ROBOT_AXIS_NUM * sizeof(int));
    int iRet = _IRobotArm
        ->saveAvrLoadLimit(static_cast<quint16>(bSwitch), value);
    qDebug() << __FUNCTION__ << iRet;
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int RobotArmInterface::ReadAvrLoadLimit(bool &bSwitch,
                                        int IntValue[ROBOT_AXIS_NUM])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    quint16 uSwitch = 0;
    int value[8] = {0};
    int ret = _IRobotArm->readAvrLoadLimit(uSwitch, value);
    memcpy(IntValue, value, ROBOT_AXIS_NUM * sizeof(int));
    bSwitch = static_cast<bool>(uSwitch);
    qDebug() << "[ReadAvrLoadLimit]ret = " << ret << "| switch = " << bSwitch;
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotArmInterface::saveOverHeatAndLoadLimit(bool heatSwitch,
                                                bool loadSwitch)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _IRobotArm
        ->writeOverLoadLimit(static_cast<quint16>(loadSwitch));
    if (iRet != 0) {
        return iRet;
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return _IRobotArm
        ->writeOverHeatLimit(static_cast<quint16>(heatSwitch));
}

int RobotArmInterface::ReadOverHeatLimit(bool &bSwitch)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    quint16 uSwitch = 0;
    int ret = _IRobotArm->readOverHeatLimit(uSwitch);
    bSwitch = static_cast<bool>(uSwitch);
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotArmInterface::ReadOverLoadLimit(bool &bSwitch)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    quint16 uSwitch = 0;
    int ret = _IRobotArm->readOverLoadLimit(uSwitch);
    bSwitch = static_cast<bool>(uSwitch);
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotArmInterface::ReadOverHeatSupportFlag(bool &bSupport)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    quint16 flag = 0;
    int ret = _IRobotArm->readOverHeatSupportFlag(flag);
    bSupport = static_cast<bool>(flag);
    FREQ_LOG_PRINT_TIMESTAMP
    return ret;
}

int RobotArmInterface::getRobotCompParam(double compParam[])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IRobotArm->getRobotCompParam(compParam);
    LOG_INFO(QString("#### [RobotArmInterface::getRobotCompParam] alpha = %1, beta = %2").arg(QString::number(compParam[10]),
                                                  QString::number(compParam[11])));
    return ret;
}

int RobotArmInterface::saveRobotCompensationParam(double compParam[], bool autoSaveFileCommd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IRobotArm->writeRobotInstallParam(compParam);
    return ret;
}

