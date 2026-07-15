#ifndef JPOS_H
#define JPOS_H

#include <cmath>

#pragma pack(1)

#define COBOT_EXT_AXIS_NUM (6)
#define COBOT_JOINT_AXIS_NUM (8)

// 机器人关节点
typedef struct stJointPos
{
    stJointPos()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        for (int i = 0; i < COBOT_JOINT_AXIS_NUM; i++)
        {
            JointData[i] = 0.0;
        }
        for (int i = 0; i < COBOT_EXT_AXIS_NUM; i++)
        {
            EPosData[i] = 0.0;
        }
    }

    stJointPos &operator=(const stJointPos &other)
    {
        for (int i = 0; i < COBOT_JOINT_AXIS_NUM; i++)
            this->JointData[i] = other.JointData[i];
        for (int i = 0; i < COBOT_EXT_AXIS_NUM; i++)
            this->EPosData[i] = other.EPosData[i];

        return (*this);
    }

    bool operator==(const stJointPos &other) const
    {
        for (int i = 0; i < COBOT_JOINT_AXIS_NUM; i++)
        {
            if (std::abs(this->JointData[i] - other.JointData[i]) > 0.000001)
            {
                return false;
            }
        }

        for (int i = 0; i < COBOT_EXT_AXIS_NUM; i++)
        {
            if (std::abs(this->EPosData[i] - other.EPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        return true;
    }

    double JointData[COBOT_JOINT_AXIS_NUM];  // J1-J8
    double EPosData[COBOT_EXT_AXIS_NUM];     // E1-E6
} JointPos;

#pragma pack() // 单字节对齐

#endif  // JPOS_H
