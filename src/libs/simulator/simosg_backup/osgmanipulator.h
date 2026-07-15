#ifndef OSGMANIPULATOR_H
#define OSGMANIPULATOR_H

#include <osg/Vec3d>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

enum ManipulatorType
{
    MainpulatorLeftMove,
    MainpulatorRightMove,
    MainpulatorUpMove,
    MainpulatorDownMove,
    MainpulatorZoomIn,
    MainpulatorZoomOut,
    MainpulatorLeftRotate,
    MainpulatorRightRotate,
    MainpulatorFronView,
};

class OsgManipulator
{
public:
    OsgManipulator(osgViewer::Viewer *pViewer = nullptr);

    //同步当前操纵器的视角到所有操纵器
    void setCurrentToAllViewer();

    //同步视角
    void static angleSync(osgGA::TrackballManipulator*);

    void setManipulator(ManipulatorType type);

    //围绕up方向旋转（左右转）
    void setRotateByUp(float angle);

    //垂直up方向旋转（上下转）
    void setRotateByLeft(float angle);

private:


    void goHome();
private:
    osg::Vec3d m_initEye;
    osg::Vec3d m_initCenter;
    osg::Vec3d m_initUp;

    osg::ref_ptr<osgGA::TrackballManipulator> m_trackball;
};

#endif  // OSGMANIPULATOR_H
