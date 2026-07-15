#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../../InoRobBusiness/Project/IProject.h"
#include "../../third_party/include/instruction/CmdForInoRobotLab.h"

class CInterpreter
{
public:
    CInterpreter();
    ~CInterpreter();

    // 单例
    static CInterpreter *Inst();

    // 依赖注入
    void setProject(InoRobBusiness::IProject *pProject);

    static void MSetProLineTempList(std::vector<std::string> proList);
    static void MPraseTempFileStart();
    // 将元素加入到不同的 Vector
    static int MOnAddAStringToTable(TABELNAME tabelName, char *pString, char *pNotes);
    static int MAddAVarToTable(char *pstrVarName, int varType, int varKind, int varRange, ARR_INFO *pArrInfo);
    static int MAddALineVarToTable(char *pstrVarName, int varType);

    static void MOnClearLineVarTable();
    // 清除存储元素的对象
    static void MOnClearTable(TABELNAME tabelName);

    // 查询结构体的信息回调;
    static void MOnAddStructInfo(char *name, int varType);

    // 获取文件基本信息的回调
    static void MOnAddProFileInfo(char *pModelName, char *pVersionInfo, char *pModefyTime, char *pRobotName, int bOK);

    static bool MOnIsModeNameInProject(char *pMebName);

// #ifdef _WIN32
//     static int MOnOutPutError(char *proName, int LineNo, std::wstring strErrorInfo, LABINFO_KIND infoKind);  // 编译时输出错误
//     static int MOnTranslateLanguag(std::wstring &wstrChinese, std::wstring &wstrothaerLanguage);
// #else
    static int MOnOutPutError(char *proName, int LineNo, char *strErrorInfo, LABINFO_KIND infoKind);
    static int MOnTranslateLanguag(char *wstrChinese, char *wstrOtherLanguage);
//#endif

    static std::vector<StrInfo> GetKeywordsInfo();

    /**
     * @brief 控制下一次是否打印编译信息
     * @param isPrint
     */
    void setPrintSwitch(bool isPrint);
    bool getPrintSwitch();

    // 判断模块名是否存在
#ifdef TRANSFOR_WIN32

    static void MReg_RobotLab_AddAStringToTable();

    static void MReg_RobotLab_AddAVarToTable();

    static void MReg_RobotLab_AddALineVarToTable();

    static void MReg_RobotLab_OutPutError();

    static void MReg_RobotLab_ClearTable();

    static void MReg_RobotLab_AutoParserLineCallBack();

    static void MReg_RobotLab_PraseTempFileStart();

    static void MReg_RobotLab_IsModeNameInProject();

    static void MReg_RobotLab_AddProFileInfo();

    static void MReg_RobotLab_AddStructInfo();

    static void MReg_RobotLab_TranslateLanguage();

#endif  // TRANSFOR_WIN32

    static bool MIsArryVar(std::string strVarName, ARR_INFO &OutPutArrInfo);

    static void MOnAutoParserLineCallBack();
    static char *MGetALineStringCallBack();
    static void MPraseTempFileStartCallBack();

public:
    // 注册回调函数
    static void RegesiterCallBack();

    std::vector<VarInLineInfo_stu> m_LineVarInfo;  // 选中行的变量信息
    // 关键字
    std::vector<StrInfo> m_KeyWords;

    std::vector<std::string> m_VarName;        // 所有变量的名字
    std::vector<std::string> m_VarLocalName;   // 局部变量名
    std::vector<std::string> m_VarModelName;   // 模块变量名
    std::vector<std::string> m_VarGlobalName;  // 全局变量名
    // 字符串变量名
    std::vector<std::string> m_VarStringName;
    // Bool变量名
    std::vector<std::string> m_VarBoolName;
    // Byte变量名
    std::vector<std::string> m_VarByteName;
    // Int变量名
    std::vector<std::string> m_VarIntName;
    // Float变量名
    std::vector<std::string> m_VarFloatName;
    // double变量名
    std::vector<std::string> m_VarDoubleName;
    // 结构体变量名
    std::vector<std::string> m_VarStructName;
    // 结构体名
    std::vector<std::string> m_StructName;
    // 模块名
    std::vector<std::string> m_ModelName;
    // Speed名
    std::vector<std::string> m_SpeedName;
    // 数组信息
    std::vector<ArrayVarInfo_stu> m_VarArrayName;
    // 方法
    std::vector<SyntaxInfo> m_FunInfos;
    // 成员
    std::vector<std::string> m_Mebs;

    std::vector<SyntaxInfo> m_MebFunInfos;
    // 结构体
    map<std::string, int> m_StructInfo;
    // 程序信息
    std::vector<std::string> m_ProgLines;
    // 曲线组
    std::vector<SyntaxInfo> m_CurveInfos;
    // Curve变量名
    std::vector<std::string> m_VarCurveName;
    // fileHandle
    std::vector<std::string> m_fileHandle;
    // fileDirHandle
    std::vector<std::string> m_fileDirHandle;
    int m_CurParseLine;

private:
    typedef int (*_RobotLab_OutPutError)(char *proName, int LineNo, char *strErrorInfo, LABINFO_KIND RobotLabInfoKind);

    typedef int (*_RobotLab_AddAStringToTable)(TABELNAME tabelName, char *pString, char *pNotes);

    typedef int (*_RobotLab_AddAVarToTable)(char *pstrVarName, int varType, int varKind, int varRange, ARR_INFO *pArrInfo);

    typedef int (*_RobotLab_AddALineVarToTable)(char *pstrVarName, int varType);

    typedef void (*_RobotLab_ClearTable)(TABELNAME tabelName);

    typedef char *(*_RobotLab_GetALineString)();

    typedef void (*_RobotLab_AddStructInfo)(char *pMebname, int varType);

    typedef void (*_RobotLab_AddProFileInfo)(char *pModelName, char *pVersionInfo, char *pModefyTime, char *pRobotName, int bOK);

    typedef void (*_RobotLab_PraseTempFileStart)();

    bool IsExistInVector(std::vector<std::string> strVec, std::string strTaget);
    bool IsArrayNameExistInVector(std::vector<ArrayVarInfo_stu> varArrayName, std::string strTaget);
    bool IsNameExistInLineVector(std::vector<VarInLineInfo_stu> varName, std::string strTaget);

    void AddStringAndNotes(TABELNAME tabelName, std::string strString, std::string strNotes);
    void AddAVarToTable(std::string strVarName, int varType, int varKind, int varRange, ARR_INFO *pArrInfo);
    void AddALineVarToTable(std::string strVarName, int varKind);
    void AddInfosFun(std::vector<SyntaxInfo> &infos, std::string strString, std::string strNotes);
    void AddInfosCurve(std::vector<SyntaxInfo> &infos, std::string strString, std::string strNotes);
    bool IsExistTagetKeyFun(const std::vector<SyntaxInfo> &infos, std::string key);
    bool IsExistTagetKeyCurve(const std::vector<SyntaxInfo> &infos, std::string key);
    void OutPutError(std::string strError, std::string strProName, LABINFO_KIND infoKind, int LineNo);

    bool IsArryVar(std::string strVarName, ARR_INFO &OutPutArrInfo);
    // 清除存储数据的对象
    void OnClearTable(TABELNAME tabelName);

    void OnClearLineVarTable();

    // 添加自定义结构体
    void OnAddStructInfo(char *name, int varType);

    void SetProLineTempList(std::vector<std::string> proList);

    void PraseTempFileStart();

    char *GetALineStringCallBack();

    InoRobBusiness::IProject *_pProject = nullptr;
    bool _isPrintMsg = true;  // 是否打印编译结果信息
};
