#pragma once
#include <string>
#include <array>
#include <vector>
#include <QObject>
#include <QHash>
#include <QMetaType>
#include <GlobalDataTypes.h>
#include "../../Project/IProject.h"
#include "GlobalVar/IVarMonitor.h"
#include "../Fieldbus/IFieldbus.h"

// 全局变量
constexpr int GLOBAL_VAR_B_NUM = 256;       // 全局B变量总个数
constexpr int GLOBAL_VAR_R_NUM = 256;       // 全局R变量总个数
constexpr int GLOBAL_VAR_D_NUM = 256;       // 全局D变量总个数
constexpr int GLOBAL_VAR_PR_NUM = 256;      // 全局PR变量总个数
constexpr int GLOBAL_VAR_STRING_NUM = 256;  // 全局String变量总个数
constexpr int GLOBAL_P_NUM = 10000;         // 全局P变量总个数
constexpr int GLOBAL_P_PAGE_SIZE = 5;       // 全局P变量每帧数据大小
constexpr int GLOBAL_JP_NUM = 10000;        // 全局P变量总个数
constexpr int GLOBAL_JP_PAGE_SIZE = 5;      // 全局P变量每帧数据大小

// 总线
constexpr int STANDARD_IO_STARTINDEX = 0;           // 标准IO起始下标(以byte参考)
constexpr int STANDARD_IO_SIZE = 16;                // 标准IO大小(以byte参考)
constexpr int TOOL_IO_STARTINDEX = 16;              // 协作工具IO起始下标(以byte参考)
constexpr int TOOL_IO_SIZE = 2;                     // 协作工具IO大小(以byte参考)
constexpr int SLAVE_FIELDBUS_IO_STARTINDEX = 64;    // 从站现场总线IO起始下标(以byte参考)
constexpr int SLAVE_FIELDBUS_IO_SIZE = 512;         // 从站现场总线IO大小(以byte参考)
constexpr int MASTER_FIELDBUS_IO_STARTINDEX = 832;  // 主站现场总线IO起始下标(以byte参考)
constexpr int MASTER_FIELDBUS_IO_SIZE = 512;        // 主站现场总线IO大小(以byte参考)
constexpr int MEMORY_IO_STARTINDEX = 1600;          // 内存IO起始下标(以byte参考)
constexpr int MEMORY_IO_SIZE = 128;                 // 内存IO大小(以byte参考)

// AD DA
constexpr int ADDA_MAX_SIZE = 16;                  // AD、DA最大大小
constexpr int COBOT_CONTROLLER_ADDA_MAX_SIZE = 2;  // 协作电柜自带的AD DA两个
constexpr int ECAT_ADDA_STARTINDEX = 64;           // EtherCATADDA起始索引
constexpr int ECAT_ADDA_ENDINDEX = 80;             // EtherCATADDA结束索引

// sysIO
constexpr int SYSIO_SIZE = 16;    // IO端子数量
constexpr int CABINET_COUNT = 7;  // 电柜种类

constexpr int SERVO_IS620N_NUM = 25;  // IS620N伺服个数
constexpr int SERVO_IS820N_NUM = 33;  // IS820N伺服个数
constexpr int SERVO_IS660N_NUM = 32;  // IS660N伺服个数
constexpr int SERVO_SV660N_NUM = 31;  // SV660N伺服个数

const int TCP_CLIENT_NUM = 16;  // TCP连接数量
const int MC_CONNECT_NUM = 4;   // MC连接数量

namespace InoRobBusiness
{
#pragma region 结构体
// B变量数据
struct GlobalVarBData
{
    int index;            // 下标
    unsigned char value;  // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarBData()
    {
        index = -1;
        value = 0;
        favorite = false;
    }

    GlobalVarBData &operator=(const GlobalVarBData &other)
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
struct GlobalVarRData
{
    int index;            // 下标
    int value;            // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarRData()
    {
        index = -1;
        value = 0;
        favorite = false;
    }

    GlobalVarRData &operator=(const GlobalVarRData &other)
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
struct GlobalVarDData
{
    int index;            // 下标
    double value;         // 值
    std::string labs;     // 标签
    std::string remarks;  // 备注
    bool favorite;        // 收藏

    GlobalVarDData()
    {
        index = -1;
        value = 0.0;
        favorite = false;
    }

    GlobalVarDData &operator=(const GlobalVarDData &other)
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
struct GlobalPData
{
    RAM_P globalP;        // 全局P点值
    std::string labs;     // 标签
    std::string remarks;  // 备注
};

// 全局JP点数据
struct GlobalJPData
{
    RAM_J globalJP;       // 全局JP点值
    std::string labs;     // 标签
    std::string remarks;  // 备注
};

// AD、DA状态 协作电柜自带的AD DA
struct Cobot_ADDA_Status
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

    Cobot_ADDA_Status &operator=(const Cobot_ADDA_Status &other)
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
    bool compare(const Cobot_ADDA_Status &other)
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
struct Cobot_ADDA_Data
{
    Cobot_ADDA_Status status;  // 状态
    std::string labs;          // 标签
    std::string remarks;       // 备注
};

// IRLink AD、DA数据
struct IRLinkADDAData
{
    IRLinkADDAStatus status;  // IRLink状态
    std::string labs;         // 标签
    std::string remarks;      // 备注
};

// ECat AD、DA数据
struct ECatADDAData
{
    EcatAdDaState status;  // ECAT状态
    std::string labs;      // 标签
    std::string remarks;   // 备注
};

/**
 * @brief 系统IOInOut描述
 */
struct SysIODat
{
    int cabinetType = 0;                                  // 电柜类型
    std::array<std::string, SYSIO_SIZE> inDescriptions;   // In描述数组
    std::array<std::string, SYSIO_SIZE> outDescriptions;  // Out描述数组
};

struct EthInfo
{
    bool isDHCP = false;             // true 动态，false 静态
    std::string ipAddr = "0.0.0.0";  // IP地址
};

struct ControllerEthInfo
{
    EthInfo eth0;  // 网口1
    EthInfo eth1;  // 网口2
};

// TCP连接状态
struct ModbusTCPConnectStatus
{
    unsigned char owner = 0;        // 控制权 0-未开启，1-二次开发，2-控制器
    unsigned char status = 0;       // 运行情况 0-未运行，1-运行
    unsigned short port = 502;      // 端口号
    unsigned short framedelay = 1;  // 帧间隔

    bool compare(const ModbusTCPConnectStatus &other)
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
struct ModbusRTUConnectStatus
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

    bool compare(const ModbusRTUConnectStatus &other)
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
struct ModbusConnectStatus
{
    unsigned char modbusAddrType = 0;                                 // Modbus地址类型 0-旧版地址，1-新版地址
    ModbusTCPConnectStatus modbusTcpCS;                               // ModbusTCP配置结构体
    ModbusRTUConnectStatus modbusRtuCS;                               // ModbusRtu配置结构
    unsigned char modbusTcpConnectFlag[TCP_CLIENT_NUM] = { 0 };       // modbusTcp连接状态，0表示未连接，1表示已连
    unsigned char modbusTcpClientIP[TCP_CLIENT_NUM][16] = { { 0 } };  // 主站IP地址（第一行表示第一个连接上的主站的IP）
    unsigned short modbusTcpClientPort[TCP_CLIENT_NUM] = { 0 };       // 主站端口（第一元素表示第一个连接上的主站的端口）

    // 比较 相同返回ture， 不相同返回false
    bool compare(const ModbusConnectStatus &other)
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
struct EthernetIPStatus
{
    unsigned char active = 0;            // EIP激活状态:0-未开启，1-已开启
    unsigned char connect = 0;           // EIP连接状态:0-未连接，1-已连接
    unsigned char masterIP[16] = { 0 };  // EIP主站(客户端)IP地址
    unsigned short masterPort = 502;     // EIP主站(客户端)的端口
    unsigned short slavePort = 44818;    // EIP从站(服务器)端口,暂时固定为44818

    EthernetIPStatus &operator=(const EthernetIPStatus &other)
    {
        this->active = other.active;
        this->connect = other.connect;
        std::copy(other.masterIP, other.masterIP + 16, this->masterIP);
        this->masterPort = other.masterPort;
        this->slavePort = other.slavePort;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const EthernetIPStatus &other)
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
struct EtherCATStatus
{
    unsigned char active = 0;             // Ethcat激活状态:0-未开启，1-已开启
    unsigned char connect = 0;            // Ethcat连接状态:0-未连接，1-已连接
    unsigned short siteAlias = 0;         // 站点别名（默认值为0）
    unsigned short maxFramLossTimes = 8;  // 最大丢站次数（默认值为8次）

    EtherCATStatus &operator=(const EtherCATStatus &other)
    {
        this->active = other.active;
        this->connect = other.connect;
        this->siteAlias = other.siteAlias;
        this->maxFramLossTimes = other.maxFramLossTimes;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const EtherCATStatus &other)
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
struct MCConnectStatus
{
    unsigned char connectIndex = 0;      // 连接索引
    unsigned char serverIP[16] = { 0 };  // MC 服务器IP
    unsigned short port = 0;             // MC 端口号
    unsigned char connect = 0;           // 读连接状态 0未连接，1已连接；（写命令：1连接；0是断开）
    unsigned char autoReconnect = 0;     // 0- 不进行重连， 1- 进行自动重连 (断电，激活 MC开关时)

    MCConnectStatus &operator=(const MCConnectStatus &other)
    {
        this->connectIndex = other.connectIndex;
        std::copy(other.serverIP, other.serverIP + 16, this->serverIP);
        this->port = other.port;
        this->connect = other.connect;
        this->autoReconnect = other.autoReconnect;
        return (*this);
    }

    // 比较 相同返回ture， 不相同返回false
    bool compare(const MCConnectStatus &other)
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
struct ProfinetConnectStatus
{
    unsigned char activeStatus = 0;          // PN激活状态:0-未开启，1-已开启
    unsigned char connectStatus = 0;         // PN连接状态:0-未连接，1-已连接
    char ip[16] = { 0 };                     // ip地址
    char defaultGateWay[16] = { 0 };         // 默认网关
    char macAddress[18] = { 0 };             // MAC地址
    unsigned short version = 0;              // 版本号
    unsigned short maxFrameDropNumber = 10;  // 已设置的最大丢帧次数

    bool compare(const ProfinetConnectStatus &other)
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

/*
    资源
    Create by WuJian at 2023/8/10 创建。
*/
class INOROBBUSINESS_CLASS IResource : public QObject
{
    Q_OBJECT

public:
    virtual ~IResource()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 枚举
public:
    // IO类型
    enum IOType
    {
        COMMON_IO = 0,       // 常用IO(设置了标签或者备注)
        STANDARD_IO,         // 标准IO
        SLAVE_FIELDBUS_IO,   // 从站现场总线IO
        MASTER_FIELDBUS_IO,  // 主站现场总线IO
        MEMORY_IO,           // 内存IO
        TOOL_IO              // 末端IO
    };

    // 数据进制
    enum SystemType
    {
        DECIMAL = 0,  // 十进制
        BINARY,       // 二进制
        HEXADECIMAL   // 十六进制
    };

    // 显示类型
    enum ShowType
    {
        BIT = 0,   // bit
        BYTE = 1,  // 字节
        WORD = 2   // 字
    };
#pragma endregion

#pragma region 获取pt文件列表
    virtual int getPointFileListFromController(vector<std::string> &fileList) = 0;
#pragma endregion

#pragma region 变量监控
    virtual IVarMonitor *getVarMonitor() const = 0;
#pragma endregion

#pragma region 全局变量B
    /**
     * @brief 设置全局B变量调度
     * @param scheduler true调度 false不调度
     */
    virtual void setGlobalVarBScheduler(bool scheduler) = 0;

    /**
     * @brief 与控制器通信读取所有全局B变量值
     * @param values 全局B变量值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readGlobalVarBValues(std::array<int8u, GLOBAL_VAR_B_NUM> &values) = 0;

    /**
     * @brief 与控制器通信设置一个全局B变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int writeGlobalVarBValue(const unsigned char value, const unsigned int index) = 0;

    /**
     * @brief 获取所有全局B变量数据
     */
    virtual std::vector<GlobalVarBData> getGlobalVarBDatas() const = 0;

    /**
     * @brief 设置一个全局B变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarBFavorite(const bool favorite, const int index) = 0;

    /**
     * @brief 获取全局B变量是否显示收藏
     * @return true显示 false不显示
     */
    virtual bool getGlobalVarBShowFavorite() const = 0;

    /**
     * @brief 设置全局B变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    virtual bool setGlobalVarBShowFavorite(const bool show) = 0;

    /**
     * @brief 获取所有全局B变量值
     */
    virtual std::array<unsigned char, GLOBAL_VAR_B_NUM> getGlobalVarBValues() const = 0;

    /**
     * @brief 设置一个全局B变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarBValue(const unsigned char value, const unsigned int index) = 0;

    /**
     * @brief 更新全局B变量数据
     * @return true更新成功 false更新失败
     */
    virtual bool updataGlobalVarBDatas() = 0;
#pragma endregion

#pragma region 全局变量R
    /**
     * @brief 设置全局R变量调度
     * @param scheduler true调度 false不调度
     */
    virtual void setGlobalVarRScheduler(bool scheduler) = 0;

    /**
     * @brief 与控制器通信读取所有全局R变量值
     * @param values 全局R变量值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readGlobalVarRValues(std::array<int, GLOBAL_VAR_R_NUM> &values) = 0;

    /**
     * @brief 与控制器通信设置一个全局R变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int writeGlobalVarRValue(const int value, const unsigned int index) = 0;

    /**
     * @brief 获取所有全局R变量数据
     */
    virtual std::vector<GlobalVarRData> getGlobalVarRDatas() const = 0;

    /**
     * @brief 设置一个全局R变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     * @retun true成功 false失败
     */
    virtual bool setGlobalVarRFavorite(const bool favorite, const int index) = 0;

    /**
     * @brief 获取全局R变量是否显示收藏
     * @return true显示 false不显示
     */
    virtual bool getGlobalVarRShowFavorite() const = 0;

    /**
     * @brief 设置全局R变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    virtual bool setGlobalVarRShowFavorite(const bool show) = 0;

    /**
     * @brief 获取所有全局R变量值
     */
    virtual std::array<int, GLOBAL_VAR_R_NUM> getGlobalVarRValues() const = 0;

    /**
     * @brief 设置一个全局R变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarRValue(const int value, const unsigned int index) = 0;

    /**
     * @brief 更新全局R变量数据
     * @return true更新成功 false更新失败
     */
    virtual bool updataGlobalVarRDatas() = 0;
#pragma endregion

#pragma region 全局变量D
    /**
     * @brief 设置全局D变量调度
     * @param scheduler true调度 false不调度
     */
    virtual void setGlobalVarDScheduler(bool scheduler) = 0;

    /**
     * @brief 与控制器通信读取所有全局D变量值
     * @param values 全局D变量值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readGlobalVarDValues(std::array<double, GLOBAL_VAR_D_NUM> &values) = 0;

    /**
     * @brief 与控制器通信设置一个全局D变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int writeGlobalVarDValue(const double value, const unsigned int index) = 0;

    /**
     * @brief 获取所有全局D变量数据
     */
    virtual std::vector<GlobalVarDData> getGlobalVarDDatas() const = 0;

    /**
     * @brief 设置一个全局D变量是否收藏
     * @param favorite true收藏 false取消收藏
     * @param index 下标
     */
    virtual bool setGlobalVarDFavorite(const bool favorite, const int index) = 0;

    /**
     * @brief 获取全局D变量是否显示收藏
     * @return true显示 false不显示
     */
    virtual bool getGlobalVarDShowFavorite() const = 0;

    /**
     * @brief 设置全局D变量是否显示收藏
     * @param show true显示 false不显示
     * @return true成功 false失败
     */
    virtual bool setGlobalVarDShowFavorite(const bool show) = 0;

    /**
     * @brief 获取所有全局D变量值
     */
    virtual std::array<double, GLOBAL_VAR_D_NUM> getGlobalVarDValues() const = 0;

    /**
     * @brief 设置一个全局D变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarDValue(const double value, const unsigned int index) = 0;

    /**
     * @brief 更新全局D变量数据
     * @return true更新成功 false更新失败
     */
    virtual bool updataGlobalVarDDatas() = 0;
#pragma endregion

#pragma region 全局变量PR
    /**
     * @brief 设置全局PR变量调度
     * @param scheduler true调度 false不调度
     */
    virtual void setGlobalVarPRScheduler(bool scheduler) = 0;

    /**
     * @brief 与控制器通信读取所有全局PR变量值
     * @param values 全局PR变量值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readGlobalVarPRValues(std::vector<Pose> &values) const = 0;

    /**
     * @brief 与控制器通信设置一个全局PR变量值
     * @param value 值
     * @param index 下标
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int writeGlobalVarPRValue(const Pose &value, const unsigned int index) = 0;

    /**
     * @brief 获取所有全局变量PR的值
     */
    virtual std::vector<Pose> getGlobalVarPRValues() const = 0;

    /**
     * @brief 检查当前是否允许设置全局变量PR值
     * @return true允许 false不允许
     */
    virtual bool allowSetGlobalVarPRValue() = 0;

    /**
     * @brief 设置一个全局PR变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarPRValue(const Pose &value, const unsigned int index) = 0;

    /**
     * @brief 更新全局PR变量数据
     * @return true成功 false失败
     */
    virtual bool updateGlobalVarPRDatas() = 0;
#pragma endregion

#pragma region 全局变量String
    /**
     * @brief 设置全局string变量调度
     * @param scheduler true调度 false不调度
     */
    virtual void setGlobalVarStringScheduler(bool scheduler) = 0;

    /**
     * @brief 与控制器通信读取所有全局String变量值
     * @param values 全局string变量值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readGlobalVarStringValues(std::array<std::string, GLOBAL_VAR_STRING_NUM> &values) const = 0;

    /**
     * @brief 与控制器通信设置一个全局String变量值
     * @param value 值
     * @param index 下标
     * @return
     */
    virtual int writeGlobalVarStringValue(const std::string &value, const unsigned int index) = 0;

    /**
     * @brief 获取全局String变量所有数据
     */
    virtual std::array<std::string, GLOBAL_VAR_STRING_NUM> getGlobalVarStringDatas() const = 0;

    /**
     * @brief 设置一个全局String变量值
     * @param value 值
     * @param index 下标
     * @return true成功 false失败
     */
    virtual bool setGlobalVarStringValue(const std::string &value, const unsigned int index) = 0;

    /**
     * @brief 更新全局String变量数据
     * @return true成功 false失败
     */
    virtual bool updateGlobalVarStringDatas() = 0;
#pragma endregion

#pragma region 全局点位P
    /**
     * @brief 与控制器通信读取全局P点位值
     * @param values 值
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readGlobalPValues(std::vector<RAM_P> &values, const int pageIndex, const int pageNum) = 0;

    /**
     * @brief 获取全局P点数据
     * @param datas 数据
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return true成功 false失败
     */
    virtual bool getGlobalPDatas(std::vector<GlobalPData> &datas, const int pageIndex, const int pageNum, bool isNeedErrorPrint = true) = 0;
#pragma endregion

#pragma region 全局点位JP
    /**
     * @brief 与控制器通信读取全局JP点位值
     * @param values 值
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readGlobalJPValues(std::vector<RAM_J> &values, const int pageIndex, const int pageNum) = 0;

    /**
     * @brief 获取全局JP点数据
     * @param datas 数据
     * @param pageIndex 获取页下标
     * @param pageNum 获取页大小
     * @return true成功 false失败
     */
    virtual bool getGlobalJPDatas(std::vector<GlobalJPData> &datas, const int pageIndex, const int pageNum, bool isNeedMsgPrint = true) = 0;
#pragma endregion

#pragma region IO
#pragma region Input
    /**
     * @brief 设置Input调度
     * @param scheduler true调度 false不调度
     */
    virtual void setInputScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信获取常用输入状态
     *        每次与控制器通信最多获取8个字节数据
     * @param showType 显示类型（查看ShowType枚举）
     * @param size 常用输入数量
     * @param inputIndexs 常用输入下标
     * @param status 读取状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCommonInputStatus(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &inputIndexs, std::vector<int8u> &status) = 0;

    /**
     * @brief 与控制器通信获取Input状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readInputStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) = 0;

    /**
     * @brief 与控制器通信获取Input强制高状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readInputForceHighStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) = 0;

    /**
     * @brief 与控制器通信获取强制低状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 状态的首地址（内存上连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readInputForceLowStatus(const int16u startByteId, const int16u byteNum, int8u *dataBuf) = 0;

    /**
     * @brief 与控制器通信写Input状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf Input状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeInputStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) = 0;

    /**
     * @brief 与控制器通信写Input强制高状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 强制高状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeInputForceHighStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) = 0;

    /**
     * @brief 与控制器通信写Input强制低状态
     * @param startByteId 起始下标
     * @param byteNum 状态数量
     * @param dataBuf 强制低状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeInputForceLowStatus(const int16u startByteId, const int16u byteNum, const std::vector<int8u> &dataBuf) = 0;

    /**
     * @brief 设置InputIO类型
     * @param ioType IO类型
     */
    virtual void setInputIOType(const IResource::IOType ioType) = 0;

    /**
     * @brief 获取InputIO类型
     */
    virtual IResource::IOType getInputIOType() const = 0;

    /**
     * @brief 设置Input显示类型
     * @param showType 显示类型
     */
    virtual void setInputShowType(const IResource::ShowType showType) = 0;

    /**
     * @brief 获取Input显示类型
     */
    virtual IResource::ShowType getInputShowType() const = 0;

    /**
     * @brief 获取常用Input值
     */
    virtual std::vector<int8u> getCommonInputValues() const = 0;

    /**
     * @brief 获取标准Input值
     */
    virtual std::array<int8u, STANDARD_IO_SIZE> getStandardInputValues() const = 0;

    /**
     * @brief 获取从站现场总线Input值
     */
    virtual std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> getSlaveFieldbusInputValues() const = 0;

    /**
     * @brief 获取主站现场总线Input值
     */
    virtual std::array<int8u, MASTER_FIELDBUS_IO_SIZE> getMasterFieldbusInputValues() const = 0;

    /**
     * @brief 获取内存Input值
     */
    virtual std::array<int8u, MEMORY_IO_SIZE> getMemoryInputValues() const = 0;

    /**
     * @brief 获取标准Input强制高值
     */
    virtual std::array<int8u, STANDARD_IO_SIZE> getStandardInputForceHighValues() const = 0;

    /**
     * @brief 获取标准Input强制低值
     */
    virtual std::array<int8u, STANDARD_IO_SIZE> getStandardInputForceLowValues() const = 0;

    /**
     * @brief 根据ShowType获取Input标签与备注
     */
    virtual IoLabelItems getInputLabelAndRemark() const = 0;

    /**
     * @brief 获取常用Input下标
     */
    virtual std::vector<unsigned short> getCommonInputIndexs() const = 0;

    /**
     * @brief 设置标准输入强制状态
     *        强制高->强制低  强制低->强制高
     * @param index 下标(bit下标)
     * @return true成功 false失败
     */
    virtual bool setStandardInputForceStatus(const unsigned int index) = 0;

    /**
     * @brief 设置标准输入状态
     * @param index 下标(bit下标)
     * @return true成功 false失败
     */
    virtual bool setStandardInputStatus(const unsigned int index) = 0;

    /**
     * @brief 设置内存输入状态
     *        按Bit设置
     * @param statusIndex 界面中的下标（非IO下标）
     * @param isOn true:on false:off
     * @return true成功 false失败
     */
    virtual bool setMemoryInputStatus(const unsigned int statusIndex, const bool isOn) = 0;

    /**
     * @brief 更新标准输入值（在设置标准输入之后调用，有改变发送改变信号）
     */
    virtual void updateStandardInputValue() = 0;

    /**
     * @brief 更新Input标签、备注
     * @return true更新成功 false失败
     */
    virtual bool updateInputLabelAndRemark() = 0;

    /**
     * @brief 更新常用Input数据
     * @return true成功 false失败
     */
    virtual bool updateCommonInputDatas() = 0;

    /**
     * @brief 更新标准Input数据
     * @return true成功 false失败
     */
    virtual bool updateStandardInputDatas() = 0;

    /**
     * @brief 更新从站现场总线Input数据
     * @return true成功 false失败
     */
    virtual bool updateSlaveFieldbusInputDatas() = 0;

    /**
     * @brief 更新主站现场总线Input数据
     * @return true成功 false失败
     */
    virtual bool updateMasterFieldbusInputDatas() = 0;

    /**
     * @brief 更新内存Input数据
     * @return true成功 false失败
     */
    virtual bool updateMemoryInputDatas() = 0;
#pragma endregion

#pragma region Output
    /**
     * @brief 设置输出调度
     * @param scheduler true:调度 false:取消调度
     */
    virtual void setOutputScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信获取常用输出状态
     *        每次与控制器通信最多获取8个字节数据
     * @param showType 显示类型（查看ShowType枚举）
     * @param size 常用输出数量
     * @param outputIndexs 常用输出下标
     * @param status 读取状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCommonOutputStatus(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &status) = 0;

    /**
     * @brief 与控制器通信获取常用输出控制权
     *        每次与控制器通信最多读取8个字节，读取到对应的bit位为0表示有控制权
     * @param showType 显示类型（查看ShowType枚举）目前只有BIT
     * @param size 常用输出数量
     * @param outputIndexs 常用输出下标
     * @param controls 读取控制权
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCommonOutputControls(const ShowType showType, const unsigned int size, const std::vector<unsigned short> &outputIndexs, std::vector<int8u> &controls) = 0;

    /**
     * @brief 与控制器通信读取输出状态
     *        每次与控制器通信最多读取16个字节，获取状态的地址在内存上需连续
     * @param startByteId 起始下标
     * @param byteNum 数量
     * @param dataBuf 读取状态起始地址（内存上需连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readOutputStatus(const int16u startByteId, const int16u byteNum, int8u *status) = 0;

    /**
     * @brief 与控制器通信读取输出控制权
     *        每次与控制器通信最多读取16个字节，读取到对应的bit位为0表示有控制权
     * @param startByteId 起始下标
     * @param byteNum 数量
     * @param pBuf 读取控制权起始地址（内存上需连续）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readOutputControls(const int16u startByteId, const int16u byteNum, std::vector<int8u> &controls) = 0;

    /**
     * @brief 与控制器通信写输出状态
     *        按Bit设置
     * @param bitIndex Bit下标
     * @param bitValue Bit值。0x00代表设置OFF，0x01代表设置ON
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeOutputStatusByBit(const int16u bitIndex, const int8u bitValue) = 0;

    /**
     * @brief 与控制器通信写输出状态
     *        按byte写
     * @param byteStartIndex byte开始下标
     * @param byteSize byte大小
     * @param status 状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeOutputStatusByByte(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status) = 0;

    /**
     * @brief 设置输出IO类型
     * @param ioType IO类型
     */
    virtual void setOutputIOType(const IResource::IOType ioType) = 0;

    /**
     * @brief 获取输出IO类型
     */
    virtual IResource::IOType getOutputIOType() const = 0;

    /**
     * @brief 设置输出显示类型
     * @param showType 显示类型
     */
    virtual void setOutputShowType(const IResource::ShowType showType) = 0;

    /**
     * @brief 获取输出显示类型
     */
    virtual IResource::ShowType getOutputShowType() const = 0;

    /**
     * @brief 获取常用输出值
     */
    virtual std::vector<int8u> getCommonOutputValues() const = 0;

    /**
     * @brief 获取标准输出值
     */
    virtual std::array<int8u, STANDARD_IO_SIZE> getStandardOutputValues() const = 0;

    /**
     * @brief 获取从站现场总线输出值
     */
    virtual std::array<int8u, SLAVE_FIELDBUS_IO_SIZE> getSlaveFieldbusOutputValues() const = 0;

    /**
     * @brief 获取主站现场总线输出值
     */
    virtual std::array<int8u, MASTER_FIELDBUS_IO_SIZE> getMasterFieldbusOutputValues() const = 0;

    /**
     * @brief 获取内存输出值
     */
    virtual std::array<int8u, MEMORY_IO_SIZE> getMemoryOutputValues() const = 0;

    /**
     * @brief 根据ShowType获取输出标签与备注
     */
    virtual IoLabelItems getOutputLabelAndRemark() const = 0;

    /**
     * @brief 获取常用输出下标
     */
    virtual std::vector<unsigned short> getCommonOutputIndexs() const = 0;

    /**
     * @brief 设置输出状态
     *        按Bit设置
     * @param index 界面中的下标（用于更新模型层值）
     * @param statusIndex 状态下标（bit下标）
     * @param isOn true:on false:off
     * @return true成功 false失败
     */
    virtual bool setOutputStatus(const unsigned int index, const unsigned int statusIndex, const bool isOn) = 0;

    /**
     * @brief 设置输出状态
     *        按byte设置
     * @param byteStartIndex 开始下标（相对于byte）
     * @param byteSize 大小(相对于byte）
     * @param status 状态
     * @return true成功 false失败
     */
    virtual bool setOutputStatus(const int16u byteStartIndex, const int16u byteSize, const std::vector<unsigned char> &status) = 0;

    /**
     * @brief 更新输出标签、备注
     * @return true更新成功 false失败
     */
    virtual bool updateOutputLabelAndRemark() = 0;

    /**
     * @brief 更新常用输出数据
     * @return true成功 false失败
     */
    virtual bool updateCommonOutputDatas() = 0;

    /**
     * @brief 更新标准输出值
     * @return true成功 false失败
     */
    virtual bool updateStandardOutputValues() = 0;

    /**
     * @brief 更新从站现场总线输出值
     * @return true成功 false失败
     */
    virtual bool updateSlaveFieldbusOutputValues() = 0;

    /**
     * @brief 更新主站现场总线输出值
     * @return true成功 false失败
     */
    virtual bool updateMasterFieldbusOutputValues() = 0;

    /**
     * @brief 更新内存输出值
     * @return true成功 false失败
     */
    virtual bool updateMemoryOutputValues() = 0;
#pragma endregion

#pragma region 协作末端IO
    /**
     * @brief 读取末端IO的配置
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readToolIoConfig(std::string &ans) = 0;
    /**
     * @brief 写末端IO的配置
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int writeToolIoConfig(std::string &ans) = 0;
    /**
     * @brief 通知控制器设置配置监听状态
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int setToolIOConfigMonitorState(bool state) = 0;

#pragma endregion

#pragma endregion

#pragma region AD DA
    /**
     * @brief 设置AD调度
     * @param scheduler true调度 false不调度
     */
    virtual void setADScheduler(const bool scheduler) = 0;

    /**
     * @brief 设置AD显示类型
     * @param type AD显示类型
     */
    virtual void setADShowType(const ADDAType type) = 0;

    /**
     * @brief 与控制器通信读取IRLinkAD值
     * @param values AD值
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readIRLinkADValues(std::array<IRLinkADDAStatus, ADDA_MAX_SIZE> &values) = 0;

    /**
     * @brief 获取AD数据 false AD数据 true DA数据
     */
    virtual int readCobotAnalogIODatas(bool isDA, std::vector<Cobot_ADDA_Data> &data) = 0;

    /**
     * @brief 写入AD数据 false AD数据 true DA数据
     */
    virtual int writeCobotAnalogIODatas(const Cobot_ADDA_Status &data) = 0;

    /**
     * @brief 获取IRLinkAD数据
     */
    virtual std::vector<IRLinkADDAData> getIRLinkADDatas() const = 0;

    /**
     * @brief 获取ECatAD数据
     */
    virtual std::vector<ECatADDAData> getECatADDatas() const = 0;

    /**
     * @brief 更新IRLinkAD数据
     */
    virtual bool updateIRLinkADDatas() = 0;

    /**
     * @brief 更新ECatAD数据
     */
    virtual bool updateECatADDatas() = 0;

    /**
     * @brief 设置DA调度
     * @param scheduler true调度 false不调度
     */
    virtual void setDAScheduler(const bool scheduler) = 0;

    /**
     * @brief 设置DA显示类型
     * @param type DA显示类型
     */
    virtual void setDAShowType(const ADDAType type) = 0;

    /**
     * @brief 与控制器通信获取IRLinkDA值
     * @param values DA值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readIRLinkDAValues(std::array<IRLinkADDAStatus, ADDA_MAX_SIZE> &values) = 0;

    /**
     * @brief 与控制器通信写DA值
     * @param index 下标
     * @param flag 0:写输出的值 1:开关量
     * @param value 值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int writeIRLinkDAValue(const int index, const int flag, const IRLinkADDAStatus &value) = 0;

    /**
     * @brief 获取IRLinkDA数据
     */
    virtual std::vector<IRLinkADDAData> getIRLinkDADatas() const = 0;

    /**
     * @brief 获取ECatDA数据
     */
    virtual std::vector<ECatADDAData> getECatDADatas() const = 0;

    /**
     * @brief 设置IRLinkDA的状态
     * @param index 下标
     * @param flag 0：写输出的值 1：写开关量
     * @param status DA状态
     * @return true成功 false失败
     */
    virtual bool setIRLinkDAStatus(const int index, const int flag, const IRLinkADDAStatus &status) = 0;

    /**
     * @brief 设置ECatDA的状态
     * @param index 下标
     * @param falg 1：写输出的值 2：写开关量
     * @param status DA状态
     * @return true成功 false失败
     */
    virtual bool setECatDAStatus(const int index, const int flag, const EcatAdDaState &status) = 0;

    /**
     * @brief 更新IRLinkDA数据
     * @return true成功 false失败
     */
    virtual bool updateIRLinkDADatas() = 0;

    /**
     * @brief 更新ECatDA数据
     * @return true成功 false失败
     */
    virtual bool updateECatDADatas() = 0;
#pragma endregion

#pragma region sysIO
    /**
     * @brief 设置系统Input调度
     * @param scheduler true调度 false不调度
     */
    virtual void setSysInputScheduler(const bool scheduler) = 0;

    /**
     * @brief 设置系统Output调度
     * @param schedulertrue调度 false不调度
     */
    virtual void setSysOutputScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取系统IO值
     * @param inputData 输入值
     * @param outputData 输出值
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readSysIOValues(int16u &inputData, int16u &outputData) = 0;

    /**
     * @brief 与控制器通信 读取系统IO强制状态
     * @param inputFH 输入强制高
     * @param inputFL 输入强制低
     * @param outputFH 输出强制高
     * @param outputFL 输出强制低
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readSysIOForceValues(int16u &inputFH, int16u &inputFL, int16u &outputFH, int16u &outputFL) = 0;

    /**
     * @brief 获取系统输入状态
     */
    virtual std::array<bool, SYSIO_SIZE> getSysInputStatus() const = 0;

    /**
     * @brief 获取系统输入备注
     */
    virtual std::array<std::string, SYSIO_SIZE> getSysInputRemarks() const = 0;

    /**
     * @brief 获取系统输出状态
     */
    virtual std::array<bool, SYSIO_SIZE> getSysOutputStatus() const = 0;

    /**
     * @brief 获取系统输出备注
     */
    virtual std::array<std::string, SYSIO_SIZE> getSysOutputRemarks() const = 0;

    /**
     * @brief 更新系统输入数据
     * @return true成功 false失败
     */
    virtual bool updateSysInputDatas() = 0;

    /**
     * @brief 更新系统输出数据
     * @return true成功 false失败
     */
    virtual bool updateSysOutputDatas() = 0;
#pragma endregion

#pragma region 网络 EtherCAT
    /**
     * @brief 与控制器通信 读取控制器EthInfo信息
     * @param[out] controllerEI EthInfo信息
     * @return ERR_OK成功 其它见错误码
     */
    virtual int readControllerEthInfo(ControllerEthInfo &controllerEI) const = 0;

    /**
     * @brief 与控制器通信 读取EtherCAT PDO丢帧信息
     * @param[out] totalLostCount 总丢包数
     * @param[out] continueLostCount 连续丢包数
     * @param[out] lostFlag 丢失flag
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readEcatPdoLostInfo(int16u &totalLostCount, int16u &continueLostCount, int16u &lostFlag) const = 0;
#pragma endregion

#pragma region 存储卡
    /**
     * @brief 与控制器通信 读取控制器存储卡信息
     * @param[out] info 存储卡信息
     * @return ERR_OK为成功，其它见错误码
     */
    virtual int readSDInfo(std::string &info) const = 0;
#pragma endregion

#pragma region 总线通讯
    /**
     * @brief 设置modbus连接调度
     * @param scheduler true调度 false不调度
     */
    virtual void setModbusConnectScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取Modbus连接状态
     * @param[out] status Modbus连接状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readModbusConnectStatus(ModbusConnectStatus &status) = 0;

    /**
     * @brief 获取Modbus连接状态
     */
    virtual ModbusConnectStatus getModbusConnectStatus() const = 0;

    /**
     * @brief 更新Modbus连接状态
     * @return true成功 false失败
     */
    virtual bool updateModbusConnectStatus() = 0;

    /**
     * @brief 设置EthernetIP调度
     * @param scheduler true调度 false不调度
     */
    virtual void setEthernetIPScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取EthernetIP状态
     * @param[out] status EthernetIP状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readEthernetIPStatus(EthernetIPStatus &status) = 0;

    /**
     * @brief 获取EthernetIP状态
     */
    virtual EthernetIPStatus getEthernetIPStatus() const = 0;

    /**
     * @brief 更新EthernetIP状态
     * @return true成功 false失败
     */
    virtual bool updateEthernetIPStatus() = 0;

    /**
     * @brief 设置EtherCat调度
     * @param scheduler true调度 false不调度
     */
    virtual void setEtherCatScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取EtherCAT状态
     * @param[out] status EtherCAT状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readEtherCatStatus(EtherCATStatus &status) = 0;

    /**
     * @brief 获取EtherCat状态
     */
    virtual EtherCATStatus getEtherCatStatus() const = 0;

    /**
     * @brief 更新EtherCat状态
     * @return true成功 false失败
     */
    virtual bool updateEtherCatStatus() = 0;

    /**
     * @brief 设置MC调度
     * @param scheduler true调度 false不调度
     */
    virtual void setMCScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取MC激活状态
     * @param[out] active MC激活状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readMCActiveStatus(unsigned char &active) = 0;

    /**
     * @brief 与控制器通信 读取MC连接状态
     * @param[out] status MC连接状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readMCConnectStatus(std::array<MCConnectStatus, MC_CONNECT_NUM> &status) = 0;

    /**
     * @brief 获取MC激活状态
     */
    virtual bool getMCActiveStatus() const = 0;

    /**
     * @brief 获取MC连接状态
     * @return
     */
    virtual std::array<MCConnectStatus, MC_CONNECT_NUM> getMCConnectStatus() = 0;

    /**
     * @brief 更新MC状态
     * @return true成功 false失败
     */
    virtual bool updateMCStatus() = 0;

    /**
     * @brief 设置profinet连接调度
     * @param scheduler true调度 false不调度
     */
    virtual void setProfinetConnectScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取profinet连接状态
     * @param[out] status profinet连接状态
     * @return ERR_OK为成功，其他为失败
     */
    virtual int readProfinetConnectStatus(ProfinetConnectStatus &status) = 0;

    /**
     * @brief 获取profinet连接状态
     */
    virtual ProfinetConnectStatus getProfinetConnectStatus() const = 0;

    /**
     * @brief 更新profinet连接状态
     * @return true成功 false失败
     */
    virtual bool updateProfinetConnectStatus() = 0;
#pragma endregion

#pragma region 伺服状态
    /**
     * @brief 与控制器通信通知控制器准备伺服参数(驱控一体电柜专用)
     * @param axisNo 轴号
     * @param pageID 页号
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int prepareServoParam(int axisNo, int pageID) = 0;

    /**
     * @brief 与控制器通信读取伺服参数（一次只能读取10个）
     * @param axisNo 轴号
     * @param pageID 页ID
     * @param pFunCode 获取的伺服参数
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readServoParam(int axisNo, int pageID, char pFunCode[10][12]) = 0;

    /**
     * @brief 与控制器通信读取一个伺服码的值(注意：该读取有延时！由控制器内部控制！)
     * @param axisNo 轴号
     * @param[in] code 伺服码
     * @param[out] value 值
     * @return true读取成功 false读取失败
     */
    virtual bool readSingleServoCode(int axisNo, const std::string &code, std::string &value) = 0;

    /**
     * @brief 与控制器通信设置单个伺服码的值
     * @param axisNo 轴号
     * @param code 伺服码
     * @param value 值
     * @return true成功 false失败
     */
    virtual bool writeSingleServoCode(int axisNo, const std::string &code, const std::string &value) = 0;

    /**
     * @brief 允许重置编码器
     * @param axisNo 轴号
     * @return true允许 false不允许
     */
    virtual bool allowResetEncoder() = 0;

    /**
     * @brief 与控制器通信重置编码器
     * @param axisNo 轴号
     * @return true成功 false失败
     */
    virtual bool writeResetEncoder(int axisNo) = 0;

    /**
     * @brief 与控制器通信读重置编码器结果
     * @param[in] axisNo 轴号
     * @param[out] result 结果
     * @return true成功 false失败
     */
    virtual bool readResetEncoderResult(int axisNo, int &result) = 0;
#pragma endregion

#pragma region 工况
    /**
     * @brief 设置电流调度
     * @param scheduler true调度 false不调度
     */
    virtual void setElectricScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取机械臂当前电流
     * @param[out] current 当前电流值
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCurrentElectric(std::vector<double> &current) = 0;

    /**
     * @brief 与控制器通信 读取机械臂电流最大值（单位百分比）
     * @param[out] maxCurrent 电流最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readMaxElectric(std::vector<double> &maxCurrent) = 0;

    /**
     * @brief 与控制器通信 重置机械臂电流最大值（单位百分比）
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int resetMaxElectric() = 0;

    /**
     * @brief 是否允许重置电流历史最大值
     * @return true允许 false不允许
     */
    virtual bool allowResetMaxElectric() = 0;

    /**
     * @brief 获取当前电流值
     */
    virtual std::vector<double> getCurrentElectric() const = 0;

    /**
     * @brief 获取电流历史最大值
     * @return
     */
    virtual std::vector<double> getMaxElectric() const = 0;

    /**
     * @brief 更新电流当前值、历史最大值
     * @return true成功 false失败
     */
    virtual bool updateElectric() = 0;

    /**
     * @brief 设置平均负载率调度
     * @param scheduler true调度 false不调度
     */
    virtual void setAvgLoadRateScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取机械臂当前平均负载率（单位百分比）
     * @param[out] avgLoadRate 平均负载率
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCurrentAvgLoadRate(std::vector<double> &avgLoadRate) = 0;

    /**
     * @brief 获取当前平均负载率
     */
    virtual std::vector<double> getCurrentAvgLoadRate() const = 0;

    /**
     * @brief 更新平均负载率
     * @return true成功 false失败
     */
    virtual bool updateAvgLoadRate() = 0;

    /**
     * @brief 设置过载率调度
     * @param scheduler true调度 false不调度
     */
    virtual void setOverLoadScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取当前过载率（单位百分比）
     * @param[out] overLoad 过载率
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readCurrentOverLoad(std::vector<double> &overLoad) = 0;

    /**
     * @brief 与控制器通信 读取过载率最大值（单位百分比）
     * @param[out] maxOverLoad 过载率最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int readMaxOverLoad(std::vector<double> &maxOverLoad) = 0;

    /**
     * @brief 与控制器通信 重置过载率最大值
     * @return ERR_OK为成功，其它请见错误码
     */
    virtual int resetMaxOverLoad() = 0;

    /**
     * @brief 是否允许重置过载率最大值
     * @return true允许 false不允许
     */
    virtual bool allowResetMaxOverLoad() = 0;

    /**
     * @brief 获取当前过载率
     */
    virtual std::vector<double> getCurrentOverLoad() const = 0;

    /**
     * @brief 获取过载率最大值
     */
    virtual std::vector<double> getMaxOverLoad() const = 0;

    /**
     * @brief 更新过载率当前值、最大值
     * @return true成功 false失败
     */
    virtual bool updateOverLoad() = 0;

    /**
     * @brief 设置过热率调度
     * @param scheduler true调度 false不调度
     */
    virtual void setOverHeatScheduler(const bool scheduler) = 0;

    /**
     * @brief 与控制器通信 读取当前过热率
     * @param[out] overHeat 过热率
     * @return ERR_OK为成功，其它请见错误
     */
    virtual int readCurrentOverHeat(std::vector<double> &overHeat) = 0;

    /**
     * @brief 获取当前过热率
     */
    virtual std::vector<double> getCurrentOverHeat() const = 0;

    /**
     * @brief 更新过热率当前值
     * @return true成功 false失败
     */
    virtual bool updateOverHeat() = 0;
#pragma endregion

#pragma region 示教器压缩包信息
    /**
     * @brief 向控制器写入统计示教器压缩包信息的命令
     * @param cmd 输入，命令，1 - 开始统计
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeCountTPPackagesInfoCmd(int cmd) = 0;
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
    virtual int readCountTPPackagesInfoCmdResult(int &result) = 0;
#pragma endregion

#pragma region 信号
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
    void IRLinkADValueChanged(const QHash<int, IRLinkADDAStatus> &status);
    // EtherCATAD值改变信号
    void ECatADValueChanged(const QHash<int, EcatAdDaState> &status);
    // IRLinkDA值改变信号
    void IRLinkDAValueChanged(const QHash<int, IRLinkADDAStatus> &status);
    // EtherCATDA值改变信号
    void ECatDAValueChanged(const QHash<int, EcatAdDaState> &status);

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
}  // namespace InoRobBusiness
