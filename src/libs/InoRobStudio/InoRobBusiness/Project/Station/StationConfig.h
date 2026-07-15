#pragma once
#include "IStationConfig.h"

namespace InoRobBusiness
{


class IProject;

/// <summary>
/// 全局标签处理类
/// </summary>
class StationConfig : public IStationConfig
{
    Q_OBJECT

public:
    StationConfig(QObject *parent = nullptr);
    virtual ~StationConfig();

public:
    static int FromFile(StationReserveCfg &stStationReserveCfg, const std::string &path);
    static int ToFile(const std::string &path, const StationReserveCfg &stStationReserveCfg);

public:
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) override;
    virtual void SetControllerIp(const std::string &ip) override;
    virtual void SetProjectName(const std::string &name) override;
    virtual std::string DefaultFileName() override;

    virtual bool isModified() override;
    virtual void setModifyState(bool state) override;
    virtual int readStationReserveCfgFile() override;
    virtual int saveStationReserveCfgFile() override;
    virtual int setStationReserveCfg(const StationReserveCfg &stationCfg) override;
    virtual StationReserveCfg getStationReserveCfg() override;
    virtual int setRISPProgNameByIndex(int index, const string &programName) override;
    virtual int getRISPProgNameByIndex(int index, string &programName) override;
    virtual void setRISPProgName(const std::array<std::string, STATIONRESERVE_RISP_NUM> &arrStationProgramName) override;
    virtual void getRISPProgName(std::array<std::string, STATIONRESERVE_RISP_NUM> &arrStationProgramName) override;
    virtual int setStationReserveMode(int mode) override;
    virtual int getStationReserveMode() override;
    virtual int resetStationState(int flag, int i32Stationindex) override;
    virtual int readStationStates(uint32_t stationState[STATIONRESERVE_RISP_NUM]) override;
private:
    /**
     * @brief 执行相关操作前的状态检查
     */
    bool checkStatus();
    // 将Json对象解析为数据
    int static FromJsonObj(cJSON *obj, StationReserveCfg &stStationReserveCfg);
    // 将数据转换为Json对象
    int static ToJsonObj(const StationReserveCfg &stStationReserveCfg, cJSON *obj);

    // 转换文本编码格式
    void convertGB2312ToUTF8(IoLabelItems &labels);
    void convertUTF8ToGB2312(IoLabelItems &labels);

private:
    IProject *_pProject = nullptr;  // 工程父对象
    std::string m_Ip;               // 控制器ip地址
    std::string m_ProjectName;      // 当前加载的工程名称
    bool _isModified;               // 是否被修改过
    IDataSrvBase *_pDataSrvBase = nullptr;

    StationReserveCfg m_stStationReserveCfg; //工位预约配置信息

    ProjectFileOperateMode _fileOperateMode;  // 工程文件操作模式
};
}  // namespace InoRobBusiness
