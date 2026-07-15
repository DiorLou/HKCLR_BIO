#pragma once

#include <cstring>

// TCP
typedef struct tagCobotModbusTCP_Para
{
    tagCobotModbusTCP_Para()
    {
        owner = 0;
        sts = 0;
        port = 502;
        framedelay = 1;
    }
    unsigned char owner;        // 控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // 运行情况 0-未运行，1-运行
    unsigned short port;        // 端口号
    unsigned short framedelay;  // 帧间隔
} CobotModbusTCP_Para;

// RTU
typedef struct tagCobotModbusRTU_Para
{
    tagCobotModbusRTU_Para()
    {
        owner = 0;
        sts = 0;
        baud = 5;
        stopbits = 0;
        databits = 0;
        parity = 0;
        tmode = 0;
        slaveid = 1;
        framedelay = 5;
        timeout = 0;
    }
    unsigned char owner;        // Modbus控制权 0-未开启，1-二次开发，2-控制器
    unsigned char sts;          // Modbus 运行情况 0-未运行，1-运行
    unsigned char baud;         // 波特率，索引值，其具体值见Baud数组
    unsigned char stopbits;     // 停止位 0-1位 1-2位
    unsigned char databits;     // 数据位 0-7位 1-8位
    unsigned char parity;       // 奇偶校验 0-无校验 1-奇校验 2-偶校验
    unsigned char tmode;        // 传输模式 0-RTU 1-ASCII
    unsigned char slaveid;      // 站点号
    unsigned short framedelay;  // 帧间隔
    unsigned short timeout;     // 超时时间
} CobotModbusRTU_Para;

// Modbus写入总结构体
typedef struct stCobotMODBUS_PARA_CONFIG
{
    stCobotMODBUS_PARA_CONFIG()
    {
        ModbusAddrType = 0;  // 0-旧版地址
    };
    unsigned char ModbusAddrType;    // Modbus地址类型 0-旧版地址，1-新版地址
    CobotModbusTCP_Para stModbusTcpPara;  // Modbus配置结构体
    CobotModbusRTU_Para stModbusRtuPara;  // ModbusRtu配置结构体
} CobotModbusParaConfig;

// Modbus读取总结构体
typedef struct stCobotMODBUS_CONNECT_STS
{
    stCobotMODBUS_CONNECT_STS()
    {
        ModbusAddrType = 0;
        for (int i = 0; i < 16; i++)
        {
            ModbusTcpConnectFlag[i] = 0;  // 0表示未连接
            ModbusTcpClientPort[i] = 502;
            memset(&ModbusTcpClientIP[i], 0, 16 * sizeof(unsigned char));
        }
    }

    unsigned char ModbusAddrType;            // Modbus地址类型 0-旧版地址，1-新版地址
    CobotModbusTCP_Para stModbusTcpPara;     // Modbus配置结构体
    CobotModbusRTU_Para stModbusRtuPara;     // ModbusRtu配置结构
    char ModbusTcpConnectFlag[16];           // modbusTcp连接状态，0表示未连接，1表示已连
    char ModbusTcpClientIP[16][16];          // 主站IP地址（第一行表示第一个连接上的主站的IP）
    unsigned short ModbusTcpClientPort[16];  // 主站端口（第一元素表示第一个连接上的主站的端口）
} CobotModbusConnectSts;
