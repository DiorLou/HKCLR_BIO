/*! @file
********************************************************************************
<PRE>
模块名       : 解释器
文件名       : GlobalsData.h
相关文件     : <与此文件相关的其它文件>
文件实现功能 : 定义双方都需要导出的结构体以及枚举
作者         : llw
版本         : v2.0
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
</PRE>
*******************************************************************************/
#pragma once

#ifndef FOR_LINUX
// #define FOR_LINUX
#endif

#ifndef FOR_TEACHBOX
    #define FOR_TEACHBOX
#endif

#ifndef DEBUG_TRANSFOR
// #define DEBUG_TRANSFOR
#endif

#define USE_VAR_COPY

#ifdef _WIN32_WCE
    #define FOR_WINCE
#endif

#ifdef FOR_WINCE
    #define _WIN32_WINNT 0x0502
    // #define _AFXDLL
    #include <afx.h>
#endif

#ifndef __linux__
    #ifndef FOR_WINCE
        #include <cstdint>
    #else
        #ifndef int8_t
            #define int8_t char
        #endif
        #ifndef int16_t
            #define int16_t short
        #endif
        #ifndef int32_t
            #define int32_t int
        #endif
        #ifndef int64_t
            #define int64_t long long int
        #endif
        #ifndef uint8_t
            #define uint8_t unsigned char
        #endif
        #ifndef uint16_t
            #define uint16_t unsigned short
        #endif
        #ifndef uint32_t
            #define uint32_t unsigned int
        #endif
        #ifndef uint64_t
            #define uint64_t unsigned long long int
        #endif
    #endif
#endif

#ifdef _WIN32
    #ifdef GLOBALSDATA_EXPORTS
        #define DLL_API extern "C" __declspec(dllexport)
    #else
        #define DLL_API __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define DLL_API extern "C"
    #define _DEBUG  1
#endif  // _WIN32

#include "GlobalDataTypes.h"
#include "EnumListForRobLab.h"
// typedef enum
//{
//     MAXRESERVED = 1000,
// } ENUM_TOKEN_TYPE;
// typedef enum
//{
//     EndK = 1000
// } STMT_KIND;

#define MAX_TASK_NUM      16
#define ALLOWRUNVERSIONNO 3022
#define MAX_QUE_SIZE      256
#define MAXCHILDREN       3
/* 路径信息长度 */
#define LENGTHOFPATH    256
#define LENGTHOFPRONAME 256

#define MAX_D_VALUE (1.79E+308)
#define MIN_D_VALUE (-1.79E+308)
#define MAX_R_VALUE MAX_INT_VALUE
#define MIN_R_VALUE MIN_INT_VALUE
#ifndef PI
    #define PI 3.141592653589
#endif

// IDSTR类型
typedef enum
{
    IDString,       // 简单字符串、
    IDStringVar,    // 字符串变量
    IDBvar,         // B变量
    IDRvar,         // R变量
    IDDvar,         // D变量
    IDLBvar,        // LB变量
    IDLRvar,        // LR变量
    IDLDvar,        // LD变量
    IDPRvar,        // PR变量
    IDLPRvar,       // 局部PR变量
    IDPRvarmeb,     // PR变量成员变量
    IDLPRvarmeb,    // 局部PR变量成员变量
    IDPvar,         // 全局P变量
    IDPvarmeb,      // P变量成员变量
    IDJPvar,        // JPVar
    IDJPvarmeb,     // JP变量成员变量
    IDLPvar,        // GP变量
    IDLPvarmeb,     // GP变量成员变量
    IDFilename,     // 文件名
    IDGStringVar,   // 全局字符串变量
    IDBoolVar,      // Bool 类型变量
    IDByteVar,      // Byte类型变量
    IDIntVar,       // int 类型变量
    IDFileHandleVar,// filehandle 类型变量
    IDFileDirHandleVar,// filedirHandle 类型变量
    IDFloatVar,     // Float类型变量
    IDDoubleVar,    // double 类型变量
    IDSpeedVar,     // Speed类型变量
    IDSpeedVarmeb,  // Speed类型变量成员
    IDMebBit,
    IDMebInt,
    IDMebFloat,
    IDMebDouble,
    IDFunName,     // 函数名
    IDMacDefName,  // 宏定义名
    IDModelName,   // 模块名
    IDStructName,  // 结构体名
    IDStructVar,   // 结构体变量名
    IDCurveParmVar,//CurveParm变量名
    IDTrapName, // 回调变量名
    // 以下供示教器使用
    IDINVar = 100,
    IDOUTVar,
    IDINBVar,
    IDOUTBVar,
    IDINWVar,
    IDOUTWVar,
    IDIGVar,
    IDOGVar,
    IDToolVar,
    IDWobjVar,
    IDToolVarmeb,
    IDWobjVarmeb,
    IDLoadVar,
    IDLoadVarMeb
} IDSTR_KIND;

typedef struct ARR_INFO_STR
{
    int RowNum;
    int ColNo[3];  // 每一行的列数,最大支持3行
} ARR_INFO;

// 表达式的属性
typedef struct EXP_ATTR_STR
{
    ENUM_TOKEN_TYPE eOP;
    IDSTR_KIND mStrKind;
    char *szName;
    struct EXP_NOTE_STR *pExpCld;
    union
    {
        int nVal;
        double fVal;
    };
} EXP_ATTR;

// 表达式类型
typedef enum
{
    EXPCOMA,         // 逗号表达式
    OP,              // 复合型表达式
    IDSTR,           // 变量名/标签名等
    VARTOKEN,        // 带下标的表达式
    TOKEN,           // 关键字
    INUM,            // 整型数值
    DNUM,            // 浮点型数值
    EXPASSIGN,       // 赋值表达式
    PIDSTR,          // 指针
    VARARR,          // 数组
    IDSTU,           // 结构体
    IDSTUARR,        // 结构体数组前缀
    EXPBRACE,        // 大括号表达式
    VARTOKENSTUMEB,  // P PR 后缀
    EXPFUNC,
    EXPMODELNAME,
} EXP_KIND;

// 表达式的属性
/////////////////////////////////////////////////////////////////////////////////
/*
可考虑把ExpAttr作为指针，当ExpKind为EXPCOMA，OP，VARTOKEN，TOKEN，EXPASSIGN的时候不需要EXP_ATTR属性
*/
/////////////////////////////////////////////////////////////////////////////////
typedef struct EXP_NOTE_STR
{
    EXP_KIND ExpKind;                   // 表达式的类型
    struct EXP_NOTE_STR *pExpNoteNext;  // 下一节点
    // struct EXP_NOTE_STR *pExpNotePre;//上一节点
    struct EXP_NOTE_STR *pExpNoteChild[MAXCHILDREN];  // 子节点
    struct EXP_NOTE_STR *pExpNoteFather;              // 子节点
    EXP_ATTR ExpAttr;                                 // 表达式的属性
} EXP_NOTE;
// 语句及语法树结构体
typedef struct STMT_NOTE_STR
{
    int LineNo;    // 行号
    int FlagMovc;  // 圆弧段号标志 1为第一段 2为第二段 10 EOffsOn 11 EOffsOn 为第一段 12 EOffsOn为第二段
    STMT_KIND StmtKind;
    struct STMT_NOTE_STR *pStmtNoteChild[3];  // 子节点
    struct STMT_NOTE_STR *pStmtNoteFather;    // 父节点
    struct STMT_NOTE_STR *pStmtNoteNext;      // 下一节点
    struct STMT_NOTE_STR *pStmtNotePre;       // 上一节点
    EXP_NOTE *pExpNoteList;                   // 表达式
} STMT_NOTE;

struct VarInfoA
{
    char cVarName[256];  // 变量、函数、模块、结构体名字
    int VarKind;
};
struct VarInLine
{
    int varNum;
    VarInfoA *pVarInfoArr[10];
};

typedef struct PRASEALINE_INFO
{
    unsigned int iErrorNum;  // 错误数目
    int iNowLineDegreeNum;   // 当前行 -1 回退 0 不变 1 缩进
    int iNextLineDegreeNum;  // 下一行 -1 回退 0 不变 1 缩进
    StringKind eStrKind;
    char *cName;  // 变量、函数、模块、结构体名字
} PraseALineInfo;

// 工程信息
typedef struct PROJECT_INFO
{
    unsigned int iErrorNum;  // 错误总个数
    unsigned int iProNum;    // 程序文件数
    char prjFileName[32];    // 工程配置prj文件名称
} Project_Info;

typedef struct MOV_STMT_INFO_STR
{
    int MoveKind;  // 运动类型 0 MOVJ  ; 1 MOVL;  2 MOVC, 3 JUMP
    int CmdKind;   // 指令形式 0 P[***]；  1 OFFSET(PE,PR***)；2 OFFSET(PE,X,Y,Z,A,B,C)；3 OFFSET(P[***],PR***)；4 OFFSET(P[***],X,Y,Z,A,B,C); 5 PORT  ; 6 PALLET 7 LPALLET
    int GPKind;    // P 0 ENUM_LP 1 PE 2
    EXP_NOTE *PRValueNo;
    EXP_NOTE *ExpPointNo;
    EXP_NOTE *ExpVel;       // 运动速度百分比
    EXP_NOTE *ExpZone;      // 精度
    EXP_NOTE *ExpAccTime;   // 加速时间 0无加速时间参数
    EXP_NOTE *ExpToolNo;    // 工具号
    EXP_NOTE *ExpUserNo;    // 工具号
    EXP_NOTE *ExpNWait;     // NWAIT标志。0 无  1 有
    EXP_NOTE *ExpUntil;     // 运动传感指令标志 0 无，1 有
    EXP_NOTE *ExpIONo;      // 运动传感指令IO名
    EXP_NOTE *ExpIOValue;   // 运动传感指令IO的值
    EXP_NOTE *ExpLH;        // jump LH 参数
    EXP_NOTE *ExpMH;        // jump MH 参数
    EXP_NOTE *ExpPL;        // jump MH 参数
    EXP_NOTE *ExpRH;        // jump RH 参数
    EXP_NOTE *ExpTPNo;      // PALLET NO
    EXP_NOTE *ExpTP1;       // PALLET i
    EXP_NOTE *ExpTP2;       // PALLET j
    EXP_NOTE *ExpTP3;       // PALLET k
    EXP_NOTE *ExpRepeat;    // 精度
    EXP_NOTE *ExpOutIO[3];  // 精度
    RobPos PRVarData;       // 平移变量数据
    RobPos *PointData;      // 点变量数据
    EXP_NOTE *ExpDec;       // 减速度
} MOV_STMT_INFO;

typedef struct PRASE_INFO
{
    unsigned int iErrorNum;  // 是否有语法报错
    unsigned int iLineNum;   // 程序总行数
} PraseInfo;

struct ArrayVarInfo_stu
{
    int kind;
    std::string m_varName;
    ARR_INFO m_arrInfo;
};

struct VarInLineInfo_stu
{
    std::string m_varName;
    int VarKind;  // 变量类型
};

typedef struct
{
    std::string SyntaxTip;
    std::string Annotation;
} TipInfo;

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
    std::string strName;
    StringKind eStringKind;
} StrInfo;

typedef struct
{
    // 关键字信息
    StrInfo Keyword;
    // 提示信息
    std::vector<TipInfo> Tipinfo;
    /// 语法片段提示
    std::vector<std::string> Snippets;

} SyntaxInfo;
