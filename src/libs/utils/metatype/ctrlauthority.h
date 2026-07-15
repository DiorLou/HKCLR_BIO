#pragma once

enum InoCtrlAuthority {
    InoCtrlAuthority_Unknown = -1,
    InoCtrlAuthority_TeachPad,
    InoCtrlAuthority_InorobShop,
    InoCtrlAuthority_Ethernet,
    InoCtrlAuthority_IO,
    InoCtrlAuthority_Modbus,
    InoCtrlAuthority_IO_AUTO,
    InoCtrlAuthority_NoCtrl
};

/**
 * @brief 远程IO单元控制权子模式
 */
enum class InoRmtIoSubMode : unsigned char {
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
enum class InoRmtRunLineResetMode : unsigned char {
    // 切换模式重置行号
    YES = 0,
    // 切换模式不重置行号
    NO,
    // 未知
    UNKNOWN,
};

/**
 * @brief 远程IO单元控制权下，上位机应用软件停止按钮使能策略
 */
enum class InoRmtStopEnableState : unsigned char {
    // 非使能
    DISENABLE = 0,
    // 使能
    ENABLE,
    // 未知
    UNKNOWN,
};
