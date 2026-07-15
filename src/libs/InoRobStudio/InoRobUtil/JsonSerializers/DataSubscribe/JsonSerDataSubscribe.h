#pragma once

#include "IInoRobUtil.h"
#include "DataSubscibeTypes.h"

namespace InoRobUtil
{
/**
 * @brief 数据订阅序列化处理类
 */
class INOROBUTIL_CLASS JsonSerDataSubscribe
{
public:
    /**
     * @brief 序列化变量监控
     * @param[in] obj 变量监控信息
     * @param[out] jsonStr json字符串
     * @return true成功 false失败
     */
    static bool serializeVarMonitor(VarMonitorJson obj, std::string &jsonStr);

    /**
     * @brief 反序列化变量监控
     * @param[in] jsonStr json字符串
     * @param[out] dataObj 变量监控信息
     * @return true成功 false失败
     */
    static bool deserializeVarMonitor(const std::string &jsonStr, VarMonitorJson &dataObj);

    /**
     * @brief 反序列化控制器消息
     * @param jsonStr[in] json字符串
     * @param msgInfo[out] 控制器消息
     * @return true成功 false失败
     */
    static bool deserializeRcMessage(const std::string &jsonStr, RcMessageJson &msgInfo);
};
}  // namespace InoRobUtil
