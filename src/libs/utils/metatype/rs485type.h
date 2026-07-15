#pragma once
#include <qobject.h>
#include <QString>

enum ToolIO_RS485OrAD_ReuseMode {
    ReuseMode_Unknown = -1,
    ReuseMode_AD = 0,
    ReuseMode_RS485 = 1
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(ToolIO_RS485OrAD_ReuseMode)
#endif

enum DataVerificationMethod{
    Verification_None = 0,
    Verification_Odd = 1,
    Verification_Even = 2
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(DataVerificationMethod)
#endif

enum RS485_Channel {
    ALL = -1,
    Controller_RS485 = 0,
    TOOLIO_RS485 = 1
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(RS485_Channel)
#endif

struct ToolIO_RS485_Config {
    RS485_Channel type = Controller_RS485;
    int baudrate = 0;
    int dataBit = 0;
    int stopBit = 0;
    DataVerificationMethod checkWay = Verification_None;
};


enum ToolIO_RS485_VerCheckType {
    CRC16 = 0,
    Other = 1
};
#ifdef INOCOBOTTP_MSVC_QT5
Q_DECLARE_METATYPE(ToolIO_RS485_VerCheckType)
#endif

struct ToolIO_RS485_Debugging {
    RS485_Channel type = Controller_RS485;
    ToolIO_RS485_VerCheckType checkType = CRC16;
    QString content = "";
};
