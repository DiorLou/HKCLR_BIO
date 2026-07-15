#ifndef TRAJRECOVERYDEFINES_H
#define TRAJRECOVERYDEFINES_H

#pragma pack(1)
// 轨迹恢复阈值设置参数
typedef struct stCobotTrajRecoveryThreshold
{
    stCobotTrajRecoveryThreshold()
    {
        Initialize();
    }
    void Initialize()
    {
        f64TCPDistance = 0;
        f64TCPRotation = 0;
        f64ExternalDistance = 0;
        f64ExternalRotation = 0;
    }

    double f64TCPDistance;       // TCP距离
    double f64TCPRotation;       // TCP旋转
    double f64ExternalDistance;  // 外部轴距离
    double f64ExternalRotation;  // 外部轴旋转
} CobotTrajRecoveryThreshold;

// 轨迹恢复设置参数
typedef struct stCobotTrajRecoveryParam
{
    stCobotTrajRecoveryParam()
    {
        Initialize();
    }
    void Initialize()
    {
        i32Mode = 0;
    }

    int i32Mode;                               // 轨迹恢复与之设置模式
    CobotTrajRecoveryThreshold stManualParam;  // 位置模式下，手动阈值参数
    CobotTrajRecoveryThreshold stAutoParam;    // 位置模式下，自动阈值参数
} CobotTrajRecoveryParam;
#pragma pack()

#endif  // TRAJRECOVERYDEFINES_H
