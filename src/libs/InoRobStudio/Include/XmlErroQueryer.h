#pragma once
#include "QueryerExGT.h"
#include <vector>
#include "XmlGlobal.h"

typedef struct tagAxisErro
{
    UINT uAxisId;  // 轴号
    UINT uErroId;  // 错误码(0x8N**,用0x81**替代)
} AXIS_ERRO;

class CXmlErroQueryer : public CQueryerExGT
{
public:
    CXmlErroQueryer(void);
    virtual ~CXmlErroQueryer(void);

    // 装载功能点页面文件
    BOOL LoadXmlInfo(CString strFunPagePath);

    // 释放并delete该查询对象
    void ReleaseQueryer();

    // 读取错误码描述
    void ReadErroCodeInfo(std::vector<STRU_LAN_INFO> &vt_SoftLan);

    // 轴错误码
    BOOL IsAxisErroCode(UINT uErroId);

    // 是否多线程错误码
    int IsThreadErroCode(UINT uErroId);

    // 轴错误码转换
    void AxisErroConvert(UINT uErroId, AXIS_ERRO &AxisErro);
};
