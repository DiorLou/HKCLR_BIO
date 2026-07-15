#pragma once

#include "metatype.h"
#include "osgrobotmodel.h"
#include "roadpoint.h"
#include "toolparams.h"
#include "wobjparams.h"

#include <osg/MatrixTransform>
#include <osg/Node>
#include <osg/Matrix>
#include <osg/Group>
#include <QMap>
#include <osg/Material>

class SixAxisModelBase : public osgRobotModel
{
public:
    SixAxisModelBase(QString robotType);

public:
    virtual void setDHParam(const DHParam &dhParam) override;
    virtual void drawModel(bool draw = true) override;
    virtual void drawTool(bool draw = true) override;
    virtual void setModelRoot(osg::Group* root,bool bIsRealTime) override;
};

class U8Model : public SixAxisModelBase
{
public:
    U8Model();

public:
    virtual void initDHParam() override;
};

class U4Model : public SixAxisModelBase
{
public:
    U4Model();

public:
    virtual void initDHParam() override;
};

class U13Model : public SixAxisModelBase
{
public:
    U13Model();

public:
    virtual void initDHParam() override;
};

class U18Model : public SixAxisModelBase
{
public:
    U18Model();

public:
    virtual void initDHParam() override;
};
