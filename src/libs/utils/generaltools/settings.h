#pragma once

#include "generaltools_global.h"
#include "metatype.h"
#include <QSettings>

class GENERALTOOLS_EXPORT Settings : public QSettings
{
    Q_OBJECT

public:
    explicit Settings(
        MetaType::RobotType robotType = MetaType::RobotType_invalid);

    static QString getConfigFileName(const MetaType::RobotType &robotType);
};
