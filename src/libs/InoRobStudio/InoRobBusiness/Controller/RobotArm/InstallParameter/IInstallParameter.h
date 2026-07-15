#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
/*!
 * \brief  安装参数抽象类, 机械臂下的子类
 */
class INOROBBUSINESS_CLASS IInstallParameter : public QObject
{
    Q_OBJECT
public:
    virtual ~IInstallParameter()
    {
    }

    virtual int print() = 0;

#pragma region 臂上负载
    /**
     * @brief 读取臂上负载数据
     * @param nLinkNo 臂上负载号
     * @param armload 臂上负载数据
     * @return 0-成功
     */
    virtual int ReadArmLoad(int nLinkNo, ArmLoadPara &armload) = 0;

    /**
     * @brief 写入臂上负载数据
     * @param armload 臂上负载数据
     * @return 0-成功
     */
    virtual int WriteArmLoad(ArmLoadPara armload) = 0;

    /**
     * @brief 检查臂上负载的修改权限
     * @return true-符合权限, false-不符合权限
     */
    virtual bool checkArmLoadPermission() = 0;
#pragma endregion

#pragma region 自动热机
    /**
     * @brief 保存自动热机参数
     * @param param 自动热机参数
     * @return 0-成功
     */
    virtual int saveWarmUpMachineParam(WarmUpMachineParam &param) = 0;

    /**
     * @brief 读取自动热机数据
     * @param param 自动热机参数
     * @return 0-成功
     */
    virtual int readWarmUpMachineParam(WarmUpMachineParam &param) = 0;

    /**
     * @brief 保存热机参数权限
     * @return true-权限符合
     */
    virtual bool checkSaveWarmMachinePermission() = 0;

    /**
     * @brief 读取自动热机实时信息
     * @param param 自动热机参数
     * @return 0-成功
     */
    virtual int readWarmUpMachineInfo(WarmUpMachineInfo &param) = 0;

    /**
     * @brief 读取电机实时过热率
     * @param overheat 过热率
     * @return 0-成功
     */
    virtual int readMotorOverheatRatio(double overheat[AXIS_NUM]) = 0;

    /**
     * @brief 读取温度校准状态
     * @param state 状态
     * @return 0-成功
     */
    virtual int readTemperatrueCalibState(bool &state) = 0;

    /**
     * @brief 读取当前机型是否支持温升保护功能
     * @param supFlag 是否支持
     * @return 0-成功
     */
    virtual int readOverHeatSupportState(bool &supFlag) = 0;

    /**
     * @brief 读取各轴过热率，用于判断其是否支持温度功能
     * @param state 状态
     * @return 0-成功
     */
    virtual int readSupportHeatState(bool state[AXIS_NUM]) = 0;

    /**
     * @brief 设置是否开启了自动热机功能
     * @param status 自动热机状态
     */
    virtual void setWarmMachineActiveStatus(bool status) = 0;

    /**
     * @brief 获取自动热机功能开启状态
     * @return true-开启
     */
    virtual bool getWarmMachineActiveStatus() = 0;
#pragma endregion

#pragma region 环境参数
    /**
     * @brief 读取环境温度
     * @param dTemperature 温度
     * @param calibState 校准标志
     * @param calibTemperature 校准数据
     * @return 0-成功
     */
    virtual int readEnvironmentTemperature(double &dTemperature, int16u &calibState, int16s calibTemperature[8]) = 0;

    /**
     * @brief 写入环境温度
     * @param calibFlag 校准标志
     * @param temperature 温度
     * @return
     */
    virtual int writeEnvironmentTemperature(int16u calibState, double dTemperature) = 0;

    // 环境参数权限检查
    virtual bool checkEnvironmentSavePermission() = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
