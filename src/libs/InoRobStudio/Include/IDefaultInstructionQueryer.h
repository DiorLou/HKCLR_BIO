#pragma once
#include <vector>
using std::vector;
#include "dllspec.h"

class CQueryerExGT;

// XML中指令的结构
typedef struct
{
    CString sCMD;                    // 指令名称
    CString sInstruction;            // 指令内容
    vector<CString> vFillParameter;  // 指令内的填充字符
} tagDefaultInstruction;

class XMLQUERYER_CLASS IDefaultInstructionQueryer
{
public:
    IDefaultInstructionQueryer(void);
    virtual ~IDefaultInstructionQueryer(void);

    // 根据默认指令文件（XML格式）、指令名称，获取指令结构。
    bool FindDefaultInstruction(LPCTSTR sxml, LPCTSTR sCMD, tagDefaultInstruction &instruction);

private:
    void GetFillParameter(CQueryerExGT &queryer, void *pNode, CString sAttr, vector<CString> &vFillParameter);
};
