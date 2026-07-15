#pragma once

#include "abstractwidget.h"
#include "teachcontainer_global.h"
#include "simcontainerform.h"
#include "commandinfo.h"

class CoordParam;
class QGroupBox;

namespace Ui
{
class TeachContainerForm;
}

class TEACHCONTAINER_EXPORT TeachContainerForm
    : public AbstractWidget<Ui::TeachContainerForm>
{
    Q_OBJECT

public:
    static TeachContainerForm *instance();

    explicit TeachContainerForm(QWidget *parent = 0);
    ~TeachContainerForm();

    void initialize();

    void delayInitialized();

    // 权限管理
    void getFunctionEnabledList(QList<QVariant> &retList);
    Q_INVOKABLE void axisMoveEnabled(bool isEnabled);
    Q_INVOKABLE void coordDisplayEnabled(bool isEnabled);
    Q_INVOKABLE void stepGradeEnabled(bool isEnabled);
    Q_INVOKABLE void mechineunitLockEnabled(bool isEnabled);
    Q_INVOKABLE void move2pointEnabled(bool isEnabled);
    Q_INVOKABLE void setCurrentPositionEnabled(bool isEnabled);

    Q_INVOKABLE int getPtFileCount();

    Q_INVOKABLE void refreshMove2Point();

protected:
    virtual void retranslateUi();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pbn_mechLock_clicked(bool checked);

private slots:
    void slot_mechLockStateChanged(bool enable);
    void slot_enableMechLockInterface_result(QObject *object, bool isSuccess);

    void slot_getPtFileList_result(QObject *object, const QStringList &fileList);
    void slot_control_getPtList_result(
        QObject *object,
        const QVector<InoRPointInfo> vecRPointInfos,
        const QVector<InoJPointInfo> vecJPointInfos);
    void slot_control_setcurrent_result(QObject *object, bool isSuccess);

    void slot_controllerConnectionStatusChanged(ControllerConnectionState status);
    void slot_KineInverseSolution_result(
        QObject *object, bool bRet, int iRetCode, const QVector<double> &joints);

    void on_cmb_fileList_activated(int index);
    void on_cmb_ptlist_activated(int index);
    void on_pbn_ctrl_getcurrent_clicked();

    void on_pbn_ctrl_movehere_pressed();

private:
    void updateUI();

    void updateSimForm();

    void updateRoadPointData();
    void updateMoveTypeOptions();

private:
    Ui::TeachContainerForm *ui;

    int m_iMainTabIndex = -1;

    QVector<InoRPointInfo> m_vecRPointInfos;
    QVector<InoJPointInfo> m_vecJPointInfos;

    RoadPoint m_pt;
};
