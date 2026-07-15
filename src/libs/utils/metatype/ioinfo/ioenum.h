#pragma once

#include <QString>
#include <QColor>
#include <QVariant>

// 总线
const int STANDARD_IO_START_INDEX = 0;   // 标准IO起始下标(以byte参考)
const int STANDARD_IO_COUNT = 16;        // 标准IO大小(以byte参考)
const int TOOL_IO_START_INDEX = 16;      // 协作工具IO起始下标(以byte参考)
const int TOOL_IO_COUNT = 2;             // 协作工具IO大小(以byte参考)
const int FIELDBUS_IO_START_INDEX = 64;  // 现场总线IO起始下标(以byte参考)
const int FIELDBUS_IO_COUNT = 512;       // 现场总线IO大小(以byte参考)
const int MEMORY_IO_START_INDEX = 1600;  // 内存IO起始下标(以byte参考)
const int MEMORY_IO_COUNT = 128;         // 内存IO大小(以byte参考)

enum InoIOType {
    InoIOType_CommonIO = 0,  // 常用IO(设置了标签或者备注)
    InoIOType_StandardIO,    // 标准IO
    InoIOType_FieldbusIO,    // 现场总线IO
    InoIOType_MemoryIO,      // 内存IO
    InoIOType_ToolIO,        // 末端IO
    InoIOTypeSize
};

enum Ino_IOMapResetMethod {
    UNKNOW_IO = 0,           // 未知IO
    DIGITAL_IO = 1,          // 标准IO
    FIELDBUS_IO = 2,         // 从站IO
    MEMORY_IO = 3,           // 内存IO
    SYSTEM_IO = 4,           // 系统IO
    FIELDBUS_MASTER_IO = 5,  // 主站IO
};

enum BaseType {
    BaseType_Decimal = 0,  // 十进制
    BaseType_Binary,       // 二进制
    BaseType_Hexadecimal,  // 十六进制
};

enum ShowType {
    ShowType_Bit = 0,   // bit
    ShowType_Byte = 1,  // 字节
    ShowType_Word = 2,  // 字
    ShowType_Size = 3
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(ShowType)
#endif

