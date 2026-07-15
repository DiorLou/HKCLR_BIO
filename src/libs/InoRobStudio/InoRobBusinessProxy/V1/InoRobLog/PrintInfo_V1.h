#pragma once
#include "dllspec.h"
#include "../../../InoRobLog/PrintInfo/PrintInfo.h"
using namespace InoRobLog;

namespace InoRobBusinessProxy
{
/**
 * @brief 消息输出条件
 */
enum MsgCond_V1 : unsigned short
{
    PRINT_V1 = 0b001,              // 打印输出
    WRITE_V1 = 0b010,              // 日志保存
    POPUP_V1 = 0b100,              // 弹出提示
    PRINT_WRITE_V1 = 0b011,        // 打印并写
    PRINT_POPUP_V1 = 0b101,        // 打印并弹出
    WRITE_POPUP_V1 = 0b110,        // 写并弹出
    PRINT_WRITE_POPUP_V1 = 0b111,  // 打印、写、弹出
    ALL_V1 = 0xFF                  // 全部
};

/**
 * @brief 消息输出类型
 */
enum class MsgType_V1 : unsigned short
{
    MESSAGE_OPUTPUT_V1 = 0,  // 消息
    SUCCESS_OPUTPUT_V1,      // 成功
    WARNING_OPUTPUT_V1,      // 警告
    ERROR_OPUTPUT_V1         // 错误
};

class INOROBBUSINESSPROXY_CLASS PrintInfo_V1
{
#pragma region 数据转换

public:
    static MsgCond_V1 MsgCond_ToProxy(MsgCond msgCond);
    static MsgCond MsgCond_FromProxy(MsgCond_V1 msgCondV1);

    static MsgType_V1 MsgType_ToProxy(MsgType msgType);
    static MsgType MsgType_FromProxy(MsgType_V1 msgTypeV1);

#pragma endregion

#pragma region 业务逻辑

public:
    static void outputInfoForPlugin(MsgCond_V1 type, std::string &msg);
    static void outputInfoForPlugin(MsgCond_V1 type, QString msg);

    static void outputWarningForPlugin(MsgCond_V1 type, std::string &msg);
    static void outputWarningForPlugin(MsgCond_V1 type, QString msg);

    static void outputErrorForPlugin(MsgCond_V1 type, std::string &msg);
    static void outputErrorForPlugin(MsgCond_V1 type, QString msg);

    static void outputSuccessForPlugin(MsgCond_V1 type, std::string &msg);
    static void outputSuccessForPlugin(MsgCond_V1 type, QString msg);

    static void outputWaitingForPlugin(std::string &msg);
    static void outputWaitingForPlugin(QString msg);

    static void outputCloseInfoForPlugin(MsgCond_V1 condType, MsgType_V1 msgType, std::string &msg);
    static void outputCloseInfoForPlugin(MsgCond_V1 condType, MsgType_V1 msgType, QString msg);

    static void printMessageInfoForPlugin(std::string &msg);
    static void printMessageInfoForPlugin(QString msg);

    static void printWarningInfoForPlugin(std::string &msg);
    static void printWarningInfoForPlugin(QString msg);

    static void printErrorInfoForPlugin(std::string &msg);
    static void printErrorInfoForPlugin(QString msg);

#pragma endregion
};

}  // namespace InoRobBusinessProxy
