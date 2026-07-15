#pragma once
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"
#include "InstallParameter/IInstallParameter.h"
#include "CrashDetection/ICrashDetection.h"
#include "InterferenceArea/IInterferenceArea.h"
#include "ZeroPoint/IZeroPoint.h"
#include "ZeroPointRepair/IZeroPointRepair.h"

namespace InoRobBusiness
{
// 0-start, 1-homing 2-success, 3-interrupt, 4-failed, -1-readError
typedef enum
{
    HOMINGSTS_COMM_ERR = -1,
    HOMINGSTS_START = 0,
    HOMINGSTS_HOMING = 1,
    HOMINGSTS_SUCCESS = 2,
    HOMINGSTS_INTERRUPT = 3,
    HOMINGSTS_FAILED = 4,
} E_HOMINGSTS;

typedef struct tagHomingRes
{
    tagHomingRes()
    {
        axis = 0;
        status = 0;
        zeroAbsPos[0] = 0;
        zeroAbsPos[1] = 0;
    }
    int16s axis;       /**< \brief homing aixs */
    int16s status;     /**< \brief 0-start, 1-homing 2-success, 3-interrupt, 4-failed */
    int zeroAbsPos[2]; /**< \brief homing zero position */
} ST_HOMING_RES;

typedef struct tagHomingSts
{
    tagHomingSts()
    {
        axis = 0;
        dir = 1;
        cmd = 0;
    }
    int16s axis; /**< \brief homing aixs<0~5> */
    int16s dir;  /**< \brief homing dir: -1-negetive, 1-position*/
    int16s cmd;  /**< \brief homing command: 0-stop, 1-start */
} ST_HOMING_OPT;

/*!
 * \brief 机械臂抽象类  机械臂也是我们常称作本体
 */
class INOROBBUSINESS_CLASS IRobotArm : public QObject
{
    Q_OBJECT
public:
    virtual ~IRobotArm()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    // 常用的权限检查
    virtual bool checkCommonPermission() = 0;

    // 检查控制器保存文件标志
    virtual bool checkFileSaveFlag() = 0;

    // 向ARM发送保存文件命令
    virtual void saveFileCommond(bool *ok = 0) = 0;

#pragma region 安装参数
    // 安装参数
    virtual IInstallParameter *GetInstallParam() = 0;
#pragma endregion

#pragma region 六关节零点校准
    virtual IZeroPoint *getZeroPoint() = 0;
#pragma endregion

#pragma region 六关节零点校准
    virtual IZeroPointRepair *getZeroPointRepair() = 0;
#pragma endregion

    // 获取机械臂最大轴数
    virtual int8u getMaxAxisNum() = 0;

#pragma region 绝对零点

    // 获取当前绝对零点值
    virtual int getAbsZeroValue(double absZero[AXIS_NUM]) = 0;

    // 获取当前电机位置
    virtual int getCurrMotorPos(double motorPos[AXIS_NUM]) = 0;

    // 保存绝对零点值至控制器
    virtual int saveAbsZeroValue(double absZero[AXIS_NUM]) = 0;

    //重置绝对零点
    virtual int resetAbsZeroValue(uint16_t u16AxisNo) = 0;

    //获取重置绝对零结果
    virtual int getResetAbsZeroValue(uint16_t u16AxisNo,uint16_t &result) = 0;

    //获取七轴拖动示教状态
    virtual int getSevenDragSwitchTeaching() = 0;

    //设置七轴拖动示教状态
    virtual int setSevenDragSwitchTeaching(int nType) = 0;

    //七轴取点
    virtual int setSevenTakePoint() = 0;

#pragma endregion

#pragma region 工作原点

    // 从控制器中读取工作原点
    virtual int ReadWorkOriginPts(JPos &JAndEData, UINT ulIndx) = 0;

    // 将工作原点写入控制器中
    virtual int WriteWorkOriginPts(JPos &JAndEData, UINT ulIndx) = 0;

    // 保存工作原点的数据
    virtual int saveWorkOriginData(double jPoint[JOINT_AXIS_NUM], double ePoint[EXT_AXIS_NUM], UINT ulIndex) = 0;

    // 保存工作原点前的权限检查
    virtual bool checkPermissionBeforeSaveWorkOrigin() = 0;

    // 运动到点
    virtual bool moveToPoint(JPos jPos, std::string originName) = 0;

    // 停止运动
    virtual bool stopMoveToPoint() = 0;

#pragma endregion

#pragma region 回零校准

    // 读工厂回零操作记录（0-无记录，不允许进入回零模式 1-有记录）
    virtual int readFactoryHomingRecord(int16s posRecordFlag[6]) = 0;

    // read Enconder multi circle sts:  iAxisNo:current axisNo; nSts:0-not over; 1-over
    // 读取编码器多圈状态 轴号 状态 0-圈数过多   1-圈数不过多
    virtual int readEncodeMultiCircle(int16s iAxisNo, int &nSts) = 0;

    // 模式设置
    virtual int setMode(MODE_TYPE nMode) = 0;

    // 获取使能状态 1-使能 0-非使能
    virtual int16u getEnableState() = 0;

    // 调控回零模式
    virtual int changedHomeModeWhenSetHome(int &runMode, int currAxisNo) = 0;

    // 启动回零功能
    virtual bool startHoming(int16s axisNo, int currMode) = 0;

    // 停止回零
    virtual bool stopHoming(int16s axisNo) = 0;

    // 读取绝对零点位置
    virtual int ReadAbsZero(double dValue[AXIS_NUM]) = 0;

    // 读取回零状态
    virtual int ReadHomingSts(ST_HOMING_RES &theReslut) = 0;

    // 获取回零状态
    virtual E_HOMINGSTS getHomingState(int16s axisNo) = 0;

    // 应用校准值
    virtual bool applyCalibValue(double writeValue[AXIS_NUM]) = 0;

    // 应用校准前的权限检查
    virtual bool checkPermissionBeforeSaveCalibValue() = 0;

    // 获取测试模式
    virtual int getTestMode() = 0;

    // 获取回零模式
    virtual int getHomeMode() = 0;

    // 读取参数重置中的偏移值
    virtual int ReadHomeOffset(int posOffset[6]) = 0;

    // 保存参数重置中的偏移值
    virtual int savePosOffset(int posOffset[6]) = 0;

    // 检查修改权限
    virtual bool CheckModifyPermission() = 0;

    // nMark: 1-save, 0-No parameter need save //ARM收到1之后进行保存，完成保存置0, 错误置-1
    virtual int readFileSaveFlag(int &nMark) = 0;

    // 参数配置文件保存标示
    virtual int writeFileSaveFlag(int nMark) = 0;

    /**
     * @brief 启动回零前权限和模式检查
     * @param 当前的运行模式
     * @param 当前回零的轴号
     * @return 0-成功, -1-权限不足, -2-进入回零模式失败, -3-当前模式不正确
     */
    virtual int checkPermissionBeforeStartHome() = 0;

#pragma endregion

#pragma region 机器人设置
    // 获取当前机型
    virtual RBTTYPE_E getRobotType() = 0;

    // 读取结构参数 工业
    virtual int getRotbotStructParameters(double structParams[LINK_PARM_NUM]) = 0;
    // 读取结构参数 协作
    virtual int getCoRotbotStructParameters(std::vector<double> &data) = 0;

    // 保存机器人结构参数 工业
    virtual int saveRobotStructParam(double structParams[LINK_PARM_NUM]) = 0;

    // 保存机器人结构参数 协作
    virtual int saveCoRobotStructParam(const vector<double> &data, bool autoSaveFileCommd = true) = 0;

    // 保存机器人的减速比
    virtual int saveRobotReductionRatioParam(double reduRatio[AXIS_NUMB], bool autoSaveFileCommd = true) = 0;

    // 保存机器人耦合参数
    virtual int saveRobotCouplingParam(double coupParam[AXIS_NUMB * 2], bool autoSaveFileCommd = true) = 0;

    // 保存机器人内部补偿参数
    virtual int saveRobotCompensationParam(double compParam[COM_PARM_NUM], bool autoSaveFileCommd = true) = 0;

    // 获取轴的数量
    virtual int getAxiCount() = 0;

    // 读取减速比参数
    virtual int getReductionRatioParam(double reduRatio[AXIS_NUMB]) = 0;

    // 获取耦合参数
    virtual int getCouplingParam(double coupParaM[AXIS_NUMB], double coupParaS[AXIS_NUMB]) = 0;

    // 获取内部补偿参数
    virtual int getRobotCompParam(double compParam[COM_PARM_NUM]) = 0;

    // 保存安装姿态
    virtual int writeRobotInstallParam(double param[16]) = 0;

    // 七轴机器人参数
    virtual int getSevenRobotStructParameters(std::vector<double> &data) = 0;

    // 七轴机器人参数
    virtual int saveSevenRobotStructParam(std::vector<double> &data, bool autoSaveFileCommd = true) = 0;

#pragma endregion

#pragma region 运动参数
    // 检查运动参数的保存权限
    virtual bool checkPermissionBeforeSaveMotionParam() = 0;

    ///******示教参数设置*******///
    // 保存寸动步长
    virtual int saveJogDistan(double dbJoint, double dbPos, double dbAngle) = 0;

    // 读取寸动步长
    virtual int readJogDistan(double &dbJoint, double &dbPos, double &dbAngle) = 0;

    // 写入最大允许位置速度（示教）
    virtual int writeTeachCoorMaxSpeed(double dbSpeed) = 0;

    // 写入最大允许姿态速度（示教）
    virtual int writeTeachMaxGuiseSpeed(double dbGuiseSpeed) = 0;

    // 保存最大允许关节速度（示教）
    virtual int saveTeachAxisMaxSpeed(double jointSpeed[AXIS_NUMB]) = 0;

    // 获取最大允许关节速度（示教）
    virtual int getTeachAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) = 0;

    // 读取最大允许位置速度（示教）
    virtual int readTeachCoorMaxSpeed(double &dbSpeed) = 0;

    // 读取最大允许姿态速度（示教）
    virtual int readTeachMaxGuiseSpeed(double &dbGuiseSpeed) = 0;

    // 保存最大允许关节加速度（示教）
    virtual int saveTeachAxisMaxAcc(double jointAcc[AXIS_NUMB]) = 0;

    // 写入最大允许位置加速度（示教）
    virtual int writeTeachCoorMaxAcc(double dbAcc) = 0;

    // 写入最大允许姿态加速度（示教）
    virtual int writeTeachMaxGuiseAcc(double dbGuiseAcc) = 0;

    // 获取最大允许关节加速度（示教）
    virtual int getTeachAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) = 0;

    // 读取最大允许位置加速度（示教）
    virtual int readTeachCoorMaxAcc(double &dbAcc) = 0;

    // 读取最大允许姿态加速度（示教）
    virtual int readTeachMaxGuiseAcc(double &dbGuiseAcc) = 0;

    ///******运行参数设置*******///
    // 获取最大允许关节速度（运动）
    virtual int getAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) = 0;

    // 读取最大允许位置速度（运动）
    virtual int readCoorMaxSpeed(double &dbSpeed) = 0;

    // 读取最大允许姿态速度（运动）
    virtual int readMaxGuiseSpeed(double &dbGuiseSpeed) = 0;

    // 保存最大允许关节速度（运动）
    virtual int saveAxisMaxSpeed(double AxisDbParam[AXIS_NUM]) = 0;

    // 写入最大允许位置速度（运动）
    virtual int writeCoorMaxSpeed(double dbSpeed) = 0;

    // 写入最大允许姿态速度（运动）
    virtual int writeMaxGuiseSpeed(double dbGuiseSpeed) = 0;

    // 获取最大允许关节加速度（运动）
    virtual int getAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) = 0;

    // 保存最大允许关节加速度（运动）
    virtual int saveAxisMaxAcc(double AxisDbParam[AXIS_NUMB]) = 0;

    // 读取最大允许位置加速度（运动）
    virtual int readCoorMaxAcc(double &dbAcc) = 0;

    // 读取最大允许姿态加速度（运动）
    virtual int readMaxGuiseAcc(double &dbGuiseAcc) = 0;

    // 写入最大允许位置加速度（运动）
    virtual int writeCoorMaxAcc(double dbAcc) = 0;

    // 写入最大允许姿态加速度（运动）
    virtual int writeMaxGuiseAcc(double dbGuiseAcc) = 0;

    // 获取最大允许关节减速度
    virtual int getAxisMaxDec(double AxisDbParam[AXIS_NUMB]) = 0;

    // 读取最大允许位置减速度
    virtual int readCoorMaxDec(double &dbStopDec) = 0;

    // 读取最大允许姿态减速度
    virtual int readGuiseMaxDec(double &dbGuiseStopDec) = 0;

    // 保存最大允许关节减速度
    virtual int saveAxisMaxDec(double AxisDbParam[AXIS_NUMB]) = 0;

    // 写入最大允许位置减速度
    virtual int writeCoorMaxDec(double dbStopDec) = 0;

    // 写入最大允许姿态减速度
    virtual int writeGuiseMaxDec(double dbGuiseStopDec) = 0;

    // 写入过渡精度数据
    virtual int writeTransJogDistan(double dbJoint, double dbPos, double dbAngle) = 0;

    // 读取过渡精度数据
    virtual int readTransJogDistan(double &dbJoint, double &dbPos, double &dbAngle) = 0;

    ///******轴参数设置*******///
    // 轴参数权限检查
    virtual bool checkPermissionBeforeSaveAxisParam() = 0;

    // 获取跟随误差
    virtual int getErrPos(double posError[AXIS_NUM]) = 0;

    // 保存跟随误差
    virtual int saveErrPos(double posError[AXIS_NUM]) = 0;

    // 获取到位误差
    virtual int getErrBand(double bandErr[AXIS_NUM]) = 0;

    // 保存到位误差
    virtual int saveErrBand(double bandErr[AXIS_NUM]) = 0;

    // 获取到位误差保持时间
    virtual int getErrBandTime(double bandErrTime[AXIS_NUM]) = 0;

    // 保存到位误差保持时间
    virtual int saveErrBandTime(double bandErrTime[AXIS_NUM]) = 0;

    // 读取最大转矩限制(等同于电流限制)
    virtual int readTorqueLimit(int16u &uSwitch, int IntValue[AXIS_NUM]) = 0;

    // 保存最大转矩限制(等同于电流限制)
    virtual int saveTorqueLimit(int16u uSwitch, int IntValue[AXIS_NUM]) = 0;

    // 保存平均负载率限制值(最大值)
    virtual int saveAvrLoadLimit(int16u uSwitch, int IntValue[AXIS_NUM]) = 0;

    // 读取平均负载率限制值(最大值)
    virtual int readAvrLoadLimit(int16u &uSwitch, int IntValue[AXIS_NUM]) = 0;

    // 写入过热率限制
    virtual int writeOverHeatLimit(int16u uSwitch) = 0;

    // 写入过载率限制
    virtual int writeOverLoadLimit(int16u uSwitch) = 0;

    // 读取过热率限制
    virtual int readOverHeatLimit(int16u &uSwitch) = 0;

    // 读取过载率限制
    virtual int readOverLoadLimit(int16u &uSwitch) = 0;

    // 是否支持温升保护
    virtual int readOverHeatSupportFlag(int16u &flag) = 0;

    ///******闭环振动设置*******///
    // 保存振动抑制模式
    virtual int saveVibSuppressParam(int16u nCtrMode, int16u nErrSenMode) = 0;

    // 保存振动抑制模式
    virtual int saveVibCtrMode(int16u nMode) = 0;

    // 陀螺仪报警等级
    virtual int saveGryoErrSenMode(int16u nMode) = 0;

    // 读取振动抑制模式
    virtual int ReadVibCtrMode(int16u &nMode) = 0;

    // 读取陀螺仪报警等级
    virtual int ReadGryoErrSenMode(int16u &nMode) = 0;

    ///******力矩模型校正*******///
    // 开启力矩自动学习
    virtual int startTorqueModelRectifyAutoLearn() = 0;

    // 读取学习状态和学习结果
    virtual int readTorqueModelRectifyAutoLearnStatus(TorqueRectifyAutoLearnPara &status) = 0;

    // 读取力矩校正参数
    virtual int readTorqueModelRectifyPara(double *paraArray) = 0;

    // 保存力矩校正参数
    virtual int saveTorqueModelRectifyPara(double *paraArray) = 0;

    // 检查力矩校正权限
    virtual bool checkTorqueModelRectifyPermission() = 0;

    ///******软浮动*******///
    // 写入软浮动参数
    virtual int writeSoftMoveParm(int16s i16ParaIndex, SoftMovePara &param) = 0;

    // 读取软浮动参数
    virtual int readSoftMoveParam(int16s i16ParaIndex, SoftMovePara &param, float actionLimit[3]) = 0;

    // 保存软浮动权限
    virtual bool checkSaveSoftMovePermission() = 0;
#pragma endregion

#pragma region 工作空间
    ///******轴极限设置*******///
    /*!
     * \brief 获取正向极限
     * \param posLimit 各轴的正极限
     * \return 0-获取成功
     */
    virtual int getPosLimit(double posLimit[AXIS_NUMB]) = 0;

    /*!
     * \brief 获取负极限
     * \param negLimit 各轴的负极限
     * \return 0-获取成功
     */
    virtual int getNegLimit(double negLimit[AXIS_NUMB]) = 0;

    /*!
     * \brief 保存设置的正极限和负极限
     * \param posLimit 各轴的正极限
     * \param negLimit 各轴的负极限
     * \return 0-保存成功
     */
    virtual int savePosLimitAndNegLimit(double posLimit[AXIS_NUMB], double negLimit[AXIS_NUMB]) = 0;

    ///******干涉区设置(24版本)*******///
    // 读取激活的干涉区标识
    virtual int readActiveInterference(int16s &InterferenceFlag) = 0;

    // 写入激活的干涉区标识
    virtual int writeActiveInterference(int16s InterferenceFlag) = 0;

    // 读取干涉区数据
    virtual int readInterferenceRange(double interferenceData[64]) = 0;

    // 写入干涉区数据
    virtual int writeInterferenceRange(double interferenceData[64]) = 0;

    // 检查干涉区的操作权限
    virtual bool checkInterRangeOperatePermission() = 0;

    /**
     * @brief 25版本干涉区
     * @return
     */
    virtual IInterferenceArea *getInterferenceArea() = 0;
#pragma endregion

#pragma region 伺服校验
    // 读取伺服校验状态：0-关 1-开
    virtual int readServoCheck(int8u &nSwicth) = 0;

    // 写入伺服校验状态：0-关 1-开
    virtual int writeServoCheck(int8u nSwicth) = 0;

    // 伺服校验状态权限检查
    virtual bool checkServoCheckPermission() = 0;
#pragma endregion

#pragma region 碰撞检测
    /**
     * @brief 碰撞检测
     */
    virtual ICrashDetection *getCrashDetectionObject() = 0;
#pragma endregion

signals:
    // 回零校准
    void errorInformation(string errInfo);
    void initialZeroData(int curZero1, int curZero2);
};
}  // namespace InoRobBusiness
