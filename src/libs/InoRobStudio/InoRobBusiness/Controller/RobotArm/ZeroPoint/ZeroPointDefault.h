#pragma once
#include "IInoRobBusiness.h"
#include "mutex"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS ZeroPointDefault : public IZeroPoint
{
    Q_OBJECT

public:
    // 构造与析构
    ZeroPointDefault(IDataSrvBase *dataService, IMonitor *pMonitor, IRobotArm *pRobotArm);
    ~ZeroPointDefault();

#pragma region 通讯相关

    /// <summary>
    /// 写入绝对零点
    /// </summary>
    /// <param name="dValue">绝对零点数组</param>
    /// <returns>通讯状态</returns>
    virtual int writeAbsZero(double dValue[AXIS_NUM]);

    /// <summary>
    /// 读取绝对零点
    /// </summary>
    /// <param name="dValue">绝对零点数组</param>
    /// <returns>通讯状态</returns>
    virtual int readAbsZero(double dValue[AXIS_NUM]);

    /// <summary>
    /// 读取校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    virtual int readCalibrateMode(int &mode);

    /// <summary>
    /// 写入校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    /// <returns>通讯状态</returns>
    virtual int writeCalibrateMode(int mode);

    /// <summary>
    /// 写入参数重置结构体
    /// </summary>
    /// <param name="resetParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    virtual int writeResetParam(ZeroPointResetParam resetParam);

    /// <summary>
    /// 读取参数重置结构体
    /// </summary>
    /// <param name="zeroParam">参数重置结构体</param>
    /// <returns>通讯状态</returns>
    virtual int readResetParam(ZeroPointResetParam &zeroParam);

    /// <summary>
    /// 读取负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    virtual int readLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX]);

    /// <summary>
    /// 写入负载补偿
    /// </summary>
    /// <param name="loadCompensation">负载补偿数组</param>
    /// <returns>通讯状态</returns>
    virtual int writeLoadCompensation(double loadCompensation[JOINT_AXIS_NUM_SIX]);

    /// <summary>
    /// 写入校准命令
    /// </summary>
    /// <param name="opt">校准命令结构体</param>
    /// <returns>通讯状态</returns>
    virtual int writeHomingOpt(ZeroPointCommand opt);

    /// <summary>
    /// 读取校准状态
    /// </summary>
    /// <param name="res">反馈状态</param>
    /// <returns>通讯状态</returns>
    virtual int readHomingSts(ZeroPointResult &res);

    /// <summary>
    /// 读取负载号
    /// </summary>
    /// <param name="number">负载号</param>
    /// <returns>通讯状态</returns>
    virtual int readLoadNumber(int &number);

    /// <summary>
    /// 写入负载号
    /// </summary>
    /// <param name="number">负载号码</param>
    /// <returns>通讯状态</returns>
    virtual int writeLoadNumber(int number);

    /// <summary>
    /// 通知控制器记录当前位置
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeRecordCurrentPos();

    /// <summary>
    /// 碰撞工具检查命令
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>通讯状态</returns>
    virtual int writeCollisionToolsCheck(int axisNo[JOINT_AXIS_NUM_SIX]);

    /// <summary>
    /// 碰撞工具停止命令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int wirteStopCollisionToolsCheck();

    /// <summary>
    /// 触发开关传感器状态监测
    /// </summary>
    /// <param name="switchParam">开关参数</param>
    /// <returns>通讯状态</returns>
    virtual int writeSwitchSensorStatusCheck(ZeroPointSensorSwitch switchParam);

    /// <summary>
    /// 是否支持六关节零点校准功能
    /// </summary>
    /// <returns>支持标志</returns>
    virtual bool readIsSupportZeroPointCalibrate();

    /// <summary>
    /// 执行编码器多圈清理操作
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>通讯状态</returns>
    virtual int writeEncodeMultiCircle(int16s axisNo);

    /// <summary>
    /// 读取选中轴对应的编码器多圈情况并清理
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">多圈清理状态</param>
    /// <returns>通讯状态</returns>
    virtual int readEncodeMultiCircle(int16s axisNo, int &status);

    /// <summary>
    /// 读取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="zeroFlag">零值标志</param>
    /// <returns>通讯状态</returns>
    virtual int readJposPreIsZero(int8u axisNo);

    /// <summary>
    /// 读取轴号碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="mode">碰撞方式</param>
    /// <returns>通讯状态</returns>
    virtual int readAxisCollisionMode(int8u axisNo);

    /// <summary>
    /// 下发零点参数计算模式
    /// </summary>
    /// <param name="mode">计算模式</param>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamCalculateMode(int mode);

    /// <summary>
    /// 下发零点参数计算指令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamCalculate();

    /// <summary>
    /// 下发零点参数应用指令
    /// </summary>
    /// <returns>通讯状态</returns>
    virtual int writeKBParamApply();

    /// <summary>
    /// 下发零点参数重置指令
    /// </summary>
    /// <returns></returns>
    virtual int writeKBParamReset();

    /// <summary>
    /// 读取开发者模式零点参数
    /// </summary>
    /// <param name="param">参数结构体</param>
    /// <returns>通讯状态</returns>
    virtual int readKBParam(ZeroPointParamDeveloper &param);

    /// <summary>
    /// 通知下位机是否处于开发者模式
    /// </summary>
    /// <param name="modeFlag">开发者模式标志</param>
    /// <returns>通讯状态</returns>
    virtual int writeIsDeveloperMode(bool modeFlag);

    /// <summary>
    /// 读取测试模式
    /// </summary>
    /// <param name="nMode">模式</param>
    /// <returns>通讯状态</returns>
    virtual int readTestMode(int &nMode);

    /// <summary>
    /// 读取工厂回零操作记录
    /// </summary>
    /// <param name="recordFlag">记录存在标志</param>
    /// <returns>通讯状态</returns>
    virtual int readFactoryHomingRecord(int16s recordFlag[JOINT_AXIS_NUM_SIX]);

#pragma endregion

#pragma region 操作相关

    /// <summary>
    /// 启动
    /// </summary>
    /// <returns>启动成功标志</returns>
    virtual bool start();

    /// <summary>
    /// 停止
    /// </summary>
    /// <returns>停止成功标志</returns>
    virtual bool stop();

    /// <summary>
    /// 应用校准值
    /// </summary>
    /// <returns>应用成功标志</returns>
    virtual bool applyValue();

    /// <summary>
    /// 零点模式开关
    /// </summary>
    /// <returns>处理结果</returns>
    virtual int switchModeToHoming();

    /// <summary>
    /// 退出
    /// </summary>
    /// <returns>退出准备是否成功</returns>
    virtual bool exit();

    /// <summary>
    /// 碰撞工具检查
    /// </summary>
    virtual void collisionToolsCheck();

#pragma endregion

    /// <summary>
    /// 设置轴号选中标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isChecked">选中标志</param>
    virtual void setAxisIsChecked(int axisNo, bool isChecked);

    /// <summary>
    /// 获取轴号选中状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>选中标志</returns>
    virtual bool getAxisIsChecked(int axisNo);

    /// <summary>
    /// 刷新信息结构体数据
    /// </summary>
    virtual void refreshParameterStruct();

    /// <summary>
    /// 设置校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="isSuccessed">成功标志</param>
    virtual void setCalibrateIsSuccess(int axisNo, bool isSuccessed);

    /// <summary>
    /// 获取校准成功标志
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>成功标志</returns>
    virtual bool getCalibrateIsSuccess(int axisNo);

    /// <summary>
    /// 设置校准线程运行状态
    /// </summary>
    /// <param name="isRunning">运行标志</param>
    virtual void setThreadRunningStatus(bool isRunning);

    /// <summary>
    /// 获取校准线程运行状态
    /// </summary>
    /// <returns>运行标志</returns>
    virtual bool getThreadRunningStatus();

    /// <summary>
    /// 设置碰撞工具检查运动状态
    /// </summary>
    /// <param name="isChecking">运动状态</param>
    virtual void setCollisionToolsIsChecking(bool isChecking);

    /// <summary>
    /// 获取碰撞工具检查运动状态
    /// </summary>
    /// <returns>运动状态</returns>
    virtual bool getCollisionToolsIsChecking();

    /// <summary>
    /// 设置退出标志
    /// </summary>
    /// <param name="isExit"></param>
    virtual void setExitFlag(bool isExit);

    /// <summary>
    /// 获取退出标志
    /// </summary>
    /// <returns>退出标志</returns>
    virtual bool getExitFlag();

    /// <summary>
    /// 初始化数据
    /// </summary>
    virtual void init();

    /// <summary>
    /// 设置运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    virtual void setStatus(int axisNo, int status);

    /// <summary>
    /// 获取运动状态
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    virtual int getStatus(int axisNo);

    /// <summary>
    /// 设置零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">数值</param>
    virtual void setCalibrateValue(int axisNo, int value);

    /// <summary>
    /// 获取零点相关数值(绝对零点值、零点偏置值)
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>数值</returns>
    virtual int getCalibrateValue(int axisNo);

    /// <summary>
    /// 启动监听线程
    /// </summary>
    virtual void openListenThread();

    /// <summary>
    /// 零点校准监听线程
    /// </summary>
    virtual void threadListenCalibrating();

    /// <summary>
    /// 切换模式
    /// </summary>
    /// <param name="type">模式</param>
    /// <returns>成功标志</returns>
    virtual bool switchMode(MODE_TYPE type);

    /// <summary>
    /// 单轴校准
    /// </summary>
    /// <param name="axisNo">轴号</param>
    virtual void singleAxisCalibrate(int axisNo);

    /// <summary>
    /// 是否选中轴号
    /// </summary>
    /// <returns>选中标志</returns>
    virtual bool axisNoIsSelected();

    /// <summary>
    /// 是否存在未校准的轴号
    /// </summary>
    /// <param name="nextAxisNo">下一个轴号</param>
    /// <returns>存在标志</returns>
    virtual bool isExistUncalibratedAxis(int &nextAxisNo);

    /// <summary>
    /// 设置当前校准的轴号
    /// </summary>
    /// <param name="axisNo">轴号</param>
    virtual void setCalibratingAxisNo(int axisNo);

    /// <summary>
    /// 获取当前校准的轴号
    /// </summary>
    /// <returns>轴号</returns>
    virtual int getCalibratingAxisNo();

    /// <summary>
    /// 设置运动类型
    /// </summary>
    /// <param name="type">运动类型</param>
    virtual void setMotionType(int type);

    /// <summary>
    /// 获取运动类型
    /// </summary>
    /// <returns>运动类型</returns>
    virtual int getMotionType();

    /// <summary>
    /// 设置传感器连接状态
    /// </summary>
    /// <param name="status">连接状态</param>
    virtual void setSensorConnectionStatus(bool status);

    /// <summary>
    /// 获取传感器连接状态
    /// </summary>
    /// <returns>连接状态</returns>
    virtual bool getSensorConnectionStatus();

    /// <summary>
    /// 获取预校准位置是否为0
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>置零标志</returns>
    virtual bool getJposPreIsZero(int axisNo);

    /// <summary>
    /// 获取碰撞方式
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>碰撞方式</returns>
    virtual int getCollisionMode(int axisNo);

    /// <summary>
    /// 获取校准值应用标志
    /// </summary>
    /// <returns>应用标志</returns>
    virtual bool getIsApplied();

    /// <summary>
    /// 设置校准值应用标志
    /// </summary>
    /// <param name="appliedFlag">应用标志</param>
    virtual void setIsApplied(bool appliedFlag);

    /// <summary>
    /// 设置UI状态到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="status">状态</param>
    virtual void setUiStatus(int axisNo, int status);

    /// <summary>
    /// 获取缓存状态到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>状态</returns>
    virtual int getUiStatus(int axisNo);

    /// <summary>
    /// 设置UI校准值到缓存
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <param name="value">校准值</param>
    virtual void setUiCaliValue(int axisNo, int value);

    /// <summary>
    /// 获取缓存校准值到UI
    /// </summary>
    /// <param name="axisNo">轴号</param>
    /// <returns>校准值</returns>
    virtual int getUiCaliValue(int axisNo);

    /// <summary>
    /// 设置当前选择的子页面
    /// </summary>
    /// <param name="page"></param>
    virtual void setUiCurrentPage(int page);

    /// <summary>
    /// 获取上一次停留的子页面
    /// </summary>
    /// <returns></returns>
    virtual int getUiLastPage();

    /// <summary>
    /// 设置UI选择的校准模式
    /// </summary>
    /// <param name="mode">校准模式</param>
    virtual void setUiSelectedCalibrateMode(int mode);

    /// <summary>
    /// 获取UI选择的校准模式
    /// </summary>
    /// <returns>校准模式</returns>
    virtual int getUiSelectedCalibrateMode();

    /// <summary>
    /// 设置界面负载号
    /// </summary>
    /// <param name="number">负载号</param>
    virtual void setUiLoadNumber(int number);

    /// <summary>
    /// 获取界面负载号
    /// </summary>
    /// <returns>负载号</returns>
    virtual int getUiLoadNumber();

    /// <summary>
    /// 设置多圈清理状态
    /// </summary>
    /// <param name="isCleared">是否清多圈</param>
    virtual void setMultiCircleClear(bool isCleared);

    /// <summary>
    /// 获取多圈清理状态
    /// </summary>
    /// <returns>是否清多圈</returns>
    virtual bool getMultiCircleClear();

private:
    IDataSrvBase *_pDataService;  // 依赖注入的抽象数据服务对象
    IMonitor *_pMonitor;
    IRobotArm *_pRobotArm;

private:
    std::shared_ptr<std::thread> _pListenThread;             // 监听线程对象
    std::mutex _threadRunLock;                               // 线程锁
    bool _bThreadRun;                                        // 监听线程运行情况
    int _currentAxisNo;                                      // 获取到的当前轴号
    ZeroPointCalibrateParam _robotAxes[JOINT_AXIS_NUM_SIX];  // 零点校准信息结构体
    ZeroPointUiParam _zeroPointUiParam;                      // UI信息缓存
    bool _bIsApplied;                                        // 校准值应用标志
    bool _bIsStop;                                           // 停止校准标志
    bool _bIsExit;                                           // 零点校准功能退出标志
    bool _bIsCheckingCollisionTools;                         // 碰撞工具检查标志
    int _collisionToolsCheckAxisNo[JOINT_AXIS_NUM_SIX];      // 碰撞工具检查轴号数组
    int16s _i16MotionType;                                   // 校准运动类型
    bool _bSensorConnectionStatus;                           // 力矩传感器连接状态
    bool _bIsNeedClearMultiCircle;                           // 清多圈状态标志
};
}  // namespace InoRobBusiness
