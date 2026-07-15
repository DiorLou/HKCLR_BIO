#pragma once
#include "IRobotArm.h"
#include "IInoRobBusiness.h"
#include "InstallParameter/InstallParamDefault.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS RobotArmDefault : public IRobotArm
{
    Q_OBJECT

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService;
    IMonitor *_pMonitor;
    IConnection *_pConnection;
    IUser *_pUser;
    IDebuger *_pDebuger;              // 调试
    IMotion *_pMotion;                // 运动
    ITool *_pTool = nullptr;          // 工具
    IWobj *_pWobj = nullptr;          // 工件
    IPosition *_pPosition = nullptr;  // 位置

    // 安装参数
    IInstallParameter *_pInstallParam;

    // 干涉区
    IInterferenceArea *_pInterferenceArea = nullptr;

    // 六关节零点校准
    IZeroPoint *_pZeroPoint = nullptr;

    // 六关节零点修复
    IZeroPointRepair *_pZeroPointRepair = nullptr;

public:
    RobotArmDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~RobotArmDefault() override;
    void init() override;
    // 安装参数
    IInstallParameter *GetInstallParam() override;

    // 25版本干涉区
    IInterferenceArea *getInterferenceArea() override;

    // 六关节零点校准
    IZeroPoint *getZeroPoint();

    // 六关节零点修复
    IZeroPointRepair *getZeroPointRepair();

    int8u getMaxAxisNum() override;

    // 常用的权限检查
    bool checkCommonPermission() override;

#pragma region 碰撞检测
private:
    ICrashDetection *_pCrashDetection = nullptr;

public:
    ICrashDetection *getCrashDetectionObject() override;
#pragma endregion

#pragma region 绝对零点

    // 当前电机位置
    int ReadCurMotorPos(AXIS_DBPARAM &AxisDbParam);

    // 获取当前电机位置
    int getCurrMotorPos(double motorPos[AXIS_NUM]) override;

    // 获取当前绝对零点值
    int getAbsZeroValue(double absZero[AXIS_NUM]) override;

    // 保存绝对零点值至控制器
    int saveAbsZeroValue(double absZero[AXIS_NUM]) override;

    //重置绝对零点
    int resetAbsZeroValue(uint16_t u16AxisNo) override;

    //获取重置绝对零点结构
    int getResetAbsZeroValue(uint16_t u16AxisNo ,uint16_t &result) override;

    // 保存绝对零点前的权限检查
    bool checkPermissionBeforeSaveAbsZero();

    // 运动到点
    bool moveToPoint(JPos jPos, std::string originName) override;

    // 停止运动
    bool stopMoveToPoint() override;

#pragma endregion

#pragma region 工作原点

    // 从控制器中读取工作原点
    int ReadWorkOriginPts(JPos &JAndEData, UINT ulIndx) override;

    // 将工作原点写入控制器中
    int WriteWorkOriginPts(JPos &JAndEData, UINT ulIndx) override;

    // 保存工作原点的数据
    int saveWorkOriginData(double jPoint[JOINT_AXIS_NUM], double ePoint[EXT_AXIS_NUM], UINT ulIndex) override;

    // 检查jPoint数据是否正确
    bool checkJPointData(double jPoint[JOINT_AXIS_NUM]);

    // 保存工作原点前的权限检查
    bool checkPermissionBeforeSaveWorkOrigin() override;

#pragma endregion

#pragma region 回零校准

    // 读工厂回零操作记录（0-无记录，不允许进入回零模式 1-有记录）
    int readFactoryHomingRecord(int16s posRecordFlag[6]) override;

    // 读取编码器多圈状态 轴号 状态 0-圈数过多   1-圈数不过多
    int readEncodeMultiCircle(int16s iAxisNo, int &nSts) override;

    // 模式设置
    int setMode(MODE_TYPE nMode) override;

    // 获取使能状态 1-使能 0-非使能
    int16u getEnableState() override;

    // 启动回零功能
    bool startHoming(int16s axisNo, int currMode) override;

    // 停止回零
    bool stopHoming(int16s axisNo) override;

    // 获取回零状态
    E_HOMINGSTS getHomingState(int16s axisNo) override;

    // 应用校准前的权限检查
    bool checkPermissionBeforeSaveCalibValue() override;

    // 应用校准值
    bool applyCalibValue(double writeValue[AXIS_NUM]) override;

    // 获取回零模式
    int getHomeMode() override;

    // 保存参数重置中的偏移值
    int savePosOffset(int posOffset[6]) override;

    // 检查保存偏移值的权限
    bool checkPermissionBeforeSavePosOffset();

    // 检查修改权限
    bool CheckModifyPermission() override;

    // 检查控制器保存文件标志
    bool checkFileSaveFlag() override;

    // 向ARM发送保存文件命令
    void saveFileCommond(bool *ok = 0) override;

    // 获取测试模式
    int getTestMode();

    // 调控回零模式
    int changedHomeModeWhenSetHome(int &runMode, int currAxisNo);

    // 回零前检查权限
    int checkPermissionBeforeStartHome();

    // 读取测试模式
    // 0-正常模式 1-单板测试模式 2-系统安装刷机模式 3-系统更新模式 4-整机测试模式 5-系统安装完成，等待重启初始化PLC程序 6-系统安装完成，并已重启准备进行初始化PLC程序
    // 7-系统安装完成，下次开机设为单板测试模式 8-下次系统启动将删除PLC、机器人程序及日志文件 9-恢复模式	10-老化测试模式
    int ReadTestMode_RC(int &nMode);

    // 当前运动模式
    int ReadCurMotionMode(int &nMode);

    int UnRealReadData(int &nOutput, const int16u nCmdId);

    // 读取回零状态
    int ReadHomingSts(ST_HOMING_RES &theReslut) override;

    // 写入回零指令
    int WriteHomingOpt(ST_HOMING_OPT opt);

    // 写入绝对零点位置
    int WriteAbsZero(double dValue[AXIS_NUM]);

    // 读取绝对零点位置
    int ReadAbsZero(double dValue[AXIS_NUM]) override;

    // 重设绝对零点位置
    int ResetAbsZero(uint16_t u16AxisNo);

    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    int readFileSaveFlag(int &nMark);

    // 参数配置文件保存标示
    int writeFileSaveFlag(int nMark);

    // 读回零偏置值
    int ReadHomeOffset(int posOffset[6]) override;

    // 写回零偏置值
    int WriteHomeOffset(int posOffset[6]);

    int getSevenDragSwitchTeaching() override;

    int setSevenDragSwitchTeaching(int nType) override;

    int setSevenTakePoint() override;

    //七轴机器人参数
    int getSevenRobotStructParameters(std::vector<double> &data) override;

    int saveSevenRobotStructParam(std::vector<double> &data, bool autoSaveFileCommd = true) override;

#pragma endregion

#pragma region 机器人设置
    // 获取当前机型
    RBTTYPE_E getRobotType() override;
    // 机器人结构参数
    // 工业
    int getRotbotStructParameters(double structParams[LINK_PARM_NUM]) override;
    // 协作
    int getCoRotbotStructParameters(std::vector<double> &data) override;

    // 保存机器人结构参数
    int saveRobotStructParam(double structParams[LINK_PARM_NUM]) override;

    // 保存机器人结构参数 协作
    int saveCoRobotStructParam(const std::vector<double> &data, bool autoSaveFileCommd = true) override;

    // 保存机器人的减速比
    int saveRobotReductionRatioParam(double reduRatio[AXIS_NUMB], bool autoSaveFileCommd = true) override;

    // 保存机器人耦合参数
    int saveRobotCouplingParam(double coupParam[AXIS_NUMB * 2], bool autoSaveFileCommd = true) override;

    // 保存机器人内部补偿参数
    int saveRobotCompensationParam(double compParam[COM_PARM_NUM], bool autoSaveFileCommd = true) override;

    // 获取轴的数量
    int getAxiCount() override;

    // 机器人参数保存前权限检查
    bool checkPermissionBeforeSaveRobotParam();

    // 读取减速比参数
    int getReductionRatioParam(double reduRatio[AXIS_NUMB]) override;

    // 获取耦合参数
    int getCouplingParam(double coupParaM[AXIS_NUMB], double coupParaS[AXIS_NUMB]) override;

    // 获取内部补偿参数
    int getRobotCompParam(double compParam[COM_PARM_NUM]) override;

    // 将机器人结构参数写入控制器
    int WriteRobotParam(AXIS_DBPARAM &Param);

    // 从控制器读取机器人结构参数
    int ReadRobotParam(AXIS_DBPARAM &Param);

    // 从控制器读取减速比参数
    int ReadSpeedDownRatio(AXIS_DBPARAM &AxisDbParam);

    // 将减速比参数写入控制器
    int WriteSpeedDownRatio(AXIS_DBPARAM &AxisDbParam);

    // 从控制器读取耦合参数
    int ReadCouplingPara(double CouplingPara[AXIS_NUM * 2]);

    // 将耦合参数写入控制器
    int WriteCouplingPara(double CouplingPara[AXIS_NUM * 2]);

    // 从控制器读取内部补偿参数（旋转角度结构参数）
    int ReadRobotRotParam(double Param[16]);

    // 将内部补偿参数（旋转角度结构参数）写入控制器
    int WriteRobotRotParam(double Param[16]);

    // 将安装姿态写入控制器
    int writeRobotInstallParam(double param[16]);

    // 非实时指令：写数据
    int WriteAxisDbParam(double DbParam[AXIS_NUMB], const int16u nCmdId);

    // 非实时指令：读数据
    int ReadAxisDbParam(double DbParam[AXIS_NUMB], const int16u nCmdId);

#pragma endregion

#pragma region 运动参数

    ///******示教参数设置*******///
    bool checkPermissionBeforeSaveMotionParam() override;

    // 保存寸动步长
    int saveJogDistan(double dbJoint, double dbPos, double dbAngle) override;

    // 写入寸动步长
    int writeJogDistan(double dbJoint, double dbPos, double dbAngle);

    // 读取寸动步长
    int readJogDistan(double &dbJoint, double &dbPos, double &dbAngle) override;

    // 获取最大允许关节速度（示教）
    int getTeachAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) override;

    // 保存最大允许关节速度（示教）
    int saveTeachAxisMaxSpeed(double jointSpeed[AXIS_NUMB]) override;

    // 写入最大允许关节速度（示教）
    int writeTeachAxisMaxSpeed(AXIS_DBPARAM &AxisDbParam);

    // 读取最大允许关节速度（示教）
    int readTeachAxisMaxSpeed(AXIS_DBPARAM &AxisDbParam);

    // 写入最大允许位置速度（示教）
    int writeTeachCoorMaxSpeed(double dbSpeed) override;

    // 读取最大允许位置速度（示教）
    int readTeachCoorMaxSpeed(double &dbSpeed) override;

    // 写入最大允许姿态速度（示教）
    int writeTeachMaxGuiseSpeed(double dbGuiseSpeed) override;

    // 读取最大允许姿态速度（示教）
    int readTeachMaxGuiseSpeed(double &dbGuiseSpeed) override;

    // 获取最大允许关节加速度（示教）
    int getTeachAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) override;

    // 保存最大允许关节加速度（示教）
    int saveTeachAxisMaxAcc(double jointAcc[AXIS_NUMB]) override;

    // 写入最大允许关节加速度（示教）
    int writeTeachAxisMaxAcc(AXIS_DBPARAM &AxisDbParam);

    // 读取最大允许关节加速度（示教）
    int readTeachAxisMaxAcc(AXIS_DBPARAM &AxisDbParam);

    // 写入最大允许位置加速度（示教）
    int writeTeachCoorMaxAcc(double dbAcc) override;

    // 读取最大允许位置加速度（示教）
    int readTeachCoorMaxAcc(double &dbAcc) override;

    // 写入最大允许姿态加速度（示教）
    int writeTeachMaxGuiseAcc(double dbGuiseAcc) override;

    // 读取最大允许姿态加速度（示教）
    int readTeachMaxGuiseAcc(double &dbGuiseAcc) override;

    ///******运行参数设置*******///
    // 获取最大允许关节速度（运动）
    int getAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) override;

    // 保存最大允许关节速度（运动）
    int saveAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) override;

    // 写入最大允许关节速度（运动）
    int writeAxisMaxSpeed(AXIS_DBPARAM &AxisDbParam);

    // 读取最大允许关节速度（运动）
    int readAxisMaxSpeed(AXIS_DBPARAM &AxisDbParam);

    // 写入最大允许位置速度（运动）
    int writeCoorMaxSpeed(double dbSpeed) override;

    // 读取最大允许位置速度（运动）
    int readCoorMaxSpeed(double &dbSpeed) override;

    // 写入最大允许姿态速度（运动）
    int writeMaxGuiseSpeed(double dbGuiseSpeed) override;

    // 读取最大允许姿态速度（运动）
    int readMaxGuiseSpeed(double &dbGuiseSpeed) override;

    // 获取最大允许关节加速度（运动）
    int getAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) override;

    // 保存最大允许关节加速度（运动）
    int saveAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) override;

    // 写入最大允许关节加速度（运动）
    int writeAxisMaxAcc(AXIS_DBPARAM &AxisDbParam);

    // 读取最大允许关节加速度（运动）
    int readAxisMaxAcc(AXIS_DBPARAM &AxisDbParam);

    // 写入最大允许位置加速度（运动）
    int writeCoorMaxAcc(double dbAcc) override;

    // 读取最大允许位置加速度（运动）
    int readCoorMaxAcc(double &dbAcc) override;

    // 写入最大允许姿态加速度（运动）
    int writeMaxGuiseAcc(double dbGuiseAcc) override;

    // 读取最大允许姿态加速度（运动）
    int readMaxGuiseAcc(double &dbGuiseAcc) override;

    // 获取最大允许关节减速度
    int getAxisMaxDec(double AxisDbParam[AXIS_NUMB]) override;

    // 保存最大允许关节减速度
    int saveAxisMaxDec(double AxisDbParam[AXIS_NUMB]) override;

    // 写入最大允许关节减速度
    int writeAxisMaxDec(AXIS_DBPARAM &AxisDbParam);

    // 读取最大允许关节减速度
    int ReadAxisMaxDec(AXIS_DBPARAM &AxisDbParam);

    // 写入最大允许位置减速度
    int writeCoorMaxDec(double dbStopDec) override;

    // 读取最大允许位置减速度
    int readCoorMaxDec(double &dbStopDec) override;

    // 写入最大允许姿态减速度
    int writeGuiseMaxDec(double dbGuiseStopDec) override;

    // 读取最大允许姿态减速度
    int readGuiseMaxDec(double &dbGuiseStopDec) override;

    // 写入过渡精度数据
    int writeTransJogDistan(double dbJoint, double dbPos, double dbAngle) override;

    // 读取过渡精度数据
    int readTransJogDistan(double &dbJoint, double &dbPos, double &dbAngle) override;

    ///******轴参数设置*******///
    bool checkPermissionBeforeSaveAxisParam() override;

    // 获取跟随误差
    int getErrPos(double posError[AXIS_NUM]) override;

    // 保存跟随误差
    int saveErrPos(double posError[AXIS_NUM]) override;

    // 写入跟随误差
    int writeErrPos(AXIS_DBPARAM &Param);

    // 读取跟随误差
    int readErrPos(AXIS_DBPARAM &Param);

    // 获取到位误差
    int getErrBand(double bandErr[AXIS_NUM]) override;

    // 保存到位误差
    int saveErrBand(double bandErr[AXIS_NUM]) override;

    // 写入到位误差
    int writeErrBand(AXIS_DBPARAM &Param);

    // 读取到位误差
    int readErrBand(AXIS_DBPARAM &Param);

    // 获取到位误差保持时间
    int getErrBandTime(double bandErrTime[AXIS_NUM]) override;

    // 保存到位误差保持时间
    int saveErrBandTime(double bandErrTime[AXIS_NUM]) override;

    // 写入到位误差保持时间
    int writeErrBandTime(AXIS_DBPARAM &Param);

    // 读取到位误差保持时间
    int readErrBandTime(AXIS_DBPARAM &Param);

    // 保存最大转矩限制(等同于电流限制)
    int saveTorqueLimit(int16u uSwitch, int IntValue[AXIS_NUM]) override;

    // 写入最大转矩限制(等同于电流限制)
    int writeTorqueLimit(int16u uSwitch, int IntValue[AXIS_NUM]);

    // 读取最大转矩限制(等同于电流限制)
    int readTorqueLimit(int16u &uSwitch, int IntValue[AXIS_NUM]) override;

    // 保存平均负载率限制值(最大值)
    int saveAvrLoadLimit(int16u uSwitch, int IntValue[AXIS_NUM]) override;

    // 写入平均负载率限制值(最大值)
    int writeAvrLoadLimit(int16u uSwitch, int IntValue[AXIS_NUM]);

    // 读取平均负载率限制值(最大值)
    int readAvrLoadLimit(int16u &uSwitch, int IntValue[AXIS_NUM]) override;

    // 写入过热率限制
    int writeOverHeatLimit(int16u uSwitch) override;

    // 读取过热率限制
    int readOverHeatLimit(int16u &uSwitch) override;

    // 写入过载率限制
    int writeOverLoadLimit(int16u uSwitch) override;

    // 读取过热率限制
    int readOverLoadLimit(int16u &uSwitch) override;

    // 是否支持过热率
    int readOverHeatSupportFlag(int16u &flag) override;

    ///******闭环振动设置*******///
    // 保存振动抑制模式
    int saveVibSuppressParam(int16u nCtrMode, int16u nErrSenMode) override;

    // 保存振动抑制模式
    int saveVibCtrMode(int16u nMode) override;

    // 陀螺仪报警等级
    int saveGryoErrSenMode(int16u nMode) override;

    // 读取振动抑制模式
    int ReadVibCtrMode(int16u &nMode) override;

    // 写入振动抑制模式
    int writeVibCtrMode(int16u nMode);

    // 读取陀螺仪报警等级
    int ReadGryoErrSenMode(int16u &nMode) override;

    // 写入振动抑制模式
    int writeGryoErrSenMode(int16u nMode);

    ///******力矩模型校正*******///
    // 开启力矩自动学习
    int startTorqueModelRectifyAutoLearn() override;

    // 读取学习状态和学习结果
    int readTorqueModelRectifyAutoLearnStatus(TorqueRectifyAutoLearnPara &status) override;

    // 读取力矩校正参数
    int readTorqueModelRectifyPara(double *paraArray) override;

    // 写入力矩校正参数
    int writeTorqueModelRectifyPara(double *paraArray);

    // 保存力矩校正参数
    int saveTorqueModelRectifyPara(double *paraArray) override;

    // 检查力矩校正权限
    bool checkTorqueModelRectifyPermission() override;

    ///******软浮动*******///
    // 写入软浮动参数
    int writeSoftMoveParm(int16s i16ParaIndex, SoftMovePara &param) override;

    // 读取软浮动参数
    int readSoftMoveParam(int16s i16ParaIndex, SoftMovePara &param, float actionLimit[3]) override;

    // 保存软浮动权限
    bool checkSaveSoftMovePermission() override;
#pragma endregion

#pragma region 工作空间
    ///******轴极限设置*******///
    // 获取正极限
    int getPosLimit(double posLimit[AXIS_NUMB]) override;

    // 读取正极限
    int ReadPosLimt(AXIS_DBPARAM &AxisDbParam);

    // 写入正极限
    int WritePosLimt(AXIS_DBPARAM &AxisDbParam);

    // 获取负极限
    int getNegLimit(double negLimit[AXIS_NUMB]) override;

    // 读取负极限
    int ReadNegLimt(AXIS_DBPARAM &AxisDbParam);

    // 写入负极限
    int WriteNegLimt(AXIS_DBPARAM &AxisDbParam);

    // 保存正极限和负极限
    int savePosLimitAndNegLimit(double posLimit[AXIS_NUMB], double negLimit[AXIS_NUMB]) override;

    ///******干涉区设置(24版本)*******///
    // 读取激活的干涉区标识
    int readActiveInterference(int16s &InterferenceFlag) override;

    // 写入激活的干涉区标识
    int writeActiveInterference(int16s InterferenceFlag) override;

    // 读取干涉区数据
    int readInterferenceRange(double interferenceData[64]) override;

    // 写入干涉区数据
    int writeInterferenceRange(double interferenceData[64]) override;

    // 检查干涉区的操作权限
    bool checkInterRangeOperatePermission() override;
#pragma endregion

#pragma region 伺服校验
    // 读取伺服校验状态：0-关 1-开
    int readServoCheck(int8u &nSwicth);

    // 写入伺服校验状态：0-关 1-开
    int writeServoCheck(int8u nSwicth);

    // 伺服校验状态权限检查
    bool checkServoCheckPermission();
#pragma endregion
};
}  // namespace InoRobBusiness
