#pragma once
#include "osgrobotmodel.h"

class RobotModelFactory
{
public:

    static QSharedPointer<osgRobotModel> createModel(const QString &robotType);

private:
    RobotModelFactory() = delete;
};
