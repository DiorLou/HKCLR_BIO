#pragma once

constexpr int FIELDBUS_TOTAL_BIT = 13824;  // 总线总大小（Bit）
constexpr int FIELDBUS_TOTAL_BYTE = 1728;  // 总线总大小（Byte）
constexpr int FIELDBUS_TOTAL_WORD = 864;   // 总线总大小（Word）
constexpr int FIELDBUS_TOTAL_DWORD = 432;  // 总线总大小（DWord）

constexpr int STANDARD_IO_START_BIT = 0;    // 标准IO起始下标(以Bit参考)
constexpr int STANDARD_IO_END_BIT = 127;    // 标准IO终止下标(以Bit参考)
constexpr int FIELDBUS_IO_START_BIT = 512;  // 现场总线IO起始下标(以Bit参考)
constexpr int FIELDBUS_IO_END_BIT = 4607;   // 现场总线IO终止下标(以Bit参考)
constexpr int MEMORY_IO_START_BIT = 12800;  // 内存IO起始下标(以Bit参考)
constexpr int MEMORY_IO_END_BIT = 13823;    // 内存IO终止下标(以Bit参考)

constexpr int STANDARD_IO_START_BYTE = 0;   // 标准IO起始下标(以Byte参考)
constexpr int STANDARD_IO_END_BYTE = 15;    // 标准IO终止下标(以Byte参考)
constexpr int FIELDBUS_IO_START_BYTE = 64;  // 现场总线IO起始下标(以Byte参考)
constexpr int FIELDBUS_IO_END_BYTE = 575;   // 现场总线IO终止下标(以Byte参考)
constexpr int MEMORY_IO_START_BYTE = 1600;  // 内存IO起始下标(以Byte参考)
constexpr int MEMORY_IO_END_BYTE = 1727;    // 内存IO终止下标(以Byte参考)

constexpr int STANDARD_IO_START_WORD = 0;   // 标准IO起始下标(以Word参考)
constexpr int STANDARD_IO_END_WORD = 7;     // 标准IO终止下标(以Word参考)
constexpr int FIELDBUS_IO_START_WORD = 32;  // 现场总线IO起始下标(以Word参考)
constexpr int FIELDBUS_IO_END_WORD = 287;   // 现场总线IO终止下标(以Word参考)
constexpr int MEMORY_IO_START_WORD = 800;   // 内存IO起始下标(以Word参考)
constexpr int MEMORY_IO_END_WORD = 863;     // 内存IO终止下标(以Word参考)

constexpr int STANDARD_IO_START_DWORD = 0;   // 标准IO起始下标(以DWord参考)
constexpr int STANDARD_IO_END_DWORD = 3;     // 标准IO终止下标(以DWord参考)
constexpr int FIELDBUS_IO_START_DWORD = 16;  // 现场总线IO起始下标(以DWord参考)
constexpr int FIELDBUS_IO_END_DWORD = 143;   // 现场总线IO终止下标(以DWord参考)
constexpr int MEMORY_IO_START_DWORD = 400;   // 内存IO起始下标(以DWord参考)
constexpr int MEMORY_IO_END_DWORD = 431;     // 内存IO终止下标(以DWord参考)

namespace InoRobBusiness
{
enum FieldBusFunc_InBit : unsigned int
{
    PrgStart = 0x0000,     // 程序启动
    PrgStop,               // 程序停止
    PrgReset,              // 程序复位
    McEnable,              // 使能
    McEmergeStop,          // 急停
    McAlarmClear,          // 清除报警
    VelIncr,               // 速度加
    VelDecr,               // 速度减
    Homing,                // 原点回归
    ToTeachOrReplayMode,   // 手动/自动模式切换
    StartStaticTask,       // 启动所有静态任务
    CurOpPosTypeIn,        // 设置当前操作的点位类型, 0-位置点， 1-关节点
    DynBrakeSwitchIn,      // 动态制动
    ExSignalTriggerColli,  // 外部信号触发碰检
    Zero,                  // 回零
    RobotBodyPower,        // 机器人本体上下电

    J1XPosMov,  // 示教J1/X +
    J2YPosMov,  // 示教J2/Y +
    J3ZPosMov,  // 示教J3/Z +
    J4APosMov,  // 示教J4/A +
    J5PosMov,   // 示教J5 +
    J6PosMov,   // 示教J6 +

    ReserveIn2,  // 保留2，不在用户界面显示
    ReserveIn3,  // 保留3，不在用户界面显示

    J1XNegMov,  // 示教J1/X -
    J2YNegMov,  // 示教J2/Y -
    J3ZNegMov,  // 示教J3/Z -
    J4ANegMov,  // 示教J4/A -
    J5NegMov,   // 示教J5 -
    J6NegMov,   // 示教J6 -

    ReserveIn4,  // 保留4，不在用户界面显示
    ReserveIn5,  // 保留5，不在用户界面显示

    WrCurPosToP,  // 把当前位置写入当前P/JP变量
    ReserveA1,    // 把输入点位写入当前P/JP变量
    MoveToCurP,   // 直接运动到当前P/JP变量位置

    DigIOOutSet0,   // OUT[0]控制命令
    DigIOOutSet1,   // OUT[1]控制命令
    DigIOOutSet2,   // OUT[2]控制命令
    DigIOOutSet3,   // OUT[3]控制命令
    DigIOOutSet4,   // OUT[4]控制命令
    DigIOOutSet5,   // OUT[5]控制命令
    DigIOOutSet6,   // OUT[6]控制命令
    DigIOOutSet7,   // OUT[7]控制命令
    DigIOOutSet8,   // OUT[8]控制命令
    DigIOOutSet9,   // OUT[9]控制命令
    DigIOOutSet10,  // OUT[10]控制命令
    DigIOOutSet11,  // OUT[11]控制命令
    DigIOOutSet12,  // OUT[12]控制命令
    DigIOOutSet13,  // OUT[13]控制命令
    DigIOOutSet14,  // OUT[14]控制命令
    DigIOOutSet15,  // OUT[15]控制命令

    StationReserveInput1, //工位预约输入信号1
    StationReserveInput2, //工位预约输入信号2
    StationReserveInput3, //工位预约输入信号3
    StationReserveInput4, //工位预约输入信号4
    StationReserveInput5, //工位预约输入信号5
    StationReserveInput6, //工位预约输入信号6
    StationReserveInput7, //工位预约输入信号7
    StationReserveInput8, //工位预约输入信号8
};

enum FieldBusFunc_InWord : unsigned int
{
    RmtCtrlCmd = 0x2000,  // 远程控制命令

    RmtCtrlInputPara1,   // 输入参数1
    RmtCtrlInputPara2,   // 输入参数2
    RmtCtrlInputPara3,   // 输入参数3
    RmtCtrlInputPara4,   // 输入参数4
    RmtCtrlInputPara5,   // 输入参数5
    RmtCtrlInputPara6,   // 输入参数6
    RmtCtrlInputPara7,   // 输入参数7
    RmtCtrlInputPara8,   // 输入参数8
    RmtCtrlInputPara9,   // 输入参数9
    RmtCtrlInputPara10,  // 输入参数10
    RmtCtrlInputPara11,  // 输入参数11
    RmtCtrlInputPara12,  // 输入参数12
    RmtCtrlInputPara13,  // 输入参数13
    RmtCtrlInputPara14,  // 输入参数14
    RmtCtrlInputPara15,  // 输入参数15
    RmtCtrlInputPara16,  // 输入参数16
    RmtCtrlInputPara17,  // 输入参数17
    RmtCtrlInputPara18,  // 输入参数18
    RmtCtrlInputPara19,  // 输入参数19
    RmtCtrlInputPara20,  // 输入参数20
    RmtCtrlInputPara21,  // 输入参数21
    RmtCtrlInputPara22,  // 输入参数22
    RmtCtrlInputPara23,  // 输入参数23
    RmtCtrlInputPara24,  // 输入参数24
    RmtCtrlInputPara25,  // 输入参数25
    RmtCtrlInputPara26,  // 输入参数26
    RmtCtrlInputPara27,  // 输入参数27
    RmtCtrlInputPara28,  // 输入参数28
    RmtCtrlInputPara29,  // 输入参数29
    RmtCtrlInputPara30,  // 输入参数30
    RmtCtrlInputPara31,  // 输入参数31
    RmtCtrlInputPara32,  // 输入参数32
    RmtCtrlInputPara33,  // 输入参数33
    RmtCtrlInputPara34,  // 输入参数34
    RmtCtrlInputPara35,  // 输入参数35
    RmtCtrlInputPara36,  // 输入参数36
    RmtCtrlInputPara37,  // 输入参数37
    RmtCtrlInputPara38,  // 输入参数38
    RmtCtrlInputPara39,  // 输入参数39
    RmtCtrlInputPara40,  // 输入参数40
    RmtCtrlInputPara41,  // 输入参数41
    RmtCtrlInputPara42,  // 输入参数42
    RmtCtrlInputPara43,  // 输入参数43
    RmtCtrlInputPara44,  // 输入参数44
    RmtCtrlInputPara45,  // 输入参数45
    RmtCtrlInputPara46,  // 输入参数46
    RmtCtrlInputPara47,  // 输入参数47
    RmtCtrlInputPara48,  // 输入参数48
    RmtCtrlInputPara49,  // 输入参数49
    RmtCtrlInputPara50,  // 输入参数50（8242）
    RmtCtrlInputPara51,  // 输入参数51
    RmtCtrlInputPara52,  // 输入参数52
    RmtCtrlInputPara53,  // 输入参数53
    RmtCtrlInputPara54,  // 输入参数54
    RmtCtrlInputPara55,  // 输入参数55
    RmtCtrlInputPara56,  // 输入参数56
    RmtCtrlInputPara57,  // 输入参数57
    RmtCtrlInputPara58,  // 输入参数58
    RmtCtrlInputPara59,  // 输入参数59
    RmtCtrlInputPara60,  // 输入参数60（8252）
    // （8253）
    // （......保留14个）
    // （8266）
    ErcCommand = RmtCtrlInputPara60 + 15,  // 拓展远程周期命令（8267）
    ErcInParam1,                           // 拓展远程周期输入参数1（8268）
    ErcInParam2,                           // 拓展远程周期输入参数2（8269）

    AutoProgramSwitchIn = ErcInParam2 + 17,  // 机器人零编程模式开关（8286）

    ReserveInW1,  // 保留World1（8287）

    ChangePointFileIn,  // 切换点位文件

    ReserveInW2,  // 保留World2（8289）

    AutoProgramAuthIn,  // 机器人零编程外部权限设置（8290）
    InputPrjCut,        // IO工程切换
    LoadNoSet,          // 负载号设置
    SeelectCoord,       // 坐标系选择
    ToolNOSet,          // 工具坐标系号选择
    WobjNOSet,          // 工件坐标系号选择
    SetVel,             // 速度设置

    DirMovModeSet,  // 直接运动方式设置(0-MovJ,1-MovL,2-Jump,3-JumpL)
    JumLH_Low,      // 跳跃运动LH参数低位
    JumLH_High,     // 跳跃运动LH参数高位
    JumMH_Low,      // 跳跃运动MH参数低位
    JumMH_High,     // 跳跃运动MH参数高位
    JumRH_Low,      // 跳跃运动RH参数低位
    JumRH_High,     // 跳跃运动RH参数高位

    CurPIndexIn,  // 当前P/JP变量的序号

    ReserveInW3,  // 保留World3
    ReserveInW4   // 保留World4

    // 【重要】总线地址0~255偏移量，在此后续不能增加新的枚举，新总线功能用之前预留的
};

enum FieldBusFunc_OutBit : unsigned int
{
    PrgRunStat = 0x8000,  // 程序运行状态
    PrgStopStat,          // 程序停止状态
    PrgResetStat,         // 程序复位成功状态
    EnableStat,           // 使能状态
    EmergeStat,           // 急停状态
    SysErrStat,           // 系统故障状态
    SysWarnStat,          // 系统警告状态
    ServoErrStat,         // 伺服故障状态
    ServoWarnStat,        // 伺服警告状态
    SafeDoorWarnStat,     // 安全门警告状态
    SysInitialStat,       // 系统启动完成状态
    InMotionStat,         // 机器人运动中
    InPlaceStat,          // 机器人运动到位状态
    HeartBeatStat,        // 总线通讯心跳信号
    DynBrakeSwitchOut,    // 动态制动
    PWriteSuccessStat,    // P/JP变量写入是否成功

    DigIOStsIn0,    // IN[0]状态
    DigIOStsIn1,    // IN[1]状态
    DigIOStsIn2,    // IN[2]状态
    DigIOStsIn3,    // IN[3]状态
    DigIOStsIn4,    // IN[4]状态
    DigIOStsIn5,    // IN[5]状态
    DigIOStsIn6,    // IN[6]状态
    DigIOStsIn7,    // IN[7]状态
    DigIOStsIn8,    // IN[8]状态
    DigIOStsIn9,    // IN[9]状态
    DigIOStsIn10,   // IN[10]状态
    DigIOStsIn11,   // IN[11]状态
    DigIOStsIn12,   // IN[12]状态
    DigIOStsIn13,   // IN[13]状态
    DigIOStsIn14,   // IN[14]状态
    DigIOStsIn15,   // IN[15]状态
    DigIOStsOut0,   // OUT[0]状态
    DigIOStsOut1,   // OUT[1]状态
    DigIOStsOut2,   // OUT[2]状态
    DigIOStsOut3,   // OUT[3]状态
    DigIOStsOut4,   // OUT[4]状态
    DigIOStsOut5,   // OUT[5]状态
    DigIOStsOut6,   // OUT[6]状态
    DigIOStsOut7,   // OUT[7]状态
    DigIOStsOut8,   // OUT[8]状态
    DigIOStsOut9,   // OUT[9]状态
    DigIOStsOut10,  // OUT[10]状态
    DigIOStsOut11,  // OUT[11]状态
    DigIOStsOut12,  // OUT[12]状态
    DigIOStsOut13,  // OUT[13]状态
    DigIOStsOut14,  // OUT[14]状态
    DigIOStsOut15,  // OUT[15]状态

    CurOpPosTypeOut,  // 当前操作的点位类型读取 0-位置点 1-关节点
    StationReserveOutput1, //工位预约输出信号1
    StationReserveOutput2, //工位预约输出信号2
    StationReserveOutput3, //工位预约输出信号3
    StationReserveOutput4, //工位预约输出信号4
    StationReserveOutput5, //工位预约输出信号5
    StationReserveOutput6, //工位预约输出信号6
    StationReserveOutput7, //工位预约输出信号7
    StationReserveOutput8, //工位预约输出信号8
    RobotBodyPowerIsEnable,  //协作机器人本体上下电状态
};

enum FieldBusFunc_OutWord : unsigned int
{
    RmtCtrlStat = 0xA000,  // 远程控制状态

    RmtCtrlOuputPara1,   // 远程控制返回参数1/故障码
    RmtCtrlOuputPara2,   // 远程控制返回参数2/系统故障码
    RmtCtrlOuputPara3,   // 远程控制返回参数3
    RmtCtrlOuputPara4,   // 远程控制返回参数4
    RmtCtrlOuputPara5,   // 远程控制返回参数5
    RmtCtrlOuputPara6,   // 远程控制返回参数6
    RmtCtrlOuputPara7,   // 远程控制返回参数7
    RmtCtrlOuputPara8,   // 远程控制返回参数8
    RmtCtrlOuputPara9,   // 远程控制返回参数9
    RmtCtrlOuputPara10,  // 远程控制返回参数10
    RmtCtrlOuputPara11,  // 远程控制返回参数11
    RmtCtrlOuputPara12,  // 远程控制返回参数12
    RmtCtrlOuputPara13,  // 远程控制返回参数13
    RmtCtrlOuputPara14,  // 远程控制返回参数14
    RmtCtrlOuputPara15,  // 远程控制返回参数15
    RmtCtrlOuputPara16,  // 远程控制返回参数16
    RmtCtrlOuputPara17,  // 远程控制返回参数17
    RmtCtrlOuputPara18,  // 远程控制返回参数18
    RmtCtrlOuputPara19,  // 远程控制返回参数19
    RmtCtrlOuputPara20,  // 远程控制返回参数20
    RmtCtrlOuputPara21,  // 远程控制返回参数21
    RmtCtrlOuputPara22,  // 远程控制返回参数22
    RmtCtrlOuputPara23,  // 远程控制返回参数23
    RmtCtrlOuputPara24,  // 远程控制返回参数24
    RmtCtrlOuputPara25,  // 远程控制返回参数25
    RmtCtrlOuputPara26,  // 远程控制返回参数26
    RmtCtrlOuputPara27,  // 远程控制返回参数27
    RmtCtrlOuputPara28,  // 远程控制返回参数28
    RmtCtrlOuputPara29,  // 远程控制返回参数29
    RmtCtrlOuputPara30,  // 远程控制返回参数30
    RmtCtrlOuputPara31,  // 远程控制返回参数31
    RmtCtrlOuputPara32,  // 远程控制返回参数32
    RmtCtrlOuputPara33,  // 远程控制返回参数33
    RmtCtrlOuputPara34,  // 远程控制返回参数34
    RmtCtrlOuputPara35,  // 远程控制返回参数35
    RmtCtrlOuputPara36,  // 远程控制返回参数36
    RmtCtrlOuputPara37,  // 远程控制返回参数37
    RmtCtrlOuputPara38,  // 远程控制返回参数38
    RmtCtrlOuputPara39,  // 远程控制返回参数39
    RmtCtrlOuputPara40,  // 远程控制返回参数40
    RmtCtrlOuputPara41,  // 远程控制返回参数41
    RmtCtrlOuputPara42,  // 远程控制返回参数42
    RmtCtrlOuputPara43,  // 远程控制返回参数43
    RmtCtrlOuputPara44,  // 远程控制返回参数44
    RmtCtrlOuputPara45,  // 远程控制返回参数45
    RmtCtrlOuputPara46,  // 远程控制返回参数46
    RmtCtrlOuputPara47,  // 远程控制返回参数47
    RmtCtrlOuputPara48,  // 远程控制返回参数48
    RmtCtrlOuputPara49,  // 远程控制返回参数49
    RmtCtrlOuputPara50,  // 远程控制返回参数50（41010）
    RmtCtrlOuputPara51,  // 远程控制返回参数51
    RmtCtrlOuputPara52,  // 远程控制返回参数52
    RmtCtrlOuputPara53,  // 远程控制返回参数53
    RmtCtrlOuputPara54,  // 远程控制返回参数54
    RmtCtrlOuputPara55,  // 远程控制返回参数55
    RmtCtrlOuputPara56,  // 远程控制返回参数56
    RmtCtrlOuputPara57,  // 远程控制返回参数57
    RmtCtrlOuputPara58,  // 远程控制返回参数58
    RmtCtrlOuputPara59,  // 远程控制返回参数59
    RmtCtrlOuputPara60,  // 远程控制返回参数60（41020）
    // （41021）
    // （......保留14个）
    // （41034）

    ErcStatus = RmtCtrlOuputPara60 + 15,  // 拓展远程周期状态（41035）
    ErcOutParam1,                         // 拓展远程周期输出参数1（41036）
    ErcOutParam2,                         // 拓展远程周期输出参数2（41037）
    AutoProgramSwitchOut,                 // 机器人零编程模式状态（41038）
    AutoProgramAuthOut,                   // 机器人零编程外部权限状态（41039）
    PositionJ1X_Low,                      // 当前位置J1/X 坐标低位（41040）
    PositionJ1X_High,                     // 当前位置J1/X 坐标高位（41041）
    PositionJ2Y_Low,                      // 当前位置J2/Y 坐标低位
    PositionJ2Y_High,                     // 当前位置J2/Y 坐标高位
    PositionJ3Z_Low,                      // 当前位置J3/Z 坐标低位
    PositionJ3Z_High,                     // 当前位置J3/Z 坐标高位
    PositionJ4A_Low,                      // 当前位置J4/A 坐标低位
    PositionJ4A_High,                     // 当前位置J4/A 坐标高位
    PositionJ5B_Low,                      // 当前位置J5/B 坐标低位
    PositionJ5B_High,                     // 当前位置J5/B 坐标高位
    PositionJ6C_Low,                      // 当前位置J6/C 坐标低位
    PositionJ6C_High,                     // 当前位置J6/C 坐标高位

    ReserveOutW1,  // 保留World1（41052）
    ReserveOutW2,  // 保留World2（41053）
    ReserveOutW3,  // 保留World3（41054）

    CrashAlarmState,     // 碰撞报警状态（41055）
    ChangePointFileOut,  // 切换点位文件
    CurAuthority,        // 当前控制权限
    PrjSerialNo,         // 当前工程序号
    PrjStatus,           // 工程当前状态
    CurLoad,             // 当前负载号
    CurCoord,            // 当前坐标系
    CurToolNO,           // 当前工具坐标系号
    CurWobjNO,           // 当前工件坐标系号
    CurVel,              // 当前速度
    SysErrCode,          // 当前故障码
    CurPrgMode,          // 当前模式

    CurDirMovMode,  // 当前直接运动方式
    CurJumLH_Low,   // 当前跳跃运动LH参数低位
    CurJumLH_High,  // 当前跳跃运动LH参数高位
    CurJumMH_Low,   // 当前跳跃运动MH参数低位
    CurJumMH_High,  // 当前跳跃运动MH参数高位
    CurJumRH_Low,   // 当前跳跃运动RH参数低位
    CurJumRH_High,  // 当前跳跃运动RH参数高位

    CurPIndexOut  // 当前P/JP变量的序号

    // 【重要】总线地址0~255偏移量，在此后续不能增加新的枚举，新总线功能用之前预留的
};

/**
 * @brief IO类型
 */
enum IOType
{
    IOTP_IN = 0,  // input
    IOTP_OUT      // output
};

/**
 * @brief 内存长度
 */
enum MemoryLength : unsigned int
{
    ML_BIT = 1,    // Bit
    ML_CHAR = 4,   // Char
    ML_BYTE = 8,   // Byte
    ML_WORD = 16,  // Word
    ML_DWORD = 32  // DWord
};
}  // namespace InoRobBusiness
