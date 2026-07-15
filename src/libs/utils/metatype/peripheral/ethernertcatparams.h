#pragma once

#include <QVariant>

// 写入Ethcat
typedef struct stInoEthcatPara
{
    stInoEthcatPara()
    {
        ActiveCmd = 0;
        SiteAlias = 0;
        MaxFramLossTimes = 0;
    };

    unsigned char ActiveCmd;          // 0表示关闭，1表示激活
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次，最小值为8，最大值为65535）
} InoEthcatPara;

typedef struct INO_ETHCAT_PROP
{
    INO_ETHCAT_PROP()
    {
        u8LinkState = 0;
        u8EscState = 0;
        u16AppFaultCode = 0;
        u16AppStateCode = 0;
        u8Port0InvFraCount = 0;
        u8Port0AptErrFraCount = 0;
        u8Port1InvFraCount = 0;
        u8Port1AptErrFraCount = 0;
        u8Port0ForErrCount = 0;
        u8Port1ForErrCount = 0;
        u8DataFrmProcessingErrCount = 0;
        u8PIDErrCount = 0;
        u8Port0LinkLostCount = 0;
        u8Port1LinkLostCount = 0;
        u16MCUUpSlaveLost = 0;
        u16SlaveAdderss = 0;
        u16ESCVerInfor = 0;
        u16MCUUpXMLVerInfor = 0;
        u16SoftVersion = 0;
        u16ARMSetLinkEnhanSwitch = 0;
        u16EtherCATXMLReset = 0;
    }

    quint8 u8LinkState;                 /* PHY - link状态(Bit0为端口0,Bit1为端口1，0:No Link，1:Link) */
    quint8 u8EscState;                  /* EtherCAT状态机(1：Init 2：PreOP 4：SafeOP 8：OP) */
    quint16 u16AppFaultCode;            /* 通信故障码 */
    quint16 u16AppStateCode;            /* 应用层状态码 */
    quint8 u8Port0InvFraCount;          /* 端口0无效帧计数 */
    quint8 u8Port0AptErrFraCount;       /* 端口0接收错误帧计数 */
    quint8 u8Port1InvFraCount;          /* 端口1无效帧计数 */
    quint8 u8Port1AptErrFraCount;       /* 端口1接收错误帧计数 */
    quint8 u8Port0ForErrCount;          /* [7:0]: 端口0转发错误计数 */
    quint8 u8Port1ForErrCount;          /* [15:8]: 端口1转发错误计数 */
    quint8 u8DataFrmProcessingErrCount; /* [7:0]: 数据帧处理单元错误计数 */
    quint8 u8PIDErrCount;               /* [15:8]: PDI错误计数 */
    quint8 u8Port0LinkLostCount;        /* [7:0]: 端口0链接丢失计数 */
    quint8 u8Port1LinkLostCount;        /* [15:8]: 端口1链接丢失计数 */
    quint16 u16MCUUpSlaveLost;          /* MCU上传从站累积丢帧计数; ARM读 */
    quint16 u16SlaveAdderss;            /* MCU上传主站设置的站点正名; ARM读 */
    quint16 u16ESCVerInfor;             /* MCU上传ESC的版本信息; ARM读 */
    quint16 u16MCUUpXMLVerInfor;        /* MCU上传XML版本信息; ARM读 */
    quint16 u16SoftVersion;             /* MCU上传软件版本号; ARM读 */
    quint16 u16ARMSetLinkEnhanSwitch;      //ARM设定链路增强开关, ARM可读可写(0-open; 1-close)
    quint16 u16EtherCATXMLReset;           //ARM设定执行XML复位(0-open; 1-close)
} INO_ETHCAT_PROP;

// 读取Ethcat
typedef struct stInoEthcatSts
{
    stInoEthcatSts()
    {
        ActiveSts = 0;   // 0-未开启
        ConnectSts = 0;  // 0-未连接
        SiteAlias = 0;
        MaxFramLossTimes = 8;
    }
    unsigned char ActiveSts;          // Ethcat激活状态:0-未开启，1-已开启
    unsigned char ConnectSts;         // Ethcat连接状态:0 - 未连接，1 - 已连接
    unsigned short SiteAlias;         // 站点别名（默认值为0）
    unsigned short MaxFramLossTimes;  // 最大丢站次数（默认值为8次）
} InoEthcatSts;
