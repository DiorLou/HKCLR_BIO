#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
const double DOUBLE_MIN_VALUE_WHEN_PARAM_NODE_IS_EMPTY_V1 = -999999999.999;
const double DOUBLE_MAX_VALUE_WHEN_PARAM_NODE_IS_EMPTY_V1 = 999999999.999;

const int INT_MIN_VALUE_WHEN_PARAM_NODE_IS_EMPTY_V1 = -999999999;
const int INT_MAX_VALUE_WHEN_PARAM_NODE_IS_EMPTY_V1 = 999999999;

// 机型参数
class INOROBBUSINESSPROXY_CLASS RobotParamRange_V1
{
#pragma region 构造与析构

private:
    IRobotParamRange *_robotParamRange = nullptr;

public:
    RobotParamRange_V1(IRobotParamRange *robotParamRange);
    ~RobotParamRange_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 更新参数范围
    void refreshParamRangeDataFromFile();

    // 获取参数最小值(double类型)
    double getDoubleMinValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最大值(double类型)
    double getDoubleMaxValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最小值(int类型)
    int getIntMinValue(const std::string &paraStructName, const std::string &paramName);

    // 获取参数最大值(int类型)
    int getIntMaxValue(const std::string &paraStructName, const std::string &paramName);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
