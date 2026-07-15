#pragma once
#include "IEtherCATSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class EtherCATDefault : public IEtherCATSwitch
{
    Q_OBJECT
public:
    EtherCATDefault(IDataSrvBase *dataService, IMonitor *pMonitor);
    ~EtherCATDefault();

    // 写入EtherCAT配置
    int writeEtherCATSlaveConfig(EthcatPara ecatConfig);

    // 读取EtherCAT状态
    int readEtherCATConnStatus(EthcatSts &ecatPara);

    // 读取ECAT新属性
    int ReadEtherCATProperties(ETHCAT_PROP& buf);

    // 读取ECAT从站界面 显示策略, 结果匹配ETHCAT_PROP_SHOWSTRATEGY
    int ReadEtherCATPropertiesShowStrategy(int& flag);

    // 下发ECAT新属性设置
    int WriteEtherCATEnhan(int16u &ARMSetLinkEnhanSwitch, int16u &EtherCATXMLReset);

    // 通知下位机解析EtherCAT文件
    int etherCATAnalysisFileWrite();

    // 检查EtherCAT总线开关的操作权限
    bool checkEtherCATOperatePermission();

    // 检查EtherCAT总线保存权限
    bool checkSaveEtherCATPermission();

    // 获取电柜类型
    int getElectrixBoxType(int16u &type);

    // 检查配置文件是否与当前控制器匹配
    int isMatchedCurrentBox(std::string &fileName);

    // DeviceNet文件格式检查
    bool checkDeviceNetFile(string &filePath);

    // 获取Ecat从站管理状态
    int getECATManageState(EcatSlaveManageState &slaveManageState);

    // 设置Ecat从站管理状态
    int setECATManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState);

    // 设置Ecat从站管理状态功能是否开启
    int setECATManageStateSwitch(int8u switchState, int8u &messsageBoxShowFlag);

    // 刷新从站状态 仅用于示教器端
    int refreshECATSlaveState();

    // 获取AD DA设备状态
    int EtherCATADDAStateRead(int32s i32ChannelType, int16s &pi16ChannelNum, std::vector<EcatAdDaState> &dataArr);

    // 下发AD DA设备状态
    int EtherCATADDAStateWrite(int32s i32SetFlag, int32s i32ChannelId, const EcatAdDaState &data);

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
    IMonitor *_pMonitor = nullptr;
};
}  // namespace InoRobBusiness
