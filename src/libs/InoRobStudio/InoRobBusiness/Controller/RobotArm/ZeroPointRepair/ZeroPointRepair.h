#pragma once
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ZeroPointRepair : public IZeroPointRepair
{
    Q_OBJECT

public:
    // 构造与析构
    ZeroPointRepair(IDataSrvBase *dataService, IMonitor *pMonitor, IRobotArm *pRobotArm);
    ~ZeroPointRepair();

public:
    /// <summary>
    /// 标定方法名称查询
    /// </summary>
    /// <param name="method">标定方法枚举</param>
    /// <returns>标定方法名称</returns>
    string CalibMethodNameSearch(ZeroPointRepairCalibMethod method);

    /// <summary>
    /// 获取零点修复标定数据（从文件中获取）
    /// </summary>
    /// <param name="zeroPointRepairCalibData">零点修复标定所有数据</param>
    /// <returns>是否成功</returns>
    bool RefreshCalibData(ZeroPointRepairCalibData &zeroPointRepairCalibData);

    /// <summary>
    /// 从文件中解析出标定数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadCalibDataFromFile();

    /// <summary>
    /// 保存标定数据
    /// </summary>
    /// <param name="result">标定数据</param>
    /// <returns>是否成功</returns>
    bool SaveCalibData(ZeroPointRepairCalibData &result);

    /// <summary>
    /// 写标定数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteCalibDataToFile();

    /// <summary>
    /// 零点修复标定计算
    /// </summary>
    /// <param name="calibItem">标定数据</param>
    /// <param name="calibResult">标定结果</param>
    /// <returns>标定成功返回true</returns>
    bool ZeroPointRepairCalib(ZeroPointRepairCalibItem calibItem, ZeroPointRepairCalibResult &calibResult);

    /// <summary>
    /// 获取零点标定页面是否可见
    /// </summary>
    /// <returns>可见返回true,不可见返回false</returns>
    bool ZeroPointRepairCanVisible();

private:
    IDataSrvBase *_pDataService = nullptr;  // 依赖注入的抽象数据服务对象
    IRobotArm *_pRobotArm = nullptr;        // 依赖注入的抽象机械臂对象
    IMonitor *_pMonitor = nullptr;          // 监控

    ZeroPointRepairCalibMethodItem _calibMethodNameArray[2];  // 标定方法名称数组

    // 本地配置文件路径
    static const string _localCfgPath;

    // 配置远程文件路径
    static const string _remoteCfgPath;

    // 所有标定数据
    ZeroPointRepairCalibData *_pZeroPointRepairCalibData;
    static const string _localFilePath;
    static const string _remoteFilePath;
    static const string _calibFileName;
    static const string _tmpCalibFileName;

    void InitCalibMethod();
};
}  // namespace InoRobBusiness
