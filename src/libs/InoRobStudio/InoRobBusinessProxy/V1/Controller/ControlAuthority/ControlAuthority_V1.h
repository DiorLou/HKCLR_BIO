#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

/**
 * @brief 控制权类型
 */
enum class CtrlAuthority_V1 : int16s
{
    // 机器人上位机软件（PC编程平台或示教器）
    TEACHPAD_V1 = 0,
    // 二次开发软件（InoRobShop，应该已弃用了）
    INOROBSHOP_V1,
    // 远程以太网
    RMT_ETHERNET_V1,
    // 远程IO
    RMT_IO_V1,
    // 远程Modbus
    RMT_MODBUS_V1,
    // 远程IO（仅自动模式生效）
    RMT_IO_AUTO_V1,
    // 无控制权
    NOCTRL_V1,
};

/**
 * @brief 远程IO单元控制权子模式
 */
enum class RmtIoSubMode_V1 : int8u
{
    // 自动手动模式均生效
    AUTO_AND_MANUAL_V1 = 0,
    // 仅自动模式下生效
    ONLYAUTO_V1,
    // 未知
    UNKNOWN_V1,
};

/**
 * @brief 远程IO单元控制权下，切换自动手动模式是否重置运行行号策略
 */
enum class RmtRunLineResetMode_V1 : int8u
{
    // 切换模式重置行号
    YES_V1 = 0,
    /// 切换模式不重置行号
    NO_V1,
    // 未知
    UNKNOWN_V1,
};

/**
 * @brief 远程IO单元控制权下，上位机应用软件停止按钮使能策略
 */
enum class RmtStopEnableState_V1 : int8u
{
    // 非使能
    DISENABLE_V1 = 0,
    // 使能
    ENABLE_V1,
    // 未知
    UNKNOWN_V1,
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS ControlAuthority_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static CtrlAuthority_V1 CtrlAuthority_ToProxy(CtrlAuthority ctrlAuthority);
    static CtrlAuthority CtrlAuthority_FromProxy(CtrlAuthority_V1 ctrlAuthority_V1);

    static RmtIoSubMode_V1 RmtIoSubMode_ToProxy(RmtIoSubMode rmtIoSubMode);
    static RmtIoSubMode RmtIoSubMode_FromProxy(RmtIoSubMode_V1 rmtIoSubMode_V1);

    static RmtRunLineResetMode_V1 RmtRunLineResetMode_ToProxy(RmtRunLineResetMode rmtRunLineResetMode);
    static RmtRunLineResetMode RmtRunLineResetMode_FromProxy(RmtRunLineResetMode_V1 rmtRunLineResetMode_V1);

    static RmtStopEnableState_V1 RmtStopEnableState_ToProxy(RmtStopEnableState rmtStopEnableState);
    static RmtStopEnableState RmtStopEnableState_FromProxy(RmtStopEnableState_V1 rmtStopEnableState_V1);

#pragma endregion

#pragma region 构造与析构

private:
    IControlAuthority *_controlAuthority = nullptr;

public:
    ControlAuthority_V1(IControlAuthority *controlAuthority);
    ~ControlAuthority_V1();

#pragma endregion

#pragma region 业务逻辑

private:
    void sigCtrlAuthorityChangedHandler(CtrlAuthority data);

public:
    /**
     * @brief 切换控制权
     * @param authority 输入，目标控制权
     * @param speed 输入，预设速度（目前仅远程IO和远程Modbus需要设置，其他控制权即使输入，也不会设置到控制器）
     * @return 成功返回0，其他请见错误码
     */
    int changeAuthority(CtrlAuthority_V1 authority, int speed);
    rsignal<CtrlAuthority_V1> sigCtrlAuthorityChanged;

    /**
     * @brief 设置当前控制权
     * @param authority 输入，当前控制权
     */
    void setCurrentAuthority(CtrlAuthority_V1 authority);
    /**
     * @brief 获取当前控制权   ----   已测
     */
    CtrlAuthority_V1 getCurrentAuthority();

    /**
     * @brief 当前是否正在执行切换控制权的动作   ----   已测
     */
    bool isChangingAuthority();

    /**
     * @brief 向控制器下发切换控制权的命令   ----   已测
     * @param authority 输入，目标控制权
     * @return 成功返回0，其他请见错误码
     */
    int writeAuthority(CtrlAuthority_V1 authority);
    /**
     * @brief 从控制器获取当前控制权   ----   已测
     * @param authority 输出，当前控制权
     * @return 成功返回0，其他请见错误码
     */
    int readAuthority(CtrlAuthority_V1 &authority);
    /**
     * @brief 向控制器下发远程控制权的预设速度   ----   已测
     * @param speed 输入，速度
     * @return 成功返回0，其他请见错误码
     */
    int writeRmtDefaultSpeed(int speed);
    /**
     * @brief 从控制器获取远程控制权的预设速度   ----   已测
     * @param speed 输出，速度
     * @return 成功返回0，其他请见错误码
     */
    int readRmtDefaultSpeed(int &speed);

    /**
     * @brief 向控制器下发切换远程IO单元控制权子模式的命令
     * @param mode 输入，远程IO单元控制权子模式
     * @return 成功返回0，其他请见错误码
     */
    int writeRmtIoSubMode(RmtIoSubMode_V1 mode);
    /**
     * @brief 从控制器获取当前远程IO单元控制权子模式
     * @param mode 输出，远程IO单元控制权子模式
     * @return 成功返回0，其他请见错误码
     */
    int readRmtIoSubMode(RmtIoSubMode_V1 &mode);
    /**
     * @brief 写入当前选择的行号重置策略(仅作用于远程IO控制权下，切换模式时)
     * @param mode 输入，行号重置策略
     * @return 成功返回0，其他请见错误码
     */
    int writeRmtRunLineResetMode(RmtRunLineResetMode_V1 mode);
    /**
     * @brief 读取当前选择的行号重置策略(仅作用于远程IO控制权下，切换模式时)
     * @param mode 输出，行号重置策略
     * @return 成功返回0，其他请见错误码
     */
    int readRmtRunLineResetMode(RmtRunLineResetMode_V1 &mode);
    /**
     * @brief 写入机器人应用软件停止使能策略(仅作用于远程IO控制权下)
     * @param state 输入，停止按钮使能策略
     * @return 成功返回0，其他请见错误码
     */
    int writeRmtStopEnableState(RmtStopEnableState_V1 state);
    /**
     * @brief 读取机器人应用软件停止使能策略(仅作用于远程IO控制权下)
     * @param state 输出，停止按钮使能策略
     * @return 成功返回0，其他请见错误码
     */
    int readRmtStopEnableState(RmtStopEnableState_V1 &state);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
