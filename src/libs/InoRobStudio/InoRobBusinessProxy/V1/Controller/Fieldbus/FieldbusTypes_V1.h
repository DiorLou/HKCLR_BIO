#pragma once
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

constexpr int FIELDBUS_TOTAL_BIT_V1 = 13824;  // 总线总大小（Bit）
constexpr int FIELDBUS_TOTAL_BYTE_V1 = 1728;  // 总线总大小（Byte）
constexpr int FIELDBUS_TOTAL_WORD_V1 = 864;   // 总线总大小（Word）
constexpr int FIELDBUS_TOTAL_DWORD_V1 = 432;  // 总线总大小（DWord）

constexpr int STANDARD_IO_START_BIT_V1 = 0;    // 标准IO起始下标(以Bit参考)
constexpr int STANDARD_IO_END_BIT_V1 = 127;    // 标准IO终止下标(以Bit参考)
constexpr int FIELDBUS_IO_START_BIT_V1 = 512;  // 现场总线IO起始下标(以Bit参考)
constexpr int FIELDBUS_IO_END_BIT_V1 = 4607;   // 现场总线IO终止下标(以Bit参考)
constexpr int MEMORY_IO_START_BIT_V1 = 12800;  // 内存IO起始下标(以Bit参考)
constexpr int MEMORY_IO_END_BIT_V1 = 13823;    // 内存IO终止下标(以Bit参考)

constexpr int STANDARD_IO_START_BYTE_V1 = 0;   // 标准IO起始下标(以Byte参考)
constexpr int STANDARD_IO_END_BYTE_V1 = 15;    // 标准IO终止下标(以Byte参考)
constexpr int FIELDBUS_IO_START_BYTE_V1 = 64;  // 现场总线IO起始下标(以Byte参考)
constexpr int FIELDBUS_IO_END_BYTE_V1 = 575;   // 现场总线IO终止下标(以Byte参考)
constexpr int MEMORY_IO_START_BYTE_V1 = 1600;  // 内存IO起始下标(以Byte参考)
constexpr int MEMORY_IO_END_BYTE_V1 = 1727;    // 内存IO终止下标(以Byte参考)

constexpr int STANDARD_IO_START_WORD_V1 = 0;   // 标准IO起始下标(以Word参考)
constexpr int STANDARD_IO_END_WORD_V1 = 7;     // 标准IO终止下标(以Word参考)
constexpr int FIELDBUS_IO_START_WORD_V1 = 32;  // 现场总线IO起始下标(以Word参考)
constexpr int FIELDBUS_IO_END_WORD_V1 = 287;   // 现场总线IO终止下标(以Word参考)
constexpr int MEMORY_IO_START_WORD_V1 = 800;   // 内存IO起始下标(以Word参考)
constexpr int MEMORY_IO_END_WORD_V1 = 863;     // 内存IO终止下标(以Word参考)

constexpr int STANDARD_IO_START_DWORD_V1 = 0;   // 标准IO起始下标(以DWord参考)
constexpr int STANDARD_IO_END_DWORD_V1 = 3;     // 标准IO终止下标(以DWord参考)
constexpr int FIELDBUS_IO_START_DWORD_V1 = 16;  // 现场总线IO起始下标(以DWord参考)
constexpr int FIELDBUS_IO_END_DWORD_V1 = 143;   // 现场总线IO终止下标(以DWord参考)
constexpr int MEMORY_IO_START_DWORD_V1 = 400;   // 内存IO起始下标(以DWord参考)
constexpr int MEMORY_IO_END_DWORD_V1 = 431;     // 内存IO终止下标(以DWord参考)

namespace InoRobBusinessProxy
{
enum FieldBusFunc_InBit_V1 : unsigned int
{
    PrgStart_V1 = 0x0000,     // 程序启动
    PrgStop_V1,               // 程序停止
    PrgReset_V1,              // 程序复位
    McEnable_V1,              // 使能
    McEmergeStop_V1,          // 急停
    McAlarmClear_V1,          // 清除报警
    VelIncr_V1,               // 速度加
    VelDecr_V1,               // 速度减
    Homing_V1,                // 原点回归
    ToTeachOrReplayMode_V1,   // 手动/自动模式切换
    StartStaticTask_V1,       // 启动所有静态任务
    CurOpPosTypeIn_V1,        // 设置当前操作的点位类型, 0-位置点， 1-关节点
    DynBrakeSwitchIn_V1,      // 动态制动
    ExSignalTriggerColli_V1,  // 外部信号触发碰检
    Zero_V1,                  // 回零
    RobotBodyPower_V1,        // 机器人本体上下电

    J1XPosMov_V1,  // 示教J1/X +
    J2YPosMov_V1,  // 示教J2/Y +
    J3ZPosMov_V1,  // 示教J3/Z +
    J4APosMov_V1,  // 示教J4/A +
    J5PosMov_V1,   // 示教J5 +
    J6PosMov_V1,   // 示教J6 +

    ReserveIn2_V1,  // 保留2，不在用户界面显示
    ReserveIn3_V1,  // 保留3，不在用户界面显示

    J1XNegMov_V1,  // 示教J1/X -
    J2YNegMov_V1,  // 示教J2/Y -
    J3ZNegMov_V1,  // 示教J3/Z -
    J4ANegMov_V1,  // 示教J4/A -
    J5NegMov_V1,   // 示教J5 -
    J6NegMov_V1,   // 示教J6 -

    ReserveIn4_V1,  // 保留4，不在用户界面显示
    ReserveIn5_V1,  // 保留5，不在用户界面显示

    WrCurPosToP_V1,  // 把当前位置写入当前P/JP变量
    ReserveA1_V1,    // 把输入点位写入当前P/JP变量
    MoveToCurP_V1,   // 直接运动到当前P/JP变量位置

    DigIOOutSet0_V1,   // OUT[0]控制命令
    DigIOOutSet1_V1,   // OUT[1]控制命令
    DigIOOutSet2_V1,   // OUT[2]控制命令
    DigIOOutSet3_V1,   // OUT[3]控制命令
    DigIOOutSet4_V1,   // OUT[4]控制命令
    DigIOOutSet5_V1,   // OUT[5]控制命令
    DigIOOutSet6_V1,   // OUT[6]控制命令
    DigIOOutSet7_V1,   // OUT[7]控制命令
    DigIOOutSet8_V1,   // OUT[8]控制命令
    DigIOOutSet9_V1,   // OUT[9]控制命令
    DigIOOutSet10_V1,  // OUT[10]控制命令
    DigIOOutSet11_V1,  // OUT[11]控制命令
    DigIOOutSet12_V1,  // OUT[12]控制命令
    DigIOOutSet13_V1,  // OUT[13]控制命令
    DigIOOutSet14_V1,  // OUT[14]控制命令
    DigIOOutSet15_V1   // OUT[15]控制命令
};

FieldBusFunc_InBit_V1 FieldBusFunc_InBit_ToProxy(FieldBusFunc_InBit fieldBusFunc_InBit);
FieldBusFunc_InBit FieldBusFunc_InBit_FromProxy(FieldBusFunc_InBit_V1 fieldBusFunc_InBit_V1);

enum FieldBusFunc_InWord_V1 : unsigned int
{
    RmtCtrlCmd_V1 = 0x2000,  // 远程控制命令

    RmtCtrlInputPara1_V1,   // 输入参数1
    RmtCtrlInputPara2_V1,   // 输入参数2
    RmtCtrlInputPara3_V1,   // 输入参数3
    RmtCtrlInputPara4_V1,   // 输入参数4
    RmtCtrlInputPara5_V1,   // 输入参数5
    RmtCtrlInputPara6_V1,   // 输入参数6
    RmtCtrlInputPara7_V1,   // 输入参数7
    RmtCtrlInputPara8_V1,   // 输入参数8
    RmtCtrlInputPara9_V1,   // 输入参数9
    RmtCtrlInputPara10_V1,  // 输入参数10
    RmtCtrlInputPara11_V1,  // 输入参数11
    RmtCtrlInputPara12_V1,  // 输入参数12
    RmtCtrlInputPara13_V1,  // 输入参数13
    RmtCtrlInputPara14_V1,  // 输入参数14
    RmtCtrlInputPara15_V1,  // 输入参数15
    RmtCtrlInputPara16_V1,  // 输入参数16
    RmtCtrlInputPara17_V1,  // 输入参数17
    RmtCtrlInputPara18_V1,  // 输入参数18
    RmtCtrlInputPara19_V1,  // 输入参数19
    RmtCtrlInputPara20_V1,  // 输入参数20
    RmtCtrlInputPara21_V1,  // 输入参数21
    RmtCtrlInputPara22_V1,  // 输入参数22
    RmtCtrlInputPara23_V1,  // 输入参数23
    RmtCtrlInputPara24_V1,  // 输入参数24
    RmtCtrlInputPara25_V1,  // 输入参数25
    RmtCtrlInputPara26_V1,  // 输入参数26
    RmtCtrlInputPara27_V1,  // 输入参数27
    RmtCtrlInputPara28_V1,  // 输入参数28
    RmtCtrlInputPara29_V1,  // 输入参数29
    RmtCtrlInputPara30_V1,  // 输入参数30
    RmtCtrlInputPara31_V1,  // 输入参数31
    RmtCtrlInputPara32_V1,  // 输入参数32
    RmtCtrlInputPara33_V1,  // 输入参数33
    RmtCtrlInputPara34_V1,  // 输入参数34
    RmtCtrlInputPara35_V1,  // 输入参数35
    RmtCtrlInputPara36_V1,  // 输入参数36
    RmtCtrlInputPara37_V1,  // 输入参数37
    RmtCtrlInputPara38_V1,  // 输入参数38
    RmtCtrlInputPara39_V1,  // 输入参数39
    RmtCtrlInputPara40_V1,  // 输入参数40
    RmtCtrlInputPara41_V1,  // 输入参数41
    RmtCtrlInputPara42_V1,  // 输入参数42
    RmtCtrlInputPara43_V1,  // 输入参数43
    RmtCtrlInputPara44_V1,  // 输入参数44
    RmtCtrlInputPara45_V1,  // 输入参数45
    RmtCtrlInputPara46_V1,  // 输入参数46
    RmtCtrlInputPara47_V1,  // 输入参数47
    RmtCtrlInputPara48_V1,  // 输入参数48
    RmtCtrlInputPara49_V1,  // 输入参数49
    RmtCtrlInputPara50_V1,  // 输入参数50（8242）
    RmtCtrlInputPara51_V1,  // 输入参数51
    RmtCtrlInputPara52_V1,  // 输入参数52
    RmtCtrlInputPara53_V1,  // 输入参数53
    RmtCtrlInputPara54_V1,  // 输入参数54
    RmtCtrlInputPara55_V1,  // 输入参数55
    RmtCtrlInputPara56_V1,  // 输入参数56
    RmtCtrlInputPara57_V1,  // 输入参数57
    RmtCtrlInputPara58_V1,  // 输入参数58
    RmtCtrlInputPara59_V1,  // 输入参数59
    RmtCtrlInputPara60_V1,  // 输入参数60（8252）
    // （8253）
    // （......保留14个）
    // （8266）
    ErcCommand_V1 = RmtCtrlInputPara60 + 15,  // 拓展远程周期命令（8267）
    ErcInParam1_V1,                           // 拓展远程周期输入参数1（8268）
    ErcInParam2_V1,                           // 拓展远程周期输入参数2（8269）

    AutoProgramSwitchIn_V1 = ErcInParam2 + 17,  // 机器人零编程模式开关（8286）

    ReserveInW1_V1,  // 保留World1（8287）

    ChangePointFileIn_V1,  // 切换点位文件

    ReserveInW2_V1,  // 保留World2（8289）

    AutoProgramAuthIn_V1,  // 机器人零编程外部权限设置（8290）
    InputPrjCut_V1,        // IO工程切换
    LoadNoSet_V1,          // 负载号设置
    SeelectCoord_V1,       // 坐标系选择
    ToolNOSet_V1,          // 工具坐标系号选择
    WobjNOSet_V1,          // 工件坐标系号选择
    SetVel_V1,             // 速度设置

    DirMovModeSet_V1,  // 直接运动方式设置(0-MovJ,1-MovL,2-Jump,3-JumpL)
    JumLH_Low_V1,      // 跳跃运动LH参数低位
    JumLH_High_V1,     // 跳跃运动LH参数高位
    JumMH_Low_V1,      // 跳跃运动MH参数低位
    JumMH_High_V1,     // 跳跃运动MH参数高位
    JumRH_Low_V1,      // 跳跃运动RH参数低位
    JumRH_High_V1,     // 跳跃运动RH参数高位

    CurPIndexIn_V1,  // 当前P/JP变量的序号

    ReserveInW3_V1,  // 保留World3
    ReserveInW4_V1   // 保留World4

    // 【重要】总线地址0~255偏移量，在此后续不能增加新的枚举，新总线功能用之前预留的
};

FieldBusFunc_InWord_V1 FieldBusFunc_InWord_ToProxy(FieldBusFunc_InWord fieldBusFunc_InWord);
FieldBusFunc_InWord FieldBusFunc_InWord_FromProxy(FieldBusFunc_InWord_V1 fieldBusFunc_InWord_V1);

enum FieldBusFunc_OutBit_V1 : unsigned int
{
    PrgRunStat_V1 = 0x8000,  // 程序运行状态
    PrgStopStat_V1,          // 程序停止状态
    PrgResetStat_V1,         // 程序复位成功状态
    EnableStat_V1,           // 使能状态
    EmergeStat_V1,           // 急停状态
    SysErrStat_V1,           // 系统故障状态
    SysWarnStat_V1,          // 系统警告状态
    ServoErrStat_V1,         // 伺服故障状态
    ServoWarnStat_V1,        // 伺服警告状态
    SafeDoorWarnStat_V1,     // 安全门警告状态
    SysInitialStat_V1,       // 系统启动完成状态
    InMotionStat_V1,         // 机器人运动中
    InPlaceStat_V1,          // 机器人运动到位状态
    HeartBeatStat_V1,        // 总线通讯心跳信号
    DynBrakeSwitchOut_V1,    // 动态制动
    PWriteSuccessStat_V1,    // P/JP变量写入是否成功

    DigIOStsIn0_V1,    // IN[0]状态
    DigIOStsIn1_V1,    // IN[1]状态
    DigIOStsIn2_V1,    // IN[2]状态
    DigIOStsIn3_V1,    // IN[3]状态
    DigIOStsIn4_V1,    // IN[4]状态
    DigIOStsIn5_V1,    // IN[5]状态
    DigIOStsIn6_V1,    // IN[6]状态
    DigIOStsIn7_V1,    // IN[7]状态
    DigIOStsIn8_V1,    // IN[8]状态
    DigIOStsIn9_V1,    // IN[9]状态
    DigIOStsIn10_V1,   // IN[10]状态
    DigIOStsIn11_V1,   // IN[11]状态
    DigIOStsIn12_V1,   // IN[12]状态
    DigIOStsIn13_V1,   // IN[13]状态
    DigIOStsIn14_V1,   // IN[14]状态
    DigIOStsIn15_V1,   // IN[15]状态
    DigIOStsOut0_V1,   // OUT[0]状态
    DigIOStsOut1_V1,   // OUT[1]状态
    DigIOStsOut2_V1,   // OUT[2]状态
    DigIOStsOut3_V1,   // OUT[3]状态
    DigIOStsOut4_V1,   // OUT[4]状态
    DigIOStsOut5_V1,   // OUT[5]状态
    DigIOStsOut6_V1,   // OUT[6]状态
    DigIOStsOut7_V1,   // OUT[7]状态
    DigIOStsOut8_V1,   // OUT[8]状态
    DigIOStsOut9_V1,   // OUT[9]状态
    DigIOStsOut10_V1,  // OUT[10]状态
    DigIOStsOut11_V1,  // OUT[11]状态
    DigIOStsOut12_V1,  // OUT[12]状态
    DigIOStsOut13_V1,  // OUT[13]状态
    DigIOStsOut14_V1,  // OUT[14]状态
    DigIOStsOut15_V1,  // OUT[15]状态

    CurOpPosTypeOut_V1  // 当前操作的点位类型读取 0-位置点 1-关节点
};

FieldBusFunc_OutBit_V1 FieldBusFunc_OutBit_ToProxy(FieldBusFunc_OutBit fieldBusFunc_OutBit);
FieldBusFunc_OutBit FieldBusFunc_OutBit_FromProxy(FieldBusFunc_OutBit_V1 fieldBusFunc_OutBit_V1);

enum FieldBusFunc_OutWord_V1 : unsigned int
{
    RmtCtrlStat_V1 = 0xA000,  // 远程控制状态

    RmtCtrlOuputPara1_V1,   // 远程控制返回参数1/故障码
    RmtCtrlOuputPara2_V1,   // 远程控制返回参数2/系统故障码
    RmtCtrlOuputPara3_V1,   // 远程控制返回参数3
    RmtCtrlOuputPara4_V1,   // 远程控制返回参数4
    RmtCtrlOuputPara5_V1,   // 远程控制返回参数5
    RmtCtrlOuputPara6_V1,   // 远程控制返回参数6
    RmtCtrlOuputPara7_V1,   // 远程控制返回参数7
    RmtCtrlOuputPara8_V1,   // 远程控制返回参数8
    RmtCtrlOuputPara9_V1,   // 远程控制返回参数9
    RmtCtrlOuputPara10_V1,  // 远程控制返回参数10
    RmtCtrlOuputPara11_V1,  // 远程控制返回参数11
    RmtCtrlOuputPara12_V1,  // 远程控制返回参数12
    RmtCtrlOuputPara13_V1,  // 远程控制返回参数13
    RmtCtrlOuputPara14_V1,  // 远程控制返回参数14
    RmtCtrlOuputPara15_V1,  // 远程控制返回参数15
    RmtCtrlOuputPara16_V1,  // 远程控制返回参数16
    RmtCtrlOuputPara17_V1,  // 远程控制返回参数17
    RmtCtrlOuputPara18_V1,  // 远程控制返回参数18
    RmtCtrlOuputPara19_V1,  // 远程控制返回参数19
    RmtCtrlOuputPara20_V1,  // 远程控制返回参数20
    RmtCtrlOuputPara21_V1,  // 远程控制返回参数21
    RmtCtrlOuputPara22_V1,  // 远程控制返回参数22
    RmtCtrlOuputPara23_V1,  // 远程控制返回参数23
    RmtCtrlOuputPara24_V1,  // 远程控制返回参数24
    RmtCtrlOuputPara25_V1,  // 远程控制返回参数25
    RmtCtrlOuputPara26_V1,  // 远程控制返回参数26
    RmtCtrlOuputPara27_V1,  // 远程控制返回参数27
    RmtCtrlOuputPara28_V1,  // 远程控制返回参数28
    RmtCtrlOuputPara29_V1,  // 远程控制返回参数29
    RmtCtrlOuputPara30_V1,  // 远程控制返回参数30
    RmtCtrlOuputPara31_V1,  // 远程控制返回参数31
    RmtCtrlOuputPara32_V1,  // 远程控制返回参数32
    RmtCtrlOuputPara33_V1,  // 远程控制返回参数33
    RmtCtrlOuputPara34_V1,  // 远程控制返回参数34
    RmtCtrlOuputPara35_V1,  // 远程控制返回参数35
    RmtCtrlOuputPara36_V1,  // 远程控制返回参数36
    RmtCtrlOuputPara37_V1,  // 远程控制返回参数37
    RmtCtrlOuputPara38_V1,  // 远程控制返回参数38
    RmtCtrlOuputPara39_V1,  // 远程控制返回参数39
    RmtCtrlOuputPara40_V1,  // 远程控制返回参数40
    RmtCtrlOuputPara41_V1,  // 远程控制返回参数41
    RmtCtrlOuputPara42_V1,  // 远程控制返回参数42
    RmtCtrlOuputPara43_V1,  // 远程控制返回参数43
    RmtCtrlOuputPara44_V1,  // 远程控制返回参数44
    RmtCtrlOuputPara45_V1,  // 远程控制返回参数45
    RmtCtrlOuputPara46_V1,  // 远程控制返回参数46
    RmtCtrlOuputPara47_V1,  // 远程控制返回参数47
    RmtCtrlOuputPara48_V1,  // 远程控制返回参数48
    RmtCtrlOuputPara49_V1,  // 远程控制返回参数49
    RmtCtrlOuputPara50_V1,  // 远程控制返回参数50（41010）
    RmtCtrlOuputPara51_V1,  // 远程控制返回参数51
    RmtCtrlOuputPara52_V1,  // 远程控制返回参数52
    RmtCtrlOuputPara53_V1,  // 远程控制返回参数53
    RmtCtrlOuputPara54_V1,  // 远程控制返回参数54
    RmtCtrlOuputPara55_V1,  // 远程控制返回参数55
    RmtCtrlOuputPara56_V1,  // 远程控制返回参数56
    RmtCtrlOuputPara57_V1,  // 远程控制返回参数57
    RmtCtrlOuputPara58_V1,  // 远程控制返回参数58
    RmtCtrlOuputPara59_V1,  // 远程控制返回参数59
    RmtCtrlOuputPara60_V1,  // 远程控制返回参数60（41020）
    // （41021）
    // （......保留14个）
    // （41034）

    ErcStatus_V1 = RmtCtrlOuputPara60 + 15,  // 拓展远程周期状态（41035）
    ErcOutParam1_V1,                         // 拓展远程周期输出参数1（41036）
    ErcOutParam2_V1,                         // 拓展远程周期输出参数2（41037）
    AutoProgramSwitchOut_V1,                 // 机器人零编程模式状态（41038）
    AutoProgramAuthOut_V1,                   // 机器人零编程外部权限状态（41039）
    PositionJ1X_Low_V1,                      // 当前位置J1/X 坐标低位（41040）
    PositionJ1X_High_V1,                     // 当前位置J1/X 坐标高位（41041）
    PositionJ2Y_Low_V1,                      // 当前位置J2/Y 坐标低位
    PositionJ2Y_High_V1,                     // 当前位置J2/Y 坐标高位
    PositionJ3Z_Low_V1,                      // 当前位置J3/Z 坐标低位
    PositionJ3Z_High_V1,                     // 当前位置J3/Z 坐标高位
    PositionJ4A_Low_V1,                      // 当前位置J4/A 坐标低位
    PositionJ4A_High_V1,                     // 当前位置J4/A 坐标高位
    PositionJ5B_Low_V1,                      // 当前位置J5/B 坐标低位
    PositionJ5B_High_V1,                     // 当前位置J5/B 坐标高位
    PositionJ6C_Low_V1,                      // 当前位置J6/C 坐标低位
    PositionJ6C_High_V1,                     // 当前位置J6/C 坐标高位

    ReserveOutW1_V1,  // 保留World1（41052）
    ReserveOutW2_V1,  // 保留World2（41053）
    ReserveOutW3_V1,  // 保留World3（41054）

    CrashAlarmState_V1,     // 碰撞报警状态（41055）
    ChangePointFileOut_V1,  // 切换点位文件
    CurAuthority_V1,        // 当前控制权限
    PrjSerialNo_V1,         // 当前工程序号
    PrjStatus_V1,           // 工程当前状态
    CurLoad_V1,             // 当前负载号
    CurCoord_V1,            // 当前坐标系
    CurToolNO_V1,           // 当前工具坐标系号
    CurWobjNO_V1,           // 当前工件坐标系号
    CurVel_V1,              // 当前速度
    SysErrCode_V1,          // 当前故障码
    CurPrgMode_V1,          // 当前模式

    CurDirMovMode_V1,  // 当前直接运动方式
    CurJumLH_Low_V1,   // 当前跳跃运动LH参数低位
    CurJumLH_High_V1,  // 当前跳跃运动LH参数高位
    CurJumMH_Low_V1,   // 当前跳跃运动MH参数低位
    CurJumMH_High_V1,  // 当前跳跃运动MH参数高位
    CurJumRH_Low_V1,   // 当前跳跃运动RH参数低位
    CurJumRH_High_V1,  // 当前跳跃运动RH参数高位

    CurPIndexOut_V1  // 当前P/JP变量的序号

    // 【重要】总线地址0~255偏移量，在此后续不能增加新的枚举，新总线功能用之前预留的
};

FieldBusFunc_OutWord_V1 FieldBusFunc_OutWord_ToProxy(FieldBusFunc_OutWord fieldBusFunc_OutWord);
FieldBusFunc_OutWord FieldBusFunc_OutWord_FromProxy(FieldBusFunc_OutWord_V1 fieldBusFunc_OutWord_V1);

/**
 * @brief IO类型
 */
enum IOType_V1
{
    IOTP_IN_V1 = 0,  // input
    IOTP_OUT_V1      // output
};

IOType_V1 IOType_ToProxy(IOType ioType);
IOType IOType_FromProxy(IOType_V1 ioType_V1);

/**
 * @brief 内存长度
 */
enum MemoryLength_V1 : unsigned int
{
    ML_BIT_V1 = 1,    // Bit
    ML_CHAR_V1 = 4,   // Char
    ML_BYTE_V1 = 8,   // Byte
    ML_WORD_V1 = 16,  // Word
    ML_DWORD_V1 = 32  // DWord
};

MemoryLength_V1 MemoryLength_ToProxy(MemoryLength memoryLength);
MemoryLength MemoryLength_FromProxy(MemoryLength_V1 memoryLength_V1);

}  // namespace InoRobBusinessProxy
