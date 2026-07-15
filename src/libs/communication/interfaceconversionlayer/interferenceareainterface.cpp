#include "interferenceareainterface.h"

#include <QDebug>
#include "IController.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

int InterferenceAreaInterface::readCurrPointPosOfInterAreaSetting(
    RoadPoint &pos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    RobPos robpos;
    int iRet = _IRobotArm
                           ->getInterferenceArea()->readCurrPointPosOfInterAreaSetting(robpos);

    LOG_INFO(QString("InterArea : ret = %1, x = %2, y = %3, z = %4, rx = %5, ry = %6, rz = %7")
                 .arg(QString::number(iRet),
                      QString::number(robpos.RPosData[0]),
                      QString::number(robpos.RPosData[1]),
                      QString::number(robpos.RPosData[2]),
                      QString::number(robpos.RPosData[5]),
                      QString::number(robpos.RPosData[4]),
                      QString::number(robpos.RPosData[3])));

    pos.m_position.m_x = robpos.RPosData[0];
    pos.m_position.m_y = robpos.RPosData[1];
    pos.m_position.m_z = robpos.RPosData[2];
    pos.m_orientation.m_rz = robpos.RPosData[5];
    pos.m_orientation.m_ry = robpos.RPosData[4];
    pos.m_orientation.m_rx = robpos.RPosData[3];
    return iRet;
}

int InterferenceAreaInterface::readCurrPointPosOfToolObjSetting(
    RoadPoint &pos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    RobPos robpos;
    int iRet = _IRobotArm
                   ->getInterferenceArea()->readCurrPointPosOfToolObjSetting(robpos);

    LOG_INFO(QString("EndObject : ret = %1, x = %2, y = %3, z = %4, rx = %5, ry = %6, rz = %7")
                 .arg(QString::number(iRet),
                      QString::number(robpos.RPosData[0]),
                      QString::number(robpos.RPosData[1]),
                      QString::number(robpos.RPosData[2]),
                      QString::number(robpos.RPosData[5]),
                      QString::number(robpos.RPosData[4]),
                      QString::number(robpos.RPosData[3])));

    pos.m_position.m_x = robpos.RPosData[0];
    pos.m_position.m_y = robpos.RPosData[1];
    pos.m_position.m_z = robpos.RPosData[2];
    pos.m_orientation.m_rz = robpos.RPosData[5];
    pos.m_orientation.m_ry = robpos.RPosData[4];
    pos.m_orientation.m_rx = robpos.RPosData[3];
    return iRet;
}
