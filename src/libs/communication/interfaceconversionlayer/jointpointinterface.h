#pragma once

#include "communication_global.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "pointdata.h"
#include <QVector>

namespace InoRobBusiness
{
class IController;
class IProject;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT JointPointInterface
{
public:
    JointPointInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // current joint point file
    void setCurJPointFile(const QString &sName);

    // joint points in project
    QVector<InoJPointInfo> readAllJPoints();
    // joint points in a joint point file
    QVector<InoJPointInfo> readJPoints(std::string sFileName = "");
    // save joint points to current file
    bool saveJPoints();
    // save all joint points
    bool saveAllJPoints();
    // replace coord value
    bool replaceJPointCoordValue(int index);

    bool importLocalJPoint(QString path);
    bool exportJPoint(QString name, QString folder);

    bool addJPoint(int &nIndex, const std::string &sLableName = "");
    bool copyJPoint(const std::vector<int> &indexs);
    int pasteJPoint(std::vector<int> &indexs);
    bool renameJPoint(int nIndex, int nNewIndex);
    bool deleteJPoint(int nIndex);
    bool changeJPoint(const InoJPointInfo &info, std::string sFileName = "");
    bool changeJPoint(const MJPosItem &info);
    bool changeJPointInDebug(const QString &sProgramFileName,
                             int nTaskId, const MJPosItem &item);
    bool findJPoint(int nIndex);
    InoJPointInfo getJPoint(int nIndex);
    MJPosItem getJointMJPosItem(int nIndex);
    bool getCurrentJPoint(InoJPos &point);

private:
    // read current point
    bool readCurPoint(InoJPos &point);

private:
    std::string m_sJPointFileName;
};
