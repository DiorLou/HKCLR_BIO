#pragma once
#include <string>
#include "IInoRobUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS StrSerHex
{
public:
    static unsigned int FromStr(std::string hexStr);
    static std::string ToStr(unsigned int data);

private:
    static unsigned int Char2Int(char ch);
    static unsigned int Hex2Dec(char *hex);
};
}  // namespace InoRobUtil
