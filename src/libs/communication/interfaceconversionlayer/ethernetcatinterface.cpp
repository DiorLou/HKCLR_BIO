#include "ethernetcatinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"
#include "cobotlogex.h"
#include "modulesutils.h"
#include "modulesutils.h"
int EthernetCatInterface::writeEthernetCatConfig(InoEthcatPara ecatConfig)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    EthcatPara param;
    memcpy(&param, &ecatConfig, sizeof(EthcatPara));
    int iRet =_IFieldBus->getEtherCATSwitch()->writeEtherCATSlaveConfig(param);

    bool ok = false;
    _IRobotArm->saveFileCommond(&ok);
    if (!ok) {
        qDebug() << __FUNCTION__ << "| save result : " << ok;
    }

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

int EthernetCatInterface::readEthernetCatConnStatus(InoEthcatSts &ecatPara)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    EthcatSts ipsts;
    int iRet =_IFieldBus
        ->getEtherCATSwitch()->readEtherCATConnStatus(ipsts);
    memcpy(&ecatPara, &ipsts, sizeof(EthcatSts));
    LOG_INFO(QString("[readEthernetCatConnStatus]open = %1, conn = %2").arg(QString::number(ipsts.ActiveSts),
                                                 QString::number(ipsts.ConnectSts)));
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

bool EthernetCatInterface::checkEthernetCatOperatePermission()
{
    return _IFieldBus
        ->getEtherCATSwitch()->checkEtherCATOperatePermission();
}

bool EthernetCatInterface::checkSaveEthernetCatPermission()
{
    return _IFieldBus
        ->getEtherCATSwitch()->checkSaveEtherCATPermission();
}

int EthernetCatInterface::ReadEtherCATProperties(INO_ETHCAT_PROP &buf)
{
    int ret = 0;

    ETHCAT_PROP robotEthcatProp;
    ret =_IFieldBus->getEtherCATSwitch()
              ->ReadEtherCATProperties(robotEthcatProp);
    buf.u8LinkState = robotEthcatProp.u8LinkState;
    buf.u8EscState = robotEthcatProp.u8EscState;
    buf.u16AppFaultCode = robotEthcatProp.u16AppFaultCode;
    buf.u16AppStateCode = robotEthcatProp.u16AppStateCode;
    buf.u8Port0InvFraCount = robotEthcatProp.u8Port0InvFraCount;
    buf.u8Port0AptErrFraCount = robotEthcatProp.u8Port0AptErrFraCount;
    buf.u8Port1InvFraCount = robotEthcatProp.u8Port1InvFraCount;
    buf.u8Port1AptErrFraCount = robotEthcatProp.u8Port1AptErrFraCount;
    buf.u8Port0ForErrCount = robotEthcatProp.u8Port0ForErrCount;
    buf.u8Port1ForErrCount = robotEthcatProp.u8Port1ForErrCount;
    buf.u8DataFrmProcessingErrCount = robotEthcatProp.u8DataFrmProcessingErrCount;
    buf.u8PIDErrCount = robotEthcatProp.u8PIDErrCount;
    buf.u8Port0LinkLostCount = robotEthcatProp.u8Port0LinkLostCount;
    buf.u8Port1LinkLostCount = robotEthcatProp.u8Port1LinkLostCount;
    buf.u16MCUUpSlaveLost = robotEthcatProp.u16MCUUpSlaveLost;
    buf.u16SlaveAdderss = robotEthcatProp.u16SlaveAdderss;
    buf.u16ESCVerInfor = robotEthcatProp.u16ESCVerInfor;
    buf.u16MCUUpXMLVerInfor = robotEthcatProp.u16MCUUpXMLVerInfor;
    buf.u16SoftVersion = robotEthcatProp.u16SoftVersion;
    buf.u16ARMSetLinkEnhanSwitch = robotEthcatProp.u16ARMSetLinkEnhanSwitch;
    buf.u16EtherCATXMLReset = robotEthcatProp.u16EtherCATXMLReset;

    LOG_INFO(QString("[ReadEtherCATProperties]ARMSetLinkEnhanSwitch = %1, EtherCATXMLReset = %2")
                 .arg(QString::number(robotEthcatProp.u16ARMSetLinkEnhanSwitch),
                      QString::number(robotEthcatProp.u16EtherCATXMLReset)));

    LOG_INFO(QString("[ReadEtherCATProperties]ret = %1").arg(QString::number(ret)));

    return ret;
}

int EthernetCatInterface::WriteEtherCATEnhan(
    quint16 &ARMSetLinkEnhanSwitch, quint16 &EtherCATXMLReset)
{
    int ret = 0;

    LOG_INFO(QString("[WriteEtherCATEnhan]ARMSetLinkEnhanSwitch = %1, EtherCATXMLReset = %2")
                 .arg(QString::number(ARMSetLinkEnhanSwitch), QString::number(EtherCATXMLReset)));
    ret =_IFieldBus->getEtherCATSwitch()
              ->WriteEtherCATEnhan(ARMSetLinkEnhanSwitch, EtherCATXMLReset);

    LOG_INFO(QString("[WriteEtherCATEnhan]ret = %1").arg(QString::number(ret)));

    return ret;
}
