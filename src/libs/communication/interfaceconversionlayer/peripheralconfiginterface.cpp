#include "peripheralconfiginterface.h"

#include "InoRobBusiness/Controller/Fieldbus/IOMap/IOMapDefault.h"
#include "InoRobBusiness/Controller/Fieldbus/IOMap/IIOMap.h"
#include "communication.h"

#include "communicationengine.h"
#include "InoRobBusiness/Controller/Peripheral/IndexConfig/IIndexConfig.h"
#include "cobotlogex.h"
#include "modulesutils.h"

bool PeripheralConfigInterface::getFieldbusIOMapDatas(QList<Ino_FieldbusIOMapData> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<InoRobBusiness::FieldbusIOMapData> values
        = _IFieldBus
              ->getIOMap()
              ->getFieldbusIOMapDatas();
    for (size_t i = 0; i < values.size(); ++i) {
        data.push_back(Ino_FieldbusIOMapData((Ino_IOType)values[i].ioType,
                                             values[i].funcId,
                                             values[i].memAddr,
                                             (Ino_MemoryLength)values[i].length,
                                             QString::fromStdString(values[i].name)));
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool PeripheralConfigInterface::refreshFieldbusFromControllerDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
            ->getIOMap()
        ->refreshFieldbusIOMap();
}

bool PeripheralConfigInterface::getSwitchEnableStatus(
    bool &ethernetipEnable, bool &ethercatEnable)
{
    // Modbus状态
    ModbusConnectSts modbusConnectSts;
    int nRet = _IFieldBus->getModbusSwitch()->readModbusConnStatus(modbusConnectSts);
    if (nRet != ERR_OK) {
        return false;
    }
    int modbusAddrType = modbusConnectSts.ModbusAddrType;  // 总线地址类型

    // 总线安装标志
    char filedBusInstallType[4];
    _IMonitor->GetBusInstall(filedBusInstallType);

    // EtherCAT第一个字节的第 0 位
    bool isHasEthercat = (filedBusInstallType[0] >> 0) & 0x01;
    if (isHasEthercat) {
        if (modbusAddrType == NEW_MODBUS_VISION) {
            // 新版
            ethercatEnable = true;
        } else {
            // 旧版
            ethercatEnable = false;
        }
    } else {
        ethercatEnable = false;
    }

    // 判断EthernetIP和Profinet
    if (modbusAddrType == NEW_MODBUS_VISION) {
        // 新版
        ethernetipEnable = true;
    } else {
        // 旧版
        ethernetipEnable = false;
    }
    return true;
}

bool PeripheralConfigInterface::resetFieldbusIOMap(Ino_IOMapResetMethod method)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
        ->getIOMap()
        ->resetFieldbusIOMap((InoRobBusiness::IOMapResetMethod)method);
}

bool PeripheralConfigInterface::importIOMappingFile(const QString &fileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
        ->getIOMap()
        ->importFieldbusIoMapFromFile(fileName.toStdString());
}

bool PeripheralConfigInterface::exportIOMappingFile(const QString &fileName)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IFieldBus
        ->getIOMap()
        ->exportFieldbusIOMapToFile(fileName.toStdString());
}

bool PeripheralConfigInterface::saveIOMappingData(
    const QVector<Ino_FieldbusIOMapData> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::vector<InoRobBusiness::FieldbusIOMapData> values;
    for (int i = 0; i < data.size(); ++i) {
        values.push_back(InoRobBusiness::FieldbusIOMapData(
            (InoRobBusiness::IOType)data[i].ioType,
            data[i].funcId,
            data[i].memAddr,
            (InoRobBusiness::MemoryLength)data[i].length,
            data[i].name.toStdString()));
    }
    return _IFieldBus
        ->getIOMap()
        ->saveFieldbusIOMap(values);
}

void PeripheralConfigInterface::saveIOMappingRemarks(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [datas] = ((CmdDatas<QVector<Ino_FieldbusIOMapData>> *)cmd)->m_data;
    std::string name;
    int re = comm()->project()->getActiveProject(name);
    std::string suffix = comm()->project()->ProgramFileExtension();
    // 函数返回值为ERR_OK，及获取到string不为空代表有激活的工程
    if (re != ERR_OK || name.empty() || suffix  == "pro"){
        emit CommunicationEngine::instance()->
            signal_needMainWidgetWarning(QObject::tr(
            "No active project available. Please load a project and save it before attempting this operation."));
        return;
    }

    ILabel *lable =  comm()->project()->GetLabel();
    int size = datas.size();
    int modify = InoRobUtil::OK;
    for (int i = 0; i < size; i++)
    {
        if (datas[i].memAddr >= 0)
        {
            if (datas[i].ioType == Ino_IOType::IOTP_IN)
            {
                if (datas[i].length == Ino_MemoryLength::ML_BIT)
                {
                    lable->removeDescription(LabelType::IO_INPUT_BIT, datas[i].name.toStdString());
                    modify =  lable->ModifyItemDescription(LabelType::IO_INPUT_BIT, datas[i].memAddr, datas[i].name.toStdString());
                    if(modify != InoRobUtil::OK){
                        break;
                    }
                }
                else if (datas[i].length == Ino_MemoryLength::ML_WORD)
                {
                    lable->removeDescription(LabelType::IO_INPUT_WORD, datas[i].name.toStdString());
                    modify =  lable->ModifyItemDescription(LabelType::IO_INPUT_WORD, datas[i].memAddr / 16, datas[i].name.toStdString());
                    if(modify != InoRobUtil::OK){
                        break;
                    }
                }
            }
            else if (datas[i].ioType == Ino_IOType::IOTP_OUT)
            {
                if (datas[i].length == Ino_MemoryLength::ML_BIT)
                {
                    lable->removeDescription(LabelType::IO_OUTPUT_BIT, datas[i].name.toStdString());
                    modify =  lable->ModifyItemDescription(LabelType::IO_OUTPUT_BIT, datas[i].memAddr, datas[i].name.toStdString());
                    if(modify != InoRobUtil::OK){
                        break;
                    }
                }
                else if (datas[i].length == Ino_MemoryLength::ML_WORD)
                {
                    lable->removeDescription(LabelType::IO_OUTPUT_WORD, datas[i].name.toStdString());
                    modify =  lable->ModifyItemDescription(LabelType::IO_OUTPUT_WORD, datas[i].memAddr / 16, datas[i].name.toStdString());
                    if(modify != InoRobUtil::OK){
                        break;
                    }
                }
            }
        }
    }
    if(modify == InoRobUtil::OK){
        modify = lable->SaveLabels();
        if(modify == InoRobUtil::OK){
            emit CommunicationEngine::instance()
                ->signal_IOMapping_cmd_result(cmd->m_cmdType, true);
            emit CommunicationEngine::instance()->
                signal_needMainWidgetInfo(QObject::tr("Description synchronized to the current project successfully."));
        }else{
            emit CommunicationEngine::instance()->
                signal_needMainWidgetWarning(QObject::tr("Failed to save the description."));
        }
    }else{
        emit CommunicationEngine::instance()->
            signal_needMainWidgetWarning(QObject::tr("Failed to modify the description."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}


