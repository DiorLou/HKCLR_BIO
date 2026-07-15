#pragma once
#include <QString>
#include <QVariant>

const int ARM_TYPE_COUNT = 4;
const int POSE_AXIS_COUNT = 6;
const int EXT_AXIS_COUNT = 6;
const int JOINT_AXIS_COUNT = 8;

const char POINT_FILE_FOLDER[] = "PalletInfo/";
const char CONTROLLER_POINT_FILE_DIR[] = "/robot/PalletInfo/";

const QString DEFAULT_ROBOT_POINT_FILE = "P.pts";

typedef struct InoJPos {
    double JointData[JOINT_AXIS_COUNT];  // J1-J8
    double EPosData[EXT_AXIS_COUNT];   // E1-E6
    InoJPos()
    {
        for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
            JointData[i] = 0;
        }
        for (int i = 0; i < EXT_AXIS_COUNT; i++) {
            EPosData[i] = 0;
        }
    }
    InoJPos(double JointData[JOINT_AXIS_COUNT], double EPosData[EXT_AXIS_COUNT]){
        for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
            this->JointData[i] = JointData[i];
        }
        for (int i = 0; i < EXT_AXIS_COUNT; i++) {
            this->EPosData[i] = EPosData[i];
        }
    }
    InoJPos &operator=(const InoJPos &other)
    {
        if (this != &other) {
            for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
                JointData[i] = other.JointData[i];
            }

            for (int i = 0; i < EXT_AXIS_COUNT; i++) {
                EPosData[i] = other.EPosData[i];
            }
        }

        return *this;
    }
    bool operator==(const InoJPos &other) const {
        if (this != &other) {
            for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
                if(abs(JointData[i] - other.JointData[i]) > 0.00001){
                    return false;
                }
            }
            for (int i = 0; i < EXT_AXIS_COUNT; i++) {
                if(abs(EPosData[i] - other.EPosData[i]) > 0.00001){
                    return false;
                }
            }
        }
        return true;
    }
} InoJPos;

typedef struct InoRobPos {
    double RPosData[POSE_AXIS_COUNT];  // XYZABC
    int ArmParm[ARM_TYPE_COUNT];      // 臂参数
    double EPosData[EXT_AXIS_COUNT];  // E1-E6
    InoRobPos()
    {
        for (int i = 0; i < POSE_AXIS_COUNT; i++) {
            RPosData[i] = 0;
        }
        for (int i = 0; i < ARM_TYPE_COUNT; i++) {
            ArmParm[i] = 0;
        }
        for (int i = 0; i < EXT_AXIS_COUNT; i++) {
            EPosData[i] = 0;
        }
    }
    InoRobPos(double RPosData[POSE_AXIS_COUNT], int ArmParm[ARM_TYPE_COUNT],
              double EPosData[EXT_AXIS_COUNT])
    {
        for (int i = 0; i < POSE_AXIS_COUNT; i++) {
            this->RPosData[i] = RPosData[i];
        }
        for (int i = 0; i < ARM_TYPE_COUNT; i++) {
            this->ArmParm[i] = ArmParm[i];
        }
        for (int i = 0; i < EXT_AXIS_COUNT; i++) {
            this->EPosData[i] = EPosData[i];
        }
    }
    InoRobPos &operator=(const InoRobPos &other)
    {
        if (this != &other) {
            for (int i = 0; i < POSE_AXIS_COUNT; i++) {
                RPosData[i] = other.RPosData[i];
            }

            for (int i = 0; i < ARM_TYPE_COUNT; i++) {
                ArmParm[i] = other.ArmParm[i];
            }

            for (int i = 0; i < EXT_AXIS_COUNT; i++) {
                EPosData[i] = other.EPosData[i];
            }
        }

        return *this;
    }
} InoRobPos;

typedef struct InoJPointInfo {
    int pointNo = -1;     // 点位序号
    QString name;         // 名称
    QString label;        // 标签
    QString description;  // 描述（备注）
    InoJPos pos;

    InoJPointInfo &operator=(const InoJPointInfo &other)
    {
        if (this != &other) {
            pointNo = other.pointNo;
            name = other.name;
            label = other.label;
            description = other.description;
            pos = other.pos;
        }

        return *this;
    }

    // 将当前类型转换为 QVariant 类型
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

    // 根据下标获取对应数据
    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->pointNo;
        case 1:
            return this->name;
        case 2:
            return this->label;
        case 3:
            return this->description;
        case 4:
            return this->pos.JointData[0];
        case 5:
            return this->pos.JointData[1];
        case 6:
            return this->pos.JointData[2];
        case 7:
            return this->pos.JointData[3];
        case 8:
            return this->pos.JointData[4];
        case 9:
            return this->pos.JointData[5];
        case 10:
            return this->pos.EPosData[0];
        case 11:
            return this->pos.EPosData[1];
        case 12:
            return this->pos.EPosData[2];
        case 13:
            return this->pos.EPosData[3];
        case 14:
            return this->pos.EPosData[4];
        case 15:
            return this->pos.EPosData[5];
        default:
            break;
        }
        return QString();
    }
} InoJPointInfo;
Q_DECLARE_METATYPE(InoJPointInfo)

typedef struct InoRPointInfo {
    int pointNo = -1;     // 点位序号
    QString name;         // 名称
    QString label;        // 标签
    QString description;  // 描述（备注）
    InoRobPos pos;

    InoRPointInfo &operator=(const InoRPointInfo &other)
    {
        if (this != &other) {
            pointNo = other.pointNo;
            name = other.name;
            label = other.label;
            description = other.description;
            pos = other.pos;
        }

        return *this;
    }

    // 将当前类型转换为 QVariant 类型
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

    // 根据下标获取对应数据
    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->pointNo;
        case 1:
            return this->name;
        case 2:
            return this->label;
        case 3:
            return this->description;
        case 4:
            return this->pos.RPosData[0];
        case 5:
            return this->pos.RPosData[1];
        case 6:
            return this->pos.RPosData[2];
        case 7:
            return this->pos.RPosData[3];
        case 8:
            return this->pos.RPosData[4];
        case 9:
            return this->pos.RPosData[5];
        case 10:
            return this->pos.ArmParm[0];
        case 11:
            return this->pos.ArmParm[1];
        case 12:
            return this->pos.ArmParm[2];
        case 13:
            return this->pos.ArmParm[3];
        case 14:
            return this->pos.EPosData[0];
        case 15:
            return this->pos.EPosData[1];
        case 16:
            return this->pos.EPosData[2];
        case 17:
            return this->pos.EPosData[3];
        case 18:
            return this->pos.EPosData[4];
        case 19:
            return this->pos.EPosData[5];
        default:
            break;
        }
        return QString();
    }
} InoRPointInfo;
Q_DECLARE_METATYPE(InoRPointInfo)
