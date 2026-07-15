#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ForceCtrlDefault : public IForceCtrl
{
    Q_OBJECT

public:
    ForceCtrlDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    virtual ~ForceCtrlDefault();
    void init() override;

#pragma region 新力控开关页面

    /// <summary>
    /// 获取传感器参数数据（从文件中获取）
    /// </summary>
    /// <param name="fCSensorParaArr">所有传感器参数</param>
    /// <returns>是否成功</returns>
    bool RefreshFCSensorData(FCSensorParaArr &fCSensorParaArr) override;

    /// <summary>
    /// 从控制获取传感器文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetFCSensorDataFile();

    /// <summary>
    /// 从文件中解析出传感器数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadFCSensorDataFromFile(bool firstCall);

    /// <summary>
    /// 保存指定传感器参数编号的数据
    /// </summary>
    /// <param name="i16SensorNo">传感器参数编号</param>
    /// <param name="u8ForceCtrlswitchFlag">力控开关是否打开</param>
    /// <param name="fCSensorPara">传感器参数</param>
    /// <returns>是否成功</returns>
    bool SaveFCSensorItem(int16s i16SensorNo, int8u u8ForceCtrlswitchFlag, ForceCtrlSensorPara *fCSensorPara) override;

    /// <summary>
    /// 写传感器参数数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteFCSensorDataToFile();

    /// <summary>
    /// 放置传感器参数文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutFCSensorDataFile();

    /// <summary>
    /// 通知ARM更新传感器参数数据
    /// </summary>
    /// <param name="i16SensorNo">更新的是哪组传感器编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool WriteFCSensorData(int16s i16SensorNo) override;

    /// <summary>
    /// 获取当前的传感器参数
    /// </summary>
    /// <returns></returns>
    FCSensorParaArr GetCurrentSensorData() override;

#pragma endregion

#pragma region 力传感器设置及标定

    /// <summary>
    /// 获取力控标定数据（从文件中获取）
    /// </summary>
    /// <param name="forceCtrlCalibData">力控标定所有数据</param>
    /// <returns>是否成功</returns>
    bool RefreshCalibData(ForceCtrlCalibData &forceCtrlCalibData) override;

    /// <summary>
    /// 从控制获取标定文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetCalibDataFile();

    /// <summary>
    /// 从文件中解析出标定数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadCalibDataFromFile(bool firstCall);

    /// <summary>
    /// 保存指定力控参数编号的力控标定数据
    /// </summary>
    /// <param name="i16ParaIndex">力控参数编号</param>
    /// <param name="result">标定中间点</param>
    /// <returns>是否成功</returns>
    bool SaveCalibItems(int16s i16ParaIndex, ForceCtrlCalibItem *result) override;

    /// <summary>
    /// 写力控标定数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteCalibDataToFile();

    /// <summary>
    /// 放置标定文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutCalibDataFile();

    /// <summary>
    /// 通知ARM更新力控标定结果数据
    /// </summary>
    /// <param name="i16ParaIndex">更新的是哪组标定数据</param>
    /// <returns>成功返回true，其他为失败</returns>
    bool WriteForceCtrlCalibData(int16s i16ParaIndex) override;

    /// <summary>
    /// 读取力控当前力数据
    /// </summary>
    /// <param name="i16SensorNo">传感器编号</param>
    /// <param name="forceValueArray">力数据</param>
    /// <returns>成功返回true，其他为失败</returns>
    bool ReadForceCtrlForceValue(int16s i16SensorNo, float *forceValueArray) override;

    /// <summary>
    /// 力控标定计算
    /// </summary>
    /// <param name="calibItem">标定数据</param>
    /// <param name="calibResult">标定结果</param>
    /// <returns>是否成功</returns>
    bool ForceCtrlCalibrateCalc(ForceCtrlCalibItem &calibItem) override;

    /// <summary>
    /// 保存力控标定结果
    /// </summary>
    /// <param name="i16ParaIndex">力控参数编号</param>
    /// <param name="result">标定结果</param>
    /// <returns>是否成功</returns>
    bool SaveCalibResult(int16s i16ParaIndex, ForceCtrlCalibResult result) override;

#pragma endregion

#pragma region 力控坐标系

    /// <summary>
    /// 获取力控坐标系参数数据（从文件中获取）
    /// </summary>
    /// <returns>是否成功</returns>
    bool RefreshFCCoordinateData();

    /// <summary>
    /// 从控制获取力控坐标系文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetFCCoordinateDataFile();

    /// <summary>
    /// 从文件中解析出力控坐标系数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadFCCoordinateDataFromFile(bool firstCall);

    /// <summary>
    /// 保存指定参数编号的力控坐标系数据
    /// </summary>
    /// <param name="i16SensorNo">参数编号</param>
    /// <param name="fCCoordinateParaArr">传感器参数</param>
    /// <returns>是否成功</returns>
    bool SaveFCCoordinateItem(int16s i16ParaIndex, FCCoordinatePara &fCCoordinatePara) override;

    /// <summary>
    /// 写力控坐标系数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteFCCoordinateDataToFile();

    /// <summary>
    /// 放置力控坐标系文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutFCCoordinateDataFile();

    /// <summary>
    /// 通知ARM更新力控坐标系数据
    /// </summary>
    /// <param name="i16SensorNo">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool WriteFCCoordinateData(int16s i16ParaIndex) override;

    /// <summary>
    /// 读取某一组力控坐标系数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <param name="fCCoordinatePara">返回的数据</param>
    /// <returns>成功返回0，其他为失败</returns>
    int ReadFCCoordinateData(int16s i16ParaIndex, FCCoordinatePara &fCCoordinatePara) override;

#pragma endregion

#pragma region 力控配置参数

    /// <summary>
    /// 通知ARM更新力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool WriteFCConfigParam(int16s i16ParaIndex) override;

    /// <summary>
    /// 获取力控配置参数数据（从文件中获取）
    /// </summary>
    /// <param name="fCCoordinateParaArr">所有力控坐标系参数</param>
    /// <returns>是否成功</returns>
    bool RefreshFCConfigParam();

    /// <summary>
    /// 从控制获取力控配置参数文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetFCConfigParamFile();

    /// <summary>
    /// 从文件中解析出力控配置参数数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadFCConfigParamFromFile(bool firstCall);

    /// <summary>
    /// 放置力控配置参数文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutFCConfigParamFile();

    /// <summary>
    /// 写力控配置参数数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteFCConfigParamToFile();

    /// <summary>
    /// 保存力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    bool SaveForceCtrlConfigParam(int16s i16ParaIndex, ForceCtrlConfigPara &param) override;

    /// <summary>
    /// 读取力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    bool ReadForceCtrlConfigParam(int16s i16ParaIndex, ForceCtrlConfigPara &param) override;

#pragma endregion

#pragma region 力控控制参数

    /// <summary>
    /// 通知ARM更新力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool WriteFCControlParam(int16s i16ParaIndex) override;

    /// <summary>
    /// 获取力控控制参数数据（从文件中获取）
    /// </summary>
    /// <param name="fCCoordinateParaArr">所有力控坐标系参数</param>
    /// <returns>是否成功</returns>
    bool RefreshFCControlParam();

    /// <summary>
    /// 从控制获取力控控制参数文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetFCControlParamFile();

    /// <summary>
    /// 从文件中解析出力控控制参数数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadFCControlParamFromFile(bool firstCall);

    /// <summary>
    /// 放置力控控制参数文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutFCControlParammFile();

    /// <summary>
    /// 写力控控制参数数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteFCControlParamToFile();

    /// <summary>
    /// 保存力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    bool SaveForceCtrlMoveParam(int16s i16ParaIndex, ForceCtrlMovePara &param) override;

    /// <summary>
    /// 读取力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    bool ReadForceCtrlMoveParam(int16s i16ParaIndex, ForceCtrlMovePara &param) override;

#pragma endregion

#pragma region 力控限制参数

    /// <summary>
    /// 获取力控限制参数数据（从文件中获取）
    /// </summary>
    /// <param name="fCLimitPara">力控限制参数</param>
    /// <returns>是否成功</returns>
    bool RefreshFCLimitPara();

    /// <summary>
    /// 从控制获取力控限制参数文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool GetFCLimitParaFile();

    /// <summary>
    /// 从文件中解析出力控限制数据
    /// </summary>
    /// <returns>是否成功</returns>
    bool ReadFCLimitDataFromFile(bool firstCall);

    /// <summary>
    /// 保存力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <param name="fCLimitPara">力控限制参数</param>
    /// <returns>是否成功</returns>
    bool SaveFCLimitPara(int16s i16ParaIndex, ForceCtrlLimitPara &fCLimitPara) override;

    /// <summary>
    /// 写力控限制参数数据到文件
    /// </summary>
    /// <returns>是否成功</returns>
    bool WriteFCLimitDataToFile();

    /// <summary>
    /// 放置力控限制参数文件到控制器
    /// </summary>
    /// <returns>是否成功</returns>
    bool PutFCLimitDataFile();

    /// <summary>
    /// 通知ARM更新力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool WriteFCLimitData(int16s i16ParaIndex) override;

    /// <summary>
    /// 读取力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <param name="fCLimitPara">返回的数据</param>
    /// <returns>成功返回0，其他为失败</returns>
    bool ReadFCLimitData(int16s i16ParaIndex, ForceCtrlLimitPara &fCLimitPara) override;

#pragma endregion

#pragma region 日志

    /// <summary>
    /// 执行导出控制器中日志
    /// </summary>
    /// <param name="fileName">日志名称</param>
    /// <param name="localPath">本地路径(包含文件名称)</param>
    /// <returns>成功返回0，其他为失败</returns>
    int ExportLogFromCtrl(const std::string &fileName, const std::string &localPath);


    /// <summary>
    /// 执行批量导出控制器中日志
    /// </summary>
    /// <param name="fileName">日志名称列表</param>
    /// <param name="localPath">本地路径列表</param>
    /// <returns>成功返回0，其他为失败</returns>
    int ExportLogsFromCtrl(const std::vector<std::string> &filesName, const std::vector<std::string> &localPaths);


    /**
     * @brief 获取力控路径下的文件列表（支持过滤）
     * @param filePath 入参：力控路径（如果为空，使用默认路径）
     * @param fileList 出参：力控日志文件名列表
     * @param filterType 入参：过滤类型 0-所有文件，1-仅CSV文件，2-按时间过滤等
     * @param filterParam 入参：过滤参数（如时间范围、文件大小等）
     * @return 成功返回0，其他为失败
     */
    int GetForceCtrlLogListEx(const std::string &filePath,std::vector<std::string> &fileList,int filterType = 1,const std::string &filterParam = "");

    /// <summary>
    /// 响应导出力控日志
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    void OnExportLogFromCtrl(int value);

    /// <summary>
    /// 获取日志导出的本地路径
    /// </summary>
    /// <param name="dir">本地文件夹路径</param>
    /// <param name="name">文件名称</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadLogPath(std::string &dir, std::string &name);

#pragma endregion
#pragma region 力控日志格式

    /// <summary>
    /// 设置力控功能日志的自定义数据格式
    /// </summary>
    /// <param name="logFormat">输入，自定义数据格式</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteForceCtrlLogFormat(const ForceCtrlLogFormat &logFormat);

    /// <summary>
    /// 读取力控功能日志的自定义数据格式
    /// </summary>
    /// <param name="logFormat">输出，自定义数据格式</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlLogFormat(ForceCtrlLogFormat &logFormat);
#pragma endregion

#pragma region 力控监控

    /// <summary>
    /// 设置力控监控开关
    /// </summary>
    /// <param name="state">1：开启，2：关闭</param>
    /// <param name="coord">0：传感器坐标系，1：力觉坐标系</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteForceCtrlMonitorSwitch(int8u state, int8u coord);

    /// <summary>
    /// 获取力控监控开关状态
    /// </summary>
    /// <param name="state">1：开启，2：关闭</param>
    /// <param name="coord">0：传感器坐标系，1：力觉坐标系</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlMonitorSwitch(int8u &state, int8u &coord);

    /// <summary>
    /// 获取力控反馈数据集合
    /// </summary>
    /// <param name="dataNum">当前获取到的数据个数</param>
    /// <param name="overDataNum">控制器缓存着的剩余个数</param>
    /// <param name="dataArr">当前获取到的数据集合</param>
    /// <param name="stepIdArr">当前获取到的StepId集合</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlMonitorData(int &dataNum, int &overDataNum, std::vector<ForceCtrlData> &dataArr,
                                         std::vector<int> &stepIdArr);

    /// <summary>
    /// 清除力控功能中传感器的残余应力（清零）
    /// </summary>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteClearSensorForce();

    /// <summary>
    /// 设置力觉坐标系参数
    /// </summary>
    /// <param name="i16CoordIndex">力控坐标系编号(0~15)</param>
    /// <param name="i16ParaIndex">力传感器参数编号(0~15)</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteForceCtrlCoordinateSetting(int16s i16CoordIndex, int16s i16ParaIndex);

    /// <summary>
    /// 读取力觉坐标系参数
    /// </summary>
    /// <param name="i16CoordIndex">力控坐标系编号(0~15)</param>
    /// <param name="i16ParaIndex">力传感器参数编号(0~15)</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlCoordinateSetting(int16s &i16CoordIndex, int16s &i16ParaIndex);
#pragma endregion
    

    // 检查是否连接
    bool CheckIsConnect();

    // FTP捞文件 远程目录：/robotUserParameter，本地目录./tmp
    bool GetFCDataFile(std::string localFileName, std::string remoteFileName);

    // 写文件 本地目录./tmp
    bool WriteFCDataToFile(std::string tmpLocalFileName, std::string localFileName, ForceCtrlFileType type);

    // FTP传文件
    bool PutFCDataFile(std::string localFileName, std::string tmpLocalFileName);

private:
    IDataSrvBase *_pDataSrv = nullptr;
    IConnection *_pConnection = nullptr;
    IMonitor *_pMonitor = nullptr;
    IControl *_pControl = nullptr;
    IRobotControllerEvents *_pRobotEvents = nullptr;

    // 力控日志文件在控制器中的文件夹名称
    static std::string _logFileCtrlFolder;
    static std::string _logFileCtrlFolder1;

    // 所有力控标定数据
    ForceCtrlCalibData *_forceCtrlCalibData = nullptr;
    static std::string _localFilePath;
    static std::string _remoteFilePath;
    static std::string _calibFileName;
    static std::string _tmpCalibFileName;

    // 所有传感器参数
    FCSensorParaArr *_fCSensorParaArr = nullptr;
    static std::string _sensorCfgFileName;
    static std::string _tmpSensorCfgFileName;
    bool _isInitFCSensor = false;  // 是否初始化

    // 所有力控坐标系参数
    FCCoordinateParaArr *_fCCoordinateParaArr = nullptr;
    static std::string _fcCoordinateFileName;
    static std::string _tmpFCCoordinateFileName;
    bool _isInitFCCoordinate = false;  // 是否初始化

    // 力控配置参数
    ForceCtrlConfigParaArr *_fCConfigParaArr = nullptr;
    static std::string _fCConfigFileName;
    static std::string _tmpFCConfigFileName;
    bool _isInitFCConfig = false;  // 是否初始化

    // 力控控制参数
    ForceCtrlMoveParaArr *_fCMoveParaArr = nullptr;
    static std::string _fCControlFileName;
    static std::string _tmpFCControlFileName;
    bool _isInitFCControl = false;  // 是否初始化

    ForceCtrlLimitParaArr *_fCLimitParaArr = nullptr;
    static std::string _fCLimitFileName;
    static std::string _tmpFCLimitFileName;
    bool _isInitFCLimit = false;  // 是否初始化
};
}  // namespace InoRobBusiness
