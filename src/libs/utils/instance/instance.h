#pragma once

#include "instance_global.h"
#include <QObject>

class INSTANCE_EXPORT Instance : public QObject
{
    Q_OBJECT

public:
    static Instance *instance();

    Instance();
    virtual ~Instance();

    static QObject *common();
    static void setCommon(QObject *common);

    static QObject *logicTreeModel();
    static void setLogicTreeModel(QObject *logicTreeModel);

    static QObject *languageForm();
    static void setLanguageForm(QObject *languageForm);

    static QObject *toolCalibrateForm();
    static void setToolCalibrateForm(QObject *toolCalibrateForm);

    static QObject *toolKinematicsResultForm();
    static void setToolKinematicsResultForm(
        QObject *toolKinematicsResultForm);

    static QObject *toolDynamicsCalibrateForm();
    static void setToolDynamicsCalibrateForm(
        QObject *toolDynamicsCalibrateForm);

    static QObject *comm();
    static void setComm(QObject *communication);

    static QObject *variableConfigForm();
    static void setVariableConfigForm(QObject *variableConfigForm);

    static QObject *commEngine();
    static void setCommEngine(QObject *commEngine);

    static QObject *mainWidget();
    static void setMainWidget(QObject *mainWidget);

    static QObject *dialogContainerForm();
    static void setDialogContainerForm(QObject *dialogContainerForm);

    static QObject *modellessDialogContainerForm();
    static void setModellessDialogContainerForm(QObject *modellessDialogContainerForm);

    static QObject *virtualKeyboard();
    static void setVirtualKeyboard(QObject *virtualKeyboard);

    static QObject *logicalExpressionKeyboard();
    static void setLogicalExpressionKeyboard(
        QObject *logicalExpressionKeyboard);

    static QObject *projectManageForm();
    static void setProjectManageForm(QObject *projectManageForm);

    static QObject *procedureLoadForm();
    static void setProcedureLoadForm(QObject *procedureLoadForm);

    static QObject *programmingContainerForm();
    static void setProgrammingContainerForm(
        QObject *programmingContainerForm);

    static QObject *tcpClientEngine();
    static void setTcpClientEngine(QObject *tcpClientEngine);

    static QObject *tcpServerEngine_ui();
    static void setTcpServerEngine_ui(QObject *tcpServerEngine_ui);

    static QObject *tcpServerEngine_scriptRuntime();
    static void setTcpServerEngine_scriptRuntime(
        QObject *tcpServerEngine_scriptRuntime);

    static QObject *mainThreadEngine();
    static void setMainThreadEngine(QObject *mainThreadEngine);

    static QObject *moveToReadyPointForm();
    static void setMoveToReadyPointForm(QObject *moveToReadyPointForm);

    static QObject *scriptController();
    static void setScriptController(QObject *scriptController);

    static QObject *timerConditionStateForm();
    static void setTimerConditionStateForm(QObject *timerConditionStateForm);

    static QObject *variableStateForm();
    static void setVariableStateForm(QObject *variableStateForm);

    static QObject *coordCalibrateForm();
    static void setCoordCalibrateForm(QObject *coordCalibrateForm);

    static QObject *shutdownThread();
    static void setShutdownThread(QObject *shutdownThread);

    static QObject *disclaimerDialog();
    static void setDisclaimerDialog(QObject *disclaimerDialog);

    static QObject *robotInitForm();
    static void setRobotInitForm(QObject *robotInitForm);

    static QObject *toolIOStateForm();
    static void setToolIOStateForm(QObject *toolIOStateForm);

    static QObject *interfaceBoardUserIOStateForm();
    static void setInterfaceBoardUserIOStateForm(
        QObject *interfaceBoardUserIOStateForm);

    static QObject *scriptStateMachine();
    static void setScriptStateMachine(QObject *scriptStateMachine);

    static QObject *application();
    static void setApplication(QObject *application);

    static QObject *versionForm();
    static void setVersionForm(QObject *versionForm);

    static QObject *manualForm();
    static void setManualForm(QObject *manualForm);

    static QObject *settingsContainerForm();
    static void setSettingsContainerForm(QObject *settingsContainerForm);

    static void setMonitoringContainerForm(QObject *monitoringContainerForm);
    static QObject *MonitoringContainerForm();

    static void setSafetyContainerForm(QObject *safetyContainerForm);
    static QObject *SafetyContainerForm();

    static QObject *fixedPoseForm();
    static void setFixedPoseForm(QObject *fixedPoseForm);

    static QObject *displayForm();
    static void setDisplayForm(QObject *systemForm);

    static QObject *securityConfigForm();
    static void setSecurityConfigForm(QObject *securityConfigForm);

    static QObject *lineNumbersView();
    static void setLineNumbersView(QObject *lineNumbersView);

    static QObject *educationContainerForm();
    static void setEducationContainerForm(QObject *educationContainerForm);

    static QObject *connectControllerForm();
    static void setConnectControllerForm(QObject *connectControllerForm);

    static QObject *setConditionForm();
    static void setSetConditionForm(QObject *setConditionForm);

    static QObject *scriptConditionForm();
    static void setScriptConditionForm(QObject *scriptConditionForm);

    static QObject *xmlReader();
    static void setXmlReader(QObject *xmlReader);

    static QObject *programmingForm();
    static void setProgrammingForm(QObject *programmingForm);

    static QObject *logicTreeView();
    static void setLogicTreeView(QObject *logicTreeView);

    static QObject *messageConditionForm();
    static void setMessageConditionForm(QObject *messageConditionForm);

    static QObject *procedureSaveForm();
    static void setProcedureSaveForm(QObject *procedureSaveForm);

    static QObject *defaultProjectForm();
    static void setDefaultProjectForm(QObject *defaultProjectForm);

    static QObject *projectListForm();
    static void setProjectListForm(QObject *projectListForm);

    static QObject *safetyCartesianPostionForm();
    static void setSafetyCartesianPostionForm(QObject *cpForm);

    static QObject *programContainerForm();
    static void setProgramContainerForm(QObject *programContainerForm);

    static QObject *projectManagementContainerForm();
    static void setProjectManagementContainerForm(
        QObject *projectManagementContainerForm);

    static QObject *programManagementForm();
    static void setProgramManagementForm(QObject *programManagementForm);

    static QObject *pointFileForm();
    static void setPointFileForm(QObject *pointFileForm);

    static QObject *labelForm();
    static void setLabelForm(QObject *labelListForm);

    static QObject *tempVariablesForm();
    static void setTempVariablesForm(QObject *tempVariablesForm);

    static QObject *defineWarningFileForm();
    static void setDefineWarningFileForm(QObject *defineWarningFileForm);

    static QObject *scriptFileForm();
    static void setScriptFileForm(QObject *scriptFileForm);

    static QObject *logicalExpressKeyBoardPropertySource();
    static void setLogicalExpressKeyBoardPropertySource(QObject *);

    static QObject *taskConditionForm();
    static void setTaskConditionForm(QObject *taskConditionForm);

    static QObject *taskManagementForm();
    static void setTaskManagementForm(QObject *taskManagementForm);

    static QObject *wobjCalForm();
    static void setWobjCalForm(QObject *wobjCalForm);

    static QObject *authorityManageForm();
    static void setAuthorityManageForm(QObject *authorityManageForm);
    
    static QObject *zoneHomeSettingForm();
    static void setZoneHomeSettingForm(QObject *zoneHomeSettingForm);

    static QObject *changeAuthorityForm();
    static void setChangeAuthorityForm(QObject *changeAuthorityForm);

    static QObject *customAuthorityForm();
    static void setCustomAuthorityForm(QObject *customAuthorityForm);

    static QObject *controlAuthorityForm();
    static void setControlAuthorityForm(QObject *controlAuthorityForm);

    static QObject *logForm();
    static void setLogForm(QObject *logForm);

    static QObject *palletEditFileMapping();
    static void setPalletEditFileMapping(QObject *fileMap);

    static QObject *simulationForm();
    static void setSimulationForm(QObject *simForm);

    static QObject *palletizingForm();
    static void setPalletizingForm(QObject *palletForm);

    static QObject *modbusConditionForm();
    static void setModbusConditionForm(QObject *modbusConditionForm);

    static QObject *gotoConditionForm();
    static void setGotoConditionForm(QObject *gotoConditionForm);

    static QObject *gotoLabelConditionForm();
    static void setGotoLabelConditionForm(QObject *labelConditionForm);

    static QObject *getParseExpressions();
    static void setParseExpressions(QObject *parseExpressions);

signals:
    void enabledChanged(bool enabled);
};
