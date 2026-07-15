#pragma once

#include <QString>

const char BOOL_REGEX[] = "[01]{0,1}";
const char UCHAR_REGEX[] = "[0-9]{0,4}";
const char INT_REGEX[] = "[-]{0,1}[0-9]*";
const char UINT_REGEX[] = "[0-9]*";
const char DOUBLE_REGEX[] = "[-]{0,1}[0-9]*[\\.]{0,1}[0-9]{0,3}";
const char DOUBLE_REGEX_SIXTH_DECIMAL[] = "[-]{0,1}[0-9]*[\\.]{0,1}[0-9]{0,6}";
const char DOUBLE_REGEX_NO_DECIMAL_LIMIT[] = "[-]{0,1}[0-9]*[\\.]{0,1}[0-9]*";
const char DOUBLE_REGEX_CUSTOM_DECIMAL[] = "[-]{0,1}[0-9]*[\\.]{0,1}[0-9]{0,{$$$}}";
const char CUSTOM_DECIMAL[] = "{$$$}";
const char STRING_REGEX[] = "[a-zA-Z]{1}[a-zA-Z0-9_]*";
const char STRING_REGEX_UNLIMIT[] = "[\\s\\S]{1,256}$";
const char PERCENT_REGEX[] = "[0-9]{0,3}";
const char ALIAS_REGEX[] = "[a-zA-Z]{0,1}[a-zA-Z0-9_]{0,30}";
const char IP_REGEX[] = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";
