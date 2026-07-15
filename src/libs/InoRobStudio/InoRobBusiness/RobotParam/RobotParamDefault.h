#pragma once
#include "IRobotParam.h"
#include "GeneralMatch/GeneralMatchDefault.h"
#include "RobotParamRange/RobotParamRange.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RobotParamDefault : public IRobotParam
{
public:
    RobotParamDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~RobotParamDefault();
    void init() override;
    IGeneralMatch *getGeneralMatch() const override;
    IRobotParamRange *getRobotParamRange() const override;

private:
    IDataSrvBase *_pDataSrv = nullptr;
    IConnection *_pConnection = nullptr;
    IMonitor *_pMonitor = nullptr;

    IGeneralMatch *_pGeneralMatch;        // 通配
    IRobotParamRange *_pRobotParamRange;  // 机型参数范围
};
}  // namespace InoRobBusiness
