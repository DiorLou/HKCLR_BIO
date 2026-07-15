#pragma once
#include <QObject>
#include <string>
#include "dllspec.h"
#include "../FieldbusTypes.h"

constexpr int NO_IOMAP_ADDR = -1;  // IO未映射默认地址

namespace InoRobBusiness
{
/**
 * @brief IO映射重置方式
 */
enum IOMapResetMethod
{
    UNKNOW_IO = 0,           // 未知IO
    DIGITAL_IO = 1,          // 标准IO
    FIELDBUS_IO = 2,         // 从站IO
    MEMORY_IO = 3,           // 内存IO
    SYSTEM_IO = 4,           // 系统IO
    FIELDBUS_MASTER_IO = 5,  // 主站IO
};

/**
 * @brief 总线IO映射展示数据
 */
struct FieldbusIOMapData
{
    IOType ioType = IOType::IOTP_IN;                     // IO类型
    unsigned int funcId = FieldBusFunc_InBit::PrgStart;  // funID
    int memAddr = -1;                                    // 内存地址
    MemoryLength length = MemoryLength::ML_BIT;          // 内存长度
    std::string name;                                    // 名称

    FieldbusIOMapData(IOType _ioType, unsigned int _funcId, MemoryLength _length, const std::string &_name)
    {
        ioType = _ioType;
        funcId = _funcId;
        memAddr = -1;
        length = _length;
        name = _name;
    }

    FieldbusIOMapData(IOType _ioType, unsigned int _funcId, int _memAddr, MemoryLength _length, const std::string &_name)
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
struct FieldbusIOMap
{
    unsigned short funcId;  // 枚举ID
    int memAddr;            // Bit位地址
    unsigned short length;  // 占用的Bit位数，分为1、16、32
};

/**
 * @brief IO映射通信数据信息
 */
struct FieldbusIOMapInfo
{
    unsigned int funcNum;                //  映射数量
    FieldbusIOMap *fieldbusIOMapArrays;  // 映射数据列表
};

/**
 * @brief IO映射基类
 */
class INOROBBUSINESS_CLASS IIOMap : public QObject
{
    Q_OBJECT

public:
    virtual ~IIOMap()
    {
    }

    /**
     * @brief 与控制器通信读取当前IO映射数量
     * @param[out] ioMapCount IO映射数量
     * @return true 读取成功  false 读取失败
     */
    virtual bool readFieldbusIOMapCurCount(int &ioMapCount) = 0;

    /**
     * @brief 与控制器通信读取IO映射配置
     * @param[out] info IO映射信息
     * @return true成功 false失败
     */
    virtual bool readFieldbusIOMap(FieldbusIOMapInfo &info) = 0;

    /**
     * @brief 与控制器通信写IO映射配置
     * @param[in] info IO映射信息
     * @return true成功 false失败
     */
    virtual bool writeFieldbusIOMap(const FieldbusIOMapInfo &info) = 0;

    /**
     * @brief 检查当前是否允许保存IO映射
     * @return true允许 false不允许
     */
    virtual bool allowSaveFieldbusIOMap() = 0;

    /**
     * @brief 保存IO映射
     * @param[in] datas IO映射数据
     * @return true成功 false失败
     */
    virtual bool saveFieldbusIOMap(const std::vector<FieldbusIOMapData> &datas) = 0;

    /**
     * @brief 刷新IO映射数据
     * @return true成功 false失败
     */
    virtual bool refreshFieldbusIOMap() = 0;

    /**
     * @brief 获取IO映射数据
     */
    virtual std::vector<FieldbusIOMapData> getFieldbusIOMapDatas() const = 0;

    /**
     * @brief 根据funid获取绑定的地址
     * @param funcId 输入 功能码
     * @return 绑定的总线地址
     */
    virtual int getMemAddrByFuncId(unsigned int funcId) const = 0;

    /**
     * @brief 重置IO映射
     * @param method 重置方式
     * @return true成功 false失败
     */
    virtual bool resetFieldbusIOMap(const IOMapResetMethod method) = 0;

    /**
     * @brief 导出IO映射配置到文件
     * @param fullFileName 文件名（包含完整路径）
     * @return true成功 false失败
     */
    virtual bool exportFieldbusIOMapToFile(const std::string &fullFileName) = 0;

    /**
     * @brief 从文件中导入IO映射配置
     * @param fullFileName 文件名（包含完整路径）
     * @return true成功 false失败
     */
    virtual bool importFieldbusIoMapFromFile(const std::string &fullFileName) = 0;
};
}  // namespace InoRobBusiness
