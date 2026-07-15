#include "motioninterface.h"

#include <cstring>
#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

bool MotionInterface::SetMoveStepGrade(InoMoveStepGrade grade)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    qDebug() << "[MotionInterface::SetMoveStepGrade]" << grade;
    _IMotion->SetMoveStepGrade(
        static_cast<InoRobBusiness::MoveStepGrade>(grade));
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool MotionInterface::GetMoveStepSizePara(InoMoveStepSizePara &para)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::MoveStepSizePara params;
    bool bRet = _IMotion->GetMoveStepSizePara(params);
    if (bRet) {
        memcpy(&para, &params, sizeof(params));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

bool MotionInterface::SetMoveStepSizePara(InoMoveStepSizePara para)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (para.JointSize < 0.01) {
        para.JointSize = 0.01f;
    }

    if (para.PoseSize < 0.01) {
        para.PoseSize = 0.01f;
    }

    if (para.PositionSize < 0.01) {
        para.PositionSize = 0.01f;
    }

    if (para.JointSize > 10) {
        para.JointSize = 10;
    }

    if (para.PoseSize > 10) {
        para.PoseSize = 10;
    }

    if (para.PositionSize > 10) {
        para.PositionSize = 10;
    }

    InoRobBusiness::MoveStepSizePara params;
    memcpy(&params, &para, sizeof(params));
    LOG_INFO(QString("[SetMoveStepSizePara]jointsize = %1, posesize = %2, positionsize = %3")
                 .arg(QString::number(params.JointSize), QString::number(params.PoseSize),
                      QString::number(params.PositionSize)));
    FREQ_LOG_PRINT_TIMESTAMP
    return _IMotion->SetMoveStepSizePara(params);
}

bool MotionInterface::JointMoveToZeroStart()
{
    return _IMotion->JointMoveToZeroStart();
}

bool MotionInterface::JointMoveToZeroStop()
{
    return _IMotion->JointMoveToZeroStop();
}
