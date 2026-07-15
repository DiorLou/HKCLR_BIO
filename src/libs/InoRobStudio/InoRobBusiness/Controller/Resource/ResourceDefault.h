#pragma once
#include <string>
#include <vector>
#include <array>
#include <mutex>
#include "IInoRobBusiness.h"
#include "GlobalVar/VarMonitorDefault.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ResourceDefault : public IResource, public IRCSchedulerUser
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;
    IConnection *_pConnection = nullptr;  // 连接
    IMonitor *_pMonitor = nullptr;
    IProject *_pProject = nullptr;              // 工程
    ITask *_pTask = nullptr;                    // 任务
    ITransfor *_pTransfor = nullptr;            // 译码
    IDataSubscribe *_pDataSubscribe = nullptr;  // 数据订阅
    IRCScheduler *_pScheduler = nullptr;        // RC调度
    IFieldbus *_pFieldBus = nullptr;            // 总线

    IVarMonitor *_pVarMonitor = nullptr;  // 变量监控

public:
    ResourceDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~ResourceDefault();
    void init() override;
#pragma endregion
public:
    void execute() override;

#pragma region 获取pt文件列表
    int getPointFileListFromController(vector<std::string> &fileList);

    std::string getFileExtension(const std::string &fileName);
#pragma endregion

#pragma region 变量监控
    IVarMonitor *getVarMonitor() const override;
#pragma endregion

#pragma region 全局B变量
    void setGlobalVarBScheduler(bool scheduler) override;
    int readGlobalVarBValues(std::array<int8u, GLOBAL_VAR_B_NUM> &values) override;
    int writeGlobalVarBValue(const unsigned char value, const unsigned int index) override;
    std::vector<GlobalVarBData> getGlobalVarBDatas() const override;
    bool setGlobalVarBFavorite(const bool favorite, const int index) override;
    bool getGlobalVarBShowFavorite() const override;
    bool setGlobalVarBShowFavorite(const bool show) override;
    std::array<unsigned char, GLOBAL_VAR_B_NUM> getGlobalVarBValues() const override;
    bool setGlobalVarBValue(const unsigned char value, const unsigned int index) override;
    bool updataGlobalVarBDatas() override;
#pragma endregion

#pragma region 全局R变量
    void setGlobalVarRScheduler(bool scheduler) override;
    int readGlobalVarRValues(std::array<int, GLOBAL_VAR_R_NUM> &values) override;
    int writeGlobalVarRValue(const int value, const unsigned int index) override;
    std::vector<GlobalVarRData> getGlobalVarRDatas() const override;
    bool setGlobalVarRFavorite(const bool favorite, const int index) override;
    bool getGlobalVarRShowFavorite() const override;
    bool setGlobalVarRShowFavorite(const bool show) override;
    std::array<int, GLOBAL_VAR_R_NUM> getGlobalVarRValues() const override;
    bool setGlobalVarRValue(const int value, const unsigned int index) override;
    bool updataGlobalVarRDatas() override;
#pragma endregion

#pragma region 全局D变量
    void setGlobalVarDScheduler(bool scheduler) override;
    int readGlobalVarDValues(std::array<double, GLOBAL_VAR_D_NUM> &values) override;
    int writeGlobalVarDValue(const double value, const unsigned int index) override;
    std::vector<GlobalVarDData> getGlobalVarDDatas() const override;
    bool setGlobalVarDFavorite(const bool favorite, const int index) override;
    bool getGlobalVarDShowFavorite() const override;
    bool setGlobalVarDShowFavorite(const bool show) override;
    std::array<double, GLOBAL_VAR_D_NUM> getGlobalVarDValues() const override;
    bool setGlobalVarDValue(const double value, const unsigned int index) override;
    bool updataGlobalVarDDatas() override;
#pragma endregion

#pragma region 全局变量PR
    void setGlobalVarPRScheduler(bool scheduler) override;
    int readGlobalVarPRValues(std::vector<Pose> &values) const override;
    int writeGlobalVarPRValue(const Pose &value, const unsigned int index) override;
    std::vector<Pose> getGlobalVarPRValues() const override;
    bool allowSetGlobalVarPRValue() override;
    bool setGlobalVarPRValue(const Pose &value, const unsigned int index) override;
    bool updateGlobalVarPRDatas() override;
#pragma endregion

#pragma region 全局变量String
    void setGlobalVarStringScheduler(bool scheduler) override;
    int readGlobalVarStringValues(std::array<std::string, GLOBAL_VAR_STRING_NUM> &values) const override;
    int writeGlobalVarStringValue(const std::string &value, const unsigned int index) override;
    std::array<std::string, GLOBAL_VAR_STRING_NUM> getGlobalVarStringDatas() const override;
    bool setGlobalVarStringValue(const std::string &value, const unsigned int index) override;
    bool updateGlobalVarStringDatas() override;
#pragma endregion

#pragma region 全局点位P
    int readGlobalPValues(std::vector<RAM_P> &values, const int pageIndex, const int pageNum) override;
    bool getGlobalPDatas(std::vector<GlobalPData> &datas, const int pageIndex, const int pageNum, bool isNeedErrorPrint = true) override;
#pragma endregion

#pragma region 全局点位JP
    int readGlobalJPValues(std::vector<RAM_J> &values, const int pageIndex, const int pageNum) override;
    bool getGlobalJPDatas(std::vector<GlobalJPData> &datas, const int pageIndex, const int pageNum, bool isNeedMsgPrint = true) override;
#pragma endregion

#pragma region IO
#pragma region Input
    void setInputScheduler(const bool scheduler) override;
    int readCommonInputStatus(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &inputIndexs, std::vector<int8u> &status) override;
    int readInputStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) override;
    int readInputForceHighStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) override;
    int readInputForceLowStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) override;
    int writeInputStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) override;
    int writeInputForceHighStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) override;
    int writeInputForceLowStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) override;
    void setInputIOType(const IResource::IOType ioType) override;
    IResource::IOType getInputIOType() const override;
    void setInputShowType(const IResource::ShowType showType) override;
    IResource::ShowType getInputShowType() const override;
    std::vector<int8u> getCommonInputValues() const override;
    std::array<int8u, STANDARD_IO_SIZE> getStandardInputValues() const override;
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> getSlaveFieldbusInputValues() const override;
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE> getMasterFieldbusInputValues() const override;
    std::array<int8u, MEMORY_IO_SIZE> getMemoryInputValues() const override;
    std::array<int8u, STANDARD_IO_SIZE> getStandardInputForceHighValues() const override;
    std::array<int8u, STANDARD_IO_SIZE> getStandardInputForceLowValues() const override;
    IoLabelItems getInputLabelAndRemark() const override;
    std::vector<unsigned short> getCommonInputIndexs() const override;
    bool setStandardInputForceStatus(const unsigned int index) override;
    bool setStandardInputStatus(const unsigned int index) override;
    bool setMemoryInputStatus(const unsigned int statusIndex, const bool isOn) override;
    void updateStandardInputValue() override;
    bool updateInputLabelAndRemark() override;
    bool updateCommonInputDatas() override;
    bool updateStandardInputDatas() override;
    bool updateSlaveFieldbusInputDatas() override;
    bool updateMasterFieldbusInputDatas() override;
    bool updateMemoryInputDatas() override;
#pragma endregion

#pragma region Output
    void setOutputScheduler(const bool scheduler) override;
    int readCommonOutputStatus(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &status) override;
    int readCommonOutputControls(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &controls) override;
    int readOutputStatus(const int16u startByteId, const int16u byteNum, int8u *status) override;
    int readOutputControls(const int16u startByteId, const int16u byteNum, std::vector<int8u> &controls) override;
    int writeOutputStatusByBit(const int16u bitIndex, const int8u bitValue) override;
    int writeOutputStatusByByte(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status) override;
    void setOutputIOType(const IResource::IOType ioType) override;
    IResource::IOType getOutputIOType() const override;
    void setOutputShowType(const IResource::ShowType showType) override;
    IResource::ShowType getOutputShowType() const override;
    std::vector<int8u> getCommonOutputValues() const override;
    std::array<int8u, STANDARD_IO_SIZE> getStandardOutputValues() const override;
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> getSlaveFieldbusOutputValues() const override;
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE> getMasterFieldbusOutputValues() const override;
    std::array<int8u, MEMORY_IO_SIZE> getMemoryOutputValues() const override;
    IoLabelItems getOutputLabelAndRemark() const override;
    std::vector<unsigned short> getCommonOutputIndexs() const override;
    bool setOutputStatus(const unsigned int index, const unsigned int statusIndex, const bool isOn) override;
    bool setOutputStatus(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status) override;
    bool updateOutputLabelAndRemark() override;
    bool updateCommonOutputDatas() override;
    bool updateStandardOutputValues() override;
    bool updateSlaveFieldbusOutputValues() override;
    bool updateMasterFieldbusOutputValues() override;
    bool updateMemoryOutputValues() override;
#pragma endregion

#pragma region 协作末端IO
    int readToolIoConfig(std::string &ans) override;
    int writeToolIoConfig(std::string &ans) override;
    int setToolIOConfigMonitorState(bool state) override;
#pragma endregion
#pragma endregion

#pragma region AD DA
    void setADScheduler(const bool scheduler) override;
    void setADShowType(const ADDAType type) override;
    int readIRLinkADValues(std::array<IRLinkADDAStatus, ADDA_MAX_SIZE> &values) override;
    int readCobotAnalogIODatas(bool isDA, std::vector<Cobot_ADDA_Data> &data) override;
    int writeCobotAnalogIODatas(const Cobot_ADDA_Status &data) override;
    std::vector<IRLinkADDAData> getIRLinkADDatas() const override;
    std::vector<ECatADDAData> getECatADDatas() const override;
    bool updateIRLinkADDatas() override;
    bool updateECatADDatas() override;
    void setDAScheduler(const bool scheduler) override;
    void setDAShowType(const ADDAType type) override;
    int readIRLinkDAValues(std::array<IRLinkADDAStatus, ADDA_MAX_SIZE> &values) override;
    int writeIRLinkDAValue(const int index, const int flag, const IRLinkADDAStatus &value) override;
    std::vector<IRLinkADDAData> getIRLinkDADatas() const override;
    std::vector<ECatADDAData> getECatDADatas() const override;
    bool setIRLinkDAStatus(const int index, const int flag, const IRLinkADDAStatus &status) override;
    bool setECatDAStatus(const int index, const int flag, const EcatAdDaState &status) override;
    bool updateIRLinkDADatas() override;
    bool updateECatDADatas() override;
#pragma endregion

#pragma region sysIO
    void setSysInputScheduler(const bool scheduler) override;
    void setSysOutputScheduler(const bool scheduler) override;
    int readSysIOValues(int16u &inputData, int16u &outputData) override;
    int readSysIOForceValues(int16u &inputFH, int16u &inputFL, int16u &outputFH, int16u &outputFL) override;
    std::array<bool, SYSIO_SIZE> getSysInputStatus() const override;
    std::array<std::string, SYSIO_SIZE> getSysInputRemarks() const override;
    std::array<bool, SYSIO_SIZE> getSysOutputStatus() const override;
    std::array<std::string, SYSIO_SIZE> getSysOutputRemarks() const override;
    bool updateSysInputDatas() override;
    bool updateSysOutputDatas() override;
#pragma endregion

#pragma region 网络 EtherCAT
    int readControllerEthInfo(ControllerEthInfo &controllerEI) const override;
    int readEcatPdoLostInfo(int16u &totalLostCount, int16u &continueLostCount, int16u &lostFlag) const override;
#pragma endregion

#pragma region 存储卡
    int readSDInfo(std::string &info) const override;
#pragma endregion

#pragma region 总线通讯
    void setModbusConnectScheduler(const bool scheduler) override;
    int readModbusConnectStatus(ModbusConnectStatus &status) override;
    ModbusConnectStatus getModbusConnectStatus() const override;
    bool updateModbusConnectStatus() override;
    void setEthernetIPScheduler(const bool scheduler) override;
    int readEthernetIPStatus(EthernetIPStatus &status) override;
    EthernetIPStatus getEthernetIPStatus() const override;
    bool updateEthernetIPStatus() override;
    void setEtherCatScheduler(const bool scheduler) override;
    int readEtherCatStatus(EtherCATStatus &status) override;
    EtherCATStatus getEtherCatStatus() const override;
    bool updateEtherCatStatus() override;
    void setMCScheduler(const bool scheduler) override;
    int readMCActiveStatus(unsigned char &active) override;
    int readMCConnectStatus(std::array<MCConnectStatus, MC_CONNECT_NUM> &status) override;
    bool getMCActiveStatus() const override;
    std::array<MCConnectStatus, MC_CONNECT_NUM> getMCConnectStatus() override;
    bool updateMCStatus() override;
    void setProfinetConnectScheduler(const bool scheduler) override;
    int readProfinetConnectStatus(ProfinetConnectStatus &status) override;
    ProfinetConnectStatus getProfinetConnectStatus() const override;
    bool updateProfinetConnectStatus() override;
#pragma endregion

#pragma region 伺服状态
    int prepareServoParam(int axisNo, int pageID) override;
    int readServoParam(int axisNo, int pageID, char pFunCode[10][12]) override;
    bool readSingleServoCode(int axisNo, const std::string &code, std::string &value) override;
    bool writeSingleServoCode(int axisNo, const std::string &code, const std::string &value) override;
    bool allowResetEncoder() override;
    bool writeResetEncoder(int axisNo) override;
    bool readResetEncoderResult(int axisNo, int &result) override;
#pragma endregion

#pragma region 工况
    void setElectricScheduler(const bool scheduler) override;
    int readCurrentElectric(std::vector<double> &current) override;
    int readMaxElectric(std::vector<double> &maxCurrent) override;
    int resetMaxElectric() override;
    bool allowResetMaxElectric() override;
    std::vector<double> getCurrentElectric() const override;
    std::vector<double> getMaxElectric() const override;
    bool updateElectric() override;
    void setAvgLoadRateScheduler(const bool scheduler) override;
    int readCurrentAvgLoadRate(std::vector<double> &avgLoadRate) override;
    std::vector<double> getCurrentAvgLoadRate() const override;
    bool updateAvgLoadRate() override;
    void setOverLoadScheduler(const bool scheduler) override;
    int readCurrentOverLoad(std::vector<double> &overLoad) override;
    int readMaxOverLoad(std::vector<double> &maxOverLoad) override;
    int resetMaxOverLoad() override;
    bool allowResetMaxOverLoad() override;
    std::vector<double> getCurrentOverLoad() const override;
    std::vector<double> getMaxOverLoad() const override;
    bool updateOverLoad() override;
    void setOverHeatScheduler(const bool scheduler) override;
    int readCurrentOverHeat(std::vector<double> &overHeat) override;
    std::vector<double> getCurrentOverHeat() const override;
    bool updateOverHeat() override;
#pragma endregion

#pragma region 示教器压缩包信息
    virtual int writeCountTPPackagesInfoCmd(int cmd) override;

    virtual int readCountTPPackagesInfoCmdResult(int &result) override;
#pragma endregion

#pragma region 点文件路径
    const std::string _remotePointFilePath = "PalletInfo/";
#pragma endregion

#pragma region 全局变量
private:
    bool _bScheduler = false;
    bool _bFavShow = false;
    std::vector<int> _bFavLists;
    std::vector<GlobalVarBData> _bDatas;
    std::array<int8u, GLOBAL_VAR_B_NUM> _bValues = { 0 };

    bool _rScheduler = false;
    bool _rFavShow = false;
    std::vector<int> _rFavLists;
    std::vector<GlobalVarRData> _rDatas;
    std::array<int, GLOBAL_VAR_R_NUM> _rValues = { 0 };

    bool _dScheduler = false;
    bool _dFavShow = false;
    std::vector<int> _dFavLists;
    std::vector<GlobalVarDData> _dDatas;
    std::array<double, GLOBAL_VAR_D_NUM> _dValues = { 0.000 };

    bool _prScheduler = false;
    std::vector<Pose> _prValues;

    bool _stringScheduler = false;
    std::array<std::string, GLOBAL_VAR_STRING_NUM> _stringValues;

    // 全局B、R、D变量状态检查
    bool statusCheckBRD() const;

    /**
     * @brief 确保BRD收藏文件的路径存在
     * @return true存在 false不存在
     */
    bool ensurePathExists();

    /**
     * @brief 读取收藏文件中的内容
     * @return true成功 false失败
     */
    bool readFavoriteData();

    /**
     * @brief 写收藏文件中的内容
     * @return true成功 false失败
     */
    bool writeFavoriteData();

    // 初始化全局B变量数据列表
    void initGlobalVarBDatas();

    // 全局B变量调度执行
    void globalVarBExecute();

    // 初始化全局R变量数据列表
    void initGlobalVarRDatas();

    // 全局变量R调度执行
    void globalVarRExecute();

    // 初始化全局D变量数据列表
    void initGlobalVarDDatas();

    // 全局变量D调度执行
    void globalVarDExecute();

    // 全局PR变量调度执行
    void globalVarPRExecute();

    // 全局String变量调度执行
    void globalVarStringExecute();
#pragma endregion

#pragma region IO
private:
    bool _inputScheduler = false;
    IResource::IOType _inputIOType = IResource::COMMON_IO;
    IResource::ShowType _inputShowType = IResource::BIT;

    std::vector<int8u> _commonInputValues;
    std::vector<unsigned short> _commonInputIndexs;
    std::array<int8u, STANDARD_IO_SIZE> _standardInputValues = { 0 };
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> _slaveFieldbusInputValues = { 0 };
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE> _masterFieldbusInputValues = { 0 };
    std::array<int8u, MEMORY_IO_SIZE> _memoryInputValues = { 0 };
    std::array<int8u, STANDARD_IO_SIZE> _standardInputFHValues = { 0 };
    std::array<int8u, STANDARD_IO_SIZE> _standardInputFLValues = { 0 };
    IoLabelItems _inputLabelRemarkItems;
    bool _isUpdateStandardInputValue = false;
    std::mutex _commonInputValueMutex;

    // input调度
    void inputExecute();

    bool _outputScheduler = false;
    IResource::IOType _outputIOType = IResource::COMMON_IO;
    IResource::ShowType _outputShowType = IResource::BIT;

    std::vector<int8u> _commonOutputValues;
    std::vector<unsigned short> _commonOutputIndexs;
    std::array<int8u, STANDARD_IO_SIZE> _standardOutputValues = { 0 };
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> _slaveFieldbusOutputValues = { 0 };
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE> _masterFieldbusOutputValues = { 0 };
    std::array<int8u, MEMORY_IO_SIZE> _memoryOutputValues = { 0 };
    IoLabelItems _outputLabelRemarkItems;
    std::mutex _commonOutputValueMutex;

    // 输出调度
    void outputExecute();

    // io状态检查
    bool statusCheckIO() const;
#pragma endregion

#pragma region AD DA
private:
    bool _adScheduler = false;
    ADDAType _ADShowType = ADDAType::IRLink;
    std::vector<IRLinkADDAData> _IRLinkADDatas;
    std::vector<ECatADDAData> _ECatADDatas;
    bool _daScheduler = false;
    ADDAType _DAShowType = ADDAType::IRLink;
    std::vector<IRLinkADDAData> _IRLinkDADatas;
    std::vector<ECatADDAData> _ECatDADatas;

    // AD调度
    void adExecute();

    // DA调度
    void daExecute();
#pragma endregion

#pragma region sysIO
private:
    bool _sysInputScheduler = false;
    bool _sysOutputScheduler = false;
    int16u _sysInputValue = 0x0;
    int16u _sysOutputValue = 0x0;
    int16u _sysInputFHValue = 0x0;
    int16u _sysInputFLValue = 0x0;
    int16u _sysOutputFHValue = 0x0;
    int16u _sysOutputFLValue = 0x0;
    std::array<SysIODat, CABINET_COUNT> _sysInOutDats;  // 系统IODat数组
    std::array<bool, SYSIO_SIZE> _sysInputStatus;
    std::array<bool, SYSIO_SIZE> _sysOutputStatus;
    std::array<std::string, SYSIO_SIZE> _sysInputRemarks;
    std::array<std::string, SYSIO_SIZE> _sysOutputRemarks;

    void parseSysInputStatus();  // 解析系统IO状态

    void parseSysOutputStatus();  // 解析系统输出状态

    void sysInputExecute();  // 系统输入调度

    void sysOutputExecute();  // 系统输出调度
#pragma endregion

#pragma region 总线通讯
private:
    bool _modbusConnectScheduler = false;
    ModbusConnectStatus _modbusConnectStatus;

    bool _ethernetIPScheduler = false;
    EthernetIPStatus _ethernetIPStatus;

    bool _etherCatScheduler = false;
    EtherCATStatus _etherCatStatus;

    bool _mcScheduler = false;
    bool _mcActiveStatus = false;
    std::array<MCConnectStatus, MC_CONNECT_NUM> _mcConnectStatus;

    bool _profinetConnectScheduler = false;
    ProfinetConnectStatus _profinetConnectStatus;

    // modbus连接调度
    void modbusConnectExecute();
    // EthernetIP调度
    void ethernetIPExecute();
    // EtherCat调度
    void etherCatExecute();
    // MC调度
    void mcExecute();
    // ProfinetConnect调度
    void profinetConnectExecute();
#pragma endregion

#pragma region 工况
private:
    bool _electricScheduler = false;
    std::vector<double> _currentElectrics;
    std::vector<double> _maxElectrics;

    bool _avgLoadRateScheduler = false;
    std::vector<double> _currentAvgLoadRate;

    bool _overLoadScheduler = false;
    std::vector<double> _currentOverLoad;
    std::vector<double> _maxOverLoad;

    bool _overHeatScheduler = false;
    std::vector<double> _currentOverHeat;

    // 电流调度
    void electricExecute();
    // 平均负载率调度
    void avgLoadRateExecute();
    // 过载率调度
    void overLoadExecute();
    // 过热率调度
    void overHeatExecute();
#pragma endregion
};
#pragma endregion
}  // namespace InoRobBusiness
