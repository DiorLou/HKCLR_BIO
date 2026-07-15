/**
 * @File Name: toolcalibrateinterface.h
 * @brief  : WorkPiece Calibrate Interface For GUI
 * @Author : yangchao email:yangchaoD@inovance.com
 * @Version : 1.0
 * @Creat Date : 2024-02-27
 *
 * @Copyright (C), 2023-2024 inovance. Co., Ltd. All rights
 */
#pragma once

#include "communication_global.h"
#include "wobjparams.h"
#include "toolparams.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 工件标定接口类
class COMMUNICATION_EXPORT WObjCalibrateInterface
{
public:
    WObjCalibrateInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    quint16 GetWObjCount();

    bool SetCurrentWObjId(quint16 currentId);

    bool GetCurrentWobjParam(WobjParams &params);
    bool GetWobjParam(quint16 wobjNo, WobjParams &params);
    bool SetWobjParam(quint16 wobjNo, const WobjParams &params);

    bool SaveWObjParams(int wobjNo, WobjParams *data);
    bool RefreshWObjParams(int wobjNo, WobjParams *data);

    bool ClearWobjParams(int wobjNo);

    bool WObjCalibrate(const QString &mechUnitName,
                       Robot_WObjType type,
                       bool isUFFix,
                       const CalibratePoints &midUFramePos,
                       const CalibratePoints &midOFramePos,
                       const Pos &oldUFramePos,
                       const Ori &oldUFrameOri,
                       Pos &uFrameCalibResultPos,
                       Ori &uFrameCalibResultOri,
                       Pos &oFrameCalibResultPos,
                       Ori &oFrameCalibResultOri);

    bool SaveWObjCalibratePoints(quint16 wobjNo,
                                 const CalibratePoints &uFramePoint,
                                 const CalibratePoints &oFramePoint);
    bool RefreshWObjCalibratePoints(quint16 wobjNo,
                                    CalibratePoints &uFramePoint,
                                    CalibratePoints &oFramePoint);

    bool WObjMoveToPoint(const Pos &pos, const Ori &ori, int arm[4],
                         Robot_MoveType type, Robot_WObjType method);

    /*************************************** 提供字符串给页面 ****************************************/

    QString WobjIdNameSearch(quint16 id);

    QString CalibUFrameMethodNameSearch(Robot_WObj_UFrame_CalMethod method);
    QString CalibOFrameMethodNameSearch(Robot_WObj_OFrame_CalMethod method);

    void HoldTypeUFrameCalibMethodSearch(Robot_WObjType type,
                                         QVector<QString> &vecMethods);

    void HoldTypeOFrameCalibMethodSearch(Robot_WObjType type,
                                         QVector<QString> &vecMethods);

    void WObjUFramePointsNameQuery(Robot_WObj_UFrame_CalMethod method,
                                   QVector<QString> &vecPointsName);
    void WObjOFramePointsNameQuery(Robot_WObj_OFrame_CalMethod method,
                                   QVector<QString> &vecPointsName);
};
