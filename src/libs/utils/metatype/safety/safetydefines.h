#pragma once

#include <QVariant>

#define COBOT_DI_NUM                (8)              /* 安全DI数量 */
#define COBOT_DO_NUM                (5)              /* 安全DO数量 */
#define COBOT_APOS_LIMIT_NUM        (6)              /* 轴数量 */
#define COBOT_AVEL_LIMIT_NUM        (6)              /* 轴数量 */
#define COBOT_ATORQUE_LIMIT_NUM     (6)
#define COBOT_APOWER_LIMIT_NUM      (6)
#define COBOT_STATIC_LIMIT_NUM      (6)
#define COBOT_POSDISMATCH_LIMIT_NUM      (6)
#define COBOT_APOS_GROUP_NUM        (8)              /* 轴位置组数 */
#define COBOT_AVEL_GROUP_NUM        (8)              /* 轴速度组数 */
#define COBOT_CVEL_GROUP_NUM        (8)
#define COBOT_ATORQUE_GROUP_NUM     (8)
#define COBOT_POSDISMATCH_GROUP_NUM     (8)
#define COBOT_APOWER_GROUP_NUM      (8)
#define COBOT_STATIC_GROUP_NUM      (8)
#define COBOT_TCP_FORCE_GROUP_NUM   (8)
#define COBOT_TCP_DIRECT_GROUP_NUM  (8)
#define COBOT_BODY_MOMENTUM_GROUP_NUM   (8)
#define COBOT_BODY_POWER_GROUP_NUM      (8)
#define COBOT_IZONE_CVEL_ARRAY_LENGTH           (8)      /* 笛卡尔速度组数 */

#define CO_IZONE_DESCRIPTION_CHARLENGTH    (32)  //干涉区有关备注, 全部为32长度字符数组
#define CO_IZONE_FLOATARRAYLENGTH          (6)  //干涉区有关浮点数数组, 大部分为6长度
#define CO_IZONE_MTCP_UINTARRAYLENGTH      (4)  //MTCPshort数组, 为4长度
#define CO_IZONE_BALL_POSARRAYLENGTH       (3)  //Ball Pos数组, 3长度
#define CO_IZONE_TOOLBOX_TYPE3_FLOATARRAY  (13)  //TOOLBOX第三种类型, 浮点数数组长度13
#define CO_IZONE_INTERFERZONESSTATUSLENGTH (16)  //干涉区状态长度16
#define CO_IZONE_ITOOL_TYPENUM             (4)  // 末端监测对象类别数目4
#define CO_IZONE_ITOOL_TOOLBOXTYPENUM      (3)  //工具包围盒类型数目3
#define CO_IZONE_EPSILON                   (0.1)  //工具包围盒类型数目3
#define CO_IZONE_WOBJPARAMSNUM             (12)  // 干涉区工具工件参数相关
#define CO_IZONE_MTCPTOOLPARAMSNUM         (6)  // 干涉区工具工件参数相关

#define U_COBOT_AXIS_NUM                    (6)

enum CobotSafeParaStatus
{
    Cobot_SPS_INITIAL = 0,  // 初始化
    Cobot_SPS_READED = 1,   // 已读取
    Cobot_SPS_EDITED = 2,   // 编辑未保存
    Cobot_SPS_SYNC = 3,     // 已同步
    Cobot_SPS_WRITED = 4,   // 已下发
};

enum CobotSafeParaRetVal
{
    Cobot_SPR_SUC = 0,
    Cobot_SPR_INDEX = 1,           // 地图索引错误
    Cobot_SPR_POINTER = 2,         // 变量指针错误
    Cobot_SPR_STATUS = 3,          // 错误的数据状态
    Cobot_SPR_ERRFUNC = 4,         // 查询功能得到 否的结果
    Cobot_SPR_INITIAL = 5,         // 初始化一个错误的返回值
    Cobot_SPR_NONEMOVE = 6,        // 没有执行过
    Cobot_SPR_SYSREADY = 7,        // systemReady标志位为0
    Cobot_SPR_CRCERR = 108,        // 工业安全CRC错误
    Cobot_SPR_READBACK = 109,      // 回读错误
    Cobot_SPR_RETBIT = 110,        // 回应位置错误
    Cobot_SPR_MCURET_FAIL = 30583  // 从MCU获取数据失败, 0x7777
};

enum CobotSafeParaEnum
{
    Cobot_EEP_CRC = 0,                 // CRC
    Cobot_EEP_PASSWORD = 1,            // 密码
    Cobot_EEP_STOPCONF = 2,            // 停机配置
    Cobot_EEP_LOW_SPEED = 3,           // 安全低速
    Cobot_EEP_DI = 4,                  // 安全IO DI
    Cobot_EEP_DO = 5,                  // 安全IO DO
    Cobot_EEP_APOSWAY = 6,             // 轴位置生效方式
    Cobot_EEP_AVELWAY = 7,             // 轴速度生效方式
    Cobot_EEP_APOS_0 = 8,              // 轴位置0
    Cobot_EEP_APOS_1 = 9,              // 轴位置1
    Cobot_EEP_APOS_2 = 10,             // 轴位置2
    Cobot_EEP_APOS_3 = 11,             // 轴位置3
    Cobot_EEP_APOS_4 = 12,             // 轴位置4
    Cobot_EEP_APOS_6 = 14,             // 轴位置6
    Cobot_EEP_APOS_7 = 15,             // 轴位置7
    Cobot_EEP_AVEL_0 = 16,             // 轴速度0
    Cobot_EEP_CVELWAY = 24,            // 笛卡尔速度生效方式
    Cobot_EEP_CPOSWAY = 25,            // 笛卡尔位置生效方式
    Cobot_EEP_CVEL_0 = 26,             // 笛卡尔速度0
    Cobot_EEP_IZONE_STATUS_0 = 34,     // 干涉区状态0
    Cobot_EEP_ITOOL_STATUS_0 = 50,     // 末端监测对象状态状态0
    Cobot_EEP_IZONE_PARA_0 = 66,       // 干涉区配置参数0
    Cobot_EEP_IZONE_WOBJ_0 = 82,       // 干涉区工件参数0
    Cobot_EEP_ITOOL_PARA_0 = 98,       // 末端监测对象配置参数0
    Cobot_EEP_ITOOL_MTCPTOOL_0 = 114,  // 末端监测对象, MTCP工具参数0
    Cobot_EEP_ITOOL_MTCPTOOL_F = 129,  // 末端监测对象, MTCP工具参数15
    Cobot_EEP_SAFEIO_DITRIGGER = 130,  // 安全IO DI阈值
    Cobot_EEP_TOOLPARA_0 = 131,        // 工具参数
    Cobot_EEP_TOOLPARA_15 = 146,
    Cobot_EEP_WOBJPARA_0 = 147,        // 工件参数
    Cobot_EEP_WOBJPARA_15 = 162,
    Cobot_EEP_SAFETOOLMODE = 163,  // 安全工具设置
    Cobot_EEP_CTCPFORCE = 164,         // 笛卡尔力
    Cobot_EEP_STATICWAY = 165,         // 安全静止生效方式
    Cobot_EEP_STATIC_0 = 166,          // 安全静止0
    Cobot_EEP_STATIC_1 = 167,          // 安全静止1
    Cobot_EEP_STATIC_2 = 168,          // 安全静止2
    Cobot_EEP_STATIC_3 = 169,          // 安全静止3
    Cobot_EEP_STATIC_4 = 170,          // 安全静止4
    Cobot_EEP_STATIC_5 = 171,          // 安全静止5
    Cobot_EEP_STATIC_6 = 172,          // 安全静止6
    Cobot_EEP_STATIC_7 = 173,          // 安全静止7
    Cobot_EEP_HOMING = 174,            // 安全原点
    Cobot_EEP_BODYMOMENTUM = 175,      // 整机动量
    Cobot_EEP_BODYPOWER = 176,         // 整机功率
    Cobot_EEP_TCPDIRECTIONWAY = 177,   // TCP方向生效方式
    Cobot_EEP_TCPDIRECTION_0 = 178,    // TCP方向0
    Cobot_EEP_TCPDIRECTION_1 = 179,    // TCP方向1
    Cobot_EEP_TCPDIRECTION_2 = 180,    // TCP方向2
    Cobot_EEP_TCPDIRECTION_3 = 181,    // TCP方向3
    Cobot_EEP_TCPDIRECTION_4 = 182,    // TCP方向4
    Cobot_EEP_TCPDIRECTION_5 = 183,    // TCP方向5
    Cobot_EEP_TCPDIRECTION_6 = 184,    // TCP方向6
    Cobot_EEP_TCPDIRECTION_7 = 185,    // TCP方向7
    Cobot_EEP_STOPDISTANCE = 186,      // 停机距离
    Cobot_EEP_STOPTIME = 187,          // 停机时间
    Cobot_EEP_STOP_TOLERANCE = 188,    // 停机抖动容差
    Cobot_EEP_REDUCEMODE_APOS_0 = 189, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_1 = 190, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_2 = 191, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_3 = 192, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_4 = 193, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_5 = 194, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_6 = 195, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_APOS_7 = 196, // 缩减模式轴位置
    Cobot_EEP_REDUCEMODE_AVEL_0 = 197, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_1 = 198, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_2 = 199, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_3 = 200, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_4 = 201, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_5 = 202, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_6 = 203, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_AVEL_7 = 204, // 缩减模式轴速度
    Cobot_EEP_REDUCEMODE_CVEL = 205,   // 缩减模式笛卡尔速度
    Cobot_EEP_ELBOW_SWITCH = 206,      // 肘部监控开关
    Cobot_EEP_POSITIONDISMATCHWAY = 207,   // 位置不匹配生效方式
    Cobot_EEP_POSITIONDISMATCH_0 = 208,    // 位置不匹配0
    Cobot_EEP_POSITIONDISMATCH_1 = 209,    // 位置不匹配1
    Cobot_EEP_POSITIONDISMATCH_2 = 210,    // 位置不匹配2
    Cobot_EEP_POSITIONDISMATCH_3 = 211,    // 位置不匹配3
    Cobot_EEP_POSITIONDISMATCH_4 = 212,    // 位置不匹配4
    Cobot_EEP_POSITIONDISMATCH_5 = 213,    // 位置不匹配5
    Cobot_EEP_POSITIONDISMATCH_6 = 214,    // 位置不匹配6
    Cobot_EEP_POSITIONDISMATCH_7 = 215,    // 位置不匹配7
    Cobot_EEP_DRAGTEACH = 216,             // 拖动示教
    Cobot_EEP_CHECKYES = 217,          // 数据同步到EEPROM
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_0 = 218,    // 获取组末端向量0
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_1 = 219,    // 获取组末端向量1
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_2 = 220,    // 获取组末端向量2
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_3 = 221,    // 获取组末端向量3
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_4 = 222,    // 获取组末端向量4
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_5 = 223,    // 获取组末端向量5
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_6 = 224,    // 获取组末端向量6
    Cobot_RAM_TCP_DIRECT_GET_VECTOR_7 = 225,    // 获取组末端向量7
    Cobot_RAM_ACTIVE_SAFETY_MONITOR   = 226,    // 激活安全监控
    Cobot_RAM_CHECKYES = 227,          // 数据同步RAM
    Cobot_EEP_SYSTEM_READY = 228,      // EEP握手成功
    Cobot_RAM_RESEST = 229,
    Cobot_RAM_RESEST_STATUS = 230,
    Cobot_SPARA_MEMBER_NUM = 231,      // 数据地图长度(内存变量个数)
};

enum CobotSafeIOCfgItem
{
    Cobot_SIOC_NONE = 0,

    Cobot_SIOC_DI_STARTENUM = 1,
    Cobot_SIOC_DI_EMERSTOP = 1,
    Cobot_SIOC_DI_SAFEDOOR = 2,
    Cobot_SIOC_DI_APOS = 3,
    Cobot_SIOC_DI_AVEL = 4,
    Cobot_SIOC_DI_CPOS = 5,
    Cobot_SIOC_DI_CVEL = 6,
    Cobot_SIOC_DI_SAFELOWSPEED = 7,
    Cobot_SIOC_DI_TCPORECP = 8,
    Cobot_SIOC_DI_BIT0 = 9,
    Cobot_SIOC_DI_BIT1 = 10,
    Cobot_SIOC_DI_BIT2 = 11,
    Cobot_SIOC_DI_BIT3 = 12,
    Cobot_SIOC_DI_SPEEDREDUCING_LEVEL1 = 13,  // 缩减模式速度缩减等级1
    Cobot_SIOC_DI_SPEEDREDUCING_LEVEL2 = 14,  // 缩减模式速度缩减等级2
    Cobot_SIOC_DI_PROTECTION_STOP_RESET = 15,         // 保护性停止复位
    Cobot_SIOC_DI_TCP_FORCE = 16,                     // TCP力监控
    Cobot_SIOC_DI_TCP_DIRECTION = 17,                 // TCP力方向监控
    Cobot_SIOC_DI_JOINT_TORQUE = 18,                  // 关节转矩监控
    Cobot_SIOC_DI_JOINT_POWER = 19,                   // 关节功率监控
    Cobot_SIOC_DI_BODY_POWER = 20,                    // 整机功率监控
    Cobot_SIOC_DI_BODY_MOMENTUM = 21,                 // 整机动量监控
    Cobot_SIOC_DI_STATIC = 22,                        // 安全静止监控
    Cobot_SIOC_DI_POSITION_NOT_MATCH = 23,            // 位置不匹配监控
    Cobot_SIOC_DI_SAFETY_ORIGIN = 24,                 // 安全原点到位
    Cobot_SIOC_DI_LASTENUM = 25,

    Cobot_SIOC_DO_STARTENUM = 201,
    Cobot_SIOC_DO_EMERSTOP = 201,
    Cobot_SIOC_DO_STATUS_RUN = 202,
    Cobot_SIOC_DO_STATUS_STOP = 203,
    Cobot_SIOC_DO_APOS = 204,
    Cobot_SIOC_DO_AVEL = 205,
    Cobot_SIOC_DO_CPOS = 206,
    Cobot_SIOC_DO_CVEL = 207,
    Cobot_SIOC_DO_SAFELOWSPEED = 208,
    Cobot_SIOC_DO_SAFESTATUS = 209,
    Cobot_SIOC_DO_SPEEDREDUCING_LEVEL1 = 210,  // 缩减模式速度缩减等级1
    Cobot_SIOC_DO_SPEEDREDUCING_LEVEL2 = 211,  // 缩减模式速度缩减等级2
    Cobot_SIOC_DO_SYSTEM_EMERGECY_STOP = 212,     // 系统急停状态
    Cobot_SIOC_DO_SYSTEM_PROTECTION_STOP = 213,   // 系统保护性停止状态
    Cobot_SIOC_DO_STOP_NOT = 214,                 // 非停止状态
    Cobot_SIOC_DO_REDUCING_MODE_NOT = 215,        // 非缩减模式状态
    Cobot_SIOC_DO_REDUCING_MODE = 216,            // 缩减模式状态
    Cobot_SIOC_DO_SAFETY_ORIGIN = 217,            // 安全原点到位状态
    Cobot_SIOC_DO_TCP_FORCE = 218,                // TCP力监控状态
    Cobot_SIOC_DO_TCP_DIRECTION = 219,            // TCP方向监控状态
    Cobot_SIOC_DO_JOINT_TORQUE = 220,             // 关节转矩监控状态
    Cobot_SIOC_DO_JOINT_POWER = 221,              // 关节功率监控状态
    Cobot_SIOC_DO_BODY_POWER = 222,               // 整机功率监控状态
    Cobot_SIOC_DO_BODY_MOMENTUM = 223,            // 整机动量监控状态
    Cobot_SIOC_DO_STATIC = 224,                   // 安全静止监控状态
    Cobot_SIOC_DO_POSITION_NOT_MATCH = 225,       // 位置不匹配监控状态
    Cobot_SIOC_DO_DRAGTEACH_SPEED = 226,          // 拖动示教速度监控状态
    Cobot_SIOC_DO_LASTENUM = 227,
};

enum SAFETY_STOP_MODE
{
    SAFETY_STOP_MODE_INVALID,

    SAFETY_STOP_MODE_0,
    SAFETY_STOP_MODE_1,

    SAFETY_STOP_MODE_MAX
};

#pragma pack(1)

typedef struct stCobotStopConfig
{
    stCobotStopConfig()
    {
        u32TimeOut0 = 0;  /* 0类停机最长延时时间ms */
        u32TimeOut1 = 0;  /* 1类停机最长延时时间ms */
        u32Distance0 = 0; /* 0类停机最长距离 */
        u32Distance1 = 0; /* 1类停机最长距离 */
        u8EStop = 0;       /* DI急停方式 */
        u8SafeStop = 0;    /* DI安全门停机方式 */
    }

    unsigned int u32TimeOut0;                        /* 0类停机最长延时时间ms */
    unsigned int u32TimeOut1;                        /* 1类停机最长延时时间ms */
    unsigned int u32Distance0;                       /* 0类停机最长距离 */
    unsigned int u32Distance1;                       /* 1类停机最长距离 */
    unsigned char u8EStop;                           /* DI急停方式 */
    unsigned char u8SafeStop;                        /* DI安全门停机方式 */
} CobotStopConfig;

typedef struct stCobotIO
{
    stCobotIO()
    {
        u8Attr = 0;
        u8AMcuValue = 0;
        u8BMcuValue = 0;
    }

    quint8 u8Attr;                          /* 功能属性 */
    quint8 u8AMcuValue;                     /* MCUA电平值 */
    quint8 u8BMcuValue;	                   /* MCUB电平值 */
} CobotIO;
/* 安全IO */
typedef struct stCobotSafeIO {
    stCobotSafeIO()
    {
        memset(DI, 0X00, sizeof(DI));
        memset(DO, 0X00, sizeof(DO));
    }

    CobotIO DI[COBOT_DI_NUM];
    CobotIO DO[COBOT_DO_NUM];
} CobotSafeIO;

typedef struct stCobotSafeToolSetting
{
    unsigned short SafeToolMode;       // 0 - FollowSys, 1 - Fixed, 2 - Manual
    unsigned short FixedSafeToolNo;    // Tool 1 - 16
    short DoNo[COBOT_DO_NUM];
} CobotSafeToolSetting;

typedef struct stCobotSafeLowSpeed
{
    stCobotSafeLowSpeed()
    {
        u8Active = 0;   /* 生效 */
        u8StopCat = 0;  /* 停机 */
        f64Speed = 0;   /* 安全低速 */
    }

    quint8 u8Active;                        /* 生效 */
    quint8 u8StopCat;                       /* 停机 */
    double f64Speed;                       /* 安全低速 */
} CobotSafeLowSpeed;

/* 轴位置 */
typedef struct stCobotAPos {
    stCobotAPos()
    {
        u8Active = 0;
        u8StopCat = 0;
        memset(f64APosMax, 0x00, sizeof(f64APosMax));
        memset(f64APosMin, 0x00, sizeof(f64APosMin));
    }

    quint8 u8Active;                          /* 生效 0-不激活；1-激活*/
    quint8 u8StopCat;                         /* 停机 1-0类停机；2-1类停机 */
    double f64APosMax[COBOT_APOS_LIMIT_NUM];       /* 位置正限位 */
    double f64APosMin[COBOT_APOS_LIMIT_NUM];       /* 位置负限位 */
} CobotAPos;

/* 轴速度 */
typedef struct stCobotAVel {
    stCobotAVel()
    {
        u8active = 0;
        u8StopCat = 0;
        memset(f64AVelMax, 0x00, sizeof(f64AVelMax));
    }

    quint8 u8active;                        /* 生效 */
    quint8 u8StopCat;                       /* 停机 */
    double f64AVelMax[COBOT_AVEL_LIMIT_NUM];     /* 最大速度限制 */
} CobotAVel;

/* 轴相关 */
typedef struct stCobotSAxis {
    quint8 u8APosWay;                       /* IO生效，永久生效 0-永久；1-IO；2-不生效*/
    quint8 u8AVelWay;                       /* IO生效，永久生效 */
    CobotAPos APosGroup[COBOT_APOS_GROUP_NUM];      /* 轴位置 */
    CobotAVel AVelGroup[COBOT_AVEL_GROUP_NUM];      /* 轴速度 */
} CobotSAxis;

/* 关节转矩 */
typedef struct stCobotAxisTorque
{
    uint8_t u8JtUnitSwitch;
    uint8_t u8JtUnitStopWay;
    float f32TorqueMax[COBOT_ATORQUE_LIMIT_NUM];
    float f32ReDuceModeTorqueMax[COBOT_ATORQUE_LIMIT_NUM];
} CobotAxisTorque;

typedef struct stCobotJointTorque
{
    uint8_t u8JTActiveWay;
    CobotAxisTorque stJtGroup[COBOT_ATORQUE_GROUP_NUM];
} CobotJointTorque;

/* 位置匹配监控单元 */
typedef struct stCobotPosDismatchUnit
{
    uint8_t u8PmUnitSwitch;                 /* 组激活开关 */
    uint8_t u8PmUnitStopWay;                /* 组停机类型 */
    float f32PmUnitMax[COBOT_POSDISMATCH_LIMIT_NUM];                    /* 组关节位置容差最大阈值 */
    float f32ReduceModePmUnitMax[COBOT_POSDISMATCH_LIMIT_NUM];          /* 缩减模式下组关节位置容差最大阈值 */
} CobotPosDismatchUnit;

/* 位置匹配监控 */
typedef struct stCobotPosDismatch
{
	uint8_t u8PdmActiveWay;
    CobotPosDismatchUnit stPosMatchGrop[COBOT_POSDISMATCH_GROUP_NUM];
} CobotPosDismatch;

/* 关节功率监控 */
typedef struct stCobotAxisPower
{
    uint8_t u8JpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8JpUnitStopWay;                /* 组停机类型 */
    float f32JpUnitMax[COBOT_APOS_LIMIT_NUM];                    /* 组关节功率最大阈值 */
    float f32ReduceModeJpUnitMax[COBOT_APOS_LIMIT_NUM];          /* 缩减模式下组关节功率最大阈值 */
} CobotAxisPower;

typedef struct stCobotJointPower
{
    uint8_t u8JpActiveWay;
    CobotAxisPower stJointPowerGrop[COBOT_APOS_GROUP_NUM];
} CobotJointPower;

/* 安全静止监控 */
typedef struct stCobotStaticMonitorUnit
{
    uint8_t u8BsSwitch;                                     /* 激活开关 */
    uint8_t u8BsStopWay;                                    /* 停机 */
    float f32ToleranceThreshold[COBOT_STATIC_LIMIT_NUM];    /* 轴容差阈值 */
    uint8_t u8AposSwitch[COBOT_STATIC_LIMIT_NUM];           /* 轴启动开关 */
} CobotStaticMonitorUnit;

typedef struct stCobotStaticMonitor
{
    uint8_t u8ActiveWay;            /* 生效方式 */
    CobotStaticMonitorUnit stSafeBodyStaticGroup[COBOT_STATIC_GROUP_NUM];
} CobotStaticMonitor;

/* TCP 力监控 */
typedef struct stCobotTcpForceUnit
{
    uint8_t u8TcpUnitSwitch;                /* 组激活开关 */
    uint8_t u8TcpUnitStopWay;               /* 组停机类型 */
    float f32TcpForceMax;                  /* 组TCP力最大阈值 */
    float f32ReduceModeTcpForceMax;        /* 缩减模式下组TCP力最大阈值 */
} CobotTcpForceUnit;

typedef struct stCobotTcpForce
{
    uint8_t u8TcpActiveWay;
    CobotTcpForceUnit stTcpForceGrop[COBOT_TCP_FORCE_GROUP_NUM];
} CobotTcpForce;

/* 安全原点到位状态 */
typedef struct stCobotSafetyHoming
{
    uint8_t u8SafePointActiveWay;                     /* 生效方式 */
    uint8_t u8SafePointActiveMode;                    /* 生效模式 0-手动 1-自动 2-手动+自动 */
    float f32SafeErrorThreshold[U_COBOT_AXIS_NUM];    /* 轴误差阈值 */
    float f32SafePointValue[U_COBOT_AXIS_NUM];        /* 轴安全原点设置值 */

    stCobotSafetyHoming()
    {
        u8SafePointActiveWay = 0;
        u8SafePointActiveMode = 0;
        memset(f32SafeErrorThreshold, 0, sizeof(f32SafeErrorThreshold));
        memset(f32SafePointValue, 0, sizeof(f32SafePointValue));
    }
} CobotSafetyHoming;

/* 拖动示教 */
typedef struct stCobotDragTeachInterface
{
    uint8_t u8active;                     /* 生效方式 */
    uint8_t u8StopCat;                    /* 生效模式 */
    float tcpVel;                         /* 速度值 */
} CobotDragTeachInterface;

/* 停机时间监控 */
typedef struct stCobotStopTime
{
    uint8_t u8StActiveWay;                                /* 功能生效方式 */
    // float  f32JointSpeedMax[U_COBOT_AXIS_NUM];            /* 最大关节转速 */
    // uint32_t i32SpeedDelayTimes[U_COBOT_AXIS_NUM];        /* 减速执行延迟时间 */
    // uint32_t i32BrakeCloseTimes[U_COBOT_AXIS_NUM];        /* 制动器闭合时间 */
    // float f32SpeedMonitTolerance[U_COBOT_AXIS_NUM];       /* 速度监控容差 */
    uint32_t u32TimeThresholdMax;                         /* 最大时间阈值 */
} CobotStopTime;

/* 停机距离监控 */
typedef struct stCobotStopDistance
{
    uint8_t u8StActiveWay;                                /* 功能生效方式 */
    float  f32DistanceMax;                                /* 最大距离阈值 */
    uint8_t u8TcpStopDistanceSwitch;                      /* TCP停机距离监控开关 */
    // float f32TcpDistanceTol;                              /* TCP距离监控容差 */
    uint8_t u8AposDistanceSwitch;                         /* 轴停机距离监控开关 */
    // float f32AposDistanceTol[U_COBOT_AXIS_NUM];           /* 轴距离监控容差 */
    float f32AposDistanceDeg[U_COBOT_AXIS_NUM];           /* 轴距离阈值deg */
} CobotStopDistance;

typedef struct stCobotTolerance
{
    float f32StopDisTolerance[U_COBOT_AXIS_NUM];   /* 停机容差阈值 停机距离界面中设置 */
} CobotTolerance;

typedef struct stCobotElbowSwitch
{
	uint8_t u8ElbowMonitor[CO_IZONE_INTERFERZONESSTATUSLENGTH];                            /* 肘部监控开关 */
} CobotElbowSwitch;

typedef struct stCobotReduceModeAPos
{
    double f64APosReduceModeMax[U_COBOT_AXIS_NUM];              /* 缩减模式下位置正限位(轴位置) */
    double f64APosReduceModeMin[U_COBOT_AXIS_NUM];              /* 缩减模式下位置负限位(轴位置) */
} CobotReduceModeAPos;

typedef struct stCobotReduceModeAVel
{
    double f64AVelReduceModeMax[U_COBOT_AXIS_NUM];              /* 缩减模式下最大速度限制(轴速度) */
} CobotReduceModeAVel;

typedef struct stCobotReduceModeCVel
{
    double f64CVelReduceModeMax[COBOT_CVEL_GROUP_NUM];   /* 缩减模式下最大速度限制(笛卡尔速度) */
} CobotReduceModeCVel;

typedef struct stCobotReduceMode
{
    CobotReduceModeAPos stReduceModeApos[COBOT_APOS_GROUP_NUM];    /* 缩减模式，轴位置相关 */
    CobotReduceModeAVel stReduceModeAvel[COBOT_AVEL_GROUP_NUM];    /* 缩减模式，轴速度相关 */
    CobotReduceModeCVel stReduceModeCvel;                    /* 缩减模式，笛卡尔速度相关 */
} CobotReduceMode;

/* TCP 方向监控 */
typedef struct stCobotTcpVector
{
    uint8_t u8Switch;
    float f32VectorX;
    float f32VectorY;
    float f32VectorZ;
    float f32Deg;
} CobotTcpVector;

typedef struct stCobotTcpDirectionUnit
{
    uint8_t u8TdSwitch;                      /* 激活开关 */
    uint8_t u8TdStopWay;                     /* 停机 */
    CobotTcpVector stVectorGroupX;           /* 组X向量 */
    CobotTcpVector stVectorGroupZ;           /* 组Z向量 */
} CobotTcpDirectionUnit;

typedef struct stCobotTcpDirection
{
    uint8_t u8ActiveWay;                                       /* 生效方式 */
    CobotTcpDirectionUnit stTcpDeGroup[COBOT_TCP_DIRECT_GROUP_NUM];  /* TCP 监控 */
} CobotTcpDirection;

/* 整机功率监控 */
typedef struct stCobotBodyPowerUnit
{
    uint8_t u8BpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8BpUnitStopWay;                /* 组停机类型 */
    float f32BpUintMax;                     /* 组整机功率最大阈值 */
    float f32ReduceModeBpUintMax;           /* 缩减模式下组整机功率最大阈值 */
} CobotBodyPowerUnit;

typedef struct stCobotBodyPower
{
    uint8_t u8BpActiveWay;
    CobotBodyPowerUnit stBodyPowerGrop[COBOT_BODY_POWER_GROUP_NUM];
} CobotBodyPower;

/* 整机动量监控 */
typedef struct stCobotBodyMomentumUnit
{
    uint8_t u8BpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8BpUnitStopWay;                /* 组停机类型 */
    float f32BpUintMax;                     /* 组整机动量最大阈值 */
    float f32ReduceModeBpUintMax;           /* 缩减模式下组整机动量最大阈值 */
} CobotBodyMomentumUnit;

typedef struct stBodyMomentum
{
    uint8_t u8BmActiveWay;
    CobotBodyMomentumUnit stBodyMomGrop[COBOT_BODY_MOMENTUM_GROUP_NUM];
} CobotBodyMomentum;

// 干涉区
typedef struct stCoInterZone
{
    stCoInterZone()
    {
        Initialize();
    }

    void Initialize()
    {
        u16Index = 0xffff;
        memset(cRemarks, 0, CO_IZONE_DESCRIPTION_CHARLENGTH);
        i32Input = -1;
        i32Output = -1;
        u16Scope = 0xffff;
        u16IsAlert = 0xffff;
        f32SafeL = 0;
        u16WobjNum = 0xffff;
        i16StopType = -1;
        i16ZoneType = -1;
        i16ForeCast = -1;

        u16SetType = 0xffff;
        memset(f32Diagonal, 0, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointL, 0, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
    }

    stCoInterZone &operator=(const stCoInterZone &other)
    {
        u16Index = other.u16Index;
        ::memcpy(cRemarks, other.cRemarks, CO_IZONE_DESCRIPTION_CHARLENGTH);
        i32Input = other.i32Input;
        i32Output = other.i32Output;
        u16Scope = other.u16Scope;
        u16IsAlert = other.u16IsAlert;
        f32SafeL = other.f32SafeL;
        u16WobjNum = other.u16WobjNum;
        i16StopType = other.i16StopType;
        i16ZoneType = other.i16ZoneType;
        i16ForeCast = other.i16ForeCast;

        u16SetType = other.u16SetType;
        ::memcpy(f32Diagonal, other.f32Diagonal, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        ::memcpy(f32PointL, other.f32PointL, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        return (*this);
    }

    bool operator==(const stCoInterZone &other)
    {
        if (this == &other)
            return true;

        if (u16Index != other.u16Index)
            return false;
        if (strcmp(cRemarks, other.cRemarks) != 0)
            return false;
        if (i32Input != other.i32Input)
            return false;
        if (i32Output != other.i32Output)
            return false;
        if (u16Scope != other.u16Scope)
            return false;
        if (u16IsAlert != other.u16IsAlert)
            return false;
        if (fabs(f32SafeL - other.f32SafeL) > CO_IZONE_EPSILON)
            return false;
        if (u16WobjNum != other.u16WobjNum)
            return false;
        if (i16StopType != other.i16StopType)
            return false;
        if (i16ZoneType != other.i16ZoneType)
            return false;
        if (i16ForeCast != other.i16ForeCast)
            return false;
        if (u16SetType != other.u16SetType)
            return false;
        for (size_t i = 0; i < CO_IZONE_FLOATARRAYLENGTH; i++)
        {
            if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > CO_IZONE_EPSILON)
                return false;
        }
        for (size_t i = 0; i < CO_IZONE_FLOATARRAYLENGTH; i++)
        {
            if (fabs(f32PointL[i] - other.f32PointL[i]) > CO_IZONE_EPSILON)
                return false;
        }

        return true;
    }

    bool IsValid()
    {
        if (u16Index < 0 || u16Index > 15)
            return false;

        return true;
    }

    unsigned short u16Index;                     /* 第x组参数 */
    char cRemarks[CO_IZONE_DESCRIPTION_CHARLENGTH]; /* 备注 */
    int i32Input;                                /* 输入信号 */
    int i32Output;                               /* 输出信号 */
    unsigned short u16Scope;                     /* 内外侧 0-内侧，1-外侧 */
    unsigned short u16IsAlert;                   /* 是否报警 0-警告，1-报警 */
    float f32SafeL;                              /* 安全距离 */
    unsigned short u16WobjNum;                   /* 当前工件号 */
    short i16StopType;                           /* 停机方式 */
    short i16ZoneType;                           /* 干涉区类型 */
    short i16ForeCast;                           /* 是否开启目标点预测 */
    /* 干涉区 */
    unsigned short u16SetType;                 /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[CO_IZONE_FLOATARRAYLENGTH]; /* 对角点 */
    float f32PointL[CO_IZONE_FLOATARRAYLENGTH];   /* 基准点+偏移 */
} CoInterZone;

// 末端监测对象MTCP
typedef struct stCoInterMTcpBox
{
    stCoInterMTcpBox()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(u16IsUse, 0, CO_IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        memset(u16ToolNum, 0, CO_IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
    }
    stCoInterMTcpBox &operator=(const stCoInterMTcpBox &other)
    {
        ::memcpy(u16IsUse, other.u16IsUse, CO_IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        ::memcpy(u16ToolNum, other.u16ToolNum, CO_IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        return (*this);
    }
    bool operator==(const stCoInterMTcpBox &other)
    {
        if (this == &other)
            return true;
        for (size_t i = 0; i < CO_IZONE_MTCP_UINTARRAYLENGTH; i++)
        {
            if (u16IsUse[i] != other.u16IsUse[i])
                return false;
        }
        for (size_t i = 0; i < CO_IZONE_MTCP_UINTARRAYLENGTH; i++)
        {
            if (u16ToolNum[i] != other.u16ToolNum[i])
                return false;
        }
        return true;
    }
    unsigned short u16IsUse[CO_IZONE_MTCP_UINTARRAYLENGTH];
    unsigned short u16ToolNum[CO_IZONE_MTCP_UINTARRAYLENGTH];
} CoInterMTcpBox;

// 末端监测对象球体
typedef struct stCoInterBallBox
{
    stCoInterBallBox()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(f32Pos, 0, CO_IZONE_BALL_POSARRAYLENGTH * sizeof(float));
        f32BallR = 0;
    }
    stCoInterBallBox &operator=(const stCoInterBallBox &other)
    {
        ::memcpy(f32Pos, other.f32Pos, CO_IZONE_BALL_POSARRAYLENGTH * sizeof(float));
        f32BallR = other.f32BallR;
        return (*this);
    }
    bool operator==(const stCoInterBallBox &other)
    {
        if (this == &other)
            return true;

        for (size_t i = 0; i < CO_IZONE_BALL_POSARRAYLENGTH; i++)
        {
            if (fabs(f32Pos[i] - other.f32Pos[i]) > CO_IZONE_EPSILON)
                return false;
        }
        if (fabs(f32BallR - other.f32BallR) > CO_IZONE_EPSILON)
            return false;

        return true;
    }

    float f32Pos[CO_IZONE_BALL_POSARRAYLENGTH];
    float f32BallR;
} CoInterBallBox;

// 末端监测对象长方体包围盒
typedef struct stCoInterToolBox
{
    stCoInterToolBox()
    {
        Initialize();
    }
    void Initialize()
    {
        u16SetType = 0;
        memset(f32Diagonal, 0, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointL, 0, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointH, 0, CO_IZONE_TOOLBOX_TYPE3_FLOATARRAY * sizeof(float));
    }
    stCoInterToolBox &operator=(const stCoInterToolBox &other)
    {
        u16SetType = other.u16SetType;
        ::memcpy(f32Diagonal, other.f32Diagonal, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        ::memcpy(f32PointL, other.f32PointL, CO_IZONE_FLOATARRAYLENGTH * sizeof(float));
        ::memcpy(f32PointH, other.f32PointH, CO_IZONE_TOOLBOX_TYPE3_FLOATARRAY * sizeof(float));
        return (*this);
    }
    bool operator==(const stCoInterToolBox &other)
    {
        if (this == &other)
            return true;
        if (u16SetType != other.u16SetType)
            return false;
        if (u16SetType == 0)
        {
            for (size_t i = 0; i < CO_IZONE_FLOATARRAYLENGTH; i++)
            {
                if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > CO_IZONE_EPSILON)
                    return false;
            }
        }
        else if (u16SetType == 1)
        {
            for (size_t i = 0; i < CO_IZONE_FLOATARRAYLENGTH; i++)
            {
                if (fabs(f32PointL[i] - other.f32PointL[i]) > CO_IZONE_EPSILON)
                    return false;
            }
        }
        else
        {
            for (size_t i = 0; i < CO_IZONE_TOOLBOX_TYPE3_FLOATARRAY; i++)
            {
                if (fabs(f32PointH[i] - other.f32PointH[i]) > CO_IZONE_EPSILON)
                    return false;
            }
        }

        return true;
    }

    unsigned short u16SetType;                       /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[CO_IZONE_FLOATARRAYLENGTH];       /* 对角点 */
    float f32PointL[CO_IZONE_FLOATARRAYLENGTH];         /* 基准点+偏移 */
    float f32PointH[CO_IZONE_TOOLBOX_TYPE3_FLOATARRAY]; /* 取点+高度 */
} CoInterToolBox;

/* 监控对象, 内含MTCP, 球体, 长方体包围盒 */
typedef struct stCoInterTool
{
    stCoInterTool()
    {
        Initialize();
    }
    void Initialize()
    {
        u16Index = 0;
        u16Type = 0;
        memset(cRemarks, 0, CO_IZONE_DESCRIPTION_CHARLENGTH);

        stMTcpBox.Initialize();
        stBallBox.Initialize();
        stToolBox.Initialize();
    }
    stCoInterTool &operator=(const stCoInterTool &other)
    {
        u16Index = other.u16Index;
        u16Type = other.u16Type;
        ::memcpy(cRemarks, other.cRemarks, CO_IZONE_DESCRIPTION_CHARLENGTH);

        stMTcpBox = other.stMTcpBox;
        stBallBox = other.stBallBox;
        stToolBox = other.stToolBox;
        return (*this);
    }
    bool operator==(const stCoInterTool &other)
    {
        if (this == &other)
            return true;

        if (u16Index != other.u16Index)
            return false;
        if (u16Type != other.u16Type)
            return false;
        if (strcmp(cRemarks, other.cRemarks) != 0)
            return false;

        if (!(stMTcpBox == other.stMTcpBox))
            return false;
        if (!(stBallBox == other.stBallBox))
            return false;
        if (!(stToolBox == other.stToolBox))
            return false;

        return true;
    }
    unsigned short u16Index;                     /* 第x组参数 */
    unsigned short u16Type;                      /* 监控对象类型 */
    char cRemarks[CO_IZONE_DESCRIPTION_CHARLENGTH]; /* 备注 */
    CoInterMTcpBox stMTcpBox;
    CoInterBallBox stBallBox;
    CoInterToolBox stToolBox;
} CoInterTool;

// 干涉区激活状态
typedef struct stCoInterZoneStatus
{
    stCoInterZoneStatus()
    {
        uint16IZonesIndex = 0;
        memset(cRemarks, 0x00, CO_IZONE_DESCRIPTION_CHARLENGTH);
    }
    unsigned short uint16IZonesIndex;
    char cRemarks[CO_IZONE_DESCRIPTION_CHARLENGTH];
} CoInterZoneStatus;

// 干涉区工件参数相关
typedef struct stCoInterZoneWObjParam
{
    stCoInterZoneWObjParam()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterWobjParams, 0, sizeof(InterWobjParams));
    }
    stCoInterZoneWObjParam &operator=(const stCoInterZoneWObjParam &other)
    {
        ::memcpy(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams));
        return (*this);
    }

    bool operator==(const stCoInterZoneWObjParam &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams)))
            return false;

        return true;
    }
    double InterWobjParams[CO_IZONE_WOBJPARAMSNUM];  //干涉区 - 工件 - 工件坐标系
} CoInterZoneWObjParam;

// 干涉区工具参数相关
typedef struct stCoInterZoneMTcpToolParam
{
    stCoInterZoneMTcpToolParam()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterTFramePos, 0, sizeof(InterTFramePos));
    }

    stCoInterZoneMTcpToolParam &operator=(const stCoInterZoneMTcpToolParam &other)
    {
        ::memcpy(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos));
        return (*this);
    }

    bool operator==(const stCoInterZoneMTcpToolParam &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos)))
            return false;

        return true;
    }
    double InterTFramePos[CO_IZONE_MTCPTOOLPARAMSNUM * CO_IZONE_MTCP_UINTARRAYLENGTH];  // 末端监控对象MTCP - 工具参数
} CoInterZoneMTcpToolParam;

// 干涉区所有功能的集合
typedef struct stCobotSCPos
{
    CoInterZoneStatus IZONES_STATUS[CO_IZONE_INTERFERZONESSTATUSLENGTH];
    CoInterZoneStatus ITOOLS_STATUS[CO_IZONE_INTERFERZONESSTATUSLENGTH];

    CoInterZone IZONES_PARA[CO_IZONE_INTERFERZONESSTATUSLENGTH];
    CoInterZoneWObjParam IZONES_WOBJ[CO_IZONE_INTERFERZONESSTATUSLENGTH];

    CoInterTool ITOOLS_PARA[CO_IZONE_INTERFERZONESSTATUSLENGTH];
    CoInterZoneMTcpToolParam ITOOLS_MTCP_TOOL[CO_IZONE_INTERFERZONESSTATUSLENGTH];

} CobotSCPos;

/* 笛卡尔速度 */
typedef struct stCobotCVel {
    stCobotCVel()
    {
        u8Active = 0;
        u8StopCat = 0;
        f64CVelMax = 0;
    }

    quint8 u8Active;                        /* 生效 */
    quint8 u8StopCat;                       /* 停机 */
    double f64CVelMax;                     /* 最大速度限制 */
} CobotCVel;

typedef struct stCobotCcartesian {
    quint8 u8CVelWay;                                    /* 生效方式 */
    quint8 u8CPosWay;                                    /* 生效方式 */
    CobotCVel CVelGroup[COBOT_IZONE_CVEL_ARRAY_LENGTH];          /* 笛卡尔速度 */
    CobotSCPos CPosGroup;                                   /* 笛卡尔位置 */
} CobotCcartesian;

typedef struct stSpeedReducingConf
{
    stSpeedReducingConf()
    {
        speedLevel1 = 0;
        speedLevel2 = 0;
    }
    stSpeedReducingConf(quint32 l1, quint32 l2)
    {
        speedLevel1 = l1;
        speedLevel2 = l2;
    }
    quint32 speedLevel1;     /// > 缩减等级1对应速度缩减百分比
    quint32 speedLevel2;     /// > 缩减模式2对应速度缩减百分比
} SpeedReducingConf;

#pragma pack()

typedef struct stSafeReadWriteCmdParam
{
    stSafeReadWriteCmdParam()
    {
        int key = -1;
        int offset = -1;
        int num = -1;
        int length = -1;
        unsigned char *buf = nullptr;
        bool forceFlag = false;      
    }
    int key;
    int offset;
    int num;
    int length;
    unsigned char *buf;
    bool forceFlag;  
} SafeReadWriteCmdParam;
