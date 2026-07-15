#pragma once

#include "dialog_global.h"
#include "abstractwidget.h"
#include <QDateTime>
#include "metatype.h"

class QRadioButton;

namespace Ui
{
class ConnectControllerForm;
}
class QTimer;
class DIALOG_EXPORT ConnectControllerForm : public AbstractWidget<Ui::ConnectControllerForm>
{
    Q_OBJECT

public:
    static ConnectControllerForm *instance();

    explicit ConnectControllerForm(QWidget *parent = 0);
    ~ConnectControllerForm();

    void getFunctionEnabledList(QList<QVariant> &retList);
    void initialize();

    Q_INVOKABLE void viewEnabled(bool isEnabled);

    Q_INVOKABLE void triggerAutoConnect();
    Q_INVOKABLE QString getIP() const;
    Q_INVOKABLE void refreshWifiName();

protected:
    void retranslateUi() override;
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pbn_connectController_clicked(bool checked);

    void slot_connectControllerInterface_result(QObject *object,
                                                bool isSuccess);
    void slot_disconnectControllerInterface_result(QObject *object,
                                                   bool isSuccess);
    void slot_controllerConnectionStatusChanged(
        ControllerConnectionState status);

    void slot_controllerStateChanged(ControllerState state);
    void on_le_ip_textChanged(const QString &arg1);

    void on_pbn_close_clicked();

private:
    Ui::ConnectControllerForm *ui;
    QRadioButton *pbn_connectBtn = nullptr;
};

