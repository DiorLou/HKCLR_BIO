#include "robotdebug.h"
#include "robotdebug_p.h"
#include <QDebug>
#include "communication.h"
#include "communicationengine.h"
// #include "DataSrvGlobal.h"
#include "InoRobBusiness/RobotParam/IRobotParam.h"
// #include "robotioinfo.h"
// #include "instance.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "InoRobBusiness/Controller/Connection/IConnection.h"
#include "InoRobBusiness/Controller/Resource/ResourceDefault.h"
#include "IController.h"
#include "taskneedtime.h"
#include "cobotlogex.h"
#include "FTP/FtpDefault.h"
#include "communication.h"
#include "stringutils.h"
#include "fileutils.h"
#include "metapath.h"
#include "InoRobUdf/udf.h"
#include "modulesutils.h"
#include "InoRobBusiness/VirtualControllerDeviceManager.h"
inline QString addNewLine(const QString &in, const QString &newLine)
{
    // qDebug() << in << newLine;
    return in + (in.isEmpty() ? "" : "\n") + newLine;
}

static bool splitRemoteNameFromMetaData(std::string src, std::string &dest)
{
    dest.clear();
    int size = src.size();
    int count = 0;
    for (int i = 0; i < size - 1; ++i) {
        if (src[i] == ' ' && src[i + 1] != ' ') {
            ++count;
            if (count == 8) {
                dest = src.substr(i + 1);
                return true;
            }
        }
    }
    return false;
}

namespace Internal {

RobotDebugPrivate::RobotDebugPrivate(RobotDebug *robotDebug) :
    q(robotDebug)
{

}

RobotDebugPrivate::~RobotDebugPrivate()
{

}

IController *RobotDebugPrivate::controller()
{
    return q->controller();
}

void RobotDebugPrivate::ping(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int nSend = 0, nRecv = 0;
    double nLoss = 100.0, minT = 0.0, maxT = 0.0, aveT = 0.0;
    auto [ip] = ((CmdDatas<QString> *)absCmd)->m_data;
    _IConnection->ping(nSend, nRecv, nLoss, minT, maxT, aveT, ip.toStdString(), 4);
    QString res = QObject::tr("Ping statistics for {0}: ").replace("{0}", ip) + "\r\n"
                + QString(QObject::tr("Packets: Sent = %1, Accepted = %2, Loss = %3%") + "\r\n")
                      .arg(QString::number(nSend), QString::number(nRecv), QString::number(nLoss, 'f', 2));
    emit CommunicationEngine::instance()->singnal_getPing_result(absCmd->m_object, res);
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::readComState(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    int ans;
    int nRet = _IRCConfig->readComSwitch(ans);
    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to read COM status."));
    } else {
        emit CommunicationEngine::instance()->singnal_getComState_result(absCmd->m_object, ans == 0 ? false : true);
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::writeComState(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
    int nRet = _IRCConfig->saveComSwitch(state ? 1 : 0);
    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to save COM status."));
    } else {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("COM status saved successfully and takes effect after controller restart. "));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::startDiagnose(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [sys, logic, track] = ((CmdDatas<bool, bool, bool> *)absCmd)->m_data;
    int nRet = _IMaintenance->startDiagnose(sys, logic, track);
    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to start system diagnosis."));
    } else {
        emit CommunicationEngine::instance()->singnal_systemDiagnoseTaskHasStartSucess(absCmd->m_object, absCmd->m_cmdType);
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::stopDiagnose(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [variant] = ((CmdDatas<QVariant> *)absCmd)->m_data;
    QVariantList list = variant.toList();
    int nRet = _IMaintenance->stopDiagnose(list[0].toBool(),
                                           list[1].toBool(),
                                           list[2].toBool());
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_stopResult(absCmd->m_object, nRet == ERR_OK, "");
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::readDiagnosePercent(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (_IConnection->GetConnectionStatus()
        != InoRobBusiness::CONTROLLER_CONNECTION_STATUS_CONNECTED) {
        emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
            absCmd->m_object, false, 0, Task_UnknowState, "");
        return;
    }
    ErrsaveSta sta;  //-1-保存失败  0-null 1-保存中  2-保存成功  3-保存终止
    int nRet = _IMaintenance->ReadErrSaveSta(sta);
    InoTaskState state;
    switch (sta.saveRes) {
    case (-1): {
        state = Task_Falid;
        break;
    }
    case (0): {
        state = Task_UnknowState;
        break;
    }
    case (1): {
        state = Task_InProcess;
        break;
    }
    case (2): {
        state = Task_FineshedSuccess;
        break;
    }
    case (3): {
        state = Task_WasForciblyTerminated;
        break;
    }
    default:
        state = Task_UnknowState;
        break;
    }
    emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
        absCmd->m_object, nRet == ERR_OK, sta.saveProgress, state, "");
    FREQ_LOG_PRINT_TIMESTAMP
}



void RobotDebugPrivate::startExportReportToControllerUSB(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [dialog, sys, logic, track, type] = ((CmdDatas<QObject *, bool, bool, bool, int> *)absCmd)->m_data;
    m_errorStrForUsb = "";
    m_isExportFilesFinished = false;
    m_noMoreSignalExportReportToControllerUSB = true;
    int nRet = _IMaintenance->startExportReport(sys, logic, track, type, 2);
    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to export system diagnostic files to USB drive."), false);
        return;
    }

    emit CommunicationEngine::instance()->singnal_systemDiagnoseTaskHasStartSucess(absCmd->m_object, absCmd->m_cmdType);
    QString srcPath = QDir::cleanPath(ABSOLUTE_SHARE_PATH + "/../studio/logs");
    QString destPath = "./MonitorLog/TeachpantLog";
    // QString destPath = "./MonitorLog/RobLogicInfo/OperationLog";//OperationLog

    QPair<QObject *, int> callBackPara = QPair<QObject *, int>(dialog, absCmd->m_cmdType);
    UDF udf(0, false);
    bool ans = udf.uploadDir(destPath.toStdString(), srcPath.toStdString(), true, UDF::bindTransfer(this, &RobotDebugPrivate::tranferFileProcess), &callBackPara);
    if (!ans)
        m_errorStrForUsb = udf.getLastErrorStr().c_str();

    nRet = _IMaintenance->startExportReport(sys, logic, track, type);
    if (nRet == ERR_OK) {
        m_isExportFilesFinished = true;
    } else {
        emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
            dialog, true, 100, Task_Falid, "");
    }
    // downloadFiles
    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::readErrExportStaPercentToControllerUSB(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!m_isExportFilesFinished) {
        return;
    } else {
        int process = 0;
        InoTaskState state = Task_UnknowState;
        bool isSuccess = false;
        isSuccess = readErrExportStaPercent(process, state);
        if (state == Task_UnknowState)
            state = Task_InProcess;
        if (state == Task_FineshedSuccess && !m_errorStrForUsb.isEmpty()) {
            PRINT_ERROR(m_errorStrForUsb);
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                absCmd->m_object, isSuccess, 20 + process * 80 / 100, Task_Falid, "Error when upload teachpant logs, files maybe not complete.");
            m_noMoreSignalExportReportToControllerUSB = false;
        }
        if (m_noMoreSignalExportReportToControllerUSB)
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                absCmd->m_object, isSuccess, 20 + process * 80 / 100, state, "");
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::startExportReportToLocal(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [sys, logic, track, type, dst, path] = ((CmdDatas<bool, bool, bool, int, int, QString> *)absCmd)->m_data;
    int nRet = _IMaintenance->startExportReport(sys, logic, track, type, dst);

    if (nRet != ERR_OK) {
        emit CommunicationEngine::instance()->signal_needMainWidgetWarning(QObject::tr("Failed to export system diagnostic files to local."));
    } else {
        m_isNeedTeachpantLog = logic;
        m_isFilesForFtpToLoaclReady = false;
        m_FilesForFtpToLocalHasStart = false;
        m_exportLocalPath = path.mid(0);
        emit CommunicationEngine::instance()->singnal_systemDiagnoseTaskHasStartSucess(absCmd->m_object, absCmd->m_cmdType);
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::readErrExportStaPercentToLocal(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    if (!m_isFilesForFtpToLoaclReady) {
        int process = 0;
        InoTaskState state = Task_UnknowState;
        bool isSuccess = false;
        isSuccess = readErrExportStaPercent(process, state);
        if (state == Task_FineshedSuccess) {
            m_isFilesForFtpToLoaclReady = true;
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                absCmd->m_object, isSuccess, 50, Task_InProcess, RobotDebugTR::tr("Getting file list..."));
        } else {
            QString tips;
            if (state == Task_InProcess) {
                tips = RobotDebugTR::tr("The controller is preparing files...");
            }
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                absCmd->m_object, isSuccess, process / 2, state, tips);
        }
    } else if (!m_FilesForFtpToLocalHasStart) {
        m_FilesForFtpToLocalHasStart = true;
        UDF udf(0, false);
        QPair<QObject *, int> callBackPara = QPair<QObject *, int>(absCmd->m_object, absCmd->m_cmdType);
#if defined(PLATFORM_COBOT_TP_WINDOWS) && defined(COPY_SYSTEM_DIAGNOISE_FILE_TO_TARGET)
        QString tempPath = "c:/temp/" + StringUtils::getUuid();
#else
        QString tempPath = m_exportLocalPath;
#endif
        // bool res = udf.downloadDirectory("./MonitorLogToTP/", m_exportLocalPath.toStdString(),
        //                                  UDF::bindTransfer(this, &RobotDebugPrivate::tranferFileProcess), &callBackPara);
        bool res = false;
        if (Communication::instance()->isConnectVirtualController()) {
            string srcPath = CombinePath(VirtualControllerDeviceManager::instance()->getVirtualControllerPath(), "/MonitorLogToTP");
            res = DirectoryCopy(srcPath, tempPath.toStdString());
        } else {
            res = udf.downloadDirectory("./MonitorLogToTP/", tempPath.toStdString(),
                                        UDF::bindTransfer(this, &RobotDebugPrivate::tranferFileProcess), &callBackPara);
        }
        QStringList makeFolderFileFaliedList, copyFileFailedList;

        QString teachPantLogPath = ABSOLUTE_SHARE_PATH + "/../studio/logs";
        QString targetLogPath = m_exportLocalPath + "/TeachpandtLog";
        FileUtils::copyFolderRecursively(teachPantLogPath, targetLogPath, makeFolderFileFaliedList, copyFileFailedList);
        QString errorStr;
        if (res && makeFolderFileFaliedList.size() == 0 && copyFileFailedList.size() == 0) {
#if defined(PLATFORM_COBOT_TP_WINDOWS) && defined(COPY_SYSTEM_DIAGNOISE_FILE_TO_TARGET)
            FileUtils::copyFolderRecursively(tempPath, m_exportLocalPath, makeFolderFileFaliedList, copyFileFailedList);
            if (makeFolderFileFaliedList.size() == 0 && copyFileFailedList.size() == 0) {
                emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                    absCmd->m_object, true, 100, Task_FineshedSuccess, "");
                FileUtils::removeDirectoryRecursively(tempPath);
                return;
            } else {
                FileUtils::removeDirectoryRecursively(tempPath);
            }
#else
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                absCmd->m_object, true, 100, Task_FineshedSuccess, "");
            return;
#endif
        }
        if (!res)
            errorStr = addNewLine(errorStr, QString::fromStdString(udf.getLastErrorStr()));
        if (makeFolderFileFaliedList.size() != 0) {
            errorStr = addNewLine(errorStr, RobotDebugTR::tr("Error creating local directory, files may be incomplete. Details:"));
            for (int i = 0; i < makeFolderFileFaliedList.size(); ++i) {
                errorStr = addNewLine(errorStr, makeFolderFileFaliedList[i]);
            }
        }
        int copyFileFailedListSize = copyFileFailedList.size();
        if (copyFileFailedListSize != 0) {
            errorStr = addNewLine(errorStr, RobotDebugTR::tr("Failed to upload %1 teach pendant log files. Details: ").arg(copyFileFailedListSize));
            for (int i = 0; i < copyFileFailedListSize; ++i) {
                errorStr = addNewLine(errorStr, copyFileFailedList[i]);
            }
        }
        if (!errorStr.isEmpty())
            PRINT_ERROR(errorStr);
        emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
            absCmd->m_object, true, 100, Task_Falid, "");
    }

    FREQ_LOG_PRINT_TIMESTAMP
}

void RobotDebugPrivate::tranferFileProcess(const int total, const int current, void *data)
{
    QPair<QObject *, int> callBackPara = (*static_cast<QPair<QObject *, int> *>(data));
    // qDebug() << "callBackPara is" << callBackPara.second;
    if (callBackPara.second == AbstractCmd::CmdType_ReadErrExportStaToLocal) {
        emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
            callBackPara.first, true, 45 + current * 50 / total, Task_InProcess,
            RobotDebugTR::tr("Transferring files...(%1/%2)").arg(QString::number(current), QString::number(total)));
    } else if (callBackPara.second == AbstractCmd::CmdType_StartExportDiagnoseReportToUSB) {
        if (total == -1)
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                callBackPara.first, true, 5, Task_InProcess,
                RobotDebugTR::tr("Deleting outdated files...(Complete: %1)").arg(QString::number(current)));
        else
            emit CommunicationEngine::instance()->singnal_processBarFormWithComm_currentState(
                callBackPara.first, true, 5 + current * 15 / total, Task_InProcess,
                RobotDebugTR::tr("Uploading the latest teachpant log...(%1/%2)").arg(QString::number(current), QString::number(total)));
    }
}

bool RobotDebugPrivate::readErrExportStaPercent(int &process, InoTaskState &state)
{
    ErrexportSta sta;
    int nRet = _IMaintenance->ReadErrExportSta(sta);
    if (nRet != ERR_OK) {
        process = 100;
        state = Task_UnknowState;
        return false;
    }
    switch (sta.exportRes) {
    case (-1): {
        state = Task_Falid;
        break;
    }
    case (0): {
        state = Task_UnknowState;
        break;
    }
    case (1): {
        state = Task_InProcess;
        break;
    }
    case (2): {
        state = Task_FineshedSuccess;
        break;
    }
    default:
        state = Task_UnknowState;
        break;
    }
    process = sta.exportProgress;
    return true;
}
}
RobotDebug::RobotDebug()
{
    d = new Internal::RobotDebugPrivate(this);
}

RobotDebug::~RobotDebug()
{
    delete d;
    d = nullptr;
}

void RobotDebug::ping(AbstractCmd *absCmd)
{
    d->ping(absCmd);
}

void RobotDebug::readComState(AbstractCmd *absCmd)
{
    d->readComState(absCmd);
}

void RobotDebug::writeComState(AbstractCmd *absCmd)
{
    d->writeComState(absCmd);
}

void RobotDebug::startDiagnose(AbstractCmd *absCmd)
{
    d->startDiagnose(absCmd);
}

void RobotDebug::stopDiagnose(AbstractCmd *absCmd)
{
    d->stopDiagnose(absCmd);
}

void RobotDebug::readDiagnosePercent(AbstractCmd *absCmd)
{
    d->readDiagnosePercent(absCmd);
}

void RobotDebug::startExportReportToControllerUSB(AbstractCmd *absCmd)
{
    d->startExportReportToControllerUSB(absCmd);
}

void RobotDebug::readErrExportStaPercentToControllerUSB(AbstractCmd *absCmd)
{
    d->readErrExportStaPercentToControllerUSB(absCmd);
}

void RobotDebug::startExportReportToLocal(AbstractCmd *absCmd)
{
    d->startExportReportToLocal(absCmd);
}

void RobotDebug::readErrExportStaPercentToLocal(AbstractCmd *absCmd)
{
    d->readErrExportStaPercentToLocal(absCmd);
}

void RobotDebug::tranferFileProcess(const int total, const int current, void *data)
{
    d->tranferFileProcess(total, current, data);
}
