#ifndef OSGCOMMON_H
#define OSGCOMMON_H

#include <osg/Node>

class osgCommon
{
public:
    osgCommon();

    static void setTextureForNode(osg::Node *node, std::string path);

    static void setNodeStatesetColor(osg::Node *node,bool bIsRealTime);

};

#endif  // OSGCOMMON_H
