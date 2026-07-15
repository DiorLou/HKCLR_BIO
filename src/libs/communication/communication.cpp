#include "communication.h"
#include "communication_p.h"
#include <QDebug>
#include <QTimer>
#include "cobotlog.h"
#include "communicationengine.h"
#include "communicationthread.h"
#include "metatypeconversion.h"
#include "instance.h"
#include "configinfo.h"
#include "datacollectioninterface_p.h"
#include "InoRobLog.h"
#include "InoRobUtil.h"
#include "InoRobBusiness/Workstation/IWorkstation.h"
#include "InoRobBusiness/Project/IProject.h"
#include "InoRobBusiness/User/IUser.h"
#include "InoRobLog/PrintInfo/PrintInfo.h"
#include "IController.h"
#include "Factory.h"
#include "messagebox.h"
#include "InoRobBusiness/RobotParam/IRobotParam.h"
#include "modulesutils.h"
static Communication *s_instance = 0;
const QString VIRTUAL_CONTROLELR_IP = "127.0.0.1";

// CommunicationPrivate *CommunicationPrivate::instance()
// {
//     return s_instance;
// }
namespace Internal {


CommunicationPrivate::CommunicationPrivate(Communication *comm) :
    q(comm)
{

}

CommunicationPrivate::~CommunicationPrivate()
{
    qDebug() << "CommunicationPrivate::~CommunicationPrivate()";
    if (m_pProject) {
        disconnect(_IProject,
                   &InoRobBusiness::IProject::loadRPFileNameChanged,
                   this,
                   &CommunicationPrivate::loadRPFileNameChanged);
    }
}

InoRobBusiness::IController *CommunicationPrivate::controller()
{
    return m_pController;
}

InoRobBusiness::IProject *CommunicationPrivate::project()
{
    return m_pProject;
}

InoRobBusiness::IRobotParam *CommunicationPrivate::robotParam()
{
    return m_pRobotParam;
}

IUser *CommunicationPrivate::user()
{
    return m_pUser;
}


bool CommunicationPrivate::login()
{
    bool ret = true;

    ConfigInfo configInfo;
    QMetaObject::invokeMethod(
        Instance::common(), "getConfigInfo", Qt::DirectConnection,
        Q_RETURN_ARG(ConfigInfo, configInfo));

    QMetaObject::invokeMethod(
        Instance::common(), "setConfigInfo", Qt::DirectConnection,
        Q_ARG(const ConfigInfo &, configInfo));

    QMetaObject::invokeMethod(
        Instance::common(), "updateConfigInfo", Qt::DirectConnection);

    return ret;
}

bool CommunicationPrivate::loginAllClient()
{
    // 工作站
    if (!m_pWorkstation) {
        InoRobBusiness::FactoryDefault *factory
            = new InoRobBusiness::FactoryDefault();
        m_pWorkstation = factory->WorkstationBuild(
            InoRobBusiness::WorkstationType::TP2,
            std::string(QApplication::applicationDirPath().toUtf8().constData()));
        delete factory;
        factory = nullptr;
        if (!m_pWorkstation)
            qDebug() << "m_pWorkstation init failed";
    }

    // 控制器
    if (!m_pController) {
        if(m_pWorkstation){
            m_pController = m_pWorkstation->GetController();
            if (!m_pController) {
                qDebug() << "m_pController init failed";
            }
        }
    }

    // 工程管理
    if (!m_pProject) {
        if(m_pWorkstation){
            m_pProject = m_pWorkstation->GetProject();
            if (!m_pProject) {
                qDebug() << "m_pProject init failed";
            } else {
                if (m_pController) {  // 添加空指针检查
                    connect(_IProject, &InoRobBusiness::IProject::loadRPFileNameChanged,
                            this, &CommunicationPrivate::loadRPFileNameChanged);
                } else {
                    qDebug() << "Warning: Cannot connect signal, m_pController is null";
                }
            }
        }
    }

    // 用户管理
    if (!m_pUser) {
        if(m_pWorkstation){
            m_pUser = m_pWorkstation->GetUser();
            if (!m_pUser)
                qDebug() << "m_pUser init failed";
        }
    }

    if (!m_pRobotParam) {
        if(m_pWorkstation){
            m_pRobotParam = m_pWorkstation->getRobotParam();
            if (!m_pRobotParam)
                qDebug() << "m_pRobotParam init failed";
        }
    }
    q->listenStateChanged();
    q->initdatas();

    bool ret = true;

    for (CommunicationThread *thread :
         CommunicationEngine::instance()->getCommunicationThreadPool())
        if (!(ret = thread->m_commInstance->login()))
            break;

    if (!(ret = Communication::instance()->login()))
        ;

    if (!ret) {
        MessageBox::warning(QObject::tr("Login failed!"));
        Instance::common()->setProperty("isShutdownAfterPowerOff", false);
        dynamic_cast<QThread *>(Instance::shutdownThread())->start();
    }

    // CommunicationPrivate::instance()->robotMoveSlowlyStopInterface();

    return ret;
}

void CommunicationPrivate::logoutAllClient()
{
    for (CommunicationThread *thread :
         CommunicationEngine::instance()->getCommunicationThreadPool())
        ;
}

QString CommunicationPrivate::getIP() const
{
    return m_ip;
}

void CommunicationPrivate::setIP(const QString &newIP)
{
    m_ip = newIP;
}

bool CommunicationPrivate::isConnectVirtualController()
{
    return (Communication::instance()->isConnected()
            && 0 == m_ip.compare(VIRTUAL_CONTROLELR_IP));
}

int CommunicationPrivate::getPort() const
{
    return m_port;
}

void CommunicationPrivate::setPort(int newPort)
{
    m_port = newPort;
}

CoordParam CommunicationPrivate::getCurCoordParams()
{
    QStringList curTools = q->comm()->getCurToolNames();
    QStringList curWobjs = q->comm()->getCurWobjNames();

    CoordParam coordParam;
    coordParam.m_coordType = getCoordTypeStr();
    if (ToolCoordinate == coordParam.m_coordType) {
        coordParam.m_toolName = curTools[q->comm()->GetCurToolId()];
    } else if (UserCoordinate == coordParam.m_coordType) {
        coordParam.m_coordName = curWobjs[q->comm()->GetCurWObjId()];
    }

    return coordParam;
}

QString CommunicationPrivate::getCoordTypeStr()
{
    if (q->comm()->GetCurCoodType() == RobotCoordType_Base) {
        return BaseCoordinate;
    } else if (q->comm()->GetCurCoodType() == RobotCoordType_Tool) {
        return ToolCoordinate;
    } else if (q->comm()->GetCurCoodType() == RobotCoordType_User) {
        return UserCoordinate;
    } else if (q->comm()->GetCurCoodType() == RobotCoordType_Joint) {
        return JoinCoordinate;
    } else if (q->comm()->GetCurCoodType() == RobotCoordType_World) {
        return WorldCoordinate;
    }

    return BaseCoordinate;
}

void CommunicationPrivate::loadRPFileNameChanged(std::string fileName)
{
    emit CommunicationEngine::instance()->signal_loadRPFileChanged(fileName);
    q->setCurLoadedRPointFile(std::move(fileName));
}
}

Communication *Communication::instance()
{
    return s_instance;
}

Communication::Communication()
{
    d = new Internal::CommunicationPrivate(this);
    s_instance = this;
    Instance::setComm(this);
}

Communication::~Communication()
{
    delete d;
    d = nullptr;
}

IUser *Communication::user()
{
    return d->user();
}

Communication *Communication::comm()
{
    return this;
}

bool Communication::loginAllClient()
{
    return d->loginAllClient();
}

void Communication::logoutAllClient()
{
    d->logoutAllClient();
}

QString Communication::getIP() const
{
    return d->getIP();
}

void Communication::setIP(const QString &newIP)
{
    d->setIP(newIP);
}

bool Communication::isConnectVirtualController()
{
    return d->isConnectVirtualController();
}

int Communication::getPort() const
{
    return d->getPort();
}

void Communication::setPort(int newPort)
{
    d->setPort(newPort);
}

CoordParam Communication::getCurCoordParams()
{
    return d->getCurCoordParams();
}

bool Communication::login()
{
    return d->login();
}

IRobotParam *Communication::robotParam()
{
    return d->robotParam();
}

IProject *Communication::project()
{
    return d->project();
}

IController *Communication::controller()
{
    return d->controller();
}
