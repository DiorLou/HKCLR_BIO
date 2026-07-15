#pragma once

#include <QString>
#include <QStringList>
#include <QSet>
#include "instance.h"

#define XML_EXP_IS_IN_Range(res, exp,errorList)             \
    QMetaObject::invokeMethod(                              \
        Instance::logicalExpressKeyBoardPropertySource(),   \
        "expressIsValid",                                   \
        Qt::DirectConnection,                               \
        Q_RETURN_ARG(bool, res),                            \
        Q_ARG(const QString&, exp),                         \
        Q_ARG(QList<TypeCheckError>*, errorList)            \
        )

const char KEYBOARD_TYPE[] = "Imt";
const char PROMPT_SOURCE_PROPERTY[] = "PdsSpecial";
const char PROMPT_SOURCE_FROM_STR_PROPERTY[] = "PdsString";
const char HEX_INPUT_ENABLE[] = "HexInput";
const char PROPERTY_SELECTMODE[] = "SelectMode";
const char PROPERTY_NUMBER_SHOW_COMMA[] = "ShowComma";
const char SELECTMODE_ONLYNUMBER[] = "OnlyNumber";
const char SELECTMODE_ONLYLABEL[] = "OnlyLabel";
const char SELECTMODE_NO_CONTAINS_LIST[] = "NotContainsStrInList";


inline const QString PREFIX_USER = "User";
inline const QString PREFIX_TOOL = "Tool";
inline const QString PREFIX_MODBUS = "Modbus";
inline const QString PREFIX_PLC = "PLC";

inline const QString PREFIX_B = "V_B";
inline const QString PREFIX_R = "V_R";
inline const QString PREFIX_D = "V_D";
inline const QString PREFIX_P = "V_P";
inline const QString PREFIX_JP = "V_JP";
inline const QString PREFIX_STR = "V_Str";
inline const QString PREFIX_U_STR = "U_Str";
inline const QString SPECIAL_P_POINT_PE = "PE";

inline const QString PREFIX_COMMON = "Common";
inline const QString PREFIX_STANDARD = "Standard";
inline const QString PREFIX_FIELDBUS = "FieldBus";
inline const QString PREFIX_MEMORY = "Memory";
inline const QString PREFIX_CONTROLLER = "Controller";

inline const QString PREFIX_BIT = "Bit";
inline const QString PREFIX_BYTE = "Byte";
inline const QString PREFIX_WORD = "Word";

inline const QString PREFIX_AD = "AD";
inline const QString PREFIX_DA = "DA";
inline const QString PREFIX_INPUT = "Input";
inline const QString PREFIX_OUTPUT = "Output";
inline const QString PREFIX_SYSTEMIN = "SystemIN";
inline const QString PREFIX_SYSTEMOUT = "SystemOut";
inline const QString PREFIX_BOOL = "BOOL";

inline const QString LOCAL_B = "L_B";
inline const QString LOCAL_R = "L_R";
inline const QString LOCAL_D = "L_D";
inline const QString LOCAL_Int = "L_Int";
inline const QString LOCAL_Double = "L_Double";
inline const QString LOCAL_P = "L_P";
inline const QString LOCAL_JP = "L_JP";
inline const QString LOCAL_STR = "L_Str";
inline const QString LOCAL_ARRAY = "L_Array";
inline const QString LOCAL_ARRAY_INT = "L_ArrayInt";
inline const QString LOCAL_ARRAY_DOUBLE = "L_ArrayDouble";
inline const QString LOCAL_ARRAY_STR = "L_ArrayStr";
inline const QString LOCAL_ARRAY_P = "L_ArrayP";
inline const QString LOCAL_ARRAY_JP = "L_ArrayJP";


inline const QString INDEX_LEFT = "(";
inline const QString INDEX_RIGHT = ")";
inline const QString SIGN_RANGE_LINK = "~";
inline const QString SIGN_PREFIX_LINK = "_";
inline const QString SIGN_SUB = "–";
inline const QString SIGN_Negative = "-";
inline const QString SIGN_SPLIT = " ";
inline const QString SIGN_SEMICOLON = ";";
inline const QString SIGN_COLON = ":";
inline const QString SIGN_COMMA = ",";
inline const QString SIGN_PIPE = "|";
inline const QString SIGN_PARAMS_SPLIT = ",";


inline const QString SHOW_SIGN = INDEX_LEFT + INDEX_RIGHT;
inline const QString MATCH_ANY_WORDS = "(\\(.*?\\))";

const int INDEX_LEFT_SIZE = INDEX_LEFT.size();
const int INDEX_RIGHT_SIZE = INDEX_RIGHT.size();
const int SIGN_SPLIT_SIZE = SIGN_SPLIT.size();

const QHash<QString, QString> HashSpecialVarAndVarNamePrefix = {
    {SPECIAL_P_POINT_PE, PREFIX_P}};

const QHash<QString, QString> HashSpecialVarAndExp = {
    {SPECIAL_P_POINT_PE, "CurPos()"}};

inline QString createPrefix(QString ioType, QString inOrOut, QString sizeType)
{
    return ioType + "_" + inOrOut + "_" + sizeType;
}

inline QString createSingleExp(QString prefix, QString suffix)
{
    return prefix + "(" + suffix + ")";
}

inline QString createSpecialExp(const QString suffix)
{
    QString exp = QString();

    if (HashSpecialVarAndExp.contains(suffix)) {
        exp = HashSpecialVarAndExp.value(suffix);
    }

    return exp;
}

inline QString processSuffixIsNum(const QString suffix)
{
    bool ok = false;
    suffix.toDouble(&ok);
    return ok ? suffix : "\"" + suffix + "\"";
}

inline bool splitPrefix(QString str, QString &ioType, QString &inOrOut, QString &sizeType)
{
    QStringList after = str.split("_");
    if (after.size() == 3) {
        ioType = after[0];
        inOrOut = after[1];
        sizeType = after[2];
        return true;
    }
    return false;
}

inline bool getSingleExpPreAndSuffix(const QString &in, QString &prefix, QString &suffix)
{
    int start = in.indexOf(INDEX_LEFT);
    int end = in.indexOf(INDEX_RIGHT);
    if (start != -1 && end != -1) {
        prefix = in.mid(0, start);
        suffix = in.mid(start + 1, end - start - 1);
        return true;
    } else {
        return false;
    }
}

inline bool isSpecialLabel(QString prefix, QString suffix)
{
    bool bRet = false;
    if (HashSpecialVarAndVarNamePrefix.contains(suffix)) {
        bRet = (!HashSpecialVarAndVarNamePrefix.value(suffix).compare(prefix));
    }

    return bRet;
}

inline const QString PREFIX_INPUT_COMMON_BIT = createPrefix(PREFIX_COMMON, PREFIX_INPUT, PREFIX_BIT);
inline const QString PREFIX_INPUT_STANDARD_BIT = createPrefix(PREFIX_STANDARD, PREFIX_INPUT, PREFIX_BIT);
inline const QString PREFIX_INPUT_FIELDBUS_BIT = createPrefix(PREFIX_FIELDBUS, PREFIX_INPUT, PREFIX_BIT);
inline const QString PREFIX_INPUT_MEMORY_BIT = createPrefix(PREFIX_MEMORY, PREFIX_INPUT, PREFIX_BIT);
inline const QString PREFIX_INPUT_TOOL_BIT = createPrefix(PREFIX_TOOL, PREFIX_INPUT, PREFIX_BIT);

inline const QString PREFIX_OUTPUT_COMMON_BIT = createPrefix(PREFIX_COMMON, PREFIX_OUTPUT, PREFIX_BIT);
inline const QString PREFIX_OUTPUT_STANDARD_BIT = createPrefix(PREFIX_STANDARD, PREFIX_OUTPUT, PREFIX_BIT);
inline const QString PREFIX_OUTPUT_FIELDBUS_BIT = createPrefix(PREFIX_FIELDBUS, PREFIX_OUTPUT, PREFIX_BIT);
inline const QString PREFIX_OUTPUT_MEMORY_BIT = createPrefix(PREFIX_MEMORY, PREFIX_OUTPUT, PREFIX_BIT);
inline const QString PREFIX_OUTPUT_TOOL_BIT = createPrefix(PREFIX_TOOL, PREFIX_OUTPUT, PREFIX_BIT);

inline const QString PREFIX_INPUT_COMMON_BYTE = createPrefix(PREFIX_COMMON, PREFIX_INPUT, PREFIX_BYTE);
inline const QString PREFIX_INPUT_STANDARD_BYTE = createPrefix(PREFIX_STANDARD, PREFIX_INPUT, PREFIX_BYTE);
inline const QString PREFIX_INPUT_FIELDBUS_BYTE = createPrefix(PREFIX_FIELDBUS, PREFIX_INPUT, PREFIX_BYTE);
inline const QString PREFIX_INPUT_MEMORY_BYTE = createPrefix(PREFIX_MEMORY, PREFIX_INPUT, PREFIX_BYTE);
inline const QString PREFIX_INPUT_TOOL_BYTE = createPrefix(PREFIX_TOOL, PREFIX_INPUT, PREFIX_BYTE);

inline const QString PREFIX_OUTPUT_COMMON_BYTE = createPrefix(PREFIX_COMMON, PREFIX_OUTPUT, PREFIX_BYTE);
inline const QString PREFIX_OUTPUT_STANDARD_BYTE = createPrefix(PREFIX_STANDARD, PREFIX_OUTPUT, PREFIX_BYTE);
inline const QString PREFIX_OUTPUT_FIELDBUS_BYTE = createPrefix(PREFIX_FIELDBUS, PREFIX_OUTPUT, PREFIX_BYTE);
inline const QString PREFIX_OUTPUT_MEMORY_BYTE = createPrefix(PREFIX_MEMORY, PREFIX_OUTPUT, PREFIX_BYTE);
inline const QString PREFIX_OUTPUT_TOOL_BYTE = createPrefix(PREFIX_TOOL, PREFIX_OUTPUT, PREFIX_BYTE);

inline const QString PREFIX_INPUT_COMMON_WORD = createPrefix(PREFIX_COMMON, PREFIX_INPUT, PREFIX_WORD);
inline const QString PREFIX_INPUT_STANDARD_WORD = createPrefix(PREFIX_STANDARD, PREFIX_INPUT, PREFIX_WORD);
inline const QString PREFIX_INPUT_FIELDBUS_WORD = createPrefix(PREFIX_FIELDBUS, PREFIX_INPUT, PREFIX_WORD);
inline const QString PREFIX_INPUT_MEMORY_WORD = createPrefix(PREFIX_MEMORY, PREFIX_INPUT, PREFIX_WORD);
inline const QString PREFIX_INPUT_TOOL_WORD = createPrefix(PREFIX_TOOL, PREFIX_INPUT, PREFIX_WORD);

inline const QString PREFIX_OUTPUT_COMMON_WORD = createPrefix(PREFIX_COMMON, PREFIX_OUTPUT, PREFIX_WORD);
inline const QString PREFIX_OUTPUT_STANDARD_WORD = createPrefix(PREFIX_STANDARD, PREFIX_OUTPUT, PREFIX_WORD);
inline const QString PREFIX_OUTPUT_FIELDBUS_WORD = createPrefix(PREFIX_FIELDBUS, PREFIX_OUTPUT, PREFIX_WORD);
inline const QString PREFIX_OUTPUT_MEMORY_WORD = createPrefix(PREFIX_MEMORY, PREFIX_OUTPUT, PREFIX_WORD);
inline const QString PREFIX_OUTPUT_TOOL_WORD = createPrefix(PREFIX_TOOL, PREFIX_OUTPUT, PREFIX_WORD);
// 全局变量
const int GLOBAL_VAR_B_COUNT = 256;       // 全局B变量总个数
const int GLOBAL_VAR_R_COUNT = 256;       // 全局R变量总个数
const int GLOBAL_VAR_D_COUNT = 256;       // 全局D变量总个数
const int GLOBAL_VAR_PR_COUNT = 256;      // 全局PR变量总个数
const int GLOBAL_VAR_STRING_COUNT = 256;  // 全局String变量总个数
const int GLOBAL_P_COUNT = 10000;         // 全局P变量总个数
const int GLOBAL_P_PAGE_NUM = 5;          // 全局P变量每帧数据大小
const int GLOBAL_JP_COUNT = 10000;        // 全局P变量总个数
const int GLOBAL_JP_PAGE_NUM = 5;         // 全局P变量每帧数据大小

// AD DA
const int ADDA_COUNT = 16;  // AD、DA最大大小

enum class VariableParamsType {
    var_type_int = 0,
    var_type_double,
    var_type_bool,
    var_type_string,
    var_type_pose,
    var_type_joint_point,
    var_type_array,
    var_type_array_int,
    var_type_array_double,
    var_type_array_str,
    var_type_array_pose,
    var_type_array_jp,
    var_type_not_return,
    var_type_unknown
};

const QSet<QString> SET_GLOBAL_VAR_PREFIX = {
    PREFIX_B,
    PREFIX_R,
    PREFIX_D,
    PREFIX_STR,
    PREFIX_P,
    PREFIX_JP,
};

const QSet<QString> IO_PREFIX = {
    PREFIX_INPUT_COMMON_BIT,
    PREFIX_INPUT_STANDARD_BIT,
    PREFIX_INPUT_FIELDBUS_BIT,
    PREFIX_INPUT_MEMORY_BIT,
    PREFIX_INPUT_TOOL_BIT,

    PREFIX_OUTPUT_COMMON_BIT,
    PREFIX_OUTPUT_STANDARD_BIT,
    PREFIX_OUTPUT_FIELDBUS_BIT,
    PREFIX_OUTPUT_MEMORY_BIT,
    PREFIX_OUTPUT_TOOL_BIT,

    PREFIX_INPUT_COMMON_BYTE,
    PREFIX_INPUT_STANDARD_BYTE,
    PREFIX_INPUT_FIELDBUS_BYTE,
    PREFIX_INPUT_MEMORY_BYTE,
    PREFIX_INPUT_TOOL_BYTE,

    PREFIX_OUTPUT_COMMON_BYTE,
    PREFIX_OUTPUT_STANDARD_BYTE,
    PREFIX_OUTPUT_FIELDBUS_BYTE,
    PREFIX_OUTPUT_MEMORY_BYTE,
    PREFIX_OUTPUT_TOOL_BYTE,

    PREFIX_INPUT_COMMON_WORD,
    PREFIX_INPUT_STANDARD_WORD,
    PREFIX_INPUT_FIELDBUS_WORD,
    PREFIX_INPUT_MEMORY_WORD,
    PREFIX_INPUT_TOOL_WORD,

    PREFIX_OUTPUT_COMMON_WORD,
    PREFIX_OUTPUT_STANDARD_WORD,
    PREFIX_OUTPUT_FIELDBUS_WORD,
    PREFIX_OUTPUT_MEMORY_WORD,
    PREFIX_OUTPUT_TOOL_WORD,

    PREFIX_AD,
    PREFIX_DA};

const QHash<QString, QString> HashRobotIOTypeAndVarNamePrefix = {
    {PREFIX_INPUT_COMMON_BIT, "In"},
    {PREFIX_INPUT_COMMON_BYTE, "InB"},
    {PREFIX_INPUT_COMMON_WORD, "InW"},

    {PREFIX_INPUT_STANDARD_BIT, "In"},
    {PREFIX_INPUT_STANDARD_BYTE, "InB"},
    {PREFIX_INPUT_STANDARD_WORD, "InW"},

    {PREFIX_INPUT_FIELDBUS_BIT, "In"},
    {PREFIX_INPUT_FIELDBUS_BYTE, "InB"},
    {PREFIX_INPUT_FIELDBUS_WORD, "InW"},

    {PREFIX_INPUT_MEMORY_BIT, "In"},
    {PREFIX_INPUT_MEMORY_BYTE, "InB"},
    {PREFIX_INPUT_MEMORY_WORD, "InW"},

    {PREFIX_INPUT_TOOL_BIT, "In"},
    {PREFIX_INPUT_TOOL_BYTE, "InB"},
    {PREFIX_INPUT_TOOL_WORD, "InW"},
    // output
    {PREFIX_OUTPUT_COMMON_BIT, "Out"},
    {PREFIX_OUTPUT_COMMON_BYTE, "OutB"},
    {PREFIX_OUTPUT_COMMON_WORD, "OutW"},

    {PREFIX_OUTPUT_STANDARD_BIT, "Out"},
    {PREFIX_OUTPUT_STANDARD_BYTE, "OutB"},
    {PREFIX_OUTPUT_STANDARD_WORD, "OutW"},

    {PREFIX_OUTPUT_FIELDBUS_BIT, "Out"},
    {PREFIX_OUTPUT_FIELDBUS_BYTE, "OutB"},
    {PREFIX_OUTPUT_FIELDBUS_WORD, "OutW"},

    {PREFIX_OUTPUT_MEMORY_BIT, "Out"},
    {PREFIX_OUTPUT_MEMORY_BYTE, "OutB"},
    {PREFIX_OUTPUT_MEMORY_WORD, "OutW"},

    {PREFIX_OUTPUT_TOOL_BIT, "Out"},
    {PREFIX_OUTPUT_TOOL_BYTE, "OutB"},
    {PREFIX_OUTPUT_TOOL_WORD, "OutW"},
    // AD/DA
    {PREFIX_AD, "AD"},
    {PREFIX_DA, "DA"}};

// variable
const char VariableType_B[] = "B";
const char VariableType_R[] = "R";
const char VariableType_D[] = "D";
const char VariableType_Str[] = "Str";
const char VariableType_P[] = "P";
const char VariableType_JP[] = "JP";

const QHash<QString, QString> HashVarTypeAndVarNamePrefix = {
    {PREFIX_B, VariableType_B},
    {PREFIX_R, VariableType_R},
    {PREFIX_D, VariableType_D},
    {PREFIX_STR, VariableType_Str},
    {PREFIX_P, VariableType_P},
    {PREFIX_JP, VariableType_JP}};

const QHash<QString, QString> SET_CONDITION_VALUE_XML_TO_LUA{
    {PREFIX_B, "SetB"},
    {PREFIX_R, "SetR"},
    {PREFIX_D, "SetD"},
    {PREFIX_STR, "SetStr"},
    {PREFIX_OUTPUT_COMMON_BIT, "SetOut"},
    {PREFIX_OUTPUT_STANDARD_BIT, "SetOut"},
    {PREFIX_OUTPUT_MEMORY_BIT, "SetOut"},
    {PREFIX_OUTPUT_FIELDBUS_BIT, "SetOut"},
    {PREFIX_OUTPUT_TOOL_BIT, "SetOut"},

    {PREFIX_OUTPUT_COMMON_BYTE, "SetOutB"},
    {PREFIX_OUTPUT_STANDARD_BYTE, "SetOutB"},
    {PREFIX_OUTPUT_FIELDBUS_BYTE, "SetOutB"},
    {PREFIX_OUTPUT_MEMORY_BYTE, "SetOutB"},
    {PREFIX_OUTPUT_TOOL_BYTE, "SetOutB"},

    {PREFIX_OUTPUT_COMMON_WORD, "SetOutW"},
    {PREFIX_OUTPUT_STANDARD_WORD, "SetOutW"},
    {PREFIX_OUTPUT_FIELDBUS_WORD, "SetOutW"},
    {PREFIX_OUTPUT_MEMORY_WORD, "SetOutW"},
    {PREFIX_OUTPUT_TOOL_WORD, "SetOutW"},

    {PREFIX_INPUT_MEMORY_BIT, "SetIn"},
    {PREFIX_INPUT_MEMORY_BYTE, "SetInB"},
    {PREFIX_INPUT_MEMORY_WORD, "SetInW"},
};


inline const QSet<QString>& LocalVarParams()
{
    static const QSet<QString> set = {
        LOCAL_B,
        LOCAL_R,
        LOCAL_D,
        LOCAL_Int,
        LOCAL_Double,
        LOCAL_P,
        LOCAL_JP,
        LOCAL_STR,
        LOCAL_ARRAY_INT,
        LOCAL_ARRAY_DOUBLE,
        LOCAL_ARRAY_STR,
        LOCAL_ARRAY_P,
        LOCAL_ARRAY_JP
    };
    return set;
}

