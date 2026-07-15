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
class AbstractCmd;
namespace Internal
{
class RobotPointInterfacePrivate;
}

class COMMUNICATION_EXPORT RobotPointInterface
{
public:
    RobotPointInterface();
    ~RobotPointInterface();

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // current robot point file
    void setCurRPointFile(const QString &sName);
    QString curRPointFile() const;

    // current loaded robot point file
    void setCurLoadedRPointFile(std::string sName);
    QString curLoadedRPointFile() const;

    // default global robot point file name
    QString getDefaultRPFileName(QString baseName = "");

    bool isRPointFileUpperLimit(int count = 1);
    // check file name valid
    bool isRPointFileNameValid(const QString &sName, std::string &errMsg);
    bool isRPointFileExist(const QString &sName);

    bool createRPointFile(const QString &sName);
    bool deleteRPointFile(const QString &sName);
    bool copyRPointFile(const QString &sName);
    QString getCopiedRPointFileName();
    bool pasteRPointFile(const QString &sName);

    bool addRobotPointConfig(const QString &sFileName);
    bool deleteRobotPointConfig(const QString &sFileName);

    // robot points in project
    QVector<InoRPointInfo> readAllRPoints();
    // robot points in a robot point file
    QVector<InoRPointInfo> readRPoints(std::string sFileName = "");
    // save robot points to current file
    bool saveRPoints();
    // save all robot points
    bool saveAllRPoints();
    // replace coord value
    bool replaceRPointCoordValue(int index);

    bool importLocalRPointFile(const QString &name, QString path);
    bool exportRPointFile(QString name, QString folder);

    bool addRPoint(int &nIndex, const std::string &sLabelName = "");
    bool copyRPoint(const std::vector<int> &indexs);
    int pasteRPoint(std::vector<int> &indexs);
    bool renameRPoint(int nIIndex, int nNewIndex);
    bool deleteRPoint(int nIndex);
    bool changeRPoint(const InoRPointInfo &info, std::string sFileName = "");
    bool changeRPoint(const MRobPosItem &item);
    bool changeRPointInDebug(const QString &sProgramFileName, int nTaskId,
                             const MRobPosItem &item);
    bool findRPoint(int nIndex);
    InoRPointInfo getRPoint(int nIndex);
    MRobPosItem getRobotMRobPosItem(int nIndex);

    void setAbsoluteZeroPoint(AbstractCmd *absCmd);
    bool getAbsoluteZeroPoint(QList<double> &pos,
                              QList<int> &min,
                              QList<int> &max);
    void getAbsoluteZeroCurrentValue(AbstractCmd *absCmd);
    void resetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd);
    void getResetAbsoluteZeroPointByAxisNo(AbstractCmd *cmd);

    void setWorikOriginPoint(const int index, InoJPos &pos);
    void setWorikOriginPointTriggerData(AbstractCmd *cmd);
    void getWorikOriginData(AbstractCmd *cmd);

    bool getWorikOriginPoint(const int index,
                             InoJPos &pos,
                             QList<double> &min,
                             QList<double> &max);
    bool getWorikOriginTriggerData(const int index,
                                   InoJPos &pos,
                                   int &mode,
                                   int &outIndex);

    void setSevenDragTeaching(AbstractCmd *cmd);
    void setSevenTakePoint(AbstractCmd *cmd);
private:
    Internal::RobotPointInterfacePrivate *d;
    friend class Internal::RobotPointInterfacePrivate;
};
