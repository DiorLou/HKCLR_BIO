#pragma once
#include <vector>
#include <string>
#include "DataTypeDef.h"
#include "instruction/EnumListForRobLab.h"
#include "instruction/GlobalsData.h"
using namespace std;

typedef struct STMT_NOTE_STR_AGENT
{
    int LineNo;    // 行号
    int FlagMovc;  // 圆弧段号标志 1为第一段 2为第二段 10 EOffsOn 11 EOffsOn 为第一段 12 EOffsOn为第二段
    STMT_KIND StmtKind;
    struct STMT_NOTE_STR *pStmtNoteChild[3];  // 子节点
    struct STMT_NOTE_STR *pStmtNoteFather;    // 父节点
    struct STMT_NOTE_STR *pStmtNoteNext;      // 下一节点
    struct STMT_NOTE_STR *pStmtNotePre;       // 上一节点
    EXP_NOTE *pExpNoteList;                   // 表达式
} STMT_NOTE_AGENT;

typedef struct _SystemActionScopInstListAgent
{
    uint32_t u32StartEnum;
    uint32_t u32EndEnum;
    uint32_t u32FuncDefEnum;
    uint32_t u32EndFuncEnum;
    uint32_t u32FuncEnum;
    uint32_t u32ModelFuncEnum;
    uint32_t u32InstEnumReserved[32];
} SystemActionScopInstListAgent;

typedef struct _SystemSpecialInstListAgent
{
    SystemActionScopInstListAgent stActionScopInstList;
    uint32_t u32MotionInstList[256];
} SystemSpecialInstListAgent;
