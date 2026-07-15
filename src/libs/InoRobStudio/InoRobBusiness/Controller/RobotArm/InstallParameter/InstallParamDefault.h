#pragma once
#include "IInstallParameter.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS InstallParameter : public IInstallParameter
{
    Q_OBJECT

private:
    // 依赖注入
    IDataSrvBase *_pDataService = nullptr;
    IRobotArm *_pRobotArm = nullptr;

public:
    InstallParameter(IDataSrvBase *dataService, IRobotArm *robotArm);
    ~InstallParameter();

    int print();

#pragma region 臂上负载

    // 读取臂上负载数据
    int ReadArmLoad(int nLinkNo, ArmLoadPara &armload);

    // 写入臂上负载数据
    int WriteArmLoad(ArmLoadPara armload);

    // 检查臂上负载的修改权限
    bool checkArmLoadPermission();

#pragma endregion

#pragma region 自动热机
    // 保存自动热机参数
    int saveWarmUpMachineParam(WarmUpMachineParam &param);

    // 写入自动热机参数
    int writeWarmUpMachineParam(WarmUpMachineParam &param);

    // 保存热机参数权限
    bool checkSaveWarmMachinePermission();

    // 读取自动热机数据
    int readWarmUpMachineParam(WarmUpMachineParam &param);

    // 读取自动热机实时信息
    int readWarmUpMachineInfo(WarmUpMachineInfo &param);

    // 读取电机实时过热率
    int readMotorOverheatRatio(double overheat[AXIS_NUM]);

    // 读取温度校准状态
    int readTemperatrueCalibState(bool &state);

    // 读取当前机型是否支持温升保护功能
    int readOverHeatSupportState(bool &supFlag);

    // 读取各轴过热率，用于判断其是否支持温度功能
    int readSupportHeatState(bool state[AXIS_NUM]);

    // 设置是否开启了自动热机功能
    void setWarmMachineActiveStatus(bool status);

    // 获取自动热机功能开启状态
    bool getWarmMachineActiveStatus();
#pragma endregion

#pragma region 环境参数
    // 读取环境温度
    int readEnvironmentTemperature(double &dTemperature, int16u &calibState, int16s calibTemperature[8]);

    // 写入环境温度
    int writeEnvironmentTemperature(int16u calibState, double dTemperature);

    // 环境参数权限检查
    bool checkEnvironmentSavePermission();
#pragma endregion

private:
    bool _isWarmMachineActived = false;  // 自动热机开启状态
};
}  // namespace InoRobBusiness
