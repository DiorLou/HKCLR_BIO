#include "robotpointinterface_p.h"
#include "robotpointinterface.h"
#include "communication.h"
#include "metatypeconversion.h"
#include "InoRobBusiness/RobotParam/IRobotParam.h"
#include "InoRobBusiness/Controller/StatusChecks/StatusChecks.h"
#include "communicationengine.h"
#include "projectinfo.h"
#include <QObject>
#include "cobotlogex.h"
#include "modulesutils.h"

namespace Internal {

RobotPointInterfacePrivate::RobotPointInterfacePrivate(RobotPointInterface *interface):
    q(interface)
{
}

IController *RobotPointInterfacePrivate::controller()
{
    return q->controller();
}

void RobotPointInterfacePrivate::setCurRPointFile(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!sName.isEmpty()) {
        m_sRPointFileName = sName.toStdString();
    }
}

QString RobotPointInterfacePrivate::curRPointFile() const
{
    return QString::fromStdString(m_sRPointFileName);
}

void RobotPointInterfacePrivate::setCurLoadedRPointFile(std::string sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!sName.empty()) {
        m_sLoadedRPointFileName = std::move(sName);
    }
}

QString RobotPointInterfacePrivate::curLoadedRPointFile() const
{
    return QString::fromStdString(m_sLoadedRPointFileName);
}

QVector<InoRPointInfo> RobotPointInterfacePrivate::readAllRPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string errMsg;
    QVector<InoRPointInfo> infos;
    std::vector<MRobPosItem> points;
    InoRPointInfo info;
    infos.clear();

    std::vector<std::string> vecFiles = q->comm()->project()->GetRPointFileList();
    for (const std::string &fileName : vecFiles) {
        // 读取点位
        int ret = q->comm()->project()->GetRPoint()->ReadPoints(points, fileName);
        if (ret != ERR_OK) {
            return infos;
        }

        // 赋值
        size_t count = points.size();
        for (size_t i = 0; i < count; i++) {
            info.pointNo = points[i].PointNo;  // 点位序号
            info.name = QString("%1%2%3").arg("P[").arg(points[i].PointNo, 4, 10, QLatin1Char('0')).arg("]");
            info.label = QString::fromStdString(points[i].LabelName);                                // 标签
            info.description = QString::fromStdString(points[i].Description);                        // 描述(备注)
            info.pos.RPosData[0] = QString::number(points[i].PData.RPosData[0], 'f', 3).toDouble();  // XYZABC
            info.pos.RPosData[1] = QString::number(points[i].PData.RPosData[1], 'f', 3).toDouble();
            info.pos.RPosData[2] = QString::number(points[i].PData.RPosData[2], 'f', 3).toDouble();
            info.pos.RPosData[3] = QString::number(points[i].PData.RPosData[3], 'f', 3).toDouble();
            info.pos.RPosData[4] = QString::number(points[i].PData.RPosData[4], 'f', 3).toDouble();
            info.pos.RPosData[5] = QString::number(points[i].PData.RPosData[5], 'f', 3).toDouble();
            info.pos.ArmParm[0] = QString::number(points[i].PData.ArmParm[0], 'f', 3).toDouble();  // 臂参数
            info.pos.ArmParm[1] = QString::number(points[i].PData.ArmParm[1], 'f', 3).toDouble();
            info.pos.ArmParm[2] = QString::number(points[i].PData.ArmParm[2], 'f', 3).toDouble();
            info.pos.ArmParm[3] = QString::number(points[i].PData.ArmParm[3], 'f', 3).toDouble();
            info.pos.EPosData[0] = QString::number(points[i].PData.EPosData[0], 'f', 3).toDouble();  // E1~E6
            info.pos.EPosData[1] = QString::number(points[i].PData.EPosData[1], 'f', 3).toDouble();
            info.pos.EPosData[2] = QString::number(points[i].PData.EPosData[2], 'f', 3).toDouble();
            info.pos.EPosData[3] = QString::number(points[i].PData.EPosData[3], 'f', 3).toDouble();
            info.pos.EPosData[4] = QString::number(points[i].PData.EPosData[4], 'f', 3).toDouble();
            info.pos.EPosData[5] = QString::number(points[i].PData.EPosData[5], 'f', 3).toDouble();
            infos.append(info);
        }
    }

    std::sort(infos.begin(), infos.end(),
              [](const InoRPointInfo &a, const InoRPointInfo &b) {
                  return a.pointNo < b.pointNo;
              });

    FREQ_LOG_PRINT_TIMESTAMP
    return infos;
}

QVector<InoRPointInfo> RobotPointInterfacePrivate::readRPoints(std::string sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    std::string errMsg;
    QVector<InoRPointInfo> infos;

    sFileName = sFileName.empty() ? m_sRPointFileName : sFileName;

    std::vector<MRobPosItem> points;
    InoRPointInfo info;
    infos.clear();

    // 读取点位
    int ret = q->comm()->project()->GetRPoint()->ReadPoints(points, sFileName);
    if (ret != ERR_OK) {
        return infos;
    }

    // 添加到缓存中
    q->comm()->project()->GetRPoint()->AddViewPoints(sFileName, points);

    // 赋值
    size_t count = points.size();
    for (size_t i = 0; i < count; i++) {
        info.pointNo = points[i].PointNo;  // 点位序号
        info.name = QString("%1%2%3").arg("P[").arg(points[i].PointNo, 4, 10, QLatin1Char('0')).arg("]");
        info.label = QString::fromStdString(points[i].LabelName);                                // 标签
        info.description = QString::fromStdString(points[i].Description);                        // 描述(备注)
        info.pos.RPosData[0] = QString::number(points[i].PData.RPosData[0], 'f', 3).toDouble();  // XYZABC
        info.pos.RPosData[1] = QString::number(points[i].PData.RPosData[1], 'f', 3).toDouble();
        info.pos.RPosData[2] = QString::number(points[i].PData.RPosData[2], 'f', 3).toDouble();
        info.pos.RPosData[3] = QString::number(points[i].PData.RPosData[3], 'f', 3).toDouble();
        info.pos.RPosData[4] = QString::number(points[i].PData.RPosData[4], 'f', 3).toDouble();
        info.pos.RPosData[5] = QString::number(points[i].PData.RPosData[5], 'f', 3).toDouble();
        info.pos.ArmParm[0] = QString::number(points[i].PData.ArmParm[0], 'f', 3).toDouble();  // 臂参数
        info.pos.ArmParm[1] = QString::number(points[i].PData.ArmParm[1], 'f', 3).toDouble();
        info.pos.ArmParm[2] = QString::number(points[i].PData.ArmParm[2], 'f', 3).toDouble();
        info.pos.ArmParm[3] = QString::number(points[i].PData.ArmParm[3], 'f', 3).toDouble();
        info.pos.EPosData[0] = QString::number(points[i].PData.EPosData[0], 'f', 3).toDouble();  // E1~E6
        info.pos.EPosData[1] = QString::number(points[i].PData.EPosData[1], 'f', 3).toDouble();
        info.pos.EPosData[2] = QString::number(points[i].PData.EPosData[2], 'f', 3).toDouble();
        info.pos.EPosData[3] = QString::number(points[i].PData.EPosData[3], 'f', 3).toDouble();
        info.pos.EPosData[4] = QString::number(points[i].PData.EPosData[4], 'f', 3).toDouble();
        info.pos.EPosData[5] = QString::number(points[i].PData.EPosData[5], 'f', 3).toDouble();
        infos.append(info);
    }

    std::sort(infos.begin(), infos.end(),
              [](const InoRPointInfo &a, const InoRPointInfo &b) {
                  return a.pointNo < b.pointNo;
              });

    FREQ_LOG_PRINT_TIMESTAMP
    return infos;
}

bool RobotPointInterfacePrivate::saveRPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = q->comm()->project()->GetRPoint()->SaveViewPoints(
        m_sRPointFileName, false);
    if (nRet != ERR_OK) {
        return false;
    }

    q->comm()->project()->updateLablesToTransfor();

    q->comm()->project()->sendSyncFlag(
        static_cast<int>(InoRobBusiness::SyncProjcetInfoType::SYNC_GOBAL_POINT));
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::saveAllRPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = q->comm()->project()->GetRPoint()->SaveAllViewPoints();
    if (nRet != ERR_OK) {
        return false;
    }

    q->comm()->project()->updateLablesToTransfor();

    q->comm()->project()->sendSyncFlag(
        static_cast<int>(InoRobBusiness::SyncProjcetInfoType::SYNC_GOBAL_POINT));
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::isRPointFileUpperLimit(int count)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> vecRPointFileList
        = q->comm()->project()->GetRPointFileList();

    FREQ_LOG_PRINT_TIMESTAMP
    return ((vecRPointFileList.size() + count) > MAX_NUM_RPOINTFILE);
}

bool RobotPointInterfacePrivate::isRPointFileNameValid(const QString &sName,
                                                std::string &errMsg)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return false;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return q->comm()->project()->GetRPoint()->IsPointFileNameValid(
        errMsg, sName.toStdString());
}

bool RobotPointInterfacePrivate::isRPointFileExist(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return true;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return q->comm()->project()->IsRPointFileExisted(sName.toStdString());
}

QString RobotPointInterfacePrivate::getDefaultRPFileName(QString baseName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> vecRPointFileList = q->comm()->project()->GetRPointFileList();

    std::string sFileName = "";
    if (baseName.isEmpty()) {
        sFileName = q->comm()->project()->GetRPoint()->NewDefaultFileName(vecRPointFileList);
    } else {
        sFileName = q->comm()->project()->GetRPoint()->NewDefaultFileName(
            vecRPointFileList, baseName.toStdString());
    }

    FREQ_LOG_PRINT_TIMESTAMP

    return QString::fromStdString(sFileName);
}

bool RobotPointInterfacePrivate::createRPointFile(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return false;
    }

    int nRet = q->comm()->project()->GetRPoint()->NewFile(sName.toStdString());
    if (ERR_OK != nRet) {
        return false;
    }

    q->comm()->project()->AddRPointConfig(sName.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::deleteRPointFile(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return false;
    }

    int nRet = q->comm()->project()->GetRPoint()->DelFile(sName.toStdString());
    if (ERR_OK != nRet) {
        return false;
    }

    q->comm()->project()->DelRPointConfig(sName.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::copyRPointFile(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return false;
    }

    q->comm()->project()->GetRPoint()->SetCopyFile(sName.toStdString());
    std::string copiedFileName = q->comm()->project()->GetRPoint()->GetCopiedName();
    // copied file name is without extension
    FREQ_LOG_PRINT_TIMESTAMP
    return (sName.contains(QString::fromStdString(copiedFileName)));
}

QString RobotPointInterfacePrivate::getCopiedRPointFileName()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string copiedFileName = q->comm()->project()->GetRPoint()->GetCopiedName();
    FREQ_LOG_PRINT_TIMESTAMP
    return QString::fromStdString(copiedFileName);
}

bool RobotPointInterfacePrivate::pasteRPointFile(const QString &sName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (sName.isEmpty()) {
        return false;
    }

    std::string copiedFileName = q->comm()->project()->GetRPoint()->GetCopiedName();
    if (copiedFileName.empty()) {
        return false;
    }

    int nRet = q->comm()->project()->GetRPoint()->PasteFile(copiedFileName,
                                                         sName.toStdString());
    qDebug() << "pasteRPointFile, ret = " << nRet << ", file = " << sName;
    if (ERR_OK != nRet) {
        return false;
    }

    q->comm()->project()->AddRPointConfig(sName.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::addRobotPointConfig(const QString &sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    q->comm()->project()->AddRPointConfig(sFileName.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::deleteRobotPointConfig(const QString &sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    q->comm()->project()->DelRPointConfig(sFileName.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::importLocalRPointFile(const QString &name, QString path)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    path = QDir::fromNativeSeparators(path);

    std::vector<std::string> paths;
    paths.push_back(path.toStdString());
    int nRet = q->comm()->project()->GetRPoint()->ImportFiles(paths);
    if (ERR_OK != nRet) {
        return false;
    }

    q->comm()->project()->AddRPointConfig(name.toStdString());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::exportRPointFile(QString name, QString folder)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> names;
    names.push_back(name.toStdString());

    folder = QDir::fromNativeSeparators(folder);
    int ret = q->comm()->project()->GetRPoint()->ExportFiles(
        names, folder.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool RobotPointInterfacePrivate::addRPoint(int &nIndex, const string &sLabelName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobPos pointValue;
    if (!readCurPoint(pointValue)) {
        return false;
    }

    MRobPosItem point;
    point.PointNo = -1;
    point.LabelName = sLabelName;
    point.Description = "";
    point.PData = MetaTypeConversion::inoApi2tp_robPos(pointValue);

    int nRet = q->comm()->project()->GetRPoint()->AddPoint(
        nIndex, m_sRPointFileName, point);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(pointValue);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::replaceRPointCoordValue(int index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobPos pointValue;
    if (!readCurPoint(pointValue)) {
        return false;
    }

    MRobPosItem point = q->comm()->project()->GetRPoint()->GetPoint(
        m_sRPointFileName, index);
    if (point.PointNo < 0) {
        return false;
    }

    point.PData = MetaTypeConversion::inoApi2tp_robPos(pointValue);
    int nRet = q->comm()->project()->GetRPoint()->ChangePoint(
        m_sRPointFileName, point, false);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(pointValue);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::copyRPoint(const std::vector<int> &indexs)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    q->comm()->project()->GetRPoint()->CopyPoints(m_sRPointFileName, indexs);

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

int RobotPointInterfacePrivate::pasteRPoint(std::vector<int> &indexs)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = q->comm()->project()->GetRPoint()->PastePoints(
        indexs, m_sRPointFileName);
    if (nRet != ERR_OK) {
        return INVALID_INDEX;
    }

    if (indexs.size() == 0) {
        return INVALID_INDEX;
    }

    for (const int &index : indexs) {
        InoRPointInfo info = getRPoint(indexs[0]);
        if (info.pointNo == INVALID_INDEX) {
            continue;
        }

        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(info);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, info.pointNo, info.label, pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::renameRPoint(int nIIndex, int nNewIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (nNewIndex < 0) {
        return false;
    }

    int nRet = q->comm()->project()->GetRPoint()->RenamePoint(
        m_sRPointFileName, nIIndex, nNewIndex);

    if (nRet == ERR_OK) {
        InoRPointInfo info = getRPoint(nNewIndex);
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(info);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, info.pointNo, info.label, pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::deleteRPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = q->comm()->project()->GetRPoint()->DelPoint(
        m_sRPointFileName, nIndex);

    if (nRet == ERR_OK) {
        ProjectRoadPointInfo::instance()->deleteRoadPointInfo(PREFIX_P, nIndex);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::changeRPoint(const InoRPointInfo &info, std::string sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    sFileName = sFileName.empty() ? m_sRPointFileName : sFileName;

    MRobPosItem point;
    point.PointNo = info.pointNo;
    point.LabelName = info.label.toStdString();
    point.Description = info.description.toStdString();
    point.PData = MetaTypeConversion::inoApi2tp_robPos(info.pos);

    int nRet = q->comm()->project()->GetRPoint()->ChangePoint(sFileName,
                                                           point, false);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(point);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::changeRPoint(const MRobPosItem &item)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (item.PointNo < 0) {
        return false;
    }

    int nRet = q->comm()->project()->GetRPoint()->ChangePoint(m_sLoadedRPointFileName,
                                                           item, false);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(item);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, item.PointNo, QString::fromStdString(item.LabelName), pt);
    }

    if (nRet == ERROR_OK) {
        q->comm()->project()->GetRPoint()->setModifyState(m_sLoadedRPointFileName, true);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::changeRPointInDebug(
    const QString &sProgramFileName, int nTaskId, const MRobPosItem &item)
{
    int nRet = q->comm()->project()->GetRPoint()->ChangePoint(m_sLoadedRPointFileName,
                                                           item, false);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(item);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_P, item.PointNo, QString::fromStdString(item.LabelName), pt);
    }

    if (nRet == ERROR_OK) {
        InoRobBusiness::ModifyPointStatus modifyStatus
            = InoRobBusiness::ModifyPointStatus::ERR;
        RobPos robPos;
        robPos.Initialize();
        nRet = q->comm()->project()->modifyControllerRPoint(
            item.PointNo, InoRobBusiness::PointType::RP, nTaskId,
            sProgramFileName.toStdString(), robPos, modifyStatus);
    }

    if (nRet == ERROR_OK) {
        nRet = q->comm()->project()->GetRPoint()
                   ->SaveViewPoints(m_sLoadedRPointFileName, false);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool RobotPointInterfacePrivate::findRPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = q->comm()->project()->GetRPoint()->FindPoint(m_sRPointFileName,
                                                         nIndex);
    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet >= 0);
}

InoRPointInfo RobotPointInterfacePrivate::getRPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    MRobPosItem point = q->comm()->project()->GetRPoint()->GetPoint(
        m_sRPointFileName, nIndex);
    if (point.PointNo < 0) {
        return InoRPointInfo();
    }

    InoRPointInfo info;
    info.pointNo = point.PointNo;
    info.name = QString("%1%2%3").arg("P[").arg(point.PointNo, 4, 10, QLatin1Char('0')).arg("]");
    info.label = QString::fromStdString(point.LabelName);
    info.description = QString::fromStdString(point.Description);
    info.pos.RPosData[0] = QString::number(point.PData.RPosData[0], 'f', 3).toDouble();  // XYZABC
    info.pos.RPosData[1] = QString::number(point.PData.RPosData[1], 'f', 3).toDouble();
    info.pos.RPosData[2] = QString::number(point.PData.RPosData[2], 'f', 3).toDouble();
    info.pos.RPosData[3] = QString::number(point.PData.RPosData[3], 'f', 3).toDouble();
    info.pos.RPosData[4] = QString::number(point.PData.RPosData[4], 'f', 3).toDouble();
    info.pos.RPosData[5] = QString::number(point.PData.RPosData[5], 'f', 3).toDouble();
    info.pos.ArmParm[0] = QString::number(point.PData.ArmParm[0], 'f', 3).toDouble();  // 臂参数
    info.pos.ArmParm[1] = QString::number(point.PData.ArmParm[1], 'f', 3).toDouble();
    info.pos.ArmParm[2] = QString::number(point.PData.ArmParm[2], 'f', 3).toDouble();
    info.pos.ArmParm[3] = QString::number(point.PData.ArmParm[3], 'f', 3).toDouble();
    info.pos.EPosData[0] = QString::number(point.PData.EPosData[0], 'f', 3).toDouble();  // E1~E6
    info.pos.EPosData[1] = QString::number(point.PData.EPosData[1], 'f', 3).toDouble();
    info.pos.EPosData[2] = QString::number(point.PData.EPosData[2], 'f', 3).toDouble();
    info.pos.EPosData[3] = QString::number(point.PData.EPosData[3], 'f', 3).toDouble();
    info.pos.EPosData[4] = QString::number(point.PData.EPosData[4], 'f', 3).toDouble();
    info.pos.EPosData[5] = QString::number(point.PData.EPosData[5], 'f', 3).toDouble();

    FREQ_LOG_PRINT_TIMESTAMP
    return info;
}

MRobPosItem RobotPointInterfacePrivate::getRobotMRobPosItem(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    MRobPosItem robPosItem = q->comm()->project()->GetRPoint()->GetPoint(
        m_sLoadedRPointFileName, nIndex);
    if (robPosItem.PointNo < 0) {
        return MRobPosItem();
    }
    FREQ_LOG_PRINT_TIMESTAMP

    return robPosItem;
}

bool RobotPointInterfacePrivate::readCurPoint(InoRobPos &point)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::ReadCurPosState status;
    int16u toolId = _IMonitor->GetToolId();
    int16u wobjId = _IMonitor->GetWobjId();

    RobPos curRobPos;
    bool bRet = _IPosition->GetCurPos(
        toolId, static_cast<ReferObj>(wobjId), status, curRobPos);
    if (bRet) {
        point = MetaTypeConversion::tp2InoApi_robPos(curRobPos);
    }
    FREQ_LOG_PRINT_TIMESTAMP

    return bRet;
}

void RobotPointInterfacePrivate::setAbsoluteZeroPoint(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [pos] = ((CmdDatas<QList<int>> *)absCmd)->m_data;
    // 控制权是否在示教器、手动低速模式、下使能状态、不在调试模式下
    bool check = InoRobBusiness::StatusChecks::getInstance().cobotCheck(
        InoRobBusiness::StatusItemGroup::CTRL_AUTHORITY_TEACHPAD
        | InoRobBusiness::StatusItemGroup::DEVICE_MODE_MANUAL_LOW
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_DISENABLE
        | InoRobBusiness::StatusItemGroup::DEBUG_MODE_EDIT
        | InoRobBusiness::StatusItemGroup::CTRL_STATUS_EMERGENCY);
    if (!check) {
        return;
    }
    double data[AXIS_NUM] = {0};
    QString print = "AbsoluteZeroPoint value is";

    for (int i = 0; i < pos.size(); ++i) {
        data[i] = pos[i];
    }
    for (int i = 0; i < AXIS_NUM; ++i) {
        print += " " + QString::number(data[i]);
    }
    LOG_INFO(print);
    int ret = _IRobotArm->saveAbsZeroValue(data);
    if (ret != ERROR_OK)
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to save data."));
    FREQ_LOG_PRINT_TIMESTAMP
}

bool RobotPointInterfacePrivate::getAbsoluteZeroPoint(QList<double> &pos, QList<int> &min, QList<int> &max)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    double data[AXIS_NUM];
    pos.clear();
    min.clear();
    max.clear();
    int ret = _IRobotArm->getAbsZeroValue(data);
    if (ret == ERROR_OK) {
        for (int i = 0; i < AXIS_NUM; ++i) {
            pos.push_back(data[i]);
        }
    }
    if (ret != ERROR_OK)
        return false;
    std::string paraStructName = "AbsZeroPoint";
    InoRobBusiness::IRobotParamRange *param = q->comm()->robotParam()->getRobotParamRange();
    for (int i = 0; i < 6; ++i) {
        std::string paramName = "J" + std::to_string(i + 1);
        min.push_back(param->getIntMinValue(paraStructName, paramName));
        max.push_back(param->getIntMaxValue(paraStructName, paramName));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return ret == ERROR_OK;
}

void RobotPointInterfacePrivate::setWorikOriginPoint(const int index, InoJPos &pos)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ret = _IRobotArm->saveWorkOriginData(pos.JointData, pos.EPosData, index);
    if (ret != ERROR_OK) {
        QString warning;
        if (index == 0)
            warning = QObject::tr("Failed to save initial pose.");
        else if (index == 1)
            warning = QObject::tr("Failed to save delivery pose.");
        else
            warning = QObject::tr("Failed to save work origin {0}.")
                          .replace("{0}", QString::number(index));
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(warning);
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotPointInterfacePrivate::setWorikOriginPointTriggerData(AbstractCmd *cmd)
{
    auto [index, mode, outIndex, pos] = BIND(cmd, int, int, int, InoJPos);
    JHomeTriggertOutData data;
    data.index = index;
    data.mode = mode;
    data.outNum = outIndex;
    for (int i = 0; i < JOINT_AXIS_COUNT; ++i) {
        data.JointOffsetData[i] = pos.JointData[i];
    }
    for (int i = 0; i < EXT_AXIS_COUNT; ++i) {
        data.EPosOffsetData[i] = pos.EPosData[i];
    }
    int ret = _IPosition->setHomeTriggerOutData(data);
    bool ok = false;
    if(ret == ERROR_OK)
        _IRobotArm->saveFileCommond(&ok);
    if (ret != ERROR_OK || !ok) {
        QString warning;
        if (index == 0)
            warning = QObject::tr("Failed to save initial pose trigger data.");
        else if (index == 1)
            warning = QObject::tr("Failed to save delivery pose trigger data.");
        else
            warning = QObject::tr("Failed to save work origin {0} trigger data.")
                          .replace("{0}", QString::number(index));
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(warning);
    }
}

bool RobotPointInterfacePrivate::getWorikOriginPoint(const int index,
                                              InoJPos &source,
                                              QList<double> &min,
                                              QList<double> &max)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    JPos pos;
    int ret = _IRobotArm->ReadWorkOriginPts(pos, index);
    source = MetaTypeConversion::tp2InoApi_jPos(pos);
    if (ret != ERROR_OK)
        return false;
    InoRobBusiness::IRobotParamRange *param = q->comm()->robotParam()->getRobotParamRange();
    std::string paraStructName = "WorkOriginParam" + std::to_string(index);
    for (int j = 0; j < 6; ++j) {
        std::string paramName = "J" + std::to_string(j + 1) + "(°)";
        min.push_back(param->getDoubleMinValue(paraStructName, paramName));
        max.push_back(param->getDoubleMaxValue(paraStructName, paramName));
    }
    paraStructName = "WorkOriginParam" + std::to_string(index + 6);
    for (int j = 0; j < 6; ++j) {
        std::string paramName = "J" + std::to_string(j + 1) + "(°)";
        min.push_back(param->getDoubleMinValue(paraStructName, paramName));
        max.push_back(param->getDoubleMaxValue(paraStructName, paramName));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool RobotPointInterfacePrivate::getWorikOriginTriggerData(const int index,
                                                    InoJPos &pos,
                                                    int &mode,
                                                    int &outIndex)
{
    // virtual int getHomeTriggerOutData(JHomeTriggertOutData &data) = 0;
    JHomeTriggertOutData data;
    data.index = index;
    int ret = _IPosition->getHomeTriggerOutData(data);
    if (ret != ERROR_OK)
        return false;
    for (int i = 0; i < EXT_AXIS_COUNT; ++i) {
        pos.EPosData[i] = data.EPosOffsetData[i];
    }
    for (int i = 0; i < JOINT_AXIS_COUNT; ++i) {
        pos.JointData[i] = data.JointOffsetData[i];
    }
    mode = data.mode;
    outIndex = data.outNum;
    return true;
}

void RobotPointInterfacePrivate::setSevenDragTeaching(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
        auto [nType] = BIND(cmd, int);
    int ret = _IRobotArm->setSevenDragSwitchTeaching(nType);
    emit CommunicationEngine::instance()->signal_setSevenDragTeaching(cmd->m_object, ret);
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotPointInterfacePrivate::setSevenTakePoint(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
        int ret = _IRobotArm->setSevenTakePoint();
    emit CommunicationEngine::instance()->signal_setSevenTakePoint(cmd->m_object, ret);
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotPointInterfacePrivate::getWorikOriginData(AbstractCmd *cmd)
{
    QString errorMsg;
    for (int i = 0; i < 5; ++i) {
        InoJPos pos, homeTriggerData;
        QList<double> min, max;
        int mode = 0, outIndex = -1;
        if (getWorikOriginPoint(i, pos, min, max) && getWorikOriginTriggerData(i, homeTriggerData, mode, outIndex))
            emit CommunicationEngine::instance()
                ->signal_getWorkOriginZeroResult(
                    cmd->m_object, i, pos, min, max, mode, outIndex, homeTriggerData);
        else {
            if (i == 0)
                errorMsg += QObject::tr("Failed to read initial pose home trigger data.") + "\n";
            else if (i == 1)
                errorMsg += QObject::tr("Failed to read delivery pose home trigger data.") + "\n";
            else
                errorMsg += QObject::tr("Failed to read work origin {0} home trigger data.")
                                .replace("{0}", QString::number(i - 2))
                          + "\n";
        }
    }
    if (!errorMsg.isEmpty()) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(errorMsg);
    }
}

void RobotPointInterfacePrivate::getAbsoluteZeroCurrentValue(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [index] = BIND(cmd, int);
#ifdef INOCOBOTTP_MSVC_QT5
    QList<double> pos;
    for(int i = 0; i < AXIS_NUM; i++) {
        pos.append(0);
    }
#else
    QList<double> pos(AXIS_NUM, 0);
#endif
    int ret = _IRobotArm->getCurrMotorPos(&pos[0]);
    if (ret == ERROR_OK)
        emit CommunicationEngine::instance()->signal_getAbsoluteZeroCurrent_result(cmd->m_object, index, pos);
    else
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to get current encoder value."));
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotPointInterfacePrivate::resetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [axisNo] = BIND(cmd, int);
    int ret = _IRobotArm->resetAbsZeroValue(axisNo);
    emit CommunicationEngine::instance()->signal_resetAbsoluteZero_result(cmd->m_object,axisNo,ret);
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotPointInterfacePrivate::getResetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
        auto [axisNo] = BIND(cmd, int);
    uint16_t result = 0;
    int ret = _IRobotArm->getResetAbsZeroValue(axisNo,result);
    if(ret == ERROR_OK){
        ret = result;
    }

    emit CommunicationEngine::instance()->signal_getResetAbsoluteZero_result(cmd->m_object,axisNo,ret);
    FREQ_LOG_PRINT_TIMESTAMP
}
}

RobotPointInterface::RobotPointInterface()
{
    d = new Internal::RobotPointInterfacePrivate(this);
}

RobotPointInterface::~RobotPointInterface()
{
    delete d;
    d = nullptr;
}

void RobotPointInterface::setCurRPointFile(const QString &sName)
{
    d->setCurRPointFile(sName);
}

QString RobotPointInterface::curRPointFile() const
{
    return d->curRPointFile();
}

void RobotPointInterface::setCurLoadedRPointFile(string sName)
{
    d->setCurLoadedRPointFile(sName);
}

QString RobotPointInterface::curLoadedRPointFile() const
{
    return d->curLoadedRPointFile();
}

QString RobotPointInterface::getDefaultRPFileName(QString baseName)
{
    return d->getDefaultRPFileName(baseName);
}

bool RobotPointInterface::isRPointFileUpperLimit(int count)
{
    return d->isRPointFileUpperLimit(count);
}

bool RobotPointInterface::isRPointFileNameValid(const QString &sName, string &errMsg)
{
    return d->isRPointFileNameValid(sName, errMsg);
}

bool RobotPointInterface::isRPointFileExist(const QString &sName)
{
    return d->isRPointFileExist(sName);
}

bool RobotPointInterface::createRPointFile(const QString &sName)
{
    return d->createRPointFile(sName);
}

bool RobotPointInterface::deleteRPointFile(const QString &sName)
{
    return d->deleteRPointFile(sName);
}

bool RobotPointInterface::copyRPointFile(const QString &sName)
{
    return d->copyRPointFile(sName);
}

QString RobotPointInterface::getCopiedRPointFileName()
{
    return d->getCopiedRPointFileName();
}

bool RobotPointInterface::pasteRPointFile(const QString &sName)
{
    return d->pasteRPointFile(sName);
}

bool RobotPointInterface::addRobotPointConfig(const QString &sFileName)
{
    return d->addRobotPointConfig(sFileName);
}

bool RobotPointInterface::deleteRobotPointConfig(const QString &sFileName)
{
    return d->deleteRobotPointConfig(sFileName);
}

QVector<InoRPointInfo> RobotPointInterface::readAllRPoints()
{
    return d->readAllRPoints();
}

QVector<InoRPointInfo> RobotPointInterface::readRPoints(string sFileName)
{
    return d->readRPoints(std::move(sFileName));
}

bool RobotPointInterface::saveRPoints()
{
    return d->saveRPoints();
}

bool RobotPointInterface::saveAllRPoints()
{
    return d->saveAllRPoints();
}

bool RobotPointInterface::replaceRPointCoordValue(int index)
{
    return d->replaceRPointCoordValue(index);
}

bool RobotPointInterface::importLocalRPointFile(const QString &name, QString path)
{
    return d->importLocalRPointFile(name, path);
}

bool RobotPointInterface::exportRPointFile(QString name, QString folder)
{
    return d->exportRPointFile(name, folder);
}

bool RobotPointInterface::addRPoint(int &nIndex, const string &sLabelName)
{
    return d->addRPoint(nIndex, sLabelName);
}

bool RobotPointInterface::copyRPoint(const std::vector<int> &indexs)
{
    return d->copyRPoint(indexs);
}

int RobotPointInterface::pasteRPoint(std::vector<int> &indexs)
{
    return d->pasteRPoint(indexs);
}

bool RobotPointInterface::renameRPoint(int nIIndex, int nNewIndex)
{
    return d->renameRPoint(nIIndex, nNewIndex);
}

bool RobotPointInterface::deleteRPoint(int nIndex)
{
    return d->deleteRPoint(nIndex);
}

bool RobotPointInterface::changeRPoint(const InoRPointInfo &info, string sFileName)
{
    return d->changeRPoint(info, std::move(sFileName));
}

bool RobotPointInterface::changeRPoint(const MRobPosItem &item)
{
    return d->changeRPoint(item);
}

bool RobotPointInterface::changeRPointInDebug(const QString &sProgramFileName, int nTaskId, const MRobPosItem &item)
{
    return d->changeRPointInDebug(sProgramFileName, nTaskId, item);
}

bool RobotPointInterface::findRPoint(int nIndex)
{
    return d->findRPoint(nIndex);
}

InoRPointInfo RobotPointInterface::getRPoint(int nIndex)
{
    return d->getRPoint(nIndex);
}

MRobPosItem RobotPointInterface::getRobotMRobPosItem(int nIndex)
{
    return d->getRobotMRobPosItem(nIndex);
}

void RobotPointInterface::setAbsoluteZeroPoint(AbstractCmd *absCmd)
{
    d->setAbsoluteZeroPoint(absCmd);
}

bool RobotPointInterface::getAbsoluteZeroPoint(QList<double> &pos, QList<int> &min, QList<int> &max)
{
    return d->getAbsoluteZeroPoint(pos, min, max);
}

void RobotPointInterface::getAbsoluteZeroCurrentValue(AbstractCmd *absCmd)
{
    d->getAbsoluteZeroCurrentValue(absCmd);
}

void RobotPointInterface::resetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd)
{
    d->resetAbsoluteZeroPointByAxisNo(cmd);
}

void RobotPointInterface::getResetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd)
{
    d->getResetAbsoluteZeroPointByAxisNo(cmd);
}

void RobotPointInterface::setWorikOriginPoint(const int index, InoJPos &pos)
{
    d->setWorikOriginPoint(index, pos);
}

void RobotPointInterface::setWorikOriginPointTriggerData(AbstractCmd *cmd)
{
    d->setWorikOriginPointTriggerData(cmd);
}

void RobotPointInterface::getWorikOriginData(AbstractCmd *cmd)
{
    d->getWorikOriginData(cmd);
}

bool RobotPointInterface::getWorikOriginPoint(const int index, InoJPos &pos, QList<double> &min, QList<double> &max)
{
    return d->getWorikOriginPoint(index, pos, min, max);
}

bool RobotPointInterface::getWorikOriginTriggerData(const int index, InoJPos &pos, int &mode, int &outIndex)
{
    return d->getWorikOriginTriggerData(index, pos, mode, outIndex);
}

void RobotPointInterface::setSevenDragTeaching(AbstractCmd *cmd)
{
    d->setSevenDragTeaching(cmd);
}

void RobotPointInterface::setSevenTakePoint(AbstractCmd *cmd)
{
    d->setSevenTakePoint(cmd);
}


