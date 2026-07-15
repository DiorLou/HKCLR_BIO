#pragma once

#include <QObject>
#include "communication_global.h"
#include "generalmatchdefines.h"

namespace InoRobBusiness
{
class IController;
class IRobotParam;
}  // namespace InoRobBusiness

class Communication;

/// @brief 控制器接口
class COMMUNICATION_EXPORT GeneralMatchInterface
{
public:
    GeneralMatchInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;
    virtual InoRobBusiness::IRobotParam *robotParam() = 0;

    bool getGeneralMatchOpen();
    bool setGeneralMatchOpen(bool open);

    bool allowTracingGeneralMatch();
    int getGeneralMatchRecord(const std::string &fileName);

    bool getGeneralMatchInfo(CobotGeneralMatchInfo &retinfo);
    bool getRobotParamSyncStatus(CobotRobotParamSyncStatus &status);

    int startRobotParamSync(const std::string &info);

    int readRobotParamMatchInfo(std::string &info);
};
