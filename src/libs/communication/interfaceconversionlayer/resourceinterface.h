#pragma once

#include "communication_global.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT ResourceInterface
{
public:
    ResourceInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    /**
     * @brief 设置电流调度
     * @param scheduler true调度 false不调度
     */
    void setElectricScheduler(bool scheduler);

    /**
     * @brief 设置平均负载率调度
     * @param scheduler true调度 false不调度
     */
    void setAvgLoadRateScheduler(bool scheduler);

    /**
     * @brief 设置过载率调度
     * @param scheduler true调度 false不调度
     */
    void setOverLoadScheduler(bool scheduler);

    /**
     * @brief 设置过热率调度
     * @param scheduler true调度 false不调度
     */
    void setOverHeatScheduler(bool scheduler);

    /**
     * @brief 读取实时电流值(单位百分比)
     * @param 实时电流值
     * @return ERR_OK为成功，其它请见错误码
     */
    int readActCurrent(std::vector<double> &actualCurrent);

    /**
     * @brief 读历史电流最大值（单位百分比）
     * @param 获取数据
     * @return ERR_OK为成功，其它请见错误码
     */
    int readHisMaxCurrent(std::vector<double> &maxCurrent);

    /**
     * @brief 重置历史最大电流值
     * @return ERR_OK为成功，其它请见错误码
     */
    int resetHisMaxCurrent();

    /**
     * @brief 读取实时平均负载率（单位百分比）
     * @param 获取数据
     * @return ERR_OK为成功，其它请见错误码
     */
    int readActLoadrate(std::vector<double> &actualLoad);

    /**
     * @brief 读取实时过载率（单位百分比）
     * @param 获取数据
     * @return ERR_OK为成功，其它请见错误码
     */
    int readActualOverLoad(std::vector<double> &actualOverLoad);

    /**
     * @brief 读取过载率最大值（单位百分比）
     * @param 获取数据
     * @return ERR_OK为成功，其它请见错误码
     */
    int readMaxOverLoad(std::vector<double> &maxOverLoad);

    /**
     * @brief 重置过载率最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    int resetMaxOverLoad();

    /**
     * @brief 读取过热率（单位百分比）
     * @param 获取数据
     * @return ERR_OK为成功，其它请见错误码
     */
    int readOverHeat(std::vector<double> &overHeat);

    int readEmgTrigMethod(quint8 &iMethod);
    int saveEmgTrigMethod(quint16 iMethod);

    int saveEmgStopMode(quint8 nMode, quint8 nSecondMode);
    int readEmgStopMode(quint8 &nMode, quint8 &nSecondMode);

    void setModbusConnectScheduler(const bool scheduler);
    void setEthernetIPScheduler(const bool scheduler);
    void setEtherCatScheduler(const bool scheduler);
};
