#pragma once

#include "GlobalDataTypes.h"
#include "labeldata.h"
#include "communication_global.h"
#include "iostruct.h"
#include "Controller/BacklashCompensation/IBacklashCompensation.h"

namespace InoRobBusiness
{
class IWorkstation;
class IController;
class IProject;
class IResource;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
class COMMUNICATION_EXPORT BacklashCompensationInterface
{
public:
    BacklashCompensationInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // 获取间隙参数
    void getBacklashParams(AbstractCmd *cmd);

    // 设置间隙补偿状态
    bool setBacklashCompensationStatus(const InoRobBusiness::BacklashIdentifyResult &array);

    // 恢复出厂设置
    bool restoreBacklashFactorySettings();

    // 获取推荐轨迹端点
    // void getRecommendedTrajectoryEndPoints(AbstractCmd *cmd);

    // 开始间隙辨识
    void startBacklashIdentification(AbstractCmd *cmd);

    // 结束间隙辨识
    void endBacklashIdentification(AbstractCmd *cmd);

    // 获取辨识结果
    void getBacklashRecognitionResult(AbstractCmd *cmd);

    // 设置辨识结果
    // void setBacklashRecognitionResult(AbstractCmd *cmd);

private slots:
    void slot_CompleteBacklashIdentify();

};
