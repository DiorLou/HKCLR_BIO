#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../FieldbusTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
constexpr int NO_IOMAP_ADDR_V1 = -1;  // IO未映射默认地址

/**
 * @brief IO映射重置方式
 */
enum IOMapResetMethod_V1
{
    UNKNOW_IO_V1 = 0,           // 未知IO
    DIGITAL_IO_V1 = 1,          // 标准IO
    FIELDBUS_IO_V1 = 2,         // 从站IO
    MEMORY_IO_V1 = 3,           // 内存IO
    SYSTEM_IO_V1 = 4,           // 系统IO
    FIELDBUS_MASTER_IO_V1 = 5,  // 主站IO
};

/**
 * @brief 总线IO映射展示数据
 */
struct FieldbusIOMapData_V1
{
    IOType_V1 ioType = IOType_V1::IOTP_IN_V1;                  // IO类型
    unsigned int funcId = FieldBusFunc_InBit_V1::PrgStart_V1;  // funID
    int memAddr = -1;                                          // 内存地址
    MemoryLength_V1 length = MemoryLength_V1::ML_BIT_V1;       // 内存长度
    std::string name;                                          // 名称

    FieldbusIOMapData_V1(IOType_V1 _ioType, unsigned int _funcId, MemoryLength_V1 _length, const std::string &_name)
    {
        ioType = _ioType;
        funcId = _funcId;
        memAddr = -1;
        length = _length;
        name = _name;
    }

    FieldbusIOMapData_V1(IOType_V1 _ioType, unsigned int _funcId, int _memAddr, MemoryLength_V1 _length, const std::string &_name)
    {
        ioType = _ioType;
        funcId = _funcId;
        memAddr = _memAddr;
        length = _length;
        name = _name;
    }
};

/**
 * @brief IO映射通信数据
 */
struct FieldbusIOMap_V1
{
    unsigned short funcId;  // 枚举ID
    int memAddr;            // Bit位地址
    unsigned short length;  // 占用的Bit位数，分为1、16、32
};

/**
 * @brief IO映射通信数据信息
 */
struct FieldbusIOMapInfo_V1
{
    unsigned int funcNum;                   //  映射数量
    FieldbusIOMap_V1 *fieldbusIOMapArrays;  // 映射数据列表
};

/**
 * @brief IO映射基类
 */

class INOROBBUSINESSPROXY_CLASS IOMap_V1
{
#pragma region 数据转换

public:
    static IOMapResetMethod_V1 IOMapResetMethod_ToProxy(IOMapResetMethod ioMapResetMethod);
    static IOMapResetMethod IOMapResetMethod_FromProxy(IOMapResetMethod_V1 ioMapResetMethod_V1);

    static bool FieldbusIOMapData_ToProxy(const FieldbusIOMapData &fieldbusIOMapData, FieldbusIOMapData_V1 &fieldbusIOMapData_V1);
    static bool FieldbusIOMapData_FromProxy(const FieldbusIOMapData_V1 &fieldbusIOMapData_V1, FieldbusIOMapData &fieldbusIOMapData);

    static bool FieldbusIOMap_ToProxy(const FieldbusIOMap &fieldbusIOMap, FieldbusIOMap_V1 &fieldbusIOMap_V1);
    static bool FieldbusIOMap_FromProxy(const FieldbusIOMap_V1 &fieldbusIOMap_V1, FieldbusIOMap &fieldbusIOMap);

    static bool FieldbusIOMapInfo_ToProxy(const FieldbusIOMapInfo &fieldbusIOMapInfo, FieldbusIOMapInfo_V1 &fieldbusIOMapInfo_V1);
    static bool FieldbusIOMapInfo_FromProxy(const FieldbusIOMapInfo_V1 &fieldbusIOMapInfo_V1, FieldbusIOMapInfo &fieldbusIOMapInfo);

#pragma endregion

#pragma region 构造与析构

private:
    IIOMap *_ioMap = nullptr;

public:
    IOMap_V1(IIOMap *ioMap);
    ~IOMap_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 与控制器通信读取当前IO映射数量   ---   已测
     * @param[out] ioMapCount IO映射数量
     * @return true 读取成功  false 读取失败
     */
    bool readFieldbusIOMapCurCount(int &ioMapCount);

    /**
     * @brief 与控制器通信读取IO映射配置
     * @param[out] info IO映射信息
     * @return true成功 false失败
     */
    bool readFieldbusIOMap(FieldbusIOMapInfo_V1 &info);

    /**
     * @brief 与控制器通信写IO映射配置
     * @param[in] info IO映射信息
     * @return true成功 false失败
     */
    bool writeFieldbusIOMap(const FieldbusIOMapInfo_V1 &info);

    /**
     * @brief 检查当前是否允许保存IO映射   ---   已测
     * @return true允许 false不允许
     */
    bool allowSaveFieldbusIOMap();

    /**
     * @brief 保存IO映射
     * @param[in] datas IO映射数据
     * @return true成功 false失败
     */
    bool saveFieldbusIOMap(const std::vector<FieldbusIOMapData_V1> &datas);

    /**
     * @brief 刷新IO映射数据   ---   已测
     * @return true成功 false失败
     */
    bool refreshFieldbusIOMap();

    /**
     * @brief 获取IO映射数据   ---   已测
     */
    std::vector<FieldbusIOMapData_V1> getFieldbusIOMapDatas() const;

    /**
     * @brief 重置IO映射
     * @param method 重置方式
     * @return true成功 false失败
     */
    bool resetFieldbusIOMap(const IOMapResetMethod_V1 method);

    /**
     * @brief 导出IO映射配置到文件
     * @param fullFileName 文件名（包含完整路径）
     * @return true成功 false失败
     */
    bool exportFieldbusIOMapToFile(const std::string &fullFileName);

    /**
     * @brief 从文件中导入IO映射配置
     * @param fullFileName 文件名（包含完整路径）
     * @return true成功 false失败
     */
    bool importFieldbusIoMapFromFile(const std::string &fullFileName);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
