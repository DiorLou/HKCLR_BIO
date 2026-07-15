#pragma once
#include "ctrlauthority.h"
#include "labeldata.h"
#include "metatype.h"
#include "pointdata.h"
#include "projectdata.h"
#include "task.h"
#include "InoRobBusiness/Controller/Connection/IConnection.h"
#include "InoRobBusiness/Include/GlobalDataTypes.h"
#include "InoRobBusiness/Controller/Resource/IResource.h"
#include "InoRobBusiness/Controller/ControlAuthority/IControlAuthority.h"
#include "InoRobBusiness/Controller/Task/ITask.h"

class RoadPoint;
class Pos;
class Ori;

class MetaTypeConversion
{
public:
    static ControllerConnectionState api2tp_controllerConnectionStatus(
        const InoRobBusiness::ControllerConnectionStatus &status);

    static RoadPoint inoApi2tp_roadPoint(const JPos &src);
    static JPos tp2InoApi_roadPoint(const RoadPoint &src);
    static RobPos tp2InoApi_roadPoint2RobPos(const RoadPoint &src);
    static InoJPos tp2InoApi_jPos(const JPos &src);
    static JPos inoApi2tp_jPos(const InoJPos &src);
    static InoRobPos tp2InoApi_robPos(const RobPos &src);
    static RobPos inoApi2tp_robPos(const InoRobPos &src);
    static RoadPoint inoApi2tp_roadPoint(const InoJPos &src);
    static RoadPoint inoApi2tp_roadPoint(const MRobPosItem &src);
    static RoadPoint inoApi2tp_roadPoint(const InoRPointInfo &src);
    static RoadPoint inoApi2tp_roadPoint(const InoRobPos &src);

    // project management
    static ProjectFileOperateMode inoApi2tp_projectFileOperateMode(
        const InoFileType &src);
    static ProjectType inoApi2tp_projectType(const InoProjectType &src);
    static QVector<InoProjectInfo> tp2InoApi_projectInfos(
        std::vector<struct _ProjectFolderInfo> &src);
    static std::vector<struct _ProjectFolderInfo> inoApi2tp_projectInfos(
        const QVector<InoProjectInfo> &src);

    static EUSER_MODE inoApi2tp_userMode(const InoUserMode &src);
    static InoUserMode tp2InoApi_userMode(const EUSER_MODE &src);

    static InoRobBusiness::CtrlAuthority inoApi2tp_controlAuthority(
        const InoCtrlAuthority &src);
    static InoCtrlAuthority tp2InoApi_controlAuthority(
        const InoRobBusiness::CtrlAuthority &src);

    // global variable
    // B
    static QVector<QVector<QVariant>> tp2InoApi_globalVarBVariant(
        const std::vector<InoRobBusiness::GlobalVarBData> &src);
    // R
    static QVector<QVector<QVariant>> tp2InoApi_globalVarRVariant(
        const std::vector<InoRobBusiness::GlobalVarRData> &src);
    // D
    static QVector<QVector<QVariant>> tp2InoApi_globalVarDVariant(
        const std::vector<InoRobBusiness::GlobalVarDData> &src);
    // string
    static QVector<QVector<QVariant>> tp2InoApi_globalVarStringVariant(
        const std::array<std::string, GLOBAL_VAR_STRING_COUNT> &src);
    // P
    static QVector<QVector<QVariant>> tp2InoApi_globalVarPVariant(
        const std::vector<InoRobBusiness::GlobalPData> &src);
    // JP
    static QVector<QVector<QVariant>> tp2InoApi_globalVarJPVariant(
        const std::vector<InoRobBusiness::GlobalJPData> &src);

    // label
    static LabelType inoApi2tp_labelType(const InoLabelType &src);
    static AdDaType inoApi2tp_addaType(const InoAdDaType &src);
    static IoType inoApi2tp_ioType(const InoLabelIOType &src);
    static IoDataType inoApi2tp_dataType(const ShowType &src);

    static QVector<InoLabelItem> tp2InoApi_Items(
        const std::vector<LabelItem> &src);
    static InoIOLabelItems tp2InoApi_labelItems(const IoLabelItems &src);

    static QVector<InoTaskInfo> tp2InoApi_taskInfo(
        const std::vector<MultiTaskInfo> &src);

    static InoTaskStatus tp2InoApi_taskStatus(InoRobBusiness::TaskStatus &src);
    static InoTaskStatusArr tp2InoApi_taskStatusArr(
        InoRobBusiness::TaskStatusArr &src);
};
