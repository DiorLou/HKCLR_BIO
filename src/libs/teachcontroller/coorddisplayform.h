#ifndef COORDDISPLAYFORM_H
#define COORDDISPLAYFORM_H

#include "abstractwidget.h"
#include "coordparam.h"
#include "teachcontroller_global.h"

namespace Ui
{
class CoordDisplayForm;
}

class TEACHCONTROLLER_EXPORT CoordDisplayForm
    : public AbstractWidget<Ui::CoordDisplayForm>
{
    Q_OBJECT

public:
    explicit CoordDisplayForm(QWidget *parent = nullptr);
    ~CoordDisplayForm();

    void SetPageIndex(int index);
    void SetPosFormatIdx(int index);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void retranslateUi();
public slots:
    void slot_updateRealtimeRoadPoint();

private slots:
    void slot_posformat_changed(RobotCoordDisplayFormat foramt);

    void on_cmb_coordType_display_activated(int index);

    void slot_controllerConnectionStatusChanged(ControllerConnectionState status);

private:
    void setInvalidPosition();
    void updateUI();

private:
    Ui::CoordDisplayForm *ui;
};

#endif  // COORDDISPLAYFORM_H
