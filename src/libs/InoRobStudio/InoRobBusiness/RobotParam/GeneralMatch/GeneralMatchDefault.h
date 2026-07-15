#pragma once
#include "IGeneralMatch.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS GeneralMatchDefault : public IGeneralMatch
{
public:
    GeneralMatchDefault(IDataSrvBase *pDataService, IConnection *pConnection);
    ~GeneralMatchDefault();
    int readRobotParamMatchInfo(std::string &info) override;
    int readRobotParamSyncStatus(std::string &info) override;
    int startRobotParamSync(const std::string &info) override;
    int setGeneralMatchStatus(const std::string &status) override;
    int startControllerGetBodyMatchRecord() override;
    int readBodyMatchRecordStatus(std::string &status) override;
    bool getGeneralMatchInfo(GeneralMatchInfo &matchInfo) override;
    bool getRobotParamSyncStatus(RobotParamSyncStatus &status) override;
    bool getGeneralMatchOpen() override;
    bool setGeneralMatchOpen(bool open) override;
    bool allowTracingGeneralMatch() override;
    int getGeneralMatchRecord(const std::string &fullFileName) override;

private:
    IDataSrvBase *_pDataService = nullptr;
    IConnection *_pConnection = nullptr;

    /**
     * @brief 反序列化机型参数匹配状态
     * @param[in] info 信息
     * @param[out] matchInfo 匹配信息
     * @return 0 反序列化成功, -1 info转换CJson失败, -2 异常。
     */
    int deserializeRobotParamMatchInfo(const string &info, GeneralMatchInfo &matchInfo);

    /**
     * @brief 反序列化机型参数同步状态
     * @param[in] info 信息
     * @param[out] syncStatus 机型参数同步状态
     * @return 0 反序列化成功, -1 info转换CJson失败, -2 异常。
     */
    int deserializeRobotParamSyncStatus(const string &info, RobotParamSyncStatus &syncStatus);

    /**
     * @brief 获取本体通配记录
     * @return true成功 false失败
     */
    bool getBodyMatchRecord();
};
}  // namespace InoRobBusiness
