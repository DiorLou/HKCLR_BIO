#include "communicationthread.h"
#include <QWidget>
#include "cobotlog.h"
#include "communication.h"
#include "metapath.h"
#include "simulator/simosg/robotosgmodel/osgrobotmodel.h"

#include <osg/MatrixTransform>
#include <osg/Node>
#include <osg/Matrix>
#include <osg/Group>
#include <QMap>
#include <osg/Material>
#include <osgDB/Options>
#include <osgDB/ReadFile>
#ifdef INOCOBOTTP_MSVC_QT5
    #include <QDateTime>
#endif

osg::Node* readNodeFromFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString extName = fileInfo.suffix();

    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz") << "OOOOOOOOOOOOOOOOOO filePath=" << filePath << " fileName=" << fileName << " suffix=" <<extName;

    osg::ref_ptr<osg::Node> pNode = new osg::Node;
    osg::ref_ptr<osgDB::Options> options = new osgDB::Options(std::string("smooth"));
    QFile file(filePath);
    LOG_INFO(QString("[readNodeFromFile]path = %1").arg(filePath));
    // PRINT_MSG(QString("[readNodeFromFile]path = %1").arg(filePath));

    if(file.exists())
    {
        pNode = osgDB::readNodeFile(filePath.toLocal8Bit().data(), options);
    }
    else
    {
        LOG_INFO("[readNodeFromFile]File is Not exists");
        // PRINT_MSG("[readNodeFromFile]File is Not exists");
    }
    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz") << "ReadpNode:" << pNode << " fileName=" << fileName;

    return pNode.release();
}

void CommunicationThread::loadRobotModel(AbstractCmd *absCmd)
{
    auto [robotType, axisCount] = BIND(absCmd, QString, int);
    LOG_INFO(QString("loadRobotModel, start, robotType = %1").arg(robotType));

    const QString dirName = QString("%1/%2/%3")
                                .arg(ABSOLUTE_SHARE_PATH)
                                .arg(SIMULATION_FILE_NAME)
                                .arg("white");

    QList<osg::Node *> linkList_STL;
    QList<osg::Node *> linkList_3DS;
    QList<osg::Node *> coordinateList_3DS;

    for (int i=0; i<=axisCount; ++i) {
        linkList_STL.append(
            readNodeFromFile(QString("%1/%2/stl/P%3.STL").arg(dirName, robotType, QString::number(i))));

        linkList_3DS.append(
            readNodeFromFile(QString("%1/%2/3ds/P%3.3ds").arg(dirName, robotType, QString::number(i))));
    }
    coordinateList_3DS.append(readNodeFromFile(QString("%1/coordinate.3DS").arg(dirName)));

    CommunicationEngine::instance()->signal_loadRobotModel_result(linkList_STL, linkList_3DS, coordinateList_3DS);
    LOG_INFO("loadRobotModel, end");
}

void CommunicationThread::loadRobotModelSegment(AbstractCmd *absCmd)
{
    auto [robotType, axisNo] = BIND(absCmd, QString, int);
    LOG_INFO(QString("loadRobotModelSegment, start, robotType = %1, axisNo = %2").arg(robotType).arg(axisNo));

    const QString dirName = QString("%1/%2/%3")
                                .arg(ABSOLUTE_SHARE_PATH)
                                .arg(SIMULATION_FILE_NAME)
                                .arg("white");

    osg::Node *link_STL;
    osg::Node *link_3DS;
    osg::Node *linkCoordinate_3DS;

    if (axisNo <= RobotModel::MapRobotTypeAndAxisCount.value(robotType)) {
        link_STL = readNodeFromFile(QString("%1/%2/stl/P%3.STL").arg(dirName, robotType, QString::number(axisNo)));
        link_3DS = readNodeFromFile(QString("%1/%2/3ds/P%3.3ds").arg(dirName, robotType, QString::number(axisNo)));
    } else {
        linkCoordinate_3DS = readNodeFromFile(QString("%1/coordinate.3DS").arg(dirName));
    }
    CommunicationEngine::instance()->signal_loadRobotModelSegment_result(absCmd->m_object, link_STL, link_3DS, linkCoordinate_3DS, axisNo);
    LOG_INFO("loadRobotModelSegment, end");
}

