#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../Monitor/Monitor_V1.h"
#include "../../GlobalDataTypes_V1.h"
#include "SafeIOAction/SafeIOAction_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 数据（结构体与枚举）

#define MANUAL_MODE_DEFAULT_SPEED_V1    1                // 手动模式下的默认速度
#define MAX_TIME_TURNOFF_SPEED_LIMIT_V1 (5 * 60 * 1000)  // 关闭限速且未上使能的最长保持时间（5分钟），仅作用于手动高速模式

/**
 * @brief 运动状态
 */
enum class MotionStatus_V1 : int
{
    // 运动完成
    MOTION_FINISHED_V1 = 0,
    // 正在运动
    MOTIONING_V1,
    // 插补完成（不在运动中）
    IMPUTATION_FINISHED_V1,
};

// 运动到点的状态
enum MoveStatus_V1 : int8s
{
    DIRMOVSTS_POSERR_V1 = -2,         // 直接运动点位解析失败
    DIRMOVSTS_SYSERR_V1 = -1,         // 直接运动状态异常（系统有报错）
    DIRMOVSTS_MOVING_V1 = 1,          // 直接运动中
    DIRMOVSTS_FINISH_V1 = 2,          // 直接运动完成
    DIRMOVSTS_BREAK_V1 = 3,           // 直接运动中断
    DIRMOVSTS_MAX_DIRMOV_STS_V1 = 4,  // 控制器最大枚举值标识
    DIRMOVSTS_TIMEOUT_V1 = 5,         // 超时（非控制器返回）
};

// 运动到点类型
enum MotionType_V1
{
    MOTION_TYPE_POSITION_V1 = 1,  // 位置运动到点
    MOTION_TYPE_JOINT_V1 = 2,     // 关节运动到点
    MOTION_TYPE_ZERO_V1 = 3,      // 回零
    MOTION_TYPE_ALIGN_V1 = 4,     // 对准
    MOTION_TYPE_VISION_V1 = 5     // 视觉标定（关节）
};

/// <summary>
/// 旋转方向
/// </summary>
enum class RotateDir_V1
{
    POSITIVE_V1 = 0,
    REVERSE_V1,
};

/// <summary>
/// 按下状态
/// </summary>
enum class PressState_V1
{
    BTN_DOWN_V1 = 1,
    BTN_UP_V1 = 0,
};

// 寸动步长参数
struct MoveStepSizePara_V1
{
    double JointSize;     // 关节步长(°)
    double PositionSize;  // 位置步长(mm)
    double PoseSize;      // 姿态步长(°)

    MoveStepSizePara_V1()
    {
        JointSize = 0.0;
        PositionSize = 0.0;
        PoseSize = 0.0;
    }
};

#pragma endregion

class INOROBBUSINESSPROXY_CLASS Motion_V1 : public QObject
{
    Q_OBJECT
#pragma region 数据转换

public:
    static MotionStatus_V1 MotionStatus_ToProxy(MotionStatus motionStatus);
    static MotionStatus MotionStatus_FromProxy(MotionStatus_V1 motionStatus_V1);

    static MoveStatus_V1 MoveStatus_ToProxy(MoveStatus moveStatus);
    static MoveStatus MoveStatus_FromProxy(MoveStatus_V1 moveStatus_V1);

    static MotionType_V1 MotionType_ToProxy(MotionType motionType);
    static MotionType MotionType_FromProxy(MotionType_V1 motionType_V1);

    static RotateDir_V1 RotateDir_ToProxy(RotateDir rotateDir);
    static RotateDir RotateDir_FromProxy(RotateDir_V1 rotateDir_V1);

    static PressState_V1 PressState_ToProxy(PressState pressState);
    static PressState PressState_FromProxy(PressState_V1 pressState_V1);

    static bool MoveStepSizePara_ToProxy(const MoveStepSizePara &moveStepSizePara, MoveStepSizePara_V1 &moveStepSizePara_V1);
    static bool MoveStepSizePara_FromProxy(const MoveStepSizePara_V1 &moveStepSizePara_V1, MoveStepSizePara &moveStepSizePara);

#pragma endregion

#pragma region 构造与析构

private:
    IMotion *_motion = nullptr;

public:
    Motion_V1(IMotion *motion);
    ~Motion_V1();

#pragma endregion

#pragma region 通用

private:
    void MoveToPointCompletedHandler(MoveStatus data);

public:
    /**
     * @brief 运动状态
     * @param status 运动状态
     * @return 成功返回0，其他请见错误码
     */
    int readMotionStatus(MotionStatus_V1 &status);

    // 获取当前运动到点的状态（实时获取）
    MoveStatus_V1 GetMoveToPointStatus();
    // 运动到点状态描述
    string MoveStatusDescription(MoveStatus_V1 moveStatus);

    // 是否正在执行运动到点
    bool GetIsMoveToPoint();
    // 运动到点完成信号（包含运动到点、回零、对准）
    rsignal<MoveStatus_V1> MoveToPointCompleted;
    // 获取缓存中记录的机器人运动状态
    MoveStatus_V1 getMoveStatus();

    // 获取当前视觉标定标识（true:当前正在进行视觉标定, false:当前未进行视觉标定）
    bool GetIsVisionCalibrating();
    // 设置视觉标定标识（true:视觉标定中, false:未进行视觉标定）
    // 警告：当为视觉标定中时，会阻止其它一切运动，因此视觉标定标识务必及时重置
    void SetIsVisionCalibrating(bool isCalibrating);

#pragma endregion

    /**
     * @brief 检查当前是否可以设置速度（无弹窗提示）
     */
    bool checkSetSpeedStatus();

    /**
     * @brief 设置全局速度
     * @param speed 输入，速度（百分比）
     * @param isCheckEnableAndMode 输入，是否检查使能状态和设备模式（外部调用默认true即可，内部调用特殊情况下可为false）
     * @return 成功true，失败false
     */
    bool SetSpeed(int16u speed, bool isCheckEnableAndMode = true);

#pragma region 寸动

    // 设置寸动等级
    bool SetMoveStepGrade(MoveStepGrade_V1 grade);
    // 根据寸动等级枚举值获取对应的名称（注：不含MOVE_STEP_GRADE_NONE）
    string MoveStepGradeName(MoveStepGrade_V1 grade);

    // 获取当前寸动步长参数
    bool GetMoveStepSizePara(MoveStepSizePara_V1 &para);
    // 设置当前寸动步长参数
    // 注1：设置寸动步长参数在控制器中会写PF文件，写PF文件前需要一次交互进行确认，所有写PF文件的操作不允许并发需要互斥锁 from 张焱 at 2022/5/23
    // 注2：关于参数范围值，PC与示教器的处理不同，PC通过控制器返回的值进行范围验证 from 张焱 at 2022/5/23
    bool SetMoveStepSizePara(MoveStepSizePara_V1 para);

#pragma endregion

#pragma region 运动到点

    // Movj 开始关节差补运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    bool MovjToPointStart(RobPos_V1 robPos, int16u toolId, ReferObj_V1 referObj);

    // Movl 开始直线差补运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    bool MovlToPointStart(RobPos_V1 robPos, int16u toolId, ReferObj_V1 referObj);

    // Jump 开始跳跃运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    bool JumpToPointStart(RobPos_V1 robPos, int16u toolId, ReferObj_V1 referObj, double lh, double mh, double rh);

    // Jumpl 开始直线跳跃运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    bool JumplToPointStart(RobPos_V1 robPos, int16u toolId, ReferObj_V1 referObj, double lh, double mh, double rh);

    // 开始直角运动到点
    // moveType 运动类型
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    bool MoveToPointStart(MoveType_V1 moveType, RobPos_V1 robPos, int16u toolId, ReferObj_V1 referObj, double lh = 0.0, double mh = 0.0, double rh = 0.0);

    // 开始关节运动到点
    // jPos 目标关节值
    bool JointMoveToPointStart(JPos_V1 jPos);

    // 停止运动到点（含对运动到点、回零、对准的停止）
    // isPrintLog 是否打印成功日志
    bool MoveToPointStop(bool isPrintLog = true);  //  --  已测

#pragma endregion

#pragma region 视觉标定

    // 开始关节运动到点（视觉标定专用，注：建议视觉标定通过SetIsVisionCalibrating()避免与其它运动冲突）
    // jPos 目标关节值
    bool JointMoveToPointStartWithVision(JPos_V1 jPos);

    // 停止运动到点（视觉标定专用）
    // isPrintLog 是否打印成功日志
    bool MoveToPointStopWithVision(bool isPrintLog = true);

#pragma endregion

#pragma region 回零

    // 开始关节回零
    bool JointMoveToZeroStart();

    // 停止关节回零
    bool JointMoveToZeroStop();

#pragma endregion

#pragma region 对准

    // 开始对准
    bool AlignStart(CoordType_V1 alignType);

    // 停止对准
    bool AlignStop();

#pragma endregion

#pragma region 轴运动

    // 开始轴运动
    bool AxisMoveStart(int axisNo, RotateDir_V1 turnDir);
    // 停止轴运动
    bool AxisMoveStop(int axisNo);
    // 轴运动（开始/停止）
    // axisId:轴编号
    // turnDir:运动方向
    // pressState:运动/停止）
    bool AxisMove(int8u axisId, RotateDir_V1 turnDir, PressState_V1 pressState);

#pragma endregion

#pragma region 奇异穿越
    /**
     * @brief 与控制器通信 读取奇异穿越状态
     * @return true开启 false关闭
     * @note 由于奇异穿越并不属于实时数据，所以在某些情景下状态并不准确
     */
    bool getSingAreaHandleStatus() const;

    /**
     * @brief 与控制器通信 设置奇异穿越状态
     * @param status true开启 false关闭
     * @return true成功 false失败
     */
    bool setSingAreaHandleStatus(bool status);
#pragma endregion

#pragma region 子模型

private:
    SafeIOAction_V1 *_safeIOAction_V1 = nullptr;

public:
    SafeIOAction_V1 *GetSafeIOAction();
    bool SetSafeIOAction(SafeIOAction_V1 *safeIOActionV1);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
