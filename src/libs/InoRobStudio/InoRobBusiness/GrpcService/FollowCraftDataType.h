#pragma once

#include <string>
#include <vector>
#include <map>
#include "DataTypeDef.h"
#include "GlobalDataTypes.h"  //TODO后续删除

using namespace InoRobUtil;
using namespace std;
using std::string;
using std::vector;
using std::map;

#pragma region 跟随工艺

#define CRAFT_FOLLOW_MAX_CATCH_OBJ_COUNT  (16)  // 最大工件数
#define CRAFT_FOLLOW_MAX_BELT_COUNT       (16)  // 最大可配置传送带数
#define CRAFT_FOLLOW_ENCODER_POS_COUNT    (2)   // 编码器位置数目
#define CRAFT_FOLLOW_CALIB_POINT_COUNT    (9)   // 标定点数目
#define CRAFT_FOLLOW_CALIB_ERR_COUNT      (8)   // 标定误差数量
#define CRAFT_FOLLOW_CALIB_MATRIX_SIZE    (16)  // 标定矩阵大小
#define INVALID_BELTINDEX                 (-1)
#define INVALID_BELTTYPE                  (-1)
#define OTM_ALLOCATION_INFO_NUM           (17)  // 一拖多分配比信息数量
#define FOLLOW_CRAFT_OBJ_MAXNUM           (50)  // 视觉一拖多监控最大物体数量
#define OTM_MEMBER_NUM                    (5)   // 一拖多功能主从机器人总数
#define OTM_IP_LENGTH                     (16)  // 一拖多功能IP长度
#define FOLLOW_CRAFT_OBJ_TEULER_POS_LEN   (6)   // 物体传送带坐标数组长度
#define FOLLOW_CRAFT_OBJ_TEULER_PIXEL_LEN (3)   // 物体像素坐标数组长度
#define OTM_SLAVE_VISION_DATA_NUM         (50)  // 监控页面从控单次接收最大数据量

enum eSigType
{
    SIGTYPE_UPEDGE = 0,
    SIGTYPE_DOWNEDGE = 1
};

enum class eBeltType : int
{
    BELTT_LINEAR = 0,
    BELTT_DISC = 1
};

// 传感器标定点
struct SensorCaliPos
{
    double X;
    double Y;
    double A;

    SensorCaliPos()
    {
        Initialize();
    }

    void Initialize()
    {
        X = 0.0;
        Y = 0.0;
        A = 0.0;
    }

    void From(const SensorCaliPos &other)
    {
        X = other.X;
        Y = other.Y;
        A = other.A;
    }

    bool Compare(const SensorCaliPos &other)
    {
        if (X != other.X || Y != other.Y || A != other.A)
        {
            return false;
        }
        return true;
    }
};

// 传感器参数
struct SensorCfg
{
    short TriggerDiId;        // 传感器信号输入DI的Id
    short TriggerEdge;        // 信号类型,上升沿、下降沿
    short ObjId;              // 工件类型编号
    double RepRejectDist;     // 重复剔除距离
    SensorCaliPos TeachPos;   // 示教位置类
    SensorCaliPos DetectPos;  // 检测位置类

    SensorCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        TriggerDiId = 0;
        TriggerEdge = 0;
        ObjId = 0;
        RepRejectDist = 0.0;
        TeachPos.Initialize();
        DetectPos.Initialize();
    }

    void From(const SensorCfg &other)
    {
        TriggerDiId = other.TriggerDiId;
        TriggerEdge = other.TriggerEdge;
        ObjId = other.ObjId;
        RepRejectDist = other.RepRejectDist;
        TeachPos.From(other.TeachPos);
        DetectPos.From(other.DetectPos);
    }

    bool Compare(const SensorCfg &other)
    {
        if (TriggerDiId != other.TriggerDiId || TriggerEdge != other.TriggerEdge
            || ObjId != other.ObjId || RepRejectDist != other.RepRejectDist)
        {
            return false;
        }
        if (!TeachPos.Compare(other.TeachPos))
        {
            return false;
        }
        if (!DetectPos.Compare(other.DetectPos))
        {
            return false;
        }
        return true;
    }
};

// 标定点类
struct CaliPoint
{
    double X;
    double Y;

    CaliPoint()
    {
        Initialize();
    }

    void Initialize()
    {
        X = 0.0;
        Y = 0.0;
    }

    void From(const CaliPoint &other)
    {
        X = other.X;
        Y = other.Y;
    }
    bool Compare(const CaliPoint &other)
    {
        if (X != other.X || Y != other.Y)
        {
            return false;
        }
        return true;
    }
};

// 相机连接参数
struct VisionConnectCfg
{
    char IPAddr[16];     // ip地址
    int PortNum;         // 端口号
    char Separator[8];   // 分隔符
    char Terminator[8];  // 终止符
    char HeadTcp[8];     // 帧头
    int SendRcvFlag;     // 接收、发送标志（1-发送；2-接收）
    int TcpState;        // tcp连接状态（0-未连接；1-已连接）
    char Data[256];      // 接收或发送数据

    VisionConnectCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(&IPAddr[0], 0, 16 * sizeof(char));
        PortNum = 0;
        memset(&Separator[0], 0, 8 * sizeof(char));
        memset(&Terminator[0], 0, 8 * sizeof(char));
        memset(&HeadTcp[0], 0, 8 * sizeof(char));
        SendRcvFlag = 0;
        TcpState = 0;
        memset(&Data[0], 0, 256 * sizeof(char));
    }

    void From(const VisionConnectCfg &other)
    {
        memcpy(&IPAddr[0], &other.IPAddr[0], 16 * sizeof(char));
        PortNum = other.PortNum;
        memcpy(&Separator[0], &other.Separator[0], 8 * sizeof(char));
        memcpy(&Terminator[0], &other.Terminator[0], 8 * sizeof(char));
        memcpy(&HeadTcp[0], &other.HeadTcp[0], 8 * sizeof(char));
        SendRcvFlag = other.SendRcvFlag;
        TcpState = other.TcpState;
        memcpy(&Data[0], &other.Data[0], 256 * sizeof(char));
    }
    bool Compare(const VisionConnectCfg &other)
    {
        if (PortNum != other.PortNum || SendRcvFlag != other.SendRcvFlag
            || TcpState != other.TcpState)
        {
            return false;
        }
        if (strcmp(IPAddr, other.IPAddr) != 0
            || strcmp(Separator, other.Separator) != 0
            || strcmp(Terminator, other.Terminator) != 0
            || strcmp(HeadTcp, other.HeadTcp) != 0
            || strcmp(Data, other.Data) != 0)
        {
            return false;
        }
        return true;
    }
};

// 相机基本参数
struct CameraBasicCfg
{
    short TriggerDoId;     // 触发相机的DO的Id -1表示null
    double ShotDist;       // 拍照间距
    double DelayDist;      // 直线型：延时距离，圆盘型：延时角度
    short TriggerEdge;     // 触发沿，0-上升沿；1-下降沿
    short DataType;        // 数据类型，0-机器人；1-像素
    double RepDetectDist;  // 重复检测判定距离
    double IOHoldTime;     // IO电平保持时间
    // short VisCoorId;  //视觉坐标系Id

    CameraBasicCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        TriggerDoId = -1;
        ShotDist = 0.0;
        DelayDist = 0.0;
        TriggerEdge = 0;
        DataType = 0;
        RepDetectDist = 0.0;
        IOHoldTime = 20.0;
        // VisCoorId = 0;
    }

    void From(const CameraBasicCfg &other)
    {
        TriggerDoId = other.TriggerDoId;
        ShotDist = other.ShotDist;
        DelayDist = other.DelayDist;
        TriggerEdge = other.TriggerEdge;
        DataType = other.DataType;
        RepDetectDist = other.RepDetectDist;
        IOHoldTime = other.IOHoldTime;
        // VisCoorId = other.VisCoorId;
    }

    bool Compare(const CameraBasicCfg &other)
    {
        if (TriggerDoId != other.TriggerDoId || ShotDist != other.ShotDist
            || DelayDist != other.DelayDist || TriggerEdge != other.TriggerEdge
            || DataType != other.DataType || RepDetectDist != other.RepDetectDist
            || IOHoldTime != other.IOHoldTime)
        {
            return false;
        }
        return true;
    }
};

// 视觉参数
struct VisionCfg
{
    CameraBasicCfg CameraBasicPara;                  // 相机基本参数
    vector<CaliPoint> VisionPoints;                  // 视觉像素点
    VisionConnectCfg VisionConnectPara;              // 视觉参数配置
    int64s BeltPosForVision;                         // 相机取点时传送带的位置
    vector<CaliPoint> RobotPoints;                   // 机器人示教点
    int64s BeltPosForTeach;                          // 机器人取点时传送带的位置
    bool HasOffsetForTeach;                          // 示教时传送带是否有偏移
    double BeltPosOffsetDisForTeach;                 // 示教时传送带的偏移大小
    double CaliMat[CRAFT_FOLLOW_CALIB_MATRIX_SIZE];  // 标定矩阵（大小为16）
    double CaliErr[CRAFT_FOLLOW_CALIB_ERR_COUNT];    // 标定误差（大小为8）

    VisionCfg()
    {
        CameraBasicPara.Initialize();
        for (size_t i = 0; i < CRAFT_FOLLOW_CALIB_POINT_COUNT; i++)
        {
            CaliPoint visionCalibPoint;
            CaliPoint robotCalibPoint;
            VisionPoints.push_back(visionCalibPoint);
            RobotPoints.push_back(robotCalibPoint);
        }
        VisionConnectPara.Initialize();
        BeltPosForVision = 0;
        BeltPosForTeach = 0;
        HasOffsetForTeach = false;
        BeltPosOffsetDisForTeach = 0.0;
        memset(&CaliMat[0], 0, CRAFT_FOLLOW_CALIB_MATRIX_SIZE * sizeof(double));
        memset(&CaliErr[0], 0, CRAFT_FOLLOW_CALIB_ERR_COUNT * sizeof(double));
    }

    void Initialize()
    {
        CameraBasicPara.Initialize();
        VisionConnectPara.Initialize();
        for (size_t i = 0; i < VisionPoints.size(); i++)
        {
            VisionPoints[i].Initialize();
            RobotPoints[i].Initialize();
        }
        BeltPosForVision = 0;
        BeltPosForTeach = 0;
        HasOffsetForTeach = false;
        BeltPosOffsetDisForTeach = 0.0;
        memset(&CaliMat[0], 0, CRAFT_FOLLOW_CALIB_MATRIX_SIZE * sizeof(double));
        memset(&CaliErr[0], 0, CRAFT_FOLLOW_CALIB_ERR_COUNT * sizeof(double));
    }

    void From(const VisionCfg &other)
    {
        CameraBasicPara.From(other.CameraBasicPara);
        VisionConnectPara.From(other.VisionConnectPara);
        VisionPoints.assign(other.VisionPoints.begin(), other.VisionPoints.end());
        RobotPoints.assign(other.RobotPoints.begin(), other.RobotPoints.end());
        BeltPosForVision = other.BeltPosForVision;
        BeltPosForTeach = other.BeltPosForTeach;
        HasOffsetForTeach = other.HasOffsetForTeach;
        BeltPosOffsetDisForTeach = other.BeltPosOffsetDisForTeach;
        memcpy(&CaliMat[0], &other.CaliMat[0], CRAFT_FOLLOW_CALIB_MATRIX_SIZE * sizeof(double));
        memcpy(&CaliErr[0], &other.CaliErr[0], CRAFT_FOLLOW_CALIB_ERR_COUNT * sizeof(double));
    }

    bool Compare(const VisionCfg &other)
    {
        if (!CameraBasicPara.Compare(other.CameraBasicPara))
        {
            return false;
        }
        if (!VisionConnectPara.Compare(other.VisionConnectPara))
        {
            return false;
        }
        for (size_t i = 0; i < std::min(VisionPoints.size(), other.VisionPoints.size()); i++)
        {
            if (!VisionPoints[i].Compare(other.VisionPoints[i]))
            {
                return false;
            }
        }
        for (size_t i = 0; i < std::min(RobotPoints.size(), other.RobotPoints.size()); i++)
        {
            if (!RobotPoints[i].Compare(other.RobotPoints[i]))
            {
                return false;
            }
        }
        if (BeltPosForVision != other.BeltPosForVision || BeltPosForTeach != other.BeltPosForTeach
            || HasOffsetForTeach != other.HasOffsetForTeach
            || BeltPosOffsetDisForTeach != other.BeltPosOffsetDisForTeach)
        {
            return false;
        }
        for (int i = 0; i < CRAFT_FOLLOW_CALIB_MATRIX_SIZE; i++)
        {
            if (CaliMat[i] != other.CaliMat[i])
            {
                return false;
            }
        }
        for (int i = 0; i < CRAFT_FOLLOW_CALIB_ERR_COUNT; i++)
        {
            if (CaliErr[i] != other.CaliErr[i])
            {
                return false;
            }
        }
        return true;
    }
};

// 检测参数
struct DetectCfg
{
    VisionCfg VisionPara;  // 视觉参数
    SensorCfg SensorPara;  // 传感器参数

    DetectCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        VisionPara.Initialize();
        SensorPara.Initialize();
    }

    void From(const DetectCfg &other)
    {
        VisionPara.From(other.VisionPara);
        SensorPara.From(other.SensorPara);
    }

    bool Compare(const DetectCfg &other)
    {
        if (!VisionPara.Compare(other.VisionPara))
        {
            return false;
        }
        if (!SensorPara.Compare(other.SensorPara))
        {
            return false;
        }
        return true;
    }
};

// 某一工件类型下，各机器人的分配比
struct AllocationINF
{
    int8u u8Rate[OTM_MEMBER_NUM];  //[0]主控机器人的分配比,[2]~[5]从控机器人的分配比

    AllocationINF()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < OTM_MEMBER_NUM; ++i)
        {
            u8Rate[i] = 0;
        }
    }

    void From(const AllocationINF &other)
    {
        for (int i = 0; i < OTM_MEMBER_NUM; ++i)
        {
            u8Rate[i] = other.u8Rate[i];
        }
    }

    bool Compare(const AllocationINF &other)
    {
        for (int i = 0; i < OTM_MEMBER_NUM; ++i)
        {
            if (u8Rate[i] != other.u8Rate[i])
            {
                return false;
            }
        }
        return true;
    }
};

enum VisionOTMMutex0
{
    VOTM_AND_MECH_UNIT_ALL_OFF,  // 0-均未开启
    VOTM_AND_MECH_UNIT_MECH_ON,  // 1-已配置机械单元
    VOTM_AND_MECH_UNIT_VOTM_ON,  // 2-仅开启一拖多
    VOTM_AND_MECH_UNIT_ERR       // 3-异常
};

enum VisionOTMMutex1
{
    VOTMS_AND_ECAT_ALL_OFF,         // 0-均未开启
    VOTMS_AND_ECAT_ECAT_ON,         // 1-仅开启EtherCAT从站功能
    VOTMS_AND_ECAT_MASTER_ON,       // 2-仅开启主控
    VOTMS_AND_ECAT_SLAVE_ON,        // 3-仅开启从控
    VOTMS_AND_ECAT_ECAT_MASTER_ON,  // 4-开启EtherCAT从站和主控
    VOTMS_AND_ECAT_ERR              // 5-异常
};

// 视觉一拖多和其它功能的互斥结构体
struct VisionOTMFnMutex
{
    // u8Data[0]，针对一拖多和机械单元的互斥,0-均未开启 1-已配置机械单元 2-仅开启一拖多 3-异常
    // u8Data[1]，针对一拖多从控和EtherCAT从站功能的互斥 0-均未开启 1-仅开启EtherCAT从站功能 2-仅开启主控 3-仅开启从控 4-开启EtherCAT从站和主控 5-异常
    // u8Data[2], 未使用
    // u8Data[3], 未使用
    int8u u8Data[4];

    VisionOTMFnMutex()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(u8Data, 0, 4);
    }
};

// 主从相关参数
struct VisionOneToMoreCfg
{
    int8u u8State;                 // 一拖多功能使能开关, 0关闭, 1开启
    int8u u8DeviceNum;             // 主站设置连接数量,2~5
    int8u u8DeviceIndex;           // 设备索引值,1~5
    int8u u8DeviceType;            // 设备类型,1:主控 2:从控
    char MasterIP[OTM_IP_LENGTH];  // 从站保存主站的IP地址

    int8u u8AllocateState;                                 // 分配比使能,0关闭,1开启
    int8u u8WorkpieceType;                                 // 当前所使用的分配比号 0~16
    AllocationINF AllocationInf[OTM_ALLOCATION_INFO_NUM];  // 分配比信息,0-15单一类型,16通用类型

    VisionOneToMoreCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        u8State = 0;
        u8DeviceNum = 2;
        u8DeviceIndex = 1;
        u8DeviceType = 1;
        u8AllocateState = 0;
        u8WorkpieceType = 0;

        memset(MasterIP, 0, OTM_IP_LENGTH);

        for (int i = 0; i < OTM_ALLOCATION_INFO_NUM; i++)
        {
            AllocationInf[i].Initialize();
        }
    }

    void From(const VisionOneToMoreCfg &other)
    {
        u8State = other.u8State;
        u8DeviceNum = other.u8DeviceNum;
        u8DeviceIndex = other.u8DeviceIndex;
        u8DeviceType = other.u8DeviceType;
        u8AllocateState = other.u8AllocateState;
        u8WorkpieceType = other.u8WorkpieceType;

        memcpy(MasterIP, other.MasterIP, OTM_IP_LENGTH);

        for (int i = 0; i < OTM_ALLOCATION_INFO_NUM; i++)
        {
            AllocationInf[i].From(other.AllocationInf[i]);
        }
    }

    bool Compare(const VisionOneToMoreCfg &other)
    {
        if (u8State != other.u8State || u8DeviceNum != other.u8DeviceNum || u8DeviceIndex != other.u8DeviceIndex
            || u8DeviceType != other.u8DeviceType || u8AllocateState != other.u8AllocateState || u8WorkpieceType != other.u8WorkpieceType)
        {
            return false;
        }

        for (int i = 0; i < OTM_IP_LENGTH; ++i)
        {
            if (other.MasterIP[i] != MasterIP[i])
            {
                return false;
            }
        }

        for (int i = 0; i < OTM_ALLOCATION_INFO_NUM; i++)
        {
            bool bRet = AllocationInf[i].Compare(other.AllocationInf[i]);

            if (!bRet)
            {
                return false;
            }
        }

        return true;
    }
};

// 边界取点
struct BoundaryPoint
{
    double X;
    double Y;
    BoundaryPoint()
    {
        Initialize();
    }

    void Initialize()
    {
        X = 0.0;
        Y = 0.0;
    }

    void From(const BoundaryPoint &other)
    {
        X = other.X;
        Y = other.Y;
    }

    bool Compare(const BoundaryPoint &other)
    {
        if (X != other.X || Y != other.Y)
        {
            return false;
        }
        return true;
    }
};

// 圆弧边界结构体
struct ArcBoundaryCfg
{
    double dWorkUpBoundary;    // 工作上界
    double dWorkDownBoundary;  // 工作下界
    double dPickDownBoundary;  // 拾取下界
    double dStopLen;           // 停止距离
    double dRadius;            // 圆盘半径R
    int8s i8IsRLimit;          // R限位是否生效（1：是，0：否）

    ArcBoundaryCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        dWorkUpBoundary = 0.0;
        dWorkDownBoundary = 0.0;
        dPickDownBoundary = 0.0;
        dStopLen = 0.0;
        dRadius = 0.0;
        i8IsRLimit = 0;
    }

    void From(const ArcBoundaryCfg &other)
    {
        dWorkUpBoundary = other.dWorkUpBoundary;
        dWorkDownBoundary = other.dWorkDownBoundary;
        dPickDownBoundary = other.dPickDownBoundary;
        dStopLen = other.dStopLen;
        dRadius = other.dRadius;
        i8IsRLimit = other.i8IsRLimit;
    }

    bool Compare(const ArcBoundaryCfg &other)
    {
        if (dWorkUpBoundary != other.dWorkUpBoundary || dWorkDownBoundary != other.dWorkDownBoundary
            || dPickDownBoundary != other.dPickDownBoundary || dStopLen != other.dStopLen
            || dRadius != other.dRadius || i8IsRLimit != other.i8IsRLimit)
        {
            return false;
        }
        return true;
    }
};

// 倾斜上下界
struct TiltBoundaryCfg
{
    BoundaryPoint WorkUpBoundaryP1;
    BoundaryPoint WorkUpBoundaryP2;
    BoundaryPoint WorkDownBoundaryP3;
    BoundaryPoint WorkDownBoundaryP4;

    double PickDownBoundary;  // 拾取下界(拾取下界与工作下界在x方向的距离)
    double StopLen;           // 停止距离
    int8s i8IsYLimit;         // Y限位是否生效（1：是，0：否）

    TiltBoundaryCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        WorkUpBoundaryP1.Initialize();
        WorkUpBoundaryP2.Initialize();
        WorkDownBoundaryP3.Initialize();
        WorkDownBoundaryP4.Initialize();
        PickDownBoundary = 0.0;
        StopLen = 0.0;
        i8IsYLimit = 0;
    }

    void From(const TiltBoundaryCfg &other)
    {
        WorkUpBoundaryP1.From(other.WorkUpBoundaryP1);
        WorkUpBoundaryP2.From(other.WorkUpBoundaryP2);
        WorkDownBoundaryP3.From(other.WorkDownBoundaryP3);
        WorkDownBoundaryP4.From(other.WorkDownBoundaryP4);
        PickDownBoundary = other.PickDownBoundary;
        StopLen = other.StopLen;
        i8IsYLimit = other.i8IsYLimit;
    }
    bool Compare(const TiltBoundaryCfg &other)
    {
        if (!WorkUpBoundaryP1.Compare(other.WorkUpBoundaryP1))
        {
            return false;
        }
        if (!WorkUpBoundaryP2.Compare(other.WorkUpBoundaryP2))
        {
            return false;
        }
        if (!WorkDownBoundaryP3.Compare(other.WorkDownBoundaryP3))
        {
            return false;
        }
        if (!WorkDownBoundaryP4.Compare(other.WorkDownBoundaryP4))
        {
            return false;
        }
        if (PickDownBoundary != other.PickDownBoundary
            || StopLen != other.StopLen || i8IsYLimit != other.i8IsYLimit)
        {
            return false;
        }
        return true;
    }
};

// 普通上下界参数配置
struct OrdinaryBoundaryCfg
{
    double WorkUpBoundary;      // 工作上界
    double WorkDownBoundary;    // 工作下界
    double PickDownBoundary;    // 拾取下界（距离工作下界的距离）
    double StopLen;             // 停止距离
    double dWorkUpBoundaryY;    // 工作上界Y值
    double dWorkDownBoundaryY;  // 工作下界Y值
    int8s i8IsYLimit;           // Y限位是否生效（1：是，0：否）

    OrdinaryBoundaryCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        WorkUpBoundary = 0.0;
        WorkDownBoundary = 0.0;
        PickDownBoundary = 0.0;
        StopLen = 0.0;
        dWorkUpBoundaryY = 0.0;
        dWorkDownBoundaryY = 0.0;
        i8IsYLimit = 0;
    }

    void From(const OrdinaryBoundaryCfg &other)
    {
        WorkUpBoundary = other.WorkUpBoundary;
        WorkDownBoundary = other.WorkDownBoundary;
        PickDownBoundary = other.PickDownBoundary;
        StopLen = other.StopLen;
        dWorkUpBoundaryY = other.dWorkUpBoundaryY;
        dWorkDownBoundaryY = other.dWorkDownBoundaryY;
        i8IsYLimit = other.i8IsYLimit;
    }

    bool Compare(const OrdinaryBoundaryCfg &other)
    {
        if (WorkUpBoundary != other.WorkUpBoundary || WorkDownBoundary != other.WorkDownBoundary
            || PickDownBoundary != other.PickDownBoundary || StopLen != other.StopLen
            || dWorkUpBoundaryY != other.dWorkUpBoundaryY || dWorkDownBoundaryY != other.dWorkDownBoundaryY
            || i8IsYLimit != other.i8IsYLimit)
        {
            return false;
        }
        return true;
    }
};

// 传送带边界类
struct BoundaryCfg
{
    int BoundaryType;                          // 边界类型，0-普通上下界，1-倾斜上下界， 2-圆弧边界
    OrdinaryBoundaryCfg OrdinaryBoundaryPara;  // 普通上下界参数
    TiltBoundaryCfg TiltBoundaryPara;          // 倾斜上下界参数
    ArcBoundaryCfg arcBoundaryPara;            // 圆弧边界参数

    BoundaryCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        BoundaryType = 0;
        OrdinaryBoundaryPara.Initialize();
        TiltBoundaryPara.Initialize();
        arcBoundaryPara.Initialize();
    }

    void From(const BoundaryCfg &other)
    {
        BoundaryType = other.BoundaryType;
        OrdinaryBoundaryPara.From(other.OrdinaryBoundaryPara);
        TiltBoundaryPara.From(other.TiltBoundaryPara);
        arcBoundaryPara.From(other.arcBoundaryPara);
    }

    bool Compare(const BoundaryCfg &other)
    {
        if (BoundaryType != other.BoundaryType)
        {
            return false;
        }
        if (!OrdinaryBoundaryPara.Compare(other.OrdinaryBoundaryPara))
        {
            return false;
        }
        if (!TiltBoundaryPara.Compare(other.TiltBoundaryPara))
        {
            return false;
        }
        if (!arcBoundaryPara.Compare(other.arcBoundaryPara))
        {
            return false;
        }

        return true;
    }
};

// 工件高度类
struct ObjectCaliCfg
{
    vector<double> HightList;  // 工件高度校准数组

    ObjectCaliCfg()
    {
        for (int i = 0; i < CRAFT_FOLLOW_MAX_CATCH_OBJ_COUNT; i++)
        {
            HightList.push_back(0.0);
        }
    }

    void Initialize()
    {
        for (size_t i = 0; i < HightList.size(); i++)
        {
            HightList[i] = 0.0;
        }
    }

    void From(const ObjectCaliCfg &other)
    {
        // for (size_t i = 0; i < HightList.size(); i++)
        //{
        //     HightList[i] = other.HightList[i];
        // }
        HightList.assign(other.HightList.begin(), other.HightList.end());
    }

    bool Compare(const ObjectCaliCfg &other)
    {
        if (HightList != other.HightList)
        {
            return false;
        }
        return true;
    }
};

// 编码器取点类
struct EncoderPoint
{
    double RobotX;
    double RobotY;
    double RobotZ;
    int64s EncoderPos;

    EncoderPoint()
    {
        Initialize();
    }

    void From(const EncoderPoint &other)
    {
        RobotX = other.RobotX;
        RobotY = other.RobotY;
        RobotZ = other.RobotZ;
        EncoderPos = other.EncoderPos;
    }

    void Initialize()
    {
        RobotX = 0;
        RobotY = 0;
        RobotZ = 0;
        EncoderPos = 0;
    }

    bool Compare(const EncoderPoint &other)
    {
        if (RobotX != other.RobotX || RobotY != other.RobotY
            || RobotZ != other.RobotZ || EncoderPos != other.EncoderPos)
        {
            return false;
        }
        return true;
    }
};

// 编码器参数
struct EncoderCfg
{
    vector<EncoderPoint> Points;    // 编码器示教点
    double EncoderResolutionRatio;  // 编码器分辨率
    bool EncoderFilt;               // 编码器滤波

    EncoderCfg()
    {
        EncoderResolutionRatio = 0.0;
        EncoderFilt = true;
        for (int i = 0; i < CRAFT_FOLLOW_ENCODER_POS_COUNT; i++)
        {
            EncoderPoint point;
            Points.push_back(point);
        }
    }

    void Initialize()
    {
        EncoderResolutionRatio = 0.0;
        EncoderFilt = true;
        for (size_t i = 0; i < Points.size(); i++)
        {
            Points[i].Initialize();
        }
    }

    void From(const EncoderCfg &other)
    {
        EncoderResolutionRatio = other.EncoderResolutionRatio;
        EncoderFilt = other.EncoderFilt;
        // for (size_t i = 0; i < Points.size(); i++)
        //{
        //     Points[i].From(other.Points[i]);
        // }
        Points.assign(other.Points.begin(), other.Points.end());
    }

    bool Compare(const EncoderCfg &other)
    {
        for (size_t i = 0; i < std::min(Points.size(), other.Points.size()); i++)
        {
            if (!Points[i].Compare(other.Points[i]))
            {
                return false;
            }
        }

        if (EncoderResolutionRatio != other.EncoderResolutionRatio || EncoderFilt != other.EncoderFilt)
        {
            return false;
        }

        return true;
    }
};

// 传送带基本参数
struct BasicCfg
{
    short BeltType;    // 传送带类型，0-直线型；1-圆盘型
    short EncoderId;   // 编码器通道
    short WobjCoorId;  // 关联工件坐标系的Id
    short DetectType;  // 检测类型，0-视觉；1-传感器；2-视觉+传感器 3-指令+视觉

    BasicCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        BeltType = 0;
        EncoderId = 0;
        WobjCoorId = 0;
        DetectType = 0;
    }

    void From(const BasicCfg &other)
    {
        BeltType = other.BeltType;
        EncoderId = other.EncoderId;
        WobjCoorId = other.WobjCoorId;
        DetectType = other.DetectType;
    }

    bool Compare(const BasicCfg &other)
    {
        if (BeltType != other.BeltType || EncoderId != other.EncoderId
            || WobjCoorId != other.WobjCoorId || DetectType != other.DetectType)
        {
            return false;
        }
        return true;
    }
};

// 抓取补偿类
struct CapturePosCompensation
{
    double dX;
    double dY;
    double dZ;
    double dA;
    double dB;
    double dC;

    CapturePosCompensation()
    {
        Initialize();
    }

    void Initialize()
    {
        dX = 0.0;
        dY = 0.0;
        dZ = 0.0;
        dA = 0.0;
        dB = 0.0;
        dC = 0.0;
    }

    void From(const CapturePosCompensation &other)
    {
        dX = other.dX;
        dY = other.dY;
        dZ = other.dZ;
        dA = other.dA;
        dB = other.dB;
        dC = other.dC;
    }

    bool Compare(const CapturePosCompensation &other)
    {
        if (dX != other.dX || dY != other.dY
            || dZ != other.dZ || dA != other.dA
            || dB != other.dB || dC != other.dC)
        {
            return false;
        }
        return true;
    }
};

// 单条传送带参数
struct ConvCoorCfg
{
    int CoorId;  // 坐标系Id

    // 索引0对应的数据
    bool IsEnable;                          // 该坐标系是否被使能
    bool IsMonitor;                         // 该坐标系是否被监控
    CapturePosCompensation CapPosCompPara;  // 抓取补偿类

    // 索引1对应的数据
    BasicCfg BasicPara;  // 坐标系基本参数

    // 索引2对应数据
    EncoderCfg EncoderPara;  // 编码器参数

    // 索引3对应数据
    ObjectCaliCfg ObjCaliPara;  // 工件参数

    // 索引4对应数据
    BoundaryCfg BoundaryPara;  // 边界参数

    // 索引5对应数据 -- DetectCfg结构体中除了标定矩阵和标定误差的其他参数
    // 索引6对应数据 -- DetectCfg中的标定矩阵CaliMat和标定误差CaliErr
    DetectCfg DetectPara;  // 检测参数

    VisionOneToMoreCfg VisionOTMPara;  // 主从参数

    ConvCoorCfg()
    {
        Initialize();
    }

    void Initialize()
    {
        CoorId = 0;
        IsEnable = false;
        IsMonitor = false;
        CapPosCompPara.Initialize();
        BasicPara.Initialize();
        EncoderPara.Initialize();
        ObjCaliPara.Initialize();
        BoundaryPara.Initialize();
        DetectPara.Initialize();
        VisionOTMPara.Initialize();
    }

    void From(const ConvCoorCfg &other)
    {
        CoorId = other.CoorId;
        IsEnable = other.IsEnable;
        IsMonitor = other.IsMonitor;
        CapPosCompPara.From(other.CapPosCompPara);
        BasicPara.From(other.BasicPara);
        EncoderPara.From(other.EncoderPara);
        ObjCaliPara.From(other.ObjCaliPara);
        BoundaryPara.From(other.BoundaryPara);
        DetectPara.From(other.DetectPara);
        VisionOTMPara.From(other.VisionOTMPara);
    }
    bool Compare(const ConvCoorCfg &other)
    {
        if (CoorId != other.CoorId || IsEnable != other.IsEnable
            || IsMonitor != other.IsMonitor)
        {
            return false;
        }
        if (!CapPosCompPara.Compare(other.CapPosCompPara))
        {
            return false;
        }
        if (!BasicPara.Compare(other.BasicPara))
        {
            return false;
        }
        if (!EncoderPara.Compare(other.EncoderPara))
        {
            return false;
        }
        if (!ObjCaliPara.Compare(other.ObjCaliPara))
        {
            return false;
        }
        if (!BoundaryPara.Compare(other.BoundaryPara))
        {
            return false;
        }
        if (!DetectPara.Compare(other.DetectPara))
        {
            return false;
        }
        if (!VisionOTMPara.Compare(other.VisionOTMPara))
        {
            return false;
        }
        return true;
    }
};

// 主结构体
struct FollowCraftCfgIo
{
    vector<ConvCoorCfg> CoorCfgList;

    FollowCraftCfgIo()
    {
        for (int i = 0; i < CRAFT_FOLLOW_MAX_BELT_COUNT; i++)
        {
            ConvCoorCfg cfg;
            CoorCfgList.push_back(cfg);
        }
    }

    void Initialize()
    {
        for (size_t i = 0; i < CoorCfgList.size(); i++)
        {
            CoorCfgList[i].Initialize();
            CoorCfgList[i].CoorId = i;
            CoorCfgList[i].EncoderPara.Initialize();
            CoorCfgList[i].ObjCaliPara.Initialize();
            CoorCfgList[i].DetectPara.VisionPara.Initialize();
        }
    }

    void From(const FollowCraftCfgIo &other)
    {
        for (size_t i = 0; i < CoorCfgList.size(); i++)
        {
            CoorCfgList[i].From(other.CoorCfgList[i]);
        }
    }

    bool Compare(const FollowCraftCfgIo &other)
    {
        for (size_t i = 0; i < CoorCfgList.size(); i++)
        {
            if (!CoorCfgList[i].Compare(other.CoorCfgList[i]))
            {
                return false;
            }
        }
        return true;
    }
};

typedef struct stCnvorPara
{
    stCnvorPara()
    {
        i16BeltIndex = -1;
        i16Active = 0;
        i16BeltType = 0;
        i16CoordNum = -1;
        i16EncoderNum = -1;
        i16SensType = -1;

        dRatio = 0.0;

        memset(&dCatchHeight[0], 0x00, sizeof(double) * CRAFT_FOLLOW_MAX_CATCH_OBJ_COUNT);

        dUpEdge = 0.0;
        dDownEdge = 0.0;
        dAcptEdge = 0.0;
        dStopLength = 0.0;

        i16VTrigDoNum = 0;
        i16VTrigSigType = 0;
        dVTrigLen = 0.0;
        dObjRpetRmvLen = 0.0;

        i16SnsTrigDiNum = 0;
        i16SnsSignalType = 0;
        i16SnsObjType = 0;

        i16VisionDataType = 0;
        i64BeltCntPose = 0;
        i64BeltTrigPose = 0;
    }

    void SetParaByGrp(const struct stCnvorPara &other, UINT16 iGrpId)
    {
        switch (iGrpId)
        {
            case 0:
                SetParaGrp0(other);
                break;
            case 1:
                SetParaGrp1(other);
                break;
            case 2:
                SetParaGrp2(other);
                break;
            case 3:
                SetParaGrp3(other);
                break;
            case 4:
                SetParaGrp4(other);
                break;
            case 5:
                SetParaGrp5(other);
                break;
            case 6:
                SetParaGrp6(other);
                break;
            case 7:
                SetParaGrp7(other);
                break;
            default:
                {
                    SetParaGrp0(other);
                    SetParaGrp1(other);
                    SetParaGrp2(other);
                    SetParaGrp3(other);
                    SetParaGrp4(other);
                    SetParaGrp5(other);
                    SetParaGrp6(other);
                    SetParaGrp7(other);
                }
                break;
        }
    }

    void SetParaGrp0(const struct stCnvorPara &other)
    {
        i16BeltIndex = other.i16BeltIndex;
        i16Active = other.i16Active;
        i16BeltType = other.i16BeltType;
        i16CoordNum = other.i16CoordNum;
        i16EncoderNum = other.i16EncoderNum;
        i16SensType = other.i16SensType;
        stPosOffset = other.stPosOffset;
    }

    void SetParaGrp1(const struct stCnvorPara &other)
    {
        dRatio = other.dRatio;
    }

    void SetParaGrp2(const struct stCnvorPara &other)
    {
        dUpEdge = other.dUpEdge;
        dDownEdge = other.dDownEdge;
        dAcptEdge = other.dAcptEdge;
        dStopLength = other.dStopLength;
    }

    void SetParaGrp3(const struct stCnvorPara &other)
    {
        i16VTrigDoNum = other.i16VTrigDoNum;
        i16VTrigSigType = other.i16VTrigSigType;
        dVTrigLen = other.dVTrigLen;
        dObjRpetRmvLen = other.dObjRpetRmvLen;
        i16VisionDataType = other.i16VisionDataType;
    }

    void SetParaGrp4(const struct stCnvorPara &other)
    {
        i16SnsTrigDiNum = other.i16SnsTrigDiNum;
        i16SnsSignalType = other.i16SnsSignalType;
        i16SnsObjType = other.i16SnsObjType;
        stSnsTrigPos = other.stSnsTrigPos;
        dObjRpetRmvLen = other.dObjRpetRmvLen;  // 参数组4额外增加“重复剔除距离”
    }

    void SetParaGrp5(const struct stCnvorPara &other)
    {
        memcpy(&dCatchHeight[0], &other.dCatchHeight[0], sizeof(double) * CRAFT_FOLLOW_MAX_CATCH_OBJ_COUNT);
    }

    void SetParaGrp6(const struct stCnvorPara &other)
    {
        i64BeltCntPose = other.i64BeltCntPose;
    }

    void SetParaGrp7(const struct stCnvorPara &other)
    {
        i64BeltTrigPose = other.i64BeltTrigPose;
    }

    // 传送带基本参数，静态参数 -- 0
    INT16 i16BeltIndex;   // 传送带编号
    INT16 i16Active;      // 启动状态
    INT16 i16BeltType;    // 外部轴运动形式，平移、旋转
    INT16 i16CoordNum;    // 用户坐标系编号
    INT16 i16EncoderNum;  // 编码器通道
    INT16 i16SensType;    // 检测方式
    Pose stPosOffset;     // 抓取位置补偿量

    // 传送带编码器分辨率 -- 1
    double dRatio;

    // 工件抓取高度 -- 5
    double dCatchHeight[CRAFT_FOLLOW_MAX_CATCH_OBJ_COUNT];

    // 边界参数 -- 2
    double dUpEdge;      // 工作上届
    double dDownEdge;    // 工作下届
    double dAcptEdge;    // 拾取下届
    double dStopLength;  // 停止平滑距离

    // 视觉参数 -- 3
    INT16 i16VTrigDoNum;      // 触发相机信号输出 DO 口
    INT16 i16VTrigSigType;    // 触发信号类型：0-上升沿，1-下降沿
    double dVTrigLen;         // 触发相机的传输带间距
    double dObjRpetRmvLen;    // 视觉重复点检测判断距离
    INT16 i16VisionDataType;  // 视觉数据类型，0-机器人坐标，1-像素

    // 传感器参数 -- 4
    INT16 i16SnsTrigDiNum;   // 传感器信号输入IO口
    INT16 i16SnsSignalType;  // 传感器触发电平类型
    INT16 i16SnsObjType;     // 传感器检测到的物体类型编号
    Pose stSnsTrigPos;       // 光电传感器被触发时物体的坐标 //TODO Pose

    // 传送带当前位置  -- 6
    INT64 i64BeltCntPose;

    // 触发传感器时传送带的位置 -- 7
    INT64 i64BeltTrigPose;
} CNVOR_PARA;

typedef struct CnvorMonitorPara
{
    CnvorMonitorPara()
    {
        i64EncoderPos = 0;
        dBeltSpeed = 0;
        i16WorkpieceNum = 0;
        i32WorkpieceBeyoundBoundaryNum = 0;
        memset(&i16WorkpieceNo[0], 0x00, sizeof(i16WorkpieceNo));
        memset(&i16WorkpieceType[0], 0x00, sizeof(i16WorkpieceType));
        memset(&dWorkpieceDist[0], 0x00, sizeof(dWorkpieceDist));
        memset(&fWorkpiecePos[0], 0x00, sizeof(fWorkpiecePos));
    }

    INT64 i64EncoderPos;                   // 编码器位置
    double dBeltSpeed;                     // 传送带速度
    INT16 i16WorkpieceNum;                 // 工件检测数
    INT32 i32WorkpieceBeyoundBoundaryNum;  // 工件超界数
    INT16 i16WorkpieceNo[10];              // 工件号
    INT16 i16WorkpieceType[10];            // 工件类型
    float dWorkpieceDist[10];              // 工件距离
    float fWorkpiecePos[10][3];            // 工件坐标（x、y、A）
} CNVOR_MONITOR_PARA;

typedef struct CnvorOffsetPoint
{
    CnvorOffsetPoint()
    {
        beltType = 0;
        dist = 0.0;
        pointNum = 0;
        memset(&dWobjUFrame[0], 0, 6 * sizeof(double));
    }
    int beltType;                                                 // 传送带类型（0-直线型，1-圆盘形）
    double dist;                                                  // 偏移量
    int pointNum;                                                 // 点数量(1-9)传感器1个点，视觉9个点
    double dWobjUFrame[6];                                        // 用户坐标系数据
    CaliPoint teachPoints[CRAFT_FOLLOW_CALIB_POINT_COUNT];        // 示教点
    CaliPoint offsetTeachPoints[CRAFT_FOLLOW_CALIB_POINT_COUNT];  // 偏移后示教点
} CNVOR_OFFSET_POINT;

typedef struct CnvorCaliPoint
{
    CaliPoint imageInputPoints[CRAFT_FOLLOW_CALIB_POINT_COUNT];  // 视觉点
    CaliPoint robotInputPoints[CRAFT_FOLLOW_CALIB_POINT_COUNT];  // 示教点
} CNVOR_CALI_POINT;

typedef struct CnvorCaliErr
{
    CnvorCaliErr()
    {
        xAvgError = 0.0;
        yAvgError = 0.0;
        xMaxError = 0.0;
        yMaxError = 0.0;
        xMmPerPixel = 0.0;
        yMmPerPixel = 0.0;
        toolOffsetX = 0.0;
        toolOffsetY = 0.0;
    }

    double xAvgError;    // x方向平均误差
    double yAvgError;    // y方向平均误差
    double xMaxError;    // x方向最大误差
    double yMaxError;    // y方向最大误差
    double xMmPerPixel;  // x方向单位像素的尺寸
    double yMmPerPixel;  // y方向单位像素的尺寸
    double toolOffsetX;  // x方向工具偏移
    double toolOffsetY;  // y方向工具偏移
} CNVOR_CALI_ERR;

typedef struct CnvorCaliResult
{
    CnvorCaliResult()
    {
        memset(&caliMatrix[0], 0x00, 9 * sizeof(double));
    }

    double caliMatrix[9];      // 标定矩阵
    CnvorCaliErr caliErrPara;  // 标定误差
} CNVOR_CALI_RESULT;

#pragma pack(push)
#pragma pack(1)
// 视觉一拖多传送带坐标    注：为了实现上位机向下兼容,不要修改此结构体
typedef struct _VISION_ONETOMORE_TEULERPOS_
{
    _VISION_ONETOMORE_TEULERPOS_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(fItem, 0, sizeof(float) * 6);
    }

    float fItem[6];
} VisionOTMTeulerPos;

// 视觉一拖多像素坐标    注：为了实现上位机向下兼容,不要修改此结构体
typedef struct _VISION_ONETOMORE_TPIXELDATA_
{
    _VISION_ONETOMORE_TPIXELDATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        memset(fItem, 0, sizeof(float) * 3);
    }

    float fItem[3];
} VisionOTMTPixelData;

// 视觉一拖多从控视觉数据监控单个数据   注：为了实现上位机向下兼容,不要修改此结构体
typedef struct _VISION_ONETOMORE_VISIONDATA_
{
    _VISION_ONETOMORE_VISIONDATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16ObjIndex = 0;
        i16ObjType = 0;
        tarPos.Initialize();
        tarPixel.Initialize();
        i64TriggerPulse = 0;
        i16RobotIndex = 0;
    }
    INT16 i16ObjIndex;             // 传送带上工件序号
    INT16 i16ObjType;              // 工件类型
    VisionOTMTeulerPos tarPos;     // 传送带坐标
    VisionOTMTPixelData tarPixel;  // 像素坐标
    INT64 i64TriggerPulse;         // 编码器位置
    INT16 i16RobotIndex;           // 机器人编号
} VisionOTMVisionData;

// 视觉一拖多从控视觉数据监控数据
typedef struct _VISION_ONETOMORE_DETECT_VISIONDATA_
{
    _VISION_ONETOMORE_DETECT_VISIONDATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i8WorkPieceNum = 0;
        for (int i = 0; i < OTM_SLAVE_VISION_DATA_NUM; ++i)
        {
            visionData[i].Initialize();
        }
    }

    INT8 i8WorkPieceNum;  // 工件数量
    VisionOTMVisionData visionData[OTM_SLAVE_VISION_DATA_NUM];

    // 注：为了实现上位机向下兼容，若要新增变量，请在已有变量后追加
} VisionOTMDetectVisionData;

// 视觉一拖多主站监控视觉数据    注：为了实现上位机向下兼容,不要修改此结构体
typedef struct _VISION_DETECT_MASTER_DATA_
{
    _VISION_DETECT_MASTER_DATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i16WorkPieceType = 0;

        for (int i = 0; i < 6; ++i)
        {
            f32VisionData[i] = 0.0;
        }
    }

    INT16 i16WorkPieceType;  // 工件类型
    float f32VisionData[6];  // 工件传送带坐标
} MasterDetectObj;

// 视觉一拖多主控视觉数据监控数据
typedef struct _VISION_DETECT_DATA_
{
    _VISION_DETECT_DATA_()
    {
        Initialize();
    }

    void Initialize()
    {
        i8WorkPieceNum = 0;
        for (int i = 0; i < FOLLOW_CRAFT_OBJ_MAXNUM; ++i)
        {
            masterDetectObj[i].Initialize();
        }
    }

    INT8 i8WorkPieceNum;                                       // 工件数量
    MasterDetectObj masterDetectObj[FOLLOW_CRAFT_OBJ_MAXNUM];  // 工件解析结果

    // 注：为了实现上位机向下兼容，若要新增变量，请在已有变量后追加
} MasterDetectData;
#pragma pack(pop)

#pragma endregion
