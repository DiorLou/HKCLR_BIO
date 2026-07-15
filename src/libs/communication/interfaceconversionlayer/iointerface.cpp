#include "iointerface.h"
#include <QDebug>
#include "communication.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "IController.h"
#include "communicationengine.h"
#include "cobotlog.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "cobotlog.h"
#include <QJsonArray>
#include "templateutils.h"

#include "cobotlogex.h"
#include "modulesutils.h"
// 示教器2.0
#pragma region "comment" {in
//
static InoRobBusiness::IResource::IOType convertTypeToInoRobtbussiness(InoIOType ioType)
{
    switch (ioType) {
    case InoIOType_CommonIO: return InoRobBusiness::IResource::IOType::COMMON_IO;
    case InoIOType_StandardIO: return InoRobBusiness::IResource::IOType::STANDARD_IO;
    case InoIOType_FieldbusIO: return InoRobBusiness::IResource::IOType::SLAVE_FIELDBUS_IO;
    case InoIOType_MemoryIO: return InoRobBusiness::IResource::IOType::MEMORY_IO;
    case InoIOType_ToolIO: return InoRobBusiness::IResource::IOType::TOOL_IO;
    default: return InoRobBusiness::IResource::IOType::COMMON_IO;
    }
    return InoRobBusiness::IResource::IOType::COMMON_IO;
}

void IOInterface::getInputControlAuthority(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int standardSize = 0, fieldBusSize = 256;  // standardSize bit  fieldBusSize byte
    standardSize = _IMonitor->GetInputNum();
    FIELDBUS_MEM_ASSIGN_CONFIG memAsgnCfg;
    int fieldbusType = 0;
    InoRobBusiness::IFieldbus *fieldBus = _IFieldBus;
    int ret = fieldBus->readMemoryAssignConfig(memAsgnCfg);
    if (ret != ERR_OK) {
        emit MWARNING(QObject::tr("Failed to get I/O control configuration."));
    } else {
        if (fieldBus->getCurFieldBusType(fieldbusType) != ERR_OK)
            emit MWARNING(QObject::tr("Failed to get fieldbus I/O."));
        else {
            fieldbusType = (E_FieldBusType)fieldbusType;
            // 根据当前激活的总线类型，执行对应的赋值
            switch (fieldbusType) {
            case E_FieldBusType::FB_Unknow:
                break;
            case E_FieldBusType::FB_Modbus:
                fieldBusSize = memAsgnCfg.modbusConfig.inputSize;
                break;
            case E_FieldBusType::FB_EthernetIp:
                fieldBusSize = memAsgnCfg.eipConfig.inputSize;
                break;
            case E_FieldBusType::FB_EtherCATSlave:
                fieldBusSize = memAsgnCfg.etherCATConfig.inputSize;
                break;
            case E_FieldBusType::FB_FINS:
                break;
            case E_FieldBusType::FB_MC: {
                McConnectPara mcPara[InoRobBusiness::MAX_MC_NUM];
                InoRobBusiness::IMCSwitch *pMCSwitch = fieldBus->getMCSwitch();
                if (pMCSwitch == nullptr)
                    break;
                // 读取所有MC的连接状态
                int ret = pMCSwitch->readAllMcConnectSts(mcPara);
                if (ret != ERR_OK) {
                    emit MWARNING(QObject::tr("Failed to get MC configuration."));
                    break;
                }
                // 单位为字，转换为Byte，需要乘以2。先默认赋值第一个MC的
                fieldBusSize = memAsgnCfg.mcConfig[0].mcInputRegSize * 2;
                // 遍历哪个激活了，则对应进行赋值
                for (int i = 0; i < InoRobBusiness::MAX_MC_NUM; i++) {
                    if (mcPara[i].ConnectFlag == 1) {
                        fieldBusSize = memAsgnCfg.mcConfig[i].mcInputRegSize * 2;
                    }
                }
                break;
            }
            default:
                break;
            }
            emit CommunicationEngine::instance()->signal_getDigitalInputControlAuthority(cmd->m_object, standardSize, fieldBusSize * 8);
        }
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::getOutputControlAuthority(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    int startByteId, byteSize;
    std::vector<unsigned char> standardControl(STANDARD_IO_SIZE, 0);
    startByteId = STANDARD_IO_STARTINDEX;
    byteSize = STANDARD_IO_SIZE;
    InoRobBusiness::IResource *resource = _IResource;
    int ret = resource->readOutputControls(startByteId, byteSize, standardControl);
    if (ret != ERROR_OK)
        return;

    std::vector<unsigned char> fiedlBusControl(SLAVE_FIELDBUS_IO_SIZE, 0);
    startByteId = SLAVE_FIELDBUS_IO_STARTINDEX;
    byteSize = SLAVE_FIELDBUS_IO_SIZE;
    ret = resource->readOutputControls(startByteId, byteSize, fiedlBusControl);
    if (ret != ERROR_OK)
        return;

    std::vector<unsigned char> memoryControl(MEMORY_IO_SIZE, 0);
    startByteId = MEMORY_IO_STARTINDEX;
    byteSize = MEMORY_IO_SIZE;
    ret = resource->readOutputControls(startByteId, byteSize, memoryControl);
    if (ret != ERROR_OK)
        return;

    int standardSize = _IMonitor->GetOutputNum();
    int fieldBusSize = 256;
    FIELDBUS_MEM_ASSIGN_CONFIG memAsgnCfg;
    InoRobBusiness::IFieldbus *fieldBus = _IFieldBus;
    ret = fieldBus->readMemoryAssignConfig(memAsgnCfg);
    if (ret != ERROR_OK)
        return;
    int fieldbusType = 0;  // 单位是byte
    if (fieldBus->getCurFieldBusType(fieldbusType) == ERR_OK)
        fieldbusType = (E_FieldBusType)fieldbusType;

    switch (fieldbusType) {
    case E_FieldBusType::FB_Unknow:
        break;
    case E_FieldBusType::FB_Modbus:
        fieldBusSize = memAsgnCfg.modbusConfig.outputSize;
        break;
    case E_FieldBusType::FB_EthernetIp:
        fieldBusSize = memAsgnCfg.eipConfig.outputSize;
        break;
    case E_FieldBusType::FB_EtherCATSlave:
        fieldBusSize = memAsgnCfg.etherCATConfig.outputSize;
        break;
    case E_FieldBusType::FB_FINS:
        break;
    case E_FieldBusType::FB_MC: {
        McConnectPara mcPara[InoRobBusiness::MAX_MC_NUM];
        InoRobBusiness::IMCSwitch *pMCSwitch = fieldBus->getMCSwitch();
        if (pMCSwitch == nullptr)
            break;
        // 读取所有MC的连接状态
        int ret = pMCSwitch->readAllMcConnectSts(mcPara);
        if (ret != ERR_OK) {
            LOG_ERROR(QObject::tr("Failed to get MC connection status."));
            return;
        }
        // 单位为字，转换为Byte，需要乘以2。先默认赋值第一个MC的
        fieldBusSize = memAsgnCfg.mcConfig[0].mcOutputRegSize * 2;
        // 遍历哪个激活了，则对应进行赋值
        for (int i = 0; i < InoRobBusiness::MAX_MC_NUM; i++) {
            if (mcPara[i].ConnectFlag == 1) {
                fieldBusSize = memAsgnCfg.mcConfig[i].mcOutputRegSize * 2;
            }
        }
        break;
    }
    default:
        break;
    }
    emit CommunicationEngine::instance()->signal_getDigitalOutputControlAuthority(
        cmd->m_object,
        standardSize,
        fieldBusSize * 8,
        QList<quint8>(standardControl.begin(), standardControl.end()),
        QList<quint8>(fiedlBusControl.begin(), fiedlBusControl.end()),
        QList<quint8>(memoryControl.begin(), memoryControl.end()));
    FREQ_LOG_PRINT_TIMESTAMP
}

// in fieldbus
bool IOInterface::getInputValuesFieldbus(QList<quint8> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateFieldbusInputDatas())
        return false;
    std::array<int8u, FIELDBUS_IO_COUNT> fieldbusInputValues
        = _IResource->getSlaveFieldbusInputValues();
    data = QList<quint8>(fieldbusInputValues.begin(), fieldbusInputValues.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

// out fieldbus
bool IOInterface::getOutputValuesFieldbus(QList<quint8> &src)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateFieldbusOutputDatas())
        return false;
    std::array<int8u, FIELDBUS_IO_COUNT> fieldbusOutputValues
        = _IResource
              ->getSlaveFieldbusOutputValues();
    src = QList<quint8>(fieldbusOutputValues.begin(),
                        fieldbusOutputValues.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
// in 设置当前显示IO类型 (常用 标准 总线 内存) 通知模型层刷新对应类型数据
void IOInterface::setInputIOType(InoIOType ioType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setInputIOType(
        convertTypeToInoRobtbussiness(ioType));
    FREQ_LOG_PRINT_TIMESTAMP
}
// in 设置当前显示IO单位 (bit bytes word)
void IOInterface::setInputShowType(const ShowType &showType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setInputShowType(
        static_cast<InoRobBusiness::IResource::ShowType>(showType));
    FREQ_LOG_PRINT_TIMESTAMP
}

// in 前面是高位 后面是低位
bool IOInterface::getInputForceValuesStandard(QList<quint8> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::array<int8u, STANDARD_IO_COUNT> fhDatas
        = _IResource->getStandardInputForceHighValues();
    std::array<int8u, STANDARD_IO_COUNT> flDatas
        = _IResource->getStandardInputForceLowValues();
    data = QList<quint8>(fhDatas.begin(), fhDatas.end());
    data.append(QList<quint8>(flDatas.begin(), flDatas.end()));
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

// in standard
bool IOInterface::getInputValuesStandard(QList<quint8> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateStandardInputDatas())
        return false;
    std::array<int8u, STANDARD_IO_COUNT> standardInputValues
        = _IResource
              ->getStandardInputValues();
    std::array<int8u, STANDARD_IO_COUNT> fhDatas
        = _IResource
              ->getStandardInputForceHighValues();
    std::array<int8u, STANDARD_IO_COUNT> flDatas
        = _IResource
              ->getStandardInputForceLowValues();
    data = QList<quint8>(standardInputValues.begin(), standardInputValues.end());
    data.append(QList<quint8>(fhDatas.begin(), fhDatas.end()));
    data.append(QList<quint8>(flDatas.begin(), flDatas.end()));

    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
// in Memory
bool IOInterface::getInputValuesMemory(QList<quint8> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateMemoryInputDatas())
        return false;
    std::array<int8u, MEMORY_IO_COUNT> memoryInputValues
        = _IResource
              ->getMemoryInputValues();
    data = QList<quint8>(memoryInputValues.begin(), memoryInputValues.end());
    return true;
}

// in Common 刷新
bool IOInterface::updateCommonInputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateCommonInputDatas();
}

// in Standard 刷新
bool IOInterface::updateStandardInputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateStandardInputDatas();
}

// in Memory 刷新
bool IOInterface::updateMemoryInputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateMemoryInputDatas();
}

// in 写强制状态
bool IOInterface::writeInputStatusForce(const int index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool ret = _IResource->setStandardInputForceStatus(index);
    FREQ_LOG_PRINT_TIMESTAMP
    // if(ret)
    //     return updateStandardInputDatas();
    return ret;
}

// in
void IOInterface::setSchedulerInput(bool scheduler)
{
    // _IResource->setInputScheduler(scheduler);
}

// in  Fieldbus 刷新
bool IOInterface::updateFieldbusInputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateSlaveFieldbusInputDatas();
}

bool IOInterface::writeInputStatusByBit(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD
    InoRobBusiness::IResource *resource = _IResource;
    auto [bitIndex, value_, high, low] = BIND(cmd, int, quint8, quint8, quint8);
    quint16 byteIndex = bitIndex / 8;
    quint8 bitIndexInByte = bitIndex % 8;
    quint8 temp = 0x01 << bitIndexInByte;
    bool bitValue = value_ & temp;
    if (bitIndex < (STANDARD_IO_START_INDEX + STANDARD_IO_COUNT + TOOL_IO_COUNT) * 8) {
        bool fh = high & temp;
        bool fl = low & temp;
        if ((fh && !fl) || (!fh && fl))  // 强制高、低才写
        {
            if (fh) {
                high &= (~temp);
                low |= temp;
            } else {
                low &= (~temp);  // 将bitIndex位置0，其他位不变
                high |= temp;    // 将bitIndex位置1，其他位不变
            }
        } else {
            return false;
        }
        std::vector<unsigned char> arraryH, arraryL;
        arraryH.push_back(high);
        arraryL.push_back(low);
        int ret1 = resource->writeInputForceHighStatus(byteIndex, 1, arraryH);
        int ret2 = resource->writeInputForceLowStatus(byteIndex, 1, arraryL);
    } else {
        bool ret = _IResource->setMemoryInputStatus(bitIndex - MEMORY_IO_START_INDEX * 8, !bitValue);
        return false;
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return false;
}

bool IOInterface::writeInputStatusForce(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    InoRobBusiness::IResource *resource = _IResource;
    auto [bitIndex, value_, high_, low_] = BIND(cmd, int, quint8, quint8, quint8);
    quint8 high = high_, low = low_;
    if (bitIndex < (STANDARD_IO_START_INDEX + STANDARD_IO_COUNT + TOOL_IO_COUNT) * 8) {
        quint16 byteIndex = bitIndex / 8;
        quint8 bitIndexInByte = bitIndex % 8;
        quint8 temp = 0x01 << bitIndexInByte;
        bool bitState = value_ & (0x01 << bitIndexInByte);
        bool fh = high & temp;
        bool fl = low & temp;
        if (!fh && !fl) {
            if (bitState) {
                high |= temp;
                low &= (~temp);
            } else {
                high &= (~temp);
                low |= temp;
            }
        } else if ((fh && !fl) || (!fh && fl))  // 强制 => 不强制
        {
            // 强制高、强制低都置0、io位置off
            high &= (~temp);
            low &= (~temp);
        } else {
            return false;
        }
        std::vector<int8u> arraryH, arraryL;
        arraryH.push_back(high);
        arraryL.push_back(low);
        int ret1 = resource->writeInputForceHighStatus(byteIndex, 1, arraryH);
        int ret2 = resource->writeInputForceLowStatus(byteIndex, 1, arraryL);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

// in 写输入状态
bool IOInterface::writeInputStatusByBit(const int bitIndex, const bool bitValue)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (bitIndex < (STANDARD_IO_START_INDEX + STANDARD_IO_COUNT) * 8) {
        bool ret = _IResource->setStandardInputStatus(bitIndex);
        if (ret)
            return updateStandardInputDatas();
    } else if (bitIndex < (TOOL_IO_START_INDEX + TOOL_IO_COUNT) * 8) {
    } else {
        bool ret = _IResource->setMemoryInputStatus(bitIndex - MEMORY_IO_START_INDEX * 8, bitValue);
        if (ret)
            return updateMemoryInputDatas();
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return false;
}

bool IOInterface::getCommonInputIndexs(QList<unsigned short> &index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    vector<unsigned short> source = _IResource->getCommonInputIndexs();
    index = QList<unsigned short>(source.begin(), source.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool IOInterface::getCommonInputValues(QList<quint8> &values)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    vector<int8u> data = _IResource->getCommonInputValues();
    values = QList<quint8>(data.begin(), data.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool IOInterface::getCommonOutputIndexs(QList<unsigned short> &index)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    vector<unsigned short> source = _IResource->getCommonOutputIndexs();
    index = QList<unsigned short>(source.begin(), source.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool IOInterface::getCommonOutputValues(QList<quint8> &values)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    vector<int8u> data = _IResource->getCommonOutputValues();
    values = QList<quint8>(data.begin(), data.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
#pragma endregion }

#pragma region "comment" {out
// out
// out Memory
bool IOInterface::getOutputValuesMemory(QList<quint8> &src)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateMemoryOutputDatas())
        return false;
    std::array<int8u, MEMORY_IO_COUNT> memoryOutputValues
        = _IResource
              ->getMemoryOutputValues();
    src = QList<quint8>(memoryOutputValues.begin(), memoryOutputValues.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

// out label and remark
bool IOInterface::getOutputLabelAndRemarkForCurrentShow(QVector<InoLabelItem> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool ret = _IResource
                   ->updateOutputLabelAndRemark();
    if (!ret)
        return false;
    IoLabelItems items = _IResource
                             ->getOutputLabelAndRemark();
    data.clear();
    for (int i = 0; i < items.LabelsArray.size(); ++i) {
        InoLabelItem item;
        item.nLabelId = items.LabelsArray[i].nLabelId;
        item.nIndex = items.LabelsArray[i].nIndex;
        item.sLabel = QString::fromStdString(items.LabelsArray[i].sLabel);
        item.sDescription = QString::fromStdString(items.LabelsArray[i].sDescription);
        item.sOriginalName = QString::fromStdString(items.LabelsArray[i].sOriginalName);
        data.push_back(item);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
bool IOInterface::getInputLabelAndRemarkForCurrentShow(QVector<InoLabelItem> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool ret = _IResource
                   ->updateInputLabelAndRemark();
    if (!ret)
        return false;
    IoLabelItems items = _IResource
                             ->getInputLabelAndRemark();
    data.clear();
    for (int i = 0; i < items.LabelsArray.size(); ++i) {
        InoLabelItem item;
        item.nLabelId = items.LabelsArray[i].nLabelId;
        item.nIndex = items.LabelsArray[i].nIndex;
        item.sLabel = QString::fromStdString(items.LabelsArray[i].sLabel);
        item.sDescription = QString::fromStdString(items.LabelsArray[i].sDescription);
        item.sOriginalName = QString::fromStdString(items.LabelsArray[i].sOriginalName);
        data.push_back(item);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
void IOInterface::setOutputIOType(InoIOType ioType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setOutputIOType(
        convertTypeToInoRobtbussiness(ioType));
    FREQ_LOG_PRINT_TIMESTAMP
}

// out
void IOInterface::setOutputShowType(const ShowType &showType)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->setOutputShowType(
        static_cast<InoRobBusiness::IResource::ShowType>(showType));
    FREQ_LOG_PRINT_TIMESTAMP
}

// out standard
bool IOInterface::getOutputValuesStandard(QList<quint8> &src)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    if (!updateStandardOutputDatas())
        return false;
    src.clear();

#ifdef INOCOBOTTP_MSVC_QT5
    for (int i = 0; i < STANDARD_IO_COUNT; ++i) {
        src.append(0);
    }
#else
    src.resize(STANDARD_IO_COUNT);
#endif

    std::array<int8u, STANDARD_IO_COUNT> standardOutputValues
        = _IResource
              ->getStandardOutputValues();
    src = QList<quint8>(standardOutputValues.begin(),
                        standardOutputValues.end());
    FREQ_LOG_PRINT_TIMESTAMP
    // 该通讯码无错误处理
    return true;
}

// out Common 刷新
bool IOInterface::updateCommonOutputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateCommonOutputDatas();
}

// out Standard 刷新
bool IOInterface::updateStandardOutputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateStandardOutputValues();
}

// out  Fieldbus 刷新
bool IOInterface::updateFieldbusOutputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateSlaveFieldbusOutputValues();
}

// out Memory 刷新
bool IOInterface::updateMemoryOutputDatas()
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    return _IResource->updateMemoryOutputValues();
}

// OUT 写输出状态
void IOInterface::writeOutputStatusByBit(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [uiRow, realIndex, bitValue] = BIND(cmd, int, int, bool);
    if (realIndex < STANDARD_IO_STARTINDEX + STANDARD_IO_SIZE * 8)
        setOutputIOType(InoIOType_StandardIO);
    else if (realIndex < (TOOL_IO_STARTINDEX + TOOL_IO_SIZE) * 8) {
        _IResource->writeOutputStatusByBit(realIndex, bitValue);
        return;
    } else if (realIndex < (SLAVE_FIELDBUS_IO_STARTINDEX + SLAVE_FIELDBUS_IO_SIZE) * 8)
        setOutputIOType(InoIOType_FieldbusIO);
    else
        setOutputIOType(InoIOType_MemoryIO);
    qDebug() << uiRow << realIndex << bitValue << "writeOutputStatusByBit";
    _IResource->setOutputStatus(uiRow, realIndex, bitValue);
    FREQ_LOG_PRINT_TIMESTAMP
}

// out
void IOInterface::setSchedulerOutput(bool scheduler)
{
    // _IResource->setOutputScheduler(scheduler);
}
#pragma endregion }

#pragma region "comment" {ad
void IOInterface::setSchedulerAD(const bool scheduler)
{
    // _IResource->setADScheduler(scheduler);
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::setSchedulerDA(const bool scheduler)
{
    // _IResource->setDAScheduler(scheduler);
    FREQ_LOG_PRINT_TIMESTAMP
}

bool IOInterface::getDatasAD(QList<Ino_AD_DA_Data> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    bool ret = _IResource->updateIRLinkADDatas();
    if (!ret)
        return false;
    std::vector<InoRobBusiness::IRLinkADDAData> value = _IResource->getIRLinkADDatas();
    for (size_t i = 0; i < value.size(); ++i) {
        Ino_AD_DA_Data temp;
        temp.labs = QString::fromStdString(value[i].labs);
        temp.remarks = QString::fromStdString(value[i].remarks);
        temp.status.favorite = value[i].status.favorite;
        temp.status.kind = value[i].status.kind;
        temp.status.minValue = value[i].status.minValue;
        temp.status.maxValue = value[i].status.maxValue;
        temp.status.actualValue = value[i].status.actualValue;
        temp.status.out = value[i].status.out;
        data.push_back(temp);
    }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

Ino_Cobot_ADDA_Data ConvertBussinessCobot_ADDA_DataToCommunication(const InoRobBusiness::Cobot_ADDA_Data &data)
{
    Ino_Cobot_ADDA_Data temp;
    temp.labs = QString::fromStdString(data.labs);
    temp.remarks = QString::fromStdString(data.remarks);
    temp.status.type = data.status.type;
    temp.status.index = data.status.index;
    temp.status.setModelEnable = data.status.setModelEnable;
    temp.status.currentConfigState = data.status.currentConfigState;
    temp.status.deviceType = data.status.deviceType;
    temp.status.kind = data.status.kind;
    temp.status.minValue = data.status.minValue;
    temp.status.maxValue = data.status.maxValue;
    temp.status.actualValue = data.status.actualValue;
    temp.status.out = data.status.out;
    return temp;
}

void IOInterface::getCobotDatasADDA(AbstractCmd *cmd)
{
    // readCobotAnalogIODatas
    auto [state, data] = BIND(cmd, Ino_Cobot_ADDA_type, QList<Ino_Cobot_ADDA_Data> *);
    std::vector<InoRobBusiness::Cobot_ADDA_Data> src;
    int ret = _IResource->readCobotAnalogIODatas(state == Ino_Cobot_ADDA_type_DA, src);
    if (ret != ERROR_OK)
        return;
    QList<int> index;
    QList<Ino_Cobot_ADDA_Data> all;
    QList<Ino_Cobot_ADDA_Data> different;
    int size = src.size();
    for (int i = 0; i < size; ++i) {
        all.push_back(ConvertBussinessCobot_ADDA_DataToCommunication(src[i]));
        // qDebug()<<i<<all[i].status.kind;
    }
    if (data->size() != size) {
        for (int i = 0; i < size; ++i) {
            index.push_back(i);
        }
        emit CommunicationEngine::instance()->signal_Cobot_ADDA_getDatas_result(cmd->m_object, true, index, all);
        return;
    }

    if (compareAndObtainDifferentDatas((*data), all, index, different)) {
        emit CommunicationEngine::instance()->signal_Cobot_ADDA_getDatas_result(cmd->m_object, false, index, different);
        return;
    }
    return;
}

void IOInterface::setCobotDatasADDA(AbstractCmd *cmd)
{
    auto [data] = ((CmdDatas<Ino_Cobot_ADDA_Data> *)cmd)->m_data;
    InoRobBusiness::Cobot_ADDA_Status temp;
    temp.actualValue = data.status.actualValue;
    temp.index = data.status.index;
    temp.kind = data.status.kind;
    temp.type = data.status.type;
    temp.out = data.status.out;
    int ret = _IResource->writeCobotAnalogIODatas(temp);
    if (ret != ERROR_OK) {
        emit MWARNING("Set AD/DA datas falid!");
    } else {
        PRINT_MSG(CommTr::tr("AD/DA config information sent."));
    }
    return;
}

bool IOInterface::getDatasDA(QList<Ino_AD_DA_Data> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // bool ret = _IResource->updateIRLinkDADatas();
    // if (!ret)
    //     return false;
    // std::vector<InoRobBusiness::IRLinkADDAData> value = _IResource->getIRLinkDADatas();
    // for (size_t i = 0; i < value.size(); ++i) {
    //     Ino_AD_DA_Data temp;
    //     temp.labs = QString::fromStdString(value[i].labs);
    //     temp.remarks = QString::fromStdString(value[i].remarks);
    //     temp.status.favorite = value[i].status.favorite;
    //     temp.status.kind = value[i].status.kind;
    //     temp.status.minValue = value[i].status.minValue;
    //     temp.status.maxValue = value[i].status.maxValue;
    //     temp.status.actualValue = value[i].status.actualValue;
    //     temp.status.out = value[i].status.out;
    //     data.push_back(temp);
    // }
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}
bool IOInterface::setDataDA(const int index,
                            const int flag,
                            const Ino_AD_DA_Data &value)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    // InoRobBusiness::IRLinkADDAData temp;
    // temp.favorite = value.status.favorite;
    // temp.kind = value.status.kind;
    // temp.minValue = value.status.minValue;
    // temp.maxValue = value.status.maxValue;
    // temp.actualValue = value.status.actualValue;
    // temp.out = value.status.out;
    // int ret = _IResource->writeDAValue(index, flag, temp);
    // FREQ_LOG_PRINT_TIMESTAMP
    // if (ret == ERR_OK)
    //     return true;
    return false;
}
#pragma endregion

bool IOInterface::getDatasSystemIn(QList<bool> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->updateSysInputDatas();
    std::array<bool, SYSIO_SIZE> value = _IResource->getSysInputStatus();
    data = QList<bool>(value.begin(), value.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool IOInterface::getDatasSystemOut(QList<bool> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->updateSysOutputDatas();
    std::array<bool, SYSIO_SIZE> value = _IResource->getSysOutputStatus();
    data = QList<bool>(value.begin(), value.end());
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

void IOInterface::setSchedulerSysInput(const bool scheduler)
{
    // _IResource->setSysInputScheduler(scheduler);
}

void IOInterface::setSchedulerSysOutput(const bool scheduler)
{
    // _IResource->setSysOutputScheduler(scheduler);
}

bool IOInterface::getSysInputRemark(QStringList &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->updateSysInputDatas();
    std::array<std::string, SYSIO_SIZE> remark = _IResource->getSysInputRemarks();
    foreach (auto &str, remark) {
        data.push_back(QString::fromStdString(str));
    };
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

bool IOInterface::getSysOutputRemark(QStringList &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->updateSysOutputDatas();
    std::array<std::string, SYSIO_SIZE> remark = _IResource->getSysOutputRemarks();
    foreach (auto &str, remark) {
        data.push_back(QString::fromStdString(str));
    };
    FREQ_LOG_PRINT_TIMESTAMP
    return true;
}

#if defined(INOCOBOTTP_MSVC_QT5)
bool IOInterface::getSysOutputRemarkList(QList<QString> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    _IResource->updateSysOutputDatas();
    std::array<std::string, SYSIO_SIZE> remark = _IResource->getSysOutputRemarks();
    foreach (auto &str, remark) {
        data.push_back(QString::fromStdString(str));
    };
    FREQ_LOG_PRINT_TIMESTAMP
        return true;
}

bool IOInterface::getSysInputRemarkList(QList<QString> &data)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

            _IResource->updateSysInputDatas();
    std::array<std::string, SYSIO_SIZE> remark = _IResource->getSysInputRemarks();
    foreach (auto &str, remark) {
        data.push_back(QString::fromStdString(str));
    };
    FREQ_LOG_PRINT_TIMESTAMP
        return true;
}
#endif


void IOInterface::readToolIOConfig(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    std::string ans;
    int ret = _IResource->readToolIoConfig(ans);
    // int ret = 1;
    if (ret != ERROR_OK) {
        PRINT_ERROR(QObject::tr("Failed to read tool I/O configuration."));
    }
    QJsonObject jsonObj = QJsonDocument::fromJson(ans.c_str()).object();
    QStringList parents;
    QList<QList<ToolIOConfigContent>> chlids;
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        parents.push_back(it.key());
        chlids << QList<ToolIOConfigContent>();
        QJsonArray arrarys = it.value().toArray();
        for (int i = 0; i < arrarys.size(); ++i) {
            QJsonObject childObj = arrarys[i].toObject();
            ToolIOConfigContent childContent;
            childContent.name = childObj.value("name").toString();
            childContent.index = childObj.value("index").toInt();
            childContent.subIndex = childObj.value("subindex").toInt();
            childContent.describe = childObj.value("describe").toString();
            childContent.valueType = childObj.value("valueType").toInt();
            childContent.rangeType = childObj.value("rangeType").toInt();
            childContent.valueDecimals = childObj.value("vaueDecimals").toInt();
            childContent.permission = childObj.value("permission").toInt();
            childContent.value = childObj.value("value");
            if (childContent.valueType != ToolIOConfigContent::ContinutyDouble) {
                childContent.valueDecimals = 0;
            }
            QJsonArray rangeArrary = childObj.value("valueRange").toArray();
            for (int j = 0; j < rangeArrary.size(); ++j) {
                childContent.valueRange << rangeArrary[j].toString();
            }
            chlids[chlids.size() - 1] << childContent;
        }
    }

    emit CommunicationEngine::instance()->signal_getToolIOConfigResulte(absCmd->m_object, parents, chlids);
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::writeToolIOConfig(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [group, index, subIndex, valueType, value] = ((CmdDatas<QString, int, int, int, QString> *)absCmd)->m_data;

    QJsonObject childJson;
    // childJson["group"] = group;
    childJson["index"] = index;
    childJson["subIndex"] = subIndex;
    if (valueType == ToolIOConfigContent::ContinutyDouble)
        childJson["value"] = value.toDouble();
    else
        childJson["value"] = value.toInt();

    QJsonArray arrary;
    arrary.append(childJson);

    QJsonObject parentJson;
    parentJson[group] = arrary;

    QJsonDocument jsonDocument(parentJson);
    std::string content = jsonDocument.toJson(QJsonDocument::Compact).toStdString();
    int ret = _IResource->writeToolIoConfig(content);
    if (ret == ERR_OK) {
        PRINT_MSG(QObject::tr("Tool I/O configuration sent successfully."));
    } else if (ret == ERR_CMD_ACTION_FAILED) {
        emit MWARNING(QObject::tr("Failed to send configuration to tool MCU."));
    } else {
        QString first = QString::number(index, 16).toUpper();
        QString second = QString::number(subIndex, 16).toUpper();
        QString ans = "H";
        if (first.size() >= 2 && second.size() <= 2) {
            ans += first.mid(first.size() - 2, 2) + "." + (second.size() == 2 ? second : "0" + second);
        } else {
            ans += first + "." + second;
        }
        emit MWARNING(QObject::tr("Failed to set tool I/O configuration. Group: %1, ID: %2").arg(group, ans));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::setToolIOConfigMonitorState(AbstractCmd *absCmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

    auto [state] = ((CmdDatas<bool> *)absCmd)->m_data;
    int ret = _IResource->setToolIOConfigMonitorState(state);
    // int ret = 1;
    if (ret != ERROR_OK)
        emit MWARNING(QObject::tr("Failed to set monitoring status of tool I/O. "));
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::getOutputValuesTool(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

#ifdef INOCOBOTTP_MSVC_QT5
        QList<quint8> data;
    for (int i = 0; i < TOOL_IO_SIZE; ++i) {
        data.append(0);
    }
#else
        QList<quint8> data(TOOL_IO_SIZE);
#endif
    int ret = _IResource->readOutputStatus(TOOL_IO_STARTINDEX, TOOL_IO_SIZE, &data[0]);
    if (ret == ERROR_OK) {
        auto [address] = ((CmdDatas<QList<quint8> *> *)cmd)->m_data;
        QList<int> index;
        QList<quint8> different;
        if (compareAndObtainDifferentDatas(*address, data, index, different)) {
            emit CommunicationEngine::instance()->signal_output_getDatas_result(InoIOType_ToolIO, index, different);
        }
    } else {
        PRINT_ERROR(QObject::tr("Failed to read tool DO status."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::getInputValuesTool(AbstractCmd *cmd)
{
    FREQ_LOG_PRINT_TIMESTAMP_THREAD

#ifdef INOCOBOTTP_MSVC_QT5
    QList<quint8> data;
    for (int i = 0; i < TOOL_IO_SIZE * 3; ++i) {
        data.append(0);
    }
#else
    QList<quint8> data(TOOL_IO_SIZE * 3);
#endif
    int ret1 = _IResource->readInputStatus(TOOL_IO_STARTINDEX, TOOL_IO_SIZE, &data[0]);
    int ret2 = _IResource->readInputForceHighStatus(TOOL_IO_STARTINDEX, TOOL_IO_SIZE, &data[TOOL_IO_SIZE]);
    int ret3 = _IResource->readInputForceLowStatus(TOOL_IO_STARTINDEX, TOOL_IO_SIZE, &data[TOOL_IO_SIZE * 2]);
    if (ret1 == ERROR_OK && ret2 == ERROR_OK && ret3 == ERROR_OK) {
        auto [address] = ((CmdDatas<QList<quint8> *> *)cmd)->m_data;
        QList<int> index;
        QList<quint8> different;
        if (compareAndObtainDifferentDatas(*address, data, index, different)) {
            emit CommunicationEngine::instance()->signal_input_getDatas_result(InoIOType_ToolIO, index, different);
        }
    } else {
        PRINT_ERROR(QObject::tr("Failed to read tool DI status."));
    }
    FREQ_LOG_PRINT_TIMESTAMP
}

void IOInterface::getCobotABZData(AbstractCmd *cmd)
{
    std::string data;
    int ret = _IMonitor->readCobotABZDatas(data);
    if (ret != ERROR_OK) {
        PRINT_ERROR(QObject::tr("Failed to read encoder data."));
        return;
    }
    QJsonObject obj = QJsonDocument::fromJson(data.c_str()).object();
    int ans = obj["encoder"].toInt();
    emit CommunicationEngine::instance()->signal_get_ABZ_Data(cmd->m_object, ans);
}
