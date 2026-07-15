#include "monitorinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"

#include "cobotlogex.h"
#include "modulesutils.h"
quint16 MonitorInterface::GetToolId()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMonitor->GetToolId();
}
bool MonitorInterface::SetToolId(quint16 toolID)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    qDebug() << "MonitorInterface::SetToolId : " << toolID;
    return _ITool->SetCurrentId(toolID);
}

quint16 MonitorInterface::GetWobjId()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMonitor->GetWobjId();
}

bool MonitorInterface::SetWobjId(quint16 wobjID)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    qDebug() << "MonitorInterface::SetWobjId : " << wobjID;
    return _IWobj->SetCurrentId(wobjID);
}

quint16 MonitorInterface::GetLoadId()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMonitor->GetLoadId();
}

bool MonitorInterface::SetLoadId(quint16 loadID)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    qDebug() << "MonitorInterface::SetLoadId : " << loadID;
    return _ILoad->SetCurrentId(loadID);
}

RobotCoordType MonitorInterface::GetCurrentCoordType()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    switch (_IMonitor->GetCurrentCoordType()) {
    case COORD_BASE:
        return RobotCoordType_Base;
    case COORD_JOINT:
        return RobotCoordType_Joint;
    case COORD_TOOL:
        return RobotCoordType_Tool;
    case COORD_WOBJ:
        return RobotCoordType_User;
    case COORD_WORLD:
        return RobotCoordType_World;
    default:
        return RobotCoordType_Base;
    }

    return RobotCoordType_Base;
}

void MonitorInterface::SetCurrentCoordType(RobotCoordType coordType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobUtil::CoordType type;
    switch(coordType) {
    case RobotCoordType_Base:
        type = COORD_BASE;
        break;
    case RobotCoordType_Joint:
        type = COORD_JOINT;
        break;
    case RobotCoordType_Tool:
        type = COORD_TOOL;
        break;
    case RobotCoordType_User:
        type = COORD_WOBJ;
        break;
    case RobotCoordType_World:
        type = COORD_WORLD;
        break;
    default:
        type = COORD_UNKNOW;
        break;
    }
    _IPosition->SetCurrentCoordType(type);
    FREQ_LOG_PRINT_TIMESTAMP
}

RobotCoordDisplayFormat MonitorInterface::GetPosFormat()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    switch (_IMonitor->GetPosFormat()) {
    case FORMAT_BASE:
        return RobotCoordDisplayFormat_Base;
    case FORMAT_WOBJ:
        return RobotCoordDisplayFormat_User;
    case FORMAT_WORLD:
        return RobotCoordDisplayFormat_World;
    case FORMAT_FLANGLE:
        return RobotCoordDisplayFormat_Flange;
    case FORMAT_JOINT:
        return RobotCoordDisplayFormat_Joint;
    default:
        return RobotCoordDisplayFormat_Base;
    }

    return RobotCoordDisplayFormat_Base;
}

void MonitorInterface::SetPosFormat(RobotCoordDisplayFormat posFormat)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobUtil::PosFormat format;
    switch(posFormat) {
    case RobotCoordDisplayFormat_Base:
        format = FORMAT_BASE;
        break;
    case RobotCoordDisplayFormat_User:
        format = FORMAT_WOBJ;
        break;
    case RobotCoordDisplayFormat_World:
        format = FORMAT_WORLD;
        break;
    case RobotCoordDisplayFormat_Flange:
        format = FORMAT_FLANGLE;
        break;
    case RobotCoordDisplayFormat_Joint:
        format = FORMAT_JOINT;
        break;
    default:
        format = FORMAT_BASE;
        break;
    }
    _IPosition->SetPosFormat(format);
    FREQ_LOG_PRINT_TIMESTAMP
}

quint16 MonitorInterface::GetSpeed()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMonitor->GetSpeed();
}

bool MonitorInterface::SetSpeed(quint16 speed)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMotion->SetSpeed(speed);
}

bool MonitorInterface::getDragTeachStatus()
{
    bool bRet = _IMotion->getDragTeachStatus();
    LOG_INFO(QString("drag status read, status = %1").arg(QString::number(bRet)));
    return bRet;
}

void MonitorInterface::getRcVersionNum(int32s &i32ValV, int32s &i32ValR, int32s &i32ValC)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IMonitor->getRcVersionNum(i32ValV, i32ValR, i32ValR);
}

std::string MonitorInterface::getRcVersionName()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IMonitor->GetRCVersionName();
}
