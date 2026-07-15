#pragma once
#include "dllspec.h"

//#ifdef INOROBBUSINESSPROXY_EXPORTS
//    #include "../Include/PluginCmdForRobotLab.h"
//#endif  // INOROBPLUGIN_EXPORTS
//#include "../Include/ICommonData.h"
//#include "../Include/TokenEnumType.h"

#include "instruction/CmdForInoRobotLab.h"
#include "../Include/ICommonData.h"

//#if (defined INOROBBUSINESSPROXY_EXPORTS) || (defined PLUGIN_EXPORTS)
namespace InoRobBusinessProxy
{

    #define MAXCHILDREN 3
/*
    // add by brucenie for plugin 20221110
    typedef int (*PFunSemanticCheck)(const EXP_NOTE* pExpNode, char* pszErrorChn, char* pszErrorEn);
    typedef int (*PFunExcuteInterface)(int iTaskId, int iLineNo, const STMT_NOTE* pstStmt);
    //typedef int (*PFunExtractMotionData)(Transfor_Stu *, EXP_NOTE *);
    typedef int (*PFunExtractMotionData)(EXP_NOTE*);
    typedef EXP_NOTE* (*PFunExpParse)(ENUM_TOKEN_TYPE eToken, void* pTransforInfoPass);
    typedef int (*PFunTraverseSyntaxTree4Plugin)(int StmtKind, char* pszErrorChn, char* pszErrorEn);
    // add end
*/

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
INOROBBUSINESSPROXY_CLASS int RegistKeywordAgent(const char *pszKeywordDesc, PFunSemanticCheck pfunSemCheck, PFunExpParse pfunExpresionParse);

// 反注册关键字
/**************************************************************
 * Function: interface for unregist keyword from compiler module
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: successful/others: failure
 **************************************************************/
INOROBBUSINESSPROXY_CLASS int UnRegistKeywordAgent(const char *pszKeywordDesc);

// 注册语句（指令/函数）及语句类型、语句执行接口
/**************************************************************
 * Function: interface for regist statement
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: failure/others: statement type(STMT_KIND or ReStmtKind)
 **************************************************************/
INOROBBUSINESSPROXY_CLASS int RegistStatementAgent(const char *pszKeywordDesc, PluginExpType ePluginExpType, PFunExcuteInterface pfunXqtInterface, int i32InstType);

// 反注册语句
/**************************************************************
 * Function: interface for unregist statement
 * Parameters:
 *     pszKeywordDesc: keyword string description
 * Return:
 *    0: successful/others: failure
 **************************************************************/
INOROBBUSINESSPROXY_CLASS int UnRegistStatementAgent(const char *pszKeywordDesc);

// 反注册所有关键字及语句
/**************************************************************
 * Function: interface for unregist all statements and keywords
 * Parameters:
 *     none
 * Return:
 *    0: successful/others: failure
 **************************************************************/
INOROBBUSINESSPROXY_CLASS int UnRegistAllAgent();

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

INOROBBUSINESSPROXY_CLASS int GetSystemVariableEnumListAgent(SystemVariableEnumList *pstSysVariableEnumList);
INOROBBUSINESSPROXY_CLASS EXP_NOTE *CreatNewExpNodeAgent(EXP_KIND eExpType, unsigned char u8CheckPara, void *pTransforInfoPass);
INOROBBUSINESSPROXY_CLASS int RegistTraverseSyntaxTree4PluginAgent(PFunTraverseSyntaxTree4Plugin pFunTraverseSyntaxTree4Plugin, char pPluginName[32]);
INOROBBUSINESSPROXY_CLASS int GetSystemSpecialInstListAgent(SystemSpecialInstListAgent *pstSpecialInstList);
};  // namespace InoRobBusinessProxy

//#endif