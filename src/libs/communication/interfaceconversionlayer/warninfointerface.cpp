#include "warninfointerface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

void WarnInfoInterface::setWarnMonitorEnable(bool isEnable)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IWarnInfo->setWarnMonitorEnable(isEnable);

    FREQ_LOG_PRINT_TIMESTAMP
}
