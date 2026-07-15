/*! @file
********************************************************************************
<PRE>
模块名       : 解释器
文件名       : Globals.h
相关文件     : <与此文件相关的其它文件>
文件实现功能 : 全局常量的定义,常用的数据类型
作者         : llw
版本         : v2.0
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
</PRE>
2015-3-26 增加VELSET指令
2015-03-26 增加VetSetK类别
2015-03026 增加REVELSET类别
*******************************************************************************/
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifdef FOR_CONTROLLER_LINUX32
    #include "../include/Language.h"
#endif

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#ifndef INT_MAX
    #define INT_MAX    ((int)(~0U >> 1))
    #define INT_MIN    (-INT_MAX - 1)
    #define UINT_MAX   (~0U)
    #define LONG_MAX   ((long)(~0UL >> 1))
    #define LONG_MIN   (-LONG_MAX - 1)
    #define ULONG_MAX  (~0UL)
    #define LLONG_MAX  ((long long)(~0ULL >> 1))
    #define LLONG_MIN  (-LLONG_MAX - 1)
    #define ULLONG_MAX (~0ULL)
#endif

#ifndef PRE_TRANSFOR
// #define PRE_TRANSFOR
#endif
#ifndef WIN32
    #define _atoi64(val) strtoll(val, NULL, 10)
#endif

#define MAX_SOCKET_NUM (16U)
// #include <setjmp.h>
// extern jmp_buf jmpbuffer;

#define FOR_STEPRUN 1
#include "../third_party/include/instruction/GlobalsData.h"
#include "../third_party/include/instruction/EnumListForRobLab.h"

// #include "MemoryPool.h"
// #include "CommonData.h"
// #include "ExecuteData.h"
// #include "EnumListForLinux.h"

#if defined(FOR_CONTROLLER_LINUX32)
    #define PATH_OF_PRO "/robot/TeachProgram/"
    #include "log_printf.h"
    #include "stdint.h"
    #include <pthread.h>
    #include <stdbool.h>
#elif defined(FOR_TEACHBOX_LINUX32)
    #define PATH_OF_PRO "./TeachProgram/"
    // #include "log_printf.h"
    #include "stdint.h"
    #include <pthread.h>
    #include <stdbool.h>
#else
    #include <Windows.h>
    #include <iostream>
using namespace std;
    #define PATH_OF_PRO "D:\\"
#endif
#define MAX_PRO_LINNUM 2000
#ifndef TRANS_PRINT
    #define TRANS_PRINT m_printf
    #ifndef MTRB_DEBUG
        #define MTRB_EMERG   0
        #define MTRB_ALERT   1
        #define MTRB_CRIT    2
        #define MTRB_ERR     3
        #define MTRB_WARNING 4
        #define MTRB_NOTICE  5
        #define MTRB_INFO    6
        #define MTRB_DEBUG   7
    #endif
#endif

#ifndef NULL
    #define NULL 0x00
#endif

#ifndef FALSE
    #define FALSE 0
#endif
#ifndef ZERO
    #define ZERO 0.000001
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef _SIZE_T_DEFINED
    #ifdef __RPC_WIN64__
typedef unsigned long long int size_t;
    #else
typedef unsigned int size_t;
    #endif
    #define _SIZE_T_DEFINED
#endif

#define MAX_ARR_ROWNUM 3
#ifndef INT_MIN
    #define INT_MIN (-2147483648)
#endif
#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif

#define P_FORMAT_STRING       "P[%d] = %lf,%lf,%lf,%lf,%lf,%lf;%d,%d,%d,%d;%lf,%lf,%lf,%lf,%lf,%lf;Name = %s;"
#define JP_FORMAT_STRING      "JP[%d] = %lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf;%lf,%lf,%lf,%lf,%lf,%lf;Name = %s;"
#define PAVR_FORMAT_STRING    "%lf,%lf,%lf,%lf,%lf,%lf;%d,%d,%d,%d;%lf,%lf,%lf,%lf,%lf,%lf;"
#define JPAVR_FORMAT_STRING   "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf;%lf,%lf,%lf,%lf,%lf,%lf;"
#define PRAVR_FORMAT_STRING   "%lf,%lf,%lf,%lf,%lf,%lf;"
#define TOOLAVR_FORMAT_STRING "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf;"
#define WOBJAVR_FORMAT_STRING "%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf;"
#define LOADAVR_FORMAT_STRING "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf;"
#define PNo_FORMAT_STRING     "P[%d]"

#ifndef ENUM_FORLINUX
// 语句类型返回
typedef enum
{
    RESTMTEND = 1000
} ReStmtKind;
#endif

#ifndef ERTTYPENO
    #define ERTTYPENO
typedef enum
{
    RBTYPE_INVALID = 0,
    // 3轴
    RBTYPE_SCARA_C = 46,            // 3关节串联scara无Z轴；
    RBTYPE_SCARA_E = 47,            // 3轴+外司电批轴（三轴挂于EtherCat总线上，电批独立）
    RBTYPE_DELTA_A = 41,            // 3轴对称并联+1轴旋转的delta
    RBTYPE_DELTA_B = 45,            // 3轴对称并联的delta
    RBTYPE_SCARA_SCREW_THREE = 48,  // 3轴+外司电批轴（三轴挂于EtherCat总线上，电批独立）
    RBTYPE_SCARA_SCREW_FOUR = 44,   // 3轴+本司电批轴（全部挂于EtherCat总线上，电批非独立）
    // 4轴
    RBTYPE_SCARA_A = 4,      // 4关节串联scara
    RBTYPE_SCARA_R = 4110,   // 倒装scara
    RBTYPE_PALLET_A = 42,    // 码垛一型
    RBTYPE_PALLET_B = 43,    // 码垛二型
    RBTYPE_SCARA_D = 4140,   // 平面SCARA，不联动
    RBTYPE_TRIPOD_A = 4710,  // tripod，3D打印机械手A
    RBTYPE_TRIPOD_B = 4720,  // tripod，3D打印机械手B
    RBTYPE_PUNCH_A = 4800,   // 冲压机械手
    RBTYPE_FOUR_NA = 4900,   // 四轴联动，无模型 PPRR
    // 5轴
    RBTYPE_FIVE_A = 5,   // 3p2r
    RBTYPE_FIVE_B = 51,  // 3p2r
    // 6轴
    RBTYPE_SIXR_A = 6,   // 通用串联6R
    RBTYPE_SIXR_B = 61,  // 通用串联6R减去两轴
    RBTYPE_SIXR_C = 62,  // 变异SCARA+2直线轴 科瑞
    RBTYPE_SIXR_D = 63   // 6轴并联机器人 Stewart
} eRtTypeNo;
#endif

#ifdef FOR_CONTROLLER
    #define MaxMemPoolBufSize (64 * 1024 * 1024)
#else
    #ifdef FOR_X64
        #define MaxMemPoolBufSize (100 * 1024 * 1024)
    #else
        #define MaxMemPoolBufSize (23 * 1024 * 1024)
    #endif
#endif

/* SHIFT is the power of hash function */
#define SHIFT             4
#define MAX_L_VAR_NUM     10000
#define MAX_ACC_VAR_NUM   120
#define MAX_DEC_VAR_NUM   120
#define MAX_ALARM_NUM     16
#define MAX_AOUT_VAR_NUM  16
#define MAX_DA_NUM        16
#define MAX_IG_VAR_NUM    16
#define MAX_IO_VAR_NUM    13824
#define MAX_PYIO_NUM      128
#define MEMRY_IO_STARTBIT 12800

#define MAX_BYTE_VAR_NUM  256
#define MAX_WORD_VAR_NUM  256
#define MAX_DWORD_VAR_NUM 256
#define MAX_REAL_VAR_NUM  256

#define LLW_COORD_JOINT     1
#define LLW_COORD_WORLD     2
#define LLW_COORD_TOOL      3
#define LLW_COORD_USER      4
#define LLW_COORD_VXCALIB   5
#define LLW_COORD_VXCALIBPR 6
#define LLW_COORD_CNVPR     7
#define LLW_COORD_TCP       5

#define MAX_IG_CHARNUM 8

/* 翻译字符串最大长度 */
#define TRANSLATE_MAX_LEN 256

// #define _DEBUG  1

#ifndef MAX_FLOAT_VALUE
    #define MAX_FLOAT_VALUE (3.40e+38)
#endif
#ifndef MIN_FLOAT_VALUE
    #define MIN_FLOAT_VALUE (-3.40e+38)
#endif
#ifndef MAX_DOUBLE_VALUE
    #define MAX_DOUBLE_VALUE (1.79E+308)
#endif
#ifndef MIN_DOUBLE_VALUE
    #define MIN_DOUBLE_VALUE (-1.79E+308)
#endif
#ifndef MAX_INT_VALUE
    #define MAX_INT_VALUE 2147483647
#endif
#ifndef MIN_INT_VALUE
    #define MIN_INT_VALUE -2147483647
#endif

#define C_JPOS_AXIS_NUM 6

#define INTERRUPT_SINGEL_MAX 127

typedef struct RESAVEDATA_STR
{
    int ComNo;
    char GetPortBufString[1024];
} ReasveData;

#ifndef FOR_LINUX
typedef struct _mkheader_params
{
    int magic;
    int os;                /*1:Linux, 2:winCE*/
    int arch;              /*1:ARM, 2:X86*/
    int type;              /*1:FPGA, 2:DSP, 3:robot */
    int comp;              /*0:not compress, 1: bz2*/
    unsigned int loadaddr; /* loader image to ram ,only run image in uboot*/
    unsigned int runaddr;  /* loader image to ram ,only run image in uboot*/
    unsigned int filesize;
    char sversion[32]; /* software version*/
    char hversion[32]; /* hardware version*/
    char name[32];
    char reserve[128];
} mkheader_params;
#else
    #include "DataType.h"
#endif

#ifndef POS_ITEM
    #define POS_ITEM
typedef struct
{
    int PointNo;
    RobPos mPos;
} POSITEM;
#endif

// IDSTR类型
typedef enum
{
    ValueTypeOther = 0,
    ValueTypeInt = 1,
    ValueTypeDouble = 2,
    ValueTypeString = 3,
    ValueTypeStruct = 4,
    ValueTypeArry = 5,
    ValueTypeBrace = 6,
    ValueTypeCurveParm = 7,
    ValueTypeBool = 8,
    ValueTypeByte = 9,
    ValueTypeFloat = 10,
    ValueTypeSpeed = 11,
} ExpValueType;

// IDSTR类型
typedef enum
{
    ValueToken,
    ValueNumber = 1,  // 数字
    ValueStruct = 2,  // 结构体
    ValueString = 3,  // 简单字符串
    ValueNumberVar = 11,
    ValueStructVar = 12,  // 结构体变量
    ValueStringVar = 13,
    ValueNumberArry0Var = 21,  // 数组单项
    ValueStructArry0Var = 22,  // 数组单项
    ValueStringArry0Var = 23,  // 数组单项
    ValueNumberArry1Var = 31,  // 1维数组
    ValueStructArry1Var = 32,  // 1维数组
    ValueStringArry1Var = 33,  // 1维数组
    ValueNumberArry2Var = 41,  // 2维数组
    ValueStructArry2Var = 42,  // 2维数组
    ValueStringArry2Var = 43,  // 2维数组
    ValueNumberArry3Var = 51,  // 3维数组
    ValueStructArry3Var = 52,  // 3维数组
    ValueStringArry3Var = 53,  // 3维数组
    ValuePalletVar = 66,       // P
    ValuePVar = 67,            // P
    ValuePrVar = 68,           // PR
    ValueComma = 69,           // 逗号表达式
    ValueJPVar = 70,
    ValueToolVar,
    ValueWobjVar,
    ValueLoadDataVar,
    ValueCurveParmVar,
    ValueSpeedVar,
    ValuePIDStr = 100,  // 指针 &
} EXP_VALUEKIND;

// add by brucenie 2022/11/10
typedef enum
{
    eExtExpType_Null = 0x00,
    eExtExpType_ComaExp = 0x01,
    eExtExpType_FuncSingleParaExp = 0x02,
    eExtExpType_FuncMultiParaExt = 0x03,

    eExtExpType_Butt,
} PluginExpType;

typedef enum
{
    INSTP_JOINT = 0,          // 关节（纯运动指令）
    INSTP_LINEAR = 1,         // 直线（纯运动指令）
    INSTP_ARC = 2,            // 圆弧（纯运动指令）
    INSTP_WAIT = 3,           // Wait
    INSTP_SETDO = 4,          // Set（与时间无关的）
    INSTP_JUMP = 5,           // jump（纯运动指令）
    INSTP_DELAY = 7,          // delay
    INSTP_REPEAT = 8,         // 重复运动类型（纯运动指令）
    INSTP_SETOG = 9,          // set og
    INSTP_SETDAOUT = 10,      // set daout
    INSTP_SETADIN = 11,       // set adin  现在没用
    INSTP_PALLETTO = 12,      // pallet to（纯运动指令）
    INSTP_PALLETFROM = 13,    // pallet from（纯运动指令）
    INSTP_REFSYS = 14,        // coord
    INSTP_JUMPL = 17,         // jumpcp（纯运动指令）
    INSTP_ARMCHANGE = 19,     // Arm change（纯运动指令）
    INSTP_PULSE = 20,         // 脉冲
    INSTP_INVERT = 21,        // IO反转
    INSTP_BACKTRACE = 22,     // 轨迹恢复
    INSTP_CUSTOM_FUNC = 23,   // DSP通用接口参数
    INSTP_CUSTOM_MOVE = 24,   // DSP通用接口参数(带点位)
    INSTP_SLVS = 30,          // 自学习振动抑制开关
    INSTP_SLDATA_CLEAR = 31,  // 清除自学习振动抑制数据
    INSTP_DEFAULT = -1
} MotionInstType;
// add end

typedef struct
{
    VAR_KIND mValKind;
    union
    {
        bool bVal;
        unsigned char ucVal;
        int iVal;
        float fVal;
        double dVal;
        char *spValue;
    };
} VAR_VALUE;

typedef struct PALLET_SEND_STR
{
    int isdefined;
    int LayerNum;   // 层数
    int NumPerLay;  // 每层个数
    int IsLabel;    // 标签朝外
    int IsReverse;  // 奇偶层反向
    int ToolNo;
    char PalletName[20];  // 托盘名
    char ModelName[20];   // 垛型名
    double LayerHi;       // 层高
    double ProductLen;    // 货物长
    double ProductWidth;  // 货物高
    double TrayLen;       // 托盘长
    double TrayWidth;     // 托盘高
    double LimitHi;       // 限制高
    double Distance;      // 间距
    double BaseA;         // 原点A的值
} PALLET_SEND;

typedef struct STRUCTVAR_INFO_STR
{
    STRUCT_INFO *pStructInfo;  // 结构体
    void *pStructValue;        // 结构体数据
} STRUCTVAR_INFO;              // 结构体变量存储

typedef struct tagVarArrValue_stu
{
    VAR_KIND VarKind;
    ARR_INFO mArrInfo;
    STRUCT_INFO *pStructInfo;
    void *pValue;
} tagVarArrValue;

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
extern NameSpaceList *g_pNameSpaceList;

// 定义局部变量存储列表，以便从子程序返回时调用
typedef struct STRVAR_INFO_STR
{
    char VarName[MAXTOKENLEN + 1];  // 字符串变量名
    char StrVarValue[BUFLEN];
    struct STRVAR_INFO_STR *pnext;
} STRVAR_INFO;
typedef struct PVAR_INFO_STR
{
    char VarName[11];
    RobPos mPos;
    struct PVAR_INFO_STR *pnext;
} PVAR_INFO;

typedef struct PRVAR_INFO_STR
{
    char VarName[11];
    RobPos mPosData;
    struct PRVAR_INFO_STR *pnext;
} PRVAR_INFO;

typedef struct BVAR_INFO_STR
{
    unsigned char BValue;
    char VarName[11];
    struct BVAR_INFO_STR *pnext;
} BVAR_INFO;
typedef struct DVAR_INFO_STR
{
    char VarName[11];
    struct DVAR_INFO_STR *pnext;
    double DValue;
} DVAR_INFO;
typedef struct RVAR_INFO_STR
{
    char VarName[11];
    int RValue;
    struct RVAR_INFO_STR *pnext;
} RVAR_INFO;

#ifndef DE_TASK_INFO
    #define DE_TASK_INFO
// 工程信息
typedef struct TASK_INFO
{
    unsigned int nError;    // 错误总个数
    unsigned int nFileNum;  // 程序文件数
    unsigned int nStartLine;
} Task_Info;
#endif

typedef struct
{
    int PointKind;  // 点的属性
    int FlagIO;     // IO输出标志
    int IOBinary;   // IO的二进制值
} PortSendData;

typedef struct
{
    char PointFileName[MAX_VARNAME_LEN];
    int PointNum;  // 点的个数
    void *pAddData;
} ExternPVarInfo;

#ifndef _LabelXStru_
typedef struct _LabelXStru_
{
    unsigned int nLabelId;         // 标签号
    unsigned int nAddrId;          // 对应的位、字节、字序号、点位号
    char sLabel[MAX_VARNAME_LEN];  // 首字符不能为数字
    char sDescription[256];        // 描述
} LabelX;

typedef struct _LabelMatchInfoStru_
{
    uint16_t iLabelType;          // 匹配的标签类型
    struct _LabelXStru_ stLabel;  // 匹配的标签结构体信息
} LabelMatchInfo;

typedef enum
{
    LABEL_TYPE_NULL = 0,      // NULL
    LABEL_TYPE_DINBIT = 1,    // InputBitLabels
    LABEL_TYPE_DOUTBIT = 2,   // OutputBitLabels
    LABEL_TYPE_DINBYTE = 3,   // InputByteLabels
    LABEL_TYPE_DOUTBYTE = 4,  // OutputByteLabels
    LABEL_TYPE_DINWORD = 5,   // InputWordLabels
    LABEL_TYPE_DOUTWORD = 6,  // OutputWordLabels
    LABEL_TYPE_AD = 7,        // AdLabels
    LABEL_TYPE_DA = 8,        // DaLabels
    LABEL_TYPE_GP = 9         // GPLabels
} LABEL_TYPE_ENUM;
#endif

// add by brucenie for plugin 20221110
// B LB D LD R LR PR LPR P LP
typedef struct _SystemVariableEnumList
{
    uint32_t u32BVarEnum;
    uint32_t u32LBVarEnum;
    uint32_t u32DVarEnum;
    uint32_t u32LDVarEnum;
    uint32_t u32RVarEnum;
    uint32_t u32LRVarEnum;
    uint32_t u32PRVarEnum;
    uint32_t u32LPRVarEnum;
    uint32_t u32PVarEnum;
    uint32_t u32LPVarEnum;
    uint32_t u32VarEnumReserved[32];
} SystemVariableEnumList;

typedef struct _SystemActionScopInstList
{
    uint32_t u32StartEnum;
    uint32_t u32EndEnum;
    uint32_t u32FuncDefEnum;
    uint32_t u32EndFuncEnum;
    uint32_t u32FuncEnum;
    uint32_t u32ModelFuncEnum;
    uint32_t u32InstEnumReserved[32];
} SystemActionScopInstList;

typedef struct _SystemSpecialInstList
{
    SystemActionScopInstList stActionScopInstList;
    uint32_t u32MotionInstList[256];
} SystemSpecialInstList;

extern void GF_InitialSpecialInstList();

typedef int (*PFunSemanticCheck)(const EXP_NOTE *pExpNode, char *pszErrorChn, char *pszErrorEn);
typedef EXP_NOTE *(*PFunExpParse)(ENUM_TOKEN_TYPE eToken, void *pTransforInfoPass);

typedef int (*PFunExcuteInterface)(int iTaskId, int iLineNo, const STMT_NOTE *pstStmt);
typedef int (*PFunExtractMotionData)(EXP_NOTE *);
typedef int (*PFunTraverseSyntaxTree4Plugin)(int StmtKind, char *pszErrorChn, char *pszErrorEn);
typedef int (*PFunOffsetCalc)(RobPos *posIn, double *prVal, RobPos *posOut);

// add end

// 错误数目
extern int m_ErrorNum;
// 错误信息
extern char *m_ErrorInfo[ERRINFOSIZE];
extern char *m_ErrorInfo_en[ERRINFOSIZE];
extern char *pStrMemErr;
extern char *pStrMemErren;
extern unsigned char *g_pIG_GroupInfo[MAX_IG_VAR_NUM];  // 定义IO数组指针
extern unsigned char *g_pOG_GroupInfo[MAX_IG_VAR_NUM];  // 定义IO数组指针
extern PMEMORYPOOL g_pMemPool;
extern int g_SaveAram;
extern int LanKind;  // 0,中文 1 英文......
void SetLanKind(int lankind);

extern char SendPortBufString[1024];
extern ReasveData g_ReasveData[MAX_SOCKET_NUM + 1];
extern int inTransforEnter;

extern PortGetData g_PortGetData;
extern PortSendData g_PortSendData;
extern char ExeNowPath[LENGTHOFPATH];
extern FILE *g_pPRSource;  // PR变量文件指针
extern FILE *g_pRSource;   // R变量文件指针
extern FILE *g_pBSource;   // B变量文件指针
extern FILE *g_pDSource;   // D变量文件指针
// extern char *pathOfProTmp;
extern int g_bRCTestMode;
// extern FILE *g_pSymTab;//符号表输出文件指针
// extern STMT_NOTE *g_StmtNoteTree;//语法树的头指针
// extern int g_LineNo;//当前的行数
// extern int g_NumOfLine;//文件行数
// extern int g_EchoSource;
// extern int g_ErrorNum;//错误数目
// extern int g_Error;//错误标志
// extern char *g_ErrorInfo[ERRINFOSIZE];//错误信息列表
// extern char *g_ErrorInfo_en[ERRINFOSIZE];//错误信息列表
// extern char g_RunErrorInfo[128];//运行时错误信息列表
// extern char g_RunErrorInfo_en[128];//运行时错误信息列表
// extern int bRunError;//运行错误标志
extern char *pathOfPalletVar;
extern tagXqtTaskInfo *g_pXqtProQue[MAX_TASK_NUM];  // xqt 任务队列
extern char DefaultGPFileName[LENGTHOFPATH];
extern char PFileList[MAX_PFILE_NUM][MAX_FILENAME_LEN];
extern bool g_bLoadPointsInUse;
extern bool g_bNameSpaceListInUse;

#ifndef FOR_CONTROLLER
extern double g_DVar[MAX_R_VAR_NUM];                    // 变量作为全局变量使用
extern unsigned char g_BVar[MAX_B_VAR_NUM];             // 变量作为全局变量使用
extern int g_RVar[MAX_D_VAR_NUM];                       // 变量作为全局变量使用
extern Pose g_PRVar[MAX_PR_VAR_NUM];                    // 变量作为全局变量使用
extern unsigned char pByteVar[MAX_BYTE_VAR_NUM];        // PLC BYTE[256]
extern short pWordVar[MAX_WORD_VAR_NUM];                // INT[256]
extern int pDWordVar[MAX_DWORD_VAR_NUM];                // DINT[256]
extern double pRealVar[MAX_REAL_VAR_NUM];               // LREAL[256]
extern PALLET_INFO *g_pPalletInfo[MAX_PALLET_VAR_NUM];  // 托盘变量
extern char *g_pStrVar[256];
extern RobPos *g_PVar[MAX_P_VAR_NUM];
extern JPos *g_JPVar[MAX_P_VAR_NUM];
extern bool g_PVarDefined[MAX_P_VAR_NUM];
extern bool g_PVarRenew[MAX_P_VAR_NUM];
extern bool g_JPVarDefined[MAX_P_VAR_NUM];
extern ProInfoQueue g_ProQue[MAX_TASK_NUM];  // 工程中程序文件队列
extern ToolData g_ToolParm[MAX_TOOL_NUM];    // ToolParm[MAX_TOOL_NUM]
extern LoadData g_LoadData[MAX_LOAD_NUM];
extern WobjData g_WobjParm[MAX_WOBJ_NUM];  // WobjParm[MAX_WOBJ_NUM];
#else
extern double *g_DVar;                                  // 变量作为全局变量使用
extern unsigned char *g_BVar;                           // 变量作为全局变量使用
extern int *g_RVar;                                     // 变量作为全局变量使用
extern Pose *g_PRVar;                                   // 变量作为全局变量使用
extern unsigned char *pByteVar;                         // PLC BYTE[256]
extern short *pWordVar;                                 // INT[256]
extern int *pDWordVar;                                  // DINT[256]
extern double *pRealVar;                                // LREAL[256]
extern PALLET_INFO *g_pPalletInfo[MAX_PALLET_VAR_NUM];  // 托盘变量
extern PALLET_INFO *g_pPalletInfo[MAX_PALLET_VAR_NUM];  // 工程托盘变量
extern char *g_pStrVar[256];
extern RobPos *g_PVar[MAX_P_VAR_NUM];
extern JPos *g_JPVar[MAX_P_VAR_NUM];
extern bool g_PVarDefined[MAX_P_VAR_NUM];
extern bool g_PVarRenew[MAX_P_VAR_NUM];
extern bool g_JPVarDefined[MAX_P_VAR_NUM];
extern ToolData *g_ToolParm;  // ToolParm[MAX_TOOL_NUM]
extern LoadData *g_LoadData;
extern WobjData *g_WobjParm;  // WobjParm[MAX_WOBJ_NUM];
#endif

extern PROFILE_INFO g_PFileInfo[MAX_PFILE_NUM];
extern PROFILE_INFO g_JPFileInfo;
extern uint64_t g_InValue[4];
extern uint64_t g_OutValue[4];

extern double ex_calMat[MAX_WOBJ_NUM][3][3];
extern WobjData ex_calCarmUserParm[MAX_WOBJ_NUM];  // 相机标定对应的用户坐标系参数
extern double ex_calCarm[MAX_WOBJ_NUM];            // 相机安装方式
extern long int Freememerysize;
extern INTERVAREA ex_IntervArea[8];                 // 干涉区 8；
extern double ex_IntervAreaCopy[8][JPOS_AXIS_NUM];  // 干涉区 8；
extern BUCKET *g_pGlobalVarHashTable[TABSIZE];      // 全局变量的符号表

// 建立一个字符串的拷贝
char *CopyString(Transfor_Stu *pTransforInfo, char *s);
// 功能: 建立一个字符串的拷贝,固定长度
// char * CopyStringC(Transfor_Stu* pTransforInfo,char * s);
char *CopyStringA(char *s);
// 初始化全局变量
void InitGlobalVar();
void InitTaskGlobalVar(Transfor_Stu *pTransforInfo);
void FreeInterpreter(Transfor_Stu *pTransforInfo, STMT_NOTE *pStmtNoteTree);
DLL_API void UpLoadGlobalVar(void);

int SetIO_IN_Value(Transfor_Stu *pTransforInfo, int IONo, uint8_t IOValue);
int GetIO_IN_Value(Transfor_Stu *pTransforInfo, int IONo);
int GetIO_OUT_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUT_Value(Transfor_Stu *pTransforInfo, int IONo, uint8_t IOValue);
int SetIO_INB_Value(Transfor_Stu *pTransforInfo, int IONo, uint8_t IOValue);
int GetIO_INB_Value(Transfor_Stu *pTransforInfo, int IONo);
int GetIO_OUTB_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTB_Value(Transfor_Stu *pTransforInfo, int IONo, uint8_t IOValue);
int SetIO_INW_Value(Transfor_Stu *pTransforInfo, int IONo, uint16_t IOValue);
int GetIO_INW_Value(Transfor_Stu *pTransforInfo, int IONo);
int GetIO_OUTW_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTW_Value(Transfor_Stu *pTransforInfo, int IONo, uint16_t IOValue);
int SetIO_INBINT_Value(Transfor_Stu *pTransforInfo, int IONo, int IOValue);
int GetIO_INBINT_Value(Transfor_Stu *pTransforInfo, int IONo);
int GetIO_OUTBINT_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTBINT_Value(Transfor_Stu *pTransforInfo, int IONo, int IOValue);
int SetIO_INWINT_Value(Transfor_Stu *pTransforInfo, int IONo, int IOValue);
int GetIO_INWINT_Value(Transfor_Stu *pTransforInfo, int IONo);
int GetIO_OUTWINT_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTWINT_Value(Transfor_Stu *pTransforInfo, int IONo, int IOValue);
///////////////////////////////
int SetIO_INBFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo, float IOValue);
float GetIO_INBFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo);
float GetIO_OUTBFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTBFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo, float IOValue);
int SetIO_INWFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo, float IOValue);
float GetIO_INWFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo);
float GetIO_OUTWFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTWFLOAT_Value(Transfor_Stu *pTransforInfo, int IONo, float IOValue);
////////////////////////////////////////////////
int SetIO_INBDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo, double IOValue);
double GetIO_INBDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo);
double GetIO_OUTBDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTBDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo, double IOValue);
int SetIO_INWDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo, double IOValue);
double GetIO_INWDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo);
double GetIO_OUTWDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo);
int SetIO_OUTWDOUBLE_Value(Transfor_Stu *pTransforInfo, int IONo, double IOValue);

////保存全局点位
// void SaveGPVar(char *PathOfGP);
/* 语法树内存释放 */
void FreeSyntaxTree(Transfor_Stu *pTransforInfo, STMT_NOTE *t);
DLL_API int ReadPRVar(void);
DLL_API int ReadRVar(void);
DLL_API int ReadBVar(void);
DLL_API int ReadDVar(void);
DLL_API int ReadStrVar(void);
DLL_API char *GetTokenString(Transfor_Stu *pTransforInfo, ENUM_TOKEN_TYPE token);

DLL_API void ToRad(double RobPos[], int size);
DLL_API void ToAngle(double RobPos[], int size);

DLL_API unsigned char *getBForWatch(void);                              // 一次256个字符
DLL_API char *getRForWatch(int StartNo);                                // 一次128*8个字符
DLL_API char *getDForWatch(int StartNo);                                // 一次64*8个字符
DLL_API void *getPRForWatch(Transfor_Stu *pTransforInfo, int StartNo);  // 一次8*8 + 4*4 + 4 + 4 +4 = 92个字符
// 读取字符流赋值给偏移量
DLL_API void UpdatePRVarData(Transfor_Stu *pTransforInfo, int StartNo, void *p);
DLL_API void UpdateRVarData(int StartNo, char *p);
DLL_API void UpdateBVarData(int StartNo, char *p);
DLL_API void UpdateDVarData(int StartNo, char *p);

// 保存LB变量
DLL_API void UpdateLBVarData(Transfor_Stu *pTransforInfo, int StartNo, char *p);
// 保存LR变量
DLL_API void UpdateLRVarData(Transfor_Stu *pTransforInfo, int StartNo, char *p);
// 保存LD变量
DLL_API void UpdateLDVarData(Transfor_Stu *pTransforInfo, int StartNo, char *p);
// 将LB变量赋值给字符流
DLL_API char *getLBForWatch(Transfor_Stu *pTransforInfo);  // 一次256个字符
// 将LR变量赋值给字符流
DLL_API char *getLRForWatch(Transfor_Stu *pTransforInfo, int StartNo);  // 一次128*8个字符
// 将LD变量赋值给字符流
DLL_API char *getLDForWatch(Transfor_Stu *pTransforInfo, int StartNo);  // 一次64*8个字符
// 检查表达式值的类型
DLL_API int CheckExpValueKind(EXP_NOTE *t);
// 读取全局字符串监控列表的值 1个
DLL_API void *getAStrVarForWatch(int StartNo);
// 设置一个字符串变量 成功返回1，失败返回0
DLL_API int SetAStrVar(int StartNo, char *pChar);
// 与位置变量监控模块交互
// 将符号表中位置变量的值写入文件中
void WritePRForWatch(void);
// 将符号表中R变量的值写入文件中
void WriteRForWatch(void);
// 将符号表中D变量的值写入文件中
void WriteDForWatch(void);
// 将符号表中B变量的值写入文件中
void WriteBForWatch(void);
// 将托盘变量的值写入文件中
void WritePalletForWatch(void);

#ifdef FOR_LINUX
/*! @function
*******************************************************************************************
函数名   : int EncryptProFile(const char *filePathName)
功能     : 加密程序文件
参数     : filePathName 文件
返回值   : 0 成功，1 给定程序文件路径不存在， 2 程序文件加密失败， 3 remove文件失败，4 rename失败
*******************************************************************************************/
int EncryptProFile(const char *filePathName);

/*! @function
*******************************************************************************************
函数名   : int UnEncryptProFile(const char *filePathName)
功能     : 解密程序文件
参数     : filePathName 文件
返回值   : 0 成功，1 给定程序文件路径不存在，2 程序文件解密失败，3 remove文件失败，4 rename失败
******************************************************************************************/
int UnEncryptProFile(const char *filePathName);
#endif
/*! @function
********************************************************************************
<PRE>
函数名   : WriteStrVar()
功能     : 写Str变量
参数     : 无
</PRE>
*******************************************************************************/
DLL_API void WriteStrVar(void);

// 正解函数
void rFkineCalTcp(int nAxis, RobPos mJPosInfo, RobPos *mCPosInfo);
// 逆解函数
// DLL_API int rJogToBase(Transfor_Stu *pTransforInfo,int nAxis, RobPos mJPosInfo, RobPos *mCPosInfo);
// DLL_API int rBaseToJog(Transfor_Stu *pTransforInfo,int nAxis, RobPos mCPosInfo, int armType[4], RobPos *mJPosInfo);
// DLL_API int rUsrCrdtoTool(Transfor_Stu *pTransforInfo,RobPos UsrPosInfo, int UserNo, RobPos* ToolPosInfo);
// DLL_API int rTooltoUsrCrd(Transfor_Stu *pTransforInfo,RobPos ToolPosInfo, int UserNo, RobPos*UsrPosInfo);
// DLL_API int rToolCrdtoBase(Transfor_Stu *pTransforInfo,RobPos ToolPosInfo, int ToolNo, RobPos* BasePosInfo);
// DLL_API int rBasetoToolCrd(Transfor_Stu *pTransforInfo,RobPos BasePosInfo, int ToolNo, RobPos*ToolPosInfo);
// DLL_API int rUsrCrdtoBase(Transfor_Stu *pTransforInfo,RobPos UsrPosInfo, int UserNo, int ToolNo, RobPos* BasePosInfo);
// DLL_API int rBasetoUsrCrd(Transfor_Stu *pTransforInfo,RobPos BasePosInfo, int UserNo, int ToolNo, RobPos*UsrPosInfo);

int CalcOffsetToBase(double *Pos_o, double *Pos_x, double *Pos_y, double dz, double dBase[3]);
int rCalcOffsetToBase(RobPos PosInfo1, RobPos PosInfo2, RobPos PosInfo3, double dz, Pose *PosInfoResult);
DLL_API int rAddDifPos(RobPos PosInfo1, Pose difPos, RobPos *PosInfo2);
DLL_API int rAddDifPosTcp(RobPos PosInfo1, Pose difPos, RobPos *PosInfo2);
// int rPRAlltoToolCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*ToolPosInfo,int ToolNo);
// int rPRAlltoUserCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*UserPosInfo,int UserNo);
// int rPRAlltoJointCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*JointPosInfo);
// int rPRAlltoBaseCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*BasePosInfo);
// DLL_API int rAlltoToolCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*ToolPosInfo,int ToolNo);
// DLL_API int rAlltoUserCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*UserPosInfo,int UserNo);
// DLL_API int rAlltoJointCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*JointPosInfo);
// DLL_API int rAlltoBaseCrd(Transfor_Stu *pTransforInfo,RobPos PosInfo, RobPos*BasePosInfo);
#ifdef FOR_LINUX
// int rVxCalibToTool(Transfor_Stu *pTransforInfo,RobPos PosInfo1,RobPos PosInfo2,RobPos*ToolPosInfo);
#endif
// void rAlltoVxCalibCrd(RobPos PosInfo, RobPos*ToolPosInfo);
void FreeExpList(Transfor_Stu *pTransforInfo, EXP_NOTE *t);
DLL_API ENUM_TOKEN_TYPE GetStmtTokenType(STMT_KIND StmtKind);

#ifdef FOR_WINCE
bool IsDirExits(char *FilePath);
#endif

DLL_API void ClearTransforError(Transfor_Stu *pTransforInfo);
// 得到版崩信息号
DLL_API int get_libTransfor_v(mkheader_params *header);

// 设置内存中点数据的值 成功返回0 失败非0值
DLL_API RobPos *GetLPVarIndexTemp(Transfor_Stu *pTransforInfo, int PosNo);  // 内部调用
// 设置内存中点数据的值 成功返回0 失败非0值
DLL_API int SetLPVarIndexTemp(Transfor_Stu *pTransforInfo, int PosNo, RobPos mPosItem);

// 检查LP序列中的点是否定义
DLL_API int CheckLPArrIsDefined(Transfor_Stu *pTransforInfo, int PosNoStart, int PosNoEnd, int *pPosNoDefNum);
// 检查P序列中的点是否定义
DLL_API int CheckPArrIsDefined(Transfor_Stu *pTransforInfo, int PosNoStart, int PosNoEnd, int *pPosNoDefNum);

// int ReadGolbalPalletPoint(int PalletNo);
// StartNo 取上一页最大的点序号+1；
DLL_API void *getPosForWatch(Transfor_Stu *pTransforInfo, int StartNo[5]);
DLL_API PALLET_INFO *GetPalletInfo(int Index);
DLL_API PALLET_INFO *GetLocalPalletInfo(Transfor_Stu *pTransforInfo, int Index);
DLL_API int CalPalletIndexPoint(RobPos Pos1, RobPos Pos2, RobPos Pos3, int RowIndex, int ColIndex, int LayIndex, PALLET_INFO *mPalletItem, RobPos *PosResult);
DLL_API int CalPalletIndexPoint4(RobPos Pos1, RobPos Pos2, RobPos Pos3, RobPos Pos4, int RowIndex, int ColIndex, int LayIndex, PALLET_INFO *mPalletItem, RobPos *PosResult);

// 查看一个标示符是否是关键字
DLL_API ENUM_TOKEN_TYPE rReservedLookup(Transfor_Stu *pTransforInfo, char *s);

extern FILE *g_fpfile;
extern FILE *pFpWriteFile;
extern unsigned int s_NanID;
/*! @function
********************************************************************************
<PRE>
函数名   : ReLoadPVar()
功能     : 从文件中重新加载P变量
参数     : 无
返回值 ：0 成功 1 错误
</PRE>
*******************************************************************************/
DLL_API int ReLoadPVar(char *PathOfGP);

/*! @function
********************************************************************************
<PRE>
函数名   : ReLoadJPVar(char *PathOfGP)
功能     : 从文件中重新加载JP变量
参数     : 无
返回值 ：0 成功 1 错误
</PRE>
*******************************************************************************/
DLL_API int ReLoadJPVar(char *PathOfGP);
/*! @function
********************************************************************************
<PRE>
函数名   : ReadJPVar(char *PathOfGP)
功能     : 从文件中读取P变量
参数     : 无
返回值 ：0 成功 1 错误
</PRE>
*******************************************************************************/
DLL_API int ReadJPVar(char *PathOfGP);

/*! @function
********************************************************************************
<PRE>
函数名  : ReLoadPNo(char *PathOfGP)
功能    : 从文件中读取P变量下标
参数    : 点文件路径
返回值  ：0 成功 1 错误
</PRE>
*******************************************************************************/
DLL_API int ReLoadPNo(char *PathOfGP);

/*! @function
********************************************************************************
<PRE>
函数名  : ReLoadPNo(char *PathOfGP)
功能    : 从文件中读取P变量下标
参数    : 点文件路径  P变量下标
返回值  ：>0 成功 -1 错误
</PRE>
*******************************************************************************/
DLL_API int PraseAPointNo(char *pSource, int *pPNo);

////Ret指令后，如果进入的是主程序，TransforEnter后设置标志
// DLL_API int SetFlagIfBackToMainProgram(Transfor_Stu*pTransforInfo);

DLL_API VAR_VALUE GetVarValueByName(Transfor_Stu *pTransforInfo, char *pStrVarName);

VAR_VALUE GetVarValueByNameInBucket(Transfor_Stu *pTransforInfo, char *pStrVarName, BUCKET *pHashTable[TABSIZE]);

int m_snprintf(char *OutBuf, int size, const char *format, ...);

int CheckPFileNum(char *PathOfGP, char *FileName);

#ifdef FOR_TEACHBOX_LINUX32
int m_printf(int level, const char *_Format, ...);
int TranslationEntry(char *cpOutBuf, char *cpFormat, ...);
#endif

#ifndef FOR_LINUX
std::wstring ConvertToWideString(const char *pcStr);
int TranslationEntry(char *cpOutBuf, char *cpFormat, ...);
int m_printf(int level, _In_z_ _Printf_format_string_ const char *_Format, ...);
int LogOut(_In_z_ _Printf_format_string_ const char *_Format, ...);
#endif

void ArmLogOutString(Transfor_Stu *pTransforInfo, const char *_Format, ...);

int m_snprintf(char *OutBuf, int size, const char *format, ...);

void ProcessFileEncodingFormat(FILE *file);

#ifndef FOR_LINUX
    #ifndef FOR_WINCE
char *GB2312ToUtf8(const char *gb2312Str);
char *stringToHexChar(const char *input);
    #endif
#endif
#ifdef FOR_CONTROLLER_LINUX32

/*! @function
********************************************************************************
<PRE>
函数名   : ReadBVarFromMRam()
功能     : 从铁电中读取B变量
参数     : 无
返回值 ：1 成功 0 错误
</PRE>
*******************************************************************************/
DLL_API int ReadBVarFromMRam(void);
/*! @function
********************************************************************************
<PRE>
函数名   : ReadRVarFromMRam()
功能     : 从铁电中读取R变量
参数     : 无
返回值 ：1 成功 0 错误
</PRE>
*******************************************************************************/
DLL_API int ReadRVarFromMRam(void);
/*! @function
********************************************************************************
<PRE>
函数名   : ReadDVarFromMRam()
功能     : 从铁电中读取D变量
参数     : 无
返回值 ：1 成功 0 错误
</PRE>
*******************************************************************************/
DLL_API int ReadDVarFromMRam(void);
/*! @function
********************************************************************************
<PRE>
函数名   : ReadPRVarFromMRam()
功能     : 从铁电中读取PR变量
参数     : 无
返回值 ：1 成功 0 错误
</PRE>
*******************************************************************************/
DLL_API int ReadPRVarFromMRam(void);
#endif

int CheckVControlNoSupportToken(int token);
int CheckVControlNoSupportStmtKind(int stmtKind);

// 获取表达式值的类型
DLL_API int GetExpChildNum(Transfor_Stu *pTransforInfo, EXP_NOTE *t);
// 获取表达式值的类型
DLL_API ExpValueType GetExpValueType(Transfor_Stu *pTransforInfo, EXP_NOTE *t);
DLL_API CONST_TYPE GetVarConstType(Transfor_Stu *pTransforInfo, char *pVarName);
/*! @function
********************************************************************************
<PRE>
函数名   : void InitFuncVar(Transfor_Stu *pTransforInfo,FUNC_INFO *pFuncInfo);
功能     : 函数初始化
参数     : 无
</PRE>
*******************************************************************************/
void InitFuncVar(Transfor_Stu *pTransforInfo, FUNC_INFO *pFuncInfo);
/*! @function
********************************************************************************
<PRE>
函数名   : InitModelVar(Transfor_Stu *pTransforInfo,ModelInfoStu *pModelInfo)
功能     : 模块初始化
参数     : 无
</PRE>
*******************************************************************************/
void InitModelVar(Transfor_Stu *pTransforInfo, ModelInfoStu *pModelInfo);
void ClearTaskVar(Transfor_Stu *pTransfor_Stu);
DLL_API void DeleteAllLabelName();
DLL_API void AddALabelNameToList(char *pLabelName, char *pRealName);
DLL_API void AddALabelNameToGlobalSyb(Transfor_Stu *pTransforInfo, char *pLabelName, char *pRealName);

/*! @function
********************************************************************************
<PRE>
函数名   : TransforError(pTransforInfo,char * message, char * message_en,int num)
功能     : 如果出现语法错误,输出错误
参数     :
返回值   : void
</PRE>
*******************************************************************************/
DLL_API int SetRunLineNo(Transfor_Stu *pTransfor_Stu, int LineNo, char *pProPathName);
void TransforError(Transfor_Stu *pTransforInfo, char *message, char *message_en, int num);
void TransforGlobalError(char *message, char *message_en, int num);
// 获取当前模块的模块名
DLL_API char *GetCurProName(Transfor_Stu *pTransforInfo);
char *GetALineStringFromRobotLab();
DLL_API int BackToMainPro(Transfor_Stu *pTransfor_Stu);
// 获取当前任务所有包含的文件模块名 返回值：包含文件的个数
DLL_API int GetAllModelName(Transfor_Stu *pTransforInfo, char StrModelName[MAX_QUE_SIZE][32]);
// 判断当前模块是否在工程内
DLL_API bool IsModelInTask(Transfor_Stu *pTransforInfo, char *pStrModelName);
// 获取栈顶的函数名
DLL_API char *GetTopFuncNameForArm(Transfor_Stu *pTransforInfo);
DLL_API char *GetTopModelNameForArm(Transfor_Stu *pTransforInfo);
// 1是 2 否
DLL_API int IsMotionCmd(ReStmtKind stmtKind);
void LockThread(Transfor_Stu *pTransforInfo);
void UnLockThread(Transfor_Stu *pTransforInfo);
// 解释器模块接口函数
DLL_API INTERPRETER TransforEnterSubProForRobotLab(Transfor_Stu *pTransforInfo, char *source);
void WirteProFileTile(FILE *fpFile);
void ClearXqtTaskInfo();
tagXqtTaskInfo *GetXqtTaskInfo(int TaskNo);
// 输出内存错误信息
void MemeError(Transfor_Stu *pTransforInfo);
// 获取工装测试模式
DLL_API int GetTestMode();
// 设置工装测试模式
DLL_API void SetRCTestMode(int TestMode);

void LockBuildThread();
void UnLockBuildThread();

// 返回点序号 -1 表示失败
DLL_API int PraseAPointString(char *pSource, int *pPNo, RobPos *pPosTemp, char *pLabel);
// 返回点序号 -1 表示失败
DLL_API int PraseAJPString(char *pSource, int *pPNo, JPos *pPosTemp, char *pLabel);

// 输出错误到PC平台
void OutPutErrorInfoToLab(int lineNo, char *strErrorInfo, LABINFO_KIND RobotLabInfoKind);
void OutPutErrorInfoToRobotLab(Transfor_Stu *pTransforInfo, char *proName, int LineNo, char *strErrorInfo, LABINFO_KIND RobotLabInfoKind);
// 清除指定模块内部所有变量的值
DLL_API int ClearModelAllVar(Transfor_Stu *pTransforInfo, ModelInfoStu *pModeInfo);
DLL_API int ClearAllModelVar(Transfor_Stu *pTransforInfo);
/*******************************************************************************
//关节坐标转换成工件坐标(内部调用)
//输入：theJ 关节坐标 td工具参数  wd 工件参数 gload 负载参数
//输出：theP：工件坐标
//返回值：成功返回0  失败返回非0
*******************************************************************************/
DLL_API int JointToWobjPos(Transfor_Stu *pTransforInfo, JPos theJ, ToolData td, WobjData wd, LoadData gload, RobPos *theP);
/*******************************************************************************
//工件坐标换成关节坐标转 内部调用
//输入： theP：工件坐标 td工具参数  wd 工件参数 gload 负载参数
//输出：theJ 关节坐标
//返回值：成功返回0  失败返回非0
*******************************************************************************/
DLL_API int WobjPosToJoint(Transfor_Stu *pTransforInfo, RobPos theP, ToolData td, WobjData wd, LoadData gload, JPos *theJ);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
//计算工件偏移
//输入：posIn 输入点位，prVal 偏移量，tool 工具参数，wobj 工件参数，payload 负载参数
//输出：pPosOut 偏移结果
//返回值：0 表示成功 非0 表示失败
*******************************************************************************/
DLL_API int WobjCoordOffset(Transfor_Stu *pTransforInfo, RobPos posIn, Pose prVal, RobPos *pPosOut);
/*******************************************************************************
//计算工具偏移
//输入：posIn 输入点位，prVal 偏移量，tool 工具参数，wobj 工件参数，payload 负载参数
//输出：pPosOut 偏移结果
//返回值：0 表示成功 非0 表示失败
*******************************************************************************/
DLL_API int ToolCoordOffset(Transfor_Stu *pTransforInfo, RobPos posIn, Pose prVal, RobPos *pPosOut);

// 坐标转换 随动相机坐标系到工具坐标系
DLL_API int rVxCalibOnHandToTool(Transfor_Stu *pTransforInfo, int CamNo, RobPos PosInfo1, JPos CamPosInfo, RobPos *ToolPosInfo);
// 坐标转换 固定相机坐标系到工具坐标系
DLL_API int rVxCalibToHandToTool(Transfor_Stu *pTransforInfo, int CamNo, RobPos PosInfo, RobPos *ToolPosInfo);
RobPos CalcOffsetExp(Transfor_Stu *pTransforInfo, EXP_NOTE *pExpnode, int ToolNo, int WobjNo);
DLL_API int CheckRunInMotionTask(ReStmtKind iStmtKind);
double GetConstExpValue(EXP_NOTE *pExpNote);
DLL_API VAR_KIND GetVarKindByName(Transfor_Stu *pTransforInfo, char *pVarName);
void CheckMovsAndIntCmd(Transfor_Stu *pTransforInfo, STMT_NOTE *t, ReStmtKind iStmtKind);
void InitInstMovsAndIntCmdCount(void);
void InitInterruptCmdCountValue(Transfor_Stu *pTransforInfo);                 /* 初始化中断指令调用个数 */
void AddInterruptCmdCount(Transfor_Stu *pTransforInfo, ReStmtKind iStmtKind); /* 每调用一个中断指令，就自增一次 */
int32_t IsInterruptCmd(uint16_t u16TaskID);                                   /* 是否有中断指令 */
/********************************************************************
 * 功能描述：解析机型名称
 * 输入参数：
 * @ pMachineName
 * 输出参数：
 * @ pJointNum
 * @ pArmLength
 * @ pZMax
 * 返 回 值：0：正常；-1 错误
 * 其他说明：无
 * 修改日期     版本号        修改人         修改内容
 * ------------------------------------------------------------------
 * 20220919    S03.21N94_L0     lzl     创建
 ********************************************************************/
int ParseMachineInfo(const char *pMachineName, uint8_t *pJointNum, uint32_t *pArmLength, uint32_t *pZMax);
// GBK编码转换到UTF8编码
// int GBKToUTF8(char* lpGBKStr, char* lpUTF8Str, int nUTF8StrLen);
#ifdef FOR_LINUX
int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
// UNICODE码转为utf-8码
int g2u(char *inbuf, int inlen, char *outbuf, int outlen);
#endif

// add by brucenie for plugin 20221110
// 注册关键字及关键字及需要的语义检查函数
/**************************************************************
 * Function: interface for regist keyword to compiler module
 * Parameters:
 *     pszKeywordDesc: keyword string description
 *     pfunSemCheck: callback of semantic check for plugin if need or null
 * Return:
 *    0: failure/others: token type (9000 ~ 9512)
 **************************************************************/
DLL_API int CI_RegistKeyword(const char *pszKeywordDesc, PFunSemanticCheck pfunSemCheck, PFunExpParse pfunExpresionParse);

// 反注册关键字
/**************************************************************
 * Function: interface for unregist keyword from compiler module
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: successful/others: failure
 **************************************************************/
DLL_API int CI_UnRegistKeyword(const char *pszKeywordDesc);

// 注册语句（指令/函数）及语句类型、语句执行接口
/**************************************************************
 * Function: interface for regist statement
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: failure/others: statement type(STMT_KIND or ReStmtKind)
 **************************************************************/
DLL_API int CI_RegistStatement(const char *pszKeywordDesc, PluginExpType ePluginExpType, PFunExcuteInterface pfunXqtInterface, int i32InstType);

// 反注册语句
/**************************************************************
 * Function: interface for unregist statement
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: successful/others: failure
 **************************************************************/
DLL_API int CI_UnRegistStatement(const char *pszKeywordDesc);

// 反注册所有关键字及语句
/**************************************************************
 * Function: interface for unregist all statements and keywords
 * Parameters:
 *     none
 * Return:
 *    0: successful/others: failure
 **************************************************************/
DLL_API int CI_UnRegistAll();

// 插件运动指令数据获取
/**************************************************************
 * Function: interface for get motion data for plugin
 * Parameters:
 *     pTransforInfo : Transfor_Stu data
 *     LineNo : current statment line number
 *     pMovData : motion data type for plugin (extension)
 *     pFunExtractMData : callback for extract data
 * Return:
 *    0: successful/others: failure
 **************************************************************/
DLL_API int CI_GetMotionData4Plugin(Transfor_Stu *pTransforInfo, int LineNo, MOVDATA_EXT4PLUGIN *pMovData, PFunExtractMotionData pFunExtractMData, PFunOffsetCalc pFunOffsetCal);

/*! @function
********************************************************************************
函数名   :
功能     : 得到插件运动指令的运动数据，更泛的接口

参数     : 行号
返回值   : 0成功；26存在点位问题（可能是坐标系未给导致），但不报错，由插件自行判断；其他，错误
*******************************************************************************/
DLL_API int CI_GetComMotionData4Plugin(Transfor_Stu *pTransforInfo, int LineNo, MOVDATA_EXT4PLUGIN *pMovData, PFunExtractMotionData pFunExtractMData, PFunOffsetCalc pFunOffsetCal);

DLL_API int CI_GetSystemVariableEnumList(SystemVariableEnumList *pstSysVariableEnumList);

DLL_API EXP_NOTE *CreatNewExpNode(EXP_KIND eExpType, unsigned char u8CheckPara, void *pTransforInfoPass);

DLL_API int CI_RegistTraverseSyntaxTree4Plugin(PFunTraverseSyntaxTree4Plugin pFunTraverseSyntaxTree4Plugin, char pPluginName[32]);

DLL_API int CI_GetSystemSpecialInstList(SystemSpecialInstList *pstSpecialInstList);

// end

#endif
