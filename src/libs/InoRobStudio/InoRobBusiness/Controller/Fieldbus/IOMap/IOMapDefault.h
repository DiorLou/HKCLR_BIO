#pragma once
#include <vector>
#include "IIOMap.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class IOMapDefault : public IIOMap
{
    Q_OBJECT

public:
    IOMapDefault(IDataSrvBase *dataService, IMonitor *monitor, IRobotArm *pRobotArm);
    ~IOMapDefault();

    bool readFieldbusIOMapCurCount(int &ioMapCount) override;
    bool readFieldbusIOMap(FieldbusIOMapInfo &info) override;
    bool writeFieldbusIOMap(const FieldbusIOMapInfo &info) override;
    bool allowSaveFieldbusIOMap() override;
    bool saveFieldbusIOMap(const std::vector<FieldbusIOMapData> &datas) override;
    bool refreshFieldbusIOMap() override;
    std::vector<FieldbusIOMapData> getFieldbusIOMapDatas() const override;
    int getMemAddrByFuncId(unsigned int funcId) const override;
    bool resetFieldbusIOMap(const IOMapResetMethod method) override;
    bool exportFieldbusIOMapToFile(const std::string &fullFileName) override;
    bool importFieldbusIoMapFromFile(const std::string &fullFileName) override;

private:
    IDataSrvBase *_pDataSrvBase = nullptr;
    IMonitor *_pMonitor = nullptr;
    IRobotArm *_pRobotArm = nullptr;

    std::vector<FieldbusIOMapData> _datas;         // IO映射展示数据列表
    std::map<unsigned short, int> _digitalIOMap;   // 标准IO映射Map
    std::map<unsigned short, int> _fieldbusIOMap;  // 从站IO映射Map

    // 初始化数据
    void initDatas();
    // 初始化输入Bit数据
    void initInputBitDatas();
    // 初始化输入Word数据
    void initInputWordDatas();
    // 初始化输出Bit数据
    void initOutputBitDatas();
    // 初始化输出Word数据
    void initOutputWordDatas();

    // 初始化标准IO映射Map
    void initDigitalIOMap();
    // 初始化从站IO映射Map
    void initFieldbusIOMap();

    /**
     * @brief 导出文件
     * @param fullFileName 文件名称（包含完整路径）
     * @param[in] dataStr 文件内容
     * @return true成功 false失败
     */
    bool exportFile(const std::string &fullFileName, const std::string &dataStr);

    /**
     * @brief 导入文件
     * @param fullFileName 文件名称（包含完整路径）
     * @param[out] dataStr 文件内容（除文件title）
     * @return true成功 false失败
     */
    bool importFile(const std::string &fullFileName, std::string &dataStr);
    /**
     * @brief 切换语言时重新翻译
     * @param languageCode 语言名称
     * @return
     */
    void retranslateIoMappingCache(const std::string &languageCode);
};
}  // namespace InoRobBusiness
