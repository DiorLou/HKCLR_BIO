#pragma once
#include <string>
#include "DataTypeDef.h"
#include "GlobalDataTypes.h"
#include <QObject>

namespace InoRobBusiness
{

/**
 * @brief 自动化测试接口
 */
// 摩擦辨识轨迹速度
typedef struct _AT_STSetFricIdentTrajVel_
{
    std::array<double, 4>  vel;                      /* 速度 */
    _AT_STSetFricIdentTrajVel_ &operator=(const _AT_STSetFricIdentTrajVel_ &other)
    {
        this->vel = other.vel;
        return (*this);
    }
} AT_STSetFricIdentTrajVel;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_STSetFricIdentTrajVel, vel)

/**
 * @brief 摩擦辨识推荐轨迹
 */
typedef struct _AT_FricIdentifyRecommendTraj
{
    int result;        /**< 执行结果，0表示成功，否则表示失败 */
    std::array<double, 6> recommenPoint;  // 推荐轨迹点位(单位°)

    _AT_FricIdentifyRecommendTraj()
    {
        result = 0;
    }

    _AT_FricIdentifyRecommendTraj &operator=(const _AT_FricIdentifyRecommendTraj &other)
    {
        this->result = other.result;
        this->recommenPoint = other.recommenPoint;
        return (*this);
    }
} AT_FricIdentifyRecommendTraj;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_FricIdentifyRecommendTraj, result, recommenPoint)

/**
 * @brief 摩擦辨识轨迹
 */
typedef struct _AT_FricIdentifyTraj
{
    std::array<std::array<double, 6>, 2> point;  // 轨迹点位(单位°)
    _AT_FricIdentifyTraj &operator=(const _AT_FricIdentifyTraj &other)
    {
        this->point = other.point;
        return (*this);
    }

} AT_FricIdentifyTraj;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_FricIdentifyTraj, point)

// 摩擦辨识结果 - 库伦系数
typedef struct _AT_FricCompParam_
{
    int result;                                            /**< 执行结果，0表示成功，否则表示失败 */
    std::array<float, 6>  f32FricIdentifyActualPercent;    /* 摩擦辨识实际百分比 */
    std::array<float, 6>  coulomb;                         /* 库伦摩擦:6关节 */
    _AT_FricCompParam_ &operator=(const _AT_FricCompParam_ &other)
    {
        this->result = other.result;
        this->f32FricIdentifyActualPercent = other.f32FricIdentifyActualPercent;
        this->coulomb = other.coulomb;
        return (*this);
    }
} AT_FricCompParam;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_FricCompParam, result, f32FricIdentifyActualPercent, coulomb)

// 设置摩擦辨识参数
typedef struct _AT_SetFricCompParam_
{
    std::array<float, 6>  coulomb;                      /* 库伦摩擦系数:6关节 */
    std::array<float, 6>  coulombIsSelectFlag;          /* 1:补偿； 0：不补偿 */
    _AT_SetFricCompParam_ &operator=(const _AT_SetFricCompParam_ &other)
    {
        this->coulomb = other.coulomb;
        this->coulombIsSelectFlag = other.coulombIsSelectFlag;
        return (*this);
    }
} AT_SetFricCompParam;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_SetFricCompParam, coulomb, coulombIsSelectFlag)



// 摩擦辨识参数
typedef struct _AT_SetFricCompensationParam_
{
    int16_t u16IsUseFricIdentifyResult;                 /* 是否使用摩擦辨识 */
    std::array<float, 6> f32FricIdentifyActualPercent;  /* 摩擦辨识实际百分比,从0-200% */
    std::array<float, 6> coulomb;                       /* 库伦摩擦:6关节 */
    _AT_SetFricCompensationParam_ &operator=(const _AT_SetFricCompensationParam_ &other)
    {
        this->u16IsUseFricIdentifyResult = other.u16IsUseFricIdentifyResult;
        this->f32FricIdentifyActualPercent = other.f32FricIdentifyActualPercent;
        this->coulomb = other.coulomb;
        return (*this);
    }
} AT_SetFricCompensationParam;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AT_SetFricCompensationParam, u16IsUseFricIdentifyResult, f32FricIdentifyActualPercent, coulomb)


#pragma pack(1) // 单字节对齐

// 摩擦辨识推荐轨迹, 上位机与ARM数据、ARM数据与dsp(根据第一个点获取推荐点位信息)
typedef struct _FricIdentifyRecommendTraj_
{
    double recommenPoint[2][6];  // 推荐轨迹点位(单位°)
} FricIdentifyRecommendTraj;

//摩擦辨识计算轨迹, 上位机与ARM数据、ARM数据与dsp
typedef struct _FricIdentifyCalcTraj_
{
    double point[2][6];  // 推荐轨迹点位(单位°)
} FricIdentifyCalcTraj;

// 摩擦辨识轨迹速度 上位机数据与ARM
typedef struct _FricIdentTrajVel_
{
    double vel[4];              // 速度百分比
} FricIdentTrajVel;

// 摩擦辨识结果 - 库伦系数, 上位机数据与ARM
typedef struct _FricIdentifyResult_
{
    int16_t u16IsUseFricIdentifyResult;         /* 是否使用摩擦辨识 */
    float   f32FricIdentifyActualPercent[6];    /* 摩擦辨识实际百分比,从0-200% */
    float   coulomb[6];                           /* 库伦摩擦:6关节 */
} FricIdentifyResult;

// 摩擦辨识结果 - 库伦系数, 上位机数据与ARM
typedef struct _FricCompParam_
{
    float f32FricIdentifyActualPercent[6];    /* 摩擦辨识实际百分比 */
    float coulomb[6];                         /* 库伦摩擦:6关节 */

    // _FricCompParam_ &operator=(const _FricCompParam_ &other)
    // {
    //     for (int i = 0; i < 6; ++i)
    //     {
    //         f32FricIdentifyActualPercent[i] = other.f32FricIdentifyActualPercent[i];
    //         coulomb[i] = other.coulomb[i];
    //     }
    //     return (*this);
    // }
} FricCompParam;

// 设置摩擦辨识参数, 上位机数据到ARM
typedef struct _ToArmFricParam_
{
    double coulomb[6];              // 库伦摩擦系数:6关节
    int8u coulombIsSelectFlag[6];   // 1:补偿； 0：不补偿
} ToArmFricParam;

// 设置是否打开摩擦补偿开关及对应参数
typedef struct _TurnOnFricCompSwichParam_
{
    int16u isTurnOn;               // 1:打开； 0：关闭
    float coulomb[6];              // 库伦摩擦系数:6关节
} TurnOnFricCompSwichParam;

#pragma pack() // 单字节对齐

class IFrictionCompensation : public QObject
{
    Q_OBJECT

public:
    virtual ~IFrictionCompensation(){}

    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

    /*!
     * \brief 恢复出厂值
     */
    virtual int restoreFactorySettings() = 0;

    /*!
     * \brief 根据起点获取摩擦推荐轨迹点
     */
    virtual int getRecommendedTrajectoryEndPoints(FricIdentifyRecommendTraj& jointAngles) = 0;

    /*!
     * \brief 开始摩擦辨识
     */
    virtual int startFricIdentification(FricIdentifyCalcTraj& calcTraj) = 0;

    /*!
     * \brief 终止摩擦辨识
     */
    virtual int endFricIdentification() = 0;

    /*!
     * \brief 获取辨识结果
     */
    virtual int getRecognitionResult(FricCompParam& coulombArray) = 0;

    /*!
     * \brief 应用辨识结果
     */
    virtual int setRecognitionResult(ToArmFricParam coulombArray) = 0;

    /*!
     * \brief 设置摩擦辨识轨迹速度
     */
    virtual int setFricIdentTraj4Vel(FricIdentTrajVel trajVel) = 0;

    /*!
     * \brief 设置摩擦补偿开关状态及相关参数，当为关闭时，库伦摩擦系数无效
     */
    virtual int setFricCompensationStatus(const FricIdentifyResult& coulombArray) = 0;

    /*!
     * \brief 获取库伦摩擦参数
     */
    virtual int getCoulombFrictionParams(FricIdentifyResult& coulombArray) = 0;

    /**
     * @brief 设置摩擦辨识轨迹速度
     * @param at_fricIdentTrajVel 速度参数
     * @return 响应结果
     */
    //virtual int AT_SetFricIdentVel(AT_STSetFricIdentTrajVel at_fricIdentTrajVel) = 0;
};
}  // namespace InoRobBusiness
