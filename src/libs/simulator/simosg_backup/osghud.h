#ifndef OSGHUD_H
#define OSGHUD_H

#include <osg/Camera>

class osgHUD
{
public:
    osgHUD();
    osg::MatrixTransform* createFixedScreenNode(const std::string& modelPath, float screenX, float screenY);
    osg::Camera *createHUD();

    void updateHUD(osg::ref_ptr<osg::Camera> mainCamera, double alpha = 0, double beta = 0);

    osg::ref_ptr<osg::Camera> cameraHUD = nullptr;


};

#endif  // OSGHUD_H
