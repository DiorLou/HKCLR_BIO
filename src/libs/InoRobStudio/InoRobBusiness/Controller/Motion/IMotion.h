#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "SafeIOAction/ISafeIOAction.h"

/*
    运动
    Create by WuJian at 2022/6/13
    Update by WuJian at 2022/7/22 增加视觉标定相关逻辑
    Update by WuJian at 2023/7/27 合入速度与寸动功能
*/
namespace InoRobBusiness
{

#define MANUAL_MODE_DEFAULT_SPEED    1                // 手动模式下的默认速度
#define MANUAL_MODE_FULL_SPEED       100              // 自动模式下的全速100%
#define MAX_TIME_TURNOFF_SPEED_LIMIT (5 * 60 * 1000)  // 关闭限速且未上使能的最长保持时间（5分钟），仅作用于手动高速模式

/**
 * @brief 运动状态
 */
enum class MotionStatus : int
{
    // 运动完成
    MOTION_FINISHED = 0,
    // 正在运动
    MOTIONING,
    // 插补完成（不在运动中）
    IMPUTATION_FINISHED,
};

// 运动到点的状态
enum MoveStatus : int8s
{
    DIRMOVSTS_POSERR = -2,         // 直接运动点位解析失败
    DIRMOVSTS_SYSERR = -1,         // 直接运动状态异常（系统有报错）
    DIRMOVSTS_MOVING = 1,          // 直接运动中
    DIRMOVSTS_FINISH = 2,          // 直接运动完成
    DIRMOVSTS_BREAK = 3,           // 直接运动中断
    DIRMOVSTS_MAX_DIRMOV_STS = 4,  // 控制器最大枚举值标识
    DIRMOVSTS_TIMEOUT = 5,         // 超时（非控制器返回）
};

// 运动到点类型
enum MotionType
{
    MOTION_TYPE_POSITION = 1,  // 位置运动到点
    MOTION_TYPE_JOINT = 2,     // 关节运动到点
    MOTION_TYPE_ZERO = 3,      // 回零
    MOTION_TYPE_ALIGN = 4,     // 对准
    MOTION_TYPE_VISION = 5     // 视觉标定（关节）
};

/// <summary>
/// 旋转方向
/// </summary>
enum class RotateDir
{
    POSITIVE = 0,
    REVERSE,
};

/// <summary>
/// 按下状态
/// </summary>
enum class PressState
{
    BTN_DOWN = 1,
    BTN_UP = 0,
};

// 寸动步长参数
struct MoveStepSizePara
{
    double JointSize;     // 关节步长(°)
    double PositionSize;  // 位置步长(mm)
    double PoseSize;      // 姿态步长(°)

    MoveStepSizePara()
    {
        JointSize = 0.0;
        PositionSize = 0.0;
        PoseSize = 0.0;
    }
};

class INOROBBUSINESS_CLASS IMotion : public QObject
{
    Q_OBJECT

public:
    virtual ~IMotion()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
#pragma region 安全IO动作
    /**
     * @brief 获取安全IO动作对象
     */
    virtual ISafeIOAction *getSafeIOAction() const = 0;
#pragma endregion

#pragma region 通用
    /**
     * @brief 运动状态
     * @param status 运动状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int readMotionStatus(MotionStatus &status) = 0;

    // 获取当前运动到点的状态（实时获取）
    virtual MoveStatus GetMoveToPointStatus() = 0;
    // 运动到点状态描述
    virtual string MoveStatusDescription(MoveStatus moveStatus) = 0;

    // 是否正在执行运动到点
    virtual bool GetIsMoveToPoint() = 0;
    // 运动到点完成（自动判断并触发事件，注：模型外严禁调用）
    virtual void OnMoveToPointComplete(MoveStatus status) = 0;
    // 获取缓存中记录的机器人运动状态
    virtual MoveStatus getMoveStatus() = 0;

    // 获取当前视觉标定标识（true:当前正在进行视觉标定, false:当前未进行视觉标定）
    virtual bool GetIsVisionCalibrating() = 0;
    // 设置视觉标定标识（true:视觉标定中, false:未进行视觉标定）
    // 警告：当为视觉标定中时，会阻止其它一切运动，因此视觉标定标识务必及时重置
    virtual void SetIsVisionCalibrating(bool isCalibrating) = 0;

#pragma endregion

    /**
     * @brief 检查当前是否可以设置速度（无弹窗提示）
     */
    virtual bool checkSetSpeedStatus() = 0;

    /**
     * @brief 设置全局速度
     * @param speed 输入，速度（百分比）
     * @param isCheckEnableAndMode 输入，是否检查使能状态和设备模式（外部调用默认true即可，内部调用特殊情况下可为false）
     * @return 成功true，失败false
     */
    virtual bool SetSpeed(int16u speed, bool isCheckEnableAndMode = true) = 0;

#pragma region 寸动

    // 设置寸动等级
    virtual bool SetMoveStepGrade(MoveStepGrade grade) = 0;
    // 根据寸动等级枚举值获取对应的名称（注：不含MOVE_STEP_GRADE_NONE）
    virtual string MoveStepGradeName(MoveStepGrade grade) = 0;

    // 获取当前寸动步长参数
    virtual bool GetMoveStepSizePara(MoveStepSizePara &para) = 0;
    // 设置当前寸动步长参数
    // 注1：设置寸动步长参数在控制器中会写PF文件，写PF文件前需要一次交互进行确认，所有写PF文件的操作不允许并发需要互斥锁 from 张焱 at 2022/5/23
    // 注2：关于参数范围值，PC与示教器的处理不同，PC通过控制器返回的值进行范围验证 from 张焱 at 2022/5/23
    virtual bool SetMoveStepSizePara(MoveStepSizePara para) = 0;

#pragma endregion

#pragma region 运动到点

    // Movj 开始关节差补运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    virtual bool MovjToPointStart(RobPos robPos, int16u toolId, ReferObj referObj) = 0;

    // Movl 开始直线差补运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    virtual bool MovlToPointStart(RobPos robPos, int16u toolId, ReferObj referObj) = 0;

    // Jump 开始跳跃运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    virtual bool JumpToPointStart(RobPos robPos, int16u toolId, ReferObj referObj, double lh, double mh, double rh) = 0;

    // Jumpl 开始直线跳跃运动到点
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    virtual bool JumplToPointStart(RobPos robPos, int16u toolId, ReferObj referObj, double lh, double mh, double rh) = 0;

    // 开始直角运动到点
    // moveType 运动类型
    // robPos 目标点位置
    // toolId 工具号
    // referObj 参考对象（-2：Base，-1：flange，0至15：工件号）
    // lh，mh，rh Jump运动参数数值
    virtual bool MoveToPointStart(MoveType moveType, RobPos robPos, int16u toolId, ReferObj referObj, double lh = 0.0, double mh = 0.0, double rh = 0.0) = 0;

    // 开始关节运动到点
    // jPos 目标关节值
    virtual bool JointMoveToPointStart(JPos jPos) = 0;

    // 停止运动到点（含对运动到点、回零、对准的停止）
    // isPrintLog 是否打印成功日志
    virtual bool MoveToPointStop(bool isPrintLog = true) = 0;

#pragma endregion

#pragma region 视觉标定

    // 开始关节运动到点（视觉标定专用，注：建议视觉标定通过SetIsVisionCalibrating()避免与其它运动冲突）
    // jPos 目标关节值
    virtual bool JointMoveToPointStartWithVision(JPos jPos) = 0;

    // 停止运动到点（视觉标定专用）
    // isPrintLog 是否打印成功日志
    virtual bool MoveToPointStopWithVision(bool isPrintLog = true) = 0;

#pragma endregion

#pragma region 回零

    // 开始关节回零
    virtual bool JointMoveToZeroStart() = 0;

    // 停止关节回零
    virtual bool JointMoveToZeroStop() = 0;

#pragma endregion

#pragma region 对准

    // 开始对准
    virtual bool AlignStart(CoordType alignType) = 0;

    // 停止对准
    virtual bool AlignStop() = 0;

#pragma endregion

#pragma region 轴运动

    // 开始轴运动
    virtual bool AxisMoveStart(int axisNo, RotateDir turnDir) = 0;
    // 停止轴运动
    virtual bool AxisMoveStop(int axisNo) = 0;
    // 轴运动（开始/停止）
    // axisId:轴编号
    // turnDir:运动方向
    // pressState:运动/停止）
    virtual bool AxisMove(int8u axisId, RotateDir turnDir, PressState pressState) = 0;

    /**
     * @brief 设置禁止轴运动标志和提示信息
     * @param isForbidAxisMove 是否拦截轴运动
     * @param hintStr 拦截信息
     */
    virtual void setAxisMoveForbidFlagAndHint(bool isForbidAxisMove, bool isPrint, std::string hintStr) = 0;

    /**
     * @brief 解除轴运动拦截
     */
    virtual void removeAxisMoveForbid() = 0;

#pragma endregion

#pragma region 奇异穿越
    /**
     * @brief 与控制器通信 读取奇异穿越状态
     * @return true开启 false关闭
     * @note 由于奇异穿越并不属于实时数据，所以在某些情景下状态并不准确
     */
    virtual bool getSingAreaHandleStatus() const = 0;

    /**
     * @brief 与控制器通信 设置奇异穿越状态
     * @param status true开启 false关闭
     * @return true成功 false失败
     */
    virtual bool setSingAreaHandleStatus(bool status) = 0;
#pragma endregion

Q_SIGNALS:
    // 运动到点完成信号（包含运动到点、回零、对准）
    void moveToPointCompleted(MoveStatus status);

#pragma region 拖动示教状态(协作)
    /**
     * @brief 与控制器通信 读取拖动示教状态
     * @return true开启 false关闭
     */
    virtual bool getDragTeachStatus() const = 0;
#pragma endregion
};
}  // namespace InoRobBusiness
