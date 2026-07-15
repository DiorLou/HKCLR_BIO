#include "jointpointinterface.h"
#include "communication.h"
#include "IController.h"
#include "metatypeconversion.h"
#include "projectinfo.h"
#include "cobotlogex.h"
#include "modulesutils.h"

void JointPointInterface::setCurJPointFile(const QString &sName)
{
    if (!sName.isEmpty()) {
        m_sJPointFileName = sName.toStdString();
    }
}

QVector<InoJPointInfo> JointPointInterface::readAllJPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string errMsg;
    QVector<InoJPointInfo> infos;
    std::vector<MJPosItem> points;
    InoJPointInfo info;
    infos.clear();

    std::vector<std::string> vecFiles = comm()->project()->GetJPointFileList();
    for (const std::string &fileName : vecFiles) {
        // 读取点位
        int ret = comm()->project()->GetJPoint()->ReadPoints(
            points, fileName);
        if (ret != ERR_OK) {
            return infos;
        }

        // 赋值
        size_t count = points.size();
        for (size_t i = 0; i < count; i++) {
            info.pointNo = points[i].PointNo;  // 点位序号
            info.name = QString("%1%2%3").arg("JP[").arg(points[i].PointNo, 4, 10, QLatin1Char('0')).arg("]");
            info.label = QString::fromStdString(points[i].LabelName);                                  // 标签
            info.description = QString::fromStdString(points[i].Description);                          // 描述(备注)
            info.pos.JointData[0] = QString::number(points[i].JData.JointData[0], 'f', 3).toDouble();  // J1-J6
            info.pos.JointData[1] = QString::number(points[i].JData.JointData[1], 'f', 3).toDouble();
            info.pos.JointData[2] = QString::number(points[i].JData.JointData[2], 'f', 3).toDouble();
            info.pos.JointData[3] = QString::number(points[i].JData.JointData[3], 'f', 3).toDouble();
            info.pos.JointData[4] = QString::number(points[i].JData.JointData[4], 'f', 3).toDouble();
            info.pos.JointData[5] = QString::number(points[i].JData.JointData[5], 'f', 3).toDouble();
            info.pos.EPosData[0] = QString::number(points[i].JData.EPosData[0], 'f', 3).toDouble();  // E1~E6
            info.pos.EPosData[1] = QString::number(points[i].JData.EPosData[1], 'f', 3).toDouble();
            info.pos.EPosData[2] = QString::number(points[i].JData.EPosData[2], 'f', 3).toDouble();
            info.pos.EPosData[3] = QString::number(points[i].JData.EPosData[3], 'f', 3).toDouble();
            info.pos.EPosData[4] = QString::number(points[i].JData.EPosData[4], 'f', 3).toDouble();
            info.pos.EPosData[5] = QString::number(points[i].JData.EPosData[5], 'f', 3).toDouble();
            infos.append(info);
        }
    }

    std::sort(infos.begin(), infos.end(),
              [](const InoJPointInfo &a, const InoJPointInfo &b) {
                  return a.pointNo < b.pointNo;
              });

    FREQ_LOG_PRINT_TIMESTAMP
    return infos;
}

QVector<InoJPointInfo> JointPointInterface::readJPoints(std::string sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string errMsg;
    QVector<InoJPointInfo> infos;

    sFileName = sFileName.empty() ? m_sJPointFileName : sFileName;

    std::vector<MJPosItem> points;
    InoJPointInfo info;
    infos.clear();

    // 读取点位
    int ret = comm()->project()->GetJPoint()->ReadPoints(points, sFileName);
    if (ret != ERR_OK) {
        return infos;
    }

    // 添加到缓存中
    comm()->project()->GetJPoint()->AddViewPoints(sFileName, points);

    // 赋值
    size_t count = points.size();
    for (size_t i = 0; i < count; i++) {
        info.pointNo = points[i].PointNo;  // 点位序号
        info.name = QString("%1%2%3").arg("JP[").arg(points[i].PointNo, 4, 10, QLatin1Char('0')).arg("]");
        info.label = QString::fromStdString(points[i].LabelName);                                  // 标签
        info.description = QString::fromStdString(points[i].Description);                          // 描述(备注)
        info.pos.JointData[0] = QString::number(points[i].JData.JointData[0], 'f', 3).toDouble();  // J1-J6
        info.pos.JointData[1] = QString::number(points[i].JData.JointData[1], 'f', 3).toDouble();
        info.pos.JointData[2] = QString::number(points[i].JData.JointData[2], 'f', 3).toDouble();
        info.pos.JointData[3] = QString::number(points[i].JData.JointData[3], 'f', 3).toDouble();
        info.pos.JointData[4] = QString::number(points[i].JData.JointData[4], 'f', 3).toDouble();
        info.pos.JointData[5] = QString::number(points[i].JData.JointData[5], 'f', 3).toDouble();
        info.pos.EPosData[0] = QString::number(points[i].JData.EPosData[0], 'f', 3).toDouble();  // E1~E6
        info.pos.EPosData[1] = QString::number(points[i].JData.EPosData[1], 'f', 3).toDouble();
        info.pos.EPosData[2] = QString::number(points[i].JData.EPosData[2], 'f', 3).toDouble();
        info.pos.EPosData[3] = QString::number(points[i].JData.EPosData[3], 'f', 3).toDouble();
        info.pos.EPosData[4] = QString::number(points[i].JData.EPosData[4], 'f', 3).toDouble();
        info.pos.EPosData[5] = QString::number(points[i].JData.EPosData[5], 'f', 3).toDouble();
        infos.append(info);
    }

    std::sort(infos.begin(), infos.end(),
              [](const InoJPointInfo &a, const InoJPointInfo &b) {
                  return a.pointNo < b.pointNo;
              });

    FREQ_LOG_PRINT_TIMESTAMP
    return infos;
}

bool JointPointInterface::saveJPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->GetJPoint()->SaveViewPoints(
        m_sJPointFileName, false);
    if (nRet != ERR_OK) {
        return false;
    }

    comm()->project()->updateLablesToTransfor();

    comm()->project()->sendSyncFlag(
        static_cast<int>(InoRobBusiness::SyncProjcetInfoType::SYNC_GOBAL_JPOINT));
    return (nRet == ERR_OK);
}

bool JointPointInterface::saveAllJPoints()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->GetJPoint()->SaveAllViewPoints();
    if (nRet != ERR_OK) {
        return false;
    }

    comm()->project()->updateLablesToTransfor();

    comm()->project()->sendSyncFlag(
        static_cast<int>(InoRobBusiness::SyncProjcetInfoType::SYNC_GOBAL_JPOINT));
    return (nRet == ERR_OK);
}

bool JointPointInterface::importLocalJPoint(QString path)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    path = QDir::fromNativeSeparators(path);

    std::vector<std::string> paths;
    paths.push_back(path.toStdString());
    int ret = comm()->project()->GetJPoint()->ImportFiles(paths);

    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool JointPointInterface::exportJPoint(QString name, QString folder)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<std::string> names;
    names.push_back(name.toStdString());

    folder = QDir::fromNativeSeparators(folder);
    int ret = comm()->project()->GetJPoint()->ExportFiles(
        names, folder.toStdString());

    FREQ_LOG_PRINT_TIMESTAMP
    return (ret == ERR_OK);
}

bool JointPointInterface::addJPoint(int &nIndex, const string &sLableName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoJPos pointValue;
    if (!readCurPoint(pointValue)) {
        return false;
    }

    MJPosItem point;
    point.PointNo = -1;
    point.LabelName = sLableName;
    point.Description = "";
    point.JData = MetaTypeConversion::inoApi2tp_jPos(pointValue);

    int nRet = comm()->project()->GetJPoint()->AddPoint(
        nIndex, m_sJPointFileName, point);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(pointValue);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::replaceJPointCoordValue(int index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoJPos pointValue;
    if (!readCurPoint(pointValue)) {
        return false;
    }

    MJPosItem point = comm()->project()->GetJPoint()->GetPoint(
        m_sJPointFileName, index);
    if (point.PointNo < 0) {
        return false;
    }

    point.JData = MetaTypeConversion::inoApi2tp_jPos(pointValue);
    int nRet = comm()->project()->GetJPoint()->ChangePoint(
        m_sJPointFileName, point, false);

    if (nRet == ERROR_OK) {
        RoadPoint pt = MetaTypeConversion::inoApi2tp_roadPoint(pointValue);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::copyJPoint(const std::vector<int> &indexs)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    comm()->project()->GetJPoint()->CopyPoints(m_sJPointFileName, indexs);

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

int JointPointInterface::pasteJPoint(std::vector<int> &indexs)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->GetJPoint()->PastePoints(
        indexs, m_sJPointFileName);
    if (nRet != ERR_OK) {
        return INVALID_INDEX;
    }

    if (indexs.size() == 0) {
        return INVALID_INDEX;
    }

    for (const int &index : indexs) {
        InoJPointInfo info = getJPoint(index);
        if (info.pointNo == INVALID_INDEX) {
            continue;
        }

        RoadPoint pt;
        pt.setJointAngle(info.pos.JointData);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, info.pointNo, info.label, pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::renameJPoint(int nIndex, int nNewIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (nNewIndex < 0) {
        return false;
    }

    int nRet = comm()->project()->GetJPoint()->RenamePoint(
        m_sJPointFileName, nIndex, nNewIndex);

    if (nRet == ERR_OK) {
        InoJPointInfo info = getJPoint(nNewIndex);
        RoadPoint pt;
        pt.setJointAngle(info.pos.JointData);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, info.pointNo, info.label, pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::deleteJPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->GetJPoint()->DelPoint(
        m_sJPointFileName, nIndex);

    if (nRet == ERR_OK) {
        ProjectRoadPointInfo::instance()->deleteRoadPointInfo(PREFIX_JP, nIndex);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::changeJPoint(const InoJPointInfo &info, std::string sFileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    sFileName = sFileName.empty() ? m_sJPointFileName : sFileName;

    MJPosItem point;
    point.PointNo = info.pointNo;
    point.LabelName = info.label.toStdString();
    point.Description = info.description.toStdString();
    point.JData = MetaTypeConversion::inoApi2tp_jPos(info.pos);

    int nRet = comm()->project()->GetJPoint()->ChangePoint(sFileName,
                                                           point, false);

    if (nRet == ERR_OK) {
        RoadPoint pt;
        pt.setJointAngle(point.JData.JointData);
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, point.PointNo, QString::fromStdString(point.LabelName), pt);
    }

    qDebug() << __FUNCTION__ << nRet;
    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::changeJPoint(const MJPosItem &item)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (item.PointNo < 0) {
        return false;
    }

    int nRet = comm()->project()->GetJPoint()->ChangePoint(m_sJPointFileName,
                                                           item, false);
    if (nRet != ERR_OK) {
        return false;
    }

    comm()->project()->GetJPoint()->setModifyState(true);

    if (nRet == ERR_OK) {
        RoadPoint pt;
        pt.setJointAngle(const_cast<double *>(item.JData.JointData));
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, item.PointNo, QString::fromStdString(item.LabelName), pt);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet == ERR_OK);
}

bool JointPointInterface::changeJPointInDebug(
    const QString &sProgramFileName, int nTaskId, const MJPosItem &item)
{
    int nRet = comm()->project()->GetJPoint()->ChangePoint(m_sJPointFileName,
                                                           item, false);

    if (nRet == ERR_OK) {
        RoadPoint pt;
        pt.setJointAngle(const_cast<double *>(item.JData.JointData));
        ProjectRoadPointInfo::instance()->updateRoadPointInfo(
            PREFIX_JP, item.PointNo, QString::fromStdString(item.LabelName), pt);
    }

    if (nRet == ERR_OK) {
        InoRobBusiness::ModifyPointStatus modifyStatus
            = InoRobBusiness::ModifyPointStatus::ERR;
        JPos jPos;
        jPos.Initialize();
        nRet = comm()->project()->modifyControllerJPoint(
            item.PointNo, jPos, modifyStatus);
    }

    if (nRet == ERR_OK) {
        nRet = comm()->project()->GetJPoint()
                   ->SaveViewPoints(m_sJPointFileName, false);
    }

    FREQ_LOG_PRINT_TIMESTAMP
        return (nRet == ERR_OK);
}

bool JointPointInterface::findJPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->project()->GetJPoint()->FindPoint(m_sJPointFileName,
                                                         nIndex);
    qDebug() << __FUNCTION__ << nRet;
    FREQ_LOG_PRINT_TIMESTAMP
    return (nRet >= 0);
}

InoJPointInfo JointPointInterface::getJPoint(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    MJPosItem point = comm()->project()->GetJPoint()->GetPoint(
        m_sJPointFileName, nIndex);
    if (point.PointNo < 0) {
        return InoJPointInfo();
    }

    InoJPointInfo info;
    info.pointNo = point.PointNo;
    info.name = QString("%1%2%3").arg("JP[").arg(point.PointNo, 4, 10, QLatin1Char('0')).arg("]");
    info.label = QString::fromStdString(point.LabelName);
    info.description = QString::fromStdString(point.Description);
    info.pos.JointData[0] = QString::number(point.JData.JointData[0], 'f', 3).toDouble();  // J1-J6
    info.pos.JointData[1] = QString::number(point.JData.JointData[1], 'f', 3).toDouble();
    info.pos.JointData[2] = QString::number(point.JData.JointData[2], 'f', 3).toDouble();
    info.pos.JointData[3] = QString::number(point.JData.JointData[3], 'f', 3).toDouble();
    info.pos.JointData[4] = QString::number(point.JData.JointData[4], 'f', 3).toDouble();
    info.pos.JointData[5] = QString::number(point.JData.JointData[5], 'f', 3).toDouble();
    info.pos.EPosData[0] = QString::number(point.JData.EPosData[0], 'f', 3).toDouble();  // E1~E6
    info.pos.EPosData[1] = QString::number(point.JData.EPosData[1], 'f', 3).toDouble();
    info.pos.EPosData[2] = QString::number(point.JData.EPosData[2], 'f', 3).toDouble();
    info.pos.EPosData[3] = QString::number(point.JData.EPosData[3], 'f', 3).toDouble();
    info.pos.EPosData[4] = QString::number(point.JData.EPosData[4], 'f', 3).toDouble();
    info.pos.EPosData[5] = QString::number(point.JData.EPosData[5], 'f', 3).toDouble();

    FREQ_LOG_PRINT_TIMESTAMP
    return info;
}

MJPosItem JointPointInterface::getJointMJPosItem(int nIndex)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    MJPosItem jPosItem = comm()->project()->GetJPoint()->GetPoint(
        m_sJPointFileName, nIndex);
    if (jPosItem.PointNo < 0) {
        return MJPosItem();
    }
    FREQ_LOG_PRINT_TIMESTAMP

    return jPosItem;
}

bool JointPointInterface::readCurPoint(InoJPos &point)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    JPos curJPos;
    bool bRet = _IPosition->GetCurJPos(curJPos);
    if (bRet) {
        point = MetaTypeConversion::tp2InoApi_jPos(curJPos);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

bool JointPointInterface::getCurrentJPoint(InoJPos &point)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    JPos curJPos;
    bool bRet = _IPosition->GetCurJPos(curJPos);
    if (bRet) {
        point = MetaTypeConversion::tp2InoApi_jPos(curJPos);
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}
