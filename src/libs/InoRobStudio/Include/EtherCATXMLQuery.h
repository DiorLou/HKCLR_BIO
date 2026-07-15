// 功能: 从EtherCAT标准xml文件中读取厂家功能码参数
// 版本: V1.0
// 时间: 2015/1/23
#pragma once
#include <math.h>
#include "dllspec.h"
#include "ServoFunctionCodeType.h"
#include "XmlQueryer.h"

class XMLQUERYER_CLASS CEtherCATXMLQuery
{
public:
    CEtherCATXMLQuery(void);
    virtual ~CEtherCATXMLQuery(void);

    void SetXMLPath(CString sPath);
    bool GetAllFunCode(vector<tagServoFunGroup> &vGroup);

private:
    bool IsVendorObject(CString sName);  // 是否是厂家功能码段0x20段
    bool GetChildNode(CQueryerExGT &query, IXMLDOMNode *pParent, CString sNodeName, IXMLDOMNode *&pChild);
    bool GetChildNodeText(CQueryerExGT &query, IXMLDOMNode *pParent, CString sNodeName, CString &sText);
    bool FindSpecifiedDType(CQueryerExGT &query, CString sDType, IXMLDOMNodeList *&pNodeList);
    bool FindSpecifiedObject(CQueryerExGT &query, IXMLDOMNode *pObj, IXMLDOMNodeList *&pNodeList);
    unsigned int ConvertGroupNOToInt(CString sGroupNO);

    bool GetGroupNO(CQueryerExGT &query, IXMLDOMNode *pParent, unsigned int &uGNO);
    bool GetDefaultAccess(CQueryerExGT &query, IXMLDOMNode *pObj, CString &sDefaultAccess);
    bool GetFunCode(CQueryerExGT &query, IXMLDOMNode *pDTNode, IXMLDOMNode *pObjNode, CString sDefaultAccess, tagServoFunCode &funcode);
    bool GetFunCodeVector(CQueryerExGT &query, IXMLDOMNodeList *pDTNodeList, IXMLDOMNodeList *pObjNodeList, CString sDefaultAccess, vServoFunCode &vFunCode);
    bool GetFromDType(CQueryerExGT &query, IXMLDOMNode *pSub, CString sDefaultAccess, tagServoFunCode &funcode);
    void ExplainType(CString sType, tagServoFunCode &funcode);
    bool GetFromObject(CQueryerExGT &query, IXMLDOMNode *pSub, tagServoFunCode &funcode);

    void InitServoFunCode(tagServoFunCode &funCode);

private:
    CString m_sXMLPath;
};