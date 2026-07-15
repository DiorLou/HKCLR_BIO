#include "resourceinterface.h"

#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

void ResourceInterface::setElectricScheduler(bool scheduler)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (scheduler) {
        _IResource->updateElectric();
    }
    _IResource->setElectricScheduler(scheduler);
}

void ResourceInterface::setAvgLoadRateScheduler(bool scheduler)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (scheduler) {
        _IResource->updateAvgLoadRate();
    }
    _IResource->setAvgLoadRateScheduler(scheduler);
}

void ResourceInterface::setOverLoadScheduler(bool scheduler)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (scheduler) {
        _IResource->updateOverLoad();
    }
    _IResource->setOverLoadScheduler(scheduler);
}

void ResourceInterface::setOverHeatScheduler(bool scheduler)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (scheduler) {
        _IResource->updateOverHeat();
    }
    _IResource->setOverHeatScheduler(scheduler);
}

int ResourceInterface::readActCurrent(std::vector<double> &actualCurrent)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _IResource->readCurrentElectric(actualCurrent);
    return iRet;
}

int ResourceInterface::readHisMaxCurrent(std::vector<double> &maxCurrent)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _IResource->readMaxElectric(maxCurrent);
    return iRet;
}

int ResourceInterface::resetHisMaxCurrent()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->resetMaxElectric();
}

int ResourceInterface::readActLoadrate(std::vector<double> &actualLoad)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->readCurrentAvgLoadRate(actualLoad);
}

int ResourceInterface::readActualOverLoad(std::vector<double> &actualOverLoad)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->readCurrentOverLoad(actualOverLoad);
}

int ResourceInterface::readMaxOverLoad(std::vector<double> &maxOverLoad)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->readMaxOverLoad(maxOverLoad);
}

int ResourceInterface::resetMaxOverLoad()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->resetMaxOverLoad();
}

int ResourceInterface::readOverHeat(std::vector<double> &overHeat)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IResource->readCurrentOverHeat(overHeat);
}

int ResourceInterface::readEmgTrigMethod(quint8 &iMethod)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IRCConfig->readEmgTrigMethod(iMethod);
}

int ResourceInterface::saveEmgTrigMethod(quint16 iMethod)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!_IRCConfig->checkPermissionBeforeSaveEmgTrigMethod()) {
        return -1;
    }

    return _IRCConfig->saveEmgTrigMethod(iMethod);
}

int ResourceInterface::saveEmgStopMode(quint8 nMode, quint8 nSecondMode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!_IRCConfig->checkSaveEmgStopModePermission()) {
        return -1;
    }

    return _IRCConfig->saveEmgStopMode(nMode, nSecondMode);
}

int ResourceInterface::readEmgStopMode(quint8 &nMode, quint8 &nSecondMode)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _IRCConfig->readEmgStopMode(nMode, nSecondMode);
}

void ResourceInterface::setModbusConnectScheduler(const bool scheduler)
{
    _IResource->setModbusConnectScheduler(scheduler);
}

void ResourceInterface::setEthernetIPScheduler(const bool scheduler)
{
    _IResource->setEthernetIPScheduler(scheduler);
}

void ResourceInterface::setEtherCatScheduler(const bool scheduler)
{
    _IResource->setEtherCatScheduler(scheduler);
}


