#pragma once

#include "simulationform_global.h"
#include "abstractwidget.h"
#include "simcontainerform.h"
#include "pileupinfo.h"
#include "pos.h"
#include "ori.h"

class RoadPoint;

class SimContainerForm;

namespace Ui
{
class SimulationForm;
}

class SIMULATIONFORM_EXPORT SimulationForm
    : public AbstractWidget<Ui::SimulationForm>
{
    Q_OBJECT

public:
    static SimulationForm *instance();
    explicit SimulationForm(QWidget *parent = 0);
    ~SimulationForm();

    void initialize();

    SimContainerForm *getSimContainerForm();

    void setSimulationFormSize(const QSize &size);

    void enableDrawTrack(bool bEnable);

    void enableDrawTargetRoadPoint(bool bEnable);

    void enableDrawRealTimeRoadPoint(bool bEnable);

    void enableDrawGroundModel(bool bEnable);

    void enableInstallationMode(bool bEnable);

    void enableDrawInstallationReferenceLocationModel(bool bEnable);

    void enableDrawInstallationRealLocationModel(bool bEnable);

    void enableDrawInstallationGroundModel(bool bEnable);

    void setTemporaryInstallParams(const double &alpha, const double &beta);

    void setTargetRoadPoint(RoadPoint position);
    RoadPoint getTargetRoadPoint();

    void setRealTimeRoadPoint(RoadPoint position);
    RoadPoint getRealTimeRoadPoint();

    void setCurrentIndex(SimContainerForm::SimStackIndex index);
    void setTeachPageEnable(bool bEnable);
    int getCurrentIndex();

    void addDePallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removeDePallet(const QString &uuid);

    void removeAllDePallet();

    void addPallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removePallet(const QString &uuid);

    void removeAllPallet();

    Q_INVOKABLE void addDepalletizingBox(const QString &uuid,const int &boxNum,const QString &wobj,
                             const Pos &pos, const Ori &ori,
                             const CubeSize &size,const Ori& rotate,const bool &isVisible = true);

    Q_INVOKABLE void setData(int index,bool leftOrRight);
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

    void extensionsInitialized();

    Q_INVOKABLE void clearTrack();
signals:
    void changeData(int index,bool leftOrRight);
protected:
    virtual void retranslateUi() override;

private:
    Ui::SimulationForm *ui;

    SimContainerForm *m_simContainerForm;

};

class Ui_SimulationForm
{
public:
    QVBoxLayout *mainLayout;
    void setupUi(QWidget *widgetMiddle);
    void retranslateUi(QWidget *widgetMiddle);
};

namespace Ui
{
class SimulationForm : public Ui_SimulationForm
{
};
}  // namespace Ui
