#ifndef CMD_FOR_INOROBOTLAB_H
#define CMD_FOR_INOROBOTLAB_H

// #include "CommonData.h"
#include "EnumListForRobLab.h"
#include "GlobalsData.h"

#include <string>

DLL_API PraseALineInfo *PraseACmdStringLineDegree(char *cmdstring);
DLL_API int SetRunLineNoForLab(int LineNo, char *pProPathName);
DLL_API int BackToMainProForLab();
// 程序工程编译
DLL_API bool PraseProject(char *pathname[MAX_TASK_NUM], Project_Info *pProjectInfo);
// 程序单个文件编译
DLL_API bool PraseAProgram(char *pathname, PraseInfo *pPraseInfo);
// 文档中临时程序文件编译
DLL_API bool PraseProgramTempForRobotLab(char *source);
DLL_API unsigned int GetReservedWordsNum();
DLL_API bool PraseInistal();
DLL_API void SetRobotNameForLab(int AxisNo, char *pRobotName);
DLL_API void PraseDebugClose();
DLL_API void PraseReInistal();

// 程序工程编译
// DLL_API bool SetRobotParm(int RtTypeNo, double RtPara[8],double RtParaComp[16],char *pStrRobotName);
// DLL_API void SetCompParam(double RtParaComp[16]);

DLL_API ARR_INFO GetVarArrInfoForRobotLab(char *pStrVarName);
DLL_API int GetVarTypeForRobotLab(char *pStrVarName);
DLL_API void UpdateStructInfoForRobotLab(char *pStrVarName);
DLL_API char *GetFuncNameByLineNoForTeachLab(char *pModelName, int LineNo);
DLL_API void UpdateVarListForRobotLab(char *pModelName, int LineNo, bool bUpdate);
DLL_API int UpdateKeyWord();
DLL_API int UpdateMebListForRobotLab(char *pStrName);
// 获取一行指令的所有变量的信息
DLL_API int UpdateALineVarInfo(int TaskNo, char *pProPathName, int LineNo);

typedef int (*_RobotLab_OutPutError)(char *proName, int LineNo, char *strErrorInfo, LABINFO_KIND RobotLabInfoKind);
typedef int (*_RobotLab_AddAStringToTable)(TABELNAME tabelName, char *pString, char *pNotes);
typedef int (*_RobotLab_AddAVarToTable)(char *pstrVarName, int varType, int varKind, int varRange, ARR_INFO *pArrInfo);
typedef int (*_RobotLab_AddALineVarToTable)(char *pstrVarName, int varType);
typedef void (*_RobotLab_ClearTable)(TABELNAME tabelName);
typedef char *(*_RobotLab_GetALineString)();
typedef void (*_RobotLab_PraseTempFileStart)();
typedef void (*_RobotLab_AddStructInfo)(char *pMebname, int varType);
typedef void (*_RobotLab_AddProFileInfo)(char *pModelName, char *pVersionInfo, char *pModefyTime, char *pRobotName, int bOK);
typedef bool (*_RobotLab_IsModeNameInProject)(char *pMebname);

extern _RobotLab_AddALineVarToTable pFun_RobotLab_AddALineVarToTable;
extern _RobotLab_AddAVarToTable pFun_RobotLab_AddAVarToTable;
extern _RobotLab_AddAStringToTable pFun_RobotLab_AddAStringToTable;
extern _RobotLab_OutPutError pFun_RobotLab_OutPutError;
extern _RobotLab_ClearTable pFun_RobotLab_ClearTable;
extern _RobotLab_GetALineString pFun_RobotLab_GetALineString;
extern _RobotLab_AddStructInfo pFun_RobotLab_AddStructInfo;
extern _RobotLab_AddProFileInfo pFun_RobotLab_AddProFileInfo;
extern _RobotLab_PraseTempFileStart pFun_RobotLab_PraseTempFileStart;
extern _RobotLab_IsModeNameInProject pFun_RobotLab_IsModeNameInProject;

#ifdef _WIN32
typedef int (*_RobotLab_TranslateLanguage)(std::wstring &wstrChinese, std::wstring &wstrothaerLanguage);
#else
typedef int (*_RobotLab_TranslateLanguage)(char *wstrChinese, char *wstrOtherLanguage);
#endif

DLL_API void Reg_RobotLab_AddALineVarToTable(_RobotLab_AddALineVarToTable pFunc);
DLL_API void Reg_RobotLab_AddAVarToTable(_RobotLab_AddAVarToTable pFunc);
DLL_API void Reg_RobotLab_AddAStringToTable(_RobotLab_AddAStringToTable pFunc);
DLL_API void Reg_RobotLab_OutPutError(_RobotLab_OutPutError pFunc);
DLL_API void Reg_RobotLab_ClearTable(_RobotLab_ClearTable pFunc);
DLL_API void Reg_RobotLab_GetALineString(_RobotLab_GetALineString pFunc);
DLL_API void Reg_RobotLab_AddStructInfo(_RobotLab_AddStructInfo pFunc);
DLL_API void Reg_RobotLab_AddProFileInfo(_RobotLab_AddProFileInfo pFunc);
DLL_API void Reg_RobotLab_PraseTempFileStart(_RobotLab_PraseTempFileStart pFunc);
DLL_API void Reg_RobotLab_IsModeNameInProject(_RobotLab_IsModeNameInProject pFunc);
DLL_API void Reg_RobotLab_TranslateLanguage(_RobotLab_TranslateLanguage pFunc);

DLL_API void AddALabelNameToListForRobotLab(char *pLabelName, char *pRealName);
DLL_API void AddAllLabelNameToGlobalSybForLab();
DLL_API void DeleteAllLabelNameForRobotLab();
DLL_API int ReLoadPVarForRobotLab(char *PathOfGP);
DLL_API int ReLoadJPVarForRobotLab(char *PathOfGP);
DLL_API int IsCanSetRunLineNo(char *pModelName, int LineNo);
DLL_API int IsCanSetDebugLineNo(char *pModelName, int LineNo);
// 获取当前任务所有包含的文件模块名
DLL_API int GetAllModelNameForRobotLab(char StrModelName[MAX_QUE_SIZE][32]);
// 判断当前模块是否在解释器中已经编译
DLL_API bool IsModelInTransfor(char *pStrModelName);

int AddALineVarToTable(char *pstrVarName, int varType);
int AddAVarToTable(char *pstrVarName, int varType, int varKind, int varRange, ARR_INFO *pArrInfo);
int AddAStringToTable(TABELNAME tabelName, char *pString, char *pNotes);
// 获取变量作用域 0 全局 1 模块 2 局部变量
DLL_API int GetVarScopeForRobotLab(char *pStrVarName);
DLL_API ValueKind GetVarValueKindAndRangeForRobotLab(char *pStrVarName, double range[2]);
DLL_API char *GetXqtTaskEntryNameForLab(int TaskNo);
DLL_API char *GetACmdStringKindKeyWordForRobotLab(char *cmdstring);
// 获取某一个任务对应的所有程序名，不带路径以及后缀 并且有内存分配，外面注意释放内存
// pProName[i]只要不为空就需要释放内存
DLL_API int GetTaskAllProName(int TaskNo, char *pProName[MAX_QUE_SIZE]);
DLL_API int GetAllFuncNameInModel(char *pModelName);
DLL_API void FreeMemoryToLab(void *p);
DLL_API int GetNowSelectFunStartEndLine(char *pModelName, int LineNo, int *p_iStartLine, int *p_iEndLine);
// 返回Curve函数的个数
DLL_API int GetAllCurveFuncNameInModel(char *pModelName);
DLL_API void FreeMemoryToLab(void *p);
DLL_API int GetNowSelectFunStartEndLine(char *pModelName, int LineNo, int *p_iStartLine, int *p_iEndLine);
DLL_API void PraseReInit();
DLL_API int GetModelAndFuncLineNo(char *pNowModelName, int LineNo, char *pJumpedModelName, int *pJumpedLineNo);
DLL_API int MatchRobotNameForRobotLab(char *pRobotName);
DLL_API void SetRCTestModeForLab(int TestMode);
DLL_API void GetPointFromLineCmdForRobotLab(char *pNowModelName, int LineNo, bool *isCanGetPoint, int *pointType, int *pointNo, int *wobjNo, int *toolNo);
// 获取模块行数
DLL_API void GetLineNumFromModeNameForRobotLab(char *pNowModelName, int *LineNum, bool *isCanGetLineNum);
// 获取点位信息,调点优化
DLL_API void GetPotFromLineUseInAdjustOptForRobotLab(char *pNowModelName, int LineNo, bool *isCanGetPoint, int *pointType, int *pointLeftNo, int *pointRightNo, int *wobjNo, int *toolNo);

// 设置轴数
DLL_API void SetAxisNumForRobotLab(int AxisNum);
DLL_API char *GetTokenStringForRobotLab(ENUM_TOKEN_TYPE token);
DLL_API int IsKeyWardForRobotLab(char *str);
DLL_API STMT_NOTE *CmdStringLineToStmtNoteForRobotLab(char *CmdString);
DLL_API ENUM_TOKEN_TYPE GetStmtTokenType(STMT_KIND StmtKind);
DLL_API int FTGetErrorNum(void);  // 得到某一行错误数目
DLL_API char *CaclStringExpForLab(EXP_NOTE *pExpnode);
DLL_API void StrInsertToSybForRobotLab(char *name, char *StrValue);
// 重命名变量名
DLL_API void StrReNameToSybForRobotLab(char *Oldname, char *Newname, char *NewStrValue);
// 查看一个标示符是否是关键字
DLL_API ENUM_TOKEN_TYPE rReservedLookupForRobotLab(char *s);
DLL_API char *FTGetErrorInfo(int No, int LanKind);  // 得到指令序号的错误信息
void TransforErrorForLab(char *message, char *message_en, int num);
DLL_API bool IsNeedPraseProgram(char *pModelName);
DLL_API bool IsLoadPointsInPrj();

// 工艺插件
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
/*! @function
********************************************************************************
<PRE>
函数名   : IsTransforWorking(void)
功能     : 提供给上位机是否正在译码
参数     :
返回值   : true,正在译码；false空闲
</PRE>
*******************************************************************************/
DLL_API bool IsTransforWorking();

// add by brucenie for plugin 20221110
typedef int (*PFunSemanticCheck)(const EXP_NOTE *pExpNode, char *pszErrorChn, char *pszErrorEn);
typedef int (*PFunExcuteInterface)(int iTaskId, int iLineNo, const STMT_NOTE *pstStmt);
// typedef int (*PFunExtractMotionData)(Transfor_Stu *, EXP_NOTE *);
typedef int (*PFunExtractMotionData)(EXP_NOTE *);
typedef EXP_NOTE *(*PFunExpParse)(ENUM_TOKEN_TYPE eToken, void *pTransforInfoPass);
typedef int (*PFunTraverseSyntaxTree4Plugin)(int StmtKind, char *pszErrorChn, char *pszErrorEn);

// add end

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

DLL_API int CI_GetSystemVariableEnumList(SystemVariableEnumList *pstSysVariableEnumList);
DLL_API EXP_NOTE *CreatNewExpNode(EXP_KIND eExpType, unsigned char u8CheckPara, void *pTransforInfoPass);
DLL_API int CI_RegistTraverseSyntaxTree4Plugin(PFunTraverseSyntaxTree4Plugin pFunTraverseSyntaxTree4Plugin, char pPluginName[32]);
DLL_API int CI_GetSystemSpecialInstList(SystemSpecialInstList *pstSpecialInstList);
#endif
