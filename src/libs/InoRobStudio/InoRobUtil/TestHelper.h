#pragma once
#include "Include/IUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS CTestHelper
{
public:
    CTestHelper();
    ~CTestHelper();

    /*
     * 获取某个整数的阶乘
     * 参数一：整数 n
     * 返回：整数 n 的阶乘
     */
    int Factorial(int n);

    /*
     * 判断某个数是否是质数
     * 参数一：某个数 n
     * 返回：是否是质数，是返回 True； 否返回 False
     */
    bool IsPrime(int n);
};

}  // namespace InoRobUtil
