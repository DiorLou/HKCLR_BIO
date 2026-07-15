#pragma once

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

namespace RobotModel {
    const char RobotType_U4[] = "U4";
    const char RobotType_U8[] = "U8";
    const char RobotType_U13[] = "U13";
    const char RobotType_U18[] = "U18";
    const char RobotType_R7[] = "R7";

    const QHash<QString, int> MapRobotTypeAndAxisCount{
        {RobotType_U4, 6},
        {RobotType_U8, 6},
        {RobotType_U13, 6},
        {RobotType_U18, 6},
        {RobotType_R7, 7},
    };
}

class osgRobotModel
{
public:
    enum RobotModelType{
        RobotModelType_STL,
        RobotModelType_3DS
    };

    osgRobotModel(QString robotType, int axisCount);
    virtual ~osgRobotModel() = default;

public:
    void setModelResources(const QList<osg::ref_ptr<osg::Node>>& linkSTL,
                           const QList<osg::ref_ptr<osg::Node>>& link3DS,
                           const QList<osg::ref_ptr<osg::Node>>& coordinate);
    virtual void drawModel(bool draw = true) = 0;
    virtual void drawTool(bool draw = true) = 0;
    virtual void initDHParam() = 0;
    virtual void setDHParam(const DHParam &dhParam) = 0;
    virtual void setModelRoot(osg::Group* root,bool bIsRealTime) = 0;
    virtual void setData(int index,bool leftOrRight);

    virtual void removeModeFromRoot();

    void drawWobJ();
    void setIsTarget(bool isTarget);
    void setModelType(const RobotModelType &type);

    void setRoadPoint(const RoadPoint &roadPoint);
    void setTool(const ToolParams &toolParam, bool isNull = true);
    void setWobj(const WobjParams &wobjParams, bool isNull = true);
    osg::Vec3d getCurToolRoadPos();

    void addModelToTool(osg::ref_ptr<osg::MatrixTransform> child);

    void addModelToWobj(osg::ref_ptr<osg::MatrixTransform> child, const Pos &pos, const Ori &ori);

    void removeModelFromTool(osg::ref_ptr<osg::MatrixTransform> child);

    void removeModelFromWobj(osg::ref_ptr<osg::MatrixTransform> child);

private:
    void importModels();
    void initModelNode();
    void initCoordinateSystem();

    osg::Node* readNodeFromFile(const QString &filePath);
    osg::Matrix calculateDHMatrix(double a, double alpha, double d, double theta);

protected:

    bool m_isTarget;//是否为目标点

    // 本体参数
    QString m_robotType;
    // RobotType m_robotType;
    RobotModelType m_robotModelType;
    int m_axisCount;
    QMap<int, QMap<QString, double>> m_mapDHParms;
    QList<float> m_rotJoint;      //关节角

    // 本体渲染模型
    QList<osg::ref_ptr<osg::Node>> m_linkList_STL;
    QList<osg::ref_ptr<osg::Node>> m_linkList_3DS;

    // 本体转换
    osg::ref_ptr<osg::MatrixTransform> m_modelBase;
    QList<osg::ref_ptr<osg::MatrixTransform>> m_modelLinkList;
    // 应用DH参数后的模型转换
    QMap<int, osg::ref_ptr<osg::MatrixTransform>> m_mapLinkNoAndModel;

    // 工具模型
    osg::ref_ptr<osg::MatrixTransform> m_modelTool;
    bool m_toolNull; // 是否存在工具
    ToolParams m_toolParams; // 工具参数
    // 工件模型
    osg::ref_ptr<osg::MatrixTransform> m_modelWobj;
    bool m_wobjNull;// 是否存在工件
    WobjParams m_wobjParams;// 工件参数
    // 坐标系节点
    QList<osg::ref_ptr<osg::Node>> m_coordinate_3DS;

    osg::Group *m_root = nullptr;
};
