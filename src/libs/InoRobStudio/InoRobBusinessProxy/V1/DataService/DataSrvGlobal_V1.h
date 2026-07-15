#pragma once
#include <string>
#include <vector>
#include <map>
#include "../GlobalDataService/DataService/DataSrvGlobal.h"

using std::string;

namespace InoRobBusinessProxy
{
#define COM_PARM_NUM_V1   16
#define JOINT_AXIS_NUM_V1 (8)  // 机器人关节轴数
#define LINK_PARM_NUM_V1  8
#define MAXDANUM_V1       16
#define MAXIONUM_V1       128
#define MODULE_NUM_V1     8  // 控制器模块数量

// 轴个数
#define AXIS_NUMB_V1 8
#define MAX_IONUM_V1 10
#define AXIS_NUM_V1  (AXIS_NUMB_V1)

#pragma region 用户模式类型

typedef enum
{
    USER_UNKNOW_V1 = -1,
    USER_CUSTOMER_V1 = 1,
    USER_EDIT_V1,
    USER_MANAGE_V1,
    USER_FACTORY_V1,
} EUSER_MODE_V1;

EUSER_MODE_V1 EUSER_MODE_ToProxy(EUSER_MODE euser_Mode);
EUSER_MODE EUSER_MODE_FromProxy(EUSER_MODE_V1 euser_Mode_V1);

#pragma endregion

#pragma region 开发者调试类型

typedef enum
{
    DEVELOPER_CLOSE_V1,
    DEVELOPER_OPEN_V1,
} DEVELOPER_DEBUG_V1;

DEVELOPER_DEBUG_V1 DEVELOPER_DEBUG_ToProxy(DEVELOPER_DEBUG developer_Debug);
DEVELOPER_DEBUG DEVELOPER_DEBUG_FromProxy(DEVELOPER_DEBUG_V1 developer_Debug_V1);

#pragma endregion

#pragma region 权限密码

// 密码长度
#define ALL_PWD_SIZE_V1 40  // 所有密码数据总长
#define MAX_PWD_SIZE_V1 6   // 单个密码长度

// 权限密码
typedef struct tagUesrPwd_V1
{
    tagUesrPwd_V1()
    {
        eUserMode = USER_UNKNOW_V1;
        memset(szPwd, 0, sizeof(szPwd));
    }

    EUSER_MODE_V1 eUserMode;
    char szPwd[MAX_PWD_SIZE_V1 + 1];
} USER_PWD_V1;

bool USER_PWD_ToProxy(const USER_PWD &user_Pwd, USER_PWD_V1 &user_Pwd_V1);
bool USER_PWD_FromProxy(const USER_PWD_V1 &user_Pwd_V1, USER_PWD &user_Pwd);

#pragma endregion

#pragma region PING功能

// ping to check net state
typedef struct net_check_para_V1
{
    net_check_para_V1()
    {
        memset(addr, 0x00, 16);
        term = 0;
        total = 0;
        size = 0;
    }

    char addr[16];  // IP地址
    int term;       // 周期
    int total;      // 总数
    int size;       // 每包大小
} net_check_para_V1;
bool net_check_para_ToProxy(const net_check_para &netCheckPara, net_check_para_V1 &netCheckParaV1);
bool net_check_para_FromProxy(const net_check_para_V1 &netCheckParaV1, net_check_para &netCheckPara);

typedef struct net_check_ret_V1
{
    int nsend;    // 已发送
    int nrec;     // 已接受
    double loss;  // 丢失率
    double min;   // 最小往返时间
    double max;   // 最长往返时间
    double avg;   // 平均往返时间

} net_check_ret_V1;
bool net_check_ret_ToProxy(const net_check_ret &netCheckRet, net_check_ret_V1 &netCheckRetV1);
bool net_check_ret_FromProxy(const net_check_ret_V1 &netCheckRetV1, net_check_ret &netCheckRet);

#pragma endregion

#pragma region 机械臂型号

typedef enum
{
    RBTYPE_INVALID_V1 = 0,
    // 3轴
    RBTYPE_SCARA_C_V1 = 46,            // 3关节串联scara无Z轴；
    RBTYPE_SCARA_E_V1 = 47,            // 3关节串联scara无A轴；
    RBTYPE_DELTA_A_V1 = 41,            // 3轴对称并联+1轴旋转的delta
    RBTYPE_DELTA_B_V1 = 45,            // 3轴对称并联的delta
    RBTYPE_SCARA_SCREW_THREE_V1 = 48,  // 3轴+外司电批轴（三轴挂于EtherCat总线上，电批独立）
    RBTYPE_SCARA_SCREW_FOUR_V1 = 44,   // 3轴+本司电批轴（全部挂于EtherCat总线上，电批非独立）
    // 4轴
    RBTYPE_SCARA_A_V1 = 4,      // 4关节串联scara
    RBTYPE_SCARA_R_V1 = 4110,   // 倒装scara
    RBTYPE_PALLET_A_V1 = 42,    // 码垛一型
    RBTYPE_PALLET_B_V1 = 43,    // 码垛二型
    RBTYPE_SCARA_D_V1 = 4140,   // 平面SCARA，不联动
    RBTYPE_TRIPOD_A_V1 = 4710,  // tripod，3D打印机械手A
    RBTYPE_TRIPOD_B_V1 = 4720,  // tripod，3D打印机械手B
    RBTYPE_PUNCH_A_V1 = 4800,   // 冲压机械手
    RBTYPE_FOUR_NA_V1 = 4900,   // 四轴联动，无模型 PPRR
    // 5轴
    RBTYPE_FIVE_A_V1 = 5,   // 3p2r
    RBTYPE_FIVE_B_V1 = 51,  // 3p2r
    // 6轴
    RBTYPE_SIXR_A_V1 = 6,   // 通用串联6R
    RBTYPE_SIXR_B_V1 = 61,  // 通用串联6R减去两轴
    RBTYPE_SIXR_C_V1 = 62,  // 变异SCARA+2直线轴 科瑞
    RBTYPE_SIXR_D_V1 = 63   // 6轴并联机器人 Stewart
} RBTTYPE_E_V1;

RBTTYPE_E_V1 RBTTYPE_E_ToProxy(RBTTYPE_E rbttype_E);
RBTTYPE_E RBTTYPE_E_FromProxy(RBTTYPE_E_V1 rbttype_E_V1);

#pragma endregion

#pragma region IRlink配置权

typedef enum IR_CTRL_SET_V1
{
    IR_RC_ACTIVE_V1 = 0,
    IR_PLC_ACTIVE_V1 = 1,
} IR_CTRL_SET_V1;

IR_CTRL_SET_V1 IR_CTRL_SET_ToProxy(IR_CTRL_SET ir_CTRL_SET);
IR_CTRL_SET IR_CTRL_SET_FromProxy(IR_CTRL_SET_V1 ir_CTRL_SET_V1);

#pragma endregion

#pragma region ReferObj

enum ReferObj_V1 : int16s
{
    ReferNoSense_V1 = -3,
    ReferBase_V1 = -2,
    ReferFlange_V1 = -1,
    ReferObj0_V1 = 0,
    ReferObj1_V1 = 1,
    ReferObj2_V1 = 2,
    ReferObj3_V1 = 3,
    ReferObj4_V1 = 4,
    ReferObj5_V1 = 5,
    ReferObj6_V1 = 6,
    ReferObj7_V1 = 7,
    ReferObj8_V1 = 8,
    ReferObj9_V1 = 9,
    ReferObj10_V1 = 10,
    ReferObj11_V1 = 11,
    ReferObj12_V1 = 12,
    ReferObj13_V1 = 13,
    ReferObj14_V1 = 14,
    ReferObj15_V1 = 15,
};

ReferObj_V1 ReferObj_ToProxy(ReferObj referObj);
ReferObj ReferObj_FromProxy(ReferObj_V1 referObj_V1);

#pragma endregion

#pragma region ToolCalibError

typedef struct tagToolCalibError_V1
{
    tagToolCalibError_V1()
    {
        dMax = 0;
        dAve = 0;
        dMin = 0;
    }
    double dMax;
    double dAve;
    double dMin;
} ToolCalibError_V1;

bool ToolCalibError_ToProxy(const ToolCalibError &toolCalibError, ToolCalibError_V1 &toolCalibError_V1);
bool ToolCalibError_FromProxy(const ToolCalibError_V1 &toolCalibError_V1, ToolCalibError &toolCalibError);

#pragma endregion

#pragma region 自动热机参数

/// <summary>
/// 自动热机参数
/// </summary>
typedef struct _WarmUpMachineParam_V1
{
    _WarmUpMachineParam_V1()
    {
        mode = 0;
        memset(axisEnableArr, 0, sizeof(axisEnableArr));
        threshold = 10;
        time = 10;
        initSpeed = 75;
        intervalTime = 20;
    }

    int16_t mode;                        // 热机策略，0表示关闭，1表示仅考虑热机时间，2表示考虑轴温度与热机时间
    int16_t axisEnableArr[AXIS_NUM_V1];  // 轴号激活状态集合，数据长度为8(预留)，元素值1表示激活，0表示未激活，按轴序号存取
    int16_t threshold;                   // 轴温度阈值
    int16_t time;                        // 热机时间
    int16_t initSpeed;                   // 热机初始速度
    int16_t intervalTime;                // 重新热机时间间隔

} WarmUpMachineParam_V1;

bool WarmUpMachineParam_ToProxy(const WarmUpMachineParam &warmUpMachineParam, WarmUpMachineParam_V1 &warmUpMachineParam_V1);
bool WarmUpMachineParam_FromProxy(const WarmUpMachineParam_V1 &warmUpMachineParam_V1, WarmUpMachineParam &warmUpMachineParam);

#pragma endregion

#pragma region 自动热机实时信息

/// <summary>
/// 自动热机实时信息
/// </summary>
typedef struct _WarmUpMachineInfo_V1
{
    _WarmUpMachineInfo_V1()
    {
        state = 0;
        curSpeed = 0;
    }
    int16_t state;     // 热机状态，1表示热机中，0表示未在热机
    int16_t curSpeed;  // 热机时机器人当前速度
} WarmUpMachineInfo_V1;

bool WarmUpMachineInfo_ToProxy(const WarmUpMachineInfo &warmUpMachineInfo, WarmUpMachineInfo_V1 &warmUpMachineInfo_V1);
bool WarmUpMachineInfo_FromProxy(const WarmUpMachineInfo_V1 &warmUpMachineInfo_V1, WarmUpMachineInfo &warmUpMachineInfo);

#pragma endregion

#pragma region 模式类型

// 模式类型
typedef enum
{
    MODE_UNKNOW_V1 = -1,      // 未知
    MODE_TEACH_V1 = 1,        // 示教
    MODE_REAPPEAR_V1 = 2,     // 再现
    MODE_TEACH_CHECK_V1 = 3,  // 单步示教检查
    MODE_FOUR_V1 = 4,
    MODE_TEACH_RUN_V1 = 5,  // 连续示教运行
    MODE_HOMING_V1 = 6,     // 回零

    MODE_TYPE_BUTT_V1
} MODE_TYPE_V1;

MODE_TYPE_V1 MODE_TYPE_ToProxy(MODE_TYPE mode_TYPE);
MODE_TYPE MODE_TYPE_FromProxy(MODE_TYPE_V1 mode_TYPE_V1);

#pragma endregion

#pragma region 自学习

typedef struct torqueRectifyAutoLearnPara_V1
{
    torqueRectifyAutoLearnPara_V1()
    {
        learnSts = 0;
        memset(learnRet, 0, sizeof(double) * 8);
    }
    short learnSts;      // 学习状态（0-未开始 1-进行中 2-已完成 -1 出错）
    double learnRet[8];  // 学习结果
} TorqueRectifyAutoLearnPara_V1;

bool TorqueRectifyAutoLearnPara_ToProxy(const TorqueRectifyAutoLearnPara &torqueRectifyAutoLearnPara, TorqueRectifyAutoLearnPara_V1 &torquerectifyAutoLearnPara_V1);
bool TorqueRectifyAutoLearnPara_FromProxy(const TorqueRectifyAutoLearnPara_V1 &torquerectifyAutoLearnPara_V1, TorqueRectifyAutoLearnPara &torqueRectifyAutoLearnPara);

#pragma endregion

#pragma region 软浮动参数

/// <summary>
/// 软浮动参数
/// </summary>
#pragma pack(1)
typedef struct _SoftMovePara_V1
{
    _SoftMovePara_V1()
    {
        i16Switch = 0;
        i16Mode = 0;
        i16RefCoor = 0;
        memset(i16CartSoftMoveRatio, 0, sizeof(i16CartSoftMoveRatio));
        memset(i16JointSoftMoveRatio, 0, sizeof(i16JointSoftMoveRatio));
        f32OperatRangeX = 200;
        f32OperatRangeY = 200;
        f32OperatRangeZ = 200;
    }

    int16s i16Switch;                                 // 开关
    int16s i16Mode;                                   // 软浮动模式
    int16s i16RefCoor;                                // 参考坐标系
    int16s i16CartSoftMoveRatio[JOINT_AXIS_NUM_V1];   // 笛卡尔软浮动比率
    int16s i16JointSoftMoveRatio[JOINT_AXIS_NUM_V1];  // 关节软浮动比率
    float f32OperatRangeX;                            // 补偿范围X
    float f32OperatRangeY;                            // 补偿范围Y
    float f32OperatRangeZ;                            // 补偿范围Z
} SoftMovePara_V1;
#pragma pack()

bool SoftMovePara_ToProxy(const SoftMovePara &softMovePara, SoftMovePara_V1 &softMovePara_V1);
bool SoftMovePara_FromProxy(const SoftMovePara_V1 &softMovePara_V1, SoftMovePara &softMovePara);

#pragma endregion

#pragma region 写入Ethcat

typedef struct _ETHCAT_PARA_V1
{
    _ETHCAT_PARA_V1()
    {
        ActiveCmd = 0;
        SiteAlias = 0;
        MaxFramLossTimes = 0;
    };

    unsigned char ActiveCmd;          // 0表示关闭，1表示激活
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次，最小值为8，最大值为65535）
} EthcatPara_V1;

bool EthcatPara_ToProxy(const EthcatPara &ethcatPara, EthcatPara_V1 &ethcatPara_V1);
bool EthcatPara_FromProxy(const EthcatPara_V1 &ethcatPara_V1, EthcatPara &ethcatPara);

#pragma endregion

#pragma region 读取Ethcat

typedef struct _ETHCAT_STS_V1
{
    _ETHCAT_STS_V1()
    {
        ActiveSts = 0;   // 0-未开启
        ConnectSts = 0;  // 0-未连接
        SiteAlias = 0;
        MaxFramLossTimes = 8;
    }
    unsigned char ActiveSts;          // Ethcat激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;         // Ethcat连接状态:0 - 未连接，1 - 已连接
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次）
} EthcatSts_V1;

bool EthcatSts_ToProxy(const EthcatSts &ethcatSts, EthcatSts_V1 &ethcatSts_V1);
bool EthcatSts_FromProxy(const EthcatSts_V1 &ethcatSts_V1, EthcatSts &ethcatSts);

#pragma endregion

#pragma region EthernetIp写入状态

// EthernetIp 写入状态
typedef struct _ETHERNET_IP_PARA_V1
{
    _ETHERNET_IP_PARA_V1()
    {
        ActiveCmd = 0;  // 0表示关闭
    }
    unsigned char ActiveCmd;  // 0表示关闭，1表示激活
} EthernetIpPara_V1;

bool EthernetIpPara_ToProxy(const EthernetIpPara &ethernetIpPara, EthernetIpPara_V1 &ethernetIpPara_V1);
bool EthernetIpPara_FromProxy(const EthernetIpPara_V1 &ethernetIpPara_V1, EthernetIpPara &ethernetIpPara);

#pragma endregion

#pragma region EthernetIp读取状态

// EthernetIp 读取状态
typedef struct _ETHERNET_IP_STS_V1
{
    _ETHERNET_IP_STS_V1()
    {
        ActiveSts = 0;  // 0-未开启
        ConnectSts = 0;
        for (size_t i = 0; i < 16; i++)
        {
            MsterIp[i] = 0;  // 0-未连接
        }
        MasterPort = 502;   // EIP主站(客户端)的端口
        SlavePort = 44818;  // 固定为44818
    }
    unsigned char ActiveSts;    // EIP激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;   // EIP连接状态:0-未连接，1-已连接
    char MsterIp[16];           // EIP主站(客户端)IP地址
    unsigned short MasterPort;  // EIP主站(客户端)的端口
    unsigned short SlavePort;   // EIP从站(服务器)端口,暂时固定为44818
} EthernetIpSts_V1;

bool EthernetIpSts_ToProxy(const EthernetIpSts &ethernetIpSts, EthernetIpSts_V1 &ethernetIpSts_V1);
bool EthernetIpSts_FromProxy(const EthernetIpSts_V1 &ethernetIpSts_V1, EthernetIpSts &ethernetIpSts);

#pragma endregion

#pragma region MC

// MC激活指令
typedef struct _MC_ACTIVE_PARA_V1
{
    _MC_ACTIVE_PARA_V1()
    {
        ActiveFlag = 0;  // 0表示关闭，1表示激活
    }
    // 激活指令
    unsigned char ActiveFlag;  // 0表示关闭，1表示激活
} McActivePara_V1;

bool McActivePara_ToProxy(const McActivePara &mcActivePara, McActivePara_V1 &mcActivePara_V1);
bool McActivePara_FromProxy(const McActivePara_V1 &mcActivePara_V1, McActivePara &mcActivePara);

// MC连接状态
typedef struct _MC_CONNECT_PARA_V1
{
    _MC_CONNECT_PARA_V1()
    {
        for (size_t i = 0; i < 16; i++)
        {
            ServerIp[i] = 0;  // IP地址
        }
        ConnectIndex = 0;
        Port = 0;           // 端口号
        ConnectFlag = 0;    // 0未连接，1已连接
        IsAutoConnect = 0;  // 0-不进行自动重连，1-自动重连
    }
    unsigned char ConnectIndex;   // 连接索引
    unsigned char ServerIp[16];   // MC服务器IP
    unsigned short Port;          // MC端口号
    unsigned char ConnectFlag;    // 连接标识(读的时候标识状态，0-未连接，1-已连接；写的时候表示命令；0-断开，1-连接)
    unsigned char IsAutoConnect;  // 是否自动重连，0-不进行自动重连，1-进行自动重连
} McConnectPara_V1;

bool McConnectPara_ToProxy(const McConnectPara &mcConnectPara, McConnectPara_V1 &mcConnectPara_V1);
bool McConnectPara_FromProxy(const McConnectPara_V1 &mcConnectPara_V1, McConnectPara &mcConnectPara);

#pragma endregion

#pragma region Modbus

// TCP
typedef struct tagModbusTCP_Para_V1
{
    tagModbusTCP_Para_V1()
    {
        owner = 0;
        sts = 0;
        port = 502;
        framedelay = 1;
    }
    unsigned char owner;        // 控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // 运行情况 0-未运行，1-运行
    unsigned short port;        // 端口号
    unsigned short framedelay;  // 帧间隔
} ModbusTCP_Para_V1;

bool ModbusTCP_Para_ToProxy(const ModbusTCP_Para &modbusTCP_Para, ModbusTCP_Para_V1 &modbusTCP_Para_V1);
bool ModbusTCP_Para_FromProxy(const ModbusTCP_Para_V1 &modbusTCP_Para_V1, ModbusTCP_Para &modbusTCP_Para);

// RTU
typedef struct tagModbusRTU_Para_V1
{
    tagModbusRTU_Para_V1()
    {
        owner = 0;
        sts = 0;
        baud = 5;
        stopbits = 0;
        databits = 0;
        parity = 0;
        tmode = 0;
        slaveid = 1;
        framedelay = 5;
        timeout = 0;
    }
    unsigned char owner;        // Modbus控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // Modbus 运行情况 0-未运行，1-运行
    unsigned char baud;         // 波特率，索引值，其具体值见Baud数组
    unsigned char stopbits;     // 停止位 0-1位 1-2位
    unsigned char databits;     // 数据位 0-7位 1-8位
    unsigned char parity;       // 奇偶校验 0-无校验 1-奇校验 2-偶校验
    unsigned char tmode;        // 传输模式 0-RTU 1-ASCII
    unsigned char slaveid;      // 站点号
    unsigned short framedelay;  // 帧间隔
    unsigned short timeout;     // 超时时间
} ModbusRTU_Para_V1;

bool ModbusRTU_Para_ToProxy(const ModbusRTU_Para &modbusRTU_Para, ModbusRTU_Para_V1 &modbusRTU_Para_V1);
bool ModbusRTU_Para_FromProxy(const ModbusRTU_Para_V1 &modbusRTU_Para_V1, ModbusRTU_Para &modbusRTU_Para);

// Modbus写入总结构体
typedef struct MODBUS_PARA_CONFIG_V1
{
    MODBUS_PARA_CONFIG_V1()
    {
        ModbusAddrType = 0;  // 0-旧版地址
    };
    unsigned char ModbusAddrType;       // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCP_Para_V1 stModbusTcpPara;  // Modbus配置结构体
    ModbusRTU_Para_V1 stModbusRtuPara;  // ModbusRtu配置结构体
} ModbusParaConfig_V1;

bool ModbusParaConfig_ToProxy(const ModbusParaConfig &modbusParaConfig, ModbusParaConfig_V1 &modbusParaConfig_V1);
bool ModbusParaConfig_FromProxy(const ModbusParaConfig_V1 &modbusParaConfig_V1, ModbusParaConfig &modbusParaConfig);

// Modbus读取总结构体
typedef struct MODBUS_CONNECT_STS_V1
{
    MODBUS_CONNECT_STS_V1()
    {
        ModbusAddrType = 0;
        for (size_t i = 0; i < 16; i++)
        {
            ModbusTcpConnectFlag[i] = 0;  // 0表示未连接
            ModbusTcpClientPort[i] = 502;
            memset(&ModbusTcpClientIP[i], 0, 16 * sizeof(unsigned char));
        }
    }

    unsigned char ModbusAddrType;            // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCP_Para_V1 stModbusTcpPara;       // Modbus配置结构体
    ModbusRTU_Para_V1 stModbusRtuPara;       // ModbusRtu配置结构
    char ModbusTcpConnectFlag[16];           // modbusTcp连接状态，0表示未连接，1表示已连
    char ModbusTcpClientIP[16][16];          // 主站IP地址（第一行表示第一个连接上的主站的IP）
    unsigned short ModbusTcpClientPort[16];  // 主站端口（第一元素表示第一个连接上的主站的端口）
} ModbusConnectSts_V1;

bool ModbusConnectSts_ToProxy(const ModbusConnectSts &modbusConnectSts, ModbusConnectSts_V1 &modbusConnectSts_V1);
bool ModbusConnectSts_FromProxy(const ModbusConnectSts_V1 &modbusConnectSts_V1, ModbusConnectSts &modbusConnectSts);

#pragma endregion

#pragma region Profinet

// Profinet总线激活指令
typedef struct _BUS_PN_ACTIVE_CFG_V1
{
    _BUS_PN_ACTIVE_CFG_V1()
    {
        ActiveCmd = 0;
        MaxFrameDropNumber = 10;
    }
    unsigned char ActiveCmd;            // PN激活指令:0-关闭，1-激活
    unsigned short MaxFrameDropNumber;  // 允许的最大丢帧次数
} PnActiveCfg_V1;

bool PnActiveCfg_ToProxy(const PnActiveCfg &pnActiveCfg, PnActiveCfg_V1 &pnActiveCfg_V1);
bool PnActiveCfg_FromProxy(const PnActiveCfg_V1 &pnActiveCfg_V1, PnActiveCfg &pnActiveCfg);

// Profinet总线连接状态
typedef struct _BUS_PN_CONNECT_STS_V1
{
    _BUS_PN_CONNECT_STS_V1()
    {
        ActiveSts = 0;
        ConnectSts = 0;
        for (size_t i = 0; i < 16; i++)
        {
            ProfinetIP[i] = 0;
            DefaultGateWay[i] = 0;
        }
        for (int j = 0; j < 18; j++)
        {
            MacAddress[j] = 0;
        }
        VersionID = 0;
        MaxFrameDropNumber = 10;
    }
    unsigned char ActiveSts;            // PN激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;           // PN连接状态:0-未连接，1-已连接
    char ProfinetIP[16];                // ip地址
    char DefaultGateWay[16];            // 默认网关
    char MacAddress[18];                // MAC地址
    unsigned short VersionID;           // 版本号
    unsigned short MaxFrameDropNumber;  // 已设置的最大丢帧次数
} PnConnectSts_V1;

bool PnConnectSts_ToProxy(const PnConnectSts &pnConnectSts, PnConnectSts_V1 &pnConnectSts_V1);
bool PnConnectSts_FromProxy(const PnConnectSts_V1 &pnConnectSts_V1, PnConnectSts &pnConnectSts);

#pragma endregion

#pragma region EthCfg

typedef struct tagEthCfg_V1
{
    tagEthCfg_V1()
    {
        strDHCP = "0";
        strIP = "0.0.0.0";
    }
    string strDHCP;
    string strIP;
} EthCfg_V1;

bool EthCfg_ToProxy(const EthCfg &ethCfg, EthCfg_V1 &ethCfg_V1);
bool EthCfg_FromProxy(const EthCfg_V1 &eEthCfg_V1, EthCfg &ethCfg);

typedef struct tagControllerEthCfg_V1
{
    EthCfg_V1 strcEth0;
    EthCfg_V1 strcEth1;
} ControllerEthCfg_V1;

bool ControllerEthCfg_ToProxy(const ControllerEthCfg &controllerEthCfg, ControllerEthCfg_V1 &controllerEthCfg_V1);
bool ControllerEthCfg_FromProxy(const ControllerEthCfg_V1 &controllerEthCfg_V1, ControllerEthCfg &controllerEthCfg);

#pragma endregion

#pragma region AddrInfo

struct AddrInfo_V1
{
    char IP[16] = { 0 };  // IP信息，位数最多16位：192.168.222.333
    int Port = 0;         // 端口信息
};

bool AddrInfo_ToProxy(const AddrInfo &addrInfo, AddrInfo_V1 &addrInfo_V1);
bool AddrInfo_FromProxy(const AddrInfo_V1 &addrInfo_V1, AddrInfo &addrInfo);

struct CommonNetStatus_V1
{
    AddrInfo_V1 LocalAddrInfo;  // 本地网络信息
    AddrInfo_V1 PeerAddrInfo;   // 对端网络信息
    int NetStatus = 0;       // 0:unconnected; 1:connected 2:主动关闭服务器端口
    int LocalNetType = 0;    // 0: client; 1: server
};

bool CommonNetStatus_ToProxy(const CommonNetStatus &commonNetStatus, CommonNetStatus_V1 &commonNetStatus_V1);
bool CommonNetStatus_FromProxy(const CommonNetStatus_V1 &commonNetStatus_V1, CommonNetStatus &commonNetStatus);

#pragma endregion

#pragma region 现场总线从站配置信息

typedef struct MODBUS_ADDRASSIGN_CONFIG_V1
{
    MODBUS_ADDRASSIGN_CONFIG_V1()
    {
        inputSize = 256;
        outputSize = 256;
        modbusInputCoilSize = 20;
        modbusInputRegSize = 236;
        modbusOutputCoilSize = 20;
        modbusOutputRegSize = 236;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short modbusInputCoilSize;
    unsigned short modbusInputRegSize;
    unsigned short modbusOutputCoilSize;
    unsigned short modbusOutputRegSize;
} ModbusAddrassignConfig_V1;

bool MODBUS_ADDRASSIGN_CONFIG_ToProxy(const MODBUS_ADDRASSIGN_CONFIG &modbus_ADDRASSIGN_CONFIG, MODBUS_ADDRASSIGN_CONFIG_V1 &modbus_ADDRASSIGN_CONFIG_V1);
bool MODBUS_ADDRASSIGN_CONFIG_FromProxy(const MODBUS_ADDRASSIGN_CONFIG_V1 &modbus_ADDRASSIGN_CONFIG_V1, MODBUS_ADDRASSIGN_CONFIG &modbus_ADDRASSIGN_CONFIG);

struct EIP_ADDRASSIGN_CONFIG_V1
{
    EIP_ADDRASSIGN_CONFIG_V1()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

bool EIP_ADDRASSIGN_CONFIG_ToProxy(const EIP_ADDRASSIGN_CONFIG &eIP_ADDRASSIGN_CONFIG, EIP_ADDRASSIGN_CONFIG_V1 &eIP_ADDRASSIGN_CONFIG_V1);
bool EIP_ADDRASSIGN_CONFIG_FromProxy(const EIP_ADDRASSIGN_CONFIG_V1 &eIP_ADDRASSIGN_CONFIG_V1, EIP_ADDRASSIGN_CONFIG &eIP_ADDRASSIGN_CONFIG);

struct ETHERCAT_ADDRASSIGN_CONFIG_V1
{
    ETHERCAT_ADDRASSIGN_CONFIG_V1()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

bool ETHERCAT_ADDRASSIGN_CONFIG_ToProxy(const ETHERCAT_ADDRASSIGN_CONFIG &eTHERCAT_ADDRASSIGN_CONFIG, ETHERCAT_ADDRASSIGN_CONFIG_V1 &eTHERCAT_ADDRASSIGN_CONFIG_V1);
bool ETHERCAT_ADDRASSIGN_CONFIG_FromProxy(const ETHERCAT_ADDRASSIGN_CONFIG_V1 &eTHERCAT_ADDRASSIGN_CONFIG_V1, ETHERCAT_ADDRASSIGN_CONFIG &eTHERCAT_ADDRASSIGN_CONFIG);

struct MC_ADDRASSIGN_CONFIG_V1
{
    MC_ADDRASSIGN_CONFIG_V1()
    {
        inputSize = 256;
        outputSize = 256;
        mcInputStartAddr = 1025;
        mcInputRegSize = 2025;
        mcOutputStartAddr = 256;
        mcOutputRegSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short mcInputStartAddr;
    unsigned short mcInputRegSize;
    unsigned short mcOutputStartAddr;
    unsigned short mcOutputRegSize;
};

bool MC_ADDRASSIGN_CONFIG_ToProxy(const MC_ADDRASSIGN_CONFIG &mc_ADDRASSIGN_CONFIG, MC_ADDRASSIGN_CONFIG_V1 &mc_ADDRASSIGN_CONFIG_V1);
bool MC_ADDRASSIGN_CONFIG_FromProxy(const MC_ADDRASSIGN_CONFIG_V1 &mc_ADDRASSIGN_CONFIG_V1, MC_ADDRASSIGN_CONFIG &mc_ADDRASSIGN_CONFIG);

struct PN_ADDRASSIGN_CONFIG_V1
{
    PN_ADDRASSIGN_CONFIG_V1()
    {
        inputSize = 127;
        outputSize = 127;
    }
    unsigned short inputSize;
    unsigned short outputSize;
};

bool PN_ADDRASSIGN_CONFIG_ToProxy(const PN_ADDRASSIGN_CONFIG &pn_ADDRASSIGN_CONFIG, PN_ADDRASSIGN_CONFIG_V1 &pn_ADDRASSIGN_CONFIG_V1);
bool PN_ADDRASSIGN_CONFIG_FromProxy(const PN_ADDRASSIGN_CONFIG_V1 &pn_ADDRASSIGN_CONFIG_V1, PN_ADDRASSIGN_CONFIG &pn_ADDRASSIGN_CONFIG);

struct FIELDBUS_MEM_ASSIGN_CONFIG_V1
{
    FIELDBUS_MEM_ASSIGN_CONFIG_V1()
    {
        memset(Version, 0, sizeof(char) * 8);
        for (int i = 0; i < 4; i++)
        {
            MC_ADDRASSIGN_CONFIG_V1 mc;
            mcConfig[i] = mc;
        }
    };
    char Version[8];
    MODBUS_ADDRASSIGN_CONFIG_V1 modbusConfig;
    EIP_ADDRASSIGN_CONFIG_V1 eipConfig;
    ETHERCAT_ADDRASSIGN_CONFIG_V1 etherCATConfig;
    MC_ADDRASSIGN_CONFIG_V1 mcConfig[4];
    PN_ADDRASSIGN_CONFIG_V1 pnConfig;
};

bool FIELDBUS_MEM_ASSIGN_CONFIG_ToProxy(const FIELDBUS_MEM_ASSIGN_CONFIG &fIELDBUS_MEM_ASSIGN_CONFIG, FIELDBUS_MEM_ASSIGN_CONFIG_V1 &fIELDBUS_MEM_ASSIGN_CONFIG_V1);
bool FIELDBUS_MEM_ASSIGN_CONFIG_FromProxy(const FIELDBUS_MEM_ASSIGN_CONFIG_V1 &fIELDBUS_MEM_ASSIGN_CONFIG_V1, FIELDBUS_MEM_ASSIGN_CONFIG &fIELDBUS_MEM_ASSIGN_CONFIG);

#pragma endregion

}  // namespace InoRobBusinessProxy
