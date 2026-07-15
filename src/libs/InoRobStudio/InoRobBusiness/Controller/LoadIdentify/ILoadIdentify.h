#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "signal_slot.h"
#include "GlobalDataTypes.h"


/*
    Migrate and optimize by LiaoChuanMing at 2024/02/26，负载辨识功能
*/
namespace InoRobBusiness
{

#pragma region 常量与数据类型

    /**
     * @brief 负载辨识类型
    */
    enum class IdentifyType
    {
        // 空载校准
        Calib = 0,
        // 工具的负载辨识
        TOOL,
        // 负载的负载辨识
        LOAD,
        // 未知
        UNKNOW,
    };

    /**
     * @brief 负载辨识状态
    */
    enum class IdentifyStatus
    {
        // 辨识中
        ING = 0,
        // 辨识完成
        FINISH,
        // 辨识失败
        FAIL,
    };

    /**
     * @brief 空载校准标识
    */
    enum class IdentifyCalibFlag
    {
        // 未空载校准
        NOT_DONE = 0,
        // 已空载校准
        DONE,
    };

#pragma pack(1) // 单字节对齐

    /**
     * @brief 负载辨识参数
    */
    typedef struct _LoadIdentifyData
    {
        _LoadIdentifyData()
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

        _LoadIdentifyData &operator=(const _LoadIdentifyData &other)
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

        bool operator==(const _LoadIdentifyData &other) const
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

        int8u identifyType;     // 辨识类型，0-空载校准，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
        int8u calibFlag;        // 空载校准标识，0-未校准，1-已校准，对应枚举IdentifyCalibFlag
        double mass;            // 校准的质量
        INT16 toolNo;           // 工具号
        INT16 loadNo;           // 负载号
        JPos pos[6];            // 空载校准或负载辨识点位
        float InstallAngleX;    // 安装角度，绕X旋转
        float InstallAngleY;    // 安装角度，绕Y旋转
        double traj3Speed;      // 轨迹3速度
        double traj2Speed;      // 轨迹2速度，仅用于Scara，默认30
        INT16 wobjNumber;       // 工件号
    }LoadIdentifyData;

    /**
     * @brief 负载辨识结果
    */
    typedef struct _LoadIdentifyResult
    {
        _LoadIdentifyResult()
        {
            Initialize();
        }

        void Initialize()
        {
            identifyType = 0;
            toolOrLoadNo = 0;
            resultData.InitZero();
        }

        _LoadIdentifyResult &operator=(const _LoadIdentifyResult &other)
        {
            this->identifyType = other.identifyType;
            this->toolOrLoadNo = other.toolOrLoadNo;
            this->resultData = other.resultData;

            return (*this);
        }

        INT16 identifyType;     // 辨识类型，1-工具的负载辨识，2-负载的负载辨识，对应枚举IdentifyType
        int16u toolOrLoadNo;    // 工具或者负载号
        LoadData resultData;    // 辨识结果数据

    }LoadIdentifyResult;

    /**
     * @brief 负载辨识推荐轨迹
     */
    typedef struct _LoadIdentifyRecommendTraj
    {
        _LoadIdentifyRecommendTraj()
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
    } LoadIdentifyRecommendTraj;

#pragma pack() // 单字节对齐

#pragma endregion 常量与数据类型

class INOROBBUSINESS_CLASS ILoadIdentify : public QObject
{
    Q_OBJECT

public:
    virtual ~ILoadIdentify() {}
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /**
     * @brief 开始负载辨识（或空载校准）
     * @param data 输入，负载辨识数据
     * @return 成功返回0，失败请见错误码
    */
    virtual int startIdentify(const LoadIdentifyData &data) = 0;
    /**
     * @brief 停止负载辨识（或空载校准）
     * @return 成功返回0，失败请见错误码
    */
    virtual int stopIdentify() = 0;
    /**
     * @brief 读取负载辨识运动轨迹
     * @param data 输出，负载辨识数据
     * @return 成功返回0，失败请见错误码
    */
    virtual int readIdentifyData(LoadIdentifyData &data) = 0;
    /**
     * @brief 读取负载辨识（或空载校准）状态
     * @param status 输出，辨识状态
     * @return成功返回0，失败请见错误码
    */
    virtual int readIdentifyStatus(IdentifyStatus &status) = 0;
    /**
     * @brief 读取负载辨识（或空载校准）结果
     * @param result 输出，辨识结果
     * @return 成功返回0，失败请见错误码
    */
    virtual int readIdentifyResult(LoadIdentifyResult &result) = 0;

    /**
     * @brief 获取当前的负载辨识类型
    */
    virtual IdentifyType getIdentifyType() = 0;
    /**
     * @brief 设置当前的负载辨识类型
     * @param type 输入，负载辨识类型
    */
    virtual void setIdentifyType(const IdentifyType &type) = 0;

    /**
     * @brief 读取控制器存储的辨识轨迹
     * @param trajPoint 辨识轨迹的点位信息
     * @return 成功返回0，失败请见错误码
    */
    virtual int readIdentifyTrajectoryFromRc(float trajPoint[6][6]) = 0;

    /**
     * @brief 获取推荐的负载辨识轨迹
     * @param pointIndex 轨迹点位下标
     * @param recommendTraj 推荐轨迹数据
     * @param isOneTraj 是否为单一轨迹
     * @return 
    */
    virtual int readIdentifyRecommenPoint(int pointIndex, LoadIdentifyRecommendTraj recommendTraj, float identifyPoint[6][6], bool isOneTraj) = 0;

    /**
     * @brief 开始七轴负载辨识（或空载校准）
     * @param data 输入，负载辨识数据
     * @return 成功返回0，失败请见错误码
     */
    virtual int startSevenIdentify(const LoadIdentifyData &data) = 0;
};
}  // namespace InoRobBusiness
