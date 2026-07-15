#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
#pragma region 常量与数据类型

#define MAX_NUM_PRJ_INDEX_CFG  256                           // 工程序号配置最大数量
#define PRJ_INDEX_CFG_FILENAME "ProjMappingFile.dat"         // 工程序号配置文件名称
#define PRJ_INDEX_CFG_VERSION  "S03.21--projmappingVer 1.0"  // 工程序号配置文件版本信息

#define MAX_NUM_RP_INDEX_CFG  128                        // 全局位置点位文件序号配置最大数量
#define RP_INDEX_CFG_FILENAME "RobPointMappingFile.dat"  // 全局位置点位文件序号配置文件名称
#define RP_INDEX_CFG_FILETYPE "PosMappingFile"           // 点位文件序号配置文件类型

/**
 * @brief 序号配置信息
 */
struct IndexConfig
{
    IndexConfig()
    {
        Initialize();
    }

    void Initialize()
    {
        index = -1;
        name = std::string();
    }

    IndexConfig &operator=(const IndexConfig &other)
    {
        this->index = other.index;
        this->name = other.name;
        return (*this);
    }

    int index;         // 序号
    std::string name;  // 名称
};
#pragma endregion

/*
    序号配置基类
    Create by lcm at 2024/04/03 创建。
*/
class INOROBBUSINESS_CLASS IIndexConfig : public QObject
{
    Q_OBJECT

public:
    virtual ~IIndexConfig()
    {
    }

    /**
     * @brief 配置(序号)上限
     */
    virtual int indexUpperLimit() = 0;
    /**
     * @brief 配置是否达到上限
     */
    virtual bool isUpperLimit() = 0;
    /**
     * @brief 配置文件本地路径
     */
    virtual std::string configFileLocalPath() = 0;
    /**
     * @brief 配置文件控制器路径
     */
    virtual std::string configFileCtrlPath() = 0;
    /**
     * @brief 从控制器下载配置文件到本地
     * @param localPath 输出，配置文件在控制器中是否存在，因为需要上位机配置后才会有，不存在则应当不执行后续处理
     * @param localPath 输入，配置文件本地路径
     * @param ctrlPath 输入，配置文件控制器路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int downloadConfigFile(bool &isExisted, const std::string &localPath, const std::string &ctrlPath) = 0;
    /**
     * @brief 解析配置文件，配置数据存在缓存中
     * @param localPath 输入，配置文件本地路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int analysisConfigFile(const std::string &localPath) = 0;
    /**
     * @brief 初始化缓存的配置信息
     */
    virtual void initConfigArr() = 0;
    /**
     * @brief 获取配置信息集合
     */
    virtual std::vector<IndexConfig> getConfigArr() = 0;
    /**
     * @brief 根据序号从缓存中的配置信息集合中获取对应配置信息
     * @param index 输入，序号
     * @return 配置信息
     */
    virtual IndexConfig getConfig(int index) = 0;
    /**
     * @brief 根据名称从缓存中的配置信息集合中获取对应配置信息
     * @param name 输入，名称
     * @return 配置信息
     */
    virtual IndexConfig getConfig(const std::string &name) = 0;
    /**
     * @brief 查找对应序号的配置信息，在集合中的下标
     * @param index 输入，序号
     * @return 在集合中的下标，不存在则返回-1
     */
    virtual int findConfig(int index) = 0;
    /**
     * @brief 查找对应名称的配置信息，在集合中的下标
     * @param index 输入，名称
     * @return 在集合中的下标，不存在则返回-1
     */
    virtual int findConfig(const std::string &name) = 0;
    /**
     * @brief 向缓存中的配置信息集合中添加配置信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int addConfig() = 0;
    /**
     * @brief 修改缓存中配置集合的对应配置信息项
     * @param oldConfig 输入，待修改的原配置信息
     * @param newConfig 输入，新配置信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int modifyConfig(const IndexConfig &oldConfig, const IndexConfig &newConfig) = 0;
    /**
     * @brief 删除缓存中的配置信息集合的对应配置信息项
     * @param config 输入，待删除的配置信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int delConfig(const IndexConfig &config) = 0;
    /**
     * @brief 获取可用的序号集合
     */
    virtual std::vector<int> getAvailableIndexs() = 0;
    /**
     * @brief 获取可用的名称集合
     */
    virtual std::vector<std::string> getAailableNames() = 0;
    /**
     * @brief 获取无效项的集合
     * @return 无效项在配置信息中的下标集合
     */
    virtual std::vector<int> getInvalidItem() = 0;
    /**
     * @brief 检查缓存的配置信息集合中是否已存在该序号对应的配置信息
     * @param index 输入，序号
     * @return true-已存在，false-不存在
     */
    virtual bool isIndexExisted(int index) = 0;
    /**
     * @brief 检查缓存的配置信息集合中是否已存在该名称对应的配置信息
     * @param index 输入，名称
     * @return true-已存在，false-不存在
     */
    virtual bool isNameExisted(const std::string &name) = 0;
    /**
     * @brief 将缓存中的配置信息集合保存到本地文件中，同时下发给控制器，并通知控制器更新配置
     * @param localPath 输入，配置文件本地路径
     * @param ctrlPath 输入，配置文件控制器路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveConfigFile(const std::string &localPath, const std::string &ctrlPath) = 0;

    /**
     * @brief 检查操作权限
     * @return true-通过，false-不通过
     */
    virtual bool checkConfigFileOperatePermission() = 0;

    /**
     * @brief 检查保存权限
     * @return true-通过，false-不通过
     */
    virtual bool checkConfigFileSavePermission() = 0;
};
}  // namespace InoRobBusiness
