#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../../DataService/DataSrvGlobal_V1.h"
#include "../../../GlobalDataTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
// 碰撞方式
typedef enum : int
{
    DOWEL_MODE_V1 = 0,   // 定位销方式
    SENSOR_MODE_V1 = 1,  // 传感器方式
    LIMIT_MODE_V1 = 2,   // 限位方式
} ZP_CALIB_COLLISION_MODE_V1;

/*!
 * \brief  零点参数抽象类, 机械臂下的子类
 * 2024/08/20
 */
class INOROBBUSINESSPROXY_CLASS ZeroPoint_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static ZP_CALIB_COLLISION_MODE_V1 ZP_CALIB_COLLISION_MODE_ToProxy(ZP_CALIB_COLLISION_MODE zp_CALIB_COLLISION_MODE);
    static ZP_CALIB_COLLISION_MODE ZP_CALIB_COLLISION_MODE_FromProxy(ZP_CALIB_COLLISION_MODE_V1 zp_CALIB_COLLISION_MODE_V1);

#pragma endregion

#pragma region 构造与析构

private:
    IZeroPoint *_zeroPoint = nullptr;

public:
    ZeroPoint_V1(IZeroPoint *zeroPoint);
    ~ZeroPoint_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    int writeAbsZero(double dValue[AXIS_NUM_V1]);

    /// <summary>
    /// 读取绝对零点
    /// </summary>
    /// <param name="dValue">绝对零点数组</param>
    /// <returns>通讯状态</returns>
    int readAbsZero(double dValue[AXIS_NUM_V1]);

    /// <summary>
    /// 读取校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    int readCalibrateMode(int &mode);

    /// <summary>
    /// 写入校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    int writeCalibrateMode(int mode);

    /// <summary>
    /// 写入参数重置结构体
    /// </summary>
    /// <param name="resetParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    int writeResetParam(ZeroPointResetParam_V1 resetParam);

    /// <summary>
    /// 读取参数重置结构体
    /// </summary>
    /// <param name="zeroParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    int readResetParam(ZeroPointResetParam_V1 &zeroParam);

    /// <summary>
    /// 读取负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    int readLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX_V1]);

    /// <summary>
    /// 写入负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    int writeLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX_V1]);

    /// <summary>
    /// 写入校准命令
    /// </summary>
    /// <param name="opt">校准命令结构体</param>
    /// <returns>通讯状态</returns>
    int writeHomingOpt(ZeroPointCommand_V1 opt);

    /// <summary>
    /// 读取校准状态
    /// </summary>
    /// <param name="res">反馈状态</param>
    /// <returns>通讯状态</returns>
    int readHomingSts(ZeroPointResult_V1 &res);

    /// <summary>
    /// 读取负载号
    /// </summary>
    /// <param name="number">负载号</param>
    /// <returns>通讯状态</returns>
    int readLoadNumber(int &number);

    /// <summary>
    /// 写入负载号
    /// </summary>
    /// <param name="number">负载号码</param>
    /// <returns>通讯状态</returns>
    int writeLoadNumber(int number);

    /// <summary>
    /// 通知控制器记录当前位置
    /// </summary>
    /// <returns>通讯状态</returns>
    int writeRecordCurrentPos();

    /// <summary>
    /// 碰撞工具检查命令
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>通讯状态</returns>
    int writeCollisionToolsCheck(int axisNo[JOINT_AXIS_NUM_SIX_V1]);

    /// <summary>
    /// 碰撞工具停止命令
    /// </summary>
    /// <returns>通讯状态</returns>
    int wirteStopCollisionToolsCheck();

    /// <summary>
    /// 触发开关传感器状态监测
    /// </summary>
    /// <param name="switchParam">开关参数</param>
    /// <returns>通讯状态</returns>
    int writeSwitchSensorStatusCheck(ZeroPointSensorSwitch_V1 switchParam);

    /// <summary>
    /// 是否支持六关节零点校准功能
    /// </summary>
    /// <returns>支持标志</returns>
    bool readIsSupportZeroPointCalibrate();

    /// <summary>
    /// 读取选中轴对应的编码器多圈情况并清理
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">多圈清理状态</param>
    /// <returns>通讯状态</returns>
    int readEncodeMultiCircle(int16s axisNo, int &status);

    /// <summary>
    /// 读取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="zeroFlag">零值标志</param>
    /// <returns>通讯状态</returns>
    int readJposPreIsZero(int8u axisNo);

    /// <summary>
    /// 读取轴号碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="mode">碰撞方式</param>
    /// <returns>通讯状态</returns>
    int readAxisCollisionMode(int8u axisNo);

    /// <summary>
    /// 下发零点参数计算模式
    /// </summary>
    /// <param name="mode">计算模式</param>
    /// <returns>通讯状态</returns>
    int writeKBParamCalculateMode(int mode);

    /// <summary>
    /// 下发零点参数计算指令
    /// </summary>
    /// <returns>通讯状态</returns>
    int writeKBParamCalculate();

    /// <summary>
    /// 下发零点参数应用指令
    /// </summary>
    /// <returns>通讯状态</returns>
    int writeKBParamApply();

    /// <summary>
    /// 下发零点参数重置指令
    /// </summary>
    /// <returns></returns>
    int writeKBParamReset();

    /// <summary>
    /// 读取开发者模式零点参数
    /// </summary>
    /// <param name="param">参数结构体</param>
    /// <returns>通讯状态</returns>
    int readKBParam(ZeroPointParamDeveloper_V1 &param);

    /// <summary>
    /// 通知下位机是否处于开发者模式
    /// </summary>
    /// <param name="modeFlag">开发者模式标志</param>
    /// <returns>通讯状态</returns>
    int writeIsDeveloperMode(bool modeFlag);

    /// <summary>
    /// 读取测试模式
    /// </summary>
    /// <param name="nMode">模式</param>
    /// <returns>通讯状态</returns>
    int readTestMode(int &nMode);

    /// <summary>
    /// 读取工厂回零操作记录
    /// </summary>
    /// <param name="recordFlag">记录存在标志</param>
    /// <returns>通讯状态</returns>
    int readFactoryHomingRecord(int16s recordFlag[JOINT_AXIS_NUM_SIX_V1]);

    /// <summary>
    /// 启动
    /// </summary>
    /// <returns>启动成功标志</returns>
    bool start();

    /// <summary>
    /// 停止
    /// </summary>
    /// <returns>停止成功标志</returns>
    bool stop();

    /// <summary>
    /// 应用校准值
    /// </summary>
    /// <returns>应用成功标志</returns>
    bool applyValue();

    /// <summary>
    /// 零点模式开关
    /// </summary>
    /// <returns>处理结果</returns>
    int switchModeToHoming();

    /// <summary>
    /// 退出
    /// </summary>
    /// <returns>退出准备是否成功</returns>
    bool exit();

    /// <summary>
    /// 碰撞工具检查
    /// </summary>
    void collisionToolsCheck();

    /// <summary>
    /// 设置轴号选中标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isChecked">选中标志</param>
    void setAxisIsChecked(int axisNo, bool isChecked);

    /// <summary>
    /// 获取轴号选中状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>选中标志</returns>
    bool getAxisIsChecked(int axisNo);

    /// <summary>
    /// 刷新信息结构体数据
    /// </summary>
    void refreshParameterStruct();

    /// <summary>
    /// 设置校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isSuccessed">成功标志</param>
    void setCalibrateIsSuccess(int axisNo, bool isSuccessed);

    /// <summary>
    /// 获取校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>成功标志</returns>
    bool getCalibrateIsSuccess(int axisNo);

    /// <summary>
    /// 设置校准线程运行状态
    /// </summary>
    /// <param name="isRunning">运行标志</param>
    void setThreadRunningStatus(bool isRunning);

    /// <summary>
    /// 获取校准线程运行状态
    /// </summary>
    /// <returns>运行标志</returns>
    bool getThreadRunningStatus();

    /// <summary>
    /// 设置碰撞工具检查运动状态
    /// </summary>
    /// <param name="isChecking">运动状态</param>
    void setCollisionToolsIsChecking(bool isChecking);

    /// <summary>
    /// 获取碰撞工具检查运动状态
    /// </summary>
    /// <returns>运动状态</returns>
    bool getCollisionToolsIsChecking();

    /// <summary>
    /// 设置退出标志
    /// </summary>
    /// <param name="isExit"></param>
    void setExitFlag(bool isExit);

    /// <summary>
    /// 获取退出标志
    /// </summary>
    /// <returns>退出标志</returns>
    bool getExitFlag();

    /// <summary>
    /// 初始化数据
    /// </summary>
    void init();

    /// <summary>
    /// 设置运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    void setStatus(int axisNo, int status);

    /// <summary>
    /// 获取运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    int getStatus(int axisNo);

    /// <summary>
    /// 设置零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">数值</param>
    void setCalibrateValue(int axisNo, int value);

    /// <summary>
    /// 获取零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>数值</returns>
    int getCalibrateValue(int axisNo);

    /// <summary>
    /// 启动监听线程
    /// </summary>
    void openListenThread();

    /// <summary>
    /// 切换模式
    /// </summary>
    /// <param name="type">模式</param>
    /// <returns>成功标志</returns>
    bool switchMode(MODE_TYPE_V1 type);

    /// <summary>
    /// 单轴校准
    /// </summary>
    /// <param name="axisNo">轴号</param>
    void singleAxisCalibrate(int axisNo);

    /// <summary>
    /// 是否选中轴号
    /// </summary>
    /// <returns>选中标志</returns>
    bool axisNoIsSelected();

    /// <summary>
    /// 是否存在未校准的轴号
    /// </summary>
    /// <param name="nextAxisNo">下一个轴号</param>
    /// <returns>存在标志</returns>
    bool isExistUncalibratedAxis(int &nextAxisNo);

    /// <summary>
    /// 设置当前校准的轴号
    /// </summary>
    /// <param name="axisNo">轴号</param>
    void setCalibratingAxisNo(int axisNo);

    /// <summary>
    /// 获取当前校准的轴号
    /// </summary>
    /// <returns>轴号</returns>
    int getCalibratingAxisNo();

    /// <summary>
    /// 设置运动类型
    /// </summary>
    /// <param name="type">运动类型</param>
    void setMotionType(int type);

    /// <summary>
    /// 获取运动类型
    /// </summary>
    /// <returns>运动类型</returns>
    int getMotionType();

    /// <summary>
    /// 设置传感器连接状态
    /// </summary>
    /// <param name="status">连接状态</param>
    void setSensorConnectionStatus(bool status);

    /// <summary>
    /// 获取传感器连接状态
    /// </summary>
    /// <returns>连接状态</returns>
    bool getSensorConnectionStatus();

    /// <summary>
    /// 获取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>置零标志</returns>
    bool getJposPreIsZero(int axisNo);

    /// <summary>
    /// 获取碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>碰撞方式</returns>
    int getCollisionMode(int axisNo);

    /// <summary>
    /// 获取校准值应用标志
    /// </summary>
    /// <returns>应用标志</returns>
    bool getIsApplied();

    /// <summary>
    /// 设置校准值应用标志
    /// </summary>
    /// <param name="appliedFlag">应用标志</param>
    void setIsApplied(bool appliedFlag);

    /// <summary>
    /// 设置UI状态到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    void setUiStatus(int axisNo, int status);

    /// <summary>
    /// 获取缓存状态到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    int getUiStatus(int axisNo);

    /// <summary>
    /// 设置UI校准值到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">校准值</param>
    void setUiCaliValue(int axisNo, int value);

    /// <summary>
    /// 获取缓存校准值到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>校准值</returns>
    int getUiCaliValue(int axisNo);

    /// <summary>
    /// 设置当前选择的子页面
    /// </summary>
    /// <param name="page"></param>
    void setUiCurrentPage(int page);

    /// <summary>
    /// 获取上一次停留的子页面
    /// </summary>
    /// <returns></returns>
    int getUiLastPage();

    /// <summary>
    /// 设置UI选择的校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    void setUiSelectedCalibrateMode(int mode);

    /// <summary>
    /// 获取UI选择的校准模式
    /// </summary>
    /// <returns>校准模式</returns>
    int getUiSelectedCalibrateMode();

    /// <summary>
    /// 设置界面负载号
    /// </summary>
    /// <param name="number">负载号</param>
    void setUiLoadNumber(int number);

    /// <summary>
    /// 获取界面负载号
    /// </summary>
    /// <returns>负载号</returns>
    int getUiLoadNumber();

    // 零点校准状态信号
    rsignal<ZeroPointCalibrateParam_V1> SignalZeroPointStateChanged;
    void SignalZeroPointStateChangedHandler(ZeroPointCalibrateParam SignalZeroPointStateChangedData);

    // 零点校准成功标志信号
    rsignal<bool> SignalZeroPointCalibrateIsSuccessed;
    void SignalZeroPointCalibrateIsSuccessedHandler(bool SignalZeroPointCalibrateIsSuccessedData);

    // 零点校准退出信号
    rsignal<bool> SignalZeroPointCalibrateIsExit;
    void SignalZeroPointCalibrateIsExitHandler(bool SignalZeroPointCalibrateIsExitData);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
