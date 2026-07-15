#pragma once
#include "DataTypeDef.h"
#include "Include/IUtil.h"

namespace InoRobUtil
{
template <class Type>
// 用于比较两个数组是否完全相等
bool INOROBUTIL_CLASS CompareArray(Type arry1[], Type arry2[], int n);
bool INOROBUTIL_CLASS CompareArray(int16u *arry1, int16u *arry2, int n);
bool INOROBUTIL_CLASS CompareArray(int8u *arry1, int8u *arry2, int n);

int32u INOROBUTIL_CLASS CalPadding(int32u length, int32u times);

}  // namespace InoRobUtil