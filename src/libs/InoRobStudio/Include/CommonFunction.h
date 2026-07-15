#pragma once
// #include "../src/TeachPendant/TeachPendantMainDlg.h"

#define RELEASE_POINTER(x) \
    {                      \
        if (x != NULL)     \
        {                  \
            delete x;      \
            x = NULL;      \
        }                  \
    }  // 单个对象
#define RELEASE_ARRAY_POINTER(x) \
    {                            \
        if (x != NULL)           \
        {                        \
            delete[] x;          \
            x = NULL;            \
        }                        \
    }  // 数组指针

class CCommonFunction
{
public:
    virtual ~CCommonFunction(void)
    {
    }

    // 获取文件夹
    CString GetRunModuleDir()
    {
        CString strName = GetModulePath("TeachPendant");
        int pos = strName.ReverseFind('\\');
        strName = strName.Left(pos + 1);
        return strName;
    }

    // 获取文件夹
    CString GetModuleDir(CString sModuleName)
    {
        CString strName = GetModulePath(sModuleName);
        int pos = strName.ReverseFind('\\');
        strName = strName.Left(pos + 1);
        return strName;
    }

    // 获取完整路径
    CString GetModulePath(CString sModuleName)
    {
        CString strName;
        HMODULE hmodule;
        hmodule = GetModuleHandle(sModuleName);
        TCHAR name[_MAX_FNAME];
        memset(name, 0, sizeof(name));
        GetModuleFileName(hmodule, name, sizeof(name) / sizeof(TCHAR));
        strName = name;

        return strName;
    }

    // 用图片填充
    void FillWnd(CDC *pDC, CRect rc, int iIdx)
    {
        // SetPaintDC(pDC);
        if (iIdx >= TEACH_BMP_BUTT)
            return;
        if (NULL == g_stLoadBmps[iIdx].pBitMap)
        {
            g_stLoadBmps[iIdx].pBitMap = new CBitmap();
            if (g_stLoadBmps[iIdx].pBitMap)
            {
                CString strBmpPath;
                CCommonFunction CommFunc;
                strBmpPath = CommFunc.GetRunModuleDir() + _T("skin2\\");
                strBmpPath += g_stLoadBmps[iIdx].strBmpName;
                if (false == LoadJPGFromFile(strBmpPath, g_stLoadBmps[iIdx].pBitMap, pDC))
                {
                    delete g_stLoadBmps[iIdx].pBitMap;
                    g_stLoadBmps[iIdx].pBitMap = NULL;
                }
                else
                {
                    BITMAP BmpProp;
                    g_stLoadBmps[iIdx].pBitMap->GetBitmap(&BmpProp);
                    g_stLoadBmps[iIdx].lW = BmpProp.bmWidth;
                    g_stLoadBmps[iIdx].lH = BmpProp.bmHeight;
                }
            }
        }

        if (NULL == g_stLoadBmps[iIdx].pBitMap)
            return;

        CDC dcImage;
        if (!dcImage.CreateCompatibleDC(pDC))
            return;
        CBitmap *pOldBitmap = dcImage.SelectObject(g_stLoadBmps[iIdx].pBitMap);
#if 1
        if (g_stLoadBmps[iIdx].lW <= 0)
            g_stLoadBmps[iIdx].lW = 100;
        int nMod = rc.Width() % g_stLoadBmps[iIdx].lW;
        int nDev = rc.Width() / g_stLoadBmps[iIdx].lW;
        nDev += (nMod > 0) ? 1 : 0;

        int nLeft = rc.left;
        for (int i = 0; i < nDev; i++)
        {
            nLeft = rc.left + i * g_stLoadBmps[iIdx].lW;
            pDC->BitBlt(nLeft, rc.top, g_stLoadBmps[iIdx].lW, rc.Height(), &dcImage, 0, 0, SRCCOPY);
        }
#else
        pDC->StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &dcImage,
                        0, 0, g_stLoadBmps[iIdx].lW, g_stLoadBmps[iIdx].lH, SRCCOPY);
#endif

        dcImage.SelectObject(pOldBitmap);
        dcImage.DeleteDC();

        // Bitmap.DeleteObject();
    }

#if 0
	void FillWnd(CDC* pDC, CRect rc, CString sBMP)
	{
		//if (0)//复制填充
		//{
		//	CDC backBmp;                 
		//	backBmp.CreateCompatibleDC(pDC);  
		//	CBitmap bitmap;  
		//	LoadBMPFromFile(sBMP,&bitmap);

		//	CBrush m_brushBackground; 
		//	m_brushBackground.CreatePatternBrush(&bitmap);    ///创建位图画刷   
		//	CBrush* pOldMemDCBrush = pDC->SelectObject(&m_brushBackground);   
		//	pDC->PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY);  		
		//	pDC->SelectObject(pOldMemDCBrush);  
		//}		
		
		CBitmap Bitmap;  
		bool bRes = LoadBMPFromFile(sBMP,&Bitmap);			
		if (!bRes)
		{
			return;
		}

		CDC dcImage;
		if (!dcImage.CreateCompatibleDC(pDC))
			return;

		BITMAP BmpProp;
		Bitmap.GetBitmap(&BmpProp);

		//保存句柄
		CBitmap* pOldBitmap = dcImage.SelectObject(&Bitmap);

    #if 1  // 复制填充
		int nMod = rc.Width()%BmpProp.bmWidth;
		int nDev = rc.Width()/BmpProp.bmWidth;
		nDev += (nMod > 0)? 1:0;

		int nLeft = rc.left;
		for (int i=0; i<nDev; i++)
		{
			nLeft = rc.left + i*BmpProp.bmWidth;
			pDC->BitBlt(nLeft, rc.top, BmpProp.bmWidth, rc.Height(), &dcImage,0,0,SRCCOPY);
		}

    #else  // 整图拉伸填充
		pDC->StretchBlt(rc.left, rc.top, rc.Width(),rc.Height(),&dcImage,
			0,0, BmpProp.bmWidth, BmpProp.bmHeight,SRCCOPY);
    #endif	

		dcImage.SelectObject(pOldBitmap);
		dcImage.DeleteDC();		
	}
#endif
    // 从文件中获取BMP
    bool LoadJPGFromFile(CString sFile, CBitmap *&pBMP, CDC *pDC)
    {
        if (CBeeCDC::LoadJpgFromFile(sFile, pBMP, pDC) != NULL)
            return true;
        else
            return false;
        return true;
    }
    // 从文件中获取BMP
    bool LoadBMPFromFile(CString sFile, CBitmap *pBMP)
    {
        HBITMAP bitmap = NULL;
#if defined(_WIN32_WCE)
        bitmap = (HBITMAP)::SHLoadDIBitmap(sFile);
#else
        bitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), sFile, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
#endif
        if (NULL == bitmap)
        {
            return false;
        }

        if (bitmap)
        {
            pBMP->Attach(bitmap);
        }
        return true;
    }
};
