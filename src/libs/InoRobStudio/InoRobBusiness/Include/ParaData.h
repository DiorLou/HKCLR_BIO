#ifndef __PARADATA_H__
#define __PARADATA_H__

/// ParaData.h 中维护着大部分的功能安全数据结构 和 数据地图(地址, 偏移等)。
/// SafeMCU变动需同步变更此文件，详细可咨询下位机。

#include "GlobalDataTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* EERPOM中功能码参数 */
#define DI_NUM                (8)              /* 安全DI数量 */
#define DO_NUM                (5)              /* 安全DO数量 */
#define APOS_LIMIT_NUM        (6)              /* 轴数量 */
#define AVEL_LIMIT_NUM        (6)              /* 轴数量 */
#define APOS_GROUP_NUM        (8)              /* 轴位置组数 */
#define AVEL_GROUP_NUM        (8)              /* 轴速度组数 */

#define DI_NO_ACTIVE          (1)              /* DI 不生效 */
#define DI_ACTIVE             (0)              /* DI 生效 */
typedef      int16u    CRC_TYPE;
typedef      int32u    PASSWORD_TYPE;


/* 1字节对齐 */
#pragma pack(1)

#ifdef COBOT
/* 缩减模式 */
typedef struct SPEEDREDUCINGCONF
{
    SPEEDREDUCINGCONF()
    {
        speedLevel1 = 0;
        speedLevel2 = 0;    
    }
    int32u speedLevel1;     /// > 缩减等级1对应速度缩减百分比
    int32u speedLevel2;     /// > 缩减模式2对应速度缩减百分比
} S_SPEEDREDUCINGCONF;
#endif // COBOT

/* 停机配置 */
typedef struct STOPCONF
{
    STOPCONF()
    {
        u32TimeOut0 = 0;  /* 0类停机最长延时时间ms */
        u32TimeOut1 = 0;  /* 1类停机最长延时时间ms */
        u32Distance0 = 0; /* 0类停机最长距离 */
        u32Distance1 = 0; /* 1类停机最长距离 */
        u8EStop = 0;       /* DI急停方式 */
        u8SafeStop = 0;    /* DI安全门停机方式 */
    }

    int32u u32TimeOut0;                        /* 0类停机最长延时时间ms */
    int32u u32TimeOut1;                        /* 1类停机最长延时时间ms */
    int32u u32Distance0;                       /* 0类停机最长距离 */
    int32u u32Distance1;                       /* 1类停机最长距离 */
    int8u u8EStop;                             /* DI急停方式 */
    int8u u8SafeStop;                          /* DI安全门停机方式 */
}S_STOPCONF;

/* 安全低速 */
typedef struct SAFELOWSPEED
{
    SAFELOWSPEED()
    {
        u8Active = 0;   /* 生效 */
        u8StopCat = 0;  /* 停机 */
        f64Speed = 0;   /* 安全低速 */
    }

    int8u u8Active;                        /* 生效 */
    int8u u8StopCat;                       /* 停机 */
    double f64Speed;                       /* 安全低速 */
}S_SPPEDMODEL;

typedef struct CHECKPARA
{
    CRC_TYPE CrcPara;                        /* 安全参数CRC */
    PASSWORD_TYPE PasswordPara;              /* 密码 */
}S_CHECKPARA;

typedef struct IO
{
    IO()
    {
        u8Attr = 0;
        u8AMcuValue = 0;
        u8BMcuValue = 0;
    }

    int8u u8Attr;                          /* 功能属性 */
    int8u u8AMcuValue;                     /* MCUA电平值 */
    int8u u8BMcuValue;	                   /* MCUB电平值 */
}S_IO;
/* 安全IO */
typedef struct SAFEIO {
    SAFEIO()
    {
        memset(DI, 0X00, sizeof(DI));
        memset(DO, 0X00, sizeof(DO));
    }

    S_IO DI[DI_NUM];
    S_IO DO[DO_NUM];
}S_SAFEIO;

/* 轴位置 */
typedef struct APOS {
    APOS()
    {
        u8Active = 0;
        u8StopCat = 0;
        memset(f64APosMax, 0x00, sizeof(f64APosMax));
        memset(f64APosMin, 0x00, sizeof(f64APosMin));
    }

    int8u u8Active;                          /* 生效 0-不激活；1-激活*/
    int8u u8StopCat;                         /* 停机 1-0类停机；2-1类停机 */
    double f64APosMax[APOS_LIMIT_NUM];       /* 位置正限位 */
    double f64APosMin[APOS_LIMIT_NUM];       /* 位置负限位 */
}S_APOS;

/* 轴速度 */
typedef struct AVEL {
    AVEL()
    {
        u8active = 0;
        u8StopCat = 0;
        memset(f64AVelMax, 0x00, sizeof(f64AVelMax));
    }

    int8u u8active;                        /* 生效 */
    int8u u8StopCat;                       /* 停机 */
    double f64AVelMax[AVEL_LIMIT_NUM];     /* 最大速度限制 */
}S_AVEL;

/* 轴相关 */
typedef struct AXIS {
    int8u u8APosWay;                       /* IO生效，永久生效 0-永久；1-IO；2-不生效*/
    int8u u8AVelWay;                       /* IO生效，永久生效 */
    S_APOS APosGroup[APOS_GROUP_NUM];      /* 轴位置 */
    S_AVEL AVelGroup[AVEL_GROUP_NUM];      /* 轴速度 */
}S_AXIS;

/* 笛卡尔速度 */
typedef struct CVEL {
    CVEL()
    {
        u8Active = 0;
        u8StopCat = 0;
        f64CVelMax = 0;
    }

    int8u u8Active;                        /* 生效 */
    int8u u8StopCat;                       /* 停机 */
    double f64CVelMax;                     /* 最大速度限制 */
}S_CVEL;

#define IZONE_CVEL_ARRAY_LENGTH           (8)      /* 笛卡尔速度组数 */

/* 空间相关 */
typedef struct CARTESIAN {
    int8u u8CVelWay;                                    /* 生效方式 */
    int8u u8CPosWay;                                    /* 生效方式 */
    S_CVEL CVelGroup[IZONE_CVEL_ARRAY_LENGTH];          /* 笛卡尔速度 */
    S_CPOS CPosGroup;                                   /* 笛卡尔位置 */
}S_CARTESIAN;

/* RAM中的参数信息 */
//#define             AXIS_NUM              (8)
#define             MAXPARANUM            (16)
#define             MECH_PARA_NUM         (8)
/* 关节参数 */
typedef struct
{
    double ratio[AXIS_NUM];           /* 减速比 */
    double absZero[AXIS_NUM];         /* 绝对零点 */
    int encBits[AXIS_NUM];            /* 编码器分辨率 */
}ST_JOINT_PARAM;



/* 耦合参数 （分成了1+8组）*/
typedef struct
{
    double f64CoupParam[AXIS_NUM][AXIS_NUM];     /* 耦合参数 */
}ST_COUP_PARAM;

/* 运动学参数 */
typedef struct
{
    double a1;           // a1,mm
    double a2;           // a2,mm
    double a3;           // a3,mm
    double d3;           // d3,mm
    double d4;           // d4,mm
    double df;           // df,mm
    double ex1;
    double ex2;
}ST_TRobotMechPara;

typedef struct
{
    double RobotRotPara[MAXPARANUM];                    /* 机器人旋转角度结构参数 */
    double RobotRotParaComp[MAXPARANUM];                /* 机器人旋转角度结构参数补偿 */
}ST_KINEMATIC_PARAM;

/* 杆件动力学参数 */
typedef struct
{
    double mass;            /* 连杆质量 */
    double cog[3];          /* 质心 */
    double inertia[6];      /* 重力模型 */
    double motorInertia;    /* 电机惯性 */
    double ratedTrq;        /* 额定扭矩 */
    double stiffness;       /* 关节刚度 */
    double coulombFric;     /* 关节库伦摩擦 */
    double viscousFric;     /* 关节粘性摩擦 */
}ST_ROBOT_LINK_PARAM;

/* 动力学参数 */
typedef struct
{
    ST_ROBOT_LINK_PARAM stRobotLinkParam[AXIS_NUM];
}ST_DYNAMIC_PARAM;

/* 六关节机器人全参结构体用于高精度标定 */
typedef struct
{
    double alpha1;
    double alpha2;
    double alpha3;
    double alpha4;
    double alpha5;
    double beta2;
    double d3;
    double d5;
    double a4;
    double a5;
    double gravAlpha;
    double gravBeta;
    double gravGamma;
}ST_ROBOT_MECH_FULL_PARAM;

/* 机型类型数组大小 */
#define ROBOT_TYPR_SIZE (128)

typedef struct _ToolWobjMgr_
{
    ToolData ToolDataGroup[TOOL_TOTAL_NUM];
    WobjData WobjDataGroup[TOOL_TOTAL_NUM];
}ToolWobjMgr;

typedef struct SafeToolSetting
{
    unsigned short SafeToolMode;       // 0 - FollowSys, 1 - Fixed, 2 - Manual
    unsigned short FixedSafeToolNo;    // Tool 1 - 16
    short DoNo[DO_NUM];
}SafeToolSetting;

    /* 编码器方向 */
    typedef struct ENCODEDIR
    {
        int  i32EncoderDir[POSE_AXIS_NUM];
    }S_ENCODEDIR;
/* 版本号 */
typedef struct SAFEMCUVERSION
{
    int8u u8SystemMasterVersion;
    int8u u8SystemSubVersion;
    int8u u8SystemFixVersion;
    int8u u8MonitorMasterVersion;
    int8u u8MonitorSubVersion;
    int8u u8MonitorFixVersion;
    int16u u16SoftwareVersion;
    int16u u16HardwareVersion;
}S_SAFEMCUVERSION;

/* 安全参数 */
typedef struct SAVE_TO_EEPROM
{
    SafeToolSetting stSafeToolSetting;
} ST_SAVE_TO_EEPROM;

typedef union INDUSTRY_SAVE_EEPROM
{
    int8u u8Reserver[200];
    ST_SAVE_TO_EEPROM stSaveToEE;
} ST_INDUSTRY_SAVE_EEPROM;

typedef struct SAFESYSTEMPARA
{
    /* 保存在EEPROM中的参数 */
    S_STOPCONF stStopConf;                /* 停机配置 */
    S_SPPEDMODEL stSpeedModel;            /* 安全低速 */
    S_SAFEIO stSafeIoPara;                /* 安全IO参数 */
    S_AXIS stAxisPara;                    /* 轴参数 */
    S_CARTESIAN stCartSianPara;           /* 笛卡尔空间参数 */
    int32u u32DITrigerValue;              /* DI触发阈值 */
    int8u u8RobotType[ROBOT_TYPR_SIZE];   /* 机型类型 */

    /* 算法保存在内存中的参数 */
    int8u u8SysStatus;                  /* 系统状态 */
    ST_JOINT_PARAM stJointPara;
    ST_COUP_PARAM stCoupPara;
    ST_KINEMATIC_PARAM stKinematicPara;
    ST_DYNAMIC_PARAM stDynamicPara;
    ST_ROBOT_MECH_FULL_PARAM stRobotMechFullPara;
    ST_TRobotMechPara stTrobotMechPara;
    ST_TRobotMechPara stTrobotMechCompPara;

    /* 工件工具参数 */
    SafeToolSetting stSafeToolSetting;
    ToolWobjMgr stToolWobjMgr;

    /* 轴数 */
    int i32AutulAxisNUM;

    /* 上个周期的参数 */
    S_SAFEIO stSafeIoOldPara;                /* 上一周期的安全IO参数 */

}S_SAFESYSTEMPARA;
#pragma pack()

#define         SAFE_CRC_SIZE                  (sizeof(CRC_TYPE))                          /* CRC参数大小 */
#define         PASSWORD_SIZE                  (sizeof(PASSWORD_TYPE))                     /* 密码占用空间大小 */
#define         STOP_CONF_SIZE                 (sizeof(S_STOPCONF))                        /* 停机方式size */
#define         SPEED_MODEL_SIZE               (sizeof(S_SPPEDMODEL))                      /* 安全低速模式size */
#define         DI_SIZE                        (sizeof(S_IO)*DI_NUM)                       /* DI数据结构大小 */
#define         DO_SIZE                        (sizeof(S_IO)*DO_NUM)                       /* DO数据结构大小 */
#define         APOS_WAY_SIZE                  (sizeof(int8u))                             /* 轴位置激活方式 */
#define         AVEL_WAY_SIZE                  (sizeof(int8u))                             /* 轴速度激活方式 */
#define         APOS_SIZE                      (sizeof(S_APOS))                            /* 轴位置数据结构大小 */
#define         AVEL_SIZE                      (sizeof(S_AVEL))                            /* 轴速度数据结构大小 */
#define         CPOS_WAY_SIZE                  (sizeof(int8u))                             /* 轴位置激活方式 */
#define         CVEL_WAY_SIZE                  (sizeof(int8u))                             /* 轴速度激活方式 */
#define         CVEL_SIZE                      (sizeof(S_CVEL))                            /* 笛卡尔速度数据结构大小 */
#define         INTERFER_ZONE_STATUS_SIZE      (sizeof(INTERFER_ZONE_STATUS))              /* 干涉区激活状态 */
#define         INTERFER_ZONE_SIZE             (sizeof(INTERFER_ZONE))                     /* 干涉区size */
#define         INTERFER_ZONE_WOBJPARAM_SIZE   (sizeof(INTERFER_ZONE_WOBJPARAM))
#define         INTERFER_TOOL_SIZE             (sizeof(INTERFER_TOOL))                     /* 末端监控size */
#define         INTERFER_ZONE_MTCPTOOLPARAM_SIZE  (sizeof(INTERFER_ZONE_MTCPTOOLPARAM))
#define         DI_TRIGER_SIZE                 (sizeof(int32u))                            /* DI 阈值触发 */
#define         ROBOT_TYPE_SIZE                (sizeof(int8u)*ROBOT_TYPR_SIZE)             /* 机型类型 */

#ifdef COBOT

#define         JOINT_TORQUE_SIZE                     (sizeof(S_A_JOINT_TORQUE_UNIT))             /* 关节转矩数据结构大小 */
#define         JOINT_TORQUE_WAY_SIZE                 (sizeof(int8u))                             /* 关节转矩激活方式 */
#define         JOINT_POWER_SIZE                      (sizeof(S_A_JOINT_POWER_UNIT))              /* 关节功率数据结构大小 */
#define         JOINT_POWER_WAY_SIZE                  (sizeof(int8u))                             /* 关节功率激活方式 */
#define         JOINT_STATIC_SIZE                     (sizeof(S_A_SAFE_BODY_STATIC_UNIT))         /* 安全静止监控数据结构大小 */
#define         JOINT_STATIC_WAY_SIZE                 (sizeof(int8u))                             /* 安全静止监控激活方式 */
#define         TCP_FORCE_SIZE                        (sizeof(S_A_TCP_FORCE))                     /* TCP力数据结构大小 */
#define         HOMING_MONITOR_SIZE                   (sizeof(S_A_SAFE_BASE_POINT_STATUS))        /* 安全原点数据结构大小 */

#define         BODY_MOMENTUM_SIZE                    (sizeof(S_A_BODY_MOMENTUM))                 /* 整机动量数据结构大小 */
#define         BODY_POWER_SIZE                       (sizeof(S_A_BODY_POWER))                    /* 整机功率数据结构大小 */
#define         STOP_DISTANCE_SIZE                    (sizeof(S_A_STOP_DISTANCE))                 /* 停机距离数据结构大小 */
#define         STOP_TIME_SIZE                        (sizeof(S_A_STOP_TIME))                     /* 停机时间数据结构大小 */
#define         TCP_DIRECTION_SIZE                    (sizeof(S_A_TCP_DIRECTION_UNIT))            /* TCP方向数据结构大小 */
#define         TCP_DIRECTION_WAY_SIZE                (sizeof(int8u))                             /* TCP方向激活方式 */

#define         STOP_TOLERANCE_SIZE                   (sizeof(S_A_STOP_TOLERANCE))                /* 停机容差大小 */
#define         REDUCEMODE_APOS_SIZE                  (sizeof(S_A_REDUCE_MODE_APOS))              /* 缩减模式轴位置结构大小 */
#define         REDUCEMODE_AVEL_SIZE                  (sizeof(S_A_REDUCE_MODE_AVEL))              /* 缩减模式轴速度结构大小 */
#define         REDUCEMODE_CVEL_SIZE                  (sizeof(S_A_REDUCE_MODE_CVEL))              /* 缩减模式笛卡尔速度结构大小 */
#define         ELBOW_SWITCH_SIZE                     (sizeof(INTERFER_TOOL_EXTRAL))              /* 肘部检测开关 */
#define         DRAGTEACH_SIZE                        (sizeof(S_A_DRAG_TEACH_INTERFACE))          /* 拖动示教 */

#define         POSITIONDISMATCH_WAY_SIZE             (sizeof(int8u))                             /* 位置不匹配激活方式 */
#define         POSITIONDISMATCH_SIZE                 (sizeof(S_A_POS_MATCH_UNIT))                /* 位置不匹配数据结构大小 */

#endif // COBOT

/* RAM中的参数 */
#define         ST_JOINT_PARAM_SIZE            (sizeof(ST_JOINT_PARAM))
#define         AUTUL_AXIS_NUM_SIZE            (sizeof(int))
#define         ST_COUP_PARAM_ARRAY_SIZE       (sizeof(double)*AXIS_NUM)

/* ST_KINEMATIC_PARAM */
#define         ROBOT_PARAM_SIZE               (sizeof(ST_TRobotMechPara))
#define         ROBOT_PARAM_COMP_SIZE          (sizeof(ST_TRobotMechPara))
#define         ROBOT_ROT_PARAM_SIZE           (sizeof(double)*MAXPARANUM)
#define         ROBOT_ROT_PARAM_COMP_SIZE      (sizeof(double)*MAXPARANUM)

#define         ST_ROBOT_LINK_PARAM_SIZE       (sizeof(ST_ROBOT_LINK_PARAM))
#define         ST_ROBOT_MECH_FULL_PARAM_SIZE  (sizeof(ST_ROBOT_MECH_FULL_PARAM))
/* 工件工具参数 */
#define         ST_SAFE_TOOL_SETTING_PARAM_SIZE  (sizeof(SafeToolSetting))
#define         ST_TOOL_DATA_PARAM_SIZE          (sizeof(ToolData))                       /* 工具参数大小 */
#define         ST_WOBJ_DATA_PARAM_SIZE          (sizeof(WobjData))                       /* 工具参数大小 */


    /* 参数地图，功能码映射 */
#define         EEPROM_START_ADDR               0x0000                                    /* EEPROM起始地址 */
/* CRC */
#define         EEPROM_CRC_ADDR                 EEPROM_START_ADDR
/* 保存在EEPROM中的 Check yes */
#define         EEPROM_CHECKYES_ADDR            (EEPROM_CRC_ADDR + SAFE_CRC_SIZE)
/* 保存在RAM中的 Check yes */
#define         RAM_CHECKYES_ADDR               (EEPROM_CHECKYES_ADDR + sizeof(int8u))
/* 密码 */
#define         EEPROM_PASSWORD_ADDR            (RAM_CHECKYES_ADDR + sizeof(int8u))

/* 参数保存 */
#define         EEPROM_PARA_ADDR_BASE           (EEPROM_PASSWORD_ADDR + PASSWORD_SIZE)
/* 停机方式 */
#define         EEPROM_STOP_CONF_PARA_ADDR      EEPROM_PARA_ADDR_BASE
/* 安全低速模式T1参数 */
#define         EEPROM_SPEED_MODEL_PARA_ADDR    (EEPROM_STOP_CONF_PARA_ADDR + STOP_CONF_SIZE)
/* 安全DI */
#define         EEPROM_DI_PARA_ADDR             (EEPROM_SPEED_MODEL_PARA_ADDR + SPEED_MODEL_SIZE)
/* 安全DO */
#define         EEPROM_DO_PARA_ADDR             (EEPROM_DI_PARA_ADDR + DI_SIZE)


/* 轴参数 */
#define         EEPROM_AXI_PARA_ADDR            (EEPROM_DO_PARA_ADDR + DO_SIZE)
/* 轴位置激活方式 */
#define         EEPROM_APOS_WAY_PARA_ADDR        EEPROM_AXI_PARA_ADDR
/* 轴速度激活方式 */
#define         EEPROM_AVEL_WAY_PARA_ADDR       (EEPROM_APOS_WAY_PARA_ADDR + APOS_WAY_SIZE)

/* 轴位置参数 */
#define         EEPROM_APOS_PARA_ADDR           (EEPROM_AVEL_WAY_PARA_ADDR + AVEL_WAY_SIZE)
/* 第1组轴位置参数 */
#define         EEPROM_APOS1_PARA_ADDR          EEPROM_APOS_PARA_ADDR
/* 第2组轴位置参数 */
#define         EEPROM_APOS2_PARA_ADDR          (EEPROM_APOS1_PARA_ADDR + APOS_SIZE)
/* 第3组轴位置参数 */
#define         EEPROM_APOS3_PARA_ADDR          (EEPROM_APOS2_PARA_ADDR + APOS_SIZE)
/* 第4组轴位置参数 */
#define         EEPROM_APOS4_PARA_ADDR          (EEPROM_APOS3_PARA_ADDR + APOS_SIZE)
/* 第5组轴位置参数 */
#define         EEPROM_APOS5_PARA_ADDR          (EEPROM_APOS4_PARA_ADDR + APOS_SIZE)
/* 第6组轴位置参数 */
#define         EEPROM_APOS6_PARA_ADDR          (EEPROM_APOS5_PARA_ADDR + APOS_SIZE)
/* 第7组轴位置参数 */
#define         EEPROM_APOS7_PARA_ADDR          (EEPROM_APOS6_PARA_ADDR + APOS_SIZE)
/* 第8组轴位置参数 */
#define         EEPROM_APOS8_PARA_ADDR          (EEPROM_APOS7_PARA_ADDR + APOS_SIZE)

/* 轴速度参数 */
#define         EEPROM_AVEL_PARA_ADDR           (EEPROM_APOS8_PARA_ADDR + APOS_SIZE)
/* 第1组轴速度参数 */
#define         EEPROM_AVEL1_PARA_ADDR           EEPROM_AVEL_PARA_ADDR
/* 第2组轴速度参数 */
#define         EEPROM_AVEL2_PARA_ADDR          (EEPROM_AVEL1_PARA_ADDR + AVEL_SIZE)
/* 第3组轴速度参数 */
#define         EEPROM_AVEL3_PARA_ADDR          (EEPROM_AVEL2_PARA_ADDR + AVEL_SIZE)
/* 第4组轴速度参数 */
#define         EEPROM_AVEL4_PARA_ADDR          (EEPROM_AVEL3_PARA_ADDR + AVEL_SIZE)
/* 第5组轴速度参数 */
#define         EEPROM_AVEL5_PARA_ADDR          (EEPROM_AVEL4_PARA_ADDR + AVEL_SIZE)
/* 第6组轴速度参数 */
#define         EEPROM_AVEL6_PARA_ADDR          (EEPROM_AVEL5_PARA_ADDR + AVEL_SIZE)
/* 第7组轴速度参数 */
#define         EEPROM_AVEL7_PARA_ADDR          (EEPROM_AVEL6_PARA_ADDR + AVEL_SIZE)
/* 第8组轴速度参数 */
#define         EEPROM_AVEL8_PARA_ADDR          (EEPROM_AVEL7_PARA_ADDR + AVEL_SIZE)


/* 笛卡尔参数 */
#define         EEPROM_CARTESIAN_PARA_ADDR      (EEPROM_AVEL8_PARA_ADDR + AVEL_SIZE)
/* 笛卡尔速度激活方式 */
#define         EEPROM_CVEL_WAY_PARA_ADDR       EEPROM_CARTESIAN_PARA_ADDR
/* 笛卡尔位置激活方式 */
#define         EEPROM_CPOS_WAY_PARA_ADDR       (EEPROM_CVEL_WAY_PARA_ADDR + CVEL_WAY_SIZE)

/* 笛卡尔速度参数 */
#define         EEPROM_CVEL_PARA_ADDR           (EEPROM_CPOS_WAY_PARA_ADDR + CPOS_WAY_SIZE)
/* 第1组笛卡尔速度参数 */
#define         EEPROM_CVEL1_PARA_ADDR           EEPROM_CVEL_PARA_ADDR
/* 第2组笛卡尔速度参数 */
#define         EEPROM_CVEL2_PARA_ADDR          (EEPROM_CVEL1_PARA_ADDR + CVEL_SIZE)
/* 第3组笛卡尔速度参数 */
#define         EEPROM_CVEL3_PARA_ADDR          (EEPROM_CVEL2_PARA_ADDR + CVEL_SIZE)
/* 第4组笛卡尔速度参数 */
#define         EEPROM_CVEL4_PARA_ADDR          (EEPROM_CVEL3_PARA_ADDR + CVEL_SIZE)
/* 第5组笛卡尔速度参数 */
#define         EEPROM_CVEL5_PARA_ADDR          (EEPROM_CVEL4_PARA_ADDR + CVEL_SIZE)
/* 第6组笛卡尔速度参数 */
#define         EEPROM_CVEL6_PARA_ADDR          (EEPROM_CVEL5_PARA_ADDR + CVEL_SIZE)
/* 第7组笛卡尔速度参数 */
#define         EEPROM_CVEL7_PARA_ADDR          (EEPROM_CVEL6_PARA_ADDR + CVEL_SIZE)
/* 第8组笛卡尔速度参数 */
#define         EEPROM_CVEL8_PARA_ADDR          (EEPROM_CVEL7_PARA_ADDR + CVEL_SIZE)


/* 笛卡尔位置相关参数 */
#define         EEPROM_CPOS_PARA_ADDR           (EEPROM_CVEL8_PARA_ADDR + CVEL_SIZE)
/* 干涉区状态状态 */
#define         EEPROM_IZONES_STATUS_PARA_ADDR           EEPROM_CPOS_PARA_ADDR
/* 第1组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS1_PARA_ADDR          EEPROM_IZONES_STATUS_PARA_ADDR
/* 第2组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS2_PARA_ADDR          (EEPROM_IZONES_STATUS1_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第3组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS3_PARA_ADDR          (EEPROM_IZONES_STATUS2_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第4组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS4_PARA_ADDR          (EEPROM_IZONES_STATUS3_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第5组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS5_PARA_ADDR          (EEPROM_IZONES_STATUS4_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第6组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS6_PARA_ADDR          (EEPROM_IZONES_STATUS5_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第7组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS7_PARA_ADDR          (EEPROM_IZONES_STATUS6_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第8组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS8_PARA_ADDR          (EEPROM_IZONES_STATUS7_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第9组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS9_PARA_ADDR          (EEPROM_IZONES_STATUS8_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第10组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS10_PARA_ADDR         (EEPROM_IZONES_STATUS9_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第11组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS11_PARA_ADDR         (EEPROM_IZONES_STATUS10_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第12组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS12_PARA_ADDR         (EEPROM_IZONES_STATUS11_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第13组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS13_PARA_ADDR         (EEPROM_IZONES_STATUS12_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第14组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS14_PARA_ADDR         (EEPROM_IZONES_STATUS13_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第15组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS15_PARA_ADDR         (EEPROM_IZONES_STATUS14_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第16组干涉区状态参数 */
#define         EEPROM_IZONES_STATUS16_PARA_ADDR         (EEPROM_IZONES_STATUS15_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)

/* 末端监测对象状态 */
#define         EEPROM_ITOOLS_STATUS_PARA_ADDR           (EEPROM_IZONES_STATUS16_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第1组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS1_PARA_ADDR          EEPROM_ITOOLS_STATUS_PARA_ADDR
/* 第2组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS2_PARA_ADDR          (EEPROM_ITOOLS_STATUS1_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第3组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS3_PARA_ADDR          (EEPROM_ITOOLS_STATUS2_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第4组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS4_PARA_ADDR          (EEPROM_ITOOLS_STATUS3_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第5组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS5_PARA_ADDR          (EEPROM_ITOOLS_STATUS4_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第6组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS6_PARA_ADDR          (EEPROM_ITOOLS_STATUS5_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第7组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS7_PARA_ADDR          (EEPROM_ITOOLS_STATUS6_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第8组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS8_PARA_ADDR          (EEPROM_ITOOLS_STATUS7_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第9组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS9_PARA_ADDR          (EEPROM_ITOOLS_STATUS8_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第10组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS10_PARA_ADDR         (EEPROM_ITOOLS_STATUS9_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第11组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS11_PARA_ADDR         (EEPROM_ITOOLS_STATUS10_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第12组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS12_PARA_ADDR         (EEPROM_ITOOLS_STATUS11_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第13组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS13_PARA_ADDR         (EEPROM_ITOOLS_STATUS12_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第14组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS14_PARA_ADDR         (EEPROM_ITOOLS_STATUS13_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第15组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS15_PARA_ADDR         (EEPROM_ITOOLS_STATUS14_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第16组末端监测对象状态参数 */
#define         EEPROM_ITOOLS_STATUS16_PARA_ADDR         (EEPROM_ITOOLS_STATUS15_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)

/* 干涉区配置参数 */
#define         EEPROM_IZONES_PARA_ADDR                  (EEPROM_ITOOLS_STATUS16_PARA_ADDR + INTERFER_ZONE_STATUS_SIZE)
/* 第1组干涉区状态参数 */
#define         EEPROM_IZONES1_PARA_ADDR          EEPROM_IZONES_PARA_ADDR
/* 第2组干涉区状态参数 */
#define         EEPROM_IZONES2_PARA_ADDR          (EEPROM_IZONES1_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第3组干涉区状态参数 */
#define         EEPROM_IZONES3_PARA_ADDR          (EEPROM_IZONES2_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第4组干涉区状态参数 */
#define         EEPROM_IZONES4_PARA_ADDR          (EEPROM_IZONES3_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第5组干涉区状态参数 */
#define         EEPROM_IZONES5_PARA_ADDR          (EEPROM_IZONES4_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第6组干涉区状态参数 */
#define         EEPROM_IZONES6_PARA_ADDR          (EEPROM_IZONES5_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第7组干涉区状态参数 */
#define         EEPROM_IZONES7_PARA_ADDR          (EEPROM_IZONES6_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第8组干涉区状态参数 */
#define         EEPROM_IZONES8_PARA_ADDR          (EEPROM_IZONES7_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第9组干涉区状态参数 */
#define         EEPROM_IZONES9_PARA_ADDR          (EEPROM_IZONES8_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第10组干涉区状态参数 */
#define         EEPROM_IZONES10_PARA_ADDR         (EEPROM_IZONES9_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第11组干涉区状态参数 */
#define         EEPROM_IZONES11_PARA_ADDR         (EEPROM_IZONES10_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第12组干涉区状态参数 */
#define         EEPROM_IZONES12_PARA_ADDR         (EEPROM_IZONES11_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第13组干涉区状态参数 */
#define         EEPROM_IZONES13_PARA_ADDR         (EEPROM_IZONES12_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第14组干涉区状态参数 */
#define         EEPROM_IZONES14_PARA_ADDR         (EEPROM_IZONES13_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第15组干涉区状态参数 */
#define         EEPROM_IZONES15_PARA_ADDR         (EEPROM_IZONES14_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第16组干涉区状态参数 */
#define         EEPROM_IZONES16_PARA_ADDR         (EEPROM_IZONES15_PARA_ADDR + INTERFER_ZONE_SIZE)


/* 干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ_PARA_ADDR           (EEPROM_IZONES16_PARA_ADDR + INTERFER_ZONE_SIZE)
/* 第1组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ1_PARA_ADDR          EEPROM_IZONES_WOBJ_PARA_ADDR
/* 第2组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ2_PARA_ADDR          (EEPROM_IZONES_WOBJ1_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第3组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ3_PARA_ADDR          (EEPROM_IZONES_WOBJ2_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第4组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ4_PARA_ADDR          (EEPROM_IZONES_WOBJ3_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第5组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ5_PARA_ADDR          (EEPROM_IZONES_WOBJ4_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第6组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ6_PARA_ADDR          (EEPROM_IZONES_WOBJ5_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第7组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ7_PARA_ADDR          (EEPROM_IZONES_WOBJ6_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第8组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ8_PARA_ADDR          (EEPROM_IZONES_WOBJ7_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第9组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ9_PARA_ADDR          (EEPROM_IZONES_WOBJ8_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第10组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ10_PARA_ADDR         (EEPROM_IZONES_WOBJ9_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第11组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ11_PARA_ADDR         (EEPROM_IZONES_WOBJ10_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第12组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ12_PARA_ADDR         (EEPROM_IZONES_WOBJ11_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第13组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ13_PARA_ADDR         (EEPROM_IZONES_WOBJ12_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第14组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ14_PARA_ADDR         (EEPROM_IZONES_WOBJ13_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第15组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ15_PARA_ADDR         (EEPROM_IZONES_WOBJ14_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第16组干涉区工件参数 */
#define         EEPROM_IZONES_WOBJ16_PARA_ADDR         (EEPROM_IZONES_WOBJ15_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)

/* 末端监测对象配置参数 */
#define         EEPROM_ITOOLS_PARA_ADDR           (EEPROM_IZONES_WOBJ16_PARA_ADDR + INTERFER_ZONE_WOBJPARAM_SIZE)
/* 第1组末端监测对象配置参数 */
#define         EEPROM_ITOOLS1_PARA_ADDR          EEPROM_ITOOLS_PARA_ADDR
/* 第2组末端监测对象配置参数 */
#define         EEPROM_ITOOLS2_PARA_ADDR          (EEPROM_ITOOLS1_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第3组末端监测对象配置参数 */
#define         EEPROM_ITOOLS3_PARA_ADDR          (EEPROM_ITOOLS2_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第4组末端监测对象配置参数 */
#define         EEPROM_ITOOLS4_PARA_ADDR          (EEPROM_ITOOLS3_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第5组末端监测对象配置参数 */
#define         EEPROM_ITOOLS5_PARA_ADDR          (EEPROM_ITOOLS4_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第6组末端监测对象配置参数 */
#define         EEPROM_ITOOLS6_PARA_ADDR          (EEPROM_ITOOLS5_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第7组末端监测对象配置参数 */
#define         EEPROM_ITOOLS7_PARA_ADDR          (EEPROM_ITOOLS6_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第8组末端监测对象配置参数 */
#define         EEPROM_ITOOLS8_PARA_ADDR          (EEPROM_ITOOLS7_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第9组末端监测对象配置参数 */
#define         EEPROM_ITOOLS9_PARA_ADDR          (EEPROM_ITOOLS8_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第10组末端监测对象配置参数 */
#define         EEPROM_ITOOLS10_PARA_ADDR         (EEPROM_ITOOLS9_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第11组末端监测对象配置参数 */
#define         EEPROM_ITOOLS11_PARA_ADDR         (EEPROM_ITOOLS10_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第12组末端监测对象配置参数 */
#define         EEPROM_ITOOLS12_PARA_ADDR         (EEPROM_ITOOLS11_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第13组末端监测对象配置参数 */
#define         EEPROM_ITOOLS13_PARA_ADDR         (EEPROM_ITOOLS12_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第14组末端监测对象配置参数 */
#define         EEPROM_ITOOLS14_PARA_ADDR         (EEPROM_ITOOLS13_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第15组末端监测对象配置参数 */
#define         EEPROM_ITOOLS15_PARA_ADDR         (EEPROM_ITOOLS14_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第16组末端监测对象配置参数 */
#define         EEPROM_ITOOLS16_PARA_ADDR         (EEPROM_ITOOLS15_PARA_ADDR + INTERFER_TOOL_SIZE)


/* 干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL_PARA_ADDR           (EEPROM_ITOOLS16_PARA_ADDR + INTERFER_TOOL_SIZE)
/* 第1组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL1_PARA_ADDR          EEPROM_ITOOLS_MTCP_TOOL_PARA_ADDR
/* 第2组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL2_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL1_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第3组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL3_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL2_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第4组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL4_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL3_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第5组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL5_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL4_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第6组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL6_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL5_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第7组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL7_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL6_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第8组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL8_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL7_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第9组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL9_PARA_ADDR          (EEPROM_ITOOLS_MTCP_TOOL8_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第10组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL10_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL9_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第11组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL11_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL10_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第12组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL12_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL11_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第13组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL13_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL12_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第14组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL14_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL13_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第15组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL15_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL14_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 第16组干涉区工具参数 */
#define         EEPROM_ITOOLS_MTCP_TOOL16_PARA_ADDR         (EEPROM_ITOOLS_MTCP_TOOL15_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* DI 触发阈值 */
#define         EEPROM_DI_TRIGER_ADDR                       (EEPROM_ITOOLS_MTCP_TOOL16_PARA_ADDR + INTERFER_ZONE_MTCPTOOLPARAM_SIZE)
/* 机型类型 */
#define         EEPROM_ROBOT_TYPE_ADDR                      (EEPROM_DI_TRIGER_ADDR + DI_TRIGER_SIZE)

/* 安全工具模式 */
#define         EEPROM_ST_SAFE_TOOL_SETTING_PARAM_ADDR      (EEPROM_ROBOT_TYPE_ADDR + ROBOT_TYPE_SIZE)

/* 协作新增 */
#ifdef COBOT
#define         INDUSTERY_EEPROM_END_ADDR                   (EEPROM_ST_SAFE_TOOL_SETTING_PARAM_ADDR + sizeof(ST_INDUSTRY_SAVE_EEPROM))

/* 力监控起始地址 */
#define         U_EEPROM_TCP_FORCE_PARAM_ADDR                   (INDUSTERY_EEPROM_END_ADDR)

/* 整机功率起始地址 */
#define         U_EEPROM_BODY_POWER_PARAM_ADDR                 (U_EEPROM_TCP_FORCE_PARAM_ADDR + sizeof(S_A_TCP_FORCE))

/* 整机动量起始地址 */
#define         U_EEPROM_BODY_MOMENTUM_PARAM_ADDR              (U_EEPROM_BODY_POWER_PARAM_ADDR + sizeof(S_A_BODY_POWER))

/* 安全原点到位状态 */
#define         U_EEPROM_SAFE_BASE_POINT_STATUS_PARAM_ADDR     (U_EEPROM_BODY_MOMENTUM_PARAM_ADDR + sizeof(S_A_BODY_MOMENTUM))

/* 安全静止监控 */
/* 安全静止起始地址 */
#define         U_EEPROM_SAFE_BODY_STATIC_ADDR                 (U_EEPROM_SAFE_BASE_POINT_STATUS_PARAM_ADDR + sizeof(S_A_SAFE_BASE_POINT_STATUS))
/* 安全静止激活方式地址 */
#define         U_EEPROM_SAFE_BODY_STATIC_ACTIVE_WAY_PARA_ADDR       (U_EEPROM_SAFE_BODY_STATIC_ADDR)
/* 安全静止第1组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC1_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC_ACTIVE_WAY_PARA_ADDR + sizeof(uint8_t))
/* 安全静止第2组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC2_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC1_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第3组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC3_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC2_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第4组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC4_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC3_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第5组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC5_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC4_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第6组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC6_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC5_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第7组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC7_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC6_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止第8组地址 */
#define         U_EEPROM_SAFE_BODY_STATIC8_PARA_ADDR                (U_EEPROM_SAFE_BODY_STATIC7_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))

/* TCP 方向监控 */
/* 安全静止起始地址 */
#define         U_EEPROM_TCP_DIRECTION_ADDR                      (U_EEPROM_SAFE_BODY_STATIC8_PARA_ADDR + sizeof(S_A_SAFE_BODY_STATIC_UNIT))
/* 安全静止激活方式地址 */
#define         U_EEPROM_TCP_DIRECTION_ACTIVE_WAY_PARA_ADDR      (U_EEPROM_TCP_DIRECTION_ADDR)
/* 安全静止第1组地址 */
#define         U_EEPROM_TCP_DIRECTION1_PARA_ADDR                (U_EEPROM_TCP_DIRECTION_ACTIVE_WAY_PARA_ADDR + sizeof(uint8_t))
/* 安全静止第2组地址 */
#define         U_EEPROM_TCP_DIRECTION2_PARA_ADDR                (U_EEPROM_TCP_DIRECTION1_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第3组地址 */
#define         U_EEPROM_TCP_DIRECTION3_PARA_ADDR                (U_EEPROM_TCP_DIRECTION2_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第4组地址 */
#define         U_EEPROM_TCP_DIRECTION4_PARA_ADDR                (U_EEPROM_TCP_DIRECTION3_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第5组地址 */
#define         U_EEPROM_TCP_DIRECTION5_PARA_ADDR                (U_EEPROM_TCP_DIRECTION4_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第6组地址 */
#define         U_EEPROM_TCP_DIRECTION6_PARA_ADDR                (U_EEPROM_TCP_DIRECTION5_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第7组地址 */
#define         U_EEPROM_TCP_DIRECTION7_PARA_ADDR                (U_EEPROM_TCP_DIRECTION6_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))
/* 安全静止第8组地址 */
#define         U_EEPROM_TCP_DIRECTION8_PARA_ADDR                (U_EEPROM_TCP_DIRECTION7_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))


/* 停机时间监控 */
#define         U_EEPROM_STOP_TIME_PARAM_ADDR                    (U_EEPROM_TCP_DIRECTION8_PARA_ADDR + sizeof(S_A_TCP_DIRECTION_UNIT))

/* 停机距离监控 */
#define         U_EEPROM_STOP_DISTANCE_PARAM_ADDR                (U_EEPROM_STOP_TIME_PARAM_ADDR + sizeof(S_A_STOP_TIME))
/* 停机容差阈值 */
#define         U_EEPROM_STOP_DISTANCE_TOLERANCE_PARAM_ADDR      (U_EEPROM_STOP_DISTANCE_PARAM_ADDR + sizeof(S_A_STOP_DISTANCE))

/* 额外补充参数 */
/* 缩减模式 */
/* 缩减模式，轴位置相关 */
/* 缩减模式下位置正限位(轴位置)第1组 */
#define         U_REDUCE_MODE_APOS1_PARAM_ADDR                    (U_EEPROM_STOP_DISTANCE_TOLERANCE_PARAM_ADDR + sizeof(S_A_STOP_TOLERANCE))
/* 缩减模式下位置正限位(轴位置)第2组 */
#define         U_REDUCE_MODE_APOS2_PARAM_ADDR                     (U_REDUCE_MODE_APOS1_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第3组 */
#define         U_REDUCE_MODE_APOS3_PARAM_ADDR                     (U_REDUCE_MODE_APOS2_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第4组 */
#define         U_REDUCE_MODE_APOS4_PARAM_ADDR                     (U_REDUCE_MODE_APOS3_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第5组 */
#define         U_REDUCE_MODE_APOS5_PARAM_ADDR                     (U_REDUCE_MODE_APOS4_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第6组 */
#define         U_REDUCE_MODE_APOS6_PARAM_ADDR                     (U_REDUCE_MODE_APOS5_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第7组 */
#define         U_REDUCE_MODE_APOS7_PARAM_ADDR                     (U_REDUCE_MODE_APOS6_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下位置正限位(轴位置)第8组 */
#define         U_REDUCE_MODE_APOS8_PARAM_ADDR                     (U_REDUCE_MODE_APOS7_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))

/* 缩减模式下最大速度限制(轴速度)第1组 */
#define         U_REDUCE_MODE_AVEL1_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_APOS8_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_APOS))
/* 缩减模式下最大速度限制(轴速度)第2组 */
#define         U_REDUCE_MODE_AVEL2_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL1_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第3组 */
#define         U_REDUCE_MODE_AVEL3_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL2_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第4组 */
#define         U_REDUCE_MODE_AVEL4_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL3_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第5组 */
#define         U_REDUCE_MODE_AVEL5_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL4_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第6组 */
#define         U_REDUCE_MODE_AVEL6_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL5_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第7组 */
#define         U_REDUCE_MODE_AVEL7_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL6_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 缩减模式下最大速度限制(轴速度)第8组 */
#define         U_REDUCE_MODE_AVEL8_SPEED_MAX_PARAM_ADDR            (U_REDUCE_MODE_AVEL7_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))


/* 缩减模式下最大速度限制(笛卡尔速度) */
#define         U_REDUCE_MODE_C_SPEED_MAX_PARAM_ADDR               (U_REDUCE_MODE_AVEL8_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_AVEL))
/* 肘部监控开关 */
#define         U_REDUCE_MODE_ELBOW_MONITOR_PARAM_ADDR             (U_REDUCE_MODE_C_SPEED_MAX_PARAM_ADDR + sizeof(S_A_REDUCE_MODE_CVEL))
/* 位置匹配监控 */
#define         U_POS_MATCH_MONITOR_PARAM_START_ADDR               (U_REDUCE_MODE_ELBOW_MONITOR_PARAM_ADDR + sizeof(INTERFER_TOOL_EXTRAL))
/* 位置匹配监控触发方式 */
#define         U_POS_MATCH_MONITOR_ACTIVE_PARAM_ADDR              U_POS_MATCH_MONITOR_PARAM_START_ADDR 
/* 位置匹配监控第1组 */
#define         U_POS_MATCH_MONITOR1_PARAM_ADDR                     (U_POS_MATCH_MONITOR_ACTIVE_PARAM_ADDR + sizeof(uint8_t))
/* 位置匹配监控第2组 */
#define         U_POS_MATCH_MONITOR2_PARAM_ADDR                     (U_POS_MATCH_MONITOR1_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第3组 */
#define         U_POS_MATCH_MONITOR3_PARAM_ADDR                     (U_POS_MATCH_MONITOR2_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第4组 */
#define         U_POS_MATCH_MONITOR4_PARAM_ADDR                     (U_POS_MATCH_MONITOR3_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第5组 */
#define         U_POS_MATCH_MONITOR5_PARAM_ADDR                     (U_POS_MATCH_MONITOR4_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第6组 */
#define         U_POS_MATCH_MONITOR6_PARAM_ADDR                     (U_POS_MATCH_MONITOR5_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第7组 */
#define         U_POS_MATCH_MONITOR7_PARAM_ADDR                     (U_POS_MATCH_MONITOR6_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))
/* 位置匹配监控第8组 */
#define         U_POS_MATCH_MONITOR8_PARAM_ADDR                     (U_POS_MATCH_MONITOR7_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))

/* 拖动示教设置 */
#define         U_DRAG_TEACH_INTERFACE_PARAM_ADDR                   (U_POS_MATCH_MONITOR8_PARAM_ADDR + sizeof(S_A_POS_MATCH_UNIT))

/* EEPROM End Address */
#define         EEPROM_END_ADDR                                     (U_DRAG_TEACH_INTERFACE_PARAM_ADDR + sizeof(S_A_DRAG_TEACH_INTERFACE))

#else

/* EEPROM End Address */
#define         EEPROM_END_ADDR                                  (EEPROM_ST_SAFE_TOOL_SETTING_PARAM_ADDR + sizeof(ST_INDUSTRY_SAVE_EEPROM))

#endif

/* EEPROM是否为初始值 FF */
#define         RAM_Inital_Value_Flag_ADDR                  (0x7FFF - sizeof(int8u))

/* RAM中功能码参数 */
#define         RAM_START_ADDR                               (0x8000)
/* 系统状态 */
#define         RAM_SYSTEM_READY_ADDR                        RAM_START_ADDR

/* 关节参数 */
#define         RAM_ST_JOINT_PARAM_ADDR                      (RAM_SYSTEM_READY_ADDR + sizeof(int8u))
/* 轴数 */
#define         RAM_AUTULAXISNUM_PARAM_ADDR                  (RAM_ST_JOINT_PARAM_ADDR + ST_JOINT_PARAM_SIZE)
/* 耦合参数 */
#define         RAM_COUP1_PARAM_ADDR                         (RAM_AUTULAXISNUM_PARAM_ADDR + AUTUL_AXIS_NUM_SIZE)
#define         RAM_COUP2_PARAM_ADDR                         (RAM_COUP1_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP3_PARAM_ADDR                         (RAM_COUP2_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP4_PARAM_ADDR                         (RAM_COUP3_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP5_PARAM_ADDR                         (RAM_COUP4_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP6_PARAM_ADDR                         (RAM_COUP5_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP7_PARAM_ADDR                         (RAM_COUP6_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
#define         RAM_COUP8_PARAM_ADDR                         (RAM_COUP7_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE )
/* 运动学参数 */
/* 机器人结构参数 */
#define         RAM_ROBOT_PARAM_ADDR                         (RAM_COUP8_PARAM_ADDR + ST_COUP_PARAM_ARRAY_SIZE)
/* 机器人结构参数补偿 */
#define         RAM_ROBOT_COMP_PARAM_ADDR                    (RAM_ROBOT_PARAM_ADDR + ROBOT_PARAM_SIZE)
/* 机器人旋转角度结构参数 */
#define         RAM_ROBOT_ROT_PARAM_ADDR                     (RAM_ROBOT_COMP_PARAM_ADDR + ROBOT_PARAM_COMP_SIZE)
/* 机器人旋转角度结构参数补偿 */
#define         RAM_ROBOT_ROT_COMP_PARAM_ADDR                (RAM_ROBOT_ROT_PARAM_ADDR + ROBOT_ROT_PARAM_SIZE)

/* 动力学参数 */
#define         RAM_ST_DYNAMIC_PARAM_ADDR                    (RAM_ROBOT_ROT_COMP_PARAM_ADDR + ROBOT_ROT_PARAM_COMP_SIZE)
#define         RAM_ST_DYNAMIC1_PARAM_ADDR                    RAM_ST_DYNAMIC_PARAM_ADDR
#define         RAM_ST_DYNAMIC2_PARAM_ADDR                   (RAM_ST_DYNAMIC1_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC3_PARAM_ADDR                   (RAM_ST_DYNAMIC2_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC4_PARAM_ADDR                   (RAM_ST_DYNAMIC3_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC5_PARAM_ADDR                   (RAM_ST_DYNAMIC4_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC6_PARAM_ADDR                   (RAM_ST_DYNAMIC5_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC7_PARAM_ADDR                   (RAM_ST_DYNAMIC6_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
#define         RAM_ST_DYNAMIC8_PARAM_ADDR                   (RAM_ST_DYNAMIC7_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)
/* 六关节机器人全参结构体用于高精度标定 */
#define         RAM_ST_ROBOT_MECH_FULL_PARAM_ADDR            (RAM_ST_DYNAMIC8_PARAM_ADDR + ST_ROBOT_LINK_PARAM_SIZE)

/* 工件工具参数 */
/* 安全工具模式 (废弃)*/
#define         RAM_ST_SAFE_TOOL_SETTING_PARAM_ADDR           (RAM_ST_ROBOT_MECH_FULL_PARAM_ADDR + ST_ROBOT_MECH_FULL_PARAM_SIZE)
/* 工具参数 */
/* 第一组 */
#define         RAM_ST_TOOL_DATA1_PARAM_ADDR                  (RAM_ST_SAFE_TOOL_SETTING_PARAM_ADDR + ST_SAFE_TOOL_SETTING_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_TOOL_DATA2_PARAM_ADDR                  (RAM_ST_TOOL_DATA1_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第3组 */
#define         RAM_ST_TOOL_DATA3_PARAM_ADDR                  (RAM_ST_TOOL_DATA2_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第4组 */
#define         RAM_ST_TOOL_DATA4_PARAM_ADDR                  (RAM_ST_TOOL_DATA3_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第5组 */
#define         RAM_ST_TOOL_DATA5_PARAM_ADDR                  (RAM_ST_TOOL_DATA4_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第6组 */
#define         RAM_ST_TOOL_DATA6_PARAM_ADDR                  (RAM_ST_TOOL_DATA5_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第7组 */
#define         RAM_ST_TOOL_DATA7_PARAM_ADDR                  (RAM_ST_TOOL_DATA6_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第8组 */
#define         RAM_ST_TOOL_DATA8_PARAM_ADDR                  (RAM_ST_TOOL_DATA7_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第9组 */
#define         RAM_ST_TOOL_DATA9_PARAM_ADDR                  (RAM_ST_TOOL_DATA8_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第10组 */
#define         RAM_ST_TOOL_DATA10_PARAM_ADDR                  (RAM_ST_TOOL_DATA9_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第11组 */
#define         RAM_ST_TOOL_DATA11_PARAM_ADDR                  (RAM_ST_TOOL_DATA10_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第12组 */
#define         RAM_ST_TOOL_DATA12_PARAM_ADDR                  (RAM_ST_TOOL_DATA11_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第13组 */
#define         RAM_ST_TOOL_DATA13_PARAM_ADDR                  (RAM_ST_TOOL_DATA12_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第14组 */
#define         RAM_ST_TOOL_DATA14_PARAM_ADDR                  (RAM_ST_TOOL_DATA13_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第15组 */
#define         RAM_ST_TOOL_DATA15_PARAM_ADDR                  (RAM_ST_TOOL_DATA14_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第16组 */
#define         RAM_ST_TOOL_DATA16_PARAM_ADDR                  (RAM_ST_TOOL_DATA15_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)

/* 工件参数 */
/* 第一组 */
#define         RAM_ST_WOBJ_DATA1_PARAM_ADDR                  (RAM_ST_TOOL_DATA16_PARAM_ADDR + ST_TOOL_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA2_PARAM_ADDR                  (RAM_ST_WOBJ_DATA1_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA3_PARAM_ADDR                  (RAM_ST_WOBJ_DATA2_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA4_PARAM_ADDR                  (RAM_ST_WOBJ_DATA3_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA5_PARAM_ADDR                  (RAM_ST_WOBJ_DATA4_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA6_PARAM_ADDR                  (RAM_ST_WOBJ_DATA5_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA7_PARAM_ADDR                  (RAM_ST_WOBJ_DATA6_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA8_PARAM_ADDR                  (RAM_ST_WOBJ_DATA7_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA9_PARAM_ADDR                  (RAM_ST_WOBJ_DATA8_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA10_PARAM_ADDR                  (RAM_ST_WOBJ_DATA9_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA11_PARAM_ADDR                  (RAM_ST_WOBJ_DATA10_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA12_PARAM_ADDR                  (RAM_ST_WOBJ_DATA11_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA13_PARAM_ADDR                  (RAM_ST_WOBJ_DATA12_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA14_PARAM_ADDR                  (RAM_ST_WOBJ_DATA13_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA15_PARAM_ADDR                  (RAM_ST_WOBJ_DATA14_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 第2组 */
#define         RAM_ST_WOBJ_DATA16_PARAM_ADDR                  (RAM_ST_WOBJ_DATA15_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 手动模式标志 */
#define         RAM_ST_POWER_MODE_PARAM_ADDR                   (RAM_ST_WOBJ_DATA16_PARAM_ADDR + ST_WOBJ_DATA_PARAM_SIZE)
/* 机器人类型 */
#define         RAM_ST_ROBOT_TYPE_PARAM_ADDR                   (RAM_ST_POWER_MODE_PARAM_ADDR + sizeof(int))
/* 编码器方向 */
#define         RAM_ST_ENCODER_DIR_PARAM_ADDR                  (RAM_ST_ROBOT_TYPE_PARAM_ADDR + sizeof(int))
/* 子模式 */
#define         RAM_ST_SUB_MODE_PARAM_ADDR                     (RAM_ST_ENCODER_DIR_PARAM_ADDR + sizeof(S_ENCODEDIR))
/* 激活安全模块 */
#define         RAM_ACTIVE_MONITOR_ADDR                        (RAM_ST_SUB_MODE_PARAM_ADDR + sizeof(int))
/* 三位置使能标志 */
#define         RAM_THREE_POS_ENABLE_ADDR                      (RAM_ACTIVE_MONITOR_ADDR + sizeof(int8u))
/* 版本号 */
#define         RAM_SAFE_MCU_VERSION_ADDR                      (RAM_THREE_POS_ENABLE_ADDR + sizeof(int8u))

/* 通知系统参数进行初始化 */
#define         RAM_SYSTEM_PARA_INITIAL_ADDR                   (RAM_SAFE_MCU_VERSION_ADDR + sizeof(S_SAFEMCUVERSION))
/* 参数初始化状态 */
#define         RAM_SYSTEM_INITIAL_STATUS_ADDR                 (RAM_SYSTEM_PARA_INITIAL_ADDR + sizeof(int8u))
/* 自动/手动模式切换 */
#define         RAM_MAN_MODE_ADDR                              (RAM_SYSTEM_INITIAL_STATUS_ADDR + sizeof(uint8_t))
/* 对内工装版本号 */
#define         RAM_INNER_VERSION                              (RAM_MAN_MODE_ADDR + sizeof(int))

/* 末尾地址 */
#define         RAM_END_ADDR                                   (RAM_INNER_VERSION + sizeof(int))

#ifdef COBOT

/* 协作上位机使用地址 */
#define U_RAM_TP_START_ADDR                                 (0xE000)
/* TCP 方向获取第1组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR1_ADDR                U_RAM_TP_START_ADDR
/* TCP 方向获取第2组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR2_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR1_ADDR + sizeof(int8u))
/* TCP 方向获取第3组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR3_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR2_ADDR + sizeof(int8u))
/* TCP 方向获取第4组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR4_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR3_ADDR + sizeof(int8u))
/* TCP 方向获取第5组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR5_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR4_ADDR + sizeof(int8u))
/* TCP 方向获取第6组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR6_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR5_ADDR + sizeof(int8u))
/* TCP 方向获取第7组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR7_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR6_ADDR + sizeof(int8u))
/* TCP 方向获取第8组末端向量 */
#define U_RAM_TCP_DIRECTION_GET_VECTOR8_ADDR                (U_RAM_TCP_DIRECTION_GET_VECTOR7_ADDR + sizeof(int8u))
/* 协作上位机使用地址 */
#define U_RAM_TP_END_ADDR                                   (U_RAM_TCP_DIRECTION_GET_VECTOR8_ADDR + sizeof(int8u))

#endif


/* 虚拟功能功能码(预留500个位置) */

/* 清报警 */
#define         RAM_CLEAR_ALARM_ADDR                           (0xFE0C)
/* 通知系统重置 */
#define         RAM_RESET_SYSTEM_ADDR                          (RAM_CLEAR_ALARM_ADDR + sizeof(int8u))




#ifdef __cplusplus
}
#endif
#endif /* __PARADATA_H__ */
