#include "robotinitform.h"
#include "ui_robotinitform.h"
#include <QDebug>
#include "communicationengine.h"
#include "databaselocal.h"
#include "messagebox.h"
#include "dialogcontainerform.h"
#include "roboteventinfo.h"
#include "tcpserverengine.h"
#include "tcpclientengine.h"
#include "instance.h"
#include "configinfo.h"
#include "communication.h"
#include "toolparam.h"
#include "propertydefine.h"

static RobotInitForm *s_instance = 0;

RobotInitForm *RobotInitForm::instance()
{
    return s_instance;
}

RobotInitForm::RobotInitForm(QWidget *parent) :
    AbstractWidget(parent, 880, 376, 880, 376),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::RobotInitForm)
#else
    ui(AbstractWidget::ui)
#endif
{
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif
    setAttribute(Qt::WA_StyledBackground);

    s_instance = this;
    Instance::setRobotInitForm(this);

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_tool_GetItems_result,
            this,
            &RobotInitForm::slot_tool_GetItems_result);

    initUI();
}

RobotInitForm::~RobotInitForm()
{
    delete ui;
}

void RobotInitForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Robot initialized"));
}

void RobotInitForm::on_pbn_save_clicked()
{
    save();
}

void RobotInitForm::on_pbn_startUp_clicked()
{
    startUp();
}

void RobotInitForm::on_cmb_toolName_currentIndexChanged(int index)
{
    if (index >= 0) {
        ToolParam toolParam;
        ui->cmb_toolName->setCurrentText(toolParam.m_toolName);
    }
}

void RobotInitForm::showEvent(QShowEvent *)
{
    CommunicationEngine::instance()->enqueueCmd(
        this, AbstractCmd::CmdType_Tool_GetItems);

    ToolParam toolParam;
    QMetaObject::invokeMethod(
        Instance::common(), "getToolParam", Qt::DirectConnection,
        Q_RETURN_ARG(ToolParam, toolParam));
    ui->cmb_toolName->setCurrentText(toolParam.m_toolName);
}

void RobotInitForm::initUI()
{
    ToolParam toolParam;
    DatabaseLocal::getToolParam(toolParam);
    if (toolParam.isExist())
        ui->cmb_toolName->setCurrentText(toolParam.m_toolName);
    else
        ui->cmb_toolName->setCurrentText(FLANGE_CENTER_NAME);

    on_cmb_toolName_currentIndexChanged(ui->cmb_toolName->currentIndex());
}

void RobotInitForm::save()
{
    QMetaObject::invokeMethod(
        Instance::mainWidget(), "showMainWidget",
        Qt::DirectConnection);
}

void RobotInitForm::startUp()
{
    ui->pbn_startUp->setEnabled(false);
}

void RobotInitForm::on_pbn_shutdown_clicked()
{
    QMetaObject::invokeMethod(
        Instance::mainWidget(), "power", Qt::DirectConnection);
}

void RobotInitForm::on_pbn_close_clicked()
{
    Instance::common()->setProperty("isShutdownAfterPowerOff", false);
    QMetaObject::invokeMethod(
        Instance::mainWidget(), "power", Qt::DirectConnection,
        Q_ARG(bool, true));
}

void RobotInitForm::on_pbn_logout_clicked()
{
    QMetaObject::invokeMethod(
        Instance::mainWidget(), "on_pbn_logout_clicked",
        Qt::DirectConnection);
}

void RobotInitForm::slot_tool_GetItems_result(const QVector<QString> &items)
{
    ui->cmb_toolName->clear();
    for (auto &toolName : items) {
        ui->cmb_toolName->addItem(toolName);
    }
    ui->cmb_toolName->setCurrentIndex(0);
}
