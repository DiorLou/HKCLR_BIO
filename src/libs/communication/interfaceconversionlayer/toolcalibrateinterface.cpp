#include "toolcalibrateinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "InoRobBusiness/Controller/Tool/ITool.h"
#include "communication.h"

#include "cobotlogex.h"
#include "modulesutils.h"

quint16 LoadInterface::GetLoadCount()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetCount();
}

bool LoadInterface::GetLoadParam(quint16 loadNo, LoadParams &loadParam)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LoadData loadData;
    if (!_ILoad->GetLoadParam(loadNo, loadData)) {
        return false;
    }

    memcpy(&loadParam, &loadData, sizeof(loadData));
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool LoadInterface::SetLoadParam(quint16 loadNo, const LoadParams &loadParam)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LoadData loadData;
    memcpy(&loadData, &loadParam, sizeof(loadParam));
    FREQ_LOG_PRINT_TIMESTAMP
    return _ILoad->SetLoadParam(loadNo, loadData);
}

bool LoadInterface::LoadSave(quint16 loadId, const LoadParams &params, bool bSaveNeed)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LoadData loadData;
    memcpy(&loadData, &params, sizeof(params));
    FREQ_LOG_PRINT_TIMESTAMP
    return _ILoad->Save(static_cast<int>(loadId), loadData, bSaveNeed);
}

bool LoadInterface::LoadRefresh(quint16 loadId, LoadParams &params)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LoadData loadData;
    if (!_ILoad->Refresh(static_cast<int>(loadId), loadData)) {
        return false;
    }

    memcpy(&params, &loadData, sizeof(loadData));
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool LoadInterface::LoadClear(quint16 loadId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->Clear(loadId);
}

double LoadInterface::GetMinMass()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMinMass();
}

double LoadInterface::GetMaxMass()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMaxMass();
}

double LoadInterface::GetMinCentroid()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMinCentroid();
}

double LoadInterface::GetMaxCentroid()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMaxCentroid();
}

double LoadInterface::GetMinInertia()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMinInertia();
}

double LoadInterface::GetMaxInertia()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ILoad->GetMaxInertia();
}

bool LoadInterface::CheckCurLoadValid(const LoadParams &params)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LoadData loadData;
    memcpy(&loadData, &params, sizeof(params));
    FREQ_LOG_PRINT_TIMESTAMP
    return _ILoad->CheckCurLoadValid(loadData);
}

QString LoadInterface::LoadIDNameSearch(quint16 loadId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sName = _ILoad->LoadIDNameSearch(
        static_cast<InoRobBusiness::LoadID>(loadId));
    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(sName);
}

////////////////////////////////////////////////////////////////////////////////////////

bool ToolCalibrateInterface::SetCurrentId(quint16 currentId)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ITool->SetCurrentId(currentId);
}

bool ToolCalibrateInterface::CurrentIsRobotHold(bool &result)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ITool->CurrentIsRobotHold(result);
}

void ToolCalibrateInterface::GetToolItem(QVector<QString> &vecItems)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    vector<InoRobBusiness::ToolItem> vecResult =
        _ITool->GetToolItem();
    for (auto &item : vecResult) {
        vecItems.append(QString::fromStdString(item.ItemName));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

bool ToolCalibrateInterface::GetToolParam(quint16 toolNo, ToolParams &toolParam)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    ToolData toolData;

    if (!comm()->isConnected()) return false;

    if (!_ITool->GetToolParam(toolNo, toolData)) {
        return false;
    }

    Pos pos(toolData.TFrame.Data[0], toolData.TFrame.Data[1],
            toolData.TFrame.Data[2]);
    Ori ori(toolData.TFrame.Data[5], toolData.TFrame.Data[4],
            toolData.TFrame.Data[3]);

    LoadParams lParams;
    memcpy(&lParams, &toolData.TLoad, sizeof(toolData.TLoad));

    toolParam.SetParams(toolData.RobHold, pos, ori, lParams);
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool ToolCalibrateInterface::SetToolParam(quint16 toolNo, const ToolParams &toolParam)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    ToolData toolData;

    toolData.RobHold = toolParam.robHold;
    toolData.TFrame.Data[0] = toolParam.pos.m_x;
    toolData.TFrame.Data[1] = toolParam.pos.m_y;
    toolData.TFrame.Data[2] = toolParam.pos.m_z;
    toolData.TFrame.Data[5] = toolParam.ori.m_rx;
    toolData.TFrame.Data[4] = toolParam.ori.m_ry;
    toolData.TFrame.Data[3] = toolParam.ori.m_rz;
    memcpy(&toolData.TLoad, &toolParam.tLoad, sizeof(toolParam.tLoad));

    FREQ_LOG_PRINT_TIMESTAMP
    return _ITool->SetToolParam(toolNo, toolData);
}

bool ToolCalibrateInterface::Save(int toolNo, ToolParams *toolParam, bool bSaveNeed)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    ToolData toolData;

    toolData.RobHold = toolParam->robHold;
    toolData.TFrame.Data[0] = toolParam->pos.m_x;
    toolData.TFrame.Data[1] = toolParam->pos.m_y;
    toolData.TFrame.Data[2] = toolParam->pos.m_z;
    toolData.TFrame.Data[5] = toolParam->ori.m_rx;
    toolData.TFrame.Data[4] = toolParam->ori.m_ry;
    toolData.TFrame.Data[3] = toolParam->ori.m_rz;
    memcpy(&toolData.TLoad, &toolParam->tLoad, sizeof(toolParam->tLoad));

    FREQ_LOG_PRINT_TIMESTAMP
    return _ITool->Save(toolNo, &toolData, bSaveNeed);
}

bool ToolCalibrateInterface::Refresh(int toolNo, ToolParams *toolParam)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    ToolData toolData;

    if (!_ITool->Refresh(toolNo, &toolData)) {
        return false;
    }

    Pos pos(toolData.TFrame.Data[0], toolData.TFrame.Data[1],
            toolData.TFrame.Data[2]);
    Ori ori(toolData.TFrame.Data[5], toolData.TFrame.Data[4],
            toolData.TFrame.Data[3]);

    LoadParams lParams;
    memcpy(&lParams, &toolData.TLoad, sizeof(toolData.TLoad));

    toolParam->SetParams(toolData.RobHold, pos, ori, lParams);
    FREQ_LOG_PRINT_TIMESTAMP
    return true;   
}

bool ToolCalibrateInterface::Clear(int toolNo)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ITool->Clear(toolNo);
}

QString ToolCalibrateInterface::ToolIdNameSearch(quint16 id)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sName = _ITool->ToolIdNameSearch(
        static_cast<InoRobBusiness::ToolId>(id));
    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(sName);
}

void ToolCalibrateInterface::HoldTypeCalibMethodSearch(
    Robot_ToolType type, QVector<QString> &vecMethods)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    vector<string> vecRet = _ITool->HoldTypeCalibMethodSearch(
        static_cast<InoRobBusiness::RobotHoldToolType>(type));
    for (auto &it : vecRet) {
        vecMethods.append(QString::fromStdString(it));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

QString ToolCalibrateInterface::CalibMethodNameSearch(
    Robot_ToolCalibrateType method)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string sMethodName = _ITool->CalibMethodNameSearch(
        static_cast<InoRobBusiness::ToolCalibMethod>(method));
    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(sMethodName);
}

bool ToolCalibrateInterface::Calibrate(const CalibratePoints &midPos,
                                       Pos &calResultPos, Ori &calResultOri)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    CsCalibPoints csCaliPoints;
    csCaliPoints.MethodType = static_cast<int>(midPos.MethodType);

    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csCaliPoints.Points[i].RPosData[0] = midPos.Points[i].pos.m_x;
        csCaliPoints.Points[i].RPosData[1] = midPos.Points[i].pos.m_y;
        csCaliPoints.Points[i].RPosData[2] = midPos.Points[i].pos.m_z;
        csCaliPoints.Points[i].RPosData[5] = midPos.Points[i].ori.m_rx;
        csCaliPoints.Points[i].RPosData[4] = midPos.Points[i].ori.m_ry;
        csCaliPoints.Points[i].RPosData[3] = midPos.Points[i].ori.m_rz;
        memcpy(csCaliPoints.Points[i].ArmParm, midPos.Points[i].ArmParm,
               sizeof(midPos.Points[i].ArmParm));
        memcpy(csCaliPoints.Points[i].EPosData, midPos.Points[i].EPosData,
               sizeof(midPos.Points[i].ArmParm));
    }

    Pose calResultPose;

    if (!_ITool->Calibrate(csCaliPoints, calResultPose)) {
        qDebug() << "Call Model Func Calibrate Failed.";
        return false;
    }

    calResultPos.m_x = calResultPose.Data[0];
    calResultPos.m_y = calResultPose.Data[1];
    calResultPos.m_z = calResultPose.Data[2];
    calResultOri.m_rx = calResultPose.Data[5];
    calResultOri.m_ry = calResultPose.Data[4];
    calResultOri.m_rz = calResultPose.Data[3];

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool ToolCalibrateInterface::SaveCalibratePoints(quint16 toolNo,
                                                 const CalibratePoints &point)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    CsCalibPoints csCaliPoints;
    csCaliPoints.MethodType = static_cast<int>(point.MethodType);

    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        csCaliPoints.Points[i].RPosData[0] = point.Points[i].pos.m_x;
        csCaliPoints.Points[i].RPosData[1] = point.Points[i].pos.m_y;
        csCaliPoints.Points[i].RPosData[2] = point.Points[i].pos.m_z;
        csCaliPoints.Points[i].RPosData[5] = point.Points[i].ori.m_rx;
        csCaliPoints.Points[i].RPosData[4] = point.Points[i].ori.m_ry;
        csCaliPoints.Points[i].RPosData[3] = point.Points[i].ori.m_rz;
        memcpy(csCaliPoints.Points[i].ArmParm, point.Points[i].ArmParm,
               sizeof(point.Points[i].ArmParm));
        memcpy(csCaliPoints.Points[i].EPosData, point.Points[i].EPosData,
               sizeof(point.Points[i].ArmParm));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return _ITool->SaveCalibratePoints(toolNo, csCaliPoints);
}

bool ToolCalibrateInterface::RefreshCalibratePoints(quint16 toolNo,
                                                    CalibratePoints &points)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    ToolCalibData toolCalData;
    if (!_ITool->RefreshCalibratePoints(toolCalData)) {
        return false;
    }

    if (toolCalData.MethodDatas.size() <= toolNo) {
        qDebug() << "Controller RefreshCalibratePoints Func Failed, toolNo : "
                 << toolNo
                 << ", ArrSize : " << toolCalData.MethodDatas.size();
        return false;
    }
    CsCalibPoints csCaliPoints = std::move(toolCalData.MethodDatas[toolNo]);

    points.MethodType = static_cast<Robot_ToolCalibrateType>(
        csCaliPoints.MethodType);
    for (int i = 0; i < CALIB_POINTS_COUNT; ++i) {
        points.Points[i].pos.m_x = csCaliPoints.Points[i].RPosData[0];
        points.Points[i].pos.m_y = csCaliPoints.Points[i].RPosData[1];
        points.Points[i].pos.m_z = csCaliPoints.Points[i].RPosData[2];
        points.Points[i].ori.m_rx = csCaliPoints.Points[i].RPosData[5];
        points.Points[i].ori.m_ry = csCaliPoints.Points[i].RPosData[4];
        points.Points[i].ori.m_rz = csCaliPoints.Points[i].RPosData[3];
        memcpy(points.Points[i].ArmParm, csCaliPoints.Points[i].ArmParm,
               sizeof(csCaliPoints.Points[i].ArmParm));
        memcpy(points.Points[i].EPosData, csCaliPoints.Points[i].EPosData,
               sizeof(csCaliPoints.Points[i].ArmParm));
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool ToolCalibrateInterface::MoveToPoint(Robot_ToolCalibrateType method,
                                         const Pos &pos, const Ori &ori,
                                         Robot_MoveType type)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    InoRobBusiness::ToolCalibMethod toolCalMethod =
        static_cast<InoRobBusiness::ToolCalibMethod>(method);

    RobPos robPos;
    robPos.RPosData[0] = pos.m_x;
    robPos.RPosData[1] = pos.m_y;
    robPos.RPosData[2] = pos.m_z;
    robPos.RPosData[5] = ori.m_rz;
    robPos.RPosData[4] = ori.m_ry;
    robPos.RPosData[3] = ori.m_rx;

    robPos.ArmParm[3] = 1;

    MoveType moveType = static_cast<MoveType>(type);
    if (!_ITool->MoveToPoint(
            toolCalMethod, robPos, moveType)) {
        qDebug() << "Call Controller MoveToPoint Func Failed";
        return false;
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

QString ToolCalibrateInterface::ToolExcuteMoveTypeNameSearch(Robot_MoveType type)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    MoveType moveType = static_cast<MoveType>(type);
    std::string sName =
        _ITool->ToolExcuteMoveTypeNameSearch(moveType);
    LOG_TRACE(QString("[%1][%2][%3]")
                .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return QString::fromStdString(sName);
}

void ToolCalibrateInterface::ToolPointsNameQuery(
    Robot_ToolCalibrateType method, QVector<QString> &vecPointsName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::vector<std::string> vecResult =
        _ITool->CalibMethodTeachPointNameSearch(
            static_cast<InoRobBusiness::ToolCalibMethod>(method));
    for (auto &it : vecResult) {
        vecPointsName.append(QString::fromStdString(it));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

int ToolCalibrateInterface::CalibMethodByName(const QString &name)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return static_cast<int>(
        _ITool->CalibMethodByName(name.toStdString()));
}

string ToolCalibrateInterface::ToolCalibrateTipSearch(Robot_ToolCalibrateType method)
{
    InoRobBusiness::ToolCalibMethod mtd =
        static_cast<InoRobBusiness::ToolCalibMethod>(method);
    return _ITool->ToolCalibrateTipSearch(mtd);
}
