/**
 * @File Name: wobjparams.h
 * @brief  : WorkPiece Params
 * @Author : yangchao email:yangchaoD@inovance.com
 * @Version : 1.0
 * @Creat Date : 2024-02-28
 * 
 * @Copyright (C), 2023-2024 inovance. Co., Ltd. All rights
 */
#ifndef WOBJPARAMS_H
#define WOBJPARAMS_H

#include <cstring>

#include "pos.h"
#include "ori.h"

// 机械单元名称最大长度
#define MAX_NAME_LEN_MECHUNIT (18)

enum Robot_WObjType
{
    Robot_WObjType_EXTERN_WOBJ  = 0,  
    Robot_WObjType_HOLD_WOBJ    = 1   
};

enum Robot_WObj_UFrame_CalMethod
{
    Robot_WObj_UFrame_CalMethod_NO_MODIFY   = 0,  // uframe无修改
    Robot_WObj_UFrame_CalMethod_THREE_POINT = 1,  // uframe三点法
    Robot_WObj_UFrame_CalMethodROTARY       = 2,  // uframe旋转法
};

enum Robot_WObj_OFrame_CalMethod
{
    Robot_WObj_OFrame_CalMethod_NO_MODIFY = 0,    // Oframe无修改
    Robot_WObj_OFrame_CalMethod_THREE_POINT = 1,  // Oframe三点法
};

typedef struct _WobjParams_
{
    _WobjParams_()
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
        memset(&UFMec, 0, MAX_NAME_LEN_MECHUNIT);
        UFramePos.init();
        UFrameOri.init();
        OFramePos.init();
        OFrameOri.init();
    }
    _WobjParams_ &operator=(const _WobjParams_ &other)
    {
        this->RobHold = other.RobHold;
        this->UFFix = other.UFFix;
        memcpy(&this->UFMec, &other.UFMec, MAX_NAME_LEN_MECHUNIT);
        this->UFramePos = other.UFramePos;
        this->UFrameOri = other.UFrameOri;
        this->OFramePos = other.OFramePos;
        this->OFrameOri = other.OFrameOri;
        return (*this);
    }
    bool operator==(const _WobjParams_ &other) const {
        bool bUFMec = false;
        if (strncmp(this->UFMec, other.UFMec, MAX_NAME_LEN_MECHUNIT) == 0) {
            bUFMec = true;
        } else {
            bUFMec = false;
        }
        return (this->RobHold == other.RobHold) &&
               (this->UFFix == other.UFFix) &&
               bUFMec&&
               (this->UFramePos == other.UFramePos) &&
               (fabs(this->UFrameOri.m_rx - other.UFrameOri.m_rx)<0.00001) &&
               (fabs(this->UFrameOri.m_ry - other.UFrameOri.m_ry)<0.00001) &&
               (fabs(this->UFrameOri.m_rz - other.UFrameOri.m_rz)<0.00001) &&
               (this->OFramePos == other.OFramePos) &&
               (fabs(this->OFrameOri.m_rx - other.OFrameOri.m_rx)<0.00001) &&
               (fabs(this->OFrameOri.m_ry - other.OFrameOri.m_ry)<0.00001) &&
               (fabs(this->OFrameOri.m_rz - other.OFrameOri.m_rz)<0.00001);
    }
    bool RobHold;                       /// > 工件是否夹持  true 夹持； FALSE 非夹持
    bool UFFix;                         /// > 工件是否固定（是否相对于大地坐标系固定、是否相对于法兰盘固定）
    char UFMec[MAX_NAME_LEN_MECHUNIT];  /// > 关联的机械单元名称
    Pos UFramePos;                      /// > 用户坐标位置
    Ori UFrameOri;                      /// > 用户坐标姿态
    Pos OFramePos;                      /// > 工件坐标位置
    Ori OFrameOri;                      /// > 工件坐标姿态
} WobjParams;  

#endif // WOBJPARAMS_H
