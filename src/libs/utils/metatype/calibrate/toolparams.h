/**
 * @File Name: ToolParams.h
 * @brief  : Add For Inovance Tool Calibrate, Replace Old Class ToolParam
 * @Author : yangchao email:yangchaoD@inovance.com
 * @Version : 1.0
 * @Creat Date : 2024-02-23
 * 
 * @Copyright (C), 2023-2024 inovance. Co., Ltd. All rights
 */
#ifndef TOOLPARAMS_H
#define TOOLPARAMS_H

#include "pos.h"
#include "ori.h"
#include "loadparams.h"

/**************************** CONST VAR ****************************************/

#define MAX_POINTS_NUM_CALIBRATE        (6)

#define NUM_ROB_CAL_ARM_ARGS            (4)
#define NUM_ROB_CAL_EXTERN_AXLE_ARGS    (6)

/***************************** ENUMS *******************************************/

enum Robot_MoveType
{
    Robot_MoveType_MovJ = 0,
    Robot_MoveType_MovL = 1
};

enum Robot_ToolCalibrateType
{
    Robot_ToolCalibrateType_Hold_3TCP       = 0,    
    Robot_ToolCalibrateType_Hold_3TCPZX     = 1,  
    Robot_ToolCalibrateType_Extern_1TCP     = 2,      
    Robot_ToolCalibrateType_Extern_1TCPZX   = 3,   
    Robot_ToolCalibrateType_Extern_3TCP     = 4,      
    Robot_ToolCalibrateType_Extern_3TCPZX   = 5
};

enum Robot_ToolType
{
    Robot_ToolType_EXTERN_TOOL  = 0,  
    Robot_ToolType_ROBOT_HOLD   = 1   
};

/***************************** STRUCTS *****************************************/

/// @brief Tool Params Desc
typedef struct _ToolParams_
{
    _ToolParams_()
    {
        InitZero();
    }
    void SetParams(bool robHold, const Pos &pos, const Ori &ori, const LoadParams &tLoad)
    {
        this->robHold = robHold;
        this->pos = pos;
        this->ori = ori;
        this->tLoad = tLoad;
    }
    void InitZero()
    {
        robHold = true;
        pos.init();
        ori.init();
        tLoad.InitZero();
    }
    _ToolParams_ &operator=(const _ToolParams_ &other)
    {
        this->robHold = other.robHold;
        this->pos = other.pos;
        this->ori = other.ori;
        this->tLoad = other.tLoad;
        return (*this);
    }
    bool operator==(const _ToolParams_ &other) const {
        return (this->robHold == other.robHold) &&
               (this->pos == other.pos) &&
               (fabs(this->ori.m_rx - other.ori.m_rx)<0.00001) &&
               (fabs(this->ori.m_ry - other.ori.m_ry)<0.00001) &&
               (fabs(this->ori.m_rz - other.ori.m_rz)<0.00001) &&
               (this->tLoad == other.tLoad);
    }
    bool robHold;       /// > whether tool is holded
    Pos pos;            /// > tool pos, x y z
    Ori ori;            /// > tool orient, A B C
    LoadParams tLoad;   /// > tool load params
} ToolParams;

/// @brief Robot Position Desc
typedef struct _RobCalPos_
{
    _RobCalPos_()
    {
        Initialize();
    }
    void Reset()
    {
        Initialize();
    }
    void Initialize()
    {
        pos.init();
        ori.init();

        for (int i = 0; i < NUM_ROB_CAL_ARM_ARGS; ++i)
        {
            ArmParm[i] = 0;
        }

        for (int i = 0; i < NUM_ROB_CAL_EXTERN_AXLE_ARGS; ++i) {
            EPosData[i] = 0.0f;
        }
    }

    _RobCalPos_ &operator=(const _RobCalPos_ &other)
    {
        this->pos = other.pos;
        this->ori = other.ori;

        for (int i = 0; i < NUM_ROB_CAL_ARM_ARGS; ++i) {
            this->ArmParm[i] = other.ArmParm[i];
        }  

        for (int i = 0; i < NUM_ROB_CAL_EXTERN_AXLE_ARGS; ++i) {
            this->EPosData[i] = other.EPosData[i];
        }   

        return (*this);
    }

    Pos pos; /// > calibrate point pos, x y z
    Ori ori; /// > calibrate point orient, A B C
    int ArmParm[NUM_ROB_CAL_ARM_ARGS]; /// > calibrate point arm params      
    double EPosData[NUM_ROB_CAL_EXTERN_AXLE_ARGS]; /// > calibrate external axle params
} RobCalPos;

/// @brief Calibrate Mid Points Desc
typedef struct _CalibratePoints_
{
    _CalibratePoints_()
    {
        Initialize();
    }

    void Initialize()
    {
        MethodType = 0;
        for (int i = 0; i < MAX_POINTS_NUM_CALIBRATE; i++)
        {
            Points[i].Initialize();
        }
    }

    _CalibratePoints_ &operator=(const _CalibratePoints_ &other)
    {
        this->MethodType = other.MethodType;
        for (int i = 0; i < MAX_POINTS_NUM_CALIBRATE; i++)
        {
            Points[i] = other.Points[i];
        }
        return (*this);
    }

    int MethodType;                                 /// > calibrate method
    RobCalPos Points[MAX_POINTS_NUM_CALIBRATE];     /// > calibrate points
} CalibratePoints;

#endif  // TOOLPARAMS_H
