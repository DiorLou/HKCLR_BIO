#pragma once
#include "IFieldbus.h"
#include "IInoRobBusiness.h"
#include "IOMap/IOMapDefault.h"
#include "FieldBusSwitch/ModbusDefaut.h"
#include "FieldBusSwitch/EthernetIPDefault.h"
#include "FieldBusSwitch/EtherCATDefault.h"
#include "FieldBusSwitch/MCDefault.h"
#include "FieldBusSwitch/ProfinetDefault.h"
#include "FieldBusSwitch/CANopenDefault.h"

namespace InoRobBusiness
{
class FieldbusDefault : public IFieldbus
{
    // 依赖注入
private:
    IDataSrvBase *_pDataService = nullptr;
    IMonitor *_pMonitor = nullptr;
    IConnection *_pConnection = nullptr;
    IRobotArm *_pRobotArm = nullptr;

public:
    FieldbusDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~FieldbusDefault();
    void init() override;
    IIOMap *getIOMap() const;

    // Modbus总线
    IModbusSwitch *getModbusSwitch() const;

    // EthernetIP总线
    IEthernetIPSwitch *getEthernetIPSwitch() const;

    // EtherCAT总线
    IEtherCATSwitch *getEtherCATSwitch() const;

    // MC总线
    IMCSwitch *getMCSwitch() const;

    // Profinet总线
    IProfinetSwitch *getProfinetSwitch() const;

    // CANopen总线
    ICANopenSwitch *getCANopenSwitch() const;

#pragma region 总线开关全局处理
    // 检查除当前总线外其他总线的激活状态
    bool checkOtherFieldBusIsActive(FieldBusType currFieldBus);

    // 将总线主站配置文件放入控制器中
    int putFieldBusMasterCfgToController(const string &localDir, bool bDeviceNet, bool bCanOpen, bool bFollwCraftCfg, bool bEip);

    // 通知控制器，组态配置文件导入了
    int networkFieldBusImportWrite();

    // ftp传输总线文件
    int ftpTransferFieldBusFiles(ftp::client &ftpClient, const string &localDir, const string &remoteDir, const string &fileName);

    // 检查导入主站配置文件权限
    bool checkImportMasterConfigPermission();
#pragma endregion

#pragma region 从站状态管理
    // 检查从站状态管理操作权限
    bool checkSlaveManagePermission();
#pragma endregion

#pragma region 地址分配设置
    // 获取当前的总线类型
    int getCurFieldBusType(int &curType);

    // 写入地址分配
    int writeMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG memAsgnCfg);

    // 读取地址分配
    int readMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG &memAsgnCfg);

    // 数据保存权限检查
    bool checkFieldBusMemoryDataSavePermission();
#pragma endregion

private:
    IIOMap *_pIOMap = nullptr;

    IModbusSwitch *_pModbusSwitch = nullptr;          // Modbus
    IEthernetIPSwitch *_pEthernetIPSwitch = nullptr;  // EthernetIP
    IEtherCATSwitch *_pEtherCATSwitch = nullptr;      // IEtherCAT
    IMCSwitch *_pMCSwitch = nullptr;                  // MC
    IProfinetSwitch *_pProfinetSwitch = nullptr;      // Profinet
    ICANopenSwitch *_pCANopenSwitch = nullptr;        // CANopen

    static const std::string _remoteDeviceNetPath;    // 控制器下DeviceNet目录
    static const std::string _remoteCANopenPath;      // 控制器下CANopen目录
    static const std::string _remoteFollowCraftPath;  // 控制器下FollowCraft目录
    static const std::string _remoteEtherIpPath;      // 控制器下EtherIp目录
};
}  // namespace InoRobBusiness
