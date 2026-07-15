/*************************************************************************
 *	Copyright (C), 2012-2013 inovance. Co., Ltd. All rights
 *	reserved.
 *	File Name:	QueryerEx.h
 *	Author:		majun
 *	Description:
        interface for the CQueryerEx class.
 *	Version:	1.0
 *	Date:		2013-01-01
*************************************************************************/

#if _MSC_VER > 1000
    #pragma once
#endif  // _MSC_VER > 1000

// #include "GCMGlobals.h"
// #import "msxml2.dll"  //导入动态库，装了IE5就有
#include "msxml2.h"

class CQueryerEx
{
public:
    CQueryerEx();
    virtual ~CQueryerEx();

public:
    BOOL LoadBuffer(LPCTSTR lpszXMLBuffer);
    BOOL GetDOMNodeAttrValue(IXMLDOMNode *pNode, UINT *nValue);
    BOOL GetDOMNodeTextByNode(IXMLDOMNode *pNode,
                              CString &strValue);
    BOOL GetDOMNodeNameByNode(IXMLDOMNode *pNode,
                              CString &strName);
    BOOL GetDOMNodeByName(LPCTSTR lpszName, IXMLDOMNode **pNode);
    virtual BOOL Save(LPCTSTR lpszDocName);
    BOOL Load(LPCTSTR lpszDocName);
    virtual BOOL DestroyQueryer();
    BOOL CreateQueryer();
    BOOL SetNodeTextByName(LPCTSTR lpszName,
                           LPCTSTR lpszValue,
                           LPCTSTR lpszParent);
    BOOL GetNodeTextByName(IXMLDOMNode *pParent,
                           LPCTSTR lpszName,
                           CString &strValue);
    BOOL GetNodeTextByName(IXMLDOMNode *pParent,
                           LPCTSTR lpszName,
                           UINT &nValue);
    BOOL GetNodeTextByNameID(IXMLDOMNode *pParent,
                             LPCTSTR lpszName,
                             LPCTSTR lpszTitle,
                             UINT nID,
                             CString &nValue);
    BOOL GetNodeTextByNameID(IXMLDOMNode *pParent,
                             LPCTSTR lpszName,
                             LPCTSTR lpszTitle,
                             UINT nID,
                             UINT &nValue);
    /*virtual BOOL GetListTextByName(CString strName, CStringList& listValue);
    virtual BOOL SetDocHeader(CString strName, CString strValue);*/
protected:
    /*IXMLDOMDocument2*/ IXMLDOMDocument *m_pXMLDoc;
};

// #endif // !defined(AFX_QUERYERPROJ_H__D1655F8D_27A5_4BED_8F53_FE76C8A5D46B__INCLUDED_)
