#pragma once
#include "IInoRobUtil.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS Crc16
{
public:
    Crc16();
    ~Crc16();

    // 通过字节数组获取校验值
    unsigned short static FromData(unsigned char *buffer, unsigned int size, unsigned short crc = 0xFFFF);

    // 功能安全CRC校验组件
    unsigned short static CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);
    void static InvertUint8(unsigned char *dBuf, unsigned char *srcBuf);
    void static InvertUint16(unsigned short *dBuf, unsigned short *srcBuf);

private:
};

}  // namespace InoRobUtil
