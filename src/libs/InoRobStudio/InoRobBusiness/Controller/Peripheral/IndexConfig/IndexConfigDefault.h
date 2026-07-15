#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IIndexConfig.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS IndexConfigDefault : public IIndexConfig
{
    Q_OBJECT

public:
    IndexConfigDefault(IDataSrvBase *pDataSrv, IConnection *pConnection, IProject *pProject, IMonitor *pMonitor);
    virtual ~IndexConfigDefault();

public:
    virtual int indexUpperLimit() override;
    virtual bool isUpperLimit() override;
    virtual std::string configFileLocalPath() override;
    virtual std::string configFileCtrlPath() override;
    virtual int downloadConfigFile(bool &isExisted, const std::string &localPath, const std::string &ctrlPath) override;
    virtual int analysisConfigFile(const std::string &localPath) override;
    virtual void initConfigArr() override;
    virtual std::vector<IndexConfig> getConfigArr() override;
    virtual IndexConfig getConfig(int index) override;
    virtual IndexConfig getConfig(const std::string &name) override;
    virtual int findConfig(int index) override;
    virtual int findConfig(const std::string &name) override;
    virtual int addConfig() override;
    virtual int modifyConfig(const IndexConfig &oldConfig, const IndexConfig &newConfig) override;
    virtual int delConfig(const IndexConfig &config) override;
    virtual std::vector<int> getAvailableIndexs() override;
    virtual std::vector<std::string> getAailableNames() override;
    virtual std::vector<int> getInvalidItem() override;
    virtual bool isIndexExisted(int index) override;
    virtual bool isNameExisted(const std::string &name) override;
    virtual int saveConfigFile(const std::string &localPath, const std::string &ctrlPath) override;

    // 检查操作权限
    bool checkConfigFileOperatePermission();

    // 检查保存权限
    bool checkConfigFileSavePermission();

private:
    /**
     * @brief 按序号升序排列配置信息
     * @param configArr 序号配置信息集合
     */
    void SortConfigArr(std::vector<IndexConfig> &configArr);
    /**
     * @brief 按序号升序排列配置信息模板
     */
    static bool SortConfigArrMode(const IndexConfig &config1, const IndexConfig &config2);

public:
    std::vector<IndexConfig> _configArr;  // 配置信息集合
    IDataSrvBase *_pDataSrv = nullptr;    // 通讯
    IConnection *_pConnection = nullptr;  // 连接
    IProject *_pProject = nullptr;        // 工程
    IMonitor *_pMonitor = nullptr;        // 监控
};
}  // namespace InoRobBusiness
