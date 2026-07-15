#include "safetyinterface.h"

#include <QDebug>
#include "IController.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "GlobalDataService/DataService/DataSrvGlobal.h"

#include "cobotlogex.h"
#include "modulesutils.h"

int SafetyInterface::QuerySafeParaCabinet()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->QuerySafeParaCabinet();
}

int SafetyInterface::QuerySafeParaCabinetProcess(bool printFlag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->QuerySafeParaCabinetProcess(printFlag);
}

int SafetyInterface::CheckSafeParaPassword(const unsigned int password)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->CheckSafeParaPassword(password);
}

int SafetyInterface::CheckSafeParaPassword()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->CheckSafeParaPassword();
}

int SafetyInterface::SafetyReadParams(int key, int offset, int num)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->Read(key, offset, num);

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::GetSafeParaCommon(int key, int offset, int length,
                                       unsigned char *buf, bool forceFlag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->GetSafeParaCommon(key, offset, length, buf, forceFlag);

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::SetSafeParaCommon(int key, int offset, int length,
                                       unsigned char *buf, bool forceFlag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->SetSafeParaCommon(key, offset, length, buf, forceFlag);

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::SafetyWriteParams(int key, int offset, int num)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->Write(key, offset, num);

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::SafetyWriteParams(int *range, int num)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->Write(range, num);

    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::SafeParaReset()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->SafeParaReset(true);
}

int SafetyInterface::CheckAStatus(int key, int offset, int num, int status)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->CheckAStatus(key, offset, num, status);
}

int SafetyInterface::GetSafeHardVer(std::string &system, std::string &moni,
                                    std::string &commu)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    return _ISafeParaSettingMgr->GetSafeHardVer(system, moni, commu);
}

int SafetyInterface::QuerySafeIORealTime(bool switchFlag)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->QuerySafeIORealTime(switchFlag);
    qDebug() << __FUNCTION__ << ", iRet = " << iRet << ", switchFlag = " << switchFlag;
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

bool SafetyInterface::WriteParamsDirect2Mcu(
    const QVector<SafeReadWriteCmdParam> &vecParams)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool bRet = true;
    for (const auto &it : vecParams) {
        int iRet = SetSafeParaCommon(it.key, it.offset, it.length, it.buf, it.forceFlag);

        bRet &= (iRet == 0);

        iRet = SafetyWriteParams(it.key, it.offset, it.num);

        bRet &= (iRet == 0);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

bool SafetyInterface::ReadParamsDirectFromMcu(
    QVector<SafeReadWriteCmdParam> &vecParams)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    bool bRet = true;
    for (auto &it : vecParams) {
        int iRet = CheckAStatus(it.key, it.offset, it.num, Cobot_SPS_SYNC);
        if (iRet != Cobot_SPR_ERRFUNC && iRet != Cobot_SPR_SUC) {
            break;
        }

        if (iRet == Cobot_SPR_ERRFUNC) {
            // 数据不一致, 先将MCU的数据读取到模型层
            iRet = SafetyReadParams(it.key, it.offset, it.num);
            bRet &= (iRet == 0);
        }

        // 将模型层数据读取到GUI
        iRet = GetSafeParaCommon(it.key, it.offset, it.length, it.buf, it.forceFlag);

        bRet &= (iRet == 0);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return bRet;
}

int SafetyInterface::SetInterZoneSendStatus(quint8 status)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int iRet = _ISafeParaSettingMgr->SetInterZoneSendStatus(status);
    LOG_INFO(QString("[%1]iRet = %2, status = %3.").arg(__FUNCTION__, QString::number(iRet), QString::number(status)));
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::WriteSpeedReducing(const SpeedReducingConf &conf)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    S_SPEEDREDUCINGCONF speedReducing;
    memcpy(&speedReducing, &conf, sizeof(speedReducing));
    int iRet = _ISafeParaSettingMgr->WriteSpeedReducing(speedReducing);
    LOG_INFO(QString("[%1]iRet = %2, status = %3.").arg(__FUNCTION__, QString::number(iRet), QString::number(iRet)));
    qDebug() << __FUNCTION__ << "| ret = " << iRet << ", l1 = " << conf.speedLevel1
             << ", l2 = " << conf.speedLevel2;
    FREQ_LOG_PRINT_TIMESTAMP
    return iRet;
}

int SafetyInterface::ReadSpeedReducing(SpeedReducingConf &conf)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    S_SPEEDREDUCINGCONF speedReducing;
    int iRet = _ISafeParaSettingMgr->ReadSpeedReducing(speedReducing);
    memcpy(&conf, &speedReducing, sizeof(speedReducing));
    LOG_INFO(QString("[%1]iRet = %2, status = %3.").arg(__FUNCTION__, QString::number(iRet), QString::number(iRet)));
    qDebug() << __FUNCTION__ << "| ret = " << iRet << ", l1 = " << conf.speedLevel1
             << ", l2 = " << conf.speedLevel2;
    FREQ_LOG_PRINT_TIMESTAMP
        return iRet;
}

int SafetyInterface::ExportFunctionSafeParaFile(const std::string exportRoute)
{
    int iRet = _ISafeParaSettingMgr->ExportFunctionSafeParaFile(exportRoute);
    LOG_INFO(QString("safety config export, ret = %1, path = %2").arg(QString::number(iRet), exportRoute.data()));
    return iRet;
}

int SafetyInterface::ImportFunctionSafeParaFile(const std::string importRoute)
{
    int iRet = _ISafeParaSettingMgr->ImportFunctionSafeParaFile(importRoute);
    LOG_INFO(QString("safety config import, ret = %1, path = %2").arg(QString::number(iRet), importRoute.data()));
    return iRet;
}
