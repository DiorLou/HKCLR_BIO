#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "IndexConfigDefault.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS RPFileIndexConfig : public IndexConfigDefault
{
    Q_OBJECT

public:
    RPFileIndexConfig(IDataSrvBase *pDataSrv, IConnection *pConnection, IProject *pProject, IMonitor *pMonitor);
    ~RPFileIndexConfig();

public:
    virtual int indexUpperLimit() override;
    virtual bool isUpperLimit() override;
    virtual std::string configFileLocalPath() override;
    virtual std::string configFileCtrlPath() override;
    virtual int analysisConfigFile(const std::string &localPath) override;
    virtual void initConfigArr() override;
    virtual int delConfig(const IndexConfig &config) override;
    virtual std::vector<int> getAvailableIndexs() override;
    virtual std::vector<std::string> getAailableNames() override;
    virtual std::vector<int> getInvalidItem() override;
    virtual int saveConfigFile(const std::string &localPath, const std::string &ctrlPath) override;

private:
    /**
     * @brief 获取控制器工程名称列表
    */
    std::vector<std::string> getRPFileNames();
    /**
     * @brief 向控制器下发更新全局位置点位文件序号配置命令
     * @return 成功返回0，其他请见错误码
    */
    int sendIndexConfigUpdateCmd();
    /**
     * @brief 回读控制器更新全局位置点位文件序号配置的状态
     * @param state 更新状态，0-成功，非0-失败
     * @return 成功返回0，其他请见错误码
    */
    int readIndexConfigUpdateStatus(int &state);
};
}  // namespace InoRobBusiness
