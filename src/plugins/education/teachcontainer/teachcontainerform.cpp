#include "teachcontainerform.h"

#include "instance.h"
#include "mainwidget.h"
#include "robotcontrolform.h"

namespace {
TeachContainerForm *s_instance = nullptr;
constexpr int MainWidgetRobotControlTabIndex = 0;
}

TeachContainerForm *TeachContainerForm::instance()
{
    return s_instance;
}

TeachContainerForm::TeachContainerForm(QWidget *parent)
    : QObject(parent),
      m_robotControlForm(new RobotControlForm(parent))
{
    s_instance = this;
    Instance::setEducationContainerForm(this);
}

void TeachContainerForm::initialize()
{
    m_robotControlTabIndex = MainWidget::instance()->addTabWidget(
        MainWidgetRobotControlTabIndex,
        m_robotControlForm,
        tr("Robot Control"),
        QStringLiteral(":/mainwidget/image/mainwidget/robotbodypoweron.svg"));
}

void TeachContainerForm::delayInitialized()
{
}

void TeachContainerForm::getFunctionEnabledList(QList<QVariant> &retList)
{
    retList.clear();
}

void TeachContainerForm::setFunctionEnabledList(const QVariant &params)
{
    Q_UNUSED(params)
}

int TeachContainerForm::getPtFileCount()
{
    return 0;
}
