#include "modbusinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

int ModbusInterface::writeModbusConfig(CobotModbusParaConfig modbusConfig)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    ModbusParaConfig rModbusConfig;
    memcpy(&rModbusConfig, &modbusConfig, sizeof(ModbusParaConfig));
    int iRet = _IFieldBus
              ->getModbusSwitch()->writeModbusConfig(rModbusConfig);

    bool ok = false;
    _IRobotArm->saveFileCommond(&ok);
    if (!ok) {
        qDebug() << __FUNCTION__ << "| save result : " << ok;
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

int ModbusInterface::readModbusConnStatus(CobotModbusConnectSts &modbusPara)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    ModbusConnectSts rModbusPara;
    int iRet = _IFieldBus
        ->getModbusSwitch()->readModbusConnStatus(rModbusPara);
    memcpy(&modbusPara, &rModbusPara, sizeof(rModbusPara));
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet == 0;
}

bool ModbusInterface::checkModbusOperatePermission()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
        ->getModbusSwitch()->checkModbusOperatePermission();
}

bool ModbusInterface::checkSaveModbusPermission()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
        ->getModbusSwitch()->checkSaveModbusPermission();
}
