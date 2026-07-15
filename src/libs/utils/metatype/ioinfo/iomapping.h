#pragma once
#include <QString>

enum Ino_IOType
{
    IOTP_IN = 0,  // input
    IOTP_OUT      // output
};

enum Ino_MemoryLength : unsigned int
{
    ML_BIT = 1,    // Bit
    ML_CHAR = 4,   // Char
    ML_BYTE = 8,   // Byte
    ML_WORD = 16,  // Word
    ML_DWORD = 32  // DWord
};

struct Ino_FieldbusIOMapData
{
    Ino_IOType ioType = Ino_IOType::IOTP_IN;                     // IO类型
    unsigned int funcId = 0;  // funID
    int memAddr = -1;                                    // 内存地址
    Ino_MemoryLength length = Ino_MemoryLength::ML_BIT;          // 内存长度
    QString name;

    Ino_FieldbusIOMapData()
    {

    }

    Ino_FieldbusIOMapData(Ino_IOType ioType,
                          unsigned int funcId,
                          Ino_MemoryLength length,
                          const QString &name)
    {
        this->ioType = ioType;
        this->funcId = funcId;
        this->memAddr = -1;
        this->length = length;
        this->name = name;
    }

    Ino_FieldbusIOMapData(Ino_IOType ioType,
                          unsigned int funcId,
                          int memAddr,
                          Ino_MemoryLength length,
                          const QString &name)
    {
        this->ioType = ioType;
        this->funcId = funcId;
        this->memAddr = memAddr;
        this->length = length;
        this->name = name;
    }

    bool operator ==(const Ino_FieldbusIOMapData &other) const
    {
        if (ioType != other.ioType)
            return false;
        if (funcId != other.funcId)
            return false;
        if (memAddr != other.memAddr)
            return false;
        if (length != other.length)
            return false;
        if (name != other.name)
            return false;
        return true;
    }

    Ino_FieldbusIOMapData &operator=(const Ino_FieldbusIOMapData &other)
    {
        this->ioType = other.ioType;
        this->funcId = other.funcId;
        this->memAddr = other.memAddr;
        this->length = other.length;
        this->name = other.name;
        return (*this);
    }
};

enum IOMappingCmdType{
    ResetIOMapping = 0,
    ImportIOMapping = 1,
    ExportIOMapping = 2,
    SaveDatas = 3,
};
