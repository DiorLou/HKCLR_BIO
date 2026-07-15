#ifndef __UPARADATA_H__
#define __UPARADATA_H__

#include "GlobalDataTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* u8协作的EERPOM中功能码参数 */
#define   U_JOINT_TORQUE_NUM        (8)
#define   U_TCP_FORCE_NUM           (8)

#define   U_JOINT_POWER_NUM         (8)
#define   U_BODY_POWER_NUM          (8)
#define   U_BODY_MOMENTTUM_NUM      (8)
#define   U_SAFE_STATIC_NUM         (8)
#define   U_TCP_DIRECTION_NUM       (8)
#define   U_CVEL_GROUP_NUM          (8)
#define   U_AVEL_GROUP_NUM          (8)
#define   U_APOS_GROUP_NUM          (8)
#define   U_ROBOT_AXIS_NUM          (6)
#define   U_IZONE_INTERFERZONESSTATUSLENGTH (16)       /* 干涉区状态长度16 */
#define   U_IZONE_CVEL_ARRAY_LENGTH         (8)        /* 笛卡尔速度组数 */
#define   U_POS_DISMATCH_GROUP_NUM (8)
/* 1字节对齐 */
#pragma pack(1)

/* 关节转矩 */
typedef struct A_JOINT_TORQUE_UNIT
{
    uint8_t u8JtUnitSwitch;
    uint8_t u8JtUnitStopWay;
    float f32TorqueMax[U_ROBOT_AXIS_NUM];
    float f32ReDuceModeTorqueMax[U_ROBOT_AXIS_NUM];  
}S_A_JOINT_TORQUE_UNIT;


typedef struct A_JOINT_TORQUE
{
    uint8_t u8JTActiveWay;
    S_A_JOINT_TORQUE_UNIT stJtGroup[U_JOINT_TORQUE_NUM];
}S_A_JOINT_TORQUE;


/* TCP 力监控 */
typedef struct A_TCP_FORCE_UNIT
{   
    uint8_t u8TcpUnitSwitch;                /* 组激活开关 */
    uint8_t u8TcpUnitStopWay;               /* 组停机类型 */
    float f32TcpForceMax;                  /* 组TCP力最大阈值 */
    float f32ReduceModeTcpForceMax;        /* 缩减模式下组TCP力最大阈值 */
}S_A_TCP_FORCE_UNIT;

typedef struct A_TCP_FORCE
{
    uint8_t u8TcpActiveWay;
    S_A_TCP_FORCE_UNIT stTcpForceGrop[U_TCP_FORCE_NUM];
}S_A_TCP_FORCE;

/* 关节功率监控 */
typedef struct A_JOINT_POWER_UNIT
{   
    uint8_t u8JpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8JpUnitStopWay;                /* 组停机类型 */
    float f32JpUnitMax[U_ROBOT_AXIS_NUM];                    /* 组关节功率最大阈值 */
    float f32ReduceModeJpUnitMax[U_ROBOT_AXIS_NUM];          /* 缩减模式下组关节功率最大阈值 */
}S_A_JOINT_POWER_UNIT;

typedef struct A_JOINT_POWER
{
    uint8_t u8JpActiveWay;
    S_A_JOINT_POWER_UNIT stJointPowerGrop[U_JOINT_POWER_NUM];
}S_A_JOINT_POWER;

/* 整机功率监控 */
typedef struct A_BODY_POWER_UNIT
{   
    uint8_t u8BpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8BpUnitStopWay;                /* 组停机类型 */
    float f32BpUintMax;                     /* 组整机功率最大阈值 */
    float f32ReduceModeBpUintMax;           /* 缩减模式下组整机功率最大阈值 */
}S_A_BODY_POWER_UNIT;

typedef struct A_BODY_POWER
{
    uint8_t u8BpActiveWay;
    S_A_BODY_POWER_UNIT stBodyPowerGrop[U_BODY_POWER_NUM];
}S_A_BODY_POWER;

/* 整机动量监控 */
typedef struct A_BODY_MOMENTUM_UNIT
{   
    uint8_t u8BpUnitSwitch;                 /* 组激活开关 */
    uint8_t u8BpUnitStopWay;                /* 组停机类型 */
    float f32BpUintMax;                     /* 组整机动量最大阈值 */
    float f32ReduceModeBpUintMax;           /* 缩减模式下组整机动量最大阈值 */
}S_A_BODY_MOMENTUM_UNIT;

typedef struct A_BODY_MOMENTUM
{
    uint8_t u8BmActiveWay;
    S_A_BODY_MOMENTUM_UNIT stBodyMomGrop[U_BODY_MOMENTTUM_NUM];
}S_A_BODY_MOMENTUM;

/* 安全原点到位状态 */
typedef struct A_SAFE_BASE_POINT_STATUS
{
    uint8_t u8SafePointActiveWay;                     /* 生效方式 */
    uint8_t u8SafePointActiveMode;                    /* 生效模式 */
    float f32SafeErrorThreshold[U_ROBOT_AXIS_NUM];    /* 轴误差阈值 */
    float f32SafePointValue[U_ROBOT_AXIS_NUM];        /* 轴安全原点设置值 */

}S_A_SAFE_BASE_POINT_STATUS;

/* 拖动示教 */
typedef struct A_DRAG_TEACH_INTERFACE
{
    uint8_t u8active;                     /* 生效方式 */
    uint8_t u8StopCat;                    /* 生效模式 */
    float tcpVel;                         /* 速度值 */
}S_A_DRAG_TEACH_INTERFACE;

/* 安全静止监控 */
typedef struct A_SAFE_BODY_STATIC_UNIT
{
    uint8_t u8BsSwitch;                             /* 激活开关 */
    uint8_t u8BsStopWay;                            /* 停机 - 算法未使用*/
    float f32ToleranceThreshold[U_ROBOT_AXIS_NUM];  /* 轴容差阈值 */
    uint8_t u8AposSwitch[U_ROBOT_AXIS_NUM];         /* 轴启动开关 */
}S_A_SAFE_BODY_STATIC_UNIT;

typedef struct A_SAFE_BODY_STATIC
{
    uint8_t u8ActiveWay;            /* 生效方式 */
    S_A_SAFE_BODY_STATIC_UNIT stSafeBodyStaticGroup[U_SAFE_STATIC_NUM];        
}S_A_SAFE_BODY_STATIC;

/* TCP 方向监控 */
typedef struct A_TCP_VECTOR
{
    uint8_t u8Switch;
    float f32VectorX;
    float f32VectorY;
    float f32VectorZ;
    float f32Deg;
}S_A_TCP_VECTOR;

typedef struct A_TCP_DIRECTION_UNIT
{
    uint8_t u8TdSwitch;                      /* 激活开关 */
    uint8_t u8TdStopWay;                     /* 停机 */
    S_A_TCP_VECTOR stVectorGroupX;           /* 组X向量 */
    S_A_TCP_VECTOR stVectorGroupZ;           /* 组Z向量 */

}S_A_TCP_DIRECTION_UNIT;

typedef struct A_TCP_DIRECTION
{
    uint8_t u8ActiveWay;                                       /* 生效方式 */
    S_A_TCP_DIRECTION_UNIT stTcpDeGroup[U_TCP_DIRECTION_NUM];  /* TCP 监控 */

}S_A_TCP_DIRECTION;

/* 停机时间监控保存EEPROM（上位机） */
typedef struct A_STOP_TIME
{
    uint8_t u8StActiveWay;                                /* 功能生效方式 */
    // float  f32JointSpeedMax[U_ROBOT_AXIS_NUM];            /* 最大关节转速 */
    // uint32_t i32SpeedDelayTimes[U_ROBOT_AXIS_NUM];        /* 减速执行延迟时间 */
    // uint32_t i32BrakeCloseTimes[U_ROBOT_AXIS_NUM];        /* 制动器闭合时间 */
    // float f32SpeedMonitTolerance[U_ROBOT_AXIS_NUM];       /* 速度监控容差 */
    uint32_t u32TimeThresholdMax;                         /* 最大时间阈值 */
}S_A_STOP_TIME;

/* 停机时间监控上电下发（保存在RAM中，A40i） */
typedef struct A_STOP_TIME_RAM
{
    uint32_t i32SpeedDelayTimes[U_ROBOT_AXIS_NUM];        /* 减速执行延迟时间 */
    uint32_t i32BrakeCloseTimes[U_ROBOT_AXIS_NUM];        /* 制动器闭合时间 */
    float f32SpeedMonitTolerance[U_ROBOT_AXIS_NUM];       /* 速度监控容差 */
    uint32_t u32PlanDelayTime;                            /* 规划延迟时间 */
}S_A_STOP_TIME_RAM;

/* 停机距离监控 （上位机）*/
typedef struct A_STOP_DISTANCE
{
    uint8_t u8StActiveWay;                                /* 功能生效方式 */ 
    float  f32DistanceMax;                                /* 最大距离阈值 */
    uint8_t u8TcpStopDistanceSwitch;                      /* TCP停机距离监控开关 */ 
    // float f32TcpDistanceTol;                              /* TCP距离监控容差 */
    uint8_t u8AposDistanceSwitch;                         /* 轴停机距离监控开关 */
    // float f32AposDistanceTol[U_ROBOT_AXIS_NUM];           /* 轴距离监控容差 */
    float f32AposDistanceDeg[U_ROBOT_AXIS_NUM];           /* 轴距离阈值deg */
}S_A_STOP_DISTANCE;

/* 停机距离监控上电下发(保存在RAM中，A40i) */
typedef struct A_STOP_DISTANCE_RAM
{
    float f32TcpDistanceTol;                              /* TCP距离监控容差 */
    float f32AposDistanceTol[U_ROBOT_AXIS_NUM];           /* 轴距离监控容差 */
}S_A_STOP_DISTANCE_RAM;



/* 缩减模式相关参数 */  

typedef struct A_REDUCE_MODE_APOS
{
    double f64APosReduceModeMax[U_ROBOT_AXIS_NUM];              /* 缩减模式下位置正限位(轴位置) */
    double f64APosReduceModeMin[U_ROBOT_AXIS_NUM];              /* 缩减模式下位置负限位(轴位置) */
}S_A_REDUCE_MODE_APOS;
typedef struct A_REDUCE_MODE_AVEL
{
    double f64AVelReduceModeMax[U_ROBOT_AXIS_NUM];              /* 缩减模式下最大速度限制(轴速度) */
}S_A_REDUCE_MODE_AVEL;
typedef struct A_REDUCE_MODE_CVEL
{
    double f64CVelReduceModeMax[U_CVEL_GROUP_NUM];   /* 缩减模式下最大速度限制(笛卡尔速度) */
}S_A_REDUCE_MODE_CVEL;
typedef struct A_REDUCE_MODE
{
    S_A_REDUCE_MODE_APOS stReduceModeApos[U_APOS_GROUP_NUM];    /* 缩减模式，轴位置相关 */
    S_A_REDUCE_MODE_AVEL stReduceModeAvel[U_AVEL_GROUP_NUM];    /* 缩减模式，轴速度相关 */
    S_A_REDUCE_MODE_CVEL stReduceModeCvel;                    /* 缩减模式，笛卡尔速度相关 */
}S_A_REDUCE_MODE;
/* 运动学额外新增 */
typedef struct 
{
    double d1;           // UR??d1  //TODO:协作新增
	double d5;           // UR??d5	//TODO:协作新增
	double d6;           // UR??d6	//TODO:协作新增
}ST_TROBOT_MECH_PARA_EXTRAL;

/* 六关节机器人全参结构体用于高精度标定额外新增 */
typedef struct
{
    double beta3;	//TODO:协作新增
    double a1;		//TODO:协作新增
}ST_ROBOT_MECH_FULL_PARAM_EXTRAL;

/* 监控对象, 内含MTCP, 球体, 长方体包围盒额外补充参数 */
typedef struct INTERFER_TOOL_EXTRAL
{
	uint8_t u8ElbowMonitor[U_IZONE_INTERFERZONESSTATUSLENGTH];                            /* 肘部监控开关 */
} INTERFER_TOOL_EXTRAL;

/* 附加参数补充结构体 */
typedef struct A_EXTRAL_PARAM
{
    S_A_REDUCE_MODE stReduceMode;
    INTERFER_TOOL_EXTRAL stInterferToolExtral;
}S_A_EXTRAL_PARAM;

/* 附加参数补充结构体(RAM) */
typedef struct A_EXTRAL_PARAM_RAM
{
    ST_ROBOT_MECH_FULL_PARAM_EXTRAL stRobotMechFullExtral;
    ST_TROBOT_MECH_PARA_EXTRAL stTRobotMechParaExtral;
    ST_TROBOT_MECH_PARA_EXTRAL stTRobotMechCompParaExtral;

}S_A_EXTRAL_PARAM_RAM;

typedef struct STOP_TOLERANCE
{
    float f32StopDisTolerance[U_ROBOT_AXIS_NUM];   /* 停机容差阈值 停机距离界面中设置 */
}S_A_STOP_TOLERANCE;

/* 位置匹配监控单元 */
typedef struct POS_MATCH_UNIT
{
    uint8_t u8PmUnitSwitch;                 /* 组激活开关 */
    uint8_t u8PmUnitStopWay;                /* 组停机类型 */
    float f32PmUnitMax[U_ROBOT_AXIS_NUM];                    /* 组关节位置容差最大阈值 */
    float f32ReduceModePmUnitMax[U_ROBOT_AXIS_NUM];          /* 缩减模式下组关节位置容差最大阈值 */
}S_A_POS_MATCH_UNIT;

/* 位置匹配监控 */
typedef struct POS_DISMATCH
{
	uint8_t u8PdmActiveWay;
    S_A_POS_MATCH_UNIT stPosMatchGrop[U_POS_DISMATCH_GROUP_NUM];
}S_A_POS_MATCH;

/* u8安全参数 */
typedef struct U_PARAMS_SAVE_TO_EEPROM
{
	/* 保存在EEPROM中的参数 */
	/* TCP 力监控 */
	S_A_TCP_FORCE stTcpForce;
	/* 整机功率监控 */
	S_A_BODY_POWER stBodyPower;
	/* 整机动量监控 */
	S_A_BODY_MOMENTUM stBodyMomentum;
	/* 安全原点到位状态 */
	S_A_SAFE_BASE_POINT_STATUS stSafeBasePointStatus;
	/* 安全静止监控 */
	S_A_SAFE_BODY_STATIC stBodyStatic;
	/* TCP 方向监控 */
	S_A_TCP_DIRECTION stTcpDirection;
	/* 停机时间监控 */
	S_A_STOP_TIME stStopTime;
	/* 停机距离监控 */
	S_A_STOP_DISTANCE stStopDistance;
    /* 停机容差阈值 停机距离界面中设置 */
    S_A_STOP_TOLERANCE stStopTolerance; 
    /* 额外补充参数 */
    S_A_EXTRAL_PARAM  stUExtralParam;
    /* 位置匹配监控 */
    S_A_POS_MATCH  stPosMatch;
	
}S_U_PARAMS_SAVE_TO_EEPROM;

#pragma pack()



#ifdef __cplusplus
}
#endif
#endif /* __UPARADATA_H__ */
