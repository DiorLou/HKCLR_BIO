#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
#include "../../../GlobalDataTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS EtherCAT_V1
{
#pragma region 构造与析构

private:
    IEtherCATSwitch *_etherCATSwitch = nullptr;

public:
    EtherCAT_V1(IEtherCATSwitch *etherCATSwitch);
    ~EtherCAT_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 写入EtherCAT配置
     * @param ecatConfig 写入结构体
     * @return 0-成功
     */
    int writeEtherCATSlaveConfig(EthcatPara_V1 ecatConfig);

    /**
     * @brief 读取EtherCAT状态
     * @param ecatPara 读取结构体
     * @return 0-成功
     */
    int readEtherCATConnStatus(EthcatSts_V1 &ecatPara);

    /**
     * @brief 通知下位机解析EtherCAT文件
     * @return 0-成功
     */
    int etherCATAnalysisFileWrite();

    /**
     * @brief 检查EtherCAT总线开关的操作权限
     * @return true-权限符合
     */
    bool checkEtherCATOperatePermission();

    /**
     * @brief 检查EtherCAT总线保存权限
     * @return true-权限符合
     */
    bool checkSaveEtherCATPermission();

    /**
     * @brief 检查配置文件是否与当前控制柜匹配
     * @param fileName
     * @return
     */
    int isMatchedCurrentBox(std::string &fileName);

    /**
     * @brief DeviceNet文件格式检查
     * @param filePath
     * @return
     */
    bool checkDeviceNetFile(string &filePath);

    /**
     * @brief 获取Ecat从站管理状态
     * @param slaveManageState 从站管理状态
     * @return
     */
    int getECATManageState(EcatSlaveManageState_V1 &slaveManageState);

    /**
     * @brief 设置Ecat从站管理状态
     * @param slaveIndex 从站id号
     * @param isSupportManage 是否支持切换功能
     * @param manageState 从站使能状态
     * @return
     */
    int setECATManageState(int8u slaveIndex, int8u isSupportManage, int8u manageState);

    /**
     * @brief 设置Ecat从站管理状态功能是否开启
     * @param switchState 开关状态
     * @param messsageBoxShowFlag 显示标志
     * @return
     */
    int setECATManageStateSwitch(int8u switchState, int8u &messsageBoxShowFlag);

    /**
     * @brief 刷新从站状态 仅用于示教器端
     * @return
     */
    int refreshECATSlaveState();

    /**
     * @brief 获取AD DA设备状态
     * @param i32ChannelType 通道类型
     * @param pi16ChannelNum 通道号码
     * @param dataArr 设备状态结构体
     * @return
     */
    int EtherCATADDAStateRead(int32s i32ChannelType, int16s &pi16ChannelNum, std::vector<EcatAdDaState_V1> &dataArr);

    /**
     * @brief 下发AD DA设备状态
     * @param i32SetFlag 设置标志
     * @param i32ChannelId 通道号码
     * @param data 设备状态结构体
     * @return
     */
    int EtherCATADDAStateWrite(int32s i32SetFlag, int32s i32ChannelId, const EcatAdDaState_V1 &data);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
