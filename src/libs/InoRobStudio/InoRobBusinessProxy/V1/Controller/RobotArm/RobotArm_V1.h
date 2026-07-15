#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "InstallParameter/InstallParam_V1.h"
#include "CrashDetection/CrashDetection_V1.h"
#include "InterferenceArea/InterferenceArea_V1.h"
#include "ZeroPoint/ZeroPoint_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
// 0-start, 1-homing 2-success, 3-interrupt, 4-failed, -1-readError
typedef enum
{
    HOMINGSTS_COMM_ERR_V1 = -1,
    HOMINGSTS_START_V1 = 0,
    HOMINGSTS_HOMING_V1 = 1,
    HOMINGSTS_SUCCESS_V1 = 2,
    HOMINGSTS_INTERRUPT_V1 = 3,
    HOMINGSTS_FAILED_V1 = 4,
} E_HOMINGSTS_V1;

typedef struct tagHomingRes_V1
{
    tagHomingRes_V1()
    {
        axis = 0;
        status = 0;
        zeroAbsPos[0] = 0;
        zeroAbsPos[1] = 0;
    }
    int16s axis;       /**< \brief homing aixs */
    int16s status;     /**< \brief 0-start, 1-homing 2-success, 3-interrupt, 4-failed */
    int zeroAbsPos[2]; /**< \brief homing zero position */
} ST_HOMING_RES_V1;

typedef struct tagHomingSts_V1
{
    tagHomingSts_V1()
    {
        axis = 0;
        dir = 1;
        cmd = 0;
    }
    int16s axis; /**< \brief homing aixs<0~5> */
    int16s dir;  /**< \brief homing dir: -1-negetive, 1-position*/
    int16s cmd;  /**< \brief homing command: 0-stop, 1-start */
} ST_HOMING_OPT_V1;

class INOROBBUSINESSPROXY_CLASS RobotArm_V1
{
#pragma region 数据转换

public:
    E_HOMINGSTS_V1 E_HOMINGSTS_ToProxy(E_HOMINGSTS e_HOMINGSTS);
    E_HOMINGSTS E_HOMINGSTS_FromProxy(E_HOMINGSTS_V1 e_HOMINGSTS_V1);

    bool ST_HOMING_RES_ToProxy(const ST_HOMING_RES &st_HOMING_RES, ST_HOMING_RES_V1 &st_HOMING_RES_V1);
    bool ST_HOMING_RES_FromProxy(const ST_HOMING_RES_V1 &st_HOMING_RES_V1, ST_HOMING_RES &st_HOMING_RES);

    bool ST_HOMING_OPT_ToProxy(const ST_HOMING_OPT &st_HOMING_OPT, ST_HOMING_OPT_V1 &st_HOMING_OPT_V1);
    bool ST_HOMING_OPT_FromProxy(const ST_HOMING_OPT_V1 &st_HOMING_OPT_V1, ST_HOMING_OPT &st_HOMING_OPT);

#pragma endregion

#pragma region 构造与析构

private:
    IRobotArm *_robotArm = nullptr;

public:
    RobotArm_V1(IRobotArm *robotArm);
    ~RobotArm_V1();

#pragma endregion

#pragma region 子模型

private:
    InstallParam_V1 *_installParam_V1 = nullptr;
    ZeroPoint_V1 *_zeroPoint_V1 = nullptr;
    InterferenceArea_V1 *_interferenceArea_V1 = nullptr;
    CrashDetection_V1 *_crashDetection_V1 = nullptr;

public:
    // 安装参数
    InstallParam_V1 *GetInstallParam();
    bool SetInstallParam(InstallParam_V1 *installParam_V1);
    // 六关节零点校准
    ZeroPoint_V1 *getZeroPoint();
    bool SetZeroPoint(ZeroPoint_V1 *zeroPoint_V1);
    // 25版本干涉区
    InterferenceArea_V1 *getInterferenceArea();
    bool SetInterferenceArea(InterferenceArea_V1 *interferenceArea_V1);
    // 碰撞检测
    CrashDetection_V1 *getCrashDetectionObject();
    bool SetCrashDetectionObject(CrashDetection_V1 *crashDetection_V1);

#pragma endregion

#pragma region 业务逻辑（未分类）

public:
    // 常用的权限检查
    bool checkCommonPermission();

    // 检查控制器保存文件标志
    bool checkFileSaveFlag();

    // 向ARM发送保存文件命令
    void saveFileCommond(bool *ok = 0);

#pragma endregion

public:
    // 获取机械臂最大轴数
    int8u getMaxAxisNum();  //  --  已测

#pragma region 绝对零点

public:
    // 获取当前绝对零点值
    int getAbsZeroValue(double absZero[AXIS_NUM_V1]);

    // 获取当前电机位置
    int getCurrMotorPos(double motorPos[AXIS_NUM_V1]);

    // 保存绝对零点值至控制器
    int saveAbsZeroValue(double absZero[AXIS_NUM_V1]);

#pragma endregion

#pragma region 工作原点

public:
    // 从控制器中读取工作原点
    int ReadWorkOriginPts(JPos_V1 &JAndEData, UINT ulIndx);

    // 将工作原点写入控制器中
    int WriteWorkOriginPts(JPos_V1 &JAndEData, UINT ulIndx);

    // 保存工作原点的数据
    int saveWorkOriginData(double jPoint[JOINT_AXIS_NUM_V1], double ePoint[EXT_AXIS_NUM_V1], UINT ulIndex);

    // 保存工作原点前的权限检查
    bool checkPermissionBeforeSaveWorkOrigin();

    // 运动到点
    bool moveToPoint(JPos_V1 jPos, std::string originName);

    // 停止运动
    bool stopMoveToPoint();

#pragma endregion

#pragma region 回零校准

public:
    // 读工厂回零操作记录（0-无记录，不允许进入回零模式 1-有记录）
    int readFactoryHomingRecord(int16s posRecordFlag[6]);

    // read Enconder multi circle sts:  iAxisNo:current axisNo; nSts:0-not over; 1-over
    // 读取编码器多圈状态 轴号 状态 0-圈数过多   1-圈数不过多
    int readEncodeMultiCircle(int16s iAxisNo, int &nSts);

    // 模式设置
    int setMode(MODE_TYPE_V1 nMode);

    // 获取使能状态 1-使能 0-非使能
    int16u getEnableState();

    // 调控回零模式
    int changedHomeModeWhenSetHome(int &runMode, int currAxisNo);

    // 启动回零功能
    bool startHoming(int16s axisNo, int currMode);

    // 停止回零
    bool stopHoming(int16s axisNo);

    // 读取绝对零点位置
    int ReadAbsZero(double dValue[AXIS_NUM_V1]);

    // 读取回零状态
    int ReadHomingSts(ST_HOMING_RES_V1 &theReslut);

    // 获取回零状态
    E_HOMINGSTS_V1 getHomingState(int16s axisNo);

    // 应用校准值
    bool applyCalibValue(double writeValue[AXIS_NUM_V1]);

    // 应用校准前的权限检查
    bool checkPermissionBeforeSaveCalibValue();

    // 获取测试模式
    int getTestMode();

    // 获取回零模式
    int getHomeMode();

    // 读取参数重置中的偏移值
    int ReadHomeOffset(int posOffset[6]);

    // 保存参数重置中的偏移值
    int savePosOffset(int posOffset[6]);

    // 检查修改权限
    bool CheckModifyPermission();

    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    int readFileSaveFlag(int &nMark);

    // 参数配置文件保存标示
    int writeFileSaveFlag(int nMark);

    /**
     * @brief 启动回零前权限和模式检查
     * @param 当前的运行模式
     * @param 当前回零的轴号
     * @return 0-成功, -1-权限不足, -2-进入回零模式失败, -3-当前模式不正确
     */
    int checkPermissionBeforeStartHome();

#pragma endregion

#pragma region 机器人设置

public:
    // 获取当前机型
    RBTTYPE_E_V1 getRobotType();

    // 读取结构参数 工业
    int getRotbotStructParameters(double structParams[LINK_PARM_NUM_V1]);

    // 读取结构参数 协作
    int getCoRotbotStructParameters(std::vector<double> &data);

    // 保存机器人结构参数 工业
    int saveRobotStructParam(double structParams[LINK_PARM_NUM_V1]);

    // 保存机器人结构参数 协作
    int saveCoRobotStructParam(const vector<double> &data, bool autoSaveFileCommd = true);

    // 保存机器人的减速比
    int saveRobotReductionRatioParam(double reduRatio[AXIS_NUMB_V1], bool autoSaveFileCommd = true);

    // 保存机器人耦合参数
    int saveRobotCouplingParam(double coupParam[AXIS_NUMB_V1 * 2], bool autoSaveFileCommd = true);

    // 保存机器人内部补偿参数
    int saveRobotCompensationParam(double compParam[COM_PARM_NUM_V1], bool autoSaveFileCommd = true);

    // 获取轴的数量
    int getAxiCount();

    // 读取减速比参数
    int getReductionRatioParam(double reduRatio[AXIS_NUMB_V1]);

    // 获取耦合参数
    int getCouplingParam(double coupParaM[AXIS_NUMB_V1], double coupParaS[AXIS_NUMB_V1]);

    // 获取内部补偿参数
    int getRobotCompParam(double compParam[COM_PARM_NUM_V1]);

#pragma endregion

#pragma region 运动参数

public:
    // 检查运动参数的保存权限
    bool checkPermissionBeforeSaveMotionParam();

    ///******示教参数设置*******///
    // 保存寸动步长
    int saveJogDistan(double dbJoint, double dbPos, double dbAngle);

    // 读取寸动步长
    int readJogDistan(double &dbJoint, double &dbPos, double &dbAngle);

    // 写入最大允许位置速度（示教）
    int writeTeachCoorMaxSpeed(double dbSpeed);

    // 写入最大允许姿态速度（示教）
    int writeTeachMaxGuiseSpeed(double dbGuiseSpeed);

    // 保存最大允许关节速度（示教）
    int saveTeachAxisMaxSpeed(double jointSpeed[AXIS_NUMB_V1]);

    // 获取最大允许关节速度（示教）
    int getTeachAxisMaxSpeed(double AxisDbParam[AXIS_NUM_V1]);

    // 读取最大允许位置速度（示教）
    int readTeachCoorMaxSpeed(double &dbSpeed);

    // 读取最大允许姿态速度（示教）
    int readTeachMaxGuiseSpeed(double &dbGuiseSpeed);

    // 保存最大允许关节加速度（示教）
    int saveTeachAxisMaxAcc(double jointAcc[AXIS_NUMB_V1]);

    // 写入最大允许位置加速度（示教）
    int writeTeachCoorMaxAcc(double dbAcc);

    // 写入最大允许姿态加速度（示教）
    int writeTeachMaxGuiseAcc(double dbGuiseAcc);

    // 获取最大允许关节加速度（示教）
    int getTeachAxisMaxAcc(double AxisDbParam[AXIS_NUMB_V1]);

    // 读取最大允许位置加速度（示教）
    int readTeachCoorMaxAcc(double &dbAcc);

    // 读取最大允许姿态加速度（示教）
    int readTeachMaxGuiseAcc(double &dbGuiseAcc);

    ///******运行参数设置*******///
    // 获取最大允许关节速度（运动）
    int getAxisMaxSpeed(double AxisDbParam[AXIS_NUM_V1]);

    // 读取最大允许位置速度（运动）
    int readCoorMaxSpeed(double &dbSpeed);

    // 读取最大允许姿态速度（运动）
    int readMaxGuiseSpeed(double &dbGuiseSpeed);

    // 保存最大允许关节速度（运动）
    int saveAxisMaxSpeed(double AxisDbParam[AXIS_NUM_V1]);

    // 写入最大允许位置速度（运动）
    int writeCoorMaxSpeed(double dbSpeed);

    // 写入最大允许姿态速度（运动）
    int writeMaxGuiseSpeed(double dbGuiseSpeed);

    // 获取最大允许关节加速度（运动）
    int getAxisMaxAcc(double AxisDbParam[AXIS_NUMB_V1]);

    // 保存最大允许关节加速度（运动）
    int saveAxisMaxAcc(double AxisDbParam[AXIS_NUMB_V1]);

    // 读取最大允许位置加速度（运动）
    int readCoorMaxAcc(double &dbAcc);

    // 读取最大允许姿态加速度（运动）
    int readMaxGuiseAcc(double &dbGuiseAcc);

    // 写入最大允许位置加速度（运动）
    int writeCoorMaxAcc(double dbAcc);

    // 写入最大允许姿态加速度（运动）
    int writeMaxGuiseAcc(double dbGuiseAcc);

    // 获取最大允许关节减速度
    int getAxisMaxDec(double AxisDbParam[AXIS_NUMB_V1]);

    // 读取最大允许位置减速度
    int readCoorMaxDec(double &dbStopDec);

    // 读取最大允许姿态减速度
    int readGuiseMaxDec(double &dbGuiseStopDec);

    // 保存最大允许关节减速度
    int saveAxisMaxDec(double AxisDbParam[AXIS_NUMB_V1]);

    // 写入最大允许位置减速度
    int writeCoorMaxDec(double dbStopDec);

    // 写入最大允许姿态减速度
    int writeGuiseMaxDec(double dbGuiseStopDec);

    // 写入过渡精度数据
    int writeTransJogDistan(double dbJoint, double dbPos, double dbAngle);

    // 读取过渡精度数据
    int readTransJogDistan(double &dbJoint, double &dbPos, double &dbAngle);

    ///******轴参数设置*******///
    // 轴参数权限检查
    bool checkPermissionBeforeSaveAxisParam();

    // 获取跟随误差
    int getErrPos(double posError[AXIS_NUM_V1]);

    // 保存跟随误差
    int saveErrPos(double posError[AXIS_NUM_V1]);

    // 获取到位误差
    int getErrBand(double bandErr[AXIS_NUM_V1]);

    // 保存到位误差
    int saveErrBand(double bandErr[AXIS_NUM_V1]);

    // 获取到位误差保持时间
    int getErrBandTime(double bandErrTime[AXIS_NUM_V1]);

    // 保存到位误差保持时间
    int saveErrBandTime(double bandErrTime[AXIS_NUM_V1]);

    // 读取最大转矩限制(等同于电流限制)
    int readTorqueLimit(int16u &uSwitch, int IntValue[AXIS_NUM_V1]);

    // 保存最大转矩限制(等同于电流限制)
    int saveTorqueLimit(int16u uSwitch, int IntValue[AXIS_NUM_V1]);

    // 保存平均负载率限制值(最大值)
    int saveAvrLoadLimit(int16u uSwitch, int IntValue[AXIS_NUM_V1]);

    // 读取平均负载率限制值(最大值)
    int readAvrLoadLimit(int16u &uSwitch, int IntValue[AXIS_NUM_V1]);

    // 写入过热率限制
    int writeOverHeatLimit(int16u uSwitch);

    // 写入过载率限制
    int writeOverLoadLimit(int16u uSwitch);

    // 读取过热率限制
    int readOverHeatLimit(int16u &uSwitch);

    // 读取过载率限制
    int readOverLoadLimit(int16u &uSwitch);

    // 是否支持温升保护
    int readOverHeatSupportFlag(int16u &flag);

    ///******闭环振动设置*******///
    // 保存振动抑制模式
    int saveVibSuppressParam(int16u nCtrMode, int16u nErrSenMode);

    // 保存振动抑制模式
    int saveVibCtrMode(int16u nMode);

    // 陀螺仪报警等级
    int saveGryoErrSenMode(int16u nMode);

    // 读取振动抑制模式
    int ReadVibCtrMode(int16u &nMode);

    // 读取陀螺仪报警等级
    int ReadGryoErrSenMode(int16u &nMode);

    ///******力矩模型校正*******///
    // 开启力矩自动学习
    int startTorqueModelRectifyAutoLearn();

    // 读取学习状态和学习结果
    int readTorqueModelRectifyAutoLearnStatus(TorqueRectifyAutoLearnPara_V1 &status);

    // 读取力矩校正参数
    int readTorqueModelRectifyPara(double *paraArray);

    // 保存力矩校正参数
    int saveTorqueModelRectifyPara(double *paraArray);

    // 检查力矩校正权限
    bool checkTorqueModelRectifyPermission();

    ///******软浮动*******///
    // 写入软浮动参数
    int writeSoftMoveParm(int16s i16ParaIndex, SoftMovePara_V1 &param);

    // 读取软浮动参数
    int readSoftMoveParam(int16s i16ParaIndex, SoftMovePara_V1 &param, float actionLimit[3]);

    // 保存软浮动权限
    bool checkSaveSoftMovePermission();

#pragma endregion

#pragma region 工作空间

public:
    ///******轴极限设置*******///
    /*!
     * \brief 获取正向极限
     * \param posLimit 各轴的正极限
     * \return 0-获取成功
     */
    int getPosLimit(double posLimit[AXIS_NUMB_V1]);

    /*!
     * \brief 获取负极限
     * \param negLimit 各轴的负极限
     * \return 0-获取成功
     */
    int getNegLimit(double negLimit[AXIS_NUMB_V1]);

    /*!
     * \brief 保存设置的正极限和负极限
     * \param posLimit 各轴的正极限
     * \param negLimit 各轴的负极限
     * \return 0-保存成功
     */
    int savePosLimitAndNegLimit(double posLimit[AXIS_NUMB_V1], double negLimit[AXIS_NUMB_V1]);

    ///******干涉区设置(24版本)*******///
    // 读取激活的干涉区标识
    int readActiveInterference(int16s &InterferenceFlag);

    // 写入激活的干涉区标识
    int writeActiveInterference(int16s InterferenceFlag);

    // 读取干涉区数据
    int readInterferenceRange(double interferenceData[64]);

    // 写入干涉区数据
    int writeInterferenceRange(double interferenceData[64]);

    // 检查干涉区的操作权限
    bool checkInterRangeOperatePermission();

#pragma endregion

    // 业务逻辑层无函数定义，故此处也不启用

    // 回零校准
    // void errorInformation(string errInfo);
    // void initialZeroData(int curZero1, int curZero2);
};
}  // namespace InoRobBusinessProxy
