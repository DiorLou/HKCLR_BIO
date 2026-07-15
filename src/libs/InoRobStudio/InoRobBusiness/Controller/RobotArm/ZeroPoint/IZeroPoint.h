#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
// 碰撞方式
typedef enum : int
{
    DOWEL_MODE = 0,   // 定位销方式
    SENSOR_MODE = 1,  // 传感器方式
    LIMIT_MODE = 2,   // 限位方式
} ZP_CALIB_COLLISION_MODE;

/*!
 * \brief  零点参数抽象类, 机械臂下的子类
 */
class INOROBBUSINESS_CLASS IZeroPoint : public QObject
{
    Q_OBJECT

public:
    virtual ~IZeroPoint(){};

    /// <summary>
    /// 写入绝对零点
    /// </summary>
    /// <param name="dValue">绝对零点数组</param>
    /// <returns>通讯状态</returns>
    virtual int writeAbsZero(double dValue[AXIS_NUM]) = 0;

    /// <summary>
    /// 读取绝对零点
    /// </summary>
    /// <param name="dValue">绝对零点数组</param>
    /// <returns>通讯状态</returns>
    virtual int readAbsZero(double dValue[AXIS_NUM]) = 0;

    /// <summary>
    /// 读取校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    virtual int readCalibrateMode(int &mode) = 0;

    /// <summary>
    /// 写入校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    virtual int writeCalibrateMode(int mode) = 0;

    /// <summary>
    /// 写入参数重置结构体
    /// </summary>
    /// <param name="resetParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    virtual int writeResetParam(ZeroPointResetParam resetParam) = 0;

    /// <summary>
    /// 读取参数重置结构体
    /// </summary>
    /// <param name="zeroParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    virtual int readResetParam(ZeroPointResetParam &zeroParam) = 0;

    /// <summary>
    /// 读取负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    virtual int readLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX]) = 0;

    /// <summary>
    /// 写入负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    virtual int writeLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX]) = 0;

    /// <summary>
    /// 写入校准命令
    /// </summary>
    /// <param name="opt">校准命令结构体</param>
    /// <returns>通讯状态</returns>
    virtual int writeHomingOpt(ZeroPointCommand opt) = 0;

    /// <summary>
    /// 读取校准状态
    /// </summary>
    /// <param name="res">反馈状态</param>
    /// <returns>通讯状态</returns>
    virtual int readHomingSts(ZeroPointResult &res) = 0;

    /// <summary>
    /// 读取负载号
    /// </summary>
    /// <param name="number">负载号</param>
    /// <returns>通讯状态</returns>
    virtual int readLoadNumber(int &number) = 0;

    /// <summary>
    /// 写入负载号
    /// </summary>
    /// <param name="number">负载号码</param>
    /// <returns>通讯状态</returns>
    virtual int writeLoadNumber(int number) = 0;

    /// <summary>
    /// 通知控制器记录当前位置
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeRecordCurrentPos() = 0;

    /// <summary>
    /// 碰撞工具检查命令
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>通讯状态</returns>
    virtual int writeCollisionToolsCheck(int axisNo[JOINT_AXIS_NUM_SIX]) = 0;

    /// <summary>
    /// 碰撞工具停止命令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int wirteStopCollisionToolsCheck() = 0;

    /// <summary>
    /// 触发开关传感器状态监测
    /// </summary>
    /// <param name="switchParam">开关参数</param>
    /// <returns>通讯状态</returns>
    virtual int writeSwitchSensorStatusCheck(ZeroPointSensorSwitch switchParam) = 0;

    /// <summary>
    /// 是否支持六关节零点校准功能
    /// </summary>
    /// <returns>支持标志</returns>
    virtual bool readIsSupportZeroPointCalibrate() = 0;

    /// <summary>
    /// 执行编码器多圈清理操作
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>通讯状态</returns>
    virtual int writeEncodeMultiCircle(int16s axisNo) = 0;

    /// <summary>
    /// 读取编码器多圈情况
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">多圈清理状态</param>
    /// <returns>通讯状态</returns>
    virtual int readEncodeMultiCircle(int16s axisNo, int &status) = 0;

    /// <summary>
    /// 读取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="zeroFlag">零值标志</param>
    /// <returns>通讯状态</returns>
    virtual int readJposPreIsZero(int8u axisNo) = 0;

    /// <summary>
    /// 读取轴号碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="mode">碰撞方式</param>
    /// <returns>通讯状态</returns>
    virtual int readAxisCollisionMode(int8u axisNo) = 0;

    /// <summary>
    /// 下发零点参数计算模式
    /// </summary>
    /// <param name="mode">计算模式</param>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamCalculateMode(int mode) = 0;

    /// <summary>
    /// 下发零点参数计算指令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamCalculate() = 0;

    /// <summary>
    /// 下发零点参数应用指令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamApply() = 0;

    /// <summary>
    /// 下发零点参数重置指令
    /// </summary>
    /// <returns></returns>
    virtual int writeKBParamReset() = 0;

    /// <summary>
    /// 读取开发者模式零点参数
    /// </summary>
    /// <param name="param">参数结构体</param>
    /// <returns>通讯状态</returns>
    virtual int readKBParam(ZeroPointParamDeveloper &param) = 0;

    /// <summary>
    /// 通知下位机是否处于开发者模式
    /// </summary>
    /// <param name="modeFlag">开发者模式标志</param>
    /// <returns>通讯状态</returns>
    virtual int writeIsDeveloperMode(bool modeFlag) = 0;

    /// <summary>
    /// 读取测试模式
    /// </summary>
    /// <param name="nMode">模式</param>
    /// <returns>通讯状态</returns>
    virtual int readTestMode(int &nMode) = 0;

    /// <summary>
    /// 读取工厂回零操作记录
    /// </summary>
    /// <param name="recordFlag">记录存在标志</param>
    /// <returns>通讯状态</returns>
    virtual int readFactoryHomingRecord(int16s recordFlag[JOINT_AXIS_NUM_SIX]) = 0;

    /// <summary>
    /// 启动
    /// </summary>
    /// <returns>启动成功标志</returns>
    virtual bool start() = 0;

    /// <summary>
    /// 停止
    /// </summary>
    /// <returns>停止成功标志</returns>
    virtual bool stop() = 0;

    /// <summary>
    /// 应用校准值
    /// </summary>
    /// <returns>应用成功标志</returns>
    virtual bool applyValue() = 0;

    /// <summary>
    /// 零点模式开关
    /// </summary>
    /// <returns>处理结果</returns>
    virtual int switchModeToHoming() = 0;

    /// <summary>
    /// 退出
    /// </summary>
    /// <returns>退出准备是否成功</returns>
    virtual bool exit() = 0;

    /// <summary>
    /// 碰撞工具检查
    /// </summary>
    virtual void collisionToolsCheck() = 0;

#pragma endregion

    /// <summary>
    /// 设置轴号选中标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isChecked">选中标志</param>
    virtual void setAxisIsChecked(int axisNo, bool isChecked) = 0;

    /// <summary>
    /// 获取轴号选中状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>选中标志</returns>
    virtual bool getAxisIsChecked(int axisNo) = 0;

    /// <summary>
    /// 刷新信息结构体数据
    /// </summary>
    virtual void refreshParameterStruct() = 0;

    /// <summary>
    /// 设置校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isSuccessed">成功标志</param>
    virtual void setCalibrateIsSuccess(int axisNo, bool isSuccessed) = 0;

    /// <summary>
    /// 获取校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>成功标志</returns>
    virtual bool getCalibrateIsSuccess(int axisNo) = 0;

    /// <summary>
    /// 设置校准线程运行状态
    /// </summary>
    /// <param name="isRunning">运行标志</param>
    virtual void setThreadRunningStatus(bool isRunning) = 0;

    /// <summary>
    /// 获取校准线程运行状态
    /// </summary>
    /// <returns>运行标志</returns>
    virtual bool getThreadRunningStatus() = 0;

    /// <summary>
    /// 设置碰撞工具检查运动状态
    /// </summary>
    /// <param name="isChecking">运动状态</param>
    virtual void setCollisionToolsIsChecking(bool isChecking) = 0;

    /// <summary>
    /// 获取碰撞工具检查运动状态
    /// </summary>
    /// <returns>运动状态</returns>
    virtual bool getCollisionToolsIsChecking() = 0;

    /// <summary>
    /// 设置退出标志
    /// </summary>
    /// <param name="isExit"></param>
    virtual void setExitFlag(bool isExit) = 0;

    /// <summary>
    /// 获取退出标志
    /// </summary>
    /// <returns>退出标志</returns>
    virtual bool getExitFlag() = 0;

    /// <summary>
    /// 初始化数据
    /// </summary>
    virtual void init() = 0;

    /// <summary>
    /// 设置运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    virtual void setStatus(int axisNo, int status) = 0;

    /// <summary>
    /// 获取运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    virtual int getStatus(int axisNo) = 0;

    /// <summary>
    /// 设置零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">数值</param>
    virtual void setCalibrateValue(int axisNo, int value) = 0;

    /// <summary>
    /// 获取零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>数值</returns>
    virtual int getCalibrateValue(int axisNo) = 0;

    /// <summary>
    /// 启动监听线程
    /// </summary>
    virtual void openListenThread() = 0;

    /// <summary>
    /// 切换模式
    /// </summary>
    /// <param name="type">模式</param>
    /// <returns>成功标志</returns>
    virtual bool switchMode(MODE_TYPE type) = 0;

    /// <summary>
    /// 单轴校准
    /// </summary>
    /// <param name="axisNo">轴号</param>
    virtual void singleAxisCalibrate(int axisNo) = 0;

    /// <summary>
    /// 是否选中轴号
    /// </summary>
    /// <returns>选中标志</returns>
    virtual bool axisNoIsSelected() = 0;

    /// <summary>
    /// 是否存在未校准的轴号
    /// </summary>
    /// <param name="nextAxisNo">下一个轴号</param>
    /// <returns>存在标志</returns>
    virtual bool isExistUncalibratedAxis(int &nextAxisNo) = 0;

    /// <summary>
    /// 设置当前校准的轴号
    /// </summary>
    /// <param name="axisNo">轴号</param>
    virtual void setCalibratingAxisNo(int axisNo) = 0;

    /// <summary>
    /// 获取当前校准的轴号
    /// </summary>
    /// <returns>轴号</returns>
    virtual int getCalibratingAxisNo() = 0;

    /// <summary>
    /// 设置运动类型
    /// </summary>
    /// <param name="type">运动类型</param>
    virtual void setMotionType(int type) = 0;

    /// <summary>
    /// 获取运动类型
    /// </summary>
    /// <returns>运动类型</returns>
    virtual int getMotionType() = 0;

    /// <summary>
    /// 设置传感器连接状态
    /// </summary>
    /// <param name="status">连接状态</param>
    virtual void setSensorConnectionStatus(bool status) = 0;

    /// <summary>
    /// 获取传感器连接状态
    /// </summary>
    /// <returns>连接状态</returns>
    virtual bool getSensorConnectionStatus() = 0;

    /// <summary>
    /// 获取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>置零标志</returns>
    virtual bool getJposPreIsZero(int axisNo) = 0;

    /// <summary>
    /// 获取碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>碰撞方式</returns>
    virtual int getCollisionMode(int axisNo) = 0;

    /// <summary>
    /// 获取校准值应用标志
    /// </summary>
    /// <returns>应用标志</returns>
    virtual bool getIsApplied() = 0;

    /// <summary>
    /// 设置校准值应用标志
    /// </summary>
    /// <param name="appliedFlag">应用标志</param>
    virtual void setIsApplied(bool appliedFlag) = 0;

    /// <summary>
    /// 设置UI状态到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    virtual void setUiStatus(int axisNo, int status) = 0;

    /// <summary>
    /// 获取缓存状态到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    virtual int getUiStatus(int axisNo) = 0;

    /// <summary>
    /// 设置UI校准值到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">校准值</param>
    virtual void setUiCaliValue(int axisNo, int value) = 0;

    /// <summary>
    /// 获取缓存校准值到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>校准值</returns>
    virtual int getUiCaliValue(int axisNo) = 0;

    /// <summary>
    /// 设置当前选择的子页面
    /// </summary>
    /// <param name="page"></param>
    virtual void setUiCurrentPage(int page) = 0;

    /// <summary>
    /// 获取上一次停留的子页面
    /// </summary>
    /// <returns></returns>
    virtual int getUiLastPage() = 0;

    /// <summary>
    /// 设置UI选择的校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    virtual void setUiSelectedCalibrateMode(int mode) = 0;

    /// <summary>
    /// 获取UI选择的校准模式
    /// </summary>
    /// <returns>校准模式</returns>
    virtual int getUiSelectedCalibrateMode() = 0;

    /// <summary>
    /// 设置界面负载号
    /// </summary>
    /// <param name="number">负载号</param>
    virtual void setUiLoadNumber(int number) = 0;

    /// <summary>
    /// 获取界面负载号
    /// </summary>
    /// <returns>负载号</returns>
    virtual int getUiLoadNumber() = 0;

    /// <summary>
    /// 设置多圈清理状态
    /// </summary>
    /// <param name="isCleared">是否清多圈</param>
    virtual void setMultiCircleClear(bool isCleared) = 0;

    /// <summary>
    /// 获取多圈清理状态
    /// </summary>
    /// <returns>是否清多圈</returns>
    virtual bool getMultiCircleClear() = 0;

Q_SIGNALS:
    // 零点校准状态信号
    void signalZeroPointStateChanged(ZeroPointCalibrateParam param);
    // 零点校准成功标志信号
    void signalZeroPointCalibrateIsSuccessed(bool status);
    // 零点校准退出信号
    void signalZeroPointCalibrateIsExit(bool status);
};

}  // namespace InoRobBusiness
