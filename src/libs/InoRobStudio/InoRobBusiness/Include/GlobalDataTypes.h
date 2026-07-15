#pragma once

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "IInoRobUtil.h"
#include "DataTypeDef.h"
#include "math.h"
using namespace InoRobUtil;

using std::string;
using std::vector;
using std::map;

#pragma region 常量定义
#define LINK_PARM_NUM 8
#define COM_PARM_NUM  16
#define STIF_PARM_NUM 16

#define MODULE_NUM   8  // 控制器模块数量
#define MAXIONUM     128
#define MAXDANUM     16
#define MAXIRLINKNUM 4

// PR变量
#define PALLET_VAR_NUMB     256
#define PALLET_VAR_ARR_SIZE 5  // 每帧数据
#define PR_VAR_NUMB         256
#define PR_VAR_ARR_SIZE     10  // 每帧数据

#pragma endregion

// 从站管理状态功能 - 从站类型
enum ManageFunSlaveType : int
{
    MANAGEFUN_ECAT = 0,  // EtherCAT
    MANAGEFUN_EIP = 1,   // EIP
};

#pragma region 机器人位置 - 关节位置 - 点位数据等
#pragma pack(push)
#pragma pack(1)
// 机器人位置点
typedef struct tagRobPos
{
    tagRobPos()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
        {
            RPosData[i] = 0.0;
            EPosData[i] = 0.0;
        }
        for (int i = 0; i < ARM_TYPE_NUM; i++)
        {
            ArmParm[i] = 0;
        }
    }

    tagRobPos &operator=(const tagRobPos &other)
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
            this->RPosData[i] = other.RPosData[i];
        for (int i = 0; i < ARM_TYPE_NUM; i++)
            this->ArmParm[i] = other.ArmParm[i];
        for (int i = 0; i < EXT_AXIS_NUM; i++)
            this->EPosData[i] = other.EPosData[i];

        return (*this);
    }

    bool operator==(const tagRobPos &other) const
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
        {
            if (std::abs(this->RPosData[i] - other.RPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        for (int i = 0; i < ARM_TYPE_NUM; i++)
        {
            if (std::abs(this->ArmParm[i] - other.ArmParm[i]) > 0.000001)
            {
                return false;
            }
        }

        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            if (std::abs(this->EPosData[i] - other.EPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        return true;
    }

    double RPosData[POSE_AXIS_NUM];  // XYZABC
    int ArmParm[ARM_TYPE_NUM];       // 臂参数
    double EPosData[EXT_AXIS_NUM];   // E1-E6
} RobPos;

// 机器人关节点
typedef struct tagJPos
{
    tagJPos()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            JointData[i] = 0.0;
        }
        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            EPosData[i] = 0.0;
        }
    }

    tagJPos &operator=(const tagJPos &other)
    {
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
            this->JointData[i] = other.JointData[i];
        for (int i = 0; i < EXT_AXIS_NUM; i++)
            this->EPosData[i] = other.EPosData[i];

        return (*this);
    }

    bool operator==(const tagJPos &other) const
    {
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            if (std::abs(this->JointData[i] - other.JointData[i]) > 0.000001)
            {
                return false;
            }
        }

        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            if (std::abs(this->EPosData[i] - other.EPosData[i]) > 0.000001)
            {
                return false;
            }
        }

        return true;
    }

    double JointData[JOINT_AXIS_NUM];  // J1-J8
    double EPosData[EXT_AXIS_NUM];     // E1-E6
} JPos;

// 位姿 用于描述坐标系的值 在PR,Tool,WObj有用到
typedef struct tagPosture
{
    tagPosture()
    {
        Initialize();
    }
    void Initialize()
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
        {
            Data[i] = 0;
        }
    }
    tagPosture &operator=(const tagPosture &other)
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
        {
            this->Data[i] = other.Data[i];
        }
        return (*this);
    }

    bool Compare(const struct tagPosture &other) const
    {
        for (int i = 0; i < POSE_AXIS_NUM; i++)
        {
            if (Data[i] != other.Data[i])
                return false;
        }
        return true;
    }

    double Data[POSE_AXIS_NUM];
} Pose;  // 48个字节

// P点 带点号结构体
typedef struct ROB_POS_ITEM
{
    int PointNo;
    RobPos PData;
} RobPosItem;

// P点 带标签名、备注
typedef struct M_ROB_POS_ITEM
{
    M_ROB_POS_ITEM()
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

    M_ROB_POS_ITEM &operator=(const M_ROB_POS_ITEM &other)
    {
        this->PointNo = other.PointNo;
        this->PData = other.PData;
        this->LabelName = other.LabelName;
        this->Description = other.Description;

        return (*this);
    }

    bool operator==(const M_ROB_POS_ITEM &other) const
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
    RobPos PData;
    std::string LabelName;    // 标签名
    std::string Description;  // 描述
} MRobPosItem;

// 112字节

// JP 点 带点号结构体
typedef struct J_POS_ITEM
{
    int PointNo;  // 点号
    JPos JData;   // 点位数据
} JPosItem;

// JP 点 带标签名、备注
typedef struct M_JPOS_POS_ITEM
{
    M_JPOS_POS_ITEM()
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

    M_JPOS_POS_ITEM &operator=(const M_JPOS_POS_ITEM &other)
    {
        this->PointNo = other.PointNo;
        this->JData = other.JData;
        this->LabelName = other.LabelName;
        this->Description = other.Description;

        return (*this);
    }

    bool operator==(const M_JPOS_POS_ITEM &other) const
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
    JPos JData;               // 点位数据
    std::string LabelName;    // 标签名
    std::string Description;  // 描述
} MJPosItem;

// PR变量值
typedef struct tagPRVar
{
    tagPRVar()
    {
        nOffset = 0;
        memset(&PR, 0, PR_VAR_NUMB * sizeof(Pose));
    }
    int nOffset;  // 从第几个变量开始读写
    Pose PR[PR_VAR_NUMB];
} PR_VAR;

typedef struct tagRAMP
{
    tagRAMP()
    {
        Exist = 0;
        PointNo = 0;
    }
    char Exist;  // 是否存在 0-不存在 1-存在
    int PointNo;
    RobPos Pos;
} RAM_P;  // 117字节

typedef struct tagRAMJ
{
    tagRAMJ()
    {
        Exist = 0;
        PointNo = 0;
    }
    char Exist;  // 是否存在 0-不存在 1-存在
    int PointNo;
    JPos Pos;
} RAM_J;  // 117字节
#pragma pack(pop)
#pragma endregion

// 机器人Home点触发IO信号数据 结构体
typedef struct tagJHomeTriggertOutData
{
    tagJHomeTriggertOutData()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    bool operator==(const tagJHomeTriggertOutData &in)
    {
        if (index == in.index && mode == in.mode && outNum == in.outNum)
        {
            for (int i = 0; i < JOINT_AXIS_NUM; ++i)
            {
                if (abs(JointOffsetData[i] - in.JointOffsetData[i]) > 1e-6)
                    return false;
            }
            for (int i = 0; i < EXT_AXIS_NUM; ++i)
            {
                if (abs(EPosOffsetData[i] - in.EPosOffsetData[i]) > 1e-6)
                    return false;
            }
            return true;
        }
        return false;
    }
    void operator=(const tagJHomeTriggertOutData &in)
    {
        index = in.index;
        mode = in.mode;
        outNum = in.outNum;
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            JointOffsetData[i] = in.JointOffsetData[i];
        }
        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            EPosOffsetData[i] = in.EPosOffsetData[i];
        }
    }
    void Initialize()
    {
        index = 0;
        mode = 0;
        outNum = -1;
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            JointOffsetData[i] = 0.0;
        }
        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            EPosOffsetData[i] = 0.0;
        }
    }
    int index;
    int mode;
    int outNum;
    double JointOffsetData[JOINT_AXIS_NUM];  // J1-J8
    double EPosOffsetData[EXT_AXIS_NUM];     // E1-E6
} JHomeTriggertOutData;

#pragma region 负载
#pragma pack(push)
#pragma pack(1)
// 标准负载的定义
typedef struct _Load_Para
{
    _Load_Para()
    {
        InitZero();
    }
    void InitZero()
    {
        Mass = 0;
        for (int i = 0; i < POSIT_DIMENT; i++)
        {
            Cog[i] = 0;
            Orient[i] = 0;
            Inertia[i] = 0;
        }
    }
    _Load_Para &operator=(const _Load_Para &other)
    {
        this->Mass = other.Mass;
        for (int i = 0; i < POSIT_DIMENT; i++)
        {
            this->Cog[i] = other.Cog[i];
            this->Orient[i] = other.Orient[i];
            this->Inertia[i] = other.Inertia[i];
        }
        return (*this);
    }
    double Mass;                     // Mass
    double Cog[POSIT_DIMENT];        // centre of Mass expressed in referenced coordinate 负载参数质心位置（Cog）
    double Orient[ORIENT_DIMENT];    // Orient of work-object coordinate expressed in referenced coordinate 负载参数质心的姿态（Orient）
    double Inertia[INERTIA_DIMENT];  // Inertia relative to centre of Mass: Ixx,  Iyy,  Izz  负载惯量（Inertia）
} LoadData;                          // 80字节
#pragma pack(pop)
#pragma endregion

#pragma region 臂上负载
// 臂上负载（对齐方式不同）
typedef struct _Arm_Load_Data
{
    _Arm_Load_Data()
    {
        InitZero();
    }
    void InitZero()
    {
        Mass = 0;
        for (int i = 0; i < POSIT_DIMENT; i++)
        {
            Cog[i] = 0;
            Orient[i] = 0;
            Inertia[i] = 0;
        }
    }
    _Arm_Load_Data &operator=(const _Arm_Load_Data &other)
    {
        this->Mass = other.Mass;
        for (int i = 0; i < POSIT_DIMENT; i++)
        {
            this->Cog[i] = other.Cog[i];
            this->Orient[i] = other.Orient[i];
            this->Inertia[i] = other.Inertia[i];
        }
        return (*this);
    }
    double Mass;                     // Mass
    double Cog[POSIT_DIMENT];        // centre of Mass expressed in referenced coordinate 负载参数质心位置（Cog）
    double Orient[ORIENT_DIMENT];    // Orient of work-object coordinate expressed in referenced coordinate 负载参数质心的姿态（Orient）
    double Inertia[INERTIA_DIMENT];  // Inertia relative to centre of Mass: Ixx,  Iyy,  Izz  负载惯量（Inertia）
} ArmLoadData;                       // 80字节
#pragma endregion

#pragma region 工具
#pragma pack(push)
#pragma pack(1)
// 工具参数
typedef struct _ToolData_
{
    _ToolData_()
    {
        InitZero();
    }
    void InitZero()
    {
        RobHold = true;
        TFrame.Initialize();
        TLoad.InitZero();
    }
    _ToolData_ &operator=(const _ToolData_ &other)
    {
        this->RobHold = other.RobHold;
        this->TFrame = other.TFrame;
        this->TLoad = other.TLoad;
        return (*this);
    }
    bool RobHold;  // True-夹持工具   False-外部工具
    Pose TFrame;
    LoadData TLoad;
} ToolData;  // 总计132字节
#pragma pack(pop)

#pragma endregion

#pragma region 工件

/******************* 用户坐标系开始 ******************/
#pragma pack(push)
#pragma pack(1)
typedef struct _WobjData_
{
    _WobjData_()
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
        memset(&UFMec, 0, MECHUNIT_NAME_LENGTH);
        UFrame.Initialize();
        OFrame.Initialize();
    }
    _WobjData_ &operator=(const _WobjData_ &other)
    {
        this->RobHold = other.RobHold;
        this->UFFix = other.UFFix;
        memcpy(&this->UFMec, &other.UFMec, MECHUNIT_NAME_LENGTH);
        this->UFrame = other.UFrame;
        this->OFrame = other.OFrame;
        return (*this);
    }

    bool operator==(const _WobjData_ &other) const
    {
        if (this->RobHold != other.RobHold)
        {
            return false;
        }

        if (this->UFFix != other.UFFix)
        {
            return false;
        }

        for (size_t i = 0; i < MECHUNIT_NAME_LENGTH; i++)
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

    bool RobHold;                      // 工件是否夹持  true 夹持； FALSE 非夹持
    bool UFFix;                        // 工件是否固定（是否相对于大地坐标系固定、是否相对于法兰盘固定）
    char UFMec[MECHUNIT_NAME_LENGTH];  // 关联的机械单元名称
    Pose UFrame;
    Pose OFrame;
} WobjData;  // 总计114字节
#pragma pack(pop)
/******************* 用户坐标系结束******************/

#pragma endregion

#pragma region 负载
#define DESCRIPTION_NUM 120
#pragma pack(push)
#pragma pack(1)
typedef struct _GripLoadParam_
{
    int ItemsCount;
    vector<LoadData> LoadParams;

    _GripLoadParam_()
    {
        InitZero();
    }

    void InitZero()
    {
        ItemsCount = 16;
        for (int i = 0; i < ItemsCount; i++)
        {
            LoadData loadParam;
            LoadParams.push_back(loadParam);
        }
    }

    _GripLoadParam_ &operator=(const _GripLoadParam_ &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->LoadParams.clear();
        this->LoadParams.assign(other.LoadParams.begin(), other.LoadParams.end());
        return (*this);
    }
} GripLoadParam;
#pragma pack(pop)
// 用户安装参数，工具工件负载共用此参数
typedef struct _UserInstallParam_
{
    char Description[DESCRIPTION_NUM];

    _UserInstallParam_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(Description, 0, DESCRIPTION_NUM);
    }

    _UserInstallParam_ &operator=(const _UserInstallParam_ &other)
    {
        memcpy(&this->Description[0], &other.Description[0], DESCRIPTION_NUM * sizeof(char));
        return (*this);
    }
} UserInstallParam;

// 负载用户数据
typedef struct _LoadUserData_
{
    int ItemsCount;
    vector<UserInstallParam> LoadUserParams;

    _LoadUserData_()
    {
        Initialize();
    }

    void Initialize()
    {
        ItemsCount = 16;
        LoadUserParams.clear();
        for (int i = 0; i < ItemsCount; i++)
        {
            UserInstallParam gripLoadUser;
            LoadUserParams.push_back(gripLoadUser);
        }
    }

    _LoadUserData_ &operator=(const _LoadUserData_ &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->LoadUserParams.clear();
        this->LoadUserParams.assign(other.LoadUserParams.begin(), other.LoadUserParams.end());
        return (*this);
    }
} LoadUserData;

#pragma endregion

#pragma region 工具 - 工件标定
#define CALIB_POINTS_COUNT 6
#define TOOL_TOTAL_NUM     16
typedef struct _CsCalibPoints_
{
    int MethodType;
    RobPos Points[CALIB_POINTS_COUNT];

    _CsCalibPoints_()
    {
        Initialize();
    }

    void Initialize()
    {
        MethodType = 0;
        for (int i = 0; i < CALIB_POINTS_COUNT; i++)
        {
            Points[i].Initialize();
        }
    }

    _CsCalibPoints_ &operator=(const _CsCalibPoints_ &other)
    {
        this->MethodType = other.MethodType;
        for (int i = 0; i < CALIB_POINTS_COUNT; i++)
        {
            Points[i] = other.Points[i];
        }
        return (*this);
    }
} CsCalibPoints;

/******************* 工具参数 16 套开始******************/
typedef struct _ToolParamData_
{
    int ItemsCount;
    vector<ToolData> Items;
    vector<CsCalibPoints> MethodDatas;

    _ToolParamData_()
    {
        InitZero();
    }

    void InitZero()
    {
        ItemsCount = 16;
        Items.clear();
        MethodDatas.clear();
        for (int i = 0; i < ItemsCount; i++)
        {
            ToolData td;
            Items.push_back(td);

            CsCalibPoints csCalibPoints;
            MethodDatas.push_back(csCalibPoints);
        }
    }

    _ToolParamData_ &operator=(const _ToolParamData_ &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->Items.clear();
        this->Items.assign(other.Items.begin(), other.Items.end());
        this->MethodDatas.clear();
        this->MethodDatas.assign(other.MethodDatas.begin(), other.MethodDatas.end());
        return (*this);
    }
} ToolParamData;

// 工具标定参数
typedef struct _ToolCalibData_
{
    int ItemsCount;
    vector<CsCalibPoints> MethodDatas;
    vector<UserInstallParam> ToolUserParams;

    _ToolCalibData_()
    {
        Initialize();
    }

    void Initialize()
    {
        ItemsCount = 16;
        MethodDatas.clear();
        ToolUserParams.clear();

        for (int i = 0; i < ItemsCount; i++)
        {
            CsCalibPoints csCalibPoints;
            MethodDatas.push_back(csCalibPoints);

            UserInstallParam userInstallParam;
            ToolUserParams.push_back(userInstallParam);
        }
    }

    _ToolCalibData_ &operator=(const _ToolCalibData_ &other)
    {
        this->ItemsCount = other.ItemsCount;
        this->MethodDatas.clear();
        this->MethodDatas.assign(other.MethodDatas.begin(), other.MethodDatas.end());
        this->ToolUserParams.clear();
        this->ToolUserParams.assign(other.ToolUserParams.begin(), other.ToolUserParams.end());
        return (*this);
    }
} ToolCalibData;

typedef struct _WobjParamData_
{
    int ItemsCount;
    vector<WobjData> Items;
    vector<CsCalibPoints> UMethodDatas;
    vector<CsCalibPoints> OMethodDatas;

    _WobjParamData_()
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
            WobjData wd;
            Items.push_back(wd);

            CsCalibPoints uCalibPoints;
            UMethodDatas.push_back(uCalibPoints);

            CsCalibPoints oCalibPoints;
            OMethodDatas.push_back(oCalibPoints);
        }
    }

    _WobjParamData_ &operator=(const _WobjParamData_ &other)
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
} WobjParamData;

// 工件参数
typedef struct _WobjCalibData_
{
    int ItemsCount;
    vector<CsCalibPoints> UMethodDatas;
    vector<CsCalibPoints> OMethodDatas;
    vector<UserInstallParam> WobjUserParams;

    _WobjCalibData_()
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
            CsCalibPoints uCalibPoints;
            UMethodDatas.push_back(uCalibPoints);

            CsCalibPoints oCalibPoints;
            OMethodDatas.push_back(oCalibPoints);

            UserInstallParam userInstallParam;
            WobjUserParams.push_back(userInstallParam);
        }
    }

    _WobjCalibData_ &operator=(const _WobjCalibData_ &other)
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
} WobjCalibData;
#pragma endregion

#pragma region 视觉标定工艺

// 标准视觉功能--相机参数（注：参数定义格式和数据类型来自控制器）
struct CAMERAPARA_T
{
    CAMERAPARA_T()
    {
        u8TriggerType = 1;
        u8TriggerIONum = 0;
        u8IOSignalType = 0;

        memset(&cIPAddr[0], 0x00, 16);
        memset(&u8Separator[0], 0x00, 8);
        memset(&u8Terminator[0], 0x00, 8);
        memset(&Headtcp[0], 0x00, 8);
        iPortNum = 0;
        memset(&cTriggerFlag[0], 0x00, 16);

        iVisualSendRcvFlag = 0;
        tcpState = 0;
        memset(&u8DataBuffer[0], 0x00, 256);
    }

    CAMERAPARA_T &operator=(const CAMERAPARA_T &other)
    {
        u8TriggerType = other.u8TriggerType;
        u8TriggerIONum = other.u8TriggerIONum;
        u8IOSignalType = other.u8IOSignalType;

        memcpy(&cIPAddr[0], &other.cIPAddr[0], 16);
        memcpy(&u8Separator[0], &other.u8Separator[0], 8);
        memcpy(&u8Terminator[0], &other.u8Terminator[0], 8);
        iPortNum = other.iPortNum;
        memcpy(&cTriggerFlag[0], &other.cTriggerFlag[0], 16);
        memcpy(&Headtcp[0], &other.Headtcp[0], 8);

        iVisualSendRcvFlag = other.iVisualSendRcvFlag;
        tcpState = other.tcpState;
        memcpy(&u8DataBuffer[0], &other.u8DataBuffer[0], 256);

        return *this;
    }

    char cIPAddr[16];  // IP address 192.168.0.1
    int iPortNum;

    UINT8 u8TriggerType;    // I/O; Network
    char cTriggerFlag[16];  // Trigger camera
    UINT8 u8TriggerIONum;   // I/O number if I/O trigger
    UINT8 u8IOSignalType;   // up/down edge if I/O trigger

    char Headtcp[8];
    char u8Separator[8];   // Separator string
    char u8Terminator[8];  // Terminator string

    int iVisualSendRcvFlag;  // 1-Send, 2-Receive
    int tcpState;            // 0 未连接 1，已连接
    char u8DataBuffer[256];  // buffer for send or receive
};

#ifndef DEF_VISION_ERR_PARAM
    #define DEF_VISION_ERR_PARAM
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
} VISION_ERR_PARAM;
#endif

#pragma endregion

#pragma region 负载对应通讯接口相关

#ifndef GRIPLOAD_NUM_MAX
    #define GRIPLOAD_NUM_MAX (16)

// 机器人工具负载的定义，相对于腕部坐标系(废弃)
typedef struct _Tool_Load_Para
{
    int16u toolNum;  // tool number
    short reserved;  // reserved data, using for nothing currently
    LoadData load;
} ToolLoadPara;

// 机器人工件（末端）负载的定义，相对于工具坐标系(废弃)
typedef struct _Grip_Load_Para
{
    int16u gripLoadNo;  // gripLoad number
    short reserved;     // reserved data,using for nothing currently
    LoadData load;
} GripLoadPara;

// 机器人臂上（额外）负载的定义，相对于关节坐标系
typedef struct _Robot_Arm_Load_Para
{
    int16u linkNum;  // number of the link on which the load has been mounted
    short reserved;  // reserved data, using for nothing currently
    ArmLoadData load;
} ArmLoadPara;

typedef struct _LOGSWITCH_
{
    short log_mode;
    short log_level;
} LOGSWITCH;

// 5.	动力学参数综合结构体
typedef struct _Robot_Load_Para
{
    int16u activeToolLoadNo;
    int16u activeGripLoadNo;  // non-negative for real gripLoad, negative for none
    ToolLoadPara toolLoadPara[16];
    GripLoadPara gripLoadPara[GRIPLOAD_NUM_MAX];
    ArmLoadPara armLoadPara[8];
} RobotLoadPara;

#endif
#pragma endregion

#pragma region 机械单元
//////////////////////////////////////////////////////////////////////////
// 机械单元定义
//////////////////////////////////////////////////////////////////////////
#pragma pack(1)  // 单字节对齐
typedef struct _RELATIVE_TRANSFORMAT_
{
    _RELATIVE_TRANSFORMAT_()
    {
        Initialize();
    }

    void Initialize()
    {
        Transformat.Initialize();
    }

    struct _RELATIVE_TRANSFORMAT_ &operator=(const struct _RELATIVE_TRANSFORMAT_ &other)
    {
        Transformat = other.Transformat;
        return (*this);
    }

    bool Compare(const struct _RELATIVE_TRANSFORMAT_ &other)
    {
        if (Transformat.Compare(other.Transformat))
            return true;
        return false;
    }

    Pose Transformat;  // 转换位姿关系
} RelativeTransformat;

typedef struct _MECH_UNIT_
{
    _MECH_UNIT_()
    {
        Initialize();
    }

    void Initialize()
    {
        Type = 0;
        InstallType = 0;
        AxisCount = 0;
        memset(Name, 0x00, MECHUNIT_NAME_LENGTH * sizeof(char));
        memset(MoveMechName, 0x00, MECHUNIT_NAME_LENGTH * sizeof(char));
        for (int i = 0; i < MECHUNIT_TRANSFORMAT_COUNT; i++)
        {
            Transformat[i].Initialize();
        }
        for (int i = 0; i < MECHUNIT_AXIS_MAP_COUNT; i++)
        {
            AxisMap[i] = 0xff;
        }
    }

    struct _MECH_UNIT_ &operator=(const struct _MECH_UNIT_ &other)
    {
        Type = other.Type;
        InstallType = other.InstallType;
        AxisCount = other.AxisCount;
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            Name[i] = other.Name[i];
            MoveMechName[i] = other.MoveMechName[i];
        }
        for (int i = 0; i < MECHUNIT_TRANSFORMAT_COUNT; i++)
        {
            Transformat[i] = other.Transformat[i];
        }
        for (int i = 0; i < MECHUNIT_AXIS_MAP_COUNT; i++)
        {
            AxisMap[i] = other.AxisMap[i];
        }
        return (*this);
    }

    bool Compare(const struct _MECH_UNIT_ &other)
    {
        if (Type != other.Type || InstallType != other.InstallType || AxisCount != other.AxisCount)
            return false;
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            if (Name[i] != other.Name[i] || MoveMechName[i] != other.MoveMechName[i])
                return false;
        }
        for (int i = 0; i < MECHUNIT_TRANSFORMAT_COUNT; i++)
        {
            if (Transformat[i].Compare(other.Transformat[i]))
                continue;
            else
                return false;
        }
        for (int i = 0; i < MECHUNIT_AXIS_MAP_COUNT; i++)
        {
            if (AxisMap[i] != other.AxisMap[i])
                return false;
        }
        return true;
    }

    char Name[MECHUNIT_NAME_LENGTH];                              // 机械单元的名称
    int16u Type;                                                  // 0:机器人; 1:X轴导轨; 2:单轴旋转变位机; 3:双轴旋转变位机; 101:无模型1轴; 102:无模型2轴; ...
    int8u InstallType;                                            // 0:固定安装; 1:在可移动的导轨上(机械单元上)
    char MoveMechName[MECHUNIT_NAME_LENGTH];                      // InstallType为1时，对应的可移动的导轨的机械单元名称
    int8u AxisCount;                                              // 轴数目
    RelativeTransformat Transformat[MECHUNIT_TRANSFORMAT_COUNT];  // 转换
    int8u AxisMap[MECHUNIT_AXIS_MAP_COUNT];                       // 轴映射关系
} MechUnit;

typedef struct _EXT_AXIS_PARAM_
{
    _EXT_AXIS_PARAM_()
    {
        Initialize();
    }

    void Initialize()
    {
        SvType = 1;
        OpMode = 8;
        AxisType = 0;
        MoveType = 1;
        PhyTransRatio = 30.00;
        AbsZero = 0;
        PosLimit = 180.00;
        NegLimit = -180.00;

        TeachVel = 10.00;
        TeachAcc = 100.00;

        MaxVel = 100.00;
        MaxAcc = 10000.00;
        StopDec = 10000.00;

        FollowErr = 1048576 * 3;
        InposErr = 10000;
        InposTime = 20;
        CurrentLimit = 300;
        AverageLoadRateLimit = 100;
    }

    struct _EXT_AXIS_PARAM_ &operator=(const struct _EXT_AXIS_PARAM_ &other)
    {
        SvType = other.SvType;
        OpMode = other.OpMode;
        AxisType = other.AxisType;
        MoveType = other.MoveType;
        PhyTransRatio = other.PhyTransRatio;
        AbsZero = other.AbsZero;
        PosLimit = other.PosLimit;
        NegLimit = other.NegLimit;
        TeachVel = other.TeachVel;
        TeachAcc = other.TeachAcc;
        MaxVel = other.MaxVel;
        MaxAcc = other.MaxAcc;
        StopDec = other.StopDec;
        FollowErr = other.FollowErr;
        InposErr = other.InposErr;
        InposTime = other.InposTime;
        CurrentLimit = other.CurrentLimit;
        AverageLoadRateLimit = other.AverageLoadRateLimit;
        return (*this);
    }

    bool Compare(const struct _EXT_AXIS_PARAM_ &other)
    {
        if (OpMode != other.OpMode || SvType != other.SvType || AxisType != other.AxisType || MoveType != other.MoveType
            || PhyTransRatio != other.PhyTransRatio || AbsZero != other.AbsZero || PosLimit != other.PosLimit || NegLimit != other.NegLimit
            || TeachVel != other.TeachVel || TeachAcc != other.TeachAcc || MaxVel != other.MaxVel || MaxAcc != other.MaxAcc
            || StopDec != other.StopDec || FollowErr != other.FollowErr || InposErr != other.InposErr || InposTime != other.InposTime
            || CurrentLimit != other.CurrentLimit || AverageLoadRateLimit != other.AverageLoadRateLimit)
            return false;
        return true;
    }

    int16s SvType;                // 伺服类型620N = 0,660N = 1(默认值660N)
    int16s OpMode;                // 模式 8-位置模式；9、10不开放(9-速度模式;10-转矩模式)
    int16s AxisType;              // 轴属性 0-旋转轴;线性轴不开放（1-线性轴）
    int16s MoveType;              // 传动方式 0、转动-转动  1、转动-直线
    double PhyTransRatio;         // 物理传动比
    int32s AbsZero;               // 零点
    double PosLimit;              // 正限位
    double NegLimit;              // 负限位
    double TeachVel;              // 示教速度
    double TeachAcc;              // 示教加速度
    double MaxVel;                // 最大速度
    double MaxAcc;                // 最大加速度
    double StopDec;               // 停机减速度
    int32s FollowErr;             // 跟随误差
    int32s InposErr;              // 到位误差
    int16s InposTime;             // 到位时间
    int16s CurrentLimit;          // 电流限制
    int16s AverageLoadRateLimit;  // 平局负载率
} ExtAxisParam;

typedef struct _EXT_AXIS_PARAM_ITEM_
{
    _EXT_AXIS_PARAM_ITEM_()
    {
        Initialize();
    }

    void Initialize()
    {
        ExtAxisID = 0xff;
        Param.Initialize();
        memset(MechUnitName, 0x00, MECHUNIT_NAME_LENGTH * sizeof(char));
    }

    struct _EXT_AXIS_PARAM_ITEM_ &operator=(const struct _EXT_AXIS_PARAM_ITEM_ &other)
    {
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            MechUnitName[i] = other.MechUnitName[i];
        }
        ExtAxisID = other.ExtAxisID;
        Param = other.Param;
        return (*this);
    }

    bool Compare(const struct _EXT_AXIS_PARAM_ITEM_ &other)
    {
        if (ExtAxisID != other.ExtAxisID)
            return false;
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            if (MechUnitName[i] != other.MechUnitName[i])
                return false;
        }
        if (Param.Compare(other.Param))
            return true;
        else
            return false;
    }

    char MechUnitName[MECHUNIT_NAME_LENGTH];  // 所属机械单元
    int8u ExtAxisID;                          // E1~E6(0-5),nullptr:255;
    ExtAxisParam Param;                       // 轴参数
} ExtAxisParamItem;

// 独立轴参数
typedef struct _IND_AXIS_PARAM_
{
    _IND_AXIS_PARAM_()
    {
        Initialize();
    }

    void Initialize()
    {
        IndSupportFlag = 0;
        NegLimit = -100.0;
        PosLimit = 100.0;
        InPositionErr = 5;
        InPositionErrTime = 20;
        FollowErr = 10000;
    }

    struct _IND_AXIS_PARAM_ &operator=(const struct _IND_AXIS_PARAM_ &other)
    {
        IndSupportFlag = other.IndSupportFlag;
        NegLimit = other.NegLimit;
        PosLimit = other.PosLimit;
        InPositionErr = other.InPositionErr;
        InPositionErrTime = other.InPositionErrTime;
        FollowErr = other.FollowErr;
        return (*this);
    }

    bool Compare(const struct _IND_AXIS_PARAM_ other)
    {
        if (IndSupportFlag != other.IndSupportFlag || NegLimit != other.NegLimit || PosLimit != other.PosLimit || InPositionErr != other.InPositionErr || InPositionErrTime != other.InPositionErrTime || FollowErr != other.FollowErr)
            return false;
        return true;
    }

    int16s IndSupportFlag;
    double NegLimit;
    double PosLimit;
    int16s InPositionErr;
    int32s InPositionErrTime;
    int32s FollowErr;
} IndAxisParam;

// 独立轴属性
typedef struct _IND_AXIS_PARAM_ITEM_
{
    _IND_AXIS_PARAM_ITEM_()
    {
        Initialize();
    }

    void Initialize()
    {
        IndAxisID = -1;
        RealAxisID = -1;
        AxisSNInMech = 0;
        Param.Initialize();
        memset(MechUnitName, 0x00, MECHUNIT_NAME_LENGTH * sizeof(char));
    }

    struct _IND_AXIS_PARAM_ITEM_ &operator=(const struct _IND_AXIS_PARAM_ITEM_ &other)
    {
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            MechUnitName[i] = other.MechUnitName[i];
        }
        IndAxisID = other.IndAxisID;
        RealAxisID = other.RealAxisID;
        AxisSNInMech = other.AxisSNInMech;
        Param = other.Param;
        return (*this);
    }

    bool Compare(const struct _IND_AXIS_PARAM_ITEM_ other)
    {
        if (IndAxisID != other.IndAxisID)
            return false;
        if (RealAxisID != other.RealAxisID)
            return false;
        if (AxisSNInMech != other.AxisSNInMech)
            return false;
        for (int i = 0; i < MECHUNIT_NAME_LENGTH; i++)
        {
            if (MechUnitName[i] != other.MechUnitName[i])
                return false;
        }
        if (Param.Compare(other.Param))
            return true;
        else
            return false;
    }

    char MechUnitName[MECHUNIT_NAME_LENGTH];
    int16s IndAxisID;
    int16s RealAxisID;
    int16s AxisSNInMech;
    IndAxisParam Param;
} IndAxisParamItem;

typedef struct _MECH_UNITS_CFG_DATA_
{
    _MECH_UNITS_CFG_DATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        MechUnitCount = 0;
        ExtAxisParamItemCount = 0;
        IndAxisParamItemCount = 0;
        ConfigFileVerMaj = 0;
        ConfigFileVerMin = 0;

        for (int i = 0; i < EXT_MECHUNIT_COUNT + 1; i++)
        {
            Units[i].Initialize();
        }

        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            ExtAxisParamItems[i].Initialize();
        }

        for (int i = 0; i < IND_AXIS_NUM; i++)
        {
            IndAxisParamItems[i].Initialize();
        }
    }

    struct _MECH_UNITS_CFG_DATA_ &operator=(const struct _MECH_UNITS_CFG_DATA_ &other)
    {
        // 对初始化数据赋值 或者 主版本相同赋值
        if (ConfigFileVerMaj == 0)
        {
            ConfigFileVerMaj = other.ConfigFileVerMaj;
            ConfigFileVerMin = other.ConfigFileVerMin;
        }
        else if (ConfigFileVerMaj == other.ConfigFileVerMaj)
        {
            ConfigFileVerMaj = other.ConfigFileVerMaj;
            ConfigFileVerMin = other.ConfigFileVerMin;
        }

        for (int i = 0; i < EXT_MECHUNIT_COUNT + 1; i++)
        {
            Units[i] = other.Units[i];
        }

        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            ExtAxisParamItems[i] = other.ExtAxisParamItems[i];
        }

        for (int i = 0; i < IND_AXIS_NUM; i++)
        {
            IndAxisParamItems[i] = other.IndAxisParamItems[i];
        }

        MechUnitCount = other.MechUnitCount;
        ExtAxisParamItemCount = other.ExtAxisParamItemCount;
        IndAxisParamItemCount = other.IndAxisParamItemCount;
        return (*this);
    }

    bool Comapre(const struct _MECH_UNITS_CFG_DATA_ &other)
    {
        if (MechUnitCount != other.MechUnitCount || ExtAxisParamItemCount != other.ExtAxisParamItemCount
            || IndAxisParamItemCount != other.IndAxisParamItemCount || ConfigFileVerMin != other.ConfigFileVerMin
            || ConfigFileVerMaj != other.ConfigFileVerMaj)
            return false;
        for (int i = 0; i < EXT_MECHUNIT_COUNT + 1; i++)
        {
            if (Units[i].Compare(other.Units[i]))
                continue;
            else
                return false;
        }

        for (int i = 0; i < EXT_AXIS_NUM; i++)
        {
            if (ExtAxisParamItems[i].Compare(other.ExtAxisParamItems[i]))
                continue;
            else
                return false;
        }

        for (int i = 0; i < IND_AXIS_NUM; i++)
        {
            if (IndAxisParamItems[i].Compare(other.IndAxisParamItems[i]))
                continue;
            else
                return false;
        }

        return true;
    }

    int8u MechUnitCount;                               // 机械单元个数
    MechUnit Units[EXT_MECHUNIT_COUNT + 1];            // 目前仅支持2个机械单元
    int8u ExtAxisParamItemCount;                       // 轴参数Item数
    ExtAxisParamItem ExtAxisParamItems[EXT_AXIS_NUM];  // 机械单元的轴参数
    int8u IndAxisParamItemCount;                       // 配置的独立轴数量
    IndAxisParamItem IndAxisParamItems[IND_AXIS_NUM];  // 独立轴轴参数

    int8u ConfigFileVerMaj;  // 配置文件主版本
    int8u ConfigFileVerMin;  // 配置文件副版本
} MechUnitsCfgData;

typedef struct _MECH_UNITS_CALIB_METHOD_DATA_ITEM_
{
    _MECH_UNITS_CALIB_METHOD_DATA_ITEM_()
    {
        Initialize();
    }

    void Initialize()
    {
        MethodType = 0;
        for (int i = 0; i < MECHUNIT_CALIB_MID_POS_MAX_COUNT; i++)
        {
            MidPos[i].Initialize();
        }
    }

    struct _MECH_UNITS_CALIB_METHOD_DATA_ITEM_ &operator=(const struct _MECH_UNITS_CALIB_METHOD_DATA_ITEM_ &other)
    {
        MethodType = other.MethodType;
        for (int i = 0; i < MECHUNIT_CALIB_MID_POS_MAX_COUNT; i++)
        {
            MidPos[i] = other.MidPos[i];
        }
        return (*this);
    }

    int8u MethodType;                                 // 标定方法
    RobPos MidPos[MECHUNIT_CALIB_MID_POS_MAX_COUNT];  // 标定中间点
} MechUnitsCalibMethodDataItem;

typedef struct _MECH_UNITS_CALIB_DATA_ITEM_
{
    _MECH_UNITS_CALIB_DATA_ITEM_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(MechName, 0x00, sizeof(char) * MECHUNIT_NAME_LENGTH);
        Type = 0;
        for (int i = 0; i < MECHUNIT_CALIB_METHOD_COUNT; i++)
        {
            MethodItem[i].Initialize();
        }
    }

    struct _MECH_UNITS_CALIB_DATA_ITEM_ &operator=(const struct _MECH_UNITS_CALIB_DATA_ITEM_ &other)
    {
        memcpy(MechName, other.MechName, sizeof(char) * MECHUNIT_NAME_LENGTH);
        Type = other.Type;
        for (int i = 0; i < MECHUNIT_CALIB_METHOD_COUNT; i++)
        {
            MethodItem[i] = other.MethodItem[i];
        }
        return (*this);
    }

    char MechName[MECHUNIT_NAME_LENGTH];                                   // 机械单元的名称
    int16u Type;                                                           // 机械单元的类型
    MechUnitsCalibMethodDataItem MethodItem[MECHUNIT_CALIB_METHOD_COUNT];  // 过程方法及过程点数据
} MechUnitsCalibDataItem;

typedef struct _MECH_UNITS_CALIB_DATA_
{
    _MECH_UNITS_CALIB_DATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < EXT_MECHUNIT_COUNT; i++)
        {
            Item[i].Initialize();
        }
    }

    struct _MECH_UNITS_CALIB_DATA_ &operator=(const struct _MECH_UNITS_CALIB_DATA_ &other)
    {
        for (int i = 0; i < EXT_MECHUNIT_COUNT; i++)
        {
            Item[i] = other.Item[i];
        }
        return (*this);
    }

    MechUnitsCalibDataItem Item[EXT_MECHUNIT_COUNT];  // 目前只需要除机器人以外的机械单元的标定
} MechUnitsCalibData;
#pragma pack()  // 恢复对齐
#pragma endregion

#pragma region 初始化数据
///////////////////////////////////////////////////////////////////////////////////////
// 初始化数据结构体,用于连接成功后的数据读取 0322 版本的
///////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
typedef struct _tagInitData0322_
{
    _tagInitData0322_()
    {
        memset(szRobotName, 0, 128);
        eleType = 1;
        powerDownSave = 0;
        sysAuthority = 0;
        irAuthority = 0;
        di_num = 0;
        do_num = 0;
        ad_num = 0;
        da_num = 0;
        robotType = 6;
        memset(&linkParm[0], 0, 8 * sizeof(double));
        memset(&compParm[0], 0, 16 * sizeof(double));
        memset(&negLimt[0], 0, JOINT_AXIS_NUM * sizeof(double));
        memset(&posLimt[0], 0, JOINT_AXIS_NUM * sizeof(double));
        memset(&cServoAxisType, 0, 8 * sizeof(char));
        memset(&nCabinetFPGAVer, 0, sizeof(int32u));
        memset(szRobotStructType, 0, 128);
        memset(filedBusInstall, 0, 4);
        hardWareVer = 0;
        MechUnitNum = 0;
        memset(&MechUnitAxis[0], 0, MAX_MECHUNIT_NUM * sizeof(int8u));
        memset(&MechUnitShowType[0], 0, MAX_MECHUNIT_NUM * sizeof(int8u));
        for (int i = 0; i < MAX_MECHUNIT_NUM; i++)
        {
            for (int j = 0; j < MECHUNIT_NAME_LENGTH; j++)
            {
                MechUnitName[i][j] = 0;
            }
        }
    }
    char szRobotName[128];                                      // 机器人名
    int16u eleType;                                             // 电柜类型 1-普通，2-小多传,3-20kg 6关节 4-驱控一体
    int16u powerDownSave;                                       // 掉电保存  0-无 1-有
    int16u sysAuthority;                                        // 控制权 0-示教器 1-InoRobShop 2-远程EtherNet 3-远程IO 4-Modbus 参见枚举CTL_AUTHORITY
    int16u irAuthority;                                         // IRLINK配置权限 0-RC 1-PLC 参见枚举IR_CTRL_SET
    int16u di_num;                                              // IN个数
    int16u do_num;                                              // OUT个数
    int16u ad_num;                                              // AD个数
    int16u da_num;                                              // DA个数
    int16u robotType;                                           // 机型
    double linkParm[LINK_PARM_NUM];                             // 结构参数
    double compParm[COM_PARM_NUM];                              // 补偿参数
    double negLimt[JOINT_AXIS_NUM];                             // 负极限
    double posLimt[JOINT_AXIS_NUM];                             // 正极限
    char cServoAxisType[8];                                     // 伺服轴类型 1-IS620N 2-IS820N 3-IS660N
    int32u nCabinetFPGAVer;                                     // 电柜FPGA类型
    char szRobotStructType[128];                                // 本体机型（带有内部信息）
    char filedBusInstall[4];                                    // 总线安装标志(char[0].0表示EtherCAT，char[0].1表示... 每一位表示一个总线是否安装的标识)最多支持存储 32 种总线的安装方式
    int32u hardWareVer;                                         // 电控柜硬件版本
    int8u MechUnitNum;                                          // 机械单元的总个数
    int8u MechUnitAxis[MAX_MECHUNIT_NUM];                       // 各个机械单元的轴数
    int8u MechUnitShowType[MAX_MECHUNIT_NUM];                   // 机械单元显示类型 0 机器人、1单轴、2多轴（用于界面显示机械单元的图标）
    char MechUnitName[MAX_MECHUNIT_NUM][MECHUNIT_NAME_LENGTH];  // 机械单元的名称
} INIT_DATA_0322;                                               // 1275字节
#pragma pack()
#pragma endregion

#pragma region 实时数据(周期数据)

enum eRealRunStat
{
    REALRUNSTAT_STOP = 0,
    REALRUNSTAT_STARTUP = 1,
    REALRUNSTAT_FORWARD = 2,
    REALRUNSTAT_BACK = 3,
    REALRUNSTAT_PAUSE = 4,  // add by Bruce.nie 2015-06-05
    REALRUNSTAT_BUTT
};

#pragma pack(1)
typedef struct _RCSTS_INFO_0322_
{
    _RCSTS_INFO_0322_()
    {
        nStart = REALRUNSTAT_STOP;
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
        memset(&uCommState[0], 0, MODULE_NUM * sizeof(int16u));
        memset(&OutState[0], 0, MAXIONUM * sizeof(int8u));
        memset(&DAState[0], 0, MAXDANUM * sizeof(int8u));
        iSafeDoorSts = 0;
        iDynBrake = 0;
        iPowerLv = 0;
        StepGrade = 0;  // 寸动等级（0-无寸动 1-G1 2-G2 3-G3 4-U）
        MechLock = 0;   // 机械锁定  0-未锁定, 1-锁定
        ToolObjMatchFlag = IS_MATCH;
        memset(&CurPos, 0, JOINT_AXIS_NUM * sizeof(double));
        PosFormat = FORMAT_JOINT;
        memset(&MechUnitState, 0, MAX_MECHUNIT_NUM * sizeof(int8u));
        memset(&CooperateMechUnitName, 0, MECHUNIT_NAME_LENGTH * sizeof(char));
        meetConditionsFlag = 0;
    }

    _RCSTS_INFO_0322_ &operator=(const _RCSTS_INFO_0322_ &other)
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
        memcpy(&this->uCommState[0], &other.uCommState[0], MODULE_NUM * sizeof(int16u));
        memcpy(&this->OutState[0], &other.OutState[0], MAXIONUM * sizeof(int8u));
        memcpy(&this->DAState[0], &other.DAState[0], MAXDANUM * sizeof(int8u));
        this->iSafeDoorSts = other.iSafeDoorSts;
        this->iDynBrake = other.iDynBrake;
        this->iPowerLv = other.iPowerLv;
        this->StepGrade = other.StepGrade;
        this->MechLock = other.MechLock;
        this->ToolObjMatchFlag = other.ToolObjMatchFlag;
        memcpy(&this->CurPos[0], &other.CurPos[0], JOINT_AXIS_NUM * sizeof(double));
        this->PosFormat = other.PosFormat;
        memcpy(&this->MechUnitState[0], &other.MechUnitState[0], MAX_MECHUNIT_NUM * sizeof(int8u));
        memcpy(&this->CooperateMechUnitName[0], &other.CooperateMechUnitName[0], MECHUNIT_NAME_LENGTH * sizeof(char));
        this->meetConditionsFlag = other.meetConditionsFlag;
        return (*this);
    }
    int16u nStart;                                     // 0 停止，1 启动，2 前进，3 后退，4暂停
    int16u nEmerg;                                     // 1 急停, 0 非急停
    int16u nEnable;                                    // 1 使能, 0 非使能
    int16u nMode;                                      // 1->示教 2->再现 3->单步示教检查 5-> 连续示教检查 6-> 回零
    int16u nSpeed;                                     // 速度值
    int16u nCoord;                                     // 1 2 3 4 5    关节、基坐标、工具、工件、世界
    int16u nToolNo;                                    // 工具号
    int16u nWobjNo;                                    // 工件号
    int16u nLoadNo;                                    // 负载号
    int32s nErrId;                                     // 报警号
    int32s nWarnId;                                    // 警告号
    int16u uCommState[8];                              // 控制器端各个模块的通信状态(通信状态页面，某些检测USB、存储卡状态)
    int8u OutState[MAXIONUM];                          // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE
    int8u DAState[MAXDANUM];                           // 0-RC激活 1-RC静态（IO配置使用） 3-PLC激活 参见枚举IO_CTRL_STATE
    int8u iSafeDoorSts;                                // 安全门警示状态 0-无警示 1-有警示
    int8u iDynBrake;                                   // 动态制动开关 0-关(下使能好推动) 1-开
    int8u iPowerLv;                                    // 0-低功率 1-高功率
    int8u StepGrade;                                   // 寸动等级（0-无寸动 1-G1 2-G2 3-G3 4-U）
    int8u MechLock;                                    // 机械锁定状态（0：未锁定 1：锁定）
    int8u ToolObjMatchFlag;                            // 当前工具和工件是否匹配（0：匹配 1：工具与工件不匹配 2：工件参数不匹配）
    double CurPos[JOINT_AXIS_NUM];                     // 当前激活机械单元的位置数据（关节或笛卡尔）
    int8u PosFormat;                                   // 位置格式   1 2 3 4 5    关节、基坐标、法兰、工件、世界
    int8u MechUnitState[MAX_MECHUNIT_NUM];             // 机械单元的状态（0 正常，1 激活）
    char CooperateMechUnitName[MECHUNIT_NAME_LENGTH];  // 机器人协调的机械单元名称
    int8u meetConditionsFlag;                          // 当前机械单元是否满足协调条件（0不满足，1满足）
    // 与工业对齐
    int8u u8CommStateExt[8];                           // 控制器端各个模块通信状态 扩展用 大负载EtherCat2
    int16s u16EnergySavingStatus = 0;                  // 节能状态
    int8u uSpeedReducingTriggerd = 1;                  // **********功能安全(缩减模式触发标志) 协作 工业复用**********
    // 协作挪动
    int8u uCoRobotBodyPowerState = 0;                  // **********当前机器人本体上电状态 协作专用**********
    int8u uGripperThreePositionEnable = 0;             // **********夹持器三位置使能(1:使能 其他:非使能) 协作专用**********
    int8u uGripperEnable = 0;                          // **********夹持器使能(1:使能 其他:非使能) 协作专用**********
    int8u uWiFiFrequencyBand24GHzEnable = 0;           // **********控制器WiFi频段(0:5GHz 其他:2.4GHz) 协作专用**********
    int8u uSafetyMonitorStatus = 1;                    // **********功能安全(安全监控状态标志) 协作专用**********
    int16s i16RecommendCollLevel;                      // 碰撞检测推荐值
    // 工业新增
    double f64TcpSpeed = 0;                            // 实时TCP速度 工业新增
    // 归一新增
    int8u  u8ColliDectectParamChanged = 0;             // 碰撞检测参数是否被工程指令修改 (0：未发生改变 1：发生改变)
} RCSTS_INFO_0322;
#pragma pack()
#pragma endregion

// Move 类型
enum MoveType
{
    Movj = 0,
    Movl = 1,
    Jump = 2,
    Jumpl = 3
};

#pragma region 视觉标定常量定义

#define V_ROBOT_TEACH_POINT_NUM           (9)
#define V_ROBOT_TEACH_POINT_DIMENSION_NUM (6)
#define V_IMAGE_POINT_NUM                 (9)
#define V_IMAGE_POINT_DIMENSION_NUM       (2)
#define V_FOUR_AXIS_BASE_POINT_NUM        (2)
#define V_SIX_AXIS_BASE_POINT_NUM         (3)
#define V_CALIB_MATRIX_NUM                (9)

#pragma endregion

#pragma region 干涉区 &监控对象(笛卡尔位置监控)
#pragma pack(1)

#define IZONE_DESCRIPTION_CHARLENGTH    (32)   // 干涉区有关备注, 全部为32长度字符数组
#define IZONE_FLOATARRAYLENGTH          (6)    // 干涉区有关浮点数数组, 大部分为6长度
#define IZONE_MTCP_UINTARRAYLENGTH      (4)    // MTCPshort数组, 为4长度
#define IZONE_BALL_POSARRAYLENGTH       (3)    // Ball Pos数组, 3长度
#define IZONE_TOOLBOX_TYPE3_FLOATARRAY  (13)   // TOOLBOX第三种类型, 浮点数数组长度13
#define IZONE_INTERFERZONESSTATUSLENGTH (16)   // 干涉区状态长度16
#define IZONE_ITOOL_TYPENUM             (4)    // 末端监测对象类别数目4
#define IZONE_ITOOL_TOOLBOXTYPENUM      (3)    // 工具包围盒类型数目3
#define IZONE_EPSILON                   (0.1)  // 工具包围盒类型数目3
#define IZONE_WOBJPARAMSNUM             (12)   // 干涉区工具工件参数相关
#define IZONE_MTCPTOOLPARAMSNUM         (6)    // 干涉区工具工件参数相关

// 干涉区
typedef struct INTERFER_ZONE
{
    INTERFER_ZONE()
    {
        Initialize();
    }

    void Initialize()
    {
        u16Index = 0xffff;
        memset(cRemarks, 0, IZONE_DESCRIPTION_CHARLENGTH);
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
        memset(f32Diagonal, 0, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointL, 0, IZONE_FLOATARRAYLENGTH * sizeof(float));
    }

    INTERFER_ZONE &operator=(const INTERFER_ZONE &other)
    {
        u16Index = other.u16Index;
        memcpy(cRemarks, other.cRemarks, IZONE_DESCRIPTION_CHARLENGTH);
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
        memcpy(f32Diagonal, other.f32Diagonal, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memcpy(f32PointL, other.f32PointL, IZONE_FLOATARRAYLENGTH * sizeof(float));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE &other)
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
        if (fabs(f32SafeL - other.f32SafeL) > IZONE_EPSILON)
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
        for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH; i++)
        {
            if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > IZONE_EPSILON)
                return false;
        }
        for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH; i++)
        {
            if (fabs(f32PointL[i] - other.f32PointL[i]) > IZONE_EPSILON)
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

    int IsPointsValid()
    {
        if (u16SetType == 0)  // 对角点
        {
            float tmp[6] = { 0 };
            memcpy(&tmp[0], &f32Diagonal[0], sizeof(float) * IZONE_FLOATARRAYLENGTH);
            double f64P1 = static_cast<double>(tmp[0]) - static_cast<double>(tmp[3]);
            double f64P2 = static_cast<double>(tmp[1]) - static_cast<double>(tmp[4]);
            double f64P3 = static_cast<double>(tmp[2]) - static_cast<double>(tmp[5]);
            if ((0.0001F) > fabs(f64P1)
                || (0.0001F) > fabs(f64P2)
                || (0.0001F) > fabs(f64P3))
            {
                return 9;
            }

            for (int i = 0; i < IZONE_FLOATARRAYLENGTH; ++i)
            {
                double f64DP = static_cast<double>(tmp[i]);
                if (10000.0F < fabs(f64DP))
                {
                    return 9;
                }
            }
            return 0;
        }
        else if (u16SetType == 1)  // 基准点
        {
            float f32BPoint[IZONE_FLOATARRAYLENGTH] = { 0 };
            memcpy(&f32BPoint[0], &f32PointL[0], sizeof(float) * IZONE_FLOATARRAYLENGTH);
            if ((10000.0F) < fabs(f32BPoint[0]) || (10000.0F) < fabs(f32BPoint[1])
                || (10000.0F) < fabs(f32BPoint[2]) || (10000.0F) < fabs(f32BPoint[3])
                || (10000.0F) < fabs(f32BPoint[4]) || (10000.0F) < fabs(f32BPoint[5]))
            {
                return 9;
            }

            /* 偏移不能为0 */
            if ((0.0001F) >= fabs(f32BPoint[3])
                || (0.0001F) >= fabs(f32BPoint[4])
                || (0.0001F) >= fabs(f32BPoint[5]))
            {
                return 9;
            }
            return 0;
        }
        else
            return 9;
    }

    unsigned short u16Index;                     /* 第x组参数 */
    char cRemarks[IZONE_DESCRIPTION_CHARLENGTH]; /* 备注 */
    int i32Input;                                /* 输入信号 */
    int i32Output;                               /* 输出信号 */
    unsigned short u16Scope;                     /* 内外侧 0-内侧，1-外侧 */
    unsigned short u16IsAlert;                   /* 是否报警 0-警告，1-报警 */
    float f32SafeL;                              /* 安全距离 */
    unsigned short u16WobjNum;                   /* 当前工件号 */
    short i16StopType;                           /* 停机方式 */
    short i16ZoneType;                           /* 干涉区类型 */
    short i16ForeCast;                           /* 是否开启目标点预测 */
    /* 干涉区 */
    unsigned short u16SetType;                 /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[IZONE_FLOATARRAYLENGTH]; /* 对角点 */
    float f32PointL[IZONE_FLOATARRAYLENGTH];   /* 基准点+偏移 */
} INTERFER_ZONE;

// 末端监测对象MTCP
typedef struct INTERFER_MTCP_BOX
{
    INTERFER_MTCP_BOX()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(u16IsUse, 0, IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        memset(u16ToolNum, 0, IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
    }
    INTERFER_MTCP_BOX &operator=(const INTERFER_MTCP_BOX &other)
    {
        memcpy(u16IsUse, other.u16IsUse, IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        memcpy(u16ToolNum, other.u16ToolNum, IZONE_MTCP_UINTARRAYLENGTH * sizeof(unsigned short));
        return (*this);
    }
    bool operator==(const INTERFER_MTCP_BOX &other)
    {
        if (this == &other)
            return true;
        for (size_t i = 0; i < IZONE_MTCP_UINTARRAYLENGTH; i++)
        {
            if (u16IsUse[i] != other.u16IsUse[i])
                return false;
        }
        for (size_t i = 0; i < IZONE_MTCP_UINTARRAYLENGTH; i++)
        {
            if (u16ToolNum[i] != other.u16ToolNum[i])
                return false;
        }
        return true;
    }
    unsigned short u16IsUse[IZONE_MTCP_UINTARRAYLENGTH];
    unsigned short u16ToolNum[IZONE_MTCP_UINTARRAYLENGTH];
} INTERFER_MTCP_BOX;

// 末端监测对象球体
typedef struct INTERFER_BALL_BOX
{
    INTERFER_BALL_BOX()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(f32Pos, 0, IZONE_BALL_POSARRAYLENGTH * sizeof(float));
        f32BallR = 0;
    }
    INTERFER_BALL_BOX &operator=(const INTERFER_BALL_BOX &other)
    {
        memcpy(f32Pos, other.f32Pos, IZONE_BALL_POSARRAYLENGTH * sizeof(float));
        f32BallR = other.f32BallR;
        return (*this);
    }
    bool operator==(const INTERFER_BALL_BOX &other)
    {
        if (this == &other)
            return true;

        for (size_t i = 0; i < IZONE_BALL_POSARRAYLENGTH; i++)
        {
            if (fabs(f32Pos[i] - other.f32Pos[i]) > IZONE_EPSILON)
                return false;
        }
        if (fabs(f32BallR - other.f32BallR) > IZONE_EPSILON)
            return false;

        return true;
    }

    float f32Pos[IZONE_BALL_POSARRAYLENGTH];
    float f32BallR;
} INTERFER_BALL_BOX;

// 末端监测对象长方体包围盒
typedef struct INTERFER_TOOL_BOX
{
    INTERFER_TOOL_BOX()
    {
        Initialize();
    }
    void Initialize()
    {
        u16SetType = 0;
        memset(f32Diagonal, 0, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointL, 0, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memset(f32PointH, 0, IZONE_TOOLBOX_TYPE3_FLOATARRAY * sizeof(float));
    }
    INTERFER_TOOL_BOX &operator=(const INTERFER_TOOL_BOX &other)
    {
        u16SetType = other.u16SetType;
        memcpy(f32Diagonal, other.f32Diagonal, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memcpy(f32PointL, other.f32PointL, IZONE_FLOATARRAYLENGTH * sizeof(float));
        memcpy(f32PointH, other.f32PointH, IZONE_TOOLBOX_TYPE3_FLOATARRAY * sizeof(float));
        return (*this);
    }
    bool operator==(const INTERFER_TOOL_BOX &other)
    {
        if (this == &other)
            return true;
        if (u16SetType != other.u16SetType)
            return false;
        if (u16SetType == 0)
        {
            for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH; i++)
            {
                if (fabs(f32Diagonal[i] - other.f32Diagonal[i]) > IZONE_EPSILON)
                    return false;
            }
        }
        else if (u16SetType == 1)
        {
            for (size_t i = 0; i < IZONE_FLOATARRAYLENGTH; i++)
            {
                if (fabs(f32PointL[i] - other.f32PointL[i]) > IZONE_EPSILON)
                    return false;
            }
        }
        else
        {
            for (size_t i = 0; i < IZONE_TOOLBOX_TYPE3_FLOATARRAY; i++)
            {
                if (fabs(f32PointH[i] - other.f32PointH[i]) > IZONE_EPSILON)
                    return false;
            }
        }

        return true;
    }

    int IsPointsValid()
    {
        if (u16SetType == 0)  // 对角点
        {
            float tmp[6] = { 0 };
            memcpy(&tmp[0], &f32Diagonal[0], sizeof(float) * IZONE_FLOATARRAYLENGTH);
            double f64P1 = static_cast<double>(tmp[0]) - static_cast<double>(tmp[3]);
            double f64P2 = static_cast<double>(tmp[1]) - static_cast<double>(tmp[4]);
            double f64P3 = static_cast<double>(tmp[2]) - static_cast<double>(tmp[5]);
            if ((0.0001F) > fabs(f64P1)
                || (0.0001F) > fabs(f64P2)
                || (0.0001F) > fabs(f64P3))
            {
                return 9;
            }

            for (int i = 0; i < IZONE_FLOATARRAYLENGTH; ++i)
            {
                double f64DP = static_cast<double>(tmp[i]);
                if (10000.0F < fabs(f64DP))
                {
                    return 9;
                }
            }
            return 0;
        }
        else if (u16SetType == 1)  // 基准点
        {
            float f32BPoint[IZONE_FLOATARRAYLENGTH] = { 0 };
            memcpy(&f32BPoint[0], &f32PointL[0], sizeof(float) * IZONE_FLOATARRAYLENGTH);
            if ((10000.0F) < fabs(f32BPoint[0]) || (10000.0F) < fabs(f32BPoint[1])
                || (10000.0F) < fabs(f32BPoint[2]) || (10000.0F) < fabs(f32BPoint[3])
                || (10000.0F) < fabs(f32BPoint[4]) || (10000.0F) < fabs(f32BPoint[5]))
            {
                return 9;
            }

            /* 偏移不能为0 */
            if ((0.0001F) >= fabs(f32BPoint[3])
                || (0.0001F) >= fabs(f32BPoint[4])
                || (0.0001F) >= fabs(f32BPoint[5]))
            {
                return 9;
            }
            return 0;
        }
        else if (u16SetType == 2)  // toolbox
        {
            float tmp[13] = { 0 };
            memcpy(&tmp[0], &f32PointH[0], sizeof(float) * IZONE_TOOLBOX_TYPE3_FLOATARRAY);

            for (int i = 0; i < 13; ++i)
            {
                double f64DP = static_cast<double>(tmp[i]);
                if (10000.0F < fabs(f64DP))
                {
                    return 9;
                }
            }

            if (tmp[12] < 0.0001F)
                return 9;

            float p1[3] = { tmp[0], tmp[1], tmp[2] };
            float p2[3] = { tmp[3], tmp[4], tmp[5] };
            float p3[3] = { tmp[6], tmp[7], tmp[8] };
            float p4[3] = { tmp[9], tmp[10], tmp[11] };

            if (!NotInAPointOrLine_4Points(p1, p2, p3, p4))
                return 9;

            return 0;
        }
        else
            return 9;
    }

public:
    static bool NotInAPointOrLine_4Points(const float (&p1)[3], const float (&p2)[3], const float (&p3)[3], const float (&p4)[3])
    {
        int i = 0, j = 0;
        if (IsSamePoint(p1, p2))
        {
            j++;
            if (IsSamePoint(p1, p3))
            {
                j++;
                if (IsSamePoint(p1, p4))
                {
                    j++;
                }
            }
        }
        switch (j)
        {
            case 0:
                if (IsPointOnLine(p1, p2, p3) && IsPointOnLine(p1, p2, p4))
                {
                    return false;
                }
                else
                {
                    return true;
                }
                // break;
            case 1:
                if (IsPointOnLine(p1, p3, p4))
                {
                    return false;
                }
                else
                {
                    return true;
                }
                // break;
            default:
                return false;
                // break;
        }
    }

    static bool IsSamePoint(const float (&a)[3], const float (&b)[3])
    {
        int i = 0;
        for (i = 0; i < 3; i++)
        {
            float diff = a[i] - b[i];
            if (fabs(diff) > 0.0001F)
            {
                return false;
            }
        }
        return true;
    }

    static bool IsPointOnLine(const float (&a)[3], const float (&b)[3], const float (&c)[3])
    {
        float lineVector[3] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
        float pointVector[3] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };
        float result[3] = { 0 };
        InterCross(lineVector, pointVector, result);
        return (result[0] == 0 && result[1] == 0 && result[2] == 0);
    }

    static void InterCross(const float (&a)[3], const float (&b)[3], float out[3])
    {
        out[0] = a[1] * b[2] - a[2] * b[1];
        out[1] = a[2] * b[0] - a[0] * b[2];
        out[2] = a[0] * b[1] - a[1] * b[0];
    }

    unsigned short u16SetType;                       /* 设置方式0-对角，1-基准点+边长 */
    float f32Diagonal[IZONE_FLOATARRAYLENGTH];       /* 对角点 */
    float f32PointL[IZONE_FLOATARRAYLENGTH];         /* 基准点+偏移 */
    float f32PointH[IZONE_TOOLBOX_TYPE3_FLOATARRAY]; /* 取点+高度 */
} INTERFER_TOOL_BOX;

/* 监控对象, 内含MTCP, 球体, 长方体包围盒 */
typedef struct INTERFER_TOOL
{
    INTERFER_TOOL()
    {
        Initialize();
    }
    void Initialize()
    {
        u16Index = 0;
        u16Type = 0;
        memset(cRemarks, 0, IZONE_DESCRIPTION_CHARLENGTH);

        stMTcpBox.Initialize();
        stBallBox.Initialize();
        stToolBox.Initialize();
    }
    INTERFER_TOOL &operator=(const INTERFER_TOOL &other)
    {
        u16Index = other.u16Index;
        u16Type = other.u16Type;
        memcpy(cRemarks, other.cRemarks, IZONE_DESCRIPTION_CHARLENGTH);

        stMTcpBox = other.stMTcpBox;
        stBallBox = other.stBallBox;
        stToolBox = other.stToolBox;
        return (*this);
    }
    bool operator==(const INTERFER_TOOL &other)
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

    int IsPointsValid()
    {
        if (u16Type == 3)  // toolbox情况下检查点位值
            return stToolBox.IsPointsValid();

        return 0;
    }

    unsigned short u16Index;                     /* 第x组参数 */
    unsigned short u16Type;                      /* 监控对象类型 */
    char cRemarks[IZONE_DESCRIPTION_CHARLENGTH]; /* 备注 */
    INTERFER_MTCP_BOX stMTcpBox;
    INTERFER_BALL_BOX stBallBox;
    INTERFER_TOOL_BOX stToolBox;
} INTERFER_TOOL;

// 干涉区激活状态
typedef struct INTERFER_ZONE_STATUS
{
    INTERFER_ZONE_STATUS()
    {
        uint16IZonesIndex = 0;
        memset(cRemarks, 0x00, IZONE_DESCRIPTION_CHARLENGTH);
    }
    unsigned short uint16IZonesIndex;
    char cRemarks[IZONE_DESCRIPTION_CHARLENGTH];
} INTERFER_ZONE_STATUS;

// 干涉区工件参数相关
typedef struct INTERFER_ZONE_WOBJPARAM
{
    INTERFER_ZONE_WOBJPARAM()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterWobjParams, 0, sizeof(InterWobjParams));
    }
    INTERFER_ZONE_WOBJPARAM &operator=(const INTERFER_ZONE_WOBJPARAM &other)
    {
        memcpy(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE_WOBJPARAM &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterWobjParams, &other.InterWobjParams, sizeof(InterWobjParams)))
            return false;

        return true;
    }
    double InterWobjParams[IZONE_WOBJPARAMSNUM];  // 干涉区 - 工件 - 工件坐标系
} INTERFER_ZONE_WOBJPARAM;

// 干涉区工具参数相关
typedef struct INTERFER_ZONE_MTCPTOOLPARAM
{
    INTERFER_ZONE_MTCPTOOLPARAM()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(InterTFramePos, 0, sizeof(InterTFramePos));
    }

    INTERFER_ZONE_MTCPTOOLPARAM &operator=(const INTERFER_ZONE_MTCPTOOLPARAM &other)
    {
        memcpy(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos));
        return (*this);
    }

    bool operator==(const INTERFER_ZONE_MTCPTOOLPARAM &other)
    {
        if (this == &other)
            return true;

        if (0 != memcmp(&InterTFramePos, &other.InterTFramePos, sizeof(InterTFramePos)))
            return false;

        return true;
    }
    double InterTFramePos[IZONE_MTCPTOOLPARAMSNUM * IZONE_MTCP_UINTARRAYLENGTH];  // 末端监控对象MTCP - 工具参数
} INTERFER_ZONE_MTCPTOOLPARAM;

// 干涉区所有功能的集合
typedef struct INTERFER_ZONE_PACK
{
    INTERFER_ZONE_STATUS IZONES_STATUS[IZONE_INTERFERZONESSTATUSLENGTH];
    INTERFER_ZONE_STATUS ITOOLS_STATUS[IZONE_INTERFERZONESSTATUSLENGTH];

    INTERFER_ZONE IZONES_PARA[IZONE_INTERFERZONESSTATUSLENGTH];
    INTERFER_ZONE_WOBJPARAM IZONES_WOBJ[IZONE_INTERFERZONESSTATUSLENGTH];

    INTERFER_TOOL ITOOLS_PARA[IZONE_INTERFERZONESSTATUSLENGTH];
    INTERFER_ZONE_MTCPTOOLPARAM ITOOLS_MTCP_TOOL[IZONE_INTERFERZONESSTATUSLENGTH];

} S_CPOS;

// 干涉区激活状态
typedef struct INTERFER_ZONES_STATUS
{
    INTERFER_ZONES_STATUS()
    {
        Initialize();
    }
    void Initialize()
    {
        memset(uint16IZonesIndex, 0, IZONE_INTERFERZONESSTATUSLENGTH * sizeof(unsigned short));
        memset(cRemarks, 0, IZONE_INTERFERZONESSTATUSLENGTH * IZONE_DESCRIPTION_CHARLENGTH);
    }
    unsigned short uint16IZonesIndex[16];
    char cRemarks[16][32];

} INTERFER_ZONES_STATUS;

#pragma pack()
#pragma endregion

#pragma region 轨迹恢复阈值设置
#pragma pack(1)
// 轨迹恢复阈值设置参数
struct TrajRecoveryThreshold
{
    TrajRecoveryThreshold()
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

// 轨迹恢复设置参数
struct TrajRecoveryParam
{
    TrajRecoveryParam()
    {
        Initialize();
    }
    void Initialize()
    {
        i32Mode = 0;
    }

    int i32Mode;                          // 轨迹恢复与之设置模式
    TrajRecoveryThreshold stManualParam;  // 位置模式下，手动阈值参数
    TrajRecoveryThreshold stAutoParam;    // 位置模式下，自动阈值参数
};
#pragma pack()
#pragma endregion

#pragma region 零点设置

#pragma region 零点校准

#define JOINT_AXIS_NUM_SIX 6  // 六关节轴数

/// <summary>
/// 参数结构体
/// </summary>
struct ZeroPointCalibrateParam
{
    ZeroPointCalibrateParam()
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

/// <summary>
/// 校准命令结构体
/// </summary>
struct ZeroPointCommand
{
    ZeroPointCommand()
    {
        i16Axis = 0;
        i16Direction = 1;
        i16Command = 0;
        i16Type = 0;
    }
    ZeroPointCommand(int16s axisNo, int16s direction, int16s command, int16s type = 0)
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

/// <summary>
/// 状态反馈结构体
/// </summary>
struct ZeroPointResult
{
    ZeroPointResult()
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

/// <summary>
/// 参数重置结构体
/// </summary>
struct ZeroPointResetParam
{
    ZeroPointResetParam()
    {
        Initialize();
    }
    void Initialize()
    {
        for (int i = 0; i < JOINT_AXIS_NUM_SIX; i++)
        {
            i32PosOffset[i] = 0;
            f64EmptyLoadCurrent[i] = 0.0;
        }
    }
    int i32PosOffset[JOINT_AXIS_NUM_SIX];            // 零点偏置
    double f64EmptyLoadCurrent[JOINT_AXIS_NUM_SIX];  // 空载电流
};

/// <summary>
/// 零点校准UI信息结构体
/// </summary>
struct ZeroPointUiParam
{
    ZeroPointUiParam()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < JOINT_AXIS_NUM_SIX; i++)
        {
            i32Status[i] = 0;
            i32CaliValue[i] = 0;
        }
        i32SelectedPage = 0;
        i32CalibrateMode = 0;
        i32LoadNumber = 0;
    }

    int i32Status[JOINT_AXIS_NUM_SIX];     // 各轴校准状态
    int i32CaliValue[JOINT_AXIS_NUM_SIX];  // 各轴校准值
    int i32SelectedPage;                   // UI子页面索引
    int i32CalibrateMode;                  // UI校准模式
    int i32LoadNumber;                     // 负载号
};

/// <summary>
/// 传感器开关命令结构体
/// </summary>
struct ZeroPointSensorSwitch
{
    ZeroPointSensorSwitch()
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

/// <summary>
/// 开发者模式下的零点参数
/// </summary>
struct ZeroPointParamDeveloper
{
    ZeroPointParamDeveloper()
    {
        Initialize();
    }

    void Initialize()
    {
        i16LoadState = 0;
        i16Mode = 0;
        for (int i = 0; i < JOINT_AXIS_NUM_SIX; i++)
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

    int16s i16LoadState;                         // 负载状态：0-空载，1-负载1，2-负载2
    int16s i16Mode;                              // 模式标志：0-普通模式，1-开发者模式
    int i32OffSetLoad0[JOINT_AXIS_NUM_SIX];      // 空载零点偏置
    int i32OffSetLoad1[JOINT_AXIS_NUM_SIX];      // 空载零点偏置
    int i32OffSetLoad2[JOINT_AXIS_NUM_SIX];      // 空载零点偏置
    float f32TrqLoad0[JOINT_AXIS_NUM_SIX];       // 空载碰撞前电流
    float f32TrqLoad1[JOINT_AXIS_NUM_SIX];       // 空载碰撞前电流
    float f32TrqLoad2[JOINT_AXIS_NUM_SIX];       // 空载碰撞前电流
    float f32CompensationK[JOINT_AXIS_NUM_SIX];  // 负载补偿斜率
    float f32CompensationB[JOINT_AXIS_NUM_SIX];  // 负载补偿截距
};
#pragma endregion

#pragma region DeviceNet

#define DEVICENET_STRING_NUM 30
#define DEVICENET_SLAVE_NUM  8  // 从站数量最多8个
typedef struct _DeviceNetMaster_
{
    int nodeID;
    char baudrate[DEVICENET_STRING_NUM];

    _DeviceNetMaster_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(baudrate, 0, DEVICENET_STRING_NUM);
        nodeID = 0;
    }

    bool Compare(const _DeviceNetMaster_ &other)
    {
        if (nodeID != other.nodeID)
            return false;
        for (int i = 0; i < DEVICENET_STRING_NUM; ++i)
        {
            if (other.baudrate[i] != baudrate[i])
                return false;
        }
        return true;
    }

} DeviceNetMaster;

typedef struct _DeviceNetInOut_
{
    int Size;
    int Offset;

    _DeviceNetInOut_()
    {
        Initialize();
    }

    void Initialize()
    {
        Size = 0;
        Offset = 0;
    }

    bool Compare(const _DeviceNetInOut_ &other)
    {
        if (Size != other.Size || Offset != other.Offset)
            return false;
        return true;
    }

} DeviceNetInOut;

typedef struct _DeviceNetSlave_
{
    int nodeID;
    int VendCode;
    int ProdType;
    int ProdCode;
    int Erp;
    DeviceNetInOut Input;
    DeviceNetInOut Output;

    _DeviceNetSlave_()
    {
        Initialize();
    }

    void Initialize()
    {
        nodeID = 0;
        VendCode = 0;
        ProdType = 0;
        ProdCode = 0;
        Erp = 0;
        Input.Initialize();
        Output.Initialize();
    }

    bool Compare(const _DeviceNetSlave_ &other)
    {
        if (other.nodeID != nodeID || other.VendCode != VendCode || other.ProdType != ProdType
            || other.ProdCode != ProdCode || other.Erp != Erp)
            return false;
        if (!Input.Compare(other.Input) || !Output.Compare(other.Output))
            return false;
        return true;
    }

} DeviceNetSlave;

typedef struct _DeviceNetParam_
{
    char Version[DEVICENET_STRING_NUM];
    bool IsValid;
    DeviceNetMaster Master;
    int SlaveNum;
    vector<DeviceNetSlave> Slaves;

    _DeviceNetParam_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(Version, 0, DEVICENET_STRING_NUM);
        IsValid = false;
        Master.Initialize();
        SlaveNum = 0;
        Slaves.clear();
        for (int i = 0; i < DEVICENET_SLAVE_NUM; i++)
        {
            DeviceNetSlave deviceNetSlave;
            Slaves.push_back(deviceNetSlave);
        }
    }

    bool Compare(const _DeviceNetParam_ &other)
    {
        if (other.IsValid != IsValid || other.SlaveNum != SlaveNum)
            return false;
        if (!Master.Compare(other.Master))
            return false;
        for (int i = 0; i < DEVICENET_STRING_NUM; ++i)
        {
            if (other.Version[i] != Version[i])
                return false;
        }
        if (Slaves.size() != other.Slaves.size())
            return false;
        for (size_t i = 0; i < Slaves.size(); ++i)
        {
            if (!Slaves[i].Compare(other.Slaves[i]))
                return false;
        }
        return true;
    }

} DeviceNetParam;
#pragma endregion

#pragma region EcatADDA状态
#pragma pack(push)
#pragma pack(1)
#define ETHERCAT_ADDA_MAX_NUM 16
// EcatADDA状态
typedef struct _EcatAdDaState_
{
    _EcatAdDaState_()
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

    _EcatAdDaState_ &operator=(const _EcatAdDaState_ &other)
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
    bool compare(const _EcatAdDaState_ &other)
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
} EcatAdDaState;

// Ecat从站状态
typedef struct _EcatSlaveInfo_
{
    _EcatSlaveInfo_()
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
} EcatSlaveInfo;

// Ecat从站管理状态
typedef struct _EcatSlaveManageState_
{
    _EcatSlaveManageState_()
    {
        InitZero();
    }
    void InitZero()
    {
        u8SlaveNum = 0;
        u8funtionSwitch = 0;
    }

    int8u u8funtionSwitch;             // 从站管理功能开关  0：关闭  1：开启
    int8u u8SlaveNum;                  // 从站数
    EcatSlaveInfo sEcatSlaveInfo[24];  // 从站管理状态参数
} EcatSlaveManageState;

#pragma pack(pop)
#pragma endregion

#pragma pack(push)
#pragma pack(1)
// EIP从站状态
// 固定支持8个从站，一个从站支持4个连接
#define EIPSLAVENUM     8
#define EIPSLAVECONNNUM 32

struct EIPSlaveInfo
{
    EIPSlaveInfo()
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

// EIP从站管理状态
struct EIPSlaveManageState
{
    EIPSlaveManageState()
    {
        InitZero();
    }
    void InitZero()
    {
        u8SlaveNum = 0;
    }

    int8u u8SlaveNum;                         // 从站数
    EIPSlaveInfo sEIPSlaveInfo[EIPSLAVENUM];  // 从站管理状态参数
};

// EIP从站连接状态
struct EipSlaveConnState
{
    int8u u8Instance;      // 连接实例号
    char slaveConnIP[16];  // 连接的IP地址
    int8u connState;       // 连接的状态 0——未连接；1——已连接
    int8u connIfCfg;       // 该连接是否配置

    EipSlaveConnState()
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

struct EipSlaveConnsState
{
    EipSlaveConnState connsState[EIPSLAVECONNNUM];
    EipSlaveConnsState()
    {
        memset(connsState, 0, sizeof(EipSlaveConnState) * EIPSLAVECONNNUM);
    }
};

#define FileLength 256
#define MaxFileNum 3  // 最大接受文件数量

typedef struct _UPLOAD_FILE_INFO_
{
    UINT32 taskID;              // 任务号
    UINT32 fileTimes;           // 文件上传次数
    char filePath[FileLength];  // 文件名称

    _UPLOAD_FILE_INFO_()
    {
        taskID = 0;
        fileTimes = 0;
        memset(filePath, 0, FileLength);
    }
} Upload_File_Info;

typedef struct _FileReadAndWriteInfo_
{
    Upload_File_Info fileReadWriteInfo[MaxFileNum];
    _FileReadAndWriteInfo_()
    {
        for (int i = 0; i < MaxFileNum; ++i)
            fileReadWriteInfo[i] = _UPLOAD_FILE_INFO_();
    }
} FileReadAndWriteInfo;

#pragma pack(pop)

enum FTPResultType
{
    FTPReady = 0,     // 就绪
    FTPTransmitting,  // 传输中
    FTPSuccess,
    FTPFail
};

#pragma endregion

#pragma region 设备寿命预测
#pragma pack(1)

#define COLLECT_AXIS_NUM (6)

// 设备寿命配置
struct Device_Life_Config
{
    Device_Life_Config()
    {
        f64AccPercent = 0.000;
        f64DecPercent = 0.000;
        f64StartJerkPercent = 0.000;
        f64EndJerkPercent = 0.000;
        i8TriggerMethod = 1;
        u16SampleBeatNum = 2;
        u8HoursPerDay = 24;
        u16DaysPerYear = 365;
    }

    double f64AccPercent;       /* 加速度 */
    double f64DecPercent;       /* 减速度 */
    double f64StartJerkPercent; /* 加加速度 */
    double f64EndJerkPercent;   /* 减加速度 */
    int8s i8TriggerMethod;      /* 触发方式，0-手动，1-指令 */
    int16u u16SampleBeatNum;    /* 采集节拍数目 */
    int8u u8HoursPerDay;        /* 每天运作小时数 */
    int16u u16DaysPerYear;      /* 每年运作天数 */
};

// 单轴设备寿命结果
struct Device_Life_Result
{
    Device_Life_Result()
    {
        f64LifeL10_InHours = 0;
    }

    void clear()
    {
        f64LifeL10_InHours = 0;
    }

    double f64LifeL10_InHours; /* 寿命，单位：小时 */
};

// 设备采集状态
typedef enum
{
    DEVICE_ERROR = 0,          /* 状态错误 */
    DEVICE_READY = 1,          /* 就绪状态 */
    DEVICE_COLLECTING = 2,     /* 采集状态 */
    DEVICE_OUTPUTING = 3,      /* 输出状态 */
    DEVICE_OUTPUTFINISHED = 4, /* 输出完成状态 */
    DEVICE_STATUS_NUM          /*状态数量*/
} DEVICECOLLECTSTATUS;

// 设备各轴寿命结果
struct DEVICE_ALLAXIS_RESULT
{
    DEVICE_ALLAXIS_RESULT()
    {
        for (int i = 0; i < COLLECT_AXIS_NUM; i++)
        {
            stDeviceResult[i].clear();
            u8LifeCalStatus = DEVICE_READY;
            f32SecondsPerBeat = 0;
            u16TriggerEvent = 0;
        }
    }

    Device_Life_Result stDeviceResult[COLLECT_AXIS_NUM]; /* 各轴减速机寿命结果 */
    float f32SecondsPerBeat;                             /* 每个节拍的循环时间 */
    int8u u8LifeCalStatus;                               /* 采集状态 */
    int16u u16TriggerEvent;                              /* 触发事件 */
};

struct RVLifeSpanCmd
{
    RVLifeSpanCmd()
    {
        i16Cmd = 0;
        i16BeatMode = 0;
        i16BeatCount = 0;
    }

    int16s i16Cmd;       /*命令:1-启动;2-中止*/
    int16s i16BeatMode;  /*节拍数指定方式:0-指令确定;1-页面指定*/
    int16s i16BeatCount; /*节拍数*/
};

#define RV_SPANRESULT_SIZE (6)
#define RV_THRESHOLD_SIZE  (6)
#define RV_PARAMETERS_SIZE (4)
struct RVLifeSpanStat
{
    RVLifeSpanStat()
    {
        i16Stat = 0;
        i16LoopNum = 0;
        i16CheckNum = 0;
        for (int i = 0; i < 6; i++)
        {
            SpanResult[i] = 0;
        }
    }

    int16s i16Stat;      /*寿命核算状态*/
    int16s i16LoopNum;   /*节拍总数*/
    int16s i16CheckNum;  /*已进行节拍数*/
    float SpanResult[6]; /*寿命核算结果*/
};

typedef enum
{
    NOTEXIST = -1,  // 不存在
    HARMONIC = 0,   // 谐波减速机
    RV = 1,         // RV减速机
    PLANETARY = 2,
} ENUMRVType;

typedef enum
{
    RV_NOCMD = 0,      /*无命令,默认状态*/
    RV_WAITING = 1,    /*等待开始*/
    RV_COLLECTING = 2, /*数据采集中*/
    RV_COLLECTEND = 3, /*数据采集完成*/
    RV_DONE = 4,       /*计算完成*/
    RV_SUSPEND = 5,    /*中止计算 */
    ENUMRVStatNum = 6,
} ENUMRVStat;

struct RVStatStrStruct
{
    ENUMRVStat type;  // 减速机状态
    string name;      // 减速机名称
};

#pragma pack()
#pragma endregion

#pragma region 零点恢复
#pragma pack(push)
#pragma pack(1)
#define ZERO_CALIB_NUM      6
#define ZERO_CALIB_JPOS_NUM 15
#define DIR_SIX_DEMIS_NUM   6

// 零点修复标定结果
typedef struct _ZeroPointRepairCalibResult_
{
    _ZeroPointRepairCalibResult_()
    {
        InitZero();
    }
    void InitZero()
    {
        f64Score = 0;
        f64SuccessFlag = 0;
        for (int i = 0; i < ZERO_CALIB_NUM; i++)
        {
            f64ZeroPulse[i] = 0;
            f64dZero[i] = 0;
            f64ToolPara[i] = 0;
        }
        f64ErrAve = 0;
        f64ErrMax = 0;
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM - 1; i++)
        {
            f64Err[i] = 0;
        }
    }

    _ZeroPointRepairCalibResult_ &operator=(const _ZeroPointRepairCalibResult_ &other)
    {
        this->f64SuccessFlag = other.f64SuccessFlag;
        this->f64Score = other.f64Score;
        for (int i = 0; i < ZERO_CALIB_NUM; i++)
        {
            this->f64ZeroPulse[i] = other.f64ZeroPulse[i];
            this->f64dZero[i] = other.f64dZero[i];
            this->f64ToolPara[i] = other.f64ToolPara[i];
        }
        this->f64ErrAve = other.f64ErrAve;
        this->f64ErrMax = other.f64ErrMax;
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM - 1; i++)
        {
            this->f64Err[i] = other.f64Err[i];
        }
        return (*this);
    }

    double f64Score;                         // 分数
    int f64SuccessFlag;                      // 标定成功位标志，1：成功
    double f64ZeroPulse[ZERO_CALIB_NUM];     // 标定后零点脉冲值
    double f64dZero[ZERO_CALIB_NUM];         // 零点变化角度
    double f64ToolPara[ZERO_CALIB_NUM];      // 工具标定参数，XYZABC，工具末端相对法兰的位
    double f64ErrAve;                        // 标定平均误差
    double f64ErrMax;                        // 标定最大误差
    double f64Err[ZERO_CALIB_JPOS_NUM - 1];  // 标定误差
} ZeroPointRepairCalibResult;

// 零点修复标定数据
typedef struct _ZeroPointRepairPosData_
{
    double f64JPos[JOINT_AXIS_NUM];  // 机器人取点时的关节角

    _ZeroPointRepairPosData_()
    {
        InitZero();
    }
    void InitZero()
    {
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            f64JPos[i] = 0;
        }
    }

    _ZeroPointRepairPosData_ &operator=(const _ZeroPointRepairPosData_ &other)
    {
        for (int i = 0; i < JOINT_AXIS_NUM; i++)
        {
            this->f64JPos[i] = other.f64JPos[i];
        }
        return (*this);
    }
} ZeroPointRepairPosData;

// 零点修复标定数据（中间点和标定结果，存文件）
typedef struct _ZeroPointRepairCalibData_
{
    int16u iPosDataNum;                                                    // 标定中间点数据的实际个数
    ZeroPointRepairPosData stZeroPointRepairPosData[ZERO_CALIB_JPOS_NUM];  // 标定中间点数据
    ZeroPointRepairCalibResult stZeroPointRepairCalibResult;               // 标定结果

    _ZeroPointRepairCalibData_()
    {
        Initialize();
    }

    void Initialize()
    {
        iPosDataNum = 0;
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM; i++)
        {
            stZeroPointRepairPosData[i].InitZero();
        }
        stZeroPointRepairCalibResult.InitZero();
    }

    _ZeroPointRepairCalibData_ &operator=(const _ZeroPointRepairCalibData_ &other)
    {
        this->iPosDataNum = other.iPosDataNum;
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM; i++)
        {
            this->stZeroPointRepairPosData[i] = other.stZeroPointRepairPosData[i];
        }
        this->stZeroPointRepairCalibResult = other.stZeroPointRepairCalibResult;
        return (*this);
    }
} ZeroPointRepairCalibData;

/// <summary>
/// 一组零点修复标定数据，接口所需
/// </summary>
typedef struct _ZeroPointRepairCalibItem_
{
    ZeroPointRepairPosData stZeroPointRepairPosData[ZERO_CALIB_JPOS_NUM];  // 标定中间点数据
    double f64Ratio[DIR_SIX_DEMIS_NUM];                                    // 减速比
    int16u iPosDataNum;                                                    // 标定中间点数据的实际个数
    double f64ZeroPulse[ZERO_CALIB_NUM];                                   // 标定前零点值

    _ZeroPointRepairCalibItem_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM; i++)
        {
            stZeroPointRepairPosData[i].InitZero();
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f64Ratio[i] = 0;
        }
        iPosDataNum = 0;
        for (int i = 0; i < ZERO_CALIB_NUM; i++)
        {
            f64ZeroPulse[i] = 0;
        }
    }

    _ZeroPointRepairCalibItem_ &operator=(const _ZeroPointRepairCalibItem_ &other)
    {
        for (int i = 0; i < ZERO_CALIB_JPOS_NUM; i++)
        {
            this->stZeroPointRepairPosData[i] = other.stZeroPointRepairPosData[i];
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            this->f64Ratio[i] = other.f64Ratio[i];
        }
        this->iPosDataNum = other.iPosDataNum;
        for (int i = 0; i < ZERO_CALIB_NUM; i++)
        {
            this->f64ZeroPulse[i] = other.f64ZeroPulse[i];
        }
        return (*this);
    }
} ZeroPointRepairCalibItem;

// 运动学库模型初始化参数
typedef struct _KineParm_
{
    /// <summary>
    /// 运动学连杆参数
    /// </summary>
    double linkParm[LINK_PARM_NUM];

    /// <summary>
    /// 运动学库补偿参数
    /// </summary>
    double compParm[COM_PARM_NUM];

    /// <summary>
    /// 运动学库刚度参数
    /// </summary>
    double stiffParm[STIF_PARM_NUM];
} KineParm;

typedef struct _MechUnitPara_
{
    _MechUnitPara_()
    {
        Initialize();
    }

    void Initialize()
    {
        MecIndex = 0;
        Type = 0;
        InstallType = 0;
        AxisCount = 0;
        MoveMecIndex = 0;
        for (int i = 0; i < MECHUNIT_TRANSFORMAT_COUNT; i++)
        {
            Transformat[i].Initialize();
        }
        for (int i = 0; i < MECHUNIT_AXIS_MAP_COUNT; i++)
        {
            AxisMap[i] = 0xff;
        }
    }

    int MecIndex;                                                 // 机械单元的名称
    int16u Type;                                                  // 0:机器人; 1:X轴导轨; 2:单轴旋转变位机; 3:双轴旋转变位机; 101:无模型1轴; 102:无模型2轴; ...
    int8u InstallType;                                            // 0:固定安装; 1:在可移动的导轨上(机械单元上)
    int8u MoveMecIndex;                                           // InstallType为1时，对应的可移动的导轨的机械单元名称
    int8u AxisCount;                                              // 轴数目
    RelativeTransformat Transformat[MECHUNIT_TRANSFORMAT_COUNT];  // 转换
    int8u AxisMap[MECHUNIT_AXIS_MAP_COUNT];                       // 轴映射关系
} MechUnitPara;

#pragma pack(pop)

#pragma endregion

#pragma region 力控

#pragma pack(push)
#pragma pack(1)
#define DIR_SIX_DEMIS_NUM             6
#define DIR_THREE_DEMIS_NUM           3
#define FORCE_CTRL_CALIB_POINT_NUM    8
#define FORCE_CTRL_CAILB_DATA_MAX_NUM 16
#define FORCE_CTRL_SENSOR_NUM         4
#define FORCE_CTRL_INPUT_RESERVE      19
#define FORCE_CTRL_OUTPUT_RESERVE     24
#define TOLERANCE                     0.001

enum ForceCtrlSensorType : int
{
    None = 0,   // 无
    ONE = 1,    // 一维传感器
    THREE = 2,    // 三维传感器
    SIX = 3,    // 六维传感器
};

// 力控标定结果
typedef struct _ForceCtrlCalibResult_
{
    _ForceCtrlCalibResult_()
    {
        InitZero();
    }
    void InitZero()
    {
        f64LoadGravity = 0;
        for (int i = 0; i < DIR_THREE_DEMIS_NUM; i++)
        {
            f64LoadCoord[i] = 0;
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f64ZeroForce[i] = 0;
        }
        for (int i = 0; i < DIR_THREE_DEMIS_NUM; i++)
        {
            f64GL[i] = 0;
        }
    }

    _ForceCtrlCalibResult_ &operator=(const _ForceCtrlCalibResult_ &other)
    {
        this->f64LoadGravity = other.f64LoadGravity;
        for (int i = 0; i < DIR_THREE_DEMIS_NUM; i++)
        {
            this->f64LoadCoord[i] = other.f64LoadCoord[i];
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            this->f64ZeroForce[i] = other.f64ZeroForce[i];
        }
        for (int i = 0; i < DIR_THREE_DEMIS_NUM; i++)
        {
            this->f64GL[i] = other.f64GL[i];
        }
        return (*this);
    }

    bool Compare(_ForceCtrlCalibResult_ *otherTool)
    {
        if (abs(f64LoadGravity - otherTool->f64LoadGravity) > TOLERANCE)
        {
            return false;
        }
        for (int i = 0; i < DIR_THREE_DEMIS_NUM; i++)
        {
            if (abs(f64LoadCoord[i] - otherTool->f64LoadCoord[i]) > TOLERANCE)
                return false;
            if (abs(f64GL[i] - otherTool->f64GL[i]) > TOLERANCE)
                return false;
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            if (abs(f64ZeroForce[i] - otherTool->f64ZeroForce[i]) > TOLERANCE)
                return false;
        }
        return true;
    }

    double f64LoadGravity;                     // 负载重力
    double f64LoadCoord[DIR_THREE_DEMIS_NUM];  // 负载重心坐标
    double f64ZeroForce[DIR_SIX_DEMIS_NUM];    // 零点影响的力，六维（Fx、Fy、Fz，Mx，My，Mz），一维（Fz，对应索引[2]）
    double f64GL[DIR_THREE_DEMIS_NUM];         // 重力在传感器坐标系的分量
} ForceCtrlCalibResult;

// 标定：力控位置和力数据
typedef struct _ForceCtrlPosData_
{
    _ForceCtrlPosData_()
    {
        InitZero();
    }
    void InitZero()
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f64Pos[i] = 0;
            f64JPos[i] = 0;
            f64Force[i] = 0;
        }
    }

    _ForceCtrlPosData_ &operator=(const _ForceCtrlPosData_ &other)
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            this->f64Pos[i] = other.f64Pos[i];
            this->f64JPos[i] = other.f64JPos[i];
            this->f64Force[i] = other.f64Force[i];
        }
        return (*this);
    }
    double f64Pos[DIR_SIX_DEMIS_NUM];    // 机器人取点时的笛卡尔位置
    double f64JPos[DIR_SIX_DEMIS_NUM];   // 机器人取点时的关节角
    double f64Force[DIR_SIX_DEMIS_NUM];  // 六维力
} ForceCtrlPosData;

// 一组力控标定数据
typedef struct _ForceCtrlCalibItem_
{
    int16s i16ToolNo;                                                 // 工具号
    int16s i16SensorNo;                                               // 传感器号，默认为0
    int16s i16SensorType;                                             // 传感器类型，默认为0, 0:无传感器，1:一维，2:六维
    double f64ForceSensorCoord[DIR_SIX_DEMIS_NUM];                    // 传感器坐标系相对于法兰坐标系的法兰偏移X/Y/Z/A/B/C
    ForceCtrlPosData stForceCtrlPosData[FORCE_CTRL_CALIB_POINT_NUM];  // 标定数据
    ForceCtrlCalibResult stForceCtrlCalibResult;                      // 标定结果

    _ForceCtrlCalibItem_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16ToolNo = 0;
        i16SensorNo = 0;
        i16SensorType = 0;
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f64ForceSensorCoord[i] = 0;
        }
        for (int i = 0; i < FORCE_CTRL_CALIB_POINT_NUM; i++)
        {
            stForceCtrlPosData[i].InitZero();
        }
        stForceCtrlCalibResult.InitZero();
    }

    _ForceCtrlCalibItem_ &operator=(const _ForceCtrlCalibItem_ &other)
    {
        this->i16ToolNo = other.i16ToolNo;
        this->i16SensorNo = other.i16SensorNo;
        this->i16SensorType = other.i16SensorType;
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f64ForceSensorCoord[i] = other.f64ForceSensorCoord[i];
        }
        for (int i = 0; i < FORCE_CTRL_CALIB_POINT_NUM; i++)
        {
            this->stForceCtrlPosData[i] = other.stForceCtrlPosData[i];
        }
        this->stForceCtrlCalibResult = other.stForceCtrlCalibResult;
        return (*this);
    }

    bool Compare(_ForceCtrlCalibItem_ *otherTool)
    {
        // 用于标定首页判断界面的数据是否变化了，只比较页面的数据
        if (i16SensorNo != otherTool->i16SensorNo
            || !stForceCtrlCalibResult.Compare(&otherTool->stForceCtrlCalibResult))
        {
            return false;
        }
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            if (abs(f64ForceSensorCoord[i] - otherTool->f64ForceSensorCoord[i]) > TOLERANCE)
                return false;
        }
        return true;
    }
} ForceCtrlCalibItem;

// 16组力控标定数据
typedef struct _ForceCtrlCalibData_
{
    _ForceCtrlCalibData_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; i++)
        {
            stForceCtrlCalibDataArray[i].Initialize();
        }
    }

    _ForceCtrlCalibData_ &operator=(const _ForceCtrlCalibData_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; i++)
        {
            this->stForceCtrlCalibDataArray[i] = other.stForceCtrlCalibDataArray[i];
        }
        return (*this);
    }
    ForceCtrlCalibItem stForceCtrlCalibDataArray[FORCE_CTRL_CAILB_DATA_MAX_NUM];  // 16组力控标定数据

} ForceCtrlCalibData;

typedef struct _SENSOR_CHANNEL_PARA_
{
    _SENSOR_CHANNEL_PARA_()
    {
        Initialize();
    }

    void Initialize()
    {
        u16SlaveIndex = 0;
        i64PdoIndex = 0;
        i64PdoSubIndex = 0;
        i64OffsetAddr = 0;
        i64Value = 0;
    }

    _SENSOR_CHANNEL_PARA_ &operator=(const _SENSOR_CHANNEL_PARA_ &other)
    {
        this->u16SlaveIndex = other.u16SlaveIndex;
        this->i64PdoIndex = other.i64PdoIndex;
        this->i64PdoSubIndex = other.i64PdoSubIndex;
        this->i64OffsetAddr = other.i64OffsetAddr;
        this->i64Value = other.i64Value;
        return (*this);
    }

    bool Compare(_SENSOR_CHANNEL_PARA_ *other)
    {
        if (u16SlaveIndex != other->u16SlaveIndex || i64PdoIndex != other->i64PdoIndex
            || i64PdoSubIndex != other->i64PdoSubIndex || i64OffsetAddr != other->i64OffsetAddr
            || i64Value != other->i64Value)
            return false;
        return true;
    }

    int16u u16SlaveIndex;    // 每个通道均需要填写从站索引
    int64_t i64PdoIndex;     // 对应pdo的索引
    int64_t i64PdoSubIndex;  // 对应pdo的子索引
    int64_t i64OffsetAddr;   // 映射偏移地址
    int64_t i64Value;        // 输出值
} SensorChannelPara;

typedef struct _FORCE_SENSOR_INPUT_SIGNAL_
{
    _FORCE_SENSOR_INPUT_SIGNAL_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
            stForceData->Initialize();
        for (int i = 0; i < FORCE_CTRL_INPUT_RESERVE; ++i)
            stReserveData->Initialize();
    }

    _FORCE_SENSOR_INPUT_SIGNAL_ &operator=(const _FORCE_SENSOR_INPUT_SIGNAL_ &other)
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
            stForceData[i] = other.stForceData[i];
        for (int i = 0; i < FORCE_CTRL_INPUT_RESERVE; ++i)
            stReserveData[i] = other.stReserveData[i];
        return (*this);
    }

    bool Compare(_FORCE_SENSOR_INPUT_SIGNAL_ *other)
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            if (!stForceData[i].Compare(&other->stForceData[i]))
                return false;
        }
        for (int i = 0; i < FORCE_CTRL_INPUT_RESERVE; i++)
        {
            if (!stReserveData[i].Compare(&other->stReserveData[i]))
                return false;
        }
        return true;
    }

    SensorChannelPara stForceData[DIR_SIX_DEMIS_NUM];           // 多维通道参数:力数据FX~MZ
    SensorChannelPara stReserveData[FORCE_CTRL_INPUT_RESERVE];  // 输入预留
} ForceSensorInputSignal;

typedef struct _FORCE_SENSOR_OUTPUT_SIGNAL_
{
    _FORCE_SENSOR_OUTPUT_SIGNAL_()
    {
        Initialize();
    }

    void Initialize()
    {
        stZeroReset.Initialize();
        for (int i = 0; i < FORCE_CTRL_OUTPUT_RESERVE; ++i)
            stReserveData->Initialize();
    }

    _FORCE_SENSOR_OUTPUT_SIGNAL_ &operator=(const _FORCE_SENSOR_OUTPUT_SIGNAL_ &other)
    {
        stZeroReset = other.stZeroReset;
        for (int i = 0; i < FORCE_CTRL_OUTPUT_RESERVE; ++i)
            stReserveData[i] = other.stReserveData[i];
        return (*this);
    }

    bool Compare(_FORCE_SENSOR_OUTPUT_SIGNAL_ *other)
    {
        if (!stZeroReset.Compare(&other->stZeroReset))
            return false;
        for (int i = 0; i < FORCE_CTRL_OUTPUT_RESERVE; i++)
        {
            if (!stReserveData[i].Compare(&other->stReserveData[i]))
                return false;
        }
        return true;
    }

    SensorChannelPara stZeroReset;                               // 清零
    SensorChannelPara stReserveData[FORCE_CTRL_OUTPUT_RESERVE];  // 输出预留
} ForceSensorOutputSignal;

// 一组传感器参数
typedef struct _FORCE_CTRL_SENSOR_PARA_
{
    _FORCE_CTRL_SENSOR_PARA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16SensorType = 0;
        i16ForceDirection = 0;
        i16SlaveType = 0;
        i16DataType = 0;
        f64DataCoefficient = 1.0;
        stForceSensorInput.Initialize();
        stForceSensorOutPut.Initialize();
    }

    _FORCE_CTRL_SENSOR_PARA_ &operator=(const _FORCE_CTRL_SENSOR_PARA_ &other)
    {
        i16SensorType = other.i16SensorType;
        i16ForceDirection = other.i16ForceDirection;
        i16SlaveType = other.i16SlaveType;
        i16DataType = other.i16DataType;
        f64DataCoefficient = other.f64DataCoefficient;
        stForceSensorInput = other.stForceSensorInput;
        stForceSensorOutPut = other.stForceSensorOutPut;
        return (*this);
    }

    bool Compare(_FORCE_CTRL_SENSOR_PARA_ *other)
    {
        if (i16SensorType != other->i16SensorType
            || i16ForceDirection != other->i16ForceDirection
            || i16SlaveType != other->i16SlaveType
            || i16DataType != other->i16DataType
            || f64DataCoefficient != other->f64DataCoefficient
            || !stForceSensorInput.Compare(&other->stForceSensorInput)
            || !stForceSensorOutPut.Compare(&other->stForceSensorOutPut))
        {
            return false;
        }
        return true;
    }

    int16s i16SensorType;                         // 表示是1维力传感器,6维力传感器
    int16s i16ForceDirection;                     // 表示力方向0:表示全部方向,1-6:表示 X / Y / Z / A / B / C
    int16s i16SlaveType;                          // 从站类型0:标准类型(特制的传感器从站) ;非0:非标准 模拟量模块, 不具备清0
    int16s i16DataType;                           // 数据类型 : 0 - 整型; 1 - float ;2 - double
    double f64DataCoefficient;                    // 数据转换系数默认值 : 1.0
    ForceSensorInputSignal stForceSensorInput;    // 输入参数
    ForceSensorOutputSignal stForceSensorOutPut;  // 输出参数
} ForceCtrlSensorPara;

// 4组传感器参数
typedef struct _FC_SENSOR_PARA_ARR_
{
    _FC_SENSOR_PARA_ARR_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_SENSOR_NUM; ++i)
        {
            u8ForceCtrlswitchFlag[i] = 0;
            stFCSensorParaArr[i].Initialize();
        }
    }

    _FC_SENSOR_PARA_ARR_ &operator=(const _FC_SENSOR_PARA_ARR_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_SENSOR_NUM; ++i)
        {
            u8ForceCtrlswitchFlag[i] = other.u8ForceCtrlswitchFlag[i];
            stFCSensorParaArr[i] = other.stFCSensorParaArr[i];
        }
        return (*this);
    }

    int8u u8ForceCtrlswitchFlag[FORCE_CTRL_SENSOR_NUM];  // 4组传感器开关  0-关闭;1-打开
    ForceCtrlSensorPara stFCSensorParaArr[FORCE_CTRL_SENSOR_NUM];
} FCSensorParaArr;

// 力控坐标系
typedef struct _FC_COORDINATE_PARA_
{
    _FC_COORDINATE_PARA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16ToolNo = 0;
        i16CoordinateType = 0;
        i16CoordinateNo = 0;
    }

    _FC_COORDINATE_PARA_ &operator=(const _FC_COORDINATE_PARA_ &other)
    {
        i16ToolNo = other.i16ToolNo;
        i16CoordinateType = other.i16CoordinateType;
        i16CoordinateNo = other.i16CoordinateNo;
        return (*this);
    }

    bool Compare(_FC_COORDINATE_PARA_ *other)
    {
        if (i16ToolNo != other->i16ToolNo || i16CoordinateType != other->i16CoordinateType
            || i16CoordinateNo != other->i16CoordinateNo)
            return false;
        return true;
    }

    int16s i16ToolNo;          // 参考坐标系编号 0-15
    int16s i16CoordinateType;  // 参考坐标系类型 0：工具；1：工件
    int16s i16CoordinateNo;    // 参考坐标系编号 0-15
} FCCoordinatePara;

typedef struct _FC_COORDINATE_PARA_ARR_
{
    _FC_COORDINATE_PARA_ARR_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCCoordinateParaArr[i].Initialize();
        }
    }

    _FC_COORDINATE_PARA_ARR_ &operator=(const _FC_COORDINATE_PARA_ARR_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCCoordinateParaArr[i] = other.stFCCoordinateParaArr[i];
        }
        return (*this);
    }

    FCCoordinatePara stFCCoordinateParaArr[FORCE_CTRL_CAILB_DATA_MAX_NUM];  // 十六组坐标系参数
} FCCoordinateParaArr;

/// <summary>
/// 力控配置参数
/// </summary>
typedef struct _ForceCtrlConfigPara_
{
    _ForceCtrlConfigPara_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16ForceSensorNum = 0;
        i16ForceCoordinateIndex = 0;
        memset(i16ForceMode, 0, sizeof(i16ForceMode));
        memset(f32ForceDeadZone, 0, sizeof(f32ForceDeadZone));
    }

    _ForceCtrlConfigPara_ &operator=(const _ForceCtrlConfigPara_ &other)
    {
        i16ForceSensorNum = other.i16ForceSensorNum;
        i16ForceCoordinateIndex = other.i16ForceCoordinateIndex;
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            i16ForceMode[i] = other.i16ForceMode[i];
            f32ForceDeadZone[i] = other.f32ForceDeadZone[i];
        }
        return (*this);
    }

    bool Compare(_ForceCtrlConfigPara_ *other)
    {
        if (i16ForceSensorNum != other->i16ForceSensorNum
            || i16ForceCoordinateIndex != other->i16ForceCoordinateIndex)
            return false;
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            if (i16ForceMode[i] != other->i16ForceMode[i])
                return false;
            if (abs(f32ForceDeadZone[i] - other->f32ForceDeadZone[i]) > TOLERANCE)
                return false;
        }
        return true;
    }

    int16s i16ForceSensorNum;                   // 力控传感器编号
    int16s i16ForceCoordinateIndex;             // 坐标系编号 范围：0-15
    int16s i16ForceMode[DIR_SIX_DEMIS_NUM];     // 控制模式 位置模式(0)、力控模式(1)
    float f32ForceDeadZone[DIR_SIX_DEMIS_NUM];  // 力控接触力死区
} ForceCtrlConfigPara;

typedef struct _ForceCtrlConfigParaArr_
{
    _ForceCtrlConfigParaArr_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCConfigParaArr[i].Initialize();
        }
    }

    _ForceCtrlConfigParaArr_ &operator=(const _ForceCtrlConfigParaArr_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCConfigParaArr[i] = other.stFCConfigParaArr[i];
        }
        return (*this);
    }

    ForceCtrlConfigPara stFCConfigParaArr[FORCE_CTRL_CAILB_DATA_MAX_NUM];  // 十六组
} ForceCtrlConfigParaArr;

/// <summary>
/// 力控控制参数
/// </summary>
typedef struct _ForceCtrlMovePara_
{
    _ForceCtrlMovePara_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f32ForceCtrVelMaxLimit[i] = 10;
            f32TargetForce[i] = 0;
            f32Mc[i] = 20;
            f32Bc[i] = 4000;
            f32Kc[i] = 0;
            f32AdaptiveRatio[i] = 0;
        }
        for (int i = 3; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            f32Mc[i] = 2;
            f32Bc[i] = (float)28.6479;
        }
        i16QuickTrigIndex = -1;
        i16SwitchParaIndex = -1;
    }

    _ForceCtrlMovePara_ &operator=(const _ForceCtrlMovePara_ &other)
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            f32ForceCtrVelMaxLimit[i] = other.f32ForceCtrVelMaxLimit[i];
            f32TargetForce[i] = other.f32TargetForce[i];
            f32Mc[i] = other.f32Mc[i];
            f32Bc[i] = other.f32Bc[i];
            f32Kc[i] = other.f32Kc[i];
            f32AdaptiveRatio[i] = other.f32AdaptiveRatio[i];
        }
        i16QuickTrigIndex = other.i16QuickTrigIndex;
        i16SwitchParaIndex = other.i16SwitchParaIndex;
        return (*this);
    }

    bool Compare(_ForceCtrlMovePara_ *other)
    {
        if (i16QuickTrigIndex != other->i16QuickTrigIndex
            || i16SwitchParaIndex != other->i16SwitchParaIndex)
            return false;
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            if (abs(f32ForceCtrVelMaxLimit[i] - other->f32ForceCtrVelMaxLimit[i]) > TOLERANCE
                || abs(f32TargetForce[i] - other->f32TargetForce[i]) > TOLERANCE
                || abs(f32Mc[i] - other->f32Mc[i]) >TOLERANCE
                || abs(f32Bc[i] - other->f32Bc[i]) >TOLERANCE
                || abs(f32Kc[i] - other->f32Kc[i]) >TOLERANCE
                || abs(f32AdaptiveRatio[i] - other->f32AdaptiveRatio[i]) >TOLERANCE)
                return false;
        }
        return true;
    }

    float f32ForceCtrVelMaxLimit[DIR_SIX_DEMIS_NUM];  // 力控最大速度
    float f32TargetForce[DIR_SIX_DEMIS_NUM];          // 目标力
    float f32Mc[DIR_SIX_DEMIS_NUM];                   // 笛卡尔惯性系数
    float f32Bc[DIR_SIX_DEMIS_NUM];                   // 笛卡尔阻尼系数
    float f32Kc[DIR_SIX_DEMIS_NUM];                   // 笛卡尔刚度系数
    float f32AdaptiveRatio[DIR_SIX_DEMIS_NUM];        // 自适应比率
    int16s i16QuickTrigIndex;                         // 快速触发器编号
    int16s i16SwitchParaIndex;                        // 切换参数编号
} ForceCtrlMovePara;

typedef struct _ForceCtrlMoveParaArr_
{
    _ForceCtrlMoveParaArr_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCMoveParaArr[i].Initialize();
        }
    }

    _ForceCtrlMoveParaArr_ &operator=(const _ForceCtrlMoveParaArr_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCMoveParaArr[i] = other.stFCMoveParaArr[i];
        }
        return (*this);
    }

    ForceCtrlMovePara stFCMoveParaArr[FORCE_CTRL_CAILB_DATA_MAX_NUM];  // 十六组
} ForceCtrlMoveParaArr;

/// <summary>
/// 力控限制参数
/// </summary>
typedef struct _ForceCtrlLimitPara_
{
    _ForceCtrlLimitPara_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; i++)
        {
            f32FCMaxLimit[i] = 50;
            f32FCDisMaxLimit[i] = 50;
            f32FCAccMaxLimit[i] = 1000;
            f32ForceCtrlJointLimit[i] = 100;
            f32ForceCtrlJointVelLimit[i] = 400;
            f32ForceCtrlJointAccLimit[i] = 400;
            f32SensorForceLimit[i] = 50;
        }
        for (int i = 3; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            f32FCMaxLimit[i] = 10;
            f32SensorForceLimit[i] = 10;
        }
    }

    _ForceCtrlLimitPara_ &operator=(const _ForceCtrlLimitPara_ &other)
    {
        for (int i = 0; i < DIR_SIX_DEMIS_NUM; ++i)
        {
            f32FCMaxLimit[i] = other.f32FCMaxLimit[i];
            f32FCDisMaxLimit[i] = other.f32FCDisMaxLimit[i];
            f32FCAccMaxLimit[i] = other.f32FCAccMaxLimit[i];
            f32ForceCtrlJointLimit[i] = other.f32ForceCtrlJointLimit[i];
            f32ForceCtrlJointVelLimit[i] = other.f32ForceCtrlJointVelLimit[i];
            f32ForceCtrlJointAccLimit[i] = other.f32ForceCtrlJointAccLimit[i];
            f32SensorForceLimit[i] = other.f32SensorForceLimit[i];
        }
        return (*this);
    }

    float f32FCMaxLimit[DIR_SIX_DEMIS_NUM];              // 力控接触力上限
    float f32FCDisMaxLimit[DIR_SIX_DEMIS_NUM];           // 力控运动距离上限
    float f32FCAccMaxLimit[DIR_SIX_DEMIS_NUM];           // 力控加速度上限
    float f32ForceCtrlJointLimit[DIR_SIX_DEMIS_NUM];     // 关节限制
    float f32ForceCtrlJointVelLimit[DIR_SIX_DEMIS_NUM];  // 关节速度限制
    float f32ForceCtrlJointAccLimit[DIR_SIX_DEMIS_NUM];  // 关节加速度限制
    float f32SensorForceLimit[DIR_SIX_DEMIS_NUM];        // 传感器力限制
} ForceCtrlLimitPara;

typedef struct _ForceCtrlLimitParaArr_
{
    _ForceCtrlLimitParaArr_()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCLimitParaArr[i].Initialize();
        }
    }

    _ForceCtrlLimitParaArr_ &operator=(const _ForceCtrlLimitParaArr_ &other)
    {
        for (int i = 0; i < FORCE_CTRL_CAILB_DATA_MAX_NUM; ++i)
        {
            stFCLimitParaArr[i] = other.stFCLimitParaArr[i];
        }
        return (*this);
    }

    ForceCtrlLimitPara stFCLimitParaArr[FORCE_CTRL_CAILB_DATA_MAX_NUM];  // 十六组
} ForceCtrlLimitParaArr;

#pragma pack(pop)

#define FORCE_CTRL_SYSTEMTIME_LEN 22  // 力控反馈数据中系统时间字符串的长度
/// <summary>
/// 力控反馈数据
/// </summary>
#pragma pack(1)
typedef struct _ForceCtrlData_
{
  _ForceCtrlData_()
  {
    memset(&cSysTime[0], 0, FORCE_CTRL_SYSTEMTIME_LEN);
    f32Time = 0;
    memset(f32Force, 0, sizeof(f32Force));
    memset(f32PlanPos, 0, sizeof(f32PlanPos));
    memset(f32PlanPos, 0, sizeof(f32PlanPos));
    memset(f32FeedBackPos, 0, sizeof(f32FeedBackPos));
  }

  char cSysTime[FORCE_CTRL_SYSTEMTIME_LEN];  // 系统时间
  float f32Time;                             // 采集时间or第几次采集
  float f32Force[DIR_SIX_DEMIS_NUM];         // X/Y/Z方向的力，A/B/C方向的力矩
  float f32PlanPos[DIR_SIX_DEMIS_NUM];       // 机器人规划的X/Y/Z/A/B/C
  float f32FeedBackPos[DIR_SIX_DEMIS_NUM];   // 机器人反馈的X/Y/Z/A/B/C
} ForceCtrlData;
#pragma pack()

#define FORCE_CTRL_DATA_LABEL_LEN        20  // 力控功能单个数据别名最大长度
#define FORCE_CTRL_LOGDATA_COLUMN_LEN    20  // 力控日志数据列长度
#define FORCE_CTRL_LOGDATA_COLUMN_EXTLEN 10  // 力控日志数据列扩展长度

/// <summary>
/// 自定义力控日志格式
/// </summary>
#pragma pack(1)
typedef struct _ForceCtrlLogFormat_
{
  _ForceCtrlLogFormat_()
  {
    Initialize();
  }

  void Initialize()
  {
    forceFactor = 1.0;
    momentFactor = 1.0;
    nFlag = 0;
    nForceUnit = 0;
    nTimeUnit = 0;
    nColNum = FORCE_CTRL_LOGDATA_COLUMN_LEN + FORCE_CTRL_LOGDATA_COLUMN_EXTLEN;

    for (size_t i = 0; i < FORCE_CTRL_LOGDATA_COLUMN_LEN; i++)
    {
      nId[i] = i;
      for (size_t k = 0; k < FORCE_CTRL_DATA_LABEL_LEN; k++)
      {
        cLabelName[i][k] = 0;
      }
    }

    // 扩展列，扩10列
    for (size_t i = 0; i < FORCE_CTRL_LOGDATA_COLUMN_EXTLEN; i++)
    {
      nIdExt[i] = i;
      for (size_t k = 0; k < FORCE_CTRL_DATA_LABEL_LEN; k++)
      {
        cLabelNameExt[i][k] = 0;
      }
    }
  }

  float forceFactor;                                                          // 力系数
  float momentFactor;                                                         // 力矩系数
  int16s nFlag;                                                               // 是否有文件头，0-有，1-无
  int16s nForceUnit;                                                          // 力单位，0-N，1-kg
  int16s nTimeUnit;                                                           // 时间单位，0-ms，1-s
  int16s nColNum;                                                             // 列的数量
  int16s nId[FORCE_CTRL_LOGDATA_COLUMN_LEN];                                  // 列对应参数的ID的组合，从左到右
  char cLabelName[FORCE_CTRL_LOGDATA_COLUMN_LEN][FORCE_CTRL_DATA_LABEL_LEN];  // 列对应参数的别名的组合，从左到右

  int16s nIdExt[FORCE_CTRL_LOGDATA_COLUMN_EXTLEN];                                  // 扩展列对应参数的ID的组合，从左到右
  char cLabelNameExt[FORCE_CTRL_LOGDATA_COLUMN_EXTLEN][FORCE_CTRL_DATA_LABEL_LEN];  // 扩展列对应参数的别名的组合，从左到右
} ForceCtrlLogFormat;
#pragma pack()

#pragma endregion
