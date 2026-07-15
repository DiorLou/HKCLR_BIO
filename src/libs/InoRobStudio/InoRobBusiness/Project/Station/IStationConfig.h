#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "../ProjectHelper.h"
#include "dllspec.h"

namespace InoRobBusiness
{
#define STATIONRESERVE_RISP_NUM   8  /* 远程IO启动程序的工位数量  */

//工位状态
enum StationReserveState
{
    STATION_STATE_IDLE = 0,      // 未执行
    STATION_STATE_RUNNING,       // 正在执行
    STATION_STATE_STOP,          // 暂停
    STATION_STATE_QUEUED,        // 排队等待执行
    STATION_STATE_ERR = 15,      // 工位启动失败
};

struct IOStartProgram
{
    std::array<std::string, STATIONRESERVE_RISP_NUM> arrStationProgramName;//8个工位对应的8个程序
    void initialize()
    {
        arrStationProgramName.fill("");
    }

    IOStartProgram()
    {
        initialize();
    }

    IOStartProgram &operator=(const IOStartProgram &other)
    {
        std::copy(std::begin(other.arrStationProgramName), std::end(other.arrStationProgramName), std::begin(this->arrStationProgramName));
        return (*this);
    }
};

struct StationReserveCfg
{
    int i32StationReserveMode;      // 0-禁用工位预约，1-启用工位预约-远程IO启动程序， 2-启用工位预约-远程数值启动程序
    IOStartProgram stRISPConfig;    // 远程IO启动程序工位配置
    void initialize()
    {
        i32StationReserveMode = 0;
        stRISPConfig.initialize();
    }

    StationReserveCfg()
    {
        initialize();
    }

    StationReserveCfg &operator=(const StationReserveCfg &other)
    {
        this->i32StationReserveMode = other.i32StationReserveMode;
        this->stRISPConfig = other.stRISPConfig;
        return (*this);
    }
};

/**
 * @brief 工位预约配置处理基类
 */
class INOROBBUSINESS_CLASS IStationConfig : public QObject
{
    Q_OBJECT

public:
    virtual ~IStationConfig()
    {
    }

    /**
     * @brief 设置工程的文件操作模式
     */
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) = 0;
    /**
     * @brief 设置控制器ip地址(依赖注入)
     * @param ip 输入，控制器ip
     */
    virtual void SetControllerIp(const std::string &ip) = 0;
    /**
     * @brief 设置当前加载的工程名称(依赖注入)
     * @param name 输入，工程名称
     */
    virtual void SetProjectName(const std::string &name) = 0;
    /**
     * @brief  默认文件名称
     */
    virtual std::string DefaultFileName() = 0;

    /**
     * @brief  是否被修改过
     */
    virtual bool isModified() = 0;
    /**
     * @brief 设置修改状态
     * @param state 输入，修改状态
     */
    virtual void setModifyState(bool state) = 0;

    /**
     * @brief 从文件中读取工位配置信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int readStationReserveCfgFile() = 0;
    /**
     * @brief 将工位配置信息保存到文件中
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveStationReserveCfgFile() = 0;
    /**
     * @brief 设置工位配置信息
     * @param stationCfg 输入 工位配置信息
     * @return 成功返回0，其他请见错误码
     */
    virtual int setStationReserveCfg(const StationReserveCfg &stationCfg) = 0;
    /**
     * @brief 读取工位配置信息
     * @return 工位配置信息
     */
    virtual StationReserveCfg getStationReserveCfg() = 0;
    /**
     * @brief 设置工位配置信息
     * @param index 输入 工位序号
     * @param programName 输入 程序名称
     * @return 成功返回0，其他请见错误码
     */
    virtual int setRISPProgNameByIndex(int index, const string &programName) = 0;
    /**
     * @brief 读取工位配置信息
     * @param index 输入 工位序号
     * @param programName 输出 对应工位的程序名称
     * @return 成功返回0，其他请见错误码
     */
    virtual int getRISPProgNameByIndex(int index, string &programName) = 0;
    /**
     * @brief 设置远程IO启动程序下工位的程序分配信息
     * @param arrStationProgramName 输入 远程IO启动程序下工位的程序分配信息
     */
    virtual void setRISPProgName(const std::array<std::string, STATIONRESERVE_RISP_NUM> &arrStationProgramName) = 0;
    /**
     * @brief 读取远程IO启动程序下工位的程序分配信息
     * @param arrStationProgramName 输出 远程IO启动程序下工位的程序分配信息
     */
    virtual void getRISPProgName(std::array<std::string, STATIONRESERVE_RISP_NUM> &arrStationProgramName) = 0;
    /**
     * @brief 设置工位配置信息
     * @param mode 输入 工位预约模式0：禁用，1：远程IO启动程序
     * @param programName 输入 程序名称
     * @return 成功返回0，其他请见错误码
     */
    virtual int setStationReserveMode(int mode) = 0;
    /**
     * @brief 读取工位配置信息
     * @return 工位预约模式0：禁用，1：远程IO启动程序
     */
    virtual int getStationReserveMode() = 0;
    /**
     * @brief 重置工位
     * @param flag 输入 0:重置i32Stationindex对应的工位，1：清除预约队列，2：重置所有工位
     * @param i32Stationindex 输入 工位索引
     * @return 成功返回0，其他请见错误码
     */
    virtual int resetStationState(int flag, int i32Stationindex) = 0;
    /**
     * @brief 获取工位状态
     * @param stationState 输出 工位状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int readStationStates(uint32_t stationState[STATIONRESERVE_RISP_NUM]) = 0;
};
} // namespace InoRobBusiness
