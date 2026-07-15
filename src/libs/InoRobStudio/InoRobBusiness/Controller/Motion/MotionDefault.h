#pragma once
#include "GlobalDataTypes.h"
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS MotionDefault : public IMotion
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *m_DataService = nullptr;
    // 连接
    IConnection *m_Connection = nullptr;
    // 监控
    IMonitor *m_Monitor = nullptr;
    // 控制器配置
    IRCConfig *m_RCConfig = nullptr;
    // 控制相关
    IControl *_pControl = nullptr;
    // 机器人参数
    IRobotArm *_pRobotArm = nullptr;

    ISafeIOAction *_pSafeIOAction = nullptr;

public:
    MotionDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~MotionDefault();
    void init() override;
#pragma endregion

#pragma region 安全IO动作
    ISafeIOAction *getSafeIOAction() const override;
#pragma endregion

#pragma region 速度设置

public:
    virtual bool checkSetSpeedStatus() override;
    bool SetSpeed(int16u speed, bool isCheckEnableAndMode = true);

private:
    bool checkDeviceModeAboutSpeed();

#pragma endregion

#pragma region 寸动

private:
    // 读运动参数
    bool ReadMotionParam(MOTION_PARAM &param);
    // 写运动参数
    bool WriteMotionParam(MOTION_PARAM param);

public:
    bool SetMoveStepGrade(MoveStepGrade grade);
    string MoveStepGradeName(MoveStepGrade grade);
    bool GetMoveStepSizePara(MoveStepSizePara &para);
    bool SetMoveStepSizePara(MoveStepSizePara para);

#pragma endregion

#pragma region 通用

private:
    // 是否运动到点进行中（决定异步命令线程是否轮循判断运动到点结果）
    bool m_IsMoveToPoint;
    // 运动到点的类型
    MotionType m_MotionType;
    // 开始运动时间
    long long m_MoveToPointStartTime = 0;
    // 运动到点的最长允许时间（毫秒）
    int32u m_MoveToPointMaxTime;
    // 当前是否处于视觉标定中
    bool m_IsVisionCalibrating;
    // 当前的运动状态
    MoveStatus _moveStatus = MoveStatus::DIRMOVSTS_BREAK;

public:
    int readMotionStatus(MotionStatus &status);
    MoveStatus GetMoveToPointStatus();
    string MoveStatusDescription(MoveStatus moveStatus);
    bool GetIsMoveToPoint();
    void OnMoveToPointComplete(MoveStatus status);
    virtual MoveStatus getMoveStatus() override;
    bool GetIsVisionCalibrating();
    void SetIsVisionCalibrating(bool isCalibrating);

#pragma endregion

#pragma region 运动到点

private:
    // 开始关节运动到点
    // jPos 关节值
    // motionType 运动类型
    bool JointMoveToPointStart(JPos jPos, MotionType motionType);
    // 停止运动到点
    // isPrintLog 是否打印成功日志
    // isVisionCalibration 是否来自视觉标定
    bool MoveToPointStop(bool isPrintLog, bool isVisionCalibration);

public:
    bool MovjToPointStart(RobPos robPos, int16u toolId, ReferObj referObj);
    bool MovlToPointStart(RobPos robPos, int16u toolId, ReferObj referObj);
    bool JumpToPointStart(RobPos robPos, int16u toolId, ReferObj referObj, double lh, double mh, double rh);
    bool JumplToPointStart(RobPos robPos, int16u toolId, ReferObj referObj, double lh, double mh, double rh);
    bool MoveToPointStart(MoveType moveType, RobPos robPos, int16u toolId, ReferObj referObj, double lh = 0.0, double mh = 0.0, double rh = 0.0);
    bool JointMoveToPointStart(JPos jPos);
    bool MoveToPointStop(bool isPrintLog = true);

#pragma endregion

#pragma region 视觉标定

public:
    bool JointMoveToPointStartWithVision(JPos jPos);
    bool MoveToPointStopWithVision(bool isPrintLog = true);

#pragma endregion

#pragma region 回零

public:
    bool JointMoveToZeroStart();
    bool JointMoveToZeroStop();

#pragma endregion

#pragma region 对准

private:
    CoordType m_AlignType;

public:
    bool AlignStart(CoordType alignType);
    bool AlignStop();

#pragma endregion

#pragma region 轴运动

private:
    bool _isForbidAxisMove = false;  // 是否拦截轴运动
    bool _isPrint = false;           // 是否打印拦截信息
    std::string _forbidHint = "";    // 拦截提示信息

public:
    bool AxisMoveStart(int axisNo, RotateDir turnDir);
    bool AxisMoveStop(int axisNo);
    bool AxisMove(int8u axisNo, RotateDir turnDir, PressState pressState);

    // 设置禁止轴运动标志和提示信息
    void setAxisMoveForbidFlagAndHint(bool isForbidAxisMove, bool isPrint, std::string hintStr);

    // 解除轴运动拦截
    void removeAxisMoveForbid();

#pragma endregion

#pragma region 奇异穿越
    bool getSingAreaHandleStatus() const override;
    bool setSingAreaHandleStatus(bool status) override;
#pragma endregion

#pragma region 拖动示教状态(协作)
    bool getDragTeachStatus() const override;
#pragma endregion
};
}  // namespace InoRobBusiness
