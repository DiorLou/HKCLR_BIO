#pragma once

#include "IIRLink.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS IRLinkDefault : public IIRLink
{
public:
    IRLinkDefault(IDataSrvBase *pDataSrv, IConnection *pConnection, IMonitor *pMonitor, IRobotArm *pRobotArm);
    virtual ~IRLinkDefault();

    bool readTotalModuleNum(short &num) override;
    bool writeTotalModuleNum(const short num) override;
    bool readRtuModuleNum(IRLinkRtuModuleNum &rtuModuleNum) override;
    bool writeRtuModuleNum(const IRLinkRtuModuleNum &rtuModuleNum) override;
    bool readAllModuleConfig(IRLink_All_Module_Config &ioConfig) override;
    int readModuleParam(const short moduleId, const short IONum, const short IOId, IRLink_IO_Param &ioParam) override;
    int writeModuleParam(const short moduleId, const short IONum, const short IOId, const IRLink_IO_Param &ioParam) override;
    bool addRTU(const int index) override;
    bool deleteRTU(const int index) override;
    bool addModule(const int rtuIndex, const int moduleIndex, const IRLink_Module_Type ModuleType) override;
    bool deleteModule(const int rtuIndex, const int moduleIndex) override;
    bool set4DAParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) override;
    bool set4ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) override;
    bool set8ADParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) override;
    bool set2ENCParam(const int rtuIndex, const int moduleIndex, const int ioIndex, const IRLink_IO_Param &ioParam) override;
    bool saveIRLink() override;
    bool updateAllModuleInfos() override;
    std::vector<std::vector<IRLinkModuleInfo>> getAllModuleInfos() const override;

private:
    IDataSrvBase *_pDataService = nullptr;
    IConnection *_pConnection = nullptr;
    IMonitor *_pMonitor = nullptr;
    IRobotArm *_pRobotArm = nullptr;


    std::vector<std::vector<IRLinkModuleInfo>> _IRLinkInfos;

    /**
     * @brief 判断当前RTU是否是系统固定RTU
     *        小多传、20kg的第1个RTU是系统固定的
     * @param 当前RTU下标
     * @return true是 false不是
     */
    bool isSysFixRTU(const int rtuIndex) const;

    /**
     * @brief 判断当前RTU是否功率过载
     * @param rtuIndex 当前RTU下标
     * @param type 新增模块类型
     * @return true过载 false不过载
     */
    bool isOverPowerOnRTU(const int rtuIndex, const IRLink_Module_Type type) const;

    /**
     * @brief 根据模块类型获取模块功率
     * @param type 模块类型
     * @return 功率
     */
    int getModulePowerOnType(const IRLink_Module_Type type) const;

    /**
     * @brief 判断是否资源超载
     * @param type 新增模块类型
     * @return true超载 false不超载
     */
    bool isOverResource(const IRLink_Module_Type type) const;

    /**
     * @brief 根据模块类型获取通道数
     * @param type 模块类型
     * @param[out] passageDI DI通道数
     * @param[out] passageDO DO通道数
     * @param[out] passageDAC DAC通道数
     * @param[out] passageADC ADC通道数
     * @param[out] passageENC ENC通道数
     */
    void getModulePassageNumOnType(const IRLink_Module_Type type, int &passageDI, int &passageDO, int &passageDAC, int &passageADC, int &passageENC) const;
};
}  // namespace InoRobBusiness
