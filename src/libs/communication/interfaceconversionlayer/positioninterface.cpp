#include "positioninterface.h"

#include <QDebug>
#include <QObject>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"

#include "cobotlogex.h"
#include "modulesutils.h"
#include "commandinfo.h"

RoadPoint PositionInterface::GetCurRoadPoint(
    quint16 toolId, bool isAllowSingular)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    RoadPoint retPoint;

    InoRobBusiness::ReadCurPosState state;
    ReferObj referObj = static_cast<ReferObj>(GetCoordRef());
    RobPos robPos;
    JPos jPos;
    bool bRet =
        _IPosition->GetCurPos(
            toolId, referObj, state, jPos, robPos, isAllowSingular);

    qDebug() << "**************** GetCurPos Start ****************";
    qDebug() << "tool = " << toolId << "| wobj = " << static_cast<int>(referObj);
    qDebug() << "state = " << static_cast<int>(state) << "|jPos = ["
             << jPos.JointData[0] << jPos.JointData[1] << jPos.JointData[2]
             << jPos.JointData[3] << jPos.JointData[4] << jPos.JointData[5]
             << "] | robPos = [" << robPos.RPosData[0] << robPos.RPosData[1]
             << robPos.RPosData[2] << robPos.RPosData[3] << robPos.RPosData[4]
             << robPos.RPosData[5] << "]";
    qDebug() << robPos.ArmParm[0] << "|" << robPos.ArmParm[1] << "|"
             << robPos.ArmParm[2] << "|" << robPos.ArmParm[3] << state;
    qDebug() << "**************** GetCurPos End ****************";

    if(bRet) {
        retPoint.setArmAgrs(robPos.ArmParm, ROBOT_ARM_NUM);

        if(state != InoRobBusiness::READ_POS_OK && state!= InoRobBusiness::READ_POS_SINGULAR) {
            // if (state == InoRobBusiness::READ_POS_SINGULAR) {
            //     retPoint.setJointAngle(jPos.JointData);
            // }
            retPoint.print();
            return retPoint;
        }

        retPoint.m_position.m_x = robPos.RPosData[0];
        retPoint.m_position.m_y = robPos.RPosData[1];
        retPoint.m_position.m_z = robPos.RPosData[2];
        retPoint.m_orientation.m_rz = robPos.RPosData[3];
        retPoint.m_orientation.m_ry = robPos.RPosData[4];
        retPoint.m_orientation.m_rx = robPos.RPosData[5];

        retPoint.setJointAngle(jPos.JointData);

        retPoint.m_isSingular = (state == InoRobBusiness::READ_POS_SINGULAR);
    }
    retPoint.print();
    FREQ_LOG_PRINT_TIMESTAMP
    return retPoint;
}

RoadPoint PositionInterface::GetCurRoadPoint(bool isAllowSingular)
{
    quint16 curToolId = _IMonitor->GetToolId();
    return GetCurRoadPoint(curToolId, isAllowSingular);
}

RoadPoint PositionInterface::GetCurRoadPoint(quint16 toolId, quint16 wobjId, bool isAllowSingular)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    RoadPoint retPoint;

    InoRobBusiness::ReadCurPosState state;
    ReferObj referObj = static_cast<ReferObj>(wobjId);
    RobPos robPos;
    JPos jPos;
    bool bRet =
        _IPosition->GetCurPos(
            toolId, referObj, state, jPos, robPos, isAllowSingular);

    qDebug() << "**************** GetCurPos Start ****************";
    qDebug() << "tool = " << toolId << "| wobj = " << static_cast<int>(referObj);
    qDebug() << "state = " << static_cast<int>(state) << "|jPos = ["
             << jPos.JointData[0] << jPos.JointData[1] << jPos.JointData[2]
             << jPos.JointData[3] << jPos.JointData[4] << jPos.JointData[5]
             << "] | robPos = [" << robPos.RPosData[0] << robPos.RPosData[1]
             << robPos.RPosData[2] << robPos.RPosData[3] << robPos.RPosData[4]
             << robPos.RPosData[5] << "]";
    qDebug() << robPos.ArmParm[0] << "|" << robPos.ArmParm[1] << "|"
             << robPos.ArmParm[2] << "|" << robPos.ArmParm[3] << state;
    qDebug() << "**************** GetCurPos End ****************";

    if(bRet) {
        retPoint.setArmAgrs(robPos.ArmParm, ROBOT_ARM_NUM);

        if(state != InoRobBusiness::READ_POS_OK && state!= InoRobBusiness::READ_POS_SINGULAR) {
            // if (state == InoRobBusiness::READ_POS_SINGULAR) {
            //     retPoint.setJointAngle(jPos.JointData);
            // }
            retPoint.print();
            return retPoint;
        }

        retPoint.m_position.m_x = robPos.RPosData[0];
        retPoint.m_position.m_y = robPos.RPosData[1];
        retPoint.m_position.m_z = robPos.RPosData[2];
        retPoint.m_orientation.m_rz = robPos.RPosData[3];
        retPoint.m_orientation.m_ry = robPos.RPosData[4];
        retPoint.m_orientation.m_rx = robPos.RPosData[5];

        retPoint.setJointAngle(jPos.JointData);

        retPoint.m_isSingular = (state == InoRobBusiness::READ_POS_SINGULAR);
    }
    retPoint.print();
    FREQ_LOG_PRINT_TIMESTAMP
    return retPoint;
}

RoadPoint PositionInterface::GetCurRoadPointOnBase()
{
    quint16 curToolId = _IMonitor->GetToolId();
    ReferObj referObj = ReferBase;
    return GetCurRoadPoint(curToolId,referObj,true);
}

RoadPoint PositionInterface::GetCurRoadPointOnBase(bool isAllowSingular)
{
    quint16 curToolId = _IMonitor->GetToolId();
    ReferObj referObj = ReferBase;
    return GetCurRoadPoint(curToolId,referObj,isAllowSingular);
}

int PositionInterface::GetCoordRef()
{
    // return static_cast<int>(_IMonitor->GetWobjId());

    InoRobUtil::PosFormat format = _IMonitor->GetPosFormat();
    if (format == InoRobUtil::FORMAT_BASE ||
        format == InoRobUtil::FORMAT_WORLD) {
        return static_cast<int>(ReferBase);
    }
    if (format == InoRobUtil::FORMAT_FLANGLE) {
        return static_cast<int>(ReferBase);
    }
    if (format == InoRobUtil::FORMAT_WOBJ) {
        return static_cast<int>(_IMonitor->GetWobjId());
    }
    return static_cast<int>(ReferBase);
}

bool PositionInterface::KineInverseSolution(
    short toolId, short wobjId, short loadId, double pos[6], int armArgs[4],
    int &retCode, double joint[6])
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    RobPos rPos;
    memcpy(rPos.RPosData, pos, sizeof(double) * 6);
    rPos.ArmParm[0] = armArgs[0];
    rPos.ArmParm[1] = armArgs[1];
    rPos.ArmParm[2] = armArgs[2];
    rPos.ArmParm[3] = armArgs[3];
    LOG_INFO(QString("KineInverseSolution Input : tid = %1, wid = %2, lid = %3, armparams = %4|%5|%6|%7, pos = %8|%9|%10|%11|%12|%13")
                 .arg(QString::number(toolId),
                      QString::number(wobjId),
                      QString::number(loadId),
                      QString::number(rPos.ArmParm[0]),
                      QString::number(rPos.ArmParm[1]),
                      QString::number(rPos.ArmParm[2]),
                      QString::number(rPos.ArmParm[3]),
                      QString::number(rPos.RPosData[0]),
                      QString::number(rPos.RPosData[1]),
                      QString::number(rPos.RPosData[2]),
                      QString::number(rPos.RPosData[3]),
                      QString::number(rPos.RPosData[4]),
                      QString::number(rPos.RPosData[5])));
    JPos Jpos;
    bool bRet = _IPosition->KineInverseSolution(
        toolId, wobjId, loadId, rPos, retCode, Jpos);
    LOG_INFO(QString("KineInverseSolution result : bRet = %1, retCode = %2, JPos = %3|%4|%5|%6|%7|%8")
                 .arg(QString::number(bRet),
                      QString::number(retCode),
                      QString::number(Jpos.JointData[0]),
                      QString::number(Jpos.JointData[1]),
                      QString::number(Jpos.JointData[2]),
                      QString::number(Jpos.JointData[3]),
                      QString::number(Jpos.JointData[4]),
                      QString::number(Jpos.JointData[5])));
    memcpy(joint, Jpos.JointData, sizeof(double) * 6);
    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}
