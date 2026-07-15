#include "metatypeconversion.h"
#include <QDebug>
#include "roadpoint.h"
#include "math.h"
#include "modulesutils.h"

RoadPoint MetaTypeConversion::inoApi2tp_roadPoint(const JPos &src)
{
    RoadPoint dest;
    dest.setJointAngle(const_cast<double *>(src.JointData));

    return dest;
}

RoadPoint MetaTypeConversion::inoApi2tp_roadPoint(const MRobPosItem &src)
{
    RoadPoint dest;

    dest.m_position.m_x = src.PData.RPosData[0];
    dest.m_position.m_y = src.PData.RPosData[1];
    dest.m_position.m_z = src.PData.RPosData[2];
    dest.m_orientation.m_rz = src.PData.RPosData[3];
    dest.m_orientation.m_ry = src.PData.RPosData[4];
    dest.m_orientation.m_rx = src.PData.RPosData[5];
    dest.m_arm[0] = src.PData.ArmParm[0];
    dest.m_arm[1] = src.PData.ArmParm[1];
    dest.m_arm[2] = src.PData.ArmParm[2];
    dest.m_arm[3] = src.PData.ArmParm[3];

    return dest;
}

RoadPoint MetaTypeConversion::inoApi2tp_roadPoint(const InoRPointInfo &src)
{
    RoadPoint dest;

    dest.m_position.m_x = src.pos.RPosData[0];
    dest.m_position.m_y = src.pos.RPosData[1];
    dest.m_position.m_z = src.pos.RPosData[2];
    dest.m_orientation.m_rz = src.pos.RPosData[3];
    dest.m_orientation.m_ry = src.pos.RPosData[4];
    dest.m_orientation.m_rx = src.pos.RPosData[5];
    dest.m_arm[0] = src.pos.ArmParm[0];
    dest.m_arm[1] = src.pos.ArmParm[1];
    dest.m_arm[2] = src.pos.ArmParm[2];
    dest.m_arm[3] = src.pos.ArmParm[3];

    return dest;
}

RoadPoint MetaTypeConversion::inoApi2tp_roadPoint(const InoRobPos &src)
{
    RoadPoint dest;

    dest.m_position.m_x = src.RPosData[0];
    dest.m_position.m_y = src.RPosData[1];
    dest.m_position.m_z = src.RPosData[2];
    dest.m_orientation.m_rz = src.RPosData[3];
    dest.m_orientation.m_ry = src.RPosData[4];
    dest.m_orientation.m_rx = src.RPosData[5];
    dest.m_arm[0] = src.ArmParm[0];
    dest.m_arm[1] = src.ArmParm[1];
    dest.m_arm[2] = src.ArmParm[2];
    dest.m_arm[3] = src.ArmParm[3];

    return dest;
}

JPos MetaTypeConversion::tp2InoApi_roadPoint(const RoadPoint &src)
{
    JPos dest;

    for (int i = 0; i < ROBOT_DOF; i++)
        dest.JointData[i] = src.m_jointAngle[i];

    return dest;
}

RobPos MetaTypeConversion::tp2InoApi_roadPoint2RobPos(const RoadPoint &src)
{
    RobPos dest;
    dest.RPosData[0] = src.m_position.m_x;
    dest.RPosData[1] = src.m_position.m_y;
    dest.RPosData[2] = src.m_position.m_z;
    dest.RPosData[3] = src.m_orientation.m_rz;
    dest.RPosData[4] = src.m_orientation.m_ry;
    dest.RPosData[5] = src.m_orientation.m_rx;

    for (int i = 0; i < ROBOT_ARM_NUM; i++) {
        dest.ArmParm[i] = src.m_arm[i];
    }

    return dest;
}

InoJPos MetaTypeConversion::tp2InoApi_jPos(const JPos &src)
{
    InoJPos dest;

    for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
        dest.JointData[i] = src.JointData[i];
    }

    for (int i = 0; i < EXT_AXIS_COUNT; i++) {
        dest.EPosData[i] = src.EPosData[i];
    }

    return dest;
}

JPos MetaTypeConversion::inoApi2tp_jPos(const InoJPos &src)
{
    JPos dest;
    for (int i = 0; i < JOINT_AXIS_COUNT; i++) {
        dest.JointData[i] = src.JointData[i];
    }

    for (int i = 0; i < EXT_AXIS_COUNT; i++) {
        dest.EPosData[i] = src.EPosData[i];
    }

    return dest;
}

RoadPoint MetaTypeConversion::inoApi2tp_roadPoint(const InoJPos &src)
{
    RoadPoint dest;
    dest.setJointAngle(const_cast<double *>(src.JointData));
    return dest;
}

InoRobPos MetaTypeConversion::tp2InoApi_robPos(const RobPos &src)
{
    InoRobPos dest;
    for (int i = 0; i < POSE_AXIS_COUNT; i++) {
        dest.RPosData[i] = src.RPosData[i];
    }

    for (int i = 0; i < ARM_TYPE_COUNT; i++) {
        dest.ArmParm[i] = src.ArmParm[i];
    }

    for (int i = 0; i < EXT_AXIS_COUNT; i++) {
        dest.EPosData[i] = src.EPosData[i];
    }

    return dest;
}

RobPos MetaTypeConversion::inoApi2tp_robPos(const InoRobPos &src)
{
    RobPos dest;
    for (int i = 0; i < POSE_AXIS_COUNT; i++) {
        dest.RPosData[i] = src.RPosData[i];
    }

    for (int i = 0; i < ARM_TYPE_NUM; i++) {
        dest.ArmParm[i] = src.ArmParm[i];
    }

    for (int i = 0; i < EXT_AXIS_NUM; i++) {
        dest.EPosData[i] = src.EPosData[i];
    }

    return dest;
}

ControllerConnectionState
MetaTypeConversion::api2tp_controllerConnectionStatus(
    const InoRobBusiness::ControllerConnectionStatus &status)
{
    ControllerConnectionState dest;

    switch (status) {
    case InoRobBusiness::CONTROLLER_CONNECTION_STATUS_CLOSED:
        dest = ControllerConnectionState_Closed;
        break;
    case InoRobBusiness::CONTROLLER_CONNECTION_STATUS_CONNECTING:
        dest = ControllerConnectionState_Connecting;
        break;
    case InoRobBusiness::CONTROLLER_CONNECTION_STATUS_CONNECTED:
        dest = ControllerConnectionState_Connected;
        break;
    default:
        break;
    }

    return dest;
}

ProjectFileOperateMode MetaTypeConversion::inoApi2tp_projectFileOperateMode(
    const InoFileType &src)
{
    return (static_cast<ProjectFileOperateMode>(static_cast<int>(src)));
}

ProjectType MetaTypeConversion::inoApi2tp_projectType(
    const InoProjectType &src)
{
    return (static_cast<ProjectType>(static_cast<int>(src)));
}

QVector<InoProjectInfo> MetaTypeConversion::tp2InoApi_projectInfos(
    std::vector<struct _ProjectFolderInfo> &src)
{
    QVector<InoProjectInfo> dest;

    for (size_t i = 0; i < src.size(); i++) {
        InoProjectInfo info;
        info.index = QString::number(i);
        info.name = QString::fromStdString(src.at(i).projectName);
        info.modifyTime = QString::fromStdString(src.at(i).modifyTime);
        info.memorySize = src.at(i).memorySize;

        dest.append(info);
    }

    return dest;
}

std::vector<struct _ProjectFolderInfo>
MetaTypeConversion::inoApi2tp_projectInfos(const QVector<InoProjectInfo> &src)
{
    std::vector<struct _ProjectFolderInfo> dest;

    for (int i = 0; i < src.count(); i++) {
        struct _ProjectFolderInfo info;
        info.projectName = src.at(i).name.toStdString();
        info.modifyTime = src.at(i).modifyTime.toStdString();
        info.memorySize = src.at(i).memorySize;
        dest.push_back(info);
    }

    return dest;
}

EUSER_MODE MetaTypeConversion::inoApi2tp_userMode(const InoUserMode &src)
{
    return (static_cast<EUSER_MODE>(static_cast<int>(src)));
}

InoUserMode MetaTypeConversion::tp2InoApi_userMode(const EUSER_MODE &src)
{
    return (static_cast<InoUserMode>(static_cast<int>(src)));
}

InoRobBusiness::CtrlAuthority MetaTypeConversion::inoApi2tp_controlAuthority(
    const InoCtrlAuthority &src)
{
    return (static_cast<InoRobBusiness::CtrlAuthority>(static_cast<int>(src)));
}

InoCtrlAuthority MetaTypeConversion::tp2InoApi_controlAuthority(
    const InoRobBusiness::CtrlAuthority &src)
{
    return (static_cast<InoCtrlAuthority>(static_cast<int16s>(src)));
}

// B
QVector<QVector<QVariant>> MetaTypeConversion::tp2InoApi_globalVarBVariant(
    const std::vector<InoRobBusiness::GlobalVarBData> &src)
{
    QVector<QVector<QVariant>> dest(5);
    size_t size = src.size();
    for (size_t i = 0; i < size; i++) {
        dest[0] << src.at(i).index;
        dest[1] << src.at(i).value;
        dest[2] << QString::fromStdString(src.at(i).labs);
        dest[3] << QString::fromStdString(src.at(i).remarks);
        dest[4] << src.at(i).favorite;
    }
    return dest;
}

// R
QVector<QVector<QVariant>> MetaTypeConversion::tp2InoApi_globalVarRVariant(
    const std::vector<InoRobBusiness::GlobalVarRData> &src)
{
    QVector<QVector<QVariant>> dest(5);
    size_t size = src.size();
    for (size_t i = 0; i < size; i++) {
        dest[0] << src.at(i).index;
        dest[1] << src.at(i).value;
        dest[2] << QString::fromStdString(src.at(i).labs);
        dest[3] << QString::fromStdString(src.at(i).remarks);
        dest[4] << src.at(i).favorite;
    }
    return dest;
}

// D
QVector<QVector<QVariant>> MetaTypeConversion::tp2InoApi_globalVarDVariant(
    const std::vector<InoRobBusiness::GlobalVarDData> &src)
{
    QVector<QVector<QVariant>> dest(5);
    size_t size = src.size();
    for (size_t i = 0; i < size; i++) {
        dest[0] << src.at(i).index;
        dest[1] << src.at(i).value;
        dest[2] << QString::fromStdString(src.at(i).labs);
        dest[3] << QString::fromStdString(src.at(i).remarks);
        dest[4] << src.at(i).favorite;
    }
    return dest;
}

// string
QVector<QVector<QVariant>>
MetaTypeConversion::tp2InoApi_globalVarStringVariant(
    const std::array<std::string, GLOBAL_VAR_STRING_COUNT> &src)
{
    QVector<QVector<QVariant>> dest(2);
    for (int i = 0; i < GLOBAL_VAR_STRING_COUNT; i++) {
        dest[0] << i;
        dest[1] << QString::fromStdString(src[i]);
    }
    return dest;
}
// P
QVector<QVector<QVariant>> MetaTypeConversion::tp2InoApi_globalVarPVariant(
    const std::vector<InoRobBusiness::GlobalPData> &src)
{
    QVector<QVector<QVariant>>
        dest(3 + POSE_AXIS_NUM + EXT_AXIS_NUM + ARM_TYPE_NUM);
    int size = src.size();
    for (int i = 0; i < size; ++i) {
        dest[0] << src[i].globalP.PointNo;
        dest[1] << QString::fromStdString(src[i].labs);
        dest[2] << QString::fromStdString(src[i].remarks);
        for (int j = 0; j < POSE_AXIS_NUM; ++j) {
            dest[3 + j] << src[i].globalP.Pos.RPosData[j];
        }
        for (int j = 0; j < ARM_TYPE_NUM; ++j) {
            dest[3 + POSE_AXIS_NUM + j] << src[i].globalP.Pos.ArmParm[j];
        }
        for (int j = 0; j < EXT_AXIS_NUM; ++j) {
            dest[3 + ARM_TYPE_NUM + POSE_AXIS_NUM + j]
                << src[i].globalP.Pos.EPosData[j];
        }
    }

    return dest;
}
// JP
QVector<QVector<QVariant>> MetaTypeConversion::tp2InoApi_globalVarJPVariant(
    const std::vector<InoRobBusiness::GlobalJPData> &src)
{
    QVector<QVector<QVariant>> dest(3 + POSE_AXIS_NUM + EXT_AXIS_NUM);
    int size = src.size();
    for (int i = 0; i < size; ++i) {
        dest[0] << src[i].globalJP.PointNo;
        dest[1] << QString::fromStdString(src[i].labs);
        dest[2] << QString::fromStdString(src[i].remarks);

        for (int j = 0; j < POSE_AXIS_NUM; ++j) {
            dest[3 + j] << src[i].globalJP.Pos.JointData[j];
        }
        for (int j = 0; j < EXT_AXIS_NUM; ++j) {
            dest[3 + j + POSE_AXIS_NUM] << src[i].globalJP.Pos.EPosData[j];
        }
        // for(int j = 0; j < EXT_AXIS_NUM; ++j) {
        //     dest[3 + POSE_AXIS_NUM + j] << src[i].globalJP.Pos.EPosData[j];
        // }
    }

    return dest;
}

LabelType MetaTypeConversion::inoApi2tp_labelType(const InoLabelType &src)
{
    return (static_cast<LabelType>(src));
}

AdDaType MetaTypeConversion::inoApi2tp_addaType(const InoAdDaType &src)
{
    return (static_cast<AdDaType>(src));
}

IoType MetaTypeConversion::inoApi2tp_ioType(const InoLabelIOType &src)
{
    return (static_cast<IoType>(static_cast<int>(src)));
}

IoDataType MetaTypeConversion::inoApi2tp_dataType(const ShowType &src)
{
    return (static_cast<IoDataType>(src));
}

QVector<InoLabelItem> MetaTypeConversion::tp2InoApi_Items(
    const std::vector<LabelItem> &src)
{
    QVector<InoLabelItem> dest;

    for (size_t i = 0; i < src.size(); i++) {
        InoLabelItem item;
        item.nLabelId = src.at(i).nLabelId;
        item.nIndex = src.at(i).nIndex;
        item.sLabel = QString::fromStdString(src.at(i).sLabel);
        item.sDescription = QString::fromStdString(src.at(i).sDescription);
        item.sOriginalName = QString::fromStdString(src.at(i).sOriginalName);

        dest.append(item);
    }

    return dest;
}

InoIOLabelItems MetaTypeConversion::tp2InoApi_labelItems(
    const IoLabelItems &src)
{
    InoIOLabelItems dest;

    dest.nNumberOfLabels = src.nNumberOfLabels;
    dest.LabelsArray = tp2InoApi_Items(src.LabelsArray);

    return dest;
}

QVector<InoTaskInfo> MetaTypeConversion::tp2InoApi_taskInfo(
    const std::vector<MultiTaskInfo> &src)
{
    QVector<InoTaskInfo> dest;

    for (size_t i = 0; i < src.size(); i++) {
        MultiTaskInfo taskInfo = src.at(i);
        QString sTaskFileName
            = QString::fromStdString(taskInfo.enterProgramFile);
        dest.append({taskInfo.taskId,
                     sTaskFileName.left(sTaskFileName.indexOf(".")),
                     taskInfo.taskType,
                     sTaskFileName,
                     taskInfo.isActive});
    }

    return dest;
}

InoTaskStatus MetaTypeConversion::tp2InoApi_taskStatus(
    InoRobBusiness::TaskStatus &src)
{
    return (static_cast<InoTaskStatus>(src));
}

InoTaskStatusArr MetaTypeConversion::tp2InoApi_taskStatusArr(
    InoRobBusiness::TaskStatusArr &src)
{
    InoTaskStatusArr statusArr;
    for (int i = 0; i < MAX_TASK_NUM; i++) {
        statusArr.isChanged[i] = src.isChanged[i];
    }

    for (int i = 0; i < MAX_TASK_NUM; i++) {
        qDebug() << "***** tp2InoApi_taskStatusArr status = "
                 << static_cast<int>(src.status[i]);
        statusArr.status[i] = tp2InoApi_taskStatus(src.status[i]);
    }

    return statusArr;
}
