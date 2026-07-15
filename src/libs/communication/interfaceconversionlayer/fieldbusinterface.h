#pragma once

#include <QObject>
#include "communication_global.h"

namespace InoRobBusiness
{
class IController;
}  // namespace InoRobBusiness

class Communication;
class AbstractCmd;
/// @brief 控制器接口
class COMMUNICATION_EXPORT FieldBusInterface
{
public:
    FieldBusInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    /**
     * @brief 检查除当前总线外其他总线的激活状态
     * @param currFieldBus 0-modbus 1-ethernetip 2-ethercat
     * @return true-有其他总线处于激活状态
     */
    bool checkOtherFieldBusIsActive(int currFieldBus);
    void getAddressAssignMsg(AbstractCmd *cmd);
    void setAddressAssignMsg(AbstractCmd *cmd);

    void getProjectNoAssign(AbstractCmd *cmd);
    void setProjectNoAssign(AbstractCmd *cmd);

    void getPointFileNoAssign(AbstractCmd *cmd);
    void setPointFileNoAssign(AbstractCmd *cmd);

    // 下发主站文件
    void sendMasterConfigFile(AbstractCmd *cmd);
};
