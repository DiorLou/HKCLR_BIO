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

class SevenAxisModelBase : public osgRobotModel
{
public:
    SevenAxisModelBase(QString robotType);

public:
    virtual void setDHParam(const DHParam &dhParam) override;
    virtual void drawModel(bool draw = true) override;
    virtual void drawTool(bool draw = true) override;
    virtual void setModelRoot(osg::Group* root,bool bIsRealTime) override;

private:
    void jlnAndJlp();
    void dealMatrix();

    QList<osg::Matrixd> m_transMatrix;
    QList<osg::Matrixd> m_transMatrixInverse;
    QVector<std::pair<int, int>> m_jlnAndJlpCondition;
};

class R7Model : public SevenAxisModelBase
{
public:
    R7Model();

public:
    virtual void initDHParam() override;
};
