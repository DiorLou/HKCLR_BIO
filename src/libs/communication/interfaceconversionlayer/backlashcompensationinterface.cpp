#include "backlashcompensationinterface.h"
#include "communication.h"
#include "IController.h"
#include "communicationengine.h"
#include "cobotlog.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "cobotlog.h"
#include <QJsonArray>
#include <QObject>

#include "cobotlogex.h"
#include "modulesutils.h"

void BacklashCompensationInterface::getBacklashParams(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
        LOG_INFO("BacklashCompensationInterface::getBacklashParams start");

    // 定义间隙辨识结果结构体
    BacklashIdentifyResult backlashArray;
    memset(&backlashArray, 0, sizeof(BacklashIdentifyResult));

    // 调用业务层接口获取间隙参数
    int nRet = _IBacklashCompensation->getBacklashParams(backlashArray);
    if (nRet != ERR_OK) {
        LOG_ERROR("BacklashCompensationInterface::getBacklashParams ERROR, nRet=" + QString::number(nRet));
    }

    // 发送信号通知结果
    emit CommunicationEngine::instance()->signal_getBacklashParams_result(cmd->m_object, nRet == ERR_OK, backlashArray);
    LOG_INFO("BacklashCompensationInterface::getBacklashParams end. ");
    FREQ_LOG_PRINT_TIMESTAMP
}

bool BacklashCompensationInterface::setBacklashCompensationStatus(const InoRobBusiness::BacklashIdentifyResult &array)
{
    int nRet = _IBacklashCompensation->setBacklashCompensationStatus(array);
    if (nRet != ERR_OK) {
        LOG_ERROR("BacklashCompensationInterface::setBacklashCompensationStatus ERROR, nRet=" + QString::number(nRet));
    }

    return nRet == ERR_OK;
}

bool BacklashCompensationInterface::restoreBacklashFactorySettings()
{
    int nRet = _IBacklashCompensation->restoreFactorySettings();
    if (nRet != ERR_OK) {
        LOG_ERROR("BacklashCompensationInterface::restoreFactorySettings ERROR, nRet=" + QString::number(nRet));
    }
    return nRet == ERR_OK;
}

// void BacklashCompensationInterface::getRecommendedTrajectoryEndPoints(AbstractCmd *cmd)
// {
//     LOG_INFO("BacklashCompensationInterface::getRecommendedTrajectoryEndPoints start");

//     // 解析命令参数 - 获取起点角度列表
//     auto[startPointAngless] = BIND(cmd, QStringList);

//     // 获取机器人轴数
//     int axisNum = 6;
//     if (_IMonitor->GetRobotMechUnitAxisNum() > 0) {
//         axisNum = _IMonitor->GetRobotMechUnitAxisNum();
//     }

//             // 定义间隙辨识推荐轨迹结构体
//     FricIdentifyRecommendTraj jointAngless;
//     memset(&jointAngless, 0, sizeof(FricIdentifyRecommendTraj));

//             // 填充起点角度
//     for (int i=0; i<startPointAngless.size(); ++i) {
//         jointAngless.recommenPoint[0][i] = startPointAngless.at(i).toDouble();
//     }

//     // 调用业务层接口获取推荐轨迹端点
//     int nRet = _IBacklashCompensation->getRecommendedTrajectoryEndPoints(jointAngless);

//     QStringList params;
//     if (nRet == ERR_OK) {
//         for (int i=0; i<axisNum; ++i) {
//             params.append(QString::number(jointAngless.recommenPoint[1][i]));
//         }
//     }

//             // 发送信号通知结果
//     emit CommunicationEngine::instance()->signal_getRecommendedTrajectoryEndPoints_result(cmd->m_object, nRet == ERR_OK, params);
//     LOG_INFO("BacklashCompensationInterface::getRecommendedTrajectoryEndPoints end. ");
// }

void BacklashCompensationInterface::startBacklashIdentification(AbstractCmd *cmd)
{
    // 解析命令参数 - 速度列表、起点、终点
    auto[speedItems, jointIndex, startPoints, endPoints] = BIND(cmd, QStringList, int, QStringList, QStringList);
    QString msg;

    // 先设置速度
    BacklashIdentTrajVel trajVel;
    memset(&trajVel, 0, sizeof(BacklashIdentTrajVel));

    for (int i = 0; i < speedItems.size(); ++i)
    {
        if(i >= (sizeof(trajVel.vel) / sizeof(trajVel.vel[0])))
        {
            // 目前仅支持最多5个间隙辨识轨迹速度
            break;
        }
        double speed = speedItems.at(i).toDouble() * 0.01;
        trajVel.vel[i] = speed;
    }

    // 设置间隙辨识轨迹速度
    int nRet = _IBacklashCompensation->setBacklashIdentTraj4Vel(trajVel);
    if(nRet != ERR_OK)
    {
        msg = CommTr::tr("Failed to set the backlash trajectory identification speed %1").arg(nRet);
        CommunicationEngine::instance()->signal_startBacklashIdentification_result(cmd->m_object, false, msg);
        return;
    }

    // 开始间隙辨识
    BacklashIdentifyCalcTraj calcTraj;
    memset(&calcTraj, 0, sizeof(BacklashIdentifyCalcTraj));

    if(startPoints.size() != endPoints.size())
    {
        LOG_ERROR("startPoints.size() != endPoints.size()");
        CommunicationEngine::instance()->signal_startBacklashIdentification_result(cmd->m_object, false, msg);
        return;
    }

    // 解析关节索引
    calcTraj.jointIndex = jointIndex;

    // 填充轨迹点
    for(int i=0; i<startPoints.size(); i++)
    {
        if(i < _IMonitor->GetRobotMechUnitAxisNum())
        {
            // 最多支持6关节
            calcTraj.point[0][i] = startPoints.at(i).toDouble();
            calcTraj.point[1][i] = startPoints.at(i).toDouble() + endPoints.at(i).toDouble();
        }
    }

    // 开始间隙辨识
    nRet = _IBacklashCompensation->startBacklashIdentification(calcTraj);

    if(nRet != ERR_OK)
    {
        msg = CommTr::tr("Failed to start the backlash identification");
    }

    // 发送信号通知结果
    CommunicationEngine::instance()->signal_startBacklashIdentification_result(cmd->m_object, nRet == ERR_OK, msg);
}

void BacklashCompensationInterface::endBacklashIdentification(AbstractCmd *cmd)
{
    // 结束间隙辨识
    _IBacklashCompensation->endBacklashIdentification();

    // 停止运动
    _IMotion->MoveToPointStop();

    // 发送结束信号
    CommunicationEngine::instance()->signal_endBacklashIdentification_result(cmd->m_object, true, "");
}

void BacklashCompensationInterface::getBacklashRecognitionResult(AbstractCmd *cmd)
{
    QString msg;
    float f32Backlash = 0.0;

    // 调用业务层接口获取辨识结果
    int nRet = _IBacklashCompensation->getRecognitionResult(f32Backlash);
    if (nRet != ERR_OK) {
        msg = CommTr::tr("Failed to get backlash recognition result");
    }

    // 发送信号通知结果
    CommunicationEngine::instance()->signal_getBacklashRecognitionResult_result(cmd->m_object, nRet == ERR_OK, f32Backlash, msg);
}

// void BacklashCompensationInterface::setBacklashRecognitionResult(AbstractCmd *cmd)
// {
//     // 解析命令参数 - 使能标志位、间隙辨识结果
//     auto[flags, backlashRecognitionResult] = BIND(cmd, QList<bool>, BacklashIdentifyResult);

//     // 准备发送到ARM的数据
//     ToArmBacklashParam backlashArray;
//     memset(&backlashArray, 0, sizeof(ToArmBacklashParam));

//     for (int i = 0; i < flags.size(); ++i)
//     {
//         if(i >= _IMonitor->GetRobotMechUnitAxisNum())
//         {
//             // 目前最多支持6关节的间隙补偿设置
//             break;
//         }
//         bool isUse = flags.at(i);
//         backlashArray.backlashIsSelectFlag[i] = isUse ? 1 : 0;
//         backlashArray.backlash[i] = backlashRecognitionResult.jointBacklash[i];
//     }

//             // 调用业务层接口设置辨识结果
//     int nRet = _IBacklashCompensation->setRecognitionResult(backlashArray);
//     bool isOk = false;
//     QString msg;
//     if (nRet != ERR_OK) {
//         msg = CommTr::tr("Failed to set recognition result");
//     }

//     // 发送信号通知结果
//     CommunicationEngine::instance()->signal_setBacklashRecognitionResult_result(cmd->m_object, nRet == ERR_OK, msg);
// }

void BacklashCompensationInterface::slot_CompleteBacklashIdentify()
{
    LOG_INFO("BacklashCompensationInterface::slot_CompleteBacklashIdentify");
    // 间隙辨识完成后的处理逻辑
    // 可以发送信号通知UI层更新状态
}
