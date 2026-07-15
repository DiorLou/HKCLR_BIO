#ifndef OSGPALLETMODEL_H
#define OSGPALLETMODEL_H

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include "pos.h"
#include "ori.h"

#include "pileupinfo.h"

class osgPalletModel:public osg::MatrixTransform
{
public:
    osgPalletModel(const osg::Matrix &transformForWobj, const CubeSize &size);

    void setModelRoot(osg::Group* root);

    void remove();

protected:
    osg::Node* readNodeFromFile(const QString &filePath);

private:
    osg::ref_ptr<osg::Group> m_root;

};

#endif  // OSGPALLETMODEL_H
