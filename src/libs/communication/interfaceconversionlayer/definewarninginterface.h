#pragma once

#include "communication_global.h"

namespace InoRobBusiness
{
class IController;
class IProject;
}  // namespace InoRobBusiness

class Communication;

class COMMUNICATION_EXPORT DefineWarningInterface
{
public:
    DefineWarningInterface()
    {
    }

    virtual Communication *comm() = 0;
    virtual InoRobBusiness::IController *controller() = 0;

    // 从文件中读取用户自定义报警数据
    bool readWarnings();
    // 将用户自定义报警数据写入到文件中
    bool saveWarnings();
    // 获取用户自定义报警数据
    std::vector<std::string> getWarnings();
    // 修改指定序号的报警内容
    bool modifyWarning(int index, const QString &warning);
    // 检查报警内容是否合格
    bool isWarningValid(const QString &warning);
};
