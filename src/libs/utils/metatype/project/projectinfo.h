#pragma once

#include <QHash>
#include <QString>
#include "roadpoint.h"
#include "metatype_global.h"

class METATYPE_EXPORT ProjectRoadPointInfo
{
public:
    static ProjectRoadPointInfo *instance();

    void clearPointInfos();

    bool isLabelExist(const QString &sLabel, const QString &sType = QString());

    void updateRoadPointInfo(const QString &sType, int index,
                             const QString &sLable, const RoadPoint &pt);
    void deleteRoadPointInfo(const QString &sType, int index);
    RoadPoint getRoadPointByIndex(const QString &sType, int index);
    bool isRoadPointExist(const QString &sType, int index);
    RoadPoint getRoadPointByLabel(const QString &sLabel);

    int getPointsTotalNum(const QString &sType);
    int getIndexByLabel(const QString &sType, const QString & sLabel);

private:
    ProjectRoadPointInfo(QObject *parent = 0);
    virtual ~ProjectRoadPointInfo();

private:
    QHash<int, QPair<QString, RoadPoint> > m_hashRPInfos;
    QHash<int, QPair<QString, RoadPoint> > m_hashJPInfos;
};
