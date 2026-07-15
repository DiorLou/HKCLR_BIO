#ifndef OSGMODEL_H
#define OSGMODEL_H

#include "metatype.h"
#include "roadpoint.h"
#include "toolparams.h"
#include "wobjparams.h"

#include <osg/MatrixTransform>
#include <osg/Node>
#include <osg/Matrix>
#include <osg/Group>
#include <QMap>
#include <osg/Material>

class osgModel
{
public:
    enum RobotModelType{
        RobotModelType_STL,
        RobotModelType_3DS
    };
    osgModel();

public:
    void importModels(QString& path);
    void drawModel(bool draw = true);
    void drawTool(bool draw = true);
    void drawWobJ();
    void setIsTarget(bool isTarget);
    void setModelType(const RobotModelType &type);

    void setRoadPoint(RoadPoint roadPoint);
    void setModelRoot(osg::Group* root,bool bIsRealTime);
    void setTool(ToolParams toolParam, bool isNull = true);
    void setWobj(WobjParams wobjParams, bool isNull = true);
    osg::Vec3d getCurToolRoadPos();
    void setData(int index,bool leftOrRight);
    void setDHParam(const DHParam &dhParam);

    void addModelToTool(osg::ref_ptr<osg::MatrixTransform> child);

    void addModelToWobj(osg::ref_ptr<osg::MatrixTransform> child, const Pos &pos, const Ori &ori);

    void removeModelFromTool(osg::ref_ptr<osg::MatrixTransform> child);

    void removeModelFromWobj(osg::ref_ptr<osg::MatrixTransform> child);

private:
    void initModelNode();
    osg::Node* readNodeFromFile(const QString &filePath);
    osg::Matrix calculateDHMatrix(double a, double alpha, double d, double theta);
    void jlnAndJlp();
    void initCoordinateSystem();

private:
    void dealMatrix();
    osg::ref_ptr<osg::MatrixTransform> m_modelBase;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink1;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink2;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink3;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink4;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink5;
    osg::ref_ptr<osg::MatrixTransform> m_modelLink6;
#if CommonLib_Simulator_DOF7_Enabled == 1
    osg::ref_ptr<osg::MatrixTransform> m_modelLink7;
#endif

    osg::ref_ptr<osg::MatrixTransform> m_modelTool;
    osg::ref_ptr<osg::MatrixTransform> m_modelWobj;

    //to
    osg::Matrixd transMatrix[ROBOT_DOF];
    osg::Matrixd transMatrixInverse[ROBOT_DOF];

    float m_rotJoint[ROBOT_DOF];      //关节角

    // float m_ToolPosAndOri[6];   //工具坐标
    // float m_WobjPosAndOri[6];   //工件坐标

    bool m_isTarget;//是否为目标点
    bool m_toolNull;//工具为空
    bool m_wobjNull;//工件为空
    ToolParams m_toolParams;//工具坐标
    WobjParams m_wobjParams;//工件坐标

    QMap<int, osg::ref_ptr<osg::MatrixTransform>> m_mapLinkNoAndModel;

    /*
     * DH parms
     */
    QMap<int, QMap<QString, double>> m_mapDHParms;

    RobotModelType m_robotModelType;

    QList<osg::ref_ptr<osg::Node>> m_linkList_STL;
    QList<osg::ref_ptr<osg::Node>> m_linkList_3DS;
    QList<osg::ref_ptr<osg::Node>> m_coordinate_3DS;
    std::vector<std::pair<int, int>> jlnAndJlpCondition;
};

#endif // OSGMODEL_H
