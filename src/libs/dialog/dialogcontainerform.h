#pragma once

#include <QStack>
#include "generalcustomwidget.h"
#include "dialog_global.h"
class QMutex;
class QStackedWidget;
class LockScreenForm;
class EventForm;
class ProgressBarForm;
class Application;
class RobotEventInfo;
class ProcessBarFormWithComm;
class CurrentAuthorityForm;
class ChangeAuthorityForm;
class CustomAuthorityForm;
class ProcessProgressForm;
class ControllerAuthorityForm;
class ControllerForm;
class UpdatePopupForm;
class ConnectControllerForm;

typedef struct stDialogInfo
{
    int index;
    int width;
    int height;
    QWidget *widget;

    stDialogInfo()
    {
        index = -1;
        width = 0;
        height = 0;
        widget = nullptr;
    }
} DialogInfo;

class DIALOG_EXPORT DialogContainerForm : public GeneralCustomWidget
{
    Q_OBJECT
    Q_PROPERTY(bool isNeedLogicProcess MEMBER m_isNeedLogicProcess)
public:
    enum DialogStackForm {
        DialogStackForm_LockScreenForm,
        DialogStackForm_ProgressBarForm,
        DialogStackForm_ProcessBarFormWithComm,
        DialogStackForm_CurrentAuthorityForm,
        DialogStackForm_ChangeAuthorityForm,
        DialogStackForm_CustomAuthorityForm,
        DialogStackForm_ProcessProgressForm,
        DialogStackForm_ControllerAuthorityForm,
        DialogStackForm_ConnectControllerForm,
        DialogStackForm_BasicConditionContainerForm,
        DialogStackForm_ControllerForm,
    };
    Q_ENUM(DialogStackForm)

    static DialogContainerForm *instance();

    explicit DialogContainerForm(QWidget *parent = 0);

    Q_INVOKABLE void showDialog();
    void showDialog(int dialogType);
    void hideDialog(int dialogType);

    void showPasswordValidationForm(QWidget *widgetCaller);

    Q_INVOKABLE void processRobotEventInfo(const RobotEventInfo &robotEventInfo);

    Q_INVOKABLE bool isVisible() const;

    void registDialog(QWidget *widget, int width, int height, int index = -1);
    void showDialog(const QString &sName);
    void hideDialog(const QString &sName);
    QWidget *getReigstedDialog(const QString &sName);

public slots:
    void slot_showLockScreenForm();

protected:
    void closeEvent(QCloseEvent *closeEvent);
private:
    QStackedWidget *m_stackedWidget;

    LockScreenForm *m_lockScreenForm;
    ProgressBarForm *m_progressBarForm;
    ProcessBarFormWithComm *m_processBarFormWithComm;
    CurrentAuthorityForm* m_currentAuthorityForm;
    ChangeAuthorityForm* m_changeAuthorityForm;
    CustomAuthorityForm* m_customAuthorityForm;
    ProcessProgressForm* m_processProgressForm;
    ControllerAuthorityForm* m_controllerAuthorityForm;
    ControllerForm *m_controllerForm;
    ConnectControllerForm *m_connectControllerForm;
    QStack<int> m_dialogStack;

    QMap<QString, DialogInfo> m_mapDialogs;

    QMutex *m_mutex;

    void showLockScreenForm();

    bool m_isNeedLogicProcess = true;
};
