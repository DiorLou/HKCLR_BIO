#pragma once

#include <QObject>
#include "dllspec.h"
#include "IOMap/IIOMap.h"
#include "FieldBusSwitch/IModbusSwitch.h"
#include "FieldBusSwitch/IEthernetIPSwitch.h"
#include "FieldBusSwitch/IEtherCATSwitch.h"
#include "FieldBusSwitch/IMCSwitch.h"
#include "FieldBusSwitch/IProfinetSwitch.h"
#include "FieldBusSwitch/ICANopenSwitch.h"

namespace InoRobBusiness
{
#define FIELDBUSNUM                5  // 总线数目
#define CANOPEN_FILENNAMME         "canopen.json"
#define DEVICENET_FILENAME         "devicenet.json"
#define ETHERNETIP_FILENAME        "EtIPConfig.json"
#define FOLLOWCRAFT_FILENAME       "FollowCraftCaliCfg.dat"
#define ROBOTCONFIG_FOLDER         "robotConfParameter"
#define FBUSMASTERPARACFG_FILENAME "FBusMasterParaCfg.jsn"
#define MASTER_FILE_NAME_SUFFIX    "master"

constexpr int MAX_MC_NUM = 4;  // MC主站最大显示连接数

/**
 * @brief 总线类型
 */
enum FieldBusType
{
    FIELDBUS_UNKNOW = -1,     // 未知总线类型
    FIELDBUS_MODBUS = 0,      // Modbus
    FIELDBUS_ETHERNETIP = 1,  // EthernetIP
    FIELDBUS_ETHERCAT = 2,    // EtherCAT
    FIELDBUS_MC = 3,          // MC
    FIELDBUS_PROFINET = 4,    // Profinet
};

// ADDA类型
enum class ADDAType
{
    IRLink = 0,
    EtherCAT = 1,
};

// IRLink AD、DA状态
struct IRLinkADDAStatus
{
  int favorite = 0;          // 收藏
  int kind = 0;              // 0 电流  1 电压
  double minValue = 0.0;     // 最小值
  double maxValue = 20.0;    // 最大值 默认电流 0-20mA
  double actualValue = 0.0;  // 实际的值
  int out = 0;               // 输出开关 0 不输出 1 输出

  IRLinkADDAStatus &operator=(const IRLinkADDAStatus &other)
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
  bool compare(const IRLinkADDAStatus &other)
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
struct ECatADDAStatus
{
    int32s i32EnableChannel = 0;  // 使能通道，0：未使能，1：使能
    int32s i32DAKind = 0;         // 0:电流 1：电压
    int16s i16TransformMode = 0;  // 转换模式
    int16s i16OutputRange = 0;    // 数字输出范围
    double f64MinValue = 0.0;     // 范围最小值
    double f64MaxValue = 0.0;     // 范围最小值
    double f64ActualValue = 0.0;  // 实际输出值
    int32s i32OutSwitch = 0;      // 输出开关 0：不输出 1：输出

    ECatADDAStatus &operator=(const ECatADDAStatus &other)
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
    bool compare(const ECatADDAStatus &other)
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

/**
 * @brief  总线基类
 */
class INOROBBUSINESS_CLASS IFieldbus : public QObject
{
    Q_OBJECT

public:
    virtual ~IFieldbus()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    virtual IIOMap *getIOMap() const = 0;

    // Modbus总线
    virtual IModbusSwitch *getModbusSwitch() const = 0;

    // EthernetIP总线
    virtual IEthernetIPSwitch *getEthernetIPSwitch() const = 0;

    // EtherCAT总线
    virtual IEtherCATSwitch *getEtherCATSwitch() const = 0;

    // MC总线
    virtual IMCSwitch *getMCSwitch() const = 0;

    // Profinet总线
    virtual IProfinetSwitch *getProfinetSwitch() const = 0;

    // CANopen总线
    virtual ICANopenSwitch *getCANopenSwitch() const = 0;

#pragma region 总线开关全局处理
    /**
     * @brief 检查除当前总线外其他总线的激活状态
     * @param currFieldBus
     * @return true-有其他总线处于激活状态
     */
    virtual bool checkOtherFieldBusIsActive(FieldBusType currFieldBus) = 0;

    /**
     * @brief 将总线主站配置文件放入控制器中
     * @param localDir 本地路径
     * @param bDeviceNet 是否存在DeviceNet文件
     * @param bCanOpen 是否存在CanOpen文件
     * @param bFollwCraftCfg 是否存在FollwCraftCfg文件
     * @param bEip 是否存在Eip文件
     * @return
     */
    virtual int putFieldBusMasterCfgToController(const string &localDir, bool bDeviceNet, bool bCanOpen, bool bFollwCraftCfg, bool bEip) = 0;

    /**
     * @brief 通知控制器，组态配置文件导入了
     * @return
     */
    virtual int networkFieldBusImportWrite() = 0;

    /**
     * @brief 检查导入主站配置文件权限
     * @return
     */
    virtual bool checkImportMasterConfigPermission() = 0;
#pragma endregion

#pragma region 从站状态管理
    // 检查从站状态管理操作权限
    virtual bool checkSlaveManagePermission() = 0;
#pragma endregion

#pragma region 地址分配设置
    // 获取当前的总线类型
    virtual int getCurFieldBusType(int &curType) = 0;

    // 写入地址分配
    virtual int writeMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG memAsgnCfg) = 0;

    // 读取地址分配
    virtual int readMemoryAssignConfig(FIELDBUS_MEM_ASSIGN_CONFIG &memAsgnCfg) = 0;

    // 数据保存权限检查
    virtual bool checkFieldBusMemoryDataSavePermission() = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
