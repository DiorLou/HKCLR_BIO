#include "coordselectform.h"
#include "ui_coordselectform.h"
#include "communication.h"
#include "communicationengine.h"

CoordSelectForm::CoordSelectForm(QWidget *parent) :
    AbstractWidget(0, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::CoordSelectForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    updateUI();
}

CoordSelectForm::~CoordSelectForm()
{
    delete ui;
}

QString CoordSelectForm::GetToolName()
{
    return ui->cmb_toolNo->currentText();
}

QString CoordSelectForm::GetWObjName()
{
    return ui->cmb_wobjNo->currentText();
}

int CoordSelectForm::GetCoordIndex()
{
    return ui->cmb_coordType->currentIndex();
}

void CoordSelectForm::setConnectionsDefault(bool bEnable)
{
    m_bDefaultEnable = bEnable;
}

void CoordSelectForm::showEvent(QShowEvent *event)
{
    updateUI();
    if (m_bDefaultEnable) {
        setConnectionsEnable(true);
    }
}

void CoordSelectForm::hideEvent(QHideEvent *event)
{
    setConnectionsEnable(false);
}

void CoordSelectForm::on_cmb_coordType_activated(int index)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (!isVisible()) {
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetCoordType,
        static_cast<RobotCoordType>(index));
}

void CoordSelectForm::on_cmb_toolNo_activated(int index)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (!isVisible()) {
        return;
    }
    if (Communication::instance()->getCurRunStatus()
        == MetaType::COBOT_CONTROLLER_RUN_STATUS_START) {
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetToolId, index);
}

void CoordSelectForm::on_cmb_wobjNo_activated(int index)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (!isVisible()) {
        return;
    }
    if (Communication::instance()->getCurRunStatus()
        == MetaType::COBOT_CONTROLLER_RUN_STATUS_START) {
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetWObjId, index);
}

void CoordSelectForm::on_cmb_LoadNo_activated(int index)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (!isVisible()) {
        return;
    }
    if (Communication::instance()->getCurRunStatus()
        == MetaType::COBOT_CONTROLLER_RUN_STATUS_START) {
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetLoadId, index);
}

void CoordSelectForm::slot_control_toolNo_Changed(int index)
{
    qDebug() << "[controller]toolid = " << index 
             << "|" << ui->cmb_toolNo->currentIndex();
    emit signal_mechine_unit_changed();
    updateUI();
}

void CoordSelectForm::slot_control_wobjNo_Changed(int index)
{
    emit signal_mechine_unit_changed();
    updateUI();
}

void CoordSelectForm::slot_control_LoadNo_Changed(int index)
{
    emit signal_mechine_unit_changed();
    updateUI();
}

void CoordSelectForm::slot_control_coordtype_changed(RobotCoordType type)
{
    emit signal_mechine_unit_changed();
    updateUI();
}

void CoordSelectForm::updateUI()
{
    if (m_bFistUpdate) {
        ui->cmb_toolNo->addItems(Communication::instance()->getCurToolNames());
        ui->cmb_wobjNo->addItems(Communication::instance()->getCurWobjNames());
        ui->cmb_LoadNo->addItems(Communication::instance()->getLoadNames());
        m_bFistUpdate = false;
    }
    int toolId = Communication::instance()->GetCurToolId();
    int wobjId = Communication::instance()->GetCurWObjId();
    int loadId = Communication::instance()->GetCurLoadId();

    if (loadId != ui->cmb_LoadNo->currentIndex()) {
        ui->cmb_LoadNo->setCurrentIndex(loadId);
    }
    if (wobjId != ui->cmb_wobjNo->currentIndex()) {
        ui->cmb_wobjNo->setCurrentIndex(wobjId);
    }
    if (toolId != ui->cmb_toolNo->currentIndex()) {
        ui->cmb_toolNo->setCurrentIndex(toolId);
    }
    ui->cmb_coordType->setCurrentIndex(
        static_cast<int>(Communication::instance()->GetCurCoodType()));
}

void CoordSelectForm::setConnectionsEnable(bool bEnable)
{
    if (bEnable) {
        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_coordtype_changed,
                this,
                &CoordSelectForm::slot_control_coordtype_changed);

        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_ToolChanged,
                this,
                &CoordSelectForm::slot_control_toolNo_Changed);
        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_WobjChanged,
                this,
                &CoordSelectForm::slot_control_wobjNo_Changed);
        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_LoadChanged,
                this,
                &CoordSelectForm::slot_control_LoadNo_Changed);

        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_settool_result,
                this,
                &CoordSelectForm::slot_settool_result);

        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_setwobj_result,
                this,
                &CoordSelectForm::slot_setwobj_result);

        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_setload_result,
                this,
                &CoordSelectForm::slot_setload_result);

        connect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_controllerConnectionStatusChanged,
                this, &CoordSelectForm::slot_controllerConnectionStatusChanged);
    } else {
        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_coordtype_changed,
                   this,
                   &CoordSelectForm::slot_control_coordtype_changed);

        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_ToolChanged,
                   this,
                   &CoordSelectForm::slot_control_toolNo_Changed);
        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_WobjChanged,
                   this,
                   &CoordSelectForm::slot_control_wobjNo_Changed);
        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_LoadChanged,
                   this,
                   &CoordSelectForm::slot_control_LoadNo_Changed);

        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_settool_result,
                   this,
                   &CoordSelectForm::slot_settool_result);

        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_setwobj_result,
                   this,
                   &CoordSelectForm::slot_setwobj_result);

        disconnect(CommunicationEngine::instance(),
                   &CommunicationEngine::signal_setload_result,
                   this,
                   &CoordSelectForm::slot_setload_result);

        disconnect(CommunicationEngine::instance(),
                &CommunicationEngine::signal_controllerConnectionStatusChanged,
                this, &CoordSelectForm::slot_controllerConnectionStatusChanged);
    }
}

void CoordSelectForm::slot_settool_result(QObject *object, bool isSuccess, int toolId)
{
    if (object != this) return;

    if (!isSuccess) {
        updateUI();
    }
}

void CoordSelectForm::slot_setwobj_result(QObject *object, bool isSuccess, int wobjId)
{
    if (object != this) return;

    if (!isSuccess) {
        updateUI();
    }
}

void CoordSelectForm::slot_setload_result(QObject *object, bool isSuccess, int loadId)
{
    if (object != this) return;

    if (!isSuccess) {
        updateUI();
    }
}

void CoordSelectForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    if (ControllerConnectionState_Connected == status) {
        updateUI();
    }
}

void CoordSelectForm::retranslateUi()
{
    ui->retranslateUi(this);
}
