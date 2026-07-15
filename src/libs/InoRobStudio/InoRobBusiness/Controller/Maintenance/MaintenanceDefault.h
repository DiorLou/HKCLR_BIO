#include "IMaintenance.h"
#include "GlobalDataTypes.h"
#include "IInoRobBusiness.h"
#include "RemainLifeCalculate/IRemainLifeCalculate.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS MaintenanceDefault : public IMaintenance
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService;
    // 连接
    IConnection *_pConnection;
    // 监控
    IMonitor *_pMonitor;
    // 程序运行根目录
    string _appRootPath;

    // 寿命核算
    IRemainLifeCalculate *_pRemainLifeCalculate;

public:
    MaintenanceDefault(const string &appRootPath, string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~MaintenanceDefault();
    void init() override;
#pragma endregion

#pragma region 寿命核算
    // 寿命核算
    IRemainLifeCalculate *getRemainLifeCalculatem();
#pragma endregion

#pragma region 系统诊断

    bool checkControllerUSB();
    int startDiagnose(bool sys, bool logic, bool track);
    int stopDiagnose(bool sys, bool logic, bool track);
    int startExportReport(bool sys, bool logic, bool track, int expType, int expDest = 0);
    int ReadErrExportSta(ErrexportSta &sta);

    /*!
     * \brief 获取诊断的保存状态
     * \param 返回的保存信息结构体
     * \return
     */
    int ReadErrSaveSta(ErrsaveSta &sta);

    /*!
     * \brief 发送诊断命令
     * \param 发送的命令结构体
     * \return 返回的结果 ERR_OK表示发送命令成功
     */
    int SendErrSaveCmd(ErrsaveCmd cmd);

    /*!
     * \brief 发送导出诊断报告命令
     * \param 发送的命令结构体
     * \return 返回的结果 ERR_OK表示发送命令成功
     */
    int SendErrExportCmd(ErrexportCmd cmd);

    /*!
     * \brief 获取诊断状态
     * \return 诊断状态  -1-保存失败  0-null 1-保存中  2-保存成功  3-保存终止
     */
    int getDiagnoseState();

    /*!
     * \brief 获取导出状态
     * \return 导出状态  -1-导出失败 0-null 1-导出中  2-导出成功
     */
    int getExportState();

#pragma endregion

#pragma region 平衡缸弹簧维保

public:
    // 获取平衡缸弹簧维保数据
    bool getBalCylinderSpringData(BalCylinderSpringData &balCylinderSpringData);
    // 平衡缸弹簧维保
    bool setBalCylinderSpring(const BalCylinderSpringParaSet &balCylinderSpringParaSet);

    // 读取平衡缸弹簧阈值与属性
    bool getBalCylinderSpringPara(BalCylinderSpringPara &balCylinderSpringPara);
    // 设置平衡缸弹簧阈值与属性
    bool setBalCylinderSpringPara(const BalCylinderSpringPara &balCylinderSpringPara);

#pragma endregion

#pragma region 其它组件维保

public:
    // 目录名
    static const string MaintenanceDirName;

    // 获取指定组件的维保信息（返回网络通信返回值）
    int getMaintenanceDataRaw(MaintenanceModule maintenanceModule, MaintenanceData &maintenanceData);
    // 获取指定组件的维保信息
    bool getMaintenanceData(MaintenanceModule maintenanceModule, MaintenanceData &maintenanceData);
    // 设置维保时间
    bool setMaintenanceTime(MaintenanceModule maintenanceModule, UINT8 axis, MaintenanceTime maintenanceTime);
    // 设置维保阈值
    bool setMaintenanceThreshold(MaintenanceModule maintenanceModule, UINT8 axis, double threshold);
    // 清空所有维保数据
    bool maintenanceDataClear();
    // 备份维保数据
    bool maintenanceDataBackup(const string &filePath);
    // 还原维保数据
    bool maintenanceDataRestore(const string &filePath);
    // 备份维保数据TP软件使用
    bool maintenanceDataTPBackup();
    // 还原维保数据TP软件使用
    bool maintenanceDataTPRestore();

#pragma endregion

private:
    // 打包获取实时数据
    RCSTS_INFO_0322 rcStsInfo;
};
}  // namespace InoRobBusiness
