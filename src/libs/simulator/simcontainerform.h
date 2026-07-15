#pragma once

#include "simulator_global.h"
#include "abstractwidget.h"
#include "metatype.h"

#include "simmodelwidget.h"
#include "pileupinfo.h"
#include "pos.h"
#include "ori.h"

 class SimBaseForm;
class RoadPoint;

namespace Ui
{
class SimContainerForm;
}

class SIMULATOR_EXPORT SimContainerForm
    : public AbstractWidget<Ui::SimContainerForm>
{
    Q_OBJECT

public:
    enum SimType {
        SimType_Base,
        SimType_Coord,
        SimType_Tool
    };

    enum SimStackIndex {
        SimStackIndex_RealTimeData,
        SimStackIndex_Sim3D,
        SimStackIndex_Teach
    };

    explicit SimContainerForm(
        const SimContainerForm::SimType &simType,
        QWidget *parent, bool isUpdateRealTimeRoadPoint = true);
    ~SimContainerForm();

    SimBaseForm *m_simForm = nullptr;



    QWidget *getSimForm();

    void updateUI(const RoadPoint &roadPoint);

    void setTargetRoadPoint(RoadPoint position);
    RoadPoint getTargetRoadPoint();
    void setRealTimeRoadPoint(RoadPoint position);
    RoadPoint getRealTimeRoadPoint();

    void setCurrentIndex(SimStackIndex index);
    void setTeachPageEnable(bool bEnable);
    int getCurrentIndex();

    //void resizeUI(int width, int height);

    void setDHParam(const DHParam &dhParam);

    void enableDrawTrack(bool bEnable);

    void enableDrawTargetRoadPoint(bool enable);

    void enableDrawRealTimeRoadPoint(bool bEnable = true);

    void enableDrawGroundModel(bool bEnable);

    void enableInstallationMode(bool bEnable);

    void enableDrawInstallationReferenceLocationModel(bool bEnable);

    void enableDrawInstallationRealLocationModel(bool bEnable);

    void enableDrawInstallationGroundModel(bool bEnable);

    void setTemporaryInstallParams(const double &alpha, const double &beta);

    void updateViewport();

    void setSimulationFormSize(const QSize &size);

    void addDePallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removeDePallet(const QString &uuid);

    void removeAllDePallet();

    void addPallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removePallet(const QString &uuid);

    void removeAllPallet();

    void addDepalletizingBox(const QString &uuid,const int &boxNum,const QString &wobj,
                             const Pos &pos, const Ori &ori,
                             const CubeSize &size,const Ori& rotate,const bool &isVisible = true);

    void *createPalletizingBox(const QString &uuid,const int &boxNum, const QString &wobj,
                                                   const Pos &pos, const Ori &ori, const CubeSize &size,
                                                   const Ori& rotate,const bool &isVisible = true);

    void removeDepalletizingBoxs(const QString &uuid);

    void removeAllPalletizingBoxs();

    bool isNeedReCreateModel(const QString &uuid);

    bool isAllowUpdateModel(const QString &uuid, const int &sum);

    void grapPalletizingBox(const QString &uuid, const int &boxNum);
    void grapPalletizingBox(const CubeSize &size, const Ori& rotate);

    void loosePalletizingBox(const QString &uuid, const int &boxNum,
                             const Pos &pos,const Ori &ori,
                             const QString& wobj);
    void loosePalletizingBox();

    void setPalletizingBoxVisible(const QString &uuid, const int &boxNum, bool bEnable);

    void setPalletizingBoxVisible(const QString &uuid, bool bEnable);

    void setAllPalletizingBoxVisible(bool bEnable);

    void setEnableDrawTrack(bool isDrawTrack);
    void setTrackDuration(const int &trackDuration);

protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *event);

public slots:
    // void slot_EnableDrawTrack(bool checked, int times);
    void slot_clearTrack();
    void slot_updateRealTimeRoadPoint();
    void slot_ToolChanged(int id);
    void slot_WobjChanged(int id);
    void slot_connectsuccess();
    void slot_intallposture_changed(double alpha, double beta);
    void setData(int index, bool leftOrRight);
private:
    void updateAlphaBeta();
#ifdef INOCOBOTTP_MSVC_QT5
    void connectRealtimeSignals();
    void disconnectRealtimeSignals();
#endif

private:
    Ui::SimContainerForm *ui;

    bool m_isUpdateRealTimeRoadPoint;
    SimStackIndex m_curIdx = SimStackIndex_Sim3D;
#ifdef INOCOBOTTP_MSVC_QT5
    bool m_realtimeSignalsConnected = false;
#endif
};
