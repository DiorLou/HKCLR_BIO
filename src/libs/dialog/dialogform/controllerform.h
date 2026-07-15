#pragma once
#include <QWidget>

#include "abstractwidget.h"
#include "metatype.h"
#include "dialog_global.h"
namespace Ui
{
class ControllerForm;
}

class DIALOG_EXPORT ControllerForm : public AbstractWidget<Ui::ControllerForm>
{
    Q_OBJECT

public:
    static ControllerForm *instance();
    explicit ControllerForm(QWidget *parent = nullptr);
    ~ControllerForm();

protected:
    virtual void retranslateUi();

private slots:
    void on_pbn_connectController_clicked(bool checked);

    void on_pbn_mechLock_clicked(bool checked);

    void on_pbn_clearAlarm_clicked(bool checked);

    void on_pbn_enable_clicked(bool checked);

    void on_pbn_close_clicked();

    // Inovance Interface
    void slot_connectControllerInterface_result(
        QObject *object, bool isSuccess);
    void slot_disconnectControllerInterface_result(
        QObject *object, bool isSuccess);
    void slot_controllerConnectionStatusChanged(
        ControllerConnectionState status);
    void slot_enableMechLockInterface_result(
        QObject *object, bool isSuccess);
    void slot_mechLockStateChanged(bool enable);
    void slot_clearAlarmInterface_result(
        QObject *object, bool isSuccess);
    void slot_enableRobotInterface_result(
        QObject *object, bool isSuccess);
    void slot_enableStateChanged(bool enable);
    void slot_controllerStateChanged(ControllerState state);

    void slot_axisMoveInterface_result(
        QObject *object, bool isSuccess);

private:
    Ui::ControllerForm *ui;
};
