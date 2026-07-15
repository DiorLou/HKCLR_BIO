#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../DataService/DataSrvGlobal_V1.h"
#include "IOMap/IOMap_V1.h"
#include "FieldBusSwitch/CANopen_V1.h"
#include "FieldBusSwitch/EtherCAT_V1.h"
#include "FieldBusSwitch/EthernetIP_V1.h"
#include "FieldBusSwitch/MC_V1.h"
#include "FieldBusSwitch/Modbus_V1.h"
#include "FieldBusSwitch/Profinet_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define FIELDBUSNUM_V1                5  // 总线数目
#define CANOPEN_FILENNAMME_V1         "canopen.json"
#define DEVICENET_FILENAME_V1         "devicenet.json"
#define ETHERNETIP_FILENAME_V1        "EtIPConfig.json"
#define FOLLOWCRAFT_FILENAME_V1       "FollowCraftCaliCfg.dat"
#define ROBOTCONFIG_FOLDER_V1         "robotConfParameter"
#define FBUSMASTERPARACFG_FILENAME_V1 "FBusMasterParaCfg.jsn"
#define MASTER_FILE_NAME_SUFFIX_V1    "master"

constexpr int MAX_MC_NUM_V1 = 4;  // MC主站最大显示连接数

/**
 * @brief 总线类型
 */
enum FieldBusType_V1
{
    FIELDBUS_UNKNOW_V1 = -1,     // 未知总线类型
    FIELDBUS_MODBUS_V1 = 0,      // Modbus
    FIELDBUS_ETHERNETIP_V1 = 1,  // EthernetIP
    FIELDBUS_ETHERCAT_V1 = 2,    // EtherCAT
    FIELDBUS_MC_V1 = 3,          // MC
    FIELDBUS_PROFINET_V1 = 4,    // Profinet
};

// ADDA类型
enum class ADDAType_V1
{
    IRLink_V1 = 0,
    EtherCAT_V1 = 1,
};

// IRLink AD、DA状态
struct IRLinkADDAStatus_V1
{
    int favorite = 0;          // 收藏
    int kind = 0;              // 0 电流  1 电压
    double minValue = 0.0;     // 最小值
    double maxValue = 20.0;    // 最大值 默认电流 0-20mA
    double actualValue = 0.0;  // 实际的值
    int out = 0;               // 输出开关 0 不输出 1 输出

    IRLinkADDAStatus_V1 &operator=(const IRLinkADDAStatus_V1 &other)
    {
        this->favorite = other.favorite;
        this->kind = other.kind;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->actualValue = other.actualValue;
        this->out = other.out;
        return (*this);
    }

    // 比较  相同返回ture， 不相同返回false
    bool compare(const IRLinkADDAStatus_V1 &other)
    {
        if (favorite != other.favorite)
            return false;
        if (kind != other.kind)
            return false;
        if (minValue != other.minValue)
            return false;
        if (maxValue != other.maxValue)
            return false;
        if (actualValue != other.actualValue)
            return false;
        if (out != other.out)
            return false;
        return true;
    }
};

// ECat ADDA状态
struct ECatADDAStatus_V1
{
    int32s i32EnableChannel = 0;  // 使能通道，0：未使能，1：使能
    int32s i32DAKind = 0;         // 0:电流 1：电压
    int16s i16TransformMode = 0;  // 转换模式
    int16s i16OutputRange = 0;    // 数字输出范围
    double f64MinValue = 0.0;     // 范围最小值
    double f64MaxValue = 0.0;     // 范围最小值
    double f64ActualValue = 0.0;  // 实际输出值
    int32s i32OutSwitch = 0;      // 输出开关 0：不输出 1：输出

    ECatADDAStatus_V1 &operator=(const ECatADDAStatus_V1 &other)
    {
        this->i32EnableChannel = other.i32EnableChannel;
        this->i32DAKind = other.i32DAKind;
        this->i16TransformMode = other.i16TransformMode;
        this->i16OutputRange = other.i16OutputRange;
        this->f64MinValue = other.f64MinValue;
        this->f64MaxValue = other.f64MaxValue;
        this->f64ActualValue = other.f64ActualValue;
        this->i32OutSwitch = other.i32OutSwitch;
        return (*this);
    }

    // 比较  相同返回ture， 不相同返回false
    bool compare(const ECatADDAStatus_V1 &other)
    {
        if (i32EnableChannel != other.i32EnableChannel)
            return false;
        if (i32DAKind != other.i32DAKind)
            return false;
        if (i16TransformMode != other.i16TransformMode)
            return false;
        if (i16OutputRange != other.i16OutputRange)
            return false;
        if (f64MinValue != other.f64MinValue)
            return false;
        if (f64MaxValue != other.f64MaxValue)
            return false;
        if (f64ActualValue != other.f64ActualValue)
            return false;
        if (i32OutSwitch != other.i32OutSwitch)
            return false;
        return true;
    }
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Fieldbus_V1
{
#pragma region 构造与析构

private:
    IFieldbus *_fieldbus = nullptr;

public:
    Fieldbus_V1(IFieldbus *fieldbus);
    ~Fieldbus_V1();

#pragma endregion

#pragma region 子模型

private:
    IOMap_V1 *_ioMap_V1 = nullptr;
    CANopen_V1 *_canOpen_V1 = nullptr;
    EtherCAT_V1 *_etherCAT_V1 = nullptr;
    EthernetIP_V1 *_ethernetIP_V1 = nullptr;
    MC_V1 *_mc_V1 = nullptr;
    Modbus_V1 *_modbus_V1 = nullptr;
    Profinet_V1 *_profinet_V1 = nullptr;

public:
    // IO映射
    IOMap_V1 *GetIOMap();
    bool SetIOMap(IOMap_V1 *ioMapV1);

    // CANopen总线
    CANopen_V1 *GetCANopen();
    bool SetCANopen(CANopen_V1 *canOpenV1);

    // EtherCAT总线
    EtherCAT_V1 *GetEtherCAT();
    bool SetEtherCAT(EtherCAT_V1 *etherCATV1);

    // EthernetIP总线
    EthernetIP_V1 *GetEthernetIP();
    bool SetEthernetIP(EthernetIP_V1 *ethernetIPV1);

    // MC总线
    MC_V1 *GetMC();
    bool SetMC(MC_V1 *mcV1);

    // Modbus总线
    Modbus_V1 *GetModbus();
    bool SetModbus(Modbus_V1 *modbusV1);

    // Profinet总线
    Profinet_V1 *GetProfinet();
    bool SetProfinet(Profinet_V1 *profinetV1);

#pragma endregion

#pragma region 数据转换

public:
    static FieldBusType_V1 FieldBusType_ToProxy(FieldBusType fieldBusType);
    static FieldBusType FieldBusType_FromProxy(FieldBusType_V1 fieldBusType_V1);

    static ADDAType_V1 ADDAType_ToProxy(ADDAType addaType);
    static ADDAType ADDAType_FromProxy(ADDAType_V1 addaType_V1);

    static bool IRLinkADDAStatus_ToProxy(const IRLinkADDAStatus &irLinkADDAStatus, IRLinkADDAStatus_V1 &irLinkADDAStatus_V1);
    static bool IRLinkADDAStatus_FromProxy(const IRLinkADDAStatus_V1 &irLinkADDAStatus_V1, IRLinkADDAStatus &irLinkADDAStatus);

    static bool ECatADDAStatus_ToProxy(const ECatADDAStatus &eCatADDAStatus, ECatADDAStatus_V1 &eCatADDAStatus_V1);
    static bool ECatADDAStatus_FromProxy(const ECatADDAStatus_V1 &eCatADDAStatus_V1, ECatADDAStatus &eCatADDAStatus);

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 检查除当前总线外其他总线的激活状态
     * @param currFieldBus
     * @return true-有其他总线处于激活状态
     */
    bool checkOtherFieldBusIsActive(FieldBusType_V1 currFieldBus);

    /**
     * @brief 将总线主站配置文件放入控制器中
     * @param localDir 本地路径
     * @param bDeviceNet 是否存在DeviceNet文件
     * @param bCanOpen 是否存在CanOpen文件
     * @param bFollwCraftCfg 是否存在FollwCraftCfg文件
     * @param bEip 是否存在Eip文件
     * @return
     */
    int putFieldBusMasterCfgToController(const string &localDir, bool bDeviceNet, bool bCanOpen, bool bFollwCraftCfg, bool bEip);

    /**
     * @brief 通知控制器，组态配置文件导入了
     * @return
     */
    int networkFieldBusImportWrite();

    /**
     * @brief 检查导入主站配置文件权限
     * @return
     */
    bool checkImportMasterConfigPermission();

    // 检查从站状态管理操作权限
    bool checkSlaveManagePermission();

    // 获取当前的总线类型
    int getCurFieldBusType(int &curType);

    // 写入地址分配
    int writeMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG_V1 memAsgnCfg);

    // 读取地址分配
    int readMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG_V1 &memAsgnCfg);

    // 数据保存权限检查
    bool checkFieldBusMemoryDataSavePermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
