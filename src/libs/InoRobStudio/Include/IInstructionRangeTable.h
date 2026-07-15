#pragma once

#include "dllspec.h"

typedef enum
{
    TINTEGER,
    TDOUBLE
} DATATYPE;

typedef union
{
    int nData;
    double fData;
} UnionData;

// 指令中各参数或参数下标范围
typedef struct
{
    CString sKey;  // 关键字
    DATATYPE type;
    UnionData min;
    UnionData max;
} tagInstructionRange;

class XMLQUERYER_CLASS IInstructionRangeTable
{
public:
    IInstructionRangeTable(void);
    virtual ~IInstructionRangeTable(void);

    // 从XML文件中获取对应变量的取值范围
    bool FindInstructionRange(LPCTSTR sxml, LPCTSTR sKey, tagInstructionRange &range);

private:
    bool HasDecimalPoint(CString str);
    void Assign(CString sMin, CString sMax, tagInstructionRange &range);
};
