#pragma once
#include <QObject>
#include "dllspec.h"
#include "GlobalDataTypes.h"
#include "IDataService.h"

namespace InoRobBusiness
{
enum CalibrateState : int32s
{
    // 标定成功
    CALIBRATE_SUCCESS = 0,
    // 失败（非 0）
};

// 标定模式
enum VisionCalibMode : int8u
{
    // 手动标定
    MAMUAL_CALIB = 0,
    // 半自动标定
    SEMI_AUTO_CALIB = 1,
    // 全自动标定
    FULL_AUTO_CALIB = 2,
};

class INOROBBUSINESS_CLASS ICalibrate : public QObject
{
    Q_OBJECT

public:
    virtual ~ICalibrate()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**************夹持工具标定**************/
    // 获取标定结果：夹持工具三点法TCP
    // 输入：三个标定点pos1 pos2 pos3 (点的涵义：tool0 相对wobj0)
    // 输出： 标定状态state  0 表示成功 非 0 失败； 工具参数toolCrd   工具标定错误标识 ToolCalibError
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_GripToolParmBy3P(RobPos pos1, RobPos pos2, RobPos pos3, CalibrateState &state, Pose &toolCrd, ToolCalibError &calibErr) = 0;

    // 获取标定结果：夹持工具三点法TCP+ZX)
    // 输入：三个标定点pos1 pos2 pos3(点的涵义：tool0 相对wobj0) = 0; pos_o原点, pos_z Z方向上的点, pos_x X方向上的点
    // 输出： 标定状态state  0 表示成功 非 0 失败； 工具参数toolCrd   工具标定错误标识 ToolCalibError
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_GripToolParmBy3PZX(RobPos pos1, RobPos pos2, RobPos pos3, RobPos pos_o, RobPos pos_z, RobPos pos_x, CalibrateState &state, Pose &toolCrd, ToolCalibError &calibErr) = 0;

    /**************外部工具标定**************/
    // 获取标定结果：外部工具已知工具一点法TCP
    // 输入：标定点pos_o (点的涵义：tool0 相对wobj0)
    // 输出：标定状态state  0 表示成功 非 0 失败；工具参数toolCrd
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternToolParmBy1P(RobPos pos_o, CalibrateState &state, Pose &toolCrd) = 0;

    // 获取标定结果：外部工具已知工具一点法TCP+ZX
    // 输入：标定点pos_o (点的涵义：tool0 相对wobj0) pos_z Z方向上的点 pos_x：X方向上的点
    // 输出： 标定状态state  0 表示成功 非 0 失败； 工具参数toolCrd
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternToolParmBy1PZX(RobPos pos_o, RobPos pos_z, RobPos pos_x, CalibrateState &state, Pose &toolCrd) = 0;

    // 获取标定结果：外部工具未知工具三点法TCP
    // 输入：标定点pos1 pos2 pos3 (点的涵义：tool0 相对wobj0)
    // 输出：标定状态state  0 表示成功 非 0 失败；工具参数toolCrd
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternToolParmBy3P(RobPos pos1, RobPos pos2, RobPos pos3, CalibrateState &state, Pose &toolCrd, ToolCalibError &calibErr) = 0;

    // 获取标定结果：外部工具未知工具三点法TCP+ZX
    // 输入：标定点pos1 pos2 pos3 (点的涵义：tool0 相对wobj0) = 0; pos_o原点, pos_z Z方向上的点, pos_x X方向上的点
    // 输出：标定状态state  0 表示成功 非 0 失败；工具参数toolCrd
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternToolParmBy3PZX(RobPos pos1, RobPos pos2, RobPos pos3, RobPos pos_o, RobPos pos_z, RobPos pos_x, CalibrateState &state, Pose &toolCrd, ToolCalibError &calibErr) = 0;

    /**************外部工件标定（RobHold=False）**************/
    // 获取标定结果：外部工件三点法标定用户坐标系
    // 输入：标定点pos_o pos_x pos_y(点的涵义：tool0 相对wobj0)
    // 输出：标定状态state  0 表示成功 非 0 失败；用户参数usrCrd = 0; 针对Scara机型还会返回XY平面与基座XY平面的偏移角offsAngle
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternWobj_UserParmBy3P(RobPos pos_o, RobPos pos_x, RobPos pos_y, CalibrateState &state, Pose &usrCrd, double &offsAngle) = 0;

    // 获取标定结果：外部工件旋转法标定用户坐标系
    // 输入：标定点pos_o pos_x pos_y(点的涵义：tool0 相对wobj0)
    // 输出：用户参数usrCrd
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternWobj_ObjParmBy3PCircle(RobPos pos_o, RobPos pos_x, RobPos pos_y, CalibrateState &state, Pose &usrCrd) = 0;

    // 获取标定结果：外部工件三点法标定工件坐标系
    // 输入：标定点pos_o pos_x pos_y(点的涵义：tool0 相对wobj0) usrCrd用户坐标系参数
    // 输出：标定状态state  0 表示成功 非 0 失败；工件参数objCrd = 0; 针对Scara机型还会返回XY平面与基座XY平面的偏移角offsAngle
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_ExternWobj_ObjParmBy3P(RobPos pos_o, RobPos pos_x, RobPos pos_y, Pose usrCrd, CalibrateState &state, Pose &objCrd, double &offsAngle) = 0;

    /**************外部工件标定（RobHold=False,UFFix=false）**************/
    // 获取标定结果：外部工件三点法标定工件坐标系(可移动的用户坐标系下标定工件坐标系oframe)
    // 输入：标定点pos_o pos_x pos_y(点的涵义：tool0 相对wobj0)
    // 输出：标定状态state  0 表示成功 非 0 失败；工件参数objCrd = 0; 针对Scara机型还会返回XY平面与基座XY平面的偏移角offsAngle
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_UnFixed_ExternWobj_ObjParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH], RobPos pos_o, RobPos pos_x, RobPos pos_y, CalibrateState &state, Pose &objCrd, double &offsAngle) = 0;

    /**************夹持工件标定（RobHold=True）**************/
    // 获取标定结果：夹持工件三点法标定用户坐标系
    // 输入：标定点pos_o pos_x pos_y(点的涵义：toolX 相对flangle)
    // 输出：标定状态state  0 表示成功 非 0 失败；用户参数usrCrd = 0; 针对Scara机型还会返回XY平面与法兰盘XY平面的偏移角offsAngle
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_GripWobj_UserParmBy3P(RobPos pos_o, RobPos pos_x, RobPos pos_y, CalibrateState &state, Pose &usrCrd, double &offsAngle) = 0;

    // 获取标定结果：夹持工件三点法标定工件坐标系
    // 输入：标定点pos_o pos_x pos_y(点的涵义：toolX 相对flangle) usrCrd用户坐标系参数
    // 输出：标定状态state  0 表示成功 非 0 失败；工件参数objCrd = 0; 针对Scara机型还会返回XY平面与法兰盘XY平面的偏移角offsAngle
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_GripWobj_ObjParmBy3P(RobPos pos_o, RobPos pos_x, RobPos pos_y, Pose usrCrd, CalibrateState &state, Pose &objCrd, double &offsAngle) = 0;

    /**************机器人基座相对导轨标定**************/
    // 获取标定结果：已知工具参数三点法标定导轨基坐标系
    // 输入：mechUnitName[MECHUNIT_NAME_LENGTH] 标定机械单元的名称，区分是标定的哪个机械单元
    // pos0[3]：三个标定点位置，TCP 相对基坐标系的坐标
    //           toolCrd：当前工具的参数
    // 输出：标定状态state  0 表示成功 非 0 失败；
    //  trackBaseCrd：导轨基坐标系相对机器人基坐标系的参数
    //           calibErr：导轨基坐标系的标定误差
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_TrackBaseOnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH], RobPos pos0[3], CalibrateState &state, Pose &trackBaseCrd, ToolCalibError &calibErr) = 0;

    /**************机器人基座相对导轨XZ标定**************/
    // 获取标定结果：已知工具参数六点法标定导轨基坐标系
    // 输入：mechUnitName[MECHUNIT_NAME_LENGTH] 标定机械单元的名称，区分是标定的哪个机械单元
    // pos0[6]：6个标定点位置，TCP 相对基坐标系的坐标
    // 输出：标定状态 state  0 表示成功 非 0 失败；trackBaseCrd[3]：XZ导轨基坐标系相对机器人基坐标系的参数
    //          calibErr：导轨基坐标系的标定误差；mechUnitType表示机械单元类型
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_TrackXZOnRobBase_ParmBy6P(char mechUnitName[MECHUNIT_NAME_LENGTH], RobPos pos0[6], CalibrateState &state, Pose *trackBaseCrd, ToolCalibError &calibErr, int16u mechUnitType) = 0;

    /**************机器人基座相对导轨XYZ标定**************/
    // 获取标定结果：已知工具参数九点法标定导轨基坐标系
    // 输入：mechUnitName[MECHUNIT_NAME_LENGTH] 标定机械单元的名称，区分是标定的哪个机械单元
    // pos0[9]：9个标定点位置，TCP 相对基坐标系的坐标
    // 输出：标定状态 state  0 表示成功 非 0 失败；trackBaseCrd[3]：XYZ导轨基坐标系相对机器人基坐标系的参数
    //          calibErr：导轨基坐标系的标定误差
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_TrackXYZOnRobBase_ParmBy9P(char mechUnitName[MECHUNIT_NAME_LENGTH], RobPos pos0[9], CalibrateState &state, Pose *trackBaseCrd, ToolCalibError &calibErr) = 0;

    /**************双轴旋转变位机标定**************/
    // 获取标定结果：已知工具参数三点法标定单轴变位机工作台坐标系
    //  输入：pos[3]：三个标定点位置，TCP 相对世界坐标系的坐标
    //           toolCrd：当前工具的参数
    // 输出：标定状态state  0 表示成功 非 0 失败；
    //  PositionerJ1Crd：变位机J1轴坐标系相对世界坐标系的参数
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_PositionerJ1OnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH], RobPos pos[3], CalibrateState &state, Pose &positionerCrd) = 0;

    // 获取标定结果：已知工具参数三点法标定多轴变位机工作台坐标系
    //  输入：mechUnitName[MECHUNIT_NAME_LENGTH] 标定机械单元的名称，区分是标定的哪个机械单元
    // ：curAxisNo 当前标定的变位机轴号 ；  pos[3]：三个标定点位置，TCP 相对世界坐标系的坐标
    //
    //           toolCrd：当前工具的参数
    // 输出：标定状态state  0 表示成功 非 0 失败；
    //  positionerJnCrd：变位机转台坐标系相对世界坐标系的参数
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_PositionerJnOnRobBase_ParmBy3P(char mechUnitName[MECHUNIT_NAME_LENGTH], int8u curAxisNo, RobPos pos[3], Pose positionerJn_1Crd, CalibrateState &state, Pose &positionerJnCrd) = 0;

    /**************视觉标定**************/
    // 获取标定结果：根据已有的点，求取九点
    //  输入：calibMode：       标定模式（0-手动标定，1-半自动标定，2-全自动标定）
    //        robotInputPoint： 示教的关节点位（半自动标定：3个点；全自动标定：1个点）
    //        distance:         标定模式为全自动标定时，需要增加偏移距离
    //  输出：state：           标定状态,0 表示成功 非 0 失败；
    //        robotOutputPoint：输出的9个点（关节点）
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_Calcu9Point(VisionCalibMode calibMode, double robotInputPoint[3][6], double distance, CalibrateState &state, double robotOutputPoint[9][6]) = 0;

    // 获取标定结果：手眼标定-4轴，求9对像素坐标与机器人坐标关系的映射
    //  输入：cameraStyle：      相机安装方式，1-固定俯视，2-固定仰视，3-可移动式J2，4-可移动式J4，5-可移动式J5，6-可移动式J6
    //        basePointKind：    基准点获取方式，0 机器人末端获取基准点 1 视野中心获取基准点
    //        robotPoint：       9个机器人坐标点（关节点）
    //        robotBasePoint：   2个基准点（关节点，四轴机器人只需2个基准点，用于标定工具）
    //        imagePoint：       9个像素坐标点
    //  输出：state：            标定状态,0 表示成功 非 0 失败；
    //        calMatrix：        标定参数
    //        errParam：         标定误差
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_EyeHandCalibN(int8u cameraStyle, int8u basePointKind, double robotPoint[9][6], double robotBasePoint[2][6], double imagePoint[9][2], CalibrateState &state, double calMatrix[9], VISION_ERR_PARAM &errParam) = 0;

    // 获取标定结果：手眼标定-6轴，求9对像素坐标与机器人坐标关系的映射
    //  输入：cameraStyle：      相机安装方式，1-固定俯视，2-固定仰视，3-可移动式J2，4-可移动式J4，5-可移动式J5，6-可移动式J6
    //        basePointKind：    基准点获取方式，0 机器人末端获取基准点 1 视野中心获取基准点
    //        robotPoint：       9个机器人坐标点（关节点）
    //        robotBasePoint：   3个基准点（关节点，六轴3个基准点，用于标定工具）
    //        imagePoint：       9个像素坐标点
    //        wObjParam：        工件坐标系参数（6轴机器人需要使用）
    //  输出：state：            标定状态,0 表示成功 非 0 失败
    //        calMatrix：        标定参数
    //        errParam：         标定误差
    // 返回值：true 表示通讯成功 false 表示通讯失败
    virtual bool GetCalibRet_EyeHandCalibN2(int8u cameraStyle, int8u basePointKind, double robotPoint[9][6], double robotBasePoint[3][6], double imagePoint[9][2], WobjData wObjParam, CalibrateState &state, double calMatrix[9], VISION_ERR_PARAM &errParam) = 0;
};
}  // namespace InoRobBusiness
