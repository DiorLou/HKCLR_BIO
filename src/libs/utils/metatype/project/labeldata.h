#pragma once
#include <QString>
#include <QVariant>
#include "keyboard.h"
#include "ioenum.h"

const QStringList LABEL_KEY_WORDS = {"PE", "PR"};  // 需要过滤的关键字
const QStringList COMMAND_KEY_WORDS = {"SetV", "SetZ",
                                       "SetToolNo", "SetWobjNo", "SetLoadNo",
                                       "SetAcc", "SetDec",
                                       "MovUtil", "MovOut", "MovSl",
                                       "MovJ", "MovL", "MovAbsJ", "MovC",
                                       "Jump", "JumpL", "Abort","Home", "SetAccuracyMode"};

const int LABEL_MAX_SIZE = 20;
const int DESCRIPTION_MAX_SIZE = 100;

enum InoLabelType {
    /// <summary>
    /// IO输入 - bit
    /// </summary>
    IO_INPUT_BIT = 0,
    /// <summary>
    /// IO输出 - bit
    /// </summary>
    IO_OUTPUT_BIT,
    /// <summary>
    /// IO输入 - byte
    /// </summary>
    IO_INPUT_BYTE,
    /// <summary>
    /// IO输出 - byte
    /// </summary>
    IO_OUTPUT_BYTE,
    /// <summary>
    /// IO输入 - word
    /// </summary>
    IO_INPUT_WORD,
    /// <summary>
    /// IO输出 - word
    /// </summary>
    IO_OUTPUT_WORD,
    /// <summary>
    /// DA变量
    /// </summary>
    IO_DA,
    /// <summary>
    /// AD变量
    /// </summary>
    IO_AD,
    /// <summary>
    /// B变量
    /// </summary>
    IO_B,
    /// <summary>
    /// R变量
    /// </summary>
    IO_R,
    /// <summary>
    /// D变量
    /// </summary>
    IO_D,
    /// <summary>
    /// STR变量
    /// </summary>
    IO_STR,
    /// <summary>
    /// 未知
    /// </summary>
    IO_SIZE,
};
Q_DECLARE_METATYPE(InoLabelType);

enum InoAdDaType {
    InoAdDaType_IRLink = 0,
    InoAdDaType_EtherCAT,
};
Q_DECLARE_METATYPE(InoAdDaType);

enum InoLabelIOType {
    /// <summary>
    /// 标准IO
    /// </summary>
    InoLabelIOType_StandardIO = 0,
    /// <summary>
    /// 从站现场IO
    /// </summary>
    InoLabelIOType_SlaveFiledbusIO,
    /// <summary>
    /// 从站现场IO
    /// </summary>
    InoLabelIOType_MasterFiledbusIO,
    /// <summary>
    /// 工具IO
    /// </summary>
    InoLabelIOType_ToolIO,
    /// <summary>
    /// 内存IO
    /// </summary>
    InoLabelIOType_MemoryIO,
};
Q_DECLARE_METATYPE(InoLabelIOType);

enum AllLabelType {
    LabelType_None = -1,
    LabelType_Input_Start = 0,
    LabelType_Input_Common_Bit = LabelType_Input_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Bit,
    LabelType_Input_Common_Byte = LabelType_Input_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Byte,
    LabelType_Input_Common_Word = LabelType_Input_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Word,
    LabelType_Input_Standard_Bit = LabelType_Input_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Bit,
    LabelType_Input_Standard_Byte = LabelType_Input_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Byte,
    LabelType_Input_Standard_Word = LabelType_Input_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Word,
    LabelType_Input_FieldBus_Bit = LabelType_Input_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Bit,
    LabelType_Input_FieldBus_Byte = LabelType_Input_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Byte,
    LabelType_Input_FieldBus_Word = LabelType_Input_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Word,
    LabelType_Input_Memory_Bit = LabelType_Input_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Bit,
    LabelType_Input_Memory_Byte = LabelType_Input_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Byte,
    LabelType_Input_Memory_Word = LabelType_Input_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Word,
    LabelType_Input_Tool_Bit = LabelType_Input_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Bit,
    LabelType_Input_Tool_Byte = LabelType_Input_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Byte,
    LabelType_Input_Tool_Word = LabelType_Input_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Word,

    LabelType_Output_Start = LabelType_Input_Tool_Word + 1,
    LabelType_Output_Common_Bit = LabelType_Output_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Bit,
    LabelType_Output_Common_Byte = LabelType_Output_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Byte,
    LabelType_Output_Common_Word = LabelType_Output_Start + InoIOType_CommonIO * ShowType_Size + ShowType_Word,
    LabelType_Output_Standard_Bit = LabelType_Output_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Bit,
    LabelType_Output_Standard_Byte = LabelType_Output_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Byte,
    LabelType_Output_Standard_Word = LabelType_Output_Start + InoIOType_StandardIO * ShowType_Size + ShowType_Word,
    LabelType_Output_FieldBus_Bit = LabelType_Output_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Bit,
    LabelType_Output_FieldBus_Byte = LabelType_Output_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Byte,
    LabelType_Output_FieldBus_Word = LabelType_Output_Start + InoIOType_FieldbusIO * ShowType_Size + ShowType_Word,
    LabelType_Output_Memory_Bit = LabelType_Output_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Bit,
    LabelType_Output_Memory_Byte = LabelType_Output_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Byte,
    LabelType_Output_Memory_Word = LabelType_Output_Start + InoIOType_MemoryIO * ShowType_Size + ShowType_Word,
    LabelType_Output_Tool_Bit = LabelType_Output_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Bit,
    LabelType_Output_Tool_Byte = LabelType_Output_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Byte,
    LabelType_Output_Tool_Word = LabelType_Output_Start + InoIOType_ToolIO * ShowType_Size + ShowType_Word,

    LabelType_DA_Start = 100,
    LabelType_DA = LabelType_DA_Start + IO_DA,
    LabelType_AD = LabelType_DA_Start + IO_AD,
    LabelType_GlobalVar_B = LabelType_DA_Start + IO_B,
    LabelType_GlobalVar_R = LabelType_DA_Start + IO_R,
    LabelType_GlobalVar_D = LabelType_DA_Start + IO_D,
    LabelType_GlobalVar_STR = LabelType_DA_Start + IO_STR,

    LabelType_GlobalVar_P,
    LabelType_GlobalVar_JP,
};

typedef struct VarIndexRange {
    int nStartIndex;
    int nEndIndex;

    VarIndexRange()
    {
        nStartIndex = -1;
        nEndIndex = -1;
    }

    VarIndexRange(int startIndex, int endIndex)
    {
        nStartIndex = startIndex;
        nEndIndex = endIndex;
    }

    bool isValid()
    {
        return (nStartIndex <= -1 || nEndIndex <= -1
                || nStartIndex > nEndIndex);
    }

    bool isInRange(int nIndex) const
    {
        return (nIndex >= nStartIndex && nIndex <= nEndIndex);
    }
} VarIndexRange;

// input
const char RobotIOInputCommonBit[] = "Input_Common_Bit";
const char RobotIOInputCommonByte[] = "Input_Common_Byte";
const char RobotIOInputCommonWord[] = "Input_Common_Word";
const char RobotIOInputMemoryBit[] = "Input_Memory_Bit";
const char RobotIOInputMemoryByte[] = "Input_Memory_Byte";
const char RobotIOInputMemoryWord[] = "Input_Memory_Word";
const char RobotIOInputFieldbusBit[] = "Input_FieldBus_Bit";
const char RobotIOInputFieldbusByte[] = "Input_FieldBus_Byte";
const char RobotIOInputFieldbusWord[] = "Input_FieldBus_Word";
const char RobotIOInputStandardBit[] = "Input_Standard_Bit";
const char RobotIOInputStandardByte[] = "Input_Standard_Byte";
const char RobotIOInputStandardWord[] = "Input_Standard_Word";
// output
const char RobotIOOutputCommonBit[] = "Output_Common_Bit";
const char RobotIOOutputCommonByte[] = "Output_Common_Byte";
const char RobotIOOutputCommonWord[] = "Output_Common_Word";
const char RobotIOOutputMemoryBit[] = "Output_Memory_Bit";
const char RobotIOOutputMemoryByte[] = "Output_Memory_Byte";
const char RobotIOOutputMemoryWord[] = "Output_Memory_Word";
const char RobotIOOutputFieldbusBit[] = "Output_FieldBus_Bit";
const char RobotIOOutputFieldbusByte[] = "Output_FieldBus_Byte";
const char RobotIOOutputFieldbusWord[] = "Output_FieldBus_Word";
const char RobotIOOutputStandardBit[] = "Output_Standard_Bit";
const char RobotIOOutputStandardByte[] = "Output_Standard_Byte";
const char RobotIOOutputStandardWord[] = "Output_Standard_Word";
// AD/DA
const char RobotIOAD[] = "AD";
const char RobotIODA[] = "DA";

const QHash<QString, VarIndexRange> HashVarIndexRange = {
    {PREFIX_B, VarIndexRange(0, 255)},
    {PREFIX_R, VarIndexRange(0, 255)},
    {PREFIX_D, VarIndexRange(0, 255)},
    {PREFIX_STR, VarIndexRange(0, 255)},
    {PREFIX_P, VarIndexRange(0, 10000)},
    {PREFIX_JP, VarIndexRange(0, 10000)}};


const QVector<QString> VecRobotIoPrefix = {
    RobotIOInputCommonBit,
    RobotIOInputCommonByte,
    RobotIOInputCommonWord,
    RobotIOInputMemoryBit,
    RobotIOInputMemoryByte,
    RobotIOInputMemoryWord,
    RobotIOInputFieldbusBit,
    RobotIOInputFieldbusByte,
    RobotIOInputFieldbusWord,
    RobotIOInputStandardBit,
    RobotIOInputStandardByte,
    RobotIOInputStandardWord,
    // output
    RobotIOOutputCommonBit,
    RobotIOOutputCommonByte,
    RobotIOOutputCommonWord,
    RobotIOOutputMemoryBit,
    RobotIOOutputMemoryByte,
    RobotIOOutputMemoryWord,
    RobotIOOutputFieldbusBit,
    RobotIOOutputFieldbusByte,
    RobotIOOutputFieldbusWord,
    RobotIOOutputStandardBit,
    RobotIOOutputStandardByte,
    RobotIOOutputStandardWord,
    // AD/DA
    RobotIOAD,
    RobotIODA};

const QHash<QString, VarIndexRange> HashRobotIOIndexRange = {
    {RobotIOInputMemoryBit, VarIndexRange(12800, 13823)},
    {RobotIOInputMemoryByte, VarIndexRange(1600, 1727)},
    {RobotIOInputMemoryWord, VarIndexRange(800, 863)},
    {RobotIOInputFieldbusBit, VarIndexRange(512, 4607)},
    {RobotIOInputFieldbusByte, VarIndexRange(64, 575)},
    {RobotIOInputFieldbusWord, VarIndexRange(32, 287)},
    {RobotIOInputStandardBit, VarIndexRange(0, 127)},
    {RobotIOInputStandardByte, VarIndexRange(0, 15)},
    {RobotIOInputStandardWord, VarIndexRange(0, 7)},
    // output
    {RobotIOOutputMemoryBit, VarIndexRange(12800, 13823)},
    {RobotIOOutputMemoryByte, VarIndexRange(1600, 1727)},
    {RobotIOOutputMemoryWord, VarIndexRange(800, 863)},
    {RobotIOOutputFieldbusBit, VarIndexRange(512, 4607)},
    {RobotIOOutputFieldbusByte, VarIndexRange(64, 575)},
    {RobotIOOutputFieldbusWord, VarIndexRange(32, 287)},
    {RobotIOOutputStandardBit, VarIndexRange(0, 127)},
    {RobotIOOutputStandardByte, VarIndexRange(0, 15)},
    {RobotIOOutputStandardWord, VarIndexRange(0, 7)},
    // AD/DA
    {RobotIOAD, VarIndexRange(0, 15)},
    {RobotIODA, VarIndexRange(0, 15)}};

// IO类型标签
typedef struct InoLabelItem {
    int nLabelId;
    int nIndex;
    QString sLabel;
    QString sDescription;
    QString sOriginalName;

    InoLabelItem()
    {
        nLabelId = -1;
        nIndex = -1;
        sLabel = "";
        sDescription = "";
        sOriginalName = "";
    }
    InoLabelItem(int nId, int nIndex, const QString &sLabel,
                 const QString &sDescription, const QString &sName)
    {
        this->nLabelId = nId;
        this->nIndex = nIndex;
        this->sLabel = sLabel;
        this->sDescription = sDescription;
        this->sOriginalName = sName;
    }

    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->sOriginalName;
        case 1:
            return this->sLabel;
        case 2:
            return this->sDescription;
        default:
            break;
        }
        return QString();
    }

    InoLabelItem &operator=(const InoLabelItem &other)
    {
        this->nLabelId = other.nLabelId;
        this->nIndex = other.nIndex;
        this->sLabel = other.sLabel;
        this->sDescription = other.sDescription;
        this->sOriginalName = other.sOriginalName;
        return (*this);
    }

    bool operator==(const InoLabelItem &other) const
    {
        if (this->nLabelId != other.nLabelId)
            return false;
        if (this->nIndex != other.nIndex)
            return false;
        if (this->sLabel != other.sLabel)
            return false;
        if (this->sDescription != other.sDescription)
            return false;
        if (this->sOriginalName != other.sOriginalName)
            return false;
        return true;
    }
} InoLabelItem;
Q_DECLARE_METATYPE(InoLabelItem)

typedef struct InoIOLabelItems {
    int nNumberOfLabels;
    QVector<InoLabelItem> LabelsArray;

    InoIOLabelItems()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    void clear()
    {
        nNumberOfLabels = 0;
        LabelsArray.clear();
    }

    InoIOLabelItems &operator=(const InoIOLabelItems &other)
    {
        this->nNumberOfLabels = other.nNumberOfLabels;
        this->LabelsArray.clear();
        this->LabelsArray = other.LabelsArray;
        return (*this);
    }
} InoIOLabelItems;

// IO类型标签和描述
typedef struct InoLabelAndDescriItem {
    int nIndex;
    QString sLabel;
    QString sDescription;
    InoLabelAndDescriItem()
    {
        nIndex = -1;
        sLabel = "";
        sDescription = "";
    }

    InoLabelAndDescriItem(int nIndex, const QString &sLabel,
                 const QString &sDescription)
    {
        this->nIndex = nIndex;
        this->sLabel = sLabel;
        this->sDescription = sDescription;
    }

    InoLabelAndDescriItem &operator=(const InoLabelAndDescriItem &other)
    {
        this->nIndex = other.nIndex;
        this->sLabel = other.sLabel;
        this->sDescription = other.sDescription;
        return (*this);
    }

    bool operator==(const InoLabelAndDescriItem &other) const
    {
        if (this->nIndex != other.nIndex)
            return false;
        if (this->sLabel != other.sLabel)
            return false;
        if (this->sDescription != other.sDescription)
            return false;
        return true;
    }

} InoLabelAndDescriItem;
