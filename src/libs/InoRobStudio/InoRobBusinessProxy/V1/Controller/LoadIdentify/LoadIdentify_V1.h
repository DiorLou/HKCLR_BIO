#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../../GlobalDataTypes_V1.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
#pragma region 常量与数据类型

/**
 * @brief 负载辨识类型
 */
enum class IdentifyType_V1
{
    // 空载校准
    Calib_V1 = 0,
    // 工具的负载辨识
    TOOL_V1,
    // 负载的负载辨识
    LOAD_V1,
    // 未知
    UNKNOW_V1,
};

/**
 * @brief 负载辨识状态
 */
enum class IdentifyStatus_V1
{
    // 辨识中
    ING_V1 = 0,
    // 辨识完成
    FINISH_V1,
    // 辨识失败
    FAIL_V1,
};

/**
 * @brief 空载校准标识
 */
enum class IdentifyCalibFlag_V1
{
    // 未空载校准
    NOT_DONE_V1 = 0,
    // 已空载校准
    DONE_V1,
};

/**
 * @brief 负载辨识参数
 */
typedef struct _LoadIdentifyData_V1
{
    _LoadIdentifyData_V1()
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
        for (size_t i = 0; i < 6; i++)
        {
            pos[i].Initialize();
        }
        InstallAngleX = 0;
        InstallAngleY = 0;
        traj3Speed = 100;
        traj2Speed = 30;
        wobjNumber = 0;
    }

    _LoadIdentifyData_V1 &operator=(const _LoadIdentifyData_V1 &other)
    {
        this->identifyType = other.identifyType;
        this->calibFlag = other.calibFlag;
        this->mass = other.mass;
        this->toolNo = other.toolNo;
        this->loadNo = other.loadNo;
        for (size_t i = 0; i < 6; i++)
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

    bool operator==(const _LoadIdentifyData_V1 &other) const
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

        for (size_t i = 0; i < 6; i++)
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

    int8u identifyType;   // 辨识类型，0-空载校准，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
    int8u calibFlag;      // 空载校准标识，0-未校准，1-已校准，对应枚举IdentifyCalibFlag
    double mass;          // 校准的质量
    INT16 toolNo;         // 工具号
    INT16 loadNo;         // 负载号
    JPos_V1 pos[6];          // 空载校准或负载辨识点位
    float InstallAngleX;  // 安装角度，绕X旋转
    float InstallAngleY;  // 安装角度，绕Y旋转
    double traj3Speed;    // 轨迹3速度
    double traj2Speed;    // 轨迹2速度，仅用于Scara，默认30
    INT16 wobjNumber;     // 工件号
} LoadIdentifyData_V1;

/**
 * @brief 负载辨识结果
 */
typedef struct _LoadIdentifyResult_V1
{
    _LoadIdentifyResult_V1()
    {
        Initialize();
    }

    void Initialize()
    {
        identifyType = 0;
        toolOrLoadNo = 0;
        resultData.InitZero();
    }

    _LoadIdentifyResult_V1 &operator=(const _LoadIdentifyResult_V1 &other)
    {
        this->identifyType = other.identifyType;
        this->toolOrLoadNo = other.toolOrLoadNo;
        this->resultData = other.resultData;

        return (*this);
    }

    INT16 identifyType;      // 辨识类型，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
    int16u toolOrLoadNo;     // 工具或者负载号
    LoadData_V1 resultData;  // 辨识结果数据

} LoadIdentifyResult_V1;

/**
 * @brief 负载辨识推荐轨迹
 */
typedef struct _LoadIdentifyRecommendTraj_V1
{
    _LoadIdentifyRecommendTraj_V1()
    {
        cmdFlag = 0;
        trajPointType = 0;
        trajNo = 0;
        installAngleX = 0;
        installAngleY = 0;
        memset(recommenPoint, 0, 6 * 6 * sizeof(float));
    }
    int8u cmdFlag;              // 操作标识  0：页面切换操作标识 1：编辑框更改标识
    int8u trajPointType;        // 轨迹点位类型  0：使用推荐点  1：使用当前位置点
    int8u trajNo;               // 轨迹号
    float installAngleX;        // 安装角度绕X
    float installAngleY;        // 安装角度绕Y
    float recommenPoint[6][6];  // 推荐轨迹
} LoadIdentifyRecommendTraj_V1;

#pragma endregion

class INOROBBUSINESSPROXY_CLASS LoadIdentify_V1
{
#pragma region 数据转换

public:
    static IdentifyType_V1 IdentifyType_ToProxy(IdentifyType identifyType);
    static IdentifyType IdentifyType_FromProxy(IdentifyType_V1 identifyType_V1);

    static IdentifyStatus_V1 IdentifyStatus_ToProxy(IdentifyStatus identifyStatus);
    static IdentifyStatus IdentifyStatus_FromProxy(IdentifyStatus_V1 identifyStatus_V1);

    static IdentifyCalibFlag_V1 IdentifyCalibFlag_ToProxy(IdentifyCalibFlag identifyCalibFlag);
    static IdentifyCalibFlag IdentifyCalibFlag_FromProxy(IdentifyCalibFlag_V1 identifyCalibFlag_V1);

    static bool LoadIdentifyData_ToProxy(const LoadIdentifyData &loadIdentifyData, LoadIdentifyData_V1 &loadIdentifyData_V1);
    static bool LoadIdentifyData_FromProxy(const LoadIdentifyData_V1 &loadIdentifyData_V1, LoadIdentifyData &loadIdentifyData);

    static bool LoadIdentifyResult_ToProxy(const LoadIdentifyResult &loadIdentifyResult, LoadIdentifyResult_V1 &loadIdentifyResult_V1);
    static bool LoadIdentifyResult_FromProxy(const LoadIdentifyResult_V1 &loadIdentifyResult_V1, LoadIdentifyResult &loadIdentifyResult);

    static bool LoadIdentifyRecommendTraj_ToProxy(const LoadIdentifyRecommendTraj &loadIdentifyRecommendTraj, LoadIdentifyRecommendTraj_V1 &loadIdentifyRecommendTraj_V1);
    static bool LoadIdentifyRecommendTraj_FromProxy(const LoadIdentifyRecommendTraj_V1 &loadIdentifyRecommendTraj_V1, LoadIdentifyRecommendTraj &loadIdentifyRecommendTraj);
#pragma endregion

#pragma region 构造与析构

private:
    ILoadIdentify *_loadIdentify = nullptr;

public:
    LoadIdentify_V1(ILoadIdentify *loadIdentify);
    ~LoadIdentify_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 开始负载辨识（或空载校准）
     * @param data 输入，负载辨识数据
     * @return 成功返回0，失败请见错误码
     */
    int startIdentify(const LoadIdentifyData_V1 &data);
    /**
     * @brief 停止负载辨识（或空载校准）
     * @return 成功返回0，失败请见错误码
     */
    int stopIdentify();
    /**
     * @brief 读取负载辨识运动轨迹
     * @param data 输出，负载辨识数据
     * @return 成功返回0，失败请见错误码
     */
    int readIdentifyData(LoadIdentifyData_V1 &data);
    /**
     * @brief 读取负载辨识（或空载校准）状态
     * @param status 输出，辨识状态
     * @return成功返回0，失败请见错误码
     */
    int readIdentifyStatus(IdentifyStatus_V1 &status);
    /**
     * @brief 读取负载辨识（或空载校准）结果
     * @param result 输出，辨识结果
     * @return 成功返回0，失败请见错误码
     */
    int readIdentifyResult(LoadIdentifyResult_V1 &result);

    /**
     * @brief 获取当前的负载辨识类型
     */
    IdentifyType_V1 getIdentifyType();
    /**
     * @brief 设置当前的负载辨识类型
     * @param type 输入，负载辨识类型
     */
    void setIdentifyType(const IdentifyType_V1 &type);

    /**
     * @brief 读取控制器存储的辨识轨迹
     * @param trajPoint 辨识轨迹的点位信息
     * @return 成功返回0，失败请见错误码
     */
    int readIdentifyTrajectoryFromRc(float trajPoint[6][6]);

    /**
     * @brief 获取推荐的负载辨识轨迹
     * @param pointIndex 轨迹点位下标
     * @param recommendTraj 推荐轨迹数据
     * @param isOneTraj 是否为单一轨迹
     * @return
     */
    int readIdentifyRecommenPoint(int pointIndex, const LoadIdentifyRecommendTraj_V1 &recommendTraj, float identifyPoint[6][6], bool isOneTraj);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
