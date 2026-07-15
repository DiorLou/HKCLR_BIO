#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS BacklashCompensationDefault : public IBacklashCompensation
{
    Q_OBJECT

public:
    // 构造与析构
    BacklashCompensationDefault(string name, IDataSrvBase *dataService, QObject *parent /* = nullptr*/);
    ~BacklashCompensationDefault();
    void init() override;

    /*!
     * \brief 恢复出厂值
     */
    int restoreFactorySettings() override;


    /*!
     * \brief 开始间隙辨识
     */
    int startBacklashIdentification(BacklashIdentifyCalcTraj& calcTraj) override;

    /*!
     * \brief 终止间隙辨识
     */
    int endBacklashIdentification() override;

    /*!
     * \brief 获取辨识结果
     */
    int getRecognitionResult(float& f32Backlash) override;

    /*!
     * \brief 设置间隙辨识轨迹速度
     */
    int setBacklashIdentTraj4Vel(BacklashIdentTrajVel trajVel) override;

    /*!
     * \brief 设置间隙补偿状态
     */
    int setBacklashCompensationStatus(const BacklashIdentifyResult& coulombArray) override;

    /*!
     * \brief 获取间隙参数
     */
    int getBacklashParams(BacklashIdentifyResult& coulombArray) override;

private:
    IDataSrvBase *_pDataService = nullptr;
    IConnection *_pConnection = nullptr;
    ILanguage *_pLanguage = nullptr;
    IMonitor *_pMonitor = nullptr;

};
}
