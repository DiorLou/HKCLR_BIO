// DataConvert.h : 实现文件
//

/*! @file
********************************************************************************
<PRE>
模块名       :
文件名       :
相关文件     : DataConvert.h
文件实现功能 : 数据转换
作者         : xujiangu
版本         : v1.0
--------------------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期         版本        修改人          修改内容
2014/09/10     v1.0          xujiangu           created
</PRE>
********************************************************************************/
#pragma once
#include <string>
#include "DataTypeDef.h"

// 联合体开关
#define USE_UNION 1

// 使用联合体
#if USE_UNION

typedef union
{
    int16u uValue;
    int8u uBuf[2];
} UNION_16U;

typedef union
{
    int32u uValue;
    int8u uBuf[4];
} UNION_32U;

typedef union
{
    int64u uValue;
    int8u uBuf[8];
} UNION_64U;

typedef union
{
    double dbValue;
    int8u uBuf[8];
} UNION_DOUBLE;

#endif

#define BITWISE_NOT(x) (x) = ~(x)

class CDataConvert
{
public:
    CDataConvert(){};
    ~CDataConvert(){};

public:
    static void Data16ToMem(int8u *pBuf, int16u uValue)
    {
#if USE_UNION
        UNION_16U obj;
        obj.uValue = uValue;
        memcpy(pBuf, &obj.uBuf[0], 2);
#else
        pBuf[0] = (uValue & 0xff00) >> 8;
        pBuf[1] = (uValue & 0x00ff);
#endif
    }

    static void Data32ToMem(int8u *pBuf, int32u uValue)
    {
#if USE_UNION
        UNION_32U obj;
        obj.uValue = uValue;
        memcpy(pBuf, &obj.uBuf[0], 4);
#else
        pBuf[0] = (uValue & 0xff000000) >> 24;
        pBuf[1] = (uValue & 0x00ff0000) >> 16;
        pBuf[2] = (uValue & 0x0000ff00) >> 8;
        pBuf[3] = (uValue & 0x000000ff);
#endif
    }

    static void Data64ToMem(int8u *pBuf, int64u uValue)
    {
#if USE_UNION
        UNION_64U obj;
        obj.uValue = uValue;
        memcpy(pBuf, &obj.uBuf[0], 8);
#else
        int8u uBit = 0;       // 需要移动的位数
        int64u uTemp = 0xff;  // 与运算因子

        // 填充BUFFER
        for (int i = 7; i >= 0; i--)
        {
            uBit = (8 * i);
            uTemp = uTemp << uBit;
            pBuf[7 - i] = int8u((uValue & uTemp) >> uBit);

            // 重新赋值
            uTemp = 0xff;
        }
#endif
    }

    static int16u MemToData16(int8u *pBuf)
    {
        int16u uRet = 0;

#if USE_UNION
        UNION_16U obj;
        memcpy(&obj.uBuf[0], pBuf, 2);
        uRet = obj.uValue;
#else
        uRet = pBuf[0] << 8;
        uRet += pBuf[1];
#endif

        return uRet;
    }

    static int32u MemToData32(int8u *pBuf)
    {
        int32u uRet = 0;

#if USE_UNION
        UNION_32U obj;
        memcpy(&obj.uBuf[0], pBuf, 4);
        uRet = obj.uValue;
#else
        uRet = pBuf[0] << 24;
        uRet += pBuf[1] << 16;
        uRet += pBuf[2] << 8;
        uRet += pBuf[3];
#endif

        return uRet;
    }

    static int64u MemToData64(int8u *pBuf)
    {
        int64u uRet = 0;

#if USE_UNION
        UNION_64U obj;
        memcpy(&obj.uBuf[0], pBuf, 8);
        uRet = obj.uValue;
#else
        int64u uTemp = 0;
        int8u uBit = 0;  // 需要移动的位数
        for (int i = 0; i < 8; i++)
        {
            uBit = 8 * (7 - i);
            uTemp = pBuf[i];

            uRet += uTemp << uBit;
        }
#endif

        return uRet;
    }

    // 长整型-->双精度型
    static double Int64uToDouble(int64u uValue)
    {
        int64s sValue = uValue;  // 防止丢失符号
        double dbValue = sValue / 1000000.0;

        return dbValue;
    }

    // 双精度型-->长整型
    static int64u DoubleToInt64u(double dbValue)
    {
        int64s sValue = (int64s)(dbValue * 1000000);
        int64u uValue = sValue;

        return uValue;
    }

    // int8u Buffer-->双精度
    static double MemToDouble(int8u *pBuf)
    {
#if USE_UNION
        UNION_DOUBLE obj;
        memcpy(&obj.uBuf[0], pBuf, 8);

        return obj.dbValue;
#else
        int64u uTemp = MemToData64(pBuf);
        double dbValue = Int64uToDouble(uTemp);

        return dbValue;
#endif
    }

    // 双精度-->int8u Buffer
    static void DoubleToMem(int8u *pBuf, double dbValue)
    {
#if USE_UNION
        UNION_DOUBLE obj;
        obj.dbValue = dbValue;
        memcpy(pBuf, &obj.uBuf[0], 8);
#else
        int64u uTemp = DoubleToInt64u(dbValue);
        Data64ToMem(pBuf, uTemp);
#endif
    }

    // double Buffer 拷贝到 int8u Buffer
    static void MemDoubleToInt8u(const double *pDbBuf, int8u *pIntBuf, int nDbNumb)
    {
        // 填充命令内容
        for (int i = 0; i < nDbNumb; i++)
        {
            int8u *pRecvBuf = pIntBuf + i * 8;
            DoubleToMem(pRecvBuf, pDbBuf[i]);
        }
    }

    // int16u Buffer 拷贝到 int8u Buffer
    static void MemInt16uToInt8u(const int16u *pInt16uBuf, int8u *pInt8uBuf, int nInt16uNumb)
    {
        // 填充命令内容
        for (int i = 0; i < nInt16uNumb; i++)
        {
            int8u *pRecvBuf = pInt8uBuf + i * 2;
            Data16ToMem(pRecvBuf, pInt16uBuf[i]);
        }
    }

    // int8u Buffer 拷贝到 double Buffer
    static void MemInt8uToDouble(int8u *pIntBuf, double *pDbBuf, int nDbNumb)
    {
        for (int i = 0; i < nDbNumb; i++)
        {
            int8u *pRecvBuf = pIntBuf + i * 8;
            pDbBuf[i] = MemToDouble(pRecvBuf);
        }
    }

    // int Bffuer Buffer 拷贝到 int8u Buffer
    static void MemIntToInt8u(const int *pInt, int8u *pInt8u, int nIntNumb)
    {
        for (int i = 0; i < nIntNumb; i++)
        {
            int8u *pRecvBuf = pInt8u + i * 4;
            int32u uTemp = pInt[i];

            Data32ToMem(pRecvBuf, uTemp);
        }
    }

    // int8u Bffuer 拷贝到 int16u Bffuer
    static void MemInt8uToInt16u(int8u *pInt8u, int16u *pInt16u, int nIntNumb)
    {
        for (int i = 0; i < nIntNumb; i++)
        {
            int8u *pRecvBuf = pInt8u + i * 2;
            int16u uTemp = MemToData16(pRecvBuf);

            pInt16u[i] = uTemp;
        }
    }

    // int8u Bffuer 拷贝到 int16s Bffuer
    static void MemInt8uToInt16s(int8u *pInt8u, int16s *pInt16s, int nIntNumb)
    {
        for (int i = 0; i < nIntNumb; i++)
        {
            int8u *pRecvBuf = pInt8u + i * 2;
            int16u uTemp = MemToData16(pRecvBuf);

            pInt16s[i] = uTemp;
        }
    }

    // int8u Bffuer 拷贝到 int Bffuer
    static void MemInt8uToInt(int8u *pInt8u, int *pInt, int nIntNumb)
    {
        for (int i = 0; i < nIntNumb; i++)
        {
            int8u *pRecvBuf = pInt8u + i * 4;
            int32u uTemp = MemToData32(pRecvBuf);

            pInt[i] = uTemp;
        }
    }

    // int8u Bffuer 拷贝到 UINT Bffuer
    static void MemInt8uToUINT(int8u *pInt8u, int32u *pInt, int nIntNumb)
    {
        for (int i = 0; i < nIntNumb; i++)
        {
            int8u *pRecvBuf = pInt8u + i * 4;
            int32u uTemp = MemToData32(pRecvBuf);

            pInt[i] = uTemp;
        }
    }

    static void ConvertData(int8u *u8Buf, int8u len)
    {
        if (u8Buf == NULL)
            return;

        for (int i = 0; i < len; i++)
        {
            BITWISE_NOT(u8Buf[i]);
        }
        return;
    }
};
