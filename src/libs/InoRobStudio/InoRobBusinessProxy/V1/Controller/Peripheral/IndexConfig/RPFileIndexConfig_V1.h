#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS RPFileIndexConfig_V1
{
#pragma region 构造与析构

private:
    IIndexConfig *_indexConfig = nullptr;

public:
    RPFileIndexConfig_V1(IIndexConfig *indexConfig);
    ~RPFileIndexConfig_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    int indexUpperLimit();
    bool isUpperLimit();
    std::string configFileLocalPath();
    std::string configFileCtrlPath();
    int analysisConfigFile(const std::string &localPath);
    void initConfigArr();
    int delConfig(const IndexConfig &config);
    std::vector<int> getAvailableIndexs();
    std::vector<std::string> getAailableNames();
    std::vector<int> getInvalidItem();
    int saveConfigFile(const std::string &localPath, const std::string &ctrlPath);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
