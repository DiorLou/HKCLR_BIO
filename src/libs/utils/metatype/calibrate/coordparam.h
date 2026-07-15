#pragma once

#include <QString>
#include "roadpoint.h"
#include "metatype_global.h"

const char BaseCoordinate[] = "BaseCoord";
const char ToolCoordinate[] = "ToolCoord";
const char UserCoordinate[] = "UserCoord";
const char JoinCoordinate[] = "JoinCoord";
const char WorldCoordinate[] = "WorldCoord";

enum RobotCoordType {
    RobotCoordType_Base,
    RobotCoordType_Tool,
    RobotCoordType_User,
    RobotCoordType_Joint,
    RobotCoordType_World
};

enum RobotCoordDisplayFormat {
    RobotCoordDisplayFormat_Base,
    RobotCoordDisplayFormat_User,
    RobotCoordDisplayFormat_World,
    RobotCoordDisplayFormat_Flange,
    RobotCoordDisplayFormat_Joint,
};

class ToolParam;

class METATYPE_EXPORT CoordParam
{
public:
    CoordParam();
    CoordParam(const QString &coordTypeOrName);
    CoordParam(const CoordParam &other);
    CoordParam &operator=(const CoordParam &other);
    bool operator==(const CoordParam &other) const;
    bool operator!=(const CoordParam &other) const;
    bool operator<(const CoordParam &other) const;

    void init();

    bool isExist();

    ToolParam getToolParam() const;

    static void coordParamListSort(QList<CoordParam> &tar);
    static bool coordParamSort(
        const CoordParam first, const CoordParam second);

    QString m_coordType;
    QString m_coordName;  // "Base" "End" "User"
    QString m_toolName;

private:
    void copyOthertoSelf(const CoordParam &other);
};
