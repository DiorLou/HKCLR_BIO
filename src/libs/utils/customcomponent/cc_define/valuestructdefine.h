#pragma once
#include <QVariant>
#include "limits.h"
#include "regexstrdefine.h"
#include "customcomponent_global.h"
#include <QMetaType>

enum ValueType {
    Bool = 0,
    UChar,
    Int,
    Double,
    String,
    UnsignedInt,
};

struct CUSTOMCOMPONENT_EXPORT ValueLimit {
    ValueType valueType;
    bool isNeedNumcrialLimit;
    QVariant minValue;
    QVariant maxValue;
    QString strRegex;
    unsigned int  decimals;

public:
    ValueLimit(ValueType _valueType,
               bool _isNeedNumcrialLimit,
               QVariant _minValue,
               QVariant _maxValue,
               QString _strRegex = "",
               int _decimals = 0)
    {
        valueType = _valueType;
        isNeedNumcrialLimit = _isNeedNumcrialLimit;
        minValue = _minValue;
        maxValue = _maxValue;
        strRegex = _strRegex;
        decimals = _decimals;
        if(_valueType!= Double)
            decimals = 0;
    }

    ValueLimit(const ValueLimit &other){
        this->valueType = other.valueType;
        this->isNeedNumcrialLimit = other.isNeedNumcrialLimit;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->strRegex = other.strRegex;
        this->decimals = other.decimals;
    }

    ValueLimit(bool _isNeedNumcrialLimit)
    {
        isNeedNumcrialLimit = _isNeedNumcrialLimit;
        decimals = 0;
    }
    ValueLimit()
    {
        valueType = Int;
        isNeedNumcrialLimit = true;
        minValue = INT_MIN;
        maxValue = INT_MAX;
        decimals = 3;
    }
    ValueLimit &operator=(const ValueLimit &other){
        this->valueType = other.valueType;
        this->isNeedNumcrialLimit = other.isNeedNumcrialLimit;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->strRegex = other.strRegex;
        this->decimals = other.decimals;
        return *this;
    }


};
Q_DECLARE_METATYPE(ValueLimit)

// 数值限制
const double POINT_Min = -999999999.999;
const double POINT_MAX = 999999999.999;
const int POINT_DECIMALS = 3;

const double PERCENT_MIN = 1;
const double PERCENT_MAX = 100;
const double UCHAR_MIN = 0;

const double DOUBLE_MAX = 9999999.999;
const double DOUBLE_MIN = -9999999.999;

const bool ENABLE_NUMCRIAL_LIMIT = true;
const bool DISABLE_NUMCRIAL_LIMIT = false;

const ValueLimit VALUE_LIMIT_STRING = ValueLimit(ValueType::String,
                                                 DISABLE_NUMCRIAL_LIMIT,
                                                 "",
                                                 "",
                                                 STRING_REGEX);

const ValueLimit VALUE_LIMIT_STRING_UNLIMIT = ValueLimit(ValueType::String,
                                                 DISABLE_NUMCRIAL_LIMIT,
                                                 "",
                                                 "",
                                                 STRING_REGEX_UNLIMIT);

const ValueLimit VALUE_LIMIT_INT = ValueLimit(ValueType::Int,
                                              ENABLE_NUMCRIAL_LIMIT,
                                              INT_MIN,
                                              INT_MAX,
                                              INT_REGEX);
const ValueLimit VALUE_LIMIT_UINT = ValueLimit(ValueType::UnsignedInt,
                                              ENABLE_NUMCRIAL_LIMIT,
                                              0,
                                              UINT_MAX,
                                              UINT_REGEX);
const ValueLimit VALUE_LIMIT_DOUBLE = ValueLimit(ValueType::Double,
                                                 ENABLE_NUMCRIAL_LIMIT,
                                                 DOUBLE_MIN,
                                                 DOUBLE_MAX,
                                                 DOUBLE_REGEX,
                                                 3);
const ValueLimit VALUE_LIMIT_UCHAR = ValueLimit(ValueType::UChar,
                                                ENABLE_NUMCRIAL_LIMIT,
                                                UCHAR_MIN,
                                                UCHAR_MAX,
                                                UCHAR_REGEX);
const ValueLimit VALUE_LIMIT_BOOL = ValueLimit(ValueType::Bool,
                                               ENABLE_NUMCRIAL_LIMIT,
                                               0,
                                               1,
                                               BOOL_REGEX);
const ValueLimit VALUE_LIMIT_PERCENT = ValueLimit(ValueType::Int,
                                                  ENABLE_NUMCRIAL_LIMIT,
                                                  PERCENT_MIN,
                                                  PERCENT_MAX,
                                                  PERCENT_REGEX);
const ValueLimit VALUE_LIMIT_POINT_P = ValueLimit(ValueType::Double,
                                                  ENABLE_NUMCRIAL_LIMIT,
                                                  POINT_Min,
                                                  POINT_MAX,
                                                  DOUBLE_REGEX,
                                                  POINT_DECIMALS);
const ValueLimit VALUE_LIMIT_POINT_JP = ValueLimit(ValueType::Double,
                                                   ENABLE_NUMCRIAL_LIMIT,
                                                   POINT_Min,
                                                   POINT_MAX,
                                                   DOUBLE_REGEX,
                                                   POINT_DECIMALS);
const ValueLimit VALUE_LIMIT_NONE = ValueLimit();

struct CUSTOMCOMPONENT_EXPORT CustomColumnMsg {
    QString headerName;
    QVariant defaultValue;
    int width;
    bool isEditEnable;
    bool isNeedCheckBoxWhenShow;
    ValueLimit valueLimit;

public:
    explicit CustomColumnMsg(QString _headerName,
                             QVariant _defaultValue,
                             int _width,
                             bool _isEditEnable,
                             ValueLimit _valueLimit,
                             bool _isNeedCheckBoxWhenShow = false  // 如果为bool类型 设置显示时是否需要checkbox
                             )                             // 是否需要特定格式的显示如 B[%1] 会将value转为string再替换{0}进行显示
    {
        headerName = _headerName;
        defaultValue = _defaultValue;
        width = _width;
        isNeedCheckBoxWhenShow = _isNeedCheckBoxWhenShow;
        isEditEnable = _isEditEnable;
        valueLimit = _valueLimit;
    }
};
