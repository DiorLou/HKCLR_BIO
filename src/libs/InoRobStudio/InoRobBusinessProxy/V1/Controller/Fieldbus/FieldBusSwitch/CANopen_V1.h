#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS CANopen_V1
{
#pragma region 构造与析构

private:
    ICANopenSwitch *_canOpenSwitch = nullptr;

public:
    CANopen_V1(ICANopenSwitch *canOpenSwitch);
    ~CANopen_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 将CANopen配置文件放入控制器中
     * @param filePath 即将导入的配置文件的完整路径
     * @param fileName 即将导入的配置文件的文件名称
     * @return
     */
    int putCANopenFileIntoController(const std::string &filePath, const std::string &fileName);

    /**
     * @brief 检查CANopen总线操作权限
     * @return true-权限符合
     */
    bool checkCANopenOperatePermission();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
