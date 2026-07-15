#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
// 轴编号ID
enum DeviceType : int32s
{
    LIFE_DEVICE_ERROR = 0,    // 错误设备
    LIFE_DEVICE_REDUCER = 1,  // 减速机
    LIFE_DEVICE_SCREW = 2,    // 丝杆
};

/*!
 * \brief  寿命核算（29版本）, 预维保下的子类
 * \author created by mzw
 */
class INOROBBUSINESS_CLASS IRemainLifeCalculate : public QObject
{
    Q_OBJECT
public:
    virtual ~IRemainLifeCalculate()
    {
    }

#pragma region 减速机寿命核算
    /**
     * @brief 读取设备寿命功能配置
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param status 返回状态， 0-成功，1-参数非法，2-该状态下不允许读写
     * @param plcConfig 寿命配置参数
     * @return 0-成功
     */
    virtual int readDevicePLCConfig(int8u deviceType, int8u &status, Device_Life_Config &plcConfig) = 0;

    /**
     * @brief 写入设备寿命配置
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param status 返回状态， 0-成功，1-参数非法，2-该状态下不允许读写
     * @param plcConfig 寿命配置参数
     * @return 0-成功
     */
    virtual int writeDevicePLCConfig(int8u deviceType, int8u &status, Device_Life_Config &plcConfig) = 0;

    /**
     * @brief 开始采集设备数据
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param status 返回状态， 0-成功，1-参数非法，2-该状态下不允许读写
     * @return 0-成功
     */
    virtual int startCollectDeviceData(int8u deviceType, int8u &status) = 0;

    /**
     * @brief 终止采集设备数据
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param status 返回状态， 0-成功，1-参数非法，2-该状态下不允许读写
     * @return 0-成功
     */
    virtual int stopCollectDeviceData(int8u deviceType, int8u &status) = 0;

    /**
     * @brief 读取设备寿命结果
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param status 返回状态， 0-成功，1-参数非法，2-该状态下不允许读写
     * @param deviceResult 设备结果
     * @return 0-成功
     */
    virtual int readDeviceLifeResult(int8u deviceType, int8u &status, DEVICE_ALLAXIS_RESULT &deviceResult) = 0;

    /**
     * @brief 重置设备寿命数据
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @return 0-成功
     */
    virtual int resetDeviceLifeData(int8u deviceType) = 0;

    /**
     * @brief 读取本机型是否支持寿命预测功能
     * @param deviceType 设备类型，1-减速机，2-丝杆
     * @param support 0-不支持，1-支持
     * @return 0-成功
     */
    virtual int readRobotIsSupport(int8u deviceType, int8u &support) = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
