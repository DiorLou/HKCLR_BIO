#pragma once

#include "labeldata.h"
#include "communication_global.h"
#include "iostruct.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
class COMMUNICATION_EXPORT IOInterface
{
public:
    IOInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    void setInputIOType(InoIOType ioType);
    void setOutputIOType(InoIOType ioType);

    void setInputShowType(const ShowType &showType);
    void setOutputShowType(const ShowType &showType);

    bool getOutputLabelAndRemarkForCurrentShow(QVector<InoLabelItem> &data);
    bool getInputLabelAndRemarkForCurrentShow(QVector<InoLabelItem> &data);

    void getInputControlAuthority(AbstractCmd *cmd);
    void getOutputControlAuthority(AbstractCmd *cmd);

    bool getInputForceValuesStandard(QList<quint8> &data);

    bool getInputValuesStandard(QList<quint8> &data);
    void getInputValuesTool(AbstractCmd *cmd);
    bool getInputValuesFieldbus(QList<quint8> &data);
    bool getInputValuesMemory(QList<quint8> &data);

    bool getOutputValuesStandard(QList<quint8> &src);
    void getOutputValuesTool(AbstractCmd *cmd);
    bool getOutputValuesFieldbus(QList<quint8> &src);
    bool getOutputValuesMemory(QList<quint8> &src);

    bool writeInputStatusByBit(const int Index, const bool bitValue);
    bool writeInputStatusForce(const int bitIndex);
    bool writeInputStatusByBit(AbstractCmd *cmd);
    bool writeInputStatusForce(AbstractCmd *cmd);

    void writeOutputStatusByBit(AbstractCmd *cmd);

    void setSchedulerInput(bool scheduler);
    void setSchedulerOutput(bool scheduler);

    bool updateCommonInputDatas();
    bool updateCommonOutputDatas();

    bool updateStandardInputDatas();
    bool updateStandardOutputDatas();

    bool updateFieldbusInputDatas();
    bool updateFieldbusOutputDatas();

    bool updateMemoryInputDatas();
    bool updateMemoryOutputDatas();

    void setSchedulerAD(const bool scheduler);
    void setSchedulerDA(const bool scheduler);

    bool getDatasAD(QList<Ino_AD_DA_Data> &data);
    bool getDatasDA(QList<Ino_AD_DA_Data> &data);

    void getCobotDatasADDA(AbstractCmd *cmd);
    void setCobotDatasADDA(AbstractCmd *cmd);

    void getCobotABZData(AbstractCmd *cmd);

    bool setDataDA(const int index,
                   const int flag,
                   const Ino_AD_DA_Data &value);

    bool getDatasSystemIn(QList<bool> &data);
    bool getDatasSystemOut(QList<bool> &data);

    void setSchedulerSysInput(const bool scheduler);
    void setSchedulerSysOutput(const bool scheduler);

#if defined(INOCOBOTTP_MSVC_QT5)
    bool getSysOutputRemarkList(QList<QString> &data);
    bool getSysInputRemarkList(QList<QString> &data);
#endif

    bool getSysInputRemark(QStringList &data);
    bool getSysOutputRemark(QStringList &data);

    bool getCommonInputIndexs(QList<unsigned short> &index);
    bool getCommonInputValues(QList<quint8> &values);

    bool getCommonOutputIndexs(QList<unsigned short> &index);
    bool getCommonOutputValues(QList<quint8> &values);

    void readToolIOConfig(AbstractCmd *absCmd);
    void writeToolIOConfig(AbstractCmd *absCmd);
    void setToolIOConfigMonitorState(AbstractCmd *absCmd);
};
