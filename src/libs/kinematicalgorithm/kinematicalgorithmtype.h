#pragma once
#include <stdint.h>
#include <stdbool.h>

#define KinematicAlgorithmSpace InoKinematicAlgorithmMetaType
namespace InoKinematicAlgorithmMetaType {
/*! @file
********************************************************************************
<PRE>
模块名       : librobot & libTransfor & libRtKine & DSP 共用库
文件名       : CommonData.h
相关文件     : <与此文件相关的其它文件>
文件实现功能 : 点位、坐标参数、
作者         : llw & hyz & lgy & lqp & zz
版本         : v1.0
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
</PRE>
2022-04-12 新建文件
*******************************************************************************/

#define FOR_WINDOWS
//#define FOR_LINUX

#define RPOS_MAX_NUM                9999U /* 支持RobPos最大个数 */
#define JPOS_MAX_NUM                9999U /* 支持RobJPos最大个数 */
#define ARMTYPE_NUM                 4U    /* 臂参数个数 */
#define RPOS_AXIS_NUM               6U    /* 机器人坐标个数 */
#define JPOS_AXIS_NUM               8U    /* 机器人关节个数 */
#define EXT_AXIS_NUM                6U    /* 外部轴个数 */
#define ALL_AXIS_NUM                14U    /* 外部轴个数 */

#define MAX_TOOL_NUM                16U   /* 工具参数总个数 */
#define MAX_WOBJ_NUM                16U   /* 工件参数总个数 */
#define MAX_LOAD_NUM                16U   /* 负载参数总个数 */

#define POSIT_DIMENT                3U    /* 质心位置（com） */
#define ORIENT_DIMENT               3U    /* 质心的姿态（orient） */
#define INERTIA_DIMENT              3U    /* 惯量（inertia） */

#define MECH_UNIT_NAME_LEN          18U    /* 机械单元名称长度 */
#define MAX_CFG_MECHUNIT_NUM         7U    /* 支持可配置的机械单元最大数量（可配置最多的机械单元数量） */
#define MAX_MECHUNIT_NUM            36U    /* 机械单元最大数量（用于实时命令，考虑独立轴） */

#define LINK_PARM_NUM 				8U	   /* 运动学连杆参数 */
#define COMP_PARM_NUM 				16U	   /* 运动学库补偿参数 */
#define STIF_PARM_NUM 				16U	   /* 运动学库刚度参数 */

    /* 伺服类型 */
    enum ServoType
{
    SV620N_1AXIS = 0x0000,           /* SV620一轴 */
                           SV660N_1AXIS = 0x0001,           /* SV660一轴 */
    SV660N_2AXIS = 0x0002,           /* SV660二轴 */
};

/* 坐标系类型 */
enum CoordType
{
    COORD_JOINT = 1,                 /* 关节坐标系 */
    COORD_BASE = 2,                  /* 基坐标系 */
    COORD_TOOL = 3,                  /* 工具坐标系 */
    COORD_WOBJ = 4,                  /* 工件坐标系 */
    COORD_WORLD = 5,                 /* 世界坐标系 */
};

/* 坐标系格式 */
enum PosFormat
{
    FORMAT_JOINT = 1,                /* 关节坐标系格式 */
    FORMAT_BASE = 2,                 /* 基坐标系格式 */
    FORMAT_FLANGLE = 3,              /* 法兰坐标系格式 */
    FORMAT_WOBJ = 4,                 /* 工件坐标系格式 */
    FORMAT_WORLD = 5,                /* 世界坐标系格式 */
    MAX_POSFORMAT
};

//#pragma pack(push)  /* 保存对齐状态 */
//#pragma pack(1)     /* 设置为1字节对齐 */

//运动学库模型初始化参数
typedef struct
{
    double linkParm[LINK_PARM_NUM];
    double compParm[COMP_PARM_NUM];
    double stiffParm[STIF_PARM_NUM];
}KineParm;

/* 位置点 */
typedef struct _RobPos_
{
    double  RPosData[RPOS_AXIS_NUM];     /* XYZABC */
    int ArmParm[ARMTYPE_NUM];            /* 臂参数 */
    double  EPosData[EXT_AXIS_NUM];      /* E1~E6 */
}RobPos;

/* 关节点 */
typedef struct _JPos_
{
    double JointData[JPOS_AXIS_NUM];     /* J1~J8 */
    double EPosData[EXT_AXIS_NUM];       /* E1~E6 */
}JPos;

typedef struct _Pose_
{
    double Data[RPOS_AXIS_NUM];          /* 表示位置和方位 */
}Pose;

/* 负载参数 */
typedef struct _LoadData_
{
    double Mass;
    double Cog[POSIT_DIMENT];
    double Orient[ORIENT_DIMENT];
    double Inertia[INERTIA_DIMENT];
}LoadData;

/* 工具参数 */
typedef struct _ToolData_
{
    bool RobHold;                       /* True-夹持工具; False-外部工具 */
    Pose TFrame;                        /* 工具坐标系 */
    LoadData TLoad;                     /* 工具负载 */
}ToolData;

/* 工件参数 */
typedef struct _WobjData_
{
    bool RobHold;                     /* 工件是否夹持  True-夹持; False-非夹持 */
    bool UFFix;                       /* 工件是否固定（是否相对于大地坐标系固定、是否相对于法兰盘固定）*/
    int8_t MecIndex;                  /* 机械单元索引号 */
    Pose UFame;                       /* 用户坐标系 */
    Pose OFame;                       /* 工件坐标系 */
}WobjData;

/* 外部轴轴参数 */
typedef struct _ExtAxisParam_
{
    int16_t SvType;                /* 伺服类型 */
    int16_t OpMode;                /* 模式：8-位置模式；9、10不开放（9-速度模式; 10-转矩模式) */
    int16_t AxisType;              /* 电机轴属性：0-旋转轴；线性轴不开放（1-线性轴） */
    int16_t MoveType;              /* 传动方式 0、转动-转动，1、转动-直线 */
    float PhyTransRatio;           /* 物理传动比 */
    int32_t AbsZero;               /* 零点 */
    float PosLimit;                /* 正限位：默认：180.00，范围：-10000.0~10000.0  */
    float NegLimit;                /* 负限位：默认：-180.00，范围：-10000.0~10000.0 */
    float TeachVel;                /* 示教速度：默认：10.00，范围：0.01-250 */
    float TeachAcc;                /* 示教加速度：默认：100.00，范围：10-1000 */
    float MaxVel;                  /* 最大速度：默认：1000.00，范围：10-10000 */
    float MaxAcc;                  /* 最大加速度：默认：10000.00，范围：1000-100000.0 */
    float StopDec;                 /* 停机减速度：默认：10000.00，范围：1000-100000.0 */
    int32_t FollowErr;             /* 跟随误差：默认：1048576*3，范围：1048576*1-*5 */
    int32_t InposErr;              /* 到位误差：默认：1048576*3，范围：1048576*1-*5 */
    int16_t InposTime;             /* 到位时间：默认：20，范围：3-100 */
    int16_t CurrentLimit;          /* 电流限制：默认：300，范围：100-300 */
    int16_t AverageLoadRateLimit;  /* 平均负载率：默认：100，范围：50-100 */
}ExtAxisParam;

/* 外部轴信息 */
typedef struct _ExtAxisParamItem_
{
    char MechUnitName[MECH_UNIT_NAME_LEN];   /* 所属机械单元 */
    uint8_t ExtAxisID;                       /* 外部轴ID：0-NULL；1~6对应E1~E6 */
    ExtAxisParam Param;                      /* 轴参数 */
}ExtAxisParamItem;

typedef struct _RelativeTransFormat_
{
    Pose Transformat;                        /* 转换位姿关系 */
}RelativeTransformat;

/* 机械单元参数(ARM和上位机交互) */
typedef struct _MechUnit_
{
    char Name[MECH_UNIT_NAME_LEN];                  /* 机械单元的名称 */
    uint16_t Type;                                  /* 机械单元类型：0-机器人；1-X轴导轨；2-单轴旋转变位机；3-双轴旋转变位机；4-101无模型1轴；5-102无模型2轴…. */
    uint8_t InstallType;                            /* 安装方式：0-固定安装, 1-在可移动的导轨上(机械单元上) */
    char MoveMechName[MECH_UNIT_NAME_LEN];          /* 可移动导轨机械单元名称：InstallType为1时，对应的可移动的导轨的机械单元名称 */
    uint8_t AxisCount;                              /* 轴数目 */
    RelativeTransformat Transformat[EXT_AXIS_NUM];  /* 转换关系 */
    uint8_t AxisMap[EXT_AXIS_NUM];                  /* 轴映射关系 */
}MechUnit;

/* 机械单元参数(ARM和运动学库、译码库、DSP交互，将机械单元名称映射为索引号) */
typedef struct _MechUnitPara_
{
    int MecIndex;                                   /* 机械单元索引号 */
    uint16_t Type;                                  /* 机械单元类型：0-机器人；1-X轴导轨；2-单轴旋转变位机；3-双轴旋转变位机；4-101无模型1轴；5-102无模型2轴…. */
    uint8_t InstallType;                            /* 安装方式：0-固定安装, 1-在可移动的导轨上(机械单元上) */
    uint8_t MoveMecIndex;                           /* 可移动导轨索引号：InstallType为1时，对应的可移动的导轨的机械单元名称 */
    uint8_t AxisCount;                              /* 轴数目 */
    RelativeTransformat Transformat[EXT_AXIS_NUM];  /* 转换关系 */
    uint8_t AxisMap[EXT_AXIS_NUM];                  /* 轴映射关系 */
}MechUnitPara;

/* 机械单元配置信息(ARM和上位机交互) */
typedef struct _MechUnitsCfgData_
{
    uint8_t MechUnitCount;                            /* 机械单元个数 */
    MechUnit Units[MAX_CFG_MECHUNIT_NUM];             /* 机械单元参数：目前支持1机器人+2机械单元（总共3个）*/
    uint8_t ExtAxisParamItemCount;                    /* 机械单元的总轴数（不包括机器人） */
    ExtAxisParamItem ExtAxisParamItems[EXT_AXIS_NUM]; /* 机械单元的轴参数*/
}MechUnitsCfgData;

/* 标定误差 */
typedef struct _CalibErr_
{
    double maxErr;
    double avgErr;
    double minErr;
}CalibErr;
//#pragma pack(pop)   /* 恢复原有对齐方式 */
}
