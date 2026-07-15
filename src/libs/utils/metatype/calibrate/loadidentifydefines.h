#pragma once

#include <cmath>
#include <QString>

#include "motion/jpos.h"
#include "loadparams.h"

enum CobotIdentifyType
{
    // 空载校准
    CobotIdentifyType_Calib = 0,
    // 工具的负载辨识
    CobotIdentifyType_TOOL,
    // 负载的负载辨识
    CobotIdentifyType_LOAD,
    // 未知
    CobotIdentifyType_UNKNOW,
};

/**
 * @brief 负载辨识状态
 */
enum CobotIdentifyStatus
{
    // 辨识中
    CobotIdentifyStatus_ING = 0,
    // 辨识完成
    CobotIdentifyStatus_FINISH,
    // 辨识失败
    CobotIdentifyStatus_FAIL,
};

#pragma pack(1) // 单字节对齐

typedef struct stCobotLoadIdentifyData
{
    stCobotLoadIdentifyData()
    {
        Initialize();
    }

    void Initialize()
    {
        identifyType = 0;
        calibFlag = 0;
        mass = 0.0;
        toolNo = 0;
        loadNo = 0;
        for (int i = 0; i < 6; i++)
        {
            pos[i].Initialize();
        }
        InstallAngleX = 0;
        InstallAngleY = 0;
        traj3Speed = 100;
        traj2Speed = 30;
        wobjNumber = 0;
    }

    stCobotLoadIdentifyData &operator=(const stCobotLoadIdentifyData &other)
    {
        this->identifyType = other.identifyType;
        this->calibFlag = other.calibFlag;
        this->mass = other.mass;
        this->toolNo = other.toolNo;
        this->loadNo = other.loadNo;
        for (int i = 0; i < 6; i++)
        {
            this->pos[i] = other.pos[i];
        }
        this->InstallAngleX = other.InstallAngleX;
        this->InstallAngleY = other.InstallAngleY;
        this->traj3Speed = other.traj3Speed;
        this->traj2Speed = other.traj2Speed;
        this->wobjNumber = other.wobjNumber;

        return (*this);
    }

    bool operator==(const stCobotLoadIdentifyData &other) const
    {
        if (this->identifyType != other.identifyType)
        {
            return false;
        }

        if (this->calibFlag != other.calibFlag)
        {
            return false;
        }

        if (std::abs(this->mass - other.mass) > 0.000001)
        {
            return false;
        }

        if (this->toolNo != other.toolNo)
        {
            return false;
        }

        if (this->loadNo != other.loadNo)
        {
            return false;
        }

        for (int i = 0; i < 6; i++)
        {
            if (!(this->pos[i] == other.pos[i]))
            {
                return false;
            }
        }

        if (this->InstallAngleX != other.InstallAngleX)
        {
            return false;
        }

        if (this->InstallAngleY != other.InstallAngleY)
        {
            return false;
        }

        if (this->traj3Speed != other.traj3Speed)
        {
            return false;
        }

        if (this->traj2Speed != other.traj2Speed)
        {
            return false;
        }

        if (this->wobjNumber != other.wobjNumber)
        {
            return false;
        }

        return true;
    }

    quint8 identifyType;    // 辨识类型，0-空载校准，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
    quint8 calibFlag;       // 空载校准标识，0-未校准，1-已校准，对应枚举IdentifyCalibFlag
    double mass;            // 校准的质量
    qint16 toolNo;          // 工具号
    qint16 loadNo;          // 负载号
    JointPos pos[6];        // 空载校准或负载辨识点位
    float InstallAngleX;    // 安装角度，绕X旋转
    float InstallAngleY;    // 安装角度，绕Y旋转
    double traj3Speed;      // 轨迹3速度
    double traj2Speed;      // 轨迹2速度，仅用于Scara，默认30
    qint16 wobjNumber;      // 工件号
} CobotLoadIdentifyData;

typedef struct stCobotLoadIdentifyResult
{
    stCobotLoadIdentifyResult()
    {
        Initialize();
    }

    void Initialize()
    {
        identifyType = 0;
        toolOrLoadNo = 0;
        resultData.InitZero();
    }

    stCobotLoadIdentifyResult &operator=(const stCobotLoadIdentifyResult &other)
    {
        this->identifyType = other.identifyType;
        this->toolOrLoadNo = other.toolOrLoadNo;
        this->resultData = other.resultData;

        return (*this);
    }

    qint16 identifyType;     // 辨识类型，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
    quint16 toolOrLoadNo;    // 工具或者负载号
    LoadParams resultData;     // 辨识结果数据
} CobotLoadIdentifyResult;

typedef struct stCobotLoadIdentifyRecommendTraj
{
    stCobotLoadIdentifyRecommendTraj()
    {
        cmdFlag = 0;
        trajPointType = 0;
        trajNo = 0;
        installAngleX = 0;
        installAngleY = 0;
        memset(recommenPoint, 0, 6 * 6 * sizeof(float));
    }
    quint8 cmdFlag;              // 操作标识  0：页面切换操作标识 1：编辑框更改标识
    quint8 trajPointType;        // 轨迹点位类型  0：使用推荐点  1：使用当前位置点
    quint8 trajNo;               // 轨迹号
    float installAngleX;        // 安装角度绕X
    float installAngleY;        // 安装角度绕Y
    float recommenPoint[6][6];  // 推荐轨迹
} CobotLoadIdentifyRecommendTraj;

#pragma pack() // 单字节对齐
