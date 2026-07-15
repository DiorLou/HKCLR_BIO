/****************************************************************
 * File Descrip : 总线开关
 * Author       : mzw
 ****************************************************************/
#pragma once
#include <QObject>
#include <string>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
/**
 * @brief EtherCAT基类
 */
class INOROBBUSINESS_CLASS IEtherCATSwitch : public QObject
{
    Q_OBJECT
public:
    virtual ~IEtherCATSwitch()
    {
    }

    /**
     * @brief 写入EtherCAT配置
     * @param ecatConfig 写入结构体
     * @return 0-成功
     */
    virtual int writeEtherCATSlaveConfig(EthcatPara ecatConfig) = 0;

    /**
     * @brief 读取EtherCAT状态
     * @param ecatPara 读取结构体
     * @return 0-成功
     */
    virtual int readEtherCATConnStatus(EthcatSts &ecatPara) = 0;
    /**
     * @brief 读取ECAT新属性
     * @return 0-成功
     */
    virtual int ReadEtherCATProperties(ETHCAT_PROP& buf) = 0;
    /**
     * @brief 读取ECAT从站界面 显示策略, 结果匹配ETHCAT_PROP_SHOWSTRATEGY
     * @return 0-成功
     */
    virtual int ReadEtherCATPropertiesShowStrategy(int& flag) = 0;
    /**
     * @brief 下发ECAT新属性可写字段
     * @return 0-成功
     */
    virtual int WriteEtherCATEnhan(int16u &ARMSetLinkEnhanSwitch, int16u &EtherCATXMLReset) = 0;
    /**
     * @brief 通知下位机解析EtherCAT文件
     * @return 0-成功
     */
    virtual int etherCATAnalysisFileWrite() = 0;

    /**
     * @brief 检查EtherCAT总线开关的操作权限
     * @return true-权限符合
     */
    virtual bool checkEtherCATOperatePermission() = 0;

    /**
     * @brief 检查EtherCAT总线保存权限
     * @return true-权限符合
     */
    virtual bool checkSaveEtherCATPermission() = 0;

    /**
     * @brief 检查配置文件是否与当前控制器匹配
     * @param fileName
     * @return
     */
    virtual int isMatchedCurrentBox(std::string &fileName) = 0;

    /**
     * @brief DeviceNet文件格式检查
     * @param filePath
     * @return
     */
    virtual bool checkDeviceNetFile(string &filePath) = 0;

    /**
     * @brief 获取Ecat从站管理状态
     * @param slaveManageState 从站管理状态
     * @return
     */
    virtual int getECATManageState(EcatSlaveManageState &slaveManageState) = 0;

    /**
     * @brief 设置Ecat从站管理状态
     * @param slaveIndex 从站id号
     * @param isSupportManage 是否支持切换功能
     * @param manageState 从站使能状态
     * @return
     */
    virtual int setECATManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState) = 0;

    /**
     * @brief 设置Ecat从站管理状态功能是否开启
     * @param switchState 开关状态
     * @param messsageBoxShowFlag 显示标志
     * @return
     */
    virtual int setECATManageStateSwitch(int8u switchState, int8u &messsageBoxShowFlag) = 0;

    /**
     * @brief 刷新从站状态 仅用于示教器端
     * @return
     */
    virtual int refreshECATSlaveState() = 0;

    /**
     * @brief 获取AD DA设备状态
     * @param i32ChannelType 通道类型
     * @param pi16ChannelNum 通道号码
     * @param dataArr 设备状态结构体
     * @return
     */
    virtual int EtherCATADDAStateRead(int32s i32ChannelType, int16s &pi16ChannelNum, std::vector<EcatAdDaState> &dataArr) = 0;

    /**
     * @brief 下发AD DA设备状态
     * @param i32SetFlag 设置标志
     * @param i32ChannelId 通道号码
     * @param data 设备状态结构体
     * @return
     */
    virtual int EtherCATADDAStateWrite(int32s i32SetFlag, int32s i32ChannelId, const EcatAdDaState &data) = 0;
};
}  // namespace InoRobBusiness
