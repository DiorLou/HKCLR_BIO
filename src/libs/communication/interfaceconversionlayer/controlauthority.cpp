#include "controlauthority.h"
#include <QDebug>
#include "communication.h"
#include "communicationengine.h"
#include "projectdata.h"
#include "InoRobBusiness/Controller/ControlAuthority/IControlAuthority.h"
#include "InoRobBusiness/Controller/IController.h"
#include "cobotlogex.h"
#include <QThread>
#include "modulesutils.h"
void ControlAuthority::setCurrentAuthority(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [type, speed] = ((CmdDatas<InoCtrlAuthority, int> *)absCmd)->m_data;
    InoRobBusiness::CtrlAuthority auth = InoRobBusiness::CtrlAuthority::NOCTRL;
    switch (type) {
    case InoCtrlAuthority_Unknown: auth = InoRobBusiness::CtrlAuthority::TEACHPAD; break;
    case InoCtrlAuthority_TeachPad: auth = InoRobBusiness::CtrlAuthority::TEACHPAD; break;
    case InoCtrlAuthority_InorobShop: auth = InoRobBusiness::CtrlAuthority::INOROBSHOP; break;
    case InoCtrlAuthority_Ethernet: auth = InoRobBusiness::CtrlAuthority::RMT_ETHERNET; break;
    case InoCtrlAuthority_IO: auth = InoRobBusiness::CtrlAuthority::RMT_IO; break;
    case InoCtrlAuthority_Modbus: auth = InoRobBusiness::CtrlAuthority::RMT_MODBUS; break;
    case InoCtrlAuthority_IO_AUTO: auth = InoRobBusiness::CtrlAuthority::RMT_IO_AUTO; break;
    case InoCtrlAuthority_NoCtrl: auth = InoRobBusiness::CtrlAuthority::NOCTRL; break;
    }
    int ret = _IControlAuthority->changeAuthority(auth, speed);
    if (ret != ERROR_OK) {
        //emit CommunicationEngine::instance()->signal_needMainWidgetWarning(
        //    QObject::tr("Failed to set robot control."));
        getCurrentAuthority(absCmd);
    }
    emit CommunicationEngine::instance()->singnal_setControlAuthorityRes(
        absCmd->m_object, ret == ERROR_OK);
    FREQ_LOG_PRINT_TIMESTAMP
}

void ControlAuthority::getCurrentAuthority(AbstractCmd *absCmd)
{
    LOG_TRACE(QString("[%1][%2][%3][%4]")
                  .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch()),
                       QString::number(reinterpret_cast<intptr_t>(QThread::currentThreadId()))));

    InoRobBusiness::CtrlAuthority type = InoRobBusiness::CtrlAuthority::NOCTRL;
    InoRobBusiness::RmtIoSubMode rmtIoSubMode = InoRobBusiness::RmtIoSubMode::UNKNOWN;
    int speed = 0;
    int ret1 = _IControlAuthority->readAuthority(type);
    int ret2 = _IControlAuthority->readRmtIoSubMode(rmtIoSubMode);
    int ret3 = _IControlAuthority->readRmtDefaultSpeed(speed);
    if (ret1 != ERROR_OK || ret2 != ERROR_OK || ret3 != ERROR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to get controller permission status."));
        return;
    }
    if (type == InoRobBusiness::CtrlAuthority::RMT_IO && rmtIoSubMode == InoRobBusiness::RmtIoSubMode::ONLYAUTO) {
        type = InoRobBusiness::CtrlAuthority::RMT_IO_AUTO;
    }
    InoCtrlAuthority ans;
    switch (type) {
    case InoRobBusiness::CtrlAuthority::TEACHPAD: ans = InoCtrlAuthority_TeachPad; break;
    case InoRobBusiness::CtrlAuthority::INOROBSHOP: ans = InoCtrlAuthority_InorobShop; break;
    case InoRobBusiness::CtrlAuthority::RMT_ETHERNET: ans = InoCtrlAuthority_Ethernet; break;
    case InoRobBusiness::CtrlAuthority::RMT_IO: ans = InoCtrlAuthority_IO; break;
    case InoRobBusiness::CtrlAuthority::RMT_MODBUS: ans = InoCtrlAuthority_Modbus; break;
    case InoRobBusiness::CtrlAuthority::RMT_IO_AUTO: ans = InoCtrlAuthority_IO_AUTO; break;
    case InoRobBusiness::CtrlAuthority::NOCTRL: ans = InoCtrlAuthority_NoCtrl; break;
    }
    comm()->setCurCtrlAuthority(ans);
    emit CommunicationEngine::instance()->singnal_getControlAuthorityRes(absCmd->m_object, ans, speed);

    FREQ_LOG_PRINT_TIMESTAMP
}
