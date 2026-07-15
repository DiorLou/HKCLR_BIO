#ifndef OSGGROUNDMODEL_H
#define OSGGROUNDMODEL_H

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Material>
class osgGroundModel
{
public:
    osgGroundModel();

    void setModelRoot(osg::Group* root);

    void drawModel(bool draw = true);

private:
    osg::ref_ptr<osg::MatrixTransform> m_transform;

};

#endif  // OSGGROUNDMODEL_H
