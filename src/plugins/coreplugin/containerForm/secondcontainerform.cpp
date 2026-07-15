#include "secondcontainerform.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include "propertydefine.h"
#include "instance.h"

SecondContainerForm::SecondContainerForm(const ContainerFormMsg &msg,
                                         FirstContainerForm *parent) :
    AbstractWidget(parent, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::SecondContainerForm),
#else
    ui(AbstractWidget::ui),
#endif
    m_containerFormMsg(msg),
    m_parent_firstContainerForm(parent)
{
    m_showMenu = true;
    setObjectName(m_containerFormMsg.objectName);
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
    if(!m_delayInit)
        processAfterInitUi(this);
#else
    setupUi(this);
#endif
    if (m_toolBox) {
        m_toolBox->hide();
    }
    // ui->page->setProperty("pageName", m_containerFormMsg.showText);
    // parent->addDrawerPage(m_containerFormMsg.index, ui->page);
    setProperty("pageName", m_containerFormMsg.showText);
    if (!m_containerFormMsg.bNeedShow) {
        return;
    }
    parent->addDrawerPage(m_containerFormMsg.index, this);
    connect(Instance::instance(),
            &Instance::enabledChanged,
            this,
            [=](bool) {
                parent->setCurrentToolBoxWidget(m_containerFormMsg.index);
            });
    this->setProperty(InfoFlow_Property, msg.showText);
}

SecondContainerForm::~SecondContainerForm()
{
    delete ui;
}

void SecondContainerForm::initialize()
{
}

void SecondContainerForm::addPluginPbn(
    const int &layoutIndex, QRadioButton *pbnPlugin)
{
    int size = m_listRadioBtnCurrentIndex.size();
    int i = 0;
    if (size == 0) {
        m_listRadioBtnCurrentIndex.push_back(999);
        ui->vLayout->addItem(new QSpacerItem(17, 119, QSizePolicy::Minimum, QSizePolicy::Expanding));
        size = 1;
    }
    for (; i < size; ++i) {
        if (m_listRadioBtnCurrentIndex[i] > layoutIndex)
            break;
    }

    ui->vLayout->insertWidget(i, pbnPlugin);
    m_listWidgetAddress.insert(i, pbnPlugin);
    m_listRadioBtnCurrentIndex.insert(i, layoutIndex);
    pbnPlugin->setProperty(InfoFlow_RbnIsWidgetIndex, "true");
    pbnPlugin->setProperty("itemVisible", true);
    if (m_listWidgetAddress.count() <= 0) {
        return;
    }
    QRadioButton *btn = m_listWidgetAddress.at(0);
    if (!btn) {
        return;
    }
    btn->setChecked(true);
    btn->click();
    // emit btn->clicked();
    m_parent_firstContainerForm->setCurrentToolBoxWidget(0);
}

void SecondContainerForm::retranslateUi()
{
    ui->retranslateUi(this);
}

QString SecondContainerForm::getCurrentThirdIndexText()
{
    return QString();
}

void SecondContainerForm::operationWhenShowOrHide(bool isSHow)
{
    if (isSHow)
        for (int i = 0; i < m_listWidgetAddress.size(); ++i) {
            if (m_listWidgetAddress[i]->isChecked()) {
                if (!m_listWidgetAddress[i]->isEnabled()) {
                    for (int j = 0; j < m_listWidgetAddress.size(); ++j) {
                        if (m_listWidgetAddress[j]->isEnabled()) {
                            emit m_listWidgetAddress[j]->clicked();
                            break;
                        }
                    }
                }
                break;
            }
        }
}

void Ui_SecondContainerForm::setupUi(QWidget *widget)
{
    vLayout = new QVBoxLayout(widget);
    vLayout->setObjectName("vLayout");
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    widget->setLayout(vLayout);

    retranslateUi(widget);
}

void Ui_SecondContainerForm::retranslateUi(QWidget *widget)
{
    Q_UNUSED(widget);
}
