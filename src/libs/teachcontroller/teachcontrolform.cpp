#include "teachcontrolform.h"
#include "ui_teachcontrolform.h"
#include "communication.h"
#include "communicationengine.h"
#include "coordselectform.h"
#include "stepmodeform.h"
#include "cobotlog.h"
#include "coorddisplayform.h"
#include "propertydefine.h"
#include "resolutionutils.h"

static const int JOINT_PAGE_IDX = 0;
static const int AXIS_PAGE_IDX = 1;

TeachControlForm::TeachControlForm(QWidget *parent) :
    AbstractWidget(0, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::TeachControlForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    QList<QPushButton *> posBtns
        = ui->stack_move_ctrl->widget(AXIS_PAGE_IDX)->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
    QList<QPushButton *> jointBtns
        = ui->stack_move_ctrl->widget(JOINT_PAGE_IDX)->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);

    for (QPushButton *posBtn : posBtns) {
        posBtn->setProperty("theme", "yellow");
        posBtn->setStyleSheet("");
        posBtn->setIconSize(ResolutionUtils::getRatioSize(posBtn->iconSize()));
    }

    for (QPushButton *jointBtn : jointBtns) {
        jointBtn->setProperty("theme", "yellow");
        jointBtn->setStyleSheet("");
        jointBtn->setMaximumSize(ResolutionUtils::getRatioSize(QSize(60,48)));
        jointBtn->setMinimumSize(ResolutionUtils::getRatioSize(QSize(60,48)));
        jointBtn->setIconSize(ResolutionUtils::getRatioSize(jointBtn->iconSize()));

    }
    int size = QString("pbn_joint").size();
    for (QPushButton *jointButton : jointBtns) {
        connect(jointButton, &QPushButton::pressed,
                this, &TeachControlForm::slot_pbn_joint_pressed);
        #if PluginLib_TeachController_DOF7_Enabled == 1
        connect(jointButton, &QPushButton::released,
                this, &TeachControlForm::on_pbn_joint_released);
        #endif
        connect(jointButton, &QPushButton::released,
                this, &TeachControlForm::slot_teachMoveStop);
        QString number = jointButton->objectName().mid(size, 1);
        bool ok = false;
        number.toInt(&ok);
        if (ok) {
            if (jointButton->objectName().contains("Left", Qt::CaseInsensitive)) {
                jointButton->setProperty(InfoFlow_HighLevelOperationLog, "J" + number + "-");
            } else {
                jointButton->setProperty(InfoFlow_HighLevelOperationLog, "J" + number + "+");
            }
        }
    }

    ui->pbn_ryLeft->setProperty(InfoFlow_HighLevelOperationLog, "RY-");
    ui->pbn_rxLeft->setProperty(InfoFlow_HighLevelOperationLog, "RX-");
    ui->pbn_rzLeft_2->setProperty(InfoFlow_HighLevelOperationLog, "RZ-");
    ui->pbn_xLeft->setProperty(InfoFlow_HighLevelOperationLog, "X-");
    ui->pbn_yLeft->setProperty(InfoFlow_HighLevelOperationLog, "Y-");
    ui->pbn_zLeft->setProperty(InfoFlow_HighLevelOperationLog, "Z-");

    ui->pbn_ryRight->setProperty(InfoFlow_HighLevelOperationLog, "RY+");
    ui->pbn_rxRight_2->setProperty(InfoFlow_HighLevelOperationLog, "RX+");
    ui->pbn_rzRight->setProperty(InfoFlow_HighLevelOperationLog, "RZ+");
    ui->pbn_xRight->setProperty(InfoFlow_HighLevelOperationLog, "X+");
    ui->pbn_yRight->setProperty(InfoFlow_HighLevelOperationLog, "Y+");
    ui->pbn_zRight->setProperty(InfoFlow_HighLevelOperationLog, "Z+");

    for (QPushButton *posBtn : posBtns) {
        if (posBtn->objectName().contains("pbn_r")) {
            connect(posBtn, &QPushButton::pressed,
                    this, &TeachControlForm::slot_pbn_ori_pressed);
            connect(posBtn, &QPushButton::released,
                    this, &TeachControlForm::slot_teachMoveStop);
        } else {
            connect(posBtn, &QPushButton::pressed,
                    this, &TeachControlForm::slot_pbn_position_pressed);
            connect(posBtn, &QPushButton::released,
                    this, &TeachControlForm::slot_teachMoveStop);
        }
    }

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_axisMoveInterface_result,
            this, &TeachControlForm::slot_axisMoveInterface_result);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_robotMoveTeachStartInterface_result,
            this,
            &TeachControlForm::slot_teachMoveControlInterface_result);

#if PluginLib_TeachController_DOF7_VirtualData_Enabled == 1
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, [=]() {
        if(!m_curButton)return;
        int index = m_curButton->objectName().mid(9, 1).toInt();
        if (m_curButton->objectName().contains("Left")) {
            QMetaObject::invokeMethod(
                Instance::simulationForm(),
                "setData",
                Qt::AutoConnection,
                Q_ARG(int, index),
                Q_ARG(bool, false)
                );
        } else if (m_curButton->objectName().contains("Right")) {
            QMetaObject::invokeMethod(
                Instance::simulationForm(),
                "setData",
                Qt::AutoConnection,
                Q_ARG(int, index),
                Q_ARG(bool, true)
                );
        }
    });
#endif

#if PluginLib_TeachController_DOF7_Enabled != 1
    ui->pbn_joint7Left->setVisible(false);
    ui->pbn_joint7Right->setVisible(false);
#endif
}

TeachControlForm::~TeachControlForm()
{
    delete ui;
}

void TeachControlForm::showEvent(QShowEvent *)
{
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &TeachControlForm::slot_controllerConnectionStatusChanged);

    UpdateUI();
    // m_coordDisplayForm->slot_updateRealtimeRoadPoint();
}

void TeachControlForm::hideEvent(QHideEvent *)
{
    disconnect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, &TeachControlForm::slot_controllerConnectionStatusChanged);
}

void TeachControlForm::SetReleativeWidgets(StepModeForm *stepModeForm,
                                           CoordSelectForm *coordSelectForm,
                                           CoordDisplayForm *coordDisplayForm)
{
    m_stepModeForm = stepModeForm;
    m_coordSelectForm = coordSelectForm;
    m_coordDisplayForm = coordDisplayForm;

    connect(m_coordSelectForm, SIGNAL(signal_mechine_unit_changed()),
            this, SLOT(slot_mechine_unit_changed()));
}

void TeachControlForm::UpdateUI()
{
    if (Communication::instance()->GetCurCoodType() == RobotCoordType_Joint) {
        m_coordDisplayForm->SetPageIndex(JOINT_PAGE_IDX);

        ui->stack_move_ctrl->setCurrentIndex(JOINT_PAGE_IDX);

        setGroupBtnsEnable(ui->stack_move_ctrl->widget(AXIS_PAGE_IDX), false);
        setGroupBtnsEnable(ui->stack_move_ctrl->widget(JOINT_PAGE_IDX), true);
    } else {
        m_coordDisplayForm->SetPageIndex(AXIS_PAGE_IDX);

        ui->stack_move_ctrl->setCurrentIndex(AXIS_PAGE_IDX);

        setGroupBtnsEnable(ui->stack_move_ctrl->widget(JOINT_PAGE_IDX), false);
        setGroupBtnsEnable(ui->stack_move_ctrl->widget(AXIS_PAGE_IDX), true);
    }
}

void TeachControlForm::setGroupBtnsEnable(QWidget *wgt, bool bEnable)
{
    QList<QPushButton *> btns = wgt->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton *btn : btns) {
        btn->setEnabled(bEnable);
    }
}

void TeachControlForm::on_pbn_joint_released()
{
#if PluginLib_TeachController_DOF7_VirtualData_Enabled == 1
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
#endif
}
void TeachControlForm::slot_pbn_joint_pressed()
{
    QPushButton *pbn = qobject_cast<QPushButton *>(sender());
#if PluginLib_TeachController_DOF7_VirtualData_Enabled == 1
    if(!m_timer->isActive())
    {
        m_timer->start(16);
    }
    if(pbn)m_curButton = pbn;
    return;
#endif
    int index = pbn->objectName().mid(9, 1).toInt();

    if (!m_stepModeForm->IsChecked()) {
        if (pbn->objectName().contains("Left")) {
            CommunicationEngine::instance()->enqueueCmd_axisMove(
                this, index, false, true);
        } else if (pbn->objectName().contains("Right")) {
            CommunicationEngine::instance()->enqueueCmd_axisMove(
                this, index, true, true);
        }
    } else {
        if (pbn->objectName().contains("Left")) {
            teachMoveStart(static_cast<TeachMode>(
                               TeachMode_Joint1 + index - 1),
                           false);
        } else if (pbn->objectName().contains("Right")) {
            teachMoveStart(static_cast<TeachMode>(
                               TeachMode_Joint1 + index - 1),
                           true);
        }
    }
}

void TeachControlForm::slot_pbn_position_pressed()
{
    QPushButton *pbn = qobject_cast<QPushButton *>(sender());

    if (pbn->objectName().contains("pbn_zLeft")) {
        teachMoveStart(TeachMode_MovZ, false);
    } else if (pbn->objectName().contains("pbn_zRight")) {
        teachMoveStart(TeachMode_MovZ, true);
    } else if (pbn->objectName().contains("pbn_xLeft")) {
        teachMoveStart(TeachMode_MovX, false);
    } else if (pbn->objectName().contains("pbn_xRight")) {
        teachMoveStart(TeachMode_MovX, true);
    } else if (pbn->objectName().contains("pbn_yLeft")) {
        teachMoveStart(TeachMode_MovY, false);
    } else if (pbn->objectName().contains("pbn_yRight")) {
        teachMoveStart(TeachMode_MovY, true);
    }
}

void TeachControlForm::slot_pbn_ori_pressed()
{
    QPushButton *pbn = qobject_cast<QPushButton *>(sender());

    if (pbn->objectName().contains("pbn_rzLeft")) {
        teachMoveStart(TeachMode_RotZ, false);
    } else if (pbn->objectName().contains("pbn_rzRight")) {
        teachMoveStart(TeachMode_RotZ, true);
    } else if (pbn->objectName().contains("pbn_rxLeft")) {
        teachMoveStart(TeachMode_RotX, false);
    } else if (pbn->objectName().contains("pbn_rxRight")) {
        teachMoveStart(TeachMode_RotX, true);
    } else if (pbn->objectName().contains("pbn_ryLeft")) {
        teachMoveStart(TeachMode_RotY, false);
    } else if (pbn->objectName().contains("pbn_ryRight")) {
        teachMoveStart(TeachMode_RotY, true);
    }
}

void TeachControlForm::teachMoveStart(
    TeachMode teachMode, bool direction)
{
    CoordParam coordParam = Communication::instance()->getCurCoordParams();

    CommunicationEngine::instance()->enqueueCmd_robotMoveTeachStart(
        this, teachMode, direction, coordParam);
}

void TeachControlForm::slot_teachMoveStop()
{
    if (!sender()) {
        return;
    }
    QPushButton *pbn = qobject_cast<QPushButton *>(sender());

    // 关节运动
    if (pbn->objectName().contains("joint")) {
        int index = pbn->objectName().mid(9, 1).toInt();
        if (pbn->objectName().contains("Left")) {
            teachMoveStop((TeachMode)(static_cast<int>(TeachMode_Invalid) + index),
                          false);
        } else if (pbn->objectName().contains("Right")) {
            teachMoveStop((TeachMode)(static_cast<int>(TeachMode_Invalid) + index),
                          true);
        }
    }
    // 位置运动
    else if (pbn->objectName().contains("pbn_zLeft")) {
        teachMoveStop(TeachMode_MovZ, false);
    } else if (pbn->objectName().contains("pbn_zRight")) {
        teachMoveStop(TeachMode_MovZ, true);
    } else if (pbn->objectName().contains("pbn_xLeft")) {
        teachMoveStop(TeachMode_MovX, false);
    } else if (pbn->objectName().contains("pbn_xRight")) {
        teachMoveStop(TeachMode_MovX, true);
    } else if (pbn->objectName().contains("pbn_yLeft")) {
        teachMoveStop(TeachMode_MovY, false);
    } else if (pbn->objectName().contains("pbn_yRight")) {
        teachMoveStop(TeachMode_MovY, true);
    }
    // 姿态运动
    else if (pbn->objectName().contains("pbn_rzLeft")) {
        teachMoveStop(TeachMode_RotZ, false);
    } else if (pbn->objectName().contains("pbn_rzRight")) {
        teachMoveStop(TeachMode_RotZ, true);
    } else if (pbn->objectName().contains("pbn_rxLeft")) {
        teachMoveStop(TeachMode_RotX, false);
    } else if (pbn->objectName().contains("pbn_rxRight")) {
        teachMoveStop(TeachMode_RotX, true);
    } else if (pbn->objectName().contains("pbn_ryLeft")) {
        teachMoveStop(TeachMode_RotY, false);
    } else if (pbn->objectName().contains("pbn_ryRight")) {
        teachMoveStop(TeachMode_RotY, true);
    }
}

void TeachControlForm::teachMoveStop(TeachMode teachMode,
                                     bool direction)
{
    CoordParam coordParam = Communication::instance()->getCurCoordParams();

    CommunicationEngine::instance()->enqueueCmd_robotMoveTeachStop(
        this, teachMode, direction, coordParam);
}

void TeachControlForm::slot_axisMoveInterface_result(QObject *object,
                                                     bool isSuccess)
{
    if (this == object && !isSuccess) {
        PRINT_MSG(tr("Axis motion failed."));
    }
}

void TeachControlForm::slot_teachMoveControlInterface_result(bool isSuccess)
{
    if (!isSuccess) {
        // slot_teachMoveStop();//未启动成功，不需要停止
        PRINT_MSG(tr("Motion failed."));
    }
}

void TeachControlForm::slot_mechine_unit_changed()
{
    UpdateUI();
    m_coordDisplayForm->slot_updateRealtimeRoadPoint();
}

void TeachControlForm::on_cmb_coordType_display_currentIndexChanged(int index)
{
    qDebug() << "[GUI]pos format = " << index;
    CommunicationEngine::instance()->enqueueCmd_setData(
        this, AbstractCmd::CmdType::CmdType_Control_SetPosFormat,
        static_cast<RobotCoordDisplayFormat>(index));
}

void TeachControlForm::slot_controllerConnectionStatusChanged(ControllerConnectionState status)
{
    if (ControllerConnectionState_Connected == status) {
        UpdateUI();
    }
}

void TeachControlForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void TeachControlForm::setJointBtnSize(const QSize & size)
{
    QSize after = ResolutionUtils::getRatioSize(size);
    QSize icon;
    icon.setHeight(after.height() * 0.6);
    icon.setWidth(after.width() * 0.6);
    QList<QPushButton *> jointBtns
        = ui->stack_move_ctrl->widget(JOINT_PAGE_IDX)->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton *jointButton : jointBtns) {
        jointButton->setMaximumSize(after);
        jointButton->setMinimumSize(after);
        jointButton->setFixedSize(after);
        jointButton->update();
    }
    for (QPushButton *jointButton : jointBtns) {
        jointButton->setIconSize(icon);
    }
}
