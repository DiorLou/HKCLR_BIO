#include "simulationform.h"
#include "propertydefine.h"
#include "roadpoint.h"
#include "communicationengine.h"

static SimulationForm *s_instance = 0;

SimulationForm *SimulationForm::instance()
{
    return s_instance;
}

SimulationForm::SimulationForm(QWidget *parent) :
    AbstractWidget(parent, 0, 0),
#ifdef INOCOBOTTP_MSVC_QT5
    ui(new Ui::SimulationForm)
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
    Instance::setSimulationForm(this);

    m_simContainerForm = new SimContainerForm(SimContainerForm::SimType_Base, this);
#if PluginLib_SimulationForm_DOF7_VirtualData_Enabled == 1
    connect(this, &SimulationForm::changeData,m_simContainerForm,&SimContainerForm::setData);

    connect(this, &SimulationForm::changeData,m_simContainerForm,&SimContainerForm::slot_updateRealTimeRoadPoint);
#endif
    ui->mainLayout->addWidget(m_simContainerForm);
}

SimulationForm::~SimulationForm()
{
    delete ui;
}

void SimulationForm::initialize()
{
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this,
            &SimulationForm::clearTrack);
}

SimContainerForm *SimulationForm::getSimContainerForm()
{
    return m_simContainerForm;
}

void SimulationForm::setSimulationFormSize(const QSize &size)
{
    this->setFixedSize(size);
    m_simContainerForm->setSimulationFormSize(size);
}

void SimulationForm::enableDrawTrack(bool bEnable)
{
    m_simContainerForm->enableDrawTrack(bEnable);
}

void SimulationForm::enableDrawTargetRoadPoint(bool bEnable)
{
    m_simContainerForm->enableDrawTargetRoadPoint(bEnable);
}

void SimulationForm::enableDrawRealTimeRoadPoint(bool bEnable)
{
    m_simContainerForm->enableDrawRealTimeRoadPoint(bEnable);
}

void SimulationForm::enableDrawGroundModel(bool bEnable)
{
    m_simContainerForm->enableDrawGroundModel(bEnable);
}

void SimulationForm::enableInstallationMode(bool bEnable)
{
    m_simContainerForm->enableInstallationMode(bEnable);
}

void SimulationForm::enableDrawInstallationReferenceLocationModel(bool bEnable)
{
    m_simContainerForm->enableDrawInstallationReferenceLocationModel(bEnable);
}

void SimulationForm::enableDrawInstallationRealLocationModel(bool bEnable)
{
    m_simContainerForm->enableDrawInstallationRealLocationModel(bEnable);
}

void SimulationForm::enableDrawInstallationGroundModel(bool bEnable)
{
    m_simContainerForm->enableDrawInstallationGroundModel(bEnable);
}

void SimulationForm::setTemporaryInstallParams(const double &alpha, const double &beta)
{
    m_simContainerForm->setTemporaryInstallParams(alpha,beta);
}

void SimulationForm::setTargetRoadPoint(RoadPoint position)
{
    m_simContainerForm->setTargetRoadPoint(position);
}

RoadPoint SimulationForm::getTargetRoadPoint()
{
    return m_simContainerForm->getTargetRoadPoint();
}

void SimulationForm::setRealTimeRoadPoint(RoadPoint position)
{
    m_simContainerForm->setRealTimeRoadPoint(position);
}

RoadPoint SimulationForm::getRealTimeRoadPoint()
{
    return m_simContainerForm->getRealTimeRoadPoint();
}

void SimulationForm::setCurrentIndex(SimContainerForm::SimStackIndex index)
{
    m_simContainerForm->setCurrentIndex(index);
}

void SimulationForm::setTeachPageEnable(bool bEnable)
{
    m_simContainerForm->setTeachPageEnable(bEnable);
}

int SimulationForm::getCurrentIndex()
{
    return m_simContainerForm->getCurrentIndex();
}

void SimulationForm::addDePallet(const QString &uuid, const CubeSize &size, const QString &wobj)
{
    if(m_simContainerForm){
        m_simContainerForm->addDePallet(uuid, size, wobj);
    }
}

void SimulationForm::removeDePallet(const QString &uuid)
{
    if(m_simContainerForm){
        m_simContainerForm->removeDePallet(uuid);
    }
}

void SimulationForm::removeAllDePallet()
{
    if(m_simContainerForm){
        m_simContainerForm->removeAllDePallet();
    }
}

void SimulationForm::addPallet(const QString &uuid, const CubeSize &size, const QString &wobj)
{
    if(m_simContainerForm){
        m_simContainerForm->addPallet(uuid, size, wobj);
    }
}

void SimulationForm::removePallet(const QString &uuid)
{
    if(m_simContainerForm){
        m_simContainerForm->removePallet(uuid);
    }
}

void SimulationForm::removeAllPallet()
{
    if(m_simContainerForm){
        m_simContainerForm->removeAllPallet();
    }
}

void SimulationForm::addDepalletizingBox(const QString &uuid, const int &boxNum,const QString &wobj,
                                         const Pos &pos, const Ori &ori,
                                         const CubeSize &size,const Ori& rotate,const bool &isVisible )
{
    if(m_simContainerForm){
        m_simContainerForm->addDepalletizingBox(uuid, boxNum, wobj, pos, ori, size, rotate, isVisible);
    }
}
void SimulationForm::setData(int index,bool leftOrRight)
{
#if PluginLib_SimulationForm_DOF7_VirtualData_Enabled == 1
    emit changeData(index,leftOrRight);
#endif
}
void *SimulationForm::createPalletizingBox(const QString &uuid, const int &boxNum, const QString &wobj, const Pos &pos, const Ori &ori, const CubeSize &size, const Ori &rotate, const bool &isVisible)
{
    if(m_simContainerForm){
        return (void*)m_simContainerForm->createPalletizingBox(uuid, boxNum, wobj, pos, ori, size, rotate, isVisible);
    }
    return nullptr;
}

void SimulationForm::removeDepalletizingBoxs(const QString &uuid)
{
    if(m_simContainerForm){
        m_simContainerForm->removeDepalletizingBoxs(uuid);
    }
}

void SimulationForm::removeAllPalletizingBoxs()
{
    if(m_simContainerForm){
        m_simContainerForm->removeAllPalletizingBoxs();
    }
}

bool SimulationForm::isNeedReCreateModel(const QString &uuid)
{
    if(m_simContainerForm){
        return m_simContainerForm->isNeedReCreateModel(uuid);
    }
    else{
        return false;
    }
}

bool SimulationForm::isAllowUpdateModel(const QString &uuid, const int &sum)
{
    if(m_simContainerForm){
        return m_simContainerForm->isAllowUpdateModel(uuid,sum);
    }
    else{
        return false;
    }
}

void SimulationForm::grapPalletizingBox(const QString &uuid, const int &boxNum)
{
    if (m_simContainerForm) {
        m_simContainerForm->grapPalletizingBox(uuid, boxNum);
    }
}

void SimulationForm::grapPalletizingBox(const CubeSize &size, const Ori &rotate)
{
    if (m_simContainerForm) {
        m_simContainerForm->grapPalletizingBox(size, rotate);
    }
}

void SimulationForm::loosePalletizingBox(const QString &uuid, const int &boxNum,
                                         const Pos &pos, const Ori &ori,const QString& wobj)
{
    if(m_simContainerForm){
        m_simContainerForm->loosePalletizingBox(uuid, boxNum, pos, ori, wobj);
    }
}

void SimulationForm::loosePalletizingBox()
{
    if(m_simContainerForm){
        m_simContainerForm->loosePalletizingBox();
    }
}

void SimulationForm::setPalletizingBoxVisible(const QString &uuid, const int &boxNum, bool bEnable)
{
    if(m_simContainerForm){
        m_simContainerForm->setPalletizingBoxVisible(uuid, boxNum, bEnable);
    }
}

void SimulationForm::setPalletizingBoxVisible(const QString &uuid, bool bEnable)
{
    if(m_simContainerForm){
        m_simContainerForm->setPalletizingBoxVisible(uuid, bEnable);
    }
}

void SimulationForm::setAllPalletizingBoxVisible(bool bEnable)
{
    if(m_simContainerForm){
        m_simContainerForm->setAllPalletizingBoxVisible(bEnable);
    }
}

void SimulationForm::extensionsInitialized()
{

}

void SimulationForm::clearTrack()
{
    if(m_simContainerForm){
        m_simContainerForm->slot_clearTrack();
    }
}

void SimulationForm::retranslateUi()
{
    ui->retranslateUi(this);
    setProperty(InfoFlow_Property,tr("Select condition"));
}

void Ui_SimulationForm::setupUi(QWidget *widgetMiddle)
{
    mainLayout = new QVBoxLayout(widgetMiddle);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
}

void Ui_SimulationForm::retranslateUi(QWidget *widgetMiddle)
{

}
