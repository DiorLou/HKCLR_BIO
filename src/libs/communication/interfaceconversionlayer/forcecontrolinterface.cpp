#include "forcecontrolinterface.h"
#include "communication.h"
#include "IController.h"
#include "communicationengine.h"
#include "cobotlog.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "cobotlog.h"
#include <QJsonArray>
#include <QObject>

#include "cobotlogex.h"
#include "modulesutils.h"


void ForceControlInterface::getFCSensorDataArr(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::getFCSensorDataArr start");
    FCSensorParaArr dataArr;
    bool ret = _IForceCtrl->RefreshFCSensorData(dataArr);
    emit CommunicationEngine::instance()->singal_getFCSensorDataArr_result(cmd->m_object, ret, dataArr);
    LOG_INFO("ForceControlInterface::getFCSensorDataArr end. ");
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::saveFCSensorItem(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [sensorNo, switchFlag, para] = BIND(cmd, int, int, ForceCtrlSensorPara);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveFCSensorItem(sensorNo, switchFlag, &para);
        if (!ret) {
            msg = CommTr::tr("Failed to save the configuration file of sensor %1 to the controller.").arg(sensorNo);
            break;
        }

        ret = _IForceCtrl->WriteFCSensorData(sensorNo);
        if (!ret) {
            msg = CommTr::tr("Failed to notify the controller to set the force control switch parameters.");
            break;
        }

        msg = CommTr::tr("The force control switch parameter of sensor %1 has been successfully issued.").arg(sensorNo);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCSensorItem_result(cmd->m_object, ret, msg);
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::getFCCalibData(AbstractCmd *cmd)
{
    LOG_INFO("ForceControlInterface::getFCCalibData start");
    auto [paraIndex] = BIND(cmd, int);
    ForceCtrlCalibData data;
    bool ret = _IForceCtrl->RefreshCalibData(data);
    emit CommunicationEngine::instance()->singal_getFCCalibData_result(cmd->m_object, ret, paraIndex, data);
    LOG_INFO("ForceControlInterface::getFCCalibData end.");
}

bool ForceControlInterface::refreshCalibData(ForceCtrlCalibData &data)
{
    return _IForceCtrl->RefreshCalibData(data);
}

void ForceControlInterface::saveFCCalibItem(AbstractCmd *cmd)
{
    LOG_INFO("ForceControlInterface::saveFCCalibItem start");

    auto [paramIndex, data] = BIND(cmd, int, ForceCtrlCalibItem);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveCalibItems(paramIndex, &data);
        if (!ret) {
            msg = CommTr::tr("Failed to save the calibration data file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteForceCtrlCalibData(paramIndex);
        if (!ret) {
            msg = CommTr::tr("The notification to send the updated calibration data failed.");
            break;
        }

        msg = CommTr::tr("Force sensor parameter %1 successfully issued.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCCalibItems_result(cmd->m_object, ret, msg);
    LOG_INFO("ForceControlInterface::saveFCCalibItem end.");

}

void ForceControlInterface::applyCaliResult(AbstractCmd *cmd)
{
    LOG_INFO("ForceControlInterface::applyCaliResult start");

    auto [paramIndex, data] = BIND(cmd, int, ForceCtrlCalibItem);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveCalibItems(paramIndex, &data);
        if (!ret) {
            msg = CommTr::tr("Failed to save the calibration data file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteForceCtrlCalibData(paramIndex);
        if (!ret) {
            msg = CommTr::tr("The notification to send the updated calibration result failed.");
            break;
        }

        msg = CommTr::tr("The application of force control calibration result has been successful.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_applyCaliResult_result(cmd->m_object, ret, msg);
    LOG_INFO("ForceControlInterface::applyCaliResult end.");

}

void ForceControlInterface::isCanCalibrate(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::isCanCalibrate start");

    auto [curSensorNo] = BIND(cmd, int);
    FCSensorParaArr paraArr = _IForceCtrl->GetCurrentSensorData();
    int curSensorType = paraArr.stFCSensorParaArr[curSensorNo].i16SensorType;
    int curSensorSwitch = paraArr.u8ForceCtrlswitchFlag[curSensorNo];
    int axisCount = _IRobotArm->getAxiCount();
    bool flag = (axisCount == 6) && (curSensorType == ForceCtrlSensorType::SIX) && curSensorSwitch;
    emit CommunicationEngine::instance()->singal_isCanCalibrate_result(cmd->m_object, flag, curSensorType, curSensorSwitch);

    LOG_INFO("ForceControlInterface::isCanCalibrate end.");
    FREQ_LOG_PRINT_TIMESTAMP
}

bool ForceControlInterface::getFCForceValue(int sensorNo, QList<float> &retforceArray)
{
    float forceArray[6];
    bool ret = _IForceCtrl->ReadForceCtrlForceValue(sensorNo, forceArray);
    if (!ret) {
        return false;
    }

    for (int i = 0; i < 6; ++i) {
        retforceArray.append(forceArray[i]);
    }

    return true;
}

// void ForceControlInterface::getFCForceValue(AbstractCmd *cmd)
// {
//     FREQ_LOG_PRINT_TIMESTAMP_THREAD
//     LOG_INFO("ForceControlInterface::getFCForceValue start");
//     auto [index, sensorNo] = BIND(cmd, int, int);
//     QList<float> retforceArray;
//     QString msg;
//     bool ret = true;

//     do {
//         // 获取当前关节角
//         JPos curJpos;
//         ret = _IPosition->GetCurJPos(curJpos);
//         if (!ret) {
//             msg = CommTr::tr("Failed to obtain the current joint point.");
//             break;
//         }

//         // 获取位置坐标
//         RobPos curPos;
//         ReadCurPosState state;
//         ret = _IPosition->GetCurPos(_ITool->GetCurrentId(), ReferObj::ReferBase, state, curPos, false);
//         if (!ret) {
//             msg = CommTr::tr("Failed to obtain the position point in the current base coordinate system.");
//             break;
//         }

//         float forceArray[6];
//         ret = _IForceCtrl->ReadForceCtrlForceValue(sensorNo, forceArray);
//         if (!ret) {
//             msg = CommTr::tr("Failed to read the current six-axis force.");
//             break;
//         }

//         for (int i = 0; i < 6; ++i) {
//             retforceArray.append(forceArray[i]);
//         }

//     } while (false);

//     emit CommunicationEngine::instance()->singal_getFCForceValue_result(cmd->m_object, ret, index, retforceArray, msg);
//     LOG_INFO("ForceControlInterface::getFCForceValue end. ret = " + QString::number(ret));
//     FREQ_LOG_PRINT_TIMESTAMP
// }

bool ForceControlInterface::getFCCalibrateCalc(ForceCtrlCalibItem &item)
{
    return _IForceCtrl->ForceCtrlCalibrateCalc(item);
}

void ForceControlInterface::getFCCoordinateData(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [paraIndex] = BIND(cmd, int);
    FCCoordinatePara fCCoordinatePara;
    int ret = _IForceCtrl->ReadFCCoordinateData(paraIndex, fCCoordinatePara);
    emit CommunicationEngine::instance()->singal_getFCCoordinateData_result(cmd->m_object, ret == ERR_OK, fCCoordinatePara);
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::saveFCCoordinateDataItem(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    auto [paramIndex, para] = BIND(cmd, int, FCCoordinatePara);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveFCCoordinateItem(paramIndex, para);
        if (!ret) {
            msg = CommTr::tr("Failed to save the coordinate system file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteFCCoordinateData(paramIndex);
        if (!ret) {
            msg = CommTr::tr("Failed to notify the controller to set the force control coordinate system parameter.");
            break;
        }

        msg = CommTr::tr("The force control coordinate system parameter %1 has been successfully issued.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCCoordinateDataItem_result(cmd->m_object, ret, msg);
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::getFCConfigParam(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [paraIndex] = BIND(cmd, int);
    ForceCtrlConfigPara fCConfigPara;
    bool ret = _IForceCtrl->ReadForceCtrlConfigParam(paraIndex, fCConfigPara);
    emit CommunicationEngine::instance()->singal_getFCConfigPara_result(cmd->m_object, ret, paraIndex, fCConfigPara);

    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::saveFCConfigParam(AbstractCmd *cmd)
{
    auto [paramIndex, para] = BIND(cmd, int, ForceCtrlConfigPara);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveForceCtrlConfigParam(paramIndex, para);
        if (!ret) {
            msg = CommTr::tr("Failed to save the force control configuration file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteFCConfigParam(paramIndex);
        if (!ret) {
            msg = CommTr::tr("Failed to notify the controller to set the force control configuration parameter.");
            break;
        }

        msg = CommTr::tr("The force control configuration parameter %1 has been successfully issued.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCConfigPara_result(cmd->m_object, ret, msg);

    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::getFCControlParam(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::getFCControlParam start");
    auto [paraIndex] = BIND(cmd, int);
    ForceCtrlMovePara param;
    bool ret = _IForceCtrl->ReadForceCtrlMoveParam(paraIndex, param);
    emit CommunicationEngine::instance()->singal_getFCControlPara_result(cmd->m_object, ret, paraIndex, param);
    LOG_INFO("ForceControlInterface::getFCControlParam end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::saveFCControlParam(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::saveFCControlParam start");
    auto [paramIndex, para] = BIND(cmd, int, ForceCtrlMovePara);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveForceCtrlMoveParam(paramIndex, para);
        if (!ret) {
            msg = CommTr::tr("Failed to save the force control motion control file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteFCControlParam(paramIndex);
        if (!ret) {
            msg = CommTr::tr("Failed to notify the controller to set the force control motion control parameter.");
            break;
        }

        msg = CommTr::tr("The force control motion control parameter %1 has been successfully issued.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCControlPara_result(cmd->m_object, ret, msg);

    LOG_INFO("ForceControlInterface::saveFCControlParam end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::getFCLimitData(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::getFCLimitData start");

    auto [paraIndex] = BIND(cmd, int);
    ForceCtrlLimitPara fCLimitPara;
    bool ret = _IForceCtrl->ReadFCLimitData(paraIndex, fCLimitPara);
    emit CommunicationEngine::instance()->singal_getFCLimitData_result(cmd->m_object, ret, paraIndex, fCLimitPara);

    LOG_INFO("ForceControlInterface::getFCLimitData end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

void ForceControlInterface::saveFCLimitData(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::saveFCLimitData start");
    auto [paramIndex, para] = BIND(cmd, int, ForceCtrlLimitPara);

    QString msg;
    bool ret = true;

    do {
        ret = _IForceCtrl->SaveFCLimitPara(paramIndex, para);
        if (!ret) {
            msg = CommTr::tr("Failed to save the force control limit file for parameter %1 to the controller!").arg(paramIndex);
            break;
        }

        ret = _IForceCtrl->WriteFCLimitData(paramIndex);
        if (!ret) {
            msg = CommTr::tr("Failed to notify the controller to set the force control limit parameter.");
            break;
        }

        msg = CommTr::tr("The force control limit parameter %1 has been successfully issued.").arg(paramIndex);
        break;

    } while (false);

    emit CommunicationEngine::instance()->singal_saveFCLimitData_result(cmd->m_object, ret, msg);
    LOG_INFO("ForceControlInterface::saveFCLimitData end");
    FREQ_LOG_PRINT_TIMESTAMP
}

// ===== 力控日志格式 =====

/**
 * @brief 读取力控日志格式
 * 
 * 从控制器读取力控功能日志的自定义数据格式。
 * 
 * @param cmd 命令对象，包含请求参数
 */
void ForceControlInterface::readForceCtrlLogFormat(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::readForceCtrlLogFormat start");
    
    ForceCtrlLogFormat logFormat;
    int ret = _IForceCtrl->ReadForceCtrlLogFormat(logFormat);
    
    emit CommunicationEngine::instance()->singal_readForceCtrlLogFormat_result(cmd->m_object, ret == ERR_OK, logFormat);
    
    LOG_INFO("ForceControlInterface::readForceCtrlLogFormat end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

/**
 * @brief 写入力控日志格式
 * 
 * 向控制器设置力控功能日志的自定义数据格式。
 * 
 * @param cmd 命令对象，包含日志格式参数
 */
void ForceControlInterface::writeForceCtrlLogFormat(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::writeForceCtrlLogFormat start");
    
    auto [logFormat] = BIND(cmd, ForceCtrlLogFormat);
    
    QString msg;
    bool ret = true;
    
    do {
        int result = _IForceCtrl->WriteForceCtrlLogFormat(logFormat);
        if (result != ERR_OK) {
            ret = false;
            msg = CommTr::tr("Failed to set the force control log format.");
            break;
        }
        
        msg = CommTr::tr("Force control log format has been successfully set.");
        break;
        
    } while (false);
    
    emit CommunicationEngine::instance()->singal_writeForceCtrlLogFormat_result(cmd->m_object, ret, msg);
    
    LOG_INFO("ForceControlInterface::writeForceCtrlLogFormat end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

// ===== 力控监控开关 =====

/**
 * @brief 读取力控监控开关状态
 * 
 * 从控制器读取力控监控的开关状态和坐标系设置。
 * 
 * @param cmd 命令对象
 */
void ForceControlInterface::readForceCtrlMonitorSwitch(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::readForceCtrlMonitorSwitch start");
    
    int8u state = 0;
    int8u coord = 0;
    int ret = _IForceCtrl->ReadForceCtrlMonitorSwitch(state, coord);
    
    emit CommunicationEngine::instance()->singal_readForceCtrlMonitorSwitch_result(cmd->m_object, ret == ERR_OK, state, coord);
    
    LOG_INFO("ForceControlInterface::readForceCtrlMonitorSwitch end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

/**
 * @brief 写入力控监控开关状态
 * 
 * 向控制器设置力控监控的开关状态和坐标系设置。
 * 
 * @param cmd 命令对象，包含开关状态和坐标系参数
 */
void ForceControlInterface::writeForceCtrlMonitorSwitch(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::writeForceCtrlMonitorSwitch start");
    
    auto [state, coord] = BIND(cmd, int, int);
    
    QString msg;
    bool ret = true;
    
    do {
        int result = _IForceCtrl->WriteForceCtrlMonitorSwitch(static_cast<int8u>(state), static_cast<int8u>(coord));
        if (result != ERR_OK) {
            ret = false;
            msg = CommTr::tr("Failed to set the force control monitor switch.");
            break;
        }
        
        msg = CommTr::tr("Force control monitor switch has been successfully set.");
        break;
        
    } while (false);
    
    emit CommunicationEngine::instance()->singal_writeForceCtrlMonitorSwitch_result(cmd->m_object, ret, msg);
    
    LOG_INFO("ForceControlInterface::writeForceCtrlMonitorSwitch end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

// ===== 力控监控数据 =====

/**
 * @brief 读取力控监控数据
 * 
 * 从控制器读取力控反馈数据集合，包括数据个数、剩余数据个数、数据数组和StepId数组。
 * 
 * @param cmd 命令对象
 */
void ForceControlInterface::readForceCtrlMonitorData(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::readForceCtrlMonitorData start");
    
    int dataNum = 0;
    int overDataNum = 0;
    std::vector<ForceCtrlData> dataArr;
    std::vector<int> stepIdArr;
    
    int ret = _IForceCtrl->ReadForceCtrlMonitorData(dataNum, overDataNum, dataArr, stepIdArr);
    
    emit CommunicationEngine::instance()->singal_readForceCtrlMonitorData_result(cmd->m_object, ret == ERR_OK, dataNum, overDataNum, dataArr, stepIdArr);
    
    LOG_INFO("ForceControlInterface::readForceCtrlMonitorData end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

// ===== 清除传感器力 =====

/**
 * @brief 清除力控功能中传感器的残余应力（清零）
 * 
 * 向控制器发送命令，清除力控功能中传感器的残余应力。
 * 
 * @param cmd 命令对象
 */
void ForceControlInterface::writeClearSensorForce(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::writeClearSensorForce start");
    
    QString msg;
    bool ret = true;
    
    do {
        int result = _IForceCtrl->WriteClearSensorForce();
        if (result != ERR_OK) {
            ret = false;
            msg = CommTr::tr("Failed to clear sensor force.");
            break;
        }
        
        msg = CommTr::tr("Sensor force has been successfully cleared.");
        break;
        
    } while (false);
    
    emit CommunicationEngine::instance()->singal_writeClearSensorForce_result(cmd->m_object, ret, msg);
    
    LOG_INFO("ForceControlInterface::writeClearSensorForce end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

// ===== 力控坐标系设置 =====

/**
 * @brief 读取力控坐标系设置
 * 
 * 从控制器读取力觉坐标系参数，包括力控坐标系编号和力传感器参数编号。
 * 
 * @param cmd 命令对象
 */
void ForceControlInterface::readForceCtrlCoodinateSetting(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::readForceCtrlCoodinateSetting start");
    
    int16s coordIndex = 0;
    int16s paraIndex = 0;
    int ret = _IForceCtrl->ReadForceCtrlCoordinateSetting(coordIndex, paraIndex);
    
    emit CommunicationEngine::instance()->singal_readForceCtrlCoordinateSetting_result(cmd->m_object, ret == ERR_OK, coordIndex, paraIndex);
    
    LOG_INFO("ForceControlInterface::readForceCtrlCoodinateSetting end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}

/**
 * @brief 写入力控坐标系设置
 * 
 * 向控制器设置力觉坐标系参数，包括力控坐标系编号和力传感器参数编号。
 * 
 * @param cmd 命令对象，包含坐标系编号和参数编号
 */
void ForceControlInterface::writeForceCtrlCoodinateSetting(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::writeForceCtrlCoodinateSetting start");
    
    auto [coordIndex, paraIndex] = BIND(cmd, int, int);
    
    QString msg;
    bool ret = true;
    
    do {
        int result = _IForceCtrl->WriteForceCtrlCoordinateSetting(static_cast<int16s>(coordIndex), static_cast<int16s>(paraIndex));
        if (result != ERR_OK) {
            ret = false;
            msg = CommTr::tr("Failed to set the force control coordinate setting.");
            break;
        }
        
        msg = CommTr::tr("Force control coordinate setting has been successfully set.");
        break;
        
    } while (false);
    
    emit CommunicationEngine::instance()->singal_writeForceCtrlCoordinateSetting_result(cmd->m_object, ret, msg);
    
    LOG_INFO("ForceControlInterface::writeForceCtrlCoodinateSetting end. ret=" + QString::number(ret));
    FREQ_LOG_PRINT_TIMESTAMP
}


/**
 * @brief 获取工具参数
 * @details 获取当前工具的参数信息
 * @param absCmd 命令对象
 */
void ForceControlInterface::getToolData(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
     
    // 获取当前工具ID
    int toolId = _ITool->GetCurrentId();
    if (toolId < 0) {
        qDebug() << "No current tool selected";
        emit CommunicationEngine::instance()->signal_getToolData_result(
            absCmd->m_object, false, ToolData());
        return;
    }
    
    // 获取工具参数
    ToolData toolData;
    bool ret = _ITool->GetToolParam(toolId, toolData);
    
    if (ret) {
        qDebug() << "Tool data retrieved successfully for tool ID:" << toolId;
        emit CommunicationEngine::instance()->signal_getToolData_result(
            absCmd->m_object, true, toolData);
    } else {
        qDebug() << "Failed to get tool parameters for tool ID:" << toolId;
        emit CommunicationEngine::instance()->signal_getToolData_result(
            absCmd->m_object, false, ToolData());
    }
    
    FREQ_LOG_PRINT_TIMESTAMP
}


/**
 * @brief 获取力控文件日志列表
 * @details 调用 GetForceCtrlLogList 函数获取力控日志文件列表
 * @param cmd 命令对象
 */
void ForceControlInterface::getForceCtrlLogList(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::getForceCtrlLogList start");
    
    // 解析命令参数：文件路径
    auto [filePath] = BIND(cmd, std::string);
    
    std::vector<std::string> fileList;
    int result = 0;
    QString msg;
    bool isSuccess = false;
    
    try
    {
        
        
        // 调用基础版本的函数
        result = _IForceCtrl->GetForceCtrlLogListEx(filePath, fileList);
        
        if (result == ERR_OK)
        {
            isSuccess = true;
            msg = CommTr::tr("Successfully obtained force control log file list, found %1 files.").arg(fileList.size());
            LOG_INFO("ForceControlInterface::getForceCtrlLogList: " + msg);
        }
        else
        {
            // 根据错误码设置相应的错误消息
            switch (result)
            {
                case -1:
                    msg = CommTr::tr("Controller is not connected.");
                    break;
                case -2:
                    msg = CommTr::tr("Force control log folder does not exist.");
                    break;
                case -3:
                    msg = CommTr::tr("Failed to get remote file list.");
                    break;
                case -99:
                    msg = CommTr::tr("Exception occurred while getting force control log list.");
                    break;
                default:
                    msg = CommTr::tr("Failed to get force control log list, error code: %1.").arg(result);
                    break;
            }
            LOG_WARN("ForceControlInterface::getForceCtrlLogList: " + msg);
        }
    }
    catch (const std::exception& ex)
    {
        msg = CommTr::tr("Exception occurred while getting force control log list: %1").arg(QString::fromStdString(std::string(ex.what())));
        LOG_ERROR("ForceControlInterface::getForceCtrlLogList Exception: " + QString::fromStdString(std::string(ex.what())));
        isSuccess = false;
    }
    
    // 发射结果信号
    emit CommunicationEngine::instance()->singal_getForceCtrlLogList_result(cmd->m_object, isSuccess, fileList);
    
    LOG_INFO("ForceControlInterface::getForceCtrlLogList end. result=" + QString::number(result));
    FREQ_LOG_PRINT_TIMESTAMP
}


/**
 * @brief 从控制器复制日志文件到本地
 * @details 调用 ExportLogsFromCtrl 函数批量导出控制器中的力控日志文件到本地
 * @param cmd 命令对象，包含文件名列表和本地路径列表
 */
void ForceControlInterface::copyLogFilesFromControlToLocal(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    LOG_INFO("ForceControlInterface::copyLogFilesFromControlToLocal start");
    
    // 解析命令参数：文件名列表和本地路径列表
    auto [filesName, localPaths] = BIND(cmd, std::vector<std::string>, std::vector<std::string>);
    
    int result = 0;
    QString msg;
    bool isSuccess = false;
    
    try
    {

        // 调用底层函数
        result = _IForceCtrl->ExportLogsFromCtrl(filesName, localPaths);
        
        if (result == ERR_OK)
        {
            isSuccess = true;
            msg = CommTr::tr("Successfully copied %1 log files from controller to local.").arg(filesName.size());
            LOG_INFO("ForceControlInterface::copyLogFilesFromControlToLocal: " + msg);
        }
        else
        {
            // 根据错误码设置相应的错误消息
            switch (result)
            {
                case -1:
                    msg = CommTr::tr("File list or path list is empty.");
                    break;
                case -2:
                    msg = CommTr::tr("File list and path list size mismatch.");
                    break;
                case -3:
                    msg = CommTr::tr("Controller is not connected.");
                    break;
                case -4:
                    msg = CommTr::tr("Force control log folder does not exist on controller.");
                    break;
                case -5:
                    msg = CommTr::tr("Failed to get remote file list.");
                    break;
                case -6:
                    msg = CommTr::tr("Force control log folder is empty on controller.");
                    break;
                case -99:
                    msg = CommTr::tr("Exception occurred while copying log files.");
                    break;
                default:
                    if (result > 100)
                    {
                        int failCount = result - 100;
                        int successCount = filesName.size() - failCount;
                        msg = CommTr::tr("Partially successful: %1 files copied, %2 files failed.").arg(successCount).arg(failCount);
                    }
                    else
                    {
                        msg = CommTr::tr("Failed to copy log files, error code: %1.").arg(result);
                    }
                    break;
            }
            LOG_WARN("ForceControlInterface::copyLogFilesFromControlToLocal: " + msg);
        }
    }
    catch (const std::exception& ex)
    {
        msg = CommTr::tr("Exception occurred while copying log files: %1").arg(QString::fromStdString(std::string(ex.what())));
        LOG_ERROR("ForceControlInterface::copyLogFilesFromControlToLocal Exception: " + QString::fromStdString(std::string(ex.what())));
        isSuccess = false;
    }
    
    // 发射结果信号
    emit CommunicationEngine::instance()->singal_copyLogFilesFromControlToLocal_result(cmd->m_object, isSuccess, msg);
    
    LOG_INFO("ForceControlInterface::copyLogFilesFromControlToLocal end. result=" + QString::number(result));
    FREQ_LOG_PRINT_TIMESTAMP
}


