/********************************************************************
 *@file   		文件名
 *@brief  		字符转换类
 *				详细描述
 *@note  		备注
 *@warning  		注意事项
 *@author 		梁和兵
 *@date 			2013-08-23
 *@version 		版本 1.0.0
 *@since 		修改说明
 ********************************************************************/

#pragma once
#include <stdlib.h>
#include <cstring>
#include <string>
#include <locale.h>

#pragma warning(disable : 4996)

enum
{
    MAX_STRBUF_LEN = 4 * 1024
};

class CConvert
{
public:
    CConvert(){};
    ~CConvert(){};

    /***********************************************************************/
    /*char转string*/
    /***********************************************************************/

    static std::string char2str(char *arr, int count)
    {
        return std::string(arr, count);
    }

#if 0
	std::string CConvert::char2str(char *arr,int count)
	{
		std::string result(arr,count);
		return result;
	}
#endif

    /***********************************************************************/
    /*16进制字符转10进制*/
    /***********************************************************************/

    static int Hex2Dec(std::string strHex)
    {
        const char *s = strHex.c_str();
        int i, m, temp = 0, n;
        m = strlen(s);  // 十六进制是按字符串传进来的，所以要获得他的长度
        for (i = 0; i < m; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'F')  // 十六进制还要判断他是不是在A-F或者a-f之间a=10
                n = s[i] - 'A' + 10;
            else if (s[i] >= 'a' && s[i] <= 'f')
                n = s[i] - 'a' + 10;
            else
                n = s[i] - '0';
            temp = temp * 16 + n;
        }
        return temp;
    }
};
