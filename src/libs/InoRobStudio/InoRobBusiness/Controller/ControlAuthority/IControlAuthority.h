#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
#pragma region 常量与数据类型

/**
 * @brief 控制权类型
 */
enum class CtrlAuthority : int16s
{
    // 机器人上位机软件（PC编程平台或示教器）
    TEACHPAD = 0,
    // 二次开发软件（InoRobShop，应该已弃用了）
    INOROBSHOP,
    // 远程以太网
    RMT_ETHERNET,
    // 远程IO
    RMT_IO,
    // 远程Modbus
    RMT_MODBUS,
    // 远程IO（仅自动模式生效）
    RMT_IO_AUTO,
#ifdef COBOT
    // 拖动示教权限
    DragTeach,
#endif
    // 无控制权
    NOCTRL,
};

/**
 * @brief 远程IO单元控制权子模式
 */
enum class RmtIoSubMode : int8u
{
    // 自动手动模式均生效
    AUTO_AND_MANUAL = 0,
    // 仅自动模式下生效
    ONLYAUTO,
    // 未知
    UNKNOWN,
};

/**
 * @brief 远程IO单元控制权下，切换自动手动模式是否重置运行行号策略
 */
enum class RmtRunLineResetMode : int8u
{
    // 切换模式重置行号
    YES = 0,
    /// 切换模式不重置行号
    NO,
    // 未知
    UNKNOWN,
};

/**
 * @brief 远程IO单元控制权下，上位机应用软件停止按钮使能策略
 */
enum class RmtStopEnableState : int8u
{
    // 非使能
    DISENABLE = 0,
    // 使能
    ENABLE,
    // 未知
    UNKNOWN,
};

#pragma endregion

/*
    控制权管理基类
    Create by lcm at 2024/04/11 创建。
*/
class INOROBBUSINESS_CLASS IControlAuthority : public QObject
{
    Q_OBJECT

public:
    virtual ~IControlAuthority()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**
     * @brief 切换控制权
     * @param authority 输入，目标控制权
     * @param speed 输入，预设速度（目前仅远程IO和远程Modbus需要设置，其他控制权即使输入，也不会设置到控制器）
     * @return 成功返回0，其他请见错误码
     */
    virtual int changeAuthority(CtrlAuthority authority, int speed) = 0;

    /**
     * @brief 设置当前控制权
     * @param authority 输入，当前控制权
     */
    virtual void setCurrentAuthority(CtrlAuthority authority) = 0;
    /**
     * @brief 获取当前控制权
     */
    virtual CtrlAuthority getCurrentAuthority() = 0;

    /**
     * @brief 当前是否正在执行切换控制权的动作
     */
    virtual bool isChangingAuthority() = 0;

    /**
     * @brief 向控制器下发切换控制权的命令
     * @param authority 输入，目标控制权
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeAuthority(CtrlAuthority authority) = 0;
    /**
     * @brief 从控制器获取当前控制权
     * @param authority 输出，当前控制权
     * @return 成功返回0，其他请见错误码
     */
    virtual int readAuthority(CtrlAuthority &authority) = 0;
    /**
     * @brief 向控制器下发远程控制权的预设速度
     * @param speed 输入，速度
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeRmtDefaultSpeed(int speed) = 0;
    /**
     * @brief 从控制器获取远程控制权的预设速度
     * @param speed 输出，速度
     * @return 成功返回0，其他请见错误码
     */
    virtual int readRmtDefaultSpeed(int &speed) = 0;

    /**
     * @brief 向控制器下发切换远程IO单元控制权子模式的命令
     * @param mode 输入，远程IO单元控制权子模式
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeRmtIoSubMode(RmtIoSubMode mode) = 0;
    /**
     * @brief 从控制器获取当前远程IO单元控制权子模式
     * @param mode 输出，远程IO单元控制权子模式
     * @return 成功返回0，其他请见错误码
     */
    virtual int readRmtIoSubMode(RmtIoSubMode &mode) = 0;
    /**
     * @brief 写入当前选择的行号重置策略(仅作用于远程IO控制权下，切换模式时)
     * @param mode 输入，行号重置策略
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeRmtRunLineResetMode(RmtRunLineResetMode mode) = 0;
    /**
     * @brief 读取当前选择的行号重置策略(仅作用于远程IO控制权下，切换模式时)
     * @param mode 输出，行号重置策略
     * @return 成功返回0，其他请见错误码
     */
    virtual int readRmtRunLineResetMode(RmtRunLineResetMode &mode) = 0;
    /**
     * @brief 写入机器人应用软件停止使能策略(仅作用于远程IO控制权下)
     * @param state 输入，停止按钮使能策略
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeRmtStopEnableState(RmtStopEnableState state) = 0;
    /**
     * @brief 读取机器人应用软件停止使能策略(仅作用于远程IO控制权下)
     * @param state 输出，停止按钮使能策略
     * @return 成功返回0，其他请见错误码
     */
    virtual int readRmtStopEnableState(RmtStopEnableState &state) = 0;

    /**
     * @brief 读取机器人0编程状态
     * @param mode
     * @return
     */
    virtual bool getZeroProgramMode(int16u &mode) = 0;


Q_SIGNALS:
    // 连接过程描述信息
    void sigICtrlAuthorityChanged(CtrlAuthority authority);
};
}  // namespace InoRobBusiness
