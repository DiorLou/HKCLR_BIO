#include "userinterface.h"
#include "communication.h"
#include "IController.h"
#include "InoRobBusiness/User/IUser.h"
#include "metatypeconversion.h"

#include "cobotlogex.h"
#include "modulesutils.h"

InoUserMode UserInterface::getCurrentLoginUserMode()
{
    return MetaTypeConversion::tp2InoApi_userMode(
        comm()->user()->getCurrentLoginUserMode());
}

bool UserInterface::userLogin(const InoUserMode &mode, const QString &passwd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int nRet = comm()->user()->userLogin(
        MetaTypeConversion::inoApi2tp_userMode(mode), passwd.toStdString());
    LOG_TRACE(QString("[%1][%2][%3]")
                .arg(__FILE__, __FUNCTION__, QString::number(QDateTime::currentMSecsSinceEpoch())));
    return (nRet == ERR_OK);
}

bool UserInterface::setCtlAuthority(const InoCtrlAuthority &authority)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IControlAuthority->setCurrentAuthority(
        MetaTypeConversion::inoApi2tp_controlAuthority(authority));

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

InoCtrlAuthority UserInterface::getCtlAuthority()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    InoRobBusiness::CtrlAuthority mAuthority =
        _IControlAuthority->getCurrentAuthority();
    FREQ_LOG_PRINT_TIMESTAMP
    return MetaTypeConversion::tp2InoApi_controlAuthority(mAuthority);
}
