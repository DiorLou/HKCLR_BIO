#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
#include "../../../GlobalDataTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
/*!
 * \brief  安装参数抽象类, 机械臂下的子类
 * 2024/08/19
 */
class INOROBBUSINESSPROXY_CLASS InstallParam_V1
{
#pragma region 构造与析构

private:
    IInstallParameter *_installParameter = nullptr;

public:
    InstallParam_V1(IInstallParameter *installParameter);
    ~InstallParam_V1();

#pragma endregion

public:
    int print();

#pragma region 臂上负载

public:
    /**
     * @brief 读取臂上负载数据
     * @param nLinkNo 臂上负载号
     * @param armload 臂上负载数据
     * @return 0-成功
     */
    int ReadArmLoad(int nLinkNo, ArmLoadPara_V1 &armload);

    /**
     * @brief 写入臂上负载数据
     * @param armload 臂上负载数据
     * @return 0-成功
     */
    int WriteArmLoad(ArmLoadPara_V1 armload);

    /**
     * @brief 检查臂上负载的修改权限
     * @return true-符合权限, false-不符合权限
     */
    bool checkArmLoadPermission();

#pragma endregion

#pragma region 自动热机

public:
    /**
     * @brief 保存自动热机参数
     * @param param 自动热机参数
     * @return 0-成功
     */
    int saveWarmUpMachineParam(WarmUpMachineParam_V1 &param);

    /**
     * @brief 读取自动热机数据
     * @param param 自动热机参数
     * @return 0-成功
     */
    int readWarmUpMachineParam(WarmUpMachineParam_V1 &param);

    /**
     * @brief 保存热机参数权限
     * @return true-权限符合
     */
    bool checkSaveWarmMachinePermission();

    /**
     * @brief 读取自动热机实时信息
     * @param param 自动热机参数
     * @return 0-成功
     */
    int readWarmUpMachineInfo(WarmUpMachineInfo_V1 &param);

    /**
     * @brief 读取电机实时过热率
     * @param overheat 过热率
     * @return 0-成功
     */
    int readMotorOverheatRatio(double overheat[AXIS_NUM_V1]);

    /**
     * @brief 读取温度校准状态
     * @param state 状态
     * @return 0-成功
     */
    int readTemperatrueCalibState(bool &state);

    /**
     * @brief 读取当前机型是否支持温升保护功能
     * @param supFlag 是否支持
     * @return 0-成功
     */
    int readOverHeatSupportState(bool &supFlag);

    /**
     * @brief 读取各轴过热率，用于判断其是否支持温度功能
     * @param state 状态
     * @return 0-成功
     */
    int readSupportHeatState(bool state[AXIS_NUM_V1]);

    /**
     * @brief 设置是否开启了自动热机功能
     * @param status 自动热机状态
     */
    void setWarmMachineActiveStatus(bool status);

    /**
     * @brief 获取自动热机功能开启状态
     * @return true-开启
     */
    bool getWarmMachineActiveStatus();

#pragma endregion

#pragma region 环境参数

public:
    /**
     * @brief 读取环境温度
     * @param dTemperature 温度
     * @param calibState 校准标志
     * @param calibTemperature 校准数据
     * @return 0-成功
     */
    int readEnvironmentTemperature(double &dTemperature, int16u &calibState, int16s calibTemperature[8]);

    /**
     * @brief 写入环境温度
     * @param calibFlag 校准标志
     * @param temperature 温度
     * @return
     */
    int writeEnvironmentTemperature(int16u calibState, double dTemperature);

    // 环境参数权限检查
    bool checkEnvironmentSavePermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
