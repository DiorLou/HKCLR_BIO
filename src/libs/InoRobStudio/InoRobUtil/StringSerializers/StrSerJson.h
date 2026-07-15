#pragma once
#include <string>
#include "IInoRobUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS StrSerJson
{
public:
    static cJSON *FromStr(const std::string &str);
    static std::string ToStr(const cJSON *obj);
};

}  // namespace InoRobUtil
