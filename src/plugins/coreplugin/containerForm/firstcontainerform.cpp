#include "firstcontainerform.h"
#include <QTimer>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "mainwidget.h"
#include "propertydefine.h"
#include "toolbox.h"

QList<FirstContainerForm*> s_instances;

QList<FirstContainerForm*> FirstContainerForm::FirstContainerFormInstances()
{
    return s_instances;
}

FirstContainerForm::FirstContainerForm(const ContainerFormMsg &msg) :
    AbstractWidget(0, 0, 0, 16777215, 16777215),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::FirstContainerForm)
#else
    ui(AbstractWidget::ui)
#endif
{
    m_showMenu = false;
    m_containerFormMsg = msg;
    setObjectName(m_containerFormMsg.objectName);
#ifdef INOCOBOTTP_MSVC_QT5
    ui->setupUi(this);
#else
    setupUi(this);
#endif

    m_toolBox = new ToolBox(this);
    m_toolBox->setObjectName("toolBox");
    m_toolBox->setMinimumSize(ResolutionUtils::getRatioSize(180, 0));
    m_toolBox->setMaximumSize(ResolutionUtils::getRatioSize(180, 16777215));
    m_toolBox->layout()->setSpacing(0);
    ui->mainLayout->insertWidget(0, m_toolBox);

    if (m_containerFormMsg.index == -1) {
        MainWidget::instance()->addTabWidget(
            this,
            m_containerFormMsg.showText.toUtf8(),
            m_containerFormMsg.showIcon);
    } else {
        MainWidget::instance()
            ->addTabWidget(m_containerFormMsg.index, this,
                           m_containerFormMsg.showText.toUtf8(),
                           m_containerFormMsg.showIcon);
    }

    connect(m_toolBox,
            &ToolBox::currentChanged,
            this,
            &FirstContainerForm::slot_toolBox_itemClicked);
    s_instances.push_back(this);
}

FirstContainerForm::~FirstContainerForm()
{
    for(int i=0;i<s_instances.size();++i){
        if(s_instances[i] == this){
            s_instances.erase(s_instances.begin()+i);
            break;
        }
    }
}

void FirstContainerForm::initialize()
{
}

void FirstContainerForm::addDrawerPage(
    const int &drawerIndex, QWidget *drawerPage)
{
    int size = m_vectorCurrentToolBoxDrawIndex.size();
    int i = 0;
    for (; i < size; ++i) {
        if (m_vectorCurrentToolBoxDrawIndex[i] > drawerIndex)
            break;
    }
    // QStringList currentThirdInSecond = ui->toolBox->property(InfoFlow_ToolBox).toStringList();
    // currentThirdInSecond.insert(i,"");
    // ui->toolBox->setProperty(InfoFlow_ToolBox,currentThirdInSecond);
    m_toolBox->insertItem(i, drawerPage, drawerPage->property("pageName").toString());
    m_vectorCurrentToolBoxDrawIndex.insert(m_vectorCurrentToolBoxDrawIndex.begin() + i, drawerIndex);
    m_toolBox->layout()->setSpacing(TOOLBOX_SPACEING);
    //slot_toolBox_itemClicked(0);
}

void FirstContainerForm::addPluginWidget(
    const int &drawerIndex, const QString &pluginName,
    QRadioButton *pbnPlugin, QWidget *widget, int thirdIndex)
{
    ui->stackedWidget->addWidget(widget);
    int stackFormIndex = ui->stackedWidget->indexOf(widget);
    m_mapPluginNameAndDrawerIndex.insert(pluginName, drawerIndex);
    m_mapPluginNameAndStackFormIndex.insert(pluginName, stackFormIndex);
    m_mapPluginNameAndPluginPbn.insert(pluginName, pbnPlugin);
    if (thirdIndex == 0 && drawerIndex == 0) {
        m_firstPluginName = pluginName;
    }
    if (!m_firstPluginName.isEmpty()) {
        setCurrentStackedWidget(m_firstPluginName);
    }
    // if(thirdIndex == 0){
    //     QStringList currentThirdInSecond = ui->toolBox->property(InfoFlow_ToolBox).toStringList();
    //     currentThirdInSecond[drawerIndex] = pluginName;
    //     ui->toolBox->setProperty(InfoFlow_ToolBox,currentThirdInSecond);
    // }
}

void FirstContainerForm::addPluginWidget(
    const int &drawerIndex, const QString &pluginName, QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int stackFormIndex = ui->stackedWidget->indexOf(widget);
    m_mapPluginNameAndDrawerIndex.insert(pluginName, drawerIndex);
    m_mapPluginNameAndStackFormIndex.insert(pluginName, stackFormIndex);
    // if(drawerIndex == 0){
    //     QStringList currentThirdInSecond = ui->toolBox->property(InfoFlow_ToolBox).toStringList();
    //     currentThirdInSecond[drawerIndex] = pluginName;
    //     ui->toolBox->setProperty(InfoFlow_ToolBox,currentThirdInSecond);
    // }
}

void FirstContainerForm::setToolBoxItemEnabled(
    const int &index, const bool &enabled)
{
    m_toolBox->setItemEnabled(index, enabled);
}

void FirstContainerForm::setToolBoxItemText(
    const int &index, const QString &text)
{
    m_toolBox->setItemText(index, text);
}

void FirstContainerForm::setToolBoxButtonVisible(
    const int index, QRadioButton *pbnPlugin, bool visible)
{
    m_toolBox->setItemButtonVisible(index, pbnPlugin, visible);
}

void FirstContainerForm::setDefaultDrawerIndex(const int &drawerIndex)
{
    m_defaultDrawerIndex = drawerIndex;
}

void FirstContainerForm::setCurrentStackedWidget(const QString &pluginName)
{
    int drawerIndex = m_mapPluginNameAndDrawerIndex.value(pluginName);
    m_mapDrawerIndexAndStackFormIndex[drawerIndex]
        = m_mapPluginNameAndStackFormIndex.value(pluginName);
    if (m_mapPluginNameAndPluginPbn.contains(pluginName))
        m_mapPluginNameAndPluginPbn.value(pluginName)->setChecked(true);
    setCurrentToolBoxWidget(drawerIndex);
}

void FirstContainerForm::retranslateUi()
{
    ui->retranslateUi(this);
}

void FirstContainerForm::slot_toolBox_itemClicked(int index)
{
    setCurrentToolBoxWidget(index);
}

void FirstContainerForm::setCurrentToolBoxWidget(const int &secondIndex)
{
    if (m_toolBox->count() == 0)
        return;

    m_toolBox->setCurrentIndex(secondIndex);
    ui->stackedWidget->setCurrentIndex(
        m_mapDrawerIndexAndStackFormIndex.value(secondIndex));
}

QString FirstContainerForm::getCurrentIndexText()
{
    return m_toolBox->itemText(m_toolBox->currentIndex());
}

void Ui_FirstContainerForm::setupUi(QWidget *firstContainerForm)
{
    firstContainerForm->setStyleSheet(
        "QStackedWidget#stackedWidget { background: rgb(255, 255, 255);"
        "                               border-radius:4px;}");
    firstContainerForm->resize(FIRST_CONTAINER_SIZE);
    firstContainerForm->setMaximumSize(QSize(16777215, 16777215));
    firstContainerForm->setFocusPolicy(Qt::ClickFocus);

    mainLayout = new QHBoxLayout(firstContainerForm);
    firstContainerForm->setLayout(mainLayout);
    mainLayout->setObjectName("mainLayout" + firstContainerForm->objectName());
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(FIRST_MAINLAYOUT_SPACEING);

    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setContentsMargins(0, 8, 8, 8);
    contentLayout->setSpacing(0);

    stackedWidget = new QStackedWidget();
    stackedWidget->setObjectName("stackedWidget");
    contentLayout->addWidget(stackedWidget);
    mainLayout->addLayout(contentLayout);

    retranslateUi(firstContainerForm);
}

void Ui_FirstContainerForm::retranslateUi(QWidget *FirstContainerForm)
{
    Q_UNUSED(FirstContainerForm);
}
