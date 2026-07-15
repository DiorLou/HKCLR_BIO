#pragma once
#include <string>
#include "Include/IUtil.h"
#include "DataTypeDef.h"
#include <vector>
using std::string;
using std::wstring;
using std::vector;

#define S2W(x) InoRobUtil::stringToWString(x)
#define W2S(x) InoRobUtil::wstringToString(x)

namespace InoRobUtil
{

// int to string
string INOROBUTIL_CLASS IntToString(int nIntValue);

// double to string
string INOROBUTIL_CLASS DoubleToString(double dbValue);

// 将double转为string，并保留小数点后n位
// by lcm，2023.04.25
string INOROBUTIL_CLASS DoubleToString(double dbValue, unsigned int decimalNum);

// string to int
int INOROBUTIL_CLASS StringToInt(string str);

// string to double
double INOROBUTIL_CLASS StringToDouble(string str);

// wstring与string转换
wstring INOROBUTIL_CLASS stringToWString(const string &str);
string INOROBUTIL_CLASS wstringToString(const wstring &str);

// 去除字符串左侧空格
string INOROBUTIL_CLASS StringTrimLeft(string str);

// 去除字符串右侧空格
string INOROBUTIL_CLASS StringTrimRight(string str);

// 去除字符串首尾空格
string INOROBUTIL_CLASS StringTrim(string str);

// 字符串使用字符分割
void INOROBUTIL_CLASS StringSplit(const string &str, const char split, vector<string> &res);

// 字符串使用字符串分割
void INOROBUTIL_CLASS StringSplit(const string &str, const string &split, vector<string> &res);

// 字符替换
void INOROBUTIL_CLASS StringReplaceAll(string &str, const char old_char, const char new_char);

// 字符删除
void INOROBUTIL_CLASS stringDeleteAll(string &str, const char del_char);

// 字符截取
string INOROBUTIL_CLASS subString(const string &str, size_t start, size_t length);

// 将字符串转化为大写的
void INOROBUTIL_CLASS StringMakeUpper(string &str);

// 判断字符串中是否包含中文
bool INOROBUTIL_CLASS IsContainsChinese(const std::string &str);

// 获取UTF-8编码下的字符个数
int INOROBUTIL_CLASS getUtf8LetterNumber(const std::string &str);
/**
 * @brief 检查名称/变量名是否合法
 * @param errMsg 输出，错误信息
 * @param name 输入，名称
 * @param maxLength 输入，长度限制
 * @return true:合法 false:不合法
 */
bool INOROBUTIL_CLASS isNameValid(std::string &errMsg, const std::string &name, int maxLength);

// 名称只能以字母开头，且仅由数字、字母和下划线组成
bool INOROBUTIL_CLASS isNameOnlyNumLetterUnderline(const std::string &str);

// 判断字符串是否为纯数字文本
bool INOROBUTIL_CLASS isNumber(const std::string &str);

/**
 * @brief 检查字符串的文本编码格式
 * @param str 输入，需要检查的字符串
 * @return true-是UTF-8，false-不是UTF-8
 */
bool INOROBUTIL_CLASS isUTF8(const string &str);

/// <summary>
/// 文本编码格式转换
/// </summary>
/// <param name="src">输入，原文本</param>
/// <param name="toEncoding">输入，目标编码格式</param>
/// <param name="fromEncoding">输入，原编码格式</param>
/// <returns>转换成目标编码格式的文本</returns>
string INOROBUTIL_CLASS convertBetween(const string &src, const string &toEncoding, const string &fromEncoding);
/**
 * @brief 文本编码格式转换
 * @param src 原文本
 * @param toEncoding 目标编码格式
 * @param fromEncoding 原编码格式
 * @return 转换成目标编码格式的文本
 */
string INOROBUTIL_CLASS convertBetween2(const string &src, const string &toEncoding, const string &fromEncoding);

/**
 * @brief 检测文本编码格式
 * @param src 原文本
 * @return 编码格式
 */
string INOROBUTIL_CLASS detectEncoding(const std::string& src);

/**
 * @brief 获取系统文本编码格式
 * @return 编码格式
 */
string INOROBUTIL_CLASS getSystemEncoding();

/**
 * @brief 文本编码格式转换
 * @param src 原文本
 * @return 转换成目标编码格式的文本
 */
string INOROBUTIL_CLASS convertSystemEncoding(const string &src);

/**
 * @brief 文件内容编码格式转换
 * @param content 转换后文件内容
 * @param fileName 文件名
 * @param desEncoding 目标编码格式
 * @param srcEncoding 源编码格式
 * @return true成功 false失败
 */
bool INOROBUTIL_CLASS fileEncodingFormatConvert(std::string &content, const std::string &fileName, const std::string &desEncoding, const std::string &srcEncoding);

/**
 * @brief 文件内容编码格式转换
 * @param content 转换后文件内容
 * @param fileName 文件名
 * @param desEncoding 目标编码格式
 * @param srcEncoding 源编码格式
 * @return true成功 false失败
 */
bool INOROBUTIL_CLASS fileEncodingFormatConvert(std::string &content, const std::string &fileName, const std::string &desEncoding, const std::string &srcEncoding);

// 将字符串拷贝到指定地址中
bool INOROBUTIL_CLASS copyStringToAddress(const std::string &in, int8u *out, int maxLengeh);

// ANSI - UTF8
bool INOROBUTIL_CLASS AnsiToUtf8(const char *ansiStr, string &utf8Str);
bool INOROBUTIL_CLASS Utf8ToAnsi(const char *utf8Str, string &ansiStr);
// Unicode - Utf8
bool INOROBUTIL_CLASS UnicodeToUtf8(const wchar_t *inUnicodeStr, string &outUtf8Str);
bool INOROBUTIL_CLASS Utf8ToUnicode(const char *inUtf8Str, wstring &outUnicodeStr);
// Unicode - Ansi
bool INOROBUTIL_CLASS UnicodeToAnsi(const wchar_t *inUnicodeStr, string &outAnsiString);
bool INOROBUTIL_CLASS AnsiToUnicode(const char *inAnsiStr, wstring &outUnicodeStr);

int INOROBUTIL_CLASS Replace_wstring(std::wstring &strContent, std::wstring strReplace, std::wstring wstringStr);

int INOROBUTIL_CLASS replace_string(std::string &strContent, std::string strReplace, std::string stringStr);

// 批量替换
void INOROBUTIL_CLASS ReplaceAll(string &str, const string &findStr, const string &replaceStr);
void INOROBUTIL_CLASS ReplaceAllW(wstring &str, const wstring &findStr, const wstring &replaceStr);

bool INOROBUTIL_CLASS EndsWith(const std::string &str, const std::string &key);

}  // namespace InoRobUtil
