#pragma once
#include "ICANopenSwitch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class CANopenDefault : public ICANopenSwitch
{
    Q_OBJECT
public:
    CANopenDefault(IDataSrvBase *dataService, IConnection *connection);
    ~CANopenDefault();

    // 将CANopen配置文件放入控制器中
    int putCANopenFileIntoController(const std::string &filePath, const std::string &fileName);

    // 检查CANopen总线操作权限
    bool checkCANopenOperatePermission();

private:
    // 告知控制器canopen的json文件发生变化，需重新加载
    int writeCanOpenJsonFileChange(char path[50]);

    // 通知控制器canopen组态文件更新
    int notifyControllerCANopenJsonChanged();

    // 检查配置文件名称是否有效
    bool checkCANopenFileNameIsValid(const std::string &fileName);

    IDataSrvBase *_pDataSrvBase = nullptr;
    IConnection *_pConnection = nullptr;

    // 本地文件目录
    static const std::string _localFilePath;

    // 控制器下的目录
    static const std::string _remoteFilePath;
};
}  // namespace InoRobBusiness
