#pragma once

#include <memory.h>

// 总线类型
typedef enum
{
    INO_FB_Unknow = 0,
    INO_FB_Modbus = 1,
    INO_FB_EthernetIp = 2,
    INO_FB_EtherCATSlave = 3,
    INO_FB_FINS = 4,
    INO_FB_MC = 5,
    INO_FB_Profinet = 6,
} INO_E_FieldBusType;

// 现场总线从站配置信息
typedef struct INO_MODBUS_ADDRASSIGN_CONFIG
{
    INO_MODBUS_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
        modbusInputCoilSize = 20;
        modbusInputRegSize = 236;
        modbusOutputCoilSize = 20;
        modbusOutputRegSize = 236;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short modbusInputCoilSize;
    unsigned short modbusInputRegSize;
    unsigned short modbusOutputCoilSize;
    unsigned short modbusOutputRegSize;
} INO_ModbusAddrassignConfig;

struct INO_EIP_ADDRASSIGN_CONFIG
{
    INO_EIP_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

struct INO_ETHERCAT_ADDRASSIGN_CONFIG
{
    INO_ETHERCAT_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
};

struct INO_MC_ADDRASSIGN_CONFIG
{
    INO_MC_ADDRASSIGN_CONFIG()
    {
        inputSize = 256;
        outputSize = 256;
        mcInputStartAddr = 1025;
        mcInputRegSize = 2025;
        mcOutputStartAddr = 256;
        mcOutputRegSize = 256;
    };
    unsigned short inputSize;
    unsigned short outputSize;
    unsigned short mcInputStartAddr;
    unsigned short mcInputRegSize;
    unsigned short mcOutputStartAddr;
    unsigned short mcOutputRegSize;
};

struct INO_PN_ADDRASSIGN_CONFIG
{
    INO_PN_ADDRASSIGN_CONFIG()
    {
        inputSize = 127;
        outputSize = 127;
    }
    unsigned short inputSize;
    unsigned short outputSize;
};

struct INO_FIELDBUS_MEM_ASSIGN_CONFIG
{
    INO_FIELDBUS_MEM_ASSIGN_CONFIG()
    {
        memset(Version, 0, sizeof(char) * 8);
        for (int i = 0; i < 4; i++)
        {
            INO_MC_ADDRASSIGN_CONFIG mc;
            mcConfig[i] = mc;
        }
    };
    char Version[8];
    INO_MODBUS_ADDRASSIGN_CONFIG modbusConfig;
    INO_EIP_ADDRASSIGN_CONFIG eipConfig;
    INO_ETHERCAT_ADDRASSIGN_CONFIG etherCATConfig;
    INO_MC_ADDRASSIGN_CONFIG mcConfig[4];
    INO_PN_ADDRASSIGN_CONFIG pnConfig;
};
