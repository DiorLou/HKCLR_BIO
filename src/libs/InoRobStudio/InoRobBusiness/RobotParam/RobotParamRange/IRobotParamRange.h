#pragma once
#include "dllspec.h"
#include <QObject>
const double DOUBLE_MIN_VALUE_WHEN_PARAM_NODE_IS_EMPTY = -999999999.999;
const double DOUBLE_MAX_VALUE_WHEN_PARAM_NODE_IS_EMPTY = 999999999.999;

const int INT_MIN_VALUE_WHEN_PARAM_NODE_IS_EMPTY = -999999999;
const int INT_MAX_VALUE_WHEN_PARAM_NODE_IS_EMPTY = 999999999;

namespace InoRobBusiness
{
/**
 * @brief 机型参数
 */
class INOROBBUSINESS_CLASS IRobotParamRange : public QObject
{
    Q_OBJECT
public:
    virtual ~IRobotParamRange()
    {
    }

    // 更新参数范围
    virtual void refreshParamRangeDataFromFile() = 0;

    // 获取参数最小值(double类型)
    virtual double getDoubleMinValue(const std::string &paraStructName, const std::string &paramName) = 0;

    // 获取参数最大值(double类型)
    virtual double getDoubleMaxValue(const std::string &paraStructName, const std::string &paramName) = 0;

    // 获取参数最小值(int类型)
    virtual int getIntMinValue(const std::string &paraStructName, const std::string &paramName) = 0;

    // 获取参数最大值(int类型)
    virtual int getIntMaxValue(const std::string &paraStructName, const std::string &paramName) = 0;

    // 获取机型参数默认值(string类型)
    virtual std::string getDefaultParamValue(const std::string &paraStructName, const std::string &paramName) = 0;
};
}  // namespace InoRobBusiness
