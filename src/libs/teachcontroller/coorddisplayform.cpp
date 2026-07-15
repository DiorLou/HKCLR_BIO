#include "coorddisplayform.h"
#include "ui_coorddisplayform.h"
#include <QDebug>
#include "communication.h"
#include "communicationengine.h"
#include "cobotlog.h"

CoordDisplayForm::CoordDisplayForm(QWidget *parent) :
    AbstractWidget(0, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::CoordDisplayForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    ui->cmb_coordType_display->setCurrentIndex(
        static_cast<int>(Communication::instance()->GetCurPosFormat()));

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_posformat_changed,
            this,
            &CoordDisplayForm::slot_posformat_changed);

    ui->lbl_joint7Angle->setVisible(false);
    ui->label_37->setVisible(false);

#if PluginLib_TeachController_DOF7_Enabled == 1
    ui->lbl_joint7Angle->setVisible(true);
    ui->label_37->setVisible(true);
#endif

}

CoordDisplayForm::~CoordDisplayForm()
{
    delete ui;
}

void CoordDisplayForm::SetPageIndex(int index)
{
    ui->stack_display->setCurrentIndex(index);
}

void CoordDisplayForm::SetPosFormatIdx(int index)
{
    ui->cmb_coordType_display->setCurrentIndex(index);
}

void CoordDisplayForm::showEvent(QShowEvent *event)
{
    updateUI();
    slot_updateRealtimeRoadPoint();
    connect(Communication::instance(),
            &DataCollectionInterface::signal_sendRealTimeRoadPoint,
            this,
            &CoordDisplayForm::slot_updateRealtimeRoadPoint);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &CoordDisplayForm::slot_controllerConnectionStatusChanged);
}

void CoordDisplayForm::hideEvent(QHideEvent *event)
{
    disconnect(Communication::instance(),
            &DataCollectionInterface::signal_sendRealTimeRoadPoint,
            this,
            &CoordDisplayForm::slot_updateRealtimeRoadPoint);

    disconnect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &CoordDisplayForm::slot_controllerConnectionStatusChanged);
}

void CoordDisplayForm::slot_updateRealtimeRoadPoint()
{
    int status = Communication::instance()->getToolWobjMatchStatus();
    if (status == 1) {
        // 当前工具与工件类型不匹配，无法显示当前位置
        setInvalidPosition();
        return;
    } else if (status == 2) {
        // 工件中夹持属性或固定属性设置有误，无法显示当前位置
        setInvalidPosition();
        return;
    }

    RoadPoint roadPoint;
    roadPoint
        = Communication::instance()
              ->GetRealTimePt();

    ui->lbl_x->setText(QString::number(roadPoint.m_position.m_x, 'f', 3));
    ui->lbl_y->setText(QString::number(roadPoint.m_position.m_y, 'f', 3));
    ui->lbl_z->setText(QString::number(roadPoint.m_position.m_z, 'f', 3));

    ui->lbl_rx->setText(
        QString::number(roadPoint.m_orientation.m_rx, 'f', 3));
    ui->lbl_ry->setText(
        QString::number(roadPoint.m_orientation.m_ry, 'f', 3));
    ui->lbl_rz->setText(
        QString::number(roadPoint.m_orientation.m_rz, 'f', 3));

    ui->lbl_joint1Angle->setText(
        QString::number(roadPoint.m_jointAngle[0], 'f', 3));
    ui->lbl_joint2Angle->setText(
        QString::number(roadPoint.m_jointAngle[1], 'f', 3));
    ui->lbl_joint3Angle->setText(
        QString::number(roadPoint.m_jointAngle[2], 'f', 3));
    ui->lbl_joint4Angle->setText(
        QString::number(roadPoint.m_jointAngle[3], 'f', 3));
    ui->lbl_joint5Angle->setText(
        QString::number(roadPoint.m_jointAngle[4], 'f', 3));
    ui->lbl_joint6Angle->setText(
        QString::number(roadPoint.m_jointAngle[5], 'f', 3));

#if CommonLib_Metatype_DOF7_Enabled == 1
    ui->lbl_joint7Angle->setText(
        QString::number(roadPoint.m_jointAngle[6], 'f', 3));
#endif
}

void CoordDisplayForm::slot_posformat_changed(RobotCoordDisplayFormat foramt)
{
    qDebug() << "[controller]pos format = " << static_cast<int>(foramt);
    if (static_cast<int>(foramt) != ui->cmb_coordType_display->currentIndex()) {
        ui->cmb_coordType_display->setCurrentIndex(static_cast<int>(foramt));
    }
    slot_updateRealtimeRoadPoint();
}

void CoordDisplayForm::setInvalidPosition()
{
    ui->lbl_x->setText("---");
    ui->lbl_y->setText("---");
    ui->lbl_z->setText("---");
    ui->lbl_rx->setText("---");
    ui->lbl_ry->setText("---");
    ui->lbl_rz->setText("---");
}

void CoordDisplayForm::updateUI()
{
    if (!isVisible()) {
        return;
    }
    ui->cmb_coordType_display->setCurrentIndex(
        static_cast<int>(Communication::instance()->GetCurPosFormat()));
}

void CoordDisplayForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void CoordDisplayForm::on_cmb_coordType_display_activated(int index)
{
    if (!Communication::instance()->isConnected()) {
        return;
    }
    if (!isVisible()) {
        return;
    }
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetPosFormat, static_cast<RobotCoordDisplayFormat>(index));
}

void CoordDisplayForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    if (ControllerConnectionState_Connected == status) {
        updateUI();
    }
}

