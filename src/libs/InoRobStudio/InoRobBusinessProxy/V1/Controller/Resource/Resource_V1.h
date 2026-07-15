#pragma once
#include "dllspec.h"
#include <QObject>
#include "IInoRobBusiness.h"
#include "../../GlobalDataTypes_V1.h"
#include "GlobalVar/VarMonitor_V1.h"
#include "../Fieldbus/Fieldbus_V1.h"
#include "../../Project/ProjectHelper_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

// 全局变量
constexpr int GLOBAL_VAR_B_NUM_V1 = 256;       // 全局B变量总个数
constexpr int GLOBAL_VAR_R_NUM_V1 = 256;       // 全局R变量总个数
constexpr int GLOBAL_VAR_D_NUM_V1 = 256;       // 全局D变量总个数
constexpr int GLOBAL_VAR_PR_NUM_V1 = 256;      // 全局PR变量总个数
constexpr int GLOBAL_VAR_STRING_NUM_V1 = 256;  // 全局String变量总个数
constexpr int GLOBAL_P_NUM_V1 = 10000;         // 全局P变量总个数
constexpr int GLOBAL_P_PAGE_SIZE_V1 = 5;       // 全局P变量每帧数据大小
constexpr int GLOBAL_JP_NUM_V1 = 10000;        // 全局P变量总个数
constexpr int GLOBAL_JP_PAGE_SIZE_V1 = 5;      // 全局P变量每帧数据大小

// 总线
constexpr int STANDARD_IO_STARTINDEX_V1 = 0;           // 标准IO起始下标(以byte参考)
constexpr int STANDARD_IO_SIZE_V1 = 16;                // 标准IO大小(以byte参考)
constexpr int TOOL_IO_STARTINDEX_V1 = 16;              // 协作工具IO起始下标(以byte参考)
constexpr int TOOL_IO_SIZE_V1 = 2;                     // 协作工具IO大小(以byte参考)
constexpr int SLAVE_FIELDBUS_IO_STARTINDEX_V1 = 64;    // 从站现场总线IO起始下标(以byte参考)
constexpr int SLAVE_FIELDBUS_IO_SIZE_V1 = 512;         // 从站现场总线IO大小(以byte参考)
constexpr int MASTER_FIELDBUS_IO_STARTINDEX_V1 = 832;  // 主站现场总线IO起始下标(以byte参考)
constexpr int MASTER_FIELDBUS_IO_SIZE_V1 = 256;        // 主站现场总线IO大小(以byte参考)
constexpr int MEMORY_IO_STARTINDEX_V1 = 1600;          // 内存IO起始下标(以byte参考)
constexpr int MEMORY_IO_SIZE_V1 = 128;                 // 内存IO大小(以byte参考)

// AD DA
constexpr int ADDA_MAX_SIZE_V1 = 16;                  // AD、DA最大大小
constexpr int COBOT_CONTROLLER_ADDA_MAX_SIZE_V1 = 2;  // 协作电柜自带的AD DA两个
constexpr int ECAT_ADDA_STARTINDEX_V1 = 64;           // EtherCATADDA起始索引
constexpr int ECAT_ADDA_ENDINDEX_V1 = 80;             // EtherCATADDA结束索引

// sysIO
constexpr int SYSIO_SIZE_V1 = 16;  // IO端子数量

constexpr int SERVO_IS620N_NUM_V1 = 25;  // IS620N伺服个数
constexpr int SERVO_IS820N_NUM_V1 = 33;  // IS820N伺服个数
constexpr int SERVO_IS660N_NUM_V1 = 32;  // IS660N伺服个数
constexpr int SERVO_SV660N_NUM_V1 = 31;  // SV660N伺服个数

const int TCP_CLIENT_NUM_V1 = 16;  // TCP连接数量
const int MC_CONNECT_NUM_V1 = 4;   // MC连接数量

// B变量数据
struct GlobalVarBData_V1
{
    int index;            // 下标
    unsigned char value;  // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarBData_V1()
    {
        index = -1;
        value = 0;
        favorite = false;
    }

    GlobalVarBData_V1 &operator=(const GlobalVarBData_V1 &other)
    {
        index = other.index;
        value = other.value;
        labs = other.labs;
        remarks = other.remarks;
        favorite = other.favorite;
        return (*this);
    }

    void clear()
    {
        index = -1;
        value = 0;
        labs.clear();
        remarks.clear();
        favorite = false;
    }
};

// R变量数据
struct GlobalVarRData_V1
{
    int index;            // 下标
    int value;            // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarRData_V1()
    {
        index = -1;
        value = 0;
        favorite = false;
    }

    GlobalVarRData_V1 &operator=(const GlobalVarRData_V1 &other)
    {
        index = other.index;
        value = other.value;
        labs = other.labs;
        remarks = other.remarks;
        favorite = other.favorite;
        return (*this);
    }

    void clear()
    {
        index = -1;
        value = 0;
        labs.clear();
        remarks.clear();
        favorite = false;
    }
};

// D变量数据
struct GlobalVarDData_V1
{
    int index;            // 下标
    double value;         // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarDData_V1()
    {
        index = -1;
        value = 0.0;
        favorite = false;
    }

    GlobalVarDData_V1 &operator=(const GlobalVarDData_V1 &other)
    {
        index = other.index;
        value = other.value;
        labs = other.labs;
        remarks = other.remarks;
        favorite = other.favorite;
        return (*this);
    }

    void clear()
    {
        index = -1;
        value = 0.0;
        labs.clear();
        remarks.clear();
        favorite = false;
    }
};

// 全局P点数据
struct GlobalPData_V1
{
    RAM_P_V1 globalP;     // 全局P点值
    std::string labs;     // 标签
    std::string remarks;  // 备注
};

// 全局JP点数据
struct GlobalJPData_V1
{
    RAM_J_V1 globalJP;    // 全局JP点值
    std::string labs;     // 标签
    std::string remarks;  // 备注
};

// AD、DA状态 协作电柜自带的AD DA
struct Cobot_ADDA_Status_V1
{
    unsigned short type = 0;                // 1AD 2DA
    unsigned short setModelEnable = 0;      // 是否可以配置电流/电压模式
    unsigned short index = 0;               // 协作 电柜101 102 末端103 104
    unsigned short currentConfigState = 0;  // 0已配置 1配置中
    unsigned short kind = 0;                // 1 电流  2 电压
    unsigned short out = 0;                 // 输出开关 0 不输出 1 输出
    unsigned short deviceType = 0;          // 类别 0IRLink 1EtherCat 2末端 3电柜
    double minValue = 0.0;                  // 最小值
    double maxValue = 20.0;                 // 最大值 默认电流 0-20mA
    double actualValue = 0.0;               // 实际的值

    Cobot_ADDA_Status_V1 &operator=(const Cobot_ADDA_Status_V1 &other)
    {
        this->type = other.type;
        this->index = other.index;
        this->setModelEnable = other.setModelEnable;
        this->currentConfigState = other.currentConfigState;
        this->deviceType = other.deviceType;
        this->kind = other.kind;
        this->minValue = other.minValue;
        this->maxValue = other.maxValue;
        this->actualValue = other.actualValue;
        this->out = other.out;
        return (*this);
    }

    // 比较  相同返回ture， 不相同返回false
    bool compare(const Cobot_ADDA_Status_V1 &other)
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
        return true;
    }
};

// AD、DA数据 协作电柜自带的AD DA
struct Cobot_ADDA_Data_V1
{
    Cobot_ADDA_Status_V1 status;  // 状态
    std::string labs;             // 标签
    std::string remarks;          // 备注
};

// IRLink AD、DA数据
struct IRLinkADDAData_V1
{
    IRLinkADDAStatus_V1 status;  // IRLink状态
    std::string labs;            // 标签
    std::string remarks;         // 备注
};

// ECat AD、DA数据
struct ECatADDAData_V1
{
    EcatAdDaState_V1 status;  // ECAT状态
    std::string labs;         // 标签
    std::string remarks;      // 备注
};

struct EthInfo_V1
{
    bool isDHCP = false;             // true 动态，false 静态
    std::string ipAddr = "0.0.0.0";  // IP地址
};

struct ControllerEthInfo_V1
{
    EthInfo_V1 eth0;  // 网口1
    EthInfo_V1 eth1;  // 网口2
};

// TCP连接状态
struct ModbusTCPConnectStatus_V1
{
    unsigned char owner = 0;        // 控制权 0-未开启，1-二次开发，2-控制器
    unsigned char status = 0;       // 运行情况 0-未运行，1-运行
    unsigned short port = 502;      // 端口号
    unsigned short framedelay = 1;  // 帧间隔

    bool compare(const ModbusTCPConnectStatus_V1 &other)
    {
        if (owner != other.owner)
            return false;
        if (status != other.status)
            return false;
        if (port != other.port)
            return false;
        if (framedelay != other.framedelay)
            return false;

        return true;
    }
};

// RTU连接状态
struct ModbusRTUConnectStatus_V1
{
    unsigned char owner = 0;        // Modbus控制权 0-未开启，1-二次开发，2-控制器
    unsigned char status = 0;       // Modbus 运行情况 0-未运行，1-运行
    unsigned char baud = 5;         // 波特率，索引值，其具体值见Baud数组
    unsigned char stopbits = 0;     // 停止位 0-1位 1-2位
    unsigned char databits = 0;     // 数据位 0-7位 1-8位
    unsigned char parity = 0;       // 奇偶校验 0-无校验 1-奇校验 2-偶校验
    unsigned char tmode = 0;        // 传输模式 0-RTU 1-ASCII
    unsigned char slaveid = 1;      // 站点号
    unsigned short framedelay = 5;  // 帧间隔
    unsigned short timeout = 0;     // 超时时间

    bool compare(const ModbusRTUConnectStatus_V1 &other)
    {
        if (owner != other.owner)
            return false;
        if (status != other.status)
            return false;
        if (baud != other.baud)
            return false;
        if (stopbits != other.stopbits)
            return false;
        if (databits != other.databits)
            return false;
        if (parity != other.parity)
            return false;
        if (tmode != other.tmode)
            return false;
        if (slaveid != other.slaveid)
            return false;
        if (framedelay != other.framedelay)
            return false;
        if (timeout != other.timeout)
            return false;

        return true;
    }
};

// Modbus连接状态
struct ModbusConnectStatus_V1
{
    unsigned char modbusAddrType = 0;                                    // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCPConnectStatus_V1 modbusTcpCS;                               // ModbusTCP配置结构体
    ModbusRTUConnectStatus_V1 modbusRtuCS;                               // ModbusRtu配置结构
    unsigned char modbusTcpConnectFlag[TCP_CLIENT_NUM_V1] = { 0 };       // modbusTcp连接状态，0表示未连接，1表示已连
    unsigned char modbusTcpClientIP[TCP_CLIENT_NUM_V1][16] = { { 0 } };  // 主站IP地址（第一行表示第一个连接上的主站的IP）
    unsigned short modbusTcpClientPort[TCP_CLIENT_NUM_V1] = { 0 };       // 主站端口（第一元素表示第一个连接上的主站的端口）

    // 比较 相同返回ture， 不相同返回false
    bool compare(const ModbusConnectStatus_V1 &other)
    {
        if (modbusAddrType != other.modbusAddrType)
            return false;
        if (!modbusTcpCS.compare(other.modbusTcpCS))
            return false;
        if (!modbusRtuCS.compare(other.modbusRtuCS))
            return false;
        if (std::memcmp(modbusTcpConnectFlag, other.modbusTcpConnectFlag, TCP_CLIENT_NUM) != 0)
            return false;
        for (int i = 0; i < TCP_CLIENT_NUM; i++)
        {
            if (std::memcmp(modbusTcpClientIP[i], other.modbusTcpClientIP[i], 16) != 0)
                return false;
        }
        if (std::memcmp(modbusTcpConnectFlag, other.modbusTcpConnectFlag, TCP_CLIENT_NUM) != 0)
            return false;

        return true;
    }
};

// EthernetIP状态
struct EthernetIPStatus_V1
{
    unsigned char active = 0;            // EIP激活状态:0-未开启，1-已开启
    unsigned char connect = 0;           // EIP连接状态:0-未连接，1-已连接
    unsigned char masterIP[16] = { 0 };  // EIP主站(客户端)IP地址
    unsigned short masterPort = 502;     // EIP主站(客户端)的端口
    unsigned short slavePort = 44818;    // EIP从站(服务器)端口,暂时固定为44818

    EthernetIPStatus_V1 &operator=(const EthernetIPStatus_V1 &other)
    {
        this->active = other.active;
        this->connect = other.connect;
        std::copy(other.masterIP, other.masterIP + 16, this->masterIP);
        this->masterPort = other.masterPort;
        this->slavePort = other.slavePort;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const EthernetIPStatus_V1 &other)
    {
        if (active != other.active)
            return false;
        if (connect != other.connect)
            return false;
        if (std::memcmp(masterIP, other.masterIP, 16) != 0)
            return false;
        if (masterPort != other.masterPort)
            return false;
        if (slavePort != other.slavePort)
            return false;

        return true;
    }
};

// EtherCAT状态
struct EtherCATStatus_V1
{
    unsigned char active = 0;             // Ethcat激活状态:0-未开启，1-已开启
    unsigned char connect = 0;            // Ethcat连接状态:0-未连接，1-已连接
    unsigned short siteAlias = 0;         // 站点别名（默认值为0）
    unsigned short maxFramLossTimes = 8;  // 最大丢站次数（默认值为8次）

    EtherCATStatus_V1 &operator=(const EtherCATStatus_V1 &other)
    {
        this->active = other.active;
        this->connect = other.connect;
        this->siteAlias = other.siteAlias;
        this->maxFramLossTimes = other.maxFramLossTimes;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const EtherCATStatus_V1 &other)
    {
        if (active != other.active)
            return false;
        if (connect != other.connect)
            return false;
        if (siteAlias != other.siteAlias)
            return false;
        if (maxFramLossTimes != other.maxFramLossTimes)
            return false;

        return true;
    }
};

// MC连接状态
struct MCConnectStatus_V1
{
    unsigned char connectIndex = 0;      // 连接索引
    unsigned char serverIP[16] = { 0 };  // MC 服务器IP
    unsigned short port = 0;             // MC 端口号
    unsigned char connect = 0;           // 读连接状态 0未连接，1已连接；（写命令：1连接；0是断开）
    unsigned char autoReconnect = 0;     // 0- 不进行重连， 1- 进行自动重连 (断电，激活 MC开关时)

    MCConnectStatus_V1 &operator=(const MCConnectStatus_V1 &other)
    {
        this->connectIndex = other.connectIndex;
        std::copy(other.serverIP, other.serverIP + 16, this->serverIP);
        this->port = other.port;
        this->connect = other.connect;
        this->autoReconnect = other.autoReconnect;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const MCConnectStatus_V1 &other)
    {
        if (connectIndex != other.connectIndex)
            return false;
        if (std::memcmp(serverIP, other.serverIP, 16) != 0)
            return false;
        if (port != other.port)
            return false;
        if (autoReconnect != other.autoReconnect)
            return false;

        return true;
    }
};

// Profinet总线连接状态
struct ProfinetConnectStatus_V1
{
    unsigned char activeStatus = 0;          // PN激活状态:0-未开启，1-已开启
    unsigned char connectStatus = 0;         // PN连接状态:0-未连接，1-已连接
    char ip[16] = { 0 };                     // ip地址
    char defaultGateWay[16] = { 0 };         // 默认网关
    char macAddress[18] = { 0 };             // MAC地址
    unsigned short version = 0;              // 版本号
    unsigned short maxFrameDropNumber = 10;  // 已设置的最大丢帧次数

    bool compare(const ProfinetConnectStatus_V1 &other)
    {
        if (activeStatus != other.activeStatus)
            return false;
        if (connectStatus != other.connectStatus)
            return false;
        if (std::strncmp(ip, other.ip, 16) != 0)
            return false;
        if (std::strncmp(defaultGateWay, other.defaultGateWay, 16) != 0)
            return false;
        if (std::strncmp(macAddress, other.macAddress, 18) != 0)
            return false;
        if (version != other.version)
            return false;
        if (maxFrameDropNumber != other.maxFrameDropNumber)
            return false;

        return true;
    }
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Resource_V1 : public QObject
{
    Q_OBJECT
#pragma region 构造与析构

private:
    IResource *_resource = nullptr;

public:
    Resource_V1(IResource *resource);
    ~Resource_V1();

#pragma endregion

#pragma region 子模型

private:
    VarMonitor_V1 *_varMonitor_V1 = nullptr;

public:
    VarMonitor_V1 *GetVarMonitor();
    bool SetVarMonitor(VarMonitor_V1 *varMonitor_V1);

#pragma endregion

#pragma region 数据转换

public:
    static bool GlobalVarBData_ToProxy(const GlobalVarBData &globalVarBData, GlobalVarBData_V1 &globalVarBData_V1);
    static bool GlobalVarBData_FromProxy(const GlobalVarBData_V1 &globalVarBData_V1, GlobalVarBData &globalVarBData);

    static bool GlobalVarRData_ToProxy(const GlobalVarRData &globalVarRData, GlobalVarRData_V1 &globalVarRData_V1);
    static bool GlobalVarRData_FromProxy(const GlobalVarRData_V1 &globalVarRData_V1, GlobalVarRData &globalVarRData);

    static bool GlobalVarDData_ToProxy(const GlobalVarDData &globalVarDData, GlobalVarDData_V1 &globalVarDData_V1);
    static bool GlobalVarDData_FromProxy(const GlobalVarDData_V1 &globalVarDData_V1, GlobalVarDData &globalVarDData);

    static bool GlobalPData_ToProxy(const GlobalPData &globalPData, GlobalPData_V1 &globalPData_V1);
    static bool GlobalPData_FromProxy(const GlobalPData_V1 &globalPData_V1, GlobalPData &globalPData);

    static bool GlobalJPData_ToProxy(const GlobalJPData &globalJPData, GlobalJPData_V1 &globalJPData_V1);
    static bool GlobalJPData_FromProxy(const GlobalJPData_V1 &globalJPData_V1, GlobalJPData &globalJPData);

    static bool Cobot_ADDA_Status_ToProxy(const Cobot_ADDA_Status &cobot_ADDA_Status, Cobot_ADDA_Status_V1 &cobot_ADDA_Status_V1);
    static bool Cobot_ADDA_Status_FromProxy(const Cobot_ADDA_Status_V1 &cobot_ADDA_Status_V1, Cobot_ADDA_Status &cobot_ADDA_Status);

    static bool Cobot_ADDA_Data_ToProxy(const Cobot_ADDA_Data &cobot_ADDA_Data, Cobot_ADDA_Data_V1 &cobot_ADDA_Data_V1);
    static bool Cobot_ADDA_Data_FromProxy(const Cobot_ADDA_Data_V1 &cobot_ADDA_Data_V1, Cobot_ADDA_Data &cobot_ADDA_Data);

    static bool IRLinkADDAData_ToProxy(const IRLinkADDAData &irLinkADDAData, IRLinkADDAData_V1 &irLinkADDAData_V1);
    static bool IRLinkADDAData_FromProxy(const IRLinkADDAData_V1 &irLinkADDAData_V1, IRLinkADDAData &irLinkADDAData);

    static bool ECatADDAData_ToProxy(const ECatADDAData &eCatADDAData, ECatADDAData_V1 &eCatADDAData_V1);
    static bool ECatADDAData_FromProxy(const ECatADDAData_V1 &eCatADDAData_V1, ECatADDAData &eCatADDAData);

    static bool EthInfo_ToProxy(const EthInfo &ethInfo, EthInfo_V1 &ethInfo_V1);
    static bool EthInfo_FromProxy(const EthInfo_V1 &ethInfo_V1, EthInfo &ethInfo);

    static bool ControllerEthInfo_ToProxy(const ControllerEthInfo &controllerEthInfo, ControllerEthInfo_V1 &controllerEthInfo_V1);
    static bool ControllerEthInfo_FromProxy(const ControllerEthInfo_V1 &controllerEthInfo_V1, ControllerEthInfo &controllerEthInfo);

    static bool ModbusTCPConnectStatus_ToProxy(const ModbusTCPConnectStatus &modbusTCPConnectStatus, ModbusTCPConnectStatus_V1 &modbusTCPConnectStatus_V1);
    static bool ModbusTCPConnectStatus_FromProxy(const ModbusTCPConnectStatus_V1 &modbusTCPConnectStatus_V1, ModbusTCPConnectStatus &modbusTCPConnectStatus);

    static bool ModbusRTUConnectStatus_ToProxy(const ModbusRTUConnectStatus &modbusRTUConnectStatus, ModbusRTUConnectStatus_V1 &modbusRTUConnectStatus_V1);
    static bool ModbusRTUConnectStatus_FromProxy(const ModbusRTUConnectStatus_V1 &modbusRTUConnectStatus_V1, ModbusRTUConnectStatus &modbusRTUConnectStatus);

    static bool ModbusConnectStatus_ToProxy(const ModbusConnectStatus &modbusConnectStatus, ModbusConnectStatus_V1 &modbusConnectStatus_V1);
    static bool ModbusConnectStatus_FromProxy(const ModbusConnectStatus_V1 &modbusConnectStatus_V1, ModbusConnectStatus &modbusConnectStatus);

    static bool EthernetIPStatus_ToProxy(const EthernetIPStatus &ethernetIPStatus, EthernetIPStatus_V1 &ethernetIPStatus_V1);
    static bool EthernetIPStatus_FromProxy(const EthernetIPStatus_V1 &ethernetIPStatus_V1, EthernetIPStatus &ethernetIPStatus);

    static bool EtherCATStatus_ToProxy(const EtherCATStatus &etherCATStatus, EtherCATStatus_V1 &etherCATStatus_V1);
    static bool EtherCATStatus_FromProxy(const EtherCATStatus_V1 &etherCATStatus_V1, EtherCATStatus &etherCATStatus);

    static bool MCConnectStatus_ToProxy(const MCConnectStatus &mcConnectStatus, MCConnectStatus_V1 &mcConnectStatus_V1);
    static bool MCConnectStatus_FromProxy(const MCConnectStatus_V1 &mcConnectStatus_V1, MCConnectStatus &mcConnectStatus);

    static bool ProfinetConnectStatus_ToProxy(const ProfinetConnectStatus &profinetConnectStatus, ProfinetConnectStatus_V1 &profinetConnectStatus_V1);
    static bool ProfinetConnectStatus_FromProxy(const ProfinetConnectStatus_V1 &profinetConnectStatus_V1, ProfinetConnectStatus &profinetConnectStatus);

public:
    // IO类型
    enum IOType_V1
    {
        COMMON_IO_V1 = 0,       // 常用IO(设置了标签或者备注)
        STANDARD_IO_V1,         // 标准IO
        SLAVE_FIELDBUS_IO_V1,   // 从站现场总线IO
        MASTER_FIELDBUS_IO_V1,  // 主站现场总线IO
        MEMORY_IO_V1,           // 内存IO
        TOOL_IO_V1              // 末端IO
    };
    static Resource_V1::IOType_V1 IOType_ToProxy(IResource::IOType ioType);
    static IResource::IOType IOType_FromProxy(Resource_V1::IOType_V1 ioType_V1);

    // 数据进制
    enum SystemType_V1
    {
        DECIMAL_V1 = 0,  // 十进制
        BINARY_V1,       // 二进制
        HEXADECIMAL_V1   // 十六进制
    };
    static Resource_V1::SystemType_V1 SystemType_ToProxy(IResource::SystemType systemType);
    static IResource::SystemType SystemType_FromProxy(Resource_V1::SystemType_V1 systemType_V1);

    // 显示类型
    enum ShowType_V1
    {
        BIT_V1 = 0,   // bit
        BYTE_V1 = 1,  // 字节
        WORD_V1 = 2   // 字
    };
    static Resource_V1::ShowType_V1 ShowType_ToProxy(IResource::ShowType showType);
    static IResource::ShowType ShowType_FromProxy(Resource_V1::ShowType_V1 showType_V1);

#pragma endregion

#pragma region 业务方法

public:
    // 获取pt文件列表
    int getPointFileListFromController(vector<std::string> &fileList);

    /**
     * @brief 设置全局B变量调度
     * @param scheduler true调度 false不调度
     */
    void setGlobalVarBScheduler(bool scheduler);

    /**
     * @brief 与控制器通信读取所有全局B变量值
     * @param values 全局B变量值
     * @return ERR_OK为成功，其它见错误码
     */
    int readGlobalVarBValues(std::array<int8u, GLOBAL_VAR_B_NUM_V1> &values);

    /**
     * @brief 与控制器通信设置一个全局B变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    int writeGlobalVarBValue(const unsigned char value, const unsigned int index);

    /**
     * @brief 获取所有全局B变量数据
     */
    std::vector<GlobalVarBData_V1> getGlobalVarBDatas();

    /**
     * @brief 设置一个全局B变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarBFavorite(const bool favorite, const int index);

    /**
     * @brief 获取全局B变量是否显示收藏
     * @return true显示 false不显示
     */
    bool getGlobalVarBShowFavorite();

    /**
     * @brief 设置全局B变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    bool setGlobalVarBShowFavorite(const bool show);

    /**
     * @brief 获取所有全局B变量值
     */
    std::array<unsigned char, GLOBAL_VAR_B_NUM_V1> getGlobalVarBValues();

    /**
     * @brief 设置一个全局B变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarBValue(const unsigned char value, const unsigned int index);

    /**
     * @brief 更新全局B变量数据
     * @return true更新成功 false更新失败
     */
    bool updataGlobalVarBDatas();

    /**
     * @brief 设置全局R变量调度
     * @param scheduler true调度 false不调度
     */
    void setGlobalVarRScheduler(bool scheduler);

    /**
     * @brief 与控制器通信读取所有全局R变量值
     * @param values 全局R变量值
     * @return ERR_OK为成功，其它见错误码
     */
    int readGlobalVarRValues(std::array<int, GLOBAL_VAR_R_NUM_V1> &values);

    /**
     * @brief 与控制器通信设置一个全局R变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    int writeGlobalVarRValue(const int value, const unsigned int index);

    /**
     * @brief 获取所有全局R变量数据
     */
    std::vector<GlobalVarRData_V1> getGlobalVarRDatas();

    /**
     * @brief 设置一个全局R变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     * @retun true成功 false失败
     */
    bool setGlobalVarRFavorite(const bool favorite, const int index);

    /**
     * @brief 获取全局R变量是否显示收藏
     * @return true显示 false不显示
     */
    bool getGlobalVarRShowFavorite();

    /**
     * @brief 设置全局R变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    bool setGlobalVarRShowFavorite(const bool show);

    /**
     * @brief 获取所有全局R变量值
     */
    std::array<int, GLOBAL_VAR_R_NUM_V1> getGlobalVarRValues();

    /**
     * @brief 设置一个全局R变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarRValue(const int value, const unsigned int index);

    /**
     * @brief 更新全局R变量数据
     * @return true更新成功 false更新失败
     */
    bool updataGlobalVarRDatas();

    /**
     * @brief 设置全局D变量调度
     * @param scheduler true调度 false不调度
     */
    void setGlobalVarDScheduler(bool scheduler);

    /**
     * @brief 与控制器通信读取所有全局D变量值
     * @param values 全局D变量值
     * @return ERR_OK为成功，其它见错误码
     */
    int readGlobalVarDValues(std::array<double, GLOBAL_VAR_D_NUM_V1> &values);

    /**
     * @brief 与控制器通信设置一个全局D变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    int writeGlobalVarDValue(const double value, const unsigned int index);

    /**
     * @brief 获取所有全局D变量数据
     */
    std::vector<GlobalVarDData_V1> getGlobalVarDDatas();

    /**
     * @brief 设置一个全局D变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     */
    bool setGlobalVarDFavorite(const bool favorite, const int index);

    /**
     * @brief 获取全局D变量是否显示收藏
     * @return true显示 false不显示
     */
    bool getGlobalVarDShowFavorite();

    /**
     * @brief 设置全局D变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    bool setGlobalVarDShowFavorite(const bool show);

    /**
     * @brief 获取所有全局D变量值
     */
    std::array<double, GLOBAL_VAR_D_NUM_V1> getGlobalVarDValues();

    /**
     * @brief 设置一个全局D变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarDValue(const double value, const unsigned int index);

    /**
     * @brief 更新全局D变量数据
     * @return true更新成功 false更新失败
     */
    bool updataGlobalVarDDatas();

    /**
     * @brief 设置全局PR变量调度
     * @param scheduler true调度 false不调度
     */
    void setGlobalVarPRScheduler(bool scheduler);

    /**
     * @brief 与控制器通信读取所有全局PR变量值
     * @param values 全局PR变量值
     * @return ERR_OK为成功，其它见错误码
     */
    int readGlobalVarPRValues(std::vector<Pose_V1> &values);

    /**
     * @brief 与控制器通信设置一个全局PR变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    int writeGlobalVarPRValue(const Pose_V1 &value, const unsigned int index);

    /**
     * @brief 获取所有全局变量PR的值
     */
    std::vector<Pose_V1> getGlobalVarPRValues();

    /**
     * @brief 检查当前是否允许设置全局变量PR值
     * @return true允许 false不允许
     */
    bool allowSetGlobalVarPRValue();

    /**
     * @brief 设置一个全局PR变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarPRValue(const Pose_V1 &value, const unsigned int index);

    /**
     * @brief 更新全局PR变量数据
     * @return true成功 false失败
     */
    bool updateGlobalVarPRDatas();

    /**
     * @brief 设置全局string变量调度
     * @param scheduler true调度 false不调度
     */
    void setGlobalVarStringScheduler(bool scheduler);

    /**
     * @brief 与控制器通信读取所有全局String变量值
     * @param values 全局string变量值
     * @return ERR_OK为成功，其它见错误码
     */
    int readGlobalVarStringValues(std::array<std::string, GLOBAL_VAR_STRING_NUM_V1> &values);

    /**
     * @brief 与控制器通信设置一个全局String变量值
     * @param value 值
     * @param index 下标
     * @return
     */
    int writeGlobalVarStringValue(const std::string &value, const unsigned int index);

    /**
     * @brief 获取全局String变量所有数据
     */
    std::array<std::string, GLOBAL_VAR_STRING_NUM_V1> getGlobalVarStringDatas();

    /**
     * @brief 设置一个全局String变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    bool setGlobalVarStringValue(const std::string &value, const unsigned int index);

    /**
     * @brief 更新全局String变量数据
     * @return true成功 false失败
     */
    bool updateGlobalVarStringDatas();

    /**
     * @brief 与控制器通信读取全局P点位值
     * @param values 值
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return ERR_OK为成功，其他为失败
     */
    int readGlobalPValues(std::vector<RAM_P_V1> &values, const int pageIndex, const int pageNum);

    /**
     * @brief 获取全局P点数据
     * @param datas 数据
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return true成功 false失败
     */
    bool getGlobalPDatas(std::vector<GlobalPData_V1> &datas, const int pageIndex, const int pageNum, bool isNeedErrorPrint = true);

    /**
     * @brief 与控制器通信读取全局JP点位值
     * @param values 值
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return ERR_OK为成功，其他为失败
     */
    int readGlobalJPValues(std::vector<RAM_J_V1> &values, const int pageIndex, const int pageNum);

    /**
     * @brief 获取全局JP点数据
     * @param datas 数据
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return true成功 false失败
     */
    bool getGlobalJPDatas(std::vector<GlobalJPData_V1> &datas, const int pageIndex, const int pageNum, bool isNeedMsgPrint = true);

    /**
     * @brief 设置Input调度
     * @param scheduler true调度 false不调度
     */
    void setInputScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信获取常用输入状态
     *        每次与控制器通信最多获取8个字节数据
     * @param showType 显示类型（查看ShowType枚举）
     * @param size 常用输入数量
     * @param inputIndexs 常用输入下标
     * @param status 读取状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCommonInputStatus(const ShowType_V1 showType, const unsigned int size, const std::vector<unsigned short> &inputIndexs, std::vector<int8u> &status);

    /**
     * @brief 与控制器通信获取Input状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    int readInputStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf);

    /**
     * @brief 与控制器通信获取Input强制高状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    int readInputForceHighStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf);

    /**
     * @brief 与控制器通信获取强制低状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    int readInputForceLowStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf);

    /**
     * @brief 与控制器通信写Input状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf Input状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeInputStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf);

    /**
     * @brief 与控制器通信写Input强制高状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 强制高状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeInputForceHighStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf);

    /**
     * @brief 与控制器通信写Input强制低状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 强制低状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeInputForceLowStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf);

    /**
     * @brief 设置InputIO类型
     * @param ioType IO类型
     */
    void setInputIOType(const IOType_V1 ioType);

    /**
     * @brief 获取InputIO类型
     */
    Resource_V1::IOType_V1 getInputIOType();

    /**
     * @brief 设置Input显示类型
     * @param showType 显示类型
     */
    void setInputShowType(const ShowType_V1 showType);

    /**
     * @brief 获取Input显示类型
     */
    ShowType_V1 getInputShowType();

    /**
     * @brief 获取常用Input值
     */
    std::vector<int8u> getCommonInputValues();

    /**
     * @brief 获取标准Input值
     */
    std::array<int8u, STANDARD_IO_SIZE_V1> getStandardInputValues();

    /**
     * @brief 获取从站现场总线Input值
     */
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE_V1> getSlaveFieldbusInputValues();

    /**
     * @brief 获取主站现场总线Input值
     */
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE_V1> getMasterFieldbusInputValues();

    /**
     * @brief 获取内存Input值
     */
    std::array<int8u, MEMORY_IO_SIZE_V1> getMemoryInputValues();

    /**
     * @brief 获取标准Input强制高值
     */
    std::array<int8u, STANDARD_IO_SIZE_V1> getStandardInputForceHighValues();

    /**
     * @brief 获取标准Input强制低值
     */
    std::array<int8u, STANDARD_IO_SIZE_V1> getStandardInputForceLowValues();

    /**
     * @brief 根据ShowType获取Input标签与备注
     */
    IoLabelItems_V1 getInputLabelAndRemark();

    /**
     * @brief 获取常用Input下标
     */
    std::vector<unsigned short> getCommonInputIndexs();

    /**
     * @brief 设置标准输入强制状态
     *        强制高->强制低  强制低->强制高
     * @param index 下标(bit下标)
     * @return true成功 false失败
     */
    bool setStandardInputForceStatus(const unsigned int index);

    /**
     * @brief 设置标准输入状态
     * @param index 下标(bit下标)
     * @return true成功 false失败
     */
    bool setStandardInputStatus(const unsigned int index);

    /**
     * @brief 设置内存输入状态
     *        按Bit设置
     * @param statusIndex 界面中的下标（非IO下标）
     * @param isOn true:on false:off
     * @return true成功 false失败
     */
    bool setMemoryInputStatus(const unsigned int statusIndex, const bool isOn);

    /**
     * @brief 更新标准输入值（在设置标准输入之后调用，有改变发送改变信号）
     */
    void updateStandardInputValue();

    /**
     * @brief 更新Input标签、备注
     * @return true更新成功 false失败
     */
    bool updateInputLabelAndRemark();

    /**
     * @brief 更新常用Input数据
     * @return true成功 false失败
     */
    bool updateCommonInputDatas();

    /**
     * @brief 更新标准Input数据
     * @return true成功 false失败
     */
    bool updateStandardInputDatas();

    /**
     * @brief 更新从站现场总线Input数据
     * @return true成功 false失败
     */
    bool updateSlaveFieldbusInputDatas();

    /**
     * @brief 更新主站现场总线Input数据
     * @return true成功 false失败
     */
    bool updateMasterFieldbusInputDatas();

    /**
     * @brief 更新内存Input数据
     * @return true成功 false失败
     */
    bool updateMemoryInputDatas();

    /**
     * @brief 设置输出调度
     * @param scheduler true:调度 false:取消调度
     */
    void setOutputScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信获取常用输出状态
     *        每次与控制器通信最多获取8个字节数据
     * @param showType 显示类型（查看ShowType枚举）
     * @param size 常用输出数量
     * @param outputIndexs 常用输出下标
     * @param status 读取状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCommonOutputStatus(const ShowType_V1 showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &status);

    /**
     * @brief 与控制器通信获取常用输出控制权
     *        每次与控制器通信最多读取8个字节，读取到对应的bit位为0表示有控制权
     * @param showType 显示类型（查看ShowType枚举）目前只有BIT
     * @param size 常用输出数量
     * @param outputIndexs 常用输出下标
     * @param controls 读取控制权
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCommonOutputControls(const ShowType_V1 showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &controls);

    /**
     * @brief 与控制器通信读取输出状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 数量
     * @param dataBuf 读取状态起始地址（内存上需连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    int readOutputStatus(const int16u startByteId, const int16u byteNum, int8u *status);

    /**
     * @brief 与控制器通信读取输出控制权
     *        每次与控制器通信最多读取16个字节，读取到对应的bit位为0表示有控制权
     * @param startByteId 起始下标
     * @param byteNum 数量
     * @param pBuf 读取控制权起始地址（内存上需连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    int readOutputControls(const int16u startByteId, const int16u byteNum, std::vector<int8u> &controls);

    /**
     * @brief 与控制器通信写输出状态
     *        按Bit设置
     * @param bitIndex Bit下标
     * @param bitValue Bit值。0x00代表设置OFF，0x01代表设置ON
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeOutputStatusByBit(const int16u bitIndex, const int8u bitValue);

    /**
     * @brief 与控制器通信写输出状态
     *        按byte写
     * @param byteStartIndex byte开始下标
     * @param byteSize byte大小
     * @param status 状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeOutputStatusByByte(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status);

    /**
     * @brief 设置输出IO类型
     * @param ioType IO类型
     */
    void setOutputIOType(const IOType_V1 ioType);

    /**
     * @brief 获取输出IO类型
     */
    IOType_V1 getOutputIOType();

    /**
     * @brief 设置输出显示类型
     * @param showType 显示类型
     */
    void setOutputShowType(const ShowType_V1 showType);

    /**
     * @brief 获取输出显示类型
     */
    ShowType_V1 getOutputShowType();

    /**
     * @brief 获取常用输出值
     */
    std::vector<int8u> getCommonOutputValues();

    /**
     * @brief 获取标准输出值
     */
    std::array<int8u, STANDARD_IO_SIZE_V1> getStandardOutputValues();

    /**
     * @brief 获取从站现场总线输出值
     */
    std::array<int8u, SLAVE_FIELDBUS_IO_SIZE_V1> getSlaveFieldbusOutputValues();

    /**
     * @brief 获取主站现场总线输出值
     */
    std::array<int8u, MASTER_FIELDBUS_IO_SIZE_V1> getMasterFieldbusOutputValues();

    /**
     * @brief 获取内存输出值
     */
    std::array<int8u, MEMORY_IO_SIZE_V1> getMemoryOutputValues();

    /**
     * @brief 根据ShowType获取输出标签与备注
     */
    IoLabelItems_V1 getOutputLabelAndRemark();

    /**
     * @brief 获取常用输出下标
     */
    std::vector<unsigned short> getCommonOutputIndexs();

    /**
     * @brief 设置输出状态
     *        按Bit设置
     * @param index 界面中的下标（用于更新模型层值）
     * @param statusIndex 状态下标（bit下标）
     * @param isOn true:on false:off
     * @return true成功 false失败
     */
    bool setOutputStatus(const unsigned int index, const unsigned int statusIndex, const bool isOn);

    /**
     * @brief 设置输出状态
     *        按byte设置
     * @param byteStartIndex 开始下标（相对于byte）
     * @param byteSize 大小(相对于byte）
     * @param status 状态
     * @return true成功 false失败
     */
    bool setOutputStatus(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status);

    /**
     * @brief 更新输出标签、备注
     * @return true更新成功 false失败
     */
    bool updateOutputLabelAndRemark();

    /**
     * @brief 更新常用输出数据
     * @return true成功 false失败
     */
    bool updateCommonOutputDatas();

    /**
     * @brief 更新标准输出值
     * @return true成功 false失败
     */
    bool updateStandardOutputValues();

    /**
     * @brief 更新从站现场总线输出值
     * @return true成功 false失败
     */
    bool updateSlaveFieldbusOutputValues();

    /**
     * @brief 更新主站现场总线输出值
     * @return true成功 false失败
     */
    bool updateMasterFieldbusOutputValues();

    /**
     * @brief 更新内存输出值
     * @return true成功 false失败
     */
    bool updateMemoryOutputValues();

    /**
     * @brief 读取末端IO的配置
     * @return ERR_OK为成功，其它请见错误码
     */
    int readToolIoConfig(std::string &ans);
    /**
     * @brief 写末端IO的配置
     * @return ERR_OK为成功，其它请见错误码
     */
    int writeToolIoConfig(std::string &ans);
    /**
     * @brief 通知控制器设置配置监听状态
     * @return ERR_OK为成功，其它请见错误码
     */
    int setToolIOConfigMonitorState(bool state);

    /**
     * @brief 设置AD调度
     * @param scheduler true调度 false不调度
     */
    void setADScheduler(const bool scheduler);

    /**
     * @brief 设置AD显示类型
     * @param type AD显示类型
     */
    void setADShowType(const ADDAType_V1 type);

    /**
     * @brief 与控制器通信读取IRLinkAD值
     * @param values AD值
     * @return ERR_OK为成功，其它请见错误码
     */
    int readIRLinkADValues(std::array<IRLinkADDAStatus_V1, ADDA_MAX_SIZE_V1> &values);

    /**
     * @brief 获取AD数据 false AD数据 true DA数据
     */
    int readCobotAnalogIODatas(bool isDA, std::vector<Cobot_ADDA_Data_V1> &data);

    /**
     * @brief 写入AD数据 false AD数据 true DA数据
     */
    int writeCobotAnalogIODatas(const Cobot_ADDA_Status_V1 &data);

    /**
     * @brief 获取IRLinkAD数据
     */
    std::vector<IRLinkADDAData_V1> getIRLinkADDatas();

    /**
     * @brief 获取ECatAD数据
     */
    std::vector<ECatADDAData_V1> getECatADDatas();

    /**
     * @brief 更新IRLinkAD数据
     */
    bool updateIRLinkADDatas();

    /**
     * @brief 更新ECatAD数据
     */
    bool updateECatADDatas();

    /**
     * @brief 设置DA调度
     * @param scheduler true调度 false不调度
     */
    void setDAScheduler(const bool scheduler);

    /**
     * @brief 设置DA显示类型
     * @param type DA显示类型
     */
    void setDAShowType(const ADDAType_V1 type);

    /**
     * @brief 与控制器通信获取IRLinkDA值
     * @param values DA值
     * @return ERR_OK为成功，其它见错误码
     */
    int readIRLinkDAValues(std::array<IRLinkADDAStatus_V1, ADDA_MAX_SIZE_V1> &values);

    /**
     * @brief 与控制器通信写DA值
     * @param index 下标
     * @param flag 0:写输出的值 1:开关量
     * @param value 值
     * @return ERR_OK为成功，其它见错误码
     */
    int writeIRLinkDAValue(const int index, const int flag, const IRLinkADDAStatus_V1 &value);

    /**
     * @brief 获取IRLinkDA数据
     */
    std::vector<IRLinkADDAData_V1> getIRLinkDADatas();

    /**
     * @brief 获取ECatDA数据
     */
    std::vector<ECatADDAData_V1> getECatDADatas();

    /**
     * @brief 设置IRLinkDA的状态
     * @param index 下标
     * @param flag 0：写输出的值 1：写开关量
     * @param status DA状态
     * @return true成功 false失败
     */
    bool setIRLinkDAStatus(const int index, const int flag, const IRLinkADDAStatus_V1 &status);

    /**
     * @brief 设置ECatDA的状态
     * @param index 下标
     * @param falg 1：写输出的值 2：写开关量
     * @param status DA状态
     * @return true成功 false失败
     */
    bool setECatDAStatus(const int index, const int flag, const EcatAdDaState_V1 &status);

    /**
     * @brief 更新IRLinkDA数据
     * @return true成功 false失败
     */
    bool updateIRLinkDADatas();

    /**
     * @brief 更新ECatDA数据
     * @return true成功 false失败
     */
    bool updateECatDADatas();

    /**
     * @brief 设置系统Input调度
     * @param scheduler true调度 false不调度
     */
    void setSysInputScheduler(const bool scheduler);

    /**
     * @brief 设置系统Output调度
     * @param schedulertrue调度 false不调度
     */
    void setSysOutputScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取系统IO值
     * @param inputData 输入值
     * @param outputData 输出值
     * @return ERR_OK为成功，其它见错误码
     */
    int readSysIOValues(int16u &inputData, int16u &outputData);

    /**
     * @brief 与控制器通信 读取系统IO强制状态
     * @param inputFH 输入强制高
     * @param inputFL 输入强制低
     * @param outputFH 输出强制高
     * @param outputFL 输出强制低
     * @return ERR_OK为成功，其它见错误码
     */
    int readSysIOForceValues(int16u &inputFH, int16u &inputFL, int16u &outputFH, int16u &outputFL);

    /**
     * @brief 获取系统输入状态
     */
    std::array<bool, SYSIO_SIZE_V1> getSysInputStatus();

    /**
     * @brief 获取系统输入备注
     */
    std::array<std::string, SYSIO_SIZE_V1> getSysInputRemarks();

    /**
     * @brief 获取系统输出状态
     */
    std::array<bool, SYSIO_SIZE_V1> getSysOutputStatus();

    /**
     * @brief 获取系统输出备注
     */
    std::array<std::string, SYSIO_SIZE_V1> getSysOutputRemarks();

    /**
     * @brief 更新系统输入数据
     * @return true成功 false失败
     */
    bool updateSysInputDatas();

    /**
     * @brief 更新系统输出数据
     * @return true成功 false失败
     */
    bool updateSysOutputDatas();

    /**
     * @brief 与控制器通信 读取控制器EthInfo信息
     * @param[out] controllerEI EthInfo信息
     * @return ERR_OK成功 其它见错误码
     */
    int readControllerEthInfo(ControllerEthInfo_V1 &controllerEI);

    /**
     * @brief 与控制器通信 读取EtherCAT PDO丢帧信息
     * @param[out] totalLostCount 总丢包数
     * @param[out] continueLostCount 连续丢包数
     * @param[out] lostFlag 丢失flag
     * @return ERR_OK为成功，其它见错误码
     */
    int readEcatPdoLostInfo(int16u &totalLostCount, int16u &continueLostCount, int16u &lostFlag);

    /**
     * @brief 与控制器通信 读取控制器存储卡信息
     * @param[out] info 存储卡信息
     * @return ERR_OK为成功，其它见错误码
     */
    int readSDInfo(std::string &info);

    /**
     * @brief 设置modbus连接调度
     * @param scheduler true调度 false不调度
     */
    void setModbusConnectScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取Modbus连接状态
     * @param[out] status Modbus连接状态
     * @return ERR_OK为成功，其他为失败
     */
    int readModbusConnectStatus(ModbusConnectStatus_V1 &status);

    /**
     * @brief 获取Modbus连接状态
     */
    ModbusConnectStatus_V1 getModbusConnectStatus();

    /**
     * @brief 更新Modbus连接状态
     * @return true成功 false失败
     */
    bool updateModbusConnectStatus();

    /**
     * @brief 设置EthernetIP调度
     * @param scheduler true调度 false不调度
     */
    void setEthernetIPScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取EthernetIP状态
     * @param[out] status EthernetIP状态
     * @return ERR_OK为成功，其他为失败
     */
    int readEthernetIPStatus(EthernetIPStatus_V1 &status);

    /**
     * @brief 获取EthernetIP状态
     */
    EthernetIPStatus_V1 getEthernetIPStatus();

    /**
     * @brief 更新EthernetIP状态
     * @return true成功 false失败
     */
    bool updateEthernetIPStatus();

    /**
     * @brief 设置EtherCat调度
     * @param scheduler true调度 false不调度
     */
    void setEtherCatScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取EtherCAT状态
     * @param[out] status EtherCAT状态
     * @return ERR_OK为成功，其他为失败
     */
    int readEtherCatStatus(EtherCATStatus_V1 &status);

    /**
     * @brief 获取EtherCat状态
     */
    EtherCATStatus_V1 getEtherCatStatus();

    /**
     * @brief 更新EtherCat状态
     * @return true成功 false失败
     */
    bool updateEtherCatStatus();

    /**
     * @brief 设置MC调度
     * @param scheduler true调度 false不调度
     */
    void setMCScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取MC激活状态
     * @param[out] active MC激活状态
     * @return ERR_OK为成功，其他为失败
     */
    int readMCActiveStatus(unsigned char &active);

    /**
     * @brief 与控制器通信 读取MC连接状态
     * @param[out] status MC连接状态
     * @return ERR_OK为成功，其他为失败
     */
    int readMCConnectStatus(std::array<MCConnectStatus_V1, MC_CONNECT_NUM_V1> &status);

    /**
     * @brief 获取MC激活状态
     */
    bool getMCActiveStatus();

    /**
     * @brief 获取MC连接状态
     * @return
     */
    std::array<MCConnectStatus_V1, MC_CONNECT_NUM_V1> getMCConnectStatus();

    /**
     * @brief 更新MC状态
     * @return true成功 false失败
     */
    bool updateMCStatus();

    /**
     * @brief 设置profinet连接调度
     * @param scheduler true调度 false不调度
     */
    void setProfinetConnectScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取profinet连接状态
     * @param[out] status profinet连接状态
     * @return ERR_OK为成功，其他为失败
     */
    int readProfinetConnectStatus(ProfinetConnectStatus_V1 &status);

    /**
     * @brief 获取profinet连接状态
     */
    ProfinetConnectStatus_V1 getProfinetConnectStatus();

    /**
     * @brief 更新profinet连接状态
     * @return true成功 false失败
     */
    bool updateProfinetConnectStatus();

    /**
     * @brief 与控制器通信通知控制器准备伺服参数(驱控一体电柜专用)
     * @param axisNo 轴号
     * @param pageID 页号
     * @return ERR_OK为成功，其它请见错误码
     */
    int prepareServoParam(int axisNo, int pageID);

    /**
     * @brief 与控制器通信读取伺服参数（一次只能读取10个）
     * @param axisNo 轴号
     * @param pageID 页ID
     * @param pFunCode 获取的伺服参数
     * @return ERR_OK为成功，其它请见错误码
     */
    int readServoParam(int axisNo, int pageID, char pFunCode[10][12]);

    /**
     * @brief 与控制器通信读取一个伺服码的值(注意：该读取有延时！由控制器内部控制！)
     * @param axisNo 轴号
     * @param[in] code 伺服码
     * @param[out] value 值
     * @return true读取成功 false读取失败
     */
    bool readSingleServoCode(int axisNo, const std::string &code, std::string &value);

    /**
     * @brief 与控制器通信设置单个伺服码的值
     * @param axisNo 轴号
     * @param code 伺服码
     * @param value 值
     * @return true成功 false失败
     */
    bool writeSingleServoCode(int axisNo, const std::string &code, const std::string &value);

    /**
     * @brief 允许重置编码器
     * @param axisNo 轴号
     * @return true允许 false不允许
     */
    bool allowResetEncoder();

    /**
     * @brief 与控制器通信重置编码器
     * @param axisNo 轴号
     * @return true成功 false失败
     */
    bool writeResetEncoder(int axisNo);

    /**
     * @brief 与控制器通信读重置编码器结果
     * @param[in] axisNo 轴号
     * @param[out] result 结果
     * @return true成功 false失败
     */
    bool readResetEncoderResult(int axisNo, int &result);

    /**
     * @brief 设置电流调度
     * @param scheduler true调度 false不调度
     */
    void setElectricScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取机械臂当前电流
     * @param[out] current 当前电流值
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCurrentElectric(std::vector<double> &current);

    /**
     * @brief 与控制器通信 读取机械臂电流最大值（单位百分比）
     * @param[out] maxCurrent 电流最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    int readMaxElectric(std::vector<double> &maxCurrent);

    /**
     * @brief 与控制器通信 重置机械臂电流最大值（单位百分比）
     * @return ERR_OK为成功，其它请见错误码
     */
    int resetMaxElectric();

    /**
     * @brief 是否允许重置电流历史最大值
     * @return true允许 false不允许
     */
    bool allowResetMaxElectric();

    /**
     * @brief 获取当前电流值
     */
    std::vector<double> getCurrentElectric();

    /**
     * @brief 获取电流历史最大值
     * @return
     */
    std::vector<double> getMaxElectric();

    /**
     * @brief 更新电流当前值、历史最大值
     * @return true成功 false失败
     */
    bool updateElectric();

    /**
     * @brief 设置平均负载率调度
     * @param scheduler true调度 false不调度
     */
    void setAvgLoadRateScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取机械臂当前平均负载率（单位百分比）
     * @param[out] avgLoadRate 平均负载率
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCurrentAvgLoadRate(std::vector<double> &avgLoadRate);

    /**
     * @brief 获取当前平均负载率
     */
    std::vector<double> getCurrentAvgLoadRate();

    /**
     * @brief 更新平均负载率
     * @return true成功 false失败
     */
    bool updateAvgLoadRate();

    /**
     * @brief 设置过载率调度
     * @param scheduler true调度 false不调度
     */
    void setOverLoadScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取当前过载率（单位百分比）
     * @param[out] overLoad 过载率
     * @return ERR_OK为成功，其它请见错误码
     */
    int readCurrentOverLoad(std::vector<double> &overLoad);

    /**
     * @brief 与控制器通信 读取过载率最大值（单位百分比）
     * @param[out] maxOverLoad 过载率最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    int readMaxOverLoad(std::vector<double> &maxOverLoad);

    /**
     * @brief 与控制器通信 重置过载率最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    int resetMaxOverLoad();

    /**
     * @brief 是否允许重置过载率最大值
     * @return true允许 false不允许
     */
    bool allowResetMaxOverLoad();

    /**
     * @brief 获取当前过载率
     */
    std::vector<double> getCurrentOverLoad();

    /**
     * @brief 获取过载率最大值
     */
    std::vector<double> getMaxOverLoad();

    /**
     * @brief 更新过载率当前值、最大值
     * @return true成功 false失败
     */
    bool updateOverLoad();

    /**
     * @brief 设置过热率调度
     * @param scheduler true调度 false不调度
     */
    void setOverHeatScheduler(const bool scheduler);

    /**
     * @brief 与控制器通信 读取当前过热率
     * @param[out] overHeat 过热率
     * @return ERR_OK为成功，其它请见错误
     */
    int readCurrentOverHeat(std::vector<double> &overHeat);

    /**
     * @brief 获取当前过热率
     */
    std::vector<double> getCurrentOverHeat();

    /**
     * @brief 更新过热率当前值
     * @return true成功 false失败
     */
    bool updateOverHeat();

    /**
     * @brief 向控制器写入统计示教器压缩包信息的命令
     * @param cmd 输入，命令，1 - 开始统计
     * @return 成功返回0，其他请见错误码
     */
    int writeCountTPPackagesInfoCmd(int cmd);
    /**
     * @brief 读取控制器统计示教器压缩包信息的结果
     * @param result 输出，结果ID
     0 - 正在统计，
     1 - 完成，
     2 - SD卡不存在，
     3 - SD卡中未发现示教器升级包，
     4 - 解压出错
     5 - TeachPadVersion.ini不存在或为空
     * @return 成功返回0，其他请见错误码
    */
    int readCountTPPackagesInfoCmdResult(int &result);

#pragma endregion

#pragma region 信号

private:
    void globalVarBValueChanged_Handler(const QHash<int, unsigned char> &changeValues);
    void globalVarRValueChanged_Handler(const QHash<int, int> &changeValues);
    void globalVarDValueChanged_Handler(const QHash<int, double> &changeValues);
    void globalVarPRValueChanged_Handler(const QHash<int, Pose> &changeValues);
    void globalVarStringValueChanged_Handler(const QHash<int, std::string> &changeValues);
    void inputValueChanged_Handler(const QHash<int, unsigned char> &changeValues);
    void standardInputValueChanged_Handler(const QHash<int, unsigned char> &statusValues,
                                   const QHash<int, unsigned char> &forceHValues,
                                   const QHash<int, unsigned char> &forceLValues);
    void outputValueChanged_Handler(const QHash<int, unsigned char> &changeValues);
    void IRLinkADValueChanged_Handler(const QHash<int, IRLinkADDAStatus> &status);
    void ECatADValueChanged_Handler(const QHash<int, EcatAdDaState> &status);
    void IRLinkDAValueChanged_Handler(const QHash<int, IRLinkADDAStatus> &status);
    void ECatDAValueChanged_Handler(const QHash<int, EcatAdDaState> &status);
    void sysInputValueChanged_Handler(const QHash<int, bool> &changeValues);
    void sysOutputValueChanged_Handler(const QHash<int, bool> &changeValues);
    void modbusConnectStatusChanged_Handler();
    void ethernetIPStatusChanged_Handler();
    void etherCatStatusChanged_Handler();
    void mcStatusChanged_Handler();
    void profinetConnectStatusChanged_Handler();
    void electricChanged_Handler();
    void avgLoadRateChanged_Handler();
    void overLoadChanged_Handler();
    void overHeatChanged_Handler();

public:
Q_SIGNALS:
    // 全局变量B值改变信号
    void globalVarBValueChanged(const QHash<int, unsigned char> &changeValues);
    // 全局变量R值改变信号
    void globalVarRValueChanged(const QHash<int, int> &changeValues);
    // 全局变量D值改变信号
    void globalVarDValueChanged(const QHash<int, double> &changeValues);
    // 全局PR变量值改变信号
    void globalVarPRValueChanged(const QHash<int, Pose> &changeValues);
    // 全局string变量值改变信号
    void globalVarStringValueChanged(const QHash<int, std::string> &changeValues);
    /**
     * @brief 总线输入值改变信号
     * @param changeValues 改变值（int在值容器中的下标，非IO下标）
     */
    void inputValueChanged(const QHash<int, unsigned char> &changeValues);
    /**
     * @brief 标准输入值改变信号
     * @param statusValues 改变状态值
     * @param forceHValues 改变强制高值
     * @param forceLValues 改变强制低值
     */
    void standardInputValueChanged(const QHash<int, unsigned char> &statusValues,
                                   const QHash<int, unsigned char> &forceHValues,
                                   const QHash<int, unsigned char> &forceLValues);
    /**
     * @brief 总线输出值改变信号
     * @param changeValues 改变值（int在值容器中的下标，非IO下标）
     */
    void outputValueChanged(const QHash<int, unsigned char> &changeValues);
    // IRLinkAD值改变信号
    void IRLinkADValueChanged(const QHash<int, IRLinkADDAStatus_V1> &status);
    // EtherCATAD值改变信号
    void ECatADValueChanged(const QHash<int, EcatAdDaState_V1> &status);
    // IRLinkDA值改变信号
    void IRLinkDAValueChanged(const QHash<int, IRLinkADDAStatus_V1> &status);
    // EtherCATDA值改变信号
    void ECatDAValueChanged(const QHash<int, EcatAdDaState_V1> &status);

    // 系统输入值改变信号
    void sysInputValueChanged(const QHash<int, bool> &changeValues);
    // 系统输出值改变信号
    void sysOutputValueChanged(const QHash<int, bool> &changeValues);
    // Modbus连接状态改变信号
    void modbusConnectStatusChanged();
    // EthernetIP状态改变信号
    void ethernetIPStatusChanged();
    // EtherCat状态改变信号
    void etherCatStatusChanged();
    // MC状态改变信号
    void mcStatusChanged();
    // Profinet连接状态改变信号
    void profinetConnectStatusChanged();
    // 电流改变信号
    void electricChanged();
    // 平均负载率改变信号
    void avgLoadRateChanged();
    // 过载率改变信号
    void overLoadChanged();
    // 过热率改变信号
    void overHeatChanged();

#pragma endregion
};
}  // namespace InoRobBusinessProxy
