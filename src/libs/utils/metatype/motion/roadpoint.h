#pragma once

#include "pos.h"
#include "ori.h"
#include "metatype.h"
#include "metatype_global.h"
class QString;

class METATYPE_EXPORT RoadPoint
{
public:
    RoadPoint();
    RoadPoint(const RoadPoint &other);
    RoadPoint operator=(const RoadPoint &org);
    bool operator==(const RoadPoint &other) const;
    bool operator!=(const RoadPoint &other) const;

    void init(void);
    void setJointAngle(double *jointAngle, int robotDof = ROBOT_DOF);
    void setJointAngle(QList<double> jointAngle);
    void setJointRadian(double *jointRadian, int robotDof = ROBOT_DOF);

    void setArmAgrs(int *armArgs, int armLen = ROBOT_ARM_NUM);

    void print();

    static bool isRoadpointStr(const QString &src);
    static RoadPoint string2Roadpoint(const QString &src);
    static QString roadPoint2String(RoadPoint src);
    QString getJointValueStringForScriptInterface();
    QString getPosValueStringForScriptInterface();
    QString getJointValueString();
    static bool isEqual(const RoadPoint &point1, const RoadPoint &point2);
    static bool dequals(const double &a, const double &b);
    static double angle2Radian(const double &angle);
    static double radian2Angle(const double &radian);

    double getJointAngle(const int JointNo) const;

    Pos m_position;  // Unit: meters
    Ori m_orientation;
    double m_jointAngle[ROBOT_DOF];
    double m_jointRadian[ROBOT_DOF];
    int m_arm[ROBOT_ARM_NUM];
    bool m_isSingular = false;
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(RoadPoint)
#endif
