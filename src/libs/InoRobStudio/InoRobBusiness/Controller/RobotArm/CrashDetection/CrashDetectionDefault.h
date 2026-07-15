#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "ICrashDetection.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS CrashDetectionDefault : public ICrashDetection
{
public:
    CrashDetectionDefault(IDataSrvBase *pDataSrv);
    virtual ~CrashDetectionDefault();

    int readColDetectPara(DevModeEnum mode, ColDetectPara &para) override;
    int writeColDetectPara(DevModeEnum mode, ColDetectPara &para) override;
    int readColDetectRecommadDegree(DevModeEnum mode, std::vector<double> &degree) override;
    int resetColDetectRecommadDegree(DevModeEnum mode) override;

    // 读取静态碰撞检测等级
    int readColDetectLevelPara(int16u &para) override;

    // 写入静态碰撞检测等级
    int writeColDetectLevelPara(int16u para) override;

#ifdef COBOT
    int readColDetectPara(CobotColDetectPara &para) override;
    int writeColDetectPara(CobotColDetectPara para) override;
    int readColDetectRecommadLevel(int16s &level) override;
    int resetColDetectRecommadLevel() override;
#endif

private:
    // 权限检查
    bool checkStatus();
    IDataSrvBase *_pDataService = nullptr;
};
}  // namespace InoRobBusiness
