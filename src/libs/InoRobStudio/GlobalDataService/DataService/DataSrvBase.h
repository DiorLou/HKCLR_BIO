#pragma once
#include <list>
#include "dllspec.h"
#include "Linker.h"
#include "Protocol.h"
#include "DataSrvGlobal.h"
#include "FrameDef.h"
// #include "IUiObserver.h"
#include "Container.h"
#include "DataLog.h"
#include "InoInterfaces.h"
#include "Interfaces/IDataSrvBase.h"
// #include "FollowCraftDataType.h"

// 标准文件注释
/*! @file
********************************************************************************
<PRE>
模块名       : 通信设计
文件名       : DataSrvBase.h
相关文件     :
文件实现功能 : 提供所有通信接口
作者         : 许健古 （1924）
版本         : V1.0
--------------------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期         版本        修改人          修改内容
2014/08/12    V1.0      许健古 （1924）      创建
</PRE>
********************************************************************************/

#ifdef _WIN32_WCE
    #pragma warning(disable : 4251)
#endif
// 数据服务接口
class DATASRV_CLASS CDataSrvBase : public IDataSrvBase  // : public ILinkerObServer
{
public:
    CDataSrvBase();
    virtual ~CDataSrvBase();

    // UI列表
    // typedef std::list<IUiObServer*> UiListType;

public:
    // 加密文件
    int EncryptProFile(string strPathSrc);
    // 读取静态任务选择标志
    int ReadStaticTask(unsigned char &StaticTask);
    // 写静态任务选择标志
    int WriteStaticTask(unsigned char StaticTask);
    // 读取动态任务选择标志
    int ReadDynamicTask(unsigned char &DynTask);
    // 写动态任务选择标志
    int WriteDynamicTask(unsigned char DynTask);
    // 读取任务程序信息
    int ReadTaskProName(string StrMultiProName[4]);
    // 写任务程序信息
    int WriteTaskProName(string StrMultiProName[4]);
    bool m_bConected;
    int WriteLanKind(int lankind);
    bool GetConectedState(void)
    {
        return m_bConected;
    }
    void SetConeectedState(bool bConected)
    {
        m_bConected = bConected;
    }
    void SetMaunalDisconect(bool bDisconnMaunal);
    int UnRealReadData1(int &nOutput, const int16u nCmdId);  // 正式连接前用不用判断GetConectedState
    // 读主程序的程序名以及子程序的标志 0为子程序 1 为主程序
    int ReadMainProName(int &nState, string &MainProName);
    /******************************************
    /观察者
    ******************************************/
    // 读AD模块的值 每次 8 个 以结构体 DA_STATE 传送 当实际少于8个时，按照实际多少个读取
    int ReadADPageValue(int StartIndex, DA_STATE ADValue[MAXDANUM]);
    // 读DA模块的值 每次 8 个 以结构体 DA_STATE 传送 当实际少于8个时，按照实际多少个读取
    int ReadDAPageValue(int StartIndex, DA_STATE DAValue[MAXDANUM]);
    // 写DA模块输出的值bflag = 0 或者开关量 bflag = 1;
    int WriteDAIndexValue(int Index, int bflag, DA_STATE DAValue);
    // 注册观察者
    //    int  AttachObServer(IUiObServer* pObServer);

    // 反注册
    //    int  DetachObServer(IUiObServer* pObServer = nullptr);

    //     int EmgeStopOn();
    //     int EmgeStopOff();
    /******************************************
    /通讯接口
    ******************************************/
    // 打开设备
    int OpenDev(string strIP, int nPort);

    // 关闭设备
    int CloseDev();

    // 设备在线状态
    bool IsDevOnline();

    /******************************************
    /错误信息
    ******************************************/
    // 通信错误码描述
    string GetErroCodeInfo(int nErroCode);

    // 获取响应帧里面的错误码信息
    RESP_INFO GetFrameErroCode();

    /******************************************
    /使能模拟数据通信
    ******************************************/
    // 使能模拟数据
    void EnableSimulator(bool bEnable);

    // 使能回调数据通知
    void EnableIoDataNotify(bool bEnable);

    // 使能心跳检测
    void EnableHeartBeat(bool bEnable);

    // 纯虚拟数据测试
    int RWDataTest();

    // 链路测试(心跳检测)
    int SendDetectFrame();
    /******************************************
    /实时指令
    ******************************************/
    // 模式设置
    int SetMode(MODE_TYPE nMode);
    // 读机器人名
    int ReadRobotName(string &robotName);
    // 示教
    /*
    AxisId: 最小=1, 最大=8
    */
    int TeachCmd(int AxisId, ROTATE_DIR TurnDir, PRESS_STATE PressState);
    int TeachRockCmd(int AxisGroup, int nXVal, int nYVal, int nZVal, int JogProp);

    int ReadLogSwitchInfo(LOGSWITCH logSwitchInfo[8]);
    // 写LogSwitch信息
    int WriteLogSwitchInfo(LOGSWITCH logSwitchInfo[8]);
    // 坐标系
    /*
    nId: 坐标号(直角,关节忽略此参数)
    */
    int SetCoordType(CoordType nType);

    // 速度等级
    int SetSpeedGrade(int nGrade);

    // 寸动等级
    int SetSpeedJogGrade(int nGrade);

    // 取消寸动
    int CancelStep();

    // 启动
    // int StartMove(int taskId = 0);

    // 停止
    int StopMove(int taskId = 0);

    // 暂停
    // int Pause(int taskId = 0);

    // 多任务启动/继续
    int MultiStart(int taskId);

    // 多任务停止
    int MultiStop(int taskId);

    // 多任务暂停
    int MultiSuspend(int taskId);

    // 单步前进
    // int OneStepAhead();

    // 单步后退
    // int OneStepBack();

    // 光标行号
    int SetCursorLine(int nId);

    // 急停
    // nValue: 1-急停按下, 0-急停弹起
    int EmergStop(int nValue);

    // 复位
    /*
    nValue: 1-复位按下, 0-复位弹起
    */
    int Reset(int nValue);

    // 启动或停止回零
    /*
    bEnable: true-启动回零, false-停止回零
    */
    int EnableHoming(bool bEnable = true);

    // 清报警
    int CleanWarning(PRESS_STATE PressState);
    /******************************************
    /非实时指令:轴空间结构定义(设置)
    ******************************************/

    // 耦合
    // int WriteCouplingPara(AXIS_DBPARAM AxisDbParam);
    // int ReadCouplingPara(AXIS_DBPARAM& AxisDbParam);

    // 系统备份文件
    int SysMaintenanceConfigFile(int &flag, int8u u8IOType);

    // 系统升级
    int SysMaintenanceUpdate(short cmd);
    int ReadSysMaintenanceUpdateStatus(SysMaintenanceInfo &param);

    // 参数配置文件保存标示
    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    // int WriteFileSaveFlag(int nMark);//remove
    // int ReadFileSaveFlag(int &nMark);//remove

    // INT16备用参数
    int WriteIntBackupParam(INT_BACKUPPARAM &IntParam);
    int ReadIntBackupParam(INT_BACKUPPARAM &IntParam);

    // 读取DSP插补标志 0 未插补 1 正在插补
    int ReadDSPMotionState(int16s &MotionState);

    // 读取机器人模式 0 正常模式 1 测试模式 2 取消测试模式 4 工位预约模式
    int ReadRobotMode(int16s &RobotMode);
    // 设置机器人模式 0 正常模式 1 测试模式 2 取消测试模式 4 工位预约模式
    int SetRobotMode(int16s RobotMode);

    // 用户权限模式密码
    // int WriteUserPwd(USER_PWD &UserPwd);//remove
    // int ReadUserPwd(USER_PWD &UserPwd);/remove

    int WriteFileNameForDev(string strDataSrc);
    int ReadFileNameFromDev(string &strDataSrc);

    // 设置起始运行行, flag：0， 表示成功；-1，表示未编译；-2，不在函数体中
    int WriteStartLineInProgram(char *program, short lineNum, char &flag);
    // 读程序文件中的起始行，程序名
    int ReadStartLineInProgram(char *program, int &lineNum);

    // 0：不需要提示轨迹恢复， 1：需要提示
    int ReadPathRecoverFlag(int &flag);
    // 0: 不执行轨迹恢复， 1：执行轨迹恢复
    int WritePathRecoverCmd(int exeRecover);

    // 圆弧插补
    int ReadCirInterpMode(int &nMode);
    int WriteCirInterpMode(int nMode);

    // Double备用参数
    int WriteDbBackupParam(DB_BACKUPPARAM &DbParam);
    int ReadDbBackupParam(DB_BACKUPPARAM &DbParam);

    // IO mapping output information r/w
    int WriteIOOutputMapInfo(IOMapInfo &info);
    int ReadIOOutputMapInfo(IOMapInfo &info);

    // IO mapping input information r/w
    int WriteIOInputMapInfo(IOMapInfo &ioMapInfo);
    int ReadIOInputMapInfo(IOMapInfo &ioMapInfo);

    // IO mapping program information r/w
    int WriteIOPrgMapInfo(IOMapInfo &info, int16u u16PrgId);
    int ReadIOPrgMapInfo(IOMapInfo &info, int16u u16PrgId);

    int WriteTransforFileFlag(int16s TransFlag);
    int ReadTransforFileFlag(int16s &TransFlag);

    int WriteQuitFileFlag(int16s QuitFlag);

    // 绝对零点位置
    //    int WriteAbsZero(AXIS_DBPARAM &AxisDbParam);
    //    int ReadAbsZero(AXIS_DBPARAM &AxisDbParam);

    // 备用接口:16位数据
    int ReadDebugInfoFlag(int16s &sValue);
    int WriteDebugInfoFlag(int16s sValue);

    // 备用接口:Double数据
    int ReadBackupDouble(double &dbValue);
    int WriteBackupDouble(double dbValue);

    // 备用接口:调试信息位数据
    int ReadDebugInfo(DEBUG_INFO &DebugInfo);
    int WriteDebugInfo(DEBUG_INFO &DebugInfo);

    // 配置运动参数
    int WriteMotionParam(MOTION_PARAM &MtParam);
    int RdadMotionParam(MOTION_PARAM &MtParam);

    // 电机转动方向
    int WriteMotorDir(AXIS_INTPARAM &AxisIntParam);
    int ReadMotorDir(AXIS_INTPARAM &AxisIntParam);

    // 编码器位数
    int WriteEncBit(AXIS_INTPARAM &AxisIntParam);
    int ReadEncBit(AXIS_INTPARAM &AxisIntParam);

    /******************************************
    /非实时指令:轴空间结构定义(读)
    ******************************************/
    // 正极限标志
    int ReadPosLimtFlag(AXIS_INTPARAM &AxisIntParam);

    // 负极限标志
    int ReadNegLimtFlag(AXIS_INTPARAM &AxisIntParam);

    // 使能标志
    int ReadEnableFlag(AXIS_INTPARAM &AxisIntParam);

    // 速度极限
    int ReadSpeedLimt(AXIS_INTPARAM &AxisIntParam);

    // 运行停止状态
    int ReadMotorState(AXIS_INTPARAM &AxisIntParam);

    // 方向
    int ReadDirection(AXIS_INTPARAM &AxisIntParam);

    // 到位
    int ReadInPos(AXIS_INTPARAM &AxisIntParam);

    // 当前位置
    // int ReadCurPos(AXIS_DBPARAM& AxisDbParam);
    int ReadCurJPos(double jpos[AXIS_NUM]);

    // 当前速度
    int ReadCurSpeed(AXIS_DBPARAM &AxisDbParam);

    // 当前电流
    int ReadCurElec(AXIS_DBPARAM &AxisDbParam);

    // 当前计算位置
    int ReadCurCalcPos(AXIS_DBPARAM &AxisDbParam);

    // 读视觉摄像头名
    int ReadVisionName(char *VisionName);
    // 读视觉摄像头名
    int WriteVisionName(char *VisionName);
    // 写视觉误差分析数据
    int WriteVisionError(double *VisionError);
    int ReadVisionError(double *VisionError);

    /******************************************
    /非实时指令:笛卡尔坐标系(设置)
    ******************************************/
    // 加速时间
    int WriteAccTime(int nTime);
    int ReadAccTime(int &nTime);

    // 实际控制轴数
    int WriteCtrlAxisNumb(int nAxisNumb);
    int ReadCtrlAxisNumb(int &nAxisNumb, int &nRobotSerial);

    // 恢复默认值标识
    int WriteDefValueMark(int nMark);
    int ReadDefValueMark(int &nMark);

    // 工具坐标系参数
    /*
    nId:坐标号 >=0
    */
    // 读取内存工具坐标系参数
    int ReadMemToolCoordParam(int nId, AXIS_DBPARAM &Pos);

    // 负载
    int ReadArmLoad(int nLinkNo, ArmLoadPara &armload);
    int WriteArmLoad(ArmLoadPara armload);

    int WriteNetPingParam(net_check_para_t pingPara);
    int ReadNetPingParam(net_check_para_t &pingPara);
    int ReadNetPingResult(int16s &completeFlag, net_check_ret_t &pingRet);

    // 机器人参数
    int WriteRobotConPesate(AXIS_DBPARAM &Param);
    int ReadRobotConPesate(AXIS_DBPARAM &Param);

    /////////////////////// zhangyan 2017.01.03
    int WriteRobotRotConPesate(AXIS_DBPARAM &Param);
    int ReadRobotRotConPesate(AXIS_DBPARAM &Param);

    // 6关节内部补偿参数
    int WriteRobMechFullPara(TRobotMechFullPara Param);
    int ReadRobMechFullPara(TRobotMechFullPara &Param);

    // 读取机器人重力补偿参数（自重和刚度）
    int ReadGravityCompenPara(double Param[10]);

    // int ReadDefaultTorqueLimit(int IntValue[AXIS_NUM]);//读默认值

    // int ReadDefaultAvrLoadLimit(int IntValue[AXIS_NUM]);//读默认值

    // 读当前平均负载率
    int ReadActualAvrloadrate(double actualLoad[AXIS_NUM]);
    // 读当前电流值

    int ReadActualCurrent(double actualCurrent[AXIS_NUM]);

    // 读实时平均负载率（单位百分比）
    int ReadActLoadrate(double actualLoad[AXIS_NUM]);
    // 读实时电流（单位百分比）
    int ReadActCurrent(double actualCurrent[AXIS_NUM]);
    // 读历史电流最大值（单位百分比）
    int ReadHisMaxCurrent(double dCurrent[AXIS_NUM]);

    // 读写电机保护参数
    int ReadMotorProtect(MotorProtectPara &para);
    int WriteMotorProtect(const MotorProtectPara &para);

    // 读写环境温度
    int WriteAmbientTemperature(int16u calibFlag, double temperature);
    int ReadAmbientTemperature(int16u &calibFlag, double &temperature, int16s calibData[8]);

    // 读过热率
    int ReadMotorOverheatRatio(double overheat[AXIS_NUM]);
    // 读过载率当前值
    int ReadOverLoadActualRatio(double actOverLoad[AXIS_NUM]);
    // 读过载率最大值
    int ReadOverLoadMaxRatio(double maxOverLoad[AXIS_NUM]);

    // 读写过热率限制
    int WriteOverHeatLimit(int16u uSwitch);
    int ReadOverHeatLimit(int16u &uSwitch);

    // 读写过载率限制
    int WriteOverLoadLimit(int16u uSwitch);
    int ReadOverLoadLimit(int16u &uSwitch);

    // 重置历史最大负载
    int ResetHistoryMaxLoad();

    /////////////////////////////////////////

    // 鼠标监控变量读写数据
    int ReadMouseMonitorStr(string &receiveStr);

    // 通知学习数据加载
    int WriteLearnDataLoad();
    // 读取学习数据加载状态
    int ReadLearnDataLoad(int16s &loadState);
    // 数据恢复默认
    int WriteLearnDataRestoreToDefault();
    // 清除学习数据
    int WriteClearLearnData();
    // 获取控制器中的自学习数据文件对应的版本
    int ReadLearnDataVersionInRc(char *version);
    // 通知控制器将自学习的内存数据写到文件中，1为成功，0为失败
    int UpdateLearnDataToFile(int16s &writeState);

    // 用户自定义报警
    int ReadUserAlarm(char *pAlarmInfo);
    int WriteUserAlarm(char *pAlarmInfo);

    // 工位预约速度
    int ReadStationBookSpeed(int16s &StationBookSpeed);
    int WriteStationBookSpeed(int16s StationBookSpeed);

    int ReadEleCaseConfType(int16u &type);  // 电柜类型

    // 强制I/O
    /*
    nForceInH:  输入端口强制高电平
    nForceInL:  输入端口强制低电平
    nForceOutH: 输出端口强制高电平
    nForceOutL: 输出端口强制低电平
    */
    int WriteForceIoData(int64u nForceInH, int64u nForceInL, int64u nForceOutH, int64u nForceOutL);
    int ReadForceIoData(int64u &nForceInH, int64u &nForceInL, int64u &nForceOutH, int64u &nForceOutL);

    int ElecMachiEnable(bool bEnable);       // 电机使能
    int ElecMachiModeChange(int nModeKind);  // 模式切换

    // 小多传、20kg立柜相关
    int WriteSysForceIoData(int16u nForceInH, int16u nForceInL, int16u nForceOutH, int16u nForceOutL);
    int ReadSysForceIoData(int16u &nForceInH, int16u &nForceInL, int16u &nForceOutH, int16u &nForceOutL);
    int ReadSysIoData(int16u &nIOInData, int16u &nIOOutData);
    int ElecMachiEnable_mul(bool bEnable);       // 电机使能
    int ElecMachiModeChange_mul(int nModeKind);  // 模式切换
    /******************************************
    /非实时指令:笛卡尔坐标系(读)
    ******************************************/
    // 位姿(读)
    int ReadCurLoca(AXIS_DBPARAM &Pos);

    // 读取I/O数据
    int ReadIoData(int64u &nIOInData, int64u &nIOOutData);

    /******************************************
    /全局参数(读)
    *******************************************/
    // 全局最大速度百分比
    int ReadVelPercent(int &nVelPercent);
    int WriteVelPercent(int nVelPercent);

    // 全局最大加速度百分比
    int ReadAccPercent(int &nAccPercent);
    int WriteAccPercent(int nAccPercent);

    // 正在运动
    // nState: 1-运动, 0-停止
    int ReadInMotion(int &nState);

    // 当前运动模式
    int ReadCurMotionMode(int &nMode);

    // 手动坐标系选择
    int ReadJogCoordinate(int &nSelect);

    // 当前程序行号
    int ReadCurProgramLine(int &nId);

    // 读停止状态
    int ReadErroStop(int &ErroStop);

    int ReadWaringNo(int &WaringNo);
    // ARM错误码
    int ReadArmErro(ERRO_INFO &ErroInfo);

    // COMM错误码
    int ReadCommErro(ERRO_INFO &ErroInfo);

    // DSP错误码
    int ReadDspErro(ERRO_INFO &ErroInfo);

    // 读取错误码文件标示
    /*
    nMark: 0-初始状态, 1-文件被清空(不可读), 2-错误文件可读
    */
    int WriteErroFileMark(int nMark = 1);
    int ReadErroFileMark(int &nMark);

    // 读初始化完成状态
    // nState: 1-FPGA初始化完成, 2-双DSP初始化完成, 3-ARM初始化完成
    int ReadInitState(int &nState);

    // 读ECat版本信息
    int ReadECatVersion(char *pszVer, int nLen);

    // 版本信息
    int ReadVersion(VER_INFO &VerInfo);
    int ReadVersionInfo(int8u &VerInfo);

    // 读取机器人控制系统运行模式
    int ReadTestMode_RC(int &nMode);

    // 读写回零正偏置值
    int ReadHomeOffset(int posOffset[6]);
    int WriteHomeOffset(int posOffset[6]);

    // 读工厂回零操作记录（0-无记录，不允许进入回零模式 1-有记录）
    int ReadFactoryHomingRecord(int16s posRecordFlag[6]);

    // read Enconder multi circle sts:  iAxisNo:current axisNo; nSts:0-not over; 1-over
    int ReadEncodeMultiCircle(int16s iAxisNo, int &nSts);

    ////////////////////////////////////////////////////////////////////////////
    // 机器人臂长和负载
    int ReadRobotLinkLoad(int16u &iLinkLen, int16u &iLoadMass);

    // 网络IP
    int ReadEthConfig(ControllerEthCfg &EthCfg);

    // 清除历史故障
    int WriteHisWarning(int nLineFlg = 0);

    // 写伺服参数
    int WriteServoParam(SERVO_PARAM &ServoParam);
    // 读伺服参数
    int ReadServoParam(SERVO_PARAM &ServoParam);

    int WriteResetEncoder(char nAxisId);                    // 重置编码器
    int ReadReEncoderResult(char nAxisId, int &theResult);  // 读重置编码器结果

    /**************************************
    /EtherCAT
    ***************************************/
    // CJ EtherCAT通信周期
    /*
    sCycle: 多数情况为250us的倍数
    */
    int WriteCommCycle(short sCycle);
    int ReadCommCycle(short &sCycle);

    // CJ EtherCAT版本设置
    int WriteECatVerSet(EtherCATVersion eECatVer);
    int ReadECatVerSet(EtherCATVersion &eECatVer);

    // CJ EtherCAT伺服工作模式
    int WriteServoWorkMode(SERVO_MODE eMode);
    int ReadServoWorkMode(SERVO_MODE &eMode);

    // CJ EtherCAT从站个数
    int WriteSubStationNumb(short sNumb);
    int ReadSubStationNumb(short &sNumb);

    int WriteVisualCoord(double *pdVisualCorrd);
    int ReadVisualCoord(double *pdVisualCorrd);

    // TODO
    //    int WriteCnvorPara(CNVOR_PARA *pCnvorPara, UINT16 u16FuncIndex);
    //    int ReadCnvorPara(CNVOR_PARA *pCnvorPara, UINT16 u16FuncIndex);

    //    int ReadCnvorParaAll(CNVOR_PARA *pCnvorPara);

    //    int WriteCnvorPara(UINT16 u16BeltIndex, UINT16 u16FuncIndex);
    //    int ReadBeltPara(UINT16 BeltIndex, UINT16 TriggerPos, INT64 &BeltData, INT16 &TrigNums);
    //    int ReadCnvorMonitorPara(UINT16 BeltIndex, CNVOR_MONITOR_PARA &monitorPara);
    //    int ClearWorkpieceBeyondBoundaryNum(UINT16 u16BeltIndex);
    //    int ReadOffsetTeachPoints(CnvorOffsetPoint &offsetPoint);
    //    int ReadCnvorCaliResult(const CnvorCaliPoint &caliPoint, CnvorCaliResult &caliResult);
    //    int ReadEyeToHandPoint(UINT16 u16BeltIndex, double imagePoint[2], double robPoint[2]);
    //    int WriteCnvorVisionTestData(const VisionConnectCfg &cameraPara);
    //    int ReadCnvorVisionTestData(VisionConnectCfg &cameraPara);

    // Modbus从站配置
    int ReadModbusSlave(int nIndex, ModbusTCP_Para &para1, ModbusRTU_Para &para2);
    int WriteModbusSlave(int nIndex, ModbusTCP_Para para1, ModbusRTU_Para para2);

    /**************************************
    /总线连接状态
    ***************************************/
    int GetCurFieldBusType(int &curType);
    int GetCurIOMapCount(int &ioCount);

    // 动态制动
    int WriteBrakeRelieve(int8u relieveCmd);

    //////////////////////////////////////////////////
    // CJ 功能码
    int ReadSingleServoCode(int AxisNo, char pCode[10], char pValue[12]);
    int WriteSingleServoCode(int AxisNo, char pCode[10], char pValue[12]);
    int ReadFunCode(int AxisNo, int PageID, char pFunCode[10][12]);

    // 伺服参数开关（读写伺服参数、读写当前电流值、负载值时使用）
    int WriteServoParaSwitch(int16u nSwitch);  // 0-关 1-开

    // CJ 时间同步
    /*
    sysTime:yyyymmddhhmmss(毫秒忽略)
    nFrameId: 帧索引值(>=1), 用于标识帧号
    */
    int WriteDevSysTime(GSYSTEMTIME &sysTime, int nFrameId);
    int ReadDevSysTime(GSYSTEMTIME &sysTime);

    // 子程序被调用标识
    /*
    nMark: 0-无需打开子程序, 1-打开子程序
    */
    int WriteSubProgMark(int nMark = 0);
    int ReadSubProgMark(int &nMark);

    // 机械锁定：0正常 1锁定
    int WriteMechaLock(int nMark = 0);
    int ReadMechaLock(int &nMark);

    // 动态制动：0-关 1-开, 用于20kg电柜， 电柜类型3
    int ReadDynBrakeSwitch(int16u &nSwicth);
    int WriteDynBrakeSwitch(int16u nSwicth);
    //////驱控一体//////////////////////////////////////////////
    // 急停配置(0-0类停机；1-1类停机)
    int ReadEmgStopMode(int8u &nMode);
    int WriteEmgStopMode(int8u nMode);

    // 调试按钮模式 保持|抬起   signal: 0-TP ,1-PC
    int GetStartMode(int8u signal, int8u &curMode);
    int SetStartMode(int8u signal, int8u curMode);

    // SN码匹配开关(0-关 1-开）
    int ReadSNMatchSwitch(int8u &iSwitch);
    int WriteSNMatchSwitch(int8u iSwitch);
    // 命令：重置SN码
    int WriteCmdResetSN();
    // 读SN码匹配进度状态（-1-网络通信失败 0-初始 1-进行中 2-完成 3-失败）
    int ReadSNResetSts(int &nSts);

    // 清除InoRobShop配置
    int ClearInoRobShopCFG();

    // 重置历史最大电流值
    int ResetHisMaxCurrent();

    // 读取电控柜FPGA版本信息
    // int ReadCabinetFPGAVersion(int32u& nVer);

    /******************************************
    /文件传输(读、写)
    *******************************************/
    // 创建目录
    int CreateDir(string strDirName);

    // 复制目录
    int CopyDir(string strDirSrc, string strDirDest);

    // 剪切目录
    int CutDir(string strDirSrc, string strDirDest);

    // 重命名目录
    int RenameDir(string strCurName, string strNewName);

    // 删除目录
    int DelDir(string strDirName);

    // 读取单级目录信息, 并保存到指定文件
    int ReadSingleLevelDir(string strDirName, string strFileDest);

    // 读取多级目录信息, 并保存到指定文件
    int ReadMultiLevelDir(string strDirName, string strFileDest);

    // 复制
    int DCopyFile(string strFileSrc, string strFileDest);
    // 复制
    int CopyFile(string strFileSrc, string strFileDest);

    // 剪切
    int CutFile(string strFileSrc, string strFileDest);

    // 重命名文件
    int RenameFile(string strCurName, string strNewName);

    // 写文件
    // strFileSrc-本地文件路径，strFileDest-设备文件端路径
    int WriteFilePro(string strFileSrc, string strFileDest);

    // 读文件
    // strFileSrc-设备文件端路径，strFileDest-本地文件路径
    int ReadFilePro(string strFileSrc, string strFileDest);
    int ReadFileOthers(string strFileSrc, string strFileDest, bool bCreat = false);  // will remove
    int WriteFileOthers(string strFileSrc, string strFileDest);
    int GetControllerFileMD5(string strFileSrc, char ans[32]);
    bool CompareControllerAndLoccalFileMd5(string strFileSrc, string strFileDest);
    // send file contents to controller
    int SendFileContents(string strFileSrc);
    // 发送断点信息到控制器
    int SendBreakpointsInfo(char *info, int len);

    // 获取实时指令配置信息
    int ReadRealCmdInfo(REALCMD_INFO &RealCmdInfo, bool bRecurrent = false);
    int ReadRCStsInfo(RCSTS_INFO &rcStsInfo);

    int ReadRCStsInfo_0322(RCSTS_INFO_0322 &rcStsInfo);

    // 初始化数据读取
    int ReadInitData(INIT_DATA &initData);
    int ReadInitData_0322(INIT_DATA_0322 &InitData);

    int ReadArmVerInfo(char ArmVerInfo[20]);
    /******************************************
    /变量读、写
    *******************************************/
    // 读R变量的值
    int ReadRVar(R_VAR &RVar);
    int ReadBVar(B_VAR &BVar);
    int ReadDVar(D_VAR &RVar);
    int ReadLBVar(LB_VAR &LBVar);
    int ReadLDVar(LD_VAR &LDVar);
    int ReadLRVar(LR_VAR &LRVar);
    int ReadStrVar(STR_VAR &StrVar, int ReadNum = 10);
    int WriteAStrVar(string StrValue, int Index);

    int ReadBVar(SearchB BVar[10]);
    int ReadRVar(SearchR RVar[10]);
    int ReadDVar(SearchD DVar[10]);
    int ReadMixVar(MixSearchV Var[10]);

    // 写Pallet变量的值
    int WritePalletVar(PalletInfo PallletVar, int PallletNo);
    // 读PALLET变量的值
    int ReadPalletVar(Pallet_VAR &PalletVar);
    // 读位置变量的值
    int ReadProPosVar(P_VAR &PVar);

    // 读取内存中的P点（需要比对上下程序是否一致）
    int Read_RAM_P(string strFileName, int pageIndex, int &checkRet, int &feedbackPage, POSITEM PVar[10]);
    // 搜索内存中的点
    int Search_RAM_P(string strFileName, int pointIndex, int &checkRet, int &feedbackPage, int &indexOnCurPage, POSITEM PVar[10]);
    // 读取内存中的GP点
    int Read_RAM_GP(int pageIndex, RAM_GP PVar[10]);

    // 读LPR变量的值
    int ReadLPRVar(PR_VAR &PRVar);
    // 读PR变量的值
    int ReadPRVar(PR_VAR &PRVar);
    // 写R变量的值
    int WriteRVar(int RVar, int RNo);
    // 写B变量的值
    int WriteBVar(unsigned char BVar, int BNo);
    // 写D变量的值
    int WriteDVar(double DVar, int DNo);
    // 写LR变量的值
    int WriteLRVar(int LRVar, int LRNo);
    // 写LD变量的值
    int WriteLDVar(double LDVar, int LDNo);
    // 写LB变量的值
    int WriteLBVar(unsigned char LBVar, int LBNo);
    // 写LPR变量的值
    int WriteLPRVar(PointData PRVar, int PRNo);
    // 写PR变量的值
    int WritePRVar(PointData PRVar, int PRNo);
    // 通知控制器全局点位文件已更新
    int NotifyGlobalPointFileUpdate();

    /******************************************
    /EMC测试
    *******************************************/
    // 启动
    int StartEmcTest(EMC_MOD &EmcMode);

    // 暂停计数
    int PauseEmcCount();

    // 清零计数
    int ResetEmcCount();

    // 读ECM测试监控参数
    int ReadEmcTestParam(EMCTEST_PARAM &EmcParam);

    // 停止EMC测试
    int StopEmcTest();

    int GetWSAError()
    {
        return m_commVersionMgr->ErrorCode();
    }

    void TestConnection()
    {
        m_commVersionMgr->TestConnection();
    }

    // 通知控制器标定结果已经放在文件中了
    int WriteVisualCoord_STD(int16u nIndex);
    int ReadVisualCoord_STD(int16u nIndex, double *pdVisualCorrd, WobjData &wobjParam);
    int WriteVisionIP(const CAMERAPARA_T &stCameraPara);
    int ReadVisionIP(CAMERAPARA_T &stCameraPara);
    int WriteVisionTriggerPara(const CAMERAPARA_T &stCameraPara);
    int ReadVisionTriggerPara(CAMERAPARA_T &stCameraPara);
    int WriteVisionTestData(const CAMERAPARA_T &stCameraPara);
    int ReadVisionTestData(CAMERAPARA_T &stCameraPara);
    int ReadVisionConectFlag(int &ConectFlag);

    // 读是否可以读取视觉数据的标志以及通讯是否连接的标志
    int ReadVisionDataSavedFlag(int &bResaveData, int &ConectFlag);

    // 告知ARM已经下发视觉标定的json文件，ARM从json文件读取标定结果
    int WriteVisionResult(int16u nIndex);

    // 读OUT输出控制权限
    int ReadIOOutState(int IOOutState[MAXIONUM]);
    // 读DA控制权限
    int ReadDAState(int DAState[MAXDANUM]);
    // 读AD控制权限
    int ReadADState(int ADState[MAXDANUM]);
    // 读取IRLINK配置权限及IO个数
    int ReadIRLinkState(IR_CTRL_SET &IRLinkSet, int &di_num, int &do_num, int &ad_num, int &da_num);
    // 读系统参数控制权
    // int ReadCtlAuthority(int16s &sysAuthority);//remove
    // 写系统参数控制权
    // int WriteCtlAuthority(int16s sysAuthority);//remove
    // 读波形图数据
    int ReadLockWaveform(LOCKDATA_ARR &LockDataArr);

    // 监控操作
    int WriteScrewMonPara(SCREW_MON &pScrwMon);
    int ReadScrewMonPara(SCREW_MON &pScrwMon);
    int ClearScrewCount(int nCmd);

    // 工程操作
    int ReadScrewProjsName(std::list<string> &name);
    int RenameScrewProj(string nameFrom, string nameTo);
    int CopyScrewProj(string nameFrom, string nameTo);
    int DeleteScrewProj(string strName);
    int AddScrewProj(string strName);

    // 以工程为单位读写
    int ReadScrewProj(string projName, SCREWDRIVER_PROJECT &projContent);
    int WriteScrewProj(const string &projName, const SCREWDRIVER_PROJECT &projContent);
    // int WriteLockScrewCraft(CString projName, int nId, LOCK_SCREW_SET_PARAMS lockScrwSet);
    // int WriteUnLockScrewCraft(CString projName, int nId, UNLOCK_SCREW_SET_PARAMS unlockScrwSet);

    // 以工艺为单位读写，操作最终对象是伺服而不是工程文件
    // 读-是跨过工程文件，直接显示到示教器；写-是不但保存到工程文件，而且下发到伺服）
    int ReadLockCraftFromServo(int nId, LOCK_SCREW_SET_PARAMS &lockScrwSet);
    int WriteLockCraftToServo(int nId, LOCK_SCREW_SET_PARAMS lockScrwSet);
    int ReadUnLockCraftFromServo(int nId, UNLOCK_SCREW_SET_PARAMS &UnlockScrwSet);
    int WriteUnLockCraftToServo(int nId, UNLOCK_SCREW_SET_PARAMS UnlockScrwSet);

    // 机器人错误信息
    int WriteErrInfo(int nCmd);
    int ReadErrInfo(int &nState);
    // 系统诊断（新版的错误保存和导出）
    int SendErrSaveCmd(ErrsaveCmd cmd);
    int ReadErrSaveSta(ErrsaveSta &sta);
    int SendErrExportCmd(ErrexportCmd cmd);
    int ReadErrExportSta(ErrexportSta &sta);

    int WriteCmd_CalTeachPadZipInfo(int nMark);  // 发送命令，统计控制器SD卡中包的信息，并生成文件，供后续使用
    int ReadCmd_CalTeachPadZipInfo(int &nMark);

    int ReadEcatPdoLostInfo(UINT16 &totalLostCount, UINT16 &continueLostCount, UINT16 &lostFlag);  // 读EtherCAT PDO丢帧信息
    int ReadSDStastus(char sts[11]);                                                               // 读SD卡信息

    int ReadDebugStatus(UINT16 &u16DebugStatus);
    int WriteDebugMode(UINT16 u16DebugMode);

    int ReadMultiTaskConfig(INT8 config[4]);
    int WriteMultiTaskConfig(INT8 config[4]);

    // UDP client interfaces
    int InitUdpClient(string strIpAddress, unsigned short usPort);

    int UnInitUdpClient();

    int UdpSendTo(int8u *const buffer, int iLen);

    int32u UdpDataCount();

    // get UDP frame data from buffer
    int PeekUdpBuf(int8u *const buffer, int32u offset, int32u len);

    int UdpReadData(int8u *const buffer, int len, int32u timeout = 3000);

    // read servo iptable
    int ReadServoIpTable(ALL_SERVO_INFO &stServoIpTable);
    // end

    // 同步工程信息到控制器， projectName工程名char[64], 例如/TeachProgram/a01;
    // infoFlag是同步的项的选择，工程信息、工具参数、用户参数、工件参数、标签信息、用户自定义报警、全局点位、程序文件、译码类型 共 9项选择
    int SyncProjectInfo(char *projectName, char *flags);

    // 读工程是否需要重新译码，1表示需要重新译码； 0 无需重新译码
    int ReadProjectNeedReTrans(char &flag);

    // 重新写激活工程
    int WriteActProjectName(char projSwitch, char *strProjectName);

    // 清空同步工程时所用到的临时目录里的文件
    int ClearProjectTempDir();

    /*-------------------------------------
    工程管理相关接口
    --------------------------------------*/
    // 读取当前激活的工程文件夹
    int ReadActiveProjectDir(char *name);

    // 读取工程操作状态
    // iOpType:对应枚举类 0-新增 1-删除 2-重命名 3-粘贴
    // state:操作反馈状态(-1-进行中；-10-失败；1-成功；0-缺省)
    int ReadProjectOpState(int iOpType, int16s &state);
    int ReadProjectHandleState(int nId, int16s &state);

    // 新增工程
    int WriteCreateNewProject(string strProjectName);
    // 删除工程
    int WriteDeleteProject(string strProjectName);
    // 重命名工程
    int WriteReNameProject(string strOldName, string strNewName);
    // 粘贴工程
    int WritePasteProject(string strSrcName, string strDestName);

    // 读取当前各任务断点标志， 目前以4个任务的标志返回，flags[4]
    int ReadBreakpointFlag(int16u *flags);

    // 下发任务的激活状态, 4个任务的激活状态，0不激活， 1激活
    int WriteTasksActiveState(int8u *flags);

    // 读取任务的运行信息
    // int ReadTasksRunInfo(TasksRunInfo &infos);

    // 设置所有任务到起始行到Start, ErrCode = 0x00B9
    // int SetAllTasksBackToStartLine();

    // 设置某个任务到起始行到Start, ErrCode = 0x00B9
    // int SetTaskBackStartLine(int8u taskId);

    // 设置某个任务的起始行到某一行, ErrCode = 0x00B9
    // int SetTaskStartRunLine(int8u taskId, int16u lineNum, char *fileName);

    // 读取某个任务中所有的包含的文件名, 以逗号为分隔
    // int ReadFileListInTask(int8u taskId, char *content);

    // 读工程解析状态， -1，出错； 0，正在进行； 1, 完成
    int ReadProjectParserFlag(char &flag);

    // 自动校准  UP 0;Down 1
    int WriteTeachAutoCalibration(int flag);

    // 设置全局变量的值，如果设置出错，则返回WarningID = 0x1020，通讯吗0x05B8
    int SetVarValue(const BRDP_INFO &info);

    // 总线标准化应用的监控
    int ReadFieldBusInputStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int WriteFieldBusInputStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int ReadFieldBusInputForceHighStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int WriteFieldBusInputForceHighStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int ReadFieldBusInputForceLowStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int WriteFieldBusInputForceLowStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int ReadFieldBusOutputStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int WriteFieldBusOutputStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);
    int WriteFieldBusOutputBitStatus(const int16u bitId, const unsigned char bitValue);
    int ReadOutputCtrlAuthorityStatus(int16u startByteId, int16u byteNum, unsigned char *pBuf);

    // 消息服务器
    void MsgServerActive(bool active);
    int MsgServerOutput(char *const msg, int len);
    MsgServer *GetMsgServerObj()
    {
        return m_msgServer;
    }

    // 读取机器人维护信息
    int ReadRobotMaintainInfo(MaintainReminder maintainReminder[MAINTAIN_KIND]);
    // 写入机器人维护时间
    // type ：组件类型
    // maintainedTime : 机器人维护时间
    int WriteRobotMaintainTime(int8u type, char maintainedTime[DATE_STRING_LEN]);

    UINT16 GetActualAxisNum(UINT16 u16RobotType);

    // 读取抱闸状态
    // 1-合抱闸，0-松抱闸
    int ReadBrakeState(char stateArray[6]);
    // 发送抱闸指令
    // brake_cmd 传入指令类型（1-合抱闸，0-松抱闸）
    // brake_count 传入当前计数值，用于判断程序崩溃或是断开连接
    // axis_number 轴号（1~6）
    int WriteBrakeState(char brake_cmd, int32u brake_count, int axis_number);

    // 通讯版本
    bool VersionMatch();
    void GetCommVersion(int8u &majorV, int8u &minorV);

    // 实时指令帧
    /*
    0: 写命令帧成功
    -1: 下行帧写失败
    -2: 上行帧查询失败
    -3: 读取响应帧失败
    -4 :帧格式错误
    */
    int RealCmdIo(REALTIME_CMD &RealCmd);

    // 非实时指令帧
    /*
    0: 写命令帧成功
    -1: 下行帧写失败
    -2: 上行帧查询失败
    -3: 读取响应帧失败
    -4 :帧格式错误
    */
    int UnRealCmdIo(UNREALTIME_CMD &UnRealCmd);

    // 附加数据帧
    /*
    0: 写命令帧成功
    -1: 下行帧写失败
    -2: 上行帧查询失败
    -3: 读取响应帧失败
    -4 :帧格式错误
    */
    int ExtraDataIo(EXTRA_DATA &ExtraData, IO_TYPE nIoType);

    // 工程配置
    int ProjectConfig();

    // 设置单帧超时
    void SetSingleTimeout(int timeOut);

private:
    // 非实时指令：读数据
    int ReadAxisDbParam(double DbParam[AXIS_NUMB], const int16u nCmdId);
    int ReadAxisIntParam(AXIS_INTPARAM &AxisIntParam, const int16u nCmdId);
    int UnRealReadData(double &dbOutput, const int16u nCmdId);
    int UnRealReadData(int &nOutput, const int16u nCmdId);

    // 非实时指令：写数据
    int WriteAxisDbParam(double DbParam[AXIS_NUMB], const int16u nCmdId);
    int WriteAxisIntParam(AXIS_INTPARAM &AxisIntParam, const int16u nCmdId);
    int UnRealWriteData(const double dbInput, const int16u nCmdId);
    int UnRealWriteData(const int nInput, const int16u nCmdId);

    // 从设备读取文件
    /*
    2: 创建文件失败
    3: 帧号检测失败
    0: 成功
    其他返回值，参考ExtraDataIo
    */
    /*
    参数说明:
    strDataSrc:  数据来源：目录或文件
    strFileDest: 目标文件(PC端)
    nCmdId: 命令
    */
    int ReadFileFromDev(string strDataSrc, string strFileDest, int16u nCmdId, bool bCreat = false);

    // 往设备写文件/文件夹路径
    /*
    strDataSrc:  源目录或文件
    strFileDest: 目标目录或文件
    nCmdId: 命令
    */
    int WritePathToDev(string strPathSrc, string strPathDest, int16u nCmdId);

    /*
    nOperId:  操作类型ID值
    pEmcMode: 只有启动EMC测试时有效,其他时候为nullptr
    */
    int WriteEmcParam(int nOperId, EMC_MOD *pEmcMode);

    // 检测文件名、路径合法性
    bool IsPathValid(string strPath);

    bool IsWinPathValid(string strPath);

    // IO数据数据
    void TraceIoData(int8u *pBuf, int nLen, int nIoType);

    // 子窗口回调通知
    void NotifyIoData(int8u *pBuf, int nLen, int nIoType);

    // 链路连接检测
    void ThreadHeartbeat();

    // public:
    //     void UdpClientLock() { m_lockUdpClient.Lock(); }
    //     void UdpClientUnLock() { m_lockUdpClient.UnLock(); }

private:
    // 是否使用模拟数据
    bool m_bSimulatorData;

    // 是否开启数据回调
    bool m_bEnableNotify;

    // 是否开启心跳探测
    bool m_bHeartBeat;

    // 应用协议对象
    CProtocol m_Protocol;

    // 观察者列表
    //    UiListType m_ObServerList;

    // 观察者Mutex
    std::mutex _observerMutex;

    // 错误信息
    RESP_INFO m_RespInfo;

    // 字符转换
    CConvert m_strConvert;

    // 错误信息描述
    string m_strErroInfo;  // 用成员变量,否则返回值是乱码

    // On real read flag
    bool m_bOnRealRead;

    // 通信错误
    COMM_ERRO m_CommErro;

    // 用户密码数据
    int8u m_nPwdContent[ALL_PWD_SIZE];

    // bool m_bOnReadFile;
    bool m_bOnWriteFile;
    std::mutex m_readFileMutex;

    string m_ip;
    int m_port;

    string m_destIp;

    bool m_isPinging;

    MsgServer *m_msgServer;

    // TCP/IP 客户端，用于与控制器通讯
    ICommTransportLayer *m_tcpClientTransportLayer;
    // Udp 客户端，用于与控制器间的数据订阅
    ICommTransportLayer *m_udpTransportLayer;
    // TCP/IP 客户端，用于与控制器通讯的版本集合器
    ICommVersionMgr *m_commVersionMgr;
    // 用于PING远端设备
    IPingDevice *m_pingDevice;

#pragma region 机型参数

public:
    // 通知机型参数文件更新
    int RobotParamFileChange(char *info);
    // 启动伺服监控
    int RobotParamServoStart(char *info);
    // 停止伺服监控
    int RobotParamServoStop();
    // 获取当前伺服参数数据
    int RobotParamServoCurrent(string &info);
    // 读取参数更新状态
    int RobotParamUpdateStatusRead(string &info);
    // 获取匹配信息
    int RobotParamMatchaingInformation(string &info);
    // 启动参数匹配
    int RobotParamParameterMatchingStart(char *info);
    // 启动获取本体通配信息
    int BodyWildcardInformationObtainStart(char *info);
    // 本体通配信息获取状态
    int BodyWildcardInformationObtainStatus(string &info);
    // 设置通配状态
    int RobotParamGeneralSetStatus(char *info);
#pragma endregion

#pragma region 模块激活
public:
    // 询问控制器加密授权认证是否通过
    int GetAuthStatus(int8u &status);

    // 向控制器写入模块激活信息
    int AuthActivateFunction(CHIPSECRET bufSecret, CHIPUSERDATA bufUserData);

    // 从控制器获取模块激活信息
    int GetAuthROMID(CHIPROMID buf);
    int GetAuthEtag(CHIPETAG buf);
    int GetAuthUserData(CHIPUSERDATA buf);
    int GetAuthBoardSN(ROBOTCONTROLLERSN buf);

    int GetEtherCATChipExistOrNot(int8u &status);
    int GetEtherCATSlaveStatus(int8u &status);

    static int IsArrayAllNull(unsigned char *array, int length);
    // 设置伺服参数
    int SetServoData(char *info);

#pragma endregion

#pragma region 工艺插件

public:
    int PluginTextWrite(const string &request);
    int PluginTextRead(const string &request, string &response);
    int PluginBinaryWrite(const string &name, vector<char> &request);
    int PluginBinaryRead(const string &name, int responseLength, vector<char> &response);

#pragma endregion
};

DATASRV_VAR extern CContainer<CDataSrvBase> gs_DataSrv;  // 声明数据服务模块单例对象
