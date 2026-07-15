#pragma once
#include "IRemainLifeCalculate.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RemainLifeCalculateDefault : public IRemainLifeCalculate
{
    Q_OBJECT
private:
    // 依赖注入
    IDataSrvBase *_pDataService = nullptr;
    IMaintenance *_pMaintenance = nullptr;

public:
    RemainLifeCalculateDefault(IDataSrvBase *pDataService, IMaintenance *pMaintenance);
    ~RemainLifeCalculateDefault();

#pragma region 减速机寿命核算
    ///***** 减速机新版功能 ******///
    // 读取设备寿命功能配置
    int readDevicePLCConfig(int8u deviceType, int8u &status, Device_Life_Config &plcConfig);

    // 写入设备寿命配置
    int writeDevicePLCConfig(int8u deviceType, int8u &status, Device_Life_Config &plcConfig);

    // 开始采集设备数据
    int startCollectDeviceData(int8u deviceType, int8u &status);

    // 终止采集设备数据
    int stopCollectDeviceData(int8u deviceType, int8u &status);

    // 读取设备寿命结果
    int readDeviceLifeResult(int8u deviceType, int8u &status, DEVICE_ALLAXIS_RESULT &deviceResult);

    // 重置设备寿命数据
    int resetDeviceLifeData(int8u deviceType);

    // 读取本机型是否支持寿命预测功能
    int readRobotIsSupport(int8u deviceType, int8u &support);
#pragma endregion
};
}  // namespace InoRobBusiness
