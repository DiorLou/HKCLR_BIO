#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include <list>
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"

namespace InoRobBusiness
{

#pragma region 枚举
// 文件类型
enum ForceCtrlFileType : int16s
{
    FCCalibType,       // 标定文件
    FCSensorType,      // 传感器参数文件
    FCCoordinateType,  // 力控坐标系文件
    FCConfigType,      // 力控配置参数文件
    FCControlType,     // 力控控制参数文件
    FCLimitType        // 力控限制参数文件
};
#pragma endregion

class INOROBBUSINESS_CLASS IForceCtrl : public QObject
{
    Q_OBJECT

public:
    virtual ~IForceCtrl()
    {
    }

    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

#pragma region 新力控开关页面
    /// <summary>
    /// 获取传感器参数数据（从文件中获取）
    /// </summary>
    /// <param name="fCSensorParaArr">所有传感器参数</param>
    /// <returns>是否成功</returns>
    virtual bool RefreshFCSensorData(FCSensorParaArr &fCSensorParaArr) = 0;

    /// <summary>
    /// 保存指定传感器参数编号的数据
    /// </summary>
    /// <param name="i16SensorNo">传感器参数编号</param>
    /// <param name="u8ForceCtrlswitchFlag">力控开关是否打开</param>
    /// <param name="fCSensorPara">传感器参数</param>
    /// <returns>是否成功</returns>
    virtual bool SaveFCSensorItem(int16s i16SensorNo, int8u u8ForceCtrlswitchFlag, ForceCtrlSensorPara *fCSensorPara) = 0;

    /// <summary>
    /// 通知ARM更新传感器参数数据
    /// </summary>
    /// <param name="i16SensorNo">更新的是哪组传感器编号</param>
    /// <returns>成功true</returns>
    virtual bool WriteFCSensorData(int16s i16SensorNo) = 0;

    /// <summary>
    /// 获取当前的传感器参数
    /// </summary>
    /// <returns></returns>
    virtual FCSensorParaArr GetCurrentSensorData() = 0;

#pragma endregion

#pragma region 力传感器设置及标定

    /// <summary>
    /// 获取力控标定数据（从文件中获取）
    /// </summary>
    /// <param name="forceCtrlCalibData">力控标定所有数据</param>
    /// <returns>是否成功</returns>
    virtual bool RefreshCalibData(ForceCtrlCalibData &forceCtrlCalibData) = 0;

    /// <summary>
    /// 保存指定力控参数编号的力控标定数据
    /// </summary>
    /// <param name="i16ParaIndex">力控参数编号</param>
    /// <param name="result">标定中间点</param>
    /// <returns>是否成功</returns>
    virtual bool SaveCalibItems(int16s i16ParaIndex, ForceCtrlCalibItem *result) = 0;

    /// <summary>
    /// 通知ARM更新力控标定结果数据
    /// </summary>
    /// <param name="i16ParaIndex">更新的是哪组标定数据</param>
    /// <returns>成功返回true，其他为失败</returns>
    virtual bool WriteForceCtrlCalibData(int16s i16ParaIndex) = 0;

    /// <summary>
    /// 读取力控当前力数据
    /// </summary>
    /// <param name="i16SensorNo">传感器编号</param>
    /// <param name="forceValueArray">力数据</param>
    /// <returns>成功返回true，其他为失败</returns>
    virtual bool ReadForceCtrlForceValue(int16s i16SensorNo, float *forceValueArray) = 0;

    /// <summary>
    /// 力控标定计算
    /// </summary>
    /// <param name="calibItem">标定数据</param>
    /// <param name="calibResult">标定结果</param>
    /// <returns>是否成功</returns>
    virtual bool ForceCtrlCalibrateCalc(ForceCtrlCalibItem &calibItem) = 0;

    /// <summary>
    /// 保存力控标定结果
    /// </summary>
    /// <param name="i16ParaIndex">力控参数编号</param>
    /// <param name="result">标定结果</param>
    /// <returns>是否成功</returns>
    virtual bool SaveCalibResult(int16s i16ParaIndex, ForceCtrlCalibResult result) = 0;

#pragma endregion

#pragma region 力控坐标系

    /// <summary>
    /// 保存指定参数编号的力控坐标系数据
    /// </summary>
    /// <param name="i16SensorNo">参数编号</param>
    /// <param name="fCCoordinateParaArr">传感器参数</param>
    /// <returns>是否成功</returns>
    virtual bool SaveFCCoordinateItem(int16s i16ParaIndex, FCCoordinatePara &fCCoordinatePara) = 0;

    /// <summary>
    /// 通知ARM更新力控坐标系数据
    /// </summary>
    /// <param name="i16SensorNo">参数编号</param>
    /// <returns>成功返回true</returns>
    virtual bool WriteFCCoordinateData(int16s i16ParaIndex) = 0;

    /// <summary>
    /// 读取某一组力控坐标系数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <param name="fCCoordinatePara">返回的数据</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadFCCoordinateData(int16s i16ParaIndex, FCCoordinatePara &fCCoordinatePara) = 0;

#pragma endregion

#pragma region 力控配置参数

    /// <summary>
    /// 通知ARM更新力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回true，其他为失败</returns>
    virtual bool WriteFCConfigParam(int16s i16ParaIndex) = 0;

    /// <summary>
    /// 保存力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    virtual bool SaveForceCtrlConfigParam(int16s i16ParaIndex, ForceCtrlConfigPara &param) = 0;

    /// <summary>
    /// 读取力控配置参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    virtual bool ReadForceCtrlConfigParam(int16s i16ParaIndex, ForceCtrlConfigPara &param) = 0;

#pragma endregion

#pragma region 力控控制参数

    /// <summary>
    /// 通知ARM更新力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual bool WriteFCControlParam(int16s i16ParaIndex) = 0;

    /// <summary>
    /// 保存力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    virtual bool SaveForceCtrlMoveParam(int16s i16ParaIndex, ForceCtrlMovePara &param) = 0;

    /// <summary>
    /// 读取力控控制参数
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="param">数据</param>
    /// <returns></returns>
    virtual bool ReadForceCtrlMoveParam(int16s i16ParaIndex, ForceCtrlMovePara &param) = 0;

#pragma endregion

#pragma region 力控限制参数

    /// <summary>
    /// 保存力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数序号</param>
    /// <param name="fCLimitPara">力控限制参数</param>
    /// <returns>是否成功</returns>
    virtual bool SaveFCLimitPara(int16s i16ParaIndex, ForceCtrlLimitPara &fCLimitPara) = 0;

    /// <summary>
    /// 通知ARM更新力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual bool WriteFCLimitData(int16s i16ParaIndex) = 0;

    /// <summary>
    /// 读取力控限制参数数据
    /// </summary>
    /// <param name="i16ParaIndex">参数编号</param>
    /// <param name="fCLimitPara">返回的数据</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual bool ReadFCLimitData(int16s i16ParaIndex, ForceCtrlLimitPara &fCLimitPara) = 0;

#pragma endregion


#pragma region 日志

    /// <summary>
    /// 执行导出控制器中日志
    /// </summary>
    /// <param name="fileName">日志名称</param>
    /// <param name="localPath">本地路径(包含文件名称)</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ExportLogFromCtrl(const std::string &fileName, const std::string &localPath) = 0;


    /// <summary>
    /// 执行批量导出控制器中日志
    /// </summary>
    /// <param name="fileName">日志名称列表</param>
    /// <param name="localPath">本地路径列表</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ExportLogsFromCtrl(const std::vector<std::string> &filesName, const std::vector<std::string> &localPaths) = 0;

    /// <summary>
    ///  获取得到力控路径下的全部文件(csv格式)
    /// </summary>
    /// <param name="filePath">入参 ：力控路径</param>
    /// <param name="localPath">出参：力控日志文件名列表</param>
    /// <returns>成功返回0，其他为失败</returns>

    virtual int   GetForceCtrlLogListEx(const std::string &filePath,  std::vector<std::string> &fileList, int filterType = 1,const std::string &filterParam = "") = 0;

#pragma endregion

#pragma region 力控日志格式

  /// <summary>
  /// 设置力控功能日志的自定义数据格式
  /// </summary>
  /// <param name="logFormat">输入，自定义数据格式</param>
  /// <returns>成功返回0，其他为失败</returns>
  virtual int WriteForceCtrlLogFormat(const ForceCtrlLogFormat &logFormat) = 0;

  /// <summary>
  /// 读取力控功能日志的自定义数据格式
  /// </summary>
  /// <param name="logFormat">输出，自定义数据格式</param>
  /// <returns>成功返回0，其他为失败</returns>
  virtual int ReadForceCtrlLogFormat(ForceCtrlLogFormat &logFormat) = 0;
#pragma endregion

#pragma region 力控监控

    /// <summary>
    /// 设置力控监控开关
    /// </summary>
    /// <param name="state">1：开启，2：关闭</param>
    /// <param name="coord">0：传感器坐标系，1：力觉坐标系</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteForceCtrlMonitorSwitch(int8u state, int8u coord) = 0;

    /// <summary>
    /// 获取力控监控开关状态
    /// </summary>
    /// <param name="state">1：开启，2：关闭</param>
    /// <param name="coord">0：传感器坐标系，1：力觉坐标系</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlMonitorSwitch(int8u &state, int8u &coord) = 0;

    /// <summary>
    /// 获取力控反馈数据集合
    /// </summary>
    /// <param name="dataNum">当前获取到的数据个数</param>
    /// <param name="overDataNum">控制器缓存着的剩余个数</param>
    /// <param name="dataArr">当前获取到的数据集合</param>
    /// <param name="stepIdArr">当前获取到的StepId集合</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlMonitorData(int &dataNum, int &overDataNum, std::vector<ForceCtrlData> &dataArr,
                                         std::vector<int> &stepIdArr) = 0;

    /// <summary>
    /// 清除力控功能中传感器的残余应力（清零）
    /// </summary>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteClearSensorForce() = 0;

    /// <summary>
    /// 设置力觉坐标系参数
    /// </summary>
    /// <param name="i16CoordIndex">力控坐标系编号(0~15)</param>
    /// <param name="i16ParaIndex">力传感器参数编号(0~15)</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int WriteForceCtrlCoordinateSetting(int16s i16CoordIndex, int16s i16ParaIndex) = 0;

    /// <summary>
    /// 读取力觉坐标系参数
    /// </summary>
    /// <param name="i16CoordIndex">力控坐标系编号(0~15)</param>
    /// <param name="i16ParaIndex">力传感器参数编号(0~15)</param>
    /// <returns>成功返回0，其他为失败</returns>
    virtual int ReadForceCtrlCoordinateSetting(int16s &i16CoordIndex, int16s &i16ParaIndex) = 0;


#pragma endregion
};

}  // namespace InoRobBusiness
