#pragma once
#include <string>
#include <vector>
#include "InoRobUtil/CommonEnum_V1.h"

namespace InoRobBusinessProxy
{
#pragma region 常量定义

#define LINK_PARM_NUM_V1 8
#define COM_PARM_NUM_V1  16

#define MODULE_NUM_V1   8  // 控制器模块数量
#define MAXIONUM_V1     128
#define MAXDANUM_V1     16
#define MAXIRLINKNUM_V1 4

// PR变量
#define PALLET_VAR_NUMB_V1     256
#define PALLET_VAR_ARR_SIZE_V1 5  // 每帧数据
#define PR_VAR_NUMB_V1         256
#define PR_VAR_ARR_SIZE_V1     10  // 每帧数据

#pragma endregion

#pragma region 机器人位置点

typedef struct tagRobPos_V1
{
    tagRobPos_V1()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
        {
            RPosData[i] = 0.0;
            EPosData[i] = 0.0;
        }
        for (size_t i = 0; i < ARM_TYPE_NUM_V1; i++)
        {
            ArmParm[i] = 0;
        }
    }

    tagRobPos_V1 &operator=(const tagRobPos_V1 &other)
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
            this->RPosData[i] = other.RPosData[i];
        for (size_t i = 0; i < ARM_TYPE_NUM_V1; i++)
            this->ArmParm[i] = other.ArmParm[i];
        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
            this->EPosData[i] = other.EPosData[i];

        return (*this);
    }

    bool operator==(const tagRobPos_V1 &other) const
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
        {
            if (std::abs(this->RPosData[i] - other.RPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        for (size_t i = 0; i < ARM_TYPE_NUM_V1; i++)
        {
            if (std::abs(this->ArmParm[i] - other.ArmParm[i]) > 0.000001)
            {
                return false;
            }
        }

        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
        {
            if (std::abs(this->EPosData[i] - other.EPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        return true;
    }

    double RPosData[POSE_AXIS_NUM_V1];  // XYZABC
    int ArmParm[ARM_TYPE_NUM_V1];       // 臂参数
    double EPosData[EXT_AXIS_NUM_V1];   // E1-E6
} RobPos_V1;

bool RobPos_ToProxy(const RobPos &robPos, RobPos_V1 &robPos_V1);
bool RobPos_FromProxy(const RobPos_V1 &robPos_V1, RobPos &robPos);

#pragma endregion

#pragma region 机器人关节点

typedef struct tagJPos_V1
{
    tagJPos_V1()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        for (size_t i = 0; i < JOINT_AXIS_NUM_V1; i++)
        {
            JointData[i] = 0.0;
        }
        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
        {
            EPosData[i] = 0.0;
        }
    }

    tagJPos_V1 &operator=(const tagJPos_V1 &other)
    {
        for (size_t i = 0; i < JOINT_AXIS_NUM_V1; i++)
            this->JointData[i] = other.JointData[i];
        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
            this->EPosData[i] = other.EPosData[i];

        return (*this);
    }

    bool operator==(const tagJPos_V1 &other) const
    {
        for (size_t i = 0; i < JOINT_AXIS_NUM_V1; i++)
        {
            if (std::abs(this->JointData[i] - other.JointData[i]) > 0.000001)
            {
                return false;
            }
        }

        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
        {
            if (std::abs(this->EPosData[i] - other.EPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        return true;
    }

    double JointData[JOINT_AXIS_NUM_V1];  // J1-J8
    double EPosData[EXT_AXIS_NUM_V1];     // E1-E6
} JPos_V1;

bool JPos_ToProxy(const JPos &jPos, JPos_V1 &jPos_V1);
bool JPos_FromProxy(const JPos_V1 &jPos_V1, JPos &jPos);

#pragma endregion

#pragma region Move类型

enum MoveType_V1
{
    Movj_V1 = 0,
    Movl_V1 = 1,
    Jump_V1 = 2,
    Jumpl_V1 = 3
};

MoveType_V1 MoveType_ToProxy(MoveType moveType);
MoveType MoveType_FromProxy(MoveType_V1 moveType_V1);

#pragma endregion

#pragma region JP点带标签名备注

typedef struct M_JPOS_POS_ITEM_V1
{
    M_JPOS_POS_ITEM_V1()
    {
        Clear();
    }

    void Clear()
    {
        PointNo = 0;
        JData.Initialize();
        LabelName.clear();
        Description.clear();
    }

    M_JPOS_POS_ITEM_V1 &operator=(const M_JPOS_POS_ITEM_V1 &other)
    {
        this->PointNo = other.PointNo;
        this->JData = other.JData;
        this->LabelName = other.LabelName;
        this->Description = other.Description;

        return (*this);
    }

    bool operator==(const M_JPOS_POS_ITEM_V1 &other) const
    {
        if (this->PointNo != other.PointNo)
        {
            return false;
        }

        if (!(this->JData == other.JData))
        {
            return false;
        }

        if (this->LabelName != other.LabelName)
        {
            return false;
        }

        if (this->Description != other.Description)
        {
            return false;
        }

        return true;
    }

    int PointNo;              // 点号
    JPos_V1 JData;            // 点位数据
    std::string LabelName;    // 标签名
    std::string Description;  // 描述
} MJPosItem_V1;

bool MJPosItem_ToProxy(const MJPosItem &mJPosItem, MJPosItem_V1 &mJPosItem_V1);
bool MJPosItem_FromProxy(const MJPosItem_V1 &mJPosItem_V1, MJPosItem &mJPosItem);

#pragma endregion

#pragma region 位姿

// 位姿 用于描述坐标系的值 在PR, Tool, WObj有用到
typedef struct tagPosture_V1
{
    tagPosture_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
        {
            Data[i] = 0;
        }
    }
    tagPosture_V1 &operator=(const tagPosture_V1 &other)
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
        {
            this->Data[i] = other.Data[i];
        }
        return (*this);
    }

    bool Compare(const struct tagPosture_V1 &other) const
    {
        for (size_t i = 0; i < POSE_AXIS_NUM_V1; i++)
        {
            if (Data[i] != other.Data[i])
                return false;
        }
        return true;
    }

    double Data[POSE_AXIS_NUM_V1];
} Pose_V1;  // 48个字节

bool Pose_ToProxy(const Pose &pose, Pose_V1 &pose_V1);
bool Pose_FromProxy(const Pose_V1 &pose_V1, Pose &pose);

#pragma endregion

#pragma region 标准负载的定义

typedef struct _Load_Para_V1
{
    _Load_Para_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        Mass = 0;
        for (size_t i = 0; i < POSIT_DIMENT_V1; i++)
        {
            Cog[i] = 0;
            Orient[i] = 0;
            Inertia[i] = 0;
        }
    }
    _Load_Para_V1 &operator=(const _Load_Para_V1 &other)
    {
        this->Mass = other.Mass;
        for (size_t i = 0; i < POSIT_DIMENT_V1; i++)
        {
            this->Cog[i] = other.Cog[i];
            this->Orient[i] = other.Orient[i];
            this->Inertia[i] = other.Inertia[i];
        }
        return (*this);
    }
    double Mass;                        // Mass
    double Cog[POSIT_DIMENT_V1];        // centre of Mass expressed in referenced coordinate 负载参数质心位置（Cog）
    double Orient[ORIENT_DIMENT_V1];    // Orient of work-object coordinate expressed in referenced coordinate 负载参数质心的姿态（Orient）
    double Inertia[INERTIA_DIMENT_V1];  // Inertia relative to centre of Mass: Ixx,  Iyy,  Izz  负载惯量（Inertia）
} LoadData_V1;

bool LoadData_ToProxy(const LoadData &loadData, LoadData_V1 &loadData_V1);
bool LoadData_FromProxy(const LoadData_V1 &loadData_V1, LoadData &loadData);

#pragma endregion

#pragma region 工具参数

typedef struct _ToolData_V1
{
    _ToolData_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        RobHold = true;
        TFrame.Initialize();
        TLoad.InitZero();
    }
    _ToolData_V1 &operator=(const _ToolData_V1 &other)
    {
        this->RobHold = other.RobHold;
        this->TFrame = other.TFrame;
        this->TLoad = other.TLoad;
        return (*this);
    }
    bool RobHold;  // True-夹持工具   False-外部工具
    Pose_V1 TFrame;
    LoadData_V1 TLoad;
} ToolData_V1;  // 总计132字节

bool ToolData_ToProxy(const ToolData &toolData, ToolData_V1 &toolData_V1);
bool ToolData_FromProxy(const ToolData_V1 &toolData_V1, ToolData &toolData);

#pragma endregion

#pragma region 工件

typedef struct _WobjData_V1
{
    _WobjData_V1()
    {
        InitZero();
    }
    void Reset()
    {
        InitZero();
    }
    void InitZero()
    {
        RobHold = false;
        UFFix = true;
        memset(&UFMec, 0, MECHUNIT_NAME_LENGTH_V1);
        UFrame.Initialize();
        OFrame.Initialize();
    }
    _WobjData_V1 &operator=(const _WobjData_V1 &other)
    {
        this->RobHold = other.RobHold;
        this->UFFix = other.UFFix;
        memcpy(&this->UFMec, &other.UFMec, MECHUNIT_NAME_LENGTH_V1);
        this->UFrame = other.UFrame;
        this->OFrame = other.OFrame;
        return (*this);
    }

    bool operator==(const _WobjData_V1 &other) const
    {
        if (this->RobHold != other.RobHold)
        {
            return false;
        }

        if (this->UFFix != other.UFFix)
        {
            return false;
        }

        for (size_t i = 0; i < MECHUNIT_NAME_LENGTH_V1; i++)
        {
            if (this->UFMec[i] != other.UFMec[i])
            {
                return false;
            }
        }

        if (!this->UFrame.Compare(other.UFrame))
        {
            return false;
        }

        if (!this->OFrame.Compare(other.OFrame))
        {
            return false;
        }

        return true;
    }

    bool RobHold;                         // 工件是否夹持  true 夹持； FALSE 非夹持
    bool UFFix;                           // 工件是否固定（是否相对于大地坐标系固定、是否相对于法兰盘固定）
    char UFMec[MECHUNIT_NAME_LENGTH_V1];  // 关联的机械单元名称
    Pose_V1 UFrame;
    Pose_V1 OFrame;
} WobjData_V1;  // 总计114字节

bool WobjData_ToProxy(const WobjData &wobjData, WobjData_V1 &wobjData_V1);
bool WobjData_FromProxy(const WobjData_V1 &wobjData_V1, WobjData &wobjData);

#pragma endregion

#pragma region 工具工件标定CsCalibPoints

#define CALIB_POINTS_COUNT_V1 6
#define TOOL_TOTAL_NUM_V1     16
typedef struct _CsCalibPoints_V1
{
    int MethodType;
    RobPos_V1 Points[CALIB_POINTS_COUNT_V1];

    _CsCalibPoints_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        MethodType = 0;
        for (size_t i = 0; i < CALIB_POINTS_COUNT_V1; i++)
        {
            Points[i].Initialize();
        }
    }

    _CsCalibPoints_V1 &operator=(const _CsCalibPoints_V1 &other)
    {
        this->MethodType = other.MethodType;
        for (size_t i = 0; i < CALIB_POINTS_COUNT_V1; i++)
        {
            Points[i] = other.Points[i];
        }
        return (*this);
    }
} CsCalibPoints_V1;

bool CsCalibPoints_ToProxy(const CsCalibPoints &csCalibPoints, CsCalibPoints_V1 &csCalibPoints_V1);
bool CsCalibPoints_FromProxy(const CsCalibPoints_V1 &csCalibPoints_V1, CsCalibPoints &csCalibPoints);

#pragma endregion

#pragma region 用户安装参数UserInstallParam

// 用户安装参数，工具工件负载共用此参数
#define DESCRIPTION_NUM_V1 120
typedef struct _UserInstallParam_V1
{
    char Description[DESCRIPTION_NUM_V1];

    _UserInstallParam_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(Description, 0, DESCRIPTION_NUM_V1);
    }

    _UserInstallParam_V1 &operator=(const _UserInstallParam_V1 &other)
    {
        memcpy(&this->Description[0], &other.Description[0], DESCRIPTION_NUM_V1 * sizeof(char));
        return (*this);
    }
} UserInstallParam_V1;

bool UserInstallParam_ToProxy(const UserInstallParam &userInstallParam, UserInstallParam_V1 &userInstallParam_V1);
bool UserInstallParam_FromProxy(const UserInstallParam_V1 &userInstallParam_V1, UserInstallParam &userInstallParam);

#pragma endregion

#pragma region 工具标定参数

// 工具标定参数
typedef struct _ToolCalibData_V1
{
    int ItemsCount;
    vector<CsCalibPoints_V1> MethodDatas;
    vector<UserInstallParam_V1> ToolUserParams;

    _ToolCalibData_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        ItemsCount = 16;
        MethodDatas.clear();
        ToolUserParams.clear();

        for (size_t i = 0; i < ItemsCount; i++)
        {
            CsCalibPoints_V1 csCalibPoints;
            MethodDatas.push_back(csCalibPoints);

            UserInstallParam_V1 userInstallParam;
            ToolUserParams.push_back(userInstallParam);
        }
    }

    _ToolCalibData_V1 &operator=(const _ToolCalibData_V1 &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->MethodDatas.clear();
        this->MethodDatas.assign(other.MethodDatas.begin(), other.MethodDatas.end());
        this->ToolUserParams.clear();
        this->ToolUserParams.assign(other.ToolUserParams.begin(), other.ToolUserParams.end());
        return (*this);
    }
} ToolCalibData_V1;

bool ToolCalibData_ToProxy(const ToolCalibData &toolCalibData, ToolCalibData_V1 &toolCalibData_V1);
bool ToolCalibData_FromProxy(const ToolCalibData_V1 &toolCalibData_V1, ToolCalibData &toolCalibData);

#pragma endregion

#pragma region 臂上负载

// 臂上负载（对齐方式不同）
typedef struct _Arm_Load_Data_V1
{
    _Arm_Load_Data_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        Mass = 0;
        for (size_t i = 0; i < POSIT_DIMENT_V1; i++)
        {
            Cog[i] = 0;
            Orient[i] = 0;
            Inertia[i] = 0;
        }
    }
    _Arm_Load_Data_V1 &operator=(const _Arm_Load_Data_V1 &other)
    {
        this->Mass = other.Mass;
        for (size_t i = 0; i < POSIT_DIMENT_V1; i++)
        {
            this->Cog[i] = other.Cog[i];
            this->Orient[i] = other.Orient[i];
            this->Inertia[i] = other.Inertia[i];
        }
        return (*this);
    }
    double Mass;                        // Mass
    double Cog[POSIT_DIMENT_V1];        // centre of Mass expressed in referenced coordinate 负载参数质心位置（Cog）
    double Orient[ORIENT_DIMENT_V1];    // Orient of work-object coordinate expressed in referenced coordinate 负载参数质心的姿态（Orient）
    double Inertia[INERTIA_DIMENT_V1];  // Inertia relative to centre of Mass: Ixx,  Iyy,  Izz  负载惯量（Inertia）
} ArmLoadData_V1;                       // 80字节

bool ArmLoadData_ToProxy(const ArmLoadData &armLoadData, ArmLoadData_V1 &armLoadData_V1);
bool ArmLoadData_FromProxy(const ArmLoadData_V1 &armLoadData_V1, ArmLoadData &armLoadData);

#pragma endregion

#pragma region 机器人臂上（额外）负载

// 机器人臂上（额外）负载的定义，相对于关节坐标系
typedef struct _Robot_Arm_Load_Para_V1
{
    int16u linkNum;  // number of the link on which the load has been mounted
    short reserved;  // reserved data, using for nothing currently
    ArmLoadData_V1 load;
} ArmLoadPara_V1;

bool ArmLoadPara_ToProxy(const ArmLoadPara &armLoadPara, ArmLoadPara_V1 &armLoadPara_V1);
bool ArmLoadPara_FromProxy(const ArmLoadPara_V1 &armLoadPara_V1, ArmLoadPara &armLoadPara);

#pragma endregion

#pragma region 干涉区 &监控对象(笛卡尔位置监控)

#define IZONE_DESCRIPTION_CHARLENGTH_V1    (32)   // 干涉区有关备注, 全部为32长度字符数组
#define IZONE_FLOATARRAYLENGTH_V1          (6)    // 干涉区有关浮点数数组, 大部分为6长度
#define IZONE_MTCP_UINTARRAYLENGTH_V1      (4)    // MTCPshort数组, 为4长度
#define IZONE_BALL_POSARRAYLENGTH_V1       (3)    // Ball Pos数组, 3长度
#define IZONE_TOOLBOX_TYPE3_FLOATARRAY_V1  (13)   // TOOLBOX第三种类型, 浮点数数组长度13
#define IZONE_INTERFERZONESSTATUSLENGTH_V1 (16)   // 干涉区状态长度16
#define IZONE_ITOOL_TYPENUM_V1             (4)    // 末端监测对象类别数目4
#define IZONE_ITOOL_TOOLBOXTYPENUM_V1      (3)    // 工具包围盒类型数目3
#define IZONE_EPSILON_V1                   (0.1)  // 工具包围盒类型数目3
#define IZONE_WOBJPARAMSNUM_V1             (12)   // 干涉区工具工件参数相关
#define IZONE_MTCPTOOLPARAMSNUM_V1         (6)    // 干涉区工具工件参数相关

// 干涉区
typedef struct INTERFER_ZONE_V1
{
    INTERFER_ZONE_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        u16Index = 0xffff;
        memset(cRemarks, 0, IZONE_DESCRIPTION_CHARLENGTH_V1);
        i32Input = -1;
        i32Output = -1;
        u16Scope = 0xffff;
        u16IsAlert = 0xffff;
        f32SafeL = 0;
        u16WobjNum = 0xffff;
        i16StopType = -1;
        i16ZoneType = -1;
        i16ForeCast = -1;

        u16SetType = 0xffff;
        memset(f32Diagonal, 0, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memset(f32PointL, 0, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
    }

    INTERFER_ZONE_V1 &operator=(const INTERFER_ZONE_V1 &other)
    {
        u16Index = other.u16Index;
        memcpy(cRemarks, other.cRemarks, IZONE_DESCRIPTION_CHARLENGTH_V1);
        i32Input = other.i32Input;
        i32Output = other.i32Output;
        u16Scope = other.u16Scope;
        u16IsAlert = other.u16IsAlert;
        f32SafeL = other.f32SafeL;
        u16WobjNum = other.u16WobjNum;
        i16StopType = other.i16StopType;
        i16ZoneType = other.i16ZoneType;
        i16ForeCast = other.i16ForeCast;

        u16SetType = other.u16SetType;
        memcpy(f32Diagonal, other.f32Diagonal, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memcpy(f32PointL, other.f32PointL, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE_V1 &other)
    {
        if (this == &other)
            return true;

        if (u16Index != other.u16Index)
            return false;
        if (strcmp(cRemarks, other.cRemarks) != 0)
            return false;
        if (i32Input != other.i32Input)
            return false;
        if (i32Output != other.i32Output)
            return false;
        if (u16Scope != other.u16Scope)
            return false;
        if (u16IsAlert != other.u16IsAlert)
            return false;
        if (fabs(f32SafeL - other.f32SafeL) > IZONE_EPSILON_V1)
            return false;
        if (u16WobjNum != other.u16WobjNum)
            return false;
        if (i16StopType != other.i16StopType)
            return false;
        if (i16ZoneType != other.i16ZoneType)
            return false;
        if (i16ForeCast != other.i16ForeCast)
            return false;
        if (u16SetType != other.u16SetType)
            return false;
        for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH_V1; i++)
        {
            if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > IZONE_EPSILON_V1)
                return false;
        }
        for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH_V1; i++)
        {
            if (fabs(f32PointL[i] - other.f32PointL[i]) > IZONE_EPSILON_V1)
                return false;
        }

        return true;
    }

    bool IsValid()
    {
        if (u16Index < 0 || u16Index > 15)
            return false;

        return true;
    }

    unsigned short u16Index;                        /* 第x组参数 */
    char cRemarks[IZONE_DESCRIPTION_CHARLENGTH_V1]; /* 备注 */
    int i32Input;                                   /* 输入信号 */
    int i32Output;                                  /* 输出信号 */
    unsigned short u16Scope;                        /* 内外侧 0-内侧，1-外侧 */
    unsigned short u16IsAlert;                      /* 是否报警 0-警告，1-报警 */
    float f32SafeL;                                 /* 安全距离 */
    unsigned short u16WobjNum;                      /* 当前工件号 */
    short i16StopType;                              /* 停机方式 */
    short i16ZoneType;                              /* 干涉区类型 */
    short i16ForeCast;                              /* 是否开启目标点预测 */
    /* 干涉区 */
    unsigned short u16SetType;                    /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[IZONE_FLOATARRAYLENGTH_V1]; /* 对角点 */
    float f32PointL[IZONE_FLOATARRAYLENGTH_V1];   /* 基准点+偏移 */
} INTERFER_ZONE_V1;

bool INTERFER_ZONE_ToProxy(const INTERFER_ZONE &interfer_ZONE, INTERFER_ZONE_V1 &interfer_ZONE_V1);
bool INTERFER_ZONE_FromProxy(const INTERFER_ZONE_V1 &interfer_ZONE_V1, INTERFER_ZONE &interfer_ZONE);

// 末端监测对象MTCP
typedef struct INTERFER_MTCP_BOX_V1
{
    INTERFER_MTCP_BOX_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(u16IsUse, 0, IZONE_MTCP_UINTARRAYLENGTH_V1 * sizeof(unsigned short));
        memset(u16ToolNum, 0, IZONE_MTCP_UINTARRAYLENGTH_V1 * sizeof(unsigned short));
    }
    INTERFER_MTCP_BOX_V1 &operator=(const INTERFER_MTCP_BOX_V1 &other)
    {
        memcpy(u16IsUse, other.u16IsUse, IZONE_MTCP_UINTARRAYLENGTH_V1 * sizeof(unsigned short));
        memcpy(u16ToolNum, other.u16ToolNum, IZONE_MTCP_UINTARRAYLENGTH_V1 * sizeof(unsigned short));
        return (*this);
    }
    bool operator==(const INTERFER_MTCP_BOX_V1 &other)
    {
        if (this == &other)
            return true;
        for (size_t i = 0; i < IZONE_MTCP_UINTARRAYLENGTH_V1; i++)
        {
            if (u16IsUse[i] != other.u16IsUse[i])
                return false;
        }
        for (size_t i = 0; i < IZONE_MTCP_UINTARRAYLENGTH_V1; i++)
        {
            if (u16ToolNum[i] != other.u16ToolNum[i])
                return false;
        }
        return true;
    }
    unsigned short u16IsUse[IZONE_MTCP_UINTARRAYLENGTH_V1];
    unsigned short u16ToolNum[IZONE_MTCP_UINTARRAYLENGTH_V1];
} INTERFER_MTCP_BOX_V1;

bool INTERFER_MTCP_BOX_ToProxy(const INTERFER_MTCP_BOX &interfer_MTCP_BOX, INTERFER_MTCP_BOX_V1 &interfer_MTCP_BOX_V1);
bool INTERFER_MTCP_BOX_FromProxy(const INTERFER_MTCP_BOX_V1 &interfer_MTCP_BOX_V1, INTERFER_MTCP_BOX &interfer_MTCP_BOX);

// 末端监测对象球体
typedef struct INTERFER_BALL_BOX_V1
{
    INTERFER_BALL_BOX_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(f32Pos, 0, IZONE_BALL_POSARRAYLENGTH_V1 * sizeof(float));
        f32BallR = 0;
    }
    INTERFER_BALL_BOX_V1 &operator=(const INTERFER_BALL_BOX_V1 &other)
    {
        memcpy(f32Pos, other.f32Pos, IZONE_BALL_POSARRAYLENGTH_V1 * sizeof(float));
        f32BallR = other.f32BallR;
        return (*this);
    }
    bool operator==(const INTERFER_BALL_BOX_V1 &other)
    {
        if (this == &other)
            return true;

        for (size_t i = 0; i < IZONE_BALL_POSARRAYLENGTH_V1; i++)
        {
            if (fabs(f32Pos[i] - other.f32Pos[i]) > IZONE_EPSILON_V1)
                return false;
        }
        if (fabs(f32BallR - other.f32BallR) > IZONE_EPSILON_V1)
            return false;

        return true;
    }

    float f32Pos[IZONE_BALL_POSARRAYLENGTH_V1];
    float f32BallR;
} INTERFER_BALL_BOX_V1;

bool INTERFER_BALL_BOX_ToProxy(const INTERFER_BALL_BOX &interfer_BALL_BOX, INTERFER_BALL_BOX_V1 &interfer_BALL_BOX_V1);
bool INTERFER_BALL_BOX_FromProxy(const INTERFER_BALL_BOX_V1 &interfer_BALL_BOX_V1, INTERFER_BALL_BOX &interfer_BALL_BOX);

// 末端监测对象长方体包围盒
typedef struct INTERFER_TOOL_BOX_V1
{
    INTERFER_TOOL_BOX_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        u16SetType = 0;
        memset(f32Diagonal, 0, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memset(f32PointL, 0, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memset(f32PointH, 0, IZONE_TOOLBOX_TYPE3_FLOATARRAY_V1 * sizeof(float));
    }
    INTERFER_TOOL_BOX_V1 &operator=(const INTERFER_TOOL_BOX_V1 &other)
    {
        u16SetType = other.u16SetType;
        memcpy(f32Diagonal, other.f32Diagonal, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memcpy(f32PointL, other.f32PointL, IZONE_FLOATARRAYLENGTH_V1 * sizeof(float));
        memcpy(f32PointH, other.f32PointH, IZONE_TOOLBOX_TYPE3_FLOATARRAY_V1 * sizeof(float));
        return (*this);
    }
    bool operator==(const INTERFER_TOOL_BOX_V1 &other)
    {
        if (this == &other)
            return true;
        if (u16SetType != other.u16SetType)
            return false;
        if (u16SetType == 0)
        {
            for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH_V1; i++)
            {
                if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > IZONE_EPSILON_V1)
                    return false;
            }
        }
        else if (u16SetType == 1)
        {
            for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH_V1; i++)
            {
                if (fabs(f32PointL[i] - other.f32PointL[i]) > IZONE_EPSILON_V1)
                    return false;
            }
        }
        else
        {
            for (size_t i = 0; i < IZONE_TOOLBOX_TYPE3_FLOATARRAY_V1; i++)
            {
                if (fabs(f32PointH[i] - other.f32PointH[i]) > IZONE_EPSILON_V1)
                    return false;
            }
        }

        return true;
    }

    unsigned short u16SetType;                          /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[IZONE_FLOATARRAYLENGTH_V1];       /* 对角点 */
    float f32PointL[IZONE_FLOATARRAYLENGTH_V1];         /* 基准点+偏移 */
    float f32PointH[IZONE_TOOLBOX_TYPE3_FLOATARRAY_V1]; /* 取点+高度 */
} INTERFER_TOOL_BOX_V1;

bool INTERFER_TOOL_BOX_ToProxy(const INTERFER_TOOL_BOX &interfer_TOOL_BOX, INTERFER_TOOL_BOX_V1 &interfer_TOOL_BOX_V1);
bool INTERFER_TOOL_BOX_FromProxy(const INTERFER_TOOL_BOX_V1 &interfer_TOOL_BOX_V1, INTERFER_TOOL_BOX &interfer_TOOL_BOX);

/* 监控对象, 内含MTCP, 球体, 长方体包围盒 */
typedef struct INTERFER_TOOL_V1
{
    INTERFER_TOOL_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        u16Index = 0;
        u16Type = 0;
        memset(cRemarks, 0, IZONE_DESCRIPTION_CHARLENGTH_V1);

        stMTcpBox.Initialize();
        stBallBox.Initialize();
        stToolBox.Initialize();
    }
    INTERFER_TOOL_V1 &operator=(const INTERFER_TOOL_V1 &other)
    {
        u16Index = other.u16Index;
        u16Type = other.u16Type;
        memcpy(cRemarks, other.cRemarks, IZONE_DESCRIPTION_CHARLENGTH_V1);

        stMTcpBox = other.stMTcpBox;
        stBallBox = other.stBallBox;
        stToolBox = other.stToolBox;
        return (*this);
    }
    bool operator==(const INTERFER_TOOL_V1 &other)
    {
        if (this == &other)
            return true;

        if (u16Index != other.u16Index)
            return false;
        if (u16Type != other.u16Type)
            return false;
        if (strcmp(cRemarks, other.cRemarks) != 0)
            return false;

        if (!(stMTcpBox == other.stMTcpBox))
            return false;
        if (!(stBallBox == other.stBallBox))
            return false;
        if (!(stToolBox == other.stToolBox))
            return false;

        return true;
    }
    unsigned short u16Index;                        /* 第x组参数 */
    unsigned short u16Type;                         /* 监控对象类型 */
    char cRemarks[IZONE_DESCRIPTION_CHARLENGTH_V1]; /* 备注 */
    INTERFER_MTCP_BOX_V1 stMTcpBox;
    INTERFER_BALL_BOX_V1 stBallBox;
    INTERFER_TOOL_BOX_V1 stToolBox;
} INTERFER_TOOL_V1;

bool INTERFER_TOOL_ToProxy(const INTERFER_TOOL &interfer_TOOL, INTERFER_TOOL_V1 &interfer_TOOL_V1);
bool INTERFER_TOOL_FromProxy(const INTERFER_TOOL_V1 &interfer_TOOL_V1, INTERFER_TOOL &interfer_TOOL);

// 干涉区激活状态
typedef struct INTERFER_ZONES_STATUS_V1
{
    INTERFER_ZONES_STATUS_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(uint16IZonesIndex, 0, IZONE_INTERFERZONESSTATUSLENGTH_V1 * sizeof(unsigned short));
        memset(cRemarks, 0, IZONE_INTERFERZONESSTATUSLENGTH_V1 * IZONE_DESCRIPTION_CHARLENGTH_V1);
    }
    unsigned short uint16IZonesIndex[16];
    char cRemarks[16][32];

} INTERFER_ZONES_STATUS_V1;

bool INTERFER_ZONES_STATUS_ToProxy(const INTERFER_ZONES_STATUS &interfer_ZONES_STATUS, INTERFER_ZONES_STATUS_V1 &interfer_ZONES_STATUS_V1);
bool INTERFER_ZONES_STATUS_FromProxy(const INTERFER_ZONES_STATUS_V1 &interfer_ZONES_STATUS_V1, INTERFER_ZONES_STATUS &interfer_ZONES_STATUS);

// 干涉区工件参数相关
typedef struct INTERFER_ZONE_WOBJPARAM_V1
{
    INTERFER_ZONE_WOBJPARAM_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterWobjParams, 0, sizeof(InterWobjParams));
    }
    INTERFER_ZONE_WOBJPARAM_V1 &operator=(const INTERFER_ZONE_WOBJPARAM_V1 &other)
    {
        memcpy(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE_WOBJPARAM_V1 &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams)))
            return false;

        return true;
    }
    double InterWobjParams[IZONE_WOBJPARAMSNUM_V1];  // 干涉区 - 工件 - 工件坐标系
} INTERFER_ZONE_WOBJPARAM_V1;

bool INTERFER_ZONE_WOBJPARAM_ToProxy(const INTERFER_ZONE_WOBJPARAM &interfer_ZONE_WOBJPARAM, INTERFER_ZONE_WOBJPARAM_V1 &interfer_ZONE_WOBJPARAM_V1);
bool INTERFER_ZONE_WOBJPARAM_FromProxy(const INTERFER_ZONE_WOBJPARAM_V1 &interfer_ZONE_WOBJPARAM_V1, INTERFER_ZONE_WOBJPARAM &interfer_ZONE_WOBJPARAM);

// 干涉区工具参数相关
typedef struct INTERFER_ZONE_MTCPTOOLPARAM_V1
{
    INTERFER_ZONE_MTCPTOOLPARAM_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterTFramePos, 0, sizeof(InterTFramePos));
    }

    INTERFER_ZONE_MTCPTOOLPARAM_V1 &operator=(const INTERFER_ZONE_MTCPTOOLPARAM_V1 &other)
    {
        memcpy(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE_MTCPTOOLPARAM_V1 &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos)))
            return false;

        return true;
    }
    double InterTFramePos[IZONE_MTCPTOOLPARAMSNUM_V1 * IZONE_MTCP_UINTARRAYLENGTH_V1];  // 末端监控对象MTCP - 工具参数
} INTERFER_ZONE_MTCPTOOLPARAM_V1;

bool INTERFER_ZONE_MTCPTOOLPARAM_ToProxy(const INTERFER_ZONE_MTCPTOOLPARAM &interfer_ZONE_MTCPTOOLPARAM, INTERFER_ZONE_MTCPTOOLPARAM_V1 &interfer_ZONE_MTCPTOOLPARAM_V1);
bool INTERFER_ZONE_MTCPTOOLPARAM_FromProxy(const INTERFER_ZONE_MTCPTOOLPARAM_V1 &interfer_ZONE_MTCPTOOLPARAM_V1, INTERFER_ZONE_MTCPTOOLPARAM &interfer_ZONE_MTCPTOOLPARAM);

#pragma endregion

#pragma region 零点校准

#define JOINT_AXIS_NUM_SIX_V1 6  // 六关节轴数

/// <summary>
/// 参数结构体
/// </summary>
struct ZeroPointCalibrateParam_V1
{
    ZeroPointCalibrateParam_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        i16Axis = 0;
        i32Value = 0;
        i16Status = 0;
        bChecked = false;
        bCalibrateIsSuccessed = false;
        i16MotionType = 0;
        i32CollisionMode = 0;
        bJposPreZeroFlag = false;
    }
    int16s i16Axis;              // 轴号
    int i32Value;                // 校准值
    int16s i16Status;            // 校准状态
    bool bChecked;               // 选中标志
    bool bCalibrateIsSuccessed;  // 校准成功标志
    int16s i16MotionType;        // 校准运动类型
    int i32CollisionMode;        // 碰撞方式
    bool bJposPreZeroFlag;       // 预校准位置置零标志
};

bool ZeroPointCalibrateParam_ToProxy(const ZeroPointCalibrateParam &zeroPointCalibrateParam, ZeroPointCalibrateParam_V1 &zeroPointCalibrateParam_V1);
bool ZeroPointCalibrateParam_FromProxy(const ZeroPointCalibrateParam_V1 &zeroPointCalibrateParam_V1, ZeroPointCalibrateParam &zeroPointCalibrateParam);

/// <summary>
/// 参数重置结构体
/// </summary>
struct ZeroPointResetParam_V1
{
    ZeroPointResetParam_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        for (size_t i = 0; i < JOINT_AXIS_NUM_SIX_V1; i++)
        {
            i32PosOffset[i] = 0;
            f64EmptyLoadCurrent[i] = 0.0;
        }
    }
    int i32PosOffset[JOINT_AXIS_NUM_SIX_V1];            // 零点偏置
    double f64EmptyLoadCurrent[JOINT_AXIS_NUM_SIX_V1];  // 空载电流
};

bool ZeroPointResetParam_ToProxy(const ZeroPointResetParam &zeroPointResetParam, ZeroPointResetParam_V1 &zeroPointResetParam_V1);
bool ZeroPointResetParam_FromProxy(const ZeroPointResetParam_V1 &zeroPointResetParam_V1, ZeroPointResetParam &zeroPointResetParam);

/// <summary>
/// 校准命令结构体
/// </summary>
struct ZeroPointCommand_V1
{
    ZeroPointCommand_V1()
    {
        i16Axis = 0;
        i16Direction = 1;
        i16Command = 0;
        i16Type = 0;
    }
    ZeroPointCommand_V1(int16s axisNo, int16s direction, int16s command, int16s type = 0)
    {
        i16Axis = axisNo;
        i16Direction = direction;
        i16Command = command;
        i16Type = type;
    }
    int16s i16Axis;       // 轴号(0~5)
    int16s i16Direction;  // 方向(正向:1 反向:-1)
    int16s i16Command;    // 校准命令(开始:1 停止:0)
    int16s i16Type;       // 运动类型(预校准:0 校准:1 回零:2)
};

bool ZeroPointCommand_ToProxy(const ZeroPointCommand &zeroPointCommand, ZeroPointCommand_V1 &zeroPointCommand_V1);
bool ZeroPointCommand_FromProxy(const ZeroPointCommand_V1 &zeroPointCommand_V1, ZeroPointCommand &zeroPointCommand);

/// <summary>
/// 状态反馈结构体
/// </summary>
struct ZeroPointResult_V1
{
    ZeroPointResult_V1()
    {
        i16Axis = 0;
        i16Status = 0;
        i32Value = 0;
        i16Type = 0;
    }
    int16s i16Axis;    // 轴号(0~5)
    int16s i16Status;  // 状态(开始:0 运行中:1 成功:2 中断:3 失败:4 停止:5)
    int i32Value;      // 数值(普通模式:绝对零点值 测试模式:零点偏置值)
    int16s i16Type;    // 运动类型(预校准:0 校准:1 回零:2)
};

bool ZeroPointResult_ToProxy(const ZeroPointResult &zeroPointResult, ZeroPointResult_V1 &zeroPointResult_V1);
bool ZeroPointResult_FromProxy(const ZeroPointResult_V1 &zeroPointResult_V1, ZeroPointResult &zeroPointResult);

/// <summary>
/// 传感器开关命令结构体
/// </summary>
struct ZeroPointSensorSwitch_V1
{
    ZeroPointSensorSwitch_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        i8AxisNo = 0;
        bSwitchFlag = false;
    }

    int8u i8AxisNo;    // 轴号
    bool bSwitchFlag;  // 开关标志(false-关，true-开)
};

bool ZeroPointSensorSwitch_ToProxy(const ZeroPointSensorSwitch &zeroPointSensorSwitch, ZeroPointSensorSwitch_V1 &zeroPointSensorSwitch_V1);
bool ZeroPointSensorSwitch_FromProxy(const ZeroPointSensorSwitch_V1 &zeroPointSensorSwitch_V1, ZeroPointSensorSwitch &zeroPointSensorSwitch);

/// <summary>
/// 开发者模式下的零点参数
/// </summary>
struct ZeroPointParamDeveloper_V1
{
    ZeroPointParamDeveloper_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        i16LoadState = 0;
        i16Mode = 0;
        for (size_t i = 0; i < JOINT_AXIS_NUM_SIX_V1; i++)
        {
            i32OffSetLoad0[i] = 0;
            i32OffSetLoad1[i] = 0;
            i32OffSetLoad2[i] = 0;
            f32TrqLoad0[i] = 0.0;
            f32TrqLoad1[i] = 0.0;
            f32TrqLoad2[i] = 0.0;
            f32CompensationK[i] = 0.0;
            f32CompensationB[i] = 0.0;
        }
    }

    int16s i16LoadState;                            // 负载状态：0-空载，1-负载1，2-负载2
    int16s i16Mode;                                 // 模式标志：0-普通模式，1-开发者模式
    int i32OffSetLoad0[JOINT_AXIS_NUM_SIX_V1];      // 空载零点偏置
    int i32OffSetLoad1[JOINT_AXIS_NUM_SIX_V1];      // 空载零点偏置
    int i32OffSetLoad2[JOINT_AXIS_NUM_SIX_V1];      // 空载零点偏置
    float f32TrqLoad0[JOINT_AXIS_NUM_SIX_V1];       // 空载碰撞前电流
    float f32TrqLoad1[JOINT_AXIS_NUM_SIX_V1];       // 空载碰撞前电流
    float f32TrqLoad2[JOINT_AXIS_NUM_SIX_V1];       // 空载碰撞前电流
    float f32CompensationK[JOINT_AXIS_NUM_SIX_V1];  // 负载补偿斜率
    float f32CompensationB[JOINT_AXIS_NUM_SIX_V1];  // 负载补偿截距
};

bool ZeroPointParamDeveloper_ToProxy(const ZeroPointParamDeveloper &zeroPointParamDeveloper, ZeroPointParamDeveloper_V1 &zeroPointParamDeveloper_V1);
bool ZeroPointParamDeveloper_FromProxy(const ZeroPointParamDeveloper_V1 &zeroPointParamDeveloper_V1, ZeroPointParamDeveloper &zeroPointParamDeveloper);

#pragma endregion

#pragma region 机器人Home点触发IO信号数据

// 机器人Home点触发IO信号数据 结构体
typedef struct tagJHomeTriggertOutData_V1
{
    tagJHomeTriggertOutData_V1()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    bool operator==(const tagJHomeTriggertOutData_V1 &in)
    {
        if (index == in.index && mode == in.mode && outNum == in.outNum)
        {
            for (size_t i = 0; i < JOINT_AXIS_NUM_V1; ++i)
            {
                if (abs(JointOffsetData[i] - in.JointOffsetData[i]) > 1e-6)
                    return false;
            }
            for (size_t i = 0; i < EXT_AXIS_NUM_V1; ++i)
            {
                if (abs(EPosOffsetData[i] - in.EPosOffsetData[i]) > 1e-6)
                    return false;
            }
            return true;
        }
        return false;
    }
    tagJHomeTriggertOutData_V1 &operator=(const tagJHomeTriggertOutData_V1 &in)
    {
        index = in.index;
        mode = in.mode;
        outNum = in.outNum;
        for (size_t i = 0; i < JOINT_AXIS_NUM_V1; i++)
        {
            JointOffsetData[i] = in.JointOffsetData[i];
        }
        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
        {
            EPosOffsetData[i] = in.EPosOffsetData[i];
        }
        return *this;
    }
    void Initialize()
    {
        index = 0;
        mode = 0;
        outNum = -1;
        for (size_t i = 0; i < JOINT_AXIS_NUM_V1; i++)
        {
            JointOffsetData[i] = 0.0;
        }
        for (size_t i = 0; i < EXT_AXIS_NUM_V1; i++)
        {
            EPosOffsetData[i] = 0.0;
        }
    }
    int index;
    int mode;
    int outNum;
    double JointOffsetData[JOINT_AXIS_NUM_V1];  // J1-J8
    double EPosOffsetData[EXT_AXIS_NUM_V1];     // E1-E6
} JHomeTriggertOutData_V1;

bool JHomeTriggertOutData_ToProxy(const JHomeTriggertOutData &jHomeTriggertOutData, JHomeTriggertOutData_V1 &jHomeTriggertOutData_V1);
bool JHomeTriggertOutData_FromProxy(const JHomeTriggertOutData_V1 &jHomeTriggertOutData_V1, JHomeTriggertOutData &jHomeTriggertOutData);

#pragma endregion

#pragma region P点带标签名备注

// P点带标签名、备注
typedef struct M_ROB_POS_ITEM_V1
{
    M_ROB_POS_ITEM_V1()
    {
        Clear();
    }

    void Clear()
    {
        PointNo = 0;
        PData.Initialize();
        LabelName.clear();
        Description.clear();
    }

    M_ROB_POS_ITEM_V1 &operator=(const M_ROB_POS_ITEM_V1 &other)
    {
        this->PointNo = other.PointNo;
        this->PData = other.PData;
        this->LabelName = other.LabelName;
        this->Description = other.Description;

        return (*this);
    }

    bool operator==(const M_ROB_POS_ITEM_V1 &other) const
    {
        if (this->PointNo != other.PointNo)
        {
            return false;
        }

        if (!(this->PData == other.PData))
        {
            return false;
        }

        if (this->LabelName != other.LabelName)
        {
            return false;
        }

        if (this->Description != other.Description)
        {
            return false;
        }

        return true;
    }

    int PointNo;
    RobPos_V1 PData;
    std::string LabelName;    // 标签名
    std::string Description;  // 描述
} MRobPosItem_V1;

bool MRobPosItem_ToProxy(const MRobPosItem &mRobPosItem, MRobPosItem_V1 &mRobPosItem_V1);
bool MRobPosItem_FromProxy(const MRobPosItem_V1 &mRobPosItem_V1, MRobPosItem &mRobPosItem);

#pragma endregion

#pragma region 实时数据(周期数据)

enum eRealRunStat_V1
{
    REALRUNSTAT_STOP_V1 = 0,
    REALRUNSTAT_STARTUP_V1 = 1,
    REALRUNSTAT_FORWARD_V1 = 2,
    REALRUNSTAT_BACK_V1 = 3,
    REALRUNSTAT_PAUSE_V1 = 4,  // add by Bruce.nie 2015-06-05
    REALRUNSTAT_BUTT_V1
};

eRealRunStat_V1 eRealRunStat_ToProxy(eRealRunStat erealRunStat);
eRealRunStat eRealRunStat_FromProxy(eRealRunStat_V1 erealRunStat_V1);

typedef struct _RCSTS_INFO_0322_V1
{
    _RCSTS_INFO_0322_V1()
    {
        nStart = REALRUNSTAT_STOP_V1;
        nEmerg = 0;
        nEnable = 0;
        nMode = 0;
        nSpeed = 0;
        nCoord = 0;
        nToolNo = 0;
        nWobjNo = 0;
        nLoadNo = 0;
        nErrId = 0;
        nWarnId = 0;
        memset(&uCommState[0], 0, MODULE_NUM_V1 * sizeof(int16u));
        memset(&OutState[0], 0, MAXIONUM_V1 * sizeof(int8u));
        memset(&DAState[0], 0, MAXDANUM_V1 * sizeof(int8u));
        iSafeDoorSts = 0;
        iDynBrake = 0;
        iPowerLv = 0;
        StepGrade = 0;  // 寸动等级（0-无寸动 1-G1 2-G2 3-G3 4-U）
        MechLock = 0;   // 机械锁定  0-未锁定, 1-锁定
        ToolObjMatchFlag = IS_MATCH_V1;
        memset(&CurPos, 0, JOINT_AXIS_NUM_V1 * sizeof(double));
        PosFormat = FORMAT_JOINT_V1;
        memset(&MechUnitState, 0, MAX_MECHUNIT_NUM_V1 * sizeof(int8u));
        memset(&CooperateMechUnitName, 0, MECHUNIT_NAME_LENGTH_V1 * sizeof(char));
        meetConditionsFlag = 0;
    }

    _RCSTS_INFO_0322_V1 &operator=(const _RCSTS_INFO_0322_V1 &other)
    {
        this->nStart = other.nStart;
        this->nEmerg = other.nEmerg;
        this->nEnable = other.nEnable;
        this->nMode = other.nMode;
        this->nSpeed = other.nSpeed;
        this->nCoord = other.nCoord;
        this->nToolNo = other.nToolNo;
        this->nWobjNo = other.nWobjNo;
        this->nLoadNo = other.nLoadNo;
        this->nErrId = other.nErrId;
        this->nWarnId = other.nWarnId;
        memcpy(&this->uCommState[0], &other.uCommState[0], MODULE_NUM_V1 * sizeof(int16u));
        memcpy(&this->OutState[0], &other.OutState[0], MAXIONUM_V1 * sizeof(int8u));
        memcpy(&this->DAState[0], &other.DAState[0], MAXDANUM_V1 * sizeof(int8u));
        this->iSafeDoorSts = other.iSafeDoorSts;
        this->iDynBrake = other.iDynBrake;
        this->iPowerLv = other.iPowerLv;
        this->StepGrade = other.StepGrade;
        this->MechLock = other.MechLock;
        this->ToolObjMatchFlag = other.ToolObjMatchFlag;
        memcpy(&this->CurPos[0], &other.CurPos[0], JOINT_AXIS_NUM_V1 * sizeof(double));
        this->PosFormat = other.PosFormat;
        memcpy(&this->MechUnitState[0], &other.MechUnitState[0], MAX_MECHUNIT_NUM_V1 * sizeof(int8u));
        memcpy(&this->CooperateMechUnitName[0], &other.CooperateMechUnitName[0], MECHUNIT_NAME_LENGTH_V1 * sizeof(char));
        this->meetConditionsFlag = other.meetConditionsFlag;
        return (*this);
    }
    int16u nStart;                                        // 0 停止，1 启动，2 前进，3 后退，4暂停
    int16u nEmerg;                                        // 1 急停, 0 非急停
    int16u nEnable;                                       // 1 使能, 0 非使能
    int16u nMode;                                         // 1->示教 2->再现 3->单步示教检查 5-> 连续示教检查 6-> 回零
    int16u nSpeed;                                        // 速度值
    int16u nCoord;                                        // 1 2 3 4 5    关节、基坐标、工具、工件、世界
    int16u nToolNo;                                       // 工具号
    int16u nWobjNo;                                       // 工件号
    int16u nLoadNo;                                       // 负载号
    int32s nErrId;                                        // 报警号
    int32s nWarnId;                                       // 警告号
    int16u uCommState[8];                                 // 控制器端各个模块的通信状态(通信状态页面，某些检测USB、存储卡状态)
    int8u OutState[MAXIONUM_V1];                          // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE
    int8u DAState[MAXDANUM_V1];                           // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE
    int8u iSafeDoorSts;                                   // 安全门警示状态 0-无警示 1-有警示
    int8u iDynBrake;                                      // 动态制动开关 0-关(下使能好推动) 1-开
    int8u iPowerLv;                                       // 0-低功率 1-高功率
    int8u StepGrade;                                      // 寸动等级（0-无寸动 1-G1 2-G2 3-G3 4-U）
    int8u MechLock;                                       // 机械锁定状态（0：未锁定 1：锁定）
    int8u ToolObjMatchFlag;                               // 当前工具和工件是否匹配（0：匹配 1：工具与工件不匹配 2：工件参数不匹配）
    double CurPos[JOINT_AXIS_NUM_V1];                     // 当前激活机械单元的位置数据（关节或笛卡尔）
    int8u PosFormat;                                      // 位置格式   1 2 3 4 5    关节、基坐标、法兰、工件、世界
    int8u MechUnitState[MAX_MECHUNIT_NUM_V1];             // 机械单元的状态（0 正常，1 激活）
    char CooperateMechUnitName[MECHUNIT_NAME_LENGTH_V1];  // 机器人协调的机械单元名称
    int8u meetConditionsFlag;                             // 当前机械单元是否满足协调条件（0不满足，1满足）
    int8u uCoRobotBodyPowerState = 0;                     // **********当前机器人本体上电状态 协作专用**********
    int8u uGripperThreePositionEnable = 0;                // **********夹持器三位置使能(1:使能 其他:非使能) 协作专用**********
} RCSTS_INFO_0322_V1;

bool RCSTS_INFO_0322_ToProxy(const RCSTS_INFO_0322 &rcsts_INFO_0322, RCSTS_INFO_0322_V1 &rcsts_INFO_0322_V1);
bool RCSTS_INFO_0322_FromProxy(const RCSTS_INFO_0322_V1 &rcsts_INFO_0322_V1, RCSTS_INFO_0322 &rcsts_INFO_0322);

#pragma endregion

#pragma region VISION_ERR_PARAM

typedef struct
{
    double XavgError;    // x方向平均误差
    double YavgError;    // y方向平均误差
    double XmaxError;    // x方向最大误差
    double YmaxError;    // y方向最大误差
    double XmmPerPixel;  // x方向单位像素的尺寸
    double YmmPerPixel;  // y方向单位像素的尺寸
    double ToolOffsetX;  // x方向工具偏移
    double ToolOffsetY;  // y方向工具偏移
} VISION_ERR_PARAM_V1;

bool VISION_ERR_PARAM_ToProxy(const VISION_ERR_PARAM &vision_ERR_PARAM, VISION_ERR_PARAM_V1 &vision_ERR_PARAM_V1);
bool VISION_ERR_PARAM_FromProxy(const VISION_ERR_PARAM_V1 &vision_ERR_PARAM_V1, VISION_ERR_PARAM &vision_ERR_PARAM);

#pragma endregion

#pragma region EcatADDA状态
#pragma pack(push)
#pragma pack(1)
#define ETHERCAT_ADDA_MAX_NUM 16
// EcatADDA状态
typedef struct _EcatAdDaState_V1
{
    _EcatAdDaState_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        i32EnableChannel = 0;
        i32DAKind = 0;
        i16TransformMode = 0;
        i16OutputRange = 0;
        f64MinValue = 0;
        f64MaxValue = 0;
        f64ActualValue = 0;
        i32OutSwitch = 0;
    }

    _EcatAdDaState_V1 &operator=(const _EcatAdDaState_V1 &other)
    {
        this->i32EnableChannel = other.i32EnableChannel;
        this->i32DAKind = other.i32DAKind;
        this->i16TransformMode = other.i16TransformMode;
        this->i16OutputRange = other.i16OutputRange;
        this->f64MinValue = other.f64MinValue;
        this->f64MaxValue = other.f64MaxValue;
        this->f64ActualValue = other.f64ActualValue;
        this->i32OutSwitch = other.i32OutSwitch;
        return (*this);
    }

    // 比较  相同返回ture， 不相同返回false
    bool compare(const _EcatAdDaState_V1 &other)
    {
        if (i32EnableChannel != other.i32EnableChannel)
            return false;
        if (i32DAKind != other.i32DAKind)
            return false;
        if (i16TransformMode != other.i16TransformMode)
            return false;
        if (i16OutputRange != other.i16OutputRange)
            return false;
        if (f64MinValue != other.f64MinValue)
            return false;
        if (f64MaxValue != other.f64MaxValue)
            return false;
        if (f64ActualValue != other.f64ActualValue)
            return false;
        if (i32OutSwitch != other.i32OutSwitch)
            return false;
        return true;
    }

    int32s i32EnableChannel;  // 使能通道，0：未使能，1：使能
    int32s i32DAKind;         // 0:电流 1：电压
    int16s i16TransformMode;  // 转换模式
    int16s i16OutputRange;    // 数字输出范围
    double f64MinValue;       // 范围最小值
    double f64MaxValue;       // 范围最小值
    double f64ActualValue;    // 实际输出值
    int32s i32OutSwitch;      // 输出开关 0：不输出 1：输出
} EcatAdDaState_V1;

// Ecat从站状态
typedef struct _EcatSlaveInfo_V1
{
    _EcatSlaveInfo_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        memset(slaveName, 0, 30);
        u8IsSupport = 0;
        u8ManageStatus = 0;
        u8comStatus = 0;
    }

    char slaveName[30];    // 从站模块名
    int8u u8IsSupport;     // 是否支持状态切换  0：不支持  1：支持
    int8u u8ManageStatus;  // 管理状态   0：禁用  1：启用
    int8u u8comStatus;     // 通信状态   0：通信断开  1：Init  2：Pre-OP  4:Safe-OP  8:通信正常(OP)  9:通信分离
} EcatSlaveInfo_V1;

// Ecat从站管理状态
typedef struct _EcatSlaveManageState_V1
{
    _EcatSlaveManageState_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        u8SlaveNum = 0;
        u8funtionSwitch = 0;
    }

    int8u u8funtionSwitch;                // 从站管理功能开关  0：关闭  1：开启
    int8u u8SlaveNum;                     // 从站数
    EcatSlaveInfo_V1 sEcatSlaveInfo[24];  // 从站管理状态参数
} EcatSlaveManageState_V1;

#pragma pack(pop)

bool EcatAdDaState_ToProxy(const EcatAdDaState &ecatAdDaState, EcatAdDaState_V1 &ecatAdDaState_V1);
bool EcatAdDaState_FromProxy(const EcatAdDaState_V1 &ecatAdDaState_V1, EcatAdDaState &ecatAdDaState);

bool EcatSlaveInfo_ToProxy(const EcatSlaveInfo &ecatSlaveInfo, EcatSlaveInfo_V1 &ecatSlaveInfo_V1);
bool EcatSlaveInfo_FromProxy(const EcatSlaveInfo_V1 &ecatSlaveInfo_V1, EcatSlaveInfo &ecatSlaveInfo);

bool EcatSlaveManageState_ToProxy(const EcatSlaveManageState &ecatSlaveManageState, EcatSlaveManageState_V1 &ecatSlaveManageState_V1);
bool EcatSlaveManageState_FromProxy(const EcatSlaveManageState_V1 &ecatSlaveManageState_V1, EcatSlaveManageState &ecatSlaveManageState);

#pragma endregion

#pragma region EIP从站

// EIP从站状态
// 固定支持8个从站，一个从站支持4个连接
#define EIPSLAVENUM_V1     8
#define EIPSLAVECONNNUM_V1 32

struct EIPSlaveInfo_V1
{
    EIPSlaveInfo_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        memset(slaveName, 0, 30);
        u8IsSupport = 0;
        u8ManageStatus = 0;
        u8comStatus = 0;
    }

    char slaveName[30];    // 从站模块名
    int8u u8IsSupport;     // 是否支持状态切换  0：不支持  1：支持
    int8u u8ManageStatus;  // 管理状态   0：禁用  1：启用
    int8u u8comStatus;     // 通信状态   0xFF：从站未配置连接 0：通信断开  1：通信正常(OP)  2：通信分离  其他失败
};

bool EIPSlaveInfo_ToProxy(const EIPSlaveInfo &eIPSlaveInfo, EIPSlaveInfo_V1 &eIPSlaveInfo_V1);
bool EIPSlaveInfo_FromProxy(const EIPSlaveInfo_V1 &eIPSlaveInfo_V1, EIPSlaveInfo &eIPSlaveInfo);

// EIP从站管理状态
struct EIPSlaveManageState_V1
{
    EIPSlaveManageState_V1()
    {
        InitZero();
    }
    void InitZero()
    {
        u8SlaveNum = 0;
    }

    int8u u8SlaveNum;                               // 从站数
    EIPSlaveInfo_V1 sEIPSlaveInfo[EIPSLAVENUM_V1];  // 从站管理状态参数
};

bool EIPSlaveManageState_ToProxy(const EIPSlaveManageState &eIPSlaveManageState, EIPSlaveManageState_V1 &eIPSlaveManageState_V1);
bool EIPSlaveManageState_FromProxy(const EIPSlaveManageState_V1 &eIPSlaveManageState_V1, EIPSlaveManageState &eIPSlaveManageState);

// EIP从站连接状态
struct EipSlaveConnState_V1
{
    int8u u8Instance;      // 连接实例号
    char slaveConnIP[16];  // 连接的IP地址
    int8u connState;       // 连接的状态 0——未连接；1——已连接
    int8u connIfCfg;       // 该连接是否配置

    EipSlaveConnState_V1()
    {
        InitZero();
    }

    void InitZero()
    {
        u8Instance = 0;
        memset(slaveConnIP, 0, 16);
        connState = 0;
        connIfCfg = 0;
    }
};

bool EipSlaveConnState_ToProxy(const EipSlaveConnState &eipSlaveConnState, EipSlaveConnState_V1 &eipSlaveConnState_V1);
bool EipSlaveConnState_FromProxy(const EipSlaveConnState_V1 &eipSlaveConnState_V1, EipSlaveConnState &eipSlaveConnState);

struct EipSlaveConnsState_V1
{
    EipSlaveConnState_V1 connsState[EIPSLAVECONNNUM_V1];
    EipSlaveConnsState_V1()
    {
        memset(connsState, 0, sizeof(EipSlaveConnState_V1) * EIPSLAVECONNNUM_V1);
    }
};

bool EipSlaveConnsState_ToProxy(const EipSlaveConnsState &eipSlaveConnsState, EipSlaveConnsState_V1 &eipSlaveConnsState_V1);
bool EipSlaveConnsState_FromProxy(const EipSlaveConnsState_V1 &eipSlaveConnsState_V1, EipSlaveConnsState &eipSlaveConnsState);

#pragma endregion

#pragma region 负载

typedef struct _GripLoadParam_V1
{
    int ItemsCount;
    vector<LoadData_V1> LoadParams;

    _GripLoadParam_V1()
    {
        InitZero();
    }

    void InitZero()
    {
        ItemsCount = 16;
        for (size_t i = 0; i < ItemsCount; i++)
        {
            LoadData_V1 loadParam;
            LoadParams.push_back(loadParam);
        }
    }

    _GripLoadParam_V1 &operator=(const _GripLoadParam_V1 &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->LoadParams.clear();
        this->LoadParams.assign(other.LoadParams.begin(), other.LoadParams.end());
        return (*this);
    }
} GripLoadParam_V1;

bool GripLoadParam_ToProxy(const GripLoadParam &gripLoadParam, GripLoadParam_V1 &gripLoadParam_V1);
bool GripLoadParam_FromProxy(const GripLoadParam_V1 &gripLoadParam_V1, GripLoadParam &gripLoadParam);

// 负载用户数据
typedef struct _LoadUserData_V1
{
    int ItemsCount;
    vector<UserInstallParam_V1> LoadUserParams;

    _LoadUserData_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        ItemsCount = 16;
        LoadUserParams.clear();
        for (size_t i = 0; i < ItemsCount; i++)
        {
            UserInstallParam_V1 gripLoadUser;
            LoadUserParams.push_back(gripLoadUser);
        }
    }

    _LoadUserData_V1 &operator=(const _LoadUserData_V1 &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->LoadUserParams.clear();
        this->LoadUserParams.assign(other.LoadUserParams.begin(), other.LoadUserParams.end());
        return (*this);
    }
} LoadUserData_V1;

bool LoadUserData_ToProxy(const LoadUserData &loadUserData, LoadUserData_V1 &loadUserData_V1);
bool LoadUserData_FromProxy(const LoadUserData_V1 &loadUserData_V1, LoadUserData &loadUserData);

#pragma endregion

#pragma region RAM_P &RAM_J

typedef struct tagRAMP_V1
{
    tagRAMP_V1()
    {
        Exist = 0;
        PointNo = 0;
    }
    char Exist;  // 是否存在 0-不存在 1-存在
    int PointNo;
    RobPos_V1 Pos;
} RAM_P_V1;  // 117字节

bool RAM_P_ToProxy(const RAM_P &ram_P, RAM_P_V1 &ram_P_V1);
bool RAM_P_FromProxy(const RAM_P_V1 &ram_P_V1, RAM_P &ram_P);

typedef struct tagRAMJ_V1
{
    tagRAMJ_V1()
    {
        Exist = 0;
        PointNo = 0;
    }
    char Exist;  // 是否存在 0-不存在 1-存在
    int PointNo;
    JPos_V1 Pos;
} RAM_J_V1;  // 117字节

bool RAM_J_ToProxy(const RAM_J &ram_J, RAM_J_V1 &ram_J_V1);
bool RAM_J_FromProxy(const RAM_J_V1 &ram_J_V1, RAM_J &ram_J);

#pragma endregion

#pragma region 工件

typedef struct _WobjParamData_V1
{
    int ItemsCount;
    vector<WobjData_V1> Items;
    vector<CsCalibPoints_V1> UMethodDatas;
    vector<CsCalibPoints_V1> OMethodDatas;

    _WobjParamData_V1()
    {
        InitZero();
    }

    void InitZero()
    {
        ItemsCount = 16;
        Items.clear();
        UMethodDatas.clear();
        OMethodDatas.clear();

        for (int i = 0; i < ItemsCount; i++)
        {
            WobjData_V1 wd;
            Items.push_back(wd);

            CsCalibPoints_V1 uCalibPoints;
            UMethodDatas.push_back(uCalibPoints);

            CsCalibPoints_V1 oCalibPoints;
            OMethodDatas.push_back(oCalibPoints);
        }
    }

    _WobjParamData_V1 &operator=(const _WobjParamData_V1 &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->Items.clear();
        this->Items.assign(other.Items.begin(), other.Items.end());
        this->UMethodDatas.clear();
        this->UMethodDatas.assign(other.UMethodDatas.begin(), other.UMethodDatas.end());
        this->OMethodDatas.clear();
        this->OMethodDatas.assign(other.OMethodDatas.begin(), other.OMethodDatas.end());
        return (*this);
    }
} WobjParamData_V1;

bool WobjParamData_ToProxy(const WobjParamData &wobjParamData, WobjParamData_V1 &wobjParamData_V1);
bool WobjParamData_FromProxy(const WobjParamData_V1 &wobjParamData_V1, WobjParamData &wobjParamData);

// 工件参数
typedef struct _WobjCalibData_V1
{
    int ItemsCount;
    vector<CsCalibPoints_V1> UMethodDatas;
    vector<CsCalibPoints_V1> OMethodDatas;
    vector<UserInstallParam_V1> WobjUserParams;

    _WobjCalibData_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        ItemsCount = 16;
        UMethodDatas.clear();
        OMethodDatas.clear();
        WobjUserParams.clear();

        for (int i = 0; i < ItemsCount; i++)
        {
            CsCalibPoints_V1 uCalibPoints;
            UMethodDatas.push_back(uCalibPoints);

            CsCalibPoints_V1 oCalibPoints;
            OMethodDatas.push_back(oCalibPoints);

            UserInstallParam_V1 userInstallParam;
            WobjUserParams.push_back(userInstallParam);
        }
    }

    _WobjCalibData_V1 &operator=(const _WobjCalibData_V1 &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->UMethodDatas.clear();
        this->UMethodDatas.assign(other.UMethodDatas.begin(), other.UMethodDatas.end());
        this->OMethodDatas.clear();
        this->OMethodDatas.assign(other.OMethodDatas.begin(), other.OMethodDatas.end());
        this->WobjUserParams.clear();
        this->WobjUserParams.assign(other.WobjUserParams.begin(), other.WobjUserParams.end());
        return (*this);
    }
} WobjCalibData_V1;

bool WobjCalibData_ToProxy(const WobjCalibData &wobjCalibData, WobjCalibData_V1 &wobjCalibData_V1);
bool WobjCalibData_FromProxy(const WobjCalibData_V1 &wobjCalibData_V1, WobjCalibData &wobjCalibData);

#pragma endregion

#pragma region 轨迹恢复

// 轨迹恢复阈值设置参数
struct TrajRecoveryThreshold_V1
{
    TrajRecoveryThreshold_V1()
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
};

bool TrajRecoveryThreshold_ToProxy(const TrajRecoveryThreshold &trajRecoveryThreshold, TrajRecoveryThreshold_V1 &trajRecoveryThreshold_V1);
bool TrajRecoveryThreshold_FromProxy(const TrajRecoveryThreshold_V1 &trajRecoveryThreshold_V1, TrajRecoveryThreshold &trajRecoveryThreshold);

// 轨迹恢复设置参数
struct TrajRecoveryParam_V1
{
    TrajRecoveryParam_V1()
    {
        Initialize();
    }
    void Initialize()
    {
        i32Mode = 0;
    }

    int i32Mode;                             // 轨迹恢复与之设置模式
    TrajRecoveryThreshold_V1 stManualParam;  // 位置模式下，手动阈值参数
    TrajRecoveryThreshold_V1 stAutoParam;    // 位置模式下，自动阈值参数
};

bool TrajRecoveryParam_ToProxy(const TrajRecoveryParam &trajRecoveryParam, TrajRecoveryParam_V1 &trajRecoveryParam_V1);
bool TrajRecoveryParam_FromProxy(const TrajRecoveryParam_V1 &trajRecoveryParam_V1, TrajRecoveryParam &trajRecoveryParam);

#pragma endregion

}  // namespace InoRobBusinessProxy