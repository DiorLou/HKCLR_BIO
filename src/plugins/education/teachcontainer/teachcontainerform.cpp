#include "teachcontainerform.h"
#include "ui_teachcontainerform.h"
#include <QDebug>
#include <QTimer>
#include "authoritytr.h"
#include "mainwidget.h"
#include "communicationengine.h"
#include "messagebox.h"
#include "communication.h"
#include "simcontainerform.h"
#include "propertydefine.h"
#include "cobotlog.h"
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include <QFuture>
#include "simulationform.h"
#include "pileupinfo.h"
#include "robotcontrolform.h"

#define SIM_WIDTH 659
#define SIM_HEIGHT 652

static TeachContainerForm *s_instance = 0;
static const int MAINWIDGET_TAB_TEACH_INDEX = 0;
static const int MAINWIDGET_TAB_ROBOT_CONTROL_INDEX = 1;

TeachContainerForm *TeachContainerForm::instance()
{
    return s_instance;
}

TeachContainerForm::TeachContainerForm(QWidget *parent) :
    AbstractWidget(parent, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::TeachContainerForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    s_instance = this;
    Instance::setEducationContainerForm(this);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_mechLockStateChanged,
            this, &TeachContainerForm::slot_mechLockStateChanged);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableMechLockInterface_result,
            this, &TeachContainerForm::slot_enableMechLockInterface_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_getPtFileList_result,
            this, &TeachContainerForm::slot_getPtFileList_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_control_getPtList_result,
            this, &TeachContainerForm::slot_control_getPtList_result);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &TeachContainerForm::slot_controllerConnectionStatusChanged);

    connect(CommunicationEngine::instance(), &CommunicationEngine::signal_KineInverseSolution_result,
            this, &TeachContainerForm::slot_KineInverseSolution_result);

    ui->wgt_teachcontroller->SetReleativeWidgets(ui->wgt_stepmode,
                                                 ui->wgt_coordselect,
                                                 ui->wgt_coorddisplay);
    ui->wgt_teachcontroller->UpdateUI();
    ui->wgt_teachcontroller->setJointBtnSize(QSize(105, 98));

    ui->cmb_movetype->setCurrentIndex(0);

    m_robotControlForm = new RobotControlForm;
}

TeachContainerForm::~TeachContainerForm()
{
    delete ui;
}

void TeachContainerForm::initialize()
{
    m_iMainTabIndex =
        MainWidget::instance()->addTabWidget(
            MAINWIDGET_TAB_TEACH_INDEX, this, tr("Teaching"),
        QString(":/menu/image/menu/teaching.svg"));

    m_iRobotControlTabIndex =
        MainWidget::instance()->addTabWidget(
            MAINWIDGET_TAB_ROBOT_CONTROL_INDEX,
            m_robotControlForm,
            tr("Robot Control"),
            QString(":/mainwidget/image/mainwidget/robotbodypoweron.svg"));

    ui->layout_simulator->addWidget(SimulationForm::instance());
    SimulationForm::instance()->setSimulationFormSize(
        ResolutionUtils::getRatioSize(QSize(SIM_WIDTH,SIM_HEIGHT)));
}

void TeachContainerForm::delayInitialized()
{

}

void TeachContainerForm::getFunctionEnabledList(QList<QVariant> &retList)
{
    retList.clear();
    retList.append(QVariant::fromValue(QPair<QString, QString>("axisMoveEnabled", AuthorityTr::tr("Enable axis movement button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("coordDisplayEnabled", AuthorityTr::tr("Enable coordinate display"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("stepGradeEnabled", AuthorityTr::tr("Enable jog level edit"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("mechineunitLockEnabled", AuthorityTr::tr("Enable mechanical lock button"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("move2pointEnabled", AuthorityTr::tr("Enable move to point"))));
    retList.append(QVariant::fromValue(QPair<QString, QString>("setCurrentPositionEnabled", AuthorityTr::tr("Enable set current position to point file"))));
}

void TeachContainerForm::retranslateUi()
{
    MainWidget::instance()->setTabText(MAINWIDGET_TAB_TEACH_INDEX,  QObject::tr("Teaching"));
    if (m_iRobotControlTabIndex >= 0)
        MainWidget::instance()->setTabText(m_iRobotControlTabIndex, tr("Robot Control"));
    ui->retranslateUi(this);
}

void TeachContainerForm::on_pbn_mechLock_clicked(bool checked)
{
    if (!Communication::instance()->isConnected()) {
        MessageBox::warning(tr("Controller not connected!"));
        return;
    }

    if (Communication::instance()->IsEnable()) {
        MessageBox::warning(tr("Cannot set mechanical lock when the robot is enabled."));
        return;
    }

    if (checked) {
        CommunicationEngine::instance()->enqueueCmd_enableMechLock(
            this, true);
    } else {
        CommunicationEngine::instance()->enqueueCmd_enableMechLock(
            this, false);
    }
}

void TeachContainerForm::slot_mechLockStateChanged(bool enable)
{
    qDebug() << "[TeachContainerForm::slot_mechLockStateChanged]" << enable;
    ui->pbn_mechLock->setChecked(enable);
}

void TeachContainerForm::showEvent(QShowEvent *)
{
    updateSimForm();
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_control_setcurrent_result,
            this, &TeachContainerForm::slot_control_setcurrent_result);

    updateUI();

    qDebug() << "@@@@ ui->widget_simulator->size : "
             << ui->widget_simulator->size();
}

void TeachContainerForm::hideEvent(QHideEvent *)
{
    qDebug()<<__FUNCTION__<<__FILE__;
    disconnect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_control_setcurrent_result,
               this, &TeachContainerForm::slot_control_setcurrent_result);
}

void TeachContainerForm::resizeEvent(QResizeEvent *event)
{
    AbstractWidget::resizeEvent(event);
}

void TeachContainerForm::slot_enableMechLockInterface_result(
    QObject *object, bool isSuccess)
{
    if (this == object && !isSuccess) {
        MessageBox::warning(tr("Failed to enable mechanical lock."));
    }
}

void TeachContainerForm::slot_getPtFileList_result(QObject *object, const QStringList &fileList)
{
    if (object != this) return;

    ui->cmb_fileList->clear();
    ui->cmb_fileList->addItems(fileList);

    if (fileList.isEmpty()) return;

    CommunicationEngine::instance()->enqueueCmd_setData(this, AbstractCmd::CmdType_Control_Move2Point_GetPtList,
                                                        ui->cmb_fileList->currentText());
}

void TeachContainerForm::slot_control_getPtList_result(
    QObject *object, const QVector<InoRPointInfo> vecRPointInfos, const QVector<InoJPointInfo> vecJPointInfos)
{
    if (object != this) return;

    ui->cmb_ptlist->clear();
    size_t ptsize = 0;
    if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
        ptsize = vecJPointInfos.size();
        m_vecJPointInfos = vecJPointInfos;
    } else {
        ptsize = vecRPointInfos.size();
        m_vecRPointInfos = vecRPointInfos;
    }

    for (int i = 0; i < ptsize; ++i) {
        if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
            ui->cmb_ptlist->addItem(QString::number(m_vecJPointInfos[i].pointNo));
        } else {
            ui->cmb_ptlist->addItem(QString::number(m_vecRPointInfos[i].pointNo));
        }
    }

    updateMoveTypeOptions();
}

void TeachContainerForm::slot_control_setcurrent_result(QObject *object, bool isSuccess)
{
    if (object != this) return;

    if (!isSuccess) {
        PRINT_MSG(tr("Failed to write the current point."));
    } else {
        m_pt = Communication::instance()->GetRealTimePt();

        if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[0] = m_pt.m_jointAngle[0];
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[1] = m_pt.m_jointAngle[1];
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[2] = m_pt.m_jointAngle[2];
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[3] = m_pt.m_jointAngle[3];
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[4] = m_pt.m_jointAngle[4];
            m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData[5] = m_pt.m_jointAngle[5];
        } else {
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[0] = m_pt.m_position.m_x;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[1] = m_pt.m_position.m_y;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[2] = m_pt.m_position.m_z;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[3] = m_pt.m_orientation.m_rz;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[4] = m_pt.m_orientation.m_ry;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.RPosData[5] = m_pt.m_orientation.m_rx;
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.ArmParm[0] = m_pt.m_arm[0];
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.ArmParm[1] = m_pt.m_arm[1];
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.ArmParm[2] = m_pt.m_arm[2];
            m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos.ArmParm[3] = m_pt.m_arm[3];
        }
        PRINT_MSG(tr("The current point written successfully."));
    }
}

void TeachContainerForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    if (ControllerConnectionState_Closed == status) {
        ui->cmb_fileList->clear();
        ui->cmb_ptlist->clear();
    }

    if (Communication::instance()->isConnectVirtualController()) {
        on_pbn_mechLock_clicked(true);
    }
}

void TeachContainerForm::slot_KineInverseSolution_result(
    QObject *object, bool bRet, int iRetCode, const QVector<double> &joints)
{
    if (object != this) {
        return;
    }

    if (bRet != true || iRetCode != 0) {
        LOG_INFO("[TeachContainerForm::slot_KineInverseSolution_result]kineinverse failed.");
        return;
    }

    m_pt.setJointAngle(joints.toList());

    if (ui->cmb_movetype->currentIndex() == 0 && ui->cmb_fileList->currentText().compare("JP.pts") != 0) {
        CommunicationEngine::instance()->enqueueCmd_robotMoveJointTeach(this, m_pt);
    }
}

void TeachContainerForm::updateUI()
{
    if (!Communication::instance()->isConnected()) return;

    bool isProjectLoad = Instance::common()->property("isProjectLoaded").value<bool>();
    if (!isProjectLoad) return;

    CommunicationEngine::instance()->enqueueCmd(this, AbstractCmd::CmdType_Control_Move2Point_GetFileList);
}

void TeachContainerForm::updateSimForm()
{
    ui->layout_simulator->addWidget(SimulationForm::instance());
    SimulationForm::instance()->setCurrentIndex(SimContainerForm::SimStackIndex_Sim3D);
    SimulationForm::instance()->setSimulationFormSize(
        ResolutionUtils::getRatioSize(QSize(SIM_WIDTH,SIM_HEIGHT)));
    SimulationForm::instance()->enableDrawTrack(false);
    SimulationForm::instance()->enableDrawTargetRoadPoint(false);
    SimulationForm::instance()->enableDrawRealTimeRoadPoint(true);
    SimulationForm::instance()->enableDrawGroundModel(true);
    SimulationForm::instance()->enableInstallationMode(false);
    SimulationForm::instance()->enableDrawInstallationReferenceLocationModel(false);
    SimulationForm::instance()->enableDrawInstallationRealLocationModel(false);
    SimulationForm::instance()->enableDrawInstallationGroundModel(false);
}

void TeachContainerForm::updateRoadPointData()
{
    if (ui->cmb_fileList->count() == 0 || ui->cmb_ptlist->count() == 0) {
        return;
    }

    m_pt.init();

    if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
        m_pt.setJointAngle(m_vecJPointInfos[ui->cmb_ptlist->currentIndex()].pos.JointData);
    } else {
        InoRobPos robPos = m_vecRPointInfos[ui->cmb_ptlist->currentIndex()].pos;
        m_pt.m_position.m_x = robPos.RPosData[0];
        m_pt.m_position.m_y = robPos.RPosData[1];
        m_pt.m_position.m_z = robPos.RPosData[2];
        m_pt.m_orientation.m_rz = robPos.RPosData[3];
        m_pt.m_orientation.m_ry = robPos.RPosData[4];
        m_pt.m_orientation.m_rx = robPos.RPosData[5];
        m_pt.setArmAgrs(robPos.ArmParm, ROBOT_ARM_NUM);

        short toolId = Communication::instance()->GetCurToolId();
        short wobjId = Communication::instance()->GetCurWObjId();
        CommunicationEngine::instance()->enqueueCmd_KineInverseSolution(
            this, toolId, wobjId, Communication::instance()->GetCurLoadId(), robPos.RPosData, robPos.ArmParm);
    }
}

void TeachContainerForm::updateMoveTypeOptions()
{
    ui->cmb_movetype->setItemHidden(0, false);
    ui->cmb_movetype->setItemHidden(1, false);

    if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
        ui->cmb_movetype->setItemHidden(1, true);
        ui->cmb_movetype->setCurrentIndex(0);
    }
}

void TeachContainerForm::axisMoveEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->grp_mechianicalunit->setEnabled(isEnabled);
}

void TeachContainerForm::coordDisplayEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->wgt_coorddisplay->setEnabled(isEnabled);
}

void TeachContainerForm::stepGradeEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->wgt_stepmode->setEnabled(isEnabled);
}

void TeachContainerForm::mechineunitLockEnabled(bool isEnabled)
{
    qDebug() << __FUNCTION__ << isEnabled;
    ui->grp_operatecontrol->setEnabled(isEnabled);
}

void TeachContainerForm::move2pointEnabled(bool isEnabled)
{
    ui->grp_ctrl->setEnabled(isEnabled);
}

void TeachContainerForm::setCurrentPositionEnabled(bool isEnabled)
{
    ui->pbn_ctrl_getcurrent->setEnabled(isEnabled);
}

int TeachContainerForm::getPtFileCount()
{
    return ui->cmb_fileList->count();
}

void TeachContainerForm::refreshMove2Point()
{
    updateUI();
}

void TeachContainerForm::on_cmb_fileList_activated(int index)
{
    if (!Communication::instance()->isConnected()) return;

    updateMoveTypeOptions();

    CommunicationEngine::instance()->enqueueCmd_setData(this, AbstractCmd::CmdType_Control_Move2Point_GetPtList,
                                                        ui->cmb_fileList->currentText());
}

void TeachContainerForm::on_cmb_ptlist_activated(int index)
{
    // updateRoadPointData();
    updateMoveTypeOptions();
}

void TeachContainerForm::on_pbn_ctrl_getcurrent_clicked()
{
    if (ui->cmb_fileList->currentText().isEmpty()) {
        MessageBox::information(tr("The point file list cannot be empty."));
        return;
    }

    if (ui->cmb_ptlist->currentText().isEmpty()) {
        MessageBox::information(tr("The point index cannot be empty."));
        return;
    }

    if (!Communication::instance()->isConnected()) return;

    if (ui->cmb_fileList->count() == 0 || ui->cmb_ptlist->count() == 0) return;

    RoadPoint curPt = Communication::instance()->GetRealTimeFlange2BasePt();

    if (curPt.m_isSingular && ui->cmb_fileList->currentText().compare("JP.pts") != 0) {
        MessageBox::information(tr("The current point is a singular point, please take other point instead."));
        return;
    }

    if (MessageBox::question(tr("Are you sure you want to write current position to the file?")) != QMessageBox::Yes) {
        return;
    }

    int index = ui->cmb_ptlist->currentIndex();

    InoRPointInfo rp;
    InoJPointInfo jp;

    std::string sFilename = ui->cmb_fileList->currentText().toStdString();
    if (ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
        jp = m_vecJPointInfos[index];
        for (int i = 0; i < ROBOT_DOF; i++) {
            jp.pos.JointData[i] = curPt.m_jointAngle[i];
        }
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_Control_Move2Point_SetCurrent, 1, rp, jp, sFilename);
    } else {
        rp = m_vecRPointInfos[index];
        rp.pos.RPosData[0] = curPt.m_position.m_x;
        rp.pos.RPosData[1] = curPt.m_position.m_y;
        rp.pos.RPosData[2] = curPt.m_position.m_z;
        rp.pos.RPosData[3] = curPt.m_orientation.m_rz;
        rp.pos.RPosData[4] = curPt.m_orientation.m_ry;
        rp.pos.RPosData[5] = curPt.m_orientation.m_rx;

        for (int i = 0; i < ROBOT_ARM_NUM; i++) {
            rp.pos.ArmParm[i] = curPt.m_arm[i];
        }
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_Control_Move2Point_SetCurrent, 0, rp, jp, sFilename);
    }
}

void TeachContainerForm::on_pbn_ctrl_movehere_pressed()
{
    if (!Communication::instance()->IsEnable()) {
        PRINT_MSG(tr("Please enable the robot first."));
        return;
    }

    if (!Communication::instance()->isConnected()) return;

    if (ui->cmb_fileList->currentText().isEmpty()) {
        MessageBox::information(tr("The point file list cannot be empty."));
        return;
    }

    if (ui->cmb_ptlist->currentText().isEmpty()) {
        MessageBox::information(tr("The point index cannot be empty."));
        return;
    }

    updateRoadPointData();

    if (ui->cmb_movetype->currentIndex() == 0 && ui->cmb_fileList->currentText().compare("JP.pts") == 0) {
        CommunicationEngine::instance()->enqueueCmd_robotMoveJointTeach(
            this, m_pt);
    }

    if (ui->cmb_movetype->currentIndex() == 1) {
        CommunicationEngine::instance()->enqueueCmd_robotMoveLine(
            this, m_pt);
    }
}

