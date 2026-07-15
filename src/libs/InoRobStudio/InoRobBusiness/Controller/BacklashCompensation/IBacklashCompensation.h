#pragma once
#include <string>
#include "DataTypeDef.h"
#include "GlobalDataTypes.h"
#include <QObject>

namespace InoRobBusiness
{

// 间隙辨识
typedef struct _AT_BacklashIdentificationParam_
{
    int16_t jointIndex;                 /* 关节索引,从0开始 */
    std::array<double, 6> startPoint;   /* 起点 */
    std::array<double, 6> endPoint;     /* 终点 */
    _AT_BacklashIdentificationParam_ &operator=(const _AT_BacklashIdentificationParam_ &other)
    {
        this->jointIndex = other.jointIndex;
        this->startPoint = other.startPoint;
        this->endPoint = other.endPoint;
        return (*this);
    }
} AT_BacklashIdentificationParam;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_BacklashIdentificationParam, jointIndex, startPoint, endPoint)

// 间隙辨识 - 获取辨识结果
typedef struct _AT_BacklashIdentificationResult_
{
    int result;                      /* 执行结果，0表示成功，否则表示失败 */
    float f32Backlash;               /* 间隙参数 */
    _AT_BacklashIdentificationResult_ &operator=(const _AT_BacklashIdentificationResult_ &other)
    {
        this->result = other.result;
        this->f32Backlash = other.f32Backlash;
        return (*this);
    }
} AT_BacklashIdentificationResult;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_BacklashIdentificationResult, result, f32Backlash)


// 间隙辨识 - 设置轨迹速度
typedef struct _AT_STBacklshIdentTrajVel_
{
    std::array<double, 5>  vel;                      /* 速度 */
    _AT_STBacklshIdentTrajVel_ &operator=(const _AT_STBacklshIdentTrajVel_ &other)
    {
        this->vel = other.vel;
        return (*this);
    }
} AT_STBacklshIdentTrajVel;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_STBacklshIdentTrajVel, vel)

// 间隙辨识 - 间隙参数
typedef struct _AT_STBacklshIdentParam_
{
    int16_t u16IsUseBacklashIdentifyResult;                     /* 是否使用间隙辨识 */
    std::array<int16_t, 6> i16ReducerType;                      /* 减速机类型: 0-RV减速机， 1-谐波减速机 */
    std::array<float, 6>   f32BacklashIdentifyActualPercent;    /* 间隙辨识实际百分比 */
    std::array<float, 6>   jointBacklash;                       /* 间隙:6关节 */
    _AT_STBacklshIdentParam_ &operator=(const _AT_STBacklshIdentParam_ &other)
    {
        this->u16IsUseBacklashIdentifyResult = other.u16IsUseBacklashIdentifyResult;
        this->i16ReducerType = other.i16ReducerType;
        this->f32BacklashIdentifyActualPercent = other.f32BacklashIdentifyActualPercent;
        this->jointBacklash = other.jointBacklash;
        return (*this);
    }
} AT_STBacklshIdentParam;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_STBacklshIdentParam, u16IsUseBacklashIdentifyResult, i16ReducerType, f32BacklashIdentifyActualPercent, jointBacklash)

#pragma pack(1) // 单字节对齐

// 间隙辨识计算轨迹, 上位机与ARM数据、ARM数据与dsp
typedef struct _BacklashCalcTraj_
{
    int    jointIndex;
    double point[2][6];  // 推荐轨迹点位(单位°)
} BacklashIdentifyCalcTraj;

// 间隙辨识轨迹速度 上位机数据与ARM
typedef struct _BacklashIdentTrajVel_
{
    double vel[5];              // 速度百分比
} BacklashIdentTrajVel;

// 间隙辨识结果, 上位机数据与ARM
typedef struct _BacklashIdentifyResult_
{
    int16_t u16IsUseBacklashIdentifyResult;         /* 是否使用间隙辨识 */
    int16_t i16ReducerType[6];                      /* 减速机类型: 0-RV减速机， 1-谐波减速机 */
    float f32BacklashIdentifyActualPercent[6];      /* 间隙辨识实际百分比 */
    float jointBacklash[6];                         /* 间隙:6关节 */
} BacklashIdentifyResult;


#pragma pack() // 单字节对齐

class IBacklashCompensation : public QObject
{
    Q_OBJECT

public:
    virtual ~IBacklashCompensation(){}

    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

    /*!
     * \brief 恢复出厂值
     */
    virtual int restoreFactorySettings() = 0;

    /*!
     * \brief 开始间隙辨识
     */
    virtual int startBacklashIdentification(BacklashIdentifyCalcTraj& calcTraj) = 0;

    /*!
     * \brief 终止间隙辨识
     */
    virtual int endBacklashIdentification() = 0;

    /*!
     * \brief 获取辨识结果
     */
    virtual int getRecognitionResult(float& f32Backlash) = 0;

    /*!
     * \brief 设置间隙辨识轨迹速度
     */
    virtual int setBacklashIdentTraj4Vel(BacklashIdentTrajVel trajVel) = 0;

    /*!
     * \brief 设置间隙补偿开关状态及相关参数，当为关闭时，库伦间隙系数无效
     */
    virtual int setBacklashCompensationStatus(const BacklashIdentifyResult& coulombArray) = 0;

    /*!
     * \brief 获取间隙参数
     */
    virtual int getBacklashParams(BacklashIdentifyResult& coulombArray) = 0;

};
}  // namespace InoRobBusiness
