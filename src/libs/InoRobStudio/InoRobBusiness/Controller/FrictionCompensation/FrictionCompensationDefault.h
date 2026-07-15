#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS FrictionCompensationDefault : public IFrictionCompensation
{
    Q_OBJECT

public:
    // 构造与析构
    FrictionCompensationDefault(string name, IDataSrvBase *dataService, QObject *parent /* = nullptr*/);
    ~FrictionCompensationDefault();
    void init() override;

    /*!
     * \brief 恢复出厂值
     */
    int restoreFactorySettings() override;

    /*!
     * \brief 根据起点获取摩擦推荐轨迹点
     */
    int getRecommendedTrajectoryEndPoints(FricIdentifyRecommendTraj& jointAngles) override;

    /*!
     * \brief 开始摩擦辨识
     */
    int startFricIdentification(FricIdentifyCalcTraj& calcTraj) override;

    /*!
     * \brief 终止摩擦辨识
     */
    int endFricIdentification() override;

    /*!
     * \brief 获取辨识结果
     */
    int getRecognitionResult(FricCompParam& coulombArray) override;

    /*!
     * \brief 应用辨识结果
     */
    int setRecognitionResult(ToArmFricParam coulombArray) override;

    /*!
     * \brief 设置摩擦辨识轨迹速度
     */
    int setFricIdentTraj4Vel(FricIdentTrajVel trajVel) override;

    /*!
     * \brief 设置摩擦补偿状态
     */
    int setFricCompensationStatus(const FricIdentifyResult& coulombArray) override;

    /*!
     * \brief 获取库伦摩擦参数
     */
    int getCoulombFrictionParams(FricIdentifyResult& coulombArray) override;

    //int AT_SetFricIdentVel(AT_STSetFricIdentTrajVel at_fricIdentTrajVel);

private:
    IDataSrvBase *_pDataService = nullptr;
    IConnection *_pConnection = nullptr;
    ILanguage *_pLanguage = nullptr;
    IMonitor *_pMonitor = nullptr;
};
}
