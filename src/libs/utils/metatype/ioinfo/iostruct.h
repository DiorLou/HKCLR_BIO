#pragma once

#include <QString>
#include <QColor>
#include <QVariant>

// AD、DA状态
struct Ino_AD_DA_Status {
    int favorite = 0;          // 收藏
    int kind = 0;              // 0 电流  1 电压
    double minValue = 0.0;     // 最小值
    double maxValue = 20.0;    // 最大值 默认电流 0-20mA
    double actualValue = 0.0;  // 实际的值
    int out = 0;               // 输出开关 0 不输出 1 输出

    Ino_AD_DA_Status &operator=(const Ino_AD_DA_Status &other)
    {
        this->favorite = other.favorite;
        this->kind = other.kind;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->actualValue = other.actualValue;
        this->out = other.out;
        return (*this);
    }
    bool operator==(const Ino_AD_DA_Status &other) const
    {
        if (favorite != other.favorite)
            return false;
        if (kind != other.kind)
            return false;
        if (minValue != other.minValue)
            return false;
        if (maxValue != other.maxValue)
            return false;
        if (actualValue != other.actualValue)
            return false;
        if (out != other.out)
            return false;
        return true;
    }
};

// AD、DA数据
struct Ino_AD_DA_Data {
    Ino_AD_DA_Status status;  // 状态
    QString labs;             // 标签
    QString remarks;          // 备注
    bool operator==(const Ino_AD_DA_Data &other) const
    {
        if (labs != other.labs)
            return false;
        if (remarks != other.remarks)
            return false;
        if (!(status == other.status))
            return false;
        return true;
    }
    Ino_AD_DA_Data &operator=(const Ino_AD_DA_Data &other)
    {
        this->labs = other.labs;
        this->remarks = other.remarks;
        this->status = other.status;
        return (*this);
    }
};

enum Ino_Cobot_ADDA_type : unsigned char{
    Ino_Cobot_ADDA_type_AD = 1,
    Ino_Cobot_ADDA_type_DA = 2,
};

enum Ino_Cobot_ADDA_Signal_type : unsigned char{
    ADDA_Type_Current = 1,
    ADDA_Type_Voltage = 2,
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(Ino_Cobot_ADDA_Signal_type)
#endif


// AD、DA状态 协作电柜自带的AD DA
struct Ino_Cobot_ADDA_Status {
    unsigned short type = 0;            // 1AD 2DA
    unsigned short setModelEnable = 0;  // 是否可以配置电流/电压模式
    unsigned short index = 0;           // 协作 电柜101 102 末端103 104
    unsigned short currentConfigState = 0;    // 0已配置 配置中
    unsigned short kind = 0;                  // 1 电流  2 电压
    unsigned short out = 0;                   // 输出开关 0 不输出 1 输出
    unsigned short deviceType = 0;              // 类别 0IRLink 1EtherCat 2末端 3电柜
    double minValue = 0.0;             // 最小值
    double maxValue = 20.0;            // 最大值 默认电流 0-20mA
    double actualValue = 0.0;          // 实际的值

    Ino_Cobot_ADDA_Status &operator=(const Ino_Cobot_ADDA_Status &other)
    {
        this->type = other.type;
        this->setModelEnable = other.setModelEnable;
        this->index = other.index;
        this->currentConfigState = other.currentConfigState;
        this->deviceType = other.deviceType;
        this->kind = other.kind;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->actualValue = other.actualValue;
        this->out = other.out;
        return (*this);
    }

    bool operator==(const Ino_Cobot_ADDA_Status &other) const
    {
        if (type != other.type)
            return false;
        if (index != other.index)
            return false;
        if (currentConfigState != other.currentConfigState)
            return false;
        if (deviceType != other.deviceType)
            return false;
        if (kind != other.kind)
            return false;
        if (minValue != other.minValue)
            return false;
        if (maxValue != other.maxValue)
            return false;
        if (actualValue != other.actualValue)
            return false;
        if (out != other.out)
            return false;
        if (setModelEnable != other.setModelEnable)
            return false;
        return true;
    }
};

// AD、DA数据 协作电柜自带的AD DA
struct Ino_Cobot_ADDA_Data {
    Ino_Cobot_ADDA_Status status;  // 状态
    QString labs;               // 标签
    QString remarks;            // 备注

    Ino_Cobot_ADDA_Data &operator=(const Ino_Cobot_ADDA_Data &other)
    {
        this->status = other.status;
        this->labs = other.labs;
        this->remarks = other.remarks;
        return (*this);
    }

    bool operator==(const Ino_Cobot_ADDA_Data &other) const
    {
        if (!(this->status == other.status))
            return false;
        if (this->labs != other.labs)
            return false;
        if (this->remarks != other.remarks)
            return false;
        return true;
    }
};

//
struct ToolIOConfigContent {
    enum ValueType {
        ContinutyInt = 0,
        ContinutyDouble,
        Discrete,
    };
    enum RangeType {
        None = 0,
        LeftClose_RightClose,
        LeftOpen_RightClose,
        LeftClose_RightOpen,
        LeftOpen_RightOpen
    };
    QString name;
    int index;
    int subIndex;
    QString describe;
    QList<QVariant> valueRange;
    int valueType;      // 0连续整型 1连续浮点 2多选一
    int rangeType;      // 0无 1左右闭区间 2左开右闭区间 3左闭右开区间 4左右开区间 ***多选一时无效***
    int valueDecimals;  // 小数 ***多选一时无效***
    int permission;     // 0只读 1读写
    QVariant value;     // 值
    ToolIOConfigContent &operator=(const ToolIOConfigContent &other)
    {
        name = other.name;
        index = other.index;
        subIndex = other.subIndex;
        describe = other.describe;
        permission = other.permission;
        valueRange = other.valueRange;
        valueType = other.valueType;
        rangeType = other.rangeType;
        valueDecimals = other.valueDecimals;
        value = other.value;
        return (*this);
    }
    bool operator==(const ToolIOConfigContent &other) const
    {
        if (name != other.name)
            return false;
        if (index != other.index)
            return false;
        if (subIndex != other.subIndex)
            return false;
        if (describe != other.describe)
            return false;
        if (permission != other.permission)
            return false;
        if (valueRange != other.valueRange)
            return false;
        if (valueType != other.valueType)
            return false;
        if (rangeType != other.rangeType)
            return false;
        if (valueDecimals != other.valueDecimals)
            return false;
        if (value != other.value)
            return false;
        return true;
    }
};
