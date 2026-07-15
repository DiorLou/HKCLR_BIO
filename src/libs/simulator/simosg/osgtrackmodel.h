#ifndef OSGTRACKMODEL_H
#define OSGTRACKMODEL_H

#include <QList>

#include "roadpoint.h"
#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>

class osgTrackModel
{
public:
    osgTrackModel();

    void setModelRoot(osg::Group* root);

    void drawModel(QList<RoadPoint> roadPoints, bool draw = true);

private:
    osg::ref_ptr<osg::Geode> m_trackModel;
    osg::ref_ptr<osg::Geometry> m_geometry;
    osg::ref_ptr<osg::Vec3Array> m_vec3arry;

    osg::DrawArrays *m_drawArray;
    osg::Vec4Array *m_colorArray;
};

#endif  // OSGTRACKMODEL_H
