#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS LoadIdentifyDefault : public ILoadIdentify
{
    Q_OBJECT

public:
    LoadIdentifyDefault(string name, IDataSrvBase *dataSrv, QObject *parent = nullptr);
    virtual ~LoadIdentifyDefault();
    void init() override;
    virtual int startIdentify(const LoadIdentifyData &data) override;
    virtual int stopIdentify() override;
    virtual int readIdentifyData(LoadIdentifyData &data) override;
    virtual int readIdentifyStatus(IdentifyStatus &status) override;
    virtual int readIdentifyResult(LoadIdentifyResult &result) override;

    virtual IdentifyType getIdentifyType() override;
    virtual void setIdentifyType(const IdentifyType &type) override;
    virtual int readIdentifyTrajectoryFromRc(float trajPoint[6][6]) override;
    virtual int readIdentifyRecommenPoint(int pointIndex, LoadIdentifyRecommendTraj recommendTraj, float identifyPoint[6][6], bool isOneTraj) override;

    virtual int startSevenIdentify(const LoadIdentifyData &data) override;

private:
    bool checkTrack(const LoadIdentifyData &data);
    bool checkTrackV4R24C3(const int &robotAxisNum, const LoadIdentifyData &data);

private:
    IDataSrvBase *_pDataSrv = nullptr;
    IMonitor *_pMonitor = nullptr;
    IPosition *_pPosition = nullptr;
    IRobotArm *_pRobotArm = nullptr;
    IMechUnitManage *_pMechUnitManage = nullptr;

    IdentifyType _curType;
};
}  // namespace InoRobBusiness
