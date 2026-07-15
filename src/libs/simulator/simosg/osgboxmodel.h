#ifndef OSGBOXMODEL_H
#define OSGBOXMODEL_H

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include "pos.h"
#include "ori.h"

#include "pileupinfo.h"

class osgBoxModel:public osg::MatrixTransform
{
public:
    osgBoxModel(const Pos &pos, const Ori &ori,const CubeSize &size);

    void setModelRoot(osg::Group* root,bool isRootChild);

    void remove();

    void drawModel(bool draw = true);

    void translateToPos(const Pos &pos);

    void rotateToOri(const Ori &ori);

    void rotate(const Ori &ori);

    void rotate(const double angle_x,const double angle_y,const double angle_z); 

    void rotateX(const double angle);

    void rotateY(const double angle);

    void rotateZ(const double angle);

    void setModelSize(const CubeSize &size);

    Pos pos();

    CubeSize size();

protected:
    void setTransformMatrix();

    void updateBox();

private:
    //是否位于root
    bool m_isRootChild;

    //盒体所在坐标系姿态
    Pos m_pos;
    Ori m_ori;

    //盒体绕工具坐标系旋转角度
    double m_rx;
    double m_ry;
    double m_rz;

    CubeSize m_size;

    osg::ref_ptr<osg::Geode> m_geode;

    osg::ref_ptr<osg::Group> m_root;

};

#endif  // OSGBOXMODEL_H
