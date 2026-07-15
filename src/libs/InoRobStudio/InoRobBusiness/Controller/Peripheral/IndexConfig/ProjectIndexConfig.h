#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IndexConfigDefault.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ProjectIndexConfig : public IndexConfigDefault
{
    Q_OBJECT

public:
    ProjectIndexConfig(IDataSrvBase *pDataSrv, IConnection *pConnection, IProject *pProject, IMonitor *pMonitor);
    ~ProjectIndexConfig();

public:
    virtual int indexUpperLimit() override;
    virtual bool isUpperLimit() override;
    virtual std::string configFileLocalPath() override;
    virtual std::string configFileCtrlPath() override;
    virtual int analysisConfigFile(const std::string &localPath) override;
    virtual void initConfigArr() override;
    virtual std::vector<int> getAvailableIndexs() override;
    virtual std::vector<std::string> getAailableNames() override;
    virtual std::vector<int> getInvalidItem() override;
    virtual int saveConfigFile(const std::string &localPath, const std::string &ctrlPath) override;

private:
    /**
     * @brief 获取控制器工程名称列表
     */
    std::vector<std::string> getProjectNames();
    /**
     * @brief 向控制器下发更新工程序号配置命令
     * @return 成功返回0，其他请见错误码
     */
    int sendIndexConfigUpdateCmd();

private:
    std::vector<std::string> _projectNames;
};
}  // namespace InoRobBusiness
