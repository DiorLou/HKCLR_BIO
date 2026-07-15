#pragma once

#include <QString>
#include "metatype.h"
#include "metatype_global.h"

class METATYPE_EXPORT ConfigInfo
{
public:
    ConfigInfo();
    ConfigInfo(const QString &configName);
    ConfigInfo(const ConfigInfo &other);
    ConfigInfo &operator=(const ConfigInfo &other);
    bool operator==(const ConfigInfo &other) const;
    bool operator!=(const ConfigInfo &other) const;
    bool operator<(const ConfigInfo &other) const;

    static bool configInfoSort(
        const ConfigInfo first, const ConfigInfo second);

    void setRobotType(const MetaType::RobotType &robotType);

    QString m_configName;
    MetaType::RobotType m_robotType = MetaType::RobotType_invalid;
    MetaType::RobotType m_robotDHType = MetaType::RobotType_invalid;
    double m_maxPayload = 0;
    QString m_language;
    bool m_realRobotSimulationEnabled = true;

    QString m_theme;

private:
    void copyOthertoSelf(const ConfigInfo &other);
};
Q_DECLARE_METATYPE(ConfigInfo)
