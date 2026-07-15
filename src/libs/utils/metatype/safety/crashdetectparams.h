#ifndef CRASHDETECTPARAMS_H
#define CRASHDETECTPARAMS_H

#include <QVariant>

/** 协作碰撞检测 **/
enum CobotCollisionDetectLevel
{
    CobotCollisionDetectLevel_Strict,
    CobotCollisionDetectLevel_General,
    CobotCollisionDetectLevel_Loose,
    CobotCollisionDetectLevel_None,
};

/** 工业碰撞检测 **/
enum CobotColDetectDevModeEnum
{
    COBOT_COLDETECT_MODE_UNKNOW = -1,   /// > 未知
    COBOT_COLDETECT_MODE_MANUAL,        /// > 手动
    COBOT_COLDETECT_MODE_AUTO,          /// > 自动
};

/** 协作 **/
typedef struct stCollisionProtectiontParams
{
    stCollisionProtectiontParams()
    {
        level = 0;
        strategy = 0;
        colldist = 0;
    }
    qint16 level;
    qint16 strategy;
    qint32 colldist;
} CollisionProtectiontParams;

#endif  // CRASHDETECTPARAMS_H
