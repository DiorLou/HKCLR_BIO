#include "wobjcalibrateinterface.h"

#include <QDebug>
#include <string>

#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"

#include "cobotlogex.h"
#include "modulesutils.h"

quint16 WObjCalibrateInterface::GetWObjCount()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IWobj->GetCount();
}

QString WObjCalibrateInterface::WobjIdNameSearch(quint16 id)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sName =
        _IWobj->WobjIdNameSearch(
            static_cast<InoRobBusiness::WobjId>(id));
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return QString::fromStdString(sName);
}

bool WObjCalibrateInterface::SetCurrentWObjId(quint16 currentId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IWobj->SetCurrentId(currentId);
}

bool WObjCalibrateInterface::GetCurrentWobjParam(WobjParams &params)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjData wobjData;
    if (!_IWobj->GetCurrentWobjParam(wobjData)) {
        return false;
    }

    params.RobHold = wobjData.RobHold;
    params.UFFix = wobjData.UFFix;
    memcpy(params.UFMec, wobjData.UFMec, MECHUNIT_NAME_LENGTH);

    params.UFramePos.m_x = wobjData.UFrame.Data[0];
    params.UFramePos.m_y = wobjData.UFrame.Data[1];
    params.UFramePos.m_z = wobjData.UFrame.Data[2];
    params.UFrameOri.m_rx = wobjData.UFrame.Data[5];
    params.UFrameOri.m_ry = wobjData.UFrame.Data[4];
    params.UFrameOri.m_rz = wobjData.UFrame.Data[3];

    params.OFramePos.m_x = wobjData.OFrame.Data[0];
    params.OFramePos.m_y = wobjData.OFrame.Data[1];
    params.OFramePos.m_z = wobjData.OFrame.Data[2];
    params.OFrameOri.m_rx = wobjData.OFrame.Data[5];
    params.OFrameOri.m_ry = wobjData.OFrame.Data[4];
    params.OFrameOri.m_rz = wobjData.OFrame.Data[3];

    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::GetWobjParam(quint16 wobjNo, WobjParams &params)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjData wobjData;
    if (!_IWobj->GetWobjParam(wobjNo, wobjData)) {
        return false;
    }

    params.RobHold = wobjData.RobHold;
    params.UFFix = wobjData.UFFix;
    memcpy(params.UFMec, wobjData.UFMec, MECHUNIT_NAME_LENGTH);

    params.UFramePos.m_x = wobjData.UFrame.Data[0];
    params.UFramePos.m_y = wobjData.UFrame.Data[1];
    params.UFramePos.m_z = wobjData.UFrame.Data[2];
    params.UFrameOri.m_rx = wobjData.UFrame.Data[5];
    params.UFrameOri.m_ry = wobjData.UFrame.Data[4];
    params.UFrameOri.m_rz = wobjData.UFrame.Data[3];

    params.OFramePos.m_x = wobjData.OFrame.Data[0];
    params.OFramePos.m_y = wobjData.OFrame.Data[1];
    params.OFramePos.m_z = wobjData.OFrame.Data[2];
    params.OFrameOri.m_rx = wobjData.OFrame.Data[5];
    params.OFrameOri.m_ry = wobjData.OFrame.Data[4];
    params.OFrameOri.m_rz = wobjData.OFrame.Data[3];

    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::SetWobjParam(quint16 wobjNo,
                                          const WobjParams &params)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjData wobjData;

    wobjData.RobHold = params.RobHold;
    wobjData.UFFix = params.UFFix;
    memcpy(wobjData.UFMec, params.UFMec, MECHUNIT_NAME_LENGTH);

    Pose uFrame;
    uFrame.Data[0] = params.UFramePos.m_x;
    uFrame.Data[1] = params.UFramePos.m_y;
    uFrame.Data[2] = params.UFramePos.m_z;
    uFrame.Data[5] = params.UFrameOri.m_rx;
    uFrame.Data[4] = params.UFrameOri.m_ry;
    uFrame.Data[3] = params.UFrameOri.m_rz;
    wobjData.UFrame = uFrame;

    Pose oFrame;
    oFrame.Data[0] = params.OFramePos.m_x;
    oFrame.Data[1] = params.OFramePos.m_y;
    oFrame.Data[2] = params.OFramePos.m_z;
    oFrame.Data[5] = params.OFrameOri.m_rx;
    oFrame.Data[4] = params.OFrameOri.m_ry;
    oFrame.Data[3] = params.OFrameOri.m_rz;
    wobjData.OFrame = oFrame;

    if (!_IWobj->SetWobjParam(wobjNo, wobjData)) {
        return false;
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::SaveWObjParams(int wobjNo, WobjParams *data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjData wobjData;

    wobjData.RobHold = data->RobHold;
    wobjData.UFFix = data->UFFix;
    memcpy(wobjData.UFMec, data->UFMec, MECHUNIT_NAME_LENGTH);

    Pose uFrame;
    uFrame.Data[0] = data->UFramePos.m_x;
    uFrame.Data[1] = data->UFramePos.m_y;
    uFrame.Data[2] = data->UFramePos.m_z;
    uFrame.Data[5] = data->UFrameOri.m_rx;
    uFrame.Data[4] = data->UFrameOri.m_ry;
    uFrame.Data[3] = data->UFrameOri.m_rz;
    wobjData.UFrame = uFrame;

    Pose oFrame;
    oFrame.Data[0] = data->OFramePos.m_x;
    oFrame.Data[1] = data->OFramePos.m_y;
    oFrame.Data[2] = data->OFramePos.m_z;
    oFrame.Data[5] = data->OFrameOri.m_rx;
    oFrame.Data[4] = data->OFrameOri.m_ry;
    oFrame.Data[3] = data->OFrameOri.m_rz;
    wobjData.OFrame = oFrame;

    qDebug() << "wobj save uffix = " << wobjData.UFFix;
    if (!_IWobj->Save(wobjNo, &wobjData)) {
        qDebug() << "Call Wobj Func Save Failed.";
        return false;
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::RefreshWObjParams(int wobjNo, WobjParams *data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjData wobjData;
    if (!_IWobj->Refresh(wobjNo, &wobjData)) {
        return false;
    }

    qDebug() << "wobj refresh uffix = " << wobjData.UFFix;
    data->RobHold = wobjData.RobHold;
    data->UFFix = wobjData.UFFix;
    memcpy(data->UFMec, wobjData.UFMec, MECHUNIT_NAME_LENGTH);

    data->UFramePos.m_x = wobjData.UFrame.Data[0];
    data->UFramePos.m_y = wobjData.UFrame.Data[1];
    data->UFramePos.m_z = wobjData.UFrame.Data[2];
    data->UFrameOri.m_rx = wobjData.UFrame.Data[5];
    data->UFrameOri.m_ry = wobjData.UFrame.Data[4];
    data->UFrameOri.m_rz = wobjData.UFrame.Data[3];

    data->OFramePos.m_x = wobjData.OFrame.Data[0];
    data->OFramePos.m_y = wobjData.OFrame.Data[1];
    data->OFramePos.m_z = wobjData.OFrame.Data[2];
    data->OFrameOri.m_rx = wobjData.OFrame.Data[5];
    data->OFrameOri.m_ry = wobjData.OFrame.Data[4];
    data->OFrameOri.m_rz = wobjData.OFrame.Data[3];
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::ClearWobjParams(int wobjNo)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IWobj->Clear(wobjNo);
}

void WObjCalibrateInterface::HoldTypeUFrameCalibMethodSearch(
    Robot_WObjType type, QVector<QString> &vecMethods)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> vecResult =
        _IWobj->HoldTypeUFrameCalibMethodSearch(
            static_cast<InoRobBusiness::RobotHoldWobjType>(type));
    for (auto &it : vecResult) {
        vecMethods.append(QString::fromStdString(it));
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void WObjCalibrateInterface::HoldTypeOFrameCalibMethodSearch(
    Robot_WObjType type, QVector<QString> &vecMethods)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> vecResult =
        _IWobj->HoldTypeOFrameCalibMethodSearch(
            static_cast<InoRobBusiness::RobotHoldWobjType>(type));
    for (auto &it : vecResult) {
        vecMethods.append(QString::fromStdString(it));
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void WObjCalibrateInterface::WObjUFramePointsNameQuery(
    Robot_WObj_UFrame_CalMethod method, QVector<QString> &vecPointsName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> vecResult =
        _IWobj->CalibMethodTeachPointNameSearch(
            static_cast<InoRobBusiness::WobjUFrameCalibMethod>(method));
    for (auto &it : vecResult) {
        vecPointsName.append(QString::fromStdString(it));
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

void WObjCalibrateInterface::WObjOFramePointsNameQuery(
    Robot_WObj_OFrame_CalMethod method, QVector<QString> &vecPointsName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> vecResult =
        _IWobj->CalibMethodTeachPointNameSearch(
            static_cast<InoRobBusiness::WobjOFrameCalibMethod>(method));
    for (auto &it : vecResult) {
        vecPointsName.append(QString::fromStdString(it));
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
}

bool WObjCalibrateInterface::WObjCalibrate(const QString &mechUnitName, 
                                           Robot_WObjType type, 
                                           bool isUFFix, 
                                           const CalibratePoints &midUFramePos, 
                                           const CalibratePoints &midOFramePos, 
                                           const Pos &oldUFramePos,
                                           const Ori &oldUFrameOri, 
                                           Pos &uFrameCalibResultPos, 
                                           Ori &uFrameCalibResultOri, 
                                           Pos &oFrameCalibResultPos,
                                           Ori &oFrameCalibResultOri)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    CsCalibPoints csUFrameCaliPoints;
    csUFrameCaliPoints.MethodType = static_cast<int>(midUFramePos.MethodType);
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csUFrameCaliPoints.Points[i].RPosData[0] =
            midUFramePos.Points[i].pos.m_x;
        csUFrameCaliPoints.Points[i].RPosData[1] =
            midUFramePos.Points[i].pos.m_y;
        csUFrameCaliPoints.Points[i].RPosData[2] =
            midUFramePos.Points[i].pos.m_z;
        csUFrameCaliPoints.Points[i].RPosData[5] =
            midUFramePos.Points[i].ori.m_rx;
        csUFrameCaliPoints.Points[i].RPosData[4] =
            midUFramePos.Points[i].ori.m_ry;
        csUFrameCaliPoints.Points[i].RPosData[3] =
            midUFramePos.Points[i].ori.m_rz;
        memcpy(csUFrameCaliPoints.Points[i].ArmParm,
               midUFramePos.Points[i].ArmParm,
               sizeof(midUFramePos.Points[i].ArmParm));
        memcpy(csUFrameCaliPoints.Points[i].EPosData,
               midUFramePos.Points[i].EPosData,
               sizeof(midUFramePos.Points[i].ArmParm));
    }

    CsCalibPoints csOFrameCaliPoints;
    csOFrameCaliPoints.MethodType = static_cast<int>(midOFramePos.MethodType);
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csOFrameCaliPoints.Points[i].RPosData[0] =
            midOFramePos.Points[i].pos.m_x;
        csOFrameCaliPoints.Points[i].RPosData[1] =
            midOFramePos.Points[i].pos.m_y;
        csOFrameCaliPoints.Points[i].RPosData[2] =
            midOFramePos.Points[i].pos.m_z;
        csOFrameCaliPoints.Points[i].RPosData[5] =
            midOFramePos.Points[i].ori.m_rx;
        csOFrameCaliPoints.Points[i].RPosData[4] =
            midOFramePos.Points[i].ori.m_ry;
        csOFrameCaliPoints.Points[i].RPosData[3] =
            midOFramePos.Points[i].ori.m_rz;
        memcpy(csOFrameCaliPoints.Points[i].ArmParm,
               midOFramePos.Points[i].ArmParm,
               sizeof(midOFramePos.Points[i].ArmParm));
        memcpy(csOFrameCaliPoints.Points[i].EPosData,
               midOFramePos.Points[i].EPosData,
               sizeof(midOFramePos.Points[i].ArmParm));
    }

    Pose oldUFrame;
    oldUFrame.Data[0] = oldUFramePos.m_x;
    oldUFrame.Data[1] = oldUFramePos.m_y;
    oldUFrame.Data[2] = oldUFramePos.m_z;
    oldUFrame.Data[5] = oldUFrameOri.m_rx;
    oldUFrame.Data[4] = oldUFrameOri.m_ry;
    oldUFrame.Data[3] = oldUFrameOri.m_rz;

    Pose uFrameCalibResult;
    Pose oFrameCalibResult;
    if (!_IWobj->
         Calibrate(mechUnitName.toLocal8Bit().data(),
            static_cast<InoRobBusiness::RobotHoldWobjType>(type),
                isUFFix, csUFrameCaliPoints, csOFrameCaliPoints, oldUFrame,
                    uFrameCalibResult, oFrameCalibResult)) {
        qDebug() << "WObj Calibrate Failed.";
        return false;
    }

    uFrameCalibResultPos.m_x = uFrameCalibResult.Data[0];
    uFrameCalibResultPos.m_y = uFrameCalibResult.Data[1];
    uFrameCalibResultPos.m_z = uFrameCalibResult.Data[2];

    uFrameCalibResultOri.m_rx = uFrameCalibResult.Data[5];
    uFrameCalibResultOri.m_ry = uFrameCalibResult.Data[4];
    uFrameCalibResultOri.m_rz = uFrameCalibResult.Data[3];

    oFrameCalibResultPos.m_x = oFrameCalibResult.Data[0];
    oFrameCalibResultPos.m_y = oFrameCalibResult.Data[1];
    oFrameCalibResultPos.m_z = oFrameCalibResult.Data[2];

    oFrameCalibResultOri.m_rx = oFrameCalibResult.Data[5];
    oFrameCalibResultOri.m_ry = oFrameCalibResult.Data[4];
    oFrameCalibResultOri.m_rz = oFrameCalibResult.Data[3];
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::SaveWObjCalibratePoints(
    quint16 wobjNo, const CalibratePoints &uFramePoint,
    const CalibratePoints &oFramePoint)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    CsCalibPoints csUFrameCaliPoints;
    csUFrameCaliPoints.MethodType = uFramePoint.MethodType;
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csUFrameCaliPoints.Points[i].RPosData[0] =
            uFramePoint.Points[i].pos.m_x;
        csUFrameCaliPoints.Points[i].RPosData[1] =
            uFramePoint.Points[i].pos.m_y;
        csUFrameCaliPoints.Points[i].RPosData[2] =
            uFramePoint.Points[i].pos.m_z;
        csUFrameCaliPoints.Points[i].RPosData[5] =
            uFramePoint.Points[i].ori.m_rx;
        csUFrameCaliPoints.Points[i].RPosData[4] =
            uFramePoint.Points[i].ori.m_ry;
        csUFrameCaliPoints.Points[i].RPosData[3] =
            uFramePoint.Points[i].ori.m_rz;
        memcpy(csUFrameCaliPoints.Points[i].ArmParm,
               uFramePoint.Points[i].ArmParm,
               sizeof(uFramePoint.Points[i].ArmParm));
        memcpy(csUFrameCaliPoints.Points[i].EPosData,
               uFramePoint.Points[i].EPosData,
               sizeof(uFramePoint.Points[i].ArmParm));
    }

    CsCalibPoints csOFrameCaliPoints;
    csOFrameCaliPoints.MethodType = oFramePoint.MethodType;
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csOFrameCaliPoints.Points[i].RPosData[0] =
            oFramePoint.Points[i].pos.m_x;
        csOFrameCaliPoints.Points[i].RPosData[1] =
            oFramePoint.Points[i].pos.m_y;
        csOFrameCaliPoints.Points[i].RPosData[2] =
            oFramePoint.Points[i].pos.m_z;
        csOFrameCaliPoints.Points[i].RPosData[5] =
            oFramePoint.Points[i].ori.m_rx;
        csOFrameCaliPoints.Points[i].RPosData[4] =
            oFramePoint.Points[i].ori.m_ry;
        csOFrameCaliPoints.Points[i].RPosData[3] =
            oFramePoint.Points[i].ori.m_rz;
        memcpy(csOFrameCaliPoints.Points[i].ArmParm,
               oFramePoint.Points[i].ArmParm,
               sizeof(oFramePoint.Points[i].ArmParm));
        memcpy(csOFrameCaliPoints.Points[i].EPosData,
               oFramePoint.Points[i].EPosData,
               sizeof(oFramePoint.Points[i].ArmParm));
    }
    if (!_IWobj->SaveCalibratePoints(
            wobjNo, csUFrameCaliPoints, csOFrameCaliPoints)) {
        qDebug() << "Wobj Save Mid Points Failed.";
        return false;
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

bool WObjCalibrateInterface::RefreshWObjCalibratePoints(
    quint16 wobjNo, CalibratePoints &uFramePoint, CalibratePoints &oFramePoint)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    WobjCalibData wobjCalibData;
    if (!_IWobj->RefreshCalibratePoints(wobjCalibData)) {
        qDebug() << "Refresh WObj Mid Points Failed.";
        return false;
    }

    uFramePoint.MethodType = wobjCalibData.UMethodDatas[wobjNo].MethodType;
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        uFramePoint.Points[i].pos.m_x =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[0];
        uFramePoint.Points[i].pos.m_y =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[1];
        uFramePoint.Points[i].pos.m_z =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[2];
        uFramePoint.Points[i].ori.m_rx =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[5];
        uFramePoint.Points[i].ori.m_ry =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[4];
        uFramePoint.Points[i].ori.m_rz =
            wobjCalibData.UMethodDatas[wobjNo].Points[i].RPosData[3];
        memcpy(uFramePoint.Points[i].ArmParm,
               wobjCalibData.UMethodDatas[wobjNo].Points[i].ArmParm,
               sizeof(wobjCalibData.UMethodDatas[wobjNo].Points[i].ArmParm));
        memcpy(uFramePoint.Points[i].EPosData,
               wobjCalibData.UMethodDatas[wobjNo].Points[i].EPosData,
               sizeof(wobjCalibData.UMethodDatas[wobjNo].Points[i].ArmParm));
    }

    oFramePoint.MethodType = wobjCalibData.OMethodDatas[wobjNo].MethodType;
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        oFramePoint.Points[i].pos.m_x =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[0];
        oFramePoint.Points[i].pos.m_y =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[1];
        oFramePoint.Points[i].pos.m_z =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[2];
        oFramePoint.Points[i].ori.m_rx =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[5];
        oFramePoint.Points[i].ori.m_ry =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[4];
        oFramePoint.Points[i].ori.m_rz =
            wobjCalibData.OMethodDatas[wobjNo].Points[i].RPosData[3];
        memcpy(oFramePoint.Points[i].ArmParm,
               wobjCalibData.OMethodDatas[wobjNo].Points[i].ArmParm,
               sizeof(wobjCalibData.OMethodDatas[wobjNo].Points[i].ArmParm));
        memcpy(oFramePoint.Points[i].EPosData,
               wobjCalibData.OMethodDatas[wobjNo].Points[i].EPosData,
               sizeof(wobjCalibData.OMethodDatas[wobjNo].Points[i].ArmParm));
    }
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return true;
}

QString WObjCalibrateInterface::CalibUFrameMethodNameSearch(
    Robot_WObj_UFrame_CalMethod method)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sName = _IWobj->CalibMethodNameSearch(
        static_cast<InoRobBusiness::WobjUFrameCalibMethod>(method));
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return QString::fromStdString(sName);
}

QString WObjCalibrateInterface::CalibOFrameMethodNameSearch(
    Robot_WObj_OFrame_CalMethod method)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sName = _IWobj->CalibMethodNameSearch(
        static_cast<InoRobBusiness::WobjOFrameCalibMethod>(method));
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return QString::fromStdString(sName);
}

bool WObjCalibrateInterface::WObjMoveToPoint(const Pos &pos,
                                             const Ori &ori,
                                             int arm[4],
                                             Robot_MoveType type,
                                             Robot_WObjType method)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    RobPos destPose;
    destPose.RPosData[0] = pos.m_x;
    destPose.RPosData[1] = pos.m_y;
    destPose.RPosData[2] = pos.m_z;
    destPose.RPosData[5] = ori.m_rx;
    destPose.RPosData[4] = ori.m_ry;
    destPose.RPosData[3] = ori.m_rz;
    memcpy(&destPose.ArmParm[0], &arm[0], sizeof(int) * 4);
    bool bRet = _IWobj->MoveToPoint(
        destPose, static_cast<MoveType>(type),
            static_cast<InoRobBusiness::RobotHoldWobjType>(method));
    LOG_TRACE(QString("[%1][%2][%3]")
            .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return bRet;
}

