#pragma once

enum InoMoveStepGrade {
    InoMoveStepGrade_None = 0,  // 关闭寸动（点动）
    InoMoveStepGrade_G1 = 1,    // 等级1（关节步长0.05°，位置步长0.05mm，姿态步长0.05°）
    InoMoveStepGrade_G2 = 2,    // 等级2（关节步长0.5°，位置步长0.5mm，姿态步长0.5°）
    InoMoveStepGrade_G3 = 3,    // 等级3（关节步长2.0°，位置步长2.0mm，姿态步长2.0°）
    InoMoveStepGrade_U = 4,     // 自定义
};

// 寸动步长参数
struct InoMoveStepSizePara {
    double JointSize;     // 关节步长(°)
    double PositionSize;  // 位置步长(mm)
    double PoseSize;      // 姿态步长(°)

    InoMoveStepSizePara()
    {
        JointSize = 0.01;
        PositionSize = 0.01;
        PoseSize = 0.01;
    }
};

enum TeachMode {
    TeachMode_Invalid = 0,
    TeachMode_Joint1,
    TeachMode_Joint2,
    TeachMode_Joint3,
    TeachMode_Joint4,
    TeachMode_Joint5,
    TeachMode_Joint6,
    TeachMode_Joint7,
    TeachMode_MovX,
    TeachMode_MovY,
    TeachMode_MovZ,
    TeachMode_RotX,
    TeachMode_RotY,
    TeachMode_RotZ
};
