#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define MAX_NUM_PRJ_INDEX_CFG_V1  256                           // 工程序号配置最大数量
#define PRJ_INDEX_CFG_FILENAME_V1 "ProjMappingFile.dat"         // 工程序号配置文件名称
#define PRJ_INDEX_CFG_VERSION_V1  "S03.21--projmappingVer 1.0"  // 工程序号配置文件版本信息

#define MAX_NUM_RP_INDEX_CFG_V1  128                        // 全局位置点位文件序号配置最大数量
#define RP_INDEX_CFG_FILENAME_V1 "RobPointMappingFile.dat"  // 全局位置点位文件序号配置文件名称
#define RP_INDEX_CFG_FILETYPE_V1 "PosMappingFile"           // 点位文件序号配置文件类型

/**
 * @brief 序号配置信息
 */
struct IndexConfigData_V1
{
    IndexConfigData_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        index = -1;
        name = std::string();
    }

    IndexConfigData_V1 &operator=(const IndexConfigData_V1 &other)
    {
        this->index = other.index;
        this->name = other.name;
        return (*this);
    }

    int index;         // 序号
    std::string name;  // 名称
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS IndexConfig_V1
{
#pragma region 构造与析构

public:
    IndexConfig_V1();
    ~IndexConfig_V1();

#pragma endregion

#pragma region 数据转换

public:
    static bool IndexConfig_ToProxy(const IndexConfig &indexConfig, IndexConfigData_V1 &indexConfigData_V1);
    static bool IndexConfig_FromProxy(const IndexConfigData_V1 &indexConfigData_V1, IndexConfig &indexConfig);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
