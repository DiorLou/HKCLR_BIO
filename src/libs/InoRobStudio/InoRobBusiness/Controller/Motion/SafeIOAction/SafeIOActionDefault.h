#pragma once
#include "ISafeIOAction.h"
#include "IInoRobBusiness.h"
#include <nlohmann/json.hpp>

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS SafeIOActionDefault : public ISafeIOAction
{
public:
    SafeIOActionDefault(IDataSrvBase *dataService, IConnection *connection);
    ~SafeIOActionDefault();

    bool refreshSafeIOAction(SafeIOActionData &data) override;
    bool saveSafeIOAction(const SafeIOActionData &data) override;
    bool execSafeIOAction(const std::string &cmd, const unsigned char cmdFlag) override;
    bool importSafeIOActionFromFile(const std::string &fileName, SafeIOActionData &data) override;
    bool exportSafeIOActionToFile(const std::string &fileName, const SafeIOActionData &data) override;

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;
    // 连接
    IConnection *_pConnection = nullptr;

    // 检查权限
    bool checkPermission();

    // 获取控制器安全IO动作配置文件
    bool getControllerSafeIOActionConfigFile();
    // 下发控制器安全IO动作配置文件
    bool putControllerSafeIOActionConfigFile();

    // 序列化安全IO动作数据
    bool serializationSafeIOActionData(nlohmann::ordered_json &json, const SafeIOActionData &data);
    // 序列化安全IO动作Item
    bool serializationSafeIOActionItem(nlohmann::ordered_json &itemJson, const SafeIOActionItem &item);
    // 序列化安全IO动作安全区域
    bool serializationSafeIOActionSafeArea(nlohmann::ordered_json &safeAreaJson, const SafeIOActionSafeArea &safeArea);
    // 序列化安全IO动作到位动作
    bool serializationSafeIOActionExecItem(nlohmann::ordered_json &execItemJson, const SafeIOActionExecItem &execItem);
    // 序列化安全IO动作完成动作
    bool serializationSafeIOActionFinishItem(nlohmann::ordered_json &finishItemJson, const SafeIOActionFinishItem &finishItem);

    // 反序列化安全IO动作数据
    bool deserializationSafeIOActionData(const nlohmann::json &json, SafeIOActionData &data);
    // 序列化安全IO动作Item
    bool deserializationSafeIOActionItem(const nlohmann::json &itemJson, SafeIOActionItem &item);
    // 序列化安全IO动作安全区域
    bool deserializationSafeIOActionSafeArea(const nlohmann::json &safeAreaJson, SafeIOActionSafeArea &safeArea);
    // 序列化安全IO动作到位动作
    bool deserializationSafeIOActionExecItem(const nlohmann::json &execItemJson, SafeIOActionExecItem &execItem);
    // 序列化安全IO动作完成动作
    bool deserializationSafeIOActionFinishItem(const nlohmann::json &finishItemJson, SafeIOActionFinishItem &finishItem);
};
}  // namespace InoRobBusiness
