#include "ethernetipinterface.h"
#include <QDebug>
#include "IController.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "cobotlogex.h"
#include "modulesutils.h"
#include "modulesutils.h"
int EthernetIPInterface::writeEthernetIpConfig(CobotEthernetIpPara eipConfig)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    EthernetIpPara param;
    memcpy(&param, &eipConfig, sizeof(EthernetIpPara));
    int iRet = _IFieldBus->getEthernetIPSwitch()->writeEthernetIpConfig(param);

    LOG_INFO(QString("write ethernetip ret = %1").arg(QString::number(iRet)));

    bool ok = false;
    _IRobotArm->saveFileCommond(&ok);
    if (!ok) {
        qDebug() << __FUNCTION__ << "| save result : " << ok;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

int EthernetIPInterface::readEthernetIpConnStatus(CobotEthernetIpSts &eipPara)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    EthernetIpSts ipsts;
    int iRet = _IFieldBus->getEthernetIPSwitch()->readEthernetIpConnStatus(ipsts);
    memcpy(&eipPara, &ipsts, sizeof(EthernetIpSts));

    LOG_INFO(QString("read eip, ActiveSts = %1, ConnectSts = %2").arg(QString::number(eipPara.ActiveSts),
                                                                      QString::number(eipPara.ConnectSts)));
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

bool EthernetIPInterface::checkEthernetIPOperatePermission()
{
    return _IFieldBus->getEthernetIPSwitch()->checkEthernetIPOperatePermission();
}

bool EthernetIPInterface::checkSaveEthernetIPPermission()
{
    return _IFieldBus->getEthernetIPSwitch()->checkSaveEthernetIPPermission();
}
